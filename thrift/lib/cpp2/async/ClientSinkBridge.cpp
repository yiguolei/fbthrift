/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <thrift/lib/cpp2/async/ClientSinkBridge.h>

#include <folly/Overload.h>

namespace apache {
namespace thrift {
namespace detail {

// Explicitly instantiate the base of ClientSinkBridge
template class TwoWayBridge<
    ClientSinkConsumer,
    ClientMessage,
    ClientSinkBridge,
    ServerMessage,
    ClientSinkBridge>;

ClientSinkBridge::ClientSinkBridge(FirstResponseCallback* callback)
    : firstResponseCallback_(callback) {}

ClientSinkBridge::~ClientSinkBridge() {}

SinkClientCallback* ClientSinkBridge::create(FirstResponseCallback* callback) {
  return new ClientSinkBridge(callback);
}

void ClientSinkBridge::close() {
  serverClose();
  serverCallback_ = nullptr;
  evb_.reset();
  Ptr(this);
}

bool ClientSinkBridge::wait(ClientSinkConsumer* consumer) {
  return clientWait(consumer);
}

void ClientSinkBridge::push(ServerMessage&& value) {
  clientPush(std::move(value));
}

ClientSinkBridge::ClientQueue ClientSinkBridge::getMessages() {
  return clientGetMessages();
}

#if FOLLY_HAS_COROUTINES

folly::coro::Task<folly::Try<StreamPayload>> ClientSinkBridge::sink(
    folly::coro::AsyncGenerator<folly::Try<StreamPayload>&&> generator) {
  const auto& clientCancelToken =
      co_await folly::coro::co_current_cancellation_token;
  auto mergedToken = folly::CancellationToken::merge(
      serverCancelSource_.getToken(), clientCancelToken);
  auto makeCancellationCallback = [&] {
    return folly::CancellationCallback{
        clientCancelToken, [&]() {
          if (auto* cancelledCb = cancelClientWait()) {
            cancelledCb->canceled();
          }
        }};
  };

  for (uint64_t credits = 0; !serverCancelSource_.isCancellationRequested();
       credits--) {
    if (credits == 0) {
      if (CoroConsumer consumer; clientWait(&consumer)) {
        auto cb = makeCancellationCallback();
        co_await consumer.wait();
      }

      for (auto queue = clientGetMessages(); !queue.empty(); queue.pop()) {
        auto& message = queue.front();
        if (auto* n = std::get_if<uint64_t>(&message)) {
          credits += *n;
        } else {
          co_return std::get<folly::Try<StreamPayload>>(std::move(message));
        }
      }

      if (clientCancelToken.isCancellationRequested()) {
        clientPush(folly::Try<apache::thrift::StreamPayload>(
            rocket::RocketException(rocket::ErrorCode::CANCELED)));
        co_yield folly::coro::co_cancelled;
      }
    }

    auto item = co_await folly::coro::co_withCancellation(
        mergedToken, generator.next());
    if (serverCancelSource_.isCancellationRequested()) {
      break;
    }

    if (clientCancelToken.isCancellationRequested()) {
      clientPush(folly::Try<apache::thrift::StreamPayload>(
          rocket::RocketException(rocket::ErrorCode::CANCELED)));
      co_yield folly::coro::co_cancelled;
    }

    if (item.has_value()) {
      if ((*item).hasValue()) {
        clientPush(std::move(*item));
      } else {
        clientPush(std::move(*item));
        // AsyncGenerator who serialized and yield the exception also in
        // charge of propagating it back to user, just return empty Try
        // here.
        co_return folly::Try<StreamPayload>();
      }
    } else {
      clientPush({});
      // release generator
      generator = {};
      break;
    }
  }

  // Generator is done or server cancel source signalled: wait for final respose
  while (true) {
    if (CoroConsumer consumer; clientWait(&consumer)) {
      auto cb = makeCancellationCallback();
      co_await consumer.wait();
    }

    for (auto queue = clientGetMessages(); !queue.empty(); queue.pop()) {
      auto& message = queue.front();
      if (auto* response = std::get_if<folly::Try<StreamPayload>>(&message)) {
        co_return std::move(*response);
      }
    }

    if (clientCancelToken.isCancellationRequested()) {
      if (!serverCancelSource_.isCancellationRequested()) {
        clientPush(folly::Try<apache::thrift::StreamPayload>(
            rocket::RocketException(rocket::ErrorCode::CANCELED)));
      }
      co_yield folly::coro::co_cancelled;
    }
  }
}

#endif

void ClientSinkBridge::cancel(folly::Try<StreamPayload> payload) {
  CHECK(payload.hasException());
  clientPush(std::move(payload));
}

// SinkClientCallback method
bool ClientSinkBridge::onFirstResponse(
    FirstResponsePayload&& firstPayload,
    folly::EventBase* evb,
    SinkServerCallback* serverCallback) {
  auto firstResponseCallback = firstResponseCallback_;
  serverCallback_ = serverCallback;
  evb_ = folly::getKeepAliveToken(evb);
  bool scheduledWait = serverWait(this);
  DCHECK(scheduledWait);
  firstResponseCallback->onFirstResponse(std::move(firstPayload), copy());
  return true;
}

void ClientSinkBridge::onFirstResponseError(folly::exception_wrapper ew) {
  firstResponseCallback_->onFirstResponseError(std::move(ew));
  close();
}

void ClientSinkBridge::onFinalResponse(StreamPayload&& payload) {
  serverPush(folly::Try<StreamPayload>(std::move(payload)));
  serverCancelSource_.requestCancellation();
  close();
}

void ClientSinkBridge::onFinalResponseError(folly::exception_wrapper ew) {
  using apache::thrift::detail::EncodedError;
  auto rex = ew.get_exception<rocket::RocketException>();
  auto payload = rex
      ? folly::Try<StreamPayload>(EncodedError(rex->moveErrorData()))
      : folly::Try<StreamPayload>(std::move(ew));
  serverPush(std::move(payload));
  serverCancelSource_.requestCancellation();
  close();
}

bool ClientSinkBridge::onSinkRequestN(uint64_t n) {
  serverPush(n);
  return true;
}

void ClientSinkBridge::resetServerCallback(SinkServerCallback& serverCallback) {
  serverCallback_ = &serverCallback;
}

void ClientSinkBridge::consume() {
  DCHECK(evb_);
  evb_->runInEventBaseThread(
      [self = copy()]() mutable { self->processServerMessages(); });
}

void ClientSinkBridge::processServerMessages() {
  if (!serverCallback_) {
    return;
  }

  do {
    for (auto messages = serverGetMessages(); !messages.empty();
         messages.pop()) {
      bool terminated = false;
      auto& payload = messages.front();
      if (payload.hasException()) {
        serverCallback_->onSinkError(std::move(payload).exception());
        terminated = true;
      } else if (payload.hasValue()) {
        terminated = !serverCallback_->onSinkNext(std::move(payload).value());
      } else {
        terminated = !serverCallback_->onSinkComplete();
      }

      if (terminated) {
        close();
        return;
      }
    }
  } while (!serverWait(this));
}

bool ClientSinkBridge::hasServerCancelled() {
  return serverCancelSource_.isCancellationRequested();
}

} // namespace detail
} // namespace thrift
} // namespace apache

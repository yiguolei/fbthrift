{-
  Copyright (c) Facebook, Inc. and its affiliates.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
-}

{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE OverloadedStrings #-}
--
-- Licensed to the Apache Software Foundation (ASF) under one
-- or more contributor license agreements. See the NOTICE file
-- distributed with this work for additional information
-- regarding copyright ownership. The ASF licenses this file
-- to you under the Apache License, Version 2.0 (the
-- "License"); you may not use this file except in compliance
-- with the License. You may obtain a copy of the License at
--
--   http://www.apache.org/licenses/LICENSE-2.0
--
-- Unless required by applicable law or agreed to in writing,
-- software distributed under the License is distributed on an
-- "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
-- KIND, either express or implied. See the License for the
-- specific language governing permissions and limitations
-- under the License.
--

module Thrift.Transport.Empty
       ( EmptyTransport(..)
       ) where

import Thrift.Transport

-- | The Empty Transport has no reading or writing abilities and is permanently
-- closed.  It allows you to use 'Protocols' when you are only serializing and
-- deserializing 'ByteString's, not actually reading and writing
data EmptyTransport = EmptyTransport

instance Transport EmptyTransport where
    tIsOpen = const $ return False
    tClose  = const $ return ()
    tRead _ _ = return ""
    tPeek = const $ return Nothing
    tWrite _ _ = return ()
    tFlush = const$ return ()

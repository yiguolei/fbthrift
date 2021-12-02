#
# Autogenerated by Thrift
#
# DO NOT EDIT
#  @generated
#
from abc import ABCMeta
import typing as _typing

import folly.iobuf

from thrift.py3lite.serializer import serialize_iobuf, deserialize, Protocol
from thrift.py3lite.server import ServiceInterface, oneway, PythonUserException

import module.lite_types

class RaiserInterface(
    ServiceInterface,
    metaclass=ABCMeta
):

    @staticmethod
    def service_name() -> bytes:
        return b"Raiser"

    # pyre-ignore[3]: it can return anything
    def getFunctionTable(self) -> _typing.Mapping[bytes, _typing.Callable[..., _typing.Any]]:
        functionTable = {
            b"doBland": self._fbthrift__handler_doBland,
            b"doRaise": self._fbthrift__handler_doRaise,
            b"get200": self._fbthrift__handler_get200,
            b"get500": self._fbthrift__handler_get500,
        }
        return {**super().getFunctionTable(), **functionTable}



    async def doBland(
            self
        ) -> None:
        raise NotImplementedError("async def doBland is not implemented")

    async def _fbthrift__handler_doBland(self, args: folly.iobuf.IOBuf, protocol: Protocol) -> folly.iobuf.IOBuf:
        args_struct = deserialize(module.lite_types._fbthrift_Raiser_doBland_args, args, protocol)
        value = await self.doBland()
        return_struct = module.lite_types._fbthrift_Raiser_doBland_result()

        return serialize_iobuf(return_struct, protocol)


    async def doRaise(
            self
        ) -> None:
        raise NotImplementedError("async def doRaise is not implemented")

    async def _fbthrift__handler_doRaise(self, args: folly.iobuf.IOBuf, protocol: Protocol) -> folly.iobuf.IOBuf:
        args_struct = deserialize(module.lite_types._fbthrift_Raiser_doRaise_args, args, protocol)
        try:
            value = await self.doRaise()
            return_struct = module.lite_types._fbthrift_Raiser_doRaise_result()
        except module.lite_types.Banal as e:
            return_struct = module.lite_types._fbthrift_Raiser_doRaise_result(b=e)
            buf = serialize_iobuf(return_struct, protocol)
            exp = PythonUserException('Banal', str(e), buf)
            raise exp
        except module.lite_types.Fiery as e:
            return_struct = module.lite_types._fbthrift_Raiser_doRaise_result(f=e)
            buf = serialize_iobuf(return_struct, protocol)
            exp = PythonUserException('Fiery', str(e), buf)
            raise exp
        except module.lite_types.Serious as e:
            return_struct = module.lite_types._fbthrift_Raiser_doRaise_result(s=e)
            buf = serialize_iobuf(return_struct, protocol)
            exp = PythonUserException('Serious', str(e), buf)
            raise exp

        return serialize_iobuf(return_struct, protocol)


    async def get200(
            self
        ) -> str:
        raise NotImplementedError("async def get200 is not implemented")

    async def _fbthrift__handler_get200(self, args: folly.iobuf.IOBuf, protocol: Protocol) -> folly.iobuf.IOBuf:
        args_struct = deserialize(module.lite_types._fbthrift_Raiser_get200_args, args, protocol)
        value = await self.get200()
        return_struct = module.lite_types._fbthrift_Raiser_get200_result(success=value)

        return serialize_iobuf(return_struct, protocol)


    async def get500(
            self
        ) -> str:
        raise NotImplementedError("async def get500 is not implemented")

    async def _fbthrift__handler_get500(self, args: folly.iobuf.IOBuf, protocol: Protocol) -> folly.iobuf.IOBuf:
        args_struct = deserialize(module.lite_types._fbthrift_Raiser_get500_args, args, protocol)
        try:
            value = await self.get500()
            return_struct = module.lite_types._fbthrift_Raiser_get500_result(success=value)
        except module.lite_types.Fiery as e:
            return_struct = module.lite_types._fbthrift_Raiser_get500_result(f=e)
            buf = serialize_iobuf(return_struct, protocol)
            exp = PythonUserException('Fiery', str(e), buf)
            raise exp
        except module.lite_types.Banal as e:
            return_struct = module.lite_types._fbthrift_Raiser_get500_result(b=e)
            buf = serialize_iobuf(return_struct, protocol)
            exp = PythonUserException('Banal', str(e), buf)
            raise exp
        except module.lite_types.Serious as e:
            return_struct = module.lite_types._fbthrift_Raiser_get500_result(s=e)
            buf = serialize_iobuf(return_struct, protocol)
            exp = PythonUserException('Serious', str(e), buf)
            raise exp

        return serialize_iobuf(return_struct, protocol)


#include "stdafx.h"
#include "RPC.h"
#include "Parser.h"

namespace rpc
{

bool ParsePacketHeader(const void* _ptr, uint _size, PacketHeader& _hdr)
{
  static rpc::MethodCallHeader dummyHeader;
  if (_size < sizeof(uint) + sizeof(dummyHeader.data))
    return false;

  byte* ptr = (byte*)_ptr;
  rpc::MethodCallHeader* header = (rpc::MethodCallHeader*)(ptr+sizeof(uint));
  _hdr.classCrc = *((uint*)ptr);
  _hdr.methodId = header->id;
  return true;
}

}
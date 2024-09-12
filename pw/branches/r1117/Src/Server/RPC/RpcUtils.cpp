#include "stdafx.h"
#include "RpcUtils.h"
#include "ClassFactory.h"

namespace rpc 
{

void RemoteEntityInfo_::Clear()
{
  StrongMT<IRemoteEntity> entity = instance;
}



IRemoteEntity* RemoteEntityInfo_::InvokeSharedConstructor() 
{ 
  if (!handler->isFailed)
  {
    handler->Construct();
  } else
  {
    StrongMT<IRemoteEntity> temp = instance;
    instance = 0;
  }
  return instance;
}



const char * GetCallFailReason( rpc::CallResult::Enum result )
{
  switch (result)
  {
  case rpc::CallResult::OK: return "OK";
  case rpc::CallResult::DataCorruption: return "DataCorruption";
  case rpc::CallResult::WrongMethodId: return "WrongMethodId";
  case rpc::CallResult::WrongMethodCode: return "WrongMethodCode";
  case rpc::CallResult::LocalEntityNotFound: return "LocalEntityNotFound"; 
  case rpc::CallResult::StackCorruption: return "StackCorruption";

  default: return "<unknown>";
  }
}



void PrintData(const byte* data , int size)
{
  LOG_E(0).Trace("Data size: %d", size);
  int numBytes = size*6+1;
  char* buffer = new char [numBytes];
  char* ptr = buffer;
  for (int i=0;i<size && numBytes > 0;++i)
  {
    int usedBytes = NStr::Printf(ptr, numBytes, i>0?", 0x%02X":"0x%02X", data[i]);
    ptr += usedBytes;
    numBytes -= usedBytes;
  }
  LOG_E(0).Trace("Data: { %s };", buffer);
  delete [] buffer;
}

} // rpc

#include "TamarinPCH.h"

#include "BuiltinPools.h"
//NOTE that its not complete net namespace
#include "../Natives/net/URLRequest.h"
#include "net.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetNetPool( AvmCore * core )
  {
    return AVM_INIT_BUILTIN_ABC(net, core);
  }
}
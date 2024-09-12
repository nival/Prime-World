#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/systemInclude.h"
#include "system.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetSystemPool( AvmCore * core )
  {
    return AVM_INIT_BUILTIN_ABC(system, core);
  }
}
#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/testingInclude.h"
#include "testing.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetTestingPool( AvmCore * core )
  {
    return AVM_INIT_BUILTIN_ABC(testing, core);
  }
}
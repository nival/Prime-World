#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/utilsInclude.h"
#include "utils.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetUtilsPool(AvmCore * core)
  {
    return AVM_INIT_BUILTIN_ABC(utils, core);
  }
}
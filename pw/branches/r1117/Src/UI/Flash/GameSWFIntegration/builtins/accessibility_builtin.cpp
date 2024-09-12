#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/accessibilityInclude.h"
#include "accessibility.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetAccessibilityPool( AvmCore * core )
  {
    return AVM_INIT_BUILTIN_ABC(accessibility, core);
  }
}
#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/displayInclude.h"
#include "display.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetDisplayPool( AvmCore * core )
  {
    return AVM_INIT_BUILTIN_ABC(display, core);
  }
}
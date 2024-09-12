#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/textInclude.h"
#include "text.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetTextPool( AvmCore * core )
  {
    return AVM_INIT_BUILTIN_ABC(text, core);
  }
}
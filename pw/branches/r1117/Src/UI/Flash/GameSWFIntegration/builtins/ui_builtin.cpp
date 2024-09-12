#include "TamarinPCH.h"

#include "BuiltinPools.h" 
#include "../Natives/uiInclude.h"
#include "ui.cpp"


namespace avmplus
{
  PoolObject * BuiltinPools::GetUIPool(AvmCore * core)
  {
    return AVM_INIT_BUILTIN_ABC(ui, core);
  }
}

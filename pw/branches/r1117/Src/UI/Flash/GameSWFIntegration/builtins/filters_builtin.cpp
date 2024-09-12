#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/filtersInclude.h"
#include "filters.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetFiltersPool( AvmCore * core )
  {
    return AVM_INIT_BUILTIN_ABC(filters, core);
  }
}
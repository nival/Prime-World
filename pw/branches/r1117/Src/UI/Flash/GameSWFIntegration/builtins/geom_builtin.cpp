#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/geomInclude.h"
#include "geom.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetGeomPool( AvmCore * core )
  {
    return AVM_INIT_BUILTIN_ABC(geom, core);
  }
}
#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/xmlInclude.h"
#include "xml.cpp"

namespace avmplus
{
PoolObject * BuiltinPools::GetXMLPool(AvmCore * core)
{
  return AVM_INIT_BUILTIN_ABC(xml, core);
}
}


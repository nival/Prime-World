#include "TamarinPCH.h"

#include "BuiltinPools.h"
#include "../Natives/eventsInclude.h"
#include "events.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetEventsPool(AvmCore * core)
  {
    return AVM_INIT_BUILTIN_ABC(events, core);
  }
}
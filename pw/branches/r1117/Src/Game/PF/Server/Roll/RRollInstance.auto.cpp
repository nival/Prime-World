#include "stdafx.h"
#include "RRollInstance.auto.h"

DEFINE_RE_FACTORY( roll, RIInstance );

namespace rpc
{

template<>
void RegisterRemoteFactory(roll::RIInstance* factory)
{
  &factory_roll_RIInstance;
}

} // rpc

NI_DEFINE_REFCOUNT( roll::RIInstance )

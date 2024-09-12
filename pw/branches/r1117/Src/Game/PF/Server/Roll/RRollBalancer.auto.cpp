#include "stdafx.h"
#include "RRollBalancer.auto.h"

DEFINE_RE_FACTORY( roll, RIBalancer );

namespace rpc
{

template<>
void RegisterRemoteFactory(roll::RIBalancer* factory)
{
  &factory_roll_RIBalancer;
}

} // rpc

NI_DEFINE_REFCOUNT( roll::RIBalancer )

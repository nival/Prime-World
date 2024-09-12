#include "stdafx.h"
#include "RRollClient.auto.h"

DEFINE_RE_FACTORY( roll, RIClient );

namespace rpc
{

template<>
void RegisterRemoteFactory(roll::RIClient* factory)
{
  &factory_roll_RIClient;
}

} // rpc

NI_DEFINE_REFCOUNT( roll::RIClient )

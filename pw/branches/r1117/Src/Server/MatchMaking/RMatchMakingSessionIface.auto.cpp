#include "stdafx.h"
#include "RMatchMakingSessionIface.auto.h"

DEFINE_RE_FACTORY( MatchMaking, RISession );

namespace rpc
{

template<>
void RegisterRemoteFactory(MatchMaking::RISession* factory)
{
  &factory_MatchMaking_RISession;
}

} // rpc

NI_DEFINE_REFCOUNT( MatchMaking::RISession )

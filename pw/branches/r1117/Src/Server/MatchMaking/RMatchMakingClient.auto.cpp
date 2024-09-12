#include "stdafx.h"
#include "RMatchMakingClient.auto.h"

DEFINE_RE_FACTORY( MatchMaking, RIClient );

namespace rpc
{

template<>
void RegisterRemoteFactory(MatchMaking::RIClient* factory)
{
  &factory_MatchMaking_RIClient;
}

} // rpc

NI_DEFINE_REFCOUNT( MatchMaking::RIClient )

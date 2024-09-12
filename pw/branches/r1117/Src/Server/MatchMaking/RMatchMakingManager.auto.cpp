#include "stdafx.h"
#include "RMatchMakingManager.auto.h"

DEFINE_RE_FACTORY( MatchMaking, RManager );

namespace rpc
{

template<>
void RegisterRemoteFactory(MatchMaking::RManager* factory)
{
  &factory_MatchMaking_RManager;
}

} // rpc

NI_DEFINE_REFCOUNT( MatchMaking::RManager )

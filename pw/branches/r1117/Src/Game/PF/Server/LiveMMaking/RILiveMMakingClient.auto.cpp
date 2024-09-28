#include "stdafx.h"
#include "RILiveMMakingClient.auto.h"

DEFINE_RE_FACTORY( mmaking, RILiveMMakingClient );

namespace rpc
{

template<>
void RegisterRemoteFactory(mmaking::RILiveMMakingClient* factory)
{
  &factory_mmaking_RILiveMMakingClient;
}

} // rpc

NI_DEFINE_REFCOUNT( mmaking::RILiveMMakingClient )

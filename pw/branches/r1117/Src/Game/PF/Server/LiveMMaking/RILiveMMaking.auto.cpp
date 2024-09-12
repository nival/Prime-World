#include "stdafx.h"
#include "RILiveMMaking.auto.h"

DEFINE_RE_FACTORY( mmaking, RILiveMMaking );

namespace rpc
{

template<>
void RegisterRemoteFactory(mmaking::RILiveMMaking* factory)
{
  &factory_mmaking_RILiveMMaking;
}

} // rpc

NI_DEFINE_REFCOUNT( mmaking::RILiveMMaking )

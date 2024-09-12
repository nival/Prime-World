#include "stdafx.h"
#include "RGameBalancerIface.auto.h"

DEFINE_RE_FACTORY( GameBalancer, RIBalancerCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(GameBalancer::RIBalancerCallback* factory)
{
  &factory_GameBalancer_RIBalancerCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( GameBalancer::RIBalancerCallback )
DEFINE_RE_FACTORY( GameBalancer, RIBalancer );

namespace rpc
{

template<>
void RegisterRemoteFactory(GameBalancer::RIBalancer* factory)
{
  &factory_GameBalancer_RIBalancer;
}

} // rpc

NI_DEFINE_REFCOUNT( GameBalancer::RIBalancer )

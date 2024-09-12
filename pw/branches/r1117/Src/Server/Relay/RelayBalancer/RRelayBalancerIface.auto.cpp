#include "stdafx.h"
#include "RRelayBalancerIface.auto.h"

DEFINE_RE_FACTORY( Relay, RIBalancerCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(Relay::RIBalancerCallback* factory)
{
  &factory_Relay_RIBalancerCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( Relay::RIBalancerCallback )
DEFINE_RE_FACTORY( Relay, RIBalancer );

namespace rpc
{

template<>
void RegisterRemoteFactory(Relay::RIBalancer* factory)
{
  &factory_Relay_RIBalancer;
}

} // rpc

NI_DEFINE_REFCOUNT( Relay::RIBalancer )

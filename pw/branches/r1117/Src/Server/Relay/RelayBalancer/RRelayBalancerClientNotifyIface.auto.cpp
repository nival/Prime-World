#include "stdafx.h"
#include "RRelayBalancerClientNotifyIface.auto.h"

DEFINE_RE_FACTORY( Relay, RIOutgoingClientNotifySink );

namespace rpc
{

template<>
void RegisterRemoteFactory(Relay::RIOutgoingClientNotifySink* factory)
{
  &factory_Relay_RIOutgoingClientNotifySink;
}

} // rpc

NI_DEFINE_REFCOUNT( Relay::RIOutgoingClientNotifySink )
DEFINE_RE_FACTORY( Relay, RIIncomingClientNotifySink );

namespace rpc
{

template<>
void RegisterRemoteFactory(Relay::RIIncomingClientNotifySink* factory)
{
  &factory_Relay_RIIncomingClientNotifySink;
}

} // rpc

NI_DEFINE_REFCOUNT( Relay::RIIncomingClientNotifySink )

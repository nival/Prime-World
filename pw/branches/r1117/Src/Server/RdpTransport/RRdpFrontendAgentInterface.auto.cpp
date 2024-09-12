#include "stdafx.h"
#include "RRdpFrontendAgentInterface.auto.h"

DEFINE_RE_FACTORY( rdp_transport, RIFrontendAgent );

namespace rpc
{

template<>
void RegisterRemoteFactory(rdp_transport::RIFrontendAgent* factory)
{
  &factory_rdp_transport_RIFrontendAgent;
}

} // rpc

NI_DEFINE_REFCOUNT( rdp_transport::RIFrontendAgent )

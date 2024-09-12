#include "stdafx.h"
#include "RRdpFrontendAgentRemote.auto.h"

DEFINE_RE_FACTORY( rdp_transport, RIFrontendAgentRemote );

namespace rpc
{

template<>
void RegisterRemoteFactory(rdp_transport::RIFrontendAgentRemote* factory)
{
  &factory_rdp_transport_RIFrontendAgentRemote;
}

} // rpc

NI_DEFINE_REFCOUNT( rdp_transport::RIFrontendAgentRemote )

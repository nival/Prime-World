#include "stdafx.h"
#include "RClientControlRemote.auto.h"

DEFINE_RE_FACTORY( clientCtl, RIUserPresenceCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(clientCtl::RIUserPresenceCallback* factory)
{
  &factory_clientCtl_RIUserPresenceCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( clientCtl::RIUserPresenceCallback )
DEFINE_RE_FACTORY( clientCtl, RILoginSvcAllocationCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(clientCtl::RILoginSvcAllocationCallback* factory)
{
  &factory_clientCtl_RILoginSvcAllocationCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( clientCtl::RILoginSvcAllocationCallback )

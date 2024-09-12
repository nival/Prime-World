#include "stdafx.h"
#include "RGameServerDispenserIface.auto.h"

DEFINE_RE_FACTORY( HybridServer, RIGameServerDispenser );

namespace rpc
{

template<>
void RegisterRemoteFactory(HybridServer::RIGameServerDispenser* factory)
{
  &factory_HybridServer_RIGameServerDispenser;
}

} // rpc

NI_DEFINE_REFCOUNT( HybridServer::RIGameServerDispenser )
DEFINE_RE_FACTORY( HybridServer, RIGameServerDispenserCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(HybridServer::RIGameServerDispenserCallback* factory)
{
  &factory_HybridServer_RIGameServerDispenserCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( HybridServer::RIGameServerDispenserCallback )

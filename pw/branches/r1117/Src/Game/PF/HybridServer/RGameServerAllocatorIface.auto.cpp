#include "stdafx.h"
#include "RGameServerAllocatorIface.auto.h"

DEFINE_RE_FACTORY( HybridServer, RIGameServerAllocatorNotify );

namespace rpc
{

template<>
void RegisterRemoteFactory(HybridServer::RIGameServerAllocatorNotify* factory)
{
  &factory_HybridServer_RIGameServerAllocatorNotify;
}

} // rpc

NI_DEFINE_REFCOUNT( HybridServer::RIGameServerAllocatorNotify )
DEFINE_RE_FACTORY( HybridServer, RIGameServerAllocator );

namespace rpc
{

template<>
void RegisterRemoteFactory(HybridServer::RIGameServerAllocator* factory)
{
  &factory_HybridServer_RIGameServerAllocator;
}

} // rpc

NI_DEFINE_REFCOUNT( HybridServer::RIGameServerAllocator )

#include "stdafx.h"
#include "RCoordinatorServerIface.auto.h"

DEFINE_RE_FACTORY( Coordinator, RIRegisterClientCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(Coordinator::RIRegisterClientCallback* factory)
{
  &factory_Coordinator_RIRegisterClientCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( Coordinator::RIRegisterClientCallback )
DEFINE_RE_FACTORY( Coordinator, RICoordinatorServerRemote );

namespace rpc
{

template<>
void RegisterRemoteFactory(Coordinator::RICoordinatorServerRemote* factory)
{
  &factory_Coordinator_RICoordinatorServerRemote;
}

} // rpc

NI_DEFINE_REFCOUNT( Coordinator::RICoordinatorServerRemote )

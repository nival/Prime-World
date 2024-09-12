#include "stdafx.h"
#include "RCoordinatorClientIface.auto.h"

DEFINE_RE_FACTORY( Coordinator, RICoordinatorClientRemote );

namespace rpc
{

template<>
void RegisterRemoteFactory(Coordinator::RICoordinatorClientRemote* factory)
{
  &factory_Coordinator_RICoordinatorClientRemote;
}

} // rpc

NI_DEFINE_REFCOUNT( Coordinator::RICoordinatorClientRemote )

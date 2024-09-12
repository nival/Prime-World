#include "stdafx.h"
#include "RClusterAdminSvcIntf.auto.h"

DEFINE_RE_FACTORY( ClusterAdmin, RIClusterAdmin );

namespace rpc
{

template<>
void RegisterRemoteFactory(ClusterAdmin::RIClusterAdmin* factory)
{
  &factory_ClusterAdmin_RIClusterAdmin;
}

} // rpc

NI_DEFINE_REFCOUNT( ClusterAdmin::RIClusterAdmin )

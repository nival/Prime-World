#include "stdafx.h"
#include "RMonitoringIface.auto.h"

DEFINE_RE_FACTORY( Monitoring, RIMonitor );

namespace rpc
{

template<>
void RegisterRemoteFactory(Monitoring::RIMonitor* factory)
{
  &factory_Monitoring_RIMonitor;
}

} // rpc

NI_DEFINE_REFCOUNT( Monitoring::RIMonitor )

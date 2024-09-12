#include "stdafx.h"
#include "RPerfCounterProviderIface.auto.h"

DEFINE_RE_FACTORY( Monitoring, RIPerfCounterProvider );

namespace rpc
{

template<>
void RegisterRemoteFactory(Monitoring::RIPerfCounterProvider* factory)
{
  &factory_Monitoring_RIPerfCounterProvider;
}

} // rpc

NI_DEFINE_REFCOUNT( Monitoring::RIPerfCounterProvider )

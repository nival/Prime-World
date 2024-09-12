#include "stdafx.h"
#include "MonitoringCfg.h"

static int s_monThriftIfacePort = 8703;
REGISTER_VAR("mon_thrift_iface_port", s_monThriftIfacePort, STORAGE_GLOBAL);
static int s_monConsoleThriftIfacePort = 8707;
REGISTER_VAR("mon_console_thrift_iface_port", s_monConsoleThriftIfacePort, STORAGE_GLOBAL);
static unsigned int s_monProviderRepairTimeout = 30;
REGISTER_VAR("mon_provider_repair_timeout", s_monProviderRepairTimeout, STORAGE_GLOBAL);
static int s_monDefautlSamplingTimeout = 10;
REGISTER_VAR("mon_default_sampling_timeout", s_monDefautlSamplingTimeout, STORAGE_GLOBAL);

namespace Monitoring
{
  unsigned int Cfg::GetThriftIfacePort()
  {
    return s_monThriftIfacePort;
  }

  unsigned int Cfg::GetConsoleThriftIfacePort()
  {
    return s_monConsoleThriftIfacePort;
  }

  unsigned int Cfg::GetProviderRepairTimeout()
  {
    return s_monProviderRepairTimeout;
  }

  int Cfg::GetDefaultSamplingPeriod()
  {
    return s_monDefautlSamplingTimeout;
  }
}

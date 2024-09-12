#include "Coordinator/stdafx.h"
#include "Coordinator/CoordinatorServerCfg.h"

static unsigned int s_coordClientRepairTimeout = 30;
REGISTER_VAR( "coordsrv_client_repair_timeout", s_coordClientRepairTimeout, STORAGE_GLOBAL);

static unsigned int s_coordClientPingPeriod = 15;
REGISTER_VAR( "coordsrv_client_ping_period", s_coordClientPingPeriod, STORAGE_GLOBAL);

static unsigned int s_coordClientPingResponseTimeout = 5;
REGISTER_VAR( "coordsrv_client_ping_response_timeout", s_coordClientPingResponseTimeout, STORAGE_GLOBAL);

namespace Coordinator
{
  unsigned int Cfg::GetClientRepairTimeout()
  {
    return s_coordClientRepairTimeout;
  }

  unsigned int Cfg::GetClientPingPeriod()
  {
    return s_coordClientPingPeriod;
  }

  unsigned int Cfg::GetClientPingResponseTimeout()
  {
    return s_coordClientPingResponseTimeout;
  }
}

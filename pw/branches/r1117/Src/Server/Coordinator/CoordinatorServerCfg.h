#pragma once

namespace Coordinator
{
  struct Cfg
  {
    static unsigned int GetClientRepairTimeout();
    static unsigned int GetClientPingPeriod();
    static unsigned int GetClientPingResponseTimeout();
  };
}

#pragma once

namespace Monitoring
{
  struct Cfg
  {
    static unsigned int GetThriftIfacePort();
    static unsigned int GetConsoleThriftIfacePort();
    static unsigned int GetProviderRepairTimeout();
    static int GetDefaultSamplingPeriod();
  };
}

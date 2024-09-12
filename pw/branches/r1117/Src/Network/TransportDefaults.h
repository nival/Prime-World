#pragma once

namespace Transport
{
  struct Defaults
  {
    static unsigned int GetOpenChannelTimeout();
    static unsigned int GetPingPeriod();
  };
}

#include "stdafx.h"
#include "TransportDefaults.h"

static unsigned int defaultOpenChannelTimeout = 10;
REGISTER_VAR( "tl_default_open_channel_timeout", defaultOpenChannelTimeout, STORAGE_GLOBAL );

static unsigned int defaultPingPeriod = 4;
REGISTER_VAR( "tl_default_ping_period", defaultPingPeriod, STORAGE_GLOBAL );

namespace Transport
{
  unsigned int Defaults::GetOpenChannelTimeout()
  {
    return defaultOpenChannelTimeout;
  };

  unsigned int Defaults::GetPingPeriod()
  {
    return defaultPingPeriod;
  }
}

#pragma once

#include <Network/TransportTypes.h>

namespace Relay
{
  Transport::TServiceId const ServiceClass = "relay";
  char const * const ServiceRpcIface = "relay.iface";
  char const * const IncomingClientNotifierRpcIface = "relay.notifier";
}

#pragma once

#include <Network/TransportTypes.h>

namespace Relay
{
  namespace Balancer
  {
    Transport::TServiceId const ServiceClass = "relaybalancer";
    char const * const ServiceRpcIface = "relaybalancer.iface";
    char const * const SvcAppearanceNotifierRpcIface = "relaybalancer.coordinator.notify";
  }
}

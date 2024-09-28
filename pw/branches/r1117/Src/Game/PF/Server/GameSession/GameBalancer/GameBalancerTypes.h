#pragma once

#include <Network/TransportTypes.h>

namespace GameBalancer
{
  Transport::TServiceId const ServiceClass = "gamebalancer";
  char const * const ServiceRpcIface = "gamebalancer.iface";
  char const * const GameSvcAppearanceNotifierRpcIface = "gamebalancer.coordinator.notify";
  char const * const GBALANCER = "gamebalancer";
}

#pragma once

#include <Network/TransportTypes.h>

namespace UserManager
{
  Transport::TServiceId const ServiceClass = "usermanager";
  char const * const ServiceRpcIface = "usermanager.iface";
  char const * const UserPublisherRpcIface = "usermanager.userpublisher";
}

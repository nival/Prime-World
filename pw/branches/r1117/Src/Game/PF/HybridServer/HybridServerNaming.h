#pragma once

#include <Network/TransportTypes.h>

namespace HybridServer
{
  static const Transport::TServiceId ServiceClass = "gamesvc";
  static const Transport::TServiceId ReconnectServiceClass = "gamesvc.reconnect";
  static const char * ServiceInterfaceId = "hybridserver";
  static const char * DispenserIfaceId = "hybridSvDisp";
  static const char * AllocatorIfaceId = "hybridserver.gamealloc";
}

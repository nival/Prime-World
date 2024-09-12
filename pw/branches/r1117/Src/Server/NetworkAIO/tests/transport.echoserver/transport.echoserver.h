#include "stdafx.h"

#include <Network/Network.h>
#include <Network/Initializer.h>
#include <Network/StreamAllocator.h>
#include "System/ThreadHelpers.h"
#include "System/FileSystem/FileUtils.h"
#include "System/ProfileManager.h"
#include "System/ConfigFiles.h"
#include <Network/Transport.h>
#include <Network/AddressTranslator.h>
#include <Network/TransportMessages.h>
#include <Network/TransportInitializer.h>

namespace Transport
{
  struct EchoServer : public CObjectBase
  {
    OBJECT_BASIC_METHODS(EchoServer)

  public:
    EchoServer();

    StrongMT<Network::INetworkDriver> netDriver;
    int delay;
    nstl::string listenAddr;
    StrongMT<Transport::ITransportSystem> ts;

    int messagesSent;
    int messagesReceived;

    int Process(volatile bool& isRunning);
  };

  class LocalAddressResolver : public Transport::IAddressTranslator
  {
    Network::NetAddress GetNetworkAddress( const Transport::TServiceId& service )
    {
      return Network::NetAddress("localhost:35001");
    }
  };
}

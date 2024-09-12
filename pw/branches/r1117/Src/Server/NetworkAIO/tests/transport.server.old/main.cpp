#include "stdafx.h"
#include <conio.h> 
#include <System/ServerStdOutDumper.h>
#include <System/ServerTextFileDumper.h>
#include <Network/Network.h>
#include <Network/Initializer.h>
#include <Network/StreamAllocator.h>
#include "System/ThreadHelpers.h"
#include "System/FileUtils.h"
#include "System/ProfileManager.h"
#include "System/ConfigFiles.h"
#include <Network/Transport.h>
#include <Network/AddressTranslator.h>
#include <Network/TransportMessages.h>
#include <Network/TransportInitializer.h>
#include <NetworkAIO/tests/transport.echoserver/transport.echoserver.h>


class LocalAddressResolver : public Transport::IAddressTranslator
{
  Network::NetAddress GetNetworkAddress( const Transport::TServiceId& service )
  {
    return Network::NetAddress("localhost:35001");
  }
};


int main(int argc, const char argv[])
{      
  ScopedPtr<NLogg::CServerStdOutDumper> stdoutDumper;
  Reset( stdoutDumper, new NLogg::CServerStdOutDumper( &GetSystemLog() ) );
  ScopedPtr<NLogg::CServerTextFileDumper> textLogDumper;
  Reset( textLogDumper, new NLogg::CServerTextFileDumper( &GetSystemLog() ) );
  textLogDumper->SetFileName("transport.server");

  Transport::MessageFactory msgFactory;
  Transport::RegisterMessages(&msgFactory);
  LocalAddressResolver lar;

  CObj<Network::INetworkDriver> driver = Network::Initialize();
  //  server1
  CObj<Transport::EchoServer> echosrv = new Transport::EchoServer();
  echosrv->delay = 10;
  echosrv->listenAddr = "localhost:35001";
  echosrv->ts = Transport::CreateTransportSystem(driver, &msgFactory, &lar);
  threading::ProcessingThread<Transport::EchoServer> testThread(*echosrv, true );

  int ch = 0;
  while ((ch = _getch()) != 'Q');

  testThread.Stop( true, 5000 );

  return 0;
}

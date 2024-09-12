#include <conio.h>
#include <System/systemStdAfx.h>
#include <Server/RPC/all.h>

#include <Server/Network/Initializer.h>
#include <Server/Network/Transport.h>
#include <Server/Network/TransportInitializer.h>
#include <Server/Network/TransportMessages.h>
#include <Server/Network/AddressTranslator.h>
#include <Server/RPC/P2PNode.h>

#include "RHelloWorld.auto.h"
#include "LHelloWorld.auto.h"

bool QueryDemoType()
{
  char str[256];
  gets_s(str, 256);
  if (str[0]=='s' || str[0]=='S')
    return true;
  else
    return false;
}

struct HelloWorldFactory : rpc::ILocalEntityFactory
{
  rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args)
  {
    return new test::LHelloWorld(new test::HelloWorld, false);
  }
};

static HelloWorldFactory factory_HelloWorld;

class GetInt
{
public:
  void SetInt( int val )
  {
    printf( "Get int: %d\n", val );
  }
};

int main(int argc, const char* argv[])
{
  printf("Sample: Simple Remote Objects demonstration.\n");
  printf("(S)erver or (C)lient?: ");
  bool isServer = QueryDemoType();

  CObj<Network::INetworkDriver> pDriver = Network::Initialize(); 
  CObj<Transport::ITransportSystem> pSystem = Transport::CreateTransportSystem(pDriver, Transport::GetGlobalMessageFactory(), 0);
  rpc::Gate gate;

  GetInt intgetter;

  if (isServer)
  {
    rpc::RegisterFactory(test::HelloWorld::ID, factory_HelloWorld); 

    CObj<Transport::IChannelListener> l = pSystem->CreateChannelListenerDirect(":35000" );
    nstl::vector<rpc::P2PNode*> nodes;

    printf("Listening on port 35000\n");
    printf("Press any key to exit\n");

    while(_kbhit()!= 1)
    {
      Transport::TChannels newConns;
      l->GetNewConnections( &newConns );
      for (int i=0;i<newConns.size();++i)
      {
        nodes.push_back(new rpc::P2PNode(newConns[i], gate ));
        printf("Incoming connection from %d\n", newConns[i]->GetAddress().client);
      }
      newConns.clear();
      Sleep( 5 );
      for (int i=0;i<nodes.size();++i)
      {
        nodes[i]->Poll();
      }
    }
    for (int i=0;i<nodes.size();++i)
    {
      delete nodes[i];
    }
  } else
  {
    printf("Connecting to localhost:35000\n");
    CObj<Transport::IChannel> channel = pSystem->OpenChannelDirect( Transport::Address( "test", 1 ), "", "localhost:35000" );
    while (channel->GetStatus() == Network::ConnectionState::Connecting)
    {
      Sleep( 5 );
    }
    if (channel->GetStatus() == Network::ConnectionState::Connected)
    {
      printf("Connected to server\n");
      printf("Press Esc to exit or any other key to send them to server\n");
      rpc::P2PNode node(channel, gate);

      CObj<test::RHelloWorld> remoteWorld = node.node->Create<test::RHelloWorld>();
      int key = 0;
      do 
      {
        if (_kbhit())
        {
          key = _getch();
          char buffer[32];
          sprintf_s(buffer, 32, "Key pressed %c", key);
          printf("%s\n", buffer);
          remoteWorld->Print(buffer);
          remoteWorld->GetInt( 13, &intgetter, &GetInt::SetInt );
        }
        node.Poll();
      } while (key != 27 && channel->GetStatus() == Network::ConnectionState::Connected);
      if (channel->GetStatus() != Network::ConnectionState::Connected)
      {
        printf("Server dropped\n");
      }
    } else
    {
      printf("Not connected to server, aborted\n");
    }
  }
  return 0;
} 

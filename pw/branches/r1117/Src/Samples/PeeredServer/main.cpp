#include <conio.h>
#include <System/systemStdAfx.h>
#include <System/Win32Random.h>
#include <System/StdOutDumper.h>
#include <System/TextFileDumper.h>

#include <Server/RPC/all.h>
#include <Server/RPC/LocalEntityFactory.h>

#include <Server/Network/Initializer.h>
#include <Server/Network/Transport.h>
#include <Server/Network/TransportInitializer.h>
#include <Server/Network/TransportMessages.h>
#include <Server/Network/AddressTranslator.h>
#include <Server/RPC/P2PNode.h>

#include "ServerNodeHelper.h"

bool QueryDemoType()
{
  char str[256];
  gets_s(str, 256);
  if (str[0]=='s' || str[0]=='S')
    return true;
  else
    return false;
}

nstl::string ItoA(int value)
{
  char buffer[64];
  _itoa_s(value, buffer, 64, 10);
  return nstl::string(buffer);
}

int main(int argc, const char* argv[])
{
  ScopedPtr<NLogg::CStdOutDumper> stdoutDumper;
  ScopedPtr<NLogg::CTextFileDumper> fileDumper;

  Reset( stdoutDumper, new NLogg::CStdOutDumper( &GetSystemLog() ) );
  Reset( fileDumper, new NLogg::CTextFileDumper( &GetSystemLog() ) );

  int peerType = 0;
  if (argc > 1)
  {
    if (!_strcmpi("c", argv[1]))
      peerType = 1;
    else
    if (!_strcmpi("s", argv[1]))
      peerType = 2;
  }

  if (0 == peerType)
  {
    printf("Wrong side type\n");
    return -1;
  }

  nstl::string port = ItoA(36000);
  CObj<Network::INetworkDriver> pDriver = Network::Initialize(); 
  CObj<Transport::ITransportSystem> pSystem = 
    Transport::CreateTransportSystem(pDriver, Transport::GetGlobalMessageFactory(), 0);

  CObj<rpc::Gate> gate = new rpc::Gate;

  rpc::EnableLog(true);
  if (2 == peerType)
  {
    rpc::LocalEntityFactory factory( gate );

    factory.RegisterAttach<Peered::IGameServer, Peered::LIGameServer>();

    CObj<Peered::SessionConnector> connector = new Peered::SessionConnector;
    gate->RegisterObject<Peered::SessionConnector>(connector, "connector");

    CObj<Transport::IChannelListener> l = pSystem->CreateChannelListenerDirect(":"+port);
    nstl::vector<rpc::P2PNode*> nodes;

    printf("Listening on port %s, press any key to exit\n", port.c_str());

    while(_kbhit()!= 1)
    {
      Transport::TChannels newConns;
      l->GetNewConnections( &newConns );
      for (int i=0;i<newConns.size();++i)
      {
        rpc::P2PNode* node = new rpc::P2PNode( newConns[i], gate );
        NI_ASSERT(node->node, "Node creation failed");
        nodes.push_back(node);
        printf("Incoming connection from %d\n", newConns[i]->GetAddress().client);
      }
      newConns.clear();
      Sleep( 5 );
      gate->Poll();
      connector->Step();
    }
    for (int i=0;i<nodes.size();++i)
    {
      delete nodes[i];
    }
  }
  else
  {
    int numberOfClients = 1000;
    if (argc > 2)
    {
      int nc = atoi(argv[2]);
      if (nc != 0)
        numberOfClients = nc;
    }

    nstl::string srvaddr = "localhost";
    if (argc > 3)
    {
      srvaddr.assign(argv[3]);
    }

    printf("Connecting to %s:%s\n", srvaddr.c_str(), port.c_str());
    CObj<Transport::IChannel> channel = pSystem->OpenChannelDirect( Transport::Address( "user", -1 ), "", (srvaddr+":"+port).c_str() );

    {
      typedef nstl::vector<CObj<NCore::IServerNode>> ServerNodesT;
      ServerNodesT srvNodes;

      rpc::LocalEntityFactory factory(gate);
      factory.RegisterAttach<Peered::IGameClient, Peered::LIGameClient>();

      rpc::P2PNode* node = new rpc::P2PNode( channel, gate );
      for (int i = 0; i < numberOfClients; ++i)
      {
        ServerNodeHelper m(channel, gate, node);
        CObj<NCore::ServerNode> sn = m.GetStrong();
        if (sn)
        {
          srvNodes.push_back(sn);
          printf("(%d) Server node created\n", i);
        }
        else
          printf("Can't get server node\n");
      }

      char data[] = "1111111111"
        "2222222222"
        "3333333333"
        "4444444444"
        "5555555555";

      int key = 0;
      NHPTimer::FTime delta = 0;
      NHPTimer::FTime lastSendTime = 0;
      NCore::IServerNode::TMessageList segments;

      do
      {
        for (ServerNodesT::iterator it = srvNodes.begin(); it != srvNodes.end(); ++it)
        {
          (*it)->GetServerSegment(segments);
          segments.clear();
        }

        if (lastSendTime + delta < NHPTimer::GetScalarTime())
        {
          for (ServerNodesT::iterator it = srvNodes.begin(); it != srvNodes.end(); ++it)
          {
            MemoryStream s;
            s.Write(data, sizeof(data));
            (*it)->SendMessage(&s);
          }

          delta = NWin32Random::Random(0.8f, 2.f);
          lastSendTime = NHPTimer::GetScalarTime();
        }

        gate->Poll();

        ::Sleep(10);

        if (_kbhit())
          key = _getch();
      }
      while (key != 27);

      if (node)
        delete node;
    }

  }

  return 0;
} 

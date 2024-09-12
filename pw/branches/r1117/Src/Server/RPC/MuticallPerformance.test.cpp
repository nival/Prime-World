//!Component('RPC/all')
//!Component('System/Threading')
//!Component('System/NSTL')
//!Component('System/Asserts')
//!Component('Network/Transport')
//!Component('Network/LocalNetDriver')
//!Component('System/Timer')
//!Component('RPC/WalkingRabbit.test')
//!Component('System/InlineProfiler')

#include "stdafx.h"
#include <cxxtest/TestSuite.h>

#include "Network/Transport.h"
#include "Network/TransportInitializer.h"
#include "Network/LocalNetDriver.h"
#include "Network/TransportMessages.h"
#include "Network/AddressTranslator.h"

#include <System/AutoPtr.h>
#include <System/ScopedArray.h>
#include <System/BinSaver.h>
#include <System/BitData.h>
#include <System/HPTimer.h>
#include <RPC/RPC.h>
#include <RPC/P2PNode.h>
#include "RPC/RPCMixin.h"

#include "RPC/WalkingRabbit.test.h"
#include "RPC/LWalkingRabbit.test.auto.h"
#include "RPC/RWalkingRabbit.test.auto.h"

#define REMOTE

using namespace MulticallPerformanceTest;
#include <System/InlineProfiler3\InlineProfiler3Control.h>
#include <System/InlineProfiler3/Profiler3UI.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SERIALIZE_FACTORY(TestInitialSnapshot);
int MulticallPerformanceTest::WalkingRabbit::totalProcessed = 0;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  struct WalkingRabbitFactory : rpc::ILocalEntityFactory
  {
    rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& info, rpc::Arguments& args, rpc::IEntityMap* entityMap)
    {
      return new LWalkingRabbit(new WalkingRabbit, entityMap, this);
    }

    rpc::ILocalEntity* RegisterObject(uint classId, void* instance, rpc::IEntityMap* entityMap)
    {
      return new LWalkingRabbit((WalkingRabbit*)instance, entityMap);
    }
  };
  static WalkingRabbitFactory factory_WalkingRabbit;
  static rpc::CreationEntry entry_test_WalkingRabbit(rpc::GetId<WalkingRabbit>(), factory_WalkingRabbit);

#undef TS_WAIT_FOR_G
#define TS_WAIT_FOR_G(condition, period)  \
  for (int i=period;i>0&& !(condition);i-=2) { g.Poll(); threading::Sleep(2); } \
  TS_ASSERT( condition );


struct Test_Multicall_Performance : public CxxTest::TestSuite
{
  template <typename T, typename TC>
  T* waitForEntity(rpc::Node* c, uint entityId, TC& tc)
  {
    do
    {
      T* o = c->get<T>(entityId);
      if (o)
        return o;

      tc.Poll();
    } while (true);    
  }

  struct Gates
  {
    Gates()
    {
      serverGate = new rpc::Gate();
    }
    ~Gates()
    {
      for ( int i = 0; i < clients.size(); ++i )
      {
        serverGate->RemovePipe( clients[i]->sNode );
        delete clients[i];
      }
    }

    void createClients( int count )
    {
      clients.resize( count, 0 );
      for ( int i = 0; i < clients.size(); ++i )
        clients[i] = new ClientSide( serverGate );
    }

    void Poll()
    {
      serverGate->Poll();
      for (int i=0;i<clients.size();++i)
      {
        clients[i]->cGate->Poll();
      }
    }

    struct ClientSide
    {
      StrongMT<TestChannel> channel;
      StrongMT<TestPacketPipe> cPipe, sPipe;
      StrongMT<rpc::Gate> cGate;

      StrongMT<rpc::Node> cNode;
      StrongMT<rpc::Node> sNode;
      WalkingRabbit* testObject;
      bool isBlocked;
      ClientSide(rpc::Gate* sGate) : 
      isBlocked(false),
      channel( new TestChannel( 0, isBlocked ) ),
      cPipe( new TestPacketPipe( channel ) ),
      sPipe( new TestPacketPipe( channel ) )
      {
        cGate = new rpc::Gate;
        cNode = cGate->AddPipe( cPipe, 0 );
        sNode = sGate->AddPipe( sPipe, 0 );
        testObject = 0;
      }
      ~ClientSide()
      {
        cGate->RemovePipe(cNode);
      }
    };

    StrongMT<rpc::Gate> serverGate;
    nstl::vector<ClientSide*> clients;
  };


  class DummyAddressResolver : public Transport::IAddressTranslator
  {
  public:
    DummyAddressResolver( const Network::NetAddress & server ) : server_( server ) {}

    const Network::NetAddress & GetServerIp() const { return server_; }
    Network::NetAddress GetSvcAddress( const Transport::TServiceId & _serviceId ) { return Network::NetAddress(); }

    void DefineRoute( const Transport::TServiceId &, const Network::NetAddress & ) {}
    void DefineAliasRoute( const Transport::TServiceId &, const Transport::TServiceId & ) {}
    Transport::TServiceId GetLastServiceInstance( const Transport::TServiceId & _svcClass ) { return Transport::TServiceId(); }
    ni_detail::ClassTypeId  PersistentClassId() const { return 0; }
    BaseObjectMT * CastToBaseObject() { return 0; }
    WeakPointerProxyMT * AcquireWeakProxy() { return 0; }

  private:
    Network::NetAddress server_;
  };


  struct TransportGates
  {

    TransportGates()
      : addrResolver( "11" )
    {
      Transport::RegisterMessages( &factory );
      pDriver = new Network::LocalNetDriver();
      pSystem = Transport::CreateTransportSystem( pDriver, &factory, &addrResolver );

    }
    ~TransportGates()
    {
      for ( int i = 0; i < clients.size(); ++i )
      {
        //serverGate.RemovePipe( clients[i]->sNode );
        delete clients[i];
      }
    }

    void createClients( int count )
    {
      CObj<Transport::IChannelListener> l = pSystem->CreateChannelListener( "rpctest" );

      vector<CObj<Transport::IChannel>> channels;
      channels.resize( count );
      for ( int i = 0; i < channels.size(); ++i )
      {
        channels[i] = pSystem->OpenChannel( Transport::Address( "rpctest", i + 1 ), "" );
      }
      
      Transport::TChannels srvChannels;
      while ( srvChannels.empty() )
      { l->GetNewConnections( &srvChannels ); Sleep( 10 ); }

      clients.resize( count, 0 );
      int nConnected = 0;
      do 
      {
        for ( int i = 0; i < srvChannels.size(); ++i )
        {
          int conn = srvChannels[i]->GetAddress().client;
          clients[conn-1] = new ClientSide( serverGate, channels[conn-1], srvChannels[i] );
          ++nConnected;
        }

        srvChannels.clear();
        l->GetNewConnections( &srvChannels );
      } while ( nConnected != count );
    }

    void Poll()
    {
      serverGate->Poll();
      for (int i=0;i<clients.size();++i)
      {
        clients[i]->cGate->Poll();
      }
    }

    struct ClientSide
    {
      StrongMT<Transport::IChannel> cChannel;
      StrongMT<Transport::IChannel> sChannel;
      StrongMT<rpc::Gate> cGate;

      rpc::P2PNode* cp2pNode;
      rpc::P2PNode* sp2pNode;

      StrongMT<rpc::Node> cNode;
      StrongMT<rpc::Node> sNode;

      WalkingRabbit* testObject;

      ClientSide(rpc::Gate* sGate, Transport::IChannel* channel1, Transport::IChannel* channel2 ) 
        : cChannel(channel1), sChannel(channel2)
      {
        cGate = new rpc::Gate;
        cp2pNode = new rpc::P2PNode(cChannel, cGate);
        sp2pNode = new rpc::P2PNode(sChannel, sGate);

        cNode = cp2pNode->node;
        sNode = sp2pNode->node;
        testObject = 0;
      }
      ~ClientSide()
      {
        sChannel->Close();
        cChannel->Close();
        delete cp2pNode;
        delete sp2pNode;
        cGate = 0;
      }
    };

    CObj<Network::INetworkDriver> pDriver;
    DummyAddressResolver addrResolver;
    Transport::MessageFactory factory;
    CObj<Transport::ITransportSystem> pSystem;

    StrongMT<rpc::Gate> serverGate;
    nstl::vector<ClientSide*> clients;
  };

  template<class TGates>
  void ReplicateT()
  {
    TGates g;
    const int clientsCount = 1; //50;
    const int iterations = 2; // 20
    const int snapshotSize = 100;
    int waitforProcessed = 0;
    WalkingRabbit::totalProcessed = 0;

    g.createClients( clientsCount );
    while (true)
    {
      bool isConnected = true;
      for (int i=0;i<g.clients.size();++i)
      {
        if (!g.clients[i]->sNode->IsReady() || !g.clients[i]->cNode->IsReady())
        {
          isConnected = false;
        }
        g.Poll();
      }
      if (isConnected)
        break;
    }

    StrongMT<RWalkingRabbit> serverObject = g.clients[0]->sNode->Create<RWalkingRabbit>();

    for ( int i = 1; i < clientsCount; ++i )
      g.serverGate->Replicate( *serverObject, *(g.clients[i]->sNode) );

    for ( int i = 0; i < clientsCount; ++i )
      g.clients[i]->testObject = waitForEntity<WalkingRabbit>(g.clients[i]->cNode, 0, g);

    waitforProcessed += clientsCount;
    TS_WAIT_FOR_G( WalkingRabbit::totalProcessed == waitforProcessed , 1000);

    NHPTimer::STime startTime, curTime;
    NHPTimer::GetTime( startTime );

    for ( int it = 0; it < iterations; ++it )
    {
      serverObject->WalkTo( it * 0.1f, it * 0.2f, it * 0.25f );
      TestInitialSnapshot data;
      data.serverTime = 0.f;
      data.dynamicObjects.insert( data.dynamicObjects.begin(), snapshotSize, TestInitialSnapshot::SnapshotDesc() );
      serverObject->SetSomeData( data );

      waitforProcessed += clientsCount  * 2;
      TS_WAIT_FOR_G( WalkingRabbit::totalProcessed == waitforProcessed, 100);
    }
    NHPTimer::GetTime( curTime );
    double time = NHPTimer::Time2Seconds( curTime - startTime );

    //printf_s( "Total time: %.3f seconds, %.3f ms per call \n", time, time * 1000.0 / iterations );

    for ( int i = 1; i < clientsCount; ++i )
      g.serverGate->Dereplicate( *serverObject, *(g.clients[i]->sNode) );
    serverObject  = 0;

    waitforProcessed += clientsCount;
    TS_WAIT_FOR_G( WalkingRabbit::totalProcessed == waitforProcessed , 1000);

  }
  void test_Local()
  {
    ReplicateT<Gates>();
  }
  void test_Transport()
  {
    //ReplicateT<TransportGates>();
  }

  void test_Disconnection()
  {
//#define PROFILE_RPC_DISCONNECTION
#ifdef PROFILE_RPC_DISCONNECTION
    profiler3::GetControl()->Setup(profiler3::SSettings());
    NI_PROFILE_THREAD_NAMED("NI_RPC");
    profiler3ui::Init();
    profiler3ui::Show(0);
#endif
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    const int maxClients = 100;
    nstl::vector<StrongMT<test::MockCorruptedPacketProcessor>> processors;
    nstl::vector<rpc::Gate*> gates;
    gates.reserve(maxClients);
    nstl::vector<ManyToManyCase::Gate2GateNodeInfo> nodes;
    nodes.reserve(maxClients);
    for (int i=0;i<maxClients;++i)
    {
      char buffer[16];
      sprintf(buffer, "c%d", i);
      StrongMT<test::MockCorruptedPacketProcessor> cP = new test::MockCorruptedPacketProcessor(buffer, &c);
      rpc::Gate& cx = c.AddGate(buffer, cP);
      ManyToManyCase::Gate2GateNodeInfo info = c.ConnectGates(root, cx);
      nodes.push_back(info);
      processors.push_back(cP);
      gates.push_back(&cx);
    }
    c.WaitForConnections();
    nstl::vector<StrongMT<test::RComplexRabbit>> robjects;
    for (int i=0;i<nodes.size();++i)
    {
      StrongMT<test::RComplexRabbit> robject(nodes[i].s2d->Create<test::RComplexRabbit>());
      robjects.push_back(robject);
      test::ComplexRabbit* oobject = waitForEntity<test::ComplexRabbit>(nodes[i].d2s, i, c);
    }
#ifdef PROFILE_RPC_DISCONNECTION
    for (int i=0;i<10;++i)
    {
      Sleep(1000);
    }
#endif
    for (int i=0;i<gates.size();++i)
    {
      c.DisconnectGates(root, *gates[i]);
    }
#ifdef PROFILE_RPC_DISCONNECTION
    OutputDebugString("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    for (int i=0;i<1000;++i)
    {
      Sleep(1000);
    }
    profiler3ui::Shutdown();
#endif
  }

  void test_DisconnectionAndDeletionInSeparatedThreads()
  {
    struct ClientThread0
    {
      nstl::vector<StrongMT<test::RComplexRabbit> >& robjects;
		  ClientThread0(nstl::vector<StrongMT<test::RComplexRabbit>>& _robjects):
      robjects(_robjects)
      {
      }

      virtual uint Process(volatile bool& isRunning)
      {
        robjects.clear();
        return 0;
      }
    };

    struct ClientThread1
    {
      ManyToManyCase& c;
      nstl::vector<rpc::Gate*>& gates;
      rpc::Gate& root;

		  ClientThread1(ManyToManyCase& _c, nstl::vector<rpc::Gate*>& _gates, rpc::Gate& _root):
      c(_c),
      gates(_gates),
      root(_root)
      {
      }

      virtual uint Process(volatile bool& isRunning)
      {
        for (int i=0;i<gates.size();++i)
        {
          c.DisconnectGates(root, *gates[i]);
        }
        return 0;
      }
    };

    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    const int maxClients = 3;    
    const int maxObjectsPerClient = 10;

    nstl::vector<StrongMT<test::MockCorruptedPacketProcessor>> processors;
    nstl::vector<rpc::Gate*> gates;
    gates.reserve(maxClients);
    nstl::vector<ManyToManyCase::Gate2GateNodeInfo> nodes;
    nodes.reserve(maxClients);

    for (int i=0;i<maxClients;++i)
    {
      char buffer[16];
      sprintf(buffer, "c%d", i);
      StrongMT<test::MockCorruptedPacketProcessor> cP = new test::MockCorruptedPacketProcessor(buffer, &c);
      rpc::Gate& cx = c.AddGate(buffer, cP);
      ManyToManyCase::Gate2GateNodeInfo info = c.ConnectGates(root, cx);
      nodes.push_back(info);
      processors.push_back(cP);
      gates.push_back(&cx);
    }
    c.WaitForConnections();

    nstl::vector<StrongMT<test::RComplexRabbit> > robjects;
    for (int i=0;i<nodes.size();++i)
    {
      for (int j=0;j<maxObjectsPerClient;++j)
      {
        robjects.push_back(nodes[i].s2d->Create<test::RComplexRabbit>());
        test::ComplexRabbit* oobject = waitForEntity<test::ComplexRabbit>(nodes[i].d2s, i*maxObjectsPerClient+j, c);
      }
    }
    ClientThread0* c0 = new ClientThread0(robjects);
    ClientThread1* c1 = new ClientThread1(c, gates, root);
    threading::ProcessingThread<ClientThread0> p0(*c0, false);
    threading::ProcessingThread<ClientThread1> p1(*c1, false);
  
    p0.Resume();
    p1.Resume();
    
    while (!p0.Finished() || !p1.Finished())
    {
      c.Poll();
      threading::Sleep(1);
    }
    delete c0;
    delete c1;
  }

};

/*
Before:
const int clientsCount = 500;
const int iterations = 200;
const int snapshotSize = 100;
Before: Total time: 7.546 seconds, 37.732 ms per call
After:  Total time: 7.103 seconds, 35.698 ms per call
*/

//!Component("Network/RUDP/RDP")
//!Component("System/Commands")
//!Component("Network/RUDP/SockSrvLocal")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "Rdp.h"
#include "SockSrvLocal.h"
#include "RdpProto.h"
#include "RdpPacketPool.h"
#include "System/NiTimer.h"
#include "System/RandomInterfaceImpl.h"
#include "System/TestAssertDumper.h"

struct Test_RDP : public CxxTest::TestSuite
{
  class SocketFactory : public ni_udp::IRdpSocketFactory, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( SocketFactory, ni_udp::IRdpSocketFactory, BaseObjectMT );
  public:
    SocketFactory( ni_udp::ISocketServer * _sockSrv, const char * _addr, unsigned _basePort ) :
    sockSrv( _sockSrv ),
    addr( _addr ), port( _basePort )
    {}

    const std::string & Addr() const { return addr; }
    unsigned Port() const { return port; }

    virtual StrongMT<ni_udp::ISocket> OpenSocket( ni_udp::ISocketCallback * _cb )
    {
      return sockSrv->Open( _cb, ni_udp::NetAddr( addr.c_str(), port ), 0 );
    }

  private:
    StrongMT<ni_udp::ISocketServer> sockSrv;
    std::string addr;
    unsigned port;
  };

  class ConnCallback : public ni_udp::IRdpConnectionCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( ConnCallback, ni_udp::IRdpConnectionCallback, BaseObjectMT );
  public:
    ConnCallback() {}

    virtual void OnConnectionEstablished( ni_udp::IRdpConnection * _conn ) {
      established.push_back( _conn );
    }

    virtual void OnConnectionClosed( ni_udp::IRdpConnection * _conn ) {
      closed.push_back( _conn );
    }

    virtual void OnConnectionFailed( ni_udp::IRdpConnection * _conn ) {
      failed.push_back( _conn );
    }

    virtual void OnDatagram( ni_udp::IRdpConnection * _conn, const void * _data, size_t _size, timer::Time _absRecvTime ) {
      datagrams.push_back( std::vector<char>( (char *)_data, (char*)_data + _size ) );
    }

    std::vector<StrongMT<ni_udp::IRdpConnection>> established, closed, failed;
    std::list<std::vector<char>> datagrams;
  };



  class ListenCallback : public ni_udp::IRdpListenContextCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( ListenCallback, ni_udp::IRdpListenContextCallback, BaseObjectMT );
  public:
    ListenCallback( ConnCallback * _cb ) : connCallback( _cb ) {}

    virtual ni_udp::IRdpConnectionCallback * OnConnectionEstablished( ni_udp::IRdpConnection * _conn, const ni_udp::NetAddr & _remoteAddr )
    {
      TS_ASSERT( _conn->Status() == ni_udp::EConnStatus::Pending );
      newConnections.push_back( _conn );
      return connCallback;
    }

    StrongMT<ConnCallback>  connCallback;
    std::vector<StrongMT<ni_udp::IRdpConnection>> newConnections;
  };



  StrongMT<ni_udp::LocalSocketServer> sockSrv;
  ni_udp::RdpOptions rdpOpt1, rdpOpt2;
  StrongMT<ni_udp::Rdp> rdp1, rdp2;
  ni_udp::NetAddr addr1, addr2;

  StrongMT<timer::FixedTimer> clock;

  void setUp()
  {
    OutputDebugString( "\n===========================================\n" );

    NLogg::FailTestOnLogLevel( NLogg::LEVEL_WARNING, false );
    NLogg::FailTestOnLogLevel( NLogg::LEVEL_ERROR, false );

    WSADATA data;
    memset( &data, 0, sizeof( data ) );
    WSAStartup( MAKEWORD( 2, 2 ), &data );

    clock = new timer::FixedTimer;

    sockSrv = new ni_udp::LocalSocketServer( clock );

    rdp1 = new ni_udp::Rdp( true );
    rdp2 = new ni_udp::Rdp( true );

    addr1 = ni_udp::NetAddr( "192.168.0.1", 27000 );
    addr2 = ni_udp::NetAddr( "192.168.0.2", 27000 );

    StrongMT<SocketFactory> sockFact1 = new SocketFactory( sockSrv, "192.168.0.1", addr1.Port() );
    StrongMT<SocketFactory> sockFact2 = new SocketFactory( sockSrv, "192.168.0.2", addr2.Port() );

    Strong<ni_rnd::IFactory> rndFact = new ni_rnd::Factory;
    Strong<ni_rnd::IGenerator> rnd = rndFact->Produce( 201 );
    rdp1->Init( sockFact1, rdpOpt1, rnd, clock );
    rdp2->Init( sockFact2, rdpOpt2, rnd, clock );
  }

  void tearDown()
  {
    listenConnCb = 0;
    listenCb = 0;
    listenCtx = 0;

    connCb = 0;
    connection = 0;
    accepted = 0;

    rdp1 = 0;
    rdp2 = 0;
    sockSrv = 0;

    WSACleanup();
  }


  void poll( timer::Time _deltaTime )
  {
    clock->Set( clock->Now() + _deltaTime, 0 );

    sockSrv->Poll();
    
    if ( rdp1 )
      rdp1->UnitTestPoll();

    if ( rdp2 )
      rdp2->UnitTestPoll();

    sockSrv->Poll();
  }


  void poll( timer::Time _deltaTime, int steps )
  {
    for ( int i = 0; i < steps; ++i )
      poll( _deltaTime );
  }



  StrongMT<ConnCallback>                listenConnCb;
  StrongMT<ListenCallback>              listenCb;
  StrongMT<ni_udp::IRdpListenContext>   listenCtx;

  StrongMT<ConnCallback>                connCb;
  StrongMT<ni_udp::IRdpConnection>      connection;
  StrongMT<ni_udp::IRdpConnection>      accepted;

  enum EFlags
  {
    fDoNotListen              = 1,
    fNoListenConnCallback     = 2,
    fDoNotConnect             = 4
  };

  void SetupEnvironment( unsigned _flags )
  {
    if ( !( _flags & fNoListenConnCallback ) )
      listenConnCb = new ConnCallback;

    if ( !( _flags & fDoNotListen ) )
    {
      listenCb = new ListenCallback( listenConnCb );
      listenCtx = rdp1->Listen( 100, listenCb );
    }

    if ( !( _flags & fDoNotConnect ) )
    {
      connCb = new ConnCallback;
      connection = rdp2->Connect( addr1, 100, connCb );
      TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Pending );
    }
  }


  void CheckAcceptedConnection()
  {
    poll( 0.2, 4 );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( listenCb->newConnections.size() == 1 );
    accepted = listenCb->newConnections[0];
    TS_ASSERT( accepted->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( connCb->established.size() == 1 );
  }


  void DefaultCloseConnection( ni_udp::IRdpConnection * _activeClose, ni_udp::IRdpConnection * _remoteClosed )
  {
    _activeClose->Close();
    TS_ASSERT( _activeClose->Status() == ni_udp::EConnStatus::Closed );
    poll( 0.2, 4 );
    poll( 10.0 );
    poll( 0.2, 2 );

    TS_ASSERT( _remoteClosed->Status() == ni_udp::EConnStatus::Closed );
  }


  void DefaultCloseConnection()
  {
    DefaultCloseConnection( connection, accepted );
  }


  void PopExpectedDatagram( ConnCallback * _cb, const void * _data, size_t _size, bool _last = true )
  {
    TS_ASSERT( !_cb->datagrams.empty() );
    TS_ASSERT( _cb->datagrams.front().size() == _size );
    TS_ASSERT( !memcmp( &_cb->datagrams.front()[0], _data, _size ) );
    _cb->datagrams.pop_front();
    if ( _last )
      TS_ASSERT( _cb->datagrams.empty() );
  }

  void PopExpectedDatagram( ConnCallback * _cb, const std::vector<char> & _data, bool _last = true )
  {
    PopExpectedDatagram( _cb, _data.empty() ? 0 : &_data[0], _data.size(), _last );
  }


  void SendAndRecieveDatagram( ni_udp::IRdpConnection * _srcConn, ConnCallback * _destCallback, const void * _data, size_t _size, bool _raw = false )
  {
    _srcConn->SendDatagram( _data, _size, _raw ? ni_udp::EDatagramOpt::Raw : 0 );
    poll( 0.2, 4 );
    PopExpectedDatagram( _destCallback, _data, _size );
  }


  void SendAndRecieveDatagram( ni_udp::IRdpConnection * _srcConn, ConnCallback * _destCallback, const std::vector<char> & _data, bool _raw = false )
  {
    SendAndRecieveDatagram( _srcConn, _destCallback, _data.empty() ? 0 : &_data[0], _data.size(), _raw );
  }


  void test_window_clamp()
  {
    //zero-base window
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 0, 100, 5, 1000 ) == 5 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 0, 100, 105, 1000 ) == 105 );

    //maxed window
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 10, 500, 5, 1000 ) == -5 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 10, 500, 105, 1000 ) == 95 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 10, 500, 515, 1000 ) == -495 );

    //arbitrary based window, non-verlapping
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 330, 400, 700, 1000 ) == 700 - 330 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 330, 400, 800, 1000 ) == 470 );

    //farthest point
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 330, 400, 829, 1000 ) == 499 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 330, 400, 830, 1000 ) == -500 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 330, 400, 831, 1000 ) == -499 );

    //overlapping window
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 940, 200, 960, 1000 ) == 20 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 940, 200, 30, 1000 ) == 90 );

    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 940, 200, 150, 1000 ) == 210 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 940, 200, 930, 1000 ) == -10 );

    //exact boundaries
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 935, 300, 934, 1000 ) == -1 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 935, 300, 935, 1000 ) == 0 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 935, 300, 235, 1000 ) == 300 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 935, 300, 236, 1000 ) == 301 );

    //farthest point
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 920, 400, 419, 1000 ) == 499 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 920, 400, 420, 1000 ) == -500 );
    TS_ASSERT( ni_udp::proto::SeqIdxOffsetInWindow( 920, 400, 421, 1000 ) == -499 );
  }

  void test_pool_allocator()
  {
    StrongMT<ni_udp::PacketPoolAllocator> a = new ni_udp::PacketPoolAllocator;

    a->CreatePool( 16, 10 );
    a->CreatePool( 30, 5 );

    StrongMT<ni_udp::RdpPacket> pkt0 = a->AllocatePkt( 0 );
    TS_ASSERT( pkt0 );
    TS_ASSERT( pkt0->InUse() );
    TS_ASSERT_EQUALS( pkt0->Capacity(), 16 );

    a->DeallocatePkt( pkt0 );
    TS_ASSERT( !pkt0->InUse() );

    StrongMT<ni_udp::RdpPacket> pkt1 = a->AllocatePkt( 7 );
    TS_ASSERT_EQUALS( pkt0, pkt1 );
    a->DeallocatePkt( pkt1 );
    pkt1 = 0;

    StrongMT<ni_udp::RdpPacket> pkt2 = a->AllocatePkt( 7 );
    TS_ASSERT( pkt2 );

    std::set<StrongMT<ni_udp::RdpPacket>> packets;
    for ( int i = 0; i < 10; ++i )
      packets.insert( a->AllocatePkt( 4 ) );

    while( !packets.empty() ) {
      a->DeallocatePkt( *packets.begin() );
      packets.erase( packets.begin() );
    }

    //this should be deallocated explicitly
    a->DeallocatePkt( pkt2 );

    StrongMT<ni_udp::RdpPacket> pkt3 = a->AllocatePkt( 7 );
    TS_ASSERT( pkt3 != pkt2 );
    pkt2 = 0;

    StrongMT<ni_udp::RdpPacket> pkt4 = a->AllocatePkt( 20 );
    TS_ASSERT( pkt4->InUse() );
    TS_ASSERT_EQUALS( pkt4->Capacity(), 30 );

    pkt4->PktAddRef();
    a->DeallocatePkt( pkt4 );
    TS_ASSERT( pkt4->InUse() );
    a->DeallocatePkt( pkt4 );
    TS_ASSERT( !pkt4->InUse() );


    StrongMT<ni_udp::RdpPacket> pkt5 = a->AllocatePkt( 100 );
    TS_ASSERT( pkt5->InUse() );
    TS_ASSERT_EQUALS( pkt5->Capacity(), ni_udp::RdpPacket::PayloadToCapacity( 100 ) );
    a->DeallocatePkt( pkt5 );
    TS_ASSERT( !pkt5->InUse() );

    a->DeallocatePkt( pkt3 );
    pkt3 = 0;
  }


  void test_conn_refuse()
  {
    SetupEnvironment( fDoNotListen );
    poll( 0.2, 3 );
    TS_ASSERT( connCb->failed.size() == 1 );
    TS_ASSERT( connCb->established.empty() );
    TS_ASSERT( connCb->datagrams.empty() );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Failed );
  }



  void test_conn()
  {
    SetupEnvironment( 0 );

    poll( 0.2, 4 );

    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( listenConnCb->established.size() == 1 );
    TS_ASSERT( listenConnCb->established[0]->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( listenCb->newConnections.size() == 1 );
    TS_ASSERT( listenCb->newConnections[0]->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( connCb->failed.empty() );
    TS_ASSERT( connCb->established.size() == 1 );
    TS_ASSERT( connCb->datagrams.empty() );
  }



  void test_listen_callback_returns_zero()
  {
    SetupEnvironment( fNoListenConnCallback );

    poll( 0.2, 4 );

    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Ready ); //remote side have not yet recieved the SHUTDOWN
    TS_ASSERT( listenCb->newConnections.size() == 1 );
    TS_ASSERT( listenCb->newConnections[0]->Status() == ni_udp::EConnStatus::Closed );
    TS_ASSERT( connCb->established.size() == 1 );

    //Let SHUTDOWN pass through to active side
    poll( 0.2 );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Closed );
  }



  void test_lost_INITs()
  {
    SetupEnvironment( 0 );

    sockSrv->AddIncomingLossPattern( "00" );
    poll( 0.2, 4 );

    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Pending );
    TS_ASSERT( listenCb->newConnections.empty() );

    poll( 3.0 );
    poll( 0.2 );
    poll( 3.1 );
    poll( 0.2, 5 );

    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( listenCb->newConnections.size() == 1 );
    TS_ASSERT( listenCb->newConnections[0]->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( connCb->failed.empty() );
    TS_ASSERT( connCb->established.size() == 1 );
    TS_ASSERT( connCb->datagrams.empty() );
  }



  void test_lost_all_INITs()
  {
    SetupEnvironment( 0 );

    sockSrv->AddIncomingLossPattern( "000" );
    poll( 0.2 );
    poll( 3.1 );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Pending );
    poll( 0.2 );
    poll( 3.1 );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Pending );
    poll( 0.2 );
    poll( 3.1 );
    poll( 0.2 );

    TS_ASSERT( listenCb->newConnections.empty() );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Failed );
    TS_ASSERT( connCb->failed.size() == 1 );
    TS_ASSERT( connCb->established.empty() );
    TS_ASSERT( connCb->datagrams.empty() );
  }



  void test_lost_INIT_ACK()
  {
    //Lost INIT_ACK triggers two simultaneous time-outs
    //For INIT_ACK itself on active side and
    //for ACK on reactive side
    SetupEnvironment( 0 );

    sockSrv->AddIncomingLossPattern( "10" );
    poll( 0.2, 2 );

    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Pending );
    TS_ASSERT( listenCb->newConnections.empty() );

    poll( 3.1 );
    poll( 0.2, 4 );

    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( listenCb->newConnections.size() == 1 );
    TS_ASSERT( listenCb->newConnections[0]->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( connCb->failed.empty() );
    TS_ASSERT( connCb->established.size() == 1 );
    TS_ASSERT( connCb->datagrams.empty() );

    std::vector<char> big;
    big_datagram( big, 700 );
    SendAndRecieveDatagram( connection, listenConnCb, big );
  }



  void test_lost_first_ACK()
  {
    SetupEnvironment( 0 );

    sockSrv->AddIncomingLossPattern( "110" );
    poll( 0.2, 3 );

    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( listenCb->newConnections.empty() );

    poll( 3.1 );
    poll( 0.2, 3 );

    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( listenCb->newConnections.size() == 1 );
    TS_ASSERT( listenCb->newConnections[0]->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( connCb->failed.empty() );
    TS_ASSERT( connCb->established.size() == 1 );
    TS_ASSERT( connCb->datagrams.empty() );

    poll( 10.0 ); //To test finish of handshake "TIME_WAIT"

    std::vector<char> big;
    big_datagram( big, 700 );
    SendAndRecieveDatagram( connection, listenConnCb, big );
  }


  void test_smoke()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    SendAndRecieveDatagram( connection, listenConnCb, "Hello world", 11 );
    SendAndRecieveDatagram( accepted, connCb, "Reply", 5 );
    SendAndRecieveDatagram( connection, listenConnCb, "Raw", 3, true );

    TS_ASSERT_DELTA( connection->AvgRtt(), 0.2, 1e-6 );

    DefaultCloseConnection();
  }


  void big_datagram( std::vector<char> & big, size_t sz ) {
    big = std::vector<char>( sz );
    TS_ASSERT( ( big.size() > rdpOpt1.maxDataSegment ) && ( big.size() > rdpOpt2.maxDataSegment ) );
    for ( size_t i = 0; i < big.size(); ++i )
      big[i] = i % 251;
  }

  void test_big_datagram()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    std::vector<char> big;
    big_datagram( big, 1900 );

    SendAndRecieveDatagram( connection, listenConnCb, big );

    DefaultCloseConnection();
  }


  void test_big_datagrams()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    std::vector<char> big1, big2;
    big_datagram( big1, 1200 );
    big_datagram( big2, 600 );

    connection->SendDatagram( &big1[0], big1.size() );
    connection->SendDatagram( &big2[0], big2.size() );
    poll( 0.2, 8 );
    PopExpectedDatagram( listenConnCb, big1, false );
    PopExpectedDatagram( listenConnCb, big2 );

    DefaultCloseConnection();
  }


  void help_test_data_loss( size_t _pktSz, const char * _loss, int _polls )
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    std::vector<char> big;
    big_datagram( big, _pktSz );

    sockSrv->AddIncomingLossPattern( _loss );

    connection->SendDatagram( &big[0], big.size() );
    poll( 0.2, _polls );
    poll( 0.5 );
    PopExpectedDatagram( listenConnCb, big );

    DefaultCloseConnection();
  }

  void test_data_loss() { help_test_data_loss( 1300, "110", 6 ); }

  void test_first_chunk_ack_loss() { help_test_data_loss( 800, "110", 4 ); }

  void test_ack_loss() { help_test_data_loss( 1300, "11110", 5 ); }


  void test_3_datagrams_lost_first_ack()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    sockSrv->AddIncomingLossPattern( "10" );
    sockSrv->SetDefaultDelay( 0 );

    connection->SendDatagram( "Lost", 4 );
    poll( 0.1 );
    poll( 0.3 );
    PopExpectedDatagram( listenConnCb, "Lost", 4 );

    connection->SendDatagram( "Crash1", 6 );
    poll( 0.1 );
    poll( 0.3 );
    PopExpectedDatagram( listenConnCb, "Crash1", 6 );

    connection->SendDatagram( "Crash2", 6 );
    poll( 0.1 );
    poll( 0.3 );
    PopExpectedDatagram( listenConnCb, "Crash2", 6 );

    DefaultCloseConnection();
  }


  void test_two_datagrams_first_is_lost()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    sockSrv->AddIncomingLossPattern( "0" );

    connection->SendDatagram( "Lost", 4 );
    connection->SendDatagram( "Second", 6 );
    poll( 0.1 );
    poll( 0.1, 4 );
    PopExpectedDatagram( listenConnCb, "Lost", 4, false );
    PopExpectedDatagram( listenConnCb, "Second", 6 );

    DefaultCloseConnection();
  }


  void help_test_delay( int _index )
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    std::vector<char> big;
    big_datagram( big, 800 );

    sockSrv->AddPacketDelay( _index, 0.5f );

    connection->SendDatagram( &big[0], big.size() );
    poll( 0.2, 3 );
    poll( 0.5 );
    PopExpectedDatagram( listenConnCb, big );

    DefaultCloseConnection();
  }


  void test_data_delay_first() { help_test_delay( 0 ); }

  void test_data_delay_second() { help_test_delay( 1 ); }

  void test_ack_delay_first() { help_test_delay( 2 ); }

  void test_ack_delay_second() { help_test_delay( 3 ); }



  void test_lost_shutdown()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();
    SendAndRecieveDatagram( connection, listenConnCb, "Datagram", 11 );

    sockSrv->AddIncomingLossPattern( "0" );
    connection->Close();
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Closed );
    poll( 0.2 );
    TS_ASSERT( accepted->Status() == ni_udp::EConnStatus::Ready );
    poll( 0.2, 2 );
    poll( 10.0 );
    poll( 0.2 );
    TS_ASSERT( accepted->Status() == ni_udp::EConnStatus::Closed );
  }


  void test_lost_shutdown_ack()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();
    SendAndRecieveDatagram( connection, listenConnCb, "Datagram", 11 );

    sockSrv->AddIncomingLossPattern( "10" );
    connection->Close();
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Closed );
    poll( 0.2 );
    TS_ASSERT( accepted->Status() == ni_udp::EConnStatus::Closed );
    poll( 0.2, 3 );
    poll( 10.0 );
    poll( 0.2 );
  }



  void test_disconnect_by_data_retransmit()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    SendAndRecieveDatagram( connection, listenConnCb, "Hello world", 11 );
    poll( 0.1, 3 );

    sockSrv->AddIncomingLossPattern( "0000000" );
    connection->SendDatagram( "Broken", 6, 0 );
    poll( 0.1, 3 );
    poll( 0.3, 3 );
    poll( 0.5, 8 );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Failed );
    TS_ASSERT( accepted->Status() == ni_udp::EConnStatus::Ready );
  }



  void test_ping_smoke()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();
    
    poll( 0.2 );
    TS_ASSERT_DELTA( connection->AvgRtt(), 0, 1e-6 );
    TS_ASSERT_DELTA( accepted->AvgRtt(), 0, 1e-6 );

    poll( rdpOpt1.pingPeriod );
    poll( 0.2, 2 );
    TS_ASSERT_DELTA( connection->AvgRtt(), 0.2, 1e-6 );
    TS_ASSERT_DELTA( accepted->AvgRtt(), 0.2, 1e-6 );

    DefaultCloseConnection();
  }



  void test_ping_delay()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    sockSrv->AddPacketDelay( 0, 0.05 ); //0.1 is a default delay
    sockSrv->AddPacketDelay( 1, 0.05 );
    
    poll( 0.01 );
    poll( rdpOpt1.pingPeriod );
    poll( 0.01 );
    poll( 0.15 );
    poll( 0.01, 10 );
    TS_ASSERT_DELTA( connection->AvgRtt(), 0.15 + 0.1, 1e-6 );
    TS_ASSERT_DELTA( accepted->AvgRtt(), 0.15 + 0.1, 1e-6 );

    DefaultCloseConnection();
  }


  void test_ping_retransmit()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    //ping retransmit
    sockSrv->AddIncomingLossPattern( "00" );

    poll( rdpOpt1.pingPeriod + 0.2 );
    TS_ASSERT_DELTA( connection->AvgRtt(), 0.0, 1e-6 );
    TS_ASSERT_DELTA( accepted->AvgRtt(), 0.0, 1e-6 );
    poll( 0.2, 4 );
    TS_ASSERT_DELTA( connection->AvgRtt(), 0.2, 1e-6 );
    TS_ASSERT_DELTA( accepted->AvgRtt(), 0.2, 1e-6 );

    DefaultCloseConnection();
  }


  void test_conn_failed_by_ping_retransmit()
  {
    SetupEnvironment( 0 );
    CheckAcceptedConnection();

    //ping retransmit
    sockSrv->AddIncomingLossPattern( "0000000000" );

    poll( rdpOpt1.pingPeriod + 0.2 );
    TS_ASSERT_DELTA( connection->AvgRtt(), 0.0, 1e-6 );
    TS_ASSERT_DELTA( accepted->AvgRtt(), 0.0, 1e-6 );
    poll( 0.3 );
    poll( 0.6 );
    poll( 1.2 );
    poll( 2.4 );
    poll( 3.0 );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( accepted->Status() == ni_udp::EConnStatus::Ready );
    poll( 3.0, 3 );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Failed );
    TS_ASSERT( accepted->Status() == ni_udp::EConnStatus::Failed );
  }


  void test_repeat_conn_after_shutdown()
  {
    SetupEnvironment( 0 );

    poll( 0.2, 10 );
    TS_ASSERT( connection->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( listenConnCb->established.size() == 1 );
    TS_ASSERT( listenCb->newConnections.size() == 1 );
    TS_ASSERT( connCb->established.size() == 1 );

    //Emulate one side process termination and clean restart:
    sockSrv->AddIncomingLossPattern( "0" );
    rdp2 = 0;
    connection = 0;
    connCb = 0;
    poll( 0.1 );

    Strong<ni_rnd::IFactory> rndFact = new ni_rnd::Factory;
    Strong<ni_rnd::IGenerator> rnd = rndFact->Produce( 201 );

    StrongMT<SocketFactory> sockFact = new SocketFactory( sockSrv, "192.168.0.2", addr2.Port() );

    rdp2 = new ni_udp::Rdp( true );
    rdp2->Init( sockFact, rdpOpt2, rnd, clock );

    StrongMT<ConnCallback> newConn2Cb = new ConnCallback;
    StrongMT<ni_udp::IRdpConnection> newConnection = rdp2->Connect( addr1, 100, newConn2Cb );
    TS_ASSERT( newConnection->Status() == ni_udp::EConnStatus::Pending );
    poll( 0.2, 6 );
    TS_ASSERT( newConnection->Status() == ni_udp::EConnStatus::Ready );
    TS_ASSERT( listenCb->newConnections.size() == 2 );
    accepted = listenCb->newConnections[1];

    SendAndRecieveDatagram( newConnection, listenConnCb, "Msg", 3 );
    poll( 0.1, 3 );

    DefaultCloseConnection( newConnection, accepted );
  }


  void xtest_ping_spam()
  {
    //TODO
  }
};

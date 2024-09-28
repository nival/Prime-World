//!Component("Network/RUDP/SockSrvLocal")
//!Component("System/Commands")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "SockSrvLocal.h"
#include "System/NiTimer.h"


struct Test_LocalSockSrv : public CxxTest::TestSuite
{
  void setUp()
  {
    WSADATA data;
    memset( &data, 0, sizeof( data ) );
    WSAStartup( MAKEWORD( 2, 2 ), &data );
  }

  void tearDown()
  {
    WSACleanup();
  }



  class SockCallback : public ni_udp::ISocketCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( SockCallback, ni_udp::ISocketCallback, BaseObjectMT );

  public:
    explicit SockCallback( timer::ITimer * _clock ) :
    clock( _clock )
    {}

    //ni_udp::ISocketCallback
    virtual void OnDatagram( ni_udp::ISocket * _socket, const ni_udp::NetAddr & _remoteAddr, const void * _data, size_t _size, timer::Time _absRecvTime )
    {
      StrongMT<ni_udp::LocalDatagram> dg = new ni_udp::LocalDatagram( _data, _size, _remoteAddr );
      dg->SetDeliveryTime( clock->Now() );
      queue.push_back( dg );
    }

    virtual void OnWritable( ni_udp::ISocket * _socket )
    {
    }

    std::list<StrongMT<ni_udp::LocalDatagram>> queue;
    StrongMT<timer::ITimer> clock;
  };



  void test_smoke()
  {
    StrongMT<timer::FixedTimer> clock = new timer::FixedTimer( 1.0, 0 );

    StrongMT<ni_udp::LocalSocketServer> srv = new ni_udp::LocalSocketServer( clock );

    StrongMT<SockCallback> cb1 = new SockCallback( clock ), cb2 = new SockCallback( clock );

    clock->Set( 2.0, 0 );
    srv->Poll();

    StrongMT<ni_udp::ISocket> sock1 = srv->Open( cb1, ni_udp::NetAddr( "127.0.0.1", 7777 ), 5 );
    TS_ASSERT( sock1 );
    TS_ASSERT( sock1->Status() == ni_udp::ESocketStatus::Ready );

    StrongMT<ni_udp::ISocket> sock2 = srv->Open( cb2, ni_udp::NetAddr( "127.0.0.1", 8888 ), 5 );
    TS_ASSERT( sock2 );
    TS_ASSERT( sock2->Status() == ni_udp::ESocketStatus::Ready );

    clock->Set( 4.0, 0 );
    srv->Poll();

    sock1->SendDatagram( ni_udp::NetAddr( "127.0.0.1", 8888 ), "Hello", 6 );
    clock->Set( 4.05, 0 );
    srv->Poll();
    TS_ASSERT( cb1->queue.empty() );
    TS_ASSERT( cb2->queue.empty() );

    clock->Set( 4.2, 0 );
    srv->Poll();
    TS_ASSERT( cb1->queue.empty() );
    TS_ASSERT( cb2->queue.size() == 1 );
    TS_ASSERT( cb2->queue.front()->Size() == 6 );
    TS_ASSERT_DELTA( cb2->queue.front()->DeliveryTime(), 4.2, 1e-3 );
    TS_ASSERT( cb2->queue.front()->SrcAddr() == ni_udp::NetAddr( "127.0.0.1", 7777 ) );
    TS_ASSERT( !stricmp( (const char *)cb2->queue.front()->Bytes(), "Hello" ) );
  }


  void test_loss_pattern()
  {
    StrongMT<timer::FixedTimer> clock = new timer::FixedTimer( 1.0, 0 );

    StrongMT<ni_udp::LocalSocketServer> srv = new ni_udp::LocalSocketServer( clock );
    StrongMT<SockCallback> cb1 = new SockCallback( clock ), cb2 = new SockCallback( clock );
    StrongMT<ni_udp::ISocket> sock1 = srv->Open( cb1, ni_udp::NetAddr( "127.0.0.1", 7777 ), 5 );
    StrongMT<ni_udp::ISocket> sock2 = srv->Open( cb2, ni_udp::NetAddr( "127.0.0.1", 8888 ), 5 );

    srv->AddIncomingLossPattern( "101" );

    clock->Set( 1.0, 0 );
    srv->Poll();

    sock1->SendDatagram( ni_udp::NetAddr( "127.0.0.1", 8888 ), "One", 4 );
    sock1->SendDatagram( ni_udp::NetAddr( "127.0.0.1", 8888 ), "Two", 4 );
    sock1->SendDatagram( ni_udp::NetAddr( "127.0.0.1", 8888 ), "Three", 6 );

    clock->Set( 2.0, 0 );
    srv->Poll();

    TS_ASSERT( cb1->queue.empty() );
    TS_ASSERT( cb2->queue.size() == 2 );

    TS_ASSERT( cb2->queue.front()->Size() == 4 );
    TS_ASSERT( !stricmp( (const char *)cb2->queue.front()->Bytes(), "One" ) );

    cb2->queue.pop_front();

    TS_ASSERT( cb2->queue.front()->Size() == 6 );
    TS_ASSERT( !stricmp( (const char *)cb2->queue.front()->Bytes(), "Three" ) );
  }
};

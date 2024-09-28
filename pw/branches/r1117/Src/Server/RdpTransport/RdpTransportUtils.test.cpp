//!Component('Server/RdpTransport/RdpTransportUtils')

#include <System/stdafx.h>
#include <cxxtest/TestSuite.h>
#include <System/TestSuite.h>

#include "RdpTransportUtils.h"
#include "Network/RUDP/UdpSocket.h"

struct Test_RdpTransportUtils : public CxxTest::TestSuite
{
  virtual void setUp()
  {
    ni_udp::UdpSocket::GlobalInit();
  }

  virtual void tearDown()
  {
    ni_udp::UdpSocket::GlobalShutdown();
  }


  void check_ip( const ni_udp::NetAddr & _a, const char * _templ )
  {
    char buf[32];
    _a.StrIp( buf, 32 );
    TS_ASSERT_EQUALS( stricmp( buf, _templ ), 0 );
  }

  void test_1()
  {
    ni_udp::NetAddr a( "192.168.1.55", 28000 );
    string fmt = rdp_transport::FormatAddr( a, 1001 );
    TS_ASSERT_EQUALS( fmt, "192.168.1.55:28000@1001" );
  }


  void test_fail1()
  {
    ni_udp::NetAddr a;
    unsigned mux = 0;
    TS_ASSERT( !rdp_transport::ParseAddress( a, mux, "192.168.3.55" ) );
  }


  void test_fail2()
  {
    ni_udp::NetAddr a;
    unsigned mux = 0;
    TS_ASSERT( !rdp_transport::ParseAddress( a, mux, "192.168.3.55:10:10" ) );
  }


  void test_2()
  {
    ni_udp::NetAddr a;
    unsigned mux = 0;
    TS_ASSERT( rdp_transport::ParseAddress( a, mux, "192.168.2.55:28000@1001" ) );
    check_ip( a, "192.168.2.55" );
    TS_ASSERT_EQUALS( a.Port(), 28000 );
    TS_ASSERT_EQUALS( mux, 1001 );
  }


  void test_3()
  {
    ni_udp::NetAddr a;
    unsigned mux = 0;
    TS_ASSERT( rdp_transport::ParseAddress( a, mux, "192.168.10.56:29000" ) );
    check_ip( a, "192.168.10.56" );
    TS_ASSERT_EQUALS( a.Port(), 29000 );
    TS_ASSERT_EQUALS( mux, 0 );
  }


  void test_4()
  {
    ni_udp::NetAddr a;
    unsigned mux = 0;
    TS_ASSERT( rdp_transport::ParseAddress( a, mux, "29000" ) );
    check_ip( a, "0.0.0.0" );
    TS_ASSERT_EQUALS( a.Port(), 29000 );
    TS_ASSERT_EQUALS( mux, 0 );
  }

  void test_5()
  {
    ni_udp::NetAddr a;
    unsigned mux = 0;
    TS_ASSERT( rdp_transport::ParseAddress( a, mux, "28777@101" ) );
    check_ip( a, "0.0.0.0" );
    TS_ASSERT_EQUALS( a.Port(), 28777 );
    TS_ASSERT_EQUALS( mux, 101 );
  }
};

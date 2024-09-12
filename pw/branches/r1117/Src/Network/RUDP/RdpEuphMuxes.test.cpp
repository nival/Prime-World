//!Component("Network/RUDP/RDP")
//!Component("System/Commands")
//!Component("Network/RUDP/SockSrvLocal")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "RdpEphMux.h"
#include "System/RandomInterfaceImpl.h"

struct Test_RdpEuphMuxes : public CxxTest::TestSuite
{
  class FakeRandom : public ni_rnd::IGenerator, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( FakeRandom, ni_rnd::IGenerator, BaseObjectST );
  public:
    FakeRandom() {}
    FakeRandom & operator << ( unsigned _x ) { data.push_back( _x ); return *this; }
    //ni_rnd::IGenerator
    virtual unsigned Next() {
      TS_ASSERT( !data.empty() );
      if ( data.empty() )
        return 0;
      unsigned x = data.front();
      data.pop_front();
      return x;
    }

  private:
    std::list<unsigned>  data;
  };


  void test_smoke()
  {
    ni_udp::RdpOptions rdpOpt;

    Strong<FakeRandom> rnd = new FakeRandom;
    ( *rnd ) << 100 << 0 << 123 << 0 << 60 << 3 << 10;

    StrongMT<ni_udp::RdpEphemeralMuxes> a = new ni_udp::RdpEphemeralMuxes( new ni_udp::RdpOptionsObject( rdpOpt ), rnd );

    unsigned m0 = a->AllocateMux( 3.0 );
    TS_ASSERT_EQUALS( m0, rdpOpt.firstEphemeralMux + 100 );

    a->FreeMux( m0, 13.0 );

    unsigned m1 = a->AllocateMux( 11.0 );
    TS_ASSERT_EQUALS( m1, m0 + 123 + 1 );

    unsigned m2 = a->AllocateMux( 12.0 );
    TS_ASSERT_EQUALS( m2, m0 + 60 + 1 );

    unsigned m3 = a->AllocateMux( 14.0 );
    TS_ASSERT_EQUALS( m3, m1 + 10 + 1 );
  }


  void test_close_points()
  {
    ni_udp::RdpOptions rdpOpt;

    Strong<FakeRandom> rnd = new FakeRandom;
    ( *rnd ) << 100 << 0 << 0 << 0 << 0 << 0 << 0;

    StrongMT<ni_udp::RdpEphemeralMuxes> a = new ni_udp::RdpEphemeralMuxes( new ni_udp::RdpOptionsObject( rdpOpt ), rnd );

    unsigned m0 = a->AllocateMux( 3.0 );
    TS_ASSERT_EQUALS( m0, rdpOpt.firstEphemeralMux + 100 );

    unsigned m1 = a->AllocateMux( 3.0 );
    TS_ASSERT_EQUALS( m1, rdpOpt.firstEphemeralMux + 101 );

    unsigned m2 = a->AllocateMux( 3.0 );
    TS_ASSERT_EQUALS( m2, rdpOpt.firstEphemeralMux + 102 );

    unsigned m3 = a->AllocateMux( 3.0 );
    TS_ASSERT_EQUALS( m3, rdpOpt.firstEphemeralMux + 103 );
  }



  void test_crossing_upper_bound()
  {
    ni_udp::RdpOptions rdpOpt;

    Strong<FakeRandom> rnd = new FakeRandom;
    ( *rnd ) << 32760 << 0 << 20;

    StrongMT<ni_udp::RdpEphemeralMuxes> a = new ni_udp::RdpEphemeralMuxes( new ni_udp::RdpOptionsObject( rdpOpt ), rnd );

    unsigned m0 = a->AllocateMux( 5.0 );
    TS_ASSERT_EQUALS( m0, rdpOpt.firstEphemeralMux + 32760 );

    unsigned m1 = a->AllocateMux( 5.0 );
    TS_ASSERT_EQUALS( m1, ( rdpOpt.firstEphemeralMux + 32760 ) + 20 - rdpOpt.lastEphemeralMux + rdpOpt.firstEphemeralMux );
  }


  void test_crossing_upper_bound_first_index()
  {
    ni_udp::RdpOptions rdpOpt;

    Strong<FakeRandom> rnd = new FakeRandom;
    ( *rnd ) << 25 << 0 << 32767 - 25;

    StrongMT<ni_udp::RdpEphemeralMuxes> a = new ni_udp::RdpEphemeralMuxes( new ni_udp::RdpOptionsObject( rdpOpt ), rnd );

    unsigned m0 = a->AllocateMux( 5.0 );
    TS_ASSERT_EQUALS( m0, rdpOpt.firstEphemeralMux + 25 );

    unsigned m1 = a->AllocateMux( 5.0 );
    TS_ASSERT_EQUALS( m1, rdpOpt.firstEphemeralMux );
  }
};

//!Component("LiveMMakingTool/DataHistogram")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"


#include "DataHistogram.h"

using namespace nutils;

struct DataHistogramTest : public CxxTest::TestSuite
{
  void test_empty()
  {
    DataHistogram h( 3.0 );
    TS_ASSERT_EQUALS( h.BandsCount(), 1 );

    DataHistogram::SBandDescr b;
    TS_ASSERT( !h.GetBand( b, 0 ) );
  }


  void test_range_check()
  {
    DataHistogram h( 2.5f );
    h.AddValue( 5.7f );
    TS_ASSERT_EQUALS( h.BandsCount(), 1 );

    DataHistogram::SBandDescr b;
    TS_ASSERT( !h.GetBand( b, -1 ) );
    TS_ASSERT( !h.GetBand( b, 1 ) );
    TS_ASSERT( !h.GetBand( b, 2 ) );
  }


  void test_one_hit_around_zero()
  {
    DataHistogram h( 2.4f );
    h.AddValue( 1.9f );
    TS_ASSERT_EQUALS( h.BandsCount(), 1 );

    DataHistogram::SBandDescr b;
    TS_ASSERT( h.GetBand( b, 0 ) );
    TS_ASSERT_DELTA( b.from, 0.0f, 1e-3f );
    TS_ASSERT_DELTA( b.to, 2.4f, 1e-3f );
    TS_ASSERT_EQUALS( b.hits, 1 );
  }


  void test_one_hit_forward()
  {
    DataHistogram h( 2.8f );
    h.AddValue( 9.5f );
    TS_ASSERT_EQUALS( h.BandsCount(), 1 );

    DataHistogram::SBandDescr b;
    TS_ASSERT( h.GetBand( b, 0 ) );
    TS_ASSERT_DELTA( b.from, 8.4f, 1e-3f );
    TS_ASSERT_DELTA( b.to, 11.2f, 1e-3f );
    TS_ASSERT_EQUALS( b.hits, 1 );
  }


  void test_one_hit_minus()
  {
    DataHistogram h( 3.0 );
    h.AddValue( -5.0 );
    TS_ASSERT_EQUALS( h.BandsCount(), 1 );

    DataHistogram::SBandDescr b;
    TS_ASSERT( h.GetBand( b, 0 ) );
    TS_ASSERT_DELTA( b.from, -6.0f, 1e-3f );
    TS_ASSERT_DELTA( b.to, -3.0f, 1e-3f );
    TS_ASSERT_EQUALS( b.hits, 1 );
  }


  void test_two_close_hits()
  {
    DataHistogram h( 5.0f );
    h.AddValue( 11.0f );
    h.AddValue( 13.0f );
    TS_ASSERT_EQUALS( h.BandsCount(), 1 );

    DataHistogram::SBandDescr b;
    TS_ASSERT( h.GetBand( b, 0 ) );
    TS_ASSERT_DELTA( b.from, 10.0f, 1e-3f );
    TS_ASSERT_DELTA( b.to, 15.0f, 1e-3f );
    TS_ASSERT_EQUALS( b.hits, 2 );
  }


  void test_two_neighbour_bands()
  {
    DataHistogram h( 10.0f );
    h.AddValue( 15.0f );
    h.AddValue( 16.0f );
    h.AddValue( 21.0f );
    h.AddValue( 22.0f );
    h.AddValue( 22.0f );
    TS_ASSERT_EQUALS( h.BandsCount(), 2 );

    DataHistogram::SBandDescr b;

    TS_ASSERT( h.GetBand( b, 0 ) );
    TS_ASSERT_DELTA( b.from, 10.0f, 1e-3f );
    TS_ASSERT_DELTA( b.to, 20.0f, 1e-3f );
    TS_ASSERT_EQUALS( b.hits, 2 );

    TS_ASSERT( h.GetBand( b, 1 ) );
    TS_ASSERT_DELTA( b.from, 20.0f, 1e-3f );
    TS_ASSERT_DELTA( b.to, 30.0f, 1e-3f );
    TS_ASSERT_EQUALS( b.hits, 3 );
  }


  void test_two_distant_bands()
  {
    DataHistogram h( 10.0f );
    h.AddValue( 21.0f );
    h.AddValue( 22.0f );
    h.AddValue( 22.0f );
    h.AddValue( -31.0f );
    h.AddValue( -32.0f );
    TS_ASSERT_EQUALS( h.BandsCount(), 7 );

    DataHistogram::SBandDescr b;

    TS_ASSERT( h.GetBand( b, 0 ) );
    TS_ASSERT_DELTA( b.from, -40.0f, 1e-3f );
    TS_ASSERT_DELTA( b.to, -30.0f, 1e-3f );
    TS_ASSERT_EQUALS( b.hits, 2 );

    for ( int i = 1; i < 6; ++i )
    {
      TS_ASSERT( h.GetBand( b, i ) );
      TS_ASSERT_DELTA( b.from, -40.0f + i * 10.0f, 1e-3f );
      TS_ASSERT_DELTA( b.to, -30.0f + i * 10.0f, 1e-3f );
      TS_ASSERT_EQUALS( b.hits, 0 );
    }

    TS_ASSERT( h.GetBand( b, 6 ) );
    TS_ASSERT_DELTA( b.from, 20.0f, 1e-3f );
    TS_ASSERT_DELTA( b.to, 30.0f, 1e-3f );
    TS_ASSERT_EQUALS( b.hits, 3 );
  }
};

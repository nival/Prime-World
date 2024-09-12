//!Component("System/Histogram")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "Histogram.h"
#include "SafeTextFormatHistogram.h"
#include "Lifehacks.h"
#include <string>


struct Test_Histogram : public CxxTest::TestSuite
{
  void test_uniform_smoke()
  {
    UniformHistogram h( 3.0, 10.1, 2.0 );

    TS_ASSERT( h.Size() == 4 );
    TS_ASSERT_DELTA( h.GetTotal().lowerBound, 3.0, 1e-6 );
    TS_ASSERT_DELTA( h.GetTotal().upperBound, 10.1, 1e-6 );
    TS_ASSERT_DELTA( h.GetBand( 0 ).lowerBound, 3.0, 1e-6 );
    TS_ASSERT_DELTA( h.GetBand( 0 ).upperBound, 3.0 + ( 10.1 - 3.0 ) / 4.0, 1e-6 );

    h.AddData( 5.5 );
    TS_ASSERT( h.GetBand( 0 ).hits == 0 );
    TS_ASSERT( h.GetBand( 1 ).hits == 1 );
    TS_ASSERT_DELTA( h.GetBand( 1 ).avg, 5.5, 1e-6 );
    TS_ASSERT_DELTA( h.GetBand( 1 ).minValue, 5.5, 1e-6 );
    TS_ASSERT_DELTA( h.GetBand( 1 ).maxValue, 5.5, 1e-6 );
    TS_ASSERT_DELTA( h.GetBand( 1 ).avg, 5.5, 1e-6 );

    h.AddData( 6.0 );
    h.AddData( 9.5 );
    TS_ASSERT( h.GetBand( 0 ).hits == 0 );
    TS_ASSERT( h.GetBand( 1 ).hits == 2 );
    TS_ASSERT( h.GetBand( 3 ).hits == 1 );
    TS_ASSERT_DELTA( h.GetBand( 1 ).avg, 5.75, 1e-6 );
    TS_ASSERT_DELTA( h.GetBand( 1 ).minValue, 5.5, 1e-6 );
    TS_ASSERT_DELTA( h.GetBand( 1 ).maxValue, 6.0, 1e-6 );

    TS_ASSERT( h.GetTotal().hits == 3 );
    TS_ASSERT_DELTA( h.GetTotal().avg, 7.0, 1e-6 );
    TS_ASSERT_DELTA( h.GetTotal().minValue, 5.5, 1e-6 );
    TS_ASSERT_DELTA( h.GetTotal().maxValue, 9.5, 1e-6 );

    h.AddData( 12.0 );
    h.AddData( 12.0 );
    h.AddData( 15.0 );
    h.AddData( -10.0 );
    TS_ASSERT( h.LowerHits() == 1 );
    TS_ASSERT( h.UpperHits() == 3 );

    TS_ASSERT( h.GetTotal().hits == 7 );
    TS_ASSERT_DELTA( h.GetTotal().avg, 7.1428571, 1e-6 );
    TS_ASSERT_DELTA( h.GetTotal().minValue, -10.0, 1e-6 );
    TS_ASSERT_DELTA( h.GetTotal().maxValue, 15.0, 1e-6 );

    std::string tmp = NI_STRFMT( "%.2f", h );
  }

  void test_custom_smoke()
  {
    CustomHistogram h( lifehack::EasyVector<double>( -5.0, +5.0, 50.0, 100.0, 1000.0, 10000.0 ) );

    TS_ASSERT( h.Size() == 5 );
    TS_ASSERT_DELTA( h.GetTotal().lowerBound, -5.0, 1e-6 );
    TS_ASSERT_DELTA( h.GetTotal().upperBound, 10000.0, 1e-6 );

    TS_ASSERT_DELTA( h.GetBand( 1 ).lowerBound, 5.0, 1e-6 );
    TS_ASSERT_DELTA( h.GetBand( 1 ).upperBound, 50.0, 1e-6 );

    h.AddData( 0.0 );
    h.AddData( 1.0 );
    h.AddData( 900.0 );
    h.AddData( 911.0 );
    h.AddData( 5000.0 );

    TS_ASSERT_EQUALS( h.GetBand( 0 ).hits, 2 );
    TS_ASSERT_EQUALS( h.GetBand( 1 ).hits, 0 );
    TS_ASSERT_EQUALS( h.GetBand( 2 ).hits, 0 );
    TS_ASSERT_EQUALS( h.GetBand( 3 ).hits, 2 );
    TS_ASSERT_EQUALS( h.GetBand( 4 ).hits, 1 );

    std::string tmp = NI_STRFMT( "%.1f", h );
  }
};

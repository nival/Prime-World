//!Component('EventAccumulator')
//!Component('Commands')

#include "stdafx.h"
#include "EventAccumulator.h"
#include "cxxtest/TestSuite.h"


class EventAccumulatorTest : public CxxTest::TestSuite
{
public:
  void setUp() {}
  void tearDown() {}

  void test_simpliest()
  {
    EventAccumulator c( 30.0, 3, 60.0 );

    TS_ASSERT( !c.HasNewValues() );
    TS_ASSERT_EQUALS( c.AvgRate(), 0.0 );
    TS_ASSERT_EQUALS( c.AvgValue(), 0.0 );


    c.AddEvent( 1, 5.0 );
    c.AddEvent( 1, 3.3 );
    c.Poll( 65.0 );
    TS_ASSERT( !c.HasNewValues() );
    c.AddEvent( 15, 2.17 );
    c.AddEvent( 1, 3.1 );
    c.Poll( 72.0 );

    TS_ASSERT( c.HasNewValues() );
    c.ResetNewValuesFlag();
    TS_ASSERT( !c.HasNewValues() );
    TS_ASSERT_EQUALS( c.AvgRate(), ( 15 + 3 ) / ( 72.0 - 60.0 ) );
    TS_ASSERT_EQUALS( c.AvgValue(), ( 5.0 + 3.3 + 15 * 2.17 + 3.1 ) / ( 15 + 3 ) );

    c.AddEvent( 3, -4.0 );
    TS_ASSERT( !c.HasNewValues() );
    c.AddEvent( 3 );
    c.Poll( 85.0 );

    TS_ASSERT( c.HasNewValues() );
    TS_ASSERT_EQUALS( c.AvgRate(), ( 15 + 3 + 3 + 3 ) / ( 85.0 - 60.0 ) );
    TS_ASSERT_EQUALS( c.AvgValue(), ( 5.0 + 3.3 + 15 * 2.17 + 3.1 + 3 * (-4.0) ) / ( 15 + 3 + 3 + 3 ) );
    c.ResetNewValuesFlag();

    c.AddEvent( 7 );
    c.Poll( 98.0 );

    TS_ASSERT( c.HasNewValues() );
    TS_ASSERT_EQUALS( c.AvgRate(), ( 15 + 3 + 3 + 3 + 7 ) / ( 98.0 - 60.0 ) );
    TS_ASSERT_EQUALS( c.AvgValue(), ( 5.0 + 3.3 + 15 * 2.17 + 3.1 + 3 * (-4.0) ) / ( 15 + 3 + 3 + 3 + 7 ) );
    c.ResetNewValuesFlag();

    c.AddEvent( 5, 11.0 );
    c.Poll( 110.0 );

    TS_ASSERT( c.HasNewValues() );
    TS_ASSERT_EQUALS( c.AvgRate(), ( 3 + 3 + 7 + 5 ) / ( 110.0 - 72.0 ) );
    TS_ASSERT_EQUALS( c.AvgValue(), ( 3 * (-4.0) + 5 * 11.0 ) / ( 3 + 3 + 7 + 5 ) );
    c.ResetNewValuesFlag();
  }
};

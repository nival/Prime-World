//!Component("Math4")
#include "cxxtest/TestSuite.h"

struct MyTestSuite : public CxxTest::TestSuite 
{
    void testAddition( void )
    {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
    }
};

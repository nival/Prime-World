//!Component("test1/test")
//!Component("test2/test")
#include "cxxtest/TestSuite.h"

struct BadFilterSuite : public CxxTest::TestSuite 
{
    void testAddition( void )
    {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
    }
};

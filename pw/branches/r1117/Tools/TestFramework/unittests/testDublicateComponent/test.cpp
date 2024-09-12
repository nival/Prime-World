//!Component("D")
#include "cxxtest/TestSuite.h"

struct DublicateComponent : public CxxTest::TestSuite 
{
    void testAddition( void )
    {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
    }
};

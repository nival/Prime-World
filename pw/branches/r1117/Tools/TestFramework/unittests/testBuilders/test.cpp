//!Component("System/FmodC")
//!Component("Two/Bld")
#include "cxxtest/TestSuite.h"

struct BuildersSuite : public CxxTest::TestSuite 
{
    void testAddition( void )
    {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
    }
};

//!Component("DllApp")
#include "cxxtest/TestSuite.h"
#include "dll.h"

struct ApplicationBuild : public CxxTest::TestSuite 
{
    void testAddition( void )
    {
        TS_ASSERT( 4 + 1 > getValue() );
        TS_ASSERT_EQUALS( 3 + 1, getValue() );
    }
};

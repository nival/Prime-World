//!Component("Asm/AsmComp")
#include "cxxtest/TestSuite.h"

extern "C" {int _cdecl simple(int, int *);}

struct AsmBuildTest : public CxxTest::TestSuite 
{
    void testAddition( void )
    {
        int res1;
        int res2;

        res2 = simple( 256, &res1 );

        TS_ASSERT_EQUALS( res1, 512 );
        TS_ASSERT_EQUALS( res2, 1024 );
    }
};

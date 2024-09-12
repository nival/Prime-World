//!Component("System/Math")
#include <cxxtest/TestSuite.h>
#include "stdafx.h"
#include "FastMath.h"

class TestFastMath : public CxxTest::TestSuite 
{
public:
    void testASin( void )
    {
    	TS_ASSERT_DELTA( 0.f, NMath::FastASin( 1.f ), 1e-3 );
    }
};

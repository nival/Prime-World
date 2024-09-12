#include <cxxtest/TestSuite.h>

struct MD5Hash : public CxxTest::TestSuite 
{
	void testAddition( void )
	{
		TS_ASSERT( 1 + 1 > 1 );
		TS_ASSERT_EQUALS( 1 + 1, 2 );
	}
};
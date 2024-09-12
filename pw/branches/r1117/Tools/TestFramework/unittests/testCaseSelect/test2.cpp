#include <cxxtest/TestSuite.h>
#include <iostream>
#include <fstream>


namespace
{
	std::ofstream file2;
}

struct Test2Suite : public CxxTest::TestSuite 
{
public:

	Test2Suite()
	{
		file2.open("log.log");
	}
	void testNumber1( void )
	{
		file2 << "TestSuite1.testNumber1" << std::endl << std::flush;
	}
	void testNumber2( void )
	{
		file2 << "TestSuite1.testNumber2" << std::endl << std::flush;
	}
	void testNumber3( void )
	{
		file2 << "TestSuite1.testNumber3" << std::endl << std::flush;
	}
	void testNumber4( void )
	{
		file2 << "TestSuite1.testNumber4" << std::endl << std::flush;
	}
};

struct Test2Suite2 : public CxxTest::TestSuite 
{
public:

	Test2Suite2()
	{
		if ( !file2.is_open() )
		{
			file2.open("log.log");
		}
	}
	void testNumber10( void )
	{
		file2 << "TestSuite2.testNumber10" << std::endl << std::flush;
	}
	void testNumber20( void )
	{
		file2 << "TestSuite2.testNumber20" << std::endl << std::flush;
	}
	void testNumber30( void )
	{
		file2 << "TestSuite2.testNumber30" << std::endl << std::flush;
	}
	void testNumber40( void )
	{
		file2 << "TestSuite2.testNumber40" << std::endl << std::flush;
	}
};




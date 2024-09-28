#include <cxxtest/TestSuite.h>
#include <iostream>
#include <fstream>

namespace
{
	std::ofstream file;
}


class TestSuite1 : public CxxTest::TestSuite 
{
public:

	TestSuite1()
	{
		file.open("log.log");
	}
	void testNumber1( void )
	{
		file << "TestSuite1.testNumber1" << std::endl << std::flush;
	}
	void testNumber2( void )
	{
		file << "TestSuite1.testNumber2" << std::endl << std::flush;
	}
	void testNumber3( void )
	{
		file << "TestSuite1.testNumber3" << std::endl << std::flush;
	}
	void testNumber4( void )
	{
		file << "TestSuite1.testNumber4" << std::endl << std::flush;
	}
};

class TestSuite2 : public CxxTest::TestSuite 
{
	
public:

	TestSuite2()
	{
		if ( !file.is_open() )
		{
			file.open("log.log");
		}
	}
	void testNumber10( void )
	{
		file << "TestSuite2.testNumber10" << std::endl << std::flush;
	}
	void testNumber20( void )
	{
		file << "TestSuite2.testNumber20" << std::endl << std::flush;
	}
	void testNumber30( void )
	{
		file << "TestSuite2.testNumber30" << std::endl << std::flush;
	}
	void testNumber40( void )
	{
		file << "TestSuite2.testNumber40" << std::endl << std::flush;
	}
};

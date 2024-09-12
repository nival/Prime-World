#include <System/threading/thread.h>
#include <System/sleep.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <cstdlib>
#include <ctime>

/*

	Список необходимых тестов:

	1.1. Проверка корректности установки статусов потока на различных стадиях выполнения (main case)

*/

using namespace nival;

struct thread_1_1_t: thread_t {

	virtual result_t work()
	{
		while ( is_working() )
      sleep( 1 );

		CPPUNIT_ASSERT( get_state() == thread_t::finishing );

    return result_ok;
	}

};

struct thread_test_suite_t: CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( thread_test_suite_t );

		CPPUNIT_TEST( test_1_1 );

	CPPUNIT_TEST_SUITE_END();

	// 1.1. Проверка корректности установки статусов потока на различных стадиях выполнения
	void test_1_1()
	{
		ptr_t< thread_1_1_t > thread = new ts_object_t< thread_1_1_t >;

		CPPUNIT_ASSERT( thread->get_state() == thread_t::finished );

		CPPUNIT_ASSERT( thread->start() == result_ok );
		CPPUNIT_ASSERT( NV_CSUCCESS( thread->wait_for_start( 1000 ) ) );

		CPPUNIT_ASSERT( thread->is_working() == true );

		CPPUNIT_ASSERT( thread->stop() == result_ok );
		CPPUNIT_ASSERT( thread->is_working() == false );

		CPPUNIT_ASSERT( NV_CSUCCESS( thread->wait( 1000 ) ) );
		CPPUNIT_ASSERT( thread->is_finished() == true );
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( thread_test_suite_t );

int main( int argc, char * argv[] )
{
	std::srand( static_cast< unsigned int >( time( NULL ) ) );

	CppUnit::TextUi::TestRunner runner;
	runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );

	return runner.run( "", false );
}


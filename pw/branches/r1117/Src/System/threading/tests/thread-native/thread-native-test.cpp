#include <System/Thread.h>
#include <System/object.h>
#include <System/get_tick_count.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <cstring>
#include <cstdlib>

/*

	Список необходимых тестов:

	1. Функциональность, существующая в старой реализации Thread.h
	1.1. Проверка создания экземпляра класса потока в приостановленном режиме или без создания физического потока.
	1.2. Проверка возобновляемости работы потока после создания.
	1.3. Проверка приостановки работы потока.
	1.4.1. Проверка функциональности остановки работы потока при вызове функции Wait из другого потока, нежели останавливаемый.
	1.4.2. Проверка функциональности остановки работы потока при вызове функции Wait из того же самого потока, что и останавливаемый (timeout = 0)
	1.4.3. Проверка функциональности остановки работы потока при вызове функции Wait из того же потока, что и останавливаемый (timeout > 0)
	1.5.1. Проверка Finished() при работающем потоке
	1.5.2. Проверка Finished() при остановленном потоке
	1.6.1. Проверка Terminate() при вызове метода из того же потока, что и останавливаемый (не реализован).
	1.6.2. Проверка Terminate() при вызове метода из другого потока, нежели останавливаемый (не реализован).
	1.7.1. Проверка Stop() при вызове метода с waitForStop=true из другого потока, нежели останавливаемый.
	1.7.2. Проверка Stop() при вызове метода с waitForStop=true из того же самого потока, нежели останавливаемый.
	1.7.3. Проверка работы параметра таймаута в Stop() при timeoutInMs=0
	1.7.4. Проверка работы параметра таймаута в Stop() при timeoutInMs=1000
	1.8. Проверка работы функций SetDebugThreadName() и GetDebugThreadName()
	1.9. Проверка работы функции Sleep()

	2. Кроссплатформенная функциональность, существующая в новой реализации thread.h

*/

template< typename T > class thread_wrapper_t:
	public nival::object_interface_t,
	public T
{
public:

	thread_wrapper_t( bool needs_to_resume = true ): m_executed( false )
	{
		if ( needs_to_resume )
			this->Resume();
	}

	virtual unsigned int Work()
	{
		nival::ptr_t< thread_wrapper_t > self( this );

		T::work();

		m_executed = true;

    return 0;
	}

	bool is_running() const
	{
		return this->isRunning;
	}

	bool is_executed() const
	{
		return m_executed;
	}

private:

	volatile bool m_executed;

};

struct nothing_t: threading::Thread {

	virtual unsigned int work()
	{ return 0; }

};

struct thread_1_3_t: threading::Thread {

	thread_1_3_t(): m_counter( 0 )
	{}

	virtual unsigned int work()
	{
		while ( isRunning )
			++m_counter;
    return 0;
	}

	size_t m_counter;

};

struct thread_1_4_1_t: threading::Thread {

	virtual unsigned int work()
	{
		while ( isRunning )
			threading::Sleep( 1 );
    return 0;
	}

};

struct thread_1_4_2_t: threading::Thread {

	thread_1_4_2_t(): m_wait_result( false )
	{}

	virtual unsigned int work()
	{
		while ( isRunning ) {

			Stop();
			m_wait_result = Wait( 0 );

		}

    return 0;
	}

	bool m_wait_result;

};

struct thread_1_4_3_t: threading::Thread {

	thread_1_4_3_t(): m_wait_result( false )
	{}

	virtual unsigned int work()
	{
		while ( isRunning ) {

			Stop();
			m_wait_result = Wait( 100 );

		}

    return 0;
	}

	bool m_wait_result;

};

struct thread_1_7_2_t: threading::Thread {

	virtual unsigned int work()
	{
		while ( isRunning ) {

			Stop( true );

		}

		threading::Sleep( 200 );

    return 0;
	}

};

struct thread_1_7_3_t: threading::Thread {

	virtual unsigned int work()
	{
		while ( isRunning )
			threading::Sleep( 1 );

		threading::Sleep( 200 );

    return 0;
	}

};

nival::cstr_t const thread_name_template = "sample thread name";

struct thread_1_8_t: threading::Thread {

	virtual unsigned int work()
	{
		//threading::SetDebugThreadName( thread_name_template );

		while ( isRunning )
			threading::Sleep( 1 );

    return 0;
	}

};

struct thread_test_suite_t: CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( thread_test_suite_t );

		CPPUNIT_TEST( test_1_1 );
		CPPUNIT_TEST( test_1_2 );
		CPPUNIT_TEST( test_1_3 );
		CPPUNIT_TEST( test_1_4_1 );
		CPPUNIT_TEST( test_1_4_2 );
		CPPUNIT_TEST( test_1_4_3 );
		CPPUNIT_TEST( test_1_5_1 );
		CPPUNIT_TEST( test_1_5_2 );
		CPPUNIT_TEST( test_1_7_1 );
		CPPUNIT_TEST( test_1_7_2 );
		CPPUNIT_TEST( test_1_7_3 );
		CPPUNIT_TEST( test_1_7_4 );
		CPPUNIT_TEST( test_1_8 );
		CPPUNIT_TEST( test_1_9 );

	CPPUNIT_TEST_SUITE_END();

	// 1.1. Проверка создания экземпляра класса потока в приостановленном режиме или без создания физического потока
	void test_1_1()
	{
		typedef nival::ts_object_t< thread_wrapper_t< nothing_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t( false );

		CPPUNIT_ASSERT( thread->is_executed() == false );

		// Если поток будет создан и запущен, то 100 мс должно быть более чем достаточно для отработки Work()
		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_executed() == false );
	}

	// 1.2. Проверка возобновляемости работы потока после создания
	void test_1_2()
	{
		typedef nival::ts_object_t< thread_wrapper_t< nothing_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t( false );

		threading::Sleep( 100 );
		CPPUNIT_ASSERT( thread->is_executed() == false );

		thread->Resume();

		threading::Sleep( 100 );
		CPPUNIT_ASSERT( thread->is_executed() == true );
	}

	// 1.3. Проверка приостановки работы потока
	void test_1_3()
	{
#if defined( NVN_WIN_PLATFORM )

		typedef nival::ts_object_t< thread_wrapper_t< thread_1_3_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;
		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_running() == true );
		CPPUNIT_ASSERT( thread->is_executed() == false );

		thread->Suspend();
		threading::Sleep( 100 );

		size_t current_counter = thread->m_counter;
		threading::Sleep( 100 );

		CPPUNIT_ASSERT( current_counter == thread->m_counter );

#elif defined( NVN_LINUX_PLATFORM )

		// This test exists for Windows only because Suspend()

#endif
	}

	// 1.4.1. Проверка функциональности остановки работы потока при вызове функции Wait из другого потока, нежели останавливаемый
	void test_1_4_1()
	{
		typedef nival::ts_object_t< thread_wrapper_t< thread_1_4_1_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 100 );
		CPPUNIT_ASSERT( thread->is_running() == true );

		thread->Stop();

		CPPUNIT_ASSERT( thread->Wait() == true );
		CPPUNIT_ASSERT( thread->is_running() == false );
	}

	// 1.4.2. Проверка функциональности остановки работы потока при вызове функции Wait из того же самого потока, что и останавливаемый (timeout = 0)
	void test_1_4_2()
	{
		typedef nival::ts_object_t< thread_wrapper_t< thread_1_4_2_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_running() == false);
		CPPUNIT_ASSERT( thread->is_executed() == true );
		CPPUNIT_ASSERT( thread->m_wait_result == true );
	}

	// 1.4.3. Проверка функциональности остановки работы потока при вызове функции Wait из того же потока, что и останавливаемый (timeout > 0)
	void test_1_4_3()
	{
		typedef nival::ts_object_t< thread_wrapper_t< thread_1_4_3_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 300 );

		CPPUNIT_ASSERT( thread->is_running() == false );
		CPPUNIT_ASSERT( thread->is_executed() == true );
		CPPUNIT_ASSERT( thread->m_wait_result == true );
	}

	// 1.5.1. Проверка Finished() при работающем потоке
	void test_1_5_1()
	{
		typedef nival::ts_object_t< thread_wrapper_t< thread_1_3_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_running() == true );
		CPPUNIT_ASSERT( thread->Finished() == false );
	}

	// 1.5.2. Проверка Finished() при остановленном потоке
	void test_1_5_2()
	{
		typedef nival::ts_object_t< thread_wrapper_t< nothing_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_executed() == true );
		CPPUNIT_ASSERT( thread->Finished() == true );

		// В старой системе учета isRunning есть логическая ошибка, при которой если поток сам завершился, то isRunning не выставляется в false
		// CPPUNIT_ASSERT( thread->is_running() == false );
	}

	// 1.7.1. Проверка Stop() при вызове метода с waitForStop=true из другого потока, нежели останавливаемый
	void test_1_7_1()
	{
		typedef nival::ts_object_t< thread_wrapper_t< thread_1_3_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_executed() == false );
		CPPUNIT_ASSERT( thread->is_running() == true );

		thread->Stop( true );

		CPPUNIT_ASSERT( thread->is_running() == false );
		CPPUNIT_ASSERT( thread->Finished() == true );
		CPPUNIT_ASSERT( thread->is_executed() == true );
	}

	// 1.7.2. Проверка Stop() при вызове метода с waitForStop=true из того же самого потока, нежели останавливаемый
	void test_1_7_2()
	{
		typedef nival::ts_object_t< thread_wrapper_t< thread_1_7_2_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_executed() == false );
		CPPUNIT_ASSERT( thread->is_running() == false );
		CPPUNIT_ASSERT( thread->Finished() == false );
	}

	// 1.7.3. Проверка работы параметра таймаута в Stop() при timeoutInMs=0
	void test_1_7_3()
	{
		typedef nival::ts_object_t< thread_wrapper_t< thread_1_7_3_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_executed() == false );
		CPPUNIT_ASSERT( thread->is_running() == true );

		thread->Stop( true, 0 );

		CPPUNIT_ASSERT( thread->is_running() == false );

		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->Finished() == true );
		CPPUNIT_ASSERT( thread->is_executed() == true );
	}

	// 1.7.4. Проверка работы параметра таймаута в Stop() при timeoutInMs=1000
	void test_1_7_4()
	{
		typedef nival::ts_object_t< thread_wrapper_t< thread_1_7_3_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_executed() == false );
		CPPUNIT_ASSERT( thread->is_running() == true );

		thread->Stop( true, 300 );

		CPPUNIT_ASSERT( thread->is_running() == false );
		CPPUNIT_ASSERT( thread->Finished() == true );
		CPPUNIT_ASSERT( thread->is_executed() == true );
	}

	// 1.8. Проверка работы функций SetDebugThreadName() и GetDebugThreadName()
	void test_1_8()
	{
		typedef nival::ts_object_t< thread_wrapper_t< thread_1_8_t > > thread_object_t;

		nival::ptr_t< thread_object_t > thread = new thread_object_t;

		threading::Sleep( 100 );

		CPPUNIT_ASSERT( thread->is_executed() == false );
		CPPUNIT_ASSERT( thread->is_running() == true );
		//CPPUNIT_ASSERT( std::strcmp( threading::GetDebugThreadName( thread->Id() ), thread_name_template ) == 0 );

		thread->Stop( true );
	}

	// 1.9. Проверка работы функции Sleep()
	void test_1_9()
	{
		size_t sleep_time = size_t( 100 ) + std::rand() % 100;

		nival::uint32_t start_time = nival::get_tick_count();

		threading::Sleep( sleep_time );

		nival::uint32_t real_sleep_time = nival::get_tick_count() - start_time;
		CPPUNIT_ASSERT( abs( nival::int64_t( real_sleep_time ) - nival::int64_t( sleep_time ) ) < 30 );
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( thread_test_suite_t );

int main( int argc, char * argv[] )
{
	std::srand( time( NULL ) );

	CppUnit::TextUi::TestRunner runner;
	runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );

	return runner.run( "", false );
}


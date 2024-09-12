#include "thread.h"

#include <System/sleep.h>
#include <System/get_tick_count.h>

#include <exception>
#include <sstream>

//#include <boost/thread.hpp>

namespace boost
{
  typedef void thread;
}

namespace nival {

	namespace detail {

		inline boost::thread * get_thread( void * thread )
		{
			return reinterpret_cast< boost::thread * >( thread );
		}

		inline void release_thread( void * &thread )
		{
			if ( thread ) {

				//delete get_thread( thread );
				thread = NULL;

			}
		}

		class foreign_thread_t:
			public thread_t
		{
		public:

			foreign_thread_t()
			{
				std::stringstream ss;
				ss << "foreign-thread-" << static_cast< thread_t * >( this );

				set_thread_name( ss.str().c_str() );
			}

			virtual result_t start()
			{
				return result_impossible_action;
			}

			virtual result_t stop( bool wait_for_stop, size_t timeout )
			{
				return result_impossible_action;
			}

			virtual result_t wait( size_t timeout )
			{
				return result_impossible_action;
			}

			virtual result_t set_priority( int priority )
			{
				return result_impossible_action;
			}

			virtual bool is_foreign() const
			{
				return true;
			}

			virtual result_t work()
			{
				return result_impossible_action;
			}

		};

		class main_thread_t:
			public thread_t
		{
		public:

			main_thread_t()
			{
				set_state( thread_t::started );
				set_thread_name( "main-thread" );
			}

			virtual result_t start()
			{
				return result_impossible_action;
			}

			virtual result_t wait( size_t timeout )
			{
				return result_impossible_action;
			}

			virtual result_t set_priority( int priority )
			{
				return result_impossible_action;
			}

			virtual result_t work()
			{
				return result_impossible_action;
			}

		};

		class threading_info_t
		{
		public:

			threading_info_t()
			{
				//m_main_thread = new ts_object_t< main_thread_t >;
			}

			thread_t * get_main_thread()
			{
				return NULL; //m_main_thread;
			}

			thread_t * get_current_thread()
			{
				/*thread_ptr_t *current_thread = m_current_thread.get();
				if ( NULL == current_thread ) {

					m_current_thread.reset( new thread_ptr_t( new ts_object_t< foreign_thread_t > ) );
					return *m_current_thread;

				}*/

				return NULL; //*current_thread;
			}

			void set_current_thread( thread_t *thread )
			{
				//m_current_thread.reset( new thread_ptr_t( thread ) );
			}

		private:

			//boost::thread_specific_ptr< thread_ptr_t > m_current_thread;
			//thread_ptr_t m_main_thread;

		};

		// TODO: Needs to wrap g_threading_info var to thread-safe singleton

		// FIXME
		//threading_info_t g_threading_info;

		class thread_runner_t
		{
		public:

			thread_runner_t( thread_t *thread ): m_thread( thread )
			{}

			void operator() ()
			{
				/*if ( m_thread ) {

					g_threading_info.set_current_thread( m_thread );
					m_thread->set_state( thread_t::started );

					try {

						m_thread->set_execution_result( m_thread->work() );

					} catch ( std::exception const &e ) {

						// TODO: needs to log e.what()
						throw;

					} catch ( ... ) {

						// TODO: needs to add logging the unhandled exception to inform us about it
						m_thread->set_state( thread_t::finished );
						throw;

					}

					m_thread->set_state( thread_t::finished );

				}*/
			}

		private:

			thread_ptr_t m_thread;

		};

	} // namespace detail

	thread_t * get_main_thread()
	{
		return NULL; //detail::g_threading_info.get_main_thread();
	}

	thread_t * get_current_thread()
	{
		return NULL; //detail::g_threading_info.get_current_thread();
	}

	thread_t::thread_t(): m_state( finished ), m_thread( NULL )
	{}

	thread_t::~thread_t()
	{
		//detail::release_thread( m_thread );
	}

	result_t thread_t::start()
	{
		/*if ( CAS( m_state, finished, starting ) ) {

			try {

				detail::thread_runner_t runner( this );
				detail::release_thread( m_thread );
				m_thread = new boost::thread( runner );

			} catch ( boost::thread_resource_error const & ) {

				return result_no_resources;

			} catch ( std::bad_alloc const & ) {

				return result_no_resources;

			}

			return result_ok;

		}*/

		return 0; //result_wrong_state;
	}

	result_t thread_t::stop( bool wait_for_stop, size_t timeout )
	{
		/*states_t state;

		do {

			state = get_state();

			if ( finishing == state ) {

				if ( false == wait_for_stop )
					return result_false;

			} else if ( starting != state && started != state )
				return result_ok;

		} while ( CAS( m_state, state, finishing ) == false );*/

		return 0; // wait_for_stop ? wait( timeout ) : result_ok;
	}

	result_t thread_t::wait( size_t timeout )
	{
		/*if ( 0 == timeout )
			return is_finished() ? result_ok : result_false;

		if ( boost::this_thread::get_id() == detail::get_thread( m_thread )->get_id() )
			return result_impossible_action;

		if ( INFINITE == timeout ) {

			detail::get_thread( m_thread )->join();
			return result_ok;

		}*/

		return 0; //detail::get_thread( m_thread )->timed_join( boost::posix_time::milliseconds( timeout ) ) ? result_ok : result_false;
	}

	result_t thread_t::wait_for_start( size_t timeout )
	{
		/*states_t state = get_state();

		if ( INFINITE == timeout ) {

			while ( starting == ( state = get_state() ) )
				nival::yield();

		} else {

			bool timeout_expired = false;
			uint32_t start_tick = get_tick_count();

			for ( ; starting == state && false == timeout_expired; state = get_state() ) {

				nival::yield();

				if ( INFINITE != timeout && get_tick_count() - start_tick >= timeout && started == state )
					return result_false;

			}

		}*/

		return 0; //started == state ? result_ok : result_wrong_state;
	}

	result_t thread_t::set_priority( int priority )
	{
#if defined( NV_WIN_PLATFORM )

    //return SetThreadPriority( static_cast< HANDLE >( detail::get_thread( m_thread )->native_handle() ), priority ) ? result_ok : result_false;
    return result_not_impl;

#elif defined( NV_LINUX_PLATFORM )

		// TODO: Needs to implement thread_t::set_priority() function for linux in the future
		return result_not_impl;

#endif
	}

} // namespace nival


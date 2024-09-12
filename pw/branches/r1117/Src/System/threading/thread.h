#ifndef __THREAD_H_INCLUDED__397419__
#define __THREAD_H_INCLUDED__397419__

#include "../object.h"
#include <string>


#ifdef NV_LINUX_PLATFORM
#define INFINITE            0xFFFFFFFF  // Infinite timeout
#endif


namespace nival {

	class thread_t;
	typedef ptr_t< thread_t > thread_ptr_t;
	typedef void * thread_id_t;

	namespace detail {

		class thread_runner_t;

	}

	class thread_t:
		public object_interface_t
	{
	public:

		enum states_t {

			starting,
			started,
			finishing,
			finished

		};

		thread_t();

		~thread_t();

		virtual result_t start();

		virtual result_t stop( bool wait_for_stop = false, size_t timeout = 1000 );

		virtual result_t wait( size_t timeout = INFINITE );

		virtual result_t wait_for_start( size_t timeout = INFINITE );

		states_t get_state() const
		{
			return static_cast< states_t >( m_state );
		}

		bool is_working() const
		{
			return get_state() == started;
		}

		bool is_finished() const
		{
			return get_state() == finished;
		}

		virtual result_t set_priority( int priority );

		virtual void set_thread_name( cstr_t name )
		{
			assert( NULL != name );
			m_name = name;
		}

		cstr_t get_thread_name() const
		{
			return m_name.c_str();
		}

		virtual bool is_foreign_thread() const
		{
			return false;
		}

		void set_execution_result( result_t result )
		{
			m_execution_result = result;
		}

		result_t get_execution_result() const
		{
			return m_execution_result;
		}

	public:

		virtual result_t work() = 0;

	protected:

		void set_state( states_t new_state )
		{
			m_state = new_state;
		}

		friend class detail::thread_runner_t;

	private:

		volatile long m_state;
		void * m_thread;
		std::string m_name;
		result_t m_execution_result;

	};

	thread_t * get_main_thread();
	thread_t * get_current_thread();

} // namespace nival

#endif // __THREAD_H_INCLUDED__397419__


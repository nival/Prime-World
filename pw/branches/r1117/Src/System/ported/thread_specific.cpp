#include "string.h"

#include "thread_specific.h"

#if defined( NV_LINUX_PLATFORM )

	#include <vector>

	// FIXME
	//#include <boost/thread.hpp>

	namespace nv_detail {

		const size_t MAX_TLS_INDEXES_COUNT = 4096;

		class tls_values_storage_t
		{
		public:

			tls_values_storage_t()
			{
				memset( m_pointers, 0, MAX_TLS_INDEXES_COUNT * sizeof( LPVOID ) );
			}

			LPVOID get( DWORD index )
			{
				return index < MAX_TLS_INDEXES_COUNT ? m_pointers[ index ] : NULL;
			}

			BOOL set( DWORD index, LPVOID value )
			{
				if ( index < MAX_TLS_INDEXES_COUNT ) {
					m_pointers[ index ] = value;
					return TRUE;
				}

				return FALSE;
			}

		private:

			LPVOID m_pointers[ MAX_TLS_INDEXES_COUNT ];

		};

		struct scoped_lock
		{
			scoped_lock( pthread_mutex_t &_lock ): lock( _lock ) {
				pthread_mutex_lock( &lock );
			}
			~scoped_lock() {
				pthread_mutex_unlock( &lock );
			}
			pthread_mutex_t &lock;
		};

		class tls_values_t
		{
		public:

			tls_values_t():
				m_free_indexes( MAX_TLS_INDEXES_COUNT ),
				m_indexes_map( MAX_TLS_INDEXES_COUNT )
			{
				for ( size_t counter = MAX_TLS_INDEXES_COUNT; counter--; ) {

					m_free_indexes[ counter ] = counter;
					m_indexes_map[ counter ] = false;

				}

				pthread_mutex_init( &m_protector, NULL );
			}

			DWORD alloc()
			{
				scoped_lock lock( m_protector );

				if ( m_free_indexes.empty() ) {
					return TLS_OUT_OF_INDEXES;
			    }

				DWORD index = m_free_indexes.back();
				m_free_indexes.pop_back();

				m_indexes_map[ index ] = true;

				return index;
			}

			BOOL free( DWORD index )
			{
				scoped_lock lock( m_protector );

				if ( index > m_indexes_map.size() || false == m_indexes_map[ index ] ) {
					return FALSE;
				}

				m_indexes_map[ index ] = false;
				m_free_indexes.push_back( index );

				return TRUE;
			}

			LPVOID get( DWORD index )
			{
				//tls_values_storage_t * storage = m_tls_values_storage.get();

				return ( index < MAX_TLS_INDEXES_COUNT && m_indexes_map[ index ] ) ? m_tls_values_storage.get( index ) : NULL;
			}

			BOOL set( DWORD index, LPVOID value )
			{
				/*tls_values_storage_t * storage = m_tls_values_storage.get();
				if ( NULL == storage ) {
					storage = new tls_values_storage_t;
					m_tls_values_storage.reset( storage );
				}*/

				return m_tls_values_storage.set( index, value ); //storage->set( index, value );
			}

		private:

			//boost::thread_specific_ptr< tls_values_storage_t > m_tls_values_storage;

			tls_values_storage_t			m_tls_values_storage;
			typedef std::vector< size_t >	indexes_t;
			indexes_t						m_free_indexes;
			std::vector< bool >				m_indexes_map;
			pthread_mutex_t					m_protector;			//boost::mutex m_protector;
		};

		tls_values_t g_tls_values; // TODO: Need to wrap the var to thread-safe singleton

	} // namespace nv_detail

	DWORD TlsAlloc()
	{
		return nv_detail::g_tls_values.alloc();
	}

	BOOL TlsFree(DWORD index)
	{
		return nv_detail::g_tls_values.free( index );
	}

	BOOL TlsSetValue(DWORD index, LPVOID value)
	{
		return nv_detail::g_tls_values.set( index, value );
	}

	LPVOID TlsGetValue(DWORD index)
	{
		return nv_detail::g_tls_values.get( index );
	}

#endif // defined( NV_LINUX_PLATFORM )


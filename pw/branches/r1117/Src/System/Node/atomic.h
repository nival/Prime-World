#ifndef __ATOMIC_INCLUDED__273387__
#define __ATOMIC_INCLUDED__273387__

#include "Types.h"
#include <assert.h>

#if defined( NV_WIN_PLATFORM )
	#include <intrin.h>
#endif

namespace nstd {

	typedef enum memory_order {

		memory_order_relaxed,
		memory_order_consume,
		memory_order_acquire,
		memory_order_release,
		memory_order_acq_rel,
		memory_order_seq_cst

	} memory_order;

	namespace detail {

		inline memory_order calculate_memory_order( memory_order __m )
		{
			return memory_order_acq_rel == __m ? memory_order_acquire : ( memory_order_release == __m ? memory_order_relaxed : __m );
		}

	} // namespace detail

	template< typename T > struct atomic
	{
	private:

		T volatile m_value;

	public:

		atomic(): m_value( T() )
		{}

		explicit atomic( T __v ): m_value( __v )
		{}

		operator T() const volatile
		{
			return load();
		}

		T operator=( T __v ) volatile
		{
			store( __v );
			return __v;
		}

		T operator++( int ) volatile
		{
			return fetch_add( 1 );
		}

		T operator--( int ) volatile
		{
			return fetch_sub( 1 );
		}

		T operator++() volatile
		{
#if defined( NV_WIN_PLATFORM )
			return _InterlockedIncrement( reinterpret_cast< LONG volatile * >( &m_value ) );
#elif defined( NV_LINUX_PLATFORM )
			return __sync_add_and_fetch( &m_value, 1 );
#endif
		}

		T operator--() volatile
		{
#if defined( NV_WIN_PLATFORM )
			return _InterlockedDecrement( reinterpret_cast< LONG volatile * >( &m_value ) );
#elif defined( NV_LINUX_PLATFORM )
			return __sync_sub_and_fetch( &m_value, 1 );
#endif
		}

		T operator+=( T _v ) volatile
		{
#if defined( NV_WIN_PLATFORM )
			return _InterlockedAdd( reinterpret_cast< LONG volatile * >( &m_value ), _v );
#elif defined( NV_LINUX_PLATFORM )
			return __sync_add_and_fetch( &m_value, _v );
#endif
		}

		T operator-=( T _v ) volatile
		{
#if defined( NV_WIN_PLATFORM )
			return _InterlockedAdd( reinterpret_cast< LONG volatile * >( &m_value ), -_v );
#elif defined( NV_LINUX_PLATFORM )
			return __sync_sub_and_fetch( &m_value, _v );
#endif
		}

		bool is_lock_free() const volatile
		{ return true; }

		void store( T _v, memory_order __m = memory_order_seq_cst ) volatile
		{
			assert( memory_order_acquire != __m );
			assert( memory_order_acq_rel != __m );
			assert( memory_order_consume != __m );

			if ( memory_order_relaxed == __m )
				m_value = _v;
			else {

#if defined( NV_WIN_PLATFORM )

				if ( memory_order_seq_cst == __m )
					_InterlockedExchange( reinterpret_cast< LONG volatile * >( &m_value ), _v );
				else {

					_ReadWriteBarrier();
					m_value = _v;

				}

#elif defined( NV_LINUX_PLATFORM )

				// write_mem_barrier();
				m_value = _v;
				if ( memory_order_seq_cst == __m )
					__sync_synchronize();

#endif

			}
		}

		T load( memory_order __m = memory_order_seq_cst ) const volatile
		{
			assert( memory_order_release != __m );
			assert( memory_order_acq_rel != __m );

#if defined( NV_WIN_PLATFORM )

			T value = m_value;
			_ReadWriteBarrier();

#elif defined( NV_LINUX_PLATFORM )

			__sync_synchronize();
			T value = m_value;
			__sync_synchronize();

#endif

			return value;
		}

		T exchange( T _v, memory_order __m = memory_order_seq_cst) volatile
		{
#if defined( NV_WIN_PLATFORM )

			return _InterlockedExchange( reinterpret_cast< LONG volatile * >( &m_value ), _v );

#elif defined( NV_LINUX_PLATFORM )

			// XXX built-in assumes memory_order_acquire.
			return __sync_lock_test_and_set( &m_value, _v );

#endif
		}

		bool compare_exchange_weak( T &__oldvalue, T __newvalue, memory_order __m1, memory_order __m2 ) volatile
		{
			return compare_exchange_strong( __oldvalue, __newvalue, __m1, __m2 );
		}

		bool compare_exchange_weak( T &__oldvalue, T __newvalue, memory_order __m = memory_order_seq_cst ) volatile
		{
			return compare_exchange_weak( __oldvalue, __newvalue, __m, detail::calculate_memory_order( __m ) );
		}

		bool compare_exchange_strong( T &__oldvalue, T __newvalue, memory_order __m1, memory_order __m2 ) volatile
		{
			assert( memory_order_release != __m2 );
			assert( memory_order_acq_rel != __m2 );
			assert( __m2 <= __m1 );

#if defined( NV_WIN_PLATFORM )

			T prv = _InterlockedCompareExchange( reinterpret_cast< LONG volatile * >( &m_value ), __newvalue, __oldvalue );
			if ( prv == __oldvalue )
				return true;

			__oldvalue = prv;
			return false;

#elif defined( NV_LINUX_PLATFORM )

			T v1o = __oldvalue;
			T v1n = __sync_val_compare_and_swap( &m_value, v1o, __newvalue );

			// Assume extra stores (of same value) allowed in true case.
			__oldvalue = v1n;
			return v1o == v1n;

#endif
		}

		bool compare_exchange_strong( T &__oldvalue, T __newvalue, memory_order __m = memory_order_seq_cst ) volatile
		{
			return compare_exchange_strong( __oldvalue, __newvalue, __m, detail::calculate_memory_order( __m ) );
		}

		T fetch_add( T _v, memory_order __m = memory_order_seq_cst ) volatile
		{
#if defined( NV_WIN_PLATFORM )
			return _InterlockedAdd( reinterpret_cast< LONG volatile * >( &m_value ), _v ) - _v;
#elif defined( NV_LINUX_PLATFORM )
			return __sync_fetch_and_add( &m_value, _v );
#endif
		}

		T fetch_sub( T _v, memory_order __m = memory_order_seq_cst ) volatile
		{
#if defined( NV_WIN_PLATFORM )
			return _InterlockedAdd( reinterpret_cast< LONG volatile * >( &m_value ), -_v ) + _v;
#elif defined( NV_LINUX_PLATFORM )
			return __sync_fetch_and_sub( &m_value, _v );
#endif
		}

	};

	template< typename T > struct atomic< T * >
	{
	private:

		typedef T * ptr_t;
		ptr_t volatile m_ptr;

	public:

		atomic(): m_ptr( NULL )
		{}

		atomic( ptr_t __p ): m_ptr( __p )
		{}

		operator ptr_t() const volatile
		{
			return load();
		}

		ptr_t operator=( ptr_t __p ) volatile
		{
			store( __p );
			return __p;
		}

		bool is_lock_free() const volatile
		{ return true; }

		void store( ptr_t __p, memory_order __m = memory_order_seq_cst ) volatile
		{
			assert( memory_order_acquire != __m );
			assert( memory_order_acq_rel != __m );
			assert( memory_order_consume != __m );

			if ( memory_order_relaxed == __m )
				m_ptr = __p;
			else {

#if defined( NV_WIN_PLATFORM )

				if ( memory_order_seq_cst == __m )
					InterlockedExchangePointer( &m_ptr, __p );
				else {

					_ReadWriteBarrier();
					m_ptr = __p;

				}

#elif defined( NV_LINUX_PLATFORM )

				// write_mem_barrier();
				m_ptr = __p;
				if ( memory_order_seq_cst == __m )
					__sync_synchronize();

#endif

			}
		}

		ptr_t load( memory_order __m = memory_order_seq_cst ) const volatile
		{
			assert( memory_order_release != __m );
			assert( memory_order_acq_rel != __m );

#if defined( NV_WIN_PLATFORM )

			ptr_t p = m_ptr;
			_ReadWriteBarrier();

#elif defined( NV_LINUX_PLATFORM )

			__sync_synchronize();
			ptr_t p = m_ptr;
			__sync_synchronize();

#endif
			return p;
		}

		ptr_t exchange( ptr_t __p, memory_order __m = memory_order_seq_cst ) volatile
		{
#if defined( NV_WIN_PLATFORM )

			return _InterlockedExchangePointer( &m_ptr, __p );

#elif defined( NV_LINUX_PLATFORM )

			// XXX built-in assumes memory_order_acquire.
			return __sync_lock_test_and_set( &m_ptr, __p );

#endif
		}

		bool compare_exchange_strong( ptr_t &__oldptr, ptr_t __newptr, memory_order __m1, memory_order __m2 ) volatile
		{
			assert( memory_order_release != __m2 );
			assert( memory_order_acq_rel != __m2 );
			assert( __m2 <= __m1 );

#if defined( NV_WIN_PLATFORM )

			ptr_t prev = reinterpret_cast< T * >( InterlockedCompareExchangePointer( reinterpret_cast< PVOID volatile * >( &m_ptr ), __newptr, __oldptr ) );
			if ( prev == __oldptr )
				return true;

			__oldptr = prev;
			return false;

#elif defined( NV_LINUX_PLATFORM )

			ptr_t p1o = __oldptr;
			ptr_t p1n = __sync_val_compare_and_swap( &m_ptr, p1o, __newptr );

			// Assume extra stores (of same value) allowed in true case.
			__oldptr = p1n;
			return p1o == p1n;

#endif
		}

		bool compare_exchange_strong( ptr_t &__oldptr, ptr_t __newptr, memory_order __m = memory_order_seq_cst ) volatile
		{
			return compare_exchange_strong( __oldptr, __newptr, __m, detail::calculate_memory_order( __m ) );
		}

	};

} // namespace nstd

#endif // __ATOMIC_INCLUDED__273387__

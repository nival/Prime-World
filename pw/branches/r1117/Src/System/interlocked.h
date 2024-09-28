#ifndef __INTERLOCKED_H_INCLUDED__215803__
#define __INTERLOCKED_H_INCLUDED__215803__

#include "types.h"


namespace nival
{


#if defined(NV_WIN_PLATFORM)


  template< typename T > inline T interlocked_increment(T volatile &value)
  {
    return ::InterlockedIncrement( (volatile LONG*)&value );
  }

  template< typename T > inline T interlocked_decrement(T volatile &value)
  {
    return ::InterlockedDecrement( (volatile LONG*)&value );
  }

  template< typename T > inline bool CAS(T volatile &destination, T const comparand, T const exchange)
  {
    return ( ::InterlockedCompareExchange( &destination, exchange, comparand ) == comparand );
  }

  template< typename T > inline T CAS_ex(T volatile &destination, T const comparand, T const exchange)
  {
    return ::InterlockedCompareExchange( &destination, exchange, comparand  );
  }

  template< typename T > inline T interlocked_exchange(T volatile &value, T new_value)
  {
    return ::InterlockedExchange( &value, new_value );
  }

  template< typename T, typename T2 > inline T* interlocked_exchange_pointer(T * volatile &value, T2 * new_value)
  {
    return static_cast< T* >( InterlockedExchangePointer( &value, new_value ) );
  }
  
  template< typename T > inline T* interlocked_compare_exchange_pointer( T * volatile &destination, T* exchange, T* comparand )
  {
    return static_cast< T* >( ::InterlockedCompareExchangePointer( (volatile PVOID *)&destination, exchange, comparand ) );
  }

  template< typename T > inline T interlocked_exchange_add(T volatile &addend, T value)
  {
    return ::InterlockedExchangeAdd( &addend, value );
  }


#elif defined(NV_LINUX_PLATFORM)


  template< typename T > inline T interlocked_increment(T volatile &value)
  {
    return __sync_add_and_fetch(&value, 1);
  }

  template< typename T > inline T interlocked_decrement(T volatile &value)
  {
    return __sync_sub_and_fetch(&value, 1);
  }

  template< typename T, typename T2, typename T3 > inline bool CAS(T volatile &destination, T2 const comparand, T3 const exchange)
  {
    return __sync_bool_compare_and_swap(&destination, comparand, exchange);
  }

  template< typename T, typename T2, typename T3 > inline T CAS_ex(T volatile &destination, T2 const comparand, T3 const exchange)
  {
    return __sync_val_compare_and_swap(&destination, comparand, exchange);
  }

  template< typename T, typename T2 > inline T interlocked_exchange(T volatile &value, T2 new_value)
  {
    T old_value;
    do
    {
      old_value = value;

    } while (!CAS(value, old_value, new_value));

    return old_value;
  }

  template< typename T, typename T2 > inline T* interlocked_exchange_pointer(T * volatile &value, T2 * new_value)
  {
    return interlocked_exchange( value, new_value );
  }
  
  template< typename T > inline T* interlocked_compare_exchange_pointer( T * volatile &destination, T* exchange, T* comparand )
	{
		return CAS_ex( destination, comparand, exchange );
	}

  template< typename T, typename T2 > inline T interlocked_exchange_add(T volatile &addend, T2 value)
  {
    return __sync_fetch_and_add(&addend, value);
  }


#endif  // #elif defined(NV_LINUX_PLATFORM)


} // namespace nival

#endif // __INTERLOCKED_H_INCLUDED__215803__


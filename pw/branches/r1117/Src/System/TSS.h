/**
  Thread-Specific Storage

  @TODO:
    * make initial value for key
    * handle errors in TSS_get
 */
#ifndef SYSTEM_TLS_H__
#define SYSTEM_TLS_H__

#include "System/config.h"
#if defined( NV_WIN_PLATFORM )
#include <windows.h>
#elif defined( NV_LINUX_PLATFORM )
#include <pthread.h>
#endif

namespace nival
{

/**
  TSS key type
 */
#if defined( NV_WIN_PLATFORM )
typedef DWORD                TSS_key_type;
#elif defined( NV_LINUX_PLATFORM )
typedef pthread_key_t        TSS_key_type;
#endif


/**
  Create TSS value
  @param key - [out] key to access TSS value. Valid only if function returns true
  @return true - success, false otherwise
 */
bool TSS_create( TSS_key_type & key )
{
#if defined( NV_WIN_PLATFORM )
  key = ::TlsAlloc();
  return ( key != TLS_OUT_OF_INDEXES );
#elif defined( NV_LINUX_PLATFORM )
  return ( ::pthread_key_create( &key, 0 ) == 0 );
#endif
}


/**
  Free TSS value
  @param key - [in] TSS key
  @return true - success, false otherwise
 */
bool TSS_free( TSS_key_type key )
{
#if defined( NV_WIN_PLATFORM )
		return ( ::TlsFree( key ) != FALSE );
#elif defined( NV_LINUX_PLATFORM )
    return ( ::pthread_key_delete( key ) == 0 );
#endif
}


/**
  Get TSS value
  @param key - [in] TSS key
  @return TSS value
 */
void * TSS_get( TSS_key_type key )
{
#if defined( NV_WIN_PLATFORM )
		return ::TlsGetValue( key );
#elif defined( NV_LINUX_PLATFORM )
    return ::pthread_getspecific( key );
#endif
}

/**
  Set TSS value
  @param key - [in] TSS key
  @param value - [in] value to set
  @return true - success, false otherwise
 */
bool TSS_set( TSS_key_type key, void * value )
{
#if defined( NV_WIN_PLATFORM )
		return ( ::TlsSetValue( key, value ) != FALSE );
#elif defined( NV_LINUX_PLATFORM )
    return ( ::pthread_setspecific( key, value ) == 0 );
#endif
}

} // namespace nival

#endif // SYSTEM_TLS_H__

/**
  @copyright
  Socket cross-platform abstraction
 */

#ifndef NETWORK_SOCKET_H_
#define NETWORK_SOCKET_H_

#include "Address.h"
#if defined( NV_WIN_PLATFORM )
#include <winsock2.h>
#elif defined( NV_LINUX_PLATFORM )
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#endif

namespace Network
{


#if defined( NV_WIN_PLATFORM )

typedef            SOCKET                        socket_type;
const socket_type  BAD_SOCKET =                  INVALID_SOCKET;


inline bool InitSocketEngine()
{
  // An application can call WSAStartup more than once if it needs to obtain the WSADATA structure information more than once. 
  // On each such call, the application can specify any version number supported by the Winsock DLL.
  WORD versionRequested = MAKEWORD( 2, 2 );
  WSADATA wsaData = { 0 };
  return ( ::WSAStartup( versionRequested, &wsaData ) == 0 );
}


inline void CleanupSocketEngine()
{
  // An application must call the WSACleanup function for every successful time the WSAStartup function is called.
  NI_VERIFY_NO_RET( ::WSACleanup() == 0, "WSACleanup() up failed" );
}


inline void CloseSocket( socket_type s )
{
  NI_VERIFY_NO_RET( ::closesocket( s ) == 0, "closesocket() up failed" );
}

#elif defined( NV_LINUX_PLATFORM )

typedef            int                           socket_type;
const socket_type  BAD_SOCKET =                  -1;

inline bool InitSocketEngine()
{
  return true;
}


inline void CleanupSocketEngine()
{
  ;;
}


inline void CloseSocket( socket_type s )
{
  NI_VERIFY_NO_RET( ::close( s ) == 0, "close() up failed" );
}

#endif


template< typename ValueType >
bool GetSocketOption( socket_type s, int level, int optname, ValueType & value )
{
#if defined( NV_WIN_PLATFORM )
  int len = sizeof( ValueType );
  return
    ( ::getsockopt( s, level, optname,
                    static_cast< char* >( static_cast< void* >( &value ) ),
                    &len ) == 0 );
#elif defined( NV_LINUX_PLATFORM )
  socklen_t len = sizeof( ValueType );
  return
    ( ::getsockopt( s, level, optname,
                    &value,
                    &len ) == 0 );
#endif
}


template< typename ValueType >
bool SetSocketOption( socket_type s, int level, int optname, const ValueType & value )
{
  return
    ( ::setsockopt( s, level, optname,
#if defined( NV_WIN_PLATFORM )
                    static_cast< const char* >( static_cast< const void* >( &value ) ),
#elif defined( NV_LINUX_PLATFORM )
                    &value,
#endif
                    sizeof( ValueType ) ) == 0 );
}


inline bool SetTCPNoDelay( socket_type s, int level, bool value )
{
  const int noDelay = ( value ? 1 : 0 );
  return SetSocketOption( s, level, TCP_NODELAY, &noDelay );
}


inline bool SetNonBlockingSocket( socket_type s, bool value )
{
#if defined( NV_WIN_PLATFORM )
  unsigned long nonBlocking = ( value ? 1 : 0 );
  return ( ::ioctlsocket( s, FIONBIO, &nonBlocking ) != SOCKET_ERROR );
#elif defined( NV_LINUX_PLATFORM )
  const int flags = ::fcntl( s, F_GETFL, 0 );
  if ( value )
  {
    return ::fcntl( s, F_SETFL, flags | O_NONBLOCK ) == 0;
  }
  else
  {
    return ::fcntl( s, F_SETFL, flags & ( ~O_NONBLOCK ) ) == 0;
  }
#endif
}


inline bool BindSocket( socket_type s, const Address & addr )
{
#if defined( NV_WIN_PLATFORM )
  return
    ( ::bind( s, reinterpret_cast< SOCKADDR* >( ( sockaddr_in_type* )( &addr ) ), sizeof( sockaddr_in_type ) ) == 0 );
#elif defined( NV_LINUX_PLATFORM )
  return
    ( ::bind( s, reinterpret_cast< sockaddr* >( ( sockaddr_in_type* )( &addr ) ), sizeof( sockaddr_in_type ) ) == 0 );
#endif
}


inline socket_type AcceptSocket( socket_type s, Address & addr )
{
#if defined( NV_WIN_PLATFORM )
  int len = sizeof( SOCKADDR_IN );
  return ::accept( s, addr, &len );
#elif defined( NV_LINUX_PLATFORM )
  socklen_t len = sizeof( sockaddr_in_type );
  return
    ::accept( s, reinterpret_cast< sockaddr* >( ( sockaddr_in_type* )( &addr ) ), &len  ) == 0;
#endif
}


inline bool ConnectSocket( socket_type s, const Address & addr )
{
#if defined( NV_WIN_PLATFORM )
  return
    ::connect( s, reinterpret_cast< SOCKADDR* >( ( sockaddr_in_type* )( &addr ) ), sizeof( sockaddr_in_type ) ) == 0;
#elif defined( NV_LINUX_PLATFORM )
  return
    ::connect( s, reinterpret_cast< sockaddr* >( ( sockaddr_in_type* )( &addr ) ), sizeof( sockaddr_in_type ) ) == 0;
#endif
}


} // namespace Network

#endif // NETWORK_SOCKET_H_

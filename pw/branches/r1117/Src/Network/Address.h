#ifndef ADDRESS_H_08355E67_4B40_4BF5_AA9
#define ADDRESS_H_08355E67_4B40_4BF5_AA9

#include "System/systemStdAfx.h"
#if defined( NV_WIN_PLATFORM )
#include <winsock2.h>
#elif defined( NV_LINUX_PLATFORM )
#include <sys/types.h>
#include <sys/socket.h>
#endif

namespace Network
{

#if defined( NV_WIN_PLATFORM )
  typedef SOCKADDR_IN sockaddr_in_type;
  typedef SOCKADDR sockaddr_type;
#elif defined( NV_LINUX_PLATFORM )
  typedef sockaddr_in sockaddr_in_type;
  typedef sockaddr sockaddr_type;
#endif

	/**
	 * Represents an internet ip address. 
	 * All data is in network byte order.
	 */
	class Address
	{
	public:
		typedef unsigned long IP;
		typedef unsigned short PORT;

	private:
		sockaddr_in_type address;
        mutable string ipString;

	public:
        Address() {
          ::memset( &address, 0, sizeof( address ) );
          address.sin_family = AF_INET; 
        }

		Address( const sockaddr_in_type& in ) : address( in ) {}
		Address( IP ip, PORT port );
		Address( const char* ip, PORT port );
        Address( const char* url );
		
		bool Set( const char* ip, PORT port );
		bool Set( IP ip, PORT port );
		bool SetIp( const char* str );
		bool SetIp( IP ip );
		void SetPort( PORT port ) { address.sin_port = htons( port ); }

		const char* GetIp() const;
		PORT GetPort() const;

		bool operator == ( const Address& ) const;
		bool operator != ( const Address& ) const;

		operator sockaddr_type* () { return reinterpret_cast<sockaddr_type*>( &address ); }
		operator const sockaddr_type* () const { return reinterpret_cast<const sockaddr_type*>( &address ); }

        sockaddr_in_type & SockAddrIn() { return address; }
		const sockaddr_in_type & SockAddrIn() const { return address; }
	};

  typedef nstl::string NetAddress;

  NetAddress GetHostIPByName( NetAddress const & name, bool noloopback = false );
  void GetHost(NetAddress const & netaddr, NetAddress& host);
}
#endif //#define ADDRESS_H_08355E67_4B40_4BF5_AA9

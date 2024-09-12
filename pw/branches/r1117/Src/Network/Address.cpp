#include "stdafx.h"
#include "Address.h"

#if defined( NV_LINUX_PLATFORM )
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

namespace Network
{
	Address::Address( IP ip, PORT port ) 
	{
		::memset( &address, 0, sizeof( address ) );
		address.sin_family = AF_INET;
		Set( ip, port );
	}

	Address::Address( const char* str, PORT port )
	{
		::memset( &address, 0, sizeof( address ) );
		address.sin_family = AF_INET;
		Set( str, port );
	}

  Address::Address( const char* url )
  {
    ::memset( &address, 0, sizeof( address ) );
    address.sin_family = AF_INET;
    // extract port number from address
    nstl::string addr = url;
    int index = addr.find( ':' );
    if ( index != -1 )
    {
      Address::PORT port = atoi( addr.substr( index + 1 ).c_str() );
      addr.resize( index );
      Set( addr.c_str(), port );
    }
    else
    {
      Address::PORT port = atoi( url );
      NI_ASSERT( port != 0, string( string( "Invalid url: " ) + url ).c_str() );
      Set( static_cast< IP >( INADDR_ANY ), port );
    }
  }


	bool Address::Set( const char* str, PORT port )
	{
		SetPort( port );
		return SetIp( str );
	}

	bool Address::Set( IP ip, PORT port )
	{
		SetPort( port );
		return SetIp( ip );
	}

	bool Address::SetIp( const char* str )
	{
		IP ip = inet_addr( str );
		if( ip == INADDR_NONE )
		{
			// may be it is string compatible domain
			hostent* host = gethostbyname( str );
			if( host )
      {
        ip = *reinterpret_cast<IP*>( host->h_addr_list[0] );
      }
		}
		return SetIp( ip );
	}

	bool Address::SetIp( IP ip )
	{
		if( ip != INADDR_NONE )
    {
			address.sin_addr.s_addr = ip;
      ipString = inet_ntoa( address.sin_addr );
    }
		return ip != INADDR_NONE;
	}

	//void Address::SetPort( PORT port )
	//{
	//	address.sin_port = htons( port );
	//}

	const char* Address::GetIp() const
	{
    if(ipString.empty())
    {
      //we need to fill it
      ipString = string(inet_ntoa( address.sin_addr ));
    }
		return ipString.c_str();
	}

	Address::PORT Address::GetPort() const
	{
		return ntohs(address.sin_port);
	}

	bool Address::operator == ( const Address& other ) const
	{
		return other.address.sin_port == address.sin_port
#if defined( NV_WIN_PLATFORM )
			&& other.address.sin_addr.S_un.S_addr == address.sin_addr.S_un.S_addr
#elif defined( NV_LINUX_PLATFORM )
            && other.address.sin_addr.s_addr == address.sin_addr.s_addr
#endif
			&& other.address.sin_family == address.sin_family;
	}

	bool Address::operator != ( const Address& other ) const
	{
		return !(*this == other); 
	}

  string GetHostIPByName( const string& name, bool noloopback )
  {
    DWORD ip = inet_addr( name.c_str() );
    if( ip != INADDR_NONE )
      return name;

    hostent* host = gethostbyname( name.c_str() );
    if( !host || host->h_addrtype != AF_INET )
      return "";

    ip = *reinterpret_cast<DWORD*>( host->h_addr_list[0] );
    if( noloopback && ip == ::htonl( INADDR_LOOPBACK ) )
    {
      host = gethostbyname( host->h_name );
      ip = *reinterpret_cast<DWORD*>( host->h_addr_list[0] );
    }

    struct in_addr addr;
    addr.s_addr = ip;
    char* n = ::inet_ntoa( addr );
    return string(n);
  }

  void GetHost(NetAddress const & netaddr, NetAddress& host)
  {
    size_t pos = netaddr.find(':');
    if (pos != string::npos)
    {
      host.assign(netaddr.c_str(), pos);
    }
    else
    {
      host = netaddr;
    }
  }

}

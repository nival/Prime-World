#include "stdafx.h"
#include "UdpAddr.h"


namespace ni_udp
{

NetAddr::NetAddr()
{
  Clear();
}



NetAddr::NetAddr( const char * _addr, unsigned _port )
{
  if ( !Set( _addr, _port ) )
    NI_ALWAYS_ASSERT( "Wrong network address" );
}



NetAddr::NetAddr( const char * _combined )
{
  if ( !Set( _combined ) )
    NI_ALWAYS_ASSERT( string( string( "Invalid net address '" ) + _combined + '\'' ).c_str() );
}



bool NetAddr::Set( const char * _addr, unsigned _port )
{
  Clear();

  if ( !_addr )
  {
    sin_family = AF_INET; 
    sin_addr.s_addr = INADDR_ANY;
    sin_port = ::htons( _port );
    return true;
  }

  addrinfo hints;
  memset( &hints, 0, sizeof( hints ) );
  hints.ai_flags = 0;
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = IPPROTO_UDP;

  addrinfo * info = 0;
  int result = ::getaddrinfo( _addr, NI_STRFMT( "%d", _port ), &hints, &info );
  NI_VERIFY( !result, "", return false );

  for( addrinfo * i = info; i; i = i->ai_next )
  {
    if ( i->ai_addrlen == sizeof( sockaddr_in ) )
    {
      memcpy( static_cast<sockaddr_in*>( this ), (const sockaddr_in*)i->ai_addr, sizeof( sockaddr_in ) );
      freeaddrinfo( info );
      return true;
    }
  }

  freeaddrinfo( info );
  return false;
}



inline bool SafeParseUInt( unsigned & _u, const char * _str )
{
  _u = 0;
  int pos = 0;
  if ( sscanf( _str, "%u%n", &_u, &pos ) == 1 )
    if ( pos == (int)strlen( _str ) )
      return true;

  return false;
}



bool NetAddr::Set( const char * _combined )
{
  Clear();

  nstl::string addr = _combined;
  int index = addr.find( ':' );
  if ( index != -1 )
  {
    unsigned port = 0;
    if ( SafeParseUInt( port, addr.substr( index + 1 ).c_str() ) )
      if ( port )
      {
        addr.resize( index );
        Set( addr.c_str(), port );
        return true;
      }
  }
  else
  {
    unsigned port = 0;
    if ( SafeParseUInt( port, _combined ) )
      if ( port )
      {
        Set( 0, port );
        return true;
      }
  }
  
  return false;
}



void NetAddr::SetPort( unsigned _port )
{
  sin_port = ::htons( _port );
}




bool NetAddr::operator < ( const NetAddr & that ) const
{
  if ( sin_family < that.sin_family )
    return true;
  else if ( sin_family > that.sin_family )
    return false;

  if ( sin_port < that.sin_port )
    return true;
  else if ( sin_port > that.sin_port )
    return false;

  return Address() < that.Address();
}



bool NetAddr::operator == ( const NetAddr & that ) const
{
  if ( sin_family != that.sin_family )
    return false;
  if ( sin_port != that.sin_port )
    return false;
  return Address() == that.Address();
}



unsigned NetAddr::Port() const
{
  return ::ntohs( sin_port );
}



void NetAddr::Clear()
{
  memset( static_cast<sockaddr_in*>( this ), 0, sizeof( sockaddr_in ) );
}



void NetAddr::Str( char * _buf, size_t _bufSz ) const
{
  if ( ( sin_family == AF_INET ) && ( sin_addr.s_addr == INADDR_ANY ) )
  {
    int len = _snprintf( _buf, _bufSz - 1, "%u", (unsigned)Port() );
    _buf[len] = 0;
  }
  else
  {
    int len = _snprintf( _buf, _bufSz - 1, "%d.%d.%d.%d:%u", 
      (unsigned)sin_addr.s_net, (unsigned)sin_addr.s_host, 
      (unsigned)sin_addr.s_lh, (unsigned)sin_addr.s_impno, 
      (unsigned)Port() );
    _buf[len] = 0;
  }
}



void NetAddr::StrIp( char * _buf, size_t _bufSz ) const
{
  int len = _snprintf( _buf, _bufSz - 1, "%d.%d.%d.%d", 
    (unsigned)sin_addr.s_net, (unsigned)sin_addr.s_host, 
    (unsigned)sin_addr.s_lh, (unsigned)sin_addr.s_impno );
  _buf[len] = 0;
}

} //namespace ni_udp

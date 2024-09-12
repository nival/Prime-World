#include "stdafx.h"
#include "RdpTransportUtils.h"
#include "Network/RUDP/UdpSocket.h"
#include "Network/RUDP/IRdp.h"


namespace rdp_transport
{

static bool useRdpTransport = false;
REGISTER_VAR( "rdp_enable", useRdpTransport, STORAGE_GLOBAL );



bool RdpTransportEnabled()
{
  return useRdpTransport;
}



string FormatAddr( const ni_udp::NetAddr & _addr, unsigned _mux )
{
  char buf[32];
  _addr.Str( buf, 32 );

  return NI_STRFMT( "%s@%u", buf, _mux );
}



bool ParseAddress( ni_udp::NetAddr & _addr, unsigned & _mux, const char * _str )
{
  if ( const char * muxbegin = strrchr( _str, '@' ) )
  {
    ++muxbegin;
    int pos = 0;
    if ( sscanf( muxbegin, "%u%n", &_mux, &pos ) != 1 )
      return false;

    if ( (int)strlen( muxbegin ) != pos )
      return false;

    string tmp( _str, muxbegin - 1 );
    _addr.Set( tmp.c_str() );
    return _addr.Port() != 0;
  }

  _mux = 0;
  _addr.Set( _str );
  return _addr.Port() != 0;
}











PacketWriter::PacketWriter( ni_udp::IRdpConnection * _conn ) :
conn( _conn )
{
}



bool PacketWriter::Handle( const void * _data, size_t _size )
{
  conn->SendDatagram( _data, _size );
  return true;
}



bool PacketWriter::Valid()
{
  switch ( conn->Status() )
  {
    case ni_udp::EConnStatus::Closed:
    case ni_udp::EConnStatus::Failed:
      return false;
  }

  return true;
}

} //namesapce rdp_transport

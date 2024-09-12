#include "stdafx.h"
#include "RdpWriter.h"
#include "RdpHandshake.h"
#include "RdpStats.h"
#include "System/InlineProfiler.h"


NI_DEFINE_REFCOUNT( ni_udp::RdpWriter );

namespace ni_udp
{

RdpWriter::RdpWriter( ISocket * _socket, RdpConnStats * _stats ) :
socket( _socket ),
stats( _stats )
{
}



void RdpWriter::Send( const ConnDescriptor & _descr, proto::EPktType::Enum _type, unsigned _index )
{
  NI_PROFILE_FUNCTION;

  proto::Header hdr( _type, _descr.localMux, _descr.remoteMux, _index );
  socket->SendDatagram( _descr.remote, &hdr, sizeof( hdr ) );

  stats->Inc( &RdpStats::bytesWritten, sizeof( hdr ) );
  stats->Inc( &RdpStats::packetsWritten, 1 );
}



void RdpWriter::SendRaw( const NetAddr & _destAddr, const void * _data, size_t _size )
{
  NI_PROFILE_FUNCTION;

  socket->SendDatagram( _destAddr, _data, _size );

  stats->Inc( &RdpStats::bytesWritten, _size );
  stats->Inc( &RdpStats::packetsWritten, 1 );
}

} //namespace ni_udp

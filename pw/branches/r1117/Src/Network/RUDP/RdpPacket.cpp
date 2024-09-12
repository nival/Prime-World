#include "stdafx.h"
#include "RdpPacket.h"
#include "RdpWriter.h"
#include "System/InlineProfiler.h"


NI_DEFINE_REFCOUNT( ni_udp::RdpPacket );

namespace ni_udp
{

RdpPacket::RdpPacket( size_t _totalCapacity ) :
packetRefCount( 0 ),
inUse( false ),
payloadSize( 0 ),
tryIndex( 0 ),
lastTryTime( 0 ),
solid( false ),
absRecvTime( 0 )
{
  bytes.reserve( _totalCapacity );
}



RdpPacket::~RdpPacket()
{
  NI_ASSERT( packetRefCount == 0, NI_STRFMT( "packetRefCount=%d", (int)packetRefCount ) );
}



int RdpPacket::PktAddRef()
{
  return (int)InterlockedIncrement( &packetRefCount );
}



int RdpPacket::PktReleaseRef()
{
  return (int)InterlockedDecrement( &packetRefCount );
}



void RdpPacket::Setup( proto::EPktType::Enum _type, unsigned _srcMux, unsigned _destMux, unsigned _index, const void * _data, size_t _size )
{
  size_t sz = sizeof( proto::Header ) + _size;
  NI_VERIFY( sz <= bytes.capacity(), "", return );
  bytes.resize( sz, 0 );

  proto::Header * hdr = (proto::Header *)&bytes[0];
  hdr->Header::Header( _type, _srcMux, _destMux, _index );

  if ( _data && _size )
    memcpy( hdr + 1, _data, _size );
  payloadSize = _size;

  tryIndex = 0;
  absRecvTime = 0;
}



void RdpPacket::Cleanup()
{
  inUse = false;
  bytes.clear();
  payloadSize = 0;
  tryIndex = 0;
  lastTryTime = 0;
  solid = false;
  absRecvTime = 0;
}



const proto::Header * RdpPacket::Hdr() const
{
  NI_VERIFY( sizeof( proto::Header ) <= bytes.size(), "", return 0 );

  return ( const proto::Header *)&bytes[0];
}



const void * RdpPacket::Payload() const
{
  NI_VERIFY( bytes.size() >= sizeof( proto::Header ), "", return 0 );
  return ( ( const proto::Header *)&bytes[0] ) + 1;
}



void RdpPacket::Send( timer::Time _now, RdpWriter * _writer, const NetAddr & _sendto )
{
  lastTryTime = _now;
  ++tryIndex;

  NI_VERIFY( !bytes.empty(), "", return );
  _writer->SendRaw( _sendto, &bytes[0], bytes.size() );
}









StrongMT<RdpPacket> HeapPacketAllocator::AllocatePkt( size_t _payloadSize )
{
  NI_PROFILE_FUNCTION;

  RdpPacket * pkt = new RdpPacket( RdpPacket::PayloadToCapacity( _payloadSize ) );
  pkt->PktAddRef();
  return pkt;
}



void HeapPacketAllocator::DeallocatePkt( RdpPacket * _pkt )
{
  NI_PROFILE_FUNCTION;

  int refcountleft = _pkt->PktReleaseRef();
  NI_ASSERT( refcountleft >= 0, "" );
  //do nothing
}

} //namespace ni_udp

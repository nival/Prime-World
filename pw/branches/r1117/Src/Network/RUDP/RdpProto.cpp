#include "stdafx.h"
#include "RdpProto.h"

namespace ni_udp
{

namespace proto
{

NI_ENUM_BEGIN_STD( EPktType );
  NI_ENUM_ITEM( HandshakeInit );
  NI_ENUM_ITEM( HandshakeInitAck );
  NI_ENUM_ITEM( HandshakeAck );
  NI_ENUM_ITEM( HandshakeRefused );
  NI_ENUM_ITEM( RetryHandshake );
  NI_ENUM_ITEM( Datagram );
  NI_ENUM_ITEM( DatagramChunk );
  NI_ENUM_ITEM( DatagramAck );
  NI_ENUM_ITEM( DatagramRaw );
  NI_ENUM_ITEM( Shutdown );
  NI_ENUM_ITEM( ShutdownAck );
  NI_ENUM_ITEM( Ping );
  NI_ENUM_ITEM( Pong );
NI_ENUM_END_STD;



Int32 SeqIdxOffsetInWindow( Int32 _wndStart, Int32 _wndSize, Int32 _idx, Int32 _seqIdxClamp )
{
  const Int32 half = _seqIdxClamp / 2;

  NI_VERIFY( _wndSize <= half, "", return -1 );
  NI_VERIFY( _wndStart <= _seqIdxClamp, "", return -1 );

  return SeqIdxShortestDist( _wndStart, _idx, _seqIdxClamp );
}



Int32 SeqIdxShortestDist( Int32 _from, Int32 _to, Int32 _seqIdxClamp )
{
  const Int32 half = _seqIdxClamp / 2;

  Int32 dist = _to - _from;

  if ( dist >= 0 )
  {
    if ( dist < half )
      return dist;
    else
      return dist - _seqIdxClamp;
  }
  else
  {
    if ( dist >= -half )
      return dist;
    else
      return _seqIdxClamp + dist;
  }
}

} //namespace proto

} //namespace ni_udp

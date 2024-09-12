#include "stdafx.h"
#include "RdpInPktQueue.h"
#include "RdpWriter.h"
#include "RdpStats.h"
#include "System/InlineProfiler.h"


namespace ni_udp
{

RdpInPktQueue::RdpInPktQueue( const RdpCommonCtx & _ctx, IRdpPktQueueCallback * _cb ) :
RdpPktQueue( _ctx, _cb, _ctx.options->initInPacketsQueue ),
shutdownReceived( false ),
shutdownSeqIdx( 0 )
{
}



void RdpInPktQueue::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;
}



void RdpInPktQueue::OnDatagram( timer::Time _now, RdpPacket * _packet )
{
  NI_PROFILE_HEAVY_FUNCTION;

  const proto::EPktType::Enum pktType = (proto::EPktType::Enum)_packet->Hdr()->type;
  const unsigned seqIdx = _packet->Hdr()->index;

  NI_ASSERT( ( pktType == proto::EPktType::Datagram ) || ( pktType == proto::EPktType::DatagramChunk ) || ( pktType == proto::EPktType::Shutdown ), "" );

  if ( shutdownReceived )
    if ( proto::SeqIdxShortestDist( shutdownSeqIdx, seqIdx, proto::SeqIndexClamp ) > 0 )
    {
      if ( ( ctx.options->logEvents & RdpOptions::LogDetails ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
        WarningTrace( "Ignoring datagram after shutdown. descr=%s, seq=%d, shutdown_seq=%d", callback->ConnDescr(), seqIdx, shutdownSeqIdx );
      ctx.stats->Inc( &RdpStats::warnings );
      return;
    }

  int offsetInWindow = proto::SeqIdxOffsetInWindow( sequenceIdx, ctx.options->cc.maxWindowSize, seqIdx, proto::SeqIndexClamp );

  if ( ( offsetInWindow == 0 ) && ( pktType != proto::EPktType::DatagramChunk ) )
    OnInSequencePacket( _packet );
  else if ( ( offsetInWindow >= 0 ) && ( offsetInWindow < (int)ctx.options->cc.maxWindowSize ) )
    OnOutOfSequencePacket( _now, offsetInWindow, _packet );
  else
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogDetails ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Datagram sequence out of range. descr=%s, seq=%d, wnd_start=%d, wnd_size=%d", callback->ConnDescr(), seqIdx, sequenceIdx, ctx.options->cc.maxWindowSize );
    ctx.stats->Inc( &RdpStats::warnings );
  }

  if ( offsetInWindow < (int)ctx.options->cc.maxWindowSize )
  {
    proto::EPktType::Enum ack = ( pktType == proto::EPktType::Shutdown ) ? proto::EPktType::ShutdownAck : proto::EPktType::DatagramAck;

    if ( ctx.options->logEvents & RdpOptions::LogDetails )
      MessageTrace( "Sending ACK. descr=%s, type=%d, seq=%d, size=%d", callback->ConnDescr(), PktTypeToString( ack ), seqIdx, _packet->PayloadSize() );

    ctx.writer->Send( callback->ConnDescr(), ack, seqIdx );
  }
}



void RdpInPktQueue::OnInSequencePacket( RdpPacket * _packet )
{
  NI_PROFILE_HEAVY_FUNCTION;

  const proto::EPktType::Enum pktType = (proto::EPktType::Enum)_packet->Hdr()->type;
  const unsigned seqIdx = _packet->Hdr()->index;

  //Right sequence number; Do not store the data
  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "Got in-sequence datagram. descr=%s, type=%d, size=%d, seq=%d", callback->ConnDescr(), PktTypeToString( pktType ), _packet->PayloadSize(), seqIdx );

  if ( pktType == proto::EPktType::Shutdown )
  {
    callback->QueCbShutdownRecieved();
    shutdownReceived = true;
    shutdownSeqIdx = sequenceIdx;
  }
  else
  {
    callback->QueCbDatagram( _packet );
  }

  if ( !buffer.Empty() )
  {
    StrongMT<RdpPacket> & tail = buffer.AtTail();
    if ( tail.Valid() )
    {
      NI_ALWAYS_ASSERT( NI_STRFMT( "Duplicate in-sequence datagram. descr=%s, type=%d, seq=%d", callback->ConnDescr(), PktTypeToString( pktType ), seqIdx ) );
      ctx.stats->Inc( &RdpStats::errors );
      totalBufferSize -= tail->PayloadSize();
      ctx.allocator->DeallocatePkt( tail );
      tail = 0;
    }
    buffer.PopTail();
  }

  sequenceIdx = proto::NextSeqIndex( sequenceIdx );
  ReportWindowChange();

  DeliverQueuedDatagrams( false );
}



void RdpInPktQueue::OnOutOfSequencePacket( timer::Time _now, int _offsetInWindow, RdpPacket * _packet )
{
  NI_PROFILE_HEAVY_FUNCTION;

  const proto::EPktType::Enum pktType = (proto::EPktType::Enum)_packet->Hdr()->type;
  const unsigned seqIdx = _packet->Hdr()->index;

  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "Got out-of-sequence datagram. descr=%s, type=%d, seq=%d, offs=%d", callback->ConnDescr(), PktTypeToString( pktType ), seqIdx, _offsetInWindow );

  if ( (size_t)_offsetInWindow >= buffer.Size() )
  {
    if ( ctx.options->logEvents & RdpOptions::LogDetails )
      MessageTrace( "Enlarging input buffer. descr=%d, seq=%d, new_size=%d, size=%d", callback->ConnDescr(), seqIdx, _offsetInWindow + 1, buffer.Size() );

    while( (size_t)_offsetInWindow >= buffer.Size() )
      buffer.PushAtHead( 0 );
  }

  _packet->PktAddRef();
  StrongMT<RdpPacket> & slot = buffer.AtTail( _offsetInWindow );
  if ( slot )
    slot->PktReleaseRef();
  slot = _packet;

  totalBufferSize += _packet->PayloadSize();

  if ( PropagateSolidity( _offsetInWindow, _packet ) )
    DeliverQueuedDatagrams( true );
}



bool RdpInPktQueue::PropagateSolidity( int _newPktOffs, RdpPacket * _newPkt )
{
  NI_PROFILE_HEAVY_FUNCTION;

  NI_VERIFY( _newPktOffs >= 0 && _newPktOffs < (int)buffer.Size(), "", return false );

  proto::EPktType::Enum pktType = (proto::EPktType::Enum)_newPkt->Hdr()->type;
  if ( ( pktType == proto::EPktType::Datagram ) || ( pktType == proto::EPktType::Shutdown ) )
    _newPkt->SetSolid( true );
  else
  {
    if ( _newPktOffs + 1 < (int)buffer.Size() )
      if ( RdpPacket * pkt2head = buffer.AtTail( _newPktOffs + 1 ) )
        if ( pkt2head->Solid() )
          _newPkt->SetSolid( true );
  }

  if ( !_newPkt->Solid() )
    return false;

  RdpPacket * prevPkt = _newPkt;
  int offs = _newPktOffs - 1;
  while ( true )
  {
    if ( offs < 0 )
      return true;

    RdpPacket * pkt = buffer.AtTail( offs );
    if ( !pkt )
      return false;

    if ( pkt->Solid() )
      return false; //FALSE; We haven't reached TAIL; It is just another (earlier) UNassembled datagram

    pkt->SetSolid( true );

    prevPkt = pkt;
    --offs;
  }
}



void RdpInPktQueue::DeliverQueuedDatagrams( bool _atLeastOne )
{
  NI_PROFILE_HEAVY_FUNCTION;

  bool expected = _atLeastOne;
  while ( true )
  {
    if ( !DeliverQueuedDatagram() )
    {
      NI_ASSERT( !expected, NI_STRFMT( "The should be at least one datagram. descr=%d", callback->ConnDescr() ) );
      break;
    }
    expected = false;
  }
}



bool RdpInPktQueue::DeliverQueuedDatagram()
{
  NI_PROFILE_HEAVY_FUNCTION;

  if ( buffer.Empty() )
    return false;

  if ( PopShutdownPacket() )
    return true;

  size_t totalSize = 0;
  int chunks = 0;
  for ( ; chunks < (int)buffer.Size(); ++chunks )
  {
    RdpPacket * pkt = buffer.AtTail( chunks );
    if ( !pkt )
      return false;
    if ( !pkt->Solid() )
      return false;

    totalSize += pkt->PayloadSize();

    if ( pkt->Hdr()->type == proto::EPktType::Datagram )
      break;
    NI_ASSERT( pkt->Hdr()->type == proto::EPktType::DatagramChunk, "" );
  }
  ++chunks;

  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "Assembling datagram. descr=%s, seq=%d, size=%u, chunks=%u", callback->ConnDescr(), sequenceIdx, totalSize, chunks );

  StrongMT<RdpPacket> packet2Deliver = ( chunks == 1 ) ? PopDatagramFromTail() : AssembleDatagramFromTail( chunks, totalSize );

  if ( !packet2Deliver )
    return false; //Some kind of error

  callback->QueCbDatagram( packet2Deliver );

  ctx.allocator->DeallocatePkt( packet2Deliver );
  packet2Deliver = 0;

  return true;
}



StrongMT<RdpPacket> RdpInPktQueue::AssembleDatagramFromTail( int _chunks, size_t _totalSize )
{
  NI_PROFILE_HEAVY_FUNCTION;

  NI_ASSERT( _totalSize > 0, "" );
  NI_ASSERT( !buffer.Empty(), "" );

  StrongMT<RdpPacket> packet2Deliver = ctx.allocator->AllocatePkt( _totalSize );
  packet2Deliver->Setup( proto::EPktType::Datagram, callback->ConnDescr().remoteMux, callback->ConnDescr().localMux, 0, 0, _totalSize );

  if ( _totalSize && !packet2Deliver )
  {
    ErrorTrace( "Connection failed. Out of memory. descr=%s, size=%u, chunks=%u", callback->ConnDescr(), _totalSize, _chunks );
    ctx.stats->Inc( &RdpStats::errors );
    callback->ConnCbFailure();
    return 0;
  }

  timer::Time oldestRecvTime = 0;

  proto::Byte * dest = (proto::Byte * )packet2Deliver->Payload();
  for ( int i = 0; i < _chunks; ++i )
  {
    RdpPacket * pkt = buffer.AtTail();
    NI_VERIFY( pkt, "", return false );

    if ( pkt->PayloadSize() )
      memcpy( dest, pkt->Payload(), pkt->PayloadSize() );
    dest += pkt->PayloadSize();

    oldestRecvTime = Max<timer::Time>( oldestRecvTime, pkt->AbsRecvTime() );

    ctx.allocator->DeallocatePkt( pkt );
    buffer.PopTail();
    sequenceIdx = proto::NextSeqIndex( sequenceIdx );
  }

  packet2Deliver->SetAbsReceiveTime( oldestRecvTime );

  ReportWindowChange();

  return packet2Deliver;
}



StrongMT<RdpPacket> RdpInPktQueue::PopDatagramFromTail()
{
  NI_PROFILE_HEAVY_FUNCTION;

  NI_ASSERT( !buffer.Empty(), "" );

  StrongMT<RdpPacket> pkt = buffer.AtTail();
  buffer.PopTail();
  NI_VERIFY( pkt, "", return false );
  sequenceIdx = proto::NextSeqIndex( sequenceIdx );
  ReportWindowChange();

  return pkt;
}



bool RdpInPktQueue::PopShutdownPacket()
{
  NI_PROFILE_HEAVY_FUNCTION;

  if ( RdpPacket * pkt = buffer.AtTail() )
    if ( pkt->Solid() && ( pkt->Hdr()->type == proto::EPktType::Shutdown ) )
    {
      callback->QueCbShutdownRecieved();
      shutdownReceived = true;
      shutdownSeqIdx = sequenceIdx;

      ctx.allocator->DeallocatePkt( pkt );
      buffer.PopTail();

      sequenceIdx = proto::NextSeqIndex( sequenceIdx );
      ReportWindowChange();
      return true;
    }

  return false;
}



void RdpInPktQueue::ReportWindowChange()
{
  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "In window changed. descr=%s, start=%d", callback->ConnDescr(), sequenceIdx );
}

} //namespace ni_udp

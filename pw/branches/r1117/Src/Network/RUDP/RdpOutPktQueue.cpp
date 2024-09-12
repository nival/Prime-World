#include "stdafx.h"
#include "RdpOutPktQueue.h"
#include "RdpProto.h"
#include "RdpStats.h"
#include "System/InlineProfiler.h"


namespace ni_udp
{

RdpOutPktQueue::RdpOutPktQueue( const RdpCommonCtx & _ctx, IRdpPktQueueCallback * _cb ) :
RdpPktQueue( _ctx, _cb, _ctx.options->initOutPacketsQueue )
{
}



bool RdpOutPktQueue::HasEnoughSpace( size_t _bytes, size_t _packets ) const
{
  if ( totalBufferSize + _bytes <= ctx.options->maxOutQueueSize )
    if ( buffer.Size() + _packets <= ctx.options->maxOutQueuePackets )
      return true;
  return false;
}



void RdpOutPktQueue::Add( timer::Time _now, const void * _data, size_t _size )
{
  AddImpl( _now, _data, _size, false );
}



void RdpOutPktQueue::AddShutdown( timer::Time _now )
{
  AddImpl( _now, 0, 0, true );
}



void RdpOutPktQueue::AddImpl( timer::Time _now, const void * _data, size_t _size, bool _shutdown )
{
  NI_PROFILE_FUNCTION;

  size_t segments = 1;
  
  if ( !_shutdown )
    if ( _size )
      segments = ( _size + ctx.options->maxDataSegment - 1 ) / ctx.options->maxDataSegment;

  if ( segments > ctx.options->cc.maxWindowSize )
  {
    CriticalTrace( "Outgoing datagram discarded (out of maximum window). descr=%s, size=%u, segments=%u, window=%u", callback->ConnDescr(), _size, segments, ctx.options->cc.maxWindowSize );
    ctx.stats->Inc( &RdpStats::errors );
    callback->ConnCbFailure();
    return;
  }

  if ( !HasEnoughSpace( _size, segments ) )
  {
    CriticalTrace( "%s discarded (out of space). descr=%s, size=%u, segments=%u, buffer_len=%d, buffer_sz=%d", _shutdown ? "SHUTDOWN" : "Outgoing datagram", callback->ConnDescr(), _size, segments, buffer.Size(), totalBufferSize );
    ctx.stats->Inc( &RdpStats::errors );
    callback->ConnCbFailure();
    return;
  }

  bool sendImmidiately = true;
  if ( buffer.Size() >= callback->ConnCbCurrentWindowSize() )
    sendImmidiately = false;
  else
    if ( !buffer.Empty() )
      if ( RdpPacket * head = buffer.AtHead() )
        if ( head->TryIndex() == 0 ) //Previous data wasnt sent yet (socket is not writable?)
          sendImmidiately = false;

  unsigned seqIdx = proto::ClampSeqIndex( sequenceIdx + buffer.Size() );

  const proto::Byte * segmentPtr = (const proto::Byte * )_data;
  for ( size_t dataLeft = _size, segmIdx = 0; segmIdx < segments; ++segmIdx )
  {
    NI_VERIFY( _shutdown || dataLeft > 0, "", break );

    size_t sz = Min( dataLeft, (size_t)ctx.options->maxDataSegment );
    const void * ptr = segmentPtr;

    segmentPtr += sz;
    dataLeft -= sz;

    proto::EPktType::Enum pktType = _shutdown ? proto::EPktType::Shutdown : ( ( dataLeft == 0 ) ? proto::EPktType::Datagram : proto::EPktType::DatagramChunk );

    StrongMT<RdpPacket> pkt = ctx.allocator->AllocatePkt( sz );
    pkt->Setup( pktType, callback->ConnDescr().localMux, callback->ConnDescr().remoteMux, seqIdx, ptr, sz );

    seqIdx = proto::NextSeqIndex( seqIdx );

    buffer.PushAtHead( pkt );
    totalBufferSize += sz;
  }

  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "%s segment(s) added. descr=%s, seq=%d, size=%u, count=%u, buffer_len=%d, buffer_sz=%d", _shutdown ? "Shutdown" : "Data", callback->ConnDescr(), sequenceIdx, _size, segments, buffer.Size(), totalBufferSize );

  if ( !_shutdown )
    ctx.stats->Inc( &RdpStats::datagramsQueued );

  if ( sendImmidiately )
    WriteFreshPackets( _now, segments );
}



void RdpOutPktQueue::OnAck( timer::Time _now, unsigned _seqIdx, bool _shutdown )
{
  int offsetInWindow = proto::SeqIdxOffsetInWindow( sequenceIdx, buffer.Size(), _seqIdx, proto::SeqIndexClamp );
  if ( ( offsetInWindow < 0 ) || ( offsetInWindow >= (int)buffer.Size() ) )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogDetails ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Unknown ACK. descr=%s, seq=%d, wnd_start=%d, buf_size=%d", callback->ConnDescr(), _seqIdx, sequenceIdx, buffer.Size() );
    ctx.stats->Inc( &RdpStats::warnings );
    return;
  }

  StrongMT<RdpPacket> & pktSlot = buffer.AtTail( offsetInWindow );
  if ( !pktSlot )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogDetails ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Duplicate ACK. descr=%s, seq=%d, wnd_start=%d, buf_size=%d", callback->ConnDescr(), _seqIdx, sequenceIdx, buffer.Size() );
    ctx.stats->Inc( &RdpStats::warnings );
    return;
  }

  bool pktTypeOk =  ( _shutdown && ( pktSlot->Hdr()->type == proto::EPktType::Shutdown ) ) ||
    ( !_shutdown && ( pktSlot->Hdr()->type != proto::EPktType::Shutdown ) );

  if ( !pktTypeOk )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogDetails ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Wrong ACK type. descr=%s, seq=%d, type=%d, shutdown=%d", callback->ConnDescr(), _seqIdx, PktTypeToString( pktSlot->Hdr()->type ), _shutdown );
    ctx.stats->Inc( &RdpStats::warnings );
    return;
  }

  ctx.stats->Inc( &RdpStats::bytesDelivered, pktSlot->Size() );
  ctx.stats->Inc( &RdpStats::datagramsDelivered );

  const timer::Time rtt = _now - pktSlot->LastTryTime();
  callback->ConnCbPacketAcknowledged( ( pktSlot->TryIndex() == 1 ) ? rtt : -1.0 );

  if ( ctx.options->logEvents & RdpOptions::LogPackets )
    MessageTrace( "Datagram acknowledged. descr=%s, seq=%d, shutdown=%d, try=%d, rtt=%.1f", callback->ConnDescr(), _seqIdx, _shutdown, pktSlot->TryIndex(), rtt * 1e3 );

  if ( !_shutdown )
  {
    totalBufferSize -= pktSlot->PayloadSize();
    ctx.allocator->DeallocatePkt( pktSlot );
    pktSlot = 0;
  }

  if ( offsetInWindow == 0 )
    AdvanceWindow();
}



void RdpOutPktQueue::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  size_t count = Min( buffer.Size(), callback->ConnCbCurrentWindowSize() );

  for ( size_t i = 0; i < count; ++i )
  {
    NI_PROFILE_HEAVY_BLOCK( "Packet" );

    RdpPacket * pkt = buffer.AtTail( i );

    if ( !pkt )
      continue;

    if ( pkt->TryIndex() > 0 )
    {
      timer::Time rtto = callback->ConnCbCurrentRetransmitTime();
      if ( _now < pkt->LastTryTime() + rtto )
        continue;

      if ( pkt->TryIndex() >= ctx.options->retransmitLimit )
      {
        if ( ( ctx.options->logEvents & RdpOptions::LogMajorEvents ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
          WarningTrace( "Excessed retransmit limit. descr=%s, try=%d, seq=%d", callback->ConnDescr(), pkt->TryIndex(), pkt->Hdr()->index );
        callback->ConnCbFailure();
        break;
      }

      if ( ctx.options->logEvents & RdpOptions::LogDetails )
        MessageTrace( "Re-transmitting packet. descr=%s, type=%d, seq=%d, try=%d, size=%d, rtto=%.1f, now=%.1f", callback->ConnDescr(), PktTypeToString( pkt->Hdr()->type ), pkt->Hdr()->index, pkt->TryIndex(), pkt->PayloadSize(), rtto * 1e3, _now * 1e3 );
      ctx.stats->Inc( &RdpStats::retransmits );
      callback->ConnCbPacketRetransmitted();
    }
    else
      if ( ctx.options->logEvents & RdpOptions::LogDetails )
        MessageTrace( "Sending suspended packet. descr=%s, type=%d, seq=%d, size=%d", callback->ConnDescr(), PktTypeToString( pkt->Hdr()->type ), pkt->Hdr()->index, pkt->PayloadSize() );

    pkt->Send( _now, ctx.writer, callback->ConnDescr().remote );
  }
}



void RdpOutPktQueue::WriteFreshPackets( timer::Time _now, size_t _pktNumber )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( _pktNumber <= buffer.Size(), "", return );

  size_t begin = buffer.Size() - _pktNumber;
  size_t end = Min( buffer.Size(), callback->ConnCbCurrentWindowSize() );

  for ( size_t i = begin; i < end; ++i )
  {
    RdpPacket * pkt = buffer.AtTail( i );

    if ( pkt->TryIndex() != 0 )
      break;

    if ( ctx.options->logEvents & RdpOptions::LogDetails )
      MessageTrace( "Sending packet. descr=%s, type=%d, seq=%d, size=%d, now=%.1f", callback->ConnDescr(), PktTypeToString( pkt->Hdr()->type ), pkt->Hdr()->index, pkt->PayloadSize(), _now * 1e3 );
    pkt->Send( _now, ctx.writer, callback->ConnDescr().remote );
  }
}



void RdpOutPktQueue::AdvanceWindow()
{
  bool seqIdxChanged = false;
  while ( !buffer.Empty() )
  {
    StrongMT<RdpPacket> & tail = buffer.AtTail();
    if ( tail )
    {
      if ( tail->Hdr()->type == proto::EPktType::Shutdown )
      {
        callback->QueCbShutdownAcknowledged();
        ctx.allocator->DeallocatePkt( tail );
        tail = 0;
      }
      else
        break;
    }

    buffer.PopTail();
    sequenceIdx = proto::NextSeqIndex( sequenceIdx );
    seqIdxChanged = true;
  }

  if ( seqIdxChanged )
    ReportWindowChange();
}



void RdpOutPktQueue::ReportWindowChange()
{
  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "Out window changed. descr=%s, start=%d, size=%d", callback->ConnDescr(), sequenceIdx, callback->ConnCbCurrentWindowSize() );
}

} //namespace ni_udp

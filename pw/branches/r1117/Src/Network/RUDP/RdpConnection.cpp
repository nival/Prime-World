#include "stdafx.h"
#include "RdpConnection.h"
#include "RdpHandshake.h"
#include "RdpWriter.h"
#include "RdpPktQueue.h"
#include "RdpPacket.h"
#include "RdpStats.h"
#include "System/InlineProfiler.h"


NI_DEFINE_REFCOUNT( ni_udp::RdpConnection );

namespace ni_udp
{

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

RdpConnection::RdpConnection( timer::Time _now, const RdpCommonCtx & _ctx, const ConnDescriptor & _descr ) :
descr( _descr ),
activeSide( false ),
ctx( _ctx ),
status( EConnStatus::Pending ),
now( _now ),
sequenceIdx( 0 ),
outQueue( ctx, this ),
inQueue( ctx, this ),
ccLogic( _ctx.options, this ),
shutdownTimeWait( -1 ),
ping( _now, _ctx, this )
{
  incomingNotifyQueue.reserve( _ctx.options->outgoingBufferPreallocate );
  notifyReadBuffer.reserve( _ctx.options->outgoingBufferPreallocate );
}



RdpConnection::~RdpConnection()
{
  for ( NotifyQueue::iterator it = incomingNotifyQueue.begin(); it != incomingNotifyQueue.end(); ++it )
    if ( it->datagram.Valid() )
    {
      ctx.allocator->DeallocatePkt( it->datagram );
      it->datagram = 0;
    }

  incomingNotifyQueue.clear();
}



void RdpConnection::SetupAsActiveSide( IRdpConnection * _iface, IRdpConnectionCallback * _cb, RdpActiveHandshake * _hs )
{
  threading::MutexLock lock( mutex );

  activeSide = true;

  face = _iface;
  callback = _cb;
  activeHandshake = _hs;
}



void RdpConnection::SetupAsReactiveSide1( IRdpConnection * _iface, unsigned _seqIdx )
{
  threading::MutexLock lock( mutex );

  face = _iface;
  sequenceIdx = _seqIdx;

  outQueue.SetSequenceIndex( _seqIdx );
  inQueue.SetSequenceIndex( _seqIdx );
}



void RdpConnection::SetupAsReactiveSide2( IRdpConnectionCallback * _cb )
{
  threading::MutexLock lock( mutex );

  callback = _cb;

  Switch( EConnStatus::Ready );
}



bool RdpConnection::Switch( EConnStatus::Enum _st, bool _notifyChange )
{
  if ( ( status == EConnStatus::Closed ) || ( status == EConnStatus::Failed ) )
    return false;

  if ( _st != status )
  {
    status = _st;
    if ( _notifyChange )
      AddNotify( Notify( _st, 0 ) );
    return true;
  }

  return false;
}



EConnStatus::Enum RdpConnection::Status()
{
  threading::MutexLock lock( mutex );
  return status;
}



void RdpConnection::Close()
{
  threading::MutexLock lock( mutex );

  if ( Switch( EConnStatus::Closed, false ) )
  {
    if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
      MessageTrace( "Closing connection. descr=%s, reason=local", descr );

    shutdownTimeWait = now + ctx.options->shutdownTimeWait;

    outQueue.AddShutdown( now );
  }
}



void RdpConnection::SendDatagram( const void * _data, size_t _size, unsigned _options )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( _size > 0, "", return );

  threading::MutexLock lock( mutex );

  if ( status != EConnStatus::Ready )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogMajorEvents ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Connection is not ready. Outgoing datagram rejected. descr=%s, size=%d, status=%d", descr, _size, (int)status );
    ctx.stats->Inc( &RdpStats::errors );
    return;
  }

  if ( _options & EDatagramOpt::Raw )
  {
    if ( _size > ctx.options->maxDataSegment )
    {
      return;
    }
    StrongMT<RdpPacket> pkt = ctx.allocator->AllocatePkt( _size );
    pkt->Setup( proto::EPktType::DatagramRaw, descr.localMux, descr.remoteMux, 0, _data, _size );
    pkt->Send( now, ctx.writer, descr.remote );
    ctx.allocator->DeallocatePkt( pkt );

    ctx.stats->Inc( &RdpStats::rawDatagramsSent );
  }
  else
    outQueue.Add( now, _data, _size );
}



timer::Time RdpConnection::AvgRtt( int * _index )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::MutexLock lock( mutex );
  return ping.AvgRtt( _index );
}



void RdpConnection::FillDebugString( string & _outStr ) const
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  _outStr.reserve( 512 );

  _outStr = NI_STRFMT( 
    "Avg RTT:%.1f\n"
    "Pkt in/out: %d / %d\n"
    "Bytes in/out/dlvd: %d / %d / %d\n",
    ping.AvgRtt( 0 ) * 1e3,
    (LONG)ctx.stats->packetsRecieved, (LONG)ctx.stats->packetsWritten,
    (LONG)ctx.stats->bytesRecieved, (LONG)ctx.stats->bytesWritten, (LONG)ctx.stats->bytesDelivered );

  const LONG total = ctx.stats->datagramsDelivered + ctx.stats->retransmits;
  double lossEst = total ? ( 100.0 * ctx.stats->retransmits / total ) : 0;

  _outStr += NI_STRFMT( 
    "DG in/out/dlvd: %d / %d / %d\n"
    "Err/Warn: %d / %d\n"
    "RTTO/Rtn/Loss: %.1f / %d / %.1f%%\n",
    (LONG)ctx.stats->datagramsRecieved, (LONG)ctx.stats->datagramsQueued, (LONG)ctx.stats->datagramsDelivered,
    (LONG)ctx.stats->errors, (LONG)ctx.stats->warnings,
    ccLogic.RetransmitTimeout() * 1e3, (LONG)ctx.stats->retransmits, lossEst );

  _outStr += NI_STRFMT( "OutQ/InQ/MaxWS: %d / %u / %u\n",
    outQueue.BufferSize(), inQueue.BufferSize(), ccLogic.WindowSize() );
}



bool RdpConnection::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  bool result = RdpConnection::PollLocked( _now );

  if ( !notifyReadBuffer.empty() )
  {
    StrongMT<IRdpConnectionCallback> lockedCb = callback.Lock();
    StrongMT<IRdpConnection> lockedFace = face.Lock();
    if ( !lockedCb || !lockedFace )
      ErrorTrace( "Invalid connection callback or proxy. descr=%s", descr );

    for ( NotifyQueue::iterator it = notifyReadBuffer.begin(); it != notifyReadBuffer.end(); ++it )
    {
      const Notify & evt = *it;
      if ( evt.datagram )
      {
        NI_ASSERT( evt.status == EConnStatus::None, "" );
        if ( lockedCb && lockedFace )
        {
          lockedCb->OnDatagram( lockedFace, evt.datagram->Payload(), evt.datagram->PayloadSize(), evt.datagram->AbsRecvTime() );
          ctx.stats->Inc( &RdpStats::datagramsRecieved );
        }

        ctx.allocator->DeallocatePkt( evt.datagram );
      }
      else
      {
        NI_ASSERT( !evt.datagram, "" );
        if ( lockedCb && lockedFace )
          switch( evt.status )
          {
            default:
              break;

            case EConnStatus::Ready:
              lockedCb->OnConnectionEstablished( lockedFace );
              break;

            case EConnStatus::Closed:
              lockedCb->OnConnectionClosed( lockedFace );
              break;

            case EConnStatus::Failed:
              lockedCb->OnConnectionFailed( lockedFace );
              break;
          }
      }
    }

    notifyReadBuffer.clear();
  }

  return result;
}



void RdpConnection::OnHandshakeFailed()
{
  Switch( EConnStatus::Failed );
}



void RdpConnection::OnHandshakeCompleted( const ConnDescriptor & _descr, unsigned _seqIdx )
{
  //sequenceIdx = proto::NextSeqIndex( _seqIdx );
  sequenceIdx = proto::ClampSeqIndex( _seqIdx );

  outQueue.SetSequenceIndex( sequenceIdx );
  inQueue.SetSequenceIndex( sequenceIdx );

  Switch( EConnStatus::Ready );
}



bool RdpConnection::PollLocked( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  threading::MutexLock lock( mutex );

  now = _now;

  if ( activeHandshake )
    if ( !activeHandshake->Poll( now ) )
      activeHandshake = 0;

  if ( status != EConnStatus::Failed )
  {
    outQueue.Poll( now );
    inQueue.Poll( now );
  }

  ccLogic.Poll( now );

  if ( status == EConnStatus::Ready )
    ping.Poll( now );

  NI_ASSERT( notifyReadBuffer.empty(), "" );
  incomingNotifyQueue.swap( notifyReadBuffer );

  if ( status == EConnStatus::Failed )
    return false;

  if ( status == EConnStatus::Closed )
    if ( now > shutdownTimeWait )
    {
      if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
        MessageTrace( "Closed connection time-wait %s. descr=%s", shutdownTimeWait < 0 ? "finished" : "expired", descr );
      return false;
    }

  return true;
}



void RdpConnection::AddNotify( const Notify & _evt )
{
  if ( incomingNotifyQueue.size() >= ctx.options->outgoingBufferHardlimit )
  {
    CriticalTrace( "Outgoing buffer overflow. size=%d, limit=%d", incomingNotifyQueue.size(), ctx.options->outgoingBufferHardlimit );
    ctx.stats->Inc( &RdpStats::errors );
    return;
  }

  if ( _evt.datagram )
    _evt.datagram->PktAddRef();

  incomingNotifyQueue.push_back( _evt );
}



bool RdpConnection::on_pkt_InitAck( unsigned _seqIdx )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( activeHandshake )
  {
    activeHandshake->OnInitAck( _seqIdx );
    return true;
  }

  return false;
}



bool RdpConnection::on_pkt_Refused( unsigned _seqIdx )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( activeHandshake )
  {
    activeHandshake->OnRefused( _seqIdx );
    return true;
  }

  return false;
}



bool RdpConnection::on_pkt_RetryHandshake( unsigned _seqIdx, IRdpLogic * _logic )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( activeHandshake )
  {
    activeHandshake->OnRetry( _seqIdx, _logic );
    return true;
  }

  return false;
}



void RdpConnection::on_pkt_DatagramRaw( RdpPacket * _packet )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( activeHandshake )
    activeHandshake->OnAnyDatagram( _packet->Hdr()->index );

  StrongMT<IRdpConnectionCallback> lockedCb = callback.Lock();
  StrongMT<IRdpConnection> lockedFace = face.Lock();
  if ( lockedCb && lockedFace )
    lockedCb->OnDatagram( lockedFace, _packet->Payload(), _packet->PayloadSize(), _packet->AbsRecvTime() );

  ctx.stats->Inc( &RdpStats::rawDatagramsRecieved );
}



void RdpConnection::on_pkt_Datagram( RdpPacket * _packet )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( activeHandshake )
    activeHandshake->OnAnyDatagram( _packet->Hdr()->index );

  inQueue.OnDatagram( now, _packet );
}



void RdpConnection::on_pkt_DatagramAck( unsigned _seqIdx, proto::EPktType::Enum _pktType )
{
  NI_PROFILE_HEAVY_FUNCTION;

  const bool shutdown = ( _pktType == proto::EPktType::ShutdownAck );

  threading::MutexLock lock( mutex );

  if ( activeHandshake )
    activeHandshake->OnAnyDatagram( _seqIdx );

  outQueue.OnAck( now, _seqIdx, shutdown );
}



void RdpConnection::on_pkt_Ping( unsigned _seqIdx, proto::EPktType::Enum _pktType )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::MutexLock lock( mutex );

  if ( activeHandshake )
    activeHandshake->OnAnyDatagram( _seqIdx );

  if ( status != EConnStatus::Ready )
    return;

  if ( _pktType == proto::EPktType::Ping )
    ping.OnPing( now, _seqIdx );
  else if ( _pktType == proto::EPktType::Pong )
    ping.OnPong( now, _seqIdx );
  else
    NI_ALWAYS_ASSERT( "" );
}



void RdpConnection::ConnCbFailure()
{
  Switch( EConnStatus::Failed );
}



void RdpConnection::ConnCbPacketAcknowledged( timer::Time _rtt )
{
  ping.OnDatagramAck( now, _rtt );

  ccLogic.OnPacketAcknowledged( _rtt );
}



void RdpConnection::ConnCbPacketRetransmitted()
{
  ccLogic.OnPacketRetransmitted();
}



void RdpConnection::QueCbDatagram( RdpPacket * _pkt )
{
  if ( status != EConnStatus::Ready )
    return;

  AddNotify( Notify( EConnStatus::None, _pkt ) );
}



void RdpConnection::QueCbShutdownAcknowledged()
{
  if ( status == EConnStatus::Closed )
  {
    if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
      MessageTrace( "Connection shutdown finished. descr=%s", descr );
    shutdownTimeWait = -1;
  }
}



void RdpConnection::QueCbShutdownRecieved()
{
  if ( Switch( EConnStatus::Closed ) )
  {
    if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
      MessageTrace( "Closing connection. descr=%s, reason=remote", descr );
    shutdownTimeWait = now + ctx.options->shutdownTimeWait;
  }
}

} //namespace ni_udp

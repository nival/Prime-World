#include "stdafx.h"
#include "RdpHandshake.h"
#include "RdpWriter.h"


namespace ni_udp
{


NI_ENUM_BEGIN_STD( EHandshakeStage );
  NI_ENUM_ITEM( None );
  NI_ENUM_ITEM( Active_Start );
  NI_ENUM_ITEM( Active_WaitingInitAck );
  NI_ENUM_ITEM( Active_Completed );
  NI_ENUM_ITEM( Reactive_Start );
  NI_ENUM_ITEM( Reactive_WaitingAck );
  NI_ENUM_ITEM( Failed );
  NI_ENUM_ITEM( Finished );
NI_ENUM_END_STD;



RdpHandshakeBase::RdpHandshakeBase( const RdpCommonCtx & _ctx, const ConnDescriptor & _descr, IRdpHandshakeCallback * _cb, EHandshakeStage::Enum _initial, unsigned _seqIndex, timer::Time _now ) :
descr( _descr ),
totalTimeoutEnds( _now + _ctx.options->handshakeTotalTimeout ),
ctx( _ctx ),
stage( _initial ),
callback( _cb ),
now( _now ),
sequenceIdx( _seqIndex ),
retryTemeout( _now ),
retryIndex( 1 )
{
}



void RdpHandshakeBase::SwitchStage( EHandshakeStage::Enum _new )
{
  if ( ( stage != EHandshakeStage::Failed ) && ( stage != EHandshakeStage::Finished ) )
    if ( _new != stage )
    {
      if ( _new == EHandshakeStage::Failed )
        if ( StrongMT<IRdpHandshakeCallback> locked = callback.Lock() )
          locked->OnHandshakeFailed();

      stage = _new;
      //newStages.push_back( _new );
    }
}








bool RdpActiveHandshake::Poll( timer::Time _now )
{
  now = _now;

  if ( Finished() )
    return false;

  if ( _now > totalTimeoutEnds )
  {
    if ( Stage() == EHandshakeStage::Active_Completed )
    {
      if ( ctx.options->logEvents & RdpOptions::LogHandshake )
        MessageTrace( "Active handshake TIME_WAIT completed. descr=%s", descr );
      SwitchStage( EHandshakeStage::Finished );
    }
    else
    {
      if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
        WarningTrace( "Active handshake timed out. descr=%s", descr );
      SwitchStage( EHandshakeStage::Failed );
    }
    return !Finished();
  }

  switch ( Stage() )
  {
    case EHandshakeStage::Active_Start:
      SwitchStage( EHandshakeStage::Active_WaitingInitAck );
      if ( ctx.options->logEvents & RdpOptions::LogHandshake )
        MessageTrace( "Sending INIT. descr=%s, seq=%d", descr, sequenceIdx );
      ctx.writer->Send( descr, proto::EPktType::HandshakeInit, sequenceIdx );
      //sequenceIdx = proto::NextSeqIndex( sequenceIdx );
      retryTemeout = _now + ctx.options->handshakeRetryTimeout;
      break;

    case EHandshakeStage::Active_WaitingInitAck:
      if ( _now > retryTemeout )
      {
        if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
          WarningTrace( "INIT_ACK waiting timed out. descr=%s", descr );

        if ( !Retry() )
          return false;
      }
      break;

    case EHandshakeStage::Active_Completed:
      break;

    default:
      NI_ALWAYS_ASSERT( "" );
      SwitchStage( EHandshakeStage::Failed );
  }

  return !Finished();
}



void RdpActiveHandshake::OnRefused( unsigned _seqIdx )
{
  if ( ( sequenceIdx != _seqIdx ) || ( Stage() != EHandshakeStage::Active_WaitingInitAck ) )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "REFUSED ignored. descr=%s, seq=%d, required_seq=%d, stage=%s", descr, _seqIdx, sequenceIdx, EHandshakeStage::ToString( Stage() ) );
    return;
  }

  SwitchStage( EHandshakeStage::Failed );
}



void RdpActiveHandshake::OnRetry( unsigned _seqIdx, IRdpLogic * _logic )
{
  if ( ( sequenceIdx != _seqIdx ) || ( Stage() != EHandshakeStage::Active_WaitingInitAck ) )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "RETRY_HS ignored. descr=%s, seq=%d, required_seq=%d, stage=%s", descr, _seqIdx, sequenceIdx, EHandshakeStage::ToString( Stage() ) );
    return;
  }

  if ( ctx.options->logEvents & RdpOptions::LogHandshake )
    MessageTrace( "Re-allocating local mux. descr=%s", descr );

  unsigned newLocalMux = _logic->ReallocateLocalEphemeralMux( descr );
  if ( !newLocalMux )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Could not reallocate local mux. descr=%s", descr );
    SwitchStage( EHandshakeStage::Failed );
    return;
  }

  if ( ctx.options->logEvents & RdpOptions::LogHandshake )
    MessageTrace( "New local mux. descr=%s, mux=%u", descr, newLocalMux );
  descr.localMux = newLocalMux;

  if ( !Retry() )
    return;
}



void RdpActiveHandshake::OnInitAck( unsigned _seqIdx )
{
  if ( Finished() )
    return;

  if ( ( _seqIdx < sequenceIdx ) || ( ( Stage() != EHandshakeStage::Active_WaitingInitAck ) && ( Stage() != EHandshakeStage::Active_Completed ) ) )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "INIT_ACK ignored. descr=%s, seq=%d, required_seq=%d, stage=%s", descr, _seqIdx, sequenceIdx, EHandshakeStage::ToString( Stage() ) );
    return;
  }

  //sequenceIdx = proto::NextSeqIndex( _seqIdx );

  ctx.writer->Send( descr, proto::EPktType::HandshakeAck, sequenceIdx );
  if ( ctx.options->logEvents & RdpOptions::LogHandshake )
    MessageTrace( "ACK sent. descr=%s, seq=%d, stage=%s", descr, sequenceIdx, EHandshakeStage::ToString( Stage() ) );

  if ( Stage() == EHandshakeStage::Active_WaitingInitAck )
  {
    SwitchStage( EHandshakeStage::Active_Completed );

    if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
      MessageTrace( "Active connection handshake completed. descr=%s, seq=%d", descr, sequenceIdx );

    if ( StrongMT<IRdpHandshakeCallback> locked = callback.Lock() )
      locked->OnHandshakeCompleted( descr, sequenceIdx );
  }
}



void RdpActiveHandshake::OnAnyDatagram( unsigned _seqIdx )
{
  SwitchStage( EHandshakeStage::Finished );
}



bool RdpActiveHandshake::Retry()
{
  if ( retryIndex > ctx.options->handshakeMaxTries )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Active handshake failed, too many retries. descr=%s", descr );
    SwitchStage( EHandshakeStage::Failed );
    return false;
  }

  ++retryIndex;
  if ( ctx.options->logEvents & RdpOptions::LogHandshake )
    MessageTrace( "Re-trying active handshake. descr=%s, try=%d", descr, retryIndex );

  sequenceIdx = proto::ClampSeqIndex( sequenceIdx + 3 );
  SwitchStage( EHandshakeStage::Active_Start );

  return true;
}













bool RdpReactiveHandshake::Poll( timer::Time _now )
{
  now = _now;

  if ( Finished() )
    return false;

  if ( _now > totalTimeoutEnds )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Reactive handshake timed out. descr=%s", descr );
    SwitchStage( EHandshakeStage::Failed );
    return false;
  }

  switch( Stage() )
  {
    case EHandshakeStage::Reactive_Start:
      SwitchStage( EHandshakeStage::Reactive_WaitingAck );
      ctx.writer->Send( descr, proto::EPktType::HandshakeInitAck, sequenceIdx );
      if ( ctx.options->logEvents & RdpOptions::LogHandshake )
        MessageTrace( "INIT_ACK sent. descr=%s, seq=%d", descr, sequenceIdx );
      //sequenceIdx = proto::NextSeqIndex( sequenceIdx );
      retryTemeout = _now + ctx.options->handshakeRetryTimeout;
      break;
  
    case EHandshakeStage::Reactive_WaitingAck:
      if ( _now > retryTemeout )
      {
        if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
          WarningTrace( "ACK waiting timed out. descr=%s", descr );

        if ( retryIndex > ctx.options->handshakeMaxTries )
        {
          if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
            WarningTrace( "Reactive handshake failed, too many retries. descr=%s", descr );
          SwitchStage( EHandshakeStage::Failed );
          return false;
        }

        ++retryIndex;
        if ( ctx.options->logEvents & RdpOptions::LogHandshake )
          MessageTrace( "Re-trying reactive handshake. descr=%s, try=%d", descr, retryIndex );

        SwitchStage( EHandshakeStage::Reactive_Start );
      }
      break;

    default:
      NI_ALWAYS_ASSERT( "" );
      SwitchStage( EHandshakeStage::Failed );
  }

  return !Finished();
}



void RdpReactiveHandshake::OnInit( unsigned _seqIdx )
{
  if ( retryIndex > ctx.options->handshakeMaxTries )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Max retries reached on INIT. descr=%s", descr );
    SwitchStage( EHandshakeStage::Failed );
  }
  else
  {
    ++retryIndex;
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Duplicated INIT. descr=%s, seq=%d, prev_seq=%d, try=%d", descr, _seqIdx, sequenceIdx, retryIndex );
    //sequenceIdx = proto::NextSeqIndex( _seqIdx );
    sequenceIdx = proto::ClampSeqIndex( _seqIdx );
    SwitchStage( EHandshakeStage::Reactive_Start );
  }
}



void RdpReactiveHandshake::OnAck( unsigned _seqIdx )
{
  if ( ( _seqIdx < sequenceIdx ) || ( Stage() != EHandshakeStage::Reactive_WaitingAck ) )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogHandshake ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "ACK ignored. descr=%s, seq=%d, required_seq=%d, stage=%s", descr, _seqIdx, sequenceIdx, EHandshakeStage::ToString( Stage() ) );
    return;
  }

  //sequenceIdx = proto::NextSeqIndex( _seqIdx );

  completeTime = now;
  SwitchStage( EHandshakeStage::Finished );

  if ( ctx.options->logEvents & RdpOptions::LogMajorEvents )
    MessageTrace( "Incoming connection fully accepted. descr=%s, seq=%d", descr, sequenceIdx );

  if ( StrongMT<IRdpHandshakeCallback> locked = callback.Lock() )
    locked->OnHandshakeCompleted( descr, sequenceIdx );
}

} //namespace ni_udp

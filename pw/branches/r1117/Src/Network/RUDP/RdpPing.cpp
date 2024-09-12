#include "stdafx.h"
#include "RdpPing.h"
#include "RdpProto.h"
#include "RdpWriter.h"
#include "RdpStats.h"
#include "System/InlineProfiler.h"


namespace ni_udp
{

RdpPing::RdpPing( timer::Time _now, const RdpCommonCtx & _ctx, IRdpConnImplCallback * _cb ) :
ctx( _ctx ),
callback( _cb ),
nextPingTime( _now + _ctx.options->pingPeriod ),
tryIndex( 0 ),
retransmitTime( _ctx.options->cc.initRetransmitTime ),
lastTryTime( 0 ),
seqIndex( 0 ),
previousRtt( -1 ),
avgRtt( 0 ),
antiSpamCounter( 0 ),
antiSpamPrevTime( _now )
{
}



void RdpPing::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  timer::Time antiSpamDt = _now - antiSpamPrevTime;
  antiSpamPrevTime = _now;

  antiSpamCounter -= antiSpamDt / ctx.options->pingPeriod;

  if ( !tryIndex )
  {
    if ( _now < nextPingTime )
      return;
  }

  if ( tryIndex && ( _now < lastTryTime + retransmitTime ) )
    return;

  ++tryIndex;

  seqIndex = proto::NextSeqIndex( seqIndex );

  if ( tryIndex > ctx.options->retransmitLimit )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogMajorEvents ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Excessed retransmit limit on ping. descr=%s, try=%d", callback->ConnDescr(), tryIndex );
    callback->ConnCbFailure();
    return;
  }

  if ( tryIndex > 1 )
  {
    retransmitTime *= 2;
    retransmitTime = Min( retransmitTime, (timer::Time)ctx.options->cc.maxRetransmitTime );
  }

  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "Sending ping. descr=%s, try=%d", callback->ConnDescr(), tryIndex );

  ctx.writer->Send( callback->ConnDescr(), proto::EPktType::Ping, seqIndex );

  lastTryTime = _now;
}



void RdpPing::OnPing( timer::Time _now, unsigned _seqIdx )
{
  const bool spamWasDetected = ( antiSpamCounter >= 1.0 );

  antiSpamCounter += 0.5 / (timer::Time)ctx.options->retransmitLimit;

  const bool spamDetected = ( antiSpamCounter >= 1.0 );

  if ( spamDetected )
  {
    if ( !spamWasDetected )
      if ( ( ctx.options->logEvents & RdpOptions::LogMajorEvents ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
        WarningTrace( "Ping spam detected. descr=%s", callback->ConnDescr(), tryIndex );
    ctx.stats->Inc( &RdpStats::errors );
    return;
  }

  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "Sending pong. descr=%s, seq=%d", callback->ConnDescr(), _seqIdx );

  ctx.writer->Send( callback->ConnDescr(), proto::EPktType::Pong, _seqIdx );
}



void RdpPing::OnPong( timer::Time _now, unsigned _seqIdx )
{
  if ( !tryIndex && ( seqIndex == (int)_seqIdx ) )
  {
    if ( ctx.options->logEvents & RdpOptions::LogDetails )
      MessageTrace( "Ping out of order. descr=%s, try=%d, current_ping_seq=%d, ping_seq=%d", callback->ConnDescr(), tryIndex, seqIndex, _seqIdx );
    return;
  }

  if ( !tryIndex || ( seqIndex != (int)_seqIdx ) )
  {
    if ( ( ctx.options->logEvents & RdpOptions::LogDetails ) || ( ctx.options->logEvents & RdpOptions::LogWarnings ) )
      WarningTrace( "Ping out of order. descr=%s, try=%d, current_ping_seq=%d, ping_seq=%d", callback->ConnDescr(), tryIndex, seqIndex, _seqIdx );
    return;
  }

  CountPing( _now - lastTryTime );
  ResetPingTry( _now );
}



void RdpPing::OnDatagramAck( timer::Time _now, timer::Time _rtt )
{
  if ( _rtt >= 0 )
    CountPing( _rtt );
  ResetPingTry( _now );
}



timer::Time RdpPing::AvgRtt( int * _index ) const
{
  if ( _index )
    *_index = seqIndex;
  return avgRtt;
}



void RdpPing::ResetPingTry( timer::Time _now )
{
  nextPingTime = _now + ctx.options->pingPeriod;
  tryIndex = 0;
  lastTryTime = 0;

  retransmitTime *= 0.5;
  retransmitTime = Max( retransmitTime, (timer::Time)ctx.options->cc.initRetransmitTime );
}



void RdpPing::CountPing( timer::Time _rtt )
{
  if ( previousRtt < 0 )
    previousRtt = _rtt;

  avgRtt = 0.5 * ( previousRtt + _rtt );
  previousRtt = _rtt;

  if ( ctx.options->logEvents & RdpOptions::LogDetails )
    MessageTrace( "Ping updated. descr=%s, rtt=%.1f, avg_rtt=%.1f", callback->ConnDescr(), 1e3 * _rtt, 1e3 * avgRtt );
}

} //namespace ni_udp

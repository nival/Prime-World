#include "stdafx.h"
#include "RdpCongestionControl.h"
#include "System/SafeTextFormatCyclicBuffer.h"


namespace ni_udp
{

CCLogic::CCLogic( RdpOptionsObject * _opt, IRdpConnImplCallback * _cb ) :
callback( _cb ),
options( _opt ),
retransmitTimeout( _opt->cc.initRetransmitTime ),
dbgLastReportedRtto( retransmitTimeout ),
windowSize( _opt->cc.initWindowSize ),
changed( false ),
history( _opt->cc.historyLen ),
nextWindowSize( _opt->cc.initWindowSize )
{
}



void CCLogic::OnPacketRetransmitted()
{
  PopHistory();
  history.PushAtHead( -1.0f );

  nextWindowSize -= options->cc.windowSizeDec;

  changed = true;
}



void CCLogic::OnPacketAcknowledged( timer::Time _rtt )
{
  if ( _rtt >= 0 )
  {
    PopHistory();
    history.PushAtHead( (float)( _rtt * 1e3 ) );
  }

  nextWindowSize += options->cc.windowSizeInc;

  changed = true;
}



void CCLogic::Poll( timer::Time _now )
{
  if ( !changed )
    return;

  changed = false;

  nextWindowSize = Clamp( nextWindowSize, (int)options->cc.initWindowSize, (int)options->cc.maxWindowSize );

  if ( (unsigned)nextWindowSize != windowSize )
    if ( options->logEvents & RdpOptions::LogCc )
      MessageTrace( "Connection window size changed. descr=%s, window=%d (%d)", callback->ConnDescr(), nextWindowSize, windowSize );

  windowSize = nextWindowSize;

  float rttSum = 0, weigthSum = 0;
  int retransmits = 0, hits = 0;
  for ( size_t i = 0; i < history.Size(); ++i )
  {
    float t = 1e-3f * history.AtHead( i );
    if ( t < 0 )
      ++retransmits;
    else
    {
      float w = ( hits < 2 ) ? 2.0 : 1.0;
      rttSum += w * t;
      weigthSum += w;
      ++hits;
    }
  }

  if ( !hits )
  {
    rttSum = options->cc.maxRetransmitTime;
    weigthSum = 1.0f;
  }

  const float avgRtt = rttSum / weigthSum;
  timer::Time newRtto = avgRtt * options->cc.rttoMultiplicativeMargin + options->cc.rttoAdditiveMargin;

  if ( retransmits >= 2 )
    newRtto += ( 1u << ( retransmits - 2 ) ) * options->cc.rttoFactor;

  if ( newRtto > options->cc.maxRetransmitTime )
    newRtto = options->cc.maxRetransmitTime;

  if ( fabs( newRtto - dbgLastReportedRtto ) > 0.01 )
  {
    if ( options->logEvents & RdpOptions::LogCc )
      MessageTrace( "Connection RTTO changed. descr=%s, rtto=%.1f (%.1f), rtn=%d, avg_rtt=%.1f, hist=%.1f", callback->ConnDescr(), newRtto * 1e3, dbgLastReportedRtto * 1e3, retransmits, avgRtt * 1e3, history );
    dbgLastReportedRtto = newRtto;
  }

  retransmitTimeout = newRtto;
}



void CCLogic::PopHistory()
{
  if ( history.Size() < options->cc.historyLen )
    return;

  history.PopTail();
}

} //namespace ni_udp

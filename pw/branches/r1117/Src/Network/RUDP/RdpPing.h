#ifndef RUDP_RDPPING_H_INCLUDED
#define RUDP_RDPPING_H_INCLUDED

#include "IRdp.h"
#include "RdpCommon.h"
#include "RdpConnDescriptor.h"


namespace ni_udp
{

class RdpPing
{
public:
  RdpPing( timer::Time _now, const RdpCommonCtx & _ctx, IRdpConnImplCallback * _cb );

  void Poll( timer::Time _now );
  void OnPing( timer::Time _now, unsigned _seqIdx );
  void OnPong( timer::Time _now, unsigned _seqIdx );
  void OnDatagramAck( timer::Time _now, timer::Time _rtt );

  timer::Time AvgRtt( int * _index ) const;

private:
  RdpCommonCtx            ctx;
  IRdpConnImplCallback    *callback;
  timer::Time             nextPingTime;
  unsigned                tryIndex;
  timer::Time             retransmitTime;
  timer::Time             lastTryTime;
  int                     seqIndex;

  timer::Time             previousRtt;
  timer::Time             avgRtt;

  timer::Time             antiSpamCounter;
  timer::Time             antiSpamPrevTime;

  void ResetPingTry( timer::Time _now );
  void CountPing( timer::Time _rtt );
};

} //namespace ni_udp

#endif //RUDP_RDPPING_H_INCLUDED

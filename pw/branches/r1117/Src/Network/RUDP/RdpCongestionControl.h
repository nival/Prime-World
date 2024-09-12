#ifndef RDPCONGESTIONCONTROL_H_INCLUDED
#define RDPCONGESTIONCONTROL_H_INCLUDED

#include "RdpCommon.h"
#include "System/CyclicBuffer.h"

namespace ni_udp
{

class CCLogic : public NonCopyable
{
public:
  explicit CCLogic( RdpOptionsObject * _opt, IRdpConnImplCallback * _cb );

  timer::Time RetransmitTimeout() const { return retransmitTimeout; }
  unsigned WindowSize() const { return windowSize; }

  void OnPacketRetransmitted();
  void OnPacketAcknowledged( timer::Time _rtt );

  void Poll( timer::Time _now );

private:
  IRdpConnImplCallback        *callback;
  StrongMT<RdpOptionsObject>  options;
  timer::Time                 retransmitTimeout;
  timer::Time                 dbgLastReportedRtto;
  unsigned                    windowSize;

  bool                        changed;
  CyclicBuffer<float>         history;
  int                         nextWindowSize;

  void PopHistory();
};

} //namespace ni_udp

#endif //RDPCONGESTIONCONTROL_H_INCLUDED

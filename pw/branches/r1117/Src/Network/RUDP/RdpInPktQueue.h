#ifndef RUDP_RDPINPKTQUEUE_H_INCLUDED
#define RUDP_RDPINPKTQUEUE_H_INCLUDED

#include "RdpPktQueue.h"
#include "RdpProto.h"

namespace ni_udp
{

class RdpInPktQueue : public RdpPktQueue
{
public:
  RdpInPktQueue( const RdpCommonCtx & _ctx, IRdpPktQueueCallback * _cb );

  void Poll( timer::Time _now );
  void OnDatagram( timer::Time _now, RdpPacket * _packet );

  bool ShutdownReceived() const { return shutdownReceived; }

private:
  void OnInSequencePacket( RdpPacket * _packet );
  void OnOutOfSequencePacket( timer::Time _now, int _offsetInWindow, RdpPacket * _packet );
  bool PropagateSolidity( int _newPktOffs, RdpPacket * _newPkt );
  void DeliverQueuedDatagrams( bool _atLeastOne );
  bool DeliverQueuedDatagram();
  StrongMT<RdpPacket> AssembleDatagramFromTail( int chunks, size_t totalSize );
  StrongMT<RdpPacket> PopDatagramFromTail();
  bool PopShutdownPacket();
  void ReportWindowChange();

  bool    shutdownReceived;
  int     shutdownSeqIdx;
};

} //namespace ni_udp

#endif //RUDP_RDPINPKTQUEUE_H_INCLUDED

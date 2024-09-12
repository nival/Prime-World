#ifndef RUDP_RDPOUTPKTQUEUE_H_INCLUDED
#define RUDP_RDPOUTPKTQUEUE_H_INCLUDED

#include "RdpPktQueue.h"

namespace ni_udp
{

class RdpOutPktQueue : public RdpPktQueue
{
public:
  RdpOutPktQueue( const RdpCommonCtx & _ctx, IRdpPktQueueCallback * _cb );

  void Poll( timer::Time _now );
  void Add( timer::Time _now, const void * _data, size_t _size );
  void AddShutdown( timer::Time _now );
  void OnAck( timer::Time _now, unsigned _seqIdx, bool _shutdown );

private:
  bool HasEnoughSpace( size_t _bytes, size_t _packets ) const;
  void AddImpl( timer::Time _now, const void * _data, size_t _size, bool _shutdown );
  void WriteFreshPackets( timer::Time _now, size_t _pktNumber );
  void AdvanceWindow();
  void ReportWindowChange();
};

} //namespace ni_udp

#endif //RUDP_RDPOUTPKTQUEUE_H_INCLUDED

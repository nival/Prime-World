#ifndef RUDP_RDPPKTQUEUE_H_INCLUDED
#define RUDP_RDPPKTQUEUE_H_INCLUDED

#include "IRdp.h"
#include "RdpCommon.h"
#include "RdpConnDescriptor.h"
#include "RdpPacket.h"
#include "System/CyclicBuffer.h"


namespace ni_udp
{

class RdpPacket;

class IRdpPktQueueCallback : public IRdpConnImplCallback
{
public:
  virtual timer::Time ConnCbCurrentRetransmitTime() const = 0;
  virtual unsigned ConnCbCurrentWindowSize() const = 0;
  virtual void QueCbDatagram( RdpPacket * _pkt ) = 0;
  virtual void QueCbShutdownAcknowledged() = 0;
  virtual void QueCbShutdownRecieved() = 0;
};



class RdpPktQueue
{
public:
  RdpPktQueue( const RdpCommonCtx & _ctx, IRdpPktQueueCallback * _cb, size_t _initialSize ) :
  ctx( _ctx ),
  callback( _cb ),
  buffer( _initialSize ),
  totalBufferSize( 0 ),
  sequenceIdx( 0 )
  {}

  ~RdpPktQueue()
  {
    while ( !buffer.Empty() )
    {
      StrongMT<RdpPacket> & pkt = buffer.AtTail();
      if ( pkt )
      {
        ctx.allocator->DeallocatePkt( pkt );
        pkt = 0;
      }

      buffer.PopTail();
    }
  }

  size_t BufferSize() const { return buffer.Size(); }

  void SetSequenceIndex( unsigned _seqIdx ) { sequenceIdx = _seqIdx; }

protected:
  RdpCommonCtx                        ctx;
  IRdpPktQueueCallback                *callback;
  CyclicBuffer<StrongMT<RdpPacket>>   buffer;
  unsigned                            totalBufferSize;
  unsigned                            sequenceIdx;
  bool                                failed;
};

} //namespace ni_udp

#endif //RUDP_RDPPKTQUEUE_H_INCLUDED

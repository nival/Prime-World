#ifndef RUDP_RDPPACKET_H_INCLUDED
#define RUDP_RDPPACKET_H_INCLUDED

#include "IRdp.h"
#include "RdpProto.h"
#include <vector>


namespace ni_udp
{

class RdpWriter;


class RdpPacket : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RdpPacket, BaseObjectMT );

public:
  RdpPacket( size_t _totalCapacity );
  ~RdpPacket();

  int PktAddRef();
  int PktReleaseRef();

  void SetInUse() { inUse = true; }
  bool InUse() const { return inUse; }

  size_t Size() const { return bytes.size(); }
  size_t Capacity() const { return bytes.capacity(); }
  static inline size_t PayloadToCapacity( size_t _payloadCapacity ) { return sizeof( proto::Header ) + _payloadCapacity; }

  void Setup( proto::EPktType::Enum _type, unsigned _srcMux, unsigned _destMux, unsigned _index, const void * _data, size_t _size );
  void Cleanup();

  const std::vector<proto::Byte> & Bytes() const { return bytes; }
  const proto::Header * Hdr() const;
  const void * Payload() const;
  size_t PayloadSize() const { return payloadSize; }

  timer::Time LastTryTime() const { return lastTryTime; }
  unsigned TryIndex() const { return tryIndex; }

  void Send( timer::Time _now, RdpWriter * _writer, const NetAddr & _sendto );

  bool Solid() const { return solid; }
  void SetSolid( bool _s ) { solid = _s; }

  void SetAbsReceiveTime( timer::Time _recvTime ) { absRecvTime = _recvTime; }
  timer::Time AbsRecvTime() const { return absRecvTime; }

private:
  volatile LONG             packetRefCount;
  bool                      inUse; //For use in pool allocator only
  std::vector<proto::Byte>  bytes;
  size_t                    payloadSize;
  unsigned                  tryIndex;
  timer::Time               lastTryTime;
  bool                      solid;
  timer::Time               absRecvTime;
};



class IRdpPacketAllocator : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IRdpPacketAllocator, IBaseInterfaceMT );

public:
  virtual StrongMT<RdpPacket> AllocatePkt( size_t _payloadSize ) = 0;
  virtual void DeallocatePkt( RdpPacket * _pkt ) = 0;
};






class HeapPacketAllocator : public IRdpPacketAllocator, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( HeapPacketAllocator, IRdpPacketAllocator, BaseObjectMT );

public:
  HeapPacketAllocator() {}

  virtual StrongMT<RdpPacket> AllocatePkt( size_t _payloadSize );
  virtual void DeallocatePkt( RdpPacket * _pkt );
};

} //namespace ni_udp

#endif //RUDP_RDPPACKET_H_INCLUDED

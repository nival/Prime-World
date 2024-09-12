#ifndef RUDP_RDPPACKETPOOL_H_INCLUDED
#define RUDP_RDPPACKETPOOL_H_INCLUDED

#include "RdpPacket.h"
#include <vector>
#include <map>


namespace ni_udp
{

class PacketPoolAllocator : public IRdpPacketAllocator, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( PacketPoolAllocator, IRdpPacketAllocator, BaseObjectMT );

public:
  PacketPoolAllocator();

  void CreatePool( size_t _packetsCapacity, size_t _size );

  virtual StrongMT<RdpPacket> AllocatePkt( size_t _payloadSize );
  virtual void DeallocatePkt( RdpPacket * _pkt );

private:
  typedef std::vector<StrongMT<RdpPacket>> Packets;
  
  struct Pool : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( Pool, BaseObjectST );

    size_t    packetsCapacity;
    size_t    size;
    Packets   packets;

    Pool( size_t _packetsCapacity, size_t _size ) :
    packetsCapacity( _packetsCapacity ),
    size( _size )
    {
      packets.reserve( _size );
    }
  };

  typedef std::map<size_t, Strong<Pool>> Pools;

  threading::Mutex  mutex;
  Pools             pools;
};

} //namespace ni_udp

#endif //RUDP_RDPPACKETPOOL_H_INCLUDED

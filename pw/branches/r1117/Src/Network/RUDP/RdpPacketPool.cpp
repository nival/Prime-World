#include "stdafx.h"
#include "RdpPacketPool.h"
#include "System/InlineProfiler.h"


namespace ni_udp
{


PacketPoolAllocator::PacketPoolAllocator()
{
}



void PacketPoolAllocator::CreatePool( size_t _packetsCapacity, size_t _size )
{
  threading::MutexLock lock( mutex );

  Strong<Pool> pool = new Pool( _packetsCapacity, _size );

  pools[_packetsCapacity] = pool;
}



StrongMT<RdpPacket> PacketPoolAllocator::AllocatePkt( size_t _payloadSize )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::MutexLock lock( mutex );

  size_t pktCapacity = RdpPacket::PayloadToCapacity( _payloadSize );

  Pools::iterator it = pools.lower_bound( pktCapacity );
  if ( it != pools.end() )
  {
    Strong<Pool> pool = it->second;

    NI_ASSERT( pool->packetsCapacity >= pktCapacity, "" );

    if ( !pool->packets.empty() )
    {
      StrongMT<RdpPacket> pkt = pool->packets.back();
      pool->packets.pop_back();

      size_t pktCap = pkt->Capacity();
      NI_ASSERT( pktCap == pool->packetsCapacity, "" );

      int pktRefCount = pkt->PktAddRef();
      NI_ASSERT( pktRefCount == 1, "" );

      NI_ASSERT( !pkt->InUse(), "" );
      pkt->SetInUse();
      return pkt;
    }

    NI_ASSERT( pool->packetsCapacity >= _payloadSize, "" );
    pktCapacity = pool->packetsCapacity;
  }

  RdpPacket * pkt = new RdpPacket( pktCapacity );
  pkt->PktAddRef();
  pkt->SetInUse();
  return pkt;
}



void PacketPoolAllocator::DeallocatePkt( RdpPacket * _pkt )
{
  NI_PROFILE_HEAVY_FUNCTION;

  int refcountleft = _pkt->PktReleaseRef();
  NI_ASSERT( refcountleft >= 0, "" );
  
  if ( refcountleft > 0 )
    return;

  threading::MutexLock lock( mutex );

  NI_ASSERT( _pkt->InUse(), "" );
  _pkt->Cleanup();

  Pools::iterator it = pools.lower_bound( _pkt->Capacity() );
  if ( it != pools.end() )
  {
    Strong<Pool> pool = it->second;

    size_t pktCap = _pkt->Capacity();
    NI_ASSERT( pktCap == pool->packetsCapacity, "" );

    if ( pool->packets.size() < pool->size )
    {
      pool->packets.push_back( _pkt );
      return;
    }
  }
}

} //namespace ni_udp

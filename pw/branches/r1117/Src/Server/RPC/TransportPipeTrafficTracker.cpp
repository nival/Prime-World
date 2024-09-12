#include "stdafx.h"
#include "TransportPipeTrafficTracker.h"
#include <RPC/RPC.h>

namespace rpc
{

TransportPipeTrafficTracker::TransportPipeTrafficTracker(StrongMT<NLogg::StreamHolder> const & lsh, 
                                             unsigned int rpcClassCrc, unsigned int rpcMethodIdx, unsigned int methodCallPeriodThreshold)
  :logholder_(lsh),
  rpcClassCrc_(rpcClassCrc),
  rpcMethodIdx_(rpcMethodIdx),
  methodCallPeriodThreshold_(methodCallPeriodThreshold),
  lastCallTime_(0.0)
{
}

TransportPipeTrafficTracker::~TransportPipeTrafficTracker()
{
}

void TransportPipeTrafficTracker::HandlePacket(Transport::ChannelAddr const & caddr, char const * data, size_t len)
{
  rpc::PacketHeader rpcHeaderData;
  if (ParsePacketHeader(data, len, rpcHeaderData))
  {
    if (rpcHeaderData.classCrc == rpcClassCrc_ && rpcHeaderData.methodId == rpcMethodIdx_)
    {
      if (!lastCallTime_)
        lastCallTime_ = NHPTimer::GetScalarTime();

      NHPTimer::FTime current = NHPTimer::GetScalarTime();
      unsigned int deltams = (current - lastCallTime_)*1000;
      lastCallTime_ = NHPTimer::GetScalarTime();
      if (deltams > methodCallPeriodThreshold_)
      {
        localLog(logholder_->logStream(), NLogg::LEVEL_WARNING).Trace("cid=%d rpcClassCrc=0x%x rpcMethodIdx=%d delta=%d len=%d", 
          caddr.client, rpcHeaderData.classCrc, rpcHeaderData.methodId, deltams, len);
      }
    }
  }
  else
  {
    localLog(logholder_->logStream(), NLogg::LEVEL_ERROR).Trace("Can't parse rpc header(cid=%d pipe=%d len=%d)", 
      caddr.client, caddr.pipe, len);
  }
}

}

#include "stdafx.h"
#include "GameSvcTrafficTracker.h"
#include <rpc/RPC.h>

namespace Relay
{

GameSvcTrafficTracker::GameSvcTrafficTracker(StrongMT<NLogg::StreamHolder> const & lsh, 
                                             unsigned int rpcClassCrc, unsigned int rpcMethodIdx, unsigned int methodCallPeriodThreshold)
  :logholder_(lsh),
  rpcClassCrc_(rpcClassCrc),
  rpcMethodIdx_(rpcMethodIdx),
  methodCallPeriodThreshold_(methodCallPeriodThreshold),
  lastCallTime_(0.0)
{
}

GameSvcTrafficTracker::~GameSvcTrafficTracker()
{
}

void GameSvcTrafficTracker::HandlePacket(Transport::ChannelAddr const & caddr, char const * data, size_t len)
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

NI_DEFINE_REFCOUNT( Relay::ITrafficTracker )

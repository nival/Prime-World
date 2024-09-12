#pragma once
#include <System/Pointers/BaseObjectMT.h>
#include <System/LogStreamHolder.h>
#include <Network/TransportUtils.h>

namespace rpc
{
  class TransportPipeTrafficTracker : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( TransportPipeTrafficTracker, BaseObjectMT );

  public:
    TransportPipeTrafficTracker(StrongMT<NLogg::StreamHolder> const & lsh, unsigned int rpcClassCrc, unsigned int rpcMethodIdx, unsigned int methodCallPeriodThreshold);
    ~TransportPipeTrafficTracker();

  public:
    void HandlePacket(Transport::ChannelAddr const & caddr, char const * data, size_t len);

  private:
    StrongMT<NLogg::StreamHolder> logholder_;
    unsigned int rpcClassCrc_;
    unsigned int rpcMethodIdx_;
    unsigned int methodCallPeriodThreshold_;
    NHPTimer::FTime lastCallTime_;
  };
}

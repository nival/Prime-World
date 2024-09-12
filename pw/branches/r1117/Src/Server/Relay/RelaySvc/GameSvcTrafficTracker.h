#pragma once
#include "ITrafficTracker.h"
#include <System/LogStreamHolder.h>

namespace Relay
{

class GameSvcTrafficTracker : public ITrafficTracker, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( GameSvcTrafficTracker, ITrafficTracker, BaseObjectMT );

public:
  GameSvcTrafficTracker(StrongMT<NLogg::StreamHolder> const & lsh, unsigned int rpcClassCrc, unsigned int rpcMethodIdx, unsigned int methodCallPeriodThreshold);
  ~GameSvcTrafficTracker();

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

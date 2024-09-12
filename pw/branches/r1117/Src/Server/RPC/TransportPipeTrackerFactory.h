#pragma once
#include <System/LogStreamHolder.h>
#include "TransportPipeTrafficTracker.h"

namespace rpc
{

class TransportPipeTrafficTrackerFactory : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( TransportPipeTrafficTrackerFactory, BaseObjectMT );

public:
  TransportPipeTrafficTrackerFactory(Transport::TServiceId const & tracksvcls, 
    Transport::TServiceId const & homesvcid,
    unsigned int trackGameSessionRpcClass,
    int trackGameSessionRpcMethodIdx,
    unsigned int trackGameSessionStepPeriodThreshold);
  ~TransportPipeTrafficTrackerFactory();

public:
  virtual StrongMT<TransportPipeTrafficTracker> CreateTrafficTracker();
  virtual void DestroyTrafficTracker(StrongMT<TransportPipeTrafficTracker> const & itt);
  virtual StrongMT<TransportPipeTrafficTrackerFactory> CloneFactory(Transport::TServiceId const & tracksvcid);

private:
  int cloneInit_( TransportPipeTrafficTrackerFactory * ttf, int svcidx);

private:
  Transport::TServiceId tracksvcls_;
  Transport::TServiceId homesvcid_;
  int tracksvcidx_;

  unsigned int trackGameSessionRpcClass_;
  int trackGameSessionRpcMethodIdx_;
  unsigned int trackGameSessionStepPeriodThreshold_;

  StrongMT<NLogg::StreamHolder> logholder_;
};

}

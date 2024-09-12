#pragma once
#include "ITrafficTrackerFactory.h"
#include <System/LogStreamHolder.h>

namespace Relay
{

class GameSvcTrafficTrackerFactory : public ITrafficTrackerFactory, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( GameSvcTrafficTrackerFactory, ITrafficTrackerFactory, BaseObjectMT );

public:
  GameSvcTrafficTrackerFactory(Transport::TServiceId const & tracksvcls, Transport::TServiceId const & relaysvcid);
  ~GameSvcTrafficTrackerFactory();

public:
  virtual StrongMT<ITrafficTracker> CreateTrafficTracker();
  virtual void DestroyTrafficTracker(StrongMT<ITrafficTracker> const & itt);
  virtual StrongMT<ITrafficTrackerFactory> CloneFactory(Transport::TServiceId const & tracksvcid);

private:
  int cloneInit_(StrongMT<GameSvcTrafficTrackerFactory> const & ttf, int svcidx);

private:
  Transport::TServiceId tracksvcls_;
  Transport::TServiceId relaysvcid_;
  int tracksvcidx_;

  StrongMT<NLogg::StreamHolder> logholder_;
};

}

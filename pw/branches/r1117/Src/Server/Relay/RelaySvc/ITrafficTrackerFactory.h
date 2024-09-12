#pragma once
#include "System/Pointers/BaseInterface.h"

namespace Relay
{

class ITrafficTracker;

class ITrafficTrackerFactory : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ITrafficTrackerFactory, IBaseInterfaceMT );

public:
  virtual StrongMT<ITrafficTracker> CreateTrafficTracker() = 0;
  virtual void DestroyTrafficTracker(StrongMT<ITrafficTracker> const & itt) = 0;
  virtual StrongMT<ITrafficTrackerFactory> CloneFactory(Transport::TServiceId const & svcid) = 0;
};

}

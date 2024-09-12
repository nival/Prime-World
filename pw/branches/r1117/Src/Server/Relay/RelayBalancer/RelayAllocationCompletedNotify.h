#pragma once
#include "RelayBalancer/Types.h"

namespace Relay
{
  class AllocationContext;

  class IAllocationCompletedNotify : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IAllocationCompletedNotify, IBaseInterfaceMT );

  public:
    virtual void OnAllocationCompleted(bool _res, StrongMT<AllocationContext> const & _ctx) = 0;
  };
}

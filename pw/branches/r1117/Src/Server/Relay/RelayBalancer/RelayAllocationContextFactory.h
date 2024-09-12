#pragma once
#include "RelayBalancer/RelayAllocationCompletedNotify.h"

namespace Relay
{
  class AllocationContext;
  class SvcContext;
  class UserContext;
  class RIBalancerCallback;
  namespace Balancer
  {
    class Settings;
  }

  class AllocationContextFactory : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( AllocationContextFactory, BaseObjectMT );

    typedef map<AllocCtxIdT, StrongMT<AllocationContext> > AllocCtxsT;

  public:
    AllocationContextFactory ();

  public:
    StrongMT<AllocationContext> alloc(Balancer::Settings const & _settings, StrongMT<UserContext> const & _uctx, Transport::TServiceId const & _svcpath, 
      int _userctx, StrongMT<SvcContext> const & _svctx, StrongMT<SvcContext> const & _secondarysvctx, 
      StrongMT<RIBalancerCallback> const & _cb, StrongMT<IAllocationCompletedNotify> const & _completedcb, GameUserGroupPtr const & _gameusergroup);
    void free(StrongMT<AllocationContext> & ctx);

  private:
    AllocCtxIdT nextallocid;
    AllocCtxsT  allocCtxs;
  };
}

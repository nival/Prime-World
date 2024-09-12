#include "stdafx.h"
#include "RelayBalancer/RelayAllocationContext.h"
#include "RelayBalancer/RelayAllocationContextFactory.h"

NI_DEFINE_REFCOUNT(Relay::AllocationContextFactory);

namespace Relay
{
  AllocationContextFactory::AllocationContextFactory()
    :nextallocid(0)
  {}

  StrongMT<AllocationContext> AllocationContextFactory::alloc(Balancer::Settings const & _settings, StrongMT<UserContext> const & _uctx, Transport::TServiceId const & _svcpath, 
    int _userctx, StrongMT<SvcContext> const & _svctx, StrongMT<SvcContext> const & _secondarysvctx, StrongMT<RIBalancerCallback> const & _cb, 
    StrongMT<IAllocationCompletedNotify> const & _completedcb, GameUserGroupPtr const & _gameusergroup)
  {
    StrongMT<AllocationContext> alloctx(new AllocationContext(_settings, nextallocid++, _uctx, _svcpath, _userctx, 
      _svctx, _secondarysvctx, _cb, _completedcb, _gameusergroup));
    allocCtxs[alloctx->id()] = alloctx;
    return alloctx;
  }

  void AllocationContextFactory::free(StrongMT<AllocationContext> & ctx)
  {
    NI_ASSERT(ctx.Valid(), "");
    if (ctx.Valid())
    {
      NI_ASSERT(AllocationContext::State::CLOSED == ctx->state(), "");

      AllocCtxsT::iterator it = allocCtxs.find(ctx->id());
      NI_ASSERT(it != allocCtxs.end() && it->second == ctx , "");

      if (it != allocCtxs.end() && it->second == ctx)
      {
        allocCtxs.erase(it);
        it = allocCtxs.end();
      }

      LONG volatile * refcount = ctx.GetBaseObject()->RefCountPtr();
      NI_ASSERT(*refcount == 1, "");

      ctx = 0;
    }
  }
}

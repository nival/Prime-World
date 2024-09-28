#include "stdafx.h"
#include "GameBalancer/SvcAllocContext.h"
#include "GameBalancer/SvcContext.h"

NI_DEFINE_REFCOUNT(GameBalancer::SvcAllocContext);

namespace GameBalancer
{
  uint SvcAllocContext::allocgenid = 0;

  SvcAllocContext::SvcAllocContext()
    :id_(0),
    userctx_(0),
    allocid_(0),
    cb(0),
    st(State::INIT),
    allocNotifyWaitStartTime(0)
  {
  }

  SvcAllocContext::SvcAllocContext(Transport::TServiceId const & _svcpath, Peered::TSessionId _userctx, StrongMT<RIBalancerCallback> const & _cb)
    :id_(SvcAllocContext::GenerateCtxId()),
    svcpath(_svcpath),
    userctx_(_userctx),
    allocid_(0),
    cb(_cb),
    st(State::INIT),
    allocNotifyWaitStartTime(0)
  {
  }
}

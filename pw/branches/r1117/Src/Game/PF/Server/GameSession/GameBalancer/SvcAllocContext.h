#pragma once

#include "GameBalancer/GameBalancerIface.h"
#include "RPC/IfaceRequester.h"

namespace GameBalancer
{
  class RIBalancerCallback;

  class SvcAllocContext : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( SvcAllocContext, BaseObjectMT );

    static uint allocgenid;

  public:
    struct State
    {
      enum Enum
      {
        INIT,
        OPENING,
        SERVER_ALLOC_IN_PROGRESS,
        WAIT_FOR_ALLOC_NOTIFY,
        CLOSED
      };
    };

  public:
    SvcAllocContext();
    SvcAllocContext(Transport::TServiceId const & _svcpath, Peered::TSessionId _userctx, StrongMT<RIBalancerCallback> const & _cb);

  public:
    static uint GenerateCtxId();

  public:

    uint id() const
    {
      return id_;
    }

    Peered::TSessionId userctx() const
    {
      return userctx_;
    }

    State::Enum state() const
    {
      return st;
    }

    void state(State::Enum _st)
    {
      st = _st;
    }

    uint allocid() const
    {
      return allocid_;
    }

    void allocid(uint _allocid)
    {
      allocid_ = _allocid;
    }

    Transport::TServiceId svcpath;
    uint id_;
    Peered::TSessionId userctx_;
    uint allocid_;
    StrongMT<RIBalancerCallback> cb;
    State::Enum st;
    NHPTimer::FTime allocNotifyWaitStartTime;
  };

  inline
  uint SvcAllocContext::GenerateCtxId()
  {
    return ++allocgenid;
  }
}

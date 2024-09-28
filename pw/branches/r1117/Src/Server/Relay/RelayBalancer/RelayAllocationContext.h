#pragma once

#include "RelayBalancer/RelayBalancerIface.h"
#include "RPC/IfaceRequester.h"
#include "RelayBalancer/RelayAllocationCompletedNotify.h"
#include "RelayBalancer/RelayBalancerSettings.h"

namespace Relay
{
  class RIBalancerCallback;

  class AllocationContext : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( AllocationContext, BaseObjectMT );

  public:
    struct State
    {
      enum Enum
      {
        CLOSED = -1,
        INIT,
        IN_PROGRESS,
        RELAY_NOTIFIED_PRIMARY,
        RELAY_NOTIFIED_SECONDARY,
        RELAY_NOTIFIED_ALL,
      };
    };

  public:
    AllocationContext(Balancer::Settings const & _settings, AllocCtxIdT const & _id, StrongMT<UserContext> const & _uctx, Transport::TServiceId const & _svcpath, 
      int _customid, StrongMT<SvcContext> const & _svctx, StrongMT<SvcContext> const & _secondarysvctx, 
      StrongMT<RIBalancerCallback> const & _cb, StrongMT<IAllocationCompletedNotify> const & _completedcb, GameUserGroupPtr const & _usergroup);

    int open();
    void close();

  public:

    unsigned int id() const;
    StrongMT<UserContext> const & userctx() const;
    int customid() const;
    State::Enum state() const;
    void state(State::Enum _st);
    SvcContextPtr const & svctx() const;
    SvcContextPtr const & secondarysvctx() const;
    GameUserGroupPtr const & gameusergroup() const;

  protected:

    void relayCallback(bool result, AllocCtxIdT context, rpc::CallStatus status);
    void secondaryRelayCallback(bool result, AllocCtxIdT context, rpc::CallStatus status);

    void allocationCompleted(char const * relaytype, bool result, 
      Transport::TServiceId const & genericrelay, Network::NetAddress const & genericaddr,
      Transport::TServiceId const & gamerelay, Network::NetAddress const & gameaddr);

  private:
    unsigned int id_;
    StrongMT<UserContext> uctx_;
    Transport::TServiceId svcpath;
    int customid_;
    unsigned int allocid;
    StrongMT<SvcContext> svctx_;
    StrongMT<SvcContext> secondarysvctx_;
    StrongMT<RIBalancerCallback> cb;
    State::Enum st;
    NHPTimer::FTime allocNotifyWaitStartTime;
    StrongMT<IAllocationCompletedNotify> completedcb;

    Balancer::Settings const & settings_;
    GameUserGroupPtr gameusergroup_;
  };

  inline
  unsigned int AllocationContext::id() const
  {
    return id_;
  }

  inline
  StrongMT<UserContext> const & AllocationContext::userctx() const
  {
    return uctx_;
  }

  inline
  int AllocationContext::customid() const
  {
    return customid_;
  }

  inline
  AllocationContext::State::Enum AllocationContext::state() const
  {
    return st;
  }

  inline
  void AllocationContext::state(State::Enum _st)
  {
    st = _st;
  }

  inline
  SvcContextPtr const & AllocationContext::svctx() const
  {
    return svctx_;
  }

  inline
  SvcContextPtr const & AllocationContext::secondarysvctx() const
  {
    return secondarysvctx_;
  }

  inline
  GameUserGroupPtr const & AllocationContext::gameusergroup() const
  {
    return gameusergroup_;
  }
}

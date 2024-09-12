#include "stdafx.h"
#include "RelayBalancer/RelayAllocationContext.h"
#include "RelayBalancer/RelaySvcContext.h"
#include "RelayBalancer/RRelayBalancerIface.auto.h"
#include "RelayBalancer/RRelayBalancerClientNotifyIface.auto.h"
#include "RelayBalancer/RelayBalancerGameUserGroup.h"

NI_DEFINE_REFCOUNT(Relay::AllocationContext);

namespace Relay
{
  AllocationContext::AllocationContext(Balancer::Settings const & _settings, AllocCtxIdT const & _id, StrongMT<UserContext> const & _uctx, 
    Transport::TServiceId const & _svcpath, int _customid, StrongMT<SvcContext> const & _svctx, StrongMT<SvcContext> const & _secondarysvctx,
    StrongMT<RIBalancerCallback> const & _cb, StrongMT<IAllocationCompletedNotify> const & _completedcb, GameUserGroupPtr const & _gameusergroup)
    :id_(_id),
    uctx_(_uctx),
    svcpath(_svcpath),
    customid_(_customid),
    svctx_(_svctx),
    secondarysvctx_(_secondarysvctx),
    st(State::INIT),
    allocNotifyWaitStartTime(0),
    cb(_cb),
    completedcb(_completedcb),
    settings_(_settings),
    gameusergroup_(_gameusergroup)
  {
  }

  int AllocationContext::open()
  {
    NI_ASSERT(State::INIT == state(), "");

    int rc = -1;

    if (svctx_)
    {
      StrongMT<Relay::RIIncomingClientNotifySink> notifier =  svctx_->relayNotifySink();
      if (notifier)
      {
        if (secondarysvctx_)
        {
          StrongMT<Relay::RIIncomingClientNotifySink> gnotifier =  secondarysvctx_->relayNotifySink();
          if (gnotifier)
          {
            if (0 == svctx_->addUserCtx(uctx_))
            {
              if (0 == secondarysvctx_->addUserCtx(uctx_))
              {
                notifier->IncomingClientNotify(uctx_->userid(), "", this, &AllocationContext::relayCallback, 
                  id_, settings_.incomingClientNotifyTimeout());
                gnotifier->IncomingClientNotify(uctx_->userid(), "", this, &AllocationContext::secondaryRelayCallback, 
                  id_, settings_.incomingClientNotifyTimeout());

                if (gameusergroup_)
                  gameusergroup_->attachUser(uctx_);

                rc = 0;
              }
              else
              {
                svctx_->removeUserCtx(uctx_->userid());
              }
            }
          }
          else
          {
            LOG_E(RBLOG).Trace("%s: Relay svc is found, but is not available(svcpath=%s svcid=%s userid=%d)", 
              __FUNCTION__, svcpath.c_str(), secondarysvctx_->svcid().c_str(), uctx_->userid());
          }
        }
        else
        {
          if (0 == svctx_->addUserCtx(uctx_))
          {
            notifier->IncomingClientNotify(uctx_->userid(), "", this, &AllocationContext::relayCallback, 
              id_, settings_.incomingClientNotifyTimeout());

            if (gameusergroup_)
              gameusergroup_->attachUser(uctx_);

            rc = 0;
          }
        }
      }
      else
      {
        LOG_E(RBLOG).Trace("%s: generic relay interface is NULL(svcpath=%s svcid=%s svcaddr=%s userid=%d)", 
          __FUNCTION__, svcpath.c_str(), svctx_->svcid().c_str(), svctx_->frontendAddr().c_str(), uctx_->userid());
      }
    }
    else
    {
      if (secondarysvctx_)
      {
        StrongMT<Relay::RIIncomingClientNotifySink> gnotifier =  secondarysvctx_->relayNotifySink();
        if (gnotifier)
        {
          if (0 == secondarysvctx_->addUserCtx(uctx_))
          {
            gnotifier->IncomingClientNotify(uctx_->userid(), "", this, &AllocationContext::secondaryRelayCallback, 
              id_, settings_.incomingClientNotifyTimeout());

            if (gameusergroup_)
              gameusergroup_->attachUser(uctx_);

            rc = 0;
          }
        }
      }
    }

    if (rc < 0)
      state(State::CLOSED);
    else
      state(State::IN_PROGRESS);

    return rc;
  }

  void AllocationContext::close()
  {
    if (State::CLOSED == state())
      return;

    state(State::CLOSED);
  }

  void AllocationContext::relayCallback(bool result, AllocCtxIdT context, rpc::CallStatus status)
  {
    NI_ASSERT(id_ == context, "");

    if (state() < 0)
      return;

    if (status != rpc::CallSuccessful)
    {
      LOG_E(RBLOG).Trace("%s: rpc call timeout/disconnect(sts=%d svcpath=%s relay=%s relayaddr=%s userid=%d)", 
        __FUNCTION__, (int)status, svcpath.c_str(), svctx_->svcid().c_str(), svctx_->frontendAddr().c_str(), uctx_->userid());

      result = false;
      svctx_->incRelayAllocationFailedCount();
    }
    else
    {
      svctx_->resetRelayAllocationFailedCount();
    }

    NI_ASSERT(state() == State::IN_PROGRESS || 
              state() == State::RELAY_NOTIFIED_SECONDARY, "");

    if (result)
    {
      if (State::IN_PROGRESS == state())
      {
        state(State::RELAY_NOTIFIED_PRIMARY);
        if (!secondarysvctx_)
        {
          allocationCompleted("generic-relay", true, svctx_->localFrontendsvcid(), svctx_->frontendAddr(), 
            svctx_->localFrontendsvcid(), svctx_->frontendAddr());
        }
        else
        {
          LOG_M(RBLOG).Trace("%s: generic relay confirmation received, wait for secondary relay confirmation(svcpath=%s relay=%s relayaddr=%s secondaryrelay=%s secondaryrelayaddr=%s userid=%d)", 
            __FUNCTION__, svcpath.c_str(), svctx_->svcid().c_str(), svctx_->frontendAddr().c_str(), 
            secondarysvctx_->svcid().c_str(), secondarysvctx_->frontendAddr().c_str(), uctx_->userid());
        }
      }
      else
      if (State::RELAY_NOTIFIED_SECONDARY == state())
      {
        allocationCompleted("generic-relay", true, svctx_->localFrontendsvcid(), svctx_->frontendAddr(), 
          secondarysvctx_->localFrontendsvcid(), secondarysvctx_->frontendAddr());
      }
    }
    else
    {
      svctx_->removeUserCtx(uctx_->userid());

      if (State::IN_PROGRESS == state())
      {
        if (!secondarysvctx_)
        {
          allocationCompleted("generic-relay", false, Transport::EmptySvcId, "", Transport::EmptySvcId, "");
        }
        else
        {
          LOG_M(RBLOG).Trace("%s: generic relay confirmation received(FAIL), wait for secondary relay confirmation(svcpath=%s relay=%s relayaddr=%s gamerelay=%s gamerelayaddr=%s userid=%d)", 
            __FUNCTION__, svcpath.c_str(), svctx_->svcid().c_str(), svctx_->frontendAddr().c_str(), 
            secondarysvctx_->svcid().c_str(), secondarysvctx_->frontendAddr().c_str(), uctx_->userid());
        }
      }
      else
      if (State::RELAY_NOTIFIED_SECONDARY == state())
      {
        allocationCompleted("generic-relay", false, Transport::EmptySvcId, "", Transport::EmptySvcId, "");
      }
    }
  }

  void AllocationContext::secondaryRelayCallback(bool result, AllocCtxIdT context, rpc::CallStatus status)
  {
    NI_ASSERT(id_ == context, "");

    if (state() < 0)
      return;

    if (status != rpc::CallSuccessful)
    {
      LOG_E(RBLOG).Trace("%s: rpc call timeout/disconnect(sts=%d svcpath=%s gamerelay=%s gamerelayaddr=%s userid=%d)", 
        __FUNCTION__, (int)status, svcpath.c_str(), secondarysvctx_->svcid().c_str(), secondarysvctx_->frontendAddr().c_str(), uctx_->userid());

      result = false;

      secondarysvctx_->incRelayAllocationFailedCount();
    }
    else
    {
      secondarysvctx_->resetRelayAllocationFailedCount();
    }

    NI_ASSERT(state() == State::IN_PROGRESS || 
              state() == State::RELAY_NOTIFIED_PRIMARY, "");

    if (result)
    {
      if (svctx_)
      {
        if (State::IN_PROGRESS == state())
        {
          state(State::RELAY_NOTIFIED_SECONDARY);

          LOG_M(RBLOG).Trace("%s: secondary-relay allocation confirmed(svcpath=%s secondaryrelay=%s secondaryrelayaddr=%s userid=%d)", 
            __FUNCTION__, svcpath.c_str(), secondarysvctx_->svcid().c_str(), secondarysvctx_->frontendAddr().c_str(), uctx_->userid());
        }
        else
        if (State::RELAY_NOTIFIED_PRIMARY == state())
        {
          allocationCompleted("secondary-relay", true, (svctx_ ? svctx_->localFrontendsvcid() : Transport::EmptySvcId), (svctx_ ? svctx_->frontendAddr() : ""), 
            secondarysvctx_->localFrontendsvcid(), secondarysvctx_->frontendAddr());
        }
        else
        {
          NI_ALWAYS_ASSERT("WTF");
        }
      }
      else
      {
        NI_ASSERT(State::IN_PROGRESS == state(), "Wrong state");
        state(State::RELAY_NOTIFIED_SECONDARY);
        allocationCompleted("secondary-relay", true, (svctx_ ? svctx_->localFrontendsvcid() : Transport::EmptySvcId), (svctx_ ? svctx_->frontendAddr() : ""), 
          secondarysvctx_->localFrontendsvcid(), secondarysvctx_->frontendAddr());
      }
    }
    else
    {
      secondarysvctx_->removeUserCtx(uctx_->userid());

      if (svctx_)
      {
        if (State::IN_PROGRESS == state())
        {
          state(State::RELAY_NOTIFIED_SECONDARY);
          LOG_M(RBLOG).Trace("%s: secondary-relay allocation confirmed(FAIL)(svcpath=%s secondaryrelay=%s secondaryrelayaddr=%s userid=%d)", 
            __FUNCTION__, svcpath.c_str(), secondarysvctx_->svcid().c_str(), secondarysvctx_->frontendAddr().c_str(), uctx_->userid());
        }
        else
        if (State::RELAY_NOTIFIED_PRIMARY == state())
        {
          allocationCompleted("secondary-relay", false, Transport::EmptySvcId, "", Transport::EmptySvcId, "");
        }
        else
        {
          NI_ALWAYS_ASSERT("WTF");
        }
      }
      else
      {
        NI_ASSERT(State::IN_PROGRESS == state(), "Wrong state");
        state(State::RELAY_NOTIFIED_SECONDARY);
        allocationCompleted("secondary-relay", false, Transport::EmptySvcId, "", Transport::EmptySvcId, "");
      }
    }
  }

  void AllocationContext::allocationCompleted(char const * relaytype, bool result, 
    Transport::TServiceId const & genericrelay, Network::NetAddress const & genericaddr,
    Transport::TServiceId const & gamerelay, Network::NetAddress const & gameaddr)
  {
    if (result)
      LOG_M(RBLOG).Trace("%s allocation completed(userid=%d svcpath=%s relay=%s relayaddr=%s gamerelay=%s gamerelayaddr=%s game=%s)", 
        relaytype, uctx_->userid(), svcpath.c_str(), genericrelay.c_str(), genericaddr.c_str(), 
        gamerelay.c_str(), gameaddr.c_str(), (gameusergroup() ? gameusergroup()->fmtid() : ""));
    else
      LOG_E(RBLOG).Trace("%s allocation FAILED(userid=%d svcpath=%s relay=%s relayaddr=%s gamerelay=%s gamerelayaddr=%s game=%s)", 
        relaytype, uctx_->userid(), svcpath.c_str(), genericrelay.c_str(), genericaddr.c_str(), 
        gamerelay.c_str(), gameaddr.c_str(), (gameusergroup() ? gameusergroup()->fmtid() : ""));

    state(State::RELAY_NOTIFIED_ALL);
    cb->OnRelayAllocated(uctx_->userid(), customid_, genericrelay, genericaddr, gamerelay, gameaddr);
    completedcb->OnAllocationCompleted(result, this);
  }
}

#include "stdafx.h"
#include "RelayBalancer/RelaySvcContext.h"
#include "RelaySvc/RelaySvcNaming.h"
#include "Network/AddressTranslator.h"
#include "RelayBalancer/RelaySvcContextNotity.h"
#include "RelayBalancer/RelayBalancerUserContext.h"

NI_DEFINE_REFCOUNT(Relay::SvcContext);

namespace Relay
{
  SvcContext::SvcContext(Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & role, ISvcContextNotify * cb)
    :svcid_(_svcid),
    svcrole_(role),
    notifyCallback_(cb),
    st(State::INIT),
    usersConnectTimeoutExpiredCount_(0),
    relayAllocationFailedCount_(0),
    offlineTimeStart_(0.0)
  {
    if (!Transport::GetLocalServiceId(svcid_, localsvcid_))
    {
      LOG_E(RBLOG).Trace("Can't get local service id(svcid=%s)", svcid_.c_str());
    }

    Transport::GetServicePath(svcid_, svcpath_);

    //  init frontend svcid
    int serviceIdx = Transport::GetServerIndex(svcid_);
    Transport::GenerateServiceName(Transport::ENetInterface::FrontEnd, serviceIdx, &frontendsvcid_);
    Transport::GetLocalServiceId(frontendsvcid_, localFrontendsvcid_);

    relayNotifier = new rpc::IfaceRequester<Relay::RIIncomingClientNotifySink>;
  }



  int SvcContext::open( rpc::GateKeeper * _gk, Transport::IAddressTranslator * _addrResolver, NLogg::CChannelLogger* _logstrm, char const * _chnlName )
  {
    LOG_M(RBLOG).Trace("%s(svcid=%s svccu=%d)", __FUNCTION__, svcid_.c_str(), ccu());

    int rc = -1;
    if (isstate_(State::OPENING) || isstate_(State::OPENED) || isstate_(State::REOPENING))
    {
      LOG_W(RBLOG).Trace("Context is already in opening/ed state(svcid=%s st=%d)", svcid_.c_str(), (int)st);
      rc = 1;
      return rc;
    }

    addrResolver = _addrResolver;

    rc = relayNotifier->init(_gk, localsvcid_, Relay::IncomingClientNotifierRpcIface, _logstrm, _chnlName, this, 1.0);
    if (rc >= 0)
    {
      rc = 0;

      frontendAddr_ = addrResolver->GetSvcAddress( localsvcid() );
      if (!frontendAddr_.empty())
      {
        LOG_M(RBLOG).Trace("Frontend network address resolved(svcid=%s frontendid=%s frontendaddr=%s)",
          svcid_.c_str(), frontendsvcid_.c_str(), frontendAddr_.c_str());
      }

      state_(State::OPENING);
    }
    else
    {
      LOG_E(RBLOG).Trace("Can't init iface requester(svcid=%s iface=%s)", 
        localsvcid_.c_str(), Relay::IncomingClientNotifierRpcIface);
    }

    if (rc < 0)
      close();

    return rc;
  }

  void SvcContext::close()
  {
    LOG_M(RBLOG).Trace("%s(svcid=%s svcaddr=%s svccu=%d)", __FUNCTION__, svcid_.c_str(), frontendAddr_.c_str(), ccu());

    if (isstate_(State::CLOSED))
      return;

    LOG_M(RBLOG).Trace("Close svc context(svcid=%s svcaddr=%s svccu=%d)", svcid_.c_str(), frontendAddr_.c_str(), ccu());

    state_(State::CLOSED);

    UserContextsT::iterator it = users_.begin();
    while(it != users_.end())
    {
      DetachUserFromSvc_(it->second);
      it = users_.erase(it);
    }

    if (relayNotifier)
    {
      relayNotifier->close();
    }
  }

  void SvcContext::step()
  {
    if (isstate_(State::CLOSED) || isstate_(State::INIT))
      return;

    relayNotifier->step();

    if (relayNotifier->isopen())
    {
      if (frontendAddr_.empty())
      {
        frontendAddr_ = addrResolver->GetSvcAddress( localsvcid() );
        if (!frontendAddr_.empty())
        {
          LOG_M(RBLOG).Trace("Frontend network address resolved(svcid=%s frontendid=%s frontendaddr=%s)",
            svcid_.c_str(), frontendsvcid_.c_str(), frontendAddr_.c_str());

          if (!isstate_(State::OPENED))
          {
            relayNotifier->iface()->RegisterOutgoingClientNotifySink(RemotePtr<Relay::RIOutgoingClientNotifySink>(this), 
                                                                     this, &SvcContext::OnReturn_RegisterOutgoingClientNotifySink);
            state_(State::OPENED);
            LOG_M(RBLOG).Trace("%s: service context is OPENED(svcid=%s)", __FUNCTION__, svcid_.c_str());
          }
        }
      }
      else
      {
        if (!isstate_(State::OPENED))
        {
          relayNotifier->iface()->RegisterOutgoingClientNotifySink(RemotePtr<Relay::RIOutgoingClientNotifySink>(this), 
                                                                   this, &SvcContext::OnReturn_RegisterOutgoingClientNotifySink);
        }
      }
    }
    else
    {
      NI_ASSERT(isstate_(State::REOPENING) || isstate_(State::OPENING), "");
      if (!isstate_(State::REOPENING) && !isstate_(State::OPENING))
      {
        LOG_A(RBLOG).Trace("%s: state must be OPENING or REOPENING(svcid=%s st=%d)", 
          __FUNCTION__, svcid_.c_str(), (int)state_());
      }
    }
  }

  void SvcContext::OnReturn_RegisterOutgoingClientNotifySink(int _rc)
  {
    LOG_M(RBLOG).Trace("%s(res=%d svcid=%s)", __FUNCTION__, _rc, svcid_.c_str());

    if (_rc >= 0)
    {
      ccu((uint)_rc);
      state_(State::OPENED);

      LOG_M(RBLOG).Trace("%s: service context is OPENED(svcid=%s ccu=%d)", __FUNCTION__, svcid_.c_str(), _rc);
    }
    else
    {
      state_(State::CLOSED);
    }
  }

  void SvcContext::OutgoingClientNotify(Transport::TClientId _clientid, int _reason)
  {
    LOG_M(RBLOG).Trace("%s(u=%d reason=%d svcid=%s svcaddr=%s)", 
      __FUNCTION__, _clientid, _reason, svcid_.c_str(), frontendAddr_.c_str());

    if (OutgoingClientReason::ConnectTimeoutExpired == _reason)
      ++usersConnectTimeoutExpiredCount_;

    DetachUserFromSvc_(_clientid);
  }

  void SvcContext::ClientConnectedNotify(Transport::TClientId _clientid)
  {
    LOG_M(RBLOG).Trace("%s(u=%d svcid=%s svcaddr=%s)", __FUNCTION__, _clientid, svcid_.c_str(), frontendAddr_.c_str());

    usersConnectTimeoutExpiredCount_ = 0;
  }

  int SvcContext::addUserCtx(StrongMT<UserContext> const & uctx)
  {
    LOG_M(RBLOG).Trace("%s(u=%d svcid=%s svcaddr=%s)", __FUNCTION__, uctx->userid(), svcid_.c_str(), frontendAddr_.c_str());

    int rc = -1;
    if (users_.insert(make_pair(uctx->userid(), uctx)).second)
    {
      inccu();
      if (extCounter_)
        extCounter_->inccu();
      uctx->incrementCount();
      rc = 0;

      LOG_M(RBLOG).Trace("User added successfully(u=%d ucnt=%d svcid=%s svcaddr=%s svccu=%d)", 
        uctx->userid(), uctx->count(), svcid().c_str(), frontendAddr_.c_str(), ccu());
    }
    else
    {
      LOG_E(RBLOG).Trace("%s: user already exists(u=%d svcid=%s svcaddr=%s)", __FUNCTION__, uctx->userid(), svcid_.c_str(), frontendAddr_.c_str());
    }
    return rc;
  }

  int SvcContext::removeUserCtx(Transport::TClientId const & userid)
  {
    LOG_M(RBLOG).Trace("%s(u=%d svcid=%s svcaddr=%s)", __FUNCTION__, userid, svcid_.c_str(), frontendAddr_.c_str());

    return DetachUserFromSvc_(userid);
  }

  void SvcContext::DetachUserFromSvc_(StrongMT<UserContext> const & uctx)
  {
    LOG_M(RBLOG).Trace("%s(u=%d ucnt=%d svcid=%s svcaddr=%s svccu=%d)", __FUNCTION__, uctx->userid(), uctx->count(), svcid_.c_str(), frontendAddr_.c_str(), ccu());

    deccu();
    if (extCounter_)
      extCounter_->deccu();
    uctx->decrementCount();
    notifyCallback_->OnUserLeaveSvc(svcid_, svcrole_, uctx);
  }

  int SvcContext::DetachUserFromSvc_(uint _userid)
  {
    LOG_M(RBLOG).Trace("%s(u=%d svcid=%s svcaddr=%s svccu=%d)", __FUNCTION__, _userid, svcid_.c_str(), frontendAddr_.c_str(), ccu());

    int rc = -1;
    UserContextsT::iterator it = users_.find(_userid);
    if (it != users_.end())
    {
      StrongMT<UserContext> uctx = it->second;
      DetachUserFromSvc_(uctx);
      users_.erase(it);
      rc = 0;

      LOG_M(RBLOG).Trace("User removed successfully(u=%d ucnt=%d svcid=%s svcaddr=%s svccu=%d)", 
        uctx->userid(), uctx->count(), svcid_.c_str(), frontendAddr_.c_str(), ccu());
    }
    else
    {
      deccu();
      if (extCounter_)
        extCounter_->deccu();

      LOG_E(RBLOG).Trace("%s: user NOT_FOUND(u=%d svcid=%s svcaddr=%s svccu=%d)", __FUNCTION__, _userid, svcid_.c_str(), frontendAddr_.c_str(), ccu());
    }
    return rc;
  }

  void SvcContext::onChangeState(rpc::IfaceRequesterState::Enum ifacest,
                                 StrongMT<rpc::IfaceRequester<Relay::RIIncomingClientNotifySink> > const & ifacereq)
  {
    if (rpc::IfaceRequesterState::CLOSED == ifacest)
    {
      LOG_W(RBLOG).Trace("incomingClientNotify interface is CLOSED(svcid=%s svcaddr=%s st=%d)", svcid_.c_str(), frontendAddr_.c_str(), (int)state_());
      if (!isstate_(State::CLOSED))
        state_(State::REOPENING);
    }
  }

  int SvcContext::reopen()
  {
    LOG_M(RBLOG).Trace("%s(svcid=%s svcaddr=%s svccu=%d)", __FUNCTION__, svcid_.c_str(), frontendAddr_.c_str(), ccu());

    if (!isstate_(State::OPENED))
    {
      LOG_W (RBLOG).Trace("%s: service context is NOT OPENED(svcid=%s svcaddr=%s state=%d)", 
        __FUNCTION__, svcid_.c_str(), frontendAddr_.c_str(), (int)state_());
      return -1;
    }

    relayNotifier->close();
    return 0;
  }



  StrongMT<Relay::RIIncomingClientNotifySink> SvcContext::relayNotifySink() const
  {
    if (relayNotifier->isopen())
      return relayNotifier->iface();
    else
      return 0;
  }



  void SvcContext::state_(SvcContext::State::Enum _st)
  {
    if (st != _st)
    {
      if (State::OPENED == _st)
        resetOfflineTimeStart();

      if (State::REOPENING == _st)
        initOfflineTimeStart();
    }

    st  = _st;
  }



  int SvcContext::externalCCUCounter(StrongMT<ICCUCounter> const & counter)
  {
    if (!extCounter_)
    {
      extCounter_ = counter;
      return 0;
    }

    return -1;
  }
}

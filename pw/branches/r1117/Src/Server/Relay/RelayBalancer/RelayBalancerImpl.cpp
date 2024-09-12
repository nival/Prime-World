#include "stdafx.h"
#include "RelayBalancer/RelayBalancerImpl.h"
#include "RelayBalancer/RelaySvcContext.h"
#include "RelayBalancer/RelayAllocationContext.h"
#include "RelayBalancer/RRelayBalancerIface.auto.h"
#include "UserManager/UserManagerSvc/RUserManagerIface.auto.h"
#include "UserManager/UserManagerSvc/UserManagerNaming.h"
#include <Coordinator/CoordinatorServerNaming.h>
#include "RelaySvc/RelaySvcNaming.h"
#include "RelayBalancer/RelayBalancerSettings.h"
#include "RelayBalancer/RelayBalancerGameContext.h"

NI_DEFINE_REFCOUNT(Relay::BalancerImpl);

namespace Relay
{
  BalancerImpl::BalancerImpl(Balancer::Settings const & _settings, rpc::GateKeeper * _gk, Transport::IAddressTranslator* _addrResolver)
    :gk(_gk),
    addrResolver(_addrResolver),
    settings_(_settings)
  {
    NI_ASSERT(addrResolver, "");
    allocCtxFactory.Set(new AllocationContextFactory);

    userMngrIface_ = new rpc::IfaceRequester<UserManager::RIUserManager>;
    int rc = userMngrIface_->init(gk, UserManager::ServiceClass, UserManager::ServiceRpcIface, &GetSystemLog(), RBLOG);
    if (rc < 0)
    {
      LOG_A(RBLOG).Trace("Can't init rpc iface requester(node=%s iface=%s)", UserManager::ServiceClass.c_str(),
        UserManager::ServiceRpcIface);
    }

    svcPublisherIface_ = new rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>;
    rc = svcPublisherIface_->init(gk, Transport::ENetInterface::Coordinator, Coordinator::SvcAppearancePublisherIfaceId, 
      &GetSystemLog(), RBLOG, this);
    if (rc < 0)
    {
      LOG_A(RBLOG).Trace("Can't init rpc iface requester(node=%s iface=%s)", Transport::ENetInterface::Coordinator.c_str(),
        Coordinator::SvcAppearancePublisherIfaceId);
    }
  }

  BalancerImpl::~BalancerImpl()
  {
    allocCtxFactory = 0;
  }

  int BalancerImpl::AllocateRelay(Cluster::TGameId gameid, Transport::TClientId clientid, Transport::TServiceId const & svcpath, Coordinator::TServiceRole const & _svcrole, 
    int userctx, Relay::IBalancerCallback* cb)
  {
    LOG_M(RBLOG).Trace("Allocate relay(gameid=%s userid=%d svcpath=%s svcrole=%s userctx=%d mode=%s)", 
      Cluster::FmtGameId(gameid), clientid, svcpath.c_str(), _svcrole.c_str(), userctx, Balancer::RelayAllocationMode::ToString(settings_.relayAllocationMode()));

    int rc = -1;
    if (!svcContexts.size())
    {
      LOG_W(RBLOG).Trace("Can't allocate svc: no registered services(svcpath=%s userctx=%d mode=%s)", 
        svcpath.c_str(), userctx, Balancer::RelayAllocationMode::ToString(settings_.relayAllocationMode()));
      return rc;
    }

    if (Cluster::INVALID_GAME_ID != gameid)
    {
      rc = AllocateGameSpecificRelay_(gameid, clientid, svcpath, _svcrole, userctx, cb);
    }
    else
    {
      rc =  AllocateRelay_(clientid, svcpath, _svcrole, userctx, cb);
    }

    return rc;
  }

  int BalancerImpl::AllocateRelay_(Transport::TClientId _clientid, Transport::TServiceId const & _svcpath, Coordinator::TServiceRole const & _svcrole, int _userctx, Relay::IBalancerCallback* _cb, StrongMT<GameContext> const & _gamectx)
  {
    int rc = -1;

    bool bOnlySecondary = false;
    if (Coordinator::SecondarySvcRole == _svcrole)
      bOnlySecondary = true;

    GameUserGroupPtr gameusergroup;
    Transport::TServiceId exceptedPrimaryRelaySvcid;
    Transport::TServiceId exceptedSecondaryRelaySvcid;
    if (_gamectx)
    {
      gameusergroup = _gamectx->selectGroup4relayAllocation();
      SvcContextPtr const & exceptedPrimaryRelay = _gamectx->getExceptedPrimaryRelay4Group(gameusergroup);
      if (exceptedPrimaryRelay)
        exceptedPrimaryRelaySvcid = exceptedPrimaryRelay->svcid();

      SvcContextPtr const & exceptedSecondaryRelay = _gamectx->getExceptedPrimaryRelay4Group(gameusergroup);
      if (exceptedSecondaryRelay)
        exceptedSecondaryRelaySvcid = exceptedSecondaryRelay->svcid();
    }

    StrongMT<SvcContext> svctx;
    if (!bOnlySecondary)
    {
      svctx = findPrimaryRelay(_svcpath, gameusergroup, exceptedPrimaryRelaySvcid);
      if (!svctx)
      {
        LOG_E(RBLOG).Trace("Can't allocate relay: no appropriate service found(svcpath=%s userctx=%d mode=%s)", 
          _svcpath.c_str(), _userctx, Balancer::RelayAllocationMode::ToString(settings_.relayAllocationMode()));
        return rc;
      }
    }

    StrongMT<SvcContext> secondarysvctx;
    if (Balancer::RelayAllocationMode::primary_relays_only != settings_.relayAllocationMode())
    {
      secondarysvctx = findSecondaryRelay(_svcpath, gameusergroup, exceptedSecondaryRelaySvcid);
      if (!secondarysvctx)
      {
        if (Balancer::RelayAllocationMode::secondary_relays_mandatory == settings_.relayAllocationMode())
        {
          LOG_E(RBLOG).Trace("Can't allocate secondary-relay: no appropriate service found(svcpath=%s userctx=%d mode=%s)", 
            _svcpath.c_str(), _userctx, Balancer::RelayAllocationMode::ToString(settings_.relayAllocationMode()));
          return rc;
        }
        else
        {
          LOG_W(RBLOG).Trace("Can't allocate secondary-relay: no appropriate service found(svcpath=%s userctx=%d mode=%s)", 
            _svcpath.c_str(), _userctx, Balancer::RelayAllocationMode::ToString(settings_.relayAllocationMode()));
        }
      }
    }

    StrongMT<UserContext> uctx;
    UsersT::const_iterator it = users_.find(_clientid);
    if (it != users_.end())
      uctx.Set(it->second);
    else
      uctx.Set(new UserContext(_clientid));

    return startRelayAllocation(settings_, uctx, _svcpath, _userctx, svctx, secondarysvctx, static_cast<RIBalancerCallback*>(_cb), gameusergroup);
  }

  int BalancerImpl::AllocateGameSpecificRelay_(Cluster::TGameId _gameid, Transport::TClientId _clientid, Transport::TServiceId const & _svcpath, 
    Coordinator::TServiceRole const & _svcrole, int _userctx, Relay::IBalancerCallback* _cb)
  {
    StrongMT<GameContext> gctx;
    GameCtxsT::const_iterator cit = games_.find(_gameid);
    if (games_.end() == cit)
    {
      gctx.Set(new GameContext(_gameid));
      games_[_gameid] = gctx;
    }
    else
      gctx = cit->second;

    return AllocateRelay_(_clientid, _svcpath, _svcrole, _userctx, _cb, gctx);
  }

  void BalancerImpl::AddService(Transport::TServiceId const & svcid, Coordinator::TServiceRole const & role)
  {
    LOG_M(RBLOG).Trace("%s(svcid=%s role=%s)", __FUNCTION__, svcid.c_str(), role.c_str());

    Transport::TServiceId svcpath = Transport::GetServicePath(svcid);
    StrongMT<SvcContext> svctx = registerService(svcpath, svcid, role);
    if (svctx)
    {
      int rc = svctx->open(gk, addrResolver, &GetSystemLog(), RBLOG);
      if (rc < 0)
      {
        LOG_E(RBLOG).Trace("Can't open service context(svcid=%s role=%s)", svcid.c_str(), role.c_str());
      }
      else
      if (rc > 0)
      {
        LOG_W(RBLOG).Trace("Service already registered(svcid=%s role=%s)", svcid.c_str(), role.c_str());
      }
      else
      {
        LOG_M(RBLOG).Trace("Service registered(svcid=%s role=%s)", svcid.c_str(), role.c_str());
      }
    }
    else
    {
      LOG_E(RBLOG).Trace("Service registration FAILED(svcid=%s)", svcid.c_str());
    }
  }

  void BalancerImpl::RemoveService( Transport::TServiceId const & svcid )
  {
    LOG_M(RBLOG).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

    StrongMT<SvcContext> svctx = unregisterService(svcid);
    if (svctx)
    {
      svctx->close();
      LOG_M(RBLOG).Trace("Service unregistered successfully(svcid=%s role=%s)", svcid.c_str(), svctx->svcrole().c_str());
    }
    else
    {
      LOG_W(RBLOG).Trace("Can't unregister service(svcid=%s)", svcid.c_str());
    }
  }

  StrongMT<SvcContext> BalancerImpl::registerService(Transport::TServiceId const & svcpath, 
    Transport::TServiceId const & svcid, Coordinator::TServiceRole const & role)
  {
    LOG_M(RBLOG).Trace("%s(svcpath=%s svcid=%s role=%s)", __FUNCTION__, svcpath.c_str(), svcid.c_str(), role.c_str());

    StrongMT<SvcContext> svctx;
    for(SvcContextListT::iterator it = registeredSvcCtxs.begin(); it != registeredSvcCtxs.end(); ++it)
    {
      StrongMT<SvcContext> const & ctx = *it;
      if (ctx->svcid() == svcid)
      {
        if (ctx->isclosed())
        {
          LOG_W(RBLOG).Trace("%s: remove closed svc(svcid=%s role=%s)", __FUNCTION__, ctx->svcid().c_str(), ctx->svcrole().c_str());
          registeredSvcCtxs.erase(it);
        }
        else
        {
          LOG_W(RBLOG).Trace("%s: svc already registered(svcid=%s role=%s)", __FUNCTION__, ctx->svcid().c_str(), ctx->svcrole().c_str());
          svctx = ctx;
        }
        break;
      }
    }

    if (!svctx)
    {
      svctx = new SvcContext(svcid, role, this);
      registeredSvcCtxs.push_back(svctx);
      initSvcCtxs.push_back(svctx);

      LOG_M(RBLOG).Trace("%s: new svc registered(svcpath=%s svcid=%s role=%s)", __FUNCTION__, svcpath.c_str(), svcid.c_str(), role.c_str());
    }

    return svctx;
  }

  StrongMT<SvcContext> BalancerImpl::unregisterService(Transport::TServiceId const & svcid)
  {
    LOG_M(RBLOG).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

    StrongMT<SvcContext> svctx;

    for(SvcContextListT::iterator lit = initSvcCtxs.begin(); lit != initSvcCtxs.end(); ++lit)
    {
      if ((*lit)->svcid() == svcid)
      {
        initSvcCtxs.erase(lit);
        break;
      }
    }

    for(SvcContextListT::iterator lit = registeredSvcCtxs.begin(); lit != registeredSvcCtxs.end(); ++lit)
    {
      if ((*lit)->svcid() == svcid)
      {
        svctx = *lit;
        registeredSvcCtxs.erase(lit);
        break;
      }
    }

    if (svctx)
    {
      Transport::TServiceId svcpath = Transport::GetServicePath(svcid);
      SvcContextsT::iterator it = svcContexts.find(svcpath);
      if (svcContexts.end() == it)
      {
        LOG_E(RBLOG).Trace("Can't unregister service: svc not found(svcid=%s)", svcid.c_str());
      }
      else
      {
        HostsByRolesT* hostByRoles = &(it->second);
        HostsByRolesT::iterator rit = hostByRoles->find(svctx->svcrole());
        if (hostByRoles->end() != rit)
        {
          HostContextListT* hosts = &(rit->second);
          for(HostContextListT::iterator lit = hosts->begin(); lit != hosts->end(); ++lit)
          {
            StrongMT<HostContext> hctx = (*lit);
            StrongMT<SvcContext> svctx = hctx->unregisterSvcContext(svcid);
            if (svctx)
            {
              LOG_M(RBLOG).Trace("Service unregistered(svcid=%s host=%s)", svcid.c_str(), hctx->host().c_str());
              break;
            }
          }

          if (hosts->empty())
          {
            LOG_M(RBLOG).Trace("Unregister svcrole due to last service with such role unregistered(svcid=%s svcrole=%s)", svcid.c_str(), svctx->svcrole().c_str());
            hostByRoles->erase(rit);
            hosts = 0;
          }

          if (!hostByRoles->size())
          {
            LOG_M(RBLOG).Trace("Unregister svcpath due to last service unregistered by this path(svcid=%s svcpath=%s)", svcid.c_str(), svctx->svcpath().c_str());
            svcContexts.erase(it);
            hostByRoles = 0;
          }
        }
      }
    }

    return svctx;
  }

  StrongMT<SvcContext> BalancerImpl::excludeServiceFromLoad(Transport::TServiceId const & svcid)
  {
    LOG_M(RBLOG).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

    StrongMT<SvcContext> svctx;
    for(SvcContextListT::iterator lit = registeredSvcCtxs.begin(); lit != registeredSvcCtxs.end(); ++lit)
    {
      if ((*lit)->svcid() == svcid)
      {
        svctx = *lit;
        break;
      }
    }

    if (svctx)
    {
      Transport::TServiceId svcpath = Transport::GetServicePath(svcid);
      SvcContextsT::iterator it = svcContexts.find(svcpath);
      if (svcContexts.end() == it)
      {
        LOG_E(RBLOG).Trace("Can't exclude service from load: svc not found(svcid=%s)", svcid.c_str());
      }
      else
      {
        HostsByRolesT* hostByRoles = &(it->second);
        HostsByRolesT::iterator rit = hostByRoles->find(svctx->svcrole());
        if (hostByRoles->end() != rit)
        {
          HostContextListT* hosts = &(rit->second);
          for(HostContextListT::iterator lit = hosts->begin(); lit != hosts->end(); ++lit)
          {
            StrongMT<HostContext> hctx = (*lit);
            StrongMT<SvcContext> svctx = hctx->excludeFromLoad(svcid);
            if (svctx)
            {
              LOG_M(RBLOG).Trace("Service excluded from load(svcid=%s host=%s)", svcid.c_str(), hctx->host().c_str());
              break;
            }
          }
        }
      }
    }

    return svctx;
  }

  int BalancerImpl::Step()
  {
    userMngrIface_->step();

    svcPublisherIface_->step();

    for(SvcContextListT::iterator it = initSvcCtxs.begin(); it != initSvcCtxs.end();)
    {
      StrongMT<SvcContext> svctx = *it;
      svctx->step();
      if (svctx->isopen())
      {
        it = initSvcCtxs.erase(it);
        registerOpenedContext(svctx);
      }
      else
         ++it;
    }

    for(SvcContextsT::const_iterator cit=svcContexts.begin(); cit != svcContexts.end(); ++cit)
    {
      HostsByRolesT const & hostsByRoles = cit->second;
      for(HostsByRolesT::const_iterator crit=hostsByRoles.begin(); crit != hostsByRoles.end(); ++crit)
      {
        HostContextListT const & hostctxs = crit->second;
        for(HostContextListT::const_iterator chit = hostctxs.begin(); chit != hostctxs.end(); ++chit)
        {
          (*chit)->step();
        }
      }
    }

    AllocCtxListT::iterator it = allocCtxs4Deletion.begin();
    while(it != allocCtxs4Deletion.end())
    {
      allocCtxFactory->free(*it);
      it = allocCtxs4Deletion.erase(it);
    }

    return 0;
  }

  StrongMT<SvcContext> BalancerImpl::findSvc(Transport::TServiceId const & svcpath, Coordinator::TServiceRole const & role, 
                                             unsigned int _softlimit, unsigned int _hardlimit, Transport::TServiceId const & except)
  {
    LOG_M(RBLOG).Trace("%s(svcpath=%s role=%s slimit=%d hlimit=%d)", 
      __FUNCTION__, svcpath.c_str(), role.c_str(), _softlimit, _hardlimit);

    StrongMT<SvcContext> svctx;
    SvcContextsT::iterator it = svcContexts.find(svcpath);
    if (it != svcContexts.end())
    {
      HostsByRolesT* role2hosts = &(it->second);

      HostsByRolesT::iterator rit = role2hosts->find(role);
      if (rit != role2hosts->end())
      {
        HostContextListT* hostlst = &(rit->second);
        if (!hostlst->empty())
        {
          StrongMT<HostContext> currentctx = findHost2Load(hostlst);
          if (currentctx->load())
          {
            svctx = currentctx->findSvcSoftLimit(role, _softlimit, except);
            if (!svctx && except != Transport::EmptySvcId)
              svctx = currentctx->findSvcSoftLimit(role, _softlimit);

            if (!svctx)
            {
              LOG_W(RBLOG).Trace("Soft limit reached(svcpath=%s role=%s softlimit=%d)", 
                svcpath.c_str(), role.c_str(), _softlimit);

              svctx = currentctx->findSvcHardLimit(role, _hardlimit, except);
              if (!svctx && except != Transport::EmptySvcId)
                svctx = currentctx->findSvcHardLimit(role, _hardlimit);
            }
          }
          else
          {
            LOG_W(RBLOG).Trace("Host limit is reached. Can't allocate relay(host=%s role=%s svcpath=%s)", currentctx->host().c_str(), role.c_str(), svcpath.c_str());
          }
        }
        else
        {
          LOG_W(RBLOG).Trace("No hosts registered by role(role=%s svcpath=%s)", role.c_str(), svcpath.c_str());
        }
      }
      else
      {
        LOG_W(RBLOG).Trace("No hosts registered by role(role=%s svcpath=%s)", role.c_str(), svcpath.c_str());
      }
    }
    else
    {
      LOG_W(RBLOG).Trace("Svcpath is not registered(svcpath=%s)", svcpath.c_str());
    }

    return svctx;
  }

  void BalancerImpl::OnAllocationCompleted(bool _res, StrongMT<AllocationContext> const & _ctx)
  {
    LOG_M(RBLOG).Trace("%s(res=%d allocid=%d u=%d gameid=%s)", __FUNCTION__, (int)_res, _ctx->id(), _ctx->userctx()->userid(), 
      (_ctx->gameusergroup() ? _ctx->gameusergroup()->fmtid() : ""));

    StrongMT<AllocationContext> ac = _ctx;
    ac->close();

    SvcContextPtr const & svctx = ac->svctx();
    if (svctx && svctx->isopen() &&
        settings_.relayAllocationFailureThreshold() && 
        svctx->relayAllocationFailedCount() >= settings_.relayAllocationFailureThreshold())
    {
      LOG_W(RBLOG).Trace("Relay allocation failure threshold is exceeded(svcid=%s svcaddr=%s counter=%d threshold=%d)", 
        svctx->svcid().c_str(), svctx->frontendAddr().c_str(), svctx->relayAllocationFailedCount(), settings_.relayAllocationFailureThreshold());

      svctx->reopen();
      svctx->resetRelayAllocationFailedCount();
    }

    SvcContextPtr const & secondarysvctx = ac->secondarysvctx();
    if (secondarysvctx && secondarysvctx->isopen() && 
        settings_.relayAllocationFailureThreshold() && 
        secondarysvctx->relayAllocationFailedCount() >= settings_.relayAllocationFailureThreshold())
    {
      LOG_W(RBLOG).Trace("Secondary-relay allocation failure threshold is exceeded(svcid=%s svcaddr=%s counter=%d threshold=%d)", 
        secondarysvctx->svcid().c_str(), secondarysvctx->frontendAddr().c_str(), secondarysvctx->relayAllocationFailedCount(), settings_.relayAllocationFailureThreshold());

      secondarysvctx->reopen();
      secondarysvctx->resetRelayAllocationFailedCount();
    }

    UserContextPtr uctx = ac->userctx();
    if (_res)
    {
      LOG_M(RBLOG).Trace("%s: relay allocation is completed(allocid=%d u=%d gameid=%s)", 
        __FUNCTION__, _ctx->id(), _ctx->userctx()->userid(), (_ctx->gameusergroup() ? _ctx->gameusergroup()->fmtid() : ""));

      if (svctx)
      {
        bool res = users_.insert(make_pair<Transport::TClientId, StrongMT<UserContext> >(uctx->userid(), uctx)).second;
        NI_ASSERT(res, "User context must NOT be registered");
      }

      GameUserGroupPtr gug = ac->gameusergroup();
      if (gug)
        uctx->gameusergroup(gug);
    }
    else
    {
      LOG_W(RBLOG).Trace("%s: relay allocation is FAILED(allocid=%d u=%d gameid=%s)", 
        __FUNCTION__, _ctx->id(), _ctx->userctx()->userid(), (_ctx->gameusergroup() ? _ctx->gameusergroup()->fmtid() : ""));

      GameUserGroupPtr gug = ac->gameusergroup();
      if (gug)
        gug->detachUser(uctx->userid());
    }

    allocCtxs4Deletion.push_back(ac);
  }

  void BalancerImpl::OnUserLeaveSvc(Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & _svcrole, StrongMT<UserContext> const & _uctx)
  {
    LOG_M(RBLOG).Trace("%s: remove user(u=%d svcid=%s svcrole=%s)", 
      __FUNCTION__, _uctx->userid(), _svcid.c_str(), _svcrole.c_str());

    if (0 == _uctx->count())
    {
      if (userMngrIface_->isopen())
        userMngrIface_->iface()->RemoveUser(_uctx->userid(), this, &BalancerImpl::OnReturn_RemoveUser, _uctx->userid());
      else
        LOG_E(RBLOG).Trace("%s: can't remove user. User manager is unavailable(u=%d svcid=%s svcrole=%s)", 
          __FUNCTION__, _uctx->userid(), _svcid.c_str(), _svcrole.c_str());

      GameUserGroupPtr gug = _uctx->gameusergroup();
      if (gug)
      {
        LOG_M(RBLOG).Trace("%s: detach user from game group(u=%d gameid=%s)", 
          __FUNCTION__, _uctx->userid(), gug->fmtid());

        gug->detachUser(_uctx->userid());

        GameCtxsT::iterator it = games_.find(gug->gameid());
        if (it != games_.end())
        {
          GameContextPtr gamectx = it->second;
          if (gamectx && 0 == gamectx->usercount())
          {
            LOG_M(RBLOG).Trace("%s: last user gone for game. Remove game(u=%d gameid=%s)", 
              __FUNCTION__, _uctx->userid(), gug->fmtid());
            games_.erase(it);
          }
        }
      }

      users_.erase(_uctx->userid());
    }
    else
    {
      userMngrIface_->iface()->OnUserLeave(_uctx->userid(), _svcid, _svcrole, this, &BalancerImpl::OnReturn_OnUserLeave, _uctx->userid());
    }
  }

  void BalancerImpl::OnReturn_RemoveUser(bool res, Transport::TClientId userid, rpc::CallStatus rpcsts)
  {
    LOG_M(RBLOG).Trace("%s(u=%d res=%d rpcsts=%d)", __FUNCTION__, userid, (int)res, (int)rpcsts);
  }

  void BalancerImpl::OnReturn_OnUserLeave(bool res, Transport::TClientId userid, rpc::CallStatus rpcsts)
  {
    LOG_M(RBLOG).Trace("%s(u=%d res=%d rpcsts=%d)", __FUNCTION__, userid, (int)res, (int)rpcsts);
  }

  int BalancerImpl::registerOpenedContext(StrongMT<SvcContext> const & svctx)
  {
    LOG_M(RBLOG).Trace("%s (svcid=%s svcaddr=%s netaddr=%s)", __FUNCTION__, svctx->svcid().c_str(), svctx->frontendAddr().c_str(), svctx->netaddr().c_str());

    //  register opened context
    HostContextListT& hostlist = svcContexts[svctx->svcpath()][svctx->svcrole()];
    Network::NetAddress host;
    Network::GetHost(svctx->frontendAddr(), host);
    Network::NetAddress hostip = Network::GetHostIPByName(host);
    StrongMT<HostContext> hostctx = findHostCtx(hostlist, hostip);
    if (!hostctx)
    {
      Balancer::UserLimits hostUserLimit = settings_.relayHostUserLimit(hostip);
      LOG_M(RBLOG).Trace("New host registered(host=%s svcid=%s svcrole=%s svcaddr=%s sofUserLimit=%d hardUserlimit=%d)", 
        hostip.c_str(), svctx->svcid().c_str(), svctx->svcrole().c_str(), svctx->frontendAddr().c_str(), hostUserLimit.softlimit(), hostUserLimit.hardlimit());

      hostctx = new HostContext(hostip, svctx->svcrole(), settings_);
      hostlist.push_back(hostctx);
    }
    else
    {
      LOG_M(RBLOG).Trace("The host already registered(host=%s svcid=%s svcaddr=%s)", hostip.c_str(), svctx->svcid().c_str(), svctx->frontendAddr().c_str());
    }

    return hostctx->registerSvcContext(svctx);
  }

  StrongMT<HostContext> BalancerImpl::findHostCtx(HostContextListT const & hostlst, Network::NetAddress const & host)
  {
    for(HostContextListT::const_iterator cit = hostlst.begin(); cit != hostlst.end(); ++cit)
    {
      StrongMT<HostContext> ctx = *cit;
      if (ctx->host() == host)
      {
        return ctx;
      }
    }

    return StrongMT<HostContext>();
  }

  void BalancerImpl::OnRegisterSubscriber(Coordinator::SubcriberIdT _id, Coordinator::ClusterInfo const & _cluster)
  {
    LOG_D(RBLOG).Trace("%s(subscriberid=%d)", __FUNCTION__, _id);

    if (_id < 0)
    {
      LOG_E(RBLOG).Trace("Can't register self as subscriber(res=%d)", _id);
      return;
    }

    subscriberId_ = _id;

    LOG_M(RBLOG).Trace("Cluster services:");
    Coordinator::ClusterInfo::SvcInfosT const & svcinfos = _cluster.svcinfos;
    for(Coordinator::ClusterInfo::SvcInfosT::const_iterator cit = svcinfos.begin(); cit != svcinfos.end(); ++cit)
    {
      Coordinator::SvcInfo const & si = *cit;
      if (Coordinator::ServiceStatus::S_STARTED == si.st)
      {
        Transport::TServiceId svcls;
        Transport::GetServiceClass(si.svcid, svcls);
        if (Relay::ServiceClass == svcls)
        {
          LOG_M(RBLOG).Trace("%s: started relay found(svcid=%s netaddr=%s frontend=%s status=%s)", 
            __FUNCTION__, si.svcid.c_str(), si.netaddr.c_str(), si.frontendnetaddr.c_str(), Coordinator::ServiceStatus::ToString(si.st));

          AddService(si.svcid, si.svcrole);
        }
      }
    }

    LOG_M(RBLOG).Trace("Registered as subscriber successfully(id=%d)", _id);
  }

  void BalancerImpl::OnRegisterService(Transport::TServiceId const & _svcid)
  {
    LOG_D(RBLOG).Trace("%s(svcid=%s)", __FUNCTION__, _svcid.c_str());
  }

  void BalancerImpl::OnUnregisterService(Transport::TServiceId const & _svcid)
  {
    LOG_D(RBLOG).Trace("%s(svcid=%s)", __FUNCTION__, _svcid.c_str());
  }

  void BalancerImpl::OnStartService(Coordinator::SvcInfo const & _si)
  {
    LOG_D(RBLOG).Trace("%s(svcid=%s netaddr=%s frontend=%s svcrole=%s)", __FUNCTION__, 
      _si.svcid.c_str(), _si.netaddr.c_str(), _si.frontendnetaddr.c_str(), _si.svcrole.c_str());

    Transport::TServiceId svcls;
    Transport::GetServiceClass(_si.svcid, svcls);
    if (Relay::ServiceClass == svcls)
      AddService(_si.svcid, _si.svcrole);
  }

  void BalancerImpl::OnStopService(Transport::TServiceId const & _svcid)
  {
    LOG_D(RBLOG).Trace("%s(svcid=%s)", __FUNCTION__, _svcid.c_str());

    Transport::TServiceId svcls;
    Transport::GetServiceClass(_svcid, svcls);
    if (Relay::ServiceClass == svcls)
      RemoveService(_svcid);
  }

  void BalancerImpl::OnChangeServiceStatus(Transport::TServiceId const & _svcid, /*Coordinator::ServiceStatus::Enum*/int _status)
  {
    Coordinator::ServiceStatus::Enum status = (Coordinator::ServiceStatus::Enum)_status;
    LOG_D(RBLOG).Trace("%s(svcid=%s status=%s)", __FUNCTION__, _svcid.c_str(), Coordinator::ServiceStatus::ToString(status));

    if (Coordinator::ServiceStatus::S_SOFT_STOPPING == status || 
        Coordinator::ServiceStatus::S_STOPPING == status)
    {
      Transport::TServiceId svcls;
      Transport::GetServiceClass(_svcid, svcls);
      if (Relay::ServiceClass == svcls)
        excludeServiceFromLoad(_svcid);
    }
  }

  void BalancerImpl::onChangeState(rpc::IfaceRequesterState::Enum _st, 
    StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher> > const & _ifacereq)
  {
    if (rpc::IfaceRequesterState::OPENED == _st)
    {
      LOG_M(RBLOG).Trace("Service publisher iface received");

      _ifacereq->iface()->RegisterSubscriber(this);
    }
    else
    if (rpc::IfaceRequesterState::CLOSED == _st)
    {
      LOG_W(RBLOG).Trace("Service publisher iface closed");
      subscriberId_ = Coordinator::INVALID_SUBSCRIBER_ID;
    }
  }

  StrongMT<HostContext> BalancerImpl::findHost2Load(HostContextListT* hostlst)
  {
    StrongMT<HostContext> prevctx = *hostlst->begin();
    StrongMT<HostContext> currentctx = *hostlst->begin();

    Balancer::UserLimits ulimit = settings_.relayRoleUserLimit(currentctx->role().c_str());

    //  find host to allocate relay
    HostContextListT::iterator foundit = hostlst->end();
    for(HostContextListT::iterator hit = ++hostlst->begin(); hit != hostlst->end(); ++hit)
    {
      StrongMT<HostContext> const & ctx = *hit;
      if (!currentctx->load())
      {
        //  т.к. не можем грузить текущий хост, 
        //  то выбираем контекст как отправную точку, и переходим к сравнению со следующим по списку
        currentctx = ctx;
        foundit = hit;
        continue;
      }

      if (ctx->load())
      {
        uint candidateHostCcu = ctx->ccu();
        uint currentHostCcu = currentctx->ccu();
        if (candidateHostCcu + settings_.hostUserDistributionAccuracy() <= currentHostCcu)
        {
          bool change = false;
          int currentUserSoftLimit = currentctx->onlineSvcCount()*ulimit.softlimit();
          if (currentctx->softUserLimit() && currentUserSoftLimit > (int)currentctx->softUserLimit())
            currentUserSoftLimit = currentctx->softUserLimit();
          int currentRestSoftCapacity = currentUserSoftLimit - currentHostCcu;
          int userSoftLimit = ctx->onlineSvcCount()*ulimit.softlimit();
          if (ctx->softUserLimit() && userSoftLimit > (int)ctx->softUserLimit())
            userSoftLimit = ctx->softUserLimit();
          int restSoftCapacity = userSoftLimit - candidateHostCcu;

          //-------------------------------------------------------------------------------------------------------------
          //  1.  Если обе машины не достигли softlimit'а - 
          //  выбираем с наибольшим кол-вом оставшихся свободных слотов до достижения softlimit'а машины
          //  2.  Если у одной машины softlimit не превышен, а у другой превышен - выбираем ту, у которой не превышен
          //  3.  Если softlimit превышен у обоих, то выбираем выбираем хост с наибольшим кол-вом оставшихся свободных слотов до hardlimit'а
          //-------------------------------------------------------------------------------------------------------------
          if (currentRestSoftCapacity > 0 && restSoftCapacity > 0 && restSoftCapacity > currentRestSoftCapacity)
            change = true;
          else
          if (currentRestSoftCapacity <= 0 && restSoftCapacity > 0)
            change = true;
          else
          if (currentRestSoftCapacity <= 0 && restSoftCapacity <= 0)
          { //  softlimit у обоих хостов превышен

            int currentUserHardLimit = currentctx->onlineSvcCount()*ulimit.hardlimit();
            if (currentctx->hardUserLimit() && currentUserHardLimit > (int)currentctx->hardUserLimit())
              currentUserHardLimit = currentctx->hardUserLimit();
            int currentRestHardCapacity = currentUserHardLimit - currentHostCcu;
            int userHardLimit = ctx->onlineSvcCount()*ulimit.hardlimit();
            if (ctx->hardUserLimit() && userHardLimit > (int)ctx->hardUserLimit())
              userHardLimit = ctx->hardUserLimit();
            int restHardCapacity = userHardLimit - candidateHostCcu;

            if (restHardCapacity > currentRestHardCapacity)
              change = true;
          }

          if (change)
          {
            currentctx = ctx;
            foundit = hit;
          }
        }
      }
    }

    //  place less loaded host to first position in the list
    if (foundit != hostlst->end())
    {
      LOG_M(RBLOG).Trace("Current loaded host is changed(host=%s prevhost=%s role=%s)", currentctx->host().c_str(), prevctx->host().c_str(), currentctx->role().c_str());
      hostlst->erase(foundit);
      hostlst->push_front(currentctx);
    }

    return currentctx;
  }

  StrongMT<SvcContext> BalancerImpl::findPrimaryRelay(Transport::TServiceId const & _svcpath, Transport::TServiceId const & _exceptRelay)
  {
    Balancer::UserLimits ulimit = settings_.relayRoleUserLimit(Coordinator::PrimarySvcRole.c_str());
    return findSvc(_svcpath, Coordinator::PrimarySvcRole, ulimit.softlimit(), ulimit.hardlimit(), _exceptRelay);
  }

  SvcContextPtr BalancerImpl::findPrimaryRelay(Transport::TServiceId const & _svcpath, GameUserGroupPtr const & _gameusergroup, Transport::TServiceId const & _exceptRelay)
  {
    if (_gameusergroup)
    {
      if (!_gameusergroup->primaryRelay() || !_gameusergroup->primaryRelay()->isopen())
      {
        SvcContextPtr svctx = findPrimaryRelay(_svcpath, _exceptRelay);
        if (svctx)
          _gameusergroup->primaryRelay(svctx);

        return svctx;
      }
      else
      {
        return _gameusergroup->primaryRelay();
      }
    }
    else
    {
      return findPrimaryRelay(_svcpath, _exceptRelay);
    }
  }

  StrongMT<SvcContext> BalancerImpl::findSecondaryRelay(Transport::TServiceId const & svcpath, Transport::TServiceId const & _exceptRelay)
  {
    Balancer::UserLimits ulimit = settings_.relayRoleUserLimit(Coordinator::SecondarySvcRole.c_str());
    return findSvc(svcpath, Coordinator::SecondarySvcRole, ulimit.softlimit(), ulimit.hardlimit(), _exceptRelay);
  }

  SvcContextPtr BalancerImpl::findSecondaryRelay(Transport::TServiceId const & _svcpath, GameUserGroupPtr const & _gameusergroup, Transport::TServiceId const & _exceptRelay)
  {
    if (_gameusergroup)
    {
      if (!_gameusergroup->secondaryRelay() || !_gameusergroup->secondaryRelay()->isopen())
      {
        SvcContextPtr svctx = findSecondaryRelay(_svcpath, _exceptRelay);
        if (svctx)
          _gameusergroup->secondaryRelay(svctx);

        return svctx;
      }
      else
      {
        return _gameusergroup->secondaryRelay();
      }
    }
    else
    {
      return findSecondaryRelay(_svcpath, _exceptRelay);
    }
  }

  int BalancerImpl::startRelayAllocation(Balancer::Settings const & _settings, StrongMT<UserContext> const & _uctx, Transport::TServiceId const & _svcpath, 
    int _userctx, StrongMT<SvcContext> const & _svctx, StrongMT<SvcContext> const & _secondarysvctx, 
    StrongMT<RIBalancerCallback> const & _cb, GameUserGroupPtr const & _gameusergroup)
  {
    int rc = -1;

    //  create allocation context and open it
    StrongMT<AllocationContext> alloctx = allocCtxFactory->alloc(_settings, _uctx, _svcpath, _userctx, _svctx, _secondarysvctx, 
      static_cast<RIBalancerCallback*>(_cb), (IAllocationCompletedNotify*)this, _gameusergroup);
    if (alloctx)
    {
      rc = alloctx->open();
      if (rc < 0)
      {
        LOG_E(RBLOG).Trace("%s: can't open alloc context(allocid=%d svcpath=%s userctx=%d)", 
          __FUNCTION__, alloctx->id(), _svcpath.c_str(), _userctx);
      }
    }
    else
    {
      LOG_E(RBLOG).Trace("Can't create allocation context(svcpath=%s userctx=%d)", _svcpath.c_str(), _userctx);
    }

    return rc;
  }
}

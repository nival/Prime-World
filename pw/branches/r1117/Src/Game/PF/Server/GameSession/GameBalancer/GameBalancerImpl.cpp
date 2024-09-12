#include "stdafx.h"
#include "GameBalancer/GameBalancerImpl.h"
#include "GameBalancer/SvcContext.h"
#include "GameBalancer/SvcAllocContext.h"
#include "GameBalancer/RGameBalancerIface.auto.h"
#include "GameBalancer/GameBalancerCfg.h"
#include <Coordinator/CoordinatorServerNaming.h>
#include "HybridServer/HybridServerNaming.h"

NI_DEFINE_REFCOUNT(GameBalancer::BalancerImpl);

namespace GameBalancer
{
  BalancerImpl::BalancerImpl(uint _softlimit, uint _hardlimit, rpc::GateKeeper * _gk, Transport::IAddressTranslator* _addrResolver)
    :softlimit_(_softlimit),
    hardlimit_(_hardlimit),
    gk(_gk),
    addrResolver_(_addrResolver)
  {
    svcPublisherIface_ = new rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>;
    int rc = svcPublisherIface_->init(gk, Transport::ENetInterface::Coordinator, Coordinator::SvcAppearancePublisherIfaceId, 
      &GetSystemLog(), GBALANCER, this);
    if (rc < 0)
    {
      LOG_C(GBALANCER).Trace("Can't init rpc iface requester(node=%s iface=%s)", Transport::ENetInterface::Coordinator.c_str(),
        Coordinator::SvcAppearancePublisherIfaceId);
    }
  }

  BalancerImpl::~BalancerImpl()
  {
  }

  int BalancerImpl::AllocateGameSvc(Transport::TServiceId const & svcpath, Peered::TSessionId userctx, IBalancerCallback* cb)
  {
    LOG_M(GBALANCER).Trace("Allocate game svc(userctx=%016x)", userctx);

    int rc = -1;
    if (!hostByPath_.size())
    {
      LOG_E(GBALANCER).Trace("Can't allocate game svc: no registered services(userctx=%016x)", userctx);
      return rc;
    }

    //  1) find service
    StrongMT<SvcContext> svctx = findSvc_(svcpath, userctx, softlimit_, hardlimit_);
    if (!svctx)
    {
      LOG_E(GBALANCER).Trace("Can't allocate game svc: no appropriate service found(svcpath=%s userctx=%016x)", svcpath.c_str(), userctx);
      return rc;
    }

    //  2)  create/register context for allocation
    rc = svctx->openSvcAllocCtx(svcpath, userctx, StrongMT<RIBalancerCallback>(static_cast<RIBalancerCallback*>(cb)));
    if (rc < 0)
    {
      LOG_E(GBALANCER).Trace("Svc allocation is FAILED(svcpath=%s userctx=%016x)", svcpath.c_str(), userctx);
    }
    return rc;
  }

  void BalancerImpl::AddService( Transport::TServiceId const & svcid )
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

    StrongMT<SvcContext> svctx = registerService_(svcid);
    if (svctx)
    {
      int rc = svctx->open(gk, &GetSystemLog(), GBALANCER, addrResolver_);
      if (rc < 0)
      {
        LOG_E(GBALANCER).Trace("Can't open service context(svcid=%s)", svcid.c_str());
      }
      else
      if (rc > 0)
      {
        LOG_W(GBALANCER).Trace("Service context already opened(svcid=%s)", svcid.c_str());
      }
      else
      {
        LOG_M(GBALANCER).Trace("Service registered(svcid=%s)", svcid.c_str());
      }
    }
    else
    {
      LOG_E(GBALANCER).Trace("Service registration FAILED(svcid=%s)", svcid.c_str());
    }
  }

  void BalancerImpl::RemoveService( Transport::TServiceId const & svcid )
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

    StrongMT<SvcContext> svctx = unregisterService_(svcid);
    if (svctx)
    {
      svctx->close();
      LOG_M(GBALANCER).Trace("Service unregistered successfully(svcid=%s)", svcid.c_str());
    }
    else
    {
      LOG_W(GBALANCER).Trace("Can't unregister service(svcid=%s)", svcid.c_str());
    }
  }

  StrongMT<SvcContext> BalancerImpl::registerService_(Transport::TServiceId const & svcid)
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

    StrongMT<SvcContext> svctx;

    Transport::TServiceId svcls;
    Transport::GetServiceClass(svcid, &svcls);
    if (HybridServer::ServiceClass != svcls)
    {
      LOG_E(GBALANCER).Trace("Can't register service : wrong svc class(svcid=%s)", svcid.c_str());
      return svctx;
    }

    for(SvcContextListT::iterator it = registeredSvcCtxs.begin(); it != registeredSvcCtxs.end(); ++it)
    {
      StrongMT<SvcContext> const & ctx = *it;
      if (ctx->svcid() == svcid)
      {
        if (ctx->isclosed())
        {
          LOG_W(GBALANCER).Trace("%s: remove closed svc(svcid=%s)", __FUNCTION__, ctx->svcid().c_str());
          registeredSvcCtxs.erase(it);
        }
        else
        {
          LOG_W(GBALANCER).Trace("%s: svc already registered(svcid=%s)", __FUNCTION__, ctx->svcid().c_str());
          svctx = ctx;
        }
        break;
      }
    }

    if (!svctx)
    {
      svctx = new SvcContext(svcid);
      registeredSvcCtxs.push_back(svctx);
      initSvcCtxs.push_back(svctx);

      LOG_M(GBALANCER).Trace("%s: new svc registered(svcid=%s)", __FUNCTION__, svcid.c_str());
    }

    return svctx;
  }

  StrongMT<SvcContext> BalancerImpl::unregisterService_(Transport::TServiceId const & svcid)
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

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
      HostsByPathT::iterator it = hostByPath_.find(svctx->svcpath());
      if (hostByPath_.end() == it)
      {
        LOG_E(GBALANCER).Trace("Can't unregister service: no service found by svcpath(svcpath=%s svcid=%s svcaddr=%s)", 
          svctx->svcpath().c_str(), svctx->svcid().c_str(), svctx->netaddr().c_str());
      }
      else
      {
        HostContextListT* hostlst = &(it->second);
        for(HostContextListT::iterator lit = hostlst->begin(); lit != hostlst->end(); ++lit)
        {
          StrongMT<HostContext> & hctx = (*lit);
          StrongMT<SvcContext> svctx = hctx->unregisterSvcContext(svcid);
          if (svctx)
          {
            LOG_M(GBALANCER).Trace("Service unregistered(svcid=%s svcaddr=%s host=%s)", 
              svctx->svcid().c_str(), svctx->netaddr().c_str(), hctx->host().c_str());

            if (0 == hctx->svcCount())
            {
              LOG_M(GBALANCER).Trace("Unregister host due to last service unregistered on this host(host=%s)", 
                hctx->host().c_str());

              hostlst->erase(lit);
            }
            break;
          }
        }

        if (it->second.empty())
        {
          LOG_M(GBALANCER).Trace("Unregister svcpath due to last service unregistered by this path(svcpath=%s)", 
            svctx->svcpath().c_str());
          hostByPath_.erase(it);
        }
      }
    }

    return svctx;
  }

  int BalancerImpl::Step()
  {
    svcPublisherIface_->step();

    for(SvcContextListT::iterator it = initSvcCtxs.begin(); it != initSvcCtxs.end();)
    {
      StrongMT<SvcContext> svctx = *it;
      svctx->step();
      if (svctx->isopen())
      {
        it = initSvcCtxs.erase(it);
        registerInitializedContext_(svctx);
      }
      else
        ++it;
    }

    for(HostsByPathT::iterator it=hostByPath_.begin(); it!=hostByPath_.end(); ++it)
    {
      for(HostContextListT::iterator lit = it->second.begin(); lit != it->second.end(); ++lit)
      {
        (*lit)->step();
      }
    }

    return 0;
  }

  int BalancerImpl::registerInitializedContext_( SvcContext * svctx )
  {
    LOG_M(GBALANCER).Trace("%s(svcid=%s netaddr=%s)", __FUNCTION__, svctx->svcid().c_str(), svctx->netaddr().c_str());

    //  register initialized context
    HostContextListT& hostlist = hostByPath_[svctx->svcpath()];
    Network::NetAddress host;
    Network::GetHost(svctx->netaddr(), host);
    Network::NetAddress hostip = Network::GetHostIPByName(host);
    StrongMT<HostContext> hostctx = findHostCtx_(hostlist, hostip);
    if (!hostctx)
    {
      LOG_M(GBALANCER).Trace("New host registered(host=%s svcid=%s svcaddr=%s)", 
        hostip.c_str(), svctx->svcid().c_str(), svctx->netaddr().c_str());

      hostctx = new HostContext(hostip);
      hostlist.push_front(hostctx);
    }

    return hostctx->registerSvcContext(svctx);
  }

  StrongMT<HostContext> BalancerImpl::findHostCtx_(HostContextListT const & hostlst, Network::NetAddress const & host)
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

  StrongMT<SvcContext> BalancerImpl::findSvc_(Transport::TServiceId const & svcpath, Peered::TSessionId userctx,
    unsigned int _softlimit, unsigned int _hardlimit)
  {
    LOG_M(GBALANCER).Trace("%s(svcpath=%s userctx=%016x slimit=%d hlimit=%d)", 
      __FUNCTION__, svcpath.c_str(), userctx, _softlimit, _hardlimit);

    StrongMT<SvcContext> svctx;
    HostsByPathT::iterator it = hostByPath_.find(svcpath);
    if (it != hostByPath_.end())
    {
      HostContextListT* hostlst = &(it->second);
      if (!hostlst->empty())
      {
        StrongMT<HostContext> prevctx = *hostlst->begin();
        StrongMT<HostContext> hctx = *hostlst->begin();
        //  find host with min ccu
        HostContextListT::iterator foundit = hostlst->begin();
        for(HostContextListT::iterator hit = ++hostlst->begin(); hit != hostlst->end(); ++hit)
        {
          StrongMT<HostContext> const & ctx = *hit;
          if (ctx->onlineSvcCount())
          {
            if (!hctx->onlineSvcCount())
            {
              hctx = ctx;
              foundit = hit;
            }
            else
            if (ctx->ccu() + Cfg::GetHostGameDistributionAccuracy() <= hctx->ccu())
            {
              hctx = ctx;
              foundit = hit;
            }
          }
        }

        //  place less loaded host to first position in the list
        if (foundit != hostlst->begin())
        {
          LOG_M(GBALANCER).Trace("Current loaded host is changed(host=%s prevhost=%s)", hctx->host().c_str(), prevctx->host().c_str());

          hostlst->erase(foundit);
          hostlst->push_front(hctx);
        }

        svctx = hctx->findSvcSoftLimit(_softlimit);
        if (!svctx)
        {
          LOG_W(GBALANCER).Trace("Soft limit reached(svcpath=%s userctx=%016x softlimit=%d)", 
            svcpath.c_str(), userctx, _softlimit);

          svctx = hctx->findSvcHardLimit(_hardlimit);
          if (!svctx)
          {
            LOG_W(GBALANCER).Trace("Hard limit reached(svcpath=%s userctx=%016x hardlimit=%d)", 
              svcpath.c_str(), userctx, _hardlimit);
          }
        }
      }
      else
      {
        LOG_W(GBALANCER).Trace("No hosts registered by path(svcpath=%s)", svcpath.c_str());
      }
    }
    else
    {
      LOG_W(GBALANCER).Trace("Svcpath is not registered(svcpath=%s)", svcpath.c_str());
    }

    return svctx;
  }

  void BalancerImpl::OnRegisterSubscriber(Coordinator::SubcriberIdT _id, Coordinator::ClusterInfo const & _cluster)
  {
    LOG_D(GBALANCER).Trace("%s(subscriberid=%d)", __FUNCTION__, _id);

    if (_id < 0)
    {
      LOG_E(GBALANCER).Trace("Can't register self as subscriber(res=%d)", _id);
      return;
    }

    subscriberId_ = _id;

    LOG_M(GBALANCER).Trace("Cluster services:");
    Coordinator::ClusterInfo::SvcInfosT const & svcinfos = _cluster.svcinfos;
    for(Coordinator::ClusterInfo::SvcInfosT::const_iterator cit = svcinfos.begin(); cit != svcinfos.end(); ++cit)
    {
      Coordinator::SvcInfo const & si = *cit;
      if (Coordinator::ServiceStatus::S_STARTED == si.st)
      {
        Transport::TServiceId svcls;
        Transport::GetServiceClass(si.svcid, svcls);
        if (HybridServer::ServiceClass == svcls)
        {
          LOG_M(GBALANCER).Trace("started gamesvc found(svcid=%s netaddr=%s frontend=%s status=%s)", 
            si.svcid.c_str(), si.netaddr.c_str(), si.frontendnetaddr.c_str(), Coordinator::ServiceStatus::ToString(si.st));

          AddService(si.svcid);
        }
      }
    }

    LOG_M(GBALANCER).Trace("Registered as subscriber successfully(id=%d)", _id);
  }

  void BalancerImpl::OnRegisterService(Transport::TServiceId const & _svcid)
  {
    LOG_D(GBALANCER).Trace("%s(svcid=%s)", __FUNCTION__, _svcid.c_str());
  }

  void BalancerImpl::OnUnregisterService(Transport::TServiceId const & _svcid)
  {
    LOG_D(GBALANCER).Trace("%s(svcid=%s)", __FUNCTION__, _svcid.c_str());
  }

  void BalancerImpl::OnStartService(Coordinator::SvcInfo const & _si)
  {
    LOG_D(GBALANCER).Trace("%s(svcid=%s netaddr=%s frontend=%s svcrole=%s)", __FUNCTION__, 
      _si.svcid.c_str(), _si.netaddr.c_str(), _si.frontendnetaddr.c_str(), _si.svcrole.c_str());

    Transport::TServiceId svcls;
    Transport::GetServiceClass(_si.svcid, svcls);
    if (HybridServer::ServiceClass == svcls)
      AddService(_si.svcid);
  }

  void BalancerImpl::OnStopService(Transport::TServiceId const & _svcid)
  {
    LOG_D(GBALANCER).Trace("%s(svcid=%s)", __FUNCTION__, _svcid.c_str());

    Transport::TServiceId svcls;
    Transport::GetServiceClass(_svcid, svcls);
    if (HybridServer::ServiceClass == svcls)
      RemoveService(_svcid);
  }

  void BalancerImpl::OnChangeServiceStatus(Transport::TServiceId const & _svcid, /*Coordinator::ServiceStatus::Enum*/ int _status)
  {
    Coordinator::ServiceStatus::Enum status = (Coordinator::ServiceStatus::Enum)_status;

    LOG_D(GBALANCER).Trace("%s(svcid=%s status=%s)", __FUNCTION__, _svcid.c_str(), Coordinator::ServiceStatus::ToString(status));

    if (Coordinator::ServiceStatus::S_SOFT_STOPPING == status ||
        Coordinator::ServiceStatus::S_STOPPING == status )
    {
      Transport::TServiceId svcls;
      Transport::GetServiceClass(_svcid, svcls);
      if (HybridServer::ServiceClass == svcls)
        RemoveService(_svcid);
    }
  }

  void BalancerImpl::onChangeState(rpc::IfaceRequesterState::Enum _st, 
    StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher> > const & _ifacereq)
  {
    if (rpc::IfaceRequesterState::OPENED == _st)
    {
      LOG_M(GBALANCER).Trace("Service publisher iface received");

      _ifacereq->iface()->RegisterSubscriber(this);
    }
    else
    if (rpc::IfaceRequesterState::CLOSED == _st)
    {
      LOG_W(GBALANCER).Trace("Service publisher iface closed");
      subscriberId_ = Coordinator::INVALID_SUBSCRIBER_ID;
    }
  }

}

#include "stdafx.h"
#include "ClusterAdminImpl.h"
#include "Coordinator/RCoordinatorServerIface.auto.h"
#include <Coordinator/CoordinatorServerNaming.h>

NI_DEFINE_REFCOUNT(ClusterAdmin::ClusterAdminImpl)

namespace ClusterAdmin
{
  ClusterAdminImpl::ClusterAdminImpl(StrongMT<rpc::GateKeeper> const & gk, Coordinator::ICoordinatorClient* cclient)
    :coordClient_(cclient),
    shutdown_(false),
    shutdownTimeout_(0),
    shutdownStart_(0),
    subscriberId(-1)
  {
    svcPublisherIfaceReq = new rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>;
    int rc = svcPublisherIfaceReq->init(gk, Transport::ENetInterface::Coordinator, Coordinator::SvcAppearancePublisherIfaceId, 
      &GetSystemLog(), ClusterAdmin::CALOG, this);
    if (rc < 0)
    {
      LOG_A(CALOG).Trace("Can't init rpc iface requester(node=%s iface=%s)", Transport::ENetInterface::Coordinator.c_str(),
        Coordinator::SvcAppearancePublisherIfaceId);
    }

    coordinatorIfaceReq = new rpc::IfaceRequester<Coordinator::RICoordinatorServerRemote>;
    rc = coordinatorIfaceReq->init(gk, Transport::ENetInterface::Coordinator, Coordinator::ServerIfaceId, 
      &GetSystemLog(), ClusterAdmin::CALOG, this);
    if (rc < 0)
    {
      LOG_A(CALOG).Trace("Can't init rpc iface requester(node=%s iface=%s)", Transport::ENetInterface::Coordinator.c_str(),
        Coordinator::ServerIfaceId);
    }

    GetSystemLog().SetChannelMinLevelFilter(CALOG, NLogg::LEVEL_DEBUG);
  }

  ClusterAdminImpl::~ClusterAdminImpl()
  {
  }

  void ClusterAdminImpl::Shutdown(unsigned int timeout)
  {
    if (!shutdown_)
    {
      shutdown_ = true;
      shutdownTimeout_ = timeout;
      shutdownStart_ = NHPTimer::GetScalarTime();
    }
  }

  void ClusterAdminImpl::OnRegisterService( Transport::TServiceId const & svcid )
  {
    LOG_D(CALOG).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

    SvcContext* svctx = findSvcContext_(svcid);
    if (svctx)
    {
      LOG_W(CALOG).Trace("Service already registered(svcid=%s)", svcid.c_str());
      return;
    }

    contexts.push_back(SvcContext(svcid)).sts = Coordinator::ServiceStatus::S_INIT;
  }

  void ClusterAdminImpl::OnUnregisterService( Transport::TServiceId const & svcid )
  {
    LOG_D(CALOG).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

    if (!removeSvcContext_(svcid))
    {
      LOG_E(CALOG).Trace("Service is not registered to unregister it(svcid=%s)", svcid.c_str());
    }
  }

  void ClusterAdminImpl::OnStartService( Coordinator::SvcInfo const & si )
  {
    LOG_D(CALOG).Trace("%s(svcid=%s netaddr=%s frontend=%s svcrole=%s)", __FUNCTION__, 
      si.svcid.c_str(), si.netaddr.c_str(), si.frontendnetaddr.c_str(), si.svcrole.c_str());

    SvcContext* svctx = findSvcContext_(si.svcid);
    if (svctx)
    {
      setSvcCtxData_(si, *svctx);
    }
    else
    {
      LOG_E(CALOG).Trace("Service is not registered to be started(svcid=%s)", si.svcid.c_str());
    }
  }

  void ClusterAdminImpl::OnStopService( Transport::TServiceId const & svcid )
  {
    LOG_D(CALOG).Trace("%s(svcid=%s)", __FUNCTION__, svcid.c_str());

    SvcContext* svctx = findSvcContext_(svcid);
    if (svctx)
    {
      NI_ASSERT(Coordinator::ServiceStatus::S_STARTED == svctx->sts, 
        NI_STRFMT("Service have to be started(svcid=%s)",svcid.c_str()));
      svctx->sts = Coordinator::ServiceStatus::S_STOPPED;
    }
    else
    {
      LOG_E(CALOG).Trace("Service is not registered to be stopped(svcid=%s)", svcid.c_str());
    }
  }

  void ClusterAdminImpl::OnChangeServiceStatus(Transport::TServiceId const & _svcid, /*Coordinator::ServiceStatus::Enum*/ int _status)
  {
    Coordinator::ServiceStatus::Enum status = (Coordinator::ServiceStatus::Enum)_status;

    LOG_D(CALOG).Trace("%s(svcid=%s status=%s)", __FUNCTION__, _svcid.c_str(), Coordinator::ServiceStatus::ToString(status));

    SvcContext* svctx = findSvcContext_(_svcid);
    if (svctx)
    {
      svctx->sts = status;
    }
    else
    {
      LOG_E(CALOG).Trace("Service is not registered(svcid=%s)", _svcid.c_str());
    }
  }

  void ClusterAdminImpl::Step()
  {
    svcPublisherIfaceReq->step();
    coordinatorIfaceReq->step();

    if (shutdown_)
    {
      if (NHPTimer::GetScalarTime() - shutdownStart_ > shutdownTimeout_)
      {
        LOG_A(CALOG).Trace("Shutdown command is unsupported for a while");

        //StrongMT<Coordinator::RICoordinatorServerRemote> coord = coordClient_->GetCoordinatorInterface();
        //coord->Shutdown();
        shutdown_ = false;
      }
    }
  }

  ClusterAdminImpl::SvcContext* ClusterAdminImpl::findSvcContext_(Transport::TServiceId const & svcid)
  {
    SvcContextsT::iterator it = nstl::find(contexts.begin(), contexts.end(), SvcContext(svcid));
    if (contexts.end() != it)
    {
      return &(*it);
    }

    return 0;
  }

  void ClusterAdminImpl::onChangeState(rpc::IfaceRequesterState::Enum st, 
    StrongMT<rpc::IfaceRequester<Coordinator::RIServiceAppearancePublisher>> const & ifacereq)
  {
    if (rpc::IfaceRequesterState::OPENED == st)
    {
      LOG_M(CALOG).Trace("Service publisher iface received");

      ifacereq->iface()->RegisterSubscriber(this);
    }
    else
    if (rpc::IfaceRequesterState::CLOSED == st)
    {
      LOG_W(CALOG).Trace("Service publisher iface closed");
      subscriberId = -1;
    }
  }

  void ClusterAdminImpl::onChangeState(rpc::IfaceRequesterState::Enum st, 
    StrongMT<rpc::IfaceRequester<Coordinator::RICoordinatorServerRemote>> const & ifacereq)
  {
    if (rpc::IfaceRequesterState::OPENED == st)
    {
      LOG_M(CALOG).Trace("Coordinator iface received");
    }
    else
    if (rpc::IfaceRequesterState::CLOSED == st)
    {
      LOG_W(CALOG).Trace("Coordinator iface closed");
    }
  }

  void ClusterAdminImpl::OnRegisterSubscriber(Coordinator::SubcriberIdT id, Coordinator::ClusterInfo const & cluster)
  {
    LOG_D(CALOG).Trace("%s(res=%d)", __FUNCTION__, id);

    if (id < 0)
    {
      LOG_E(CALOG).Trace("Can't register self as subscriber(res=%d)", id);
      return;
    }

    subscriberId = id;

    LOG_M(CALOG).Trace("Cluster services:");
    Coordinator::ClusterInfo::SvcInfosT const & svcinfos = cluster.svcinfos;
    for(Coordinator::ClusterInfo::SvcInfosT::const_iterator cit = svcinfos.begin(); cit != svcinfos.end(); ++cit)
    {
      Coordinator::SvcInfo const & si = *cit;
      SvcContext* svctx = findSvcContext_(si.svcid);
      if (!svctx)
      {
        svctx = &(contexts.push_back(SvcContext(si.svcid)));
        svctx->svcid = si.svcid;
      }

      setSvcCtxData_(si, *svctx);

      LOG_M(CALOG).Trace("Service svcid=%s netaddr=%s frontend=%s status=%s)", 
        svctx->svcid.c_str(), svctx->netaddr.c_str(), svctx->frontendaddr.c_str(), Coordinator::ServiceStatus::ToString(svctx->sts));
    }

    LOG_M(CALOG).Trace("Registered as subscriber successfully(id=%d)", id);
  }

  bool ClusterAdminImpl::removeSvcContext_(Transport::TServiceId const & svcid)
  {
    SvcContextsT::iterator it = nstl::find(contexts.begin(), contexts.end(), SvcContext(svcid));
    if (contexts.end() != it)
    {
      contexts.erase(it);
      return true;
    }

    return false;
  }

  void ClusterAdminImpl::GetServices(std::vector<Thrift::ServiceInfo> & _return)
  {
    _return.reserve(contexts.size());
    for(SvcContextsT::iterator it = contexts.begin(); it != contexts.end(); ++it)
    {
      Thrift::ServiceInfo si;
      getServiceInfo_(*it, si);
      _return.push_back(si);
    }
  }

  void ClusterAdminImpl::GetServicesByMachine(std::vector<Thrift::ServiceInfo> & _return, const std::string& machine)
  {
    for(SvcContextsT::iterator it = contexts.begin(); it != contexts.end(); ++it)
    {
      if (NStr::ICmp(it->machineName.c_str(), machine.c_str()) == 0)
      {
        Thrift::ServiceInfo si;
        getServiceInfo_(*it, si);
        _return.push_back(si);
      }
    }
  }

  void ClusterAdminImpl::GetServicesByType(std::vector<Thrift::ServiceInfo> & _return, const std::string& stype)
  {
    for(SvcContextsT::iterator it = contexts.begin(); it != contexts.end(); ++it)
    {
      std::string st;
      getServiceType_(*it, st);
      if (stype == st)
      {
        Thrift::ServiceInfo si;
        getServiceInfo_(*it, si);
        _return.push_back(si);
      }
    }
  }

  void ClusterAdminImpl::GetServiceById(Thrift::ServiceInfo& _return, const std::string& serviceid)
  {
    _return.sid = "";
    SvcContext* svctx = findSvcContext_(serviceid.c_str());
    if(svctx)
    {
      getServiceInfo_(*svctx, _return);
    }
  }

  int32_t ClusterAdminImpl::ExecuteCommand(const std::string& serviceid, const Thrift::ServiceCommand::type command, 
                                           const std::string& arguments)
  {
    if (Thrift::ServiceCommand::STOP == command)
    {
      LOG_M(CALOG).Trace( "Stop service (svcid=%s arguments='%s')", serviceid.c_str(), arguments.c_str() );

      if (coordinatorIfaceReq->isopen() && coordinatorIfaceReq->iface())
      {
        coordinatorIfaceReq->iface()->StopService(serviceid.c_str());
        return 0;
      }
      else
      {
        LOG_M(CALOG).Trace("Can't execute STOP command: coordinator iface is not available(svcid=%s arguments='%s')", 
          serviceid.c_str(), arguments.c_str());
      }
    }
    else if ( command == Thrift::ServiceCommand::RELOAD_CONFIG )
    {
      LOG_M(CALOG).Trace( "Reloading config. svcid=%s, arguments='%s'", serviceid.c_str(), arguments.c_str() );

      if ( coordinatorIfaceReq->isopen() && coordinatorIfaceReq->iface() )
      {
        coordinatorIfaceReq->iface()->ReloadConfig( serviceid.c_str() );
        return 0;
      }
      else
      {
        LOG_M(CALOG).Trace("Can't execute RELOAD_CONFIG command: coordinator iface is not available(svcid=%s arguments='%s')", 
          serviceid.c_str(), arguments.c_str());
      }
    }
    else if (Thrift::ServiceCommand::SOFT_STOP == command)
    {
      LOG_M(CALOG).Trace( "Soft-stop service (svcid=%s arguments='%s')", serviceid.c_str(), arguments.c_str() );

      if (coordinatorIfaceReq->isopen() && coordinatorIfaceReq->iface())
      {
        coordinatorIfaceReq->iface()->SoftStopService(serviceid.c_str());
        return 0;
      }
      else
      {
        LOG_M(CALOG).Trace("Can't execute SOFT_STOP command: coordinator iface is not available(svcid=%s arguments='%s')", 
          serviceid.c_str(), arguments.c_str());
      }
    }

    return -1;
  }

  int32_t ClusterAdminImpl::ChangeParameters(const std::string& serviceid, const std::vector<Thrift::ServiceParameter> & parameters, 
                                             const bool saveinconfig)
  {
    return -1;
  }

  void ClusterAdminImpl::getServiceInfo_(SvcContext const & svctx, Thrift::ServiceInfo & si)
  {
    si.sid = svctx.svcid.c_str();
    {
      Transport::TServiceId svcls;
      Transport::GetServiceClass(svctx.svcid, &svcls);
      si.stype = svcls.c_str();
    }
    si.status = svcStatus2thift_(svctx.sts);
    si.pid = svctx.pid;
    si.machine = svctx.machineName.c_str();
    si.backendaddr = svctx.netaddr.c_str();
    si.frontendaddr = svctx.frontendaddr.c_str();
  }

  void ClusterAdminImpl::getServiceType_(SvcContext const & svctx, std::string & svctype)
  {
    Transport::TServiceId svcls;
    Transport::GetServiceClass(svctx.svcid, &svcls);
    svctype = svcls.c_str();
  }

  Thrift::ServiceStatus::type ClusterAdminImpl::svcStatus2thift_(Coordinator::ServiceStatus::Enum sts)
  {
    switch(sts)
    {
    case Coordinator::ServiceStatus::S_INIT:
    case Coordinator::ServiceStatus::S_STARTING:
      return Thrift::ServiceStatus::START_PENDING;
    case Coordinator::ServiceStatus::S_STARTED:
      return Thrift::ServiceStatus::RUNNING;
    case Coordinator::ServiceStatus::S_STOPPED:
      return Thrift::ServiceStatus::STOPPED;
    case Coordinator::ServiceStatus::S_SOFT_STOPPING:
    case Coordinator::ServiceStatus::S_STOPPING:
      return Thrift::ServiceStatus::WAITING_FOR_STOP;
    case Coordinator::ServiceStatus::S_SOFT_STOPPED:
      return Thrift::ServiceStatus::WAITING_FOR_STOP;
    default:
      NI_ALWAYS_ASSERT("Unknown coordinator service status");
      return Thrift::ServiceStatus::STOPPED;
    }
  }

  void ClusterAdminImpl::setSvcCtxData_(Coordinator::SvcInfo const & si, SvcContext& svctx)
  {
    NI_ASSERT(si.svcid == svctx.svcid, "");

    svctx.pid = si.pid;
    svctx.netaddr = si.netaddr;
    svctx.frontendaddr = si.frontendnetaddr;
    svctx.sts = si.st;
    svctx.machineName = si.machineName;
    svctx.netaddr = si.netaddr.c_str();
    svctx.frontendaddr = si.frontendnetaddr.c_str();
  }
}

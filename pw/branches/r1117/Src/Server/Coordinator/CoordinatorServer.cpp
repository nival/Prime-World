#include "stdafx.h"
#include "CoordinatorServer.h"
#include "Coordinator/CoordinatorClientNaming.h"
#include "LCoordinatorServerIface.auto.h"
#include "RPC/Base.h"

#include "Coordinator/ServiceAppearancePublisher.h"
#include "Coordinator/CoordinatorServerNaming.h"

namespace Coordinator
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CoordinatorServer::CoordinatorServer()
  :shutdown(false),
  srvidCount_(0)
{
  LOG_D(0).Trace("%s", __FUNCTION__);
  serviceAppearanceNotify = new ServiceAppearancePublisher(this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CoordinatorServer::~CoordinatorServer()
{
  LOG_D(0).Trace("%s", __FUNCTION__);
  clientContexts.clear();
}

int CoordinatorServer::Init(const string & coordinatorAddress, StrongMT<rpc::GateKeeper> const & gkeeper)
{
  LOG_D(0).Trace("%s(coordAddr=%s", __FUNCTION__, coordinatorAddress.c_str());

  gateKeeper = gkeeper;

  gateKeeper->GetGate()->RegisterObject(StrongMT<ICoordinatorServerRemote>(this), Coordinator::ServerIfaceId);

  //  set service appearance publisher
  gateKeeper->GetGate()->RegisterObject<Coordinator::IServiceAppearancePublisher>
    ((ServiceAppearancePublisher*)(serviceAppearanceNotify.Get()), Coordinator::SvcAppearancePublisherIfaceId);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CoordinatorServer::SetServicePolicy( Transport::TServiceId intf, const SInterfacePolicy& policy )
{
  LOG_D(0).Trace("%s(intf=%s)", __FUNCTION__, intf.c_str());

  SvcClassInfo& service = svcClassesInfo_.insert( intf )->second;
  service.policy = policy;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StrongMT<SvcContext> 
CoordinatorServer::registerService_(Transport::TServiceId const & _svcls, TServiceRole const & _svcrole, ServerIdT const & _srvid, ServerDef const & _srvdef)
{
  LOG_D(0).Trace("%s(svcls=%s srvid=%d svcpath=%s svcrole=%s)", __FUNCTION__, _svcls.c_str(), _srvid, _srvdef.svcPathBase.c_str(), _svcrole.c_str());

  Transport::TServiceId svcls(_svcls);
  int svcidx = Transport::GetServerIndex(_svcls);
  if (svcidx >= 0)
    Transport::GetServiceClass(_svcls, &svcls);

  SvcClassInfo& sci = svcClassesInfo_[ svcls ];
  Transport::TServiceId svcid;
  if (EServiceInstancing::SINGLE == sci.policy.type)
  {
    svcid = svcls;
  }
  else
  {
    svcidx = ++sci.svcidxCount;
    Transport::GenerateServiceName( svcls, svcidx, &svcid );
  }

  Transport::TServiceId fullsvcid;
  Transport::MakeFullServiceId(_srvdef.svcPathBase, svcid, fullsvcid);
  SvcContextsT::iterator it = svcContexts_.find(fullsvcid);
  if (it != svcContexts_.end())
  {
    StrongMT<SvcContext> const & svctx = it->second;
    if (svctx->isstopped())
    {
      svcContexts_.erase(it);
    }
    else
    {
      LOG_E(0).Trace("%s: service ALREADY exists(svcid=%s status=%s backendaddr=%s frontendaddr=%s srvid=%d svcrole=%s)", 
        __FUNCTION__, fullsvcid.c_str(), ServiceStatus::ToString(svctx->status()), svctx->backendAddr().c_str(), svctx->frontendAddr().c_str(), svctx->srvid(), svctx->svcrole().c_str());
      return 0;
    }
  }

  StrongMT<SvcContext> svctx(new SvcContext(_srvdef.svcPathBase, svcid, _svcrole, _srvid, _srvdef.pid, _srvdef.machineInfo.machineName));
  svcContexts_[svctx->fullsvcid()] = svctx;

  MessageTrace("%s: service registered successfully(svcid=%s backendaddr=%s frontendaddr=%s srvid=%d svcrole=%s)", 
    __FUNCTION__, fullsvcid.c_str(), svctx->backendAddr().c_str(), svctx->frontendAddr().c_str(), svctx->srvid(), svctx->svcrole().c_str());

  return svctx;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CoordinatorServer::ServicesStarted( const ServicesStartInfo& info )
{
  LOG_D(0).Trace("%s(srvid=%d)", __FUNCTION__, info.srvid_);

  StrongMT<ClientContext> const & clctx = FindClientContext(info.srvid_);
  if (!clctx)
  {
    LOG_D(0).Trace("%s. Can't find client context(srvid=%d)", __FUNCTION__, info.srvid_);
    return;
  }

  for( int i = 0; i < info.serviceDefs.size(); ++i ) 
  {
    const ServiceStartInfo & svc = info.serviceDefs[i];

    StrongMT<SvcContext> const & svctx = clctx->findSvcContext(svc.svcid);
    if (svctx)
    {
      routeMap.AddRoute(svc.svcid, SvcNetAddresses(svc.backendAddr, svc.frontendAddr));

      if (ServiceStatus::S_STARTED != svctx->status())
      {
        svctx->backendAddr(svc.backendAddr);
        svctx->frontendAddr(svc.frontendAddr);
        svctx->status(ServiceStatus::S_STARTED);

        serviceAppearanceNotify->OnStartService(Coordinator::SvcInfo(svctx->fullsvcid(), svctx->svcrole(), svctx->backendAddr(), 
          svctx->status(), svctx->frontendAddr(), svctx->pid(), svctx->machineName()));

        MessageTrace("%s. Service started(svcid=%s srvid=%d netaddr=%s frontendaddr=%s)", 
          __FUNCTION__, svc.svcid.c_str(), info.srvid_, svc.backendAddr.c_str(), svc.frontendAddr.c_str());
      }
      else
      {
        LOG_W(0).Trace("%s. Service ALREADY started(svcid=%s srvid=%d netaddr=%s frontendaddr=%s)", 
          __FUNCTION__, svc.svcid.c_str(), info.srvid_, svc.backendAddr.c_str(), svc.frontendAddr.c_str());
      }
    }
    else
    {
      routeMap.AddRoute(svc.svcid, SvcNetAddresses(svc.backendAddr, svc.frontendAddr));
      MessageTrace("%s. Route w/o service added(svcid=%s srvid=%d netaddr=%s frontendaddr=%s)", __FUNCTION__, svc.svcid.c_str(), info.srvid_, svc.backendAddr.c_str(), svc.frontendAddr.c_str());
    }
  }
}

void CoordinatorServer::Shutdown()
{
  MessageTrace("%s()", __FUNCTION__);

  for(ClientContextsT::iterator it = clientContexts.begin(); it != clientContexts.end(); ++it)
  {
    StrongMT<ClientContext> const & clctx = *it;

    ClientContext::SvcContextsT & svcContexts = clctx->svcContexts_;
    for (ClientContext::SvcContextsT::const_iterator cit = svcContexts.begin(); cit != svcContexts.end(); ++cit)
    {
      StrongMT<SvcContext> const & svctx = *cit;

      MessageTrace("%s: stopping service (svcid=%s srvid=%d backendaddr=%s frontendaddr=%s)", 
        __FUNCTION__, svctx->fullsvcid().c_str(), svctx->srvid(), svctx->backendAddr().c_str(), svctx->backendAddr().c_str());

      routeMap.RemoveRoute(svctx->svcid());
      clctx->client()->StopService(svctx->svcid());
    }
    clctx->svcContexts_.clear();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StrongMT<ClientContext> CoordinatorServer::FindClientContext(ServerIdT const & _srvid)
{
  for(ClientContextsT::const_iterator cit = clientContexts.begin(); cit != clientContexts.end(); ++cit)
  {
    StrongMT<ClientContext> const & ctx = *cit;
    if (ctx->srvid_ != _srvid)
      continue;

    return ctx;
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CoordinatorServer::RemoveClient( StrongMT<ClientContext> const & _ctx )
{
  LOG_D(0).Trace("%s(srvid=%d)", __FUNCTION__, _ctx->srvid_);

  ClientContext::SvcContextsT & svcContexts = _ctx->svcContexts_;
  for (ClientContext::SvcContextsT::const_iterator cit = svcContexts.begin(); cit != svcContexts.end(); ++cit)
  {
    StrongMT<SvcContext> const & svctx = *cit;

    if (svctx->isstopped())
      continue;

    svctx->status(ServiceStatus::S_STOPPED);

    if (serviceAppearanceNotify)
    {
      serviceAppearanceNotify->OnStopService(svctx->fullsvcid());
      serviceAppearanceNotify->OnUnregisterService(svctx->fullsvcid());
    }

    routeMap.RemoveRoute(svctx->svcid());
  }

  svcContexts.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CoordinatorServer::StopService(Transport::TServiceId const & _svcid)
{
  LOG_D(0).Trace("%s (svcid=%s)", __FUNCTION__, _svcid.c_str());

  SvcContextsT::iterator it = svcContexts_.find(_svcid);
  if (it != svcContexts_.end())
  {
    StrongMT<SvcContext> const & svctx = it->second;
    StopService_(svctx);
  }
  else
  {
    LOG_E(0).Trace("%s: service NOT FOUND(svcid=%s)", __FUNCTION__, _svcid.c_str());
  }
}

int CoordinatorServer::StopService_(StrongMT<SvcContext> const & _svctx)
{
  LOG_D(0).Trace("%s (svcid=%s)", __FUNCTION__, _svctx->fullsvcid().c_str());

  int rc = -1;
  StrongMT<ClientContext> cctx = FindClientContext(_svctx->srvid());
  if (cctx)
  {
    if (cctx->isopen())
    {
      cctx->client()->StopService(_svctx->svcid());
      _svctx->status(ServiceStatus::S_STOPPING);

      if (serviceAppearanceNotify)
        serviceAppearanceNotify->OnChangeServiceStatus(_svctx->fullsvcid(), ServiceStatus::S_STOPPING);

      rc = 0;
    }
    else
    {
      LOG_W(0).Trace("%s. Coordinator client context is NOT OPENED(svcid=%s srvid=%d ctxstate=%d)", 
        __FUNCTION__, _svctx->fullsvcid().c_str(), _svctx->srvid(), (int)cctx->state());
    }
  }
  else
  {
    LOG_E(0).Trace("%s. Can't find coordinator client context(svcid=%s srvid=%d)", 
      __FUNCTION__, _svctx->fullsvcid().c_str(), _svctx->srvid());
  }

  return rc;
}

void CoordinatorServer::ServiceStopped(Transport::TServiceId const & _svcid)
{
  LOG_D(0).Trace("%s (svcid=%s)", __FUNCTION__, _svcid.c_str());

  
}

void CoordinatorServer::SoftStopService(Transport::TServiceId const & _svcid)
{
  LOG_D(0).Trace("%s (svcid=%s)", __FUNCTION__, _svcid.c_str());

  SvcContextsT::iterator it = svcContexts_.find(_svcid);
  if (it != svcContexts_.end())
  {
    StrongMT<SvcContext> const & svctx = it->second;
    if (svctx->isstarted())
    {
      SoftStopService_(svctx);
    }
    else
    {
      LOG_W(0).Trace("%s: service NOT started(svcid=%s status=%s)", 
        __FUNCTION__, _svcid.c_str(), ServiceStatus::ToString(svctx->status()));
    }
  }
  else
  {
    LOG_E(0).Trace("%s: service NOT FOUND(svcid=%s)", __FUNCTION__, _svcid.c_str());
  }
}

int CoordinatorServer::SoftStopService_(StrongMT<SvcContext> const & _svctx)
{
  LOG_D(0).Trace("%s (svcid=%s)", __FUNCTION__, _svctx->fullsvcid().c_str());

  int rc = -1;
  StrongMT<ClientContext> cctx = FindClientContext(_svctx->srvid());
  if (cctx)
  {
    if (cctx->isopen())
    {
      cctx->client()->SoftStopService(_svctx->svcid());
      _svctx->status(ServiceStatus::S_SOFT_STOPPING);

      if (serviceAppearanceNotify)
        serviceAppearanceNotify->OnChangeServiceStatus(_svctx->fullsvcid(), ServiceStatus::S_SOFT_STOPPING);

      rc = 0;
    }
    else
    {
      LOG_W(0).Trace("%s. Coordinator client context is NOT OPENED(svcid=%s srvid=%d ctxstate=%d)", 
        __FUNCTION__, _svctx->fullsvcid().c_str(), _svctx->srvid(), (int)cctx->state());
    }
  }
  else
  {
    LOG_E(0).Trace("%s. Can't find coordinator client context(svcid=%s srvid=%d)", 
      __FUNCTION__, _svctx->fullsvcid().c_str(), _svctx->srvid());
  }

  return rc;
}



void CoordinatorServer::ReloadConfig( const Transport::TServiceId & _svcid )
{
  LOG_D(0).Trace("%s (svcid=%s)", __FUNCTION__, _svcid.c_str());

  bool fReconfigSvcClass = false;
  if (_svcid.size())
    fReconfigSvcClass = ('*' == _svcid.At(_svcid.size() - 1)); //  reconfigurate all sevices of given service class

  if (fReconfigSvcClass)
  {
    MessageTrace("%s: reconfiguration by service class(svcid=%s)", 
      __FUNCTION__, _svcid.c_str());

    Transport::TServiceId svcls;
    if (Transport::GetServiceClass(_svcid, svcls))
    {
      bool bfound = false;
      for(SvcContextsT::const_iterator cit = svcContexts_.begin(); cit != svcContexts_.end(); ++cit)
      {
        StrongMT<SvcContext> const & svctx = cit->second;
        if (svcls == svctx->svcls() && svctx->isstarted())
        {
          ReloadConfig_(svctx);
          bfound = true;
        }
      }

      if (!bfound)
        LOG_W(0).Trace("%s: no service found with such service class(svcid=%s svcls=%s)", 
          __FUNCTION__, _svcid.c_str(), svcls.c_str());
    }
    else
    {
      LOG_E(0).Trace("%s: can't extract service class from service id(svcid=%s)", 
        __FUNCTION__, _svcid.c_str());
    }
  }
  else
  {
    SvcContextsT::iterator it = svcContexts_.find(_svcid);
    if (it != svcContexts_.end())
    {
      StrongMT<SvcContext> const & svctx = it->second;
      if (svctx->isstarted())
      {
        ReloadConfig_(svctx);
      }
      else
      {
        LOG_W(0).Trace("%s: service NOT started(svcid=%s status=%s)", 
          __FUNCTION__, _svcid.c_str(), ServiceStatus::ToString(svctx->status()));
      }
    }
    else
    {
      LOG_E(0).Trace("%s: service NOT FOUND(svcid=%s)", __FUNCTION__, _svcid.c_str());
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CoordinatorServer::OnNewNode( Transport::IChannel * channel,  rpc::Node * node )
{
  Transport::TServiceId const & source = channel->GetAddress().source;
  LOG_M(0) << "Coordinator: server connected: '" << source.c_str() << "'";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CoordinatorServer::OnChannelClosed( Transport::IChannel * channel,  rpc::Node * node )
{
  Transport::TServiceId const & source = channel->GetAddress().source;
  LOG_W(0) << "Coordinator: channel closed from '" << source.c_str() << "'";

  if (NStr::NCmp(source.c_str(), coordClientNamePrefix.c_str(), coordClientNamePrefix.length()) != 0)
    return;

  routeMap.RemoveSlaveCorpses();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CoordinatorServer::OnCorruptData( Transport::IChannel * channel,  rpc::Node * node )
{
  LOG_A(0) << "Coordinator: corrupted packet received from '" << channel->GetAddress().source.c_str() << "'";
  channel->Close();
}



void CoordinatorServer::Step()
{
  //  check disconnected coordinator clients
  for( ClientContextsT::iterator it = clientContexts.begin(); it != clientContexts.end(); )
  {
    StrongMT<ClientContext> const & cctx = *it;
    cctx->step();
    if (cctx->isclose())
    {
      RemoveClient( cctx );
      it = clientContexts.erase( it );
    }
    else
      ++it;
  }
}



void CoordinatorServer::GetClusterSvcInfo(ClusterInfo & csi)
{
  LOG_D(0).Trace("%s()", __FUNCTION__);

  for (SvcContextsT::const_iterator cit = svcContexts_.begin(); cit != svcContexts_.end(); ++cit)
  {
    StrongMT<SvcContext> const & svctx = cit->second;
    csi.svcinfos.push_back(Coordinator::SvcInfo(svctx->fullsvcid(), svctx->svcrole(), svctx->backendAddr(), 
      svctx->status(), svctx->frontendAddr(), svctx->pid(), svctx->machineName()));
  }
}

void CoordinatorServer::RegisterClient(Coordinator::ServerIdT _srvid, ICoordinatorClientRemote* _ccr, 
                                       ServerDef const & _serverdef, IRegisterClientCallback* _cb)
{
  LOG_D(0).Trace("%s(srvid=%d pid=%d machineName=%s)", 
    __FUNCTION__, _srvid, _serverdef.pid, _serverdef.machineInfo.machineName.c_str());

  StrongMT<ClientContext> ctx;
  int rc = RegisterClient_(_srvid, StrongMT<RICoordinatorClientRemote>(reinterpret_cast<RICoordinatorClientRemote*>(_ccr)), _serverdef, ctx);
  if (rc < 0)
  {
    _cb->OnRegisterClient(rc, INVALID_SERVER_ID);
  }
  else
  {
    _cb->OnRegisterClient(rc, ctx->srvid_);

    //  starting services
    for(ClientContext::SvcContextsT::iterator it = ctx->svcContexts_.begin(); it != ctx->svcContexts_.end(); ++it)
    {
      StrongMT<SvcContext> const & svctx = *it;
      if (ServiceStatus::S_INIT == svctx->status())
      {
        serviceAppearanceNotify->OnRegisterService(svctx->fullsvcid());

        ctx->client()->StartService(svctx->svcid());
        svctx->status(ServiceStatus::S_STARTING);
      }
    }
  }
}

int CoordinatorServer::RegisterClient_(Coordinator::ServerIdT _srvid, StrongMT<RICoordinatorClientRemote> const & _client, 
                                       ServerDef const & _serverdef,
                                       StrongMT<ClientContext> & _ctx)
{
  MessageTrace("%s(srvid=%d pid=%d machineName=%s)", 
    __FUNCTION__, _srvid, _serverdef.pid, _serverdef.machineInfo.machineName.c_str());

  int rc = -1;
  if (!_client)
  {
    LOG_E(0).Trace("%s. Client is NULL(srvid=%d pid=%d machineName=%s)", 
      __FUNCTION__, _srvid, _serverdef.pid, _serverdef.machineInfo.machineName.c_str());
    return rc;
  }

  //  get/create client context
  rc = 0;
  StrongMT<ClientContext> cctx;
  if (INVALID_SERVER_ID != _srvid)
  {
    for( ClientContextsT::iterator it = clientContexts.begin(); it != clientContexts.end(); ++it )
    {
      StrongMT<ClientContext> const & ctx = *it;
      if (ctx->srvid_ == _srvid)
      {
        if (!ctx->isclose())
        {
          cctx = ctx;
          cctx->client(_client);
          MessageTrace( "%s. Client context found(srvid=%d)", __FUNCTION__, _srvid);
        }
        else
        {
          LOG_E(0).Trace( "%s. The client context is ALREADY closed(srvid=%d)", __FUNCTION__, _srvid );
          rc = -1;
        }
        break;
      }
    }
    if (!cctx)
    {
      LOG_E(0).Trace( "%s. Such client is NOT registered(srvid=%d)", __FUNCTION__, _srvid );
      rc = -1;
    }
  }
  else
  {
    cctx = new ClientContext(_client);
    cctx->srvid_ = ++srvidCount_;
    cctx->serverDef = _serverdef;

    MessageTrace( "%s. New client context created (srvid=%d pid=%d machineName=%s)", 
      __FUNCTION__, cctx->srvid_, _serverdef.pid, _serverdef.machineInfo.machineName.c_str() );
  }

  if (rc < 0)
    return rc;

  routeMap.AddSlave( _client );

  if (INVALID_SERVER_ID == _srvid)
  {
    rc = 0;
    for ( int i = 0; i < _serverdef.svcdefs.size() && rc >= 0; ++i )
    {
      Transport::TServiceId const & svcls = _serverdef.svcdefs[i].svcid;
      TServiceRole const & svcrole = _serverdef.svcdefs[i].role;
      SvcClassInfo& service = svcClassesInfo_[ svcls ];
      StrongMT<SvcContext> svctx;

      switch( service.policy.type )
      {
      case EServiceInstancing::SINGLE:
        {
          svctx = registerService_(svcls, svcrole, cctx->srvid_, _serverdef);
        }
        break;
      case EServiceInstancing::MULTIPLE:
        {
          svctx = registerService_(svcls, svcrole, cctx->srvid_, _serverdef);
        }
        break;
      default:
        {
          LOG_A(0).Trace("Incorrect policy type(svccls=%s)", svcls.c_str());
          rc = -1;
        }
        break;
      }

      if (svctx)
        cctx->svcContexts_.push_back(svctx);
      else
        rc = -1;
    }
  }

  if (rc < 0)
  {
    RemoveClient( cctx );
    cctx = 0;

    LOG_E(0).Trace( "%s. Client registration is FAILED(srvid=%d pid=%d machineName=%s)", 
      __FUNCTION__, _srvid, _serverdef.pid, _serverdef.machineInfo.machineName.c_str() );
  }
  else
  {
    clientContexts.push_back( cctx );
    routeMap.InitSlave( cctx->client() ); // обновляем клиенту данные, которые он действительно хочет (routes)

    MessageTrace( "%s. New client completely registered(srvid=%d pid=%d machineName=%s)", 
      __FUNCTION__, cctx->srvid_, _serverdef.pid, _serverdef.machineInfo.machineName.c_str() );
  }

  _ctx = cctx;
  return rc;
}

int CoordinatorServer::ReloadConfig_(StrongMT<SvcContext> const & _svctx)
{
  MessageTrace("%s(svcid=%s backendaddr=%s frontendaddr=%s)", 
    __FUNCTION__, _svctx->fullsvcid().c_str(), _svctx->backendAddr().c_str(), _svctx->frontendAddr().c_str());

  int rc = -1;
  StrongMT<ClientContext> cctx = FindClientContext(_svctx->srvid());
  if (cctx)
  {
    if (cctx->isopen())
    {
      MessageTrace("%s. Reloading config started(svcid=%s backendaddr=%s frontendaddr=%s)", 
        __FUNCTION__, _svctx->fullsvcid().c_str(), _svctx->backendAddr().c_str(), _svctx->frontendAddr().c_str());

      cctx->client()->ReloadConfig(_svctx->svcid());

      rc = 0;
    }
    else
    {
      LOG_W(0).Trace("%s. Coordinator client context is NOT OPENED(svcid=%s srvid=%d ctxstate=%d backendaddr=%s frontendaddr=%s)", 
        __FUNCTION__, _svctx->fullsvcid().c_str(), _svctx->srvid(), (int)cctx->state(), _svctx->backendAddr().c_str(), _svctx->frontendAddr().c_str());
    }
  }
  else
  {
    LOG_E(0).Trace("%s. Can't find coordinator client context for service(svcid=%s srvid=%d backendaddr=%s frontendaddr=%s)", 
      __FUNCTION__, _svctx->fullsvcid().c_str(), _svctx->srvid(), _svctx->backendAddr().c_str(), _svctx->frontendAddr().c_str());
  }

  return rc;
}

}

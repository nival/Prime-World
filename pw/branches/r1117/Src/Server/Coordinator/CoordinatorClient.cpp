#include "stdafx.h"
#include "CoordinatorClient.h"
#include "CoordinatorServerNaming.h"
#include "Coordinator/RCoordinatorServerIface.auto.h"
#include "Coordinator/LCoordinatorServerIface.auto.h"
#include "Coordinator/RCoordinatorClientIface.auto.h"
#include "Coordinator/LCoordinatorClientIface.auto.h"
#include "Network/TransportAddress.h"
#include "UserManager/UserManagerSvc/LUserNotificationIface.auto.h"
#include "UserManager/UserManagerAgent/UserManagerAgent.h"
#include "System/ConfigFiles.h"
#include "CoordinatorClientInternals.h"
#include <map>
#if defined( NV_LINUX_PLATFORM )
#include <sys/types.h>
#include <unistd.h>
#endif // defined( NV_LINUX_PLATFORM )


namespace Coordinator
{

static bool s_userManagerAgentOn = true;
REGISTER_VAR( "user_manager_agent_on", s_userManagerAgentOn, STORAGE_GLOBAL);


void LoadServiceConfig( const char * svcClass )
{
  string cfgName = NI_STRFMT( "pvx_srv_%s.cfg", svcClass );

  NGlobal::ExecuteConfig( cfgName.c_str(), NProfile::FOLDER_GLOBAL );
}




// Интерфейс ICoordinatorClient реализует отдельный объект для предотвращения кольцевой ссылки:
//
// Strong-указатель на ICoordinatorClient хранят в себе все сервисы
// А сервисы создает и хранит в себе объект CoordinatorClient
class CoordinatorClientInterface : public ICoordinatorClient, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( CoordinatorClientInterface, ICoordinatorClient, BaseObjectMT );

public:
  CoordinatorClientInterface( CoordinatorClient * _owner, Transport::IAddressTranslator * _bat, Transport::IAddressTranslator * _fat ) :
  owner( _owner ),
  backendAT( _bat ), frontendAT( _fat )
  {}

  void SetUMA( UserManager::IUserManagerAgent * _uma ) { uma = _uma; }

  //ICoordinatorClient
  virtual UserManager::IUserManagerAgent * GetUserManagerAgent() const { return uma; }
  virtual Transport::IAddressTranslator * GetBackendAddressTranslator() const { return backendAT; }
  virtual Transport::IAddressTranslator * GetFrontendAddressTranslator() const { return frontendAT; }
  virtual void AddExplicitRoute( const Transport::TServiceId & _service, const SvcNetAddresses & _addrs )
  {
    StrongMT<CoordinatorClient> locked = owner.Lock();
    NI_VERIFY( locked, "", return );
    locked->AddRoute( _service, _addrs );
  }

private:
  WeakMT<CoordinatorClient> owner;
  StrongMT<UserManager::IUserManagerAgent> uma;
  StrongMT<Transport::IAddressTranslator> backendAT, frontendAT;
};





class CoordinatorClient::CoordinatorClientRemoteProxy : public ICoordinatorClientRemote, public IRegisterClientCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( CoordinatorClientRemoteProxy, ICoordinatorClientRemote, IRegisterClientCallback, BaseObjectMT );

public:
  CoordinatorClientRemoteProxy( CoordinatorClient * _owner ) :
  owner( _owner )
  {}

  //mirror of ICoordinatorClientRemote
  virtual void AddRoute( const Transport::TServiceId& service, SvcNetAddresses const & addrs )  { if ( StrongMT<CoordinatorClient> locked = owner.Lock() ) locked->AddRoute( service, addrs ); }
  virtual void RemoveRoute( const Transport::TServiceId& service )                              { if ( StrongMT<CoordinatorClient> locked = owner.Lock() ) locked->RemoveRoute( service ); }
  virtual void StartService( const Transport::TServiceId & serviceIdToStart )                   { if ( StrongMT<CoordinatorClient> locked = owner.Lock() ) locked->StartService( serviceIdToStart ); }
  virtual void StopService( const Transport::TServiceId & serviceIdToStop )                     { if ( StrongMT<CoordinatorClient> locked = owner.Lock() ) locked->StopService( serviceIdToStop ); }
  virtual void SoftStopService( Transport::TServiceId const & _svcid )                          { if ( StrongMT<CoordinatorClient> locked = owner.Lock() ) locked->SoftStopService( _svcid ); }
  virtual void ReloadConfig( const Transport::TServiceId & service )                            { if ( StrongMT<CoordinatorClient> locked = owner.Lock() ) locked->ReloadConfig( service ); }
  virtual unsigned int Ping(unsigned int i)                                                     { if ( StrongMT<CoordinatorClient> locked = owner.Lock() ) return locked->Ping( i ); else return 0; };

  //mirror of IRegisterClientCallback
  virtual void OnRegisterClient(int _result, ServerIdT _clientid)                               { if ( StrongMT<CoordinatorClient> locked = owner.Lock() ) locked->OnRegisterClient( _result, _clientid ); }

private:
  WeakMT<CoordinatorClient> owner;
};






CoordinatorClient::CoordinatorClient( const Transport::TServiceId & _svcpath, Network::INetworkDriver * _netDriver ) :
netdrv( _netDriver ),
st_(ClientState::INIT),
clientid_(INVALID_SERVER_ID)
{
  coordSrvIfaceReq = new rpc::IfaceRequester<RICoordinatorServerRemote>;
  serverDef_.svcPathBase = _svcpath;
#if defined( NV_WIN_PLATFORM )
  serverDef_.pid = ::GetCurrentProcessId();
#elif defined( NV_LINUX_PLATFORM )
  serverDef_.pid = ::getpid();
#endif

  remoteProxy = new CoordinatorClientRemoteProxy( this );

  classRoutes = new ClassRoutes;
  backendTranslator = new AddressTranslator( "backend", classRoutes );
  frontendTranslator = new AddressTranslator( "frontend", classRoutes );

  interfaceObject = new CoordinatorClientInterface( this, backendTranslator, frontendTranslator );
}



CoordinatorClient::~CoordinatorClient()
{
}



ICoordinatorClient * CoordinatorClient::GetInterface() const
{
  return interfaceObject;
}



void CoordinatorClient::SetIps( const Network::NetAddress & _backend, const Network::NetAddress & _frontend )
{
  backendTranslator->SetServerIp( _backend );
  frontendTranslator->SetServerIp( _frontend );
}



int CoordinatorClient::Open( Transport::ITransportSystem * _backendTransport, Transport::ITransportSystem * _frontendTransport, rpc::GateKeeper * _gk )
{
  backendTransport = _backendTransport;
  frontendTransport = _frontendTransport;
  gk = _gk;

  Reset( rpcFactory, new rpc::LocalEntityFactory( _gk->GetGate() ) );
  rpcFactory->RegisterAttach<Coordinator::ICoordinatorClientRemote, Coordinator::LICoordinatorClientRemote>();
  rpcFactory->RegisterAttach<Coordinator::IRegisterClientCallback, Coordinator::LIRegisterClientCallback>();
  rpcFactory->RegisterAttach<UserManager::IUserNotificationSubscriber, UserManager::LIUserNotificationSubscriber>();

  int rc = coordSrvIfaceReq->init(_gk, Transport::ENetInterface::Coordinator, Coordinator::ServerIfaceId, &GetSystemLog(), 0, this);
  if (rc < 0)
  {
    ErrorTrace( "Can't init rpc iface requester(node=%s iface=%s)", Transport::ENetInterface::Coordinator.c_str(), Transport::ENetInterface::Coordinator.c_str() );
    return rc;
  }

  st_ = ClientState::OPENING;
  return rc;
}



void CoordinatorClient::AddRoute( const Transport::TServiceId & service, SvcNetAddresses const & addrs )
{
  if ( !addrs.backendaddr.empty() )
    backendTranslator->AddRoute( service, addrs.backendaddr );

  if ( !addrs.frontendaddr.empty() )
    frontendTranslator->AddRoute( service, addrs.frontendaddr );
}



void CoordinatorClient::RemoveRoute( const Transport::TServiceId& service )
{
  backendTranslator->RemoveRoute( service );
  frontendTranslator->RemoveRoute( service );
}



void CoordinatorClient::AddServiceInstance( Transport::IServiceSpawner * _spawner, Transport::IServerRunner * _runner, const Transport::ServiceOptions & _options )
{
  services.push_back( new Service( _spawner, _runner, _options ) );
}



CoordinatorClient::Service * CoordinatorClient::FindNotStartedService( const Transport::TServiceId & _svcClass )
{
  for ( TServices::iterator it = services.begin(); it != services.end(); ++it )
  {
    Service * svc = *it;
    if ( svc->spawner->ServiceClass() == _svcClass )
      if ( svc->state == EServiceState::Stopped )
        return svc;
  }
  return 0;
}



CoordinatorClient::Service * CoordinatorClient::FindServiceById( const Transport::TServiceId & _svcId )
{
  for ( TServices::iterator it = services.begin(); it != services.end(); ++it )
  {
    Service * svc = *it;
    if ( svc->id == _svcId )
      return svc;
  }
  return 0;
}



void CoordinatorClient::StartService( const Transport::TServiceId& serviceIdToStart )
{
  Transport::TServiceId serviceClass;
  Transport::GetServiceClass( serviceIdToStart, &serviceClass );

  Service * svc = FindNotStartedService( serviceClass );
  if ( !svc )
  {
    ErrorTrace( "Failed to find service to start. svcid=%s", serviceIdToStart.c_str() );
    return;
  }

  svc->id = serviceIdToStart;

  const bool extService = ( svc->spawner->Policy().flags & Coordinator::ESvcFlags::EXTERNAL ) ? true : false;

  Transport::ServiceParams params( svc->options );
  params.serviceId = serviceIdToStart;
  params.backendTransport = backendTransport;
  params.frontendTransport = extService ? frontendTransport : 0;
  params.driver = netdrv;
  params.coordClient = interfaceObject;
  svc->runner->StartInstance( params );

  ServicesStartInfo info;
  PopNewRoutes( info );

  info.srvid_ = clientid_;

  coordSrvIfaceReq->iface()->ServicesStarted( info );

  svc->state = EServiceState::Started;
}



void CoordinatorClient::StopService( const Transport::TServiceId & serviceIdToStop )
{
  LOG_M(0).Trace("%s (svcid=%s)", __FUNCTION__, serviceIdToStop.c_str());

  Service * svc = FindServiceById( serviceIdToStop );

  if ( !svc )
  {
    ErrorTrace( "Trying to stop unknown service. svcid=%s", serviceIdToStop.c_str() );
    return;
  }

  svc->runner->StopInstance( serviceIdToStop );
  svc->state = EServiceState::Stopped;

  coordSrvIfaceReq->iface()->ServiceStopped(serviceIdToStop);
}



void CoordinatorClient::SoftStopService( Transport::TServiceId const & _svcid )
{
  LOG_M(0).Trace("%s (svcid=%s)", __FUNCTION__, _svcid.c_str());

  Service * svc = FindServiceById( _svcid );
  if ( !svc )
  {
    ErrorTrace( "Trying to stop unknown service. svcid=%s", _svcid.c_str() );
    return;
  }
  svc->runner->SoftStopInstance(_svcid);
  svc->state = EServiceState::Soft_Stopped;
}



void CoordinatorClient::ReloadConfig( const Transport::TServiceId & svcId )
{
  Service * svc = FindServiceById( svcId );

  if ( !svc )
  {
    ErrorTrace( "Trying to reload config of unknown service. svcid=%s", svcId.c_str() );
    return;
  }

  if ( !( svc->spawner->Policy().flags & Coordinator::ESvcFlags::CAN_RELOAD_CFG ) )
  {
    ErrorTrace( "Trying to reload config of service that does not support reload. svcid=%s", svcId.c_str() );
    return;
  }

  MessageTrace( "Reloading config. svcid=%s", svcId.c_str() );

  Transport::TServiceId svccls;
  Transport::GetServiceClass( svcId, &svccls );
  LoadServiceConfig( svccls.c_str() );

  MessageTrace( "Notifing service about new config. svcid=%s", svcId.c_str() );
  svc->runner->OnConfigReload();
}



unsigned int CoordinatorClient::Ping( unsigned int _param )
{
  return _param;
}



void CoordinatorClient::OnRegisterClient(int _result, ServerIdT _clientid)
{
  LOG_M(0).Trace("%s(rc=%d srvid=%d)", __FUNCTION__, _result, _clientid);

  if (_result >= 0)
  {
    clientid_ = _clientid;
    st_ = ClientState::OPEN;

    if ( s_userManagerAgentOn )
    {
      userManagerAgent = new UserManager::UserManagerAgent( gk, _clientid );
      interfaceObject->SetUMA( userManagerAgent );
    }
  }
  else
  {
    st_ = ClientState::CLOSE;
  }
  return;
}



void CoordinatorClient::onChangeState(rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<RICoordinatorServerRemote> > const & _ifacereq)
{
  if (rpc::IfaceRequesterState::OPENED == _st)
  {
    if (INVALID_SERVER_ID == clientid_)
      for ( TServices::iterator it = services.begin(); it != services.end(); ++it )
      {
        Service * svc = *it;
        serverDef_.svcdefs.push_back( ServiceDef( svc->spawner->ServiceClass(), svc->runner->GetRole() ) );
      }

    coordSrvIfaceReq->iface()->RegisterClient( clientid_, remoteProxy, serverDef_, remoteProxy );
  }
  else if (rpc::IfaceRequesterState::CLOSED == _st)
  {
  }
}



void CoordinatorClient::step()
{
  coordSrvIfaceReq->step();

  if (userManagerAgent)
    userManagerAgent->Step();
}



void CoordinatorClient::PopNewRoutes( ServicesStartInfo & _startInfo ) const
{
  AddressTranslator::TRouteMap newBackendRoutes, newFrontendRoutes;
  backendTranslator->PopFreshRoutes( newBackendRoutes );
  frontendTranslator->PopFreshRoutes( newFrontendRoutes );

  DebugTrace( "Flushing fresh routes. backend_num=%d, frontend_num=%d", newBackendRoutes.size(), newFrontendRoutes.size() );

  set<Transport::TServiceId> allNewServices;
  for ( AddressTranslator::TRouteMap::iterator it = newBackendRoutes.begin(); it != newBackendRoutes.end(); ++it )
    allNewServices.insert( it->first );
  for ( AddressTranslator::TRouteMap::iterator it = newFrontendRoutes.begin(); it != newFrontendRoutes.end(); ++it )
    allNewServices.insert( it->first );

  for ( set<Transport::TServiceId>::const_iterator it = allNewServices.begin(); it != allNewServices.end(); ++it )
  {
    ServiceStartInfo ssi;
    ssi.svcid = *it;

    AddressTranslator::TRouteMap::iterator backendIt = newBackendRoutes.find( ssi.svcid );
    if ( backendIt != newBackendRoutes.end() )
      ssi.backendAddr = backendIt->second;

    AddressTranslator::TRouteMap::iterator frontendIt = newFrontendRoutes.find( ssi.svcid );
    if ( frontendIt != newFrontendRoutes.end() )
      ssi.frontendAddr = frontendIt->second;

    MessageTrace( "Started svc info. svcid=%s, netaddr=%s, frontend=%s", ssi.svcid.c_str(), ssi.backendAddr, ssi.frontendAddr );
    _startInfo.serviceDefs.push_back( ssi );
  }
}

} //namespace Coordinator


NI_DEFINE_REFCOUNT(Coordinator::CoordinatorClient);
NI_DEFINE_REFCOUNT(Coordinator::ICoordinatorClient);

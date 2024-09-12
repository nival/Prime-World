#include "stdafx.h"
#include "NivalServerBase.h"
#include "ServerCfg.h"

#include "Server/LogMonitorAgent/LogMonitorAgent.h"
#include "Server/LogMonitorAgent/LogMonitorConfig.h"

#include "Network/ClusterConfiguration.h"
#include "Network/Initializer.h"
#include "Network/StreamAllocator.h"

#include "Coordinator/ConfigServiceOption.h"

#include "transport/TLTransportModule.h"
#include "transport/TLCfg.h"

#include "System/sleep.h"

#if defined( NV_WIN_PLATFORM )
#include "RdpTransport/RdpTransport.h"
#include "RdpTransport/RdpFrontendTransport.h"

#include "Network/RUDP/UdpAddr.h"
#endif

namespace Transport
{

//TEMP: Used for external services (e.g. 'statistics')
class NullServiceSpawner : public DefaultServiceSpawnerBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( NullServiceSpawner, DefaultServiceSpawnerBase );
public:
  NullServiceSpawner( const TServiceId & _serviceClass, const Coordinator::SInterfacePolicy & _policy ) :
  DefaultServiceSpawnerBase( _serviceClass, 0, _policy )
  {}

  virtual bool ServiceIsExternal() const { return true; }
  virtual IServerRunner * SpawnService() const { return 0; }
};





NivalServerBase::NivalServerBase() :
startCoordinator( false ),
showNetStat( false )
{
  svcpath = HostServer::Cfg::GetSvcPath().c_str();
}



NivalServerBase::~NivalServerBase() 
{
  Shutdown();
}



bool NivalServerBase::Startup( const TStartList & _startList, const TServerCmdLine & _serverCmdLine )
{
  LoadConfigs( _startList );

  StartLogMonitor( _startList );

  // Network initialization
  netDriver = Network::Initialize();
  netDriver->SetTrafficType( Network::EDriverTrafficType::Light ); // было Heavy == 750К буферов на каждый несчастный Connection

  netDriver->SetStreamAllocator( new Network::StreamAllocator() );

  coordinatorClientRunner = new Coordinator::CoordinatorClientRunner( svcpath, netDriver );

  if ( !StartTransport( _startList, _serverCmdLine ) )
    return false;

  if ( startCoordinator )
    if ( !StartCoordinatorService() )
      return false;

  if ( !SpawnServices( _startList, _serverCmdLine ) )
    return false;

  return true;
}



bool NivalServerBase::StartTransport( const TStartList & _startList, const TServerCmdLine & _serverCmdLine )
{
  NI_VERIFY( coordinatorClientRunner, "", return false );

#if defined( NV_WIN_PLATFORM )
  if ( rdp_transport::RdpTransportEnabled() )
  {
    MessageTrace( "Starting RDP transport" );

    bool hadExternalServices = false;
    for ( TStartList::const_iterator it = _startList.begin(); it != _startList.end(); ++it )
      if ( (*it).spawner->Policy().flags & Coordinator::ESvcFlags::EXTERNAL )
        hadExternalServices = true;

    StrongMT<Coordinator::ICoordinatorClient> coordClient = coordinatorClientRunner->GetClient()->GetInterface();

    ni_udp::NetAddr backendAddr( Network::GetBackendIPAddr().c_str(), Network::GetFirstServerPort() );
    backendTransport = new rdp_transport::BackendTransport( Transport::GetGlobalMessageFactory(), coordClient->GetBackendAddressTranslator(), backendAddr, "backend" );

    if ( hadExternalServices )
    {
      ni_udp::NetAddr frontendAddr( Network::GetFrontendIPAddr().c_str(), Network::GetFirstServerPort() );
      frontendTransport = new rdp_transport::PrimaryFrontend( Transport::GetGlobalMessageFactory(), coordClient->GetFrontendAddressTranslator(), frontendAddr );
    }
  }
  else
#endif
  {
    MessageTrace( "Starting TCP/IP transport" );

    TL::Cfg cfg;
    cfg.firstServerPort = Network::GetFirstServerPort();
    cfg.mf_ = Transport::GetGlobalMessageFactory();
    cfg.at_ = coordinatorClientRunner->GetClient()->GetInterface()->GetBackendAddressTranslator();
    cfg.threads_ = TL::GlobalCfg::GetThreads();
    cfg.loglvl_ = TL::GlobalCfg::GetLogLevel();
    cfg.terabit_loglvl_ = TL::GlobalCfg::GetTerabitLogLevel();
    cfg.read_block_size_ = TL::GlobalCfg::GetReadBlockSize();
    cfg.so_rcvbuf_ = TL::GlobalCfg::GetSoRcvbuf();
    cfg.so_sndbuf_ = TL::GlobalCfg::GetSoSndbuf();
    cfg.disableNagleAlgorithm_ = TL::GlobalCfg::GetDisableNagleAlgorithm();
    cfg.so_keepalive_ = TL::GlobalCfg::GetSoKeepalive();
    cfg.mbHeapDumpFreq_ = TL::GlobalCfg::GetMessageBlockHeapDumpFreq();
    cfg.mbHeapPerConnection_ = TL::GlobalCfg::GetMessageBlockHeapPerConnection();
    cfg.mbNotypeUseThreshold_ = TL::GlobalCfg::GetMessageBlockNotypeUseThreshold();
    cfg.mbWriteUseThreshold_ = TL::GlobalCfg::GetMessageBlockWriteUseThreshold();
    cfg.mbReadUseThreshold_ = TL::GlobalCfg::GetMessageBlockReadUseThreshold();
    cfg.logWrittenBytes_ = TL::GlobalCfg::GetLogWrittenBytes();
    cfg.checkActivityTimeout_ = TL::GlobalCfg::GetCheckActivityTimeout();

    aioTransport = TransportLayer::CreateTransportSystem(cfg);
    backendTransport = aioTransport;
  }

  return true;
}



bool NivalServerBase::StartCoordinatorService()
{
  coordinatorSvcJob = new Coordinator::CoordinatorServerJob( BackendTransport(), Network::GetCoordinatorAddress() );

  for ( ServiceSpawners::iterator it = Spawners().begin(); it != Spawners().end(); ++it )
  {
    IServiceSpawner * spn = it->second;
    coordinatorSvcJob->GetServer()->SetServicePolicy( spn->ServiceClass(), spn->Policy() );
  }

  coordinatorSvcThread = new threading::JobThread( coordinatorSvcJob, "CoordSvc" );
  return true;
}



void NivalServerBase::StartLogMonitor( const TStartList & _startList )
{
  set<string> svcClasses;

  for ( TStartList::const_iterator it = _startList.begin(); it != _startList.end(); ++it )
  {
    StrongMT<IServiceSpawner> spawner = it->spawner;
    const TServiceId & serviceClass = spawner->ServiceClass();
    svcClasses.insert( serviceClass.c_str() );
  }

  string svcNames;
  for ( set<string>::const_iterator it = svcClasses.begin(); it != svcClasses.end(); ++it )
  {
    if ( !svcNames.empty() )
      svcNames += "_";
    svcNames += *it;
  }

  //special ugly case
  if ( svcNames.empty() )
    svcNames = "coordinator";

  StrongMT<logMonitor::Agent> agent = new logMonitor::Agent( logMonitor::CreateConfigFromStatics(), svcNames.c_str() );

  logMonitorAgent = new logMonitor::AgentParallelPoller( agent );
}



void NivalServerBase::LoadConfigs( const TStartList & _startList )
{
  set<string> configNames;
  for ( TStartList::const_iterator it = _startList.begin(); it != _startList.end(); ++it )
  {
    const ServiceStartupInfo & ssi = *it;

    if ( ssi.spawner->Policy().flags & Coordinator::ESvcFlags::HAS_NO_CFG )
      continue;

    configNames.insert( ssi.spawner->ServiceClass().c_str() );
  }

  MessageTrace( "%d configs to load", configNames.size() );
  for( set<string>::const_iterator it = configNames.begin(); it != configNames.end(); ++it )
  {
    MessageTrace( "Loading config for service '%s'...", it->c_str() );
    Coordinator::LoadServiceConfig( it->c_str() );
  }
}



bool NivalServerBase::SpawnServices( const TStartList & _startList, const TServerCmdLine & _serverCmdLine )
{
  StrongMT<Coordinator::CoordinatorClient> cli = coordinatorClientRunner->GetClient();

  cli->SetIps( Network::GetBackendIPAddr(), Network::GetFrontendIPAddr() );
  MessageTrace( "IP addresses: backend=%s, frontend=%s", Network::GetBackendIPAddr(), Network::GetFrontendIPAddr() );

  for ( TStartList::const_iterator it = _startList.begin(); it != _startList.end(); ++it )
  {
    StrongMT<IServiceSpawner> spawner = it->spawner;
    const TServiceId & serviceClass = spawner->ServiceClass();

    const unsigned instanceNumber = it->instanceNumber ? it->instanceNumber : spawner->DefaultInstancesNumber();
    for ( unsigned i = 0; i < instanceNumber; ++i )
    {
      StrongMT<IServerRunner> runner = spawner->SpawnService();
      if ( !runner ) {
        ErrorTrace( "Null service spawner. svc_class=%s", serviceClass.c_str() );
        continue;
      }

      ServiceOptions svcOpts;
      svcOpts.commandLine = _serverCmdLine;

      // выбираем опции, относящиеся к данному сервису (+глобальные опции, относящиеся ко всем сервисам)
      const Coordinator::TConfigServiceOptions & configOptions = Coordinator::GetConfigServiceOptions();
      for( int idx = 0; idx < configOptions.size(); ++idx ) {
        const Coordinator::SConfigServiceOption * cfgOpt = configOptions[idx];
        if ( cfgOpt->IsGlobalOption() || ( serviceClass == cfgOpt->serviceId.c_str() ) )
          svcOpts.options.insert( cfgOpt->option );
      }
      
      cli->AddServiceInstance( spawner, runner, svcOpts );
    }
  }

  coordinatorClientRunner->Open( backendTransport, frontendTransport, Network::GetCoordinatorAddress(), "pvx" );
  coordinatorClientThread = new threading::JobThread( coordinatorClientRunner, "Coordinator Client" );

  while( cli->state() == Coordinator::ClientState::OPENING )
    nival::sleep( 10 );

  if ( cli->state() != Coordinator::ClientState::OPEN )
  {
    LOG_C(0) << "Can't connect to coordinator service OR coordinator refuse client"; 
    return false;
  }

  return true;
}



void NivalServerBase::Shutdown()
{
  spawners.clear();

  coordinatorClientRunner = 0;
  coordinatorClientThread = 0;

  if (aioTransport)
    aioTransport->Fini();
  aioTransport = 0;

  backendTransport = 0;
  frontendTransport = 0;
}



void NivalServerBase::RegisterService( IServiceSpawner * _spawner )
{
  const Transport::TServiceId & svcCls = _spawner->ServiceClass();
  bool ext = _spawner->ServiceIsExternal();
  int pol = _spawner->Policy().type;

  MessageTrace( "Registering service. svc_class=%s, ext=%d, policy=%d", svcCls.c_str(), ext, pol );

  StrongMT<IServiceSpawner> & spawner = spawners[svcCls];
  NI_ASSERT( !spawner.Valid(), NI_STRFMT( "Duplicate service spawners: svc_class='%s'", svcCls.c_str() ) );
  spawner = _spawner;
}



void NivalServerBase::RegisterExternalService( const TServiceId & _serviceClass, const Coordinator::SInterfacePolicy & _policy )
{
  RegisterService( new NullServiceSpawner( _serviceClass, _policy ) );
}



IServiceSpawner * NivalServerBase::FindSvcSpawner( const TServiceId & id ) const
{
  ServiceSpawners::const_iterator it = spawners.find( id );
  if ( it == spawners.end() )
    return 0;

  IServiceSpawner * spwn = it->second;

  if ( spwn->ServiceIsExternal() )
    return 0;

  return spwn;
}

} // namespace Transport

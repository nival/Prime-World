#ifndef NIVALSERVERBASE_H_INCLUDED
#define NIVALSERVERBASE_H_INCLUDED

#include "NivalService.h"
#include "NivalServiceRunner.h"
#include "Network/Network.h"
#include "Network/Transport.h"
#include "Network/TransportInitializer.h"
#include "transport/TLTransportModule.h"
 
#include "Coordinator/CoordinatorServer.h"
#include "Coordinator/CoordinatorRunner.h"
#include "Coordinator/CoordinatorClient.h"
#include "Coordinator/CoordinatorClientRunner.h"
#include "ServerRunner.h"


namespace logMonitor
{
  class AgentParallelPoller;
}

namespace Transport
{

//Non-template version
class DefaultServiceSpawnerBase : public IServiceSpawner, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( DefaultServiceSpawnerBase, IServiceSpawner, BaseObjectMT );
public:
  DefaultServiceSpawnerBase( 
    const TServiceId & _serviceClass, 
    unsigned _defaultInstancesNumber, 
    const Coordinator::SInterfacePolicy & _policy ) :
  serviceClass( _serviceClass ),
  defaultInstancesNumber( _defaultInstancesNumber ),
  policy( _policy )
  {
  }

  virtual const TServiceId & ServiceClass() const { return serviceClass; }
  virtual unsigned DefaultInstancesNumber() const { return defaultInstancesNumber; }
  virtual const Coordinator::SInterfacePolicy & Policy() const { return policy; }

private:
  const TServiceId serviceClass;
  unsigned defaultInstancesNumber;
  const Coordinator::SInterfacePolicy policy;
};




class NoAuxArgument { public: };

template <class TSvcRunner, class TSvcRunnerAux>
class DefaultServiceSpawner : public DefaultServiceSpawnerBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( DefaultServiceSpawner, DefaultServiceSpawnerBase );
public:
  DefaultServiceSpawner( const TServiceId & _serviceClass, unsigned _defaultInstancesNumber, const Coordinator::SInterfacePolicy & _policy, const TSvcRunnerAux & _aux ) :
  DefaultServiceSpawnerBase( _serviceClass, _defaultInstancesNumber, _policy ),
  aux( _aux )
  {}

  virtual bool ServiceIsExternal() const { return false; }
  virtual IServerRunner * SpawnService() const { return ImplSpawnService/*<TSvcRunnerAux>*/( aux ); }

private:
  TSvcRunnerAux aux;

  template <class TAux>
  IServerRunner * ImplSpawnService( const TAux & _aux ) const { return new TSvcRunner( _aux ); }

  IServerRunner * ImplSpawnService( const NoAuxArgument & _aux ) const { return new TSvcRunner; }
};



class NivalServerBase : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( NivalServerBase, BaseObjectMT );

public:
  typedef map<TServiceId, StrongMT<IServiceSpawner> >  ServiceSpawners;

  NivalServerBase();
  virtual ~NivalServerBase();

  void Shutdown();
  bool ShowNetStatistics() { return showNetStat; }

  void RegisterService( IServiceSpawner * _spawner );

  template <class TSvcRunner, class TSvcRunnerAux>
  void RegisterServiceEx( const TServiceId & _serviceClass, unsigned _defaultInstancesNumber, const Coordinator::SInterfacePolicy & _policy, const TSvcRunnerAux & _aux )
  {
    RegisterService( new DefaultServiceSpawner<TSvcRunner, TSvcRunnerAux>( _serviceClass, _defaultInstancesNumber, _policy, _aux ) );
  }

  template <class TSvcRunner>
  void RegisterServiceEx( const TServiceId & _serviceClass, unsigned _defaultInstancesNumber, const Coordinator::SInterfacePolicy & _policy )
  {
    RegisterService( new DefaultServiceSpawner<TSvcRunner, NoAuxArgument>( _serviceClass, _defaultInstancesNumber, _policy, NoAuxArgument() ) );
  }

  template <class TServiceClass>
  void RegisterService( const TServiceId & _serviceClass, unsigned _defaultInstancesNumber, const Coordinator::SInterfacePolicy & _policy )
  {
    RegisterServiceEx<Transport::ServiceRunner<TServiceClass>, NoAuxArgument>( _serviceClass, _defaultInstancesNumber, _policy, NoAuxArgument() );
  }

  template <class TServiceClass>
  void RegisterService( const TServiceId & _serviceClass, unsigned _defaultInstancesNumber, const Coordinator::SInterfacePolicy & _policy, const Transport::CustomServiceParams & _customSvcParams )
  {
    RegisterServiceEx<Transport::ServiceRunner<TServiceClass>, Transport::CustomServiceParams>( _serviceClass, _defaultInstancesNumber, _policy, _customSvcParams );
  }

  void RegisterExternalService( const TServiceId & _serviceClass, const Coordinator::SInterfacePolicy & _policy );

protected:
  struct ServiceStartupInfo
  {
    StrongMT<IServiceSpawner> spawner;
    unsigned                  instanceNumber;
    explicit ServiceStartupInfo( IServiceSpawner * spnr, unsigned num = 0 ) :
    spawner( spnr ),
    instanceNumber( num )
    {}
  };
  typedef list<ServiceStartupInfo> TStartList;

  bool showNetStat;
  Transport::TServiceId svcpath;

  ITransportSystem * BackendTransport() const { return backendTransport; }
  ITransportSystem * FrontendTransport() const { return frontendTransport; }

  bool Startup( const TStartList & _startList, const TServerCmdLine & _serverCmdLine );

  Network::INetworkDriver * NetDriver() { return netDriver; }

  const ServiceSpawners & Spawners() const { return spawners; }
  IServiceSpawner * FindSvcSpawner( const TServiceId & id ) const;

  void SetStartCoordinator() { startCoordinator = true; }
  bool IsStartCoordinator() const { return startCoordinator; }

private:
  StrongMT<logMonitor::AgentParallelPoller>  logMonitorAgent;
  StrongMT<Network::INetworkDriver> netDriver;

  bool startCoordinator;
  StrongMT<Coordinator::CoordinatorServerJob> coordinatorSvcJob;
  StrongMT<threading::JobThread> coordinatorSvcThread;

  StrongMT<Coordinator::CoordinatorClientRunner>  coordinatorClientRunner;
  StrongMT<threading::JobThread> coordinatorClientThread;

  StrongMT<ITransportSystem> backendTransport, frontendTransport;
  StrongMT<TransportLayer::TransportModule> aioTransport;

  ServiceSpawners   spawners;

  void StartLogMonitor( const TStartList & _startList );
  void LoadConfigs( const TStartList & _startList );
  bool SpawnServices( const TStartList & _startList, const TServerCmdLine & _serverCmdLine );
  bool StartTransport( const TStartList & _startList, const TServerCmdLine & _serverCmdLine );
  bool StartCoordinatorService();
};

} // namespace Transport

#endif //NIVALSERVERBASE_H_INCLUDED

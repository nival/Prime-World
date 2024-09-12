#pragma once
#include "Coordinator/Interface.h"
#include "Coordinator/CoordinatorRouteMap.h"
#include "Coordinator/CoordinatorClientIface.h"
#include "Coordinator/CoordinatorServerIface.h"
#include "System/Thread.h"
#include "Network/Transport.h"
#include "RPC/GateKeeper.h"
#include "ServerAppBase/ServerRunner.h"
#include "RPC/IfaceRequester.h"
#include "RPC/LocalEntityFactory.h"


namespace UserManager
{
  class UserManagerAgent;
}

namespace Network
{
  _interface INetworkDriver;
}

namespace Coordinator
{

namespace ClientState
{
  enum Enum
  {
    CLOSE = -2,
    CLOSING = -1,
    INIT = 0,
    OPENING,
    OPEN,
    REOPENING,
  };
};


void LoadServiceConfig( const char * svcClass );


class AddressTranslator;
class ClassRoutes;
class CoordinatorClientInterface;


class CoordinatorClient : public rpc::IfaceRequesterCallback<RICoordinatorServerRemote>, public BaseObjectMT 
{
  friend CoordinatorClientInterface;

  NI_DECLARE_REFCOUNT_CLASS_2( CoordinatorClient, rpc::IfaceRequesterCallback<RICoordinatorServerRemote>, BaseObjectMT );

public:
  CoordinatorClient( const Transport::TServiceId & _svcpath, Network::INetworkDriver * _netDriver );
  ~CoordinatorClient();

  ICoordinatorClient * GetInterface() const;

  void SetIps( const Network::NetAddress & _backend, const Network::NetAddress & _frontend );

  int Open( Transport::ITransportSystem * _backendTransport, Transport::ITransportSystem * _frontendTransport, rpc::GateKeeper * _gk );

  ClientState::Enum state() const { return st_; }

  void AddServiceInstance( Transport::IServiceSpawner * _spawner, Transport::IServerRunner * _runner, const Transport::ServiceOptions & _options );
  void step();

private:
  //mirror of ICoordinatorClientRemote
  void AddRoute( const Transport::TServiceId& service, SvcNetAddresses const & addrs );
  void RemoveRoute( const Transport::TServiceId& service );
  void StartService( const Transport::TServiceId & serviceIdToStart );
  void StopService( const Transport::TServiceId & serviceIdToStop );
  void SoftStopService( Transport::TServiceId const & _svcid );
  void ReloadConfig( const Transport::TServiceId & service );
  unsigned int Ping(unsigned int);

  //mirror of IRegisterClientCallback
  void OnRegisterClient(int _result, ServerIdT _clientid);

  //  IfaceRequesterCallback<RICoordinatorServerRemote>
  void onChangeState(rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<RICoordinatorServerRemote> > const & _ifacereq);

private:
  class CoordinatorClientRemoteProxy;

  ServerDef serverDef_;
  
  ServerIdT clientid_;
  StrongMT<CoordinatorClientRemoteProxy> remoteProxy;
  StrongMT<Transport::ITransportSystem> backendTransport, frontendTransport;
  StrongMT<Network::INetworkDriver> netdrv;

  struct EServiceState
  {
    enum Enum { Stopped, Starting /*Not used yet*/, Started, Soft_Stopped };
  };

  struct Service : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( Service, BaseObjectST );

    StrongMT<Transport::IServiceSpawner>  spawner;
    Transport::TServiceId                 id;
    StrongMT<Transport::IServerRunner>    runner;
    EServiceState::Enum                   state;
    Transport::ServiceOptions             options;

    Service( Transport::IServiceSpawner * _spawner, Transport::IServerRunner * _runner, const Transport::ServiceOptions & _options ) :
    spawner( _spawner ),
    runner( _runner ),
    state( EServiceState::Stopped ),
    options( _options )
    {}
  };

  typedef list<Strong<Service> > TServices;
  TServices services;
  friend struct ServerRunnerIsLess;

  typedef StrongMT<rpc::IfaceRequester<RICoordinatorServerRemote> > CoordServerIfaceReqT;
  CoordServerIfaceReqT coordSrvIfaceReq;

  ClientState::Enum st_;
  ScopedPtr<rpc::LocalEntityFactory> rpcFactory;

  StrongMT<UserManager::UserManagerAgent> userManagerAgent;
  StrongMT<rpc::GateKeeper> gk;
  StrongMT<ClassRoutes>  classRoutes;
  StrongMT<AddressTranslator> backendTranslator, frontendTranslator;
  StrongMT<CoordinatorClientInterface> interfaceObject;

  Service * FindNotStartedService( const Transport::TServiceId & _svcClass );
  Service * FindServiceById( const Transport::TServiceId & _svcId );
  void PopNewRoutes( ServicesStartInfo & _startInfo ) const;
};

} //namespace Coordinator

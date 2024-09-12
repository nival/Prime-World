#pragma once
#include "Coordinator/Interface.h"
#include "Coordinator/CoordinatorRouteMap.h"
#include "Network/AddressTranslator.h"
#include "System/IDGenerator.h"
#include "Network/LoginData.h"
#include "RCoordinatorClientIface.auto.h"
#include "ServiceAppearanceNotifySink.h"
#include "Coordinator/CoordinatorServiceStatus.h"
#include "Coordinator/CoordinatorServerIface.h"
#include "Coordinator/CoordinatorClientContext.h"
#include "Coordinator/CoordinatorSvcContext.h"

//#include "RPC/P2PNode.h"
#include "RPC/GateKeeper.h"

namespace Network
{
  _interface INetworkDriver;
}
namespace Login { class RLoginServerAsync; } //forward

namespace Coordinator
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CoordinatorServerTicker;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CoordinatorServer : public ICoordinatorServerRemote,
                                 public rpc::IGateKeeperCallback,
                                 public IClusterServicesInfo,
                                 public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_4( CoordinatorServer,
    ICoordinatorServerRemote,
    rpc::IGateKeeperCallback,
    IClusterServicesInfo,
    BaseObjectMT );

public:
  RPC_ID();

  CoordinatorServer();
  ~CoordinatorServer();

  int Init(const string & coordinatorAddress, StrongMT<rpc::GateKeeper> const & gkeeper);

  void SetServicePolicy( Transport::TServiceId intf, const SInterfacePolicy& policy );

  // ICoordinatorServerRemote
  virtual void RegisterClient(Coordinator::ServerIdT _srvid, ICoordinatorClientRemote* _ccr, ServerDef const & _serverdef, IRegisterClientCallback* _cb);
  virtual void ServicesStarted( const ServicesStartInfo& info );
  virtual void Shutdown();
  virtual void StopService(Transport::TServiceId const & _svcid);
  virtual void ServiceStopped(Transport::TServiceId const & _svcid);
  virtual void SoftStopService(Transport::TServiceId const & _svcid);
  virtual void ReloadConfig( const Transport::TServiceId & svcid );

  void Step(); // периодические таски (context timeouts и т.п.)

protected:

  //  IClusterServicesInfo
  virtual void GetClusterSvcInfo(ClusterInfo & csi);

  int RegisterClient_(Coordinator::ServerIdT _srvid, StrongMT<RICoordinatorClientRemote> const & _client, 
    ServerDef const & _serverdef, StrongMT<ClientContext> & _ctx);

  int SoftStopService_(StrongMT<SvcContext> const & _svctx);
  int StopService_(StrongMT<SvcContext> const & _svctx);
  int ReloadConfig_(StrongMT<SvcContext> const & _svctx);

private:
  friend class CoordinatorServerTicker;

  typedef hash_map<Transport::TServiceId, StrongMT<SvcContext>, Transport::ServiceIdHash> SvcContextsT;

  struct SvcClassInfo
  {
    SInterfacePolicy policy;
    int svcidxCount;

    SvcClassInfo()
      : svcidxCount(0)
    {
    }
  };

  typedef hash_map<Transport::TServiceId, SvcClassInfo, Transport::ServiceIdHash> SvcClass2InfoT;

  typedef NHPTimer::FTime Timestamp;

  SvcContextsT svcContexts_;
  SvcClass2InfoT svcClassesInfo_;
  ServerIdT srvidCount_;
  CoordinatorRouteMap routeMap;
  bool shutdown;

  typedef nstl::vector<StrongMT<ClientContext> > ClientContextsT;
  ClientContextsT clientContexts;

  StrongMT<rpc::GateKeeper> gateKeeper; // // был weak, но живем мы все равно только в CoordinatorRunner, у которого strong
  StrongMT<IServiceAppearanceNotifySink> serviceAppearanceNotify;

  StrongMT<ClientContext> FindClientContext(ServerIdT const & _srvid);
  void RemoveClient( StrongMT<ClientContext> const & _ctx );
  StrongMT<SvcContext> registerService_(Transport::TServiceId const & _svcls, TServiceRole const & _svcrole, ServerIdT const & _srvid, ServerDef const & _srvdef);

  // IGateKeeperCallback
  virtual void OnNewNode( Transport::IChannel * channel,  rpc::Node * node );
  virtual void OnChannelClosed( Transport::IChannel * channel,  rpc::Node * node );
  virtual void OnCorruptData( Transport::IChannel * channel,  rpc::Node * node );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
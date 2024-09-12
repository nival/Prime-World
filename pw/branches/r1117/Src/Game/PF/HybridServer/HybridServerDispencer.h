#ifndef HYBRIDSERVERDISPENCER_H_INCLUDED
#define HYBRIDSERVERDISPENCER_H_INCLUDED

#include "Network/Transport.h"
#include <RPC/RPC.h>
#include <Server/RPC/LocalEntityFactory.h>
#include <Server/RPC/GateKeeper.h>
#include "System/Thread.h"
#include <Server/AppFramework/TimeSlicer.h>
#include "GameServerDispenserIface.h"
#include "GameServerAllocatorIface.h"
#include "GameServerRegistratorIface.h"
#include "HybridServer/HybridServerNaming.h"
#include "Server/Roll/RRollBalancer.auto.h"
#include "RPC/IfaceRequester.h"
#include <System/BlockData/BlockData.h>
#include "HybridServerConfig.h"
#include "Db/DBServer.auto.h"


namespace Peered
{
  class RIGameServer;
  class CommandsScheduler;
  struct SchedulerData;
  class IPeeredStatistics;
}


namespace lobby
{
  class RISessionHybridLink;
}


namespace StatisticService
{
  class GameStatClient;
}


namespace Transport
{
  class IPerfCounters;
}


namespace HybridServer
{

class ICommandsLog;
class ICrcDumper;


class HybridServerDispencer : public IGameServerDispenser, public IGameServerAllocator, public IGameServerInstanceRegistrator, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_4( HybridServerDispencer, IGameServerDispenser, IGameServerAllocator, IGameServerInstanceRegistrator, BaseObjectMT );
  RPC_ID();

  typedef nstl::map<uint, StrongMT<IGameServerAllocatorNotify> > AllocNotifiersT;

public:
  HybridServerDispencer(
    Transport::ITransportSystem * _transport,
    rpc::GateKeeper * _gk,
    NLogg::CChannelLogger* logStream,
    const Transport::TServiceId & _serviceId,
    const Transport::TServiceId & _reconnectIfaceId,
    rpc::IfaceRequester<roll::RIBalancer> * _rollBalancer,
    nvl::ITerminator * _replaysTerminator,
    StatisticService::GameStatClient * _statistics,
    Transport::IPerfCounters * _perfCounters );
  ~HybridServerDispencer();

  //IGameServerDispenser
  void AcquireNewServer( const Peered::SAllocationParams & _params, lobby::ISessionHybridLink * _session, NI_LPTR IGameServerDispenserCallback * _cb );

  //  IGameServerAllocator
  virtual uint AllocateServer( long long userctx, IGameServerAllocatorNotify* allocnfy );

  bool AddInstance( AppFramework::ITimedInstance* instance, int threadIndex = 0 );
  void Do( const volatile bool& isRunning );

  void OnConfigReload();

  // IGameServerInstanceRegistrator
  virtual void RegisterInstance( Peered::IGameServer * instance, const char * instanceId );
  virtual void UnregisterInstance( Peered::IGameServer * instance );

private:
  struct MapReplaySettings
  {
    bool writeReplay;
    nstl::string category;
  };

  struct MapExtraSettings
  {
    int playSameTeamTimeout;
    bool disableProtectionForSinglePlayer;
  };

  void PrecacheMapSettings();
  const NDb::GameSvcSettings * GetMapSettings(const nstl::string & mapId) const;
  const MapReplaySettings * GetMapReplaySettings(const nstl::string & mapId) const;
  const MapExtraSettings * GetMapExtraSettings(const nstl::string & mapId) const;
  void FillMapSettings(Peered::SchedulerData* const data, const Peered::SAllocationParams& params) const;
  ICommandsLog * GetReplayWriter(Peered::TSessionId sessionId, const nstl::string& mapId) const;
  ICommandsLog * GetDummyReplayWriter() const;
  Peered::IPeeredStatistics * GetStatisticsWriter();

  AppFramework::TimeSlicer runner;
  NLogg::CChannelLogger* logStream;
  uint preallocid;
  AllocNotifiersT allocNotifiers;
  Transport::TServiceId serviceId;
  Transport::TServiceId reconnectIfaceId;
  StrongMT<HybridServer::ICrcDumper> crcDumper;
  StrongMT<rpc::IfaceRequester<roll::RIBalancer> >  rollBalancer;
  nvl::CPtr< nvl::ITerminator > replaysTerminator;
  StrongMT<StatisticService::GameStatClient> statistics;
  WeakMT<Transport::IPerfCounters> perfCounters;
  threading::Mutex configLock;

  HybridServer::SessionSettings sessionSettings;
  HybridServer::HybridServerSettings hybridServerSettings;
  NCore::ClientSettings clientSettings;

  typedef nstl::hash_map<nstl::string, NDb::GameSvcSettings> TMapSettings;
  TMapSettings mapSettings;
  typedef nstl::hash_map<nstl::string, MapReplaySettings> TMapReplaySettings;
  TMapReplaySettings mapReplaySettings;
  typedef nstl::hash_map<nstl::string, MapExtraSettings> TMapExtraSettings;
  TMapExtraSettings mapExtraSettings;

  StrongMT<Transport::ITransportSystem> transport;
  StrongMT<rpc::GateKeeper> frontendGk;

  unsigned instanceIndex;
};

} //namespace HybridServer

#endif //HYBRIDSERVERDISPENCER_H_INCLUDED

#include "stdafx.h"

#include <Server/RPC/RPC.h>
#include "HybridServerDispencer.h"
#include "PeeredImpl.h"
#include "LPeered.auto.h"
#include "System/LogFileName.h"
#include "System/InlineProfiler.h"
#include "Server/LobbyPvx/RISessionHybridLink.auto.h"
#include "AwardsRoll.h"
#include "PeeredStatistics.h"
#include "HybridServerDumpers.h"
#include "HybridServerMulticast.h"
#include "RdpTransport/RdpTransportUtils.h"
#include "ServerAppBase/PerfCounters.h"


NI_DEFINE_REFCOUNT( HybridServer::HybridServerDispencer )


static int gameReplayBufferSize = 1<<16;  // 64Kb
REGISTER_VAR( "game_replay_buffer_size", gameReplayBufferSize, STORAGE_NONE );

static int gameReplayFileSize = 1<<24;    // 16Mb
REGISTER_VAR( "game_replay_file_size", gameReplayFileSize, STORAGE_NONE );


namespace HybridServer
{
  namespace Instrumentation
  {
    NDebug::DebugVar<volatile int> ccu("game_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> bld_ccu("bld_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> dwd_ccu("dwd_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> ner_ccu("ner_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> eow_ccu("eow_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> ops_ccu("ops_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> trn_ccu("trn_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> tut_ccu("tut_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> lfg_ccu("lfg_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> oth_ccu("oth_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> pvet_ccu("pvet_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> pveg_ccu("pveg_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> pveb_ccu("pveb_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> pvev_ccu("pvev_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> pveo_ccu("pveo_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> pver_ccu("pver_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> ctm_ccu("ctm_ccu", "gamesvc");
    NDebug::DebugVar<volatile int> ctf_ccu("ctf_ccu", "gamesvc");
  }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SimpleCommandsHandler : public Peered::ICommandsHandler, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(SimpleCommandsHandler, Peered::ICommandsHandler, BaseObjectMT);
public:
  SimpleCommandsHandler(Peered::TSessionId _sessionId, NLogg::CChannelLogger* _logStream, const nstl::string& mapId):
  logStream(_logStream),
  sessionId(_sessionId)
  {  
    localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: Starting counters (sid=%016x map=%s)", sessionId, mapId.c_str());
    if (mapId == "Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::bld_ccu; 
    }
    else
    if (mapId == "Maps/Multiplayer/CTE/PVP.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::dwd_ccu; 
    }
    else
    if (mapId == "Maps/Multiplayer/MOBA/Mod1/_.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::ner_ccu; 
    }
    else
    if (mapId == "Maps/Multiplayer/MOBA/Mod2/_.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::eow_ccu;
    }
    else
    if (mapId == "Maps/Multiplayer/MidOnly/_.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::ops_ccu; 
    }
    else
    if (mapId == "Maps/Multiplayer/PFmap/Training.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::trn_ccu; 
    }
    else
    if (mapId == "Maps/Tutorial/_1.ADMPDSCR.xdb" || mapId == "Maps/Tutorial/_2.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::tut_ccu; 
    }
    else
    if (mapId == "Maps/Multiplayer/MOBA/Mod3/_.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::lfg_ccu; 
    }
    else
    if (mapId == "Maps/PvE/Series/Episode1/_.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::pvet_ccu; 
    }
    else
    if (mapId == "Maps/PvE/Series/Coop1/Green.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::pveg_ccu; 
    }
    else
    if (mapId == "Maps/PvE/Series/Coop1/Blue.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::pveb_ccu; 
    }
    else
    if (mapId == "Maps/PvE/Series/Coop1/Violet.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::pvev_ccu; 
    }
    else
    if (mapId == "Maps/PvE/Series/Coop1/Orange.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::pveo_ccu; 
    }
    else
    if (mapId == "Maps/PvE/Series/Coop1/Red.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::pver_ccu; 
    }
    else
    if (mapId == "Maps/Multiplayer/MOBA/Mod4/_.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::ctm_ccu; 
    }
    else
    if (mapId == "Maps/Multiplayer/MOBA/Mod5/_.ADMPDSCR.xdb") 
    { 
      modeCcu = &Instrumentation::ctf_ccu; 
    }
    else
    {
      modeCcu = &Instrumentation::oth_ccu;
    }
  }

  virtual void OnCreate(Peered::IWorld*) {}
  virtual void OnAddClient(int clientIndex, Peered::IGameClient* client, Peered::IWorld* ) 
  {
    Instrumentation::ccu.AddValue(1);
    modeCcu->AddValue(1);
    localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: Adding client counter (sid=%016x cidx=%d)", sessionId, clientIndex);
  }
  virtual void OnRemoveClient(int clientIndex, int clientId, Peered::IGameClient* client, Peered::IWorld*)
  {
    Instrumentation::ccu.DecValue(1);
    modeCcu->DecValue(1);
    localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: Removing client counter (sid=%016x cidx=%d cid=%d)", sessionId, clientIndex, clientId);
  }
  virtual bool CheckCommand(Peered::IGameClient* client, const rpc::MemoryBlock& command, Peered::IWorld*) { return true; }
private:
  NDebug::DebugVar<volatile int>* modeCcu;
  NLogg::CChannelLogger* logStream;
  Peered::TSessionId sessionId;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HybridServerDispencer::HybridServerDispencer(
  Transport::ITransportSystem * _transport,
  rpc::GateKeeper * _gk,
  NLogg::CChannelLogger* _logStream,
  const Transport::TServiceId & _serviceId,
  const Transport::TServiceId & _reconnectIfaceId,
  rpc::IfaceRequester<roll::RIBalancer> * _rollBalancer,
  nvl::ITerminator * _replaysTerminator,
  StatisticService::GameStatClient * _statistics,
  Transport::IPerfCounters * _perfCounters ):
runner(10.f, _logStream, 2),
frontendGk( _gk ),
transport(_transport),
logStream(_logStream),
preallocid(0),
instanceIndex( 1 ),
serviceId( _serviceId ),
reconnectIfaceId(_reconnectIfaceId),
rollBalancer(_rollBalancer),
replaysTerminator( _replaysTerminator ),
statistics(_statistics),
perfCounters( _perfCounters )
{
  OnConfigReload();

  crcDumper = new SimpleCrcDumper(logStream);

  PrecacheMapSettings();
}



HybridServerDispencer::~HybridServerDispencer()
{
}



void HybridServerDispencer::AcquireNewServer( const Peered::SAllocationParams & _params, lobby::ISessionHybridLink * _session, IGameServerDispenserCallback * _cb )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY( _cb, "", return );

  StrongMT<IGameServerAllocatorNotify> allocatorNotify;
  AllocNotifiersT::iterator it = allocNotifiers.find(_params.allocid);
  if (it != allocNotifiers.end())
  {
    allocatorNotify = it->second;
    if (allocatorNotify)
      allocatorNotify->AllocNotify(_params.allocid, 0);
    allocNotifiers.erase(it);
  }
  else
  {
    LOGL_DEFAULT_E( logStream ).Trace( "Acquire server is FAILED: incorrect allocid(allocid=%d sid=%016x)", _params.allocid, _params.sessionId);
    _cb->GameServerAllocated( 0, 0, Peered::SInstanceId() );
    return;
  }

  Peered::SchedulerData data;
  StrongMT<HybridServer::ICommandsLog> log;
  StrongMT<Peered::IPeeredStatistics> statisticsWrapper;
  StrongMT<Peered::IAwardsRequester> awardsRequester;
  StrongMT<HybridServer::IMcChannelsWrapper> mcChannelWrapper;
  {
    threading::MutexLock lock(configLock);
    data.serverId = _params.sessionId;
    data.sessionSettings = sessionSettings;
    data.clientSettings = clientSettings;
    log = GetReplayWriter(_params.sessionId, _params.gameParams.mapId);
    statisticsWrapper = GetStatisticsWriter();
    FillMapSettings(&data, _params);
    if (!_params.auxData.mapDesc.empty())
      awardsRequester = new Peered::AwardsRequester(rollBalancer, logStream, _params.sessionId, hybridServerSettings.rollRetryTimer);
    if (data.sessionSettings.multicastStepsEnabled)
      mcChannelWrapper = new McChannelsWrapper(transport, logStream, _params.sessionId);
  }

  StrongMT<Peered::ICommandsHandler> handler = new SimpleCommandsHandler(_params.sessionId, logStream, _params.gameParams.mapId);

  StrongMT<Peered::CommandsScheduler> sv = new Peered::CommandsScheduler(
    data,
    reconnectIfaceId,
    handler,
    log,
    crcDumper,
    &_params.clientsInfo,
    _session,
    &_params.auxData,
    logStream,
    _params.allocid,
    allocatorNotify,
    awardsRequester,
    &_params.gameLineUp,
    &_params.gameParams,
    statisticsWrapper,
    mcChannelWrapper,
    rdp_transport::RdpTransportEnabled() ? this : 0);

  AppFramework::ITimedInstance* instance = sv.Get();

  if (logStream)
  {
    string buffer;
    buffer.reserve( 1024 );
    buffer += NI_STRFMT( "HybridServer: AcquireNewServer(sid=%016x allocid=%d ptr=%p clients=[", _params.sessionId, _params.allocid, (void*)instance );
    for ( int i = 0; i < _params.clientsInfo.size(); ++i )
      buffer += NI_STRFMT( "%s%d", i ? ", " : "", _params.clientsInfo[i].clientId );
    buffer += "]";

    localLog(logStream, NLogg::LEVEL_DEBUG).Trace( "%s", buffer.c_str() );
  }

  runner.AddInstance(instance);

  StrongMT<Peered::RIGameServer> frontendGs;

  if ( rdp_transport::RdpTransportEnabled() )
  {
    Peered::SInstanceId instId;
    instId.serviceId = serviceId.c_str();
    instId.instanceId = NI_STRFMT( "gsi%08x%08x", instanceIndex++, timer::GetTicks() & 0xffffffff );
    RegisterInstance( sv.Get(), instId.instanceId.c_str() );

    _cb->GameServerAllocated( 0, RemotePtr<Peered::RIGameServerInternal>( sv->GetInternalInterface() ), instId );
  }
  else
  {
    _cb->GameServerAllocated( RemotePtr<Peered::RIGameServer>( sv ), RemotePtr<Peered::RIGameServerInternal>( sv->GetInternalInterface() ), Peered::SInstanceId() );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint HybridServerDispencer::AllocateServer( long long userctx, IGameServerAllocatorNotify* notify )
{
  localLog(logStream, NLogg::LEVEL_DEBUG).Trace("HybridServer: %s(userctx=%016x)", __FUNCTION__, userctx);

  ++preallocid;
  allocNotifiers.insert(make_pair(preallocid, StrongMT<IGameServerAllocatorNotify>(notify)));
  return preallocid;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HybridServerDispencer::AddInstance(AppFramework::ITimedInstance* instance, int threadIndex /*= 0*/ )
{
  NI_PROFILE_FUNCTION;

  return runner.AddInstance(instance, threadIndex);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HybridServerDispencer::Do(const volatile bool& isRunning)
{
  runner.Do(isRunning);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HybridServerDispencer::OnConfigReload()
{
  threading::MutexLock lock(configLock);
  GetSettings( &hybridServerSettings, &sessionSettings, &clientSettings );
  NGlobal::PrintVarsWithValueByPrefix("game_");
  runner.SetLogLagTime(hybridServerSettings.logLagSlicer);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HybridServerDispencer::RegisterInstance( Peered::IGameServer * instance, const char * instanceId )
{
  frontendGk->GetGate()->RegisterObject<Peered::IGameServer>( instance, instanceId );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HybridServerDispencer::UnregisterInstance( Peered::IGameServer * instance )
{
  frontendGk->GetGate()->UnregisterObject<Peered::IGameServer>( instance );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HybridServerDispencer::PrecacheMapSettings()
{
  if (const NDb::MapList * mapList = NDb::SessionRoot::GetRoot()->logicRoot->mapList)
  {
    for (vector<NDb::Ptr<NDb::AdvMapDescription> >::const_iterator itMap = mapList->maps.begin(); 
          itMap != mapList->maps.end(); ++itMap)
    {
      const NDb::Ptr<NDb::AdvMapDescription> & mapDesc = *itMap;

      if (!IsValid(mapDesc))
        continue;

      const nstl::string& mapId = mapDesc->GetDBID().GetFileName();

      if (IsValid(mapDesc->gameSvcSettings))
        mapSettings[mapId] = *(mapDesc->gameSvcSettings);

      MapReplaySettings& rs = mapReplaySettings[mapId];

      switch (mapDesc->mapType)
      {
      case NDb::MAPTYPE_TUTORIAL:
      case NDb::MAPTYPE_TRAINING:
        rs.writeReplay = false;
        break;
      default:
        rs.writeReplay = true;
        rs.category = NDb::KnownEnum<NDb::EMapType>::ToString(mapDesc->mapType);
        break;
      }

      MapExtraSettings& es = mapExtraSettings[mapId];

      if (mapDesc->playSameTeamTimeOut > 0)
        es.playSameTeamTimeout = mapDesc->playSameTeamTimeOut;
      else
        es.playSameTeamTimeout = 0;

      switch (mapDesc->mapType)
      {
      case NDb::MAPTYPE_TUTORIAL:
      case NDb::MAPTYPE_TRAINING:
        es.disableProtectionForSinglePlayer = true;
        break;
      default:
        es.disableProtectionForSinglePlayer = false;
        break;
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::GameSvcSettings * HybridServerDispencer::GetMapSettings(const nstl::string & mapId) const
{
  TMapSettings::const_iterator it = mapSettings.find(mapId);
  if (it == mapSettings.end())
    return 0;
  return &it->second;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const HybridServerDispencer::MapReplaySettings * HybridServerDispencer::GetMapReplaySettings(const nstl::string & mapId) const
{
  TMapReplaySettings::const_iterator it = mapReplaySettings.find(mapId);
  if (it == mapReplaySettings.end())
    return 0;
  return &it->second;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const HybridServerDispencer::MapExtraSettings * HybridServerDispencer::GetMapExtraSettings(const nstl::string & mapId) const
{
  TMapExtraSettings::const_iterator it = mapExtraSettings.find(mapId);
  if (it == mapExtraSettings.end())
    return 0;
  return &it->second;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HybridServerDispencer::FillMapSettings(Peered::SchedulerData* const data, const Peered::SAllocationParams& params) const
{
  if (!data)
    return;

  const nstl::string& mapId = params.gameParams.mapId;

  if (mapId.empty())
    return;

  if (const NDb::GameSvcSettings* const gameSvcSettings = GetMapSettings(mapId))
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "HybridServer: Found map-specific settings (sid=%016x mapId=%s)", data->serverId, mapId.c_str());

    // Get AFK settings with seconds to steps conversion
    data->sessionSettings.afkStepsCount = 1000 * gameSvcSettings->afkMessageTimer / sessionSettings.simulationStep;
    data->sessionSettings.afkStepsDisconnectCount = 1000 * gameSvcSettings->afkDisconnectTimer / sessionSettings.simulationStep;
    data->sessionSettings.timeScale = ClampFast(gameSvcSettings->timeScale, 0.1f, 10.0f);
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "HybridServer: Map-specific settings not found (sid=%016x mapId=%s)", data->serverId, mapId.c_str());
  }

  if (const MapExtraSettings* const es = GetMapExtraSettings(mapId))
  {
    data->sessionSettings.playSameTeamTimeout = es->playSameTeamTimeout;

    if (es->disableProtectionForSinglePlayer)
    {
      // TODO: count by valid clientIds?
      const bool singlePlayer = (params.clientsInfo.size() == 1);

      if (singlePlayer)
      {
        data->sessionSettings.pmConfirmFrequency = 0;

        localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
          "HybridServer: Protection disabled (sid=%016x mapId=%s)", data->serverId, mapId.c_str());
      }
    }
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "HybridServer: Map-specific extra settings not found (sid=%016x mapId=%s)", data->serverId, mapId.c_str());
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ICommandsLog * HybridServerDispencer::GetReplayWriter(Peered::TSessionId sessionId, const nstl::string& mapId) const
{
  if (!hybridServerSettings.enableReplay)
    return GetDummyReplayWriter();

  const MapReplaySettings* replaySettings = GetMapReplaySettings(mapId);
  const nstl::string* replayCategory = 0;

  if (replaySettings)
  {
    if (!replaySettings->writeReplay)
      return GetDummyReplayWriter();

    replayCategory = &replaySettings->category;
  }

  if (NGlobal::GetVar( "game_bds_replays", 0 ).GetInt64())
  {
    if (!replaysTerminator.Get())
      return GetDummyReplayWriter();

    // NUM_TASK папки для категорий; BDS использует std::ofstream, а он папок не создает
    // HACKY
    // TODO: verify?
    if (replayCategory)
    {
      const nstl::string replaysFolder = NGlobal::GetVar("game_bds_replays_folder").Get<nstl::string>();

      NFile::CreatePath(NFile::Combine(replaysFolder, *replayCategory));
    }

    // NUM_TASK представление sessionID в имени реплея в 10-чной системе
    const nstl::string fileName = replayCategory
      ? NDebug::GenerateDebugFileName(NI_STRFMT("%llu", sessionId), "pwrp", replayCategory->c_str(), true)
      : NDebug::GenerateDebugFileName(NI_STRFMT("%llu", sessionId), "pwrp", 0, false);

    nvl::CPtr< nvl::IDataFlow > cpReplaysDataFlow;

    replaysTerminator->CreateDataFlow( fileName.c_str(), cpReplaysDataFlow );

    return new BdsCommandsLog(logStream, cpReplaysDataFlow);
  }
  else
  {
    if (replayCategory)
      return new SimpleFileCommandsLog(logStream, sessionId, *replayCategory, gameReplayBufferSize, gameReplayFileSize);

    return new SimpleFileCommandsLog(logStream, sessionId, gameReplayBufferSize, gameReplayFileSize);
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ICommandsLog * HybridServerDispencer::GetDummyReplayWriter() const
{
  return new DummyCommandsLog(logStream);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Peered::IPeeredStatistics * HybridServerDispencer::GetStatisticsWriter()
{
  if ( hybridServerSettings.enableStatistics && statistics )
    return new Peered::PeeredStatistics( statistics, perfCounters.Lock() );

  return 0;
}


} //namespace HybridServer

#include "stdafx.h"
#include "GameService.h"
#include "Peered.h"
#include "LPeered.auto.h"
#include <System/Node/Initializer.h>
#include <System/FileSystem/FileUtils.h>
#include "Server/Roll/LRollClient.auto.h"
#include "Server/Statistic/GameStatClient.h"
#include "Server/Statistic/StatClientHttpDispatcher.h"
#include "System/InlineProfiler.h"
#include "System/DarkSide.h"
#include "System/sleep.h"


namespace HybridServer
{

static unsigned   s_trackGameSessionRpcClass = 0xfb78bcd4; //  IGameClient
static int        s_trackGameSessionRpcMethodIdx = 1;  //  Step
static unsigned   s_trackGameSessionStepPeriodThreshold = 102;

REGISTER_VAR("game_track_session_rpc_class",              s_trackGameSessionRpcClass, STORAGE_GLOBAL);
REGISTER_VAR("game_track_session_methond_idx",            s_trackGameSessionRpcMethodIdx, STORAGE_GLOBAL);
REGISTER_VAR("game_track_session_step_period_threshold",  s_trackGameSessionStepPeriodThreshold, STORAGE_GLOBAL);

static int s_initializeStatistics = 0;
REGISTER_VAR("game_initialize_statistics", s_initializeStatistics, STORAGE_NONE);

static int s_gamePollingInterval = 10;
REGISTER_VAR("game_polling_interval", s_gamePollingInterval, STORAGE_NONE);

static int s_gamePollingInSeparateThread = 0;
REGISTER_VAR("game_polling_in_separate_thread", s_gamePollingInSeparateThread, STORAGE_NONE);

static int s_bds_replays = 0;
REGISTER_VAR( "game_bds_replays", s_bds_replays, STORAGE_GLOBAL );

static string s_bds_replays_folder;
REGISTER_VAR( "game_bds_replays_folder", s_bds_replays_folder, STORAGE_GLOBAL );


GameService::GameService( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams ) :
Transport::BaseService( _svcParams, _customParams )
{
  Transport::TServiceId reconnectIfaceId = DefineReconnectSvcId();

  CreateMagicBlockDataWriter();

  StrongMT<rpc::TransportPipeTrafficTrackerFactory> tracker =
    new rpc::TransportPipeTrafficTrackerFactory( "relay", SvcId(), s_trackGameSessionRpcClass, s_trackGameSessionRpcMethodIdx, s_trackGameSessionStepPeriodThreshold );
  FrontendGk()->setTransportPipeTrackerFactory( tracker );

  //  create log filename postfix
  Transport::TServiceId localSvcId;
  Transport::GetLocalServiceId( SvcId(), localSvcId );
  nstl::string logFilePostfix = localSvcId.c_str();
  NStr::ReplaceAllChars(&logFilePostfix, '/', '_');

  logStream = new NLogg::CChannelLogger( logFilePostfix.c_str() );
  logDumper = NLogg::BasicTextFileDumper::New( logStream, logFilePostfix.c_str() );

  rollBalancer = new rpc::IfaceRequester<roll::RIBalancer>( "cMj4tyeV3JCHOnN" );
  rollBalancer->init( BackendGk(), roll::serviceIds::BalancerService, roll::serviceIds::BalancerInterface );

  if ( s_initializeStatistics )
  {
    StrongMT<StatisticService::ClientHttpDispatcher> statClDispatcher = new StatisticService::ClientHttpDispatcher;
    statistics = new StatisticService::GameStatClient( statClDispatcher, 0 );
  }

  //TODO: Split interfaces on client only and server only
  server = new HybridServerDispencer( BackendTransport(), FrontendGk(), logStream, SvcId(), reconnectIfaceId, rollBalancer, cpReplaysTerminator, statistics, this );
  RegisterBackendAttach<Peered::IGameServer, Peered::LIGameServer>();
  RegisterBackendAttach<Peered::IGameServerInternal, Peered::LIGameServerInternal>();
  RegisterFrontendAttach<Peered::IGameServerReconnect, Peered::LIGameServerReconnect>();
  RegisterBackendAttach<roll::IClient, roll::LIClient>();
  RegisterBackendObject<IGameServerDispenser>( server, HybridServer::DispenserIfaceId );
  RegisterBackendObject<IGameServerAllocator>( server, HybridServer::AllocatorIfaceId);

  _RegisterDebugVarCounter(L"game_ccu", "game_ccu", true);
  _RegisterDebugVarCounter(L"bld_ccu", "bld_ccu", true);
  _RegisterDebugVarCounter(L"dwd_ccu", "dwd_ccu", true);
  _RegisterDebugVarCounter(L"ner_ccu", "ner_ccu", true);
  _RegisterDebugVarCounter(L"eow_ccu", "eow_ccu", true);
  _RegisterDebugVarCounter(L"ops_ccu", "ops_ccu", true);
  _RegisterDebugVarCounter(L"trn_ccu", "trn_ccu", true);
  _RegisterDebugVarCounter(L"tut_ccu", "tut_ccu", true);
  _RegisterDebugVarCounter(L"lfg_ccu", "lfg_ccu", true);
  _RegisterDebugVarCounter(L"oth_ccu", "oth_ccu", true);
  _RegisterDebugVarCounter(L"pvet_ccu", "pvet_ccu", true);
  _RegisterDebugVarCounter(L"pveg_ccu", "pveg_ccu", true);
  _RegisterDebugVarCounter(L"pveb_ccu", "pveb_ccu", true);
  _RegisterDebugVarCounter(L"pvev_ccu", "pvev_ccu", true);
  _RegisterDebugVarCounter(L"pveo_ccu", "pveo_ccu", true);
  _RegisterDebugVarCounter(L"pver_ccu", "pver_ccu", true);
  _RegisterDebugVarCounter(L"ctm_ccu", "ctm_ccu", true);
  _RegisterDebugVarCounter(L"ctf_ccu", "ctf_ccu", true);
}



int GameService::_RegisterDebugVarCounter(const wchar_t* name, const char* externalName, bool toCumulate)
{
  NDebug::IDebugVar* pdv = NDebug::FindDebugVar(name);
  NI_VERIFY(pdv, NI_STRFMT("Can't find debug var '%s'", name), return -1 );
  return RegisterPerfCounter(externalName, pdv, toCumulate);
}



GameService::~GameService()
{
  server = 0;

  CleanupMagicBlockDataWriter();

  if (logStream)
  {
    delete logStream;
    logStream = 0;
  }
}



Transport::TServiceId GameService::DefineReconnectSvcId()
{
  Transport::TServiceId result;
  Transport::TServiceId svcpath = Transport::GetServicePath( SvcId() );
  int idx = Transport::GetServerIndex( SvcId() );
  Transport::MakeFullServiceId(svcpath, ReconnectServiceClass, idx, result);

  BackendTransport()->GetAddressTranslator()->DefineAliasRoute( SvcId(), result );
  return result;
}



void GameService::CreateMagicBlockDataWriter()
{
  if ( !s_bds_replays )
    return;

  NI_VERIFY( nvl::node::Initialize( cpNodeManager ), "Cannot initialize Node System", return );

  nvl::CPtr< nvl::IServicesFactory > cpFactory;
  NI_ASSERT( nvl::NV_CSUCCESS( nvl::bds::CreateServicesFactory( cpFactory ) ), "Cannot create BDS factory" );
  NI_ASSERT( nvl::NV_CSUCCESS( cpNodeManager->RegisterServices( cpFactory ) ), "Cannot register BDS factory" );

  if ( s_bds_replays_folder.empty() )
    s_bds_replays_folder = "replays";

  if ( NFile::DoesFolderExist( s_bds_replays_folder.c_str() ) == false )
    NI_VERIFY( NFile::CreateDiskDirectory( s_bds_replays_folder.c_str() ), "Cannot create replays directory", return );

  std::string sServiceSettings =  "{\n"
                                  "\"service\":	\"BlockData Service\",\n"
                                  "\"id\":		\"BDS\",\n"
                                  "\"thread\":	\"BDS Thread\",\n"
                                  "\"settings\": {\n"
                                  "  \"terminators\": {\n"
                                  "    \"ReplaysTerminator\": {\n"
                                  "      \"type\": \"File\",\n"
                                  "      \"settings\": {\n"
                                  "        \"folder\": \"";

  sServiceSettings += s_bds_replays_folder.c_str();

  sServiceSettings += "\"\n"
                      "      }\n"
                      "    }\n"
                      "  }\n"
                      "}}\n";

  NI_VERIFY( nvl::NV_CSUCCESS( cpNodeManager->ServiceRun( "{}", sServiceSettings.c_str() ) ),
              "Something wrong in BDS initialization", return );

  nvl::CPtr< nvl::IBlockDataService > cpBDS;
  NI_VERIFY( nvl::NV_CSUCCESS( cpNodeManager->GetService( "BDS", cpBDS.GetRef() ) ),
              "Cannot get BDS instance", return );

  while ( cpBDS->GetServiceState() != nvl::IService::WORKING )
    nival::sleep( 0 );

  NI_VERIFY( nvl::NV_CSUCCESS( cpBDS->GetTerminator( "ReplaysTerminator", cpReplaysTerminator ) ),
              "Where is not ReplaysTerminator!", return );
}



void GameService::CleanupMagicBlockDataWriter()
{
  if ( cpNodeManager.Get() )
  {
    nvl::CPtr< nvl::IBlockDataService > cpBDS;
    NI_VERIFY( nvl::NV_CSUCCESS( cpNodeManager->GetService( "BDS", cpBDS.GetRef() ) ),
                "Cannot get BDS instance", return );

    cpNodeManager->ServiceFinish( cpBDS );
  }
}

















class HybridServerContainerPoller : public AppFramework::ITimedInstance, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(HybridServerContainerPoller, AppFramework::ITimedInstance, BaseObjectMT);
public:
  HybridServerContainerPoller( IServicePollCallback * _pollCallback, NLogg::CChannelLogger * _logStream ) :
  pollCallback( _pollCallback ),
  logStream( _logStream )
  {}

  virtual int Step( int delta )
  {
    NI_PROFILE_FUNCTION;

    const int pollInterval = max( s_gamePollingInterval, 1 );

    UpdateLagsStatistics( pollInterval );

    if ( StrongMT<IServicePollCallback> locked = pollCallback.Lock() )
      locked->PollCallback();

    return pollInterval;
  }

  virtual int GetId() const
  {
    return DarkSide::ptr2int< int >( this );
  }

  void UpdateLagsStatistics(const int pollInterval)
  {
    if (stats.IsStarted())
    {
      stats.Stop();
    } 
    if (stats.GetCount() == 500)
    {
      const AppFramework::InstanceStatistics::ValueAccumulator& info = stats.Finish();
      int average = NHPTimer::Time2Milliseconds(info.averageValue);
      if ((average-pollInterval) > 7)
      {
        localLog(logStream, NLogg::LEVEL_WARNING).Trace( "GateKeeperPoller: lags detected (min=%d average=%d max=%d)", 
          NHPTimer::Time2Milliseconds(info.minValue), average, NHPTimer::Time2Milliseconds(info.maxValue));
      }
      stats.Reset();
    }
    stats.Start();
  }

private:
  HybridServerContainerPoller() {}

  AppFramework::InstanceStatistics stats;
  WeakMT<IServicePollCallback>  pollCallback;
  NLogg::CChannelLogger* logStream;
};




void GameService::ThreadMain( volatile bool & _isRunning )
{
  StrongMT<HybridServerContainerPoller> poller = new HybridServerContainerPoller( this, logStream );
  server->AddInstance( poller, s_gamePollingInSeparateThread ? 1 : 0 );
  server->Do( _isRunning );
}



void GameService::OnConfigReload()
{
  if ( server )
    server->OnConfigReload();
}



void GameService::PollCallback()
{
  BaseService::PollInternal();

  if ( rollBalancer )
    rollBalancer->step();
}

} //namespace HybridServer

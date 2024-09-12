#include "stdafx.h"
#include <Server/AppFramework/TimeSlicer.h>
#include <System/StdOutDumper.h>

#include <Game/PF/HybridServer/PeeredImpl.h>
#include <System/LockFree/spsc.h>
#include <System/RandomGenerator.h>
#include "RPC/base.h"

#include <System/Node/Initializer.h>
#include <System/BlockData/BlockData.h>
#include <System/FileSystem/FileUtils.h>
#include <System/TimeUtils.h>
#include <Game/PF/HybridServer/HybridServerDumpersIfaces.h>


struct LocalGameClient;

const int clientsPerSession = 10;
struct Clients
{
  Clients(int clientCount):items(2*Ceil2PowerOf2(clientCount)) {}
  void Schedule(LocalGameClient* client);
  void Update();
private:
  mpmc_bounded_queue<LocalGameClient*> items;
};

struct LocalGameClient : public Peered::IGameClient, BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LocalGameClient, Peered::IGameClient, BaseObjectMT);
  enum Enum
  {
    Closed,
    Disconnected,
    Loading,
    Ready,
    Started,
  };
  Enum mode;
  bool isCalcLogs;

  LocalGameClient(Peered::IGameServer* _server, Clients& _clients, NLogg::CChannelLogger* _logStream, uint _clientId, bool _isCalcLogs):isCalcLogs(_isCalcLogs), clients(_clients), logStream(_logStream)
  {
    server = _server;
    mode = Disconnected;
    status = rpc::Connected;
    clientId = _clientId;
    isScheduled = false;
  }

  void Disconnect()
  {
    mode = Disconnected;
  }

  virtual void Start(const Peered::ClientStartInfo& clientStartInfo, Peered::RIGameServerReconnect * gameServerReconnect)
  {
    index = clientStartInfo.index;
    serverId = clientStartInfo.serverId;
    confirmFrequency = clientStartInfo.confirmFrequency;
    mode = Loading;
    clients.Schedule(this);
  }
  static const int simulationStep = 100;

  virtual void Step(
    int step, 
    int lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& clientGaps,
    const NHPTimer::STime& __recieveTime__)
  {
    if (isCalcLogs)
    {
      if (stats.IsStarted())
      {
        stats.Stop();
      } 
      if (stats.GetCount() == 50)
      {
        const AppFramework::InstanceStatistics::ValueAccumulator& info = stats.Finish();
        int average = NHPTimer::Time2Milliseconds(info.averageValue);
        if (abs(average-simulationStep) > 2)
        {
          static bool isLagsLogged = true;
          if (isLagsLogged)
          {
            localLog(logStream, NLogg::LEVEL_WARNING).Trace("GameClient: lags detected (sid=%016x min=%d average=%d max=%d)", serverId, NHPTimer::Time2Milliseconds(info.minValue), NHPTimer::Time2Milliseconds(info.averageValue), NHPTimer::Time2Milliseconds(info.maxValue));
          }
        }
        stats.Reset();
      }
      stats.Start();
    }

    if (confirmFrequency > 0 && step % confirmFrequency == 0)
    {
      unconfirmedSteps.enqueue(step);
    }
    if (!isScheduled)
    {
      clients.Schedule(this);
      isScheduled = true;
    }
  }

  virtual void StepLoading(
    int step, 
    int lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& clientGaps)
  {
    Step(step, lastConfirmedStep, commands, statuses, clientGaps, 0L);
  }

  virtual void RequestCrcData(int step)
  { 
  }

  virtual void Award( const vector<roll::SAwardInfo> & _awards )
  {
  }

  virtual void OnSpectate( const Peered::SpectatorInfo& )
  {
  }


  void Update()
  {
    if (mode == Loading)
    {
      mode = Ready;
      server->OnClientReady(index);
    }
    else
    if (mode == Started)
    {
      while (true)
      {
        int value; 
        bool b = unconfirmedSteps.dequeue(value); 
        if (b)
        {
          server->OnFinishStep(index, value, value);      
          if (value % 3 == 0)
          {
            byte memory[50] = "0000000000111111111222222222233333333334444444444";
            *((uint*)(memory+4)) = clientId;
            rpc::MemoryBlock command(memory, 50);
            server->SendCommand(index, command);      
          }
        } else
        {
          break;
        }
      }
    }
    else
    if (mode == Disconnected)
    {
      status = rpc::Disconnected;
      server = 0;
      mode = Closed;
    }
    isScheduled = false;
  }

  virtual void OnAsync(int step, const nstl::vector<Peered::AsyncInfo>& _async)
  {
  }

  virtual void ApplySnapshot(int step, uint worldCrc, const nstl::vector<Peered::BriefEntityInfo>& entitiesIds, const nstl::vector<rpc::MemoryBlock>& entitiesData)
  {
  }

  virtual void OnStart(int step)
  {
    mode = Started;
  }

  virtual const nstl::vector<rpc::MemoryBlock>& GetSnapshot(uint step, const nstl::vector<uint>& entitiesIds)
  {
    return entities;
  }

  virtual void SetTimeScale(float scale)
  {
  }
  virtual void OnChangeClientStatus(const nstl::vector<Peered::BriefClientInfo>& _clientStatuses)
  {
  }

  virtual void OnDisconnect( int _reason )
  {
  }

  virtual rpc::Status GetStatus() 
  { 
    return status; 
  }

  virtual void RequestWorldData(Peered::RIGameServerReconnect * gameServerReconnect)
  {
  }

  virtual void ApplyWorldDataInfo(const Peered::WorldDataInfo& data)
  {
  }

  virtual void ApplyWorldDataPart(const rpc::MemoryBlock& data)
  {
  }

  virtual void OnRejoin( uint clientId )
  {
  }

public:
  nstl::vector<rpc::MemoryBlock> entities;
  rpc::Status status;
  StrongMT<Peered::IGameServer> server;
  int index;
  spsc_queue<int> unconfirmedSteps;
  Clients& clients;
  int confirmFrequency;
  NLogg::CChannelLogger* logStream;
  AppFramework::InstanceStatistics stats;
  uint clientId;
  volatile bool isScheduled;
  Peered::TSessionId serverId;
};

void Clients::Schedule(LocalGameClient* client)
{
  NI_VERIFY(items.enqueue(client), "No enough space for client", return);
}

void Clients::Update()
{
  while (true)
  {
    LocalGameClient* value; 
    bool b = items.dequeue(value); 
    if (b)
    {
      value->Update();      
    } else
    {
      break;
    }
  }
}


struct SessionContext
{

  SessionContext()
  {
    NHPTimer::GetTime(startTime);
  }

  ~SessionContext()
  {
    Disconnect();
  }

  float GetSessionTime()
  {
    NHPTimer::STime currentTime;
    NHPTimer::GetTime(currentTime);
    return NHPTimer::Time2Seconds(currentTime-startTime);
  }

  void Disconnect()
  {
    for (int i=0;i<clients.size();++i)
    {
      clients[i]->Disconnect();
    }
    clients.clear();
  }

  NHPTimer::STime startTime;
  nstl::vector<StrongMT<LocalGameClient>> clients;
  StrongMT<Peered::CommandsScheduler> session;
};

class MockPoller : public BaseObjectMT, public AppFramework::ITimedInstance
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockPoller, BaseObjectMT, AppFramework::ITimedInstance );
  virtual int Step(int delta=0)
  {
    Sleep(0);
    return 10;
  }
  virtual int GetId() const { return 555; }
};


class ClientsPoller : public AppFramework::ITimedInstance, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(ClientsPoller, AppFramework::ITimedInstance, BaseObjectMT);
public:
  ClientsPoller(
    Clients& _clients,
    int _targetSessionsCount,
    AppFramework::TimeSlicer& _runner,
    float _sessionLifetime,
    float _disconnectPeriod,
    float _connectPeriod,
    NLogg::CChannelLogger* _logStream,
    NLogg::CChannelLogger* _logSessionsStream,
    nvl::ITerminator * _replaysTerminator ):
  clients(_clients), 
  runner(_runner),
  targetSessionsCount(_targetSessionsCount),
  clientId(0),
  sessionId(0),
  sessionLifetime(_sessionLifetime),
  disconnectPeriod(_disconnectPeriod),
  connectPeriod(_connectPeriod),
  logStream(_logStream),
  logSessionsStream(_logSessionsStream),
  replaysTerminator( _replaysTerminator )
  {
    NHPTimer::GetTime(disconnectTime);
    NHPTimer::GetTime(connectTime);
  }

  ~ClientsPoller()
  {
    Shutdown();
  }

  virtual int Step(int delta)
  {
    NI_PROFILE_FUNCTION;
    clients.Update();
    NHPTimer::STime currentTime;
    NHPTimer::GetTime(currentTime);
    if (currentTime >= disconnectTime)
    {
      pendingSessions.clear();
      for (nstl::vector<int>::iterator it=instances.begin();it!=instances.end();)
      {
        int id = *it;
        nstl::map<int, SessionContext*>::iterator mit=session2clients.find(id);
        NI_ASSERT(mit!=session2clients.end(), "Session not found");
        if (mit->second->GetSessionTime() > sessionLifetime)
        {
          pendingSessions.push_back(mit->second->session);
          mit->second->Disconnect();
          delete mit->second;
          session2clients.erase(mit);
          it = instances.erase(it);
        } else
        {
          ++it;
        }
      }
      disconnectTime = currentTime + NHPTimer::Seconds2Time(disconnectPeriod);
    }
    if (instances.size() < targetSessionsCount && currentTime > connectTime)
    {
      connectTime = currentTime+NHPTimer::Seconds2Time(connectPeriod);
      Peered::SchedulerData data;
      data.sessionSettings.simulationStep = 100;
      data.sessionSettings.dumpStepsMaxCount = 2400; 
      data.sessionSettings.trustGap = 0;
      data.serverId = sessionId; 
      data.sessionSettings.afkStepsCount = 1400;
      data.sessionSettings.afkStepsDisconnectCount = 2000;
      data.sessionSettings.disconnectionGap = 1000;
      data.sessionSettings.disconnectionWaterline = 0;
      data.sessionSettings.connectionTimeout = 70;
      data.sessionSettings.confirmFrequency = 1;
      data.sessionSettings.firstConnectionTimeout = 600;
//      data.snapshotTimeout = 0;
      data.sessionSettings.snapshotChunkSize = 1024;
      data.sessionSettings.snapshotChunkMaxCount = 4096;
      data.sessionSettings.reconnectEnabled = true;

      lobby::SGameParameters params;
      params.gameType = lobby::EGameType::Custom;

      Transport::TServiceId reconnectSid;

      nvl::CPtr< nvl::IDataFlow > cpReplaysFlow;
      if ( replaysTerminator.Get() ) {

        struct tm t;
        GetOsUtcTime( &t );

        char buffer[ 200 ];
	    sprintf_s(
          buffer,
          sizeof( buffer ),
	      "%04d.%02d.%02d-%02d.%02d.%02d-session_%d.replay",
	      t.tm_year,
	      t.tm_mon,
	      t.tm_mday,
	      t.tm_hour,
	      t.tm_min,
	      t.tm_sec,
	      sessionId
	    );

        replaysTerminator->CreateDataFlow( buffer, cpReplaysFlow );

      }

      StrongMT< HybridServer::ICommandsLog > log = new DummyCommandsLog( cpReplaysFlow );

      StrongMT<Peered::CommandsScheduler> sv = new Peered::CommandsScheduler(
        data,
        reconnectSid,
        0,
        log,
        0,
        0,
        0,
        0,
        logSessionsStream,
        0,
        0,
        0,
        0,
        &params
        );

      AppFramework::ITimedInstance* instance = sv.Get();
      runner.AddInstance(instance);
      instances.push_back(sv->GetId());
      SessionContext* c = new SessionContext;
      c->session = sv;
      for (int j=0;j<clientsPerSession;j++)
      {
        uint newClientId = clientId++;
        StrongMT<LocalGameClient> client = new LocalGameClient(sv, clients, logStream, newClientId, false );
        c->clients.push_back(client);
        sv->AddClient("client", newClientId, client);
      }
      session2clients[sessionId] = c;
      localLog(logStream, NLogg::LEVEL_MESSAGE).Trace("Client: new session (count=%d)", session2clients.size());
      sessionId++;
    }
    return 5;
  }

  void Shutdown()
  {
    for (nstl::map<int, SessionContext*>::iterator it=session2clients.begin();it!=session2clients.end();++it)
    {
      delete it->second;
    }
    session2clients.clear();
  }
  virtual int GetId() const { return int(this); } 

protected:

struct DummyCommandsLog: public HybridServer::ICommandsLog, public BaseObjectMT {

  NI_DECLARE_REFCOUNT_CLASS_2( DummyCommandsLog, HybridServer::ICommandsLog, BaseObjectMT );

  DummyCommandsLog( nvl::IDataFlow * _replaysDataFlow = NULL ): replaysDataFlow( _replaysDataFlow )
  {}

  virtual void OnHeaderDump(Peered::TSessionId serverId, const lobby::TGameLineUp * gameLineUp, const lobby::SGameParameters * gameParams, const vector<Peered::ClientInfo> * clientInfos) {}
  virtual void OnStartGame(Peered::TSessionId serverId, int step) {}
  virtual void OnFinishGame(Peered::TSessionId serverId, int step) {}


  void OnCommandsDump( Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses )
  {
    int steps = endStep - commands.GetStartStep();
    if ( steps > 0 ) {

      if ( replaysDataFlow.Get() ) {

        replaysBuffer.Clear();
        replaysBuffer.Reserve( 500 * 1024 );
        nstl::vector< rpc::MemoryBlock > stepCommands;

        for ( int i = commands.GetStartStep(); i <= endStep; ++i ) {

          commands.CopyStep( i, stepCommands );
          if ( stepCommands.size() > 0 ) {

            replaysBuffer
                << byte( 0 )                      // stepSign
                << i                              // step
                << ushort( stepCommands.size() ); // commandsCount

            for (int j = 0; j < stepCommands.size(); ++j) {

              rpc::MemoryBlock& block = stepCommands[j];
              replaysBuffer << ushort( block.size );
              replaysBuffer.Write( block.memory, block.size );

            }

          }

        }

        if ( replaysBuffer.GetSize() )
          replaysDataFlow->StoreBinaryData( 0, replaysBuffer.GetData(), replaysBuffer.GetSize() );

      }

    }

    commands.EraseSteps( endStep + 1 );
  }

  nvl::CPtr< nvl::IDataFlow > replaysDataFlow;
  nvl::CBinaryBuffer replaysBuffer;

};

private:
  Clients& clients;
  NHPTimer::STime disconnectTime;
  NHPTimer::STime connectTime;
  AppFramework::TimeSlicer& runner;
  int targetSessionsCount;
  int clientId;
  int sessionId;
  nstl::vector<int> instances;
  nstl::map<int, SessionContext* > session2clients;
  NRandom::RandomGenerator randGen;
  float sessionLifetime;
  float disconnectPeriod;
  float connectPeriod;
  nstl::vector<StrongMT<Peered::CommandsScheduler>> pendingSessions;
  NLogg::CChannelLogger* logStream;
  NLogg::CChannelLogger* logSessionsStream;
  nvl::CPtr< nvl::ITerminator > replaysTerminator;
};


class ClientsThread : public threading::Thread
{
public:
  ClientsThread(ClientsPoller* _poller):
  poller(_poller)
  {
  }

  ~ClientsThread()
  {
    Shutdown();
  }

  
  void Shutdown()
  {
    Stop(true, 1000);
  }

  virtual unsigned Work() 
  {
    threading::SetDebugThreadName("ClientsUpdate");
    while (isRunning)
    {
      NHPTimer::STime currentTime;
      NHPTimer::GetTime(currentTime);
      poller->Step(0);
      NHPTimer::STime lastTime;
      NHPTimer::GetTime(lastTime);
      int stepTime = NHPTimer::Time2Milliseconds(lastTime-currentTime);
      const int maxStepTime = 400;
      if (stepTime > maxStepTime)
      {
        stepTime = maxStepTime;
      }
      threading::Sleep(((maxStepTime-stepTime)*5)/maxStepTime);
    }
    return 0;
  }
private:
  StrongMT<ClientsPoller> poller;
};

namespace nvl {

    bool InitializeBDS( CPtr< INodeManager > &cpNodeManager, CPtr< ITerminator > &cpReplaysTerminator )
    {
        NI_VERIFY( node::Initialize( cpNodeManager ), "Cannot initialize Node System", return false );

        CPtr< IServicesFactory > cpFactory;
        NI_VERIFY( NV_CSUCCESS( bds::CreateServicesFactory( cpFactory ) ), "Cannot create BDS factory", return false );
        NI_VERIFY( NV_CSUCCESS( cpNodeManager->RegisterServices( cpFactory ) ), "Cannot register BDS factory", return false );

        if ( NFile::DoesFolderExist( "replays" ) == false )
            NI_VERIFY( NFile::CreateDiskDirectory( "replays" ), "Cannot create replays directory", return false );

        std::string sServiceSettings =
"{\"service\":	\"BlockData Service\",\n"
"\"id\":		\"BDS\",\n"
"\"thread\":	\"BDS Thread\",\n"
"\"settings\": {\n"
"  \"terminators\": {\n"
"    \"ReplaysTerminator\": {\n"
"      \"type\": \"File\",\n"
"      \"settings\": {\n"
"        \"folder\": \"replays\"\n"
"      }\n"
"    }\n"
"  }\n"
"}}\n";

        NI_VERIFY(
            NV_CSUCCESS( cpNodeManager->ServiceRun( "{}", sServiceSettings.c_str() ) ),
            "Something wrong in BDS initialization",
            return false
        );

        CPtr< IBlockDataService > cpBDS;
        NI_VERIFY(
            NV_CSUCCESS( cpNodeManager->GetService( "BDS", cpBDS.GetRef() ) ),
            "Cannot get BDS instance",
            return false
        );

        while ( cpBDS->GetServiceState() != nvl::IService::WORKING )
            Sleep( 0 );

        NI_VERIFY(
            NV_CSUCCESS( cpBDS->GetTerminator( "ReplaysTerminator", cpReplaysTerminator ) ),
            "There is no ReplaysTerminator!",
            return false
        );

        return true;
    }

} // namespace nvl

int main(int argc, char* argv[])
{
  ni_detail::InitPointersStatics();

  const int sessionsCount = 2000;                 // количество сессий
  const float sessionLifetime = 60.f*30;         // время жизни сессии
  const float disconnectPeriod = 5.f;            // период проверки сессии на окончание
  const float connectPeriod = 0.1f;              // период добавления новых сессий
  const int simulationThreadsCount = 1;          // количество тредов симуляции логики
  const int clientsThreadsCount = 1;             // количество тредов клиентских
  const bool writeReplaysThroughBDS = false;
  const int scheduleQueueSize = 1024;

  nvl::CPtr< nvl::INodeManager > cpNodeManager;
  nvl::CPtr< nvl::ITerminator > cpReplaysTerminator;

  if ( writeReplaysThroughBDS && nvl::InitializeBDS( cpNodeManager, cpReplaysTerminator ) == false )
      return 1;

  NLogg::CChannelLogger* infoLogStream = &GetSystemLog(); 
  StrongMT<MockPoller> tpoller = new MockPoller;
  AppFramework::TimeSlicer runner(5.f, infoLogStream, simulationThreadsCount, scheduleQueueSize);
  runner.AddInstance(tpoller.Get());

  Clients clients(sessionsCount*clientsPerSession);

  nstl::vector<ClientsThread*> threads;
  for (int i=0;i<clientsThreadsCount;++i)
  {
    NLogg::CChannelLogger* sessionsLogStream = new NLogg::CChannelLogger("sessions");

    StrongMT< ClientsPoller > poller = new ClientsPoller(
      clients,
      sessionsCount / clientsThreadsCount,
      runner,
      sessionLifetime,
      disconnectPeriod,
      connectPeriod,
      infoLogStream,
      sessionsLogStream,
      cpReplaysTerminator );

    ClientsThread* thread = new ClientsThread(poller);
    thread->Resume();
    threads.push_back(thread);
  }
  bool isRunning = true;
  runner.Do(isRunning);

  if ( writeReplaysThroughBDS && cpNodeManager.Get() ) {

    nvl::CPtr< nvl::IBlockDataService > cpBDS;
    NI_VERIFY(
      nvl::NV_CSUCCESS( cpNodeManager->GetService( "BDS", cpBDS.GetRef() ) ),
      "Cannot get BDS instance",
      return 2;
	);

    cpNodeManager->ServiceFinish( cpBDS );

    while ( cpBDS->GetServiceState() != nvl::IService::FINISHED )
        Sleep( 0 );

  }

  return 0;
}
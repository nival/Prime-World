//!Component('System/Pointers')
//!Component('System/Threading')
//!Component('Game/PF/HybridServer/Peered')
//!Component('System/Crc32Utils')
//!Component('System/Random')
//!Component('Server/RPC/Base')
//!Component('System/Savers')
//!Component('System/Dumpers')
//!Component('Server/Roll/RollTypes')
//!Component('System/MemoryBlockPool')

#include <System/stdafx.h>
#include <cxxtest/TestSuite.h>
#include <System/TestSuite.h>
#include <System/ThreadHelpers.h>
#include <Server/RPC/RPC.h>
#include "PeeredImpl.h"
#include "RPeered.auto.h"
#include <conio.h>
#include <System/Win32Random.h>
#include <Server/LobbyPvx/SessionHybridLink.h>
#include "Game/PF/HybridServer/AwardsRoll.h"
#include "HybridServerDumpersIfaces.h"
#include "HybridServerMulticastIface.h"


// RPC
//   поддержка void*, size
//   поддержка битовых полей
//   поддержка in-параметров
//   наследование R-интерфейсов от интерфейсов для упрощения тестирования
//   оптимизация отсылки данных от RPC (периодически или превышении размера)
// быстрая работа с окружностями
// на стороне клиента должно работать накопление команд для замедления
// перемотка и прокрутка на стороне клиента 
// что проиcходит если клиент не присылает crc, или сущности или вообще ведет себя неправильно
// патчинг доверенного клиента
// сборка мира на доверенном клиенте если произошел асинк а собранного мира еще нет
// как применяются изменения в мире ? видимо задом наперед
// если произошел асинк, то мы:
//    блокируем отсылку step
//    запускаем процесс выяснения получаем мир эталонный путем заливки последнего согласованного образа и накатывания команд
//    выясняем кто же разошелся
//    включаем step для хороших клиентов
//    патчим каждого клиента отдельно, кэшируя изменения, отсылаем команды которые были отосланы с тех пор
//    либо отключаем асинкнутых
// надо уметь накатывать мир не полностью
// нужна специфическая история по сегментам, которая висит в памяти постоянно, сегменты отсылаются из нее
//   пишем команды lock free
//   300b с клиента в секунду * 60 *  = 540Kb на клиента за 30 минут сессии, 5 Mb лог  команд сессии на 10 игроков
//   минимум переаллокаций 
// нужен неблокирующий map
// для решения по асинкам нужна информация о порядочности клиентов 

// TODO: this class should be thread safe for AddCommand, FinishStep, GetStep, GetCommand operations

namespace boost
{
  void tss_cleanup_implemented() { }
}

namespace test
{

void CopyVector(const nstl::vector<rpc::MemoryBlock>& src, nstl::vector<rpc::CachedMemoryBlock>& dst)
{
  for (int i=0;i<src.size();++i)
  {
    const byte* data = (const byte*)src[i].memory;
    rpc::CachedMemoryBlock& info = dst.push_back();
    info.Set(data, src[i].size);
  }
}

void FormatCommand(void * command, int clientId, const char * data)
{
  memset(command, 0, sizeof(int));  // Set first part to zero (message typeID, used only by client)
  memcpy((char*)command+sizeof(int), &clientId, sizeof(clientId));
  memcpy((char*)command+sizeof(int)*2, data, strlen(data));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MockCrcDumper : public HybridServer::ICrcDumper, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(MockCrcDumper, HybridServer::ICrcDumper, BaseObjectMT);

  struct CrcData
  {
    int clientId;
    int step;
    rpc::CachedMemoryBlock data;
    int size;
  };

  virtual void OnCrcDump(Peered::TSessionId serverId, int clientId, int step, void * data, int size)
  {
    CrcData & newCrcData = crcData.push_back();
    newCrcData.clientId = clientId;
    newCrcData.step = step;
    newCrcData.data.Set(data, size);
    newCrcData.size = size;
  }

  nstl::vector<CrcData> crcData;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MockCommandsLog : HybridServer::ICommandsLog, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(MockCommandsLog, HybridServer::ICommandsLog, BaseObjectMT);

  struct StepData
  {
    int step;
    nstl::vector<rpc::CachedMemoryBlock> commands; 
  };

protected:
  virtual void OnHeaderDump(const Peered::SchedulerData & data, const lobby::TGameLineUp * gameLineUp, const lobby::SGameParameters * gameParams, const vector<Peered::ClientInfo> * clientInfos) {};
  virtual void OnStartGame(Peered::TSessionId serverId, const Login::ClientVersion & clientVersion, int step) {};
  virtual void OnCommandsDump(Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses)
  {
    for (int i=startStep;i<=endStep;++i)
    {
      nstl::vector<rpc::MemoryBlock> stepCommands;
      TS_ASSERT_EQUALS(true, commands.CopyStep(i, stepCommands));

      StepData& data = steps.push_back();
      data.step = i;
      CopyVector(stepCommands, data.commands);
    }
  }
  virtual void OnFinishGame(Peered::TSessionId serverId, int step) {};

public:
  nstl::vector<StepData> steps;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MockCommandsHandler : public Peered::ICommandsHandler, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(MockCommandsHandler, Peered::ICommandsHandler, BaseObjectMT);

public:
  MockCommandsHandler():onCreateCalled(false) {}
  virtual void OnCreate(Peered::IWorld* world)
  {
    onCreateCalled = true;
  }
  virtual void OnAddClient(int clientIndex, Peered::IGameClient* client, Peered::IWorld* world)
  {
    addedClients.push_back(client);
  }
  virtual void OnRemoveClient(int clientIndex, int clientId, Peered::IGameClient* client, Peered::IWorld* world)
  {
    removedClients.push_back(client);
  }
  virtual bool CheckCommand(Peered::IGameClient* client, const rpc::MemoryBlock& command, Peered::IWorld* world)
  {
    return true;
  }
  nstl::vector<WeakMT<Peered::IGameClient>> addedClients;
  nstl::vector<WeakMT<Peered::IGameClient>> removedClients;
  bool onCreateCalled;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MockSessionLink : public lobby::ISessionHybridLink, BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(MockSessionLink, lobby::ISessionHybridLink, BaseObjectMT);

  MockSessionLink():gameResultType(lobby::EGameResult::Unknown) {}

  virtual void OnGameFinish( Peered::TSessionId sessionId, int _gameResultType, const StatisticService::RPC::SessionClientResults & _finishInfo, const nstl::vector<Peered::SClientStatistics>& _clientStatistics ) 
  {
    gameFinishInfo = _finishInfo;
    gameResultType = lobby::EGameResult::Enum(_gameResultType);
    clientStatistics = _clientStatistics;
  }

  virtual void OnGameCheated( Peered::TSessionId sessionId, Transport::TClientId clientId, int _cheatType, const char * _clientIp ) 
  {
    cheaters.push_back(clientId);
  }

  virtual void OnChangeClientStatus( Peered::TSessionId sessionId, const nstl::vector<Peered::BriefClientInfo>& clientIds ) 
  {
    for (int i=0;i<clientIds.size();++i)
    {
      if (clientIds[i].status == Peered::DisconnectedByClient || 
          clientIds[i].status == Peered::DisconnectedByServer || 
          clientIds[i].status == Peered::ConnectionTimedOut ||
          clientIds[i].status == Peered::DisconnectedByCheatAttempt ||
          clientIds[i].status == Peered::DisconnectedByAsync)
      {
        droppedClients.push_back(clientIds[i].clientId);
      }
    }
    clientStatuses.insert(clientStatuses.end(), clientIds.begin(), clientIds.end());
  }

  StatisticService::RPC::SessionClientResults gameFinishInfo;
  nstl::vector<uint> cheaters;
  nstl::vector<uint> droppedClients;
  nstl::vector<Peered::BriefClientInfo> clientStatuses;
  lobby::EGameResult::Enum gameResultType;
  nstl::vector<Peered::SClientStatistics> clientStatistics;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MockClientReconnect : public Peered::IGameClientReconnect, BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(MockClientReconnect, Peered::IGameClientReconnect, BaseObjectMT);

  virtual void ApplyWorldDataInfo(const Peered::WorldDataInfo& data)
  {
    worldDataInfo = data;
  }

  virtual void ApplyWorldDataPart(const rpc::MemoryBlock& data)
  {
    rpc::CachedMemoryBlock & cachedData = worldDataParts.push_back();
    cachedData = data;
  }

  nstl::vector<rpc::CachedMemoryBlock> worldDataParts;
  Peered::WorldDataInfo worldDataInfo;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MockClient : public Peered::IGameClient, BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(MockClient, Peered::IGameClient, BaseObjectMT);
  struct StepData
  {
    int step;
    nstl::vector<rpc::CachedMemoryBlock> commands; 
    nstl::vector<Peered::BriefClientInfo> statuses;
    nstl::vector<Peered::GapInfo> gaps;
  };

  struct WorldPatchData
  {
    int step;
    uint crc;
    nstl::vector<Peered::BriefEntityInfo> entitiesIds;
    nstl::vector<rpc::CachedMemoryBlock> entitiesData; 
  };

  MockClient():
  worldDataRequested(false),
  crcRequestedForStep(NCore::INVALID_STEP),
  asyncStep(0xFFFFFFFF), 
  asyncCount(0),
  index(-1), 
  simulationStartStep(0xFFFFFFFF),
  timeScale(1.f), 
  serverId(-1), 
  saveData(true),
  disconnectReason(Peered::EDisconnectReason::None),
  status(rpc::Connected),
  confirmFrequency(-1),
  snapshotChunkSize(-1),
  isReconnecting(false),
  snapshotSendPerStep(0),
  minigameEnabled(true),
  stepsDelayMin(1),
  stepsDelayMax(1),
  stepsDelayFrame(0),
  sendReconnectInterface(true),
  lastConfirmedStep(NCore::INVALID_STEP),
  isAwardReceived(false),
  blockedStepsCount(0),
  fastReconnectEnabled(false),
  spectate(false)
  {
  }

  virtual void Start(const Peered::ClientStartInfo& clientStartInfo, Peered::RIGameServerReconnect * gameServerReconnect)
  {
    if (saveData)
    {
      index = clientStartInfo.index;
      serverId = clientStartInfo.serverId;
      clientInfos = clientStartInfo.clientsInfos;
      confirmFrequency = clientStartInfo.confirmFrequency;
      snapshotChunkSize = clientStartInfo.snapshotChunkSize;
      isReconnecting = clientStartInfo.isReconnecting;
      snapshotSendPerStep = clientStartInfo.snapshotSendPerStep;
      stepsDelayMin = clientStartInfo.stepsDelayMin;
      stepsDelayMax = clientStartInfo.stepsDelayMax;
      stepsDelayFrame = clientStartInfo.stepsDelayFrame;
      minigameEnabled = clientStartInfo.clientSettings.minigameEnabled;
      fastReconnectEnabled = clientStartInfo.fastReconnectEnabled;
    }

    if (clientStartInfo.isReconnecting && gameServerReconnect)
    {
      if (sendReconnectInterface)
      {
        mockClientReconnect = new MockClientReconnect();
        LocalPtr<Peered::GameServerReconnect>(gameServerReconnect)->SetGameClientReconnect(clientStartInfo.index, mockClientReconnect);
      }
      delete gameServerReconnect;
    }
  }

  virtual void Step(
    int step, 
    int _lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& clientGaps,
    const Transport::MessageMiscInfo&miscInfo)
  {
    // Ignore blocked steps
    if (step == NCore::INVALID_STEP)
    {
      ++blockedStepsCount;
      return;
    }

    if (saveData)
    {
      StepData& d = steps.push_back();
      d.step = step;
      CopyVector(commands, d.commands);
      d.statuses = statuses;
      d.gaps = clientGaps;
    }

    lastConfirmedStep = _lastConfirmedStep;

    if (statuses.size() > 0)
    {
      clientStatuses.insert(clientStatuses.end(), statuses.begin(), statuses.end());
    }
  }

  void StepBatch(
    int lastConfirmedStep,
    const nstl::vector<Peered::ClientStepData>& stepData)
  {
    for (int i = 0; i < stepData.size(); ++i)
    {
      const Peered::ClientStepData & step = stepData[i];
      Step(step.step, lastConfirmedStep, step.commands, step.statuses, step.clientGaps, Transport::MessageMiscInfo());
    }
  }

  virtual void StepLoading(
    int step, 
    int _lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& clientGaps)
  {
    // Just forward this call to a regular Step. Currently we have separate StepLoading for rpc calls statistics only.
    Step(step, _lastConfirmedStep, commands, statuses, clientGaps, Transport::MessageMiscInfo());
  }

  virtual void OnAsync(int step, const nstl::vector<Peered::AsyncInfo>& _async)
  {
    ++asyncCount;

    if (saveData)
    {
      async = _async;
      asyncStep = step;
    }
  }

  virtual void ApplySnapshot(int step, uint worldCrc, const nstl::vector<Peered::BriefEntityInfo>& entitiesIds, const nstl::vector<rpc::MemoryBlock>& entitiesData)
  {
    if (saveData)
    {
      WorldPatchData& d = patches.push_back();
      d.crc = worldCrc;
      d.step = step;
      d.entitiesIds = entitiesIds;
      CopyVector(entitiesData, d.entitiesData);
    }
  }
  virtual void OnStart(int step)
  {
    if (saveData)
    {
      simulationStartStep = step;
    }
  }

  virtual const nstl::vector<rpc::MemoryBlock>& GetSnapshot(uint step, const nstl::vector<uint>& entitiesIds)
  {
    return entities;
  }

  virtual void SetTimeScale(float scale)
  {
    if (saveData)
    {
      timeScale = scale;
    }
  }

  virtual void OnChangeClientStatus(const nstl::vector<Peered::BriefClientInfo>& _clientStatuses)
  {
    NI_ALWAYS_ASSERT("OnChangeClientStatus is obsolet!");
  }

  virtual void OnDisconnect( int _reason )
  {
    disconnectReason = Peered::EDisconnectReason::Enum(_reason);
  }

  virtual rpc::Status GetStatus() 
  { 
    return status; 
  }

  virtual void RequestWorldData(Peered::RIGameServerReconnect * gameServerReconnect)
  {
    worldDataRequested = true;
    serverReconnect = LocalPtr<Peered::GameServerReconnect>(gameServerReconnect);
    delete gameServerReconnect;
  }

  virtual void RequestCrcData(int step)
  {
    crcRequestedForStep = step;
  }

  virtual void OnRejoin( uint clientId )
  {
    rejoinClientIds.push_back(clientId);
  }

  virtual void Award( const vector<roll::SAwardInfo> & _awards )
  {
    awards = _awards;
    isAwardReceived = true;
  }

  virtual void OnSpectate(const Peered::SpectatorInfo& info)
  {
    spectatorNickname = info.nickname;
    spectate = true;
  }

  virtual void OnPlaySameTeamDecision(const Transport::TClientId clientId, const bool agreed)
  {
  }

  virtual void OnBadBehaviourComplaint(const Transport::TClientId clientId, const Transport::TClientId reportedClientId)
  {
  }

  virtual void OnProtectionAsync(int step)
  {
  }


public:
   StrongMT<MockClientReconnect> mockClientReconnect;
   StrongMT<Peered::IGameServerReconnect> serverReconnect;
   nstl::vector<StepData> steps;
   nstl::vector<rpc::MemoryBlock> entities;
   nstl::vector<WorldPatchData> patches;
   nstl::vector<Peered::AsyncInfo> async;
   nstl::vector<Peered::BriefClientInfo> clientStatuses;
   nstl::vector<uint> rejoinClientIds;
   bool worldDataRequested;
   int crcRequestedForStep;
   uint asyncStep;
   int asyncCount;
   uint simulationStartStep;
   float timeScale;
   int index;
   Peered::TSessionId serverId;
   bool saveData;
   rpc::Status status;
   Peered::EDisconnectReason::Enum disconnectReason;
   nstl::vector<Peered::ClientInfo> clientInfos;
   int confirmFrequency;
   int snapshotChunkSize;
   bool isReconnecting;
   int snapshotSendPerStep;
   bool minigameEnabled;
   int stepsDelayMin;
   int stepsDelayMax;
   int stepsDelayFrame;
   bool sendReconnectInterface;
   int lastConfirmedStep;
   vector<roll::SAwardInfo> awards;
   bool isAwardReceived;
   int blockedStepsCount;
   bool fastReconnectEnabled;
   nstl::wstring spectatorNickname;
   bool spectate;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MockAwardsRequester : public Peered::IAwardsRequester, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockAwardsRequester, Peered::IAwardsRequester, BaseObjectMT );

public:

  MockAwardsRequester() : isAwardsReceived(false), totalSeconds(0), gameResult(lobby::EGameResult::Unknown) {}
  MockAwardsRequester(bool _isAwardsReceived) : isAwardsReceived(_isAwardsReceived), totalSeconds(0), gameResult(lobby::EGameResult::Unknown) {}

  virtual void FillPreGameData(const nstl::vector<Peered::ClientInfo> & _clientsInfo, const Peered::SAuxData & _auxData)
  {
    clientsInfo = _clientsInfo;
    auxData = _auxData;
  }

  virtual void FillPostGameData(lobby::EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _gameFinishInfo, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics, uint _totalSeconds)
  {
    gameResult = _gameResult;
    gameFinishInfo = _gameFinishInfo;
    clientsStatistics = _clientsStatistics;
    totalSeconds = _totalSeconds;
  }

  virtual void Step() {};
  virtual bool IsAwardsReceived() const { return isAwardsReceived; }
  virtual void GetResults(Peered::TUserAwards * _awards) { if(_awards) *_awards = awards; }

  bool isAwardsReceived;
  Peered::TUserAwards awards;

  nstl::vector<Peered::ClientInfo> clientsInfo;
  Peered::SAuxData auxData;

  lobby::EGameResult::Enum gameResult;
  StatisticService::RPC::SessionClientResults gameFinishInfo;
  nstl::vector<Peered::SClientStatistics> clientsStatistics;
  uint totalSeconds;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MockPeeredStatistics : public Peered::IPeeredStatistics, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockPeeredStatistics, Peered::IPeeredStatistics, BaseObjectMT );

public:
  virtual void LogGSLag( StatisticService::RPC::ExceedingStepTimeInfoServer & info )
  {
    lags.push_back( info );
  }

  virtual void LogReconnect( StatisticService::RPC::ReconnectAttemptInfo & info )
  {
    reconnects.push_back( info );
  }

  virtual void LogTraffic( StatisticService::RPC::SessionTrafficInfo & info )
  {
    traffic = info;
  }

  virtual void LogClientStatus( StatisticService::RPC::UserStatusEvent & evt )
  {
    statuses.push_back( evt );
  }

  int GetStatusesDelta() const
  {
    // Calculate per user statuses delta
    nstl::map<int, int> perUserDelta;
    for (int i = 0; i < statuses.size(); ++i)
    {
      int userId = statuses[i].ctx.userid;
      nstl::map<int, int>::iterator it = perUserDelta.find(userId);
      if (it == perUserDelta.end())
        it = perUserDelta.insert(perUserDelta.begin(), nstl::pair<int, int>(userId, 0));
      int status = statuses[i].status;
      if (status == Peered::Connecting)
        ++(it->second);
      else  // We do not count connection timeouts, because it is not "in" nor "out" 
        if (status != Peered::ConnectionTimedOut && status != Peered::ConnectionTimedOutOnReconnect)
          --(it->second);
    }
    // Calculate total statuses delta
    int totalDelta = 0;
    for (nstl::map<int, int>::iterator it = perUserDelta.begin(); it != perUserDelta.end(); ++it)
    {
      totalDelta += it->second;
    }
    return totalDelta;
  }

  bool CheckStatusRange(int first, int last, int status, int reason = Peered::EDisconnectReason::None)
  {
    if (first < 0 || last >= statuses.size() || first > last)
      return false;

    for (int i = first; i <= last; ++i)
      if (statuses[i].status != status || statuses[i].reason != reason)
        return false;

    return true;
  }

  nstl::vector<StatisticService::RPC::ExceedingStepTimeInfoServer> lags;
  nstl::vector<StatisticService::RPC::ReconnectAttemptInfo> reconnects;
  StatisticService::RPC::SessionTrafficInfo traffic;
  nstl::vector<StatisticService::RPC::UserStatusEvent> statuses;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MockMcChannelsWrapper : public HybridServer::IMcChannelsWrapper, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(MockMcChannelsWrapper, IMcChannelsWrapper, BaseObjectMT);

public:
  MockMcChannelsWrapper()
    : isClosed(false)
    , retValue(true)
  {
  }

  virtual bool AddClient(const Peered::IGameClient * client, uint clientId, int clientIndex)
  {
    newClients.push_back(clientId);
    return retValue;
  }

  virtual bool RemoveClient(uint clientId)
  {
    TMulticastClients::iterator it = clients.find(clientId);
    if (it != clients.end())
      clients.erase(it);
    return retValue;
  }

  virtual bool FindClient(uint clientId)
  {
    return (clients.find(clientId) != clients.end());
  }

  virtual int GetClientsCount()
  {
    return clients.size();
  }

  virtual bool SendData(const byte * _data, int size)
  {
    rpc::CachedMemoryBlock& newData = data.push_back();
    newData.Set(_data, size);
    return retValue;
  }

  virtual void Close()
  {
    isClosed = true;
  }

  void ConnectNewClients()
  {
    if (newClients.size() > 0)
    {
      clients.reserve(clients.size() + newClients.size());
      clients.insert(clients.end(), newClients.begin(), newClients.end());
      newClients.clear();
    }
  }

  typedef vector<uint> TMulticastClients;
  typedef vector<rpc::CachedMemoryBlock> TData;

  TMulticastClients clients;
  TMulticastClients newClients;
  TData data;

  bool isClosed;
  bool retValue;
};

void CheckStepsConsistency(const nstl::vector<MockClient::StepData> & steps)
{
  for (int i = 0; i < steps.size() - 1; ++i)
  {
    TS_ASSERT_EQUALS(steps[i].step + 1, steps[i+1].step);
  }
}

}  // namespace test


struct Test_PeeredSimulation : public CxxTest::TestSuite
{
  nstl::vector<Peered::EntityInfo> changedEntities;
  nstl::vector<Peered::EntityInfo> addedEntities;
  nstl::vector<uint> deletedEntities;
  nstl::vector<rpc::MemoryBlock> requestedEntitiesData;

  int AddClient(Peered::CommandsScheduler* p, const char* name, int clientId, test::MockClient* client, bool clientReady)
  {
    p->AddClient(name, clientId, Login::ClientVersion(), client);
    int index = client?client->index:-1;
    if (clientReady && client)
    {
      p->OnClientReady(index);
    }
    return index;
  }

  void SendNumberedCommand( Peered::CommandsScheduler* p, int clientIndex, int clientId, const char* data, int i, bool isPlayerCommand = true )
  {
    char buffer[256];
    int length = sprintf_s(buffer, "%s%d", data, i);

    char commandData[256+8];
    test::FormatCommand(&commandData, clientId, buffer);
    rpc::MemoryBlock command(commandData, length + 8);

    p->SendCommand(clientIndex, command, isPlayerCommand);
  }

  nstl::vector<Peered::ClientInfo> clientIds;
  nstl::vector<Peered::ClientInfo>* FillClients(int id0, int id1, NCore::PlayerInfo* data0 = 0, NCore::PlayerInfo* data1 = 0)
  {
    {
      Peered::ClientInfo info;
      info.clientId = id0;
      if (data0)
      {
        info.info = *data0;
      }
      clientIds.push_back(info);
    }
    {
      Peered::ClientInfo info;
      info.clientId = id1;
      if (data1)
      {
        info.info = *data1;
      }
      clientIds.push_back(info);
    }
    return &clientIds;
  }

  nstl::vector<Peered::ClientInfo>* FillClients(int id0, int id1, const NCore::PlayerInfo& data0, const NCore::PlayerInfo& data1)
  {
    {
      Peered::ClientInfo info;
      info.clientId = id0;
      info.info = data0;
      clientIds.push_back(info);
    }
    {
      Peered::ClientInfo info;
      info.clientId = id1;
      info.info = data1;
      clientIds.push_back(info);
    }
    return &clientIds;
  }

  nstl::vector<Peered::ClientInfo>* FillClients(int id0, int id1, int id2)
  {
    {
      Peered::ClientInfo info;
      info.clientId = id0;
      clientIds.push_back(info);
    }
    {
      Peered::ClientInfo info;
      info.clientId = id1;
      clientIds.push_back(info);  
    }
    {
      Peered::ClientInfo info;
      info.clientId = id2;
      clientIds.push_back(info);
    }
    return &clientIds;
  }

  nstl::vector<Peered::ClientInfo>* FillClients(int id0)
  {
    {
      Peered::ClientInfo info;
      info.clientId = id0;
      clientIds.push_back(info);
    }
    return &clientIds;
  }

  nstl::vector<Peered::ClientInfo>* FillClientsAscending(int clientsCount)
  {
    clientIds.clear();
    for (int i = 0; i < clientsCount; ++i)
    {
      Peered::ClientInfo info;
      info.clientId = i;
      clientIds.push_back(info);
    }
    return &clientIds;
  }

  void clearIds()
  {
    clientIds.clear();
  }

  void setUp()
  {
    clearIds();
  }


  Peered::CommandsScheduler* Create(
    int _trustGap=0, 
    int _simulationStep=100, 
    Peered::ICommandsHandler* _handler=0, 
    HybridServer::ICommandsLog* _log=0, 
    int _dumpStepsMaxCount=2000,
    Peered::TSessionId _serverId=0,
    const vector<Peered::ClientInfo>* _clientIds=0,
    lobby::ISessionHybridLink * _statsLink = 0,
    NLogg::CChannelLogger* _logStream=0,
    int _afkStepsCount=0,
    int _disconnectionGap=0,
    int _connectionTimeout=0,
    int _confirmFrequency=1,
    int _firstConnectionTimeout=0,
    int _snapshotRequestTimeout=0,
    int _afkStepsDisconnectCount=0,
    int _snapshotChunkSize=1024,
    int _snapshotChunkMaxCount=4096,
    bool _reconnectEnabled = true,
    const Peered::SAuxData * _auxData = 0,
    int _loadTimeoutSteps = 0,
    int _snapshotApplyTimeout = 0,
    int _snapshotSendPerStep = 64000,
    bool _minigameEnabled = true,
    int _finishTimeoutSteps = 300,
    int _commandMaxSize = 128,
    int _commandsPerStepMaxSize = 64000,
    bool _timescaleEnabled = false,
    int _stepsDelayMin = 1,
    int _stepsDelayMax = 1,
    int _stepsDelayFrame = 0,
    int _reconnectTimeout = 0,
    bool _crcDataRequestsEnabled = false,
    int _crcDataRequestsTimeout = 500,
    HybridServer::ICrcDumper* _crcDumper = 0,
    int _rollTimeout = 0,
    Peered::IAwardsRequester* _awardsRequester = 0,
    int _fastReconnectReserveSteps = 0,
    bool _sendAsyncToAllClientsEnabled = false,
    Peered::IPeeredStatistics * _statisticsWrapper = 0)
  {
    Peered::SchedulerData data;
    data.serverId = _serverId;
    data.sessionSettings.trustGap = _trustGap;
    data.sessionSettings.simulationStep = _simulationStep;
    data.sessionSettings.dumpStepsMaxCount = _dumpStepsMaxCount;
    data.sessionSettings.afkStepsCount = _afkStepsCount;
    data.sessionSettings.disconnectionGap = _disconnectionGap;
    data.sessionSettings.connectionTimeout = _connectionTimeout;
    data.sessionSettings.confirmFrequency = _confirmFrequency;
    data.sessionSettings.firstConnectionTimeout = _firstConnectionTimeout;
    data.sessionSettings.snapshotRequestTimeout = _snapshotRequestTimeout;
    data.sessionSettings.afkStepsDisconnectCount = _afkStepsDisconnectCount;
    data.sessionSettings.snapshotChunkSize = _snapshotChunkSize;
    data.sessionSettings.snapshotChunkMaxCount = _snapshotChunkMaxCount;
    data.sessionSettings.reconnectEnabled = _reconnectEnabled;
    data.sessionSettings.loadTimeoutSteps = _loadTimeoutSteps;
    data.sessionSettings.snapshotApplyTimeout = _snapshotApplyTimeout;
    data.sessionSettings.snapshotSendPerStep = _snapshotSendPerStep;
    data.sessionSettings.finishTimeoutSteps = _finishTimeoutSteps;
    data.sessionSettings.commandMaxSize = _commandMaxSize;
    data.sessionSettings.commandsPerStepMaxSize = _commandsPerStepMaxSize;
    data.sessionSettings.timescaleEnabled = _timescaleEnabled;
    data.sessionSettings.stepsDelayMin = _stepsDelayMin;
    data.sessionSettings.stepsDelayMax = _stepsDelayMax;
    data.sessionSettings.stepsDelayFrame = _stepsDelayFrame;
    data.sessionSettings.reconnectTimeout = _reconnectTimeout;
    data.sessionSettings.crcDataRequestsEnabled = _crcDataRequestsEnabled;
    data.sessionSettings.crcDataRequestsTimeout = _crcDataRequestsTimeout;
    data.sessionSettings.rollTimeout = _rollTimeout;
    data.sessionSettings.fastReconnectReserveSteps = _fastReconnectReserveSteps;
    data.sessionSettings.sendAsyncToAllClientsEnabled = _sendAsyncToAllClientsEnabled;
    data.clientSettings.minigameEnabled = _minigameEnabled;

    Transport::TServiceId reconnectIfaceId;
    const lobby::TGameLineUp gameLineUp;
    const lobby::SGameParameters gameParams;

    return new Peered::CommandsScheduler(data, reconnectIfaceId, _handler, _log, _crcDumper, _clientIds, _statsLink, _auxData, _logStream, 0, 0, _awardsRequester, &gameLineUp, &gameParams, _statisticsWrapper);
  }

  Peered::CommandsScheduler* Create(
    Peered::SchedulerData & data,
    Peered::ICommandsHandler* _handler = 0,
    HybridServer::ICommandsLog* _log = 0,
    const vector<Peered::ClientInfo>* _clientIds = 0,
    lobby::ISessionHybridLink * _statsLink = 0,
    NLogg::CChannelLogger* _logStream = 0,
    const Peered::SAuxData * _auxData = 0,
    HybridServer::ICrcDumper* _crcDumper = 0,
    Peered::IAwardsRequester* _awardsRequester = 0,
    Peered::IPeeredStatistics * _statisticsWrapper = 0)
  {
    Transport::TServiceId reconnectIfaceId;
    return new Peered::CommandsScheduler(data, reconnectIfaceId, _handler, _log, _crcDumper, _clientIds, _statsLink, _auxData, _logStream, 0, 0, _awardsRequester, 0, 0, _statisticsWrapper);
  }

  struct SchedulerObjects
  {
    Peered::ICommandsHandler * handler;
    HybridServer::ICommandsLog * log;
    lobby::ISessionHybridLink * statsLink;
    NLogg::CChannelLogger * logStream;
    const Peered::SAuxData * auxData;
    HybridServer::ICrcDumper * crcDumper;
    Peered::IAwardsRequester * awardsRequester;
    Peered::IPeeredStatistics * statisticsWrapper;
    HybridServer::IMcChannelsWrapper * mcChannelsWrapper;

    SchedulerObjects(
      Peered::ICommandsHandler* _handler = 0,
      HybridServer::ICommandsLog* _log = 0,
      lobby::ISessionHybridLink * _statsLink = 0,
      NLogg::CChannelLogger* _logStream = 0,
      const Peered::SAuxData * _auxData = 0,
      HybridServer::ICrcDumper* _crcDumper = 0,
      Peered::IAwardsRequester* _awardsRequester = 0,
      Peered::IPeeredStatistics * _statisticsWrapper = 0,
      HybridServer::IMcChannelsWrapper * _mcChannelsWrapper = 0)
      : handler(_handler)
      , log(_log)
      , statsLink(_statsLink)
      , logStream(_logStream)
      , auxData(_auxData)
      , crcDumper(_crcDumper)
      , awardsRequester(_awardsRequester)
      , statisticsWrapper(_statisticsWrapper)
      , mcChannelsWrapper(_mcChannelsWrapper)
    {
    }
  };

  Peered::CommandsScheduler* Create(
    Peered::SchedulerData & data,
    SchedulerObjects & objects,
    const vector<Peered::ClientInfo> * clientIds)
  {
    Transport::TServiceId reconnectIfaceId;
    return new Peered::CommandsScheduler(data, reconnectIfaceId, objects.handler, objects.log, objects.crcDumper, 
                                          clientIds, objects.statsLink, objects.auxData, objects.logStream, 0, 0,
                                          objects.awardsRequester, 0, 0, objects.statisticsWrapper, objects.mcChannelsWrapper);
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Tests section
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void test_EmptyStep()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();

    for (int i=0;i<10;++i)
    {
      p->Step();
    }
    StrongMT<test::MockClient> client0 = new test::MockClient();
    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(0, client0->simulationStartStep);
  }

  void test_SimulationStep()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(100, 200, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 
                                                    4096, true, 0, 0, 0, 64000, true, 300, 128, 64000, true);

    TS_ASSERT_EQUALS(200, p->Step());

    StrongMT<test::MockClient> client0 = new test::MockClient();
    TS_ASSERT_EQUALS(1.f, client0->timeScale);

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);

    TS_ASSERT_EQUALS(200, p->Step());
    p->SetTimeScale(clientIndex0, 0.5);
    TS_ASSERT_EQUALS(0.5f, client0->timeScale);

    TS_ASSERT_EQUALS(400, p->Step());

    StrongMT<test::MockClient> client1 = new test::MockClient();
    AddClient(p, "ivn", 0, client1, false);
    TS_ASSERT_EQUALS(0.5f, client1->timeScale);
  }

  void test_Simple()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();
    StrongMT<test::MockClient> client = new test::MockClient();

    int clientIndex = AddClient(p, "redjack", 0, client, false);
    p->OnClientReady(clientIndex);

    const int commandSize = 11;
    char commandData[commandSize];
    test::FormatCommand(&commandData, 0, "cmd");
    rpc::MemoryBlock command(commandData, commandSize);
    p->SendCommand(clientIndex, command, true);
    TS_ASSERT_EQUALS(0, client->steps.size());
    p->Step();
    TS_ASSERT_EQUALS(0, client->steps[0].step);
    TS_ASSERT_EQUALS(1, client->steps[0].commands.size());
    TS_ASSERT_EQUALS(commandSize, client->steps[0].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData, client->steps[0].commands[0].memory, commandSize);

    p->Step();
    TS_ASSERT_EQUALS(2, client->steps.size());
    TS_ASSERT_EQUALS(1, client->steps[1].step);
    TS_ASSERT_EQUALS(0, client->steps[1].commands.size());

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 0, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    const int commandSize1 = 13;
    char commandData1[commandSize1];
    test::FormatCommand(&commandData1, 0, "cmd55");
    rpc::MemoryBlock command1(commandData1, commandSize1);
    p->SendCommand(clientIndex, command0, true);
    p->SendCommand(clientIndex, command1, true);
    p->Step();
    TS_ASSERT_EQUALS(3, client->steps.size());
    TS_ASSERT_EQUALS(2, client->steps[2].commands.size());

    TS_ASSERT_EQUALS(commandSize0, client->steps[2].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, client->steps[2].commands[0].memory, commandSize0);

    TS_ASSERT_EQUALS(commandSize1, client->steps[2].commands[1].size);
    TS_ASSERT_SAME_DATA(commandData1, client->steps[2].commands[1].memory, commandSize1);
  }

  void test_MemLeak()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();
    StrongMT<test::MockClient> client = new test::MockClient();

    int clientIndex = AddClient(p, "redjack", 0, client, false);
    p->OnClientReady(clientIndex);

    const int commandSize = 11;
    char commandData[commandSize];
    test::FormatCommand(&commandData, 0, "cmd");
    rpc::MemoryBlock command(commandData, commandSize);
    p->SendCommand(clientIndex, command, true);
  }

  void test_TwoClients()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "ivn", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    const int commandSize0 = 11;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 0, "cmd");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    p->SendCommand(clientIndex0, command0, true);
   
    const int commandSize1 = 12;
    char commandData1[commandSize1];
    test::FormatCommand(&commandData1, 1, "cmd1");
    rpc::MemoryBlock command1(commandData1, commandSize1);
    p->SendCommand(clientIndex1, command1, true);

    p->Step();
    TS_ASSERT_EQUALS(0, client0->steps[0].step);
    TS_ASSERT_EQUALS(2, client0->steps[0].commands.size());

    TS_ASSERT_EQUALS(commandSize0, client0->steps[0].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, client0->steps[0].commands[0].memory, commandSize0);
    TS_ASSERT_EQUALS(commandSize1, client0->steps[0].commands[1].size);
    TS_ASSERT_SAME_DATA(commandData1, client0->steps[0].commands[1].memory, commandSize1);
  }

  void test_CrcCheckFrequencyZero()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2, 100, 0, 0, 2000, 0, FillClients(0, 1), 0, 0, 0, 0, 0, 0, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    TS_ASSERT_EQUALS(0, client0->confirmFrequency);
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);
      TS_ASSERT_EQUALS(0, client1->confirmFrequency);

    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->Step();

    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 1, client1->steps.size() );

    for (int i=0;i<100;++i)
    {
      p->OnFinishStep(clientIndex0, i, 0xF00D);
      p->OnFinishStep(clientIndex1, i, 0xD00F);

      p->Step();
      TS_ASSERT_EQUALS( i+2, client0->steps.size() );
      TS_ASSERT_EQUALS( i+2, client1->steps.size() );
    }
  }                   

  void check_CrcFrequency(int frequency, bool sendCommandsDuringLoad=false)
  {
    clearIds();
    StrongMT<Peered::CommandsScheduler> p = Create(2, 100, 0, 0, 2000, 0, FillClients(0, 1), 0, 0, 0, 0, 0, frequency);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
      TS_ASSERT_EQUALS(frequency, client0->confirmFrequency);
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);
      TS_ASSERT_EQUALS(frequency, client1->confirmFrequency);

    int stepsSent = 0;
    if (sendCommandsDuringLoad)
    {
      int n=1;
      if (frequency == 2)
      {
        n = 1;
      } else if (frequency != 1)
      {
        n = frequency-2;
      }

      
      for (int i=0;i<n;++i)
      {
        const int commandSize = 12;
        char commandData[commandSize];
        test::FormatCommand(&commandData, 0, "cmd0");
        rpc::MemoryBlock command(commandData, commandSize);
        p->SendCommand(clientIndex0, command, true);
        p->Step();
        stepsSent += 1;
      }
    }
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    TS_ASSERT_EQUALS(stepsSent, client0->simulationStartStep);
    TS_ASSERT_EQUALS(stepsSent, client1->simulationStartStep);

    for (int i=0;i<10*frequency;++i)
    {
      p->Step();
      int steps = stepsSent+i;
      TS_ASSERT_EQUALS( steps+1 , client0->steps.size() );
      TS_ASSERT_EQUALS( steps+1, client1->steps.size() );

      if (steps % frequency == 0)
      {
        p->OnFinishStep(clientIndex0, steps, 0xF00D);
        p->OnFinishStep(clientIndex1, steps, 0xF00D);
      } else
      {
        p->OnFinishStep(clientIndex0, steps, 0xF00D);
        p->OnFinishStep(clientIndex1, steps, 0xD00F);
      }
    }
  }

  void test_CrcCheckFrequencyTwo()
  {
    for (int i=1;i<=10;++i)
    {
      check_CrcFrequency(i);
    }
  }

  void test_CrcCheckFrequencyNWithCommandsDuringLoad()
  {
    for (int i=2;i<=10;++i)
    {
      check_CrcFrequency(i, true);
    }
  }

  void test_CrcCheckingSimple()
  {
    StrongMT<test::MockClient> server = new test::MockClient();
    StrongMT<Peered::CommandsScheduler> p = Create();

    int trustedCliendIndex = 0xFFFFFFFF;
    p->AddTrustedClient(0xFFFFFFFF, server);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "sippul", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());

    TS_ASSERT_EQUALS(0, server->steps.size());
    p->OnFinishStep(clientIndex0, 0, 0xF00D);
    p->OnFinishStep(clientIndex1, 0, 0xBADF00D);
    TS_ASSERT_EQUALS(0, client1->patches.size());
    TS_ASSERT_EQUALS(1, server->steps.size());

    //TODO: trusted client is not properly supported after adding selective kick of async clients. should be fixed!
    /*p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());*/

    p->OnFinishStep(trustedCliendIndex, 0, 0xF00D);
    //TODO: trusted client is not properly supported after adding selective kick of async clients. should be fixed!
    /*TS_ASSERT_EQUALS(1, client1->patches.size());
    TS_ASSERT_EQUALS(0, client0->patches.size());
    TS_ASSERT_EQUALS(0, server->patches.size());
    TS_ASSERT_EQUALS(0, client1->patches[0].step);
    TS_ASSERT_EQUALS(0xF00D, client1->patches[0].crc);*/
 }

  void test_FullHistoryCommandsSending()
  {
    StrongMT<test::MockClient> server = new test::MockClient();
    StrongMT<Peered::CommandsScheduler> p = Create();

    int trustedClientIndex = 0xFFFFFFFF;
    p->AddTrustedClient(trustedClientIndex, server);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "sippul", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    p->Step();

    p->OnFinishStep(clientIndex0, 0, 0xF00D);
    p->OnFinishStep(clientIndex1, 0, 0xF00D);

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 0, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    p->SendCommand(clientIndex0, command0, true);
    const int commandSize1 = 12;
    char commandData1[commandSize1];
    test::FormatCommand(&commandData1, 1, "cmd1");
    rpc::MemoryBlock command1(commandData1, commandSize1);
    p->SendCommand(clientIndex1, command1, true);
    p->Step();

    p->OnFinishStep(clientIndex1, 1, 0xF00D);
    p->OnFinishStep(clientIndex0, 1, 0xBADF00D);

    TS_ASSERT_EQUALS(2, server->steps.size());
    TS_ASSERT_EQUALS(0, server->steps[0].step);
    TS_ASSERT_EQUALS(0, server->steps[0].commands.size());

    TS_ASSERT_EQUALS(1, server->steps[1].step);
    TS_ASSERT_EQUALS(2, server->steps[1].commands.size());

    TS_ASSERT_EQUALS(commandSize0, server->steps[1].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, server->steps[1].commands[0].memory, commandSize0);
    TS_ASSERT_EQUALS(commandSize1, server->steps[1].commands[1].size);
    TS_ASSERT_SAME_DATA(commandData1, server->steps[1].commands[1].memory, commandSize1);

    p->OnFinishStep(trustedClientIndex, 1, 0xF00D);
    //TODO: trusted client is not properly supported after adding selective kick of async clients. should be fixed!
    /*TS_ASSERT_EQUALS(1, client0->patches.size());
    TS_ASSERT_EQUALS(0, client1->patches.size());
    TS_ASSERT_EQUALS(0, server->patches.size());
    TS_ASSERT_EQUALS(1, client0->patches[0].step);
    TS_ASSERT_EQUALS(0xF00D, client0->patches[0].crc);*/
  }

  void test_SecondAsync()
  {
  }

  void test_RecievingAsyncCrcWhileCheckingOnTheWay()
  {
    StrongMT<test::MockClient> server = new test::MockClient();
    StrongMT<Peered::CommandsScheduler> p = Create(3);

    int trustedClientIndex = 0xFFFFFFFF;
    p->AddTrustedClient(trustedClientIndex, server);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "sippul", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());

    p->OnFinishStep(clientIndex0, 0, 0xF00D);
    p->OnFinishStep(clientIndex1, 0, 0xF00D);

    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());

    p->Step();
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());

    p->OnFinishStep(clientIndex1, 1, 0xF00D);
    p->OnFinishStep(clientIndex0, 1, 0xBADF00D);

    p->OnFinishStep(clientIndex1, 2, 0xF00D);
    p->OnFinishStep(clientIndex0, 2, 0xBADF00D);

    // check that we are waiting for verification of asynced steps (1 and 2)
    for (int i=0;i<10;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(3, client0->steps.size());
      TS_ASSERT_EQUALS(3, client1->steps.size());
    }

    // step 1 verified
    p->OnFinishStep(trustedClientIndex, 1, 0xF00D);

    // check that we are waiting for verification of asynced step 2
    p->Step();
    //TODO: trusted client is not properly supported after adding selective kick of async clients. should be fixed!
    /*TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());

    for (int i=0;i<10;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(5, client0->steps.size());
      TS_ASSERT_EQUALS(5, client1->steps.size());
    }

    // step 2 verified and clients could step further now
    p->OnFinishStep(trustedClientIndex, 2, 0xF00D);

    p->Step();

    TS_ASSERT_EQUALS(6, client0->steps.size());
    TS_ASSERT_EQUALS(6, client1->steps.size());*/
  }

  void test_AsyncedClientCommandsBehaviour()
  {
  }

  void test_ClientDisconnection()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);

    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->Step();

    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 1, client1->steps.size() );

    client0->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS( 2, client1->steps.size() );

    p->OnFinishStep(clientIndex1, 0, 0xF00D);

    p->Step();
    TS_ASSERT_EQUALS( 3, client1->steps.size() );
  }

  void test_ClientDisconnectionWhenHeIsLastWithStepConfirmation()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);

    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->Step();

    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 1, client1->steps.size() );

    p->Step();
    TS_ASSERT_EQUALS( 2, client0->steps.size() );
    TS_ASSERT_EQUALS( 2, client1->steps.size() );

    p->OnFinishStep(clientIndex1, 0, 0xF00D);

    client0->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS( 3, client1->steps.size() );
  }

  void test_ClientDisconnectionBeforeAllClientsReady()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 0, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);

    const int commandSize1 = 12;
    char commandData1[commandSize1];
    test::FormatCommand(&commandData1, 1, "cmd1");
    rpc::MemoryBlock command1(commandData1, commandSize1);

    for (int i=0;i<10;++i)
    {
      p->SendCommand(clientIndex0, command0, true);
      p->SendCommand(clientIndex1, command1, true);
      p->Step();
      TS_ASSERT_EQUALS( i+1, client0->steps.size() );
      TS_ASSERT_EQUALS( i+1, client1->steps.size() );
    }
    client0->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    for (int i=0;i<10;++i)
    {
      p->SendCommand(clientIndex1, command1, true);
      p->Step();
      TS_ASSERT_EQUALS( 10+i+1, client1->steps.size() );
    }
    p->OnClientReady(clientIndex1);
    TS_ASSERT_EQUALS(20, client1->simulationStartStep);
  }

  void test_CheckSyncOnStart()
  {
    StrongMT<test::MockClient> server = new test::MockClient();
    StrongMT<Peered::CommandsScheduler> p = Create(2);

    int trustedClientIndex = 0xFFFFFFFF;
    p->AddTrustedClient(trustedClientIndex, server);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);
    int clientIndex2 = AddClient(p, "test3", 2, client2, false);

    p->Step();
    TS_ASSERT_EQUALS( 0xFFFFFFFF, client0->simulationStartStep );
    TS_ASSERT_EQUALS( 0xFFFFFFFF, client1->simulationStartStep );
    TS_ASSERT_EQUALS( 0xFFFFFFFF, client2->simulationStartStep );

    p->OnClientReady( clientIndex0 );
    p->Step();
    TS_ASSERT_EQUALS( 0xFFFFFFFF, client0->simulationStartStep );
    TS_ASSERT_EQUALS( 0xFFFFFFFF, client1->simulationStartStep );
    TS_ASSERT_EQUALS( 0xFFFFFFFF, client2->simulationStartStep );

    p->OnClientReady( clientIndex1 );
    p->Step();
    TS_ASSERT_EQUALS( 0xFFFFFFFF, client0->simulationStartStep );
    TS_ASSERT_EQUALS( 0xFFFFFFFF, client1->simulationStartStep );
    TS_ASSERT_EQUALS( 0xFFFFFFFF, client2->simulationStartStep );

    p->OnClientReady( clientIndex2 );
    p->Step();
    TS_ASSERT_EQUALS( 0, client0->simulationStartStep );
    TS_ASSERT_EQUALS( 0, client1->simulationStartStep );
    TS_ASSERT_EQUALS( 0, client2->simulationStartStep );
  }

  void test_CheckCommandsWhileWaiting()
  {
    StrongMT<test::MockClient> server = new test::MockClient();
    StrongMT<Peered::CommandsScheduler> p = Create(2);

    int trustedClientIndex = 0xFFFFFFFF;
    p->AddTrustedClient(trustedClientIndex, server);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);
    int clientIndex2 = AddClient(p, "test3", 2, client2, false);

    p->Step();
    p->OnClientReady( clientIndex0 );

    // check that only ready client recieve step
    p->Step();
    TS_ASSERT_EQUALS( 0, client0->steps.size() );
    TS_ASSERT_EQUALS( 0, client1->steps.size() );
    TS_ASSERT_EQUALS( 0, client2->steps.size() );

    // all clients should recive step cause we have command
    char buffer[128];
    // Just memset the command to 0. No need in FormatCommand, because the clientId is 0 too
    memset( buffer, 0, sizeof( buffer ) );
    rpc::MemoryBlock block( buffer, sizeof( buffer ) );
    p->SendCommand( clientIndex0, block, true );
    p->Step();
    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 1, client1->steps.size() );
    TS_ASSERT_EQUALS( 1, client2->steps.size() );

    p->OnClientReady( clientIndex1 );
    p->OnClientReady( clientIndex2 );
 }

  void test_CheckDelayedWorldCrcDeliveringWithoutTrustedClientUsage()
  {
    StrongMT<test::MockClient> server = new test::MockClient();
    StrongMT<Peered::CommandsScheduler> p = Create(2);

    int trustedClientIndex = 0xFFFFFFFF;
    p->AddTrustedClient(trustedClientIndex, server);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "sippul", 1, client1, false);
    p->OnClientReady( clientIndex0 );
    p->OnClientReady( clientIndex1 ) ;

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());

    p->OnFinishStep(clientIndex0, 0, 0xF00D);

    // check that we are waiting for verification of asynced steps (1 and 2)
    for (int i=0;i<10;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(2, client0->steps.size());
      TS_ASSERT_EQUALS(2, client1->steps.size());
    }

    p->OnFinishStep(clientIndex1, 0, 0xF00D);
    p->Step();
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
  }

  //void test_CheckDelayedWorldCrcDeliveringWithTrustedClientUsage()
  //{
  //  StrongMT<test::MockClient> server = new test::MockClient();
  //  StrongMT<Peered::CommandsScheduler> p = Create(2);
  //  int trustedClientIndex = 0xFFFFFFFF;
  //  p->AddTrustedClient(trustedClientIndex, server);
  //  StrongMT<test::MockClient> client0 = new test::MockClient();
  //  StrongMT<test::MockClient> client1 = new test::MockClient();
  //  int clientIndex0 = AddClient(p, "redjack", 0, client0);
  //  int clientIndex1 = AddClient(p, "sippul", 1, client1);

  //  for (int i=0;i<10;++i)
  //  {
  //    p->Step();
  //    p->OnFinishStep(clientIndex0, i, 0xF00D);
  //    p->OnFinishStep(clientIndex1, i, 0xF00D);
  //  }

  //  p->Step();

  //  p->OnFinishStep(clientIndex0, 10, 0xF00D);
  //  TS_ASSERT_EQUALS(0, server->steps.size());

  //  p->OnFinishStep(clientIndex0, 11, 0xF00D);
  //  TS_ASSERT_EQUALS(0, server->steps.size());
  //  p->Step();
  //  TS_ASSERT_EQUALS(11, server->steps.size());
  //  TS_ASSERT_EQUALS(11, client0->steps.size());
  //  TS_ASSERT_EQUALS(11, client1->steps.size());

  //  p->Step();
  //  TS_ASSERT_EQUALS(11, server->steps.size());
  //  TS_ASSERT_EQUALS(11, client0->steps.size());
  //  TS_ASSERT_EQUALS(11, client1->steps.size());

  //  p->OnFinishStep(trustedClientIndex, 10, 0xF00D);
  //  p->Step();
  //  TS_ASSERT_EQUALS(11, server->steps.size());
  //  TS_ASSERT_EQUALS(13, client0->steps.size());
  //  TS_ASSERT_EQUALS(13, client1->steps.size());

  //  p->OnFinishStep(trustedClientIndex, 11, 0xF00D);
  //  p->Step();
  //  TS_ASSERT_EQUALS(14, server->steps.size());
  //  TS_ASSERT_EQUALS(13, client0->steps.size());
  //  TS_ASSERT_EQUALS(13, client1->steps.size());
  //}

  void test_CheckIfWorldHasBeenAsyncedForOneFrame()
  {
  }

  void test_TwoClientsAsynced()
  {
  }

  void test_AsyncInSecondClientWhileThirdClientIsOk()
  {
  }

  void test_Asynchronous()
  {
    struct WorkerThread
    {
      WorkerThread(Peered::CommandsScheduler* _p, bool _sendCommand, int& _cycleCounter, int _clientIndex):
      p(_p),
      sendCommand(_sendCommand),
      cycleCounter(_cycleCounter),
      clientIndex(_clientIndex)
      {
      }

      virtual uint Process(volatile bool& isRunning)
      {
        const int commandSize = 11;
        char commandData[commandSize];
        test::FormatCommand(&commandData, 0, "cmd");
        rpc::MemoryBlock command(commandData, commandSize);

        while (isRunning)
        {
          cycleCounter++;
          if (sendCommand)
          {
            for (int i=0;i<10;++i)
            {
              p->SendCommand(clientIndex, command, true);
            }
            threading::Sleep(0);
          } else
          {
            p->Step();
            threading::Sleep(20);
          }
        }
        return 0;
      }
      StrongMT<Peered::CommandsScheduler> p;
      bool sendCommand;
      int& cycleCounter;
      int clientIndex;
    };

    StrongMT<Peered::CommandsScheduler> p = Create();
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    p->OnClientReady(clientIndex0);

    AddClient(p, "sippul", 1, client1, true);

    int threadsCount = 2;
    nstl::vector<WorkerThread*> workers;
    nstl::vector<threading::ProcessingThread<WorkerThread> *> threads;
    int cycleCounter0 = 0;
    int cycleCounter1 = 0;
    for (int i=0;i<threadsCount;++i)
    {
      WorkerThread* worker = new WorkerThread(p, i==0, (i==0)?cycleCounter0:cycleCounter1, clientIndex0);
      workers.push_back(worker);
      threading::ProcessingThread<WorkerThread>* thread = new threading::ProcessingThread<WorkerThread>(*worker);
      threads.push_back(thread);
    }
    while (cycleCounter0 < 10)
    {
      threading::Sleep(1);
    }
    for (int i=0;i<threads.size();++i)
    {
      threads[i]->Stop(false);
    }    
    for (int i=0;i<threads.size();++i)
    {
      threads[i]->Stop(true);
      delete threads[i];
      delete workers[i];
    } 
  }

  void test_AddEntity()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "ivn", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    Peered::BriefEntityInfo info = { 'ENID', 'ECRC' };
    rpc::MemoryBlock data("entity", 6);
    p->AddEntity(info, data);
    p->Step();
    check_AddEntity(client0);
    check_AddEntity(client1);
  }

  void check_AddEntity(test::MockClient* client)
  {
    TS_ASSERT_EQUALS(1, client->steps.size());
  }

  void test_AsyncSendingWhenClientDisconnected()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "sippul", 1, client1, false);
    int clientIndex2 = AddClient(p, "ivn", 2, client2, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->OnClientReady(clientIndex2);

    p->Step();
    p->OnFinishStep(clientIndex0, 0, 0xF00D); // client0 sent correct crc for step 0
    p->OnFinishStep(clientIndex1, 0, 0xF00D); // client1 sent correct crc for step 0
    p->OnFinishStep(clientIndex2, 0, 0xF00D); // client2 sent correct crc for step 0

    p->Step();
    p->Step();

    p->OnFinishStep(clientIndex0, 1, 0xF00D); // client0 sent correct crc for step 1
    p->OnFinishStep(clientIndex1, 1, 0xF00A); // client1 sent wrong crc for step 1

    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    TS_ASSERT_EQUALS(-1, client1->asyncStep);

    client2->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS(1, client0->asyncStep);
    TS_ASSERT_EQUALS(1, client1->asyncStep);
  }


  void test_AsyncWithoutTrustedClient()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "sippul", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    p->Step();

    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());

    p->Step();

    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());

    p->OnFinishStep(clientIndex0, 0, 0xF00D); // client0 sent crc

    p->Step();  // we step

    TS_ASSERT_EQUALS(2, client0->steps.size());  // but still we have no enough confirmed steps, so no commands will be sent
    TS_ASSERT_EQUALS(2, client1->steps.size());
    p->OnFinishStep(clientIndex1, 0, 0xF00D);

    p->Step();  // we step

    TS_ASSERT_EQUALS(3, client0->steps.size());  // now we have confirmed step, so commands were sent
    TS_ASSERT_EQUALS(3, client1->steps.size());

    // step 1 confirmed
    p->OnFinishStep(clientIndex0, 1, 0xF00D);
    p->OnFinishStep(clientIndex1, 1, 0xF00D);

    // now we have async on step 2
    p->OnFinishStep(clientIndex0, 2, 0xF00D);
    p->OnFinishStep(clientIndex1, 2, 0xF00E);
    TS_ASSERT_EQUALS(2, client0->asyncStep);
    TS_ASSERT_EQUALS(2, client0->async.size());
    TS_ASSERT_EQUALS(0, client0->async[0].clientId);
    TS_ASSERT_EQUALS(0xF00D, client0->async[0].crc);
    TS_ASSERT_EQUALS(1, client0->async[1].clientId);
    TS_ASSERT_EQUALS(0xF00E, client0->async[1].crc);

    // we step but no steps will be send becaus of async and no trusted client
    for (int i=0;i<10;++i)
    {
      p->Step();  
      TS_ASSERT_EQUALS(3, client0->steps.size());  // we have async and no trusted client, so just we are sending information about async and no steps will be sent
      TS_ASSERT_EQUALS(3, client1->steps.size());
    }
  }

  void test_ForwardAsyncWithoutTrustedClient()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(5, 100, 0, 0, 2000, 0, FillClients(0, 1, 2), link);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "sippul", 1, client1, false);
    int clientIndex2 = AddClient(p, "ivn", 2, client2, false);
    clientIndex0;
    clientIndex1;
    clientIndex2;

    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->OnClientReady(clientIndex2);

    p->Step();

    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());
    TS_ASSERT_EQUALS(1, client2->steps.size());

    p->Step();

    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, client2->steps.size());

    p->OnFinishStep(clientIndex0, 0, 0xF00D); // client0 sent crc for step 0

    p->Step();  // we step
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, client2->steps.size());

    // Clients 0 and 1 are in the async party from now
    p->OnFinishStep(clientIndex1, 0, 0xFEEE); // client1 asynced in step 0

    p->OnFinishStep(clientIndex0, 1, 0xF00A); // client0 sent crc for step 1
    p->OnFinishStep(clientIndex1, 1, 0xF00B); // client1 still asynced in step 1

    p->Step(); // we step

    // no steps will be sent because we are in async recovery mode
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, client2->steps.size());

    // Finaly the third client get in and we are able to determine which are ok and which go out
    p->OnFinishStep(clientIndex2, 0, 0xF00D); // client2 sent crc for step 0

    // Client 0 and 2 have reported same crc and they are the majority (2 of 3), so they resume playing
    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    TS_ASSERT_EQUALS(0, client0->async.size());
    TS_ASSERT_EQUALS(-1, client2->asyncStep);
    TS_ASSERT_EQUALS(0, client2->async.size());

    // Client 1 got out by async
    TS_ASSERT_EQUALS(0, client1->asyncStep);
    TS_ASSERT_EQUALS(3, client1->async.size());
    TS_ASSERT_EQUALS(0, client1->async[0].clientId);
    TS_ASSERT_EQUALS(0xF00D, client1->async[0].crc);
    TS_ASSERT_EQUALS(1, client1->async[1].clientId);
    TS_ASSERT_EQUALS(0xFEEE, client1->async[1].crc);
    TS_ASSERT_EQUALS(2, client1->async[2].clientId);
    TS_ASSERT_EQUALS(0xF00D, client1->async[2].crc);
    // He is reported as cheater
    TS_ASSERT_EQUALS(1, link->cheaters.size());
    TS_ASSERT_EQUALS(1, link->cheaters[0]);

    // We still do not step, because we have async in the second step too, but client2 didn't reported that stap yet
    p->Step();
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, client2->steps.size());

    p->OnFinishStep(clientIndex2, 1, 0xF00A); // client1 still asynced in step 1
    p->Step();
    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(4, client2->steps.size());
  }

  void test_ClientReadyForOneClient()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    clientIndex0;

    // no commands for not started clients
    for (int i=0;i<10;++i)
    {
      p->Step(); 
      TS_ASSERT_EQUALS(0, client0->steps.size()); 
    }

    // gap restriction is disabled while not not all clients are started
    {
      const int commandSize0 = 12;
      char commandData0[commandSize0];
      test::FormatCommand(&commandData0, 0, "cmd0");
      rpc::MemoryBlock command0(commandData0, commandSize0);
      p->SendCommand(clientIndex0, command0, true);

      p->Step();
      TS_ASSERT_EQUALS(1, client0->steps.size());
      TS_ASSERT_EQUALS(1, client0->steps[0].commands.size());

      TS_ASSERT_EQUALS(commandSize0, client0->steps[0].commands[0].size);
      TS_ASSERT_SAME_DATA(commandData0, client0->steps[0].commands[0].memory, commandSize0);
      for (int i=0;i<10;++i)
      {
        p->Step();
        TS_ASSERT_EQUALS(1, client0->steps.size());
      }
    }

    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(1, client0->simulationStartStep);

    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(0, client0->steps[1].commands.size());
                           
    p->Step();
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(0, client0->steps[2].commands.size());

    p->Step();
    TS_ASSERT_EQUALS(3, client0->steps.size()); // because of gap restriction now is active

    p->OnFinishStep(clientIndex0, 1, 0xF00D); 

    p->Step();
    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(0, client0->steps[3].commands.size());
  }

  void test_ClientReadyCommandsNotSent()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(1000);
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);

    for (int i=0;i<10;++i)
    {
      const int commandSize0 = 12;
      char commandData0[commandSize0];
      test::FormatCommand(&commandData0, 0, "cmd0");
      rpc::MemoryBlock command0(commandData0, commandSize0);
      {
        p->SendCommand(clientIndex0, command0, true);
      }
      p->Step();
      // check if commands were sent to clients 
      TS_ASSERT_EQUALS(i+1, client0->steps.size());
      TS_ASSERT_EQUALS(1, client0->steps[i].commands.size());
      TS_ASSERT_EQUALS(i, client0->steps[i].step);
    }

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 0, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    // send command before ready
    {
      p->SendCommand(clientIndex0, command0, true);
    }
    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(11, client0->simulationStartStep );

    TS_ASSERT_EQUALS(11, client0->steps.size());
    TS_ASSERT_EQUALS(1, client0->steps[10].commands.size());
    TS_ASSERT_SAME_DATA(commandData0, client0->steps[10].commands[0].memory, commandSize0);

    const int commandSize1 = 12;
    char commandData1[commandSize1];
    test::FormatCommand(&commandData1, 0, "cmd1");
    rpc::MemoryBlock command1(commandData1, commandSize1);

    // send command after OnClientReady called
    {
      p->SendCommand(clientIndex0, command1, true);
    }
    p->Step();
    TS_ASSERT_EQUALS(12, client0->steps.size());

    TS_ASSERT_EQUALS(1, client0->steps[11].commands.size());
    TS_ASSERT_SAME_DATA(commandData1, client0->steps[11].commands[0].memory, commandSize1);


    StrongMT<test::MockClient> client1 = new test::MockClient();
    /*int clientIndex1 = */AddClient(p, "ivn", 1, client1, false);
    p->Step();
    TS_ASSERT_EQUALS(0, client1->steps.size()); // should be 13 if reconnect is supported
    //p->OnClientReady(clientIndex1);
  }

  void test_StepsIncrementingWhileSessionNotStarted()
  {
    StrongMT<test::MockClient> server = new test::MockClient();
    StrongMT<Peered::CommandsScheduler> p = Create(2);

    int trustedClientIndex = 0xFFFFFFFF;
    p->AddTrustedClient(trustedClientIndex, server);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    clientIndex0;

    for (int i=0;i<100;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(0, client0->steps.size());
    }
    {
      const int commandSize0 = 12;
      char commandData0[commandSize0];
      test::FormatCommand(&commandData0, 0, "cmd0");
      rpc::MemoryBlock command0(commandData0, commandSize0);
      p->SendCommand(clientIndex0, command0, true);

      p->Step();
      TS_ASSERT_EQUALS(1, client0->steps.size());
      TS_ASSERT_EQUALS(1, client0->steps[0].commands.size());
      TS_ASSERT_EQUALS(0, client0->steps[0].step);
    }
    p->OnClientReady(clientIndex0);
    {
      p->Step();
      TS_ASSERT_EQUALS(2, client0->steps.size());
      TS_ASSERT_EQUALS(1, client0->steps[1].step);
    }
  }
               
  void test_StopStepCounterOnLags()
  {
    StrongMT<test::MockClient> server = new test::MockClient();
    StrongMT<Peered::CommandsScheduler> p = Create(2);

    int trustedClientIndex = 0xFFFFFFFF;
    p->AddTrustedClient(trustedClientIndex, server);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    p->Step();

    p->OnFinishStep(clientIndex0, 0, 0xF00D); 
    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.back().step);
    TS_ASSERT_EQUALS(1, client1->steps.back().step);
    
    // "lagged" step shouldn't count it
    p->OnFinishStep(clientIndex0, 1, 0xF00D); 
    for(int i = 0; i < 10; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(1, client0->steps.back().step);
      TS_ASSERT_EQUALS(1, client1->steps.back().step);
    }

    p->OnFinishStep(clientIndex1, 0, 0xF00D); 
    p->OnFinishStep(clientIndex1, 1, 0xF00D); 
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.back().step);
    TS_ASSERT_EQUALS(2, client1->steps.back().step);
  }

  void test_GapInfo()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    int clientIndex1 = AddClient(p, "sippul", 1, client1, false);

    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    p->Step();

    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());

    {
      test::MockClient::StepData& data = client0->steps[0];
      TS_ASSERT_EQUALS(2, data.gaps.size());
      TS_ASSERT_EQUALS(0, data.gaps[0].clientId);
      TS_ASSERT_EQUALS(1, data.gaps[1].clientId);
      TS_ASSERT_EQUALS(1, data.gaps[0].confirmedStepsGap);
      TS_ASSERT_EQUALS(1, data.gaps[1].confirmedStepsGap);
    }

    {
      test::MockClient::StepData& data = client1->steps[0];
      TS_ASSERT_EQUALS(2, data.gaps.size());
      TS_ASSERT_EQUALS(0, data.gaps[0].clientId);
      TS_ASSERT_EQUALS(1, data.gaps[1].clientId);
      TS_ASSERT_EQUALS(1, data.gaps[0].confirmedStepsGap);
      TS_ASSERT_EQUALS(1, data.gaps[1].confirmedStepsGap);
    }

    p->OnFinishStep(clientIndex0, 0, 0xF00D); 
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());

    {
      test::MockClient::StepData& data = client0->steps[1];
      TS_ASSERT_EQUALS(2, data.gaps.size());
      TS_ASSERT_EQUALS(0, data.gaps[0].clientId);
      TS_ASSERT_EQUALS(1, data.gaps[1].clientId);
      TS_ASSERT_EQUALS(1, data.gaps[0].confirmedStepsGap);
      TS_ASSERT_EQUALS(2, data.gaps[1].confirmedStepsGap);
    }

    {
      test::MockClient::StepData& data = client1->steps[1];
      TS_ASSERT_EQUALS(2, data.gaps.size());
      TS_ASSERT_EQUALS(0, data.gaps[0].clientId);
      TS_ASSERT_EQUALS(1, data.gaps[1].clientId);
      TS_ASSERT_EQUALS(1, data.gaps[0].confirmedStepsGap);
      TS_ASSERT_EQUALS(2, data.gaps[1].confirmedStepsGap);
    }

  }

  void test_CheatingWithClientIndex()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    clientIndex0;

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 0, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);

    {
      p->SendCommand(clientIndex0, command0, true);
    }

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size()); 
    TS_ASSERT_EQUALS(1, client0->steps[0].commands.size()); 

    {
      p->SendCommand(999, command0, true);
    }

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size()); 
    {
      test::AssertDisabler d;
      p->OnClientReady(999);
    }

    p->OnClientReady(clientIndex0);
    {
      p->SendCommand(999, command0, true);
    }
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size()); 
    TS_ASSERT_EQUALS(0, client0->steps[1].commands.size()); 

    {
      test::AssertDisabler d;
      p->OnFinishStep(9999, 1, 0xF00D); 
    }
  }

  void test_CheatingDoubleOnReady()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, true);
    client0->simulationStartStep = uint(-1);
    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(uint(-1), client0->simulationStartStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, client0->disconnectReason);
  }

  void test_ClientsCount()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2);

    TS_ASSERT_EQUALS(0, p->GetNumberOfClients());
    StrongMT<test::MockClient> client0 = new test::MockClient();
    AddClient(p, "redjack", 0, client0, false);
    TS_ASSERT_EQUALS(1, p->GetNumberOfClients());

    StrongMT<test::MockClient> client1 = new test::MockClient();
    AddClient(p, "ivn", 0, client1, true);
    TS_ASSERT_EQUALS(2, p->GetNumberOfClients());
  }

  void test_NextStepProblem()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 0, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);

    // first steps proceeded without second client
    const int firstSteps = 5;
    for (int i=0;i<firstSteps;++i)
    {
      p->SendCommand(clientIndex0, command0, true);

      p->Step();
      TS_ASSERT_EQUALS(i+1, client0->steps.size());
    }

    // second client connected
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex1 = AddClient(p, "redjack1", 1, client1, false);
    TS_ASSERT_EQUALS(0, client1->steps.size()); // no steps recieved

    const int commandSize1 = 12;
    char commandData1[commandSize1];
    test::FormatCommand(&commandData1, 1, "cmd1");
    rpc::MemoryBlock command1(commandData1, commandSize1);

    for (int i=0;i<firstSteps;++i)
    {
      p->SendCommand(clientIndex0, command0, true);
      p->SendCommand(clientIndex1, command1, true);

      p->Step();
      TS_ASSERT_EQUALS(firstSteps+i+1, client0->steps.size());
      TS_ASSERT_EQUALS(firstSteps+i, client0->steps[firstSteps+i].step);
      TS_ASSERT_EQUALS(i+1, client1->steps.size());
      TS_ASSERT_EQUALS(firstSteps+i, client1->steps[i].step); 
    }
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    TS_ASSERT_EQUALS(2*firstSteps, client0->simulationStartStep);
    TS_ASSERT_EQUALS(2*firstSteps, client1->simulationStartStep);
    p->Step();
    p->OnFinishStep(clientIndex0, 2*firstSteps, 0xF00D); 
    p->OnFinishStep(clientIndex1, 2*firstSteps, 0xF00D); 
  }

  void test_CallOnFinishStepBeforeOnStart()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, false);

    const int commandSize = 11;
    char commandData[commandSize];
    test::FormatCommand(&commandData, 0, "cmd");
    rpc::MemoryBlock command(commandData, commandSize);

    const int firstSteps = 5;
    for (int i=0;i<firstSteps;++i)
    {
      test::AssertDisabler d;

      p->SendCommand(clientIndex0, command, true);

      p->Step();
      TS_ASSERT_EQUALS(i+1, client0->steps.size());

      p->OnFinishStep(clientIndex0, 0, 0xF00D); 
      // here we should punish client for protocol violation
    }
    for (int i=0;i<5;++i)
    {
      p->SendCommand(clientIndex0, command, true);

      p->Step();
      TS_ASSERT_EQUALS(firstSteps+i+1, client0->steps.size());
    }
    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(10, client0->simulationStartStep);
    p->Step();
    p->OnFinishStep(clientIndex0, 10, 0xF00D); 
  }

  void test_CheatingStepWrongConfirmation()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, true);

    for (int i=0;i<20;++i)
    {
      p->Step();
    }

    p->OnFinishStep(clientIndex0, 0, 0xF00D); 
    {
      test::AssertDisabler d;
      p->OnFinishStep(clientIndex0, 0, 0xF00D); 
    }
  }

  void test_CheatingNullClient()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(20);

    int clientIndex0 = AddClient(p, "redjack", 0, 0, false);
    TS_ASSERT_EQUALS(-1, clientIndex0);
  }

  void test_CheatingWrongTimescale()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(20, 200, 0, 0, 2000, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 
                                                    4096, true, 0, 0, 0, 64000, true, 300, 128, 64000, true);
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "redjack", 0, client0, true);

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size()); 
    p->SetTimeScale(clientIndex0, 0.f);
    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size()); 

    p->SetTimeScale(clientIndex0, 2.f);
    TS_ASSERT_EQUALS(2.f, client0->timeScale);

    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size()); 

    p->SetTimeScale(clientIndex0, -100.f);
    TS_ASSERT_EQUALS(0.f, client0->timeScale);
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size()); 
  }

  void test_TimeScaleDisabled()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, true);
    int clientIndex1 = AddClient(p, "test1", 1, client1, true);
                       AddClient(p, "test2", 2, client2, true);

    // Test for connected client
    TS_ASSERT_EQUALS(100, p->Step());
    p->SetTimeScale(clientIndex0, 0.5);
    TS_ASSERT_EQUALS(1.0f, client2->timeScale);
    TS_ASSERT_EQUALS(100, p->Step());
    TS_ASSERT_EQUALS(1, link->cheaters.size());
    TS_ASSERT_EQUALS(0, link->cheaters[0]);

    // Test for disconnected client
    client1->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(100, p->Step());
    p->SetTimeScale(clientIndex1, 0.5);
    TS_ASSERT_EQUALS(1.0f, client2->timeScale);
    TS_ASSERT_EQUALS(100, p->Step());
    TS_ASSERT_EQUALS(2, link->cheaters.size());
    TS_ASSERT_EQUALS(1, link->cheaters[1]);

    // Test for unknown client (wrong index)
    p->SetTimeScale(-1, 0.5);
    TS_ASSERT_EQUALS(1.0f, client2->timeScale);
    TS_ASSERT_EQUALS(100, p->Step());
    TS_ASSERT_EQUALS(2, link->cheaters.size());
  }

  void test_CheatingWrongClientId()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);

    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);

    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    p->OnClientReady(clientIndex1);

    p->Step();
    TS_ASSERT_EQUALS(0, client0->simulationStartStep);
  }

  void test_ConnectionAfterAllClientsReadyButNoStepsWereMade()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(100);

    Crc32Checksum s0;
    {
      rpc::MemoryBlock block("EntityData0", 11);
      s0.Add((const byte*)block.memory, block.size);
      Peered::BriefEntityInfo info = {0, s0.Get() };
      p->AddEntity(info, block);
    }
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    p->OnClientReady(clientIndex0);

    // commented because reconnect is delayed
    /*
    Crc32Checksum s1;
    {
      rpc::MemoryBlock block("EntityData1", 11);
      s1.Add((const byte*)block.memory, block.size);
      Peered::BriefEntityInfo info = {1, s1.Get() };
      p->AddEntity(info, block);
    }
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);
    TS_ASSERT_EQUALS(1, client1->patches.size());
    TS_ASSERT_EQUALS(0, client1->patches[0].step);
    {
      test::MockClient::WorldPatchData& data = client1->patches[0];
      TS_ASSERT_EQUALS(Crc32Checksum().Add(s0.Get()).Get(), data.crc);
      TS_ASSERT_EQUALS(1, data.entitiesIds.size());
      TS_ASSERT_EQUALS(1, data.entitiesData.size());
      {
        TS_ASSERT_EQUALS(0, data.entitiesIds[0].id);
        TS_ASSERT_EQUALS(s0.Get(), data.entitiesIds[0].crc);
        TS_ASSERT_EQUALS(11, data.entitiesData[0].size);
        TS_ASSERT_SAME_DATA("EntityData0", data.entitiesData[0].memory, 11);
      }
    }
    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    {
      test::MockClient::StepData& data = client0->steps[0];
      TS_ASSERT_EQUALS(1, data.addedEntities.size());
      TS_ASSERT_EQUALS(1, data.addedEntitiesData.size());
      {
        TS_ASSERT_EQUALS(1, data.addedEntities[0].id);
        TS_ASSERT_EQUALS(s1.Get(), data.addedEntities[0].crc);
        TS_ASSERT_EQUALS(11, data.addedEntitiesData[0].size);
        TS_ASSERT_SAME_DATA("EntityData1", data.addedEntitiesData[0].memory, 11);
      }
    }
    TS_ASSERT_EQUALS(1, client1->steps.size());
    {
      test::MockClient::StepData& data = client1->steps[0];
      TS_ASSERT_EQUALS(1, data.addedEntities.size());
      TS_ASSERT_EQUALS(1, data.addedEntitiesData.size());
      {
        TS_ASSERT_EQUALS(1, data.addedEntities[0].id);
        TS_ASSERT_EQUALS(s1.Get(), data.addedEntities[0].crc);
        TS_ASSERT_EQUALS(11, data.addedEntitiesData[0].size);
        TS_ASSERT_SAME_DATA("EntityData1", data.addedEntitiesData[0].memory, 11);
      }
    }*/
  }

  void test_ConnectionAfterAllClientsReadyButWithSteps()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(100);

    // adding entity for client0
    Crc32Checksum s0;
    {
      rpc::MemoryBlock block("EntityData0", 11);
      s0.Add((const byte*)block.memory, block.size);
      Peered::BriefEntityInfo info = {0, s0.Get() };
      p->AddEntity(info, block);
    }
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    p->OnClientReady(clientIndex0);

    // step 10 times
    for (int i=0;i<10;++i)
    {
      p->Step();
    }

    // commented because reconnect is not supported for now
    /*

    // adding entity for client1
    Crc32Checksum s1;
    {
      rpc::MemoryBlock block("EntityData1", 11);
      s1.Add((const byte*)block.memory, block.size);
      Peered::BriefEntityInfo info = {1, s1.Get() };
      p->AddEntity(info, block);
    }
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);
    TS_ASSERT_EQUALS(1, client1->patches.size());
    TS_ASSERT_EQUALS(0, client1->patches[0].step);
    {
      test::MockClient::WorldPatchData& data = client1->patches[0];
      TS_ASSERT_EQUALS(Crc32Checksum().Add(s0.Get()).Get(), data.crc);

      TS_ASSERT_EQUALS(1, data.entitiesIds.size()); // only 1 entity because step 0 world is initial
      TS_ASSERT_EQUALS(1, data.entitiesData.size());
      {
        TS_ASSERT_EQUALS(0, data.entitiesIds[0].id);
        TS_ASSERT_EQUALS(s0.Get(), data.entitiesIds[0].crc);
        TS_ASSERT_EQUALS(11, data.entitiesData[0].size);
        TS_ASSERT_SAME_DATA("EntityData0", data.entitiesData[0].memory, 11);
      }
    }
    p->Step();
    TS_ASSERT_EQUALS(11, client1->steps.size());
    for (int i=0;i<10;++i)
    {
      test::MockClient::StepData& data = client1->steps[i];
      TS_ASSERT_EQUALS(0, data.addedEntities.size());
    }
    {
      test::MockClient::StepData& data = client1->steps[10];
      TS_ASSERT_EQUALS(1, data.addedEntities.size());
      TS_ASSERT_EQUALS(1, data.addedEntitiesData.size());
      TS_ASSERT_EQUALS(11, data.addedEntitiesData[0].size);
      TS_ASSERT_SAME_DATA("EntityData1", data.addedEntitiesData[0].memory, 11);
    }*/
  }

  void test_SkippingAllCommandsRecievedBeforeSessionStart()
  {
  }

  void test_CommandsHandlerSimple()
  {
    StrongMT<test::MockCommandsHandler> handler = new test::MockCommandsHandler;
    StrongMT<Peered::CommandsScheduler> p = Create(100, 100, handler);

    TS_ASSERT_EQUALS(true, handler->onCreateCalled);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    AddClient(p, "test1", 0, client0, false);
    TS_ASSERT_EQUALS(1, handler->addedClients.size());
    TS_ASSERT_EQUALS(0, handler->removedClients.size());
    client0->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS(1, handler->removedClients.size());
  }

  void test_CommandsHandlerFastReconnect()
  {
    StrongMT<test::MockCommandsHandler> handler = new test::MockCommandsHandler;
    Peered::SchedulerData data;
    data.sessionSettings.fastReconnectReserveSteps = 500;
    SchedulerObjects objects;
    objects.handler = handler;
    StrongMT<Peered::CommandsScheduler> p = Create( data, objects, 0 );

    TS_ASSERT_EQUALS(true, handler->onCreateCalled);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int client0Idx = AddClient(p, "test1", 0, client0, false);
    int client1Idx = AddClient(p, "test2", 1, client1, false);
    TS_ASSERT_EQUALS(2, handler->addedClients.size());
    TS_ASSERT_EQUALS(0, handler->removedClients.size());

    p->OnClientReady(client0Idx);
    p->OnClientReady(client1Idx);

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());

    // Test a detected disconnect with fast reconnect
    client0->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS(2, handler->addedClients.size());
    TS_ASSERT_EQUALS(1, handler->removedClients.size());
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());

    client0->status = rpc::Connected;
    p->AddClientFast(0, client0Idx,  client0, 1);
    TS_ASSERT_EQUALS(3, handler->addedClients.size());
    TS_ASSERT_EQUALS(1, handler->removedClients.size());
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());

    // Test an undetected disconnect with fast reconnect
    p->AddClientFast(1, client1Idx,  client1, 2);
    p->Step();
    TS_ASSERT_EQUALS(3, handler->addedClients.size());
    TS_ASSERT_EQUALS(1, handler->removedClients.size());
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
  }

  void test_ConnectionBeforeAnyStepsButAfterFirstClientReady()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(100);

    // adding entity for client0
    Crc32Checksum s0;
    {
      rpc::MemoryBlock block("EntityData0", 11);
      s0.Add((const byte*)block.memory, block.size);
      Peered::BriefEntityInfo info = {0, s0.Get() };
      p->AddEntity(info, block);
    }
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    p->OnClientReady(clientIndex0);

    // commented because reconnect is not supported for now
    /*
    // adding entity for client1
    Crc32Checksum s1;
    {
      rpc::MemoryBlock block("EntityData1", 11);
      s1.Add((const byte*)block.memory, block.size);
      Peered::BriefEntityInfo info = {1, s1.Get() };
      p->AddEntity(info, block);
    }
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex1 = AddClient(p, "test2", 1, client1, false);
    p->OnClientReady(clientIndex1);
    p->Step();

    TS_ASSERT_EQUALS(1, client1->patches.size());
    TS_ASSERT_EQUALS(0, client1->patches[0].step);
    {
      test::MockClient::WorldPatchData& data = client1->patches[0];
      TS_ASSERT_EQUALS(Crc32Checksum().Add(s0.Get()).Get(), data.crc);

      TS_ASSERT_EQUALS(1, data.entitiesIds.size()); // only 1 entity because step 0 world is initial
      TS_ASSERT_EQUALS(1, data.entitiesData.size());
      {
        TS_ASSERT_EQUALS(0, data.entitiesIds[0].id);
        TS_ASSERT_EQUALS(s0.Get(), data.entitiesIds[0].crc);
        TS_ASSERT_EQUALS(11, data.entitiesData[0].size);
        TS_ASSERT_SAME_DATA("EntityData0", data.entitiesData[0].memory, 11);
      }
    }
    {
      test::MockClient::StepData& data = client1->steps[0];
      TS_ASSERT_EQUALS(1, data.addedEntities.size());
      TS_ASSERT_EQUALS(1, data.addedEntitiesData.size());
      TS_ASSERT_EQUALS(11, data.addedEntitiesData[0].size);
      TS_ASSERT_SAME_DATA("EntityData1", data.addedEntitiesData[0].memory, 11);
    }
    */
  }

  //void test_OneClientPatching()
  //{
  //  StrongMT<Peered::CommandsScheduler> p = Create(100);

  //  // adding entity for client0
  //  Crc32Checksum s0;
  //  {
  //    rpc::MemoryBlock block("EntityData0", 11);
  //    s0.Add((const byte*)block.memory, block.size);
  //    Peered::BriefEntityInfo info = {0, s0.Get() };
  //    p->AddEntity(info, block);
  //  }
  //  StrongMT<test::MockClient> client0 = new test::MockClient();

  //  int clientIndex0 = AddClient(p, "test1", 0, client0, false);
  //  p->OnClientReady(clientIndex0);

  //  p->Step();

  //  TS_ASSERT_EQUALS(1, client0->patches.size());
  //  TS_ASSERT_EQUALS(0, client0->patches[0].step);
  //  {
  //    test::MockClient::WorldPatchData& data = client0->patches[0];
  //    TS_ASSERT_EQUALS(Crc32Checksum().Add(s0.Get()).Get(), data.crc);

  //    TS_ASSERT_EQUALS(1, data.entitiesIds.size()); 
  //    TS_ASSERT_EQUALS(1, data.entitiesData.size());
  //    {
  //      TS_ASSERT_EQUALS(0, data.entitiesIds[0].id);
  //      TS_ASSERT_EQUALS(s0.Get(), data.entitiesIds[0].crc);
  //      TS_ASSERT_EQUALS(11, data.entitiesData[0].size);
  //      TS_ASSERT_SAME_DATA("EntityData0", data.entitiesData[0].memory, 11);
  //    }
  //  }
  //}

  void test_JoinAfterSessionStarted()
  {
    StrongMT<test::MockClient> server = new test::MockClient();
    StrongMT<Peered::CommandsScheduler> p = Create(2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    /*int clientIndex0 = */AddClient(p, "test1", 0, client0, true);
    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size()); 

    /*int clientIndex1 = */AddClient(p, "test2", 1, client1, false);

    // here we should send last world snapshot that we have
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(0, client1->steps.size());  // we should recieve 1 step (only after last world snapshot sent)
  }

  void test_DumpLogs()
  {
    StrongMT<test::MockCommandsLog> log = new test::MockCommandsLog;
    const int syncStepsCount = 10;
    int step = 0;

    StrongMT<Peered::CommandsScheduler> p = Create(100, 100, 0, log, syncStepsCount, 0, FillClients(0));
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);
    TS_ASSERT_EQUALS(0, client0->steps.size());

    const int commandSize = 11;
    char commandData[commandSize];
    test::FormatCommand(&commandData, 0, "cmd");
    rpc::MemoryBlock command(commandData, commandSize);

    const int loadStepsCount = 20;
    // processing loading process
    for (int i=0;i<loadStepsCount;++i)
    {
      p->SendCommand(clientIndex0, command, true);
      p->Step();
      ++step;
      TS_ASSERT_EQUALS(step, client0->steps.size()); 
    }
    p->OnClientReady(clientIndex0);

    // make syncStepsCount steps
    {
      for (int i=0;i<syncStepsCount;++i)
      {
        SendNumberedCommand(p, clientIndex0, 0, "SyncCmd", i);
        p->Step();
        ++step;
        TS_ASSERT_EQUALS(step, client0->steps.size()); 
        TS_ASSERT_EQUALS(0, log->steps.size())
        p->OnFinishStep(clientIndex0, step-1, 0xF00D); 
      }
      // As a side effect of snapshot reservation we now dump N commands after N+1 confirmed steps
      // therefore we push here next command just to get the dump
      SendNumberedCommand(p, clientIndex0, 0, "NewCmd", 0);
      p->Step();
      ++step;
      TS_ASSERT_EQUALS(step, client0->steps.size()); 
      p->OnFinishStep(clientIndex0, step-1, 0xF00D); 
      // And now another side effect, due to updating snapshots in session step and not on finish step
      SendNumberedCommand(p, clientIndex0, 0, "NewCmd", 1);
      p->Step();
      ++step;
      TS_ASSERT_EQUALS(step, client0->steps.size()); 
      p->OnFinishStep(clientIndex0, step-1, 0xF00D); 
    }
    // check that last syncStepsCount were dumped
    TS_ASSERT_EQUALS(syncStepsCount, log->steps.size())
    for (int i=0;i<log->steps.size();++i)
    {
      TS_ASSERT_EQUALS(loadStepsCount+i, log->steps[i].step);

      char buffer[16];
      int length = sprintf_s(buffer, "SyncCmd%d", i);

      char commandData[16+8];
      test::FormatCommand(&commandData, 0, buffer);

      rpc::CachedMemoryBlock& block = log->steps[i].commands[0];
      TS_ASSERT_SAME_DATA(block.memory, commandData, length+8);
    }

    // make another syncStepsCount steps
    {
      // Start from 2, because we already sent commands 0 and 1
      for (int i=2;i<syncStepsCount;++i)
      {
        SendNumberedCommand(p, clientIndex0, 0, "NewCmd", i);
        p->Step();
        ++step;
        TS_ASSERT_EQUALS(step, client0->steps.size()); 
        TS_ASSERT_EQUALS(syncStepsCount, log->steps.size())
        p->OnFinishStep(clientIndex0, step-1, 0xF00D); 
      }
      // "Side effects" same as was in the first portion above
      SendNumberedCommand(p, clientIndex0, 0, "ExtraCmd", 0);
      p->Step();
      ++step;
      TS_ASSERT_EQUALS(step, client0->steps.size()); 
      p->OnFinishStep(clientIndex0, step-1, 0xF00D); 
      SendNumberedCommand(p, clientIndex0, 0, "ExtraCmd", 1);
      p->Step();
      ++step;
      TS_ASSERT_EQUALS(step, client0->steps.size()); 
      p->OnFinishStep(clientIndex0, step-1, 0xF00D); 
    }

    // check that new syncStepsCount commands were dumped
    TS_ASSERT_EQUALS(syncStepsCount+syncStepsCount, log->steps.size())
    for (int i=syncStepsCount;i<log->steps.size();++i)
    {
      TS_ASSERT_EQUALS(loadStepsCount+i, log->steps[i].step);

      char buffer[16];
      int length = sprintf_s(buffer, "NewCmd%d", i-syncStepsCount);

      char commandData[16+8];
      test::FormatCommand(&commandData, 0, buffer);

      rpc::CachedMemoryBlock& block = log->steps[i].commands[0];
      TS_ASSERT_SAME_DATA(block.memory, commandData, length+8);
    }

    // Now lets finish the game and check, that all 2 extra steps with extra commands are dumped
    p->OnGameFinish(clientIndex0, step-1, GetFinishData(lobby::ETeam::Team1));
    p->Step();
    TS_ASSERT_EQUALS(syncStepsCount+syncStepsCount+2, log->steps.size())
    for (int i=syncStepsCount*2; i<log->steps.size();++i)
    {
      TS_ASSERT_EQUALS(loadStepsCount+i, log->steps[i].step);

      char buffer[16];
      int length = sprintf_s(buffer, "ExtraCmd%d", i-syncStepsCount*2);

      char commandData[16+8];
      test::FormatCommand(&commandData, 0, buffer);

      rpc::CachedMemoryBlock& block = log->steps[i].commands[0];
      TS_ASSERT_SAME_DATA(block.memory, commandData, length+8);
    }

    // Lets kill the session and check, that no additional steps are dumped
    p = 0;
    TS_ASSERT_EQUALS(syncStepsCount+syncStepsCount+2, log->steps.size())
  }

  void test_DumpLogsAfterFinish()
  {
    StrongMT<test::MockCommandsLog> log = new test::MockCommandsLog;
    const int syncStepsCount = 10;

    StrongMT<Peered::CommandsScheduler> p = Create(100, 100, 0, log, syncStepsCount, 0, FillClients(0));
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, false);

    const int commandSize = 11;
    char commandData[commandSize];
    test::FormatCommand(&commandData, 0, "cmd");
    rpc::MemoryBlock command(commandData, commandSize);

    const int loadStepsCount = 20;
    // processing loading process
    for (int i=0;i<loadStepsCount;++i)
    {
      p->SendCommand(clientIndex0, command, true);
      p->Step();
      TS_ASSERT_EQUALS(i+1, client0->steps.size()); 
    }
    p->OnClientReady(clientIndex0);

    // make syncStepsCount steps
    {
      for (int i=0;i<syncStepsCount-2;++i)
      {
        SendNumberedCommand(p, clientIndex0, 0, "SyncCmd", i);
        p->Step();
        TS_ASSERT_EQUALS(loadStepsCount+i+1, client0->steps.size()); 
        TS_ASSERT_EQUALS(0, log->steps.size())
        p->OnFinishStep(clientIndex0, loadStepsCount+i, 0xF00D); 
      }
    }
    client0->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    // check that last syncStepsCount were dumped
    TS_ASSERT_EQUALS(syncStepsCount-2, log->steps.size())
    for (int i=0;i<log->steps.size();++i)
    {
      TS_ASSERT_EQUALS(loadStepsCount+i, log->steps[i].step);

      char buffer[16];
      int length = sprintf_s(buffer, "SyncCmd%d", i);

      char commandData[16+8];
      test::FormatCommand(&commandData, 0, buffer);

      rpc::CachedMemoryBlock& block = log->steps[i].commands[0];
      TS_ASSERT_SAME_DATA(block.memory, commandData, length+8);
    }
  }

  void test_SessionId()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2, 100, 0, 0, 1000, 666);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    AddClient(p, "redjack", 0, client0, false);
    AddClient(p, "sippul", 1, client1, false);

    TS_ASSERT_EQUALS(666, client0->serverId);
    TS_ASSERT_EQUALS(666, client1->serverId);
  }

  void test_ClientDisconnectionBeforeStart()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();

    int clientIndex0;
    StrongMT<test::MockClient> client0 = new test::MockClient();
    clientIndex0 = AddClient(p, "redjack", 0, client0, false);
    client0->status = rpc::Disconnected;
    p->OnClientReady(clientIndex0);
  }

  void test_ClientConfirmationAfterDisconnect()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1));

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);

    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    p->Step();
    p->Step();
    p->OnFinishStep(clientIndex0, 0, 0xF00D); 
    p->OnFinishStep(clientIndex0, 1, 0xF00D); 

    client1->status = rpc::Disconnected;
    p->Step();
    p->OnFinishStep(clientIndex1, 0, 0xF00D); 
  }

  void test_ClientConnectionTimeout()
  {
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    const int connectionTimeout = 200;
    Peered::SchedulerData data;
    SchedulerObjects objects;
    data.sessionSettings.connectionTimeout = connectionTimeout;
    objects.statisticsWrapper = statisticsWrapper;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(0, 1));

    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);

    for (int i=0;i<connectionTimeout-1;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    }
    p->Step();
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);

    p->OnClientReady(clientIndex0);
    for (int i=0;i<connectionTimeout-1;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    }
    p->Step();
    TS_ASSERT_EQUALS(0, client0->simulationStartStep);
    TS_ASSERT_EQUALS(2, client0->clientStatuses.size());
    // One client is ok
    TS_ASSERT_EQUALS(-1, client0->clientStatuses[0].step);
    TS_ASSERT_EQUALS(0, client0->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[0].status);
    // Another - timed out
    TS_ASSERT_EQUALS(-1, client0->clientStatuses[1].step);
    TS_ASSERT_EQUALS(1, client0->clientStatuses[1].clientId);
    TS_ASSERT_EQUALS(Peered::ConnectionTimedOut, client0->clientStatuses[1].status);

    p->OnGameFinish(clientIndex0, 0, GetFinishData(lobby::ETeam::Team1));

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(3, statisticsWrapper->statuses.size());
    TS_ASSERT_EQUALS(Peered::Connecting, statisticsWrapper->statuses[0].status);
    TS_ASSERT_EQUALS(Peered::ConnectionTimedOut, statisticsWrapper->statuses[1].status);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, statisticsWrapper->statuses[2].status);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, statisticsWrapper->statuses[2].reason);
    TS_ASSERT_EQUALS(0, statisticsWrapper->GetStatusesDelta());
  }

  void test_ClientConnectionTimeoutWhileOtherClientsDisconnected()
  {
    const int connectionTimeout = 100;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 0, 0, 0, 0, connectionTimeout);

    // Add only 2 of 3 clients with OnClientReady report
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    AddClient(p, "test0", 55, client0, true);
    AddClient(p, "test1", 56, client1, true);

    // Drop 2 clients
    p->Step();
    client0->status = rpc::Disconnected;
    client1->status = rpc::Disconnected;

    // Check, that session will naturaly time out, after waiting to 3rd client
    for (int i = 0; i < connectionTimeout - 1; ++i)
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_LateConnection()
  {
    const int connectionTimeout = 10;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1), 0, 0, 0, 0, connectionTimeout);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    p->OnClientReady(clientIndex0);
    for (int i=0;i<connectionTimeout-1;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    }
    p->Step();
    TS_ASSERT_EQUALS(0, client0->simulationStartStep);

    StrongMT<test::MockClient> client1 = new test::MockClient();
    WeakMT<test::MockClient> wclient1 = client1;

    p->OnRejoinClient(1);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    TS_ASSERT_LESS_THAN_EQUALS(0, clientIndex1);  // Late connection today = reconnect => client will be added
    //client1 = 0;
    //TS_ASSERT_EQUALS(false, bool(wclient1.Lock()));
  }

  void test_FirstClientConnectionTimeout()
  {
    const int firstConnectionTimeout = 100;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2), 0, 0, 0, 0, 0, 1, firstConnectionTimeout);
    for (int i=0;i<firstConnectionTimeout-1;++i)
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    StrongMT<test::MockClient> client0 = new test::MockClient();
    WeakMT<test::MockClient> wclient0 = client0;
    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    TS_ASSERT_EQUALS(-1, clientIndex0);
    client0 = 0;
    TS_ASSERT_EQUALS(false, bool(wclient0.Lock()));
  }

  void test_ClientConnectionTimeoutReset()
  {
    const int connectionTimeout = 50;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2), 0, 0, 0, 0, connectionTimeout);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);

    for (int i=0;i<connectionTimeout-1;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    }
    p->Step();
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);

    p->OnClientReady(clientIndex0);
    for (int i=0;i<connectionTimeout-1;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    }
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    for (int i=0;i<connectionTimeout-1;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
      TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    }
    p->Step();
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    p->OnClientReady(clientIndex1);
    for (int i=0;i<connectionTimeout-1;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
      TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    }
    p->Step();
    TS_ASSERT_EQUALS(0, client0->simulationStartStep);
    TS_ASSERT_EQUALS(0, client1->simulationStartStep);
  }

  void test_ClientSingleConnectionAndGameStart()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0));

    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);

    const int commandSize = 11;
    char commandData[commandSize];
    test::FormatCommand(&commandData, 0, "cmd");
    rpc::MemoryBlock command(commandData, commandSize);
    p->SendCommand(clientIndex0, command, true);
    p->Step();

    p->OnClientReady(clientIndex0);     
    TS_ASSERT_EQUALS(1, client0->simulationStartStep);
  }


  void test_ClientConfirmationAfterDisconnectOnFirstStep()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1));

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);

    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    p->Step();
    p->OnFinishStep(clientIndex0, 0, 0xF00D); 

    client1->status = rpc::Disconnected;
    p->Step();
    p->OnFinishStep(clientIndex1, 0, 0xF00D); 
  }

  void test_Stress()
  {
    nstl::vector<StrongMT<Peered::CommandsScheduler>> schedulers;
    const int schedulersCount = 1; // 500
    const int clientsInOneSessionCount = 10;
    const int simulationStep = 100; // in ms
    const int dumpLogSteps = 600; // 60 seconds of logging will be dumped
    const int stepsCount = 10*60*2; // 100

    nstl::vector<StrongMT<test::MockClient>> clients;
    nstl::vector<int> confirmedSteps;

    class DummyCommandsLog : public HybridServer::ICommandsLog, public BaseObjectMT
    {
      NI_DECLARE_REFCOUNT_CLASS_2(DummyCommandsLog, HybridServer::ICommandsLog, BaseObjectMT);
    public:
      virtual void OnHeaderDump(const Peered::SchedulerData & data, const lobby::TGameLineUp * gameLineUp, const lobby::SGameParameters * gameParams, const vector<Peered::ClientInfo> * clientInfos)
      {
      }
      virtual void OnStartGame(Peered::TSessionId serverId, const Login::ClientVersion & clientVersion, int step)
      {
      }
      virtual void OnCommandsDump(Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses)
      {
      }
      virtual void OnFinishGame(Peered::TSessionId serverId, int step)
      {
      }
    };

    for (int i=0;i<schedulersCount;++i)
    {
      StrongMT<Peered::CommandsScheduler> scheduler = Create(0, simulationStep, 0, new DummyCommandsLog(), dumpLogSteps, i);

      for (int j=0;j<clientsInOneSessionCount;++j)
      {
        StrongMT<test::MockClient> client = new test::MockClient();
        int clientId = i*clientsInOneSessionCount+j;
        scheduler->AddClient("test", clientId, Login::ClientVersion(), client);
        clients.push_back(client);
        SendNumberedCommand(scheduler, client->index, clientId, "NewCmd", i*clientsInOneSessionCount+j);
        confirmedSteps.push_back(0);
      }
      for (int j=0;j<clientsInOneSessionCount;++j)
      {
        scheduler->OnClientReady(clients[i*clientsInOneSessionCount+j]->index);
        scheduler->Step();
      }
      schedulers.push_back(scheduler);
    }

    int cmdIndex = 0;
    int startStep = clients[clients.size()-1]->steps[clients[clients.size()-1]->steps.size()-1].step;
    for (int k=0;k<confirmedSteps.size();++k) 
    {
      confirmedSteps[k] = startStep;
    }
    for (int i=0;i<clients.size();++i)
    {
      clients[i]->saveData = false;
    }

    for (int i=0;i<stepsCount;++i)
    {
      for (int j=0;j<schedulers.size();++j)
      {
        for (int k=0;k<clientsInOneSessionCount;++k)
        {
          int clientId = j*clientsInOneSessionCount+k;
          SendNumberedCommand(schedulers[j], clients[clientId]->index, clientId, "GameCmd", cmdIndex++);
        }
      }
      for (int k=0;k<confirmedSteps.size();++k)
      {
        int confirmedDelta = i-confirmedSteps[k];
        bool confirm = false;
        if (confirmedDelta > 30)
        {
          confirm = true;
        } else
          if (confirmedDelta > 3)
          {
            confirm = NWin32Random::Random( 0.f, 1.f ) < 0.5f;
          }
          if (confirm)
          {
            schedulers[k/clientsInOneSessionCount]->OnFinishStep(clients[k]->index, confirmedSteps[k], confirmedSteps[k]);
            confirmedSteps[k]++;
          }
      }
      for (int j=0;j<schedulers.size();++j)
      {
        schedulers[j]->Step();
      }
    }
  }

  void test_LimitClientsCount()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);

    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);

    for (int i=0;i<10;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(0, client0->steps.size());
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    }
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    for (int i=0;i<10;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(0, client0->steps.size());
      TS_ASSERT_EQUALS(0, client1->steps.size());
    }
    p->OnClientReady(clientIndex1);
    TS_ASSERT_EQUALS(0, client1->simulationStartStep);
    TS_ASSERT_EQUALS(0, client1->simulationStartStep);
  }

  void test_LimitClientsCountAndNoConnection()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1));
    StrongMT<test::MockClient> client0 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, true);
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);

    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);

    for (int i=0;i<50;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(0, client0->steps.size());
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    }
    p->Step();
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep); // should be if situation handled correctly
  }

  void test_ClientDisconnectionBeforeAllClientsReadyAndClientsStartCountLimited()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    p->OnClientReady(clientIndex0);

    AddClient(p, "test1", 1, client1, false);
    client1->status = rpc::Disconnected;
    p->Step();
    // Should be step 1 and not 0, because disconnect status produces pending step and we have double step on start
    TS_ASSERT_EQUALS(1, client0->simulationStartStep);
  }

  void test_TwoClientsDisconnectionBeforeAllClientsReadyAndClientsStartCountLimited()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    p->OnClientReady(clientIndex0);

    AddClient(p, "test1", 1, client1, false);
    AddClient(p, "test2", 2, client2, false);
    client1->status = rpc::Disconnected;
    client2->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(0, client0->clientStatuses.size());
    p->Step();
    TS_ASSERT_EQUALS(5, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(1, client0->clientStatuses[0].clientId);  // Two disconnection statuses from step
    TS_ASSERT_EQUALS(2, client0->clientStatuses[1].clientId);
    TS_ASSERT_EQUALS(0, client0->clientStatuses[2].clientId);  // All (3) clients statuses update from start
    TS_ASSERT_EQUALS(1, client0->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(2, client0->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[0].status);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[1].status);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[2].status);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[3].status);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[4].status);
    TS_ASSERT_EQUALS(-1, client0->clientStatuses[0].step);
    TS_ASSERT_EQUALS(-1, client0->clientStatuses[1].step);
    TS_ASSERT_EQUALS(0, client0->clientStatuses[2].step);
    TS_ASSERT_EQUALS(-1, client0->clientStatuses[3].step);
    TS_ASSERT_EQUALS(-1, client0->clientStatuses[4].step);
    // Should be step 1 and not 0, because disconnect status produces pending step and we have double step on start
    TS_ASSERT_EQUALS(1, client0->simulationStartStep);
    CheckStepsConsistency(client0->steps);
  }

  void test_ClientDisconnectionDuringLoading()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);

    char commandData0[12];
    test::FormatCommand(&commandData0, 0, "cmd0");
    rpc::MemoryBlock command0(commandData0, 12);
    char commandData1[12];
    test::FormatCommand(&commandData1, 1, "cmd1");
    rpc::MemoryBlock command1(commandData1, 12);

    for (int i=0;i<10;++i)
    {
      if (i % 2 == 0)
        p->SendCommand(clientIndex0, command0, true);
      else
        p->SendCommand(clientIndex1, command1, true);

      p->Step();
    }

    client0->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(0, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(0, client1->clientStatuses.size());
    p->Step();
    TS_ASSERT_EQUALS(0, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(1, client1->clientStatuses.size());
    TS_ASSERT_EQUALS(0, client1->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client1->clientStatuses[0].status);
    TS_ASSERT_EQUALS(-1, client1->clientStatuses[0].step);
  }

  void test_DisconnectClientsAndRemoveFromQueue()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->Step();
    client0->status = rpc::Disconnected;
    client1->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_DisconnectClientsAndDrawStats()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->Step();
    client0->status = rpc::Disconnected;
    client1->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(lobby::EGameResult::NoResults, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(2, gameResults.players.size());
    TS_ASSERT_EQUALS(0, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(1, gameResults.players[1].userid);
  }

  void test_DisconnectClientsStats()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->Step();
    client0->status = rpc::Disconnected;

    p->Step();
    TS_ASSERT_EQUALS(1, link->droppedClients.size());
    TS_ASSERT_EQUALS(0, link->droppedClients[0]);

    client1->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(2, link->droppedClients.size());
    TS_ASSERT_EQUALS(1, link->droppedClients[1]);
    TS_ASSERT_EQUALS(lobby::EGameResult::NoResults, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(2, gameResults.players.size());
    TS_ASSERT_EQUALS(0, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(1, gameResults.players[1].userid);
  }

  void test_NoOneConnectedStats()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;

    const int firstConnectionTimeout = 100;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2), link, 0, 0, 0, 0, 1, firstConnectionTimeout);
    for (int i=0;i<firstConnectionTimeout-1;++i)
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(lobby::EGameResult::NobodyCame, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(3, gameResults.players.size());
    TS_ASSERT_EQUALS(0, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(1, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(2, gameResults.players[2].userid);
  }

  void test_FirstConnectionTimeOutNotification()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;

    const int connectionTimeout = 100;
    const int firstConnectionTimeout = 100;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2), link, 0, 0, 0, connectionTimeout, 1, firstConnectionTimeout);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    for (int i = 0; i < firstConnectionTimeout; ++i)
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }
    TS_ASSERT_EQUALS(100, p->Step());

    // Connecting + 2 timouts
    TS_ASSERT_EQUALS(3, link->clientStatuses.size());
    TS_ASSERT_EQUALS(0, link->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::Connecting, link->clientStatuses[0].status);
    TS_ASSERT_EQUALS(1, link->clientStatuses[1].clientId);
    TS_ASSERT_EQUALS(Peered::ConnectionTimedOut, link->clientStatuses[1].status);
    TS_ASSERT_EQUALS(2, link->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::ConnectionTimedOut, link->clientStatuses[2].status);

    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(100, p->Step());
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    TS_ASSERT_EQUALS(100, p->Step());
    p->OnClientReady(clientIndex1);
    TS_ASSERT_EQUALS(100, p->Step());

    // clients do not receive first connection time out notifications
    TS_ASSERT_EQUALS(0, client0->clientStatuses.size());

    // One previously timed out client is now connecting
    TS_ASSERT_EQUALS(4, link->clientStatuses.size());
    TS_ASSERT_EQUALS(1, link->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::Connecting, link->clientStatuses[3].status);

    for (int i = 0; i < connectionTimeout; ++i)
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }

    // On session start the third client shouldn't get additional timed out status
    TS_ASSERT_EQUALS(4, link->clientStatuses.size());

    // Clients receive all final statuses on game start
    TS_ASSERT_EQUALS(3, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(0, client0->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[0].status);
    TS_ASSERT_EQUALS(1, client0->clientStatuses[1].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[1].status);
    TS_ASSERT_EQUALS(2, client0->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::ConnectionTimedOut, client0->clientStatuses[2].status);
  }

  void test_AwayFromComputer()
  {
    const int afkSteps = 20;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, 0, 0, 0, afkSteps);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    for (int i=0;i<afkSteps;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(0, client0->clientStatuses.size());
      TS_ASSERT_EQUALS(0, client1->clientStatuses.size());
    }
    p->Step();
    TS_ASSERT_EQUALS(0, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(0, client1->clientStatuses.size());
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    for (int i=0;i<afkSteps;++i)
    {
      // Client 0 sends nothing, while client 1 sends non-player command which arent affect AFK logic
      SendNumberedCommand(p, clientIndex1, 1, "SyncCmd", 0, false);
      p->Step();
      p->OnFinishStep(clientIndex0, client0->steps.size()-1, 0);
      p->OnFinishStep(clientIndex1, client1->steps.size()-1, 0);
      TS_ASSERT_EQUALS(i+1, client0->steps.size());
      TS_ASSERT_EQUALS(i+1, client1->steps.size());
      TS_ASSERT_EQUALS(2, client0->clientStatuses.size()); // We have the first (Active) status for both clients
      TS_ASSERT_EQUALS(2, client1->clientStatuses.size());
    }
    p->Step();
    TS_ASSERT_EQUALS(4, client0->clientStatuses.size());  // Both got Away status
    TS_ASSERT_EQUALS(4, client1->clientStatuses.size());
    TS_ASSERT_EQUALS(0, client0->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(1, client0->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::Away, client0->clientStatuses[2].status);
    TS_ASSERT_EQUALS(Peered::Away, client0->clientStatuses[3].status);
    TS_ASSERT_EQUALS(19, client0->clientStatuses[2].step);
    TS_ASSERT_EQUALS(19, client0->clientStatuses[3].step);
    p->Step();
    TS_ASSERT_EQUALS(4, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(4, client1->clientStatuses.size());

    // Now client 0 wil cancel AFK by plyer command and client 1 will remain AFK despite non-player command
    SendNumberedCommand(p, clientIndex0, 0, "SyncCmd", 0);
    SendNumberedCommand(p, clientIndex1, 1, "SyncCmd", 0, false);
    p->Step();
    p->OnFinishStep(clientIndex0, client0->steps.size()-3, 0);
    p->OnFinishStep(clientIndex1, client1->steps.size()-3, 0);
    TS_ASSERT_EQUALS(5, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(5, client1->clientStatuses.size());
    TS_ASSERT_EQUALS(0, client0->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[4].status);
    TS_ASSERT_EQUALS(client0->steps.size()-4, client0->clientStatuses[2].step);
  }

  void test_AwayFromComputerDisconnect()
  {
    const int afkDisconnnectSteps = 40;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1), 0, 0, 0, 0, 0, 1, 0, 0, afkDisconnnectSteps);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    WeakMT<test::MockClient> wclient0 = client0;

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 1, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);

    for (int i=0;i<afkDisconnnectSteps;++i)
    {
      p->Step();
      p->OnFinishStep(clientIndex0, client0->steps.size()-1, 0);
      p->OnFinishStep(clientIndex1, client1->steps.size()-1, 0);
      {
        p->SendCommand(clientIndex1, command0, true);
      }
      TS_ASSERT_EQUALS(i+1, client0->steps.size());
      TS_ASSERT_EQUALS(2, client0->clientStatuses.size()); // Active*2
      TS_ASSERT_EQUALS(i+1, client1->steps.size());
      TS_ASSERT_EQUALS(2, client1->clientStatuses.size()); // Active*2
    }
    client0 = 0;
    TS_ASSERT_EQUALS(true, bool(wclient0.Lock()));
    p->Step();
    TS_ASSERT_EQUALS(false, bool(wclient0.Lock()));
    TS_ASSERT_EQUALS(3, client1->clientStatuses.size());
    TS_ASSERT_EQUALS(0, client1->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(39, client1->clientStatuses[2].step);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client1->clientStatuses[2].status);
  }

  void test_AwayFromComputerDisconnectWithAck()
  {
    Peered::SchedulerData data;
    data.sessionSettings.afkStepsDisconnectCount = 40;
    data.sessionSettings.disconnectAckTimeoutSteps = 20;
    StrongMT<Peered::CommandsScheduler> p = Create(data, 0, 0, FillClients(0, 1, 2));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    WeakMT<test::MockClient> wclient0 = client0;
    WeakMT<test::MockClient> wclient1 = client1;

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    int clientIndex2 = AddClient(p, "test2", 2, client2, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->OnClientReady(clientIndex2);

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 2, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);

    for (int i = 0; i < data.sessionSettings.afkStepsDisconnectCount; ++i)
    {
      p->Step();
      p->OnFinishStep(clientIndex0, client0->steps.size()-1, 0);
      p->OnFinishStep(clientIndex1, client1->steps.size()-1, 0);
      p->OnFinishStep(clientIndex2, client2->steps.size()-1, 0);
      {
        p->SendCommand(clientIndex2, command0, true);
      }
      TS_ASSERT_EQUALS(i+1, client0->steps.size());
      TS_ASSERT_EQUALS(3, client0->clientStatuses.size()); // Active*3
      TS_ASSERT_EQUALS(i+1, client1->steps.size());
      TS_ASSERT_EQUALS(3, client1->clientStatuses.size()); // Active*3
      TS_ASSERT_EQUALS(i+1, client2->steps.size());
      TS_ASSERT_EQUALS(3, client2->clientStatuses.size()); // Active*3
    }
    client0 = 0;
    TS_ASSERT_EQUALS(true, bool(wclient0.Lock()));
    p->Step();
    TS_ASSERT_EQUALS(true, bool(wclient0.Lock()));
    p->OnDisconnectAck(clientIndex0);
    TS_ASSERT_EQUALS(false, bool(wclient0.Lock()));

    client1 = 0;
    for (int i = 0; i < data.sessionSettings.disconnectAckTimeoutSteps; ++i)
    {
      TS_ASSERT_EQUALS(true, bool(wclient1.Lock()));
      p->Step();
    }
    TS_ASSERT_EQUALS(false, bool(wclient1.Lock()));

    TS_ASSERT_EQUALS(5, client2->clientStatuses.size());
    TS_ASSERT_EQUALS(0, client2->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(1, client2->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(39, client2->clientStatuses[3].step);
    TS_ASSERT_EQUALS(39, client2->clientStatuses[4].step);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client2->clientStatuses[3].status);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client2->clientStatuses[4].status);
  }

  void test_DisconnectClientsWhileLoadingAndRemoveFromQueue()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    AddClient(p, "test0", 0, client0, false);
    AddClient(p, "test1", 1, client1, false);
    p->Step();
    client0->status = rpc::Disconnected;
    client1->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_DoubleStartGame()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
    int clientIndex1 = AddClient(p, "test1", 1, client1, false);
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->Step();
  }

  void test_DisconnectionIfNoConfirmationWereSent()
  {
    const int disconnectionGap = 5;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), 0, 0, 0, disconnectionGap);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test0", 55, client0, true);
    int clientIndex1 = AddClient(p, "test1", 56, client1, true);
    p->Step();
    p->OnFinishStep(clientIndex0, 0, 0);
    p->OnFinishStep(clientIndex1, 0, 0);
    for (int i=0;i<disconnectionGap;++i)
    {
      p->Step();
      p->OnFinishStep(clientIndex1, i+1, 0);
    }
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(2, client1->clientStatuses.size()); // Active*2
    p->Step();
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ClientPerfomance, client0->disconnectReason);
    TS_ASSERT_EQUALS(3, client1->clientStatuses.size());
    TS_ASSERT_EQUALS(55, client1->clientStatuses[2].clientId);
  }

  void test_DisconnectionIfNoConfirmationWereSentIncludingLoadingStage()
  {
    const int disconnectionGap = 5;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), 0, 0, 0, disconnectionGap);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test0", 55, client0, false);
    int clientIndex1 = AddClient(p, "test1", 56, client1, false);
    for (int i=0;i<disconnectionGap*2;++i)
    {
      SendNumberedCommand(p, clientIndex0, 55, "data0", i); 
      SendNumberedCommand(p, clientIndex1, 56, "data1", i);
      p->Step();
    }
    p->OnClientReady(clientIndex0);
    p->OnClientReady(clientIndex1);
    p->Step();
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);
  }

  void test_GameFinishNotificaton()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());

    p->OnGameFinish( clientId0, 0, GetFinishData(lobby::ETeam::Team1) );
    TS_ASSERT_EQUALS(100, p->Step());
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client1->steps.size());

    p->OnGameFinish( clientId1, 0, GetFinishData(lobby::ETeam::Team1) );
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS( GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo );

    // OnGameFinish called on different results
    //
  }

  void test_GameFinishNotificatonWithOneClientNotArrived()
  {
    const int connectionTimeout = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link, 0, 0, 0, connectionTimeout);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);

    for (int i=0;i<connectionTimeout-1;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
      TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    }
    p->Step();
    TS_ASSERT_EQUALS(0, client0->simulationStartStep);
    TS_ASSERT_EQUALS(0, client1->simulationStartStep);

    for (int i=0;i<10;++i)
    {
      p->Step();
      p->OnFinishStep(clientId0, i, 0);
      p->OnFinishStep(clientId1, i, 0);
    }
    p->OnGameFinish(clientId1, 9, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId0, 9, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS( GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    TS_ASSERT_EQUALS(lobby::EGameResult::SyncResults, link->gameResultType);

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_GameFinishNotificatonWithOneClientNotArrivedAndDisconnectionBeforeSendingResults()
  {
    const int connectionTimeout = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link, 0, 0, 0, connectionTimeout);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);

    for (int i=0;i<connectionTimeout-1;++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
      TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    }
    p->Step();
    TS_ASSERT_EQUALS(0, client0->simulationStartStep);
    TS_ASSERT_EQUALS(0, client1->simulationStartStep);

    for (int i=0;i<10;++i)
    {
      p->Step();
      p->OnFinishStep(clientId0, i, 0);
      p->OnFinishStep(clientId1, i, 0);
    }
    p->OnGameFinish( clientId1, 9, GetFinishData(lobby::ETeam::Team1) );
    client1->status = rpc::Disconnected;
    for (int i=0;i<10;++i)
    {
      p->Step();
    }
    client0->status = rpc::Disconnected;
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS( GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo );
    TS_ASSERT_EQUALS(lobby::EGameResult::SyncResults, link->gameResultType);
  }

  void test_GameFinishNotificatonWithOneClient()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    p->OnClientReady(clientId0);
    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());

    p->OnGameFinish( clientId0, 0, GetFinishData(lobby::ETeam::Team1) );

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(lobby::EGameResult::SyncResults, link->gameResultType);
    TS_ASSERT_EQUALS( GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo );
  }

  void test_GameFinishNotificatonDiffSteps()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->Step();
    p->Step();
    p->Step();
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());

    p->OnGameFinish( clientId0, 0, GetFinishData(lobby::ETeam::Team1) );
    p->OnGameFinish( clientId1, 1, GetFinishData( lobby::ETeam::Team2 ) );
    TS_ASSERT_EQUALS(lobby::EGameResult::AsyncResults, link->gameResultType);
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_GameFinishNotificatonDiffResults()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->Step();
    p->Step();
    p->Step();
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());

    p->OnGameFinish( clientId0, 0, GetFinishData(lobby::ETeam::Team1) );
    p->OnGameFinish( clientId1, 0, GetFinishData( lobby::ETeam::Team2 ) );
    TS_ASSERT_EQUALS(lobby::EGameResult::AsyncResults, link->gameResultType);
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_GameFinishNotificatonDuringLoading()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->OnGameFinish( clientId0, 11, GetFinishData(lobby::ETeam::Team1) );
    TS_ASSERT_EQUALS(link->cheaters[0], 55);
    p->OnGameFinish( clientId1, 445, GetFinishData(lobby::ETeam::Team1) );
    TS_ASSERT_EQUALS(link->cheaters[1], 56);
  }

  void test_GameFinishNotificatonCheatersDisconnection()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    WeakMT<test::MockClient> wclient0(client0);
    WeakMT<test::MockClient> wclient1(client1);

    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    client0 = 0;
    client1 = 0;
    {
      TS_ASSERT_EQUALS(true, bool(wclient0.Lock()));
      TS_ASSERT_EQUALS(true, bool(wclient1.Lock()));
    }
    p->OnGameFinish( clientId0, 11, GetFinishData(lobby::ETeam::Team1) );
    TS_ASSERT_EQUALS(link->cheaters[0], 55);
    {
      TS_ASSERT_EQUALS(false, bool(wclient0.Lock()));
    }
    p->OnGameFinish( clientId1, 445, GetFinishData(lobby::ETeam::Team1) );
    TS_ASSERT_EQUALS(link->cheaters[1], 56);
    {
      TS_ASSERT_EQUALS(false, bool(wclient1.Lock()));
    }
  }

  void test_GameFinishNotificatonWithBadSteps()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnGameFinish(clientId0, 6666, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(link->cheaters[0], 55);
  }

  void test_GameFinishNotificatonCalledTwice()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->Step();
    p->OnGameFinish(clientId0, 0, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(0, link->cheaters.size());
    p->OnGameFinish(clientId0, 0, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(link->cheaters[0], 55);
  }

  nstl::vector<byte> GetData(const char* data)
  {
    nstl::vector<byte> result;
    int n = strlen(data);
    if (n > 0)
    {
      result.resize(n);
      for (int i=0;i<n;i++)
      {
        result[i] = data[i];
      }
    }
    return result;
  }

  NCore::PlayerInfo GetMockPlayerInfo( NCore::TAuid _auid )
  {
    NCore::PlayerInfo info;
    info.auid = _auid;
    return info;
  }

  StatisticService::RPC::SessionClientResults GetFinishData(lobby::ETeam::Enum victoriousFaction)
  {
    StatisticService::RPC::SessionClientResults info;
    info.sideWon = victoriousFaction;
    return info;
  }

  void test_ClientData()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, GetMockPlayerInfo(100500), GetMockPlayerInfo(100000000)), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    AddClient(p, "test0", 55, client0, false);
    TS_ASSERT_EQUALS(55, client0->clientInfos[0].clientId);
    TS_ASSERT_EQUALS(56, client0->clientInfos[1].clientId);
    TS_ASSERT_EQUALS(100500, client0->clientInfos[0].info.auid);
    TS_ASSERT_EQUALS(100000000, client0->clientInfos[1].info.auid);

    AddClient(p, "test1", 56, client1, false);
    TS_ASSERT_EQUALS(55, client1->clientInfos[0].clientId);
    TS_ASSERT_EQUALS(56, client1->clientInfos[1].clientId);
    TS_ASSERT_EQUALS(100500, client1->clientInfos[0].info.auid);
    TS_ASSERT_EQUALS(100000000, client1->clientInfos[1].info.auid);
  }

  void test_GameFinishNotificatonCalledAfterDisconnection()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link, 0, 0, 0);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    int clientId2 = AddClient(p, "test2", 57, client2, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientId2);
    p->Step();
    p->OnGameFinish(clientId0, 0, GetFinishData(lobby::ETeam::Team1));
    client1->status = rpc::Disconnected;
    p->Step();
    p->OnGameFinish(clientId1, 0, GetFinishData(lobby::ETeam::Team1));
    p->Step();
    p->OnGameFinish(clientId2, 0, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_CommandsDuringAsyncShouldBeDropped()
  {

  }

  void test_CompleteShapshotsInDifferentTimes()
  {
    StrongMT<Peered::CommandsScheduler> p = Create();
    nstl::vector<StrongMT<test::MockClient>> clients;

    nstl::vector<int> clientIndices;
    int clientsCount = 10;
    for (int i=0;i<clientsCount;++i)
    {
      StrongMT<test::MockClient> client = new test::MockClient();
      int index = AddClient(p, "test", i, client, false);
      clients.push_back(client);
      clientIndices.push_back(index);
    }
    // all client ready
    for (int i=0;i<clients.size();++i)
    {
      p->OnClientReady(clientIndices[i]);
    }
    // make 10 steps
    for (int i=0;i<10;++i)
    {
      p->Step();
    }
    // confirming step 0
    for (int i=0;i<clients.size();++i)
    {
      p->OnFinishStep(clientIndices[i], 0, 0);
    }
    /*struct FinishStepInfo
    {
      int step;
      int crc;
      int clientIndex;
    };
    FinishStepInfo infos[] = {
      { 1, 1, 9 }, // 1     
      { 1, 1, 0 }, // 2
      { 1, 1, 1 }, // 3
      { 2, 2, 1 },
      { 1, 1, 2 }, // 4
      { 2, 2, 2 },
      { 3, 3, 2 },
      { 1, 1, 3 }, // 5
      { 2, 2, 3 },
      { 3, 3, 3 },
      { 4, 4, 3 },
      { 1, 1, 4 }, // 6
      { 2, 2, 4 },
      { 3, 3, 4 },
      { 4, 4, 4 },
      { 5, 5, 4 },
      { 2, 2, 5 },
      { 1, 1, 5 }, // 7
      { 3, 3, 5 },
      { 4, 4, 5 },
      { 5, 5, 5 },
      { 1, 1, 6 }, // 8
      { 2, 2, 6 },
      { 4, 4, 6 },
      { 5, 5, 6 },
      { 6, 6, 6 },
      { 3, 3, 6 },
      { 1, 1, 7 }, // 9
      { 2, 2, 7 },
      { 3, 3, 7 },
      { 4, 4, 7 },
      { 5, 5, 7 },
      { 6, 6, 7 },
      { 1, 1, 8 }, // 10
    };
    int infosCount = sizeof(infos)/sizeof(FinishStepInfo);
    for (int i=0;i<infosCount-1;++i)
    {
      FinishStepInfo& info = infos[i];
      p->OnFinishStep(info.clientIndex, info.step, info.crc);
    }
    {
      FinishStepInfo& info = infos[infosCount-1];
      p->OnFinishStep(info.clientIndex, info.step, info.crc);
    }*/
  }

  void FillDataPartAscending(nstl::vector<byte> & dataPart, int size, byte first)
  {
    dataPart.resize(size);
    for (int i = 0; i < size; ++i)
      dataPart[i] = first++;
  }

  // The common case: one client disconnects and rejoins during the session + sending command and game finish
  void test_Reconnect()
  {
    const int snapshotChunkSize = 5;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,0, 0, 0, 0, 1, 0, 0, 0, snapshotChunkSize);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    TS_ASSERT_EQUALS(snapshotChunkSize, client0->snapshotChunkSize)
    TS_ASSERT_EQUALS(false, client0->isReconnecting)
    TS_ASSERT_EQUALS(snapshotChunkSize, client1->snapshotChunkSize)
    TS_ASSERT_EQUALS(false, client1->isReconnecting)
    TS_ASSERT_EQUALS(snapshotChunkSize, client2->snapshotChunkSize)
    TS_ASSERT_EQUALS(false, client2->isReconnecting)
    p->Step();
    p->Step();

    // Current client logic will report step only when the second is received
    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(4, client0->clientStatuses.size()); // Active*3 + DisconnectedByClient
    TS_ASSERT_EQUALS(57, client0->clientStatuses[3].clientId);
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    TS_ASSERT_EQUALS(snapshotChunkSize, clientR->snapshotChunkSize);
    TS_ASSERT_EQUALS(true, clientR->isReconnecting);

    TS_ASSERT_EQUALS(false, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client1->steps.size());
    TS_ASSERT_EQUALS(false, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);

    p->RequestWorldData(clientIdR);
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->Step();
    TS_ASSERT_EQUALS(true, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    TS_ASSERT_EQUALS(6, client0->steps.size());
    TS_ASSERT_EQUALS(6, client1->steps.size());

    nstl::vector<byte> part1;
    nstl::vector<byte> part2;
    FillDataPartAscending(part1, snapshotChunkSize, 0);
    FillDataPartAscending(part2, snapshotChunkSize, snapshotChunkSize);
    {
      rpc::MemoryBlock worldDataPart1(part1.begin(), part1.size());
      rpc::MemoryBlock worldDataPart2(part2.begin(), part2.size());
      Peered::WorldDataInfo worldDataInfo(5, 2);
      client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    }
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(7, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientR->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(2, clientR->mockClientReconnect->worldDataInfo.partsCount);
    TS_ASSERT_EQUALS(5, clientR->mockClientReconnect->worldDataInfo.step);
    TS_ASSERT_SAME_DATA(part1.begin(), clientR->mockClientReconnect->worldDataParts[0].memory, part1.size());
    TS_ASSERT_SAME_DATA(part2.begin(), clientR->mockClientReconnect->worldDataParts[1].memory, part2.size());
    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->OnFinishStep(clientId1, 5, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(8, client1->steps.size());
    p->OnFinishStep(clientId0, 6, 0xF00D);
    p->OnFinishStep(clientId1, 6, 0xF00D);
    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(9, client0->steps.size());
    TS_ASSERT_EQUALS(9, client1->steps.size());
    TS_ASSERT_EQUALS(3, clientR->steps.size());
    // Should receive current status of all clients on rconnect and its own active status after
    TS_ASSERT_EQUALS(4, clientR->clientStatuses.size());
    TS_ASSERT_EQUALS(55, clientR->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::Active, clientR->clientStatuses[0].status);
    TS_ASSERT_EQUALS(56, clientR->clientStatuses[1].clientId);
    TS_ASSERT_EQUALS(Peered::Active, clientR->clientStatuses[1].status);
    TS_ASSERT_EQUALS(57, clientR->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::Connecting, clientR->clientStatuses[2].status);
    TS_ASSERT_EQUALS(57, clientR->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::Active, clientR->clientStatuses[3].status);
    //Reconnected client must confirm the step it reconnected on (step of the applied world snapshot)
    p->OnFinishStep(clientId0, 7, 0xF00D);
    p->OnFinishStep(clientId1, 7, 0xF00D);
    p->OnFinishStep(clientIdR, 5, 0xF00D);
    p->OnFinishStep(clientIdR, 6, 0xF00D);
    p->OnFinishStep(clientIdR, 7, 0xF00D);
    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 55, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    p->SendCommand(clientId0, command0, true);
    p->Step();

    p->OnFinishStep(clientId0, 8, 0xF00D);
    p->OnFinishStep(clientId1, 8, 0xF00D);
    p->OnFinishStep(clientIdR, 8, 0xF00D);
    TS_ASSERT_EQUALS(10, client0->steps.size());
    TS_ASSERT_EQUALS(1, client0->steps[9].commands.size());
    TS_ASSERT_EQUALS(commandSize0, client0->steps[9].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, client0->steps[9].commands[0].memory, commandSize0);
    TS_ASSERT_EQUALS(10, client1->steps.size());
    TS_ASSERT_EQUALS(4, clientR->steps.size());
    TS_ASSERT_EQUALS(1, clientR->steps[3].commands.size());
    TS_ASSERT_EQUALS(commandSize0, clientR->steps[3].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, clientR->steps[3].commands[0].memory, commandSize0);
    CheckStepsConsistency(clientR->steps);

    p->OnGameFinish(clientId0, 9, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 9, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientIdR, 9, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
  }

  void test_ReconnectOverflowChunkSize()
  {
    const int snapshotChunkSize = 5;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link,0, 0, 0, 0, 1, 0, 0, 0, snapshotChunkSize);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    p->Step();

    {
      p->Step();
      p->OnFinishStep(clientId0, 0, 0xF00D);
      p->OnFinishStep(clientId1, 0, 0xF00D);
    }

    client1->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS(1, link->droppedClients.size());
    TS_ASSERT_EQUALS(56, link->droppedClients[0]);

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR = AddClient(p, "test1", 56, clientR, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    nstl::vector<byte> part1;
    part1.resize(snapshotChunkSize*2);
    nstl::vector<byte> part2;
    part2.resize(snapshotChunkSize*2);
    {
      rpc::MemoryBlock worldDataPart1(part1.begin(), part1.size());
      rpc::MemoryBlock worldDataPart2(part2.begin(), part2.size());
      Peered::WorldDataInfo worldDataInfo(3, 2);
      client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
      TS_ASSERT_EQUALS(55, link->cheaters[0]);
      TS_ASSERT_EQUALS(2, link->droppedClients.size());
      TS_ASSERT_EQUALS(55, link->droppedClients[1]);
    }
    // check what going on if some player cheated
    // check if statuses about cheating is sending
  }

  void test_ReconnectOverflowChunkCount()
  {
    const int snapshotChunkMaxCount = 2;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link,0, 0, 0, 0, 1, 0, 0, 0, 1024, snapshotChunkMaxCount);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    p->Step();

    {
      p->Step();
      p->OnFinishStep(clientId0, 0, 0xF00D);
      p->OnFinishStep(clientId1, 0, 0xF00D);
    }

    client1->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS(1, link->droppedClients.size());
    TS_ASSERT_EQUALS(56, link->droppedClients[0]);

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR = AddClient(p, "test1", 56, clientR, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    {
      Peered::WorldDataInfo worldDataInfo(3, snapshotChunkMaxCount+1);
      client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
      TS_ASSERT_EQUALS(55, link->cheaters[0]);
      TS_ASSERT_EQUALS(2, link->droppedClients.size());
      TS_ASSERT_EQUALS(55, link->droppedClients[1]);
    }
  }

  // Client reconnects twice
  void test_ReconnectTwice()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, client2->steps.size());
    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client2->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR1 = AddClient(p, "test1", 56, clientR1, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId2, 2, 0xF00D);
    p->RequestWorldData(clientIdR1);
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client2->steps.size());
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId2, 3, 0xF00D);
    rpc::MemoryBlock worldDataPart11("part11", 6);
    rpc::MemoryBlock worldDataPart21("part21", 6);
    Peered::WorldDataInfo worldDataInfo1(4, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart11);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart21);
    p->Step();

    TS_ASSERT_EQUALS(2, clientR1->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_SAME_DATA("part11", clientR1->mockClientReconnect->worldDataParts[0].memory, 6);
    TS_ASSERT_SAME_DATA("part21", clientR1->mockClientReconnect->worldDataParts[1].memory, 6);
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId2, 4, 0xF00D);
    p->OnClientReady(clientIdR1);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(7, client2->steps.size());
    TS_ASSERT_EQUALS(2, clientR1->steps.size());
    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->OnFinishStep(clientId2, 5, 0xF00D);
    p->OnFinishStep(clientIdR1, 4, 0xF00D);
    p->OnFinishStep(clientIdR1, 5, 0xF00D);
    clientR1->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(8, client2->steps.size());
    p->OnFinishStep(clientId0, 6, 0xF00D);
    p->OnFinishStep(clientId2, 6, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR2 = AddClient(p, "test1", 56, clientR2, false);
    p->Step();

    p->OnFinishStep(clientId0, 7, 0xF00D);
    p->OnFinishStep(clientId2, 7, 0xF00D);
    p->RequestWorldData(clientIdR1);
    p->Step();

    TS_ASSERT_EQUALS(10, client0->steps.size());
    TS_ASSERT_EQUALS(10, client2->steps.size());
    TS_ASSERT_EQUALS(true, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, client2->worldDataRequested);
    rpc::MemoryBlock worldDataPart12("part12", 6);
    rpc::MemoryBlock worldDataPart22("part22", 6);
    Peered::WorldDataInfo worldDataInfo2(9, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo2);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart12);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart22);    
    p->Step();

    TS_ASSERT_EQUALS(2, clientR2->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_SAME_DATA("part12", clientR2->mockClientReconnect->worldDataParts[0].memory, 6);
    TS_ASSERT_SAME_DATA("part22", clientR2->mockClientReconnect->worldDataParts[1].memory, 6);
    p->OnClientReady(clientIdR2);
    p->Step();

    TS_ASSERT_EQUALS(12, client0->steps.size());
    TS_ASSERT_EQUALS(12, client2->steps.size());
    TS_ASSERT_EQUALS(2, clientR2->steps.size());
  }

  void test_GameFinishWhileClientReconnecting()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    data.sessionSettings.reconnectEnabled = true;
    objects.statisticsWrapper = statisticsWrapper;
    objects.statsLink = link;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    TS_ASSERT_EQUALS(3, statisticsWrapper->statuses.size());
    TS_ASSERT_EQUALS(Peered::Connecting, statisticsWrapper->statuses[0].status);
    TS_ASSERT_EQUALS(Peered::Connecting, statisticsWrapper->statuses[1].status);
    TS_ASSERT_EQUALS(Peered::Connecting, statisticsWrapper->statuses[2].status);
    TS_ASSERT_EQUALS(55, statisticsWrapper->statuses[0].ctx.userid);
    TS_ASSERT_EQUALS(56, statisticsWrapper->statuses[1].ctx.userid);
    TS_ASSERT_EQUALS(57, statisticsWrapper->statuses[2].ctx.userid);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS(4, statisticsWrapper->statuses.size());
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, statisticsWrapper->statuses[3].status);
    TS_ASSERT_EQUALS(57, statisticsWrapper->statuses[3].ctx.userid);

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    TS_ASSERT_EQUALS(5, statisticsWrapper->statuses.size());
    TS_ASSERT_EQUALS(Peered::Connecting, statisticsWrapper->statuses[4].status);
    TS_ASSERT_EQUALS(57, statisticsWrapper->statuses[4].ctx.userid);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client1->steps.size());

    p->OnGameFinish(clientId0, 4, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 4, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(8, statisticsWrapper->statuses.size());
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, statisticsWrapper->statuses[5].status);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, statisticsWrapper->statuses[6].status);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, statisticsWrapper->statuses[7].status);
    TS_ASSERT_EQUALS(57, statisticsWrapper->statuses[5].ctx.userid); // Reconnecting clients are droped first
    TS_ASSERT_EQUALS(55, statisticsWrapper->statuses[6].ctx.userid);
    TS_ASSERT_EQUALS(56, statisticsWrapper->statuses[7].ctx.userid);
    TS_ASSERT_EQUALS(0, statisticsWrapper->GetStatusesDelta());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    TS_ASSERT_EQUALS(5, client0->clientStatuses.size()); // Active*3, Disconnected, connecting
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, clientR->disconnectReason);

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Normal, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::GameFinished, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(57, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(5, statisticsWrapper->reconnects[0].currentStep);
  }

  void test_GameFinishJustBeforeClientReconnecting()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    data.sessionSettings.reconnectEnabled = true;
    objects.statisticsWrapper = statisticsWrapper;
    objects.statsLink = link;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnGameFinish(clientId0, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 1, GetFinishData(lobby::ETeam::Team1));

    AddClient(p, "test2", 57, clientR, false);
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(0, statisticsWrapper->GetStatusesDelta());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    TS_ASSERT_EQUALS(4, client0->clientStatuses.size()); // Active*3, Disconnected
    TS_ASSERT_EQUALS(57, client0->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[3].status);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Normal, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::WrongSesionState, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(57, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(3, statisticsWrapper->reconnects[0].currentStep);
  }

  void test_DisconnectOfReconnectingClientBeforeWorldRequest()
  {
    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    data.sessionSettings.reconnectEnabled = true;
    objects.statisticsWrapper = statisticsWrapper;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    AddClient(p, "test2", 57, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client1->steps.size());
    clientR->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(6, client0->steps.size());
    TS_ASSERT_EQUALS(6, client1->steps.size());
    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3, disconnected, connecting, disconnected
    TS_ASSERT_EQUALS(57, client0->clientStatuses[5].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[5].status);
  }

  void test_DisconnectOfReconnectingClientDuringWorldRequest()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    p->RequestWorldData(clientIdR);
    clientR->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client1->steps.size());
    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3, disconnected, connecting, disconnected
    TS_ASSERT_EQUALS(57, client0->clientStatuses[5].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[5].status);
  }

  void test_DisconnectOfReconnectingClientAfterWorldRequest()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client1->steps.size());
    clientR->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(6, client0->steps.size());
    TS_ASSERT_EQUALS(6, client1->steps.size());
    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3, disconnected, connecting, disconnected
    TS_ASSERT_EQUALS(57, client0->clientStatuses[5].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[5].status);
  }

  // One client tries to reconnect, but all other clients disconnect 
  // at that point and therefore we don't have any source of world data
  void test_AllClientsDisconnectingOnClientReconnect()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    AddClient(p, "test2", 57, clientR, false);
    client0->status = rpc::Disconnected;
    client1->status = rpc::Disconnected;

    // Here we have to transfer the world, but all clients are disconnected, so we don't have any source, 
    // therefore the client being rejoined should be disconnected and the session should be ended

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished , clientR->disconnectReason);
  }

  // One client is reconnecting (assume he got the world), but all others disconnect before he gets ready
  void test_AllClientsDisconnectingDuringClientReconnect()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);

    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(4, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    client0->status = rpc::Disconnected;
    client1->status = rpc::Disconnected;
    p->Step();

    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(4, clientR->simulationStartStep);
    TS_ASSERT_EQUALS(2, clientR->steps.size());
    p->Step();

    TS_ASSERT_EQUALS(3, clientR->steps.size());
  }

  void test_AsyncJustBeforeClientReconnect()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xBADF00D);
    p->OnRejoinClient(57);
    /*int clientIdR =*/ AddClient(p, "test2", 57, clientR, false);

    // Async clients are disconnected without reason, but with async
    TS_ASSERT_EQUALS(1, client0->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(1, client1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);

    // All active clients dropped due to async and reconnecter is without world applied -> finish
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(3, gameResults.players.size());
    TS_ASSERT_EQUALS(57, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(55, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(56, gameResults.players[2].userid);

    // Reconnecting client is disconnected with GameFinish and without async
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, clientR->disconnectReason);
  }

  void test_AsyncOnClientReconnectBeforeWorldRequest()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    data.sessionSettings.reconnectEnabled = true;
    objects.statisticsWrapper = statisticsWrapper;
    objects.statsLink = link;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    p->OnRejoinClient(57);
    AddClient(p, "test2", 57, clientR, false);
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xBADF00D);

    // Async clients are disconnected without reason, but with async
    TS_ASSERT_EQUALS(1, client0->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(1, client1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);

    // All active clients dropped due to async and reconnecter is without world applied -> finish
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(0, statisticsWrapper->GetStatusesDelta());
    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(3, gameResults.players.size());
    TS_ASSERT_EQUALS(55, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(56, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(57, gameResults.players[2].userid);

    // Reconnecting client is disconnected with GameFinish and without async
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, clientR->disconnectReason);

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Normal, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::GameFinished, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(57, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(3, statisticsWrapper->reconnects[0].currentStep);
  }

  void test_AsyncOnClientReconnectAfterWorldRequst()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->RequestWorldData(clientIdR);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xBADF00D);

    // Async clients are disconnected without reason, but with async
    TS_ASSERT_EQUALS(2, client0->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(2, client1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);

    // All active clients dropped due to async and reconnecter is without world applied -> finish
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(3, gameResults.players.size());
    TS_ASSERT_EQUALS(55, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(56, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(57, gameResults.players[2].userid);

    // Reconnecting client is disconnected with GameFinish and without async
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, clientR->disconnectReason);
  }

  // Tests async handling, which occurs while reconnecting client applying world snapshot.
  void test_AsyncOnClientReconnectAfterWorldApply1()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->RequestWorldData(clientIdR);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    Peered::WorldDataInfo worldDataInfo(3, 1);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xBAFF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size()); // No steps after async
    TS_ASSERT_EQUALS(-1, client1->asyncStep);   // No async here - will wait for clientIdR
    p->OnClientReady(clientIdR);
    p->Step();

    // clientIdR confirms steps, so we can finaly handle the async
    p->OnFinishStep(clientIdR, 3, 0xF00D);
    p->OnFinishStep(clientIdR, 4, 0xF00D);
    p->Step();

    // Async client is disconnected without reason, but with async
    TS_ASSERT_EQUALS(4, client1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);

    // Reconnecting client and another one are left in the session, because their crcs match
    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);

    // Now we resume the game with two clients left
    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(4, clientR->steps.size());

    p->OnFinishStep(clientId0, 5, 0xF00D);
    // In the next row you can put a breakpoint and trace to check, that snapshot deallocation is ok
    p->OnFinishStep(clientIdR, 5, 0xF00D);
  }

  // Tests async handling, which occurs while reconnecting client applying world snapshot.
  // This time we report finish step with async twice for same client, before async is handled.
  void test_AsyncOnClientReconnectAfterWorldApply2()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->RequestWorldData(clientIdR);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    Peered::WorldDataInfo worldDataInfo(3, 1);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xBAFF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size()); // No steps after async
    TS_ASSERT_EQUALS(-1, client1->asyncStep);   // No async here - will wait for clientIdR

    // Now send another async confirmation
    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->OnFinishStep(clientId1, 5, 0xBAFF00D);
    p->OnClientReady(clientIdR);
    p->Step();

    // clientIdR confirms steps, so we can finaly handle the async
    p->OnFinishStep(clientIdR, 3, 0xF00D);
    p->OnFinishStep(clientIdR, 4, 0xF00D);
    p->OnFinishStep(clientIdR, 5, 0xF00D);
    p->Step();

    // Async client is disconnected without reason, but with async
    TS_ASSERT_EQUALS(4, client1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);

    // Reconnecting client and another one are left in the session, because their crcs match
    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);

    // Now we resume the game with two clients left
    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(4, clientR->steps.size());

    p->OnFinishStep(clientId0, 6, 0xF00D);
    // In the next row you can put a breakpoint and trace to check, that snapshot deallocation is ok
    p->OnFinishStep(clientIdR, 6, 0xF00D);
  }

  // Tests async handling, which occurs while reconnecting client applying world snapshot.
  // This time we report finish step with async twice for different clients, before async is handled.
  // On check of the first asynced step we kick one client, on check of the second - the others.
  void test_AsyncOnClientReconnectAfterWorldApply3()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->RequestWorldData(clientIdR);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    Peered::WorldDataInfo worldDataInfo(3, 1);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xBAFF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size()); // No steps after async
    TS_ASSERT_EQUALS(-1, client1->asyncStep);   // No async here - will wait for clientIdR

    // Now send another async confirmation
    p->OnFinishStep(clientId0, 5, 0xBADF00D);
    p->OnFinishStep(clientId1, 5, 0xF00D);
    p->OnClientReady(clientIdR);
    p->Step();

    // clientIdR confirms steps, so we can finaly handle the async
    p->OnFinishStep(clientIdR, 3, 0xF00D);
    p->OnFinishStep(clientIdR, 4, 0xF00D);
    p->OnFinishStep(clientIdR, 5, 0xF00D);

    // All clients asynced -> finish
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    // First async client is disconnected on check of snapshot 4
    TS_ASSERT_EQUALS(4, client1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);

    // During checking of the next snapshot (5) we found, that the rest asynced on that step
    TS_ASSERT_EQUALS(5, client0->asyncStep);
    TS_ASSERT_EQUALS(5, clientR->asyncStep);

    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(3, gameResults.players.size());
    TS_ASSERT_EQUALS(55, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(56, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(57, gameResults.players[2].userid);
  }

  // Tests async handling, which occurs while reconnecting client applying world snapshot.
  // It also imitates the situation, which caused game server to crash (NUM_TASK).
  void test_AsyncOnClientReconnectAfterWorldApply4()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    StrongMT<test::MockClient> clientR3 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 0, client0, true);
    int clientId1 = AddClient(p, "test1", 1, client1, true);
    int clientId2 = AddClient(p, "test2", 2, client2, true);
    int clientId3 = AddClient(p, "test3", 3, client3, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientId3, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientId3, 1, 0xF00D);
    p->OnRejoinClient(2);
    int clientIdR2 = AddClient(p, "test2", 2, clientR2, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnFinishStep(clientId3, 2, 0xF00D);
    p->RequestWorldData(clientIdR2);  // Here we reserve clientIdR2 in snapshots
    p->Step();

    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->OnFinishStep(clientId3, 3, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    int worldDataStep = 4;
    Peered::WorldDataInfo worldDataInfo(worldDataStep, 1);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo); // Here we will unreserve and leave clientIdR2 from snapshot 4 only
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    // Now make few steps before async
    TS_ASSERT_EQUALS(6, client0->steps.size());
    TS_ASSERT_EQUALS(6, client1->steps.size());
    TS_ASSERT_EQUALS(6, client3->steps.size());
    TS_ASSERT_EQUALS(1, clientR2->steps.size());
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xF00D);
    p->OnFinishStep(clientId3, 4, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(7, client1->steps.size());
    TS_ASSERT_EQUALS(7, client3->steps.size());
    TS_ASSERT_EQUALS(2, clientR2->steps.size());
    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->OnFinishStep(clientId1, 5, 0xF00D);
    p->OnFinishStep(clientId3, 5, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(8, client1->steps.size());
    TS_ASSERT_EQUALS(8, client3->steps.size());
    TS_ASSERT_EQUALS(3, clientR2->steps.size());
    // Now we will async
    p->OnFinishStep(clientId0, 6, 0xF00D);
    p->OnFinishStep(clientId1, 6, 0xF00D);
    p->OnFinishStep(clientId3, 6, 0xBADF00D);
    p->Step();

    // And wait for reconnecting client to confirm step
    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(8, client1->steps.size());
    TS_ASSERT_EQUALS(8, client3->steps.size());
    TS_ASSERT_EQUALS(3, clientR2->steps.size());
    p->Step();

    // Other clients may disconnect
    client1->status = rpc::Disconnected;
    client3->status = rpc::Disconnected;
    p->Step();

    // And reconnect
    p->OnRejoinClient(1);
    p->OnRejoinClient(3);
    int clientIdR1 = AddClient(p, "test1", 1, clientR1, false);
    int clientIdR3 = AddClient(p, "test3", 3, clientR3, false);
    p->Step();

    // Here thay will reserve itself in snapshots
    p->RequestWorldData(clientIdR1);
    p->RequestWorldData(clientIdR3);
    p->Step();

    // But we are still waiting for clientIdR2
    p->OnClientReady(clientIdR2);
    TS_ASSERT_EQUALS(worldDataStep, clientR2->simulationStartStep);
    p->Step();

    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    // Now he disconnects and we are left with only one active client and 2 rejoiners without world applied
    clientR2->status = rpc::Disconnected;
    int stepResult = p->Step();
    // Because it is not posible to figure out what's going on with only one active client with CRC - we finish here
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, stepResult);

    // Async client is disconnected without reason, but with async
    TS_ASSERT_EQUALS(6, client0->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);

    // Reconnecting clients are disconnected with GameFinish and without async
    TS_ASSERT_EQUALS(-1, clientR1->asyncStep);
    TS_ASSERT_EQUALS(-1, clientR3->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, clientR1->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, clientR3->disconnectReason);

    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(4, gameResults.players.size());
    TS_ASSERT_EQUALS(0, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(1, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(2, gameResults.players[2].userid);
    // client2 was disconnected not by server, therefore he is a leaver
    TS_ASSERT_EQUALS(3, gameResults.players[3].userid);
  }

  void test_AsyncJustAfterClientReconnect()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    Peered::WorldDataInfo worldDataInfo(4, 1);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xF00D);
    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(7, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientR->steps.size());
    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->OnFinishStep(clientId1, 5, 0xBADF00D);
    p->OnFinishStep(clientIdR, 4, 0xF00D);
    p->OnFinishStep(clientIdR, 5, 0xF00D);

    // Only async client got the async info
    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    TS_ASSERT_EQUALS(5, client1->asyncStep);
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);
    p->Step();

    // Not asynced clients resume the game
    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(7, client1->steps.size());
    TS_ASSERT_EQUALS(3, clientR->steps.size());
    // Active*3, disconnected->connecting(+all statuses on world info)->active of reconnecting client, disconnected of async client
    TS_ASSERT_EQUALS(10, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(56, client0->clientStatuses[9].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByAsync, client0->clientStatuses[9].status);
    // Status of all clients, own ready, disconnected of async client
    TS_ASSERT_EQUALS(5, clientR->clientStatuses.size());
    TS_ASSERT_EQUALS(56, clientR->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByAsync, clientR->clientStatuses[4].status);
    // Client got the async, so no additioanal reason is sent
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);
  }

  // Async after one client finished its reconnect and before another client finish
  void test_AsyncAfterOneClientReconnectedBeforeAnotherReconnected()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnRejoinClient(56);
    p->OnRejoinClient(57);
    int clientIdR1 = AddClient(p, "test1", 56, clientR1, false);
    /*int clientIdR2 =*/ AddClient(p, "test2", 57, clientR2, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->RequestWorldData(clientIdR1);
    p->Step();

    p->OnFinishStep(clientId0, 3, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    Peered::WorldDataInfo worldDataInfo(4, 1);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnClientReady(clientIdR1);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(2, clientR1->steps.size());
    TS_ASSERT_EQUALS(0, clientR2->steps.size());

    // After reconnect "test1" start to send async crcs
    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->OnFinishStep(clientIdR1, 4, 0xBADF00D);
    p->OnFinishStep(clientIdR1, 5, 0xBADF00D);

    // Async clients are disconnected without reason, but with async
    TS_ASSERT_EQUALS(4, client0->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None , client0->disconnectReason);
    TS_ASSERT_EQUALS(4, clientR1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None , clientR1->disconnectReason);

    // All active clients dropped due to async and reconnecter is without world applied -> finish
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(3, gameResults.players.size());
    TS_ASSERT_EQUALS(55, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(56, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(57, gameResults.players[2].userid);

    // Reconnecting client is disconnected with GameFinish and without async
    TS_ASSERT_EQUALS(-1, clientR2->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished , clientR2->disconnectReason);
  }

  // Client is disconnected during session load and reconnects before it is started
  void test_ReconnectBeforeGameStart()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    client2->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    // No need for world transfer here, because the session wasn't started yet

    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientR->simulationStartStep);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);

    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientR->simulationStartStep);
    p->Step();

    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientR->simulationStartStep);
    // We do receive steps here, because statuses are sent, but no commands
    TS_ASSERT_EQUALS(2, client0->steps.size());

    TS_ASSERT_EQUALS(1, client0->steps[0].statuses.size());
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->steps[0].statuses[0].status);
    TS_ASSERT_EQUALS(0, client0->steps[0].commands.size());
    TS_ASSERT_EQUALS(1, client0->steps[1].statuses.size());
    TS_ASSERT_EQUALS(Peered::Connecting, client0->steps[1].statuses[0].status);
    TS_ASSERT_EQUALS(0, client0->steps[0].commands.size());

    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(1, clientR->steps.size()); // Own connecting status
    p->OnClientReady(clientIdR);

    TS_ASSERT_EQUALS(2, client0->simulationStartStep);
    TS_ASSERT_EQUALS(2, client1->simulationStartStep);
    TS_ASSERT_EQUALS(2, clientR->simulationStartStep);
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientR->steps.size());

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(client1->steps);
    CheckStepsConsistency(clientR->steps);
  }

  // Client is disconnected during session load, then he is reconnecting before 
  // it is started, getting disconnected and reconnecting again before the start
  void test_ReconnectTwiceBeforeGameStart()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    client2->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(57);
    AddClient(p, "test2", 57, clientR1, false);
    p->Step();

    // No need for world transfer here, because the session wasn't started yet

    clientR1->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(57);
    int clientIdR2 = AddClient(p, "test2", 57, clientR2, false);
    p->Step();

    // No need for world transfer here, because the session wasn't started yet

    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->Step();

    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientR2->simulationStartStep);
    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    p->OnClientReady(clientIdR2);

    TS_ASSERT_EQUALS(4, client0->simulationStartStep);
    TS_ASSERT_EQUALS(4, client1->simulationStartStep);
    TS_ASSERT_EQUALS(4, clientR2->simulationStartStep);
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientR2->steps.size());

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(client1->steps);
    CheckStepsConsistency(clientR2->steps);
  }

  // Two clients are reconnecting before session start
  void test_2ClientsReconnectBeforeGameStart()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    AddClient(p, "test1", 56, client1, false);
    AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    client2->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(57);
    int clientIdR1 = AddClient(p, "test2", 57, clientR1, false);
    p->Step();

    // No need for world transfer here, because the session wasn't started yet

    client1->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(56);
    int clientIdR2 = AddClient(p, "test1", 56, clientR2, false);
    p->Step();

    // No need for world transfer here, because the session wasn't started yet

    p->OnClientReady(clientId0);
    p->Step();

    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientR1->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientR2->simulationStartStep);
    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(3, clientR1->steps.size());
    TS_ASSERT_EQUALS(1, clientR2->steps.size());
    p->OnClientReady(clientIdR1);
    p->OnClientReady(clientIdR2);

    TS_ASSERT_EQUALS(4, client0->simulationStartStep);
    TS_ASSERT_EQUALS(4, clientR1->simulationStartStep);
    TS_ASSERT_EQUALS(4, clientR2->simulationStartStep);
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(4, clientR1->steps.size());
    TS_ASSERT_EQUALS(2, clientR2->steps.size());

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(clientR1->steps);
    CheckStepsConsistency(clientR2->steps);
  }

  // Two clients are disconnected, then one is reconnecting before session start na one - after
  void test_2ClientsDisconnect1ReconnectBeforeGameStart1After()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    AddClient(p, "test1", 56, client1, false);
    AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    client1->status = rpc::Disconnected;
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(57);
    int clientIdR1 = AddClient(p, "test2", 57, clientR1, false);
    p->Step();

    // No need for world transfer here, because the session wasn't started yet

    p->OnClientReady(clientId0);
    p->Step();

    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientR1->simulationStartStep);
    TS_ASSERT_EQUALS(2, client0->steps.size()); // 2 disconnects, 1 connecting
    TS_ASSERT_EQUALS(1, clientR1->steps.size()); // Own connecting
    p->OnClientReady(clientIdR1); // Here the session should start (all active clients are ready)
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(2, client0->simulationStartStep);
    TS_ASSERT_EQUALS(2, clientR1->simulationStartStep);
    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(3, clientR1->steps.size());
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientIdR1, 2, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR2 = AddClient(p, "test1", 56, clientR2, false);
    p->Step();

    TS_ASSERT_EQUALS(-1, clientR2->simulationStartStep);
    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(4, clientR1->steps.size());
    p->RequestWorldData(clientIdR2);
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientIdR1, 3, 0xF00D);
    p->Step();

    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientIdR1, 4, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    p->Step();

    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->OnFinishStep(clientIdR1, 5, 0xF00D);
    p->OnClientReady(clientIdR2);

    TS_ASSERT_EQUALS(3, clientR2->simulationStartStep);
    p->Step();

    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(7, clientR1->steps.size());
    TS_ASSERT_EQUALS(4, clientR2->steps.size());

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(clientR1->steps);
    CheckStepsConsistency(clientR2->steps);
  }

  void test_ReconnectDuringReconnectUsingSameWorldSnapshot()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR1 = AddClient(p, "test1", 56, clientR1, false);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId2, 2, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR2 = AddClient(p, "test2", 57, clientR2, false);
    p->RequestWorldData(clientIdR1);
    p->Step();

    TS_ASSERT_EQUALS(6, client0->steps.size());
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->RequestWorldData(clientIdR2);
    p->Step();

    // The second reconnecting client should get the same world data, so hybrid 
    // server will not request it again, as well as will not expect to receive it

    TS_ASSERT_EQUALS(7, client0->steps.size());
    p->OnFinishStep(clientId0, 5, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(6, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    p->Step();

    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(2, clientR1->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(2, clientR2->mockClientReconnect->worldDataParts.size());
    p->OnClientReady(clientIdR1);
    p->Step();

    TS_ASSERT_EQUALS(9, client0->steps.size());
    TS_ASSERT_EQUALS(2, clientR1->steps.size());
    TS_ASSERT_EQUALS(6, clientR1->simulationStartStep);
    p->OnClientReady(clientIdR2);
    p->Step();

    TS_ASSERT_EQUALS(10, client0->steps.size());
    TS_ASSERT_EQUALS(3, clientR1->steps.size());
    TS_ASSERT_EQUALS(3, clientR2->steps.size());
    TS_ASSERT_EQUALS(6, clientR2->simulationStartStep);

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(clientR1->steps);
    CheckStepsConsistency(clientR2->steps);
  }

  void test_ReconnectDuringReconnectDifferentWorldSnapshots()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR1 = AddClient(p, "test1", 56, clientR1, false);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId2, 2, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(5, client0->steps.size());
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR2 = AddClient(p, "test2", 57, clientR2, false);
    p->RequestWorldData(clientIdR1);
    p->Step();

    TS_ASSERT_EQUALS(6, client0->steps.size());
    p->OnFinishStep(clientId0, 4, 0xF00D);
    rpc::MemoryBlock worldDataPart11("part11", 6);
    rpc::MemoryBlock worldDataPart12("part12", 6);
    Peered::WorldDataInfo worldDataInfo1(5, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart11);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart12);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(2, clientR1->mockClientReconnect->worldDataParts.size()); // First reconnecting client received the data
    TS_ASSERT_EQUALS(0, clientR2->mockClientReconnect->worldDataParts.size()); // While second doen't (he still didn't ask for it)
    TS_ASSERT_SAME_DATA("part11", clientR1->mockClientReconnect->worldDataParts[0].memory, 6);
    TS_ASSERT_SAME_DATA("part12", clientR1->mockClientReconnect->worldDataParts[1].memory, 6);
    clientR1->mockClientReconnect->worldDataParts.clear(); // Clear it for the next checks
    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->RequestWorldData(clientIdR2);
    p->Step();

    TS_ASSERT_EQUALS(8, client0->steps.size());
    p->OnFinishStep(clientId0, 6, 0xF00D);
    rpc::MemoryBlock worldDataPart21("part21", 6);
    rpc::MemoryBlock worldDataPart22("part22", 6);
    Peered::WorldDataInfo worldDataInfo2(7, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo2);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart21);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart22);
    p->OnClientReady(clientIdR1);
    p->Step();

    TS_ASSERT_EQUALS(0, clientR1->mockClientReconnect->worldDataParts.size()); // This time the first client doesn't get the data - he already done
    TS_ASSERT_EQUALS(2, clientR2->mockClientReconnect->worldDataParts.size()); // But the second does receive dataparts
    TS_ASSERT_SAME_DATA("part21", clientR2->mockClientReconnect->worldDataParts[0].memory, 6);
    TS_ASSERT_SAME_DATA("part22", clientR2->mockClientReconnect->worldDataParts[1].memory, 6);
    TS_ASSERT_EQUALS(9, client0->steps.size());
    TS_ASSERT_EQUALS(3, clientR1->steps.size());
    TS_ASSERT_EQUALS(5, clientR1->simulationStartStep);
    p->OnClientReady(clientIdR2);
    p->Step();

    TS_ASSERT_EQUALS(10, client0->steps.size());
    TS_ASSERT_EQUALS(4, clientR1->steps.size());
    TS_ASSERT_EQUALS(2, clientR2->steps.size());
    TS_ASSERT_EQUALS(7, clientR2->simulationStartStep);

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(clientR1->steps);
    CheckStepsConsistency(clientR2->steps);
  }

  void test_ReconnectStatusSendToClients()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(4, client0->clientStatuses.size()); // Active*3, Disconnected
    TS_ASSERT_EQUALS(57, client0->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[3].status);
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(5, client0->clientStatuses.size()); // +connecting
    TS_ASSERT_EQUALS(57, client0->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::Connecting, client0->clientStatuses[4].status);
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    p->Step();

    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(9, client0->clientStatuses.size()); // +all statuses on reconnect + own active
    TS_ASSERT_EQUALS(57, client0->clientStatuses[8].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[8].status);
  }

  // Waiting for finish step before requesting world data 
  // TODO: is it ok? currently doesn't work, because server will choose the first one with highest step reported
  //void test_WaitForStepFinishBeforeWorldDataRequest()
  //{
  //  StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 0, 0, 0, 0, 0, 1, 0, 50);
  //  StrongMT<test::MockClient> client0 = new test::MockClient();
  //  StrongMT<test::MockClient> client1 = new test::MockClient();
  //  StrongMT<test::MockClient> client2 = new test::MockClient();
  //  StrongMT<test::MockClient> clientR = new test::MockClient();
  //  int clientId0 = AddClient(p, "test0", 55, client0, true);
  //  int clientId1 = AddClient(p, "test1", 56, client1, true);
  //  int clientId2 = AddClient(p, "test2", 57, client2, true);
  //  p->Step();
  //  p->Step();

  //  p->OnFinishStep(clientId0, 0, 0xF00D);
  //  p->OnFinishStep(clientId1, 0, 0xF00D);
  //  p->OnFinishStep(clientId2, 0, 0xF00D);
  //  client2->status = rpc::Disconnected;
  //  p->Step();

  //  p->OnFinishStep(clientId0, 1, 0xF00D);
  //  p->OnFinishStep(clientId1, 1, 0xF00D);
  //  int clientIdR = AddClient(p, "test2", 57, clientR, false);
  //  p->Step();

  //  p->RequestWorldData(clientIdR);
  //  p->Step();

  //  TS_ASSERT_EQUALS(false, client0->worldDataRequested); // We didn't reported OnFinishStep for previous step,
  //  TS_ASSERT_EQUALS(false, client1->worldDataRequested); // therefore none gets world data request here
  //  p->OnFinishStep(clientId0, 2, 0xF00D);
  //  p->OnFinishStep(clientId1, 2, 0xF00D);
  //  p->Step();

  //  TS_ASSERT_EQUALS(true, client0->worldDataRequested);
  //  TS_ASSERT_EQUALS(false, client1->worldDataRequested);
  //  rpc::MemoryBlock worldDataPart1("part1", 5);
  //  rpc::MemoryBlock worldDataPart2("part2", 5);
  //  Peered::WorldDataInfo worldDataInfo(2, 2);
  //  client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
  //  client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
  //  client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
  //  p->Step();

  //  p->OnClientReady(clientIdR);
  //  p->Step();

  //  TS_ASSERT_EQUALS(5, client0->steps.size());
  //  TS_ASSERT_EQUALS(5, client1->steps.size());
  //  TS_ASSERT_EQUALS(1, clientR->steps.size());
  //}

  // Receiving higher finish step not by the first client and requesting world data from that client
  void test_NotFirstClientFinishesHigherSteptBeforeReconnect()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 0, 0, 0, 0, 0, 1, 0, 50);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(false, client0->worldDataRequested); // The first client still did not reported step, but
    TS_ASSERT_EQUALS(true, client1->worldDataRequested);  // the socond client did, therefore he gets the request
    p->OnFinishStep(clientId0, 2, 0xF00D);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(3, 2);
    client1->serverReconnect->SendWorldDataInfo(clientId1, worldDataInfo);
    client1->serverReconnect->SendWorldDataPart(clientId1, worldDataPart1);
    client1->serverReconnect->SendWorldDataPart(clientId1, worldDataPart2);
    p->Step();

    TS_ASSERT_EQUALS(6, client0->steps.size());
    TS_ASSERT_EQUALS(6, client1->steps.size());
    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(7, client1->steps.size());
    TS_ASSERT_EQUALS(3, clientR->steps.size());
  }

  // Not receiving finish steps and then dropping rejoining client
  void test_NotReceivingFinishStepsDuringReconnect()
  {
    const int worldRequestTimeOut = 50;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                        0, 0, 0, 0, 0, 1, 0, worldRequestTimeOut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    /*int clientId0 =*/ AddClient(p, "test0", 55, client0, true);
    /*int clientId1 =*/ AddClient(p, "test1", 56, client1, true);
    /*int clientId2 =*/ AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->RequestWorldData(clientIdR);

    for (int i = 0; i < worldRequestTimeOut; ++i)
    {
      p->Step();

      TS_ASSERT_EQUALS(false, client0->worldDataRequested); // We didn't reported OnFinishStep for last step,
      TS_ASSERT_EQUALS(false, client1->worldDataRequested); // therefore none gets world data request here
      TS_ASSERT_EQUALS(5 + i, client0->steps.size());
      TS_ASSERT_EQUALS(5 + i, client1->steps.size());
    }

    p->Step();

    TS_ASSERT_EQUALS(5 + worldRequestTimeOut, client0->steps.size());
    TS_ASSERT_EQUALS(5 + worldRequestTimeOut, client1->steps.size());
    TS_ASSERT_EQUALS(false, client0->worldDataRequested); // We still didn't reported OnFinishStep for last step,
    TS_ASSERT_EQUALS(false, client1->worldDataRequested); // therefore still none gets world data request here
    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3, disconnected, connecting, disconnected
    TS_ASSERT_EQUALS(57, client0->clientStatuses[5].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[5].status); // Rejoiner is dropped, sorry
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);
  }

  // Not receiving world data from chosen client and rerequesting from another
  void test_NotReceivingWorldDataAndRerequestFromOtherClient()
  {
    const int worldRequestTimeOut = 50;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                        0, 0, 0, 0, 0, 1, 0, worldRequestTimeOut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);

    for (int i = 0; i < worldRequestTimeOut; ++i)
    {
      p->Step();
    }

    TS_ASSERT_EQUALS(true, client1->worldDataRequested); // Now the second got the request
    TS_ASSERT_EQUALS(5 + worldRequestTimeOut, client0->steps.size());
    TS_ASSERT_EQUALS(5 + worldRequestTimeOut, client1->steps.size());
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(3, 2);
    client1->serverReconnect->SendWorldDataInfo(clientId1, worldDataInfo);
    client1->serverReconnect->SendWorldDataPart(clientId1, worldDataPart1);
    client1->serverReconnect->SendWorldDataPart(clientId1, worldDataPart2);
    p->Step();

    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(7 + worldRequestTimeOut, client0->steps.size());
    TS_ASSERT_EQUALS(7 + worldRequestTimeOut, client1->steps.size());
    TS_ASSERT_EQUALS(3 + worldRequestTimeOut, clientR->steps.size());
  }

  // Not receiving all data parts from chosen client and rerequesting from another
  void test_NotReceivingAllPartsAndRerequestFromOtherClient()
  {
    const int worldRequestTimeOut = 50;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                        0, 0, 0, 0, 0, 1, 0, worldRequestTimeOut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo1(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1); // Send only one part of two

    for (int i = 0; i < worldRequestTimeOut; ++i)
    {
      p->Step();
    }

    TS_ASSERT_EQUALS(true, client1->worldDataRequested); // Now the second got the request
    TS_ASSERT_EQUALS(5 + worldRequestTimeOut, client0->steps.size());
    TS_ASSERT_EQUALS(5 + worldRequestTimeOut, client1->steps.size());
    Peered::WorldDataInfo worldDataInfo2(3, 2);
    client1->serverReconnect->SendWorldDataInfo(clientId1, worldDataInfo2);
    client1->serverReconnect->SendWorldDataPart(clientId1, worldDataPart1);
    client1->serverReconnect->SendWorldDataPart(clientId1, worldDataPart2);
    p->Step();

    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(7 + worldRequestTimeOut, client0->steps.size());
    TS_ASSERT_EQUALS(7 + worldRequestTimeOut, client1->steps.size());
    TS_ASSERT_EQUALS(3 + worldRequestTimeOut, clientR->steps.size());
  }

  // Ignoring of world data parts from one client, after rerequesting from another
  void test_IgnoreWorldDataFromFirtsAfterRerequestFromAnotherClient()
  {
    const int worldRequestTimeOut = 50;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                        0, 0, 0, 0, 0, 1, 0, worldRequestTimeOut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo1(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1); // Send only one part of two

    for (int i = 0; i < worldRequestTimeOut; ++i)
    {
      p->Step();
    }

    TS_ASSERT_EQUALS(true, client1->worldDataRequested); // Now the second got the request
    TS_ASSERT_EQUALS(5 + worldRequestTimeOut, client0->steps.size());
    TS_ASSERT_EQUALS(5 + worldRequestTimeOut, client1->steps.size());

    // Send the second part, while the server already requested from another client
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    p->Step();

    TS_ASSERT_EQUALS(0, clientR->mockClientReconnect->worldDataParts.size()); // Rejoiner does not receive data
    Peered::WorldDataInfo worldDataInfo2(3, 2);
    client1->serverReconnect->SendWorldDataInfo(clientId1, worldDataInfo2);
    client1->serverReconnect->SendWorldDataPart(clientId1, worldDataPart1); // Send from the second client
    client1->serverReconnect->SendWorldDataPart(clientId1, worldDataPart2);
    p->Step();

    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(8 + worldRequestTimeOut, client0->steps.size());
    TS_ASSERT_EQUALS(8 + worldRequestTimeOut, client1->steps.size());
    TS_ASSERT_EQUALS(4 + worldRequestTimeOut, clientR->steps.size());
  }

  // Not receiving data, rerequesting and not receiving again, until no clients to rerequest, then drop rejoiner
  void test_AllRerequestsWithoutResults()
  {
    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    data.sessionSettings.reconnectEnabled = true;
    data.sessionSettings.snapshotRequestTimeout = 50;
    objects.statisticsWrapper = statisticsWrapper;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);

    for (int i = 0; i < data.sessionSettings.snapshotRequestTimeout; ++i)
    {
      p->Step();
    }

    TS_ASSERT_EQUALS(true, client1->worldDataRequested); // Now the second got the request
    TS_ASSERT_EQUALS(5 + data.sessionSettings.snapshotRequestTimeout, client0->steps.size());
    TS_ASSERT_EQUALS(5 + data.sessionSettings.snapshotRequestTimeout, client1->steps.size());

    for (int i = 0; i < data.sessionSettings.snapshotRequestTimeout; ++i)
    {
      p->Step();
    }

    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3, disconnected, connecting, disconnected
    TS_ASSERT_EQUALS(57, client0->clientStatuses[5].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[5].status); // Rejoiner is dropped, sorry
    TS_ASSERT_EQUALS(5 + 2*data.sessionSettings.snapshotRequestTimeout, client0->steps.size()); // Other players resume ticking
    TS_ASSERT_EQUALS(5 + 2*data.sessionSettings.snapshotRequestTimeout, client1->steps.size());

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Normal, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::WorldRequestFailed, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(57, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(4 + 2*data.sessionSettings.snapshotRequestTimeout, statisticsWrapper->reconnects[0].currentStep);
  }

  // Not receiving client ready after sending world to it
  void test_NotReceivingClientReadyAfterSendingWorld()
  {
    const int snapshotApplyTimeout = 40;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                     0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 0, 0, snapshotApplyTimeout);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);

    TS_ASSERT_EQUALS(2, clientR->mockClientReconnect->worldDataParts.size());

    for (int i = 0; i < snapshotApplyTimeout-1; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(8, client0->clientStatuses.size());
    }
    TS_ASSERT_EQUALS(8, client0->clientStatuses.size()); // Still in
    p->Step();

    TS_ASSERT_EQUALS(9, client0->clientStatuses.size()); // +disconnected
    TS_ASSERT_EQUALS(57, client0->clientStatuses[8].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[8].status); // Rejoiner is dropped, sorry
    TS_ASSERT_EQUALS(5 + snapshotApplyTimeout, client0->steps.size()); // Other players resume ticking
    TS_ASSERT_EQUALS(5 + snapshotApplyTimeout, client1->steps.size());
  }

  // Receiving ready from reconnecting client before world data sent to it (with cheating reporting)
  void test_ReceivingReadyFromRejoinerBeforeSendingWorld()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    data.sessionSettings.reconnectEnabled = true;
    objects.statisticsWrapper = statisticsWrapper;
    objects.statsLink = link;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3, disconnected, connecting, disconnected
    TS_ASSERT_EQUALS(57, client0->clientStatuses[5].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, client0->clientStatuses[5].status); // Cheater is dropped
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);
    TS_ASSERT_EQUALS(1, link->cheaters.size()); // Cheat is reported
    TS_ASSERT_EQUALS(57, link->cheaters[0]);
    TS_ASSERT_EQUALS(5, client0->steps.size()); // Other players resume ticking
    TS_ASSERT_EQUALS(5, client1->steps.size());

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Normal, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::Cheated, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(57, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(4, statisticsWrapper->reconnects[0].currentStep);
  }

  // Simultaneous reconnect of two clients, when one client sends OnClientReady and another doesn't send
  void test_ReconnectOf2Clients1Ok2TimedOut()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    const int worldRequestTimeOut = 50;
    const int snapshotApplyTimeout = 40;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                      link, 0, 0, 0, 0, 1, 0, worldRequestTimeOut, 0, 
                                                        1024, 4096, true, 0, 0, snapshotApplyTimeout);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnRejoinClient(56);
    p->OnRejoinClient(57);
    int clientIdR1 = AddClient(p, "test1", 56, clientR1, false);
    int clientIdR2 = AddClient(p, "test2", 57, clientR2, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->RequestWorldData(clientIdR1);
    p->RequestWorldData(clientIdR2);
    p->Step();

    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    p->Step();

    TS_ASSERT_EQUALS(2, clientR1->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(2, clientR2->mockClientReconnect->worldDataParts.size());
    p->OnClientReady(clientIdR1);

    for (int i = 0; i < snapshotApplyTimeout; ++i)
    {
      p->Step();
    }

    // Active*3, disconnected*2, all statuses(3)*2, disconnected(timeout)
    TS_ASSERT_EQUALS(12, client0->clientStatuses.size());
    // First rejoiner is ok
    TS_ASSERT_EQUALS(56, client0->clientStatuses[10].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[10].status);
    // Second rejoiner didn't send ready, therefore he is dropped, sorry
    TS_ASSERT_EQUALS(57, client0->clientStatuses[11].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[11].status);
    TS_ASSERT_EQUALS(6 + snapshotApplyTimeout, client0->steps.size());
    TS_ASSERT_EQUALS(2 + snapshotApplyTimeout, clientR1->steps.size());
    p->Step();

    TS_ASSERT_EQUALS(7 + snapshotApplyTimeout, client0->steps.size());
    TS_ASSERT_EQUALS(3 + snapshotApplyTimeout, clientR1->steps.size());
  }

  // Simultaneous reconnect of two clients, when one client disconnects during world request, before all data parts sent
  void test_ReconnectOf2Clients1Ok2DisconnectsBeforeWorldSend()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    const int connectTimeOut = 40;
    const int worldRequestTimeOut = 50;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                      link, 0, 0, 0, connectTimeOut, 1, 0, worldRequestTimeOut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnRejoinClient(56);
    p->OnRejoinClient(57);
    int clientIdR1 = AddClient(p, "test1", 56, clientR1, false);
    int clientIdR2 = AddClient(p, "test2", 57, clientR2, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->RequestWorldData(clientIdR1);
    p->RequestWorldData(clientIdR2);
    p->Step();

    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    clientR2->status = rpc::Disconnected;
    p->Step();

    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    p->Step();

    // One should receive the data and the second (disconnected) shouldn't
    TS_ASSERT_EQUALS(2, clientR1->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(0, clientR2->mockClientReconnect->worldDataParts.size());
  }

  // Simultaneous reconnect of two clients, when both disconnect during world request, before all data parts sent.
  // After that one retries to reconnect and server should make new world request for it.
  void test_ReconnectCleanUpWorldRequestIfRequesterDisconnected()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    const int connectTimeOut = 40;
    const int worldRequestTimeOut = 50;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                      link, 0, 0, 0, connectTimeOut, 1, 0, worldRequestTimeOut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    StrongMT<test::MockClient> clientR11 = new test::MockClient();
    StrongMT<test::MockClient> clientR22 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnRejoinClient(56);
    p->OnRejoinClient(57);
    int clientIdR1 = AddClient(p, "test1", 56, clientR1, false);
    int clientIdR2 = AddClient(p, "test2", 57, clientR2, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->RequestWorldData(clientIdR1);
    p->RequestWorldData(clientIdR2);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    clientR1->status = rpc::Disconnected;
    clientR2->status = rpc::Disconnected;
    p->Step();

    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2); // Srever should just ignore this
    p->Step();

    // Both clients are disconnected and shouldn't receive data
    TS_ASSERT_EQUALS(0, clientR1->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(0, clientR2->mockClientReconnect->worldDataParts.size());

    // Now both clients retry to reconnect
    client0->worldDataRequested = false;
    p->OnRejoinClient(56);
    p->OnRejoinClient(57);
    int clientIdR11 = AddClient(p, "test1", 56, clientR11, false);
    int clientIdR22 = AddClient(p, "test2", 57, clientR22, false);
    p->Step();

    p->RequestWorldData(clientIdR11);
    p->RequestWorldData(clientIdR22);
    p->Step();

    // New request received by active client
    TS_ASSERT_EQUALS(true, client0->worldDataRequested);
    // Reconnecting clients don't receive any old data
    TS_ASSERT_EQUALS(0, clientR11->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(0, clientR22->mockClientReconnect->worldDataParts.size());

    // Send world data (just for test the old data is reused)
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);

    // Both clients receive the new data
    TS_ASSERT_EQUALS(2, clientR11->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(2, clientR22->mockClientReconnect->worldDataParts.size());
  }

  // Sending of user activity statistics in game results (not connected, 
  // connected and finished, connected and disconnected, total afk time)
  void test_ActivityStatisticsInGameResults()
  {
    const int connectionTimeout = 20;
    const int afkStepCount = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                    link, 0, afkStepCount, 0, connectionTimeout);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    //int clientId1 = AddClient(p, "test1", 56, client1, true); // Assume this client did not connected
    /*int clientId2 =*/ AddClient(p, "test2", 57, client2, true);

    // Make a connection timeout
    for (int i = 0; i < connectionTimeout; ++i)
    {
      p->Step();
    }
    //p->Step(); // In current implementation first step will be made on timeout

    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(1, client2->steps.size());
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(2, client0->steps.size());

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 55, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    p->SendCommand(clientId0, command0, true);

    // Make afk statistics for afkStepCount steps
    for (int i = 0; i < (afkStepCount<<1); ++i)
    {
      p->Step();
    }

    TS_ASSERT_EQUALS(22, client0->steps.size());
    p->SendCommand(clientId0, command0, true);

    // Make afk statistics for additional afkStepCount steps
    for (int i = 0; i < (afkStepCount<<1); ++i)
    {
      p->Step();
    }

    p->OnGameFinish(clientId0, 1, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    TS_ASSERT_EQUALS(3,link->clientStatistics.size());
    TS_ASSERT_EQUALS(55,link->clientStatistics[0].clientId);
    TS_ASSERT_EQUALS(Peered::EGameFinishClientState::FinishedGame,link->clientStatistics[0].clientState);
    TS_ASSERT_EQUALS(afkStepCount*2/10,link->clientStatistics[0].totalAfkSeconds);
    TS_ASSERT_EQUALS(56,link->clientStatistics[1].clientId);
    TS_ASSERT_EQUALS(Peered::EGameFinishClientState::NotConnected,link->clientStatistics[1].clientState);
    TS_ASSERT_EQUALS(0,link->clientStatistics[1].totalAfkSeconds);
    TS_ASSERT_EQUALS(57,link->clientStatistics[2].clientId);
    TS_ASSERT_EQUALS(Peered::EGameFinishClientState::Disconnected,link->clientStatistics[2].clientState);
    TS_ASSERT_EQUALS(0,link->clientStatistics[2].totalAfkSeconds);
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  // All clients should receive notification about reconnect, so they will be able to update the UI or whatever
  void test_ReconnectNotification()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(0, client0->rejoinClientIds.size());
    TS_ASSERT_EQUALS(0, client1->rejoinClientIds.size());
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnRejoinClient(57);
    AddClient(p, "test2", 57, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(1, client0->rejoinClientIds.size());
    TS_ASSERT_EQUALS(1, client1->rejoinClientIds.size());
    TS_ASSERT_EQUALS(57, client0->rejoinClientIds[0]);
    TS_ASSERT_EQUALS(57, client1->rejoinClientIds[0]);
  }

  void test_ReconnectWhileNotAllowedToReconnect()
  {
    Peered::SchedulerData data;
    data.sessionSettings.reconnectEnabled = false;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    objects.statisticsWrapper = statisticsWrapper;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR = AddClient(p, "test1", 56, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(0, client0->rejoinClientIds.size());
    TS_ASSERT_EQUALS(-1, clientIdR);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Normal, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::Disabled, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(56, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(4, statisticsWrapper->reconnects[0].currentStep);
  }

  void test_ReconnectOfDisconnectedByCheatAttempt()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true); // First client ready here
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnClientReady(clientId1); // Second client ready => cheat
    p->Step();

    TS_ASSERT_EQUALS(1, link->cheaters.size());
    TS_ASSERT_EQUALS(56, link->cheaters[0]);
    TS_ASSERT_EQUALS(3, client0->clientStatuses.size());  // Active*2, cheat
    TS_ASSERT_EQUALS(56, client0->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, client0->clientStatuses[2].status);
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR = AddClient(p, "test1", 56, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(0, client0->rejoinClientIds.size());
    TS_ASSERT_EQUALS(-1, clientIdR);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);
  }

  // This test runs 3 clients, 1 - sends commands every step, 2 - reconnects and doesn't send, 3 - doesn't send commands
  // Expected result: client 1 and reconnecting client are ok, while client 3 will be kicked on afk
  // After that, we will try to reconnect kicked client and check that both aren't kicked on start
  void test_ReconnectNotAffectedByAfkTimer()
  {
    int afkStepsCount = 10;
    int afkStepsDisconnectCount = 20;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                    link, 0, afkStepsCount, 0, 0, 1, 0, 0, afkStepsDisconnectCount);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    /*int clientId1 =*/ AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(56);
    int clientIdR1 = AddClient(p, "test1", 56, clientR1, false);
    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 55, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);

    for (int i = 0; i < afkStepsCount; ++i)
    {
      p->OnFinishStep(clientId0, i+1, 0xF00D);
      p->SendCommand(clientId0, command0, true);  // Client 0 sends command every step to prevent afk
      p->OnFinishStep(clientId2, i+1, 0xF00D);
      p->Step();
    }

    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR1->disconnectReason);
    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3, disconnect and connecting of client 1, away of client 2
    TS_ASSERT_EQUALS(56, client0->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[3].status);
    TS_ASSERT_EQUALS(56, client0->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::Connecting, client0->clientStatuses[4].status);
    TS_ASSERT_EQUALS(57, client0->clientStatuses[5].clientId);
    TS_ASSERT_EQUALS(Peered::Away, client0->clientStatuses[5].status);

    for (int i = 0; i < afkStepsDisconnectCount; ++i)
    {
      p->OnFinishStep(clientId0, i+afkStepsCount+1, 0xF00D);
      p->SendCommand(clientId0, command0, true);  // Client 0 sends command every step to prevent afk
      p->OnFinishStep(clientId2, i+afkStepsCount+1, 0xF00D);
      p->Step();
    }

    // Rejoiner isn't disconnected by afk timer
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR1->disconnectReason);
    // While active client 2 is disconnected, because he didn't send commands
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ClientAway, client2->disconnectReason);
    TS_ASSERT_EQUALS(7, client0->clientStatuses.size()); // + disconnect of client 2
    TS_ASSERT_EQUALS(57, client0->clientStatuses[6].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[6].status);

    // Now try to reconnect client 0
    p->OnRejoinClient(57);
    int clientIdR2 = AddClient(p, "test2", 57, clientR2, false);
    p->RequestWorldData(clientIdR1);
    p->RequestWorldData(clientIdR2);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(afkStepsDisconnectCount+afkStepsCount+1, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);

    // Check that both got the world data
    TS_ASSERT_EQUALS(2, clientR1->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(2, clientR2->mockClientReconnect->worldDataParts.size());
    p->OnClientReady(clientIdR1);
    p->OnClientReady(clientIdR2);
    p->Step();

    // Both are not disconnected by afk on start
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR1->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR2->disconnectReason);
  }

  // This test runs 3 clients, 1 - confirms every step, 2 - reconnects and doesn't confirm, 3 - doesn't confirm steps
  // Expected result: client 1 and reconnecting client are ok, while client 3 will be kicked due to disconnection gap limit
  // After that, we will try to reconnect kicked client and check that both aren't kicked on start
  void test_ReconnectNotAffectedByDisconnectionGap()
  {
    int disconnectionGap = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                    link, 0, 0, disconnectionGap);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    /*int clientId1 =*/ AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(56);
    int clientIdR1 = AddClient(p, "test1", 56, clientR1, false);
    rpc::MemoryBlock command0("cmd0", 4);

    for (int i = 0; i < disconnectionGap; ++i)
    {
      // Client 0 confirms every step to prevent disconnection, client 
      p->OnFinishStep(clientId0, i+1, 0xF00D);
      p->Step();
    }

    // Rejoiner isn't disconnected due to disconnection gap
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR1->disconnectReason);
    // While active client 2 is disconnected, because he didn't confirmed steps
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ClientPerfomance, client2->disconnectReason);
    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3, disconnect and connecting of client 1, disconnect of client 2
    TS_ASSERT_EQUALS(56, client0->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[3].status);
    TS_ASSERT_EQUALS(56, client0->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::Connecting, client0->clientStatuses[4].status);
    TS_ASSERT_EQUALS(57, client0->clientStatuses[5].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[5].status);

    // Now try to reconnect client 0
    p->OnRejoinClient(57);
    int clientIdR2 = AddClient(p, "test2", 57, clientR2, false);
    p->RequestWorldData(clientIdR1);
    p->RequestWorldData(clientIdR2);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);
    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(disconnectionGap+1, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);

    // Check that both got the world data
    TS_ASSERT_EQUALS(2, clientR1->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(2, clientR2->mockClientReconnect->worldDataParts.size());
    p->OnClientReady(clientIdR1);
    p->OnClientReady(clientIdR2);
    p->Step();

    // Both are not disconnected due to disconnection gap on start
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR1->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR2->disconnectReason);
  }

  // This test imitates the situation form NUM_TASK
  void test_ProperStartFromStepByTimeout()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2400, 0, FillClients(55, 56, 57), 
                                                      link, 0, 600, 300, 600, 1, 600, 300, 3000, 1024, 4096, true);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    p->Step();
    int clientIndex0 = AddClient(p, "test1", 55, client0, false);
    char commandData0[15];
    test::FormatCommand(&commandData0, 55, "loadcmd");
    rpc::MemoryBlock command0(commandData0, 15);
    p->SendCommand(clientIndex0, command0, true);
    p->Step();
    int clientIndex1 = AddClient(p, "test2", 56, client1, false);
    p->Step();
    p->OnClientReady(clientIndex0);
    p->Step();
    p->OnClientReady(clientIndex1);
    p->Step();
    int clientIndex2 = AddClient(p, "test3", 57, client2, false);
    p->Step();
    p->Step();

    char commandData1[15];
    test::FormatCommand(&commandData1, 56, "loadcmd");
    rpc::MemoryBlock command1(commandData1, 15);
    char commandData2[15];
    test::FormatCommand(&commandData2, 57, "loadcmd");
    rpc::MemoryBlock command2(commandData2, 15);

    for (int i=0; i<30; ++i)
    {
      p->SendCommand(clientIndex0, command0, true);
      p->SendCommand(clientIndex1, command1, true);
      if (i % 100 == 0)
      {
        p->SendCommand(clientIndex2, command2, true);
      }
      p->Step();
    }

    client2->status = rpc::Disconnected;
    p->SendCommand(clientIndex0, command0, true);
    p->SendCommand(clientIndex1, command1, true);
    p->Step();

    TS_ASSERT_EQUALS(32, client0->simulationStartStep );
    TS_ASSERT_EQUALS(32, client1->simulationStartStep );

    TS_ASSERT_EQUALS(33, client0->steps.size());
    TS_ASSERT_EQUALS(32, client1->steps.size());

    for (int i=0; i<30; ++i)
    {
      string cmd( NStr::StrFmt("playcmd%04d", i));
      const int commandSize = 19;
      char commandData0[commandSize];
      char commandData1[commandSize];
      test::FormatCommand(&commandData0, 55, cmd.c_str());
      test::FormatCommand(&commandData1, 56, cmd.c_str());
      rpc::MemoryBlock command0(commandData0, commandSize);
      rpc::MemoryBlock command1(commandData1, commandSize);
      p->SendCommand(clientIndex0, command0, true);
      p->SendCommand(clientIndex1, command1, true);
      p->Step();
      TS_ASSERT_EQUALS(33+i+1, client0->steps.size());
      TS_ASSERT_EQUALS(32+i+1, client1->steps.size());
      TS_ASSERT_EQUALS(2, client0->steps[33+i].commands.size());
      TS_ASSERT_EQUALS(2, client1->steps[32+i].commands.size());
      TS_ASSERT_SAME_DATA(commandData0, client0->steps[33+i].commands[0].memory, commandSize);
      TS_ASSERT_SAME_DATA(commandData1, client0->steps[33+i].commands[1].memory, commandSize);
      TS_ASSERT_SAME_DATA(commandData0, client1->steps[32+i].commands[0].memory, commandSize);
      TS_ASSERT_SAME_DATA(commandData1, client1->steps[32+i].commands[1].memory, commandSize);
      p->OnFinishStep(clientIndex1, 32+i, 0xF00D);
      p->OnFinishStep(clientIndex2, 32+i, 0xF00D);
    }

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(client1->steps);

    TS_ASSERT_EQUALS(63, client0->steps.size());
    TS_ASSERT_EQUALS(62, client1->steps.size());
  }

  // Tests sending of disconnected clients status on session start. Clients, which came to the server after another 
  // client already disconnected, should receive the status on start. Clients, which ware on the server at the disconnection 
  // time, will receive the status twice. Game client should be smart enough to ignore it.
  void test_SendDisconnectedClientsStatusOnSessionStart()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    /*int clientId1 =*/ AddClient(p, "test1", 56, client1, false);
    p->Step();
    client1->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(1, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(56, client0->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[0].status);

    int clientId2 = AddClient(p, "test2", 57, client2, false);
    p->Step();

    TS_ASSERT_EQUALS(0, client2->clientStatuses.size());

    p->OnClientReady(clientId0);
    p->OnClientReady(clientId2);

    p->Step();

    TS_ASSERT_EQUALS(3, client2->clientStatuses.size()); // All clients statuses
    TS_ASSERT_EQUALS(56, client2->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client2->clientStatuses[2].status);
    TS_ASSERT_EQUALS(4, client0->clientStatuses.size()); // Disconnect + all clients statuses
    TS_ASSERT_EQUALS(56, client0->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[0].status);
    TS_ASSERT_EQUALS(56, client0->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client0->clientStatuses[3].status);
  }

  // Tests disconnect due to loading timeout. Loading is a time between adding client and its ready report.
  void test_ClientLoadingTimeout()
  {
    const int loadTimeout = 200;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1),
                                                     0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 0, loadTimeout);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, false);
                       AddClient(p, "test1", 1, client1, false);

    for (int i = 0; i < loadTimeout-1; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
      TS_ASSERT_EQUALS(0, client0->clientStatuses.size());
    }

    p->OnClientReady(clientIndex0);
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(0, client0->clientStatuses.size());

    p->Step();
    TS_ASSERT_EQUALS(1, client0->simulationStartStep);
    // x1 Active of client0, x2 disconnected by server of client1 (from step and from start)
    TS_ASSERT_EQUALS(3, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(1, client0->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(1, client0->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[0].status);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[2].status);
  }

  // Tests disconnect of reconnecting client due to loading timeout. 
  // Reconnecting client here will start loading, but won't report ready state and therefore kicked.
  void test_ClientLoadingTimeoutOnReconnect()
  {
    const int loadTimeout = 200;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1),
                                                     0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 0, loadTimeout);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();

    AddClient(p, "test0", 0, client0, true);
    AddClient(p, "test1", 1, client1, true);
    p->Step();

    client1->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(1);
    AddClient(p, "test1", 1, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->clientStatuses.size());  // Active*2, disconnected, connecting
    TS_ASSERT_EQUALS(1, client0->clientStatuses[2].clientId);

    for (int i = 0; i < loadTimeout-1; ++i)
    {
      TS_ASSERT_EQUALS(4, client0->clientStatuses.size());
      p->Step();
    }

    TS_ASSERT_EQUALS(5, client0->clientStatuses.size()); // + disconnect by timeout
    TS_ASSERT_EQUALS(1, client0->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[4].status);
  }

  // Tests simultaneous reconnect and disconnect of one reconnecting client due to loading timeout. 
  // Reconnecting client here will start loading, but won't report ready state and therefore kicked.
  // The seconnd reconnecting client should finish its reconnect just fine.
  void test_OneClientLoadingTimeoutOnReconnectOf2Clients()
  {
    const int loadTimeout = 200;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2),
                                                     0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 0, loadTimeout);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR0 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();

                       AddClient(p, "test0", 0, client0, true);
                       AddClient(p, "test1", 1, client1, true);
    int clientIndex2 = AddClient(p, "test2", 2, client2, true);
    p->Step();

    client0->status = rpc::Disconnected;
    client1->status = rpc::Disconnected;
    p->Step();

    p->OnRejoinClient(0);
    p->OnRejoinClient(1);
    int clientIndexR0 = AddClient(p, "test0", 0, clientR0, false);
                        AddClient(p, "test1", 1, clientR1, false);
    p->Step();

    TS_ASSERT_EQUALS(7, client2->clientStatuses.size());  // Active*3, disconnected*2, connecting*2 of both reconnecting clients

    p->RequestWorldData(clientIndexR0);
    p->OnFinishStep(clientIndex2, 0, 0xF00D);
    p->Step();

    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(1, 2);
    client2->serverReconnect->SendWorldDataInfo(clientIndex2, worldDataInfo);
    client2->serverReconnect->SendWorldDataPart(clientIndex2, worldDataPart1);
    client2->serverReconnect->SendWorldDataPart(clientIndex2, worldDataPart2);
    p->Step();

    for (int i = 0; i < loadTimeout-3; ++i)
    {
      TS_ASSERT_EQUALS(10, client2->clientStatuses.size());
      p->Step();
    }

    // The first reconnecting client ok
    p->OnClientReady(clientIndexR0);
    p->Step();

    TS_ASSERT_EQUALS(12, client2->clientStatuses.size());
    TS_ASSERT_EQUALS(1, client2->clientStatuses[10].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client2->clientStatuses[10].status);
    TS_ASSERT_EQUALS(0, client2->clientStatuses[11].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client2->clientStatuses[11].status);
  }

  // Tests, that async is sent once and not repeatedly, after each client disconnect.
  // In this case, the async information is completed in the OnFinishStep call.
  void test_AsyncSendingOnceFromOnFinishStep()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, true);
    int clientIndex1 = AddClient(p, "test1", 1, client1, true);
    int clientIndex2 = AddClient(p, "test2", 2, client2, true);
    p->Step();

    p->OnFinishStep(clientIndex0, 0, 0xF00D);
    p->OnFinishStep(clientIndex1, 0, 0xF00D);
    p->OnFinishStep(clientIndex2, 0, 0xF00D);
    p->Step();

    p->OnFinishStep(clientIndex0, 1, 0xF00D);
    p->OnFinishStep(clientIndex1, 1, 0xF00DBAD);
    p->OnFinishStep(clientIndex2, 1, 0xBADF00D);

    // All clients receive async info
    TS_ASSERT_EQUALS(1, client0->asyncStep);
    TS_ASSERT_EQUALS(1, client1->asyncStep);
    TS_ASSERT_EQUALS(1, client2->asyncStep);

    // And they receive it once
    TS_ASSERT_EQUALS(1, client0->asyncCount);
    TS_ASSERT_EQUALS(1, client1->asyncCount);
    TS_ASSERT_EQUALS(1, client2->asyncCount);

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  // Tests, that async is sent once and not repeatedly, after each client disconnect.
  // In this case, the async information is completed only after disconnect of client,
  // which did not reported finish of the async step.
  void test_AsyncSendingOnceFromClientsCheck()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, true);
    int clientIndex1 = AddClient(p, "test1", 1, client1, true);
    int clientIndex2 = AddClient(p, "test2", 2, client2, true);
    p->Step();

    p->OnFinishStep(clientIndex0, 0, 0xF00D);
    p->OnFinishStep(clientIndex1, 0, 0xF00D);
    p->OnFinishStep(clientIndex2, 0, 0xF00D);
    p->Step();

    // Only two clients reported this step and there is async detection
    p->OnFinishStep(clientIndex0, 1, 0xF00D);
    p->OnFinishStep(clientIndex2, 1, 0xBADF00D);

    // Clients do not receive async info
    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    TS_ASSERT_EQUALS(-1, client1->asyncStep);
    TS_ASSERT_EQUALS(-1, client2->asyncStep);

    // Here we disconnect the client, which did not reported 
    // async step and the async info should go to the clients.
    client1->status = rpc::Disconnected;

    // In the next Step() call the clients are checked, disconnect is detected, async is sent and game is finished
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    // Async clients received the info, while disconnected client shouldn't get it
    TS_ASSERT_EQUALS(1, client0->asyncStep);
    TS_ASSERT_EQUALS(-1, client1->asyncStep);
    TS_ASSERT_EQUALS(1, client2->asyncStep);

    // Async clients received the info only once and disconnected client didn't receive at all
    TS_ASSERT_EQUALS(1, client0->asyncCount);
    TS_ASSERT_EQUALS(0, client1->asyncCount);
    TS_ASSERT_EQUALS(1, client2->asyncCount);
  }

  // Tests, that async is sent on the hybrid link
  void test_AsyncSendingOnHybridLink()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test0", 0, client0, true);
    int clientIndex1 = AddClient(p, "test1", 1, client1, true);
    int clientIndex2 = AddClient(p, "test2", 2, client2, true);
    p->Step();

    p->OnFinishStep(clientIndex0, 0, 0xF00D);
    p->OnFinishStep(clientIndex1, 0, 0xF00D);
    p->OnFinishStep(clientIndex2, 0, 0xF00D);
    p->Step();

    // Make a "total async" to get it to game finish
    p->OnFinishStep(clientIndex0, 1, 0xF00D);
    p->OnFinishStep(clientIndex1, 1, 0xF00DBAD);
    p->OnFinishStep(clientIndex2, 1, 0xBADF00D);

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(3, gameResults.players.size());
    TS_ASSERT_EQUALS(0, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(1, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(2, gameResults.players[2].userid);
  }

  // This test will create sessions with different combinations of clients count (from 1x1 to 5x5)
  // and simultaneous asyncs count (from 1 to clients count). If most clients have same crc - only
  // async clients should be kicked from session. Otherwise whole session is ended. "Most" here is
  // the amount, which is always more than half (calculated by (clientsCount>>1) + 1).
  void test_AsyncsAllCombinations()
  {
    for (int clientsCount = 2; clientsCount <= 10; ++clientsCount)
    {
      for (int asyncsCount = 1; asyncsCount <= clientsCount; ++asyncsCount)
      {
        StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
        nstl::vector<Peered::ClientInfo> * clientIds = FillClientsAscending(clientsCount);
        StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, clientIds, link);
        nstl::vector<StrongMT<test::MockClient>> clients;
        nstl::vector<int> clientIndexes;
        clients.resize(clientsCount);
        clientIndexes.resize(clientsCount);

        for (int i = 0; i < clientsCount; ++i)
        {
          clients[i] = new test::MockClient();
          clientIndexes[i] = AddClient(p, NStr::StrFmt("test%d", i), (*clientIds)[i].clientId, clients[i], true);
        }
        p->Step();

        // Report sync finish steps
        for (int i = 0; i < clientsCount - asyncsCount; ++i)
        {
          p->OnFinishStep(clientIndexes[i], 0, 0xF00D);
          TS_ASSERT_EQUALS(1, clients[i]->steps.size());
        }

        // Report async finish steps
        for (int i = clientsCount - asyncsCount; i < clientsCount; ++i)
        {
          p->OnFinishStep(clientIndexes[i], 0, rand());
          TS_ASSERT_EQUALS(1, clients[i]->steps.size());
        }

        if ((clientsCount>>1) + 1 <= clientsCount - asyncsCount)  // Check if most clients are sync or async
        {
          TS_ASSERT_EQUALS(100, p->Step());

          // Here we have several async clients kicked, so only they receive the async, while others resume playing
          for (int i = 0; i < clientsCount - asyncsCount; ++i)
          {
            // Sync clients
            TS_ASSERT_EQUALS(-1, clients[i]->asyncStep);
            TS_ASSERT_EQUALS(2, clients[i]->steps.size());
          }
          for (int i = clientsCount - asyncsCount; i < clientsCount; ++i)
          {
            // Async clients
            TS_ASSERT_EQUALS(0, clients[i]->asyncStep);
            TS_ASSERT_EQUALS(1, clients[i]->steps.size());
          }
        }
        else
        {
          // Game is finished
          TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
          // Async is sent on the link
          TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
          const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
          TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
          TS_ASSERT_EQUALS(clientsCount, gameResults.players.size());
          // All clients received the async and none is reported as leaver
          for (int i = 0; i < clientsCount; ++i)
          {
            TS_ASSERT_EQUALS(i, gameResults.players[i].userid);
            TS_ASSERT_EQUALS(0, clients[i]->asyncStep);
          }
        }
      }
    }
  }

  // Tests waiting for async handling finish before requesting world.
  // Here we will resume game after async and kicking one async client.
  void test_ReconnectWorldRequestNotProcessedWhileHandlingAsync1()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 0, client0, true);
    int clientId1 = AddClient(p, "test1", 1, client1, true);
    int clientId2 = AddClient(p, "test2", 2, client2, true);
    int clientId3 = AddClient(p, "test3", 3, client3, true);
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientId3, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientId3, 1, 0xF00D);
    p->OnRejoinClient(2);
    int clientIdR = AddClient(p, "test2", 2, clientR, false);
    p->Step();

    // Request world and async at the same time, but one client didn't send crc, so we will wait in Blocked state
    p->RequestWorldData(clientIdR);
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xBADF00D);

    // Make few steps while in Blocked state
    for (int i = 0; i < 20; ++i)
    {
      p->Step();
      // World request is not processed
      TS_ASSERT_EQUALS(false, client0->worldDataRequested);
      TS_ASSERT_EQUALS(false, client1->worldDataRequested);
      TS_ASSERT_EQUALS(false, clientR->worldDataRequested);
      TS_ASSERT_EQUALS(false, client3->worldDataRequested);
    }

    // Finally report crc
    p->OnFinishStep(clientId3, 2, 0xF00D);

    // Only one client asynced, so he is kicked
    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    TS_ASSERT_EQUALS( 2, client1->asyncStep);
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);
    TS_ASSERT_EQUALS(-1, client3->asyncStep);
    p->Step();

    // World request is done
    TS_ASSERT_EQUALS( true, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    TS_ASSERT_EQUALS(false, client3->worldDataRequested);
  }

  // Tests waiting for async handling finish before requesting world.
  // Here the game will be finished due to async that can't be resolved by kicking specified clients.
  void test_ReconnectWorldRequestNotProcessedWhileHandlingAsync2()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 0, client0, true);
    int clientId1 = AddClient(p, "test1", 1, client1, true);
    int clientId2 = AddClient(p, "test2", 2, client2, true);
    int clientId3 = AddClient(p, "test3", 3, client3, true);
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientId3, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientId3, 1, 0xF00D);
    p->OnRejoinClient(2);
    int clientIdR = AddClient(p, "test2", 2, clientR, false);
    p->Step();

    // Request world and async at the same time, but one client didn't send crc, so we will wait in Blocked state
    p->RequestWorldData(clientIdR);
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xBADF00D);

    // Make few steps while in Blocked state
    for (int i = 0; i < 20; ++i)
    {
      p->Step();
      // World request is not processed
      TS_ASSERT_EQUALS(false, client0->worldDataRequested);
      TS_ASSERT_EQUALS(false, client1->worldDataRequested);
      TS_ASSERT_EQUALS(false, clientR->worldDataRequested);
      TS_ASSERT_EQUALS(false, client3->worldDataRequested);
    }

    // Finally report crc which async too
    p->OnFinishStep(clientId3, 2, 0xF00DBAD);

    // All client asynced, so they all are kicked, exept for the reconnecter
    TS_ASSERT_EQUALS( 2, client0->asyncStep);
    TS_ASSERT_EQUALS( 2, client1->asyncStep);
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);
    TS_ASSERT_EQUALS( 2, client3->asyncStep);
    
    // All active clients dropped due to async and reconnecter is without world applied -> finish
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(4, gameResults.players.size());
    TS_ASSERT_EQUALS(0, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(1, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(2, gameResults.players[2].userid);
    TS_ASSERT_EQUALS(3, gameResults.players[3].userid);

    // Reconnecting client is disconnected with GameFinish
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished , clientR->disconnectReason);

    // And, of course, world request isn't done
    TS_ASSERT_EQUALS(false, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    TS_ASSERT_EQUALS(false, clientR->worldDataRequested);
    TS_ASSERT_EQUALS(false, client3->worldDataRequested);
  }

  // Tests waiting for async handling finish before requesting world.
  // Here the game will be finished due to async that can't be resolved by kicking specified clients.
  void test_ReconnectWorldRequestNotProcessedWhileHandlingAsync3()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 0, client0, true);
    int clientId1 = AddClient(p, "test1", 1, client1, true);
    int clientId2 = AddClient(p, "test2", 2, client2, true);
    int clientId3 = AddClient(p, "test3", 3, client3, true);
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientId3, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientId3, 1, 0xF00D);
    p->OnRejoinClient(2);
    int clientIdR = AddClient(p, "test2", 2, clientR, false);
    p->Step();

    // Request world and async at the same time, but one client didn't send crc, so we will wait in Blocked state
    p->RequestWorldData(clientIdR);
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xBADF00D);

    // Make few steps while in Blocked state
    for (int i = 0; i < 20; ++i)
    {
      p->Step();
      // World request is not processed
      TS_ASSERT_EQUALS(false, client0->worldDataRequested);
      TS_ASSERT_EQUALS(false, client1->worldDataRequested);
      TS_ASSERT_EQUALS(false, clientR->worldDataRequested);
      TS_ASSERT_EQUALS(false, client3->worldDataRequested);
    }

    // Now lets disconnect the client we are waiting for
    client3->status = rpc::Disconnected;

    // Here we've got an async, that can't be resolved (1x1), so we will finish the game
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    // All client asynced, so they all are kicked, exept for the reconnecter
    TS_ASSERT_EQUALS( 2, client0->asyncStep);
    TS_ASSERT_EQUALS( 2, client1->asyncStep);
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);
    
    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(4, gameResults.players.size());
    TS_ASSERT_EQUALS(0, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(1, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(2, gameResults.players[2].userid);
    TS_ASSERT_EQUALS(3, gameResults.players[3].userid);
    // client3 was disconnected not by server, therefore he is a leaver

    // Reconnecting client is disconnected with GameFinish
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished , clientR->disconnectReason);

    // And, of course, world request isn't done
    TS_ASSERT_EQUALS(false, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    TS_ASSERT_EQUALS(false, clientR->worldDataRequested);
  }

  // Tests not receiving world data from chosen client on reconnect to 1x1 session. This test simulates possible problem,
  // when the world request is sent second time, even after reconnecting client already kicked by timout of the first request.
  void test_NotReceivingWorldDataOnReconnectTo1x1Session()
  {
    const int worldRequestTimeOut = 50;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), 
                                                        0, 0, 0, 0, 0, 1, 0, worldRequestTimeOut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdR = AddClient(p, "test1", 56, clientR, false);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, clientR->worldDataRequested);

    client0->worldDataRequested = false;

    for (int i = 0; i < worldRequestTimeOut; ++i)
    {
      p->OnFinishStep(clientId0, 3 + i, 0xF00D);
      p->Step();
      TS_ASSERT_EQUALS(false, client0->worldDataRequested);
      TS_ASSERT_EQUALS(false, clientR->worldDataRequested);
    }

    p->OnFinishStep(clientId0, 3 + worldRequestTimeOut, 0xF00D);

    TS_ASSERT_EQUALS(5, client0->clientStatuses.size()); // Active*2, disconnected, connecting, disconnected
    TS_ASSERT_EQUALS(56, client0->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, client0->clientStatuses[4].status); // Rejoiner is dropped, sorry
    TS_ASSERT_EQUALS(5 + worldRequestTimeOut, client0->steps.size()); // Other players resume ticking
    TS_ASSERT_EQUALS(0, clientR->steps.size());
    p->Step();

    // Additional step doesn't lead to request too
    TS_ASSERT_EQUALS(false, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, clientR->worldDataRequested);
  }

  void test_ConfigSnapshotSendPerStep()
  {
    const int snapshotSendPerStep = 100;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1),
                                                     0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 0, 0, 0, snapshotSendPerStep);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    AddClient(p, "test0", 0, client0, true);
    AddClient(p, "test1", 1, client1, true);
    TS_ASSERT_EQUALS(snapshotSendPerStep, client0->snapshotSendPerStep);
    TS_ASSERT_EQUALS(snapshotSendPerStep, client1->snapshotSendPerStep);
  }

  void test_ConfigMinigameEnabled()
  {
    StrongMT<Peered::CommandsScheduler> p0 = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(1),
                                                     0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, 
                                                     true, 0, 0, 0, 64000, false);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    client0->minigameEnabled = true;
    AddClient(p0, "test0", 0, client0, true);
    TS_ASSERT_EQUALS(false, client0->minigameEnabled);

    StrongMT<Peered::CommandsScheduler> p1 = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(1),
                                                     0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, 
                                                     true, 0, 0, 0, 64000, true);

    StrongMT<test::MockClient> client1 = new test::MockClient();
    client1->minigameEnabled = false;
    AddClient(p1, "test0", 0, client1, true);
    TS_ASSERT_EQUALS(true, client1->minigameEnabled);
  }

  void test_kickCheaterOnWrongUserIdInCommand()
  {
    StrongMT<Peered::CommandsScheduler> p = Create(2, 100, 0, 0, 2000, 0, FillClients(0, 1));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();

    int clientIndex0 = AddClient(p, "badcheater", 0, client0, true);
    int clientIndex1 = AddClient(p, "goodplayer", 1, client1, true);
    p->Step();
    p->Step();
    p->OnFinishStep(clientIndex0, 0, 0xF00D);
    p->OnFinishStep(clientIndex1, 0, 0xF00D);

    const int commandSize = 11;
    char commandData[commandSize];
    test::FormatCommand(&commandData, 0, "cmd");  // Set Id of client0
    rpc::MemoryBlock command(commandData, commandSize);
    p->SendCommand(clientIndex1, command, true);  // Send from client1...
    p->Step();
    TS_ASSERT_EQUALS(3, client0->steps.size());  // client0 is ok
    TS_ASSERT_EQUALS(0, client0->steps[0].commands.size());  // Command is not delivered
    TS_ASSERT_EQUALS(3, client0->clientStatuses.size()); // Active*2, disconnected by chaeat attempt
    TS_ASSERT_EQUALS(1, client0->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, client0->clientStatuses[2].status);
    TS_ASSERT_EQUALS(2, client1->steps.size());  // client1 is out
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, client1->disconnectReason);

    p->OnFinishStep(clientIndex0, 1, 0xF00D);

    // Now check that we cleaned snapshots and resumed stepping fine after dropping the cheater
    for (int i = 0; i < 100; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(i+4, client0->steps.size());
      p->OnFinishStep(clientIndex0, i+2, 0xF00D);
    }
  }

  // Not all clients report game finish and timeout occurs. 
  // In this case 1 of 3 doesn't report and we have a sync result.
  void test_GameFinishWithTimeOut1()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    /*int clientId2 =*/ AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnGameFinish(clientId0, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 1, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);

    for (int i = 0; i < 300; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);
    }
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    TS_ASSERT_EQUALS(lobby::EGameResult::SyncResults, link->gameResultType);
    TS_ASSERT_EQUALS(3, link->clientStatistics.size());
  }

  // Not all clients report game finish and timeout occurs. 
  // In this case 2 of 3 don't report and we have an async result.
  void test_GameFinishWithTimeOut2()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    /*int clientId1 =*/ AddClient(p, "test1", 56, client1, true);
    /*int clientId2 =*/ AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnGameFinish(clientId0, 1, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);

    for (int i = 0; i < 300; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);
    }
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(lobby::EGameResult::AsyncResults, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(3, gameResults.players.size());
    TS_ASSERT_EQUALS(55, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(56, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(57, gameResults.players[2].userid);
    TS_ASSERT_EQUALS(3, link->clientStatistics.size());
  }

  // Not all clients report game finish and timeout occurs. 
  // In this case 2 of 4 don't report without lags and we have an async result.
  void test_GameFinishWithTimeOut3()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 0, client0, true);
    int clientId1 = AddClient(p, "test1", 1, client1, true);
    int clientId2 = AddClient(p, "test2", 2, client2, true);
    int clientId3 = AddClient(p, "test3", 3, client3, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientId3, 0, 0xF00D);
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);
    p->OnFinishStep(clientId3, 1, 0xF00D);

    p->OnGameFinish(clientId0, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 2, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);

    for (int i = 0; i < 300; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);
    }
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(lobby::EGameResult::AsyncResults, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(4, gameResults.players.size());
    TS_ASSERT_EQUALS(0, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(1, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(2, gameResults.players[2].userid);
    TS_ASSERT_EQUALS(3, gameResults.players[3].userid);
    TS_ASSERT_EQUALS(4, link->clientStatistics.size());
  }

  // Not all clients report game finish and timeout occurs. 
  // In this case 2 of 4 don't report with lags and we have a sync result.
  void test_GameFinishWithTimeOut4()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 0, client0, true);
    int clientId1 = AddClient(p, "test1", 1, client1, true);
    int clientId2 = AddClient(p, "test2", 2, client2, true);
    int clientId3 = AddClient(p, "test3", 3, client3, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientId3, 0, 0xF00D);
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);

    p->OnGameFinish(clientId0, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 2, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);

    for (int i = 0; i < 300; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);
    }
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    TS_ASSERT_EQUALS(lobby::EGameResult::SyncResults, link->gameResultType);
    TS_ASSERT_EQUALS(4, link->clientStatistics.size());
  }

  // Not all clients report game finish and timeout occurs.
  // In this case 2 of 4 don't report without lags and we have an async result. Confirmation frequency=2
  void test_GameFinishWithTimeOut5()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4), link, 0, 0, 0, 0, 2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 0, client0, true);
    int clientId1 = AddClient(p, "test1", 1, client1, true);
    int clientId2 = AddClient(p, "test2", 2, client2, true);
    int clientId3 = AddClient(p, "test3", 3, client3, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientId3, 0, 0xF00D);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);

    p->OnGameFinish(clientId0, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 2, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);

    for (int i = 0; i < 300; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);
    }
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(lobby::EGameResult::AsyncResults, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(4, gameResults.players.size());
    TS_ASSERT_EQUALS(0, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(1, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(2, gameResults.players[2].userid);
    TS_ASSERT_EQUALS(3, gameResults.players[3].userid);
    TS_ASSERT_EQUALS(4, link->clientStatistics.size());
  }

  // Not all clients report game finish and timeout occurs.
  // In this case 2 of 4 don't report with lags and we have a sync result. Confirmation frequency=2
  void test_GameFinishWithTimeOut6()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4), link, 0, 0, 0, 0, 2);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 0, client0, true);
    int clientId1 = AddClient(p, "test1", 1, client1, true);
    int clientId2 = AddClient(p, "test2", 2, client2, true);
    int clientId3 = AddClient(p, "test3", 3, client3, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientId3, 0, 0xF00D);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);

    p->OnGameFinish(clientId0, 3, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 3, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);

    for (int i = 0; i < 300; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(lobby::EGameResult::Unknown, link->gameResultType);
    }
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    TS_ASSERT_EQUALS(lobby::EGameResult::SyncResults, link->gameResultType);
    TS_ASSERT_EQUALS(4, link->clientStatistics.size());
  }

  // Tests sending client statuses. It shouldn't be sent twice on hybrid link.
  // While it is sent twice to clients in some cases: on session start - to update all clients presence
  // and on reconnect - to update reconnecting client with statuses of others.
  void test_StatusesSentOnceOnHybridLink()
  {
    int connectionTimeout = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4), link, 0, 0, 0, connectionTimeout);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    //StrongMT<test::MockClient> client2 = new test::MockClient();   // This client didn't connect
    StrongMT<test::MockClient> client3 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();

    int clientId0 = AddClient(p, "test0", 0, client0, true);
    /*int clientId1 =*/ AddClient(p, "test1", 1, client1, true);
    //int clientId2 = AddClient(p, "test2", 2, client2, true);   // This client didn't connect
    /*int clientId3 =*/ AddClient(p, "test3", 3, client3, true);

    client3->status = rpc::Disconnected;    // Lets disconnect one client before start

    for (int i = 0; i < connectionTimeout - 1; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS( 4, link->clientStatuses.size() );     // Connecting*3 + One client is disconnected before
      TS_ASSERT_EQUALS( 1, client0->clientStatuses.size() );
    }
    p->Step(); // Here we will get to the connection timeout

    TS_ASSERT_EQUALS( 5, link->clientStatuses.size() );     // No "update all" is received on hybrid link, only timed out client
    TS_ASSERT_EQUALS( 5, client0->clientStatuses.size() );  // Clients do receive all updates
    client1->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS( 6, link->clientStatuses.size() );     // Received disconnect of the client1
    TS_ASSERT_EQUALS( 6, client0->clientStatuses.size() );

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnRejoinClient(1);
    int clientIdR = AddClient(p, "test1", 1, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS( 7, link->clientStatuses.size() );     // Reconnecting client detected!
    TS_ASSERT_EQUALS( 7, client0->clientStatuses.size() );  // Here too

    p->RequestWorldData(clientIdR);
    p->Step();

    rpc::MemoryBlock worldDataPart1("part1", 5);
    Peered::WorldDataInfo worldDataInfo(1, 1);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    TS_ASSERT_EQUALS( 7, link->clientStatuses.size() );     // No "update all" is received on hybrid link
    TS_ASSERT_EQUALS( 11, client0->clientStatuses.size() );  // Clients do receive update
  }

  void test_CommandSizeOverflow()
  {
    const int commandMaxSize = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55), 
                                                      link, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 
                                                        0, 0, 0, 64000, true, 300, commandMaxSize);

    StrongMT<test::MockClient> client = new test::MockClient();

    int clientIndex = AddClient(p, "test1", 55, client, true);

    // Send command with acceptable size
    const int commandSize1 = commandMaxSize; // 8(header) + 2(command) = 10
    char commandData1[commandSize1];
    test::FormatCommand(&commandData1, 55, "01");
    rpc::MemoryBlock command1(commandData1, commandSize1);
    p->SendCommand(clientIndex, command1, true);
    p->Step();

    // Command received, step done, everything is fine
    TS_ASSERT_EQUALS(1, client->steps.size());
    TS_ASSERT_EQUALS(0, client->steps[0].step);
    TS_ASSERT_EQUALS(1, client->steps[0].commands.size());
    TS_ASSERT_EQUALS(commandSize1, client->steps[0].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData1, client->steps[0].commands[0].memory, commandSize1);

    // Send command with size overflow
    const int commandSize2 = commandMaxSize+1; // 8(header) + 3(command) = 11
    char commandData2[commandSize2];
    test::FormatCommand(&commandData2, 55, "012");
    rpc::MemoryBlock command2(commandData2, commandSize2);
    p->SendCommand(clientIndex, command2, true);
    p->Step();

    // No step, no command, cheater detected
    TS_ASSERT_EQUALS(1, client->steps.size());
    TS_ASSERT_EQUALS(1, link->cheaters.size());
    TS_ASSERT_EQUALS(55, link->cheaters[0]);
  }

  void test_CommandsSizePerStepOverflow()
  {
    const int commandMaxSize = 10;
    const int commandsPerStepMaxSize = 50;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55), 
                                                      link, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 
                                                        0, 0, 0, 64000, true, 300, commandMaxSize, commandsPerStepMaxSize);

    StrongMT<test::MockClient> client = new test::MockClient();

    int clientIndex = AddClient(p, "test1", 55, client, true);

    // Send command with acceptable total size per step
    const int commandSize1 = commandMaxSize; // 8(header) + 2(command) = 10
    char commandData1[commandSize1];
    test::FormatCommand(&commandData1, 55, "01");
    rpc::MemoryBlock command1(commandData1, commandSize1);

    for (int i = 0; i < commandsPerStepMaxSize / commandMaxSize; ++i)
    {
      p->SendCommand(clientIndex, command1, true);
    }
    p->Step();

    // Commands received, step done, everything is fine
    TS_ASSERT_EQUALS(1, client->steps.size());
    TS_ASSERT_EQUALS(0, client->steps[0].step);
    TS_ASSERT_EQUALS(commandsPerStepMaxSize / commandMaxSize, client->steps[0].commands.size());
    TS_ASSERT_EQUALS(commandSize1, client->steps[0].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData1, client->steps[0].commands[0].memory, commandSize1);

    // Send commands with total size per step overflow
    for (int i = 0; i < commandsPerStepMaxSize / commandMaxSize; ++i)
    {
      p->SendCommand(clientIndex, command1, true);
    }
    p->SendCommand(clientIndex, command1, true);
    p->Step();

    // Currently we do not mark such client as cheater, because it can be a result of a lag
    // No step, no command, cheater detected
    //TS_ASSERT_EQUALS(1, client->steps.size());
    //TS_ASSERT_EQUALS(1, link->cheaters.size());
    //TS_ASSERT_EQUALS(55, link->cheaters[0]);
    // But we do ignore the subsequent commands for current step 
    TS_ASSERT_EQUALS(2, client->steps.size());
    TS_ASSERT_EQUALS(commandsPerStepMaxSize / commandMaxSize, client->steps[1].commands.size());
    TS_ASSERT_EQUALS(0, link->cheaters.size());
  }

  void test_StepDelaySettingsDelivery()
  {
    const int stepsDelayMin = 2;
    const int stepsDelayMax = 5;
    const int stepsDelayFrame = 100;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55), 
                                                      0, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 
                                                        0, 0, 0, 64000, true, 300, 128, 6400, false, 
                                                          stepsDelayMin, stepsDelayMax, stepsDelayFrame);

    StrongMT<test::MockClient> client = new test::MockClient();

    AddClient(p, "test1", 55, client, true);

    TS_ASSERT_EQUALS(stepsDelayMin, client->stepsDelayMin);
    TS_ASSERT_EQUALS(stepsDelayMax, client->stepsDelayMax);
    TS_ASSERT_EQUALS(stepsDelayFrame, client->stepsDelayFrame);
  }

  void test_ReconnectAnnouncement()
  {
    int reconnectTimeoutSteps = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    Peered::SchedulerData data;
    SchedulerObjects objects;
    data.sessionSettings.reconnectTimeout = reconnectTimeoutSteps;
    data.sessionSettings.reconnectEnabled = true;
    objects.statisticsWrapper = statisticsWrapper;
    objects.statsLink = link;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClientsAscending(4));

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    StrongMT<test::MockClient> clientR3 = new test::MockClient();
    int clientIndex0 = AddClient(p, "test0", 0, client0, true);
    AddClient(p, "test1", 1, client1, true);
    AddClient(p, "test2", 2, client2, true);
    AddClient(p, "test3", 3, client3, true);
    p->Step();

    client1->status = rpc::Disconnected;
    client2->status = rpc::Disconnected;
    client3->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(7, link->clientStatuses.size())  // Connecting*4 + Disconnect*3

    // Since NUM_TASK we can enter without announcement
    int clientIdR1 = AddClient(p, "test1", 1, clientR1, false);
    TS_ASSERT_LESS_THAN_EQUALS(0, clientIdR1);
    TS_ASSERT_EQUALS(8, link->clientStatuses.size());
    TS_ASSERT_EQUALS(Peered::Connecting, link->clientStatuses[7].status);

    p->OnRejoinClient(2);
    int clientIdR2 = AddClient(p, "test2", 2, clientR2, false);

    TS_ASSERT_LESS_THAN_EQUALS(0, clientIdR2);  // This time we have announcement, so it's ok
    TS_ASSERT_EQUALS(9, link->clientStatuses.size());
    TS_ASSERT_EQUALS(Peered::Connecting, link->clientStatuses[8].status);

    p->OnRejoinClient(3);

    for (int i = 0; i < reconnectTimeoutSteps; ++i)
    {
      p->Step();
    }
    p->Step();

    TS_ASSERT_EQUALS(10, link->clientStatuses.size());
    TS_ASSERT_EQUALS(Peered::ConnectionTimedOutOnReconnect, link->clientStatuses[9].status);

    // Since NUM_TASK we can enter after timeout
    int clientIdR3 = AddClient(p, "test3", 3, clientR3, false);
    TS_ASSERT_LESS_THAN_EQUALS(0, clientIdR3);
    TS_ASSERT_EQUALS(11, link->clientStatuses.size());
    TS_ASSERT_EQUALS(Peered::Connecting, link->clientStatuses[10].status);

    p->OnGameFinish(clientIndex0, 0, GetFinishData(lobby::ETeam::Team1));

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(15, statisticsWrapper->statuses.size());
    TS_ASSERT(statisticsWrapper->CheckStatusRange(0, 3, Peered::Connecting));
    TS_ASSERT(statisticsWrapper->CheckStatusRange(4, 6, Peered::DisconnectedByClient));
    TS_ASSERT(statisticsWrapper->CheckStatusRange(7, 8, Peered::Connecting));
    TS_ASSERT(statisticsWrapper->CheckStatusRange(9, 9, Peered::ConnectionTimedOutOnReconnect));
    TS_ASSERT(statisticsWrapper->CheckStatusRange(10, 10, Peered::Connecting));
    TS_ASSERT(statisticsWrapper->CheckStatusRange(11, 14, Peered::DisconnectedByServer, Peered::EDisconnectReason::GameFinished));
    TS_ASSERT_EQUALS(0, statisticsWrapper->GetStatusesDelta());
  }

  void test_ReconnectAnnouncementOfClientDisconnectedByCheatAttempt()
  {
    int reconnectTimeoutSteps = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(3), 
                                                    link, 0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 0, 
                                                    0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 0, 
                                                    reconnectTimeoutSteps);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR1 = new test::MockClient();
    StrongMT<test::MockClient> clientR2 = new test::MockClient();
    AddClient(p, "test0", 0, client0, true);
    int clientIndex1 = AddClient(p, "test1", 1, client1, true);
    int clientIndex2 = AddClient(p, "test2", 2, client2, true);
    p->Step();

    // Report ready second time to get kicked as cheater
    p->OnClientReady(clientIndex1);
    p->OnClientReady(clientIndex2);
    p->Step();

    TS_ASSERT_EQUALS(5, link->clientStatuses.size());
    TS_ASSERT_EQUALS(1, link->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[3].status);
    TS_ASSERT_EQUALS(2, link->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[4].status);

    // Announce rejoin for the first client
    p->OnRejoinClient(1);

    // Lobby is informed about ignored cheater
    TS_ASSERT_EQUALS(6, link->clientStatuses.size());
    TS_ASSERT_EQUALS(1, link->clientStatuses[5].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[5].status);

    // Announce rejoin for the second client
    p->OnRejoinClient(2);

    // Lobby is informed about ignored cheater
    TS_ASSERT_EQUALS(7, link->clientStatuses.size());
    TS_ASSERT_EQUALS(2, link->clientStatuses[6].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[6].status);


    // WTF they reconnect you may ask, but that's another question. 
    // Lets just check we properly ignore them any way.

    int clientIdR1 = AddClient(p, "test1", 1, clientR1, false);
    TS_ASSERT_EQUALS(-1, clientIdR1); // Cheater can't get in

    // Lobby is informed about ignored cheater
    TS_ASSERT_EQUALS(8, link->clientStatuses.size());
    TS_ASSERT_EQUALS(1, link->clientStatuses[7].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[7].status);

    int clientIdR2 = AddClient(p, "test2", 2, clientR2, false);
    TS_ASSERT_EQUALS(-1, clientIdR2); // Cheater can't get in

    // Lobby is informed about ignored cheater
    TS_ASSERT_EQUALS(9, link->clientStatuses.size());
    TS_ASSERT_EQUALS(2, link->clientStatuses[8].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[8].status);

    // Retry immideatelly for one of them
    p->OnRejoinClient(1);

    // Lobby is informed about ignored cheater
    TS_ASSERT_EQUALS(10, link->clientStatuses.size());
    TS_ASSERT_EQUALS(1, link->clientStatuses[9].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[9].status);

    clientIdR1 = AddClient(p, "test1", 1, clientR1, false);
    TS_ASSERT_EQUALS(-1, clientIdR1); // Cheater can't get in

    // Lobby is informed about ignored cheater
    TS_ASSERT_EQUALS(11, link->clientStatuses.size());
    TS_ASSERT_EQUALS(1, link->clientStatuses[10].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[10].status);

    for (int i = 0; i < reconnectTimeoutSteps; ++i)
    {
      p->Step();
    }
    p->Step();

    // Rtry for the second after timeout
    p->OnRejoinClient(2);

    // Lobby is informed about ignored cheater
    TS_ASSERT_EQUALS(12, link->clientStatuses.size());
    TS_ASSERT_EQUALS(2, link->clientStatuses[11].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[11].status);

    clientIdR2 = AddClient(p, "test2", 2, clientR2, false);
    TS_ASSERT_EQUALS(-1, clientIdR2); // Cheater can't get in

    // Lobby is informed about ignored cheater
    TS_ASSERT_EQUALS(13, link->clientStatuses.size());
    TS_ASSERT_EQUALS(2, link->clientStatuses[12].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[12].status);

    // Retry once again, without passing though lobby (no OnRejoinClient call)
    clientIdR2 = AddClient(p, "test2", 2, clientR2, false);
    TS_ASSERT_EQUALS(-1, clientIdR2); // Cheater can't get in

    // Lobby is informed about ignored cheater
    TS_ASSERT_EQUALS(14, link->clientStatuses.size());
    TS_ASSERT_EQUALS(2, link->clientStatuses[13].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByCheatAttempt, link->clientStatuses[13].status);
  }

  void test_GameLeaveIntentionally()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(2), link);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    AddClient(p, "test0", 0, client0, true);
    int clientIndex1 = AddClient(p, "test1", 1, client1, true);
    p->Step();

    p->OnGameLeave(clientIndex1);

    TS_ASSERT_EQUALS(3, link->clientStatuses.size());
    TS_ASSERT_EQUALS(1, link->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClientIntentionally, link->clientStatuses[2].status);

    TS_ASSERT_EQUALS(2, client0->clientStatuses.size());  // Active*2

    p->Step();

    TS_ASSERT_EQUALS(3, client0->clientStatuses.size());  // Active*2, DisconnectedByClientIntentionally
    TS_ASSERT_EQUALS(1, client0->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClientIntentionally, client0->clientStatuses[2].status);
  }

  // Just in case the client doesn't send its reconnect interface 
  // or it is lost/delayed somewhere on the second "non-RT" connection
  void test_ReconnectClientDoesntSendReconnectInterface()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    data.sessionSettings.reconnectEnabled = true;
    objects.statisticsWrapper = statisticsWrapper;
    objects.statsLink = link;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    // Current client logic will report step only when the second is received
    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    clientR->sendReconnectInterface = false;
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    TS_ASSERT_EQUALS(true, clientR->isReconnecting);
    p->RequestWorldData(clientIdR);
    p->Step();

    rpc::MemoryBlock worldDataPart1("part1", 5);
    rpc::MemoryBlock worldDataPart2("part2", 5);
    Peered::WorldDataInfo worldDataInfo(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);

    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Normal, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::NoReconnectIface, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(57, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(4, statisticsWrapper->reconnects[0].currentStep);
  }

  void test_ReconnectForceWorldRequestTimeout1()
  {
    int snapshotRequestTime0ut = 600;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                    0, 0, 0, 0, 0, 1, 0, snapshotRequestTime0ut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    Peered::WorldDataInfo worldDataInfo1(2, 0xFFFFFFFF);  // Put a very large parts count
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    p->Step();

    TS_ASSERT_EQUALS(true, client1->worldDataRequested);  // The second gets the request immediately
  }

  void test_ReconnectForceWorldRequestTimeout2()
  {
    int snapshotRequestTime0ut = 600;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                    0, 0, 0, 0, 0, 1, 0, snapshotRequestTime0ut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    Peered::WorldDataInfo worldDataInfo1(555, 1);  // Put step number, which wasn't sent yet
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    p->Step();

    TS_ASSERT_EQUALS(true, client1->worldDataRequested);  // The second gets the request immediately
  }

  void test_ReconnectForceWorldRequestTimeout3()
  {
    int snapshotRequestTime0ut = 600;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                    0, 0, 0, 0, 0, 1, 0, snapshotRequestTime0ut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->Step();

    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    Peered::WorldDataInfo worldDataInfo1(0, 1);  // Put step number, which already not relevant
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    p->Step();

    TS_ASSERT_EQUALS(true, client1->worldDataRequested);  // The second gets the request immediately
  }

  void test_ReconnectForceWorldRequestTimeout4()
  {
    int snapshotRequestTime0ut = 600;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                    0, 0, 0, 0, 0, 1, 0, snapshotRequestTime0ut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->Step();

    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    rpc::MemoryBlock worldDataPart1("part1", 0xFFFFFFFF);  // Very large part size
    Peered::WorldDataInfo worldDataInfo1(3, 2);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    TS_ASSERT_EQUALS(true, client1->worldDataRequested);  // The second gets the request immediately
  }

  void test_ReconnectForceWorldRequestTimeout5()
  {
    int snapshotRequestTime0ut = 600;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                    0, 0, 0, 0, 0, 1, 0, snapshotRequestTime0ut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->Step();

    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    rpc::MemoryBlock worldDataPart1("part1", 5);  // Very large part size
    Peered::WorldDataInfo worldDataInfo1(0, 1);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    TS_ASSERT_EQUALS(true, client1->worldDataRequested);  // The second gets the request immediately
  }

  void test_ReconnectForceWorldRequestTimeout6()
  {
    int snapshotRequestTime0ut = 600;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), 
                                                    0, 0, 0, 0, 0, 1, 0, snapshotRequestTime0ut);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->Step();

    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->RequestWorldData(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);  // First client got the request
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    rpc::MemoryBlock worldDataPart1("part1", 5);  // Very large part size
    Peered::WorldDataInfo worldDataInfo1(0, 1);
    client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo1);
    client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
    p->Step();

    TS_ASSERT_EQUALS(true, client1->worldDataRequested);  // The second gets the request immediately
  }

  void test_GameFinishWithInconsistentResultsFaction()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->Step();

    p->OnGameFinish(clientId0, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 2, GetFinishData(lobby::ETeam::Team2));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
  }

  void test_GameFinishWithInconsistentResultsStatistics()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->Step();

    StatisticService::RPC::SessionClientResults info1;
    StatisticService::RPC::SessionClientResults info2;

    info1.players.resize(2);
    info2.players.resize(2);

    info1.players[0].scoring.score = 150;
    info1.players[1].scoring.score = 0;
    info2.players[0].scoring.score = 0;
    info2.players[1].scoring.score = 150;

    p->OnGameFinish(clientId0, 2, info1);
    p->OnGameFinish(clientId1, 2, info1);
    p->OnGameFinish(clientId2, 2, info2);
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(info1, link->gameFinishInfo);
  }

  void test_Async2ClientsWithCrcDataRequest()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockCrcDumper> crcDumper = new test::MockCrcDumper;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link, 0, 0, 0, 0, 1, 0, 0,
                                                    0, 1024, 4096, true, 0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 
                                                      0, 0, true, 500, crcDumper);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xBADF00D);

    TS_ASSERT_EQUALS(1, client0->crcRequestedForStep);
    TS_ASSERT_EQUALS(1, client1->crcRequestedForStep);

    TS_ASSERT_EQUALS(100, p->Step()); // We are not finished yet
    TS_ASSERT_EQUALS(100, p->Step());

    rpc::MemoryBlock crcData1("test1", 6);
    p->SendCrcData(clientId0, 1, crcData1);
    TS_ASSERT_EQUALS(1, crcDumper->crcData.size());
    TS_ASSERT_EQUALS(55, crcDumper->crcData[0].clientId);
    TS_ASSERT_EQUALS(1, crcDumper->crcData[0].step);
    TS_ASSERT_SAME_DATA("test1", crcDumper->crcData[0].data.memory, 6)
    TS_ASSERT_EQUALS(6, crcDumper->crcData[0].size);

    TS_ASSERT_EQUALS(100, p->Step());

    rpc::MemoryBlock crcData2("test2", 6);
    p->SendCrcData(clientId1, 1, crcData2);
    TS_ASSERT_EQUALS(2, crcDumper->crcData.size())
    TS_ASSERT_EQUALS(56, crcDumper->crcData[1].clientId);
    TS_ASSERT_EQUALS(1, crcDumper->crcData[1].step);
    TS_ASSERT_SAME_DATA("test2", crcDumper->crcData[1].data.memory, 6)
    TS_ASSERT_EQUALS(6, crcDumper->crcData[1].size);

    TS_ASSERT_EQUALS(1, client0->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(1, client1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_Async2ClientsWithCrcDataRequestAndTimeout()
  {
    const int crcdataRequestTimeOut = 100;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockCrcDumper> crcDumper = new test::MockCrcDumper;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56), link, 0, 0, 0, 0, 1, 0, 0,
                                                    0, 1024, 4096, true, 0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 
                                                      0, 0, true, crcdataRequestTimeOut, crcDumper);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xBADF00D);

    TS_ASSERT_EQUALS(1, client0->crcRequestedForStep);
    TS_ASSERT_EQUALS(1, client1->crcRequestedForStep);

    for (int i = 0; i < crcdataRequestTimeOut; ++i)
    {
      TS_ASSERT_EQUALS(100, p->Step()); // We are not finished yet
    }

    TS_ASSERT_EQUALS(0, crcDumper->crcData.size());

    TS_ASSERT_EQUALS(1, client0->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(1, client1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_Async3ClientsWithCrcDataRequest()
  {
    const int crcdataRequestTimeOut = 100;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockCrcDumper> crcDumper = new test::MockCrcDumper;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link, 0, 0, 0, 0, 1, 0, 0,
                                                    0, 1024, 4096, true, 0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 
                                                      0, 0, true, crcdataRequestTimeOut, crcDumper);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client0->lastConfirmedStep);
    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client1->lastConfirmedStep);
    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client2->lastConfirmedStep);

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xBADF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);

    TS_ASSERT(1 == client0->crcRequestedForStep || 1 == client2->crcRequestedForStep);
    TS_ASSERT_EQUALS(1, client1->crcRequestedForStep);

    p->OnFinishStep(clientId0, 2, 0xF00D2);
    p->OnFinishStep(clientId1, 2, 0xBADF00D2);
    p->OnFinishStep(clientId2, 2, 0xF00D2);

    TS_ASSERT(1 == client0->crcRequestedForStep || 1 == client2->crcRequestedForStep);
    TS_ASSERT_EQUALS(1, client1->crcRequestedForStep);

    for (int i = 0; i < crcdataRequestTimeOut - 1; ++i)
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }

    TS_ASSERT_EQUALS(3 + crcdataRequestTimeOut - 1, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3 + crcdataRequestTimeOut - 1, client2->steps.size());
    TS_ASSERT_EQUALS(0, client0->lastConfirmedStep);
    TS_ASSERT_EQUALS(0, client1->lastConfirmedStep);
    TS_ASSERT_EQUALS(0, client2->lastConfirmedStep);

    int sender1 = (1 == client0->crcRequestedForStep)?(clientId0):(clientId2);
    rpc::MemoryBlock crcData1("test1", 6);
    p->SendCrcData(sender1, 1, crcData1);
    TS_ASSERT_EQUALS(1, crcDumper->crcData.size());
    TS_ASSERT_EQUALS(1, crcDumper->crcData[0].step);
    TS_ASSERT_SAME_DATA("test1", crcDumper->crcData[0].data.memory, 6)
    TS_ASSERT_EQUALS(6, crcDumper->crcData[0].size);

    rpc::MemoryBlock crcData2("test2", 6);
    p->SendCrcData(clientId1, 1, crcData2);
    TS_ASSERT_EQUALS(2, crcDumper->crcData.size())
    TS_ASSERT_EQUALS(56, crcDumper->crcData[1].clientId);
    TS_ASSERT_EQUALS(1, crcDumper->crcData[1].step);
    TS_ASSERT_SAME_DATA("test2", crcDumper->crcData[1].data.memory, 6)
    TS_ASSERT_EQUALS(6, crcDumper->crcData[1].size);

    for (int i = 0; i < 10; ++i)
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }

    TS_ASSERT_EQUALS(2, client0->lastConfirmedStep);
    TS_ASSERT_EQUALS(0, client1->lastConfirmedStep);
    TS_ASSERT_EQUALS(2, client2->lastConfirmedStep);

    TS_ASSERT_EQUALS(3 + crcdataRequestTimeOut + 9, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3 + crcdataRequestTimeOut + 9, client2->steps.size());

    TS_ASSERT_EQUALS(1, client1->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);

    p->OnFinishStep(clientId0, 3, 0xF00D3);
    p->OnFinishStep(clientId2, 3, 0xF00D3);

    TS_ASSERT_EQUALS(100, p->Step());

    TS_ASSERT_EQUALS(3 + crcdataRequestTimeOut + 10, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3 + crcdataRequestTimeOut + 10, client2->steps.size());
    TS_ASSERT_EQUALS(3, client0->lastConfirmedStep);
    TS_ASSERT_EQUALS(0, client1->lastConfirmedStep);
    TS_ASSERT_EQUALS(3, client2->lastConfirmedStep);
  }

  void test_Async2ClientsWithCrcDataRequestAnd1ClientReconnecting()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockCrcDumper> crcDumper = new test::MockCrcDumper;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link, 0, 0, 0, 0, 1, 0, 0,
                                                    0, 1024, 4096, true, 0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 
                                                      0, 0, true, 500, crcDumper);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    p->OnRejoinClient(57);
    AddClient(p, "test2", 57, clientR, false);
    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xBADF00D);

    TS_ASSERT_EQUALS(100, p->Step()); // We are not finished yet
    TS_ASSERT_EQUALS(100, p->Step());

    rpc::MemoryBlock crcData1("test1", 6);
    p->SendCrcData(clientId0, 1, crcData1);
    TS_ASSERT_EQUALS(1, crcDumper->crcData.size());
    TS_ASSERT_EQUALS(55, crcDumper->crcData[0].clientId);
    TS_ASSERT_EQUALS(1, crcDumper->crcData[0].step);
    TS_ASSERT_SAME_DATA("test1", crcDumper->crcData[0].data.memory, 6)
    TS_ASSERT_EQUALS(6, crcDumper->crcData[0].size);

    TS_ASSERT_EQUALS(100, p->Step());

    rpc::MemoryBlock crcData2("test2", 6);
    p->SendCrcData(clientId1, 1, crcData2);
    TS_ASSERT_EQUALS(2, crcDumper->crcData.size())
    TS_ASSERT_EQUALS(56, crcDumper->crcData[1].clientId);
    TS_ASSERT_EQUALS(1, crcDumper->crcData[1].step);
    TS_ASSERT_SAME_DATA("test2", crcDumper->crcData[1].data.memory, 6)
    TS_ASSERT_EQUALS(6, crcDumper->crcData[1].size);

    // All active clients dropped due to async and reconnecter is without world applied -> finish
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    // Async is sent on the link
    TS_ASSERT_EQUALS(lobby::EGameResult::Async, link->gameResultType);
    const StatisticService::RPC::SessionClientResults & gameResults = link->gameFinishInfo;
    TS_ASSERT_EQUALS(lobby::ETeam::None, gameResults.sideWon);
    TS_ASSERT_EQUALS(3, gameResults.players.size());
    TS_ASSERT_EQUALS(55, gameResults.players[0].userid);
    TS_ASSERT_EQUALS(56, gameResults.players[1].userid);
    TS_ASSERT_EQUALS(57, gameResults.players[2].userid);

    // Reconnecting client is disconnected with GameFinish and without async
    TS_ASSERT_EQUALS(-1, clientR->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, clientR->disconnectReason);
  }

  void test_GameFinishWithWaitingForRoll()
  {
    const Peered::SAuxData auxData;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockAwardsRequester> awardsRequester = new test::MockAwardsRequester;
    StrongMT<Peered::IAwardsRequester> awardsRequesterIface = awardsRequester.Get();
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link, 
                                                    0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, &auxData, 0,
                                                    0, 64000, true, 300, 128, 64000, false, 1, 1, 0, 0, 
                                                    false, 500, 0, 0, awardsRequesterIface.Get());
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->Step();

    p->OnGameFinish(clientId0, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 2, GetFinishData(lobby::ETeam::Team2));

    // Fill dummy awards with user IDs and one (unspecified) talent
    for (int i = 0; i < 3; ++i)
    {
      roll::SUserAward & userAward = awardsRequester->awards.push_back();
      userAward.userId = 55 + i;
      roll::SAwardInfo & awardInfo = userAward.awards.push_back();
      awardInfo.type = roll::EAwardType::Talent;
      awardInfo.count = 1;
    }

    for (int i = 0; i < 10; ++i )
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }
    awardsRequester->isAwardsReceived = true;
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    TS_ASSERT_EQUALS(true, client0->isAwardReceived);
    TS_ASSERT_EQUALS(1, client0->awards.size());
    TS_ASSERT_EQUALS(roll::EAwardType::Talent, client0->awards[0].type);
    TS_ASSERT_EQUALS(1, client0->awards[0].count);
    TS_ASSERT_EQUALS(true, client1->isAwardReceived);
    TS_ASSERT_EQUALS(1, client1->awards.size());
    TS_ASSERT_EQUALS(roll::EAwardType::Talent, client1->awards[0].type);
    TS_ASSERT_EQUALS(1, client1->awards[0].count);
    TS_ASSERT_EQUALS(true, client2->isAwardReceived);
    TS_ASSERT_EQUALS(1, client2->awards.size());
    TS_ASSERT_EQUALS(roll::EAwardType::Talent, client2->awards[0].type);
    TS_ASSERT_EQUALS(1, client2->awards[0].count);
  }

  void test_GameFinishWithWaitingForRollAndTimeout()
  {
    const int rollTimeout = 10;
    const Peered::SAuxData auxData;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockAwardsRequester> awardsRequester = new test::MockAwardsRequester;
    StrongMT<Peered::IAwardsRequester> awardsRequesterIface = awardsRequester.Get();
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link, 
                                                    0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, &auxData, 0,
                                                    0, 64000, true, 300, 128, 64000, false, 1, 1, 0, 0, 
                                                    false, 500, 0, rollTimeout, awardsRequesterIface.Get());
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->Step();

    p->OnGameFinish(clientId0, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 2, GetFinishData(lobby::ETeam::Team2));

    for (int i = 0; i < rollTimeout - 1; ++i )
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    // Check that we have received empty awards vector after timeout
    TS_ASSERT_EQUALS(true, client0->isAwardReceived);
    TS_ASSERT_EQUALS(0, client0->awards.size());
    TS_ASSERT_EQUALS(true, client1->isAwardReceived);
    TS_ASSERT_EQUALS(0, client1->awards.size());
    TS_ASSERT_EQUALS(true, client2->isAwardReceived);
    TS_ASSERT_EQUALS(0, client2->awards.size());
  }

  void test_GameFinishTestRollData()
  {
    const Peered::SAuxData auxData;
    const int connectionTimeout = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockAwardsRequester> awardsRequester = new test::MockAwardsRequester;
    StrongMT<Peered::IAwardsRequester> awardsRequesterIface = awardsRequester.Get();
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClientsAscending(4), link, 
                                                    0, 0, 0, connectionTimeout, 1, 0, 0, 0, 1024, 4096, 
                                                    true, &auxData, 0, 0, 64000, true, 300, 128, 64000, 
                                                    false, 1, 1, 0, 0, false, 500, 0, 0, awardsRequesterIface.Get());
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> client3 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 0, client0, true);
    int clientId1 = AddClient(p, "test1", 1, client1, true);
    int clientId2 = AddClient(p, "test2", 2, client2, true);
    // Client3 won't connect in this test
    //int clientId3 = AddClient(p, "test3", 3, client3, true);

    for (int i = 0; i < connectionTimeout; ++i)
    {
      p->Step();
    }
    p->Step();

    int step = 0;
    for (; step < 50; ++step)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      p->Step();
    }

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);

    // One client disconnects before game finish
    client2->status = rpc::Disconnected;

    p->OnGameFinish(clientId1, step, GetFinishData(lobby::ETeam::Team1));
    p->Step();

    // Another disconnects after he sent game finish, but before all clients sent game finish
    client1->status = rpc::Disconnected;
    p->Step();

    // Last one sends game finish
    p->OnGameFinish(clientId0, step, GetFinishData(lobby::ETeam::Team1));

    TS_ASSERT_EQUALS(step/10, awardsRequester->totalSeconds);
    TS_ASSERT_EQUALS(4, awardsRequester->clientsStatistics.size());
    TS_ASSERT_EQUALS(0, awardsRequester->clientsStatistics[0].clientId);
    TS_ASSERT_EQUALS(Peered::EGameFinishClientState::FinishedGame, awardsRequester->clientsStatistics[0].clientState);
    TS_ASSERT_EQUALS(1, awardsRequester->clientsStatistics[1].clientId);
    TS_ASSERT_EQUALS(Peered::EGameFinishClientState::FinishedGame, awardsRequester->clientsStatistics[1].clientState);
    TS_ASSERT_EQUALS(2, awardsRequester->clientsStatistics[2].clientId);
    TS_ASSERT_EQUALS(Peered::EGameFinishClientState::Disconnected, awardsRequester->clientsStatistics[2].clientState);
    TS_ASSERT_EQUALS(3, awardsRequester->clientsStatistics[3].clientId);
    TS_ASSERT_EQUALS(Peered::EGameFinishClientState::NotConnected, awardsRequester->clientsStatistics[3].clientState);
  }

  void check_FastReconnectWithDisconnectDetected(int confirmFrequency, int shift)
  {
    clearIds();
    int loop = 20;
    int step = 0;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,
                                                    0, 0, 0, 0, confirmFrequency, 0, 0, 0, 1024, 4096, true, 
                                                    0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 0, 0, 
                                                    false, 500, 0, 0, 0, 600);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    for (int i = 0; i < loop + shift; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    client2->status = rpc::Disconnected;
    // From this point steps won't be sent to client2, but to clientR after fast reconnect
    p->Step();

    TS_ASSERT_EQUALS(step + 2, client0->steps.size());
    TS_ASSERT_EQUALS(step + 2, client1->steps.size());

    TS_ASSERT_EQUALS(4, client0->clientStatuses.size()); // Active*3 + DisconnectedByClient
    TS_ASSERT_EQUALS(57, client0->clientStatuses[3].clientId);

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    p->AddClientFast(57, clientId2, clientR, loop + shift + 2);
    p->Step();
    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3 + DisconnectedByClient + Connected + Active
    TS_ASSERT_EQUALS(57, client0->clientStatuses[4].clientId);

    // Test steps consistency
    TS_ASSERT_EQUALS(loop + shift + 2, client2->steps.size());
    TS_ASSERT_EQUALS(2, clientR->steps.size());
    TS_ASSERT_EQUALS(client2->steps[loop + shift + 1].step + 1, clientR->steps[0].step);

    // Client will report the last step's CRC (step before fast reconnect) when it resumes
    p->OnFinishStep(clientId2, loop + shift + 1, 0xF00D);
    
    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    TS_ASSERT_EQUALS(loop*2 + shift + 4, client0->steps.size());
    TS_ASSERT_EQUALS(loop*2 + shift + 4, client1->steps.size());
    TS_ASSERT_EQUALS(loop + 2, clientR->steps.size());
    TS_ASSERT_EQUALS(client0->steps[loop*2 + shift + 3].step, clientR->steps[loop + 1].step);
  }

  void test_FastReconnectWithDisconnectDetected()
  {
    for (int freq = 1; freq < 5; ++freq)
    {
      for (int shift = 1; shift < 5; ++shift)
      {
        check_FastReconnectWithDisconnectDetected(freq, shift);
      }
    }
  }

  void check_FastReconnectWithoutDisconnectDetected(int confirmFrequency, int shift)
  {
    clearIds();
    int loop = 20;
    int step = 0;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,
                                                    0, 0, 0, 0, confirmFrequency, 0, 0, 0, 1024, 4096, true, 
                                                    0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 0, 0, 
                                                    false, 500, 0, 0, 0, 600);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    for (int i = 0; i < loop + shift; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    p->AddClientFast(57, clientId2, clientR, loop + shift + 2);
    p->Step();
    TS_ASSERT_EQUALS(3, client0->clientStatuses.size()); // Active*3 only

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    p->Step();

    // Test steps consistency
    TS_ASSERT_EQUALS(loop + shift + 2, client2->steps.size());
    TS_ASSERT_EQUALS(2, clientR->steps.size());
    TS_ASSERT_EQUALS(client2->steps[loop + shift + 1].step + 1, clientR->steps[0].step);

    // Client will report the last step's CRC (step before fast reconnect) when it resumes
    p->OnFinishStep(clientId2, loop + shift + 1, 0xF00D);
    
    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    TS_ASSERT_EQUALS(loop*2 + shift + 4, client0->steps.size());
    TS_ASSERT_EQUALS(loop*2 + shift + 4, client1->steps.size());
    TS_ASSERT_EQUALS(loop + 2, clientR->steps.size());
    TS_ASSERT_EQUALS(client0->steps[loop*2 + shift + 3].step, clientR->steps[loop + 1].step);
  }

  void test_FastReconnectWithoutDisconnectDetected()
  {
    for (int freq = 1; freq < 5; ++freq)
    {
      for (int shift = 1; shift < 5; ++shift)
      {
        check_FastReconnectWithoutDisconnectDetected(freq, shift);
      }
    }
  }

  void test_FastReconnectWhileFastreconnectDisabled()
  {
    // Disabled by default (_fastReconnectReserveSteps=0)
    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    objects.statisticsWrapper = statisticsWrapper;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(2, client2->steps.size());

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->AddClientFast(57, clientId2, clientR, 2);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    TS_ASSERT_EQUALS(2, client2->steps.size());
    TS_ASSERT_EQUALS(0, clientR->steps.size());

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Fast, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::Disabled, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(57, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(3, statisticsWrapper->reconnects[0].currentStep);
  }

  void test_FastReconnectWithLowStepNumber()
  {
    int loop = 20;
    int step = 0;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.fastReconnectReserveSteps = 10;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    objects.statisticsWrapper = statisticsWrapper;
    objects.statsLink = link;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    client2->status = rpc::Disconnected;
    p->Step();

    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      ++step;
      p->Step();
    }

    p->AddClientFast(57, clientId2, clientR, loop + 2);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Fast, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::WrongStep, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(57, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(3 + 2*loop, statisticsWrapper->reconnects[0].currentStep);
  }

  // Possible situation: some steps lost, therefore we have more sent steps than client actually received before disconnect
  void test_FastReconnectWithLowerThenLastSentStepNumber()
  {
    int loop = 20;
    int step = 0;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,
                                                    0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 0, 0, 0, 64000, 
                                                    true, 300, 128, 64000, false, 1, 1, 0, 0, false, 500, 0, 0, 0, 10);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    client2->status = rpc::Disconnected;
    p->Step();

    p->AddClientFast(57, clientId2, clientR, loop);
    TS_ASSERT_EQUALS(loop + 3, client0->steps.size());
    TS_ASSERT_EQUALS(loop + 3, client1->steps.size());
    TS_ASSERT_EQUALS(3, clientR->steps.size());
    TS_ASSERT_EQUALS(client0->steps[loop + 2].step, clientR->steps[2].step);
  }

  void test_FastReconnectWithHighStepNumber()
  {
    int loop = 20;
    int step = 0;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,
                                                    0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 0, 0, 0, 64000, 
                                                    true, 300, 128, 64000, false, 1, 1, 0, 0, false, 500, 0, 0, 0, 10);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    client2->status = rpc::Disconnected;
    p->Step();

    // Client did not received step 22, so fromStep can't be 23
    p->AddClientFast(57, clientId2, clientR, loop + 3);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);
  }

  void test_FastReconnectWithWrongClientIndex()
  {
    int loop = 20;
    int step = 0;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.fastReconnectReserveSteps = 10;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    objects.statisticsWrapper = statisticsWrapper;
    objects.statsLink = link;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    client2->status = rpc::Disconnected;
    p->Step();

    // We don't know such client index...
    p->AddClientFast(57, 9999, clientR, loop + 2);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);

    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Fast, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::IdAndIndexMissmatch, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(57, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(3 + loop, statisticsWrapper->reconnects[0].currentStep);
  }

  void test_FastReconnectLastConfirmedStepIsLastReservedStep()
  {
    int loop = 40;
    int step = 0;
    int reserveSteps = 10;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,
                                                    0, 0, 0, 0, 1, 0, 0, 0, 1024, 4096, true, 0, 0, 0, 64000, 
                                                    true, 300, 128, 64000, false, 1, 1, 0, 0, false, 500, 0,
                                                    0, 0, reserveSteps);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client0->lastConfirmedStep);

    for (int i = 0; i < reserveSteps-1; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
      TS_ASSERT_EQUALS(0, client0->lastConfirmedStep);
    }

    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
      TS_ASSERT_EQUALS(i+1, client0->lastConfirmedStep)
    }
  }

  void test_FastReconnectLastConfirmedStepIsLastReservedStep2()
  {
    int loop = 40;
    int step = 0;
    int reserveSteps = 100;
    int confirmFrequency = 2;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,
                                                    0, 0, 0, 0, confirmFrequency, 0, 0, 0, 1024, 4096, true, 
                                                    0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 0, 0, 
                                                    false, 500, 0, 0, 0, reserveSteps);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client0->lastConfirmedStep);

    for (int i = 0; i < reserveSteps-1; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
      TS_ASSERT_EQUALS(0, client0->lastConfirmedStep);
    }

    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
      TS_ASSERT_EQUALS(client0->steps.size() - reserveSteps - 2 + i%confirmFrequency, client0->lastConfirmedStep)
    }
  }

  void test_AsyncWithSendToAllAndWithCrcDataRequest()
  {
    const int crcdataRequestTimeOut = 100;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockCrcDumper> crcDumper = new test::MockCrcDumper;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link, 0, 0, 0, 0, 1, 0, 0,
                                                    0, 1024, 4096, true, 0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 
                                                      0, 0, true, crcdataRequestTimeOut, crcDumper, 0, 0, 0, true);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client0->lastConfirmedStep);
    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client1->lastConfirmedStep);
    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client2->lastConfirmedStep);

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xBADF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);

    TS_ASSERT(1 == client0->crcRequestedForStep || 1 == client2->crcRequestedForStep);
    TS_ASSERT_EQUALS(1, client1->crcRequestedForStep);

    p->OnFinishStep(clientId0, 2, 0xF00D2);
    p->OnFinishStep(clientId1, 2, 0xBADF00D2);
    p->OnFinishStep(clientId2, 2, 0xF00D2);

    TS_ASSERT(1 == client0->crcRequestedForStep || 1 == client2->crcRequestedForStep);
    TS_ASSERT_EQUALS(1, client1->crcRequestedForStep);

    for (int i = 0; i < crcdataRequestTimeOut - 1; ++i)
    {
      TS_ASSERT_EQUALS(100, p->Step());
    }

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, client2->steps.size());
    TS_ASSERT_EQUALS(0, client0->lastConfirmedStep);
    TS_ASSERT_EQUALS(0, client1->lastConfirmedStep);
    TS_ASSERT_EQUALS(0, client2->lastConfirmedStep);

    int sender1 = (1 == client0->crcRequestedForStep)?(clientId0):(clientId2);
    rpc::MemoryBlock crcData1("test1", 6);
    p->SendCrcData(sender1, 1, crcData1);
    TS_ASSERT_EQUALS(1, crcDumper->crcData.size());
    TS_ASSERT_EQUALS(1, crcDumper->crcData[0].step);
    TS_ASSERT_SAME_DATA("test1", crcDumper->crcData[0].data.memory, 6)
    TS_ASSERT_EQUALS(6, crcDumper->crcData[0].size);

    rpc::MemoryBlock crcData2("test2", 6);
    p->SendCrcData(clientId1, 1, crcData2);
    TS_ASSERT_EQUALS(2, crcDumper->crcData.size())
    TS_ASSERT_EQUALS(56, crcDumper->crcData[1].clientId);
    TS_ASSERT_EQUALS(1, crcDumper->crcData[1].step);
    TS_ASSERT_SAME_DATA("test2", crcDumper->crcData[1].data.memory, 6)
    TS_ASSERT_EQUALS(6, crcDumper->crcData[1].size);

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    TS_ASSERT_EQUALS(1, client0->asyncStep);
    TS_ASSERT_EQUALS(1, client1->asyncStep);
    TS_ASSERT_EQUALS(1, client2->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client2->disconnectReason);
  }

  void test_AsyncWithSendToAllAndWithoutCrcDataRequest()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link, 0, 0, 0, 0, 1, 0, 0,
                                                    0, 1024, 4096, true, 0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 
                                                      0, 0, false, 500, 0, 0, 0, 0, true);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xBADF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, client2->steps.size());
    TS_ASSERT_EQUALS(1, client0->asyncStep);
    TS_ASSERT_EQUALS(1, client1->asyncStep);
    TS_ASSERT_EQUALS(1, client2->asyncStep);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client2->disconnectReason);
  }

  void test_AsyncSendFakeStepsWhileHandlingAsync()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link);

    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client0->lastConfirmedStep);
    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client1->lastConfirmedStep);
    TS_ASSERT_EQUALS(NCore::INVALID_STEP, client2->lastConfirmedStep);

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, client2->steps.size());

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xBADF00D);

    TS_ASSERT_EQUALS(0, client0->blockedStepsCount);
    TS_ASSERT_EQUALS(0, client1->blockedStepsCount);
    TS_ASSERT_EQUALS(0, client2->blockedStepsCount);

    const int asyncDelay = 10;
    for (int i = 0; i < asyncDelay; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(i+1, client0->blockedStepsCount);
      TS_ASSERT_EQUALS(i+1, client1->blockedStepsCount);
      TS_ASSERT_EQUALS(i+1, client2->blockedStepsCount);
    }

    p->OnFinishStep(clientId2, 1, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(asyncDelay, client0->blockedStepsCount);
    TS_ASSERT_EQUALS(asyncDelay, client1->blockedStepsCount);
    TS_ASSERT_EQUALS(asyncDelay, client2->blockedStepsCount);
    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client2->steps.size());

    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(1, client1->asyncStep);

    p->Step();

    TS_ASSERT_EQUALS(asyncDelay, client0->blockedStepsCount);
    TS_ASSERT_EQUALS(asyncDelay, client1->blockedStepsCount);
    TS_ASSERT_EQUALS(asyncDelay, client2->blockedStepsCount);
    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client2->steps.size());
  }

  void test_ConfigFastReconnectEnabled()
  {
    Peered::SchedulerData data1;
    data1.sessionSettings.fastReconnectReserveSteps = 0; // = 0 steps = Disabled
    StrongMT<Peered::CommandsScheduler> p0 = Create(data1, 0, 0,FillClientsAscending(1));

    StrongMT<test::MockClient> client0 = new test::MockClient();
    AddClient(p0, "test0", 0, client0, true);
    TS_ASSERT_EQUALS(false, client0->fastReconnectEnabled);

    Peered::SchedulerData data2;
    data2.sessionSettings.fastReconnectReserveSteps = 100; // = 100 steps = Enabled
    StrongMT<Peered::CommandsScheduler> p1 = Create(data2, 0, 0,FillClientsAscending(1));

    StrongMT<test::MockClient> client1 = new test::MockClient();
    AddClient(p1, "test1", 0, client1, true);
    TS_ASSERT_EQUALS(true, client1->fastReconnectEnabled);
  }

  void test_StatisticsCommands()
  {
    //NOTE: breakpoints in this test will lead to different cmd per second statistics and asserts as the result

    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    objects.statisticsWrapper = statisticsWrapper;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientIdx0 = AddClient(p, "test0", 55, client0, true);
    int clientIdx1 = AddClient(p, "test1", 56, client1, true);

    const int commandSize = 11;
    char commandData[commandSize];
    test::FormatCommand(&commandData, 55, "cmd");
    rpc::MemoryBlock command(commandData, commandSize);
    p->SendCommand(clientIdx0, command, true);

    p->Step();
    TS_ASSERT_EQUALS(0, client0->steps[0].step);
    TS_ASSERT_EQUALS(1, client0->steps[0].commands.size());
    TS_ASSERT_EQUALS(commandSize, client0->steps[0].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData, client0->steps[0].commands[0].memory, commandSize);

    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(1, client0->steps[1].step);
    TS_ASSERT_EQUALS(0, client0->steps[1].commands.size());

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 55, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    const int commandSize1 = 13;
    char commandData1[commandSize1];
    test::FormatCommand(&commandData1, 55, "cmd55");
    rpc::MemoryBlock command1(commandData1, commandSize1);
    p->SendCommand(clientIdx0, command0, true);
    p->SendCommand(clientIdx0, command1, true);
    p->Step();
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(2, client0->steps[2].commands.size());

    TS_ASSERT_EQUALS(commandSize0, client0->steps[2].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, client0->steps[2].commands[0].memory, commandSize0);

    TS_ASSERT_EQUALS(commandSize1, client0->steps[2].commands[1].size);
    TS_ASSERT_SAME_DATA(commandData1, client0->steps[2].commands[1].memory, commandSize1);

    Sleep( 1100 ); // Just to make at least 1 second for cmd per second statistics

    p->OnGameFinish(clientIdx0, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientIdx1, 1, GetFinishData(lobby::ETeam::Team1));

    // Check in-out commands traffic size
    TS_ASSERT_EQUALS(commandSize + commandSize0 + commandSize1, statisticsWrapper->traffic.totalIn);
    int totalOutExpected = (commandSize + commandSize0 + commandSize1 + 2*sizeof(Peered::BriefClientInfo)) * 2; // 3 cmds and 2 statuses for 2 clients
    TS_ASSERT_EQUALS(totalOutExpected, statisticsWrapper->traffic.totalOut);
    TS_ASSERT_EQUALS(totalOutExpected / 2, statisticsWrapper->traffic.avgOutPerStep); // Total expected output / number of seps with data
    int maxOutPerStepExpected = (commandSize + 2*sizeof(Peered::BriefClientInfo)) * 2; // 1 cmd and 2 statuses for 2 clients
    TS_ASSERT_EQUALS(maxOutPerStepExpected, statisticsWrapper->traffic.maxOutPerStep);

    // Check commands per seond counters
    TS_ASSERT_EQUALS(3, statisticsWrapper->traffic.maxCmdPerSecond);
    TS_ASSERT_LESS_THAN(EPS_VALUE, statisticsWrapper->traffic.avgCmdPerSecond); // 0 < avgCmdPerSecond <= 3
    TS_ASSERT_LESS_THAN_EQUALS(statisticsWrapper->traffic.avgCmdPerSecond, 3.0f);

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(0, statisticsWrapper->GetStatusesDelta());
  }

  void test_StatisticsReconnect()
  {
    const int snapshotChunkSize = 5;
    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    data.sessionSettings.reconnectEnabled = true;
    objects.statisticsWrapper = statisticsWrapper;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientIdx0 = AddClient(p, "test0", 55, client0, true);
    int clientIdx1 = AddClient(p, "test1", 56, client1, true);

    p->Step();
    p->Step();

    p->OnFinishStep(clientIdx0, 0, 0xF00D);
    p->OnFinishStep(clientIdx1, 0, 0xF00D);
    client1->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());

    p->OnFinishStep(clientIdx0, 1, 0xF00D);
    p->OnRejoinClient(56);
    int clientIdxR = AddClient(p, "test1", 56, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    p->RequestWorldData(clientIdxR);
    p->OnFinishStep(clientIdx0, 2, 0xF00D);
    p->Step();

    nstl::vector<byte> part1;
    nstl::vector<byte> part2;
    FillDataPartAscending(part1, snapshotChunkSize, 0);
    FillDataPartAscending(part2, snapshotChunkSize, snapshotChunkSize);
    {
      rpc::MemoryBlock worldDataPart1(part1.begin(), part1.size());
      rpc::MemoryBlock worldDataPart2(part2.begin(), part2.size());
      Peered::WorldDataInfo worldDataInfo(3, 2);
      client0->serverReconnect->SendWorldDataInfo(clientIdx0, worldDataInfo);
      client0->serverReconnect->SendWorldDataPart(clientIdx0, worldDataPart1);
      client0->serverReconnect->SendWorldDataPart(clientIdx0, worldDataPart2);
    }
    p->OnFinishStep(clientIdx0, 3, 0xF00D);
    p->Step();

    p->OnClientReady(clientIdxR);
    p->OnFinishStep(clientIdx0, 4, 0xF00D);
    p->OnFinishStep(clientIdx1, 3, 0xF00D);
    p->OnFinishStep(clientIdx1, 4, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(3, clientR->steps.size());

    // Check reconnect event report
    TS_ASSERT_EQUALS(1, statisticsWrapper->reconnects.size());
    TS_ASSERT_EQUALS(Peered::EReconnectType::Normal, statisticsWrapper->reconnects[0].reconnectType);
    TS_ASSERT_EQUALS(Peered::EReconnectResult::Success, statisticsWrapper->reconnects[0].resultCode);
    TS_ASSERT_EQUALS(56, statisticsWrapper->reconnects[0].userId);
    TS_ASSERT_EQUALS(6, statisticsWrapper->reconnects[0].currentStep);

    p->OnGameFinish(clientIdx0, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientIdx1, 1, GetFinishData(lobby::ETeam::Team1));

    // Check reconnect traffic report
    int reconnectInOutExpected = snapshotChunkSize*2; // We sent 2 chunks of data with same size
    TS_ASSERT_EQUALS(reconnectInOutExpected, statisticsWrapper->traffic.totalInReconnect);
    TS_ASSERT_EQUALS(reconnectInOutExpected, statisticsWrapper->traffic.avgOutReconnect);
    TS_ASSERT_EQUALS(reconnectInOutExpected, statisticsWrapper->traffic.maxOutReconnect);
    TS_ASSERT_EQUALS(reconnectInOutExpected, statisticsWrapper->traffic.totalOutReconnect);

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(0, statisticsWrapper->GetStatusesDelta());
  }

  void test_StatisticsLags()
  {
    //NOTE: breakpoints in this test will lead to different cmd per second statistics and asserts as the result

    Peered::SchedulerData data;
    SchedulerObjects objects;
    StrongMT<test::MockPeeredStatistics> statisticsWrapper = new test::MockPeeredStatistics();
    objects.statisticsWrapper = statisticsWrapper;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    AddClient(p, "test0", 55, client0, true);
    AddClient(p, "test1", 56, client1, true);

    for (int i = 0; i < 25; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(i+1, client0->steps.size());
      TS_ASSERT_EQUALS(i+1, client1->steps.size());
      Sleep(100);
    }

    Sleep(1000); // Just to make at least 1 second of lag

    for (int i = 25; i <= 50; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(i+1, client0->steps.size());
      TS_ASSERT_EQUALS(i+1, client1->steps.size());
      Sleep(100);
    }

    TS_ASSERT_EQUALS(1, statisticsWrapper->lags.size());
    TS_ASSERT_EQUALS(50, statisticsWrapper->lags[0].currentStep);
    TS_ASSERT_LESS_THAN(1000, statisticsWrapper->lags[0].stepTimeMax);
    TS_ASSERT_LESS_THAN(0, statisticsWrapper->lags[0].stepTimeMin);
    TS_ASSERT_LESS_THAN(0, statisticsWrapper->lags[0].stepTimeAvg);
    TS_ASSERT_LESS_THAN(1, statisticsWrapper->lags[0].stepCount);
  }

  void test_ReconnectGapOddSuccess()
  {
    const int snapshotChunkSize = 5;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    const int disconnectionGap = 20;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,0, 0, disconnectionGap, 0, 1, 0, 0, 0, snapshotChunkSize);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    // Current client logic will report step only when the second is received
    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->RequestWorldData(clientIdR);
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->Step();

    nstl::vector<byte> part1;
    nstl::vector<byte> part2;
    FillDataPartAscending(part1, snapshotChunkSize, 0);
    FillDataPartAscending(part2, snapshotChunkSize, snapshotChunkSize);
    {
      rpc::MemoryBlock worldDataPart1(part1.begin(), part1.size());
      rpc::MemoryBlock worldDataPart2(part2.begin(), part2.size());
      Peered::WorldDataInfo worldDataInfo(5, 2);
      client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    }
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xF00D);
    p->Step();

    for (int i = 0; i < disconnectionGap; ++i)
    {
      p->OnFinishStep(clientId0, 5 + i, 0xF00D);
      p->OnFinishStep(clientId1, 5 + i, 0xF00D);
      p->Step();
    }

    p->OnFinishStep(clientId0, 5 + disconnectionGap, 0xF00D);
    p->OnFinishStep(clientId1, 5 + disconnectionGap, 0xF00D);
    p->OnClientReady(clientIdR);
    p->Step();

    int curStep = 6 + disconnectionGap;
    int curStepR = 5;
    for (int i = 0; curStepR < curStep; ++i)
    {
      for (int j = 0; j < 2; ++j)
      {
        p->OnFinishStep(clientIdR, curStepR, 0xF00D);
        ++curStepR;
      }
      p->OnFinishStep(clientId0, curStep, 0xF00D);
      p->OnFinishStep(clientId1, curStep, 0xF00D);
      ++curStep;
      p->Step();
      TS_ASSERT_EQUALS(9, client0->clientStatuses.size());
      TS_ASSERT_EQUALS(9, client1->clientStatuses.size());
      TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR->disconnectReason);
    }
  }

  void test_ReconnectGapOddFail()
  {
    const int snapshotChunkSize = 5;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    const int disconnectionGap = 20;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,0, 0, disconnectionGap, 0, 1, 0, 0, 0, snapshotChunkSize);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    // Current client logic will report step only when the second is received
    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    client2->status = rpc::Disconnected;
    p->Step();

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnRejoinClient(57);
    int clientIdR = AddClient(p, "test2", 57, clientR, false);
    p->Step();

    p->RequestWorldData(clientIdR);
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->Step();

    nstl::vector<byte> part1;
    nstl::vector<byte> part2;
    FillDataPartAscending(part1, snapshotChunkSize, 0);
    FillDataPartAscending(part2, snapshotChunkSize, snapshotChunkSize);
    {
      rpc::MemoryBlock worldDataPart1(part1.begin(), part1.size());
      rpc::MemoryBlock worldDataPart2(part2.begin(), part2.size());
      Peered::WorldDataInfo worldDataInfo(5, 2);
      client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    }
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xF00D);
    p->Step();

    for (int i = 0; i < disconnectionGap; ++i)
    {
      p->OnFinishStep(clientId0, 5 + i, 0xF00D);
      p->OnFinishStep(clientId1, 5 + i, 0xF00D);
      p->Step();
    }

    p->OnFinishStep(clientId0, 5 + disconnectionGap, 0xF00D);
    p->OnFinishStep(clientId1, 5 + disconnectionGap, 0xF00D);
    p->OnClientReady(clientIdR);

    int curStep = 6 + disconnectionGap;
    int curStepR = 5;
    for (int i = 0; i < disconnectionGap; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(9, client0->clientStatuses.size());
      TS_ASSERT_EQUALS(9, client1->clientStatuses.size());
      TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR->disconnectReason);

      p->OnFinishStep(clientIdR, curStepR, 0xF00D);
      ++curStepR;
      p->OnFinishStep(clientId0, curStep, 0xF00D);
      p->OnFinishStep(clientId1, curStep, 0xF00D);
      ++curStep;
    }
    p->Step();
    TS_ASSERT_EQUALS(10, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(10, client1->clientStatuses.size());
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ClientPerfomance, clientR->disconnectReason);
  }

  void test_FastReconnectGapOddSuccess()
  {
    int loop = 20;
    int step = 0;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    const int disconnectionGap = 20;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,
                                                    0, 0, disconnectionGap, 0, 2, 0, 0, 0, 1024, 4096, true, 
                                                    0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 0, 0, 
                                                    false, 500, 0, 0, 0, 600);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    client2->status = rpc::Disconnected;

    for (int i = 0; i < disconnectionGap - 2; ++i)
    {
      p->Step();
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      ++step;
    }
    p->Step();

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    int stepR = loop + 2;
    p->AddClientFast(57, clientId2, clientR, stepR);
    p->Step();

    // Client will report the last step's CRC (step before fast reconnect) when it resumes
    p->OnFinishStep(clientId2, stepR - 1, 0xF00D);
    
    for (int i = 0; stepR < step; ++i)
    {
      for (int j = 0; j < 2; ++j)
      {
        p->OnFinishStep(clientId2, stepR, 0xF00D);
        ++stepR;
      }
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      ++step;
      p->Step();
      TS_ASSERT_EQUALS(6, client0->clientStatuses.size());
      TS_ASSERT_EQUALS(6, client1->clientStatuses.size());
      TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR->disconnectReason);
    }
  }

  void test_FastReconnectGapOddFail()
  {
    int loop = 20;
    int step = 0;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    const int disconnectionGap = 20;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(55, 56, 57), link,
                                                    0, 0, disconnectionGap, 0, 2, 0, 0, 0, 1024, 4096, true, 
                                                    0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 0, 0, 
                                                    false, 500, 0, 0, 0, 600);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    for (int i = 0; i < loop; ++i)
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
      p->Step();
    }

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    client2->status = rpc::Disconnected;

    for (int i = 0; i < disconnectionGap; ++i)
    {
      p->Step();
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      ++step;
    }
    p->Step();

    p->OnFinishStep(clientId0, step, 0xF00D);
    p->OnFinishStep(clientId1, step, 0xF00D);
    ++step;
    int stepR = loop + 2;
    p->AddClientFast(57, clientId2, clientR, stepR);

    // Client will report the last step's CRC (step before fast reconnect) when it resumes
    p->OnFinishStep(clientId2, stepR - 1, 0xF00D);

    for (int i = 0; i < disconnectionGap; ++i)
    {
      p->Step();
      TS_ASSERT_EQUALS(6, client0->clientStatuses.size());
      TS_ASSERT_EQUALS(6, client1->clientStatuses.size());
      TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientR->disconnectReason);
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, stepR, 0xF00D);
      ++step;
      ++stepR;
    }
    p->Step();
    TS_ASSERT_EQUALS(7, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(7, client1->clientStatuses.size());
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ClientPerfomance, clientR->disconnectReason);
  }

  void test_FastReconnectWithLaggingClient()
  {
    // This case is carefully reproduced and simplified from case 1 in NUM_TASK
    int step = 0;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockCommandsLog> log = new test::MockCommandsLog;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2400, 0, FillClients(55, 56, 57), link,
                                                    0, 0, 0, 0, 2, 0, 0, 0, 1024, 4096, true, 
                                                    0, 0, 0, 64000, true, 300, 128, 64000, false, 1, 1, 0, 0, 
                                                    false, 500, 0, 0, 0, 500);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);

    for (int i = 0; i < 33; ++i)
    {
      p->Step();
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->OnFinishStep(clientId2, step, 0xF00D);
      ++step;
    }

    for (int i = 0; i < 219; ++i)
    {
      p->Step();
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      ++step;
    }

    client2->status = rpc::Disconnected;

    for (int i = 0; i < 183; ++i)
    {
      p->Step();
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      ++step;
    }

    for (int i = 0; i < 119; ++i)
    {
      p->Step();
      p->OnFinishStep(clientId0, step, 0xF00D);
      ++step;
    }

    p->AddClientFast(57, clientId2, clientR, 36);

    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientR->disconnectReason);

    p->Step();

    TS_ASSERT_EQUALS(4, client0->clientStatuses.size()); // Active*3 + DisconnectedByClient

    for (int i = 0; i < 519; ++i)
    {
      p->OnFinishStep(clientId2, 8108 + i, 0xF00D);
    }

    TS_ASSERT_EQUALS(4, client0->clientStatuses.size()); // Active*3 + DisconnectedByClient

    p->Step();

    TS_ASSERT_EQUALS(4, client0->clientStatuses.size()); // Active*3 + DisconnectedByClient
  }

  void test_SpectatorAfterGameStart()
  {
    const int snapshotChunkSize = 5;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(0, client0->simulationStartStep);
    TS_ASSERT_EQUALS(0, client1->simulationStartStep);
    TS_ASSERT_EQUALS(0, client2->simulationStartStep);

    TS_ASSERT_EQUALS(3, client0->clientStatuses.size()); // Active*3
    TS_ASSERT_EQUALS(3, link->clientStatuses.size()); // Connecting*3

    p->AddSpectator(58, L"testSpectator");
    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->Step();

    int clientIdS = AddClient(p, "spect0", 58, clientS, false);

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    TS_ASSERT_EQUALS(4, client2->steps.size());
    TS_ASSERT_EQUALS(0, clientS->steps.size());
    TS_ASSERT_EQUALS(true, clientS->isReconnecting);

    p->RequestWorldData(clientIdS);
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnFinishStep(clientId2, 2, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    TS_ASSERT_EQUALS(false, client2->worldDataRequested);
    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client1->steps.size());
    TS_ASSERT_EQUALS(5, client2->steps.size());
    TS_ASSERT_EQUALS(0, clientS->steps.size());

    nstl::vector<byte> part1;
    nstl::vector<byte> part2;
    FillDataPartAscending(part1, snapshotChunkSize, 0);
    FillDataPartAscending(part2, snapshotChunkSize, snapshotChunkSize);
    {
      rpc::MemoryBlock worldDataPart1(part1.begin(), part1.size());
      rpc::MemoryBlock worldDataPart2(part2.begin(), part2.size());
      Peered::WorldDataInfo worldDataInfo(3, 2);
      client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    }
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->OnFinishStep(clientId2, 3, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(2, clientS->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(2, clientS->mockClientReconnect->worldDataInfo.partsCount);
    TS_ASSERT_EQUALS(3, clientS->mockClientReconnect->worldDataInfo.step);
    TS_ASSERT_SAME_DATA(part1.begin(), clientS->mockClientReconnect->worldDataParts[0].memory, part1.size());
    TS_ASSERT_SAME_DATA(part2.begin(), clientS->mockClientReconnect->worldDataParts[1].memory, part2.size());
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xF00D);
    p->OnFinishStep(clientId2, 4, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(7, client1->steps.size());
    TS_ASSERT_EQUALS(7, client2->steps.size());
    TS_ASSERT_EQUALS(2, clientS->steps.size());
    TS_ASSERT_EQUALS(false, client0->spectate);
    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->OnFinishStep(clientId1, 5, 0xF00D);
    p->OnFinishStep(clientId2, 5, 0xF00D);

    TS_ASSERT_EQUALS(0, client0->spectatorNickname.length());
    TS_ASSERT_EQUALS(0, client1->spectatorNickname.length());
    TS_ASSERT_EQUALS(0, client2->spectatorNickname.length());
    p->OnClientReady(clientIdS);
    TS_ASSERT_EQUALS(wcslen(L"testSpectator"), client0->spectatorNickname.length());
    TS_ASSERT_EQUALS(wcslen(L"testSpectator"), client1->spectatorNickname.length());
    TS_ASSERT_EQUALS(wcslen(L"testSpectator"), client2->spectatorNickname.length());
    TS_ASSERT_SAME_DATA(L"testSpectator", client0->spectatorNickname.c_str(), 2*client0->spectatorNickname.length());
    TS_ASSERT_SAME_DATA(L"testSpectator", client0->spectatorNickname.c_str(), 2*client1->spectatorNickname.length());
    TS_ASSERT_SAME_DATA(L"testSpectator", client0->spectatorNickname.c_str(), 2*client2->spectatorNickname.length());
    TS_ASSERT_EQUALS(true, client0->spectate);
    TS_ASSERT_EQUALS(true, client1->spectate);
    TS_ASSERT_EQUALS(true, client2->spectate);
    p->Step();

    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(8, client1->steps.size());
    TS_ASSERT_EQUALS(8, client2->steps.size());
    TS_ASSERT_EQUALS(4, clientS->steps.size());
    // Should receive current status of all clients on rconnect
    TS_ASSERT_EQUALS(3, clientS->clientStatuses.size());
    TS_ASSERT_EQUALS(55, clientS->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::Active, clientS->clientStatuses[0].status);
    TS_ASSERT_EQUALS(56, clientS->clientStatuses[1].clientId);
    TS_ASSERT_EQUALS(Peered::Active, clientS->clientStatuses[1].status);
    TS_ASSERT_EQUALS(57, clientS->clientStatuses[2].clientId);
    TS_ASSERT_EQUALS(Peered::Active, clientS->clientStatuses[2].status);
    //Reconnected client must confirm the step it reconnected on (step of the applied world snapshot)
    p->OnFinishStep(clientId0, 6, 0xF00D);
    p->OnFinishStep(clientId1, 6, 0xF00D);
    p->OnFinishStep(clientId2, 6, 0xF00D);
    p->OnFinishStep(clientIdS, 3, 0xF00D);
    p->OnFinishStep(clientIdS, 4, 0xF00D);
    p->OnFinishStep(clientIdS, 5, 0xF00D);
    p->OnFinishStep(clientIdS, 6, 0xF00D);
    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 55, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    p->SendCommand(clientId0, command0, true);
    p->Step();

    p->OnFinishStep(clientId0, 7, 0xF00D);
    p->OnFinishStep(clientId1, 7, 0xF00D);
    p->OnFinishStep(clientId2, 7, 0xF00D);
    p->OnFinishStep(clientIdS, 7, 0xF00D);
    TS_ASSERT_EQUALS(9, client0->steps.size());
    TS_ASSERT_EQUALS(1, client0->steps[8].commands.size());
    TS_ASSERT_EQUALS(commandSize0, client0->steps[8].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, client0->steps[8].commands[0].memory, commandSize0);
    TS_ASSERT_EQUALS(9, client1->steps.size());
    TS_ASSERT_EQUALS(9, client2->steps.size());
    TS_ASSERT_EQUALS(5, clientS->steps.size());
    TS_ASSERT_EQUALS(1, clientS->steps[4].commands.size());
    TS_ASSERT_EQUALS(commandSize0, clientS->steps[4].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, clientS->steps[4].commands[0].memory, commandSize0);

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(client1->steps);
    CheckStepsConsistency(client2->steps);
    CheckStepsConsistency(clientS->steps);

    TS_ASSERT_EQUALS(6, client0->clientStatuses.size()); // Active*3*2 (statuses of all clients are sent on spectator's reconnect)
    TS_ASSERT_EQUALS(4, link->clientStatuses.size()); // Connecting*3 + Connecting (spectator)

    p->OnGameFinish(clientId0, 8, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 8, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 8, GetFinishData(lobby::ETeam::Team1));
    // Spectator's session results aren't used and aren't checked. Only the step number is used.
    p->OnGameFinish(clientIdS, 8, GetFinishData(lobby::ETeam::Team2));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    // No client statistics for the spectator
    TS_ASSERT_EQUALS(3, link->clientStatistics.size());
    TS_ASSERT_EQUALS(55, link->clientStatistics[0].clientId);
    TS_ASSERT_EQUALS(56, link->clientStatistics[1].clientId);
    TS_ASSERT_EQUALS(57, link->clientStatistics[2].clientId);
  }

  void test_SpectatorBeforeGameStart()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    int clientId2 = AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(0, client0->clientStatuses.size()); // None is active yet
    TS_ASSERT_EQUALS(3, link->clientStatuses.size()); // Connecting*3

    p->AddSpectator(58, L"testSpectator");
    p->Step();

    int clientIdS = AddClient(p, "spect0", 58, clientS, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientId2);
    p->Step();

    TS_ASSERT_EQUALS(0, client0->clientStatuses.size()); // Still none active
    TS_ASSERT_EQUALS(4, link->clientStatuses.size()); // Connecting*4

    // We are waiting for the spectator
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client2->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientS->simulationStartStep);

    TS_ASSERT_EQUALS(0, client0->steps.size());
    TS_ASSERT_EQUALS(0, client1->steps.size());
    TS_ASSERT_EQUALS(0, client2->steps.size());
    TS_ASSERT_EQUALS(0, clientS->steps.size());
    TS_ASSERT_EQUALS(false, clientS->isReconnecting);

    // Lets make few steps
    for (int i = 0; i < 100; ++i)
      p->Step();

    // We are still waiting for the spectator
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client2->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientS->simulationStartStep);

    TS_ASSERT_EQUALS(0, client0->steps.size());
    TS_ASSERT_EQUALS(0, client1->steps.size());
    TS_ASSERT_EQUALS(0, client2->steps.size());
    TS_ASSERT_EQUALS(0, clientS->steps.size());

    TS_ASSERT_EQUALS(false, client0->spectate);

    p->OnClientReady(clientIdS);

    TS_ASSERT_EQUALS(true, client0->spectate);

    TS_ASSERT_EQUALS(0, client0->simulationStartStep);
    TS_ASSERT_EQUALS(0, client1->simulationStartStep);
    TS_ASSERT_EQUALS(0, client2->simulationStartStep);
    TS_ASSERT_EQUALS(0, clientS->simulationStartStep);
    p->Step();

    TS_ASSERT_EQUALS(3, client0->clientStatuses.size()); // Active*3
    TS_ASSERT_EQUALS(4, link->clientStatuses.size()); // Connecting*4
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientIdS, 0, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, client2->steps.size());
    TS_ASSERT_EQUALS(3, clientS->steps.size());

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);
    p->OnFinishStep(clientIdS, 1, 0xF00D);
    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 55, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    p->SendCommand(clientId0, command0, true);
    p->Step();

    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnFinishStep(clientId2, 2, 0xF00D);
    p->OnFinishStep(clientIdS, 2, 0xF00D);
    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(1, client0->steps[3].commands.size());
    TS_ASSERT_EQUALS(commandSize0, client0->steps[3].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, client0->steps[3].commands[0].memory, commandSize0);
    TS_ASSERT_EQUALS(4, client1->steps.size());
    TS_ASSERT_EQUALS(4, client2->steps.size());
    TS_ASSERT_EQUALS(4, clientS->steps.size());
    TS_ASSERT_EQUALS(1, clientS->steps[3].commands.size());
    TS_ASSERT_EQUALS(commandSize0, clientS->steps[3].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, clientS->steps[3].commands[0].memory, commandSize0);

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(client1->steps);
    CheckStepsConsistency(client2->steps);
    CheckStepsConsistency(clientS->steps);

    p->OnGameFinish(clientId0, 3, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 3, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 3, GetFinishData(lobby::ETeam::Team1));
    // Spectator's session results aren't used and aren't checked. Only the step number is used.
    p->OnGameFinish(clientIdS, 3, GetFinishData(lobby::ETeam::Team2));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    // No client statistics for the spectator
    TS_ASSERT_EQUALS(3, link->clientStatistics.size());
    TS_ASSERT_EQUALS(55, link->clientStatistics[0].clientId);
    TS_ASSERT_EQUALS(56, link->clientStatistics[1].clientId);
    TS_ASSERT_EQUALS(57, link->clientStatistics[2].clientId);
  }

  void test_SpectatorBeforeGameStartAndReconnect()
  {
    const int snapshotChunkSize = 5;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    int clientId2 = AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(0, client0->clientStatuses.size()); // None is active yet
    TS_ASSERT_EQUALS(3, link->clientStatuses.size()); // Connecting*3

    p->AddSpectator(58, L"testSpectator");
    p->Step();

    int clientIdS = AddClient(p, "spect0", 58, clientS, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientId2);
    p->Step();

    TS_ASSERT_EQUALS(0, client0->clientStatuses.size()); // Still none active
    TS_ASSERT_EQUALS(4, link->clientStatuses.size()); // Connecting*4

    // We are waiting for the spectator
    TS_ASSERT_EQUALS(-1, client0->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client1->simulationStartStep);
    TS_ASSERT_EQUALS(-1, client2->simulationStartStep);
    TS_ASSERT_EQUALS(-1, clientS->simulationStartStep);

    TS_ASSERT_EQUALS(0, client0->steps.size());
    TS_ASSERT_EQUALS(0, client1->steps.size());
    TS_ASSERT_EQUALS(0, client2->steps.size());
    TS_ASSERT_EQUALS(0, clientS->steps.size());
    TS_ASSERT_EQUALS(false, clientS->isReconnecting);

    p->OnClientReady(clientIdS);

    TS_ASSERT_EQUALS(0, client0->simulationStartStep);
    TS_ASSERT_EQUALS(0, client1->simulationStartStep);
    TS_ASSERT_EQUALS(0, client2->simulationStartStep);
    TS_ASSERT_EQUALS(0, clientS->simulationStartStep);
    p->Step();

    TS_ASSERT_EQUALS(3, client0->clientStatuses.size()); // Active*3
    TS_ASSERT_EQUALS(4, link->clientStatuses.size()); // Connecting*4
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientIdS, 0, 0xF00D);
    clientS->status = rpc::Disconnected;
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, client2->steps.size());
    TS_ASSERT_EQUALS(2, clientS->steps.size());

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);

    TS_ASSERT_EQUALS(3, client0->clientStatuses.size()); // Active*3
    TS_ASSERT_EQUALS(5, link->clientStatuses.size()); // Connecting*4 + Disconnected

    p->OnRejoinClient(58);
    int clientIdR = AddClient(p, "spect0", 58, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    TS_ASSERT_EQUALS(4, client2->steps.size());
    TS_ASSERT_EQUALS(0, clientR->steps.size());
    TS_ASSERT_EQUALS(true, clientR->isReconnecting);
    p->RequestWorldData(clientIdR);
    p->OnFinishStep(clientId0, 2, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnFinishStep(clientId2, 2, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(true, client0->worldDataRequested);
    TS_ASSERT_EQUALS(false, client1->worldDataRequested);
    TS_ASSERT_EQUALS(false, client2->worldDataRequested);
    TS_ASSERT_EQUALS(5, client0->steps.size());
    TS_ASSERT_EQUALS(5, client1->steps.size());
    TS_ASSERT_EQUALS(5, client2->steps.size());
    TS_ASSERT_EQUALS(0, clientR->steps.size());

    nstl::vector<byte> part1;
    nstl::vector<byte> part2;
    FillDataPartAscending(part1, snapshotChunkSize, 0);
    FillDataPartAscending(part2, snapshotChunkSize, snapshotChunkSize);
    {
      rpc::MemoryBlock worldDataPart1(part1.begin(), part1.size());
      rpc::MemoryBlock worldDataPart2(part2.begin(), part2.size());
      Peered::WorldDataInfo worldDataInfo(3, 2);
      client0->serverReconnect->SendWorldDataInfo(clientId0, worldDataInfo);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart1);
      client0->serverReconnect->SendWorldDataPart(clientId0, worldDataPart2);
    }
    p->OnFinishStep(clientId0, 3, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->OnFinishStep(clientId2, 3, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(2, clientR->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(2, clientR->mockClientReconnect->worldDataInfo.partsCount);
    TS_ASSERT_EQUALS(3, clientR->mockClientReconnect->worldDataInfo.step);
    TS_ASSERT_SAME_DATA(part1.begin(), clientR->mockClientReconnect->worldDataParts[0].memory, part1.size());
    TS_ASSERT_SAME_DATA(part2.begin(), clientR->mockClientReconnect->worldDataParts[1].memory, part2.size());
    p->OnFinishStep(clientId0, 4, 0xF00D);
    p->OnFinishStep(clientId1, 4, 0xF00D);
    p->OnFinishStep(clientId2, 4, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, client0->steps.size());
    TS_ASSERT_EQUALS(7, client1->steps.size());
    TS_ASSERT_EQUALS(7, client2->steps.size());
    TS_ASSERT_EQUALS(2, clientR->steps.size());
    p->OnFinishStep(clientId0, 5, 0xF00D);
    p->OnFinishStep(clientId1, 5, 0xF00D);
    p->OnFinishStep(clientId2, 5, 0xF00D);
    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(8, client0->steps.size());
    TS_ASSERT_EQUALS(8, client1->steps.size());
    TS_ASSERT_EQUALS(8, client2->steps.size());
    TS_ASSERT_EQUALS(4, clientR->steps.size());
    //Reconnected client must confirm the step it reconnected on (step of the applied world snapshot)
    p->OnFinishStep(clientId0, 6, 0xF00D);
    p->OnFinishStep(clientId1, 6, 0xF00D);
    p->OnFinishStep(clientId2, 6, 0xF00D);
    p->OnFinishStep(clientIdR, 3, 0xF00D);
    p->OnFinishStep(clientIdR, 4, 0xF00D);
    p->OnFinishStep(clientIdR, 5, 0xF00D);
    p->OnFinishStep(clientIdR, 6, 0xF00D);

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 55, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    p->SendCommand(clientId0, command0, true);
    p->Step();

    p->OnFinishStep(clientId0, 7, 0xF00D);
    p->OnFinishStep(clientId1, 7, 0xF00D);
    p->OnFinishStep(clientId2, 7, 0xF00D);
    p->OnFinishStep(clientIdR, 7, 0xF00D);
    TS_ASSERT_EQUALS(9, client0->steps.size());
    TS_ASSERT_EQUALS(1, client0->steps[8].commands.size());
    TS_ASSERT_EQUALS(commandSize0, client0->steps[8].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, client0->steps[8].commands[0].memory, commandSize0);
    TS_ASSERT_EQUALS(9, client1->steps.size());
    TS_ASSERT_EQUALS(9, client2->steps.size());
    TS_ASSERT_EQUALS(5, clientR->steps.size());
    TS_ASSERT_EQUALS(1, clientR->steps[4].commands.size());
    TS_ASSERT_EQUALS(commandSize0, clientR->steps[4].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, clientR->steps[4].commands[0].memory, commandSize0);

    CheckStepsConsistency(client0->steps);
    CheckStepsConsistency(client1->steps);
    CheckStepsConsistency(client2->steps);
    CheckStepsConsistency(clientR->steps);

    p->OnGameFinish(clientId0, 3, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 3, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 3, GetFinishData(lobby::ETeam::Team1));
    // Spectator's session results aren't used and aren't checked. Only the step number is used.
    p->OnGameFinish(clientIdS, 3, GetFinishData(lobby::ETeam::Team2));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
    // No client statistics for the spectator
    TS_ASSERT_EQUALS(3, link->clientStatistics.size());
    TS_ASSERT_EQUALS(55, link->clientStatistics[0].clientId);
    TS_ASSERT_EQUALS(56, link->clientStatistics[1].clientId);
    TS_ASSERT_EQUALS(57, link->clientStatistics[2].clientId);
  }

  void test_SpectatorWithoutNoticeFromLobby()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    AddClient(p, "test0", 55, client0, false);
    AddClient(p, "test1", 56, client1, false);
    AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(0, client0->clientStatuses.size()); // None is active yet
    TS_ASSERT_EQUALS(3, link->clientStatuses.size()); // Connecting*3

    int clientIdS = AddClient(p, "spect0", 58, clientS, false);

    TS_ASSERT_EQUALS(-1, clientIdS);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ServerError, clientS->disconnectReason);
    TS_ASSERT_EQUALS(0, client0->clientStatuses.size()); // Still none active
    TS_ASSERT_EQUALS(3, link->clientStatuses.size()); // Connecting*3
  }

  void test_SpectatorNoAFK()
  {
    const int afkSteps = 20;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    data.sessionSettings.afkStepsDisconnectCount = afkSteps;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->Step();

    TS_ASSERT_EQUALS(0, client0->clientStatuses.size()); // None is active yet
    TS_ASSERT_EQUALS(2, link->clientStatuses.size()); // Connecting*2

    p->AddSpectator(57, L"testSpectator");
    p->Step();

    int clientIdS = AddClient(p, "spect0", 57, clientS, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientIdS);
    p->Step();
    p->Step();

    for (int i = 0; i < afkSteps - 2; ++i)
    {
      p->OnFinishStep(clientId0, i, 0xF00D);
      p->OnFinishStep(clientId1, i, 0xF00D);
      p->OnFinishStep(clientIdS, i, 0xF00D);
      p->Step();
    }

    TS_ASSERT_EQUALS(afkSteps, client0->steps.size());
    TS_ASSERT_EQUALS(afkSteps, client1->steps.size());
    TS_ASSERT_EQUALS(afkSteps, clientS->steps.size());
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client1->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientS->disconnectReason);
    TS_ASSERT_EQUALS(2, client0->clientStatuses.size()); // Active*2
    TS_ASSERT_EQUALS(3, link->clientStatuses.size()); // Connecting*3

    // Now only client0 sends command, so he will remain in the session with
    // clientS (spectator), while client1 will be disconnected on the next step
    SendNumberedCommand(p, clientId0, 55, "SyncCmd", 0);
    p->Step();

    TS_ASSERT_EQUALS(afkSteps + 1, client0->steps.size()); // Resumes
    TS_ASSERT_EQUALS(afkSteps, client1->steps.size()); // Finished
    TS_ASSERT_EQUALS(afkSteps + 1, clientS->steps.size()); // Resumes
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, client0->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::ClientAway, client1->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientS->disconnectReason);
    TS_ASSERT_EQUALS(3, client0->clientStatuses.size()); // Active*2 + disconnected
    TS_ASSERT_EQUALS(4, link->clientStatuses.size()); // Connecting*3 + disconnected
  }

  void test_SpectatorAsync()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->Step();

    p->AddSpectator(57, L"testSpectator");
    p->Step();

    int clientIdS = AddClient(p, "spect0", 57, clientS, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientIdS);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientS->steps.size());

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientIdS, 0, 0xF00D);
    p->Step();

    // No asyncs yet
    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    TS_ASSERT_EQUALS(-1, client1->asyncStep);
    TS_ASSERT_EQUALS(-1, clientS->asyncStep);

    p->OnFinishStep(clientId0, 1, 0xF00D);
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientIdS, 1, 0xBADF00D);

    // Only spectator got the async info
    TS_ASSERT_EQUALS(-1, client0->asyncStep);
    TS_ASSERT_EQUALS(-1, client1->asyncStep);
    TS_ASSERT_EQUALS( 1, clientS->asyncStep);
    p->Step();

    // Not asynced clients resume the game, while spectator has finished
    TS_ASSERT_EQUALS(4, client0->steps.size());
    TS_ASSERT_EQUALS(4, client1->steps.size());
    TS_ASSERT_EQUALS(3, clientS->steps.size());
    // Active*2, i.e. clients do not receive statuses for spectator
    TS_ASSERT_EQUALS(2, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(55, client0->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[0].status);
    TS_ASSERT_EQUALS(56, client0->clientStatuses[1].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[1].status);
    // Client got the async, so no additioanal reason is sent
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientS->disconnectReason);
    TS_ASSERT_EQUALS(4, link->clientStatuses.size()); // Connecting*3 + disconnected (spectator)
    TS_ASSERT_EQUALS(57, link->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByAsync, link->clientStatuses[3].status);
  }

  void test_SpectatorNoCommands()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->Step();

    p->AddSpectator(57, L"testSpectator");
    p->Step();

    int clientIdS = AddClient(p, "spect0", 57, clientS, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientIdS);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientS->steps.size());

    // Now spectator sends command...
    SendNumberedCommand(p, clientIdS, 57, "SyncCmd", 0);

    p->Step();

    // Active*2, i.e. clients do not receive statuses for spectator
    TS_ASSERT_EQUALS(2, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(55, client0->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[0].status);
    TS_ASSERT_EQUALS(56, client0->clientStatuses[1].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[1].status);

    // Spectator doesn't resume the game
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientS->steps.size());

    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientS->disconnectReason);
    TS_ASSERT_EQUALS(4, link->clientStatuses.size()); // Connecting*3 + disconnected (spectator)
    TS_ASSERT_EQUALS(57, link->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByServer, link->clientStatuses[3].status);
  }

  void test_SpectatorLimit1()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS0 = new test::MockClient();
    StrongMT<test::MockClient> clientS1 = new test::MockClient();
    StrongMT<test::MockClient> clientS2 = new test::MockClient();
    StrongMT<test::MockClient> clientSR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->Step();

    p->AddSpectator(57, L"testSpectator");
    p->AddSpectator(58, L"testSpectator");
    p->Step();

    int clientIdS1 = AddClient(p, "spect1", 58, clientS1, false);
    TS_ASSERT_EQUALS(-1, clientIdS1); // We do not expect spectator with ID 58

    int clientIdS0 = AddClient(p, "spect0", 57, clientS0, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientIdS0);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientS0->steps.size());
    TS_ASSERT_EQUALS(0, clientS1->steps.size());

    p->AddSpectator(59, L"testSpectator");
    int clientIdS2 = AddClient(p, "spect2", 59, clientS2, false);
    TS_ASSERT_EQUALS(-1, clientIdS2); // We do not expect spectator with ID 59 too
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, clientS0->steps.size());
    TS_ASSERT_EQUALS(0, clientS1->steps.size());
    TS_ASSERT_EQUALS(0, clientS2->steps.size());

    clientS0->status = rpc::Disconnected;
    p->Step();

    // We still do not expect any spectator other than 57
    clientIdS1 = AddClient(p, "spect1", 58, clientS1, false);
    TS_ASSERT_EQUALS(-1, clientIdS1);
    clientIdS2 = AddClient(p, "spect2", 59, clientS2, false);
    TS_ASSERT_EQUALS(-1, clientIdS2);

    // 57 is ok - wellcome!
    int clientIdSR = AddClient(p, "spect0", 57, clientSR, false);
    TS_ASSERT_EQUALS(clientIdSR, clientIdS0); // We get the same index
  }

  void test_SpectatorLimit2()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 2;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS0 = new test::MockClient();
    StrongMT<test::MockClient> clientS1 = new test::MockClient();
    StrongMT<test::MockClient> clientS2 = new test::MockClient();
    StrongMT<test::MockClient> clientSR0 = new test::MockClient();
    StrongMT<test::MockClient> clientSR1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->Step();

    p->AddSpectator(57, L"testSpectator1");
    p->AddSpectator(58, L"testSpectator2");
    p->Step();

    int clientIdS1 = AddClient(p, "spect1", 58, clientS1, false);
    TS_ASSERT_DIFFERS(-1, clientIdS1); // This time second spectator is ok

    int clientIdS0 = AddClient(p, "spect0", 57, clientS0, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientIdS0);
    p->OnClientReady(clientIdS1);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientS0->steps.size());
    TS_ASSERT_EQUALS(2, clientS1->steps.size());

    p->AddSpectator(59, L"testSpectator");
    int clientIdS2 = AddClient(p, "spect2", 59, clientS2, false);
    TS_ASSERT_EQUALS(-1, clientIdS2); // We do not expect spectator with ID 59
    p->Step();

    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(3, clientS0->steps.size());
    TS_ASSERT_EQUALS(3, clientS1->steps.size());
    TS_ASSERT_EQUALS(0, clientS2->steps.size());

    clientS0->status = rpc::Disconnected;
    clientS1->status = rpc::Disconnected;
    p->Step();

    // We still do not expect any spectator other than 57 and 58
    clientIdS2 = AddClient(p, "spect2", 59, clientS2, false);
    TS_ASSERT_EQUALS(-1, clientIdS2);

    // 57 and 58 is ok - wellcome!
    int clientIdSR0 = AddClient(p, "spect0", 57, clientSR0, false);
    TS_ASSERT_EQUALS(clientIdSR0, clientIdS0); // We get the same index
    int clientIdSR1 = AddClient(p, "spect1", 58, clientSR1, false);
    TS_ASSERT_EQUALS(clientIdSR1, clientIdS1); // We get the same index
  }

  void test_SpectatorNoLeaver()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    p->Step();

    p->AddSpectator(57, L"testSpectator");
    p->Step();

    int clientIdS = AddClient(p, "spect0", 57, clientS, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientIdS);
    p->Step();
    p->Step();

    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientS->steps.size());

    p->OnGameLeave(clientIdS);
    clientS->status = rpc::Disconnected;
    p->Step();

    // Active*2, i.e. clients do not receive statuses for spectator
    TS_ASSERT_EQUALS(2, client0->clientStatuses.size());
    TS_ASSERT_EQUALS(55, client0->clientStatuses[0].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[0].status);
    TS_ASSERT_EQUALS(56, client0->clientStatuses[1].clientId);
    TS_ASSERT_EQUALS(Peered::Active, client0->clientStatuses[1].status);

    // Spectator doesn't resume the game
    TS_ASSERT_EQUALS(3, client0->steps.size());
    TS_ASSERT_EQUALS(3, client1->steps.size());
    TS_ASSERT_EQUALS(2, clientS->steps.size());

    // Spectator get's DisconnectedByClient but not DisconnectedByClientIntentionally, so he can reconnect if left
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientS->disconnectReason);
    TS_ASSERT_EQUALS(4, link->clientStatuses.size()); // Connecting*3 + disconnected (spectator)
    TS_ASSERT_EQUALS(57, link->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, link->clientStatuses[3].status);
  }

  void test_SpectatorNoRoll()
  {
    const Peered::SAuxData auxData;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockAwardsRequester> awardsRequester = new test::MockAwardsRequester;
    //StrongMT<Peered::IAwardsRequester> awardsRequesterIface = awardsRequester.Get();
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link, 0, &auxData, 0, awardsRequester);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    int clientId2 = AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    p->AddSpectator(58, L"testSpectator");
    p->Step();

    //p->OnRejoinClient(58); // Do we need it?
    int clientIdS = AddClient(p, "spect0", 58, clientS, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientId2);
    p->OnClientReady(clientIdS);
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientIdS, 0, 0xF00D);
    p->Step();

    p->OnGameFinish(clientId0, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 1, GetFinishData(lobby::ETeam::Team1));
    // Spectator's session results aren't used and aren't checked. Only the step number is used.
    p->OnGameFinish(clientIdS, 1, GetFinishData(lobby::ETeam::Team2));

    // Only real player are passed to the awards requester
    TS_ASSERT_EQUALS(3, awardsRequester->clientsInfo.size());
    TS_ASSERT_EQUALS(55, awardsRequester->clientsInfo[0].clientId);
    TS_ASSERT_EQUALS(56, awardsRequester->clientsInfo[1].clientId);
    TS_ASSERT_EQUALS(57, awardsRequester->clientsInfo[2].clientId);
    TS_ASSERT_EQUALS(3, awardsRequester->clientsStatistics.size());
    TS_ASSERT_EQUALS(55, awardsRequester->clientsStatistics[0].clientId);
    TS_ASSERT_EQUALS(56, awardsRequester->clientsStatistics[1].clientId);
    TS_ASSERT_EQUALS(57, awardsRequester->clientsStatistics[2].clientId);

    // Fill dummy awards with user IDs and one (unspecified) talent
    for (int i = 0; i < 3; ++i)
    {
      roll::SUserAward & userAward = awardsRequester->awards.push_back();
      userAward.userId = 55 + i;
      roll::SAwardInfo & awardInfo = userAward.awards.push_back();
      awardInfo.type = roll::EAwardType::Talent;
      awardInfo.count = 1;
    }
    awardsRequester->isAwardsReceived = true;

    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
  }

  void test_SpectatorReconnectFromSpectator()
  {
    const int snapshotChunkSize = 5;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    int clientId2 = AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    p->AddSpectator(58, L"testSpectator");
    p->Step();

    int clientIdS = AddClient(p, "spect0", 58, clientS, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientId2);
    p->OnClientReady(clientIdS);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientIdS, 0, 0xF00D);
    client0->status = rpc::Disconnected;
    p->Step();

    // From now we will stop to confirm steps for all clients
    // except for the spectator, therfore he will be used for reconnect
    p->OnFinishStep(clientIdS, 1, 0xF00D);
    p->OnRejoinClient(55);
    int clientIdR = AddClient(p, "test0", 55, clientR, false);
    p->Step();

    TS_ASSERT_EQUALS(true, clientR->isReconnecting);
    p->RequestWorldData(clientIdR);
    p->OnFinishStep(clientIdS, 2, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(true, clientS->worldDataRequested);
    TS_ASSERT_EQUALS(5, clientS->steps.size());

    nstl::vector<byte> part1;
    nstl::vector<byte> part2;
    FillDataPartAscending(part1, snapshotChunkSize, 0);
    FillDataPartAscending(part2, snapshotChunkSize, snapshotChunkSize);
    {
      rpc::MemoryBlock worldDataPart1(part1.begin(), part1.size());
      rpc::MemoryBlock worldDataPart2(part2.begin(), part2.size());
      Peered::WorldDataInfo worldDataInfo(3, 2);
      clientS->serverReconnect->SendWorldDataInfo(clientIdS, worldDataInfo);
      clientS->serverReconnect->SendWorldDataPart(clientIdS, worldDataPart1);
      clientS->serverReconnect->SendWorldDataPart(clientIdS, worldDataPart2);
    }
    p->OnFinishStep(clientIdS, 3, 0xF00D);
    // From now we can confirm steps of others
    p->OnFinishStep(clientId1, 1, 0xF00D);
    p->OnFinishStep(clientId2, 1, 0xF00D);
    p->OnFinishStep(clientId1, 2, 0xF00D);
    p->OnFinishStep(clientId2, 2, 0xF00D);
    p->OnFinishStep(clientId1, 3, 0xF00D);
    p->OnFinishStep(clientId2, 3, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(2, clientR->mockClientReconnect->worldDataParts.size());
    TS_ASSERT_EQUALS(2, clientR->mockClientReconnect->worldDataInfo.partsCount);
    TS_ASSERT_EQUALS(3, clientR->mockClientReconnect->worldDataInfo.step);
    TS_ASSERT_SAME_DATA(part1.begin(), clientR->mockClientReconnect->worldDataParts[0].memory, part1.size());
    TS_ASSERT_SAME_DATA(part2.begin(), clientR->mockClientReconnect->worldDataParts[1].memory, part2.size());
    p->OnFinishStep(clientId1, 4, 0xF00D);
    p->OnFinishStep(clientId2, 4, 0xF00D);
    p->OnFinishStep(clientIdS, 4, 0xF00D);
    p->Step();

    TS_ASSERT_EQUALS(7, clientS->steps.size());
    TS_ASSERT_EQUALS(2, clientR->steps.size());
    p->OnFinishStep(clientId1, 5, 0xF00D);
    p->OnFinishStep(clientId2, 5, 0xF00D);
    p->OnFinishStep(clientIdS, 5, 0xF00D);
    p->OnClientReady(clientIdR);
    p->Step();

    TS_ASSERT_EQUALS(8, clientS->steps.size());
    TS_ASSERT_EQUALS(4, clientR->steps.size());
    //Reconnected client must confirm the step it reconnected on (step of the applied world snapshot)
    p->OnFinishStep(clientId1, 6, 0xF00D);
    p->OnFinishStep(clientId2, 6, 0xF00D);
    p->OnFinishStep(clientIdS, 6, 0xF00D);
    p->OnFinishStep(clientIdR, 3, 0xF00D);
    p->OnFinishStep(clientIdR, 4, 0xF00D);
    p->OnFinishStep(clientIdR, 5, 0xF00D);
    p->OnFinishStep(clientIdR, 6, 0xF00D);

    const int commandSize0 = 12;
    char commandData0[commandSize0];
    test::FormatCommand(&commandData0, 55, "cmd0");
    rpc::MemoryBlock command0(commandData0, commandSize0);
    p->SendCommand(clientIdR, command0, true);
    p->Step();

    p->OnFinishStep(clientId1, 7, 0xF00D);
    p->OnFinishStep(clientId2, 7, 0xF00D);
    p->OnFinishStep(clientIdS, 7, 0xF00D);
    p->OnFinishStep(clientIdR, 7, 0xF00D);
    TS_ASSERT_EQUALS(9, clientS->steps.size());
    TS_ASSERT_EQUALS(1, clientS->steps[8].commands.size());
    TS_ASSERT_EQUALS(commandSize0, clientS->steps[8].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, clientS->steps[8].commands[0].memory, commandSize0);
    TS_ASSERT_EQUALS(5, clientR->steps.size());
    TS_ASSERT_EQUALS(1, clientR->steps[4].commands.size());
    TS_ASSERT_EQUALS(commandSize0, clientR->steps[4].commands[0].size);
    TS_ASSERT_SAME_DATA(commandData0, clientR->steps[4].commands[0].memory, commandSize0);

    CheckStepsConsistency(client1->steps);
    CheckStepsConsistency(client2->steps);
    CheckStepsConsistency(clientS->steps);
    CheckStepsConsistency(clientR->steps);

    p->OnGameFinish(clientId1, 8, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 8, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientIdR, 8, GetFinishData(lobby::ETeam::Team1));
    // Spectator's session results aren't used and aren't checked. Only the step number is used.
    p->OnGameFinish(clientIdS, 8, GetFinishData(lobby::ETeam::Team2));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(GetFinishData(lobby::ETeam::Team1), link->gameFinishInfo);
  }

  void test_SpectatorFinishGameWhenAllPlayersDisconnected()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects(0, 0, link);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    int clientId2 = AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    p->AddSpectator(58, L"testSpectator");
    p->Step();

    int clientIdS = AddClient(p, "spect0", 58, clientS, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientId2);
    p->OnClientReady(clientIdS);
    p->Step();
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientIdS, 0, 0xF00D);
    // Now lets disconnect all clients, except for the spectator
    client0->status = rpc::Disconnected;
    client1->status = rpc::Disconnected;
    client2->status = rpc::Disconnected;
    // Check that we finish the game now
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(lobby::EGameResult::NoResults, link->gameResultType);
  }

  // In this test we just wait and finish, when spectator informs about game finish.
  // We also don't wait for spectator, which didn't came, despite he was announced.
  void test_SpectatorWaitForSpectatorsOnGameFinish1()
  {
    const int finishTimeoutSteps = 10;
    const Peered::SAuxData auxData;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockAwardsRequester> awardsRequester = new test::MockAwardsRequester;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    data.sessionSettings.finishTimeoutSteps = finishTimeoutSteps;
    SchedulerObjects objects(0, 0, link, 0, &auxData, 0, awardsRequester);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS0 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    int clientId2 = AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    p->AddSpectator(58, L"testSpectator0");
    p->AddSpectator(59, L"testSpectator1");
    p->Step();

    int clientIdS0 = AddClient(p, "spect0", 58, clientS0, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientId2);
    p->OnClientReady(clientIdS0);
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientIdS0, 0, 0xF00D);
    p->Step();

    p->OnGameFinish(clientId0, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 1, GetFinishData(lobby::ETeam::Team1));

    // Only real player are passed to the awards requester
    TS_ASSERT_EQUALS(3, awardsRequester->clientsInfo.size());
    TS_ASSERT_EQUALS(55, awardsRequester->clientsInfo[0].clientId);
    TS_ASSERT_EQUALS(56, awardsRequester->clientsInfo[1].clientId);
    TS_ASSERT_EQUALS(57, awardsRequester->clientsInfo[2].clientId);
    TS_ASSERT_EQUALS(3, awardsRequester->clientsStatistics.size());
    TS_ASSERT_EQUALS(55, awardsRequester->clientsStatistics[0].clientId);
    TS_ASSERT_EQUALS(56, awardsRequester->clientsStatistics[1].clientId);
    TS_ASSERT_EQUALS(57, awardsRequester->clientsStatistics[2].clientId);

    // Fill dummy awards with user IDs and one (unspecified) talent
    for (int i = 0; i < 3; ++i)
    {
      roll::SUserAward & userAward = awardsRequester->awards.push_back();
      userAward.userId = 55 + i;
      roll::SAwardInfo & awardInfo = userAward.awards.push_back();
      awardInfo.type = roll::EAwardType::Talent;
      awardInfo.count = 1;
    }
    awardsRequester->isAwardsReceived = true;

    // Make few steps and verify, that the session is still up and running
    TS_ASSERT_DIFFERS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_DIFFERS(AppFramework::REMOVE_FROM_QUEUE, p->Step());

    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientS0->disconnectReason);

    p->OnGameFinish(clientIdS0, 1, GetFinishData(lobby::ETeam::Team1));

    // New the session is finished
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, clientS0->disconnectReason);
  }

  // In this test we have 3 spectators: one reports game finish with players and we wait for 
  // 2 other spectators. 1 reports game finish before time out, 1 is disconnected due to time out.
  void test_SpectatorWaitForSpectatorsOnGameFinish2()
  {
    const int finishTimeoutSteps = 10;
    const Peered::SAuxData auxData;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockAwardsRequester> awardsRequester = new test::MockAwardsRequester;
    Peered::SchedulerData data;
    data.sessionSettings.spectatorsLimit = 1;
    data.sessionSettings.reconnectEnabled = true;
    data.sessionSettings.finishTimeoutSteps = finishTimeoutSteps;
    data.sessionSettings.spectatorsLimit = 3;
    SchedulerObjects objects(0, 0, link, 0, &auxData, 0, awardsRequester);
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientS0 = new test::MockClient();
    StrongMT<test::MockClient> clientS1 = new test::MockClient();
    StrongMT<test::MockClient> clientS2 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, false);
    int clientId1 = AddClient(p, "test1", 56, client1, false);
    int clientId2 = AddClient(p, "test2", 57, client2, false);
    p->Step();
    p->Step();

    p->AddSpectator(58, L"testSpectator0");
    p->AddSpectator(59, L"testSpectator1");
    p->AddSpectator(60, L"testSpectator2");
    p->Step();

    int clientIdS0 = AddClient(p, "spect0", 58, clientS0, false);
    int clientIdS1 = AddClient(p, "spect1", 59, clientS1, false);
    int clientIdS2 = AddClient(p, "spect2", 60, clientS2, false);
    p->OnClientReady(clientId0);
    p->OnClientReady(clientId1);
    p->OnClientReady(clientId2);
    p->OnClientReady(clientIdS0);
    p->OnClientReady(clientIdS1);
    p->OnClientReady(clientIdS2);
    p->Step();

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);
    p->OnFinishStep(clientIdS0, 0, 0xF00D);
    p->OnFinishStep(clientIdS1, 0, 0xF00D);
    p->OnFinishStep(clientIdS2, 0, 0xF00D);
    p->Step();

    p->OnGameFinish(clientId0, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 1, GetFinishData(lobby::ETeam::Team1));

    // One spectator reports game finish on time
    p->OnGameFinish(clientIdS0, 1, GetFinishData(lobby::ETeam::Team1));

    // Only real player are passed to the awards requester
    TS_ASSERT_EQUALS(3, awardsRequester->clientsInfo.size());
    TS_ASSERT_EQUALS(55, awardsRequester->clientsInfo[0].clientId);
    TS_ASSERT_EQUALS(56, awardsRequester->clientsInfo[1].clientId);
    TS_ASSERT_EQUALS(57, awardsRequester->clientsInfo[2].clientId);
    TS_ASSERT_EQUALS(3, awardsRequester->clientsStatistics.size());
    TS_ASSERT_EQUALS(55, awardsRequester->clientsStatistics[0].clientId);
    TS_ASSERT_EQUALS(56, awardsRequester->clientsStatistics[1].clientId);
    TS_ASSERT_EQUALS(57, awardsRequester->clientsStatistics[2].clientId);

    // Fill dummy awards with user IDs and one (unspecified) talent
    for (int i = 0; i < 3; ++i)
    {
      roll::SUserAward & userAward = awardsRequester->awards.push_back();
      userAward.userId = 55 + i;
      roll::SAwardInfo & awardInfo = userAward.awards.push_back();
      awardInfo.type = roll::EAwardType::Talent;
      awardInfo.count = 1;
    }
    awardsRequester->isAwardsReceived = true;

    // Step for a half of the timeuot
    for (int i = 0; i < finishTimeoutSteps/2; ++i)
    {
      TS_ASSERT_DIFFERS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    }

    // Lagging spectators still don't receive disconnection.
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientS1->disconnectReason);
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientS2->disconnectReason);

    // Second spectator reports game finish here
    p->OnGameFinish(clientIdS0, 1, GetFinishData(lobby::ETeam::Team1));

    // Lagging spectator still don't receive disconnection.
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::None, clientS2->disconnectReason);

    // Step for another half of the timeuot
    for (int i = 0; i < finishTimeoutSteps/2; ++i)
    {
      TS_ASSERT_DIFFERS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    }

    // Well, time is out at this point
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    TS_ASSERT_EQUALS(Peered::EDisconnectReason::GameFinished, clientS2->disconnectReason);
  }

  void test_Multicast()
  {
    StrongMT<test::MockMcChannelsWrapper> mc = new test::MockMcChannelsWrapper();
    Peered::SchedulerData data;
    data.sessionSettings.multicastStepsEnabled = true;
    SchedulerObjects objects;
    objects.mcChannelsWrapper = mc;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    int clientId2 = AddClient(p, "test2", 57, client2, true);

    TS_ASSERT_EQUALS(3, mc->newClients.size());
    TS_ASSERT_EQUALS(55, mc->newClients[0]);
    TS_ASSERT_EQUALS(56, mc->newClients[1]);
    TS_ASSERT_EQUALS(57, mc->newClients[2]);

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(0, mc->data.size());

    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(0, mc->data.size());

    mc->ConnectNewClients();
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size()); // No more regular (unicast) steps
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, client2->steps.size());
    TS_ASSERT_EQUALS(1, mc->data.size());       // Multicast wrapper now receives steps

    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, client2->steps.size());
    TS_ASSERT_EQUALS(2, mc->data.size());

    p->OnFinishStep(clientId0, 0, 0xF00D);
    p->OnFinishStep(clientId1, 0, 0xF00D);
    p->OnFinishStep(clientId2, 0, 0xF00D);

    p->Step();
    p->OnGameFinish(clientId0, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, 1, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId2, 1, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    p = 0;
    TS_ASSERT_EQUALS(true, mc->isClosed);
  }

  void test_MulticastWithReconnect()
  {
    StrongMT<test::MockMcChannelsWrapper> mc = new test::MockMcChannelsWrapper();
    Peered::SchedulerData data;
    data.sessionSettings.multicastStepsEnabled = true;
    data.sessionSettings.reconnectEnabled = true;
    SchedulerObjects objects;
    objects.mcChannelsWrapper = mc;
    StrongMT<Peered::CommandsScheduler> p = Create(data, objects, FillClients(55, 56, 57));
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();
    StrongMT<test::MockClient> clientR = new test::MockClient();

    int clientIdx0 = AddClient(p, "test0", 55, client0, true);
    int clientIdx1 = AddClient(p, "test1", 56, client1, true);
    int clientIdx2 = AddClient(p, "test2", 57, client2, true);

    TS_ASSERT_EQUALS(3, mc->newClients.size());
    TS_ASSERT_EQUALS(55, mc->newClients[0]);
    TS_ASSERT_EQUALS(56, mc->newClients[1]);
    TS_ASSERT_EQUALS(57, mc->newClients[2]);

    p->Step();
    TS_ASSERT_EQUALS(1, client0->steps.size());
    TS_ASSERT_EQUALS(0, mc->data.size());

    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(0, mc->data.size());

    p->OnFinishStep(clientIdx0, 0, 0xF00D);
    p->OnFinishStep(clientIdx1, 0, 0xF00D);
    p->OnFinishStep(clientIdx2, 0, 0xF00D);

    mc->ConnectNewClients();
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size()); // No more regular (unicast) steps
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, client2->steps.size());
    TS_ASSERT_EQUALS(1, mc->data.size());       // Multicast wrapper now receives steps

    client2->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(2, client2->steps.size());
    TS_ASSERT_EQUALS(2, mc->data.size());

    p->OnRejoinClient(57);
    int clientIdxR = AddClient(p, "test2", 57, clientR, false);

    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(0, clientR->steps.size());
    TS_ASSERT_EQUALS(3, mc->data.size());

    p->RequestWorldData(clientIdxR);
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(4, mc->data.size());

    nstl::vector<byte> part1;
    nstl::vector<byte> part2;
    FillDataPartAscending(part1, 5, 0);
    FillDataPartAscending(part2, 5, 5);
    {
      rpc::MemoryBlock worldDataPart1(part1.begin(), part1.size());
      rpc::MemoryBlock worldDataPart2(part2.begin(), part2.size());
      Peered::WorldDataInfo worldDataInfo(0, 2);
      client0->serverReconnect->SendWorldDataInfo(clientIdx0, worldDataInfo);
      client0->serverReconnect->SendWorldDataPart(clientIdx0, worldDataPart1);
      client0->serverReconnect->SendWorldDataPart(clientIdx0, worldDataPart2);
    }
    p->OnClientReady(clientIdxR);
    TS_ASSERT_EQUALS(1, mc->newClients.size());
    TS_ASSERT_EQUALS(57, mc->newClients[0]);

    p->Step();
    // Now all clients have 2uc+5mc steps, while reconnected client
    // has only 6uc steps because the first one he got with reconnect
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(6, clientR->steps.size());
    TS_ASSERT_EQUALS(5, mc->data.size());

    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(7, clientR->steps.size());
    TS_ASSERT_EQUALS(6, mc->data.size());

    mc->ConnectNewClients();
    p->Step();
    TS_ASSERT_EQUALS(2, client0->steps.size());
    TS_ASSERT_EQUALS(2, client1->steps.size());
    TS_ASSERT_EQUALS(7, clientR->steps.size());
    TS_ASSERT_EQUALS(7, mc->data.size());

    p->OnFinishStep(clientIdx0, 1, 0xF00D);
    p->OnFinishStep(clientIdx1, 1, 0xF00D);
    p->OnFinishStep(clientIdxR, 0, 0xF00D);
    p->OnFinishStep(clientIdxR, 1, 0xF00D);

    p->Step();
    p->OnGameFinish(clientIdx0, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientIdx1, 2, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientIdx2, 2, GetFinishData(lobby::ETeam::Team1));
    TS_ASSERT_EQUALS(AppFramework::REMOVE_FROM_QUEUE, p->Step());
    p = 0;
    TS_ASSERT_EQUALS(true, mc->isClosed);
  }

  void check_GameFinishTotalTimeDuration(const int simulationStep)
  {
    clearIds();
    const Peered::SAuxData auxData;
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<test::MockAwardsRequester> awardsRequester = new test::MockAwardsRequester;
    Peered::SchedulerData data;
    data.sessionSettings.simulationStep = simulationStep;
    SchedulerObjects objects;
    objects.auxData = &auxData;
    objects.statsLink = link;
    objects.awardsRequester = awardsRequester;
    StrongMT<Peered::CommandsScheduler> p = Create( data, objects, FillClients(55, 56) );
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    int clientId0 = AddClient(p, "test0", 55, client0, true);
    int clientId1 = AddClient(p, "test1", 56, client1, true);
    p->Step();

    int gameSteps = 1111;
    int step = 0;
    for ( ; step < gameSteps; ++step )
    {
      p->OnFinishStep(clientId0, step, 0xF00D);
      p->OnFinishStep(clientId1, step, 0xF00D);
      p->Step();
    }

    p->OnGameFinish(clientId0, step, GetFinishData(lobby::ETeam::Team1));
    p->OnGameFinish(clientId1, step, GetFinishData(lobby::ETeam::Team1));

    TS_ASSERT_EQUALS(gameSteps*simulationStep/1000, awardsRequester->totalSeconds);
  }

  // Tests total session time calculation with different step length settings (NUM_TASK)
  void test_GameFinishTotalTimeDuration()
  {
    check_GameFinishTotalTimeDuration(50);
    check_GameFinishTotalTimeDuration(100);
    check_GameFinishTotalTimeDuration(150);
  }

  void test_ClientRefusedToReconnect()
  {
    StrongMT<test::MockSessionLink> link = new test::MockSessionLink;
    StrongMT<Peered::CommandsScheduler> p = Create(0, 100, 0, 0, 2000, 0, FillClients(0, 1, 2), link);
    StrongMT<test::MockClient> client0 = new test::MockClient();
    StrongMT<test::MockClient> client1 = new test::MockClient();
    StrongMT<test::MockClient> client2 = new test::MockClient();

    int clientIndex0 = AddClient(p, "test1", 0, client0, true);
                       AddClient(p, "test2", 1, client1, true);
                       AddClient(p, "test3", 2, client2, true);
    p->Step();

    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 1, client1->steps.size() );
    TS_ASSERT_EQUALS( 1, client2->steps.size() );

    // One player leaves the game
    p->OnGameLeave(clientIndex0);
    TS_ASSERT_EQUALS(4, link->clientStatuses.size());
    TS_ASSERT_EQUALS(0, link->clientStatuses[3].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClientIntentionally, link->clientStatuses[3].status);

    p->Step();
    TS_ASSERT_EQUALS(4, client2->clientStatuses.size() );
    TS_ASSERT_EQUALS(0, client2->clientStatuses[3].clientId );
    TS_ASSERT_EQUALS(Peered::DisconnectedByClientIntentionally, client2->clientStatuses[3].status);
    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 2, client1->steps.size() );
    TS_ASSERT_EQUALS( 2, client2->steps.size() );

    // Inform game server about leaver
    p->UserLeftTheGameInCastle(0);
    p->Step();
    // Status sent to cliet only
    TS_ASSERT_EQUALS(4, link->clientStatuses.size());
    TS_ASSERT_EQUALS(5, client2->clientStatuses.size() );
    TS_ASSERT_EQUALS(0, client2->clientStatuses[4].clientId );
    TS_ASSERT_EQUALS(Peered::RefusedToReconnect, client2->clientStatuses[4].status);
    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 3, client1->steps.size() );
    TS_ASSERT_EQUALS( 3, client2->steps.size() );

    // Another client is disconnected (not intentionally or not via game UI)
    client1->status = rpc::Disconnected;
    p->Step();
    TS_ASSERT_EQUALS(5, link->clientStatuses.size());
    TS_ASSERT_EQUALS(1, link->clientStatuses[4].clientId);
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, link->clientStatuses[4].status);
    TS_ASSERT_EQUALS(6, client2->clientStatuses.size() );
    TS_ASSERT_EQUALS(1, client2->clientStatuses[5].clientId );
    TS_ASSERT_EQUALS(Peered::DisconnectedByClient, client2->clientStatuses[5].status);
    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 3, client1->steps.size() );
    TS_ASSERT_EQUALS( 4, client2->steps.size() );

    // Inform game server about second leaver
    p->UserLeftTheGameInCastle(1);
    p->Step();
    // Status sent to cliet only
    TS_ASSERT_EQUALS(5, link->clientStatuses.size());
    TS_ASSERT_EQUALS(7, client2->clientStatuses.size() );
    TS_ASSERT_EQUALS(1, client2->clientStatuses[6].clientId );
    TS_ASSERT_EQUALS(Peered::RefusedToReconnect, client2->clientStatuses[6].status);
    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 3, client1->steps.size() );
    TS_ASSERT_EQUALS( 5, client2->steps.size() );

    // Try to inform for connected client
    p->UserLeftTheGameInCastle(2);
    p->Step();
    // We ignore such abnormal case
    TS_ASSERT_EQUALS(5, link->clientStatuses.size());
    TS_ASSERT_EQUALS(7, client2->clientStatuses.size() );
    TS_ASSERT_EQUALS( 1, client0->steps.size() );
    TS_ASSERT_EQUALS( 3, client1->steps.size() );
    TS_ASSERT_EQUALS( 6, client2->steps.size() );
  }

};

NI_DEFINE_REFCOUNT(test::MockClient);
NI_DEFINE_REFCOUNT(test::MockClientReconnect);

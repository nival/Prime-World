#pragma once

#include "Peered.h"
#include "WorldSnapshot.h"
#include "Server/LobbyPvx/ISessionHybridLink.h"
#include "BlockHistory.h"
#include "AwardsRoll.h"
#include <System/BlockData/BlockData.h>
#include "PeeredStatistics.h"
#include "HybridServerConfig.h"
#include "Protection.hpp"


namespace HybridServer
{
  class ICommandsLog;
  class ICrcDumper;
  class IMcChannelsWrapper;
}


namespace Peered
{

enum StepSendType
{
  UNICAST = 0,
  MULTICAST = 1,
};

struct SchedulerData
{
  SchedulerData() : serverId(0) {}

  TSessionId serverId;
  HybridServer::SessionSettings sessionSettings;
  NCore::ClientSettings clientSettings;
};

struct SnapshotInfo
{
  int step;
  int changesAppliedBeforeBuilt;
  int changesAppliedAfterBuilt;
  void Reset(int _step=-1) { step = _step; changesAppliedBeforeBuilt=0; changesAppliedAfterBuilt=0; }
};


struct ClientHolder
{
  int clientIndex;
  int nextStep;
  int lastReceivedCommandStep;
  int lastReceivedProtectionMagicStep;
  int finishStep;
  StatisticService::RPC::SessionClientResults finishResults;
  bool disconnectGapWaterlineUp;
  bool delayedCommandsWarningOn;
  bool isSpectator;
  wstring nickname;
  StepSendType stepSendType;

  ClientHolder():
  disconnectGapWaterlineUp(false),
  lastVerifiedStep(NCore::INVALID_STEP),
  lastAfkStep(NCore::INVALID_STEP),
  totalAfkSteps(0),
  loadTimeoutStep(0),
  snapshotApplyTimeoutStep(0),
  commandsSizeFromLastStep(0),
  reconnectAnnouncementStep(NCore::INVALID_STEP),
  isAsynced(false),
  disconnectionStep(NCore::INVALID_STEP),
  gapOdd(0),
  isSpectator(false),
  stepSendType(UNICAST),
  lastReceivedCommandStep(NCore::INVALID_STEP),
  lastReceivedProtectionMagicStep(NCore::INVALID_STEP),
  protectionMagicAsyncs(0),
  protectionMagicDelays(0),
  protectionMagicReceiveGapBottom(0)
  {
    info.step = NCore::INVALID_STEP;
  }

  ~ClientHolder() {}

  const SnapshotInfo& GetSnapshotInfo() const { return changes; }
  const Peered::BriefClientInfo& GetInfo() const { return info; }
  uint GetClientId() const { return info.clientId; }
  int GetLastVerifiedStep() const { return lastVerifiedStep; }
  int GetLastSentVerifiedStep() const { return info.step; }
  void SetLastSentVerifiedStep(int value) { info.step = value; }
  bool CheckStepVerification(int step, int confirmFrequency) const { return (info.step != NCore::INVALID_STEP)?(step == info.step+confirmFrequency):true; }
  int GetLastSentStep() const { return nextStep-1; }
  void SetLoadTimeoutStep(int _loadTimeoutStep) { loadTimeoutStep = _loadTimeoutStep; }
  int  GetLoadTimeoutStep() const { return loadTimeoutStep; }
  void AddLoadTimeoutStep() { ++loadTimeoutStep; }
  void SetSnapshotApplyTimeoutStep(int _snapshotApplyTimeoutStep) { snapshotApplyTimeoutStep = _snapshotApplyTimeoutStep; }
  int  GetSnapshotApplyTimeoutStep() const { return snapshotApplyTimeoutStep; }
  void AddSnapshotApplyTimeoutStep() { ++snapshotApplyTimeoutStep; }

  bool OnGameFinish(int step, const StatisticService::RPC::SessionClientResults & finishInfo)
  {
    if (finishStep == NCore::INVALID_STEP)
    {
      finishStep = step;
      finishResults = finishInfo;
      return true;
    }
    return false;
  }

  bool IsGameFinished() const
  {
    return finishStep != NCore::INVALID_STEP;
  }

  bool IsBlocked() const { return isBlocked; }

  void Rewind(int step, int confirmFrequency) 
  { 
    nextStep = step; 
    lastReceivedCommandStep = nextStep;
    lastReceivedProtectionMagicStep = nextStep;
    lastVerifiedStep = step-1;
    if (confirmFrequency > 0)
    {
      if (step % confirmFrequency == 0)
      {
        info.step = step-confirmFrequency;
      } else
      {
        // TODO: info.step = step - step % confirmFrequency -- эквивалент
        info.step = (((step + (confirmFrequency-step%confirmFrequency))/confirmFrequency)-1)*confirmFrequency; // first unconfirmed step
      }
    }
  }

  int GetGap() const { return nextStep-info.step; }
  int GetGapOdd() const { return gapOdd; }
  void SetGapOdd(int _gapOdd) { gapOdd = max(_gapOdd, 0 ); }
  void UpdateGapOdd() { if (gapOdd > 0) { --gapOdd; } }

  void Start(SchedulerData & data, const nstl::vector<ClientInfo>& clientInfos, bool isReconnecting, Peered::RIGameServerReconnect * gameServerReconnect)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      ClientStartInfo clientStartInfo;

      clientStartInfo.index = clientIndex;
      clientStartInfo.serverId = data.serverId;
      clientStartInfo.clientsInfos = clientInfos;
      clientStartInfo.confirmFrequency = data.sessionSettings.confirmFrequency;
      clientStartInfo.snapshotChunkSize = data.sessionSettings.snapshotChunkSize;
      clientStartInfo.isReconnecting = isReconnecting;
      clientStartInfo.snapshotSendPerStep = data.sessionSettings.snapshotSendPerStep;
      clientStartInfo.stepsDelayMin = data.sessionSettings.stepsDelayMin;
      clientStartInfo.stepsDelayMax = data.sessionSettings.stepsDelayMax;
      clientStartInfo.stepsDelayFrame = data.sessionSettings.stepsDelayFrame;
      clientStartInfo.crcDataRequestsEnabled = data.sessionSettings.crcDataRequestsEnabled;
      clientStartInfo.fastReconnectEnabled = data.sessionSettings.fastReconnectReserveSteps > 0;
      clientStartInfo.clientSettings = data.clientSettings;
      clientStartInfo.simulationStep = data.sessionSettings.simulationStep;
      clientStartInfo.protectionMagicConfirmFrequency = data.sessionSettings.pmConfirmFrequency;

      lclient->Start(clientStartInfo, gameServerReconnect);
    }
  }

  void OnAsync(int step, const nstl::vector<AsyncInfo>& async)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->OnAsync(step, async);
    }
  }

  void OnProtectionAsync(const int step)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->OnProtectionAsync(step);
    }
  }

  void SetTimeScale(float scale)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->OnTimeScaleChanged(scale);
    }
  }

  void OnSpectate( const SpectatorInfo& info )
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->OnSpectate( info );
    }
  }

  void ApplySnapshot(int step, uint worldCrc, const nstl::vector<Peered::BriefEntityInfo>& entitiesIds, const nstl::vector<rpc::MemoryBlock>& entitiesData)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      //FIXME: obsolete NUM_TASK
      //lclient->ApplySnapshot(step, worldCrc, entitiesIds, entitiesData);
    }
  }

  void Step(
    int step,
    int lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& clientGaps,
    bool loading)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      if (loading)
        lclient->StepLoading(step, lastConfirmedStep, commands, statuses, clientGaps);
      else
        lclient->Step(step, lastConfirmedStep, commands, statuses, clientGaps, Transport::MessageMiscInfo());
    }
  }


  void Block(bool _isBlocked)
  {
    isBlocked = _isBlocked;
  }

  void OnReady()
  {
    SetStatus(Ready);
  }

  void OnDisconnect(Peered::EDisconnectReason::Enum reason)
  {
    if ( Peered::IGameClient* lclient = GetClient() )
    {
      client->OnDisconnect(int(reason));
    }
  }

  void OnStart(int currentStep, int confirmFrequency)
  {
    SetStatus(Active);
    Rewind(currentStep, confirmFrequency);
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->OnStart(currentStep);
    }
  }

  void OnStart(int currentStep)
  {
    SetStatus(Active);
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->OnStart(currentStep);
    }
  }

  bool IsReadyToGo(int trustGap) const 
  { 
    if (!IsBlocked())
    {
      if (info.status == Active || info.status == Away)
      {
        return (trustGap == 0) || ((nextStep-lastVerifiedStep) <= trustGap);
      }
      return true;
    }
    return false;  
  }

  void SetAppliedStep(const SnapshotInfo& _changes) { changes = _changes; }

  void Set(IGameClient* _client, int step = NCore::INVALID_STEP)
  {
    changes.Reset();
    isBlocked = false;
    nextStep = 0;
    lastVerifiedStep = NCore::INVALID_STEP;
    info.step = step;
    client = _client;
    SetStatus(Connecting);
    finishStep = NCore::INVALID_STEP;
    loadTimeoutStep = 0;
    SetCommandsSizeFromLastStep(0);
    SetReconnectAnnouncementStep(NCore::INVALID_STEP);
    SetAsynced(false);
    disconnectionStep = NCore::INVALID_STEP;
    stepSendType = UNICAST;
  }

  void Set(uint _clientId, IGameClient* _client, int _clientIndex, bool _isSpectator)
  {
    info.clientId = _clientId;
    clientIndex = _clientIndex;
    isSpectator = _isSpectator;
    Set(_client);
  }

  void MarkVerified(uint step)
  {
    lastVerifiedStep = step;
  }

  void MarkCommandReceived(int step)
  {
    lastReceivedCommandStep = step;
  }

  void MarkProtectionMagicReceived(const int step)
  {
    lastReceivedProtectionMagicStep = step;
  }

  bool OnChangeClientStatus(const nstl::vector<Peered::BriefClientInfo>& statusChanges)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->OnChangeClientStatus(statusChanges);
      return true;
    }
    return false;
  }

  Peered::IGameClient* GetClient() 
  {
    if (client)
    {
      if (client->GetStatus() != rpc::Disconnected)
      {
        return client;
      } 
      client = 0;
    }
    return 0;
  }

  void RequestWorldData(Peered::RIGameServerReconnect * gameServerReconnect)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->RequestWorldData(gameServerReconnect);
    }
  }

  void RequestCrcData(int step)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->RequestCrcData(step);
    }
  }

  void OnRejoin(uint clientId)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->OnRejoin(clientId);
    }
  }

  void Award(const vector<roll::SAwardInfo> & _awards)
  {
    Peered::IGameClient* lclient = GetClient();
    if (lclient)
    {
      lclient->Award(_awards);
    }
  }

  Peered::Status GetStatus() const { return info.status; }
  void SetStatus(Peered::Status value) { info.status = value; }
  void Disconnect() { client = 0; }
  bool IsConnected() const { return (client != 0); }

  void SetLastAfkStep(int _lastAfkStep) { lastAfkStep = _lastAfkStep; }
  int GetLastAfkStep() const { return lastAfkStep; }
  void UpdateTotalAfkSteps(int currentStep) 
  {
    if (lastAfkStep >= 0 && currentStep > lastAfkStep)
    {
      totalAfkSteps += currentStep - lastAfkStep;
    }
    lastAfkStep = NCore::INVALID_STEP;
  }
  int GetTotalAfkSteps() const { return totalAfkSteps; }

  void AddCommandSize(int size) { commandsSizeFromLastStep += size; }
  void SetCommandsSizeFromLastStep(int _commandsSizeFromLastStep) { commandsSizeFromLastStep = _commandsSizeFromLastStep; }
  int  GetCommandsSizeFromLastStep() const { return commandsSizeFromLastStep; }
  void SetReconnectAnnouncementStep(int _reconnectAnnouncementStep) { reconnectAnnouncementStep = _reconnectAnnouncementStep; }
  int  GetReconnectAnnouncementStep() const { return reconnectAnnouncementStep; }
  void SetAsynced(bool _isAsynced) { isAsynced = _isAsynced; }
  bool IsAsynced() const { return isAsynced; }
  void SetDisconnectionStep(int _disconnectionStep) { disconnectionStep = _disconnectionStep; }
  int  GetDisconnectionStep() const { return disconnectionStep; }
  bool IsSpectator() const { return isSpectator; }
  void SetStepSendType(StepSendType _stepSendType) { stepSendType = _stepSendType; }
  StepSendType GetStepSendType() const { return stepSendType; }

  void LogProtectionMagicAsync() { ++protectionMagicAsyncs; }
  void LogProtectionMagicDelay() { ++protectionMagicDelays; }

  int GetProtectionMagicAsyncs() const { return protectionMagicAsyncs; }
  int GetProtectionMagicDelays() const { return protectionMagicDelays; }

  int GetProtectionMagicReceiveGap() const
  {
    if (lastReceivedCommandStep < 0)
      return 0;
    if (lastReceivedProtectionMagicStep < 0)
      return 0;

    return max<int>(0, lastReceivedCommandStep - lastReceivedProtectionMagicStep);
  }

  void SetProtectionMagicReceiveGapBottom(const int gap) { protectionMagicReceiveGapBottom = gap; }
  int GetProtectionMagicReceiveGapBottom() const { return protectionMagicReceiveGapBottom; }

private:
  int lastVerifiedStep;
  Peered::BriefClientInfo info;
  SnapshotInfo changes;
  StrongMT<IGameClient> client;
  bool isBlocked;
  int lastAfkStep;
  int totalAfkSteps;
  int loadTimeoutStep;
  int snapshotApplyTimeoutStep;
  int commandsSizeFromLastStep;
  int reconnectAnnouncementStep;
  bool isAsynced;
  int disconnectionStep;
  int gapOdd;

  int protectionMagicAsyncs;
  int protectionMagicDelays;
  int protectionMagicReceiveGapBottom;
};


struct RejoinerData
{
  RejoinerData() { Set(false, NCore::INVALID_STEP); }

  void Set(bool _worldRequested, int _worldAppliedStep)
  {
    worldRequested = _worldRequested;
    worldAppliedStep = _worldAppliedStep;
  }

  void SetWorldAppliedStep(int _worldAppliedStep)
  {
    worldAppliedStep = _worldAppliedStep;
  }

  int GetWorldAppliedStep() const
  {
    return worldAppliedStep;
  }

  bool IsWorldApplied() const
  {
    return worldAppliedStep != NCore::INVALID_STEP;
  }

  bool IsWorldRequested() const
  {
    return worldRequested;
  }

  void SetWorldRequested(bool _worldRequested)
  {
    worldRequested = _worldRequested;
  }

  void SetGameClientReconnect(Peered::IGameClientReconnect * _gameClientReconnect)
  {
    gameClientReconnect = _gameClientReconnect;
  }

  Peered::IGameClientReconnect * GetGameClientReconnect() const
  {
    return gameClientReconnect;
  }

  void SetClientId(uint _clientId)
  {
    clientId = _clientId;
  }

  uint GetClientId() const
  {
    return clientId;
  }

private:
  bool  worldRequested;
  int   worldAppliedStep;
  uint  clientId;
  StrongMT<Peered::IGameClientReconnect> gameClientReconnect;
};


struct ResultsData
{
  StatisticService::RPC::SessionClientResults * results;
  int step;
  int count;

  ResultsData() : results(0), step(NCore::INVALID_STEP), count(0) {}
  ResultsData(StatisticService::RPC::SessionClientResults & _results, int _step, int _count = 0) 
    : results(&_results), step(_step), count(_count) {}

  bool operator ==(const ResultsData & rd) const
  {
    return (*results  == *rd.results && step == rd.step);
  }
};

struct AsyncData
{
  int step;
  nstl::list<int> clientsForCrcRequest;
  nstl::list<int> clientsReportedCrc;
  nstl::vector<AsyncInfo> asyncInfo;
  bool isAllAsynced;
  int requestsTimer;

  AsyncData() : step(NCore::INVALID_STEP), isAllAsynced(false), requestsTimer(0) {}
};


typedef nstl::map<int, ClientHolder*> ClientContainer;
typedef nstl::vector<rpc::MemoryBlock> WorldDataParts;
typedef nstl::map<int, RejoinerData> RejoinersData;
typedef nstl::set<int> ClientList;

class Clients
{
  typedef nstl::vector<WorldSnapshot*> WorldSnapshotContainer;

public:
  static const int INVALID_INDEX = -1;
  static const int INDEX_STEP = 1000000;

  enum Status
  {
    WaitingForClients,
    Loading,
    Started,
    Blocked,
    Finishing,
    WaitingRoll,
    Finished,
    Terminated,
  };
  static const char* GetStatus(Status status);

  Clients(bool _limitClients,
          NLogg::CChannelLogger * _logStream,
          HybridServer::ICommandsLog* _log,
          HybridServer::ICrcDumper* _crcDumper,
          const SchedulerData& _data,
          Peered::ICommandsHandler* _handler,
          lobby::ISessionHybridLink * _statsLink,
          IPeeredStatistics * _statisticsWrapper,
          HybridServer::IMcChannelsWrapper * _mcChannelWrapper):
  clientIndex(0), 
  limitClients(_limitClients), 
  logStream(_logStream),
  status(WaitingForClients),
  lastConfirmedStep(NCore::INVALID_STEP),
  lastConfirmedProtectionStep(NCore::INVALID_STEP),
  lastReservedStep(NCore::INVALID_STEP),
  log(_log),
  crcDumper(_crcDumper),
  data(_data),
  dumpStepsCount(-1), // -1 due to snapshot reservation logic, which counts first reservation as +1
  handler(_handler),
  statsLink(_statsLink),
  statisticsWrapper(_statisticsWrapper),
  mcChannelWrapper(_mcChannelWrapper),
  firstConnectionTimeOutSent(false),
  _protection(),
  _pendingMagic()
  {
    commands.SetServerId(_data.serverId);
    statuses.SetServerId(_data.serverId);
    _InitRejoinData();
    srand( time(0) );  // Init random generator for client indices generation
    trafficStatistics = new TrafficStatistics(_data.serverId, _statisticsWrapper, _logStream);
  }

  ~Clients();
  int GetTotalCount() const { return clients.size()+passiveClients.size(); } 
  int GetActiveCount() const { return clients.size(); } 
  int GetPassiveCount() const { return passiveClients.size(); } 
  int GetRejoinCount() const { return rejoinClients.size(); }
  int GetPlayingCount() const
  {
    int playingCount = 0;
    for (ClientContainer::const_iterator it = clients.begin(); it != clients.end(); ++it)
    {
      if ((it->second->GetStatus() == Peered::Active
            || it->second->GetStatus() == Peered::Away)
          && !it->second->IsSpectator())
      {
        ++playingCount;
      }
    }
    return playingCount;
  }
  int GetDisconnectedCount() const
  {
    int disconnectedCount = 0;
    for (ClientContainer::const_iterator it = passiveClients.begin(); it != passiveClients.end(); ++it)
    {
      if (it->second->GetStatus() == Peered::DisconnectedByClient 
        || it->second->GetStatus() == Peered::DisconnectedByServer)
      {
        ++disconnectedCount;
      }
    }
    return disconnectedCount;
  }
  int GetWaitCount() const { return GetPassiveCount() - GetDisconnectedCount(); } 
  int GetRejoinWithWorldAppliedCount() const 
  {
    int worldAppliedCount = 0;
    for (RejoinersData::const_iterator it = rejoinClients.begin(); it != rejoinClients.end(); ++it)
    {
      if (it->second.IsWorldApplied())
      {
        ++worldAppliedCount;
      }
    }
    return worldAppliedCount;
  }
  int GetRejoinWithPendingWorldRequestCount() const 
  {
    int pendingWorldRequestsCount = 0;
    for (RejoinersData::const_iterator it = rejoinClients.begin(); it != rejoinClients.end(); ++it)
    {
      if (it->second.IsWorldRequested() && !it->second.IsWorldApplied())
      {
        ++pendingWorldRequestsCount;
      }
    }
    return pendingWorldRequestsCount;
  }

  int GetPassiveSpectotorsCount() const
  {
    int count = 0;
    for (ClientContainer::const_iterator it = passiveClients.begin(); it != passiveClients.end(); ++it)
    {
      if (it->second->IsSpectator())
      {
        ++count;
      }
    }
    return count;
  }

  bool IsAllActiveSpectatorsFinishedGame() const
  {
    for (ClientContainer::const_iterator it = clients.begin(); it != clients.end(); ++it)
    {
      if (it->second->IsSpectator() && it->second->finishStep == NCore::INVALID_STEP)
      {
        return false;
      }
    }
    return true;
  }

  bool IsLimited() const { return limitClients; }
  Status GetStatus() const { return status; }
  void SetStatus(Status value) { status = value; }
  int GetLastConfirmedStep() const { return lastConfirmedStep; } 
  int GetLastConfirmedProtectionStep() const { return lastConfirmedProtectionStep; }
  int GetLastReservedStep() const { return lastReservedStep; }

  //TODO: rename to GetActiveClientByIndex and make GetClient a generic getter
  ClientHolder* GetClient(int clientIndex)
  {
    ClientContainer::iterator it=clients.find(clientIndex);
    if (it != clients.end())
    {
      return it->second;
    }
    return 0;
  }

  ClientHolder* GetActiveClient(uint clientId)
  {
    for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it)
    {
      if (it->second->GetClientId() == clientId)
      {
        return it->second;
      }
    }
    return 0;
  }

  ClientHolder* GetPassiveClient(int clientId) const
  {
    ClientContainer::iterator it = passiveClients.find(clientId);
    if (it != passiveClients.end())
    {
      return it->second;
    }
    return 0;
  }

  ClientHolder* GetPassiveClientByIndex(int clientIndex)
  {
    for (ClientContainer::iterator it = passiveClients.begin(); it != passiveClients.end(); ++it)
    {
      if (it->second->clientIndex == clientIndex)
      {
        return it->second;
      }
    }
    return 0;
  }

  template <typename R>
  void Call(R (ClientHolder::*func)())
  {
    for (ClientContainer::iterator it = clients.begin();it != clients.end();++it)
    {
      (it->second->*func)();
    }
  }

  template <typename R, typename P>
  void Call(R (ClientHolder::*func)(P p), P p)
  {
    for (ClientContainer::iterator it = clients.begin();it != clients.end();++it)
    {
      (it->second->*func)(p);
    }
  }

  template <typename R, typename P0, typename P1>
  void Call(R (ClientHolder::*func)(P0 p0, P1 p1), P0 p0, P1 p1)
  {
    for (ClientContainer::iterator it = clients.begin();it != clients.end();++it)
    {
      (it->second->*func)(p0, p1);
    }
  }

  void OnChangeClientStatus(const Peered::BriefClientInfo& info, bool sendOnHybridLink = true, bool sendToClients = true)
  {
    statusChanges.clear();
    statusChanges.push_back(info);
    OnChangeClientStatus(statusChanges, sendOnHybridLink, sendToClients);
  }

  void OnChangeClientStatus(const nstl::vector<Peered::BriefClientInfo>& clientIds, bool sendOnHybridLink = true, bool sendToClients = true);

  void SendAllClientsStatuses(bool sendOnHybridLink = false)
  {
    statusChanges.clear();
    for (ClientContainer::const_iterator it = clients.begin(); it != clients.end(); ++it)
    {
      statusChanges.push_back(it->second->GetInfo());
    }
    for (ClientContainer::const_iterator it = passiveClients.begin(); it != passiveClients.end(); ++it)
    {
      statusChanges.push_back(it->second->GetInfo());
    }
    OnChangeClientStatus(statusChanges, sendOnHybridLink);
  }

  void AddEntity(Peered::BriefEntityInfo& info, const rpc::MemoryBlock& data)
  {
    //FIXME: obsolete NUM_TASK
  }
  void StartGame(int forcedStartTimerValue=0);

  void ResumeGame(int forcedStartTimerValue=0);

  ClientHolder& AddClient(uint clientId, Login::ClientVersion clientVersion, IGameClient* _client);
  ClientHolder * AddClientFast(uint clientId, int clientIndex, IGameClient* _client, int fromStep);

  bool AddClientToMcChannel(ClientHolder & client);

  void AddSpectator( uint clientId, const wstring& nickname );

  void AddRejoinClient(int clientIndex, uint clientId)
  {
    rejoinClients[clientIndex].SetClientId(clientId);
  }

  bool RemoveRejoinClient(int clientIndex)
  {
    if (rejoinClients.erase(clientIndex))
    {
      if (GetRejoinWithPendingWorldRequestCount() == 0)
      {
        _InitRejoinData();
      }
      return true;
    }
    return false;
  }

  RejoinerData* GetRejoinerData(int clientIndex)
  {
    RejoinersData::iterator it = rejoinClients.find(clientIndex);
    if (it != rejoinClients.end())
    {
      return &it->second;
    }
    return 0;
  }

  bool IsClientRejoins(int clientIndex) const { return rejoinClients.find(clientIndex) != rejoinClients.end(); }

  bool IsWorldSentToRejoiner(int clientIndex) const 
  {
    RejoinersData::const_iterator it = rejoinClients.find(clientIndex);
    if (it != rejoinClients.end()) 
    {
      return it->second.IsWorldApplied();
    }
    return false;
  }

  bool IsWorldRequestedByRejoiner(int clientIndex) const 
  {
    RejoinersData::const_iterator it = rejoinClients.find(clientIndex);
    if (it != rejoinClients.end()) 
    {
      return it->second.IsWorldRequested();
    }
    return false;
  }

  bool DisconnectRejoiningClient(int clientIndex, Peered::EDisconnectReason::Enum reason, bool checkSnapshots = true);
  void DisconnectRejoiningClients(Peered::EDisconnectReason::Enum reason, bool checkSnapshots = true);

  void LogReconnectResult(int clientId, EReconnectType::Enum reconnectType, EReconnectResult::Enum reconnectResult);
  void LogClientStatus(const Peered::BriefClientInfo & info, Peered::EDisconnectReason::Enum reason = Peered::EDisconnectReason::None);

  bool IsAllClientsFinished() const;
  void LogFinishResults(const ResultsData & results, int number, int count) const;
  const StatisticService::RPC::SessionClientResults * GetFinishResults();

  bool HavePendingCommands()
  {
    return (commands.GetAccumulatedItemsCount() > 0 || statuses.GetAccumulatedItemsCount() > 0);
  }

  void MarkVerified(uint step)
  {
    Call(&ClientHolder::MarkVerified, step);
  }

  void OnStart(int step)
  {
    Call(&ClientHolder::OnStart, step, data.sessionSettings.confirmFrequency);
  }

  void Block(bool value)
  {
    Call(&ClientHolder::Block, value);
  }

  void SetTimeScale(float scale)
  {
    Call(&ClientHolder::SetTimeScale, scale);
  }

  void OnSpectate( const SpectatorInfo& info )
  {
    Call<void, const SpectatorInfo&>(&ClientHolder::OnSpectate, info );
  }

  void UpdateCommands(bool stepped);
  void UpdateCommands(bool stepped, ClientHolder & holder);
  void UpdateCommandsBlocked();

  void SendStep(bool stepped);

  // Reports async to all active clients
  void OnAsync(int step, const nstl::vector<AsyncInfo>& async)
  {
    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer: Sending async to all active clients (sid=%016x step=%d)", data.serverId, step);

    for (ClientContainer::const_iterator it = clients.begin();it != clients.end();++it)
    {
      OnAsync(step, async, it->second);
    }
  }

  // Reports async to a list of specific clients
  void OnAsync(int step, const nstl::vector<AsyncInfo>& async, const nstl::vector<int>& asyncClients)
  {
    for (int i = 0; i < asyncClients.size(); ++i)
    {
      if (Peered::ClientHolder * asyncClient = GetClient(asyncClients[i]))
      {
        OnAsync(step, async, asyncClient);
      }
    }
  }

  // Reports async to a specific client
  void OnAsync(int step, const nstl::vector<AsyncInfo>& async, Peered::ClientHolder * client)
  {
    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer: Sending async to client (sid=%016x cid=%d cidx=%d step=%d)", 
        data.serverId, client->GetClientId(), client->clientIndex, step);

    OnGameCheated(client->GetClientId(), client->clientIndex, lobby::ECheatType::Async);

    client->OnAsync(step, async);
  }

  void OnProtectionMagicDelay(const int step, Peered::ClientHolder* const client, Protection::ClientIndexVector& disconnectClients)
  {
    client->LogProtectionMagicDelay();

    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer: Protection magic delayed (sid=%016x cid=%d cidx=%d step=%d delays=%d gap=%d bottom=%d)",
        data.serverId, client->GetClientId(), client->clientIndex, step, client->GetProtectionMagicDelays(), client->GetProtectionMagicReceiveGap(), client->GetProtectionMagicReceiveGapBottom());

    if (client->GetProtectionMagicDelays() < data.sessionSettings.pmDelayThreshold)
      return;

    disconnectClients.push_back(client->clientIndex);
  }

  void OnProtectionMagicAsync(const int step, Peered::ClientHolder* const client, Protection::ClientIndexVector& disconnectClients)
  {
    client->LogProtectionMagicAsync();

    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer: Sending protection magic async to client (sid=%016x cid=%d cidx=%d step=%d asyncs=%d)",
        data.serverId, client->GetClientId(), client->clientIndex, step, client->GetProtectionMagicAsyncs());

    client->OnProtectionAsync(step);

    if (client->GetProtectionMagicAsyncs() < data.sessionSettings.pmAsyncThreshold)
      return;

    disconnectClients.push_back(client->clientIndex);
  }

  void OnProtectionMagicAsync(const int step, const Protection::ClientIndexVector& asyncClients, Protection::ClientIndexVector& disconnectClients)
  {
    for (int i = 0, count = asyncClients.size(); i < count; ++i)
    {
      if (Peered::ClientHolder* const client = GetClient(asyncClients[i]))
        OnProtectionMagicAsync(step, client, disconnectClients);
    }
  }

  void OnRejoin(uint clientId)
  {
    Call(&ClientHolder::OnRejoin, clientId);
  }

  void CheckStatuses(bool calculateGap, nstl::vector<int>& clientIndices, nstl::vector<Peered::BriefClientInfo>& clientInfos, Peered::IWorld* world);

  int GetReadyCount() const;
  int GetLoadingCount() const;
  ClientHolder* WaitClient( uint clientId, bool isSpectator, const wstring& nickname );
  bool IsClientAwaited( uint clientId ) { return !limitClients || _FindWaitClient(clientId) != passiveClients.end(); }
  bool RemoveWaitClient( uint clientId );
  bool DisconnectClient(uint clientIndex, Peered::Status status = Peered::DisconnectedByServer, Peered::EDisconnectReason::Enum reason = Peered::EDisconnectReason::None);
  bool DisconnectClients(const nstl::vector<int>& clientIndexes, Peered::Status status = Peered::DisconnectedByServer, Peered::EDisconnectReason::Enum reason = Peered::EDisconnectReason::None);
  bool IsClientDisconnected(int clientIndex);
  ClientHolder* GetDisconnectedClient(int clientIndex);

  bool IsAllClientsReadyToGo(int trustGap) const
  {
    for (ClientContainer::const_iterator it = clients.begin();it != clients.end();++it)
    {
      if (!it->second->IsReadyToGo(trustGap))
      {
        return false;
      }
    }
    return true;
  }
  void CheckAsyncSnapshots();
  bool CheckAsyncSnapshot(WorldSnapshot * snapshot, const nstl::vector<AsyncInfo> & asyncInfo);
  void RequestCrcData();
  void RequestCrcDataFromClient(int clientIndex, bool isAsync);
  void UpdateSnapshots();
  WorldSnapshot* GetWorldSnapshot(int step);
  void CheckSnapshotAllocated(int step);
  void AllocateSnapshot(int _step, CrcStatuses::Status _status=CrcStatuses::WaitingForFirstCrc);
  void DeallocateSnapshots( int _index);
  void DeleteSnapshots(WorldSnapshotContainer& _container);
  bool CheckSnapshots(int clientIndex);
  bool CheckSnapshots(nstl::vector<int>& clientIndexes);
  void AddClientToSnapshots(int clientIndex, int fromStep, bool isReserved = false);
  void RemoveClientFromSnapshots(int clientIndex, int toStep, bool unreserve = false);
  void SendCommands(int step, ClientHolder& client, int changesApplied)
  {
    commands.CopyStep(step, stepCommands);
    statuses.CopyStep<BriefClientInfo>(step, stepStatuses);
    client.Step(step, lastReservedStep, stepCommands, stepStatuses, stepGapInfo, (GetStatus() == Clients::Loading));
    for (int i = 0; i < stepCommands.size(); ++i)
      trafficStatistics->AddOutTrafficSize(stepCommands[i].size);
    if (stepStatuses.size() > 0)
      trafficStatistics->AddOutTrafficSize(stepStatuses.size() * sizeof(BriefClientInfo));
  }
  void StepBlocked(ClientHolder& client)
  {
    stepCommands.clear();
    stepStatuses.clear();
    client.Step(NCore::INVALID_STEP, lastReservedStep, stepCommands, stepStatuses, stepGapInfo, false);
  }
  void MakeStep();
  int GetPendingStep() const { return commands.GetPendingStep(); }
  void EraseSteps(int endStep);
  void DumpSteps(int endStep);
  void AddCommand(ClientHolder & client, const rpc::MemoryBlock& info, bool isPlayerCommand);
  void UpdateStatusChanges();
  int CheckClients(Peered::ICommandsHandler* handler, Peered::IWorld* world);
  void CheckPassiveClients();
  void ForceWorldRequestTimeout() { reconnectStepCounter = data.sessionSettings.snapshotRequestTimeout; }
  static const char* GetClientStatus(Peered::Status status);
  void DisconnectAllClients(Peered::EDisconnectReason::Enum reason = Peered::EDisconnectReason::None);
  void SendWorldDataInfo(int clientIndex, const WorldDataInfo& _worldDataInfo);
  void SendWorldDataPart(int clientIndex, const rpc::MemoryBlock& worldDataPart);
  void SetGameClientReconnect(int clientIndex, Peered::IGameClientReconnect * gameClientReconnect);
  void OnGameCheated(uint clientId, uint clientIndex, lobby::ECheatType::Enum cheatType = lobby::ECheatType::None);
  uint FillClientStatistics(nstl::vector<Peered::SClientStatistics> & clientsStatistics);
  void UpdateClientCommands( ClientHolder& holder, bool stepped, int lastStep );
  void SetNeedToApplyWorldData(bool _needToApplyWorldData) { needToApplyWorldData = _needToApplyWorldData; }
  void ResetCommandsSizeInfo()
  {
    Call(&ClientHolder::SetCommandsSizeFromLastStep, 0);
  }
  void FillDefaultGameResults(StatisticService::RPC::SessionClientResults & finishInfo);
  bool OnRejoinClient(uint clientId);
  bool OnGameLeave(int clientIndex, Peered::IWorld* world);

  void SetGameServerReconnect(Peered::IGameServerReconnect * _gameServerReconnect, const Transport::TServiceId & _reconnectIfaceId)
  {
    gameServerReconnect = _gameServerReconnect;
    reconnectIfaceId = _reconnectIfaceId;
  }

  void SendCrcData(int clientIndex, int step, const rpc::MemoryBlock& crcData);
  void CheckCrcDataRequestsTimeOut();
  void CancelCrcDataRequests();

  void OnDisconnectAck(int clientIndex);
  void DispatchPlaySameTeamDecision(int clientIndex, const bool agreed);
  void DispatchBadBehaviourComplaint(int clientIndex, const Transport::TClientId reportedClientId, const int reportItemId);

  void AwardClients(const TUserAwards & awards);

  void LogTraffic() { trafficStatistics->LogTraffic(); }

  void SetCommandsLog(HybridServer::ICommandsLog * _log) { log = _log; }
  void OnFirstConnectionTimeout();

  void AddClientToProtectionRecords(const int clientIndex, const int fromStep, const bool reserved = false);
  void RemoveClientFromProtectionRecords(const int clientIndex, const int toStep, const bool unreserve = false);
  void RemoveClientFromProtectionRecords(const int clientIndex);

  void UpdateProtection();

  void PushMagicRecord(const int clientIndex, const int step, const uint magic)
  {
    const Protection::MagicRecord record = { clientIndex, step, magic };

    _pendingMagic.push_back(record);
  }
private:
  WorldSnapshotContainer snapshots;
  WorldSnapshotContainer snapshotCache;
  ClientContainer::iterator _DisconnectClient( ClientContainer::iterator it, Peered::Status status, Peered::EDisconnectReason::Enum reason = Peered::EDisconnectReason::None );
  ClientContainer::iterator _RemoveClient( ClientContainer::iterator it, Peered::IWorld* world, nstl::vector<Peered::BriefClientInfo> &clientInfos, nstl::vector<int> &clientIndices, Peered::Status status, Peered::EDisconnectReason::Enum reason );
  ClientContainer::iterator _FindWaitClient(uint clientId);
  int _GenerateIndex();
  void _InitRejoinData();
  int  _RequestWorldData();
  void _SendWorldData(WorldSnapshot* snapshot);
  void _WorldDataRequestTimeOut();

  void AllocateProtectionRecord(const int step);
  void DeallocateProtectionRecords(const int count);
  void DispatchProtectionAsyncRecord(Protection::StepRecord* const record);
  void ProcessMagicRecord(const Protection::MagicRecord& record);
  void UpdateProtectionRecords();
  void UpdateProtectionAsyncRecords();
  void CheckProtectionMagicDelays();
  void CheckProtectionMagicConfirmation();
  void ProcessPendingProtectionMagic();

  int lastConfirmedStep;
  int lastConfirmedProtectionStep;
  int lastReservedStep;
  BlockHistory commands;
  BlockHistory statuses;
  nstl::vector<rpc::MemoryBlock> stepCommands;
  nstl::vector<BriefClientInfo> stepStatuses; 
  bool limitClients;
  ClientContainer clients;
  ClientContainer passiveClients;
  RejoinersData rejoinClients;
  int clientIndex;
  NLogg::CChannelLogger* logStream;
  Status status;
  nstl::vector<GapInfo> stepGapInfo;
  const SchedulerData& data;
  StrongMT<HybridServer::ICommandsLog> log;
  StrongMT<HybridServer::ICrcDumper> crcDumper;
  int dumpStepsCount;
  nstl::vector<Peered::BriefClientInfo> statusChanges;
  nstl::vector<int> statusChangesIndices;
  StrongMT<lobby::ISessionHybridLink> statsLink;

  WorldDataInfo  worldDataInfo;
  int activeRequestClientIndex;
  int reconnectStepCounter;
  bool needToApplyWorldData;
  nstl::set<int> worldDataRequests;
  StrongMT<Peered::ICommandsHandler> handler;
  StrongMT<Peered::IGameServerReconnect> gameServerReconnect;
  Transport::TServiceId reconnectIfaceId;

  AsyncData asyncData;
  StrongMT<IPeeredStatistics> statisticsWrapper;
  StrongMT<TrafficStatistics> trafficStatistics;
  ClientList  spectators;

  StrongMT<HybridServer::IMcChannelsWrapper> mcChannelWrapper;
  Login::ClientVersion clientVersion;
  bool firstConnectionTimeOutSent;

  Protection::StepRecords _protection;
  nstl::vector<Protection::MagicRecord> _pendingMagic;
};

}
#ifndef HYBRIDSERVERNODEIMPL_H_INCLUDED
#define HYBRIDSERVERNODEIMPL_H_INCLUDED


#include <Core/Scheduler.h>
#include "HybridServer/Peered.h"
#include <Server/AppFramework/Interfaces.h>
#include "System/Stream.h"
#include "System/Histogram.h"
#include "Server/Roll/RollTypes.h"
#include "PF_GameLogic/ReplayInfo.h"


namespace StatisticService
{
  class GameStatistics;
}

namespace NCore
{

class ReplayWriter;

struct StreamedBlocks
{
  NCore::IServerNode::TMessageList items;
  nstl::vector<byte> itemsData;

  void Reset()
  {
    items.resize(0);
    itemsData.resize(0);
  }

  void Copy(const nstl::vector<rpc::MemoryBlock>& blocks);
};


struct StepData
{
  uint step;
  StreamedBlocks commands;
  nstl::vector<Peered::BriefClientInfo> statuses;

  void Reset()
  {
    step = 0xFFFFFFFF;
    commands.Reset();
    statuses.resize(0);
  }
};



struct StepTimeStats
{
  // stepTimes - 128k of elements is enough to hold more than 3 hours session without reallocation
  StepTimeStats() : longStepsCount(0) { stepTimes.reserve(1<<17); }

  void SetLongTime(NHPTimer::STime _longTime) { longTime = _longTime; }

  void AddStepTime(NHPTimer::STime _stepTime)
  {
    int stepMs = NHPTimer::Time2Milliseconds(_stepTime);
    stepMs = Min( stepMs, USHRT_MAX );
    stepTimes.push_back( (unsigned short)stepMs );  // int to short is Ok here, because numbers are small
    if (_stepTime > longTime)
    {
      ++longStepsCount;
    }
  }

  int GetLongTimeCount() const { return longStepsCount; }
  const void* GetBuffer() const { return &stepTimes[0]; }
  int GetBufferSize() const { return stepTimes.size()*sizeof(stepTimes[0]); }

private:
  // Up to 64k numbers (unsigned short) should be enough. Long lags will lead to disconnect any way.
  vector<unsigned short> stepTimes;
  int longStepsCount;
  NHPTimer::STime longTime;
};



class GameClientReconnect : public Peered::IGameClientReconnect, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( GameClientReconnect, Peered::IGameClientReconnect, BaseObjectMT );

public:
  GameClientReconnect() : worldDataSize(0) {}
  ~GameClientReconnect();

  // Peered::IGameClientReconnect
  virtual void ApplyWorldDataInfo(const Peered::WorldDataInfo& _worldDataInfo);
  virtual void ApplyWorldDataPart(const rpc::MemoryBlock& worldDataPart);

  bool IsWorldDataReady() const;
  bool GetWorldData(Stream & worldData, int & segmentStep);

private:
  typedef nstl::vector<rpc::MemoryBlock> WorldDataParts;

  Peered::WorldDataInfo worldDataInfo;
  WorldDataParts        worldDataParts;
  int                   worldDataSize;
};

typedef nstl::list<StepData*> TStepsContainer;

struct PlaySameTeamDecision
{
  Transport::TClientId clientId;
  bool agreed;

  PlaySameTeamDecision()
    : clientId(-1)
    , agreed(false)
  {
  }
  PlaySameTeamDecision(const Transport::TClientId clientId, const bool agreed)
    : clientId(clientId)
    , agreed(agreed)
  {
  }
  explicit PlaySameTeamDecision(const PlaySameTeamDecision& other)
    : clientId(other.clientId)
    , agreed(other.agreed)
  {
  }
  PlaySameTeamDecision& operator=(const PlaySameTeamDecision& other)
  {
    clientId = other.clientId;
    agreed = other.agreed;
    return *this;
  }
};

struct BadBehaviourComplaint
{
  Transport::TClientId senderClientId;
  Transport::TClientId reportedClientId;
  int reportItemId;

  BadBehaviourComplaint()
    : senderClientId(-1)
    , reportedClientId(-1)
    , reportItemId(-1)
  {
  }

  BadBehaviourComplaint(const Transport::TClientId senderClientId, const Transport::TClientId reportedClientId, int reportItemId)
    : senderClientId(senderClientId)
    , reportedClientId(reportedClientId)
    , reportItemId(reportItemId)
  {
  }

  explicit BadBehaviourComplaint(const BadBehaviourComplaint& other)
    : senderClientId(other.senderClientId)
    , reportedClientId(other.reportedClientId)
    , reportItemId(other.reportItemId)
  {
  }

  BadBehaviourComplaint& operator=(const BadBehaviourComplaint& other)
  {
    senderClientId = other.senderClientId;
    reportedClientId = other.reportedClientId;
    reportItemId = other.reportItemId;
    return *this;
  }
};

class ServerNode : public NCore::IServerNode, public BaseObjectMT, public Peered::IGameClient
{
   NI_DECLARE_REFCOUNT_CLASS_3( ServerNode, NCore::IServerNode, Peered::IGameClient, BaseObjectMT );
public:
  ServerNode(Peered::IGameServer* _server);
  ~ServerNode();

  void Reinit( Peered::IGameServer* _server, int _lastStep ); //Used for fast reconnect

  bool IsStarted() const { return clientIndex >= 0; }
  bool IsReconnecting() const { return isReconnecting; }
  Peered::EDisconnectReason::Enum GracefullDisconnectReason() const { return gracefullDisconnectReason; }

  Peered::IGameServer * GameServer() { return server; }

  const Peered::ClientInfo* GetClientInfo( Transport::TClientId clientId ) const ;
  const nstl::vector<Peered::ClientInfo> & GetClientInfos() const { return clientsInfos; }

  bool PopClientStatusChange( Peered::BriefClientInfo & info );

  void OnCombatScreenStarted( const NGameX::ReplayInfo & _replayInfo );
  void GameFinished( const StatisticService::RPC::SessionClientResults & finishInfo, const NGameX::ReplayInfo & _replayInfo, int step );

  virtual void ClientReady();
  virtual int GetStartedStep() const { return startedStep; }

  // IServerNode
  virtual void SendMessage(Stream* writeStream, bool isPlayerCommand);
  virtual int GetServerSegment( TMessageList &segment, TStatusList & statuses );
  virtual void SendCRC( int step, DWORD crcValue );
  virtual void SendCrcData( int step, unsigned char * data, int size);
  virtual int GetAsyncStep() const { return asyncStep; }
  virtual int GetProtectionAsyncStep() const { return protectionAsyncStep; }
  virtual void SendProtectionMagic(int step, uint magic);
  virtual int GetProtectionMagicConfirmFrequency() const { return protectionMagicConfirmFrequency; }

  // Peered::IGameClient
  virtual void Start(const Peered::ClientStartInfo& clientStartInfo, Peered::RIGameServerReconnect * gameServerReconnect);

  virtual void Step(
    int step,
    int lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& gapInfo,
    const Transport::MessageMiscInfo& __miscInfo__);
  virtual void StepLoading(
    int step,
    int lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& gapInfo);
  virtual void StepBatch(
    int lastConfirmedStep,
    const nstl::vector<Peered::ClientStepData>& stepData);
  virtual void OnAsync(int step, const nstl::vector<Peered::AsyncInfo>& asyncs);
  virtual void OnStart(int step);
  virtual void OnTimeScaleChanged(float scale);
  virtual void OnChangeClientStatus( const nstl::vector<Peered::BriefClientInfo> & clientStatuses );
  virtual bool PopNewTimeScale(float& scale);
  virtual void OnDisconnect( int reason ); //Peered::EDisconnectReason::Enum
  virtual void OnRejoin(uint clientId);
  virtual void RequestWorldData(Peered::RIGameServerReconnect * gameServerReconnect);
  virtual void RequestCrcData(int step);
  virtual void Award( const vector<roll::SAwardInfo> & _awards );
  virtual void OnSpectate(const Peered::SpectatorInfo& info);
  virtual void OnPlaySameTeamDecision(const Transport::TClientId clientId, const bool agreed);
  virtual void OnBadBehaviourComplaint(const Transport::TClientId clientId, const Transport::TClientId reportedClientId, int reportItemId);
  virtual void OnProtectionAsync(int step);

  void StepMc(const rpc::MemoryBlock& stepData);
  void StepImpl(
    int step,
    int _lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& gapInfo,
    TStepsContainer * stepsQueue);

  bool PopWorldRequest(bool & worldRequest, int currentStep);
  bool PopWorldData(Stream & worldData, int & segmentStep);
  bool IsWorldDataReady() const { return (clientReconnect && clientReconnect->IsWorldDataReady()); }

  void SendWorldData(int step);
  void SendWorldDataParts();
  void RequestWorldDataFromServer();

  Stream & GetWorldDataStream() { return worldData; }
  bool IsWorldDataInProgress() const { return worldDataSizeLeft > 0; }

  void SetGameStatistics( StatisticService::GameStatistics * stat ) { gameStatistics = stat; }
  void UpdateStepStatistics(int step);
  void UpdateQueueTimeStatistics(int step, const Transport::MessageMiscInfo & _miscInfo);

  rpc::EntityHandler* GetHandler() { return (server)?(server->GetHandler()):(0); }

  StrongMT<Transport::IChannel> ServerChannel();
  Transport::Ping GetPingTime();

  virtual const StepsDelaySettings & GetStepsDelaySettings() { return stepsDelaySettings; }

  int GetClientIndex() const { return clientIndex; }

  void DumpLags() const;

  virtual int GetLastConfirmedStep() const { return lastConfirmedStep; }
  virtual int PopCrcRequestStep();
  virtual bool IsCrcDataEnabled() const { return crcDataRequestsEnabled; }

  bool IsAwardsReceived() const { return awardsReceived; }
  void SetAwardsReceived(bool _awardsReceived) { awardsReceived = _awardsReceived; }
  const vector<roll::SAwardInfo> & GetAwards() const { return awards; }

  const NCore::ClientSettings & GetClientSettings() const { return clientSettings; }

  bool IsFastReconnectEnabled() const { return fastReconnectEnabled; }
  int GetSimulationStep() const { return simulationStep; }

  bool DidSpectatorJoin() const { return isSpectatorJoin; }
  void DropJoinedSpectatorRecord() { isSpectatorJoin = false; }
  const Peered::SpectatorInfo& GetJoinedSpectatorInfo() const { return spectatorInfo; }

  void SetReplayWriter(NCore::ReplayWriter * _replayWriter) { replayWriter = _replayWriter; }

  bool PopPlaySameTeamDecision(PlaySameTeamDecision& decision);
  bool PopBadBehaviourComplaint(BadBehaviourComplaint& complaint);

private:
  bool SetTimeScale( const char *name, const vector<wstring> &args );

  StrongMT<Peered::IGameServer> server;
  StrongMT<Peered::IGameServerReconnect> serverReconnect;
  StrongMT<NCore::GameClientReconnect> clientReconnect;
  WeakMT<Transport::IChannel> serverChannel;
  StrongMT<StatisticService::GameStatistics> gameStatistics;
  int rpcPing;
  int transportPing;
  int clientIndex;
  TStepsContainer stepsUc;
  TStepsContainer stepsMc;
  vector<TStepsContainer*> steps;
  nstl::vector<StepData*> cache;
  int lastStep;
  int asyncStep;
  int protectionAsyncStep;
  int startedStep;
  int confirmFrequency;
  int protectionMagicConfirmFrequency;
  int snapshotChunkSize;
  bool isReconnecting;
  int snapshotSendPerStep;
  bool crcDataRequestsEnabled;
  bool fastReconnectEnabled;
  int simulationStep;
  StepsDelaySettings stepsDelaySettings;
  nstl::vector<Peered::AsyncInfo> asyncs;
  Peered::TSessionId serverId;
  AppFramework::InstanceStatistics stats;
  AppFramework::InstanceStatistics queueTimeStats;
  CustomHistogram transportTimeHisto;
  CustomHistogram queueTimeHisto;
  StepTimeStats stepTimeStatsFull;
  list<Peered::BriefClientInfo>  clientsStatusChanges;
  Peered::EDisconnectReason::Enum gracefullDisconnectReason;
  nstl::vector<Peered::ClientInfo> clientsInfos;
  bool                  worldRequested;
  float                 newTimeScale;

  MemoryStream          worldData;
  int                   worldDataSizeLeft;

  NDebug::DebugVar<int> *hybridRPCPingVar;
  int                   lastConfirmedStep;
  int                   crcRequestStep;

  vector<roll::SAwardInfo>  awards;
  bool                      awardsReceived;

  NCore::ClientSettings    clientSettings;

  // TODO: list?
  bool                  isSpectatorJoin;
  Peered::SpectatorInfo spectatorInfo;

  StrongMT<NCore::ReplayWriter> replayWriter;

  nstl::list<PlaySameTeamDecision> playSameTeamDecisions;
  nstl::list<BadBehaviourComplaint> badBehaviourComplaints;
};

} // NCore

#endif //HYBRIDSERVERNODEIMPL_H_INCLUDED

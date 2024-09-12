#pragma once
#include "Peered.h"
#include "ClientHolder.h"
#include "WorldSnapshot.h"
#include "WorldData.h"
#include <Server/AppFramework/Interfaces.h>
#include <System/BlockData/BlockData.h>
#include "GameServerRegistratorIface.h"


namespace lobby
{
  class ISessionHybridLink;
};

namespace HybridServer
{
  struct IGameServerAllocatorNotify;
  class IMcChannelsWrapper;
}

namespace Peered
{

class GameServerReconnect : public IGameServerReconnect, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( GameServerReconnect, IGameServerReconnect, BaseObjectMT );
  GameServerReconnect() { SetPointers(0, 0); }

public:
  GameServerReconnect(Clients & _clients, threading::Mutex & _clientsLock) 
  {
    SetPointers(&_clients, &_clientsLock);
  }

  void SetPointers(Clients * _clients, threading::Mutex * _clientsLock)
  {
    clients = _clients;
    clientsLock = _clientsLock;
  }

  virtual void SendWorldDataInfo(int clientIndex, const WorldDataInfo& worldDataInfo)
  {
    if (clientsLock && clients)
    {
      threading::MutexLock lock(*clientsLock);
      clients->SendWorldDataInfo(clientIndex, worldDataInfo);
    }
  }

  virtual void SendWorldDataPart(int clientIndex, const rpc::MemoryBlock& worldDataPart)
  {
    if (clientsLock && clients)
    {
      threading::MutexLock lock(*clientsLock);
      clients->SendWorldDataPart(clientIndex, worldDataPart);
    }
  }

  virtual void SetGameClientReconnect(int clientIndex, Peered::IGameClientReconnect * gameClientReconnect)
  {
    if (clientsLock && clients)
    {
      threading::MutexLock lock(*clientsLock);
      clients->SetGameClientReconnect(clientIndex, gameClientReconnect);
    }
  }

private:
  Clients * clients;
  threading::Mutex * clientsLock;
};

class CommandsScheduler : public IGameServer, public IWorld, public BaseObjectMT, public AppFramework::ITimedInstance
{
  NI_DECLARE_REFCOUNT_CLASS_3( CommandsScheduler, IGameServer, BaseObjectMT, AppFramework::ITimedInstance );
public:
  CommandsScheduler(
    const SchedulerData& _data,
    const Transport::TServiceId & _reconnectIfaceId,
    Peered::ICommandsHandler* _handler=0, 
    HybridServer::ICommandsLog* _log=0, 
    HybridServer::ICrcDumper* _crcDumper=0,
    const vector<ClientInfo>* _clientInfos=0,
    lobby::ISessionHybridLink * _statsLink = 0,
    const SAuxData * _auxData = 0,
    NLogg::CChannelLogger* _logStream=0,
    uint _allocid = 0,
    HybridServer::IGameServerAllocatorNotify* = 0,
    IAwardsRequester * _awardsRequester = 0,
    const lobby::TGameLineUp * _gameLineUp = 0,
    const lobby::SGameParameters * _gameParams = 0,
    IPeeredStatistics * _statisticsWrapper = 0,
    HybridServer::IMcChannelsWrapper * _mcChannelWrapper = 0,
    HybridServer::IGameServerInstanceRegistrator * _instanceRegistrator = 0);
  ~CommandsScheduler();

  // all public methods should be mt safe 

  IGameServerInternal * GetInternalInterface() { return internalInterface; }

  //IGameServer
  virtual void AddClient(const char* name, uint clientId, const Login::ClientVersion& clientVersion, IGameClient* _client);
  virtual void AddClientFast(int clientId, int clientIndex, NI_LPTR Peered::IGameClient* _client, int fromStep);
  virtual void SendCommand(int clientIndex, const rpc::MemoryBlock& info, bool isPlayerCommand);
  virtual void OnClientReady(int clientIndex);
  virtual SHybridPongResult& Ping( SHybridPongResult& time_step ) { return time_step; } // возвращаем ровно то же время, которое нам присылают; чтобы на стороне клиента не возиться с запоминанием.

  virtual void OnFinishStep(int clientIndex, uint step, uint worldCrc);
  virtual void SetTimeScale(int clientIndex, float _scale);

  // local usage only
  virtual int Step(int delta=0);
  virtual int GetId() const { return data.serverId; }

  int GetNumberOfClients() const { return clients.GetTotalCount(); }
  void AddTrustedClient(uint clientId, IGameClient* _client)
  {
    trustedClient.Set(clientId, _client, 0, false);
  }
  virtual void AddEntity(Peered::BriefEntityInfo& info, const rpc::MemoryBlock& data)
  {
    DebugTrace( "GameServer: AddEntity %d on step %d", info.id, clients.GetPendingStep());
    if (worldData->GetChangesInfo().step == clients.GetPendingStep())  
    {
      worldData->Append(info, data);
    }
    clients.AddEntity(info, data);
  }
  virtual void OnGameFinish(int clientIndex, int step, const StatisticService::RPC::SessionClientResults & finishInfo);
  virtual void RequestWorldData(int clientIndex);
  virtual bool OnGameLeave(int clientIndex);
  virtual void SendCrcData(int clientIndex, int step, const rpc::MemoryBlock& crcData);
  virtual void OnDisconnectAck(int clientIndex);
  virtual void DispatchPlaySameTeamDecision(int clientIndex, const bool agreed);
  virtual void DispatchBadBehaviourComplaint(int clientIndex, const Transport::TClientId reportedClientId, const int reportItemId);
  virtual void OnProtectionError(int clientIndex);
  virtual void SendProtectionMagic(int clientIndex, int step, uint magic);

  //mirror of IGameServerInternal
  bool OnRejoinClient( uint clientId );
  void AddSpectator( uint clientId, const wstring& nickname );
  void UserLeftTheGameInCastle( uint clientId );

private:
  int _AddClient(uint clientId, Login::ClientVersion clientVersion, IGameClient* _client, bool isReconnecting);
  void FinishGame(int gameResultType, const StatisticService::RPC::SessionClientResults * gameResults=0); 	
  void MakeStep();
  void StepLoading();
  void StepWaitingRoll();
  bool StepFinished();
  void UpdateLagsStatistics(int delta);
  bool CheckFinishGameTimeout();
  bool UpdateGameFinishing(bool timeOut);

  void StepPlaySameTeamTimer();
  bool CheckPlaySameTeamTimer() const;

  void UpdateTrustedClient(int step)
  {
    // sending all commands for not sent steps to trusted client
    Peered::IGameClient* lclient = trustedClient.GetClient();
    if (lclient)
    {
      for (int i=trustedClient.nextStep;i<=step;++i)
      {
        clients.SendCommands(i, trustedClient, 0); 
      }
      trustedClient.nextStep = step+1;
    }
  }

  bool CheckStartCondition();
  bool CheckTimeoutCondition();
  void StartGame(int forcedStartTimerValue=0);

  bool IsAllClientsReadyToGo() const
  {
    if (data.sessionSettings.confirmFrequency > 0)
    {
      return clients.IsAllClientsReadyToGo(data.sessionSettings.trustGap*data.sessionSettings.confirmFrequency);
    }
    return true;
  }

  SchedulerData data;
  WorldData* worldData;
  Clients clients;
  ClientHolder trustedClient;
///////////////////
  
  Status status;
  float timeScale;
  float timeScaleOO;
  StrongMT<Peered::ICommandsHandler> handler;
  StrongMT<lobby::ISessionHybridLink> statsLink;
  StrongMT<Peered::GameServerReconnect> gameServerReconnect;
  AppFramework::InstanceStatistics stats;
  NLogg::CChannelLogger* logStream;
  threading::Mutex clientsLock;
  nstl::vector<Peered::ClientInfo> clientInfos;
  int lastConnectionTimeoutTimer;
  int firstConnectionTimeoutTimer;
  int rollTimeoutTimer;
  bool isGameResultsSent;
  uint allocid;
  StrongMT<HybridServer::IGameServerAllocatorNotify> allocNotify;
  int finishGameTimeoutTimer;
  bool isWaitingForSpectators;
  lobby::EGameResult::Enum gameResult;
  Transport::TServiceId reconnectIfaceId;
  StrongMT<IAwardsRequester> awardsRequester;
  StrongMT<Peered::IPeeredStatistics> statisticsWrapper;
  StrongMT<HybridServer::ICommandsLog> log;
  StrongMT<IGameServerInternal> internalInterface;
  WeakMT<HybridServer::IGameServerInstanceRegistrator> instanceRegistrator;

  NHPTimer::STime playSameTeamTimeout;
  NHPTimer::STime playSameTeamStartTime;
};

}

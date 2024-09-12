#include "stdafx.h"

#include "PeeredImpl.h"
#include "System/InlineProfiler.h"
#include "HybridServer/GameServerAllocatorIface.h"
#include "RPeered.auto.h"
#include "HybridServerNaming.h"
#include "HybridServerDumpersIfaces.h"
#include "HybridServerMulticast.h"


namespace Peered
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InternalInterfaceWrapper : public IGameServerInternal, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( InternalInterfaceWrapper, IGameServerInternal, BaseObjectMT );

public:
  InternalInterfaceWrapper( CommandsScheduler * _owner ) :
  owner( _owner )
  {}

private:
  InternalInterfaceWrapper() : owner(0) {};

  void SetOwner(CommandsScheduler * _owner) { owner = _owner; }

  CommandsScheduler * owner;

  //IGameServerInternal
  virtual bool OnRejoinClient( uint clientId )
  {
    if (owner)
      return owner->OnRejoinClient( clientId );
    return false;
  }

  virtual void AddSpectator( uint clientId, const wstring& nickname )
  {
    if (owner)
      owner->AddSpectator( clientId, nickname );
  }


  virtual void UserLeftTheGameInCastle( uint clientId )
  {
    if (owner)
      owner->UserLeftTheGameInCastle( clientId );
  }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommandsScheduler::CommandsScheduler(
  const SchedulerData& _data,
  const Transport::TServiceId & _reconnectIfaceId,
  Peered::ICommandsHandler* _handler, 
  HybridServer::ICommandsLog* _log,
  HybridServer::ICrcDumper* _crcDumper,
  const vector<ClientInfo>* _clientInfos,
  lobby::ISessionHybridLink * _statsLink,
  const SAuxData * _auxData,
  NLogg::CChannelLogger* _logStream,
  uint _allocid,
  HybridServer::IGameServerAllocatorNotify* _allocNotify,
  IAwardsRequester * _awardsRequester,
  const lobby::TGameLineUp * _gameLineUp,       // Needed for replay
  const lobby::SGameParameters * _gameParams,   // Needed for replay
  IPeeredStatistics * _statisticsWrapper,
  HybridServer::IMcChannelsWrapper * _mcChannelWrapper,
  HybridServer::IGameServerInstanceRegistrator * _instanceRegistrator):
  data(_data),
  reconnectIfaceId(_reconnectIfaceId),
  timeScale(_data.sessionSettings.timeScale),
  timeScaleOO(1.f/_data.sessionSettings.timeScale),
  handler(_handler),
  statsLink( _statsLink ),
  stats(NHPTimer::Milliseconds2Time(_data.sessionSettings.simulationStep + _data.sessionSettings.simulationStep*_data.sessionSettings.stepsDelayMin), true),
  logStream(_logStream),
  clients(_clientInfos?true:false, _logStream, _log, _crcDumper, data, _handler, _statsLink, _statisticsWrapper, _mcChannelWrapper),
  lastConnectionTimeoutTimer(0),
  isGameResultsSent(false),
  firstConnectionTimeoutTimer(0),
  rollTimeoutTimer(0),
  allocid(_allocid),
  allocNotify(_allocNotify),
  finishGameTimeoutTimer(0),
  isWaitingForSpectators(false),
  gameResult(lobby::EGameResult::Unknown),
  statisticsWrapper(_statisticsWrapper),
  log(_log),
  instanceRegistrator(_instanceRegistrator),
  playSameTeamTimeout(0LL),
  playSameTeamStartTime(0LL)
{
  internalInterface = new InternalInterfaceWrapper( this );

  worldData = new WorldData(0);
  if (handler)
  {
    handler->OnCreate(this);
  }
  if (_clientInfos)
  {
    for (int i=0;i<_clientInfos->size();++i)
    {
      clients.WaitClient( (*_clientInfos)[i].clientId, false, L"" );
    }
    clientInfos = *_clientInfos;
  }

  if (_awardsRequester && _auxData)
  {
    awardsRequester = _awardsRequester;
    awardsRequester->FillPreGameData(clientInfos, *_auxData);
  }

  if (_log)
  {
    if (_gameLineUp && _gameParams && _clientInfos)
      _log->OnHeaderDump(data, _gameLineUp, _gameParams, _clientInfos);
    else
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: Not enough data to write replay's header (sid=%016x)", data.serverId);
      clients.SetCommandsLog(0);
    }
  }

  if (data.sessionSettings.playSameTeamTimeout > 0)
  {
    playSameTeamTimeout = NHPTimer::Milliseconds2Time((data.sessionSettings.playSameTeamTimeout + 5) * 1000);
  }

  localLog(logStream, NLogg::LEVEL_DEBUG).Trace("GameServer: Create(sid=%016x cc=%d)", data.serverId, clients.GetTotalCount());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommandsScheduler::~CommandsScheduler()
{
  if (gameServerReconnect)
    gameServerReconnect->SetPointers(0, 0);

  if (internalInterface)
    internalInterface->SetOwner(0);

  if (worldData)
  {
    delete worldData;
    worldData = 0;
  }

  if (!isGameResultsSent)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace("GameServer: game terminated from above (sid=%016x)", data.serverId);
    FinishGame(lobby::EGameResult::NoResults);
  }

  localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
    "GameServer: Session destructed (sid=%016x)", data.serverId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CommandsScheduler::_AddClient(uint clientId, Login::ClientVersion clientVersion, IGameClient* _client, bool isReconnecting)
{
  ClientHolder& holder = clients.AddClient(clientId, clientVersion, _client);
  localLog(logStream, NLogg::LEVEL_DEBUG).Trace("GameServer: AddClient(sid=%016x cid=%d cidx=%d step=%d ver=%d.%d.%d.%d)", 
    data.serverId, clientId, holder.clientIndex, clients.GetPendingStep(), clientVersion.major_, clientVersion.minor_,
      clientVersion.patch_, clientVersion.revision_);

  if (isReconnecting)
  {
    clients.AddRejoinClient(holder.clientIndex, clientId);
    clients.OnRejoin(clientId);

    if (!gameServerReconnect)
    {
      gameServerReconnect = new GameServerReconnect(clients, clientsLock);
      clients.SetGameServerReconnect(gameServerReconnect, reconnectIfaceId);
    }

    //holder.Start(data, clientInfos, isReconnecting, RemotePtrInOtherGate<Peered::RIGameServerReconnect>(gameServerReconnect, reconnectIfaceId));
    holder.Start(data, clientInfos, isReconnecting, RemotePtr<Peered::RIGameServerReconnect>(gameServerReconnect));
  }
  else
  {
    if (data.sessionSettings.multicastStepsEnabled)
      clients.AddClientToMcChannel(holder);

    holder.Start(data, clientInfos, isReconnecting, 0);
  }

  holder.SetTimeScale(timeScale);
  worldData->Apply(holder, data.sessionSettings.confirmFrequency);
  if (clients.GetStatus() == Clients::Loading)
  {
    holder.Rewind(clients.GetPendingStep(), data.sessionSettings.confirmFrequency);
  } 
  holder.SetAppliedStep(worldData->GetChangesInfo());
  lastConnectionTimeoutTimer = 0;
  return holder.clientIndex;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::AddClient(const char* name, uint clientId, const Login::ClientVersion& clientVersion, IGameClient* _client)
{
  if (_client)
  {
    threading::MutexLock lock(clientsLock);

    if (clients.IsClientAwaited(clientId))
    {
      if (clients.GetStatus() == Clients::WaitingForClients)
      {
        clients.SetStatus(Clients::Loading);
      }
      if (clients.GetStatus() == Clients::Loading)
      {
        _AddClient(clientId, clientVersion, _client, false);
      } 
      else if (data.sessionSettings.reconnectEnabled && data.sessionSettings.confirmFrequency > 0 
               && (clients.GetStatus() == Clients::Started || clients.GetStatus() == Clients::Blocked))
      {
        // We can get in while blocked, with hope, that async will be successfully resolved

        ClientHolder* passiveClient = clients.GetPassiveClient(clientId);

        if (!passiveClient || passiveClient->GetStatus() != Peered::DisconnectedByCheatAttempt)
        {
          // Rejoin during started game
          _AddClient(clientId, clientVersion, _client, true);
        }
        else
        {
          localLog(logStream, NLogg::LEVEL_WARNING).Trace(
            "GameServer: AddClient disconnected by cheat attempt (sid=%016x cid=%d step=%d), ignored", 
              data.serverId, clientId, clients.GetPendingStep());
          _client->OnDisconnect(int(EDisconnectReason::ServerError));
          // Notify lobby that cheater is kicked again
          clients.OnChangeClientStatus(passiveClient->GetInfo(), true, false);
          clients.LogReconnectResult(clientId, EReconnectType::Normal, EReconnectResult::Cheated);
        }
      }
      else
      {
        localLog(logStream, NLogg::LEVEL_WARNING).Trace(
          "GameServer: AddClient while game is in \"%s\" state (sid=%016x cid=%d step=%d), ignored", 
            Clients::GetStatus(clients.GetStatus()), data.serverId, clientId, clients.GetPendingStep());
        _client->OnDisconnect(int(EDisconnectReason::ServerError));
        clients.LogReconnectResult(clientId, EReconnectType::Normal, (data.sessionSettings.reconnectEnabled)?(EReconnectResult::WrongSesionState):(EReconnectResult::Disabled));
      }
    } 
    else
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: AddClient with unexpected clientId (sid=%016x cid=%d step=%d), ignored", 
          data.serverId, clientId, clients.GetPendingStep());
      _client->OnDisconnect(int(EDisconnectReason::ServerError));
    }
  } 
  else
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: AddClient with null object(sid=%016x cid=%d step=%d), ignored", 
        data.serverId, clientId, clients.GetPendingStep() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::AddClientFast(int clientId, int clientIndex, NI_LPTR Peered::IGameClient* _client, int fromStep)
{
  threading::MutexLock lock(clientsLock);
  
  if (!data.sessionSettings.fastReconnectReserveSteps)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: AddClientFast while fast reconnect disabled (sid=%016x cid=%d cidx=%d fromStep=%d step=%d), ignored", 
        data.serverId, clientId, clientIndex, fromStep, clients.GetPendingStep());
    _client->OnDisconnect(int(EDisconnectReason::ServerError));
    clients.LogReconnectResult(clientId, EReconnectType::Fast, EReconnectResult::Disabled);
    return;
  }

  if (clients.GetStatus() == Clients::Started)
  {
    if (ClientHolder * client = clients.AddClientFast(clientId, clientIndex, _client, fromStep))
    {
      localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
        "GameServer: AddClientFast (sid=%016x cid=%d cidx=%d fromStep=%d step=%d lastReservedStep=%d lastConfirmedStep=%d)", 
          data.serverId, clientId, clientIndex, fromStep, clients.GetPendingStep(), clients.GetLastReservedStep(), 
            clients.GetLastConfirmedStep());

      if (data.sessionSettings.multicastStepsEnabled)
        clients.AddClientToMcChannel(*client);

      client->SetTimeScale(timeScale);

      clients.LogReconnectResult(clientId, EReconnectType::Fast, EReconnectResult::Success);

      // TODO: Two calls below currently aren't used, but make wrong rewind - fix when needed
      //worldData->Apply(*client, data.confirmFrequency);
      //client->SetAppliedStep(worldData->GetChangesInfo());
    }
    //else - errors are printed in the clients.AddClientFast code
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: AddClientFast while game is in \"%s\" state (sid=%016x cid=%d cidx=%d fromStep=%d step=%d), ignored", 
        Clients::GetStatus(clients.GetStatus()), data.serverId, clientId, clientIndex, fromStep, clients.GetPendingStep());
    _client->OnDisconnect(int(EDisconnectReason::ServerError));
    clients.LogReconnectResult(clientId, EReconnectType::Fast, EReconnectResult::WrongSesionState);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::SendCommand(int clientIndex, const rpc::MemoryBlock& info, bool isPlayerCommand)
{
  threading::MutexLock lock(clientsLock);
  
  ClientHolder* client = clients.GetClient(clientIndex);
  if (client)
  {
    if (!client->IsSpectator())
    {
      if (info.size >= sizeof(int)*2 && (data.sessionSettings.commandMaxSize <= 0 
            || info.size <= uint(data.sessionSettings.commandMaxSize)))
      {
        uint clientId;
        memcpy(&clientId, (char*)info.memory+4, sizeof(clientId));

        if (clientId == client->GetClientId())
        {
          client->AddCommandSize(info.size);
          const int sizeLimit = data.sessionSettings.commandsPerStepMaxSize / clients.GetTotalCount();

          if (data.sessionSettings.commandsPerStepMaxSize <= 0 || client->GetCommandsSizeFromLastStep() <= sizeLimit)
          {
            clients.AddCommand(*client, info, isPlayerCommand);
          }
          else
          {
            localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
              "GameServer: SendCommand: Client commands size per step overflow (sid=%016x cid=%d cidx=%d size=%d maxSize=%d)", 
                data.serverId, client->GetClientId(), clientIndex, client->GetCommandsSizeFromLastStep(), sizeLimit);
            // We do not kick such client, because it can be a result of lag. We just ignore.
            // DOS attacks will be detected on relay.
            //clients.OnGameCheated(client->GetClientId(), clientIndex);
          }
        }
        else
        {
          localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
            "GameServer: SendCommand: Command with wrong clientId detected (sid=%016x cid=%d cidx=%d commandCid=%d)", 
              data.serverId, client->GetClientId(), clientIndex, clientId);
          clients.OnGameCheated(client->GetClientId(), clientIndex);
        }
      }
      else
      {
        localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
          "GameServer: SendCommand: Wrong command size (sid=%016x cid=%d cidx=%d commandSize=%d minSize=%d maxSize=%d)", 
            data.serverId, client->GetClientId(), clientIndex, info.size, sizeof(int)*2, data.sessionSettings.commandMaxSize);
        clients.OnGameCheated(client->GetClientId(), clientIndex);
      }
    }
    else
    {
      localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
        "GameServer: SendCommand: Command from spectator detected (sid=%016x cid=%d cidx=%d)", 
          data.serverId, client->GetClientId(), clientIndex);
      // Just disconnect for current (simple) version of spectator
      //clients.OnGameCheated(client->GetClientId(), clientIndex);
      clients.DisconnectClient(clientIndex);
    }
  }
  else
  {
    if (!clients.IsClientDisconnected(clientIndex))  // check if client was disconnected
    {
      localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
        "GameServer: SendCommand: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::OnClientReady(int clientIndex)
{
  threading::MutexLock lock(clientsLock);
  ClientHolder* client = clients.GetClient(clientIndex);
  if (!client)
  {
    if (ClientHolder* client = clients.GetPassiveClientByIndex(clientIndex))
    {
      localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
        "GameServer: OnClientReady: client is disconnected(sid=%016x cid=%d cidx=%d)",
          data.serverId, client->GetClientId(), clientIndex);
    }
    else
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: OnClientReady: client not found(sid=%016x cidx=%d)", data.serverId, clientIndex);
    }
    return;
  }

  uint clientId = client->GetClientId();

  if (clients.IsClientRejoins(clientIndex) && !clients.IsWorldSentToRejoiner(clientIndex))
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: OnClientReady: world data wasn't sent to client(sid=%016x cid=%d cidx=%d)", 
        data.serverId, clientId, clientIndex);
    clients.OnGameCheated(clientId, clientIndex);
    clients.DisconnectRejoiningClient(clientIndex, Peered::EDisconnectReason::ServerError);
    clients.LogReconnectResult(clientId, EReconnectType::Normal, EReconnectResult::Cheated);
    return;
  }

  localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
    "GameServer: OnClientReady(sid=%016x cid=%d cidx=%d)", data.serverId, clientId, clientIndex);

  if (client->GetStatus() == Peered::Connecting)
  {
    client->OnReady();
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: OnClientReady: Wrong client status \"%s\" (sid=%016x cid=%d cidx=%d)", 
        clients.GetClientStatus(client->GetStatus()), data.serverId, clientId, clientIndex);
    clients.OnGameCheated(clientId, clientIndex);
    return;
  }

  if (clients.GetStatus() == Clients::Started || clients.GetStatus() == Clients::Blocked)
  {
    const int currentStep = clients.GetPendingStep();

    if (clients.IsClientRejoins(clientIndex))
    {
      RejoinerData* rejoinerData = clients.GetRejoinerData(clientIndex);
      int worldAppliedStep = rejoinerData->GetWorldAppliedStep();
      clients.RemoveRejoinClient(clientIndex);
      client->OnStart(worldAppliedStep);
      clients.OnChangeClientStatus(client->GetInfo(), false, true);
      if (client->nextStep < currentStep)
        clients.UpdateClientCommands(*client, true, currentStep - 1);
      client->SetGapOdd(client->GetGap());

      if (data.sessionSettings.multicastStepsEnabled)
        clients.AddClientToMcChannel(*client);

      clients.LogReconnectResult(clientId, EReconnectType::Normal, EReconnectResult::Success);
    }
    else
    {
      client->OnStart(currentStep, data.sessionSettings.confirmFrequency);
    }
  }
  else if (clients.GetStatus() == Clients::Loading)
  {
    if (CheckStartCondition())
    {
      StartGame();
    }
  }

  if (client->IsSpectator())
  {
    const SpectatorInfo info(clientId, client->nickname);

    clients.OnSpectate(info);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::OnFinishStep(int clientIndex, uint _step, uint worldCrc)
{
  threading::MutexLock lock(clientsLock);

  if (clients.GetStatus() == Clients::Terminated)
  {
    // We don't process finish step when terminated (may occur for timed out clients on game finish)
    return;
  }

  ClientHolder* client;
  bool isClientTrusted = (trustedClient.GetClient() && int(trustedClient.GetClientId()) == clientIndex);
  if (isClientTrusted)
  {
    client = &trustedClient;
  }
  else
  {
    client = clients.GetClient(clientIndex);
    if (!client)
    {
      if (!clients.IsClientDisconnected(clientIndex))  // check if client was disconnected
      {
        localLog(logStream, NLogg::LEVEL_WARNING).Trace(
          "GameServer: OnFinishStep: Client not found (sid=%016x cidx=%d step=%d)", data.serverId, clientIndex, _step);
      }
      return; 
    }
  }


  if (data.sessionSettings.confirmFrequency == 0 || _step % data.sessionSettings.confirmFrequency != 0)
  {
    return;
  }

  if (clients.GetStatus() == Clients::Loading)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: OnFinishStep: Called before OnStart (sid=%016x cid=%d cidx=%d step=%d)", 
        data.serverId, client->GetClientId(), clientIndex, _step);
    return;
  }

  WorldSnapshot* snapshot = clients.GetWorldSnapshot(_step);
  if (!snapshot)
  {
    if (!clients.IsClientDisconnected(clientIndex))  // check if client was disconnected
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: OnFinishStep: Snapshot not found (sid=%016x cid=%d cidx=%d step=%d lastConfirmedStep=%d)", 
          data.serverId, client->GetClientId(), clientIndex, _step, clients.GetLastConfirmedStep());
      // TODO: notify about cheater
    }
    return; 
  }

  if (!isClientTrusted)
  {
    //  TODO: fix code to use if (int(_step) == client->lastSentVerifiedStep + data.confirmFrequency)
    if (int(_step) <= client->GetLastSentStep())
    {
      if (client->CheckStepVerification(_step, data.sessionSettings.confirmFrequency))
      {
        client->SetLastSentVerifiedStep(_step);
      }
      else
      {
        localLog(logStream, NLogg::LEVEL_WARNING).Trace(
          "GameServer: OnFinishStep: Wrong step confirmation recieved (sid=%016x cid=%d cidx=%d step=%d lastRecieved=%d)",
            data.serverId, client->GetClientId(), clientIndex, _step, client->GetLastSentVerifiedStep());
        // FIXME: should be marked as cheater, but currently just disconnected due to fast reconnect bug NUM_TASK
        //clients.OnGameCheated(client->GetClientId(), clientIndex);
        clients.DisconnectClient(clientIndex);
        return;
      }
    }
    else
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: OnFinishStep: Step confirmation recieved for not sent step (sid=%016x cid=%d cidx=%d step=%d lastSent=%d)",
          data.serverId, client->GetClientId(), clientIndex, _step, client->GetLastSentStep());
      clients.OnGameCheated(client->GetClientId(), clientIndex);
      return;
    }
  }

  UpdateResult result = snapshot->Update(clientIndex, worldCrc, isClientTrusted);

  if (result.needToVerify)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: Async detected (sid=%016x cid=%d cidx=%d step=%d)", 
        data.serverId, client->GetClientId(), clientIndex, _step);

    nstl::vector<AsyncInfoInternal> asyncs;
    snapshot->GetCrcInfo(asyncs);
    for (int i=0;i<asyncs.size();++i)
    {
      localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
        "GameServer:       cidx=%d crc=0x%08X", asyncs[i].clientIndex, asyncs[i].crc);
    }
    if (clients.GetStatus() != Clients::Blocked)
    {
      //clients.Block(true); // Do not block, so reconnecting clients will get missed commands. Others won't be steped any way.
      clients.SetStatus(Clients::Blocked);
    }
    if (snapshot->IsAllRecieved(false))
    {
      localLog(logStream, NLogg::LEVEL_ERROR).Trace(
        "GameServer: OnFinishStep: All crcs recieved, processing async recovery (sid=%016x step=%d)", data.serverId, _step);

      clients.CheckAsyncSnapshots();
    }
    UpdateTrustedClient(_step);
  } 

  if (result.needToPatch)
  {
    PatchData patch;
    snapshot->FillPatchData(patch);
    for (int i=0;i<patch.patches.size();++i)
    {
      ClientPatchData& data = patch.patches[i];
      ClientHolder* client = clients.GetClient(data.clientIndex);
      if (client)
      {
        client->ApplySnapshot(patch.step, patch.crc, data.entitiesIds, data.entitiesData);
      }
    }
    //clients.Block(false);
    clients.MarkVerified(patch.step);
    clients.SetStatus(Clients::Started);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::SetTimeScale(int clientIndex, float _scale)
{
  threading::MutexLock lock(clientsLock);
  ClientHolder* client = clients.GetClient(clientIndex);

  if (!client)
  {
    client = clients.GetDisconnectedClient(clientIndex);
    if (!client)
    {
      localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
        "GameServer: SetTimeScale: Client not found (sid=%016x cidx=%d), ignored", data.serverId, clientIndex);
      return;
    }
  }

  if (!data.sessionSettings.timescaleEnabled)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: SetTimeScale: Timescale disabled (sid=%016x cid=%d cidx=%d)", 
        data.serverId, client->GetClientId(), clientIndex);
    clients.OnGameCheated(client->GetClientId(), clientIndex);
    return;
  }

  if (_scale != timeScale)
  {
    float scale;
    scale = (_scale > 0.f && _scale <= 10.f) ? (_scale) : (0.f);
    timeScale = scale;
    timeScaleOO = (scale > 0.f) ? (1.f/scale) : (1.f);

    clients.SetTimeScale(timeScale);

    localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace(
      "GameServer: SetTimeScale: New timescale applied (sid=%016x cid=%d cidx=%d timeScale=%f)", 
        data.serverId, client->GetClientId(), clientIndex, timeScale);
  }
}

static TSessionId serverIdToLog = -1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CommandsScheduler::Step(int delta)
{
  NI_PROFILE_FUNCTION;

  UpdateLagsStatistics(delta);

  threading::MutexLock lock(clientsLock);
  int activeClientsCount = clients.CheckClients(handler, this);
  clients.CheckPassiveClients();

  // TODO: this overgrown if-driven code should be refactored

  if (clients.GetStatus() == Clients::WaitingForClients)
  {
    firstConnectionTimeoutTimer++;
    if (data.sessionSettings.firstConnectionTimeout > 0 
          && firstConnectionTimeoutTimer >= data.sessionSettings.firstConnectionTimeout)
    {
      localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
        "GameServer: no clients connected, exit (sid=%016x firstConnectionTimeout=%d)", 
          data.serverId, data.sessionSettings.firstConnectionTimeout);
      FinishGame(lobby::EGameResult::NobodyCame);
    }
  } 
  else if (clients.GetStatus() == Clients::Finishing)
  {
    if (activeClientsCount == 0)
    {
      UpdateGameFinishing(true);
      localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
        "GameServer: all clients disconnected before sending results, exit (sid=%016x)", data.serverId);
    }
    else if (CheckFinishGameTimeout())
    {
      localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
        "GameServer: Step: Game finish timed out (sid=%016x, timer=%d)",
          data.serverId, data.sessionSettings.finishTimeoutSteps);
      UpdateGameFinishing(true);
    }
  } //TODO: optimaize this ugly if!
  else if (activeClientsCount == 0 && (clients.GetStatus() == Clients::Started || (clients.GetStatus() == Clients::Loading && clients.GetWaitCount() == 0) || clients.GetStatus() == Clients::Blocked)
          || (clients.GetStatus() == Clients::Blocked || clients.GetStatus() == Clients::Started) && clients.GetPlayingCount() == 0 && clients.GetRejoinWithWorldAppliedCount() == 0)
  {
    localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace("GameServer: all clients disconnected, exit (sid=%016x)", data.serverId);
    FinishGame((clients.GetStatus() == Clients::Blocked)?lobby::EGameResult::Async:lobby::EGameResult::NoResults);
  }

  if (clients.GetStatus() == Clients::Loading)
  {
    StepLoading();
  }

  if (clients.GetStatus() == Clients::WaitingRoll)
  {
    StepWaitingRoll();
  }

  if (clients.GetStatus() == Clients::Finished)
  {
    StepPlaySameTeamTimer();

    if (StepFinished())
      return AppFramework::REMOVE_FROM_QUEUE;
  }

  if (clients.GetStatus() == Clients::Started || clients.GetStatus() == Clients::Blocked 
      || clients.GetStatus() == Clients::Finishing)
  {
    clients.UpdateSnapshots();
    //clients.UpdateProtection();
  }

  if(clients.GetStatus() == Clients::Blocked)
  {
    if (data.sessionSettings.crcDataRequestsEnabled)
    {
      clients.CheckCrcDataRequestsTimeOut();
    }

    clients.UpdateCommandsBlocked();
  }
  else if((clients.GetStatus() == Clients::Loading || clients.GetStatus() == Clients::Started)
          && IsAllClientsReadyToGo())
  {
    bool stepped = false;
    if (clients.GetStatus() == Clients::Started)
    {
      if (timeScale > 0.f)
      {
        clients.MakeStep();
        stepped = true;
      }
    }
    else if (clients.GetStatus() == Clients::Loading)
    {
      NI_PROFILE_BLOCK( "Check for game start" );
      bool startGame = CheckStartCondition();
      bool isForcedStart = false;
      if (!startGame)
      {
        isForcedStart = CheckTimeoutCondition();
      }
      if (startGame || isForcedStart)
      {
        localLog(logStream, NLogg::LEVEL_MESSAGE).Trace("GameServer: Start game from step (sid=%016x)", data.serverId);
        StartGame(isForcedStart?lastConnectionTimeoutTimer:0);
        clients.MakeStep();
        stepped = true;
      }
      else if (clients.HavePendingCommands())
      {
        clients.MakeStep();
        stepped = true;
      }
    }

    clients.SendStep(stepped);
  }

  return int(data.sessionSettings.simulationStep*timeScaleOO);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::StepLoading()
{
  if (data.sessionSettings.firstConnectionTimeout > 0 && firstConnectionTimeoutTimer != -1)
  {
    ++firstConnectionTimeoutTimer;
    if (firstConnectionTimeoutTimer >= data.sessionSettings.firstConnectionTimeout)
    {
      clients.OnFirstConnectionTimeout();
      firstConnectionTimeoutTimer = -1;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::StepWaitingRoll()
{
  if (awardsRequester)
  {
    awardsRequester->Step();

    ++rollTimeoutTimer;

    if (awardsRequester->IsAwardsReceived() 
        || data.sessionSettings.rollTimeout > 0 && rollTimeoutTimer >= data.sessionSettings.rollTimeout)
    {
      TUserAwards awards;

      if (awardsRequester->IsAwardsReceived())
      {
        awardsRequester->GetResults(&awards);
      }
      else
      {
        localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
          "GameServer: Awards roll request timed out. Sending default (empty) results (sid=%016x rollTimeout=%d)", 
            data.serverId, data.sessionSettings.rollTimeout);
      }

      clients.AwardClients(awards);
      clients.SetStatus(Clients::Finished);
    }
  }
  else
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: Awards roll requesting object is missing. Cancelling roll (sid=%016x)", data.serverId);

    clients.SetStatus(Clients::Finished);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandsScheduler::StepFinished()
{
  // We wait for spectators only in case of normal game finish (SyncResults).
  bool finishGame = gameResult != lobby::EGameResult::SyncResults 
                    || gameResult == lobby::EGameResult::SyncResults && clients.IsAllActiveSpectatorsFinishedGame();

  if (!finishGame)
  {
    if (!isWaitingForSpectators)
    {
      localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace(
        "GameServer: waiting for spectators (sid=%016x, remainingTimer=%d, timer=%d)",
          data.serverId, data.sessionSettings.finishTimeoutSteps - finishGameTimeoutTimer,
            data.sessionSettings.finishTimeoutSteps);

      isWaitingForSpectators = true;
    }

    // We reuse here same timer as for players without reinitializing it.
    // So we won't get double waiting in possible extreme conditions.
    finishGame = CheckFinishGameTimeout();

    if (finishGame)
    {
      localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace(
        "GameServer: waiting for spectators timed out (sid=%016x)", data.serverId);
    }
  }

  if (finishGame)
  {
    finishGame = CheckPlaySameTeamTimer();

    if (finishGame)
    {
      localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace(
        "GameServer: waiting for 'play same team' timed out (sid=%016x)", data.serverId);
    }
  }

  if (finishGame)
  {
    localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace("GameServer: game finished, exit (sid=%016x)", data.serverId);

    clients.DisconnectAllClients(Peered::EDisconnectReason::GameFinished);
    clients.SetStatus(Clients::Terminated);

    // Dump replay's tail
    clients.DumpSteps(clients.GetPendingStep()-1);
    if (log)
    {
      log->OnFinishGame(data.serverId, clients.GetPendingStep());
      log = 0;
      clients.SetCommandsLog(0);
    }

    StrongMT<HybridServer::IGameServerInstanceRegistrator> locked = instanceRegistrator.Lock();
    if (locked)
      locked->UnregisterInstance( this );
  }

  return finishGame;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::UpdateLagsStatistics(int delta)
{
  if (stats.IsStarted())
  {
    NHPTimer::STime stepTime = stats.Stop();

    if (data.sessionSettings.logLag > 0)
    {
      int stepTimeMs = NHPTimer::Time2Milliseconds(stepTime);
      if (stepTimeMs > data.sessionSettings.simulationStep + data.sessionSettings.logLag)
      {
        localLog(logStream, NLogg::LEVEL_WARNING).Trace(
          "GameServer: step lag detected (sid=%016x stepTime=%d logLag=%d lateTime=%d)", 
            data.serverId, stepTimeMs, data.sessionSettings.logLag, delta);
      }
    }
  }

  if (stats.GetCount() == 50)
  {
    if (serverIdToLog == -1 || data.serverId == serverIdToLog)
    {
      const AppFramework::InstanceStatistics::ValueAccumulator& info = stats.Finish();
      int avgValueTimeMs = NHPTimer::Time2Milliseconds(info.averageValue);
      if ((avgValueTimeMs - data.sessionSettings.simulationStep) > 2 || stats.GetLongTimeCount() > 0)
      {
        int minValueTimeMs = NHPTimer::Time2Milliseconds(info.minValue);
        int maxValueTimeMs = NHPTimer::Time2Milliseconds(info.maxValue);

        localLog(logStream, NLogg::LEVEL_WARNING).Trace(
          "GameServer: lags detected (sid=%016x min=%d average=%d max=%d longTimeCnt=%d)", 
            data.serverId, minValueTimeMs, avgValueTimeMs, maxValueTimeMs, stats.GetLongTimeCount());

        if (statisticsWrapper)
        {
          StatisticService::RPC::ExceedingStepTimeInfoServer info;

          info.sessionId = data.serverId;
          info.currentStep = clients.GetPendingStep();
          info.startTime = stats.GetFirstStartTimeStamp();
          info.finishTime = stats.GetFinishTimeStamp();
          info.stepCount = stats.GetLongTimeCount();
          info.stepTimeMin = minValueTimeMs;
          info.stepTimeMax = maxValueTimeMs;
          info.stepTimeAvg = avgValueTimeMs;

          statisticsWrapper->LogGSLag(info);
        }
      }
    }
    stats.Reset();
  }
  stats.Start();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandsScheduler::CheckFinishGameTimeout()
{
  if (data.sessionSettings.finishTimeoutSteps > 0)
  {
    if (finishGameTimeoutTimer >= data.sessionSettings.finishTimeoutSteps)
    {
      return true;
    }
    ++finishGameTimeoutTimer;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandsScheduler::UpdateGameFinishing(bool timeOut)
{
  if (timeOut || clients.IsAllClientsFinished())
  {
    const StatisticService::RPC::SessionClientResults * finishResults = clients.GetFinishResults();

    if (finishResults)
    {
      FinishGame(lobby::EGameResult::SyncResults, finishResults);
    }
    else
    {
      FinishGame(lobby::EGameResult::AsyncResults);
    }

    return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Peered::CommandsScheduler::StepPlaySameTeamTimer()
{
  if (playSameTeamTimeout < 1LL)
    return;

  if (playSameTeamStartTime == 0LL)
  {
    NHPTimer::GetTime(playSameTeamStartTime);

    if (playSameTeamStartTime < 0LL)
      localLog(logStream, NLogg::LEVEL_ERROR).Trace("GameServer: Timer overflow? (sid=%016x)", data.serverId);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Peered::CommandsScheduler::CheckPlaySameTeamTimer() const
{
  if (playSameTeamTimeout < 1LL)
    return true;

  NHPTimer::STime time;
  NHPTimer::GetTime(time);

  time -= playSameTeamStartTime;
  time -= playSameTeamTimeout;

  return (time >= 0LL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::OnGameFinish(int clientIndex, int step, const StatisticService::RPC::SessionClientResults & finishInfo)
{
  threading::MutexLock lock(clientsLock);
  ClientHolder* client = clients.GetClient(clientIndex);
  if (!client)
  {
    client = clients.GetDisconnectedClient(clientIndex);
    if (!client)
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: OnGameFinish: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
      return;
    }
  }

  // only sent steps can be marked as finished
  if (step > client->GetLastSentStep())
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: OnGameFinish: Invalid game finish step received (sid=%016x cid=%d cidx=%d step=%d)", 
        data.serverId, client->GetClientId(), clientIndex, step);
    clients.OnGameCheated(client->GetClientId(), clientIndex);
    return;
  }

  if (client->IsSpectator())
  {
    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "GameServer: OnGameFinish: Game finish from spectator (sid=%016x cid=%d cidx=%d step=%d)",
        data.serverId, client->GetClientId(), clientIndex, step);
    // Just set the finish step, so we will know he finished already
    client->finishStep = step;
    return;
  }

  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: OnGameFinish: Game results received (sid=%016x cid=%d cidx=%d step=%d)", 
        data.serverId, client->GetClientId(), clientIndex, step);
  }

  if (clients.GetStatus() == Clients::Started)
  {
    client->OnGameFinish(step, finishInfo);
    if (clients.GetPlayingCount() > 1)
    {
      clients.SetStatus(Clients::Finishing);
    }
    else
    {
      FinishGame(lobby::EGameResult::SyncResults, &finishInfo);
    }
  }
  else if (clients.GetStatus() == Clients::Finishing)
  {
    if (client->OnGameFinish(step, finishInfo))
    {
      if (UpdateGameFinishing(false))
      {
        return;
      }
    }
    else
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: OnGameFinish: Game finish step already set (sid=%016x cid=%d cidx=%d)", 
          data.serverId, client->GetClientId(), clientIndex);
      clients.OnGameCheated(client->GetClientId(), clientIndex);
      return;
    }
  } 
  else
  {
    // this method can be called only in Started, Finishing and (if time out occured) in Terminated state
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: OnGameFinish called, while session is in \"%s\" status (sid=%016x cid=%d cidx=%d) ignored", 
        clients.GetStatus(clients.GetStatus()), data.serverId, client->GetClientId(), clientIndex);

    if (clients.GetStatus() != Clients::Terminated)
    {
      clients.OnGameCheated(client->GetClientId(), clientIndex);
    }
    return;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::RequestWorldData(int clientIndex)
{
  threading::MutexLock lock(clientsLock);
  ClientHolder* client = clients.GetClient(clientIndex);
  if (!client)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: RequestWorldData: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
    return;
  }

  RejoinerData* rejoinerData = clients.GetRejoinerData(clientIndex);
  if (!rejoinerData)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: RequestWorldData: Client not in the rejoiners list (sid=%016x cid=%d cidx=%d)", 
        data.serverId, client->GetClientId(), clientIndex);
    clients.OnGameCheated(client->GetClientId(), clientIndex);
    return;
  }

  localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
    "GameServer: Request world data from server (sid=%016x cid=%d cidx=%d)", 
      data.serverId, client->GetClientId(), clientIndex);

  rejoinerData->SetWorldRequested(true);
  clients.SetNeedToApplyWorldData(true);
  //int minStep = (data.confirmFrequency>0)?(((clients.GetPendingStep()-2)/data.confirmFrequency)*data.confirmFrequency):(clients.GetPendingStep()-2);
  //clients.AddClientToSnapshots(clientIndex, minStep);
  clients.AddClientToSnapshots(clientIndex, 0, true);
  clients.AddClientToProtectionRecords(clientIndex, 0, true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::FinishGame(int gameResultType, const StatisticService::RPC::SessionClientResults * _gameResults)
{
  if (isGameResultsSent)
    return;

  gameResult = lobby::EGameResult::Enum(gameResultType);

  clients.CancelCrcDataRequests();

  if (statsLink)
  {
    StatisticService::RPC::SessionClientResults defaultResults;
    const StatisticService::RPC::SessionClientResults * gameResults = _gameResults;
    if (!gameResults) 
    {
      clients.FillDefaultGameResults(defaultResults);
      gameResults = &defaultResults;
    }

    nstl::vector<Peered::SClientStatistics> clientsStatistics;

    uint totalSeconds = clients.FillClientStatistics(clientsStatistics);

    if (awardsRequester)
    {
      awardsRequester->FillPostGameData((lobby::EGameResult::Enum)gameResultType, *gameResults, clientsStatistics, totalSeconds);
      clients.SetStatus(Clients::WaitingRoll);
    }
    else
    {
      localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
        "GameServer: No awards requester - finishing whithout awards (sid=%016x)", data.serverId);
      clients.SetStatus(Clients::Finished);
    }
    
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace("GameServer: sending game results (sid=%016x result=%d)", data.serverId, gameResultType);
    statsLink->OnGameFinish(data.serverId, gameResultType, *gameResults, clientsStatistics );
  }
  else
  {
    //TODO: do we need some special handling for this situation? Roll won't occur if we don't have hybrid link...
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace("GameServer: no game results (sid=%016x)", data.serverId);
    clients.SetStatus(Clients::Finished);
  }
  isGameResultsSent = true;
  clients.DisconnectRejoiningClients(Peered::EDisconnectReason::GameFinished);
  clients.LogTraffic();

  if (allocNotify)
  {
    allocNotify->FreeNotify(allocid);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandsScheduler::OnRejoinClient(uint clientId)
{
  threading::MutexLock lock(clientsLock);
  return clients.OnRejoinClient(clientId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandsScheduler::OnGameLeave(int clientIndex)
{
  threading::MutexLock lock(clientsLock);
  return clients.OnGameLeave(clientIndex, this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::SendCrcData(int clientIndex, int step, const rpc::MemoryBlock& crcData)
{
  threading::MutexLock lock(clientsLock);
  clients.SendCrcData(clientIndex, step, crcData);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::OnDisconnectAck(int clientIndex)
{
  threading::MutexLock lock(clientsLock);
  clients.OnDisconnectAck(clientIndex);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::DispatchPlaySameTeamDecision(int clientIndex, const bool agreed)
{
  threading::MutexLock lock(clientsLock);
  clients.DispatchPlaySameTeamDecision(clientIndex, agreed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::DispatchBadBehaviourComplaint(int clientIndex, const Transport::TClientId reportedClientId, const int reportItemId)
{
  threading::MutexLock lock(clientsLock);
  clients.DispatchBadBehaviourComplaint(clientIndex, reportedClientId, reportItemId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::OnProtectionError(int clientIndex)
{
  threading::MutexLock lock(clientsLock);

  if (const ClientHolder* const client = clients.GetClient(clientIndex))
    clients.OnGameCheated(client->GetClientId(), clientIndex, lobby::ECheatType::GameLogicHack);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::SendProtectionMagic(int clientIndex, int step, uint magic)
{
  threading::MutexLock lock(clientsLock);

  if (clients.GetStatus() == Clients::Terminated)
    return;

  clients.PushMagicRecord(clientIndex, step, magic);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::AddSpectator( uint clientId, const wstring& nickname )
{
  threading::MutexLock lock(clientsLock);
  clients.AddSpectator( clientId, nickname );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::UserLeftTheGameInCastle( uint clientId )
{
  threading::MutexLock lock(clientsLock);
  if (ClientHolder * client = clients.GetPassiveClient(clientId))
  {
    client->SetStatus(Peered::RefusedToReconnect);
    clients.OnChangeClientStatus(client->GetInfo(), false, true);
    clients.LogClientStatus(client->GetInfo());

    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "GameServer: UserLeftTheGameInCastle (sid=%016x cid=%d cidx=%d step=%d)",
        data.serverId, clientId, client->clientIndex, clients.GetPendingStep());
  }
  else
  {
    if (ClientHolder * client = clients.GetActiveClient(clientId))
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: UserLeftTheGameInCastle: Client is active (sid=%016x cid=%d cidx=%d step=%d)",
          data.serverId, clientId, client->clientIndex, clients.GetPendingStep());
    }
    else
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: UserLeftTheGameInCastle: Client not found (sid=%016x cid=%d step=%d)",
          data.serverId, clientId, clients.GetPendingStep());
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandsScheduler::CheckStartCondition()
{
  int waitCount = clients.GetWaitCount();
  if (waitCount == 0 || waitCount == clients.GetPassiveSpectotorsCount())
  {
    return (clients.GetReadyCount() == clients.GetActiveCount());
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandsScheduler::CheckTimeoutCondition()
{
  if (data.sessionSettings.connectionTimeout > 0)
  {
    if (clients.GetReadyCount() == clients.GetActiveCount())
    {
      ++lastConnectionTimeoutTimer;
      if (lastConnectionTimeoutTimer >= data.sessionSettings.connectionTimeout)
      {
        return true;
      }
    }
    else
    {
      lastConnectionTimeoutTimer = 0;
    }
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CommandsScheduler::StartGame(int forcedStartTimerValue)
{
  clients.StartGame(forcedStartTimerValue);
  worldData->MarkBuilt();
}

}
NI_DEFINE_REFCOUNT(Peered::CommandsScheduler);
NI_DEFINE_REFCOUNT(Peered::GameServerReconnect);
NI_DEFINE_REFCOUNT(lobby::ISessionHybridLink);
NI_DEFINE_REFCOUNT(Peered::IGameClient);

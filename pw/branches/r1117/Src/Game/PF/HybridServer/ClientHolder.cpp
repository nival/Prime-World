#include "stdafx.h"

#include "ClientHolder.h"
#include "System/InlineProfiler.h"
#include "RPeered.auto.h"
#include "HybridServerNaming.h"
#include "HybridServerDumpersIfaces.h"
#include "HybridServerMulticast.h"

#include "System/nalgoritm.h"

namespace
{
  static inline int GetLastConfirmationStep(const int step, const int confirmFrequency)
  {
    if (confirmFrequency <= 0)
      return step;

    if (step < confirmFrequency)
      return 0;

    if (int r = step % confirmFrequency)
      return step - r;
    else
      return step - confirmFrequency;
  }

  static inline int GetNextConfirmationStep(const int step, const int confirmFrequency)
  {
    if (confirmFrequency <= 0)
      return step;

    if (step < confirmFrequency)
      return confirmFrequency;

    return step - step % confirmFrequency + confirmFrequency;
  }
}

namespace Peered
{

Clients::~Clients() 
{
  for (ClientContainer::iterator it = clients.begin();it != clients.end();++it)
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace("GameServer: Client %s (sid=%016x cid=%d cidx=%d)", GetClientStatus(Peered::DisconnectedByServer), data.serverId, it->second->GetClientId(), it->second->clientIndex);
    delete it->second;
  }
  for (ClientContainer::iterator it = passiveClients.begin();it != passiveClients.end();++it)
  {
    delete it->second;
  }
  
  DeleteSnapshots(snapshots);
  DeleteSnapshots(snapshotCache);

  if (data.sessionSettings.multicastStepsEnabled)
    mcChannelWrapper->Close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientHolder* Clients::WaitClient( uint clientId, bool isSpectator, const wstring& nickname )
{
  ClientHolder* newClient = new ClientHolder;
  newClient->Set( clientId, 0, _GenerateIndex(), isSpectator );
  newClient->nickname = nickname;
  passiveClients[clientId] = newClient;
  return newClient;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clients::GetReadyCount() const
{
  int result = 0;
  for (ClientContainer::iterator it = clients.begin();it != clients.end();++it)
  {
    if (it->second->GetStatus() == Peered::Ready)
    {
      result++;
    }
  }
  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clients::GetLoadingCount() const
{
  int result = 0;

  ClientContainer::const_iterator it = clients.begin();
  ClientContainer::const_iterator it_end = clients.end();
  for (; it != it_end; ++it)
  {
    if (it->second->GetStatus() == Peered::Connecting)
    {
      result++;
    }
  }
  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::CheckStatuses(bool calculateGap, nstl::vector<int>& clientIndices, nstl::vector<Peered::BriefClientInfo>& clientInfos, Peered::IWorld* world)
{
  int currentStep = GetPendingStep();
  stepGapInfo.reserve(clients.size());
  clientIndices.reserve(clients.size());
  clientInfos.reserve(clients.size());
  stepGapInfo.clear();
  clientIndices.clear();
  clientInfos.clear();

  const bool stillLoading = (GetStatus() < Started);

  for (ClientContainer::iterator it = clients.begin();it != clients.end();)
  {
    ClientHolder* clientHolder = it->second;
    const Peered::BriefClientInfo& clientInfo = clientHolder->GetInfo();
    StrongMT<Peered::IGameClient> lclient = clientHolder->GetClient();
    Peered::Status status = Peered::Active;
    Peered::EDisconnectReason::Enum reason = Peered::EDisconnectReason::None;
    if (!lclient)
    {
      status = Peered::DisconnectedByClient;
    }
    else if (clientHolder->GetStatus() == Peered::Connecting)
    {
      Peered::RejoinerData * rejoinerData = GetRejoinerData(clientHolder->clientIndex);
      if (rejoinerData && rejoinerData->IsWorldRequested())
      {
        if (data.sessionSettings.snapshotApplyTimeout > 0 && rejoinerData->IsWorldApplied()) 
        {
          clientHolder->AddSnapshotApplyTimeoutStep();
          if (clientHolder->GetSnapshotApplyTimeoutStep() >= data.sessionSettings.snapshotApplyTimeout)
          {
            localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
              "GameServer: CheckStatuses: Disconnect due to world apply timeout (sid=%016x cid=%d cidx=%d applySteps=%d)",
                data.serverId, clientHolder->GetClientId(), clientHolder->clientIndex, clientHolder->GetSnapshotApplyTimeoutStep());
            reason = Peered::EDisconnectReason::ClientPerfomance;
            status = Peered::DisconnectedByServer;
          }
        }
      }
      else if (data.sessionSettings.loadTimeoutSteps > 0)
      {
        clientHolder->AddLoadTimeoutStep();
        if (clientHolder->GetLoadTimeoutStep() >= data.sessionSettings.loadTimeoutSteps)
        {
          localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
            "GameServer: CheckStatuses: Disconnect due to loading timeout (sid=%016x cid=%d cidx=%d loadSteps=%d)",
              data.serverId, clientHolder->GetClientId(), clientHolder->clientIndex, clientHolder->GetLoadTimeoutStep());
          reason = Peered::EDisconnectReason::ClientPerfomance;
          status = Peered::DisconnectedByServer;
        }
      }
    }
    else
    {
      Peered::GapInfo info = { clientInfo.clientId, calculateGap?clientHolder->GetGap():0};
      clientHolder->UpdateGapOdd();
      if (data.sessionSettings.disconnectionGap == 0 
          || info.confirmedStepsGap <= data.sessionSettings.disconnectionGap + clientHolder->GetGapOdd())
      {
        if (!clientHolder->disconnectGapWaterlineUp)
        {
          if (data.sessionSettings.disconnectionWaterline && info.confirmedStepsGap >= data.sessionSettings.disconnectionWaterline)
          {
            clientHolder->disconnectGapWaterlineUp = true;
            localLog(logStream, NLogg::LEVEL_DEBUG).Trace("Disconnection waterline UP(sid=%016x cid=%d cidx=%d step=%d confirmed=%d waterline=%d)", 
              data.serverId, clientInfo.clientId, clientHolder->clientIndex, currentStep, info.confirmedStepsGap, data.sessionSettings.disconnectionWaterline);
          }
        }
        else
        {
          if (info.confirmedStepsGap < data.sessionSettings.disconnectionWaterline)
          {
            clientHolder->disconnectGapWaterlineUp = false;
            localLog(logStream, NLogg::LEVEL_DEBUG).Trace("Disconnection waterline DOWN(sid=%016x cid=%d cidx=%d step=%d confirmed=%d waterline=%d)", 
              data.serverId, clientInfo.clientId, clientHolder->clientIndex, currentStep, info.confirmedStepsGap, data.sessionSettings.disconnectionWaterline);
          }
        }
        stepGapInfo.push_back(info);

        if (data.sessionSettings.afkStepsCount > 0 && !clientHolder->IsSpectator())
        {
          bool sendStatus = false;
          if (currentStep-clientHolder->lastReceivedCommandStep >= data.sessionSettings.afkStepsCount)
          {
            if (clientHolder->GetStatus() == Peered::Active)
            {
              clientHolder->SetStatus(Peered::Away);
              sendStatus = true;
              clientHolder->SetLastAfkStep(currentStep);
            }
          } 
          else
          {
            if (clientHolder->GetStatus() == Peered::Away)
            {
              clientHolder->SetStatus(Peered::Active);
              sendStatus = true;
              clientHolder->UpdateTotalAfkSteps(currentStep);
            }
          }
          if (sendStatus)
          {
            clientInfos.push_back(clientInfo);
            clientIndices.push_back(it->first);
          }
        }

        if (data.sessionSettings.afkStepsDisconnectCount > 0 && !clientHolder->IsSpectator() && !stillLoading)
        {
          int afkSteps = currentStep - clientHolder->lastReceivedCommandStep;
          if (afkSteps >= data.sessionSettings.afkStepsDisconnectCount)
          {
            localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
              "GameServer: CheckStatuses: Disconnect due to afk time limit (sid=%016x cid=%d cidx=%d afkSteps=%d)",
                data.serverId, clientHolder->GetClientId(), clientHolder->clientIndex, afkSteps);
            reason = Peered::EDisconnectReason::ClientAway;
            status = Peered::DisconnectedByServer;
          }
        }
      }
      else
      {
        localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
          "GameServer: CheckStatuses: Disconnect due to unconfirmed steps limit (sid=%016x cid=%d cidx=%d unconfirmedSteps=%d gapOdd=%d limit=%d)",
            data.serverId, clientHolder->GetClientId(), clientHolder->clientIndex, info.confirmedStepsGap, clientHolder->GetGapOdd(), data.sessionSettings.disconnectionGap);
        reason = Peered::EDisconnectReason::ClientPerfomance;
        status = Peered::DisconnectedByServer;
      }
    }

    if (IsDisconnectedStatus(status))
    {
      it = _RemoveClient(it, world, clientInfos, clientIndices, status, reason);
    } 
    else
    {
      ++it;
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientContainer::iterator Clients::_RemoveClient( ClientContainer::iterator it, Peered::IWorld* world, nstl::vector<Peered::BriefClientInfo> &clientInfos, nstl::vector<int> &clientIndices, Peered::Status status, Peered::EDisconnectReason::Enum reason )
{
  ClientHolder* client = it->second;
  ClientContainer::iterator result = _DisconnectClient(it, status, reason);
  clientInfos.push_back(client->GetInfo());
  clientIndices.push_back(client->clientIndex);
  return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientContainer::iterator Clients::_DisconnectClient( ClientContainer::iterator it, Peered::Status status, Peered::EDisconnectReason::Enum reason /*= Peered::EDisconnectReason::None*/ )
{
  //Debugging NUM_TASK
  DebugTrace( "Clients::_DisconnectClient. this=%08x", (void*)this );

  ClientHolder* client = it->second;
  uint clientId = client->GetClientId();
  if (reason != Peered::EDisconnectReason::None)
  {
    client->OnDisconnect(reason);
    if (!data.sessionSettings.disconnectAckTimeoutSteps)
    {
      client->Disconnect();
    }
  }
  else
  {
    client->Disconnect();
  }
  client->SetStatus(status);
  int step = GetPendingStep();
  client->SetDisconnectionStep(step);
  LogClientStatus(client->GetInfo(), reason);
  passiveClients[client->GetClientId()] = client;
  client->UpdateTotalAfkSteps(step);
  if (handler)
  {
    handler->OnRemoveClient(client->clientIndex, clientId, client->GetClient(), 0); 
  }

  if (data.sessionSettings.multicastStepsEnabled)
    mcChannelWrapper->RemoveClient(clientId);

  return clients.erase(it);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::RemoveWaitClient( uint clientId )
{
  ClientContainer::iterator it = _FindWaitClient(clientId);
  if (it != passiveClients.end())
  {
    delete it->second;
    passiveClients.erase(it);
    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::DisconnectClient(uint clientIndex, Peered::Status status /*= Peered::DisconnectedByServer*/, Peered::EDisconnectReason::Enum reason /*= Peered::EDisconnectReason::None*/)
{
  ClientContainer::iterator it = clients.find(clientIndex);
  if (it != clients.end())
  {
    ClientHolder* client = it->second;
    _DisconnectClient(it, status, reason);
    OnChangeClientStatus(client->GetInfo());
    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::DisconnectClients(const nstl::vector<int>& clientIndexes, Peered::Status status /*= Peered::DisconnectedByServer*/, Peered::EDisconnectReason::Enum reason /*= Peered::EDisconnectReason::None*/)
{
  bool retVal = true;
  for (int i = 0; i < clientIndexes.size(); ++i)
  {
    if (!DisconnectClient(clientIndexes[i], status, reason))
    {
      retVal = false;
    }
  }
  return retVal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientContainer::iterator Clients::_FindWaitClient(uint clientId)
{
  return passiveClients.find(clientId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::IsClientDisconnected(int clientIndex)
{
  ClientHolder* client = GetDisconnectedClient(clientIndex);
  return client;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientHolder* Clients::GetDisconnectedClient(int clientIndex)
{
  for (ClientContainer::iterator it = passiveClients.begin();it!=passiveClients.end();++it)
  {
    if (it->second->clientIndex == clientIndex)
    {
      return it->second;
    }
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientHolder& Clients::AddClient(uint clientId, Login::ClientVersion _clientVersion, IGameClient* _client)
{
  ClientHolder* result = 0;
  ClientContainer::iterator it = _FindWaitClient(clientId);
  if (it != passiveClients.end())
  {
    result = it->second;
    int step = NCore::INVALID_STEP;

    Peered::BriefClientInfo info = result->GetInfo();
    bool sendToClients = false;
    if (info.status != Peered::Connecting)
    {
      // Notify clients about status change only if it is reconnect
      sendToClients = true;
    }
    step = GetPendingStep()-1;
    info.status = Peered::Connecting;
    info.step = step;
    OnChangeClientStatus(info, true, sendToClients);

    passiveClients.erase(it);
    result->Set(_client, step); // Here the status will be set to Peered::Connecting
  } 
  else 
  {
    result = new ClientHolder;
    result->Set(clientId, _client, _GenerateIndex(), false);
  } 
  if (handler)
  {
    handler->OnAddClient(result->clientIndex, _client, 0);
  }
  clients[result->clientIndex] = result;
  LogClientStatus(result->GetInfo());

  if (clientVersion.isEmpty())
  {
    if (!_clientVersion.isEmpty())
    {
      clientVersion = _clientVersion;
    }
    else
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: AddClient: Client version is empty (sid=%016x cid=%d cidx=%d)",
          data.serverId, clientId, result->clientIndex);
    }
  }
  else if (clientVersion != _clientVersion)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: AddClient: Client versions differ (sid=%016x cid=%d cidx=%d)",
        data.serverId, clientId, result->clientIndex);
  }

  return *result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientHolder * Clients::AddClientFast(uint clientId, int clientIndex, IGameClient* _client, int fromStep)
{
  bool needRestore = false;
  int lastStep = fromStep - 1;  // Last step client have processed

  // First - try to find active client (he can be there if we didn't detected his disconnect yet)
  ClientHolder* client = GetClient(clientIndex);
  if (!client)
  {
    // If not in active list - get from passive
    client = GetPassiveClient(clientId);
    if (!client)
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: AddClientFast: Client not found (sid=%016x cid=%d cidx=%d)", data.serverId, clientId, clientIndex);
      _client->OnDisconnect(int(EDisconnectReason::ServerError));
      LogReconnectResult(clientId, EReconnectType::Fast, EReconnectResult::ClientNotFound);
      return 0;
    }
    needRestore = true;
  }

  if (client->GetClientId() != clientId || client->clientIndex != clientIndex)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: AddClientFast: Client's Id and Index are not correspond (sid=%016x cid=%d cidx=%d) ignored", 
        data.serverId, clientId, clientIndex);
    _client->OnDisconnect(int(EDisconnectReason::ServerError));
    LogReconnectResult(clientId, EReconnectType::Fast, EReconnectResult::IdAndIndexMissmatch);
    return 0;
  }

  int pendingStep = GetPendingStep();
  int lastSentStep = client->GetLastSentStep();
  if (fromStep < lastReservedStep || fromStep > pendingStep || lastStep > lastSentStep)
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: AddClientFast: Wrong step number (sid=%016x cid=%d cidx=%d fromStep=%d lastReservedStep=%d pendingStep=%d lastSentStep=%d), ignored", 
        data.serverId, clientId, clientIndex, fromStep, lastReservedStep, pendingStep, lastSentStep);
    _client->OnDisconnect(int(EDisconnectReason::ServerError));
    LogReconnectResult(clientId, EReconnectType::Fast, EReconnectResult::WrongStep);
    return 0;
  }

  const int nextProtectionMagicConfirmationStep =
    GetNextConfirmationStep(fromStep, data.sessionSettings.pmConfirmFrequency) + data.sessionSettings.pmConfirmFrequency;

  // Remove client from snapshots up to fromStep - this will check possibly left unconfirmed snapshot.
  // Note: crc for such snapshot won't be verified for fast-reconnecting client.
  RemoveClientFromSnapshots(clientIndex, fromStep);
  RemoveClientFromProtectionRecords(clientIndex, nextProtectionMagicConfirmationStep);

  client->Set(_client);
  client->SetStatus(Peered::Active);
  client->Rewind(lastStep, data.sessionSettings.confirmFrequency);
  client->nextStep = fromStep;

  const int clientLastConfirmedStep = GetLastConfirmationStep(lastStep, data.sessionSettings.confirmFrequency);
  const int clientLastConfirmedProtectionStep = GetLastConfirmationStep(lastStep, data.sessionSettings.pmConfirmFrequency);

  lastConfirmedStep = min(lastConfirmedStep, clientLastConfirmedStep);
  lastConfirmedProtectionStep = min(lastConfirmedProtectionStep, clientLastConfirmedProtectionStep);

  if (needRestore)
  {
    passiveClients.erase(clientId);
    clients[clientIndex] = client;

    AddClientToSnapshots(clientIndex, fromStep);
    AddClientToProtectionRecords(clientIndex, nextProtectionMagicConfirmationStep);

    Peered::BriefClientInfo info = client->GetInfo();
    info.status = Peered::Connecting;
    OnChangeClientStatus(info);
    LogClientStatus(info);
    info.status = Peered::Active;
    OnChangeClientStatus(info);

    if (handler)
      handler->OnAddClient(client->clientIndex, _client, 0);
  }

  if (client->nextStep < pendingStep)
  {
    UpdateClientCommands(*client, true, pendingStep-1);
  }

  client->SetGapOdd(client->GetGap());

  return client;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::AddClientToMcChannel(ClientHolder & client)
{
  client.SetStepSendType(UNICAST);
  return mcChannelWrapper->AddClient(client.GetClient(), client.GetClientId(), client.clientIndex);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::AddSpectator( uint clientId, const wstring& nickname )
{
  ClientList::iterator itSpectator = spectators.find(clientId);
  if (itSpectator != spectators.end())
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: AddSpectator: Reconnect spectator (sid=%016x cid=%d spectCnt=%d spectLimit=%d)",
        data.serverId, clientId, spectators.size(), data.sessionSettings.spectatorsLimit);
  }
  else if (spectators.size() < data.sessionSettings.spectatorsLimit)
  {
    ClientHolder* newSpectator = WaitClient( clientId, true, nickname );
    spectators.insert( clientId );

    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: AddSpectator: Added spectator (sid=%016x cid=%d cidx=%d spectCnt=%d spectLimit=%d)",
        data.serverId, clientId, newSpectator->clientIndex, spectators.size(), data.sessionSettings.spectatorsLimit);
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: AddSpectator: Attempt to add spectator above limit (sid=%016x cid=%d spectCnt=%d spectLimit=%d), ignored",
        data.serverId, clientId, spectators.size(), data.sessionSettings.spectatorsLimit);
    return;
  }

  OnRejoinClient(clientId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::AddCommand(ClientHolder & client, const rpc::MemoryBlock& info, bool isPlayerCommand)
{
  commands.Append(info.memory, info.size);
  if (isPlayerCommand)
    client.MarkCommandReceived(commands.GetPendingStep());

  if (status == Started || status == Blocked)
    trafficStatistics->AddCmdTraffic(1);
  trafficStatistics->AddInTrafficSize(info.size);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* Clients::GetStatus(Clients::Status status)
{
  switch (status)
  {
  case WaitingForClients : return "WaitingForClients";
  case Loading: return "Loading";
  case Started: return "Started";
  case Blocked: return "Blocked";
  case Finished: return "Finished";
  case WaitingRoll: return "WaitingRoll";
  case Finishing: return "Finishing";
  case Terminated: return "Terminated";
  }
  return "<Unknown>";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::CheckSnapshots(int clientIndex)
{
  bool result = false; 
  for (int j=0;j<snapshots.size();++j)
  {
    snapshots[j]->RemoveClient(clientIndex);
    snapshots[j]->UpdateStatus();
    if (snapshots[j]->CheckIfComplete())
    {
      result = true;
    }
  }
  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::CheckSnapshots(nstl::vector<int>& clientIndexes)
{
  bool result = false; 

  for (int i = 0; i < clientIndexes.size(); ++i)
  {
    if (CheckSnapshots(clientIndexes[i]))
    {
      result = true;
    }
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::AddClientToSnapshots(int clientIndex, int fromStep, bool isReserved /*= false*/)
{
  for (int i=0; i < snapshots.size(); ++i)
  {
    if (snapshots[i]->GetStep() >= fromStep)
    {
      snapshots[i]->AddClient(clientIndex, isReserved);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::RemoveClientFromSnapshots(int clientIndex, int toStep, bool unreserve /*= false*/)
{
  bool complete = false;
  for (int i=0; i < snapshots.size(); ++i)
  {
    if (snapshots[i]->GetStep() < toStep)
    {
      snapshots[i]->RemoveClient(clientIndex);
      if (snapshots[i]->CheckIfComplete())
      {
        complete = true;
      }
    }
    else if(unreserve)
    {
      snapshots[i]->UnreserveClient(clientIndex);
    }
  }
  if (complete)
  {
    UpdateSnapshots();
  }
  if (GetStatus() == Clients::Blocked)
  {
    CheckAsyncSnapshots();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* Clients::GetClientStatus(Peered::Status status)
{
  switch (status)
  {
  case Peered::Connecting : return "connecting";
  case Peered::Ready: return "ready";
  case Peered::Away: return "away";
  case Peered::Active : return "active";
  case Peered::DisconnectedByServer  : return "disconnected by server";
  case Peered::DisconnectedByClient  : return "disconnected by client";
  case Peered::ConnectionTimedOut  : return "connection timed out";
  case Peered::DisconnectedByCheatAttempt: return "disconnected by cheat attempt";
  case Peered::DisconnectedByClientIntentionally  : return "disconnected by client intentionally";
  case Peered::ConnectionTimedOutOnReconnect  : return "connection timed out on reconnect";
  case Peered::DisconnectedByAsync  : return "disconnected by async";
  case Peered::RefusedToReconnect  : return "refused to reconnect";
  }
  return "<Unknown>";
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::DisconnectRejoiningClient(int clientIndex, Peered::EDisconnectReason::Enum reason, bool checkSnapshots /*= true*/)
{
  if (RemoveRejoinClient(clientIndex)) // disconnect only if it was really in the rejoiners list
  {
    ClientContainer::iterator it = clients.find(clientIndex);
    if (it != clients.end() && it->second)
    {
      localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
        "GameServer: Disconnecting rejoining client (sid=%016x cid=%d cidx=%d)", 
          data.serverId, it->second->GetClientId(), clientIndex);

      Peered::BriefClientInfo info = it->second->GetInfo();
      _DisconnectClient(it, Peered::DisconnectedByServer, reason);
      info.status = Peered::DisconnectedByServer;
      info.step = GetPendingStep()-1;
      OnChangeClientStatus(info);
    }

    if (checkSnapshots)
    {
      if (CheckSnapshots(clientIndex))
      {
        UpdateSnapshots();
      }
      if (GetStatus() == Clients::Blocked)
      {
        CheckAsyncSnapshots();
      }

      RemoveClientFromProtectionRecords(clientIndex);
    }

    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::DisconnectRejoiningClients(Peered::EDisconnectReason::Enum reason, bool checkSnapshots /*= true*/)
{
  if (GetRejoinCount() == 0)
    return;

  for (RejoinersData::iterator it = rejoinClients.begin(); it != rejoinClients.end();)
  {
    int clientIndex = it->first;
    LogReconnectResult(it->second.GetClientId(), EReconnectType::Normal,
      (reason == Peered::EDisconnectReason::GameFinished)?(Peered::EReconnectResult::GameFinished):(Peered::EReconnectResult::Failure));
    ++it;
    DisconnectRejoiningClient(clientIndex, reason, checkSnapshots);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::LogReconnectResult(int clientId, EReconnectType::Enum reconnectType, EReconnectResult::Enum reconnectResult)
{
  if (statisticsWrapper)
  {
    StatisticService::RPC::ReconnectAttemptInfo info;

    info.sessionId = data.serverId;
    info.userId = clientId;
    info.currentStep = GetPendingStep();
    info.reconnectType = reconnectType;
    info.resultCode = reconnectResult;

    statisticsWrapper->LogReconnect(info);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::LogClientStatus(const Peered::BriefClientInfo & info,
                              Peered::EDisconnectReason::Enum reason /*= Peered::EDisconnectReason::None*/)
{
  if (statisticsWrapper)
  {
    StatisticService::RPC::UserStatusEvent evt;

    evt.ctx = StatisticService::RPC::SessionUserContext( data.serverId, info.clientId );
    evt.status = info.status;
    evt.step = GetPendingStep();
    evt.reason = reason;

    statisticsWrapper->LogClientStatus(evt);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::UpdateCommands(bool stepped)
{
  NI_PROFILE_BLOCK( "Sending step commands" );
  for (ClientContainer::iterator it = clients.begin();it != clients.end();++it)
  {
    UpdateCommands(stepped, *(it->second));
  }
  trafficStatistics->FinishOutTrafficFrame();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::UpdateCommands(bool stepped, ClientHolder & holder)
{
  if (!holder.IsAsynced()
    && (holder.GetInfo().status != Connecting || IsWorldSentToRejoiner(holder.clientIndex) || GetStatus() == Clients::Loading))
  {
    Peered::IGameClient* lclient = holder.GetClient();
    if (lclient)
    {
      int lastStepToSend = holder.nextStep;
      if (status == Started && data.sessionSettings.trustGap > 0 && data.sessionSettings.confirmFrequency > 0)
      {
        if (holder.GetLastVerifiedStep() != NCore::INVALID_STEP)
        {
          lastStepToSend = min(commands.GetPendingStep()-1, 
                               holder.GetLastVerifiedStep()+data.sessionSettings.trustGap*data.sessionSettings.confirmFrequency);
        } else
        {
          lastStepToSend = commands.GetPendingStep()-1;
        }
      }
      UpdateClientCommands(holder, stepped, lastStepToSend);

      if ( holder.delayedCommandsWarningOn )
      {
        if ( data.sessionSettings.delayedCommandsWarningGap 
              && commands.GetPendingStep() - holder.nextStep < data.sessionSettings.delayedCommandsWarningGap )
        {
          holder.delayedCommandsWarningOn = false;
        }
      }
      else
      {
        int delayedCommandsGap = commands.GetPendingStep() - holder.nextStep;
        if ( data.sessionSettings.delayedCommandsWarningGap 
              && delayedCommandsGap >= data.sessionSettings.delayedCommandsWarningGap )
        {
          localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
            "GameServer: UpdateCommands: Delayed commands detected (sid=%016x cid=%d cidx=%d step=%d delayedCommandsGap=%d)", 
              data.serverId, holder.GetClientId(), holder.clientIndex, commands.GetPendingStep(), delayedCommandsGap);
          holder.delayedCommandsWarningOn = true;
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::SendStep(bool stepped)
{
  if (!data.sessionSettings.multicastStepsEnabled)
  {
    UpdateCommands(stepped);
    return;
  }

  NI_PROFILE_BLOCK( "Sending step MC" );

  int step = commands.GetPendingStep()-1;

  if (status == Started)
    CheckSnapshotAllocated(step);

  if (stepped)
  {
    bool result = false;
    if (bool result = mcChannelWrapper->GetClientsCount() > 0)
    {
      for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it)
      {
        ClientHolder & client = *(it->second);
        if (client.GetStepSendType() == UNICAST 
            && mcChannelWrapper->FindClient(client.GetClientId()))
        {
          localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace(
            "GameServer: SendStep: Client switched to multicast (sid=%016x cid=%d cidx=%d step=%d)", 
              data.serverId, client.GetClientId(), client.clientIndex, step);
          client.SetStepSendType(MULTICAST);
        }
      }

      // TODO: De-crap this code in NUM_TASK
      MemoryStream stepData(data.sessionSettings.commandsPerStepMaxSize);
      stepData.Write(&step, sizeof(int));
      stepData.Write(&lastReservedStep, sizeof(int));
      commands.CopyStep(step, stepCommands);
      int size = stepCommands.size();
      stepData.Write(&size, sizeof(int));
      for (int i = 0; i < stepCommands.size(); ++i)
      {
        stepData.Write(&stepCommands[i].size, sizeof(uint));
        stepData.Write(stepCommands[i].memory, stepCommands[i].size);
      }
      statuses.CopyStep<BriefClientInfo>(step, stepStatuses);
      size = stepStatuses.size();
      stepData.Write(&size, sizeof(int));
      for (int i = 0; i < stepStatuses.size(); ++i)
      {
        stepData.Write(&stepStatuses[i], sizeof(BriefClientInfo));
      }
      size = stepGapInfo.size();
      stepData.Write(&size, sizeof(int));
      for (int i = 0; i < stepGapInfo.size(); ++i)
      {
        stepData.Write(&stepGapInfo[i], sizeof(GapInfo));
      }
      rpc::MemoryBlock stepDataBlock;
      stepDataBlock.memory = stepData.GetBuffer();
      stepDataBlock.size = stepData.GetPosition();

      trafficStatistics->AddOutTrafficSize(stepDataBlock.size);

      result = mcChannelWrapper->SendData((byte*)stepDataBlock.memory, stepDataBlock.size);
    }

    for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it)
    {
      ClientHolder & client = *(it->second);
      if (client.GetStepSendType() == MULTICAST)
      {
        if (!result && !mcChannelWrapper->FindClient(client.GetClientId()))
        {
          localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace(
            "GameServer: SendStep: Client switched to unicast (sid=%016x cid=%d cidx=%d step=%d)", 
              data.serverId, client.GetClientId(), client.clientIndex, step);
          client.SetStepSendType(UNICAST);
          UpdateCommands(stepped, client);
        }
        else
        {
          client.nextStep = step + 1;
        }
      }
      else
      {
        UpdateCommands(stepped, client);
      }
    }
  }

  trafficStatistics->FinishOutTrafficFrame();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::UpdateCommandsBlocked()
{
  for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it)
  {
    ClientHolder& holder = *(it->second);
    StepBlocked(holder);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::IsAllClientsFinished() const
{
  for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it)
  {
    ClientHolder* client = it->second;

    if (client->GetStatus() != Peered::Connecting && client->finishStep == NCore::INVALID_STEP 
        && !client->IsAsynced() && !client->IsSpectator())
    {
      return false;
    }
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::LogFinishResults(const ResultsData & results, int number, int count) const
{
  // This is kind of debug log, which should be removed or commented after NUM_TASK is fixed

  NI_ASSERT( results.results, "" );

  StatisticService::RPC::SessionClientResults & info = *results.results;

  localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
    "GameServer: Finish results %d of %d (sid=%016x faction=%d step=%d count=%d)", 
      number, count, data.serverId, info.sideWon, results.step, results.count);

  for (vector<StatisticService::RPC::SessionClientResultsPlayer>::iterator it = info.players.begin(); 
        it != info.players.end(); ++it)
  {
    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer:      sid=%016x userid=%d finalLevel=%d score=%d specialPoints=%d kills=%d deaths=%d assists=%d", 
        data.serverId, (*it).userid, (*it).scoring.finalLevel, (*it).scoring.score, (*it).scoring.specialPoints, (*it).scoring.kills, (*it).scoring.deaths, (*it).scoring.assists);
    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer:      sid=%016x enemyCreepsKilled=%d neutralCreepsKilled=%d", 
        data.serverId, (*it).scoring.enemyCreepsKilled, (*it).scoring.neutralCreepsKilled);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const StatisticService::RPC::SessionClientResults * Clients::GetFinishResults()
{
  nstl::list<ResultsData> results;

  int resultsCount = 0;
  int noResultsCount[2] = { 0, 0 };
  ClientContainer * clientContainers[2] = { &clients, &passiveClients };
  ResultsData * bestResults = 0;

  for (int i = 0; i < 2; ++i)
  {
    for (ClientContainer::iterator it = clientContainers[i]->begin(); it != clientContainers[i]->end(); ++it)
    {
      ClientHolder* client = it->second;

      if (client->GetStatus() != Peered::Connecting && !client->IsSpectator())
      {
        if (client->finishStep != NCore::INVALID_STEP)
        {
          ResultsData clientResults(client->finishResults, client->finishStep, 1);
          nstl::list<ResultsData>::iterator it = nstl::find(results.begin(), results.end(), clientResults);
          if (it == results.end())
          {
            results.push_back(clientResults);
            it = results.end();
            --it;
          }
          else
          {
            ++(*it).count;
          }
          if (!bestResults || bestResults->count < (*it).count)
          {
            bestResults = &(*it);
          }
          ++resultsCount;
        }
        else
        {
          ++noResultsCount[i];
        }
      }
    }
  }

  if (!bestResults)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: GetFinishResults: Unexpected error - no results (sid=%016x)", data.serverId);
    return 0;
  }

  if (results.size() > 1)
  {
    // Log async results for debug purposes
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace("GameServer: Finish results differ (sid=%016x)", data.serverId);
    nstl::list<ResultsData>::iterator it = results.begin();
    for (int number = 1, count = results.size(); it != results.end(); ++it, ++number)
    {
      LogFinishResults(*it, number, count);
    }
  }

  if (bestResults->count == noResultsCount[0])
  {
    // Test for special case of 50/50
    for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it)
    {
      ClientHolder* client = it->second;

      if (client->finishStep == NCore::INVALID_STEP)
      {
        // If step confirmation is on, we can check if the client is lagging.If client has confirmed the finish 
        // step or finish step falls on the next confirmation interval - the client is considered as not lagging.
        // +1 needed, because client won't confirm step if there is no next one, so the last step is never reported.
        if ( data.sessionSettings.confirmFrequency 
              && it->second->GetLastSentVerifiedStep() + 1 + data.sessionSettings.confirmFrequency > bestResults->step )
        {
          localLog(logStream, NLogg::LEVEL_WARNING).Trace(
            "GameServer: GetFinishResults: Too many clients timed out on game finish (sid=%016x count=%d)", 
              data.serverId, noResultsCount[0]);
          return 0;
        }
      }
    }
  }
  else if (bestResults->count < ((resultsCount + noResultsCount[0])>>1) + 1)
  {
    // We have no consistent results from most clients
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: GetFinishResults: Inconsistent game finish information (sid=%016x)", data.serverId);
    return 0;
  }

  if (noResultsCount[0] > 0)
  {
    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "GameServer: GetFinishResults: Some clients timed out on game finish (sid=%016x count=%d)", 
        data.serverId, noResultsCount[0]);
  }

  return bestResults->results;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint Clients::FillClientStatistics(nstl::vector<Peered::SClientStatistics> & clientsStatistics)
{
  float stepsPerSecond = 1000.0f / data.sessionSettings.simulationStep;

  for (ClientContainer::iterator itClient = clients.begin(); 
        itClient != clients.end(); ++itClient)
  {
    ClientHolder * client = itClient->second;
    if (!client->IsSpectator())
    {
      Peered::SClientStatistics & cs = clientsStatistics.push_back();

      cs.clientId = client->GetClientId();
      cs.clientState = Peered::EGameFinishClientState::FinishedGame;

      client->UpdateTotalAfkSteps(GetPendingStep());
      cs.totalAfkSeconds= client->GetTotalAfkSteps()/stepsPerSecond;
    }
  }
  
  for (ClientContainer::iterator itPassiveClient = passiveClients.begin(); 
        itPassiveClient != passiveClients.end(); ++itPassiveClient)
  {
    ClientHolder * client = itPassiveClient->second;
    if (!client->IsSpectator())
    {
      Peered::SClientStatistics & cs = clientsStatistics.push_back();

      cs.clientId = client->GetClientId();

      if (client->GetStatus() == Peered::ConnectionTimedOut)
      {
        cs.clientState = Peered::EGameFinishClientState::NotConnected;
      }
      else if (client->finishStep != NCore::INVALID_STEP)
      {
        cs.clientState = Peered::EGameFinishClientState::FinishedGame;
      }
      else
      {
        cs.clientState = Peered::EGameFinishClientState::Disconnected;
      }

      client->UpdateTotalAfkSteps(GetPendingStep());
      cs.totalAfkSeconds = client->GetTotalAfkSteps()/stepsPerSecond;
    }
  }

  return GetPendingStep()/stepsPerSecond;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::UpdateClientCommands( ClientHolder& holder, bool stepped, int lastStep )
{
  if ((data.sessionSettings.confirmFrequency == 0) || holder.IsReadyToGo(data.sessionSettings.trustGap * data.sessionSettings.confirmFrequency))
  {
    for (int j=holder.nextStep;j<=lastStep;++j)
    {
      if (status == Started)
      {
        CheckSnapshotAllocated(j);
      }
      if (stepped)
      {
        const SnapshotInfo& info = holder.GetSnapshotInfo();
        int changesApplied = (info.step == j)?info.changesAppliedBeforeBuilt:0;
        SendCommands(j, holder, changesApplied);
      }
    }
    if (stepped)
    {
      holder.nextStep = lastStep+1;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fills game results with default info:
// - victoriousFaction is None;
// - user statistics contains only IDs and "leaver" flag, while the rest is by default 0.
void Clients::FillDefaultGameResults(StatisticService::RPC::SessionClientResults & finishInfo)
{
  finishInfo = StatisticService::RPC::SessionClientResults();
  finishInfo.sideWon = lobby::ETeam::None;

  int totalCount = GetTotalCount();
  if (totalCount > 0)
  {
    finishInfo.players.resize(totalCount);
    int dataIndex = 0;
    for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it, ++dataIndex)
    {
      finishInfo.players[dataIndex].userid = it->second->GetInfo().clientId;
    }
    for (ClientContainer::iterator it = passiveClients.begin(); it != passiveClients.end(); ++it, ++dataIndex)
    {
      const Peered::BriefClientInfo clientInfo = it->second->GetInfo();
      finishInfo.players[dataIndex].userid = clientInfo.clientId;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::OnRejoinClient(uint clientId)
{
  ClientContainer::iterator it = _FindWaitClient(clientId);
  if (it != passiveClients.end())
  {
    int step = GetPendingStep();

    if (it->second->GetStatus() != Peered::DisconnectedByCheatAttempt)
    {
      localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace(
        "GameServer: OnRejoinClient: Reconnect announced (sid=%016x cid=%d cidx=%d step=%d)", 
          data.serverId, it->second->GetClientId(), it->second->clientIndex, step);

      it->second->SetReconnectAnnouncementStep(step);
      return true;
    }
    else
    {
      localLog( logStream, NLogg::LEVEL_MESSAGE ).Trace(
        "GameServer: OnRejoinClient: Client disconnected by cheat attempt (sid=%016x cid=%d cidx=%d step=%d), ignored",
          data.serverId, it->second->GetClientId(), it->second->clientIndex, step);
      // Notify lobby that cheater is kicked again
      OnChangeClientStatus(it->second->GetInfo(), true, false);
    }
  }
  else
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: OnRejoinClient: Client not found (sid=%016x cid=%d)", 
        data.serverId, clientId);
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::OnGameLeave(int clientIndex, Peered::IWorld* world)
{
  ClientContainer::iterator it = clients.find(clientIndex);
  if (it != clients.end())
  {
    const bool isSpectatorOrGameFinished =
      it->second->IsSpectator() ||
      it->second->IsGameFinished();
    const Peered::Status status = isSpectatorOrGameFinished
      ? Peered::DisconnectedByClient
      : Peered::DisconnectedByClientIntentionally;

    _RemoveClient(it, world, statusChanges, statusChangesIndices, status, Peered::EDisconnectReason::None);

    // Inside UpdateStatusChanges() function we will also log the status change, so no need to log here
    UpdateStatusChanges();
  }
  else
  {
    if (!IsClientDisconnected(clientIndex))
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: OnGameLeave: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
      return false;
    }
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::SendCrcData(int clientIndex, int step, const rpc::MemoryBlock& crcData)
{
  ClientContainer::iterator it = clients.find(clientIndex);
  if (it == clients.end())
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: SendCrcData: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
    return;
  }

  if (step != asyncData.step)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: SendCrcData: Crc data received for a wrong step (sid=%016x cid=%d cidx=%d step=%d expectedStep=%d)",
        data.serverId, it->second->GetClientId(), clientIndex, step, asyncData.step);
    return;
  }

  if (nstl::find(asyncData.clientsForCrcRequest.begin(), asyncData.clientsForCrcRequest.end(), clientIndex)
        == asyncData.clientsForCrcRequest.end())
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: SendCrcData: Crc data received from unexpected client (sid=%016x cid=%d cidx=%d step=%d)",
        data.serverId, it->second->GetClientId(), clientIndex, step);
    return;
  }

  localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
    "GameServer: SendCrcData: Crc data received (sid=%016x cid=%d cidx=%d step=%d size=%d)",
      data.serverId, it->second->GetClientId(), clientIndex, step, crcData.size);

  if (crcDumper)
  {
    crcDumper->OnCrcDump(data.serverId, it->second->GetClientId(), step, crcData.memory, crcData.size);
  }

  if (it->second->IsAsynced())
  {
    OnAsync(step, asyncData.asyncInfo, it->second);
    DisconnectClient(clientIndex, Peered::DisconnectedByAsync);
    if (CheckSnapshots(clientIndex))
    {
      UpdateSnapshots();
    }
    RemoveClientFromProtectionRecords(clientIndex);
  }
  asyncData.clientsReportedCrc.push_back(clientIndex);
  if (asyncData.clientsReportedCrc.size() == asyncData.clientsForCrcRequest.size())
  {
    asyncData.clientsForCrcRequest.clear();
    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "GameServer: SendCrcData: Crc data received from all clients (sid=%016x)", data.serverId);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::CheckCrcDataRequestsTimeOut()
{
  if (asyncData.clientsForCrcRequest.size() > 0 && data.sessionSettings.crcDataRequestsTimeout > 0)
  {
    ++asyncData.requestsTimer;
    if (asyncData.requestsTimer >= data.sessionSettings.crcDataRequestsTimeout)
    {
      localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
        "GameServer: CheckCrcDataRequestsTimeOut: Crc data requests timed out for %d clients (sid=%016x timeOutSteps=%d)", 
          asyncData.clientsForCrcRequest.size(), data.serverId, data.sessionSettings.crcDataRequestsTimeout);
      CancelCrcDataRequests();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::CancelCrcDataRequests()
{
  for (list<int>::iterator itClientIndex = asyncData.clientsForCrcRequest.begin(); 
        itClientIndex != asyncData.clientsForCrcRequest.end(); ++itClientIndex)
  {
    ClientContainer::iterator itClient = clients.find(*itClientIndex);
    if (itClient != clients.end() && itClient->second->IsAsynced())
    {
      localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
        "GameServer: CancelCrcDataRequests: Crc data request canceled (sid=%016x cid=%d cidx=%d)", 
          data.serverId, itClient->second->GetClientId(), *itClientIndex);
      OnAsync(asyncData.step, asyncData.asyncInfo, itClient->second);
      DisconnectClient(*itClientIndex, Peered::DisconnectedByAsync);
      if (CheckSnapshots(*itClientIndex))
      {
        UpdateSnapshots();
      }
      RemoveClientFromProtectionRecords(*itClientIndex);
    }
  }
  asyncData.clientsForCrcRequest.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::OnDisconnectAck(int clientIndex)
{
  if (ClientHolder * client = GetPassiveClientByIndex(clientIndex))
  {
    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "GameServer: OnDisconnectAck: Disconnection acknowledged by client (sid=%016x cid=%d cidx=%d)", 
        data.serverId, client->GetClientId(), clientIndex);
    client->Disconnect();
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: OnDisconnectAck: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::DispatchPlaySameTeamDecision(int clientIndex, const bool agreed)
{
  ClientHolder* const sender = GetClient(clientIndex);

  if (!sender)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: DispatchPlaySameTeamDecision: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
    return;
  }

  const Transport::TClientId clientId = sender->GetClientId();

  ClientContainer::const_iterator it = clients.begin();
  ClientContainer::const_iterator it_end = clients.end();
  for (; it != it_end; ++it)
  {
    ClientHolder* const peer = it->second;

    if (!peer)
      continue;
    if (!peer->GetClient())
      continue;

    peer->GetClient()->OnPlaySameTeamDecision(clientId, agreed);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::DispatchBadBehaviourComplaint(int clientIndex, const Transport::TClientId reportedClientId, const int reportItemId)
{
  ClientHolder* const sender = GetClient(clientIndex);

  if (!sender)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: DispatchBadBehaviourComplaint: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
    return;
  }

  const Transport::TClientId clientId = sender->GetClientId();

  ClientContainer::const_iterator it = clients.begin();
  ClientContainer::const_iterator it_end = clients.end();
  for (; it != it_end; ++it)
  {
    ClientHolder* const peer = it->second;

    if (!peer)
      continue;
    if (!peer->GetClient())
      continue;

    peer->GetClient()->OnBadBehaviourComplaint(clientId, reportedClientId, reportItemId);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::AwardClients(const TUserAwards & awards)
{
  for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it)
  {
    vector<roll::SAwardInfo> dummy;
    const vector<roll::SAwardInfo> * clientAwards = &dummy;
    for ( int j = 0; j < awards.size(); ++j )
    {
      if ( awards[j].userId == (int)it->second->GetClientId() )
      {
        clientAwards = &awards[j].awards;
      }
    }
    it->second->Award( *clientAwards );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::OnFirstConnectionTimeout()
{
  statusChanges.clear();
  for (ClientContainer::iterator it = passiveClients.begin(); it != passiveClients.end(); ++it)
  {
    ClientHolder* client = it->second;
    if (client->GetStatus() == Connecting)
    {
      Peered::BriefClientInfo& info = statusChanges.push_back();
      info = client->GetInfo();
      info.status = Peered::ConnectionTimedOut;
    }
  }
  if (statusChanges.size() > 0)
  {
    OnChangeClientStatus(statusChanges, true, false);
  }
  firstConnectionTimeOutSent = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::AddClientToProtectionRecords(const int clientIndex, const int fromStep, const bool reserved /*= false*/)
{
  _protection.AddClient(clientIndex, fromStep, reserved);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::RemoveClientFromProtectionRecords(const int clientIndex, const int toStep, const bool unreserve /*= false*/)
{
  _protection.RemoveClient(clientIndex, toStep, unreserve);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::RemoveClientFromProtectionRecords(const int clientIndex)
{
  const Protection::StepRecordVector& records = _protection.GetStepRecords();

  Protection::StepRecordVector::const_iterator it = records.begin();
  Protection::StepRecordVector::const_iterator it_end = records.end();
  for (; it != it_end; ++it)
  {
    Protection::StepRecordVector::const_reference record = *it;

    record->RemoveClient(clientIndex);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::UpdateProtection()
{
  if (data.sessionSettings.pmConfirmFrequency <= 0)
    return;

  _protection.DropEmptyRecords();

  ProcessPendingProtectionMagic();

  _protection.Update();

  UpdateProtectionAsyncRecords();
  CheckProtectionMagicDelays();

  _protection.Update();

  UpdateProtectionRecords();

  CheckProtectionMagicConfirmation();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::UpdateProtectionRecords()
{
  const Protection::StepRecordVector& records = _protection.GetStepRecords();

  if (records.empty())
    return;

  Protection::StepRecord* completeRecord = NULL;
  Protection::StepRecord* reservedRecord = NULL;

  int completeRecordIndex = -1;
  int reservedRecordIndex = -1;

  // Check reserved snapshot from the oldest snapshots toward the newest. Break when found.
  if (data.sessionSettings.fastReconnectReserveSteps)
  {
    const int reservedFromStep = GetPendingStep() - data.sessionSettings.fastReconnectReserveSteps;  // reservedFromStep may be negative - it's ok

    // Start from one after the first snapshot to make backward checks
    for (int i = 1; i < records.size(); ++i)
    {
      Protection::StepRecordVector::const_reference record = records[i];

      if (!record->IsComplete())
        break;

      if (record->GetStep() > reservedFromStep)
      {
        // Backward case, which means the reserved step should be between current and previous snapshots.
        // It is possible, when confirmation frequency is > 1.
        reservedRecord = records[i - 1];
        reservedRecordIndex = i - 1;
        break;
      }
      
      if (record->GetStep() == reservedFromStep)
      {
        // Just a bingo case
        reservedRecord = records[i];
        reservedRecordIndex = i;
        break;
      }
    }

    if (!reservedRecord)
    {
      // If we've found nothing (no complete steps) set the first one as reserved
      reservedRecord = records[0];
      reservedRecordIndex = 0;
    }
  }

  // Check complete snapshots from the last complete by skipping reserved steps, which should be already checked
  const int reservedRecords = max(0, (lastConfirmedProtectionStep - records.front()->GetStep()) / data.sessionSettings.pmConfirmFrequency);

  for (int i = reservedRecords; i < records.size(); ++i)
  {
    Protection::StepRecordVector::const_reference record = records[i];

    if (!record->IsComplete())
      break;

    {
      completeRecord = record;
      completeRecordIndex = i;
    }
  }

  if (!data.sessionSettings.fastReconnectReserveSteps)
  {
    reservedRecord = completeRecord;
    reservedRecordIndex = completeRecordIndex;
  }

  if (completeRecord)
  {
    const int lastConfirmedProtectionStepOld = lastConfirmedProtectionStep;

    lastConfirmedProtectionStep = completeRecord->GetStep();

    if (lastConfirmedProtectionStep != lastConfirmedProtectionStepOld)
    {
      DeallocateProtectionRecords(reservedRecordIndex);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::UpdateProtectionAsyncRecords()
{
  const Protection::StepRecordVector& records = _protection.GetStepRecords();

  Protection::StepRecordVector::const_iterator it = records.begin();
  Protection::StepRecordVector::const_iterator it_end = records.end();
  for (; it != it_end; ++it)
  {
    Protection::StepRecordVector::const_reference record = *it;

    if (record->IsAsync() && !record->IsAsyncInfoSent())
    {
      localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
        "GameServer: UpdateProtectionAsyncRecords: Async information completed for record (sid=%016x step=%d)", 
          data.serverId, record->GetStep());

      DispatchProtectionAsyncRecord(record);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clients::_GenerateIndex()
{
  ++clientIndex;

  int newIndex = rand();

  if (RAND_MAX <= 0x7FFF)
  {
    newIndex *= rand();
  }

  return newIndex % INDEX_STEP + clientIndex * INDEX_STEP;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::MakeStep()
{
  commands.FinishStep();
  statuses.FinishStep();
  ResetCommandsSizeInfo();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::EraseSteps(int endStep)
{
  if (endStep > commands.GetStartStep())
  {
    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace("GameServer: Erase steps %d-%d (sid=%016x step=%d)", 
      commands.GetStartStep(), endStep-1, data.serverId, commands.GetPendingStep());
  }
  commands.EraseSteps(endStep);
  statuses.EraseSteps(endStep);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::DisconnectAllClients(Peered::EDisconnectReason::Enum reason /*= Peered::EDisconnectReason::None*/)
{
  while (clients.size() > 0)
  {
    ClientContainer::iterator it = clients.begin();
    _DisconnectClient(it, Peered::DisconnectedByServer, reason);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::SendWorldDataInfo(int clientIndex, const WorldDataInfo& _worldDataInfo)
{
  ClientHolder* client = GetClient(clientIndex);
  if (!client)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: SendWorldDataInfo: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
    return;
  }

  if (activeRequestClientIndex != clientIndex)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: SendWorldDataInfo: World data info received from unexpected client (sid=%016x cid=%d cidx=%d expectedClient=%d)", 
        data.serverId, client->GetClientId(), clientIndex, activeRequestClientIndex);
    return;
  }

  if (_worldDataInfo.partsCount > data.sessionSettings.snapshotChunkMaxCount 
        && data.sessionSettings.snapshotChunkMaxCount > 0 || _worldDataInfo.partsCount <= 0)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: SendWorldDataInfo: Received wrong world data parts count (sid=%016x cid=%d cidx=%d partsCount=%d)", 
        data.serverId, client->GetClientId(), clientIndex, _worldDataInfo.partsCount);
    OnGameCheated(client->GetClientId(), clientIndex);
    ForceWorldRequestTimeout();
    return;
  }

  if (_worldDataInfo.step < client->GetLastVerifiedStep() || _worldDataInfo.step > client->GetLastSentStep())
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: SendWorldDataInfo: Received wrong world data step (sid=%016x cid=%d cidx=%d step=%d lastVerified=%d lastSent=%d)", 
        data.serverId, client->GetClientId(), clientIndex, _worldDataInfo.step, client->GetLastVerifiedStep(), client->GetLastSentStep());
    ForceWorldRequestTimeout();
    return;
  }

  WorldSnapshot* snapshot = GetWorldSnapshot(_worldDataInfo.step);
  if (!snapshot)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: SendWorldDataInfo: Snapshot not found for the received world data step (sid=%016x cid=%d cidx=%d step=%d)", 
        data.serverId, client->GetClientId(), clientIndex, _worldDataInfo.step);
    ForceWorldRequestTimeout();
    return;
  }

  localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
    "GameServer: SendWorldDataInfo: World data info received (sid=%016x cid=%d cidx=%d step=%d parts=%d)", 
      data.serverId, client->GetClientId(), clientIndex, _worldDataInfo.step, _worldDataInfo.partsCount);

  worldDataInfo = _worldDataInfo;
  snapshot->ClearWorldDataParts();  // Just in case we pushed something in previous request
  snapshot->ReserveWorldDataParts(worldDataInfo.partsCount);
  SendAllClientsStatuses();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::SendWorldDataPart(int clientIndex, const rpc::MemoryBlock& worldDataPart)
{
  trafficStatistics->AddInReconnectTrafficSize(worldDataPart.size);

  ClientHolder* client = GetClient(clientIndex);
  if (!client)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: SendWorldDataPart: Client not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
    return;
  }

  if (activeRequestClientIndex != clientIndex)
  {
    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer: SendWorldDataPart: World data part from unexpected client (sid=%016x cid=%d cidx=%d expectedClient=%d)", 
        data.serverId, client->GetClientId(), clientIndex, activeRequestClientIndex);
    return;
  }

  if (worldDataPart.size > data.sessionSettings.snapshotChunkSize 
        && data.sessionSettings.snapshotChunkSize > 0 || worldDataPart.size <= 0)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: SendWorldDataPart: Wrong world data part size (sid=%016x cid=%d cidx=%d size=%d limit=%d)", 
        data.serverId, client->GetClientId(), clientIndex, worldDataPart.size, data.sessionSettings.snapshotChunkSize);
    OnGameCheated(client->GetClientId(), clientIndex);
    ForceWorldRequestTimeout();
    return;
  }

  WorldSnapshot* snapshot = GetWorldSnapshot(worldDataInfo.step);
  if (!snapshot)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: SendWorldDataPart: Snapshot not found for current world data step (sid=%016x cid=%d cidx=%d step=%d)", 
        data.serverId, client->GetClientId(), clientIndex, worldDataInfo.step);
    ForceWorldRequestTimeout();
    return;
  }

  snapshot->AddWorldDataPart(worldDataPart);

  if (snapshot->GetWorldDataPartsCount() == worldDataInfo.partsCount)
  {
    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer: SendWorldDataPart: World data parts completed (sid=%016x cid=%d cidx=%d partsCount=%d)", 
        data.serverId, client->GetClientId(), clientIndex, worldDataInfo.partsCount );

    // Send world data to all rejoiners, which already requested it
    _SendWorldData(snapshot);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::SetGameClientReconnect(int clientIndex, Peered::IGameClientReconnect * gameClientReconnect)
{
  RejoinerData * rejoinerData = GetRejoinerData(clientIndex);
  if (!rejoinerData)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: SetGameClientReconnect: Rejoiner not found (sid=%016x cidx=%d)", data.serverId, clientIndex);
    return;
  }

  localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
    "GameServer: SetGameClientReconnect: Game Client reconnect interface received (sid=%016x cid=%d cidx=%d)", 
      data.serverId, rejoinerData->GetClientId(), clientIndex);

  rejoinerData->SetGameClientReconnect(gameClientReconnect);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::OnGameCheated(uint clientId, uint clientIndex, lobby::ECheatType::Enum cheatType /*= lobby::ECheatType::None*/)
{
  localLog(logStream, NLogg::LEVEL_WARNING).Trace(
    "GameServer: OnGameCheated (sid=%016x cid=%d cidx=%d)", data.serverId, clientId, clientIndex);

  if (statsLink)
  {
    statsLink->OnGameCheated(data.serverId, clientId, cheatType, "0.0.0.0" );
  }

  // TODO: Currently we do not disconnect here with DisconnectedByCheatAttempt status, but we do it in the 
  // async handling logic with status DisconnectedByServer. It is done, because currently asyncs are mostly 
  // our bugs and clients shouldn't be punished therefore. But still we need to inform lobbby for statistics.
  if (cheatType != lobby::ECheatType::Async)
  {
    DisconnectClient(clientIndex, Peered::DisconnectedByCheatAttempt, Peered::EDisconnectReason::ServerError);
    if (CheckSnapshots(clientIndex))
    {
      UpdateSnapshots();
    }
    RemoveClientFromProtectionRecords(clientIndex);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::DumpSteps(int endStep)
{
  int steps = endStep-commands.GetStartStep();
  if (log && steps > 0)
  {
    log->OnCommandsDump(data.serverId, commands.GetStartStep(), endStep, commands, statuses);
  }
  EraseSteps(endStep+1);
  dumpStepsCount = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::CheckAsyncSnapshots()
{
  bool allDisconnected = false;
  int asyncCounter = 0;

  for (WorldSnapshotContainer::iterator it=snapshots.begin(); !allDisconnected && it != snapshots.end(); ++it)
  {
    WorldSnapshot* currentSnapshot = *it;
    if (currentSnapshot->IsAsyncDetected())
    {
      ++asyncCounter;

      if(currentSnapshot->IsAllRecieved(false))
      {
        if (!currentSnapshot->IsAsyncInfoSent())
        {
          localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
            "GameServer: CheckAsyncSnapshots: Async information completed for snapshot (sid=%016x step=%d)", 
              data.serverId, currentSnapshot->GetStep());

          nstl::vector<AsyncInfo> asyncs;
          asyncs.reserve(clients.size());
          for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it)
          {
            AsyncInfo & async = asyncs.push_back();
            async.clientId = it->second->GetClientId();
            async.crc = currentSnapshot->GetCrc(it->first);
          }

          allDisconnected = CheckAsyncSnapshot(currentSnapshot, asyncs);
        }
        --asyncCounter;
      }
    }
  }

  if (allDisconnected)
  {
    localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
      "GameServer: CheckAsyncSnapshots: Async recovery failed, finishing game (sid=%016x)", data.serverId);
    // Will actually finish in the next scheduler's step
  }
  else if (!asyncCounter)
  {
    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer: CheckAsyncSnapshots: Async recovery successed, resuming game (sid=%016x)", data.serverId);

    //Block(false);
    SetStatus(Clients::Started);
  }
  else
  {
    localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
      "GameServer: CheckAsyncSnapshots: %d async snapshots left (sid=%016x)", asyncCounter, data.serverId);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clients::CheckAsyncSnapshot(WorldSnapshot * snapshot, const nstl::vector<AsyncInfo> & asyncInfo)
{
  bool allDisconnected = false;
  nstl::vector<int> asyncClients;
  asyncClients.reserve(clients.size());
  list<int> * clientsForCrcRequest = 0;
  
  if (data.sessionSettings.crcDataRequestsEnabled && asyncData.step == NCore::INVALID_STEP)
  {
    clientsForCrcRequest = &asyncData.clientsForCrcRequest;
    asyncData.asyncInfo = asyncInfo;
  }

  if (snapshot->GetAsyncClients(asyncClients, clientsForCrcRequest))
  {
    // Set async info sent flag here, so disconnects from this call will not yield repetitive CheckAsyncSnapshot calls
    snapshot->SetAsyncInfoSent(true);

    if (data.sessionSettings.sendAsyncToAllClientsEnabled)
    {
      // If we have to send async to all clients - fill asyncClients with complete list of active clients
      asyncClients.clear();
      for (ClientContainer::iterator it = clients.begin(); it != clients.end(); ++it)
      {
        asyncClients.push_back(it->first);
      }
    }

    if (clientsForCrcRequest && clientsForCrcRequest->size() == 1)
    {
      clientsForCrcRequest->clear();
    }

    nstl::vector<int> asyncClientsForDisconnect;
    asyncClientsForDisconnect.reserve(asyncClients.size());
    
    for (int i = 0; i < asyncClients.size(); ++i)
    {
      if (nstl::find(asyncData.clientsForCrcRequest.begin(), asyncData.clientsForCrcRequest.end(), asyncClients[i]) 
            == asyncData.clientsForCrcRequest.end())
      {
        asyncClientsForDisconnect.push_back(asyncClients[i]);
      }
    }

    if (asyncClients.size() == 0 || asyncClients.size() == snapshot->GetClientsCount(false))
    {
      DisconnectRejoiningClients(Peered::EDisconnectReason::GameFinished, false);
      allDisconnected = true;
      asyncData.isAllAsynced = true;
    }

    if (asyncClientsForDisconnect.size() > 0)
    {
      OnAsync(snapshot->GetStep(), asyncInfo, asyncClientsForDisconnect);
      DisconnectClients(asyncClientsForDisconnect, Peered::DisconnectedByAsync);
      CheckSnapshots(asyncClientsForDisconnect);

      {
        for (int i = 0, count = asyncClientsForDisconnect.size(); i < count; ++i)
          RemoveClientFromProtectionRecords(asyncClientsForDisconnect[i]);
      }
    }

    if (asyncData.step == NCore::INVALID_STEP)
    {
      asyncData.step = snapshot->GetStep();
      RequestCrcData();
    }
  }
  else
  {
    snapshot->UpdateStatus();
  }

  return allDisconnected;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::RequestCrcData()
{
  list<int>::iterator it =  asyncData.clientsForCrcRequest.begin();
  if (!asyncData.isAllAsynced)
  {
    RequestCrcDataFromClient(*it, false);
    ++it;
  }
  for (; it != asyncData.clientsForCrcRequest.end(); ++it)
  {
    RequestCrcDataFromClient(*it, true);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::RequestCrcDataFromClient(int clientIndex, bool isAsync)
{
  ClientContainer::iterator itClient = clients.find(clientIndex);
  if (itClient != clients.end())
  {
    ClientHolder* client = itClient->second;
    client->SetAsynced(isAsync);
    client->RequestCrcData(asyncData.step);
    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "GameServer: SendCrcData: Requesting CRC data from client (sid=%016x cid=%d cidx=%d isAsync=%d)",
        data.serverId, client->GetClientId(), client->clientIndex, isAsync);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::UpdateSnapshots()
{
  if (snapshots.size() == 0)
    return;

  WorldSnapshot* completeSnapshot = 0;
  int completeIndex = -1;

  WorldSnapshot* reservedSnapshot = 0;
  int reservedIndex = -1;

  // Check reserved snapshot from the oldest snapshost toward the newest. Break when found.
  if (data.sessionSettings.fastReconnectReserveSteps)
  {
    int reservedFromStep = GetPendingStep() - data.sessionSettings.fastReconnectReserveSteps;  // reservedFromStep may be negative - it's ok

    // Start from one after the first snapshot to make backward checks
    for (int i = 1; i < snapshots.size(); ++i)
    {
      WorldSnapshot* currentSnapshot = snapshots[i];
      if (currentSnapshot->GetStatus() == CrcStatuses::Complete)
      {
        if (currentSnapshot->GetStep() > reservedFromStep)
        {
          // Backward case, which means the reserved step should be between current and previous snapshots.
          // It is possible, when confirmation frequency is > 1.
          reservedSnapshot = snapshots[i-1];
          reservedIndex = i-1;
          break;
        }
        else if (currentSnapshot->GetStep() == reservedFromStep)
        {
          // Just a bingo case
          reservedSnapshot = snapshots[i];
          reservedIndex = i;
          break;
        }
      }
      else
      {
        break;
      }
    }

    if (!reservedSnapshot)
    {
      // If we've found nothing (no complete steps) set the first one as reserved
      reservedSnapshot = snapshots[0];
      reservedIndex = 0;
    }
  }


  // Check complete snapshots from the last complete by skipping reserved steps, which should be already checked
  for (int i = max(0, (lastConfirmedStep - snapshots[0]->GetStep())/data.sessionSettings.confirmFrequency); 
        i < snapshots.size(); ++i)
  {
    WorldSnapshot* currentSnapshot = snapshots[i];
    if (currentSnapshot->GetStatus() == CrcStatuses::Complete)
    {
      completeSnapshot = currentSnapshot;
      completeIndex = i;
    }
    else
    {
      break;
    }
  }

  if (!data.sessionSettings.fastReconnectReserveSteps)
  {
    reservedSnapshot = completeSnapshot;
    reservedIndex = completeIndex;
  }

  int stepsForDumpCount = 0;

  if (completeSnapshot)
  {
    MarkVerified(completeSnapshot->GetStep());

    lastConfirmedStep = completeSnapshot->GetStep();

    if (lastReservedStep == NCore::INVALID_STEP)
    {
      lastReservedStep = lastConfirmedStep;
    }

    int oldLastREservedStep = lastReservedStep;
    lastReservedStep = reservedSnapshot->GetStep();
    stepsForDumpCount = lastReservedStep - oldLastREservedStep;

    DeallocateSnapshots(reservedIndex);
  }

  dumpStepsCount += stepsForDumpCount;
  if (dumpStepsCount >= data.sessionSettings.dumpStepsMaxCount)
  {
    DumpSteps(lastReservedStep-1);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WorldSnapshot* Clients::GetWorldSnapshot(int step)
{
  for (WorldSnapshotContainer::iterator it=snapshots.begin();it!=snapshots.end();++it)
  {
    if ((*it)->GetStep() == step)
    {
      return (*it);
    }
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::CheckSnapshotAllocated(int step)
{
  struct Local
  {
    static inline bool IsConfirmationStep(const int step, const int confirmFrequency)
    {
      if (confirmFrequency <= 0)
        return false;
      if (step % confirmFrequency)
        return false;

      return true;
    }
  };

  if (Local::IsConfirmationStep(step, data.sessionSettings.confirmFrequency))
  {
    int lastStep = lastConfirmedStep;
    if (snapshots.size() > 0)
    {
      lastStep = snapshots[snapshots.size()-1]->GetStep();
    }
    for (int i=lastStep+1;i<=step;++i)
    {
      if (i % data.sessionSettings.confirmFrequency)
        continue;

      AllocateSnapshot(i);
    }
  }

  if (Local::IsConfirmationStep(step, data.sessionSettings.pmConfirmFrequency))
  {
    const int lastStep = _protection.GetLastStep(lastConfirmedProtectionStep);

    for (int i = lastStep + 1; i <= step; ++i)
    {
      if (i % data.sessionSettings.pmConfirmFrequency)
        continue;

      AllocateProtectionRecord(i);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::AllocateSnapshot(int _step, CrcStatuses::Status _status)
{
  WorldSnapshot* snapshot;

  if (snapshotCache.size() > 0)
  {
    snapshot = *(snapshotCache.end()-1);
    snapshotCache.pop_back();
    snapshot->Reset(_step, _status);
  }
  else
  {
    snapshot = new WorldSnapshot(_step, _status);
  }

  for (ClientContainer::iterator it = clients.begin();it != clients.end();++it)
  {
    if (it->second->GetInfo().status != Connecting || GetStatus() == Clients::Loading || IsWorldRequestedByRejoiner(it->first))
    {
      snapshot->AddClient(it->second->clientIndex);
    }
  }

  snapshots.push_back(snapshot);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::DeallocateSnapshots( int _index)
{
  for (int i=0;i<_index;++i)
  {
    snapshotCache.push_back(snapshots[i]);
    snapshots[i]->ClearWorldDataParts();
  }

  snapshots.erase(snapshots.begin(), snapshots.begin()+_index);
}

namespace
{
  struct Deleter
  {
    template <class T>
    void operator()(T* p) const
    {
      delete p;
    }
  };
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::DeleteSnapshots(WorldSnapshotContainer& _container)
{
  nstl::for_each(_container.begin(), _container.end(), Deleter());

  _container.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::UpdateStatusChanges()
{
  NI_PROFILE_BLOCK( "Client status changes" );

  bool checkForComplete = false;

  for (int i=0;i<statusChanges.size();++i)
  {
    Peered::BriefClientInfo& info = statusChanges[i];

    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: Client %s (sid=%016x cid=%d cidx=%d)", 
        GetClientStatus(info.status), data.serverId, info.clientId, statusChangesIndices[i]);

    const bool disconnected =
      (info.status == Peered::DisconnectedByClient) ||
      (info.status == Peered::DisconnectedByServer) ||
      (info.status == Peered::DisconnectedByClientIntentionally);

    if (disconnected)
    {
      if (RemoveRejoinClient(statusChangesIndices[i]))
      {
        LogReconnectResult(info.clientId, EReconnectType::Normal, EReconnectResult::Disconnected);
      }

      if (CheckSnapshots(statusChangesIndices[i]))
        checkForComplete = true;

      RemoveClientFromProtectionRecords(statusChangesIndices[i]);
    }
  }
  if (checkForComplete)
  {
    UpdateSnapshots();
  }
  if (GetStatus() == Clients::Blocked)
  {
    CheckAsyncSnapshots();
  }

  OnChangeClientStatus(statusChanges);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clients::CheckClients(Peered::ICommandsHandler* handler, Peered::IWorld* world)
{
  CheckStatuses((GetStatus() == Clients::Started), statusChangesIndices, statusChanges, world);

  if (statusChanges.size() > 0)
  {
    UpdateStatusChanges();
  }

  if (needToApplyWorldData && GetStatus() != Clients::Blocked) // Process world request only if not handling async
  {
    ++reconnectStepCounter;

    if (worldDataRequests.size() == 0 || data.sessionSettings.snapshotRequestTimeout > 0 
          && reconnectStepCounter >= data.sessionSettings.snapshotRequestTimeout)
    {
      if (_RequestWorldData() == INVALID_INDEX)
      {
        // Here we know, that there are no active clients left, which we didn't requested world from. So timeout the reconnect
        _WorldDataRequestTimeOut();
      }
    }
  }

  return clients.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::CheckPassiveClients()
{
  
  int step = GetPendingStep();

  for (ClientContainer::iterator it = passiveClients.begin(); it != passiveClients.end(); ++it)
  {
    ClientHolder * client = it->second;

    if (data.sessionSettings.reconnectTimeout > 0)
    {
      int reconnectAnnouncementStep = client->GetReconnectAnnouncementStep();

      if (reconnectAnnouncementStep != NCore::INVALID_STEP && step - reconnectAnnouncementStep >= data.sessionSettings.reconnectTimeout)
      {
        localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
          "GameServer: CheckPassiveClients: Announced reconnect timed out (sid=%016x cid=%d cidx=%d step=%d)", 
            data.serverId, client->GetClientId(), client->clientIndex, step);
        
        client->SetReconnectAnnouncementStep(NCore::INVALID_STEP);
        client->SetStatus(Peered::ConnectionTimedOutOnReconnect);
        OnChangeClientStatus(client->GetInfo(), true, false);
        LogClientStatus(client->GetInfo());
      }
    }

    if (data.sessionSettings.disconnectAckTimeoutSteps > 0 && client->IsConnected() 
        && step - client->GetDisconnectionStep() >= data.sessionSettings.disconnectAckTimeoutSteps)
    {
      localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
        "GameServer: CheckPassiveClients: Disconnection acknowledgement timed out (sid=%016x cid=%d cidx=%d step=%d disconnectAckTimeoutSteps=%d)", 
          data.serverId, client->GetClientId(), client->clientIndex, step, data.sessionSettings.disconnectAckTimeoutSteps);
      client->Disconnect();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::CheckProtectionMagicDelays()
{
  if (data.sessionSettings.pmDelayGap <= 0)
    return;

  const int shiftDownThreshold = data.sessionSettings.pmDelayGap / 4;
  const int shiftUpThreshold = data.sessionSettings.pmDelayGap * 3 / 4;
  const int shiftStep = data.sessionSettings.pmDelayGap / 2;

  const int currentStep = GetPendingStep();

  Protection::ClientIndexVector disconnectClients;

  for (ClientContainer::const_iterator it = clients.begin(); it != clients.end(); ++it)
  {
    const int clientIndex = it->first;

    if (worldDataRequests.find(clientIndex) != worldDataRequests.end())
      continue;

    ClientHolder* const client = it->second;

    const int gap = client->GetProtectionMagicReceiveGap();
    const int bottom = client->GetProtectionMagicReceiveGapBottom();

    if (gap - bottom > shiftUpThreshold)
    {
      OnProtectionMagicDelay(currentStep, client, disconnectClients);

      client->SetProtectionMagicReceiveGapBottom(bottom + shiftStep);
    }
    else if (bottom - gap > shiftDownThreshold)
    {
      client->SetProtectionMagicReceiveGapBottom(max<int>(0, bottom - shiftStep));
    }
  }

  if (disconnectClients.empty())
    return;

  for (int i = 0, count = disconnectClients.size(); i < count; ++i)
  {
    if (ClientHolder* const client = GetClient(disconnectClients[i]))
      OnGameCheated(client->GetClientId(), client->clientIndex, lobby::ECheatType::ProtectionViolation);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::CheckProtectionMagicConfirmation()
{
  if (data.sessionSettings.pmTrustGap <= 0)
    return;

  if (lastConfirmedStep < 0)
    return;
  if (lastConfirmedProtectionStep < 0)
    return;

  const int gap = max<int>(0, lastConfirmedStep - lastConfirmedProtectionStep);

  if (gap < data.sessionSettings.pmTrustGap)
    return;

  const int currentStep = GetPendingStep();

  const Protection::StepRecordVector& records = _protection.GetStepRecords();

  if (records.empty())
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: CheckProtectionMagicConfirmation: Protection magic confirmation delayed, but there are no protection step records! (sid=%016x step=%d gap=%d)",
        data.serverId, currentStep, gap);
    return;
  }

  Protection::StepRecord* record = NULL;

  Protection::StepRecordVector::const_iterator it = records.begin();
  Protection::StepRecordVector::const_iterator it_end = records.end();
  for (; it != it_end; ++it)
  {
    Protection::StepRecordVector::const_reference record = *it;

    if (record->IsComplete())
      continue;
  }

  if (!record)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: CheckProtectionMagicConfirmation: Protection magic confirmation delayed, but there is no incomplete protection step record! (sid=%016x step=%d gap=%d)",
        data.serverId, currentStep, gap);
    return;
  }

  const Protection::ClientIndexVector& pendingClients = record->GetPendingClients();

  if (pendingClients.empty())
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: CheckProtectionMagicConfirmation: Protection magic confirmation delayed, but there are no pending clients in protection step record! (sid=%016x step=%d gap=%d recordStep=%d)",
        data.serverId, currentStep, gap, record->GetStep());
    return;
  }

  for (int i = 0, count = pendingClients.size(); i < count; ++i)
  {
    if (ClientHolder* const client = GetClient(pendingClients[i]))
      OnGameCheated(client->GetClientId(), client->clientIndex, lobby::ECheatType::ProtectionViolation);
  }
}

void Clients::ProcessPendingProtectionMagic()
{
  for (int i = 0, count = _pendingMagic.size(); i < count; ++i)
  {
    const Protection::MagicRecord& record = _pendingMagic[i];

    ProcessMagicRecord(record);
  }

  _pendingMagic.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clients::_RequestWorldData()
{
  if (!gameServerReconnect)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: _RequestWorldData: Reconnect interface isn't set (sid=%016x)", data.serverId);
    return INVALID_INDEX;
  }

  //int minStep = (data.confirmFrequency>0)?(((GetPendingStep()-2)/data.confirmFrequency)*data.confirmFrequency):(GetPendingStep()-2);
  int maxStep = NCore::INVALID_STEP;
  int clientIndex = INVALID_INDEX;
  ClientHolder * client = 0;

  for (ClientContainer::iterator it = clients.begin();
        it != clients.end(); ++it)
  {
    // Choose client with highest verified step, which doesn't reconnect and we didn't requested from
    if (it->second->GetStatus() != Connecting 
      && worldDataRequests.find(it->first) == worldDataRequests.end())
    {
      int lastStep = it->second->GetLastSentVerifiedStep();
      if ((lastStep > maxStep))
      {
        maxStep = lastStep;
        clientIndex = it->first;
        client = it->second;
      }
    }
  }

  if (clientIndex != INVALID_INDEX && client)
  {
    //clients[clientIndex]->RequestWorldData(RemotePtrInOtherGate<Peered::RIGameServerReconnect>(gameServerReconnect, reconnectIfaceId));
    clients[clientIndex]->RequestWorldData(RemotePtr<Peered::RIGameServerReconnect>(gameServerReconnect));
    activeRequestClientIndex = clientIndex;
    worldDataRequests.insert(clientIndex);
    reconnectStepCounter = 0;

    localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
      "GameServer: World data requested from client (sid=%016x cid=%d cidx=%d)", 
        data.serverId, client->GetClientId(), activeRequestClientIndex);
  }

  return clientIndex;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::_SendWorldData(WorldSnapshot* snapshot)
{
  list<int> disconnectClients;

  for (RejoinersData::iterator it = rejoinClients.begin(); 
        it != rejoinClients.end(); ++it)
  {
    ClientHolder* client = GetClient(it->first);
    if (client && it->second.IsWorldRequested() && !it->second.IsWorldApplied())
    {
      if (Peered::IGameClientReconnect * gameClientReconnect = it->second.GetGameClientReconnect())
      {
        gameClientReconnect->ApplyWorldDataInfo(worldDataInfo);
        client->Rewind(worldDataInfo.step, data.sessionSettings.confirmFrequency);
        client->nextStep = worldDataInfo.step + 1;
        for (int i = 0; i < snapshot->GetWorldDataPartsCount(); ++i)
        {
          rpc::MemoryBlock & dataPart = snapshot->GetWorldDataPart(i);
          gameClientReconnect->ApplyWorldDataPart(dataPart);
          trafficStatistics->AddOutReconnectTrafficSize(dataPart.size);
        }

        localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
          "GameServer: World data sent to client (sid=%016x cid=%d cidx=%d dataStep=%d partsCount=%d)", 
            data.serverId, client->GetClientId(), it->first, worldDataInfo.step, worldDataInfo.partsCount);

        client->SetSnapshotApplyTimeoutStep(0);
        it->second.SetWorldAppliedStep(worldDataInfo.step);
        // Remove client reservation from snapshots steps prior to applied
        const int nextProtectionMagicConfirmationStep =
          GetNextConfirmationStep(worldDataInfo.step, data.sessionSettings.pmConfirmFrequency) + data.sessionSettings.pmConfirmFrequency;

        RemoveClientFromSnapshots(it->first, worldDataInfo.step, true);
        RemoveClientFromProtectionRecords(it->first, nextProtectionMagicConfirmationStep, true);
      }
      else
      {
        localLog(logStream, NLogg::LEVEL_WARNING).Trace(
          "GameServer: Client's reconnect interface isn't set (sid=%016x cid=%d cidx=%d)", 
            data.serverId, client->GetClientId(), it->first);
        disconnectClients.push_back(it->first);
        LogReconnectResult(it->second.GetClientId(), EReconnectType::Normal, EReconnectResult::NoReconnectIface);
      }
    }
  }
  if (disconnectClients.size() > 0)
  {
    for (list<int>::iterator it = disconnectClients.begin(); it != disconnectClients.end(); ++it)
    {
      DisconnectRejoiningClient(*it, Peered::EDisconnectReason::ServerError);
    }
  }
  _InitRejoinData();
  trafficStatistics->FinishOutReconnectTrafficFrame();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::_WorldDataRequestTimeOut()
{
  uint clientId = 0;
  if (ClientHolder * client = GetClient(activeRequestClientIndex))
  {
    clientId = client->GetClientId();
  }
  else if (ClientHolder * client = GetPassiveClientByIndex(activeRequestClientIndex))
  {
    clientId = client->GetClientId();
  }
  localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
    "GameServer: World data request timed out (sid=%016x cid=% cidx=%d)", 
              data.serverId, clientId, activeRequestClientIndex);

  // Kick unlucky rejoiners, if any
  for (RejoinersData::iterator it = rejoinClients.begin(); 
        it != rejoinClients.end();)
  {
    RejoinersData::iterator itTmp = it;
    ++it;

    // Force disconnect only if world was not applied
    if (!itTmp->second.IsWorldApplied())
    {
      LogReconnectResult(itTmp->second.GetClientId(), EReconnectType::Normal, EReconnectResult::WorldRequestFailed);
      DisconnectRejoiningClient(itTmp->first, Peered::EDisconnectReason::ServerError);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::AllocateProtectionRecord(const int step)
{
  Protection::StepRecord* const record = _protection.AllocateStepRecord(step);

  ClientContainer::const_iterator it = clients.begin();
  ClientContainer::const_iterator it_end = clients.end();
  for (; it != it_end; ++it)
  {
    const int clientIndex = it->first;
    ClientHolder* const client = it->second;

    const bool add =
      (client->GetInfo().status != Connecting) ||
      (GetStatus() == Clients::Loading) ||
      (IsWorldRequestedByRejoiner(clientIndex));

    if (add)
      record->AddClient(clientIndex);
  }

  record->Update();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::DeallocateProtectionRecords(const int count)
{
  _protection.DeallocateStepRecords(count);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::DispatchProtectionAsyncRecord(Protection::StepRecord* const record)
{
  record->NotifyAsyncInfoSent();

  const Protection::ClientIndexVector& asyncClients = record->GetAsyncClients();

  Protection::ClientIndexVector disconnectClients;

  disconnectClients.reserve(asyncClients.size());

  OnProtectionMagicAsync(record->GetStep(), asyncClients, disconnectClients);

  if (disconnectClients.empty())
    return;

  for (int i = 0, count = disconnectClients.size(); i < count; ++i)
  {
    if (ClientHolder* const client = GetClient(disconnectClients[i]))
      OnGameCheated(client->GetClientId(), client->clientIndex, lobby::ECheatType::ProtectionAsync);
  }
}

void Clients::ProcessMagicRecord(const Protection::MagicRecord& magicRecord)
{
  ClientHolder* client = GetClient(magicRecord.clientIndex);

  if (!client)
  {
    if (!IsClientDisconnected(magicRecord.clientIndex))  // check if client was disconnected
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: ProcessMagicRecord: Client not found (sid=%016x cidx=%d step=%d)", data.serverId, magicRecord.clientIndex, magicRecord.step);
    }

    return;
  }

  if (data.sessionSettings.pmConfirmFrequency <= 0)
    return;
  if (magicRecord.step % data.sessionSettings.pmConfirmFrequency)
    return;

  if (GetStatus() == Clients::Loading)
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: ProcessMagicRecord: Called before OnStart (sid=%016x cid=%d cidx=%d step=%d)", 
        data.serverId, client->GetClientId(), magicRecord.clientIndex, magicRecord.step);
    return;
  }

  Protection::StepRecord* const stepRecord = _protection.GetStepRecord(magicRecord.step);

  if (!stepRecord)
  {
    if (!IsClientDisconnected(magicRecord.clientIndex))  // check if client was disconnected
    {
      localLog(logStream, NLogg::LEVEL_WARNING).Trace(
        "GameServer: ProcessMagicRecord: Step record not found (sid=%016x cid=%d cidx=%d step=%d lastConfirmedProtectionStep=%d)", 
          data.serverId, client->GetClientId(), magicRecord.clientIndex, magicRecord.step, lastConfirmedProtectionStep);
      // TODO: notify about cheater
    }
    return;
  }

  if (magicRecord.step <= client->GetLastSentStep())
  {
    // TODO
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "GameServer: ProcessMagicRecord: Protection step confirmation received for not sent step (sid=%016x cid=%d cidx=%d step=%d lastSent=%d)",
        data.serverId, client->GetClientId(), magicRecord.clientIndex, magicRecord.step, client->GetLastSentStep());
    OnGameCheated(client->GetClientId(), magicRecord.clientIndex); // TODO: ProtectionViolation ?
    return;
  }

  client->MarkProtectionMagicReceived(magicRecord.step);

  stepRecord->SetClientMagic(magicRecord.clientIndex, magicRecord.magic);

  if (stepRecord->Update())
  {
    if (stepRecord->IsAsync())
    {
      localLog( logStream, NLogg::LEVEL_WARNING ).Trace(
        "GameServer: Protection async detected (sid=%016x cid=%d cidx=%d step=%d)", 
          data.serverId, client->GetClientId(), magicRecord.clientIndex, magicRecord.step);

      Protection::ClientMagicInfoContainer magics;

      stepRecord->GetMagicInfo(magics);

      for (int i = 0, count = magics.size(); i < count; ++i)
      {
        localLog( logStream, NLogg::LEVEL_DEBUG ).Trace(
          "GameServer:       cidx=%d crc=0x%08X", magics[i].clientIndex, magics[i].magic);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::OnChangeClientStatus(const nstl::vector<Peered::BriefClientInfo>& clientInfos, bool sendOnHybridLink /*= true*/, bool sendToClients /*= true*/)
{
  if (sendOnHybridLink && statsLink)
  {
    statsLink->OnChangeClientStatus(data.serverId, clientInfos);
  }

  if (sendToClients)
  {
    for (int i = 0; i < clientInfos.size(); ++i)
    {
      if (spectators.find(clientInfos[i].clientId) == spectators.end())
      {
        statuses.Append(&clientInfos[i], sizeof(clientInfos[i]));
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::StartGame(int forcedStartTimerValue)
{
  if (forcedStartTimerValue > 0)
  {
    localLog(logStream, NLogg::LEVEL_MESSAGE).Trace(
      "GameServer: Start game timed out, forcing start (sid=%016x timer=%d)", data.serverId, forcedStartTimerValue);
  }

  if (HavePendingCommands())
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace("GameServer: Pending commands detected, stepping (sid=%016x)", data.serverId);
    MakeStep();
    SendStep(true);
  }
  const int startStep = commands.GetPendingStep();
  EraseSteps(startStep);

  localLog(logStream, NLogg::LEVEL_DEBUG).Trace("GameServer: Starting game (sid=%016x step=%d)", data.serverId, startStep);
  OnStart(startStep);
  if (log)
    log->OnStartGame(data.serverId, clientVersion, startStep);
  status = Started;
  lastConfirmedStep = startStep-1;
  lastConfirmedProtectionStep = startStep - 1;
  lastReservedStep = lastConfirmedStep;

  statusChanges.clear();
  for (ClientContainer::iterator it=passiveClients.begin();it!=passiveClients.end();++it)
  {
    ClientHolder* client = it->second;
    if (client->GetInfo().status == Peered::Connecting)
    {
      client->SetStatus(Peered::ConnectionTimedOut);
      if (!firstConnectionTimeOutSent)
      {
        Peered::BriefClientInfo& info = statusChanges.push_back();
        info = client->GetInfo();
      }
      LogClientStatus(client->GetInfo());
    }
  }
  if (statusChanges.size() > 0 && statsLink)
  {
    OnChangeClientStatus(statusChanges, true, false);
  }

  SendAllClientsStatuses();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clients::_InitRejoinData()
{
  worldDataInfo.clear();
  activeRequestClientIndex = INVALID_INDEX;
  reconnectStepCounter = 0;
  needToApplyWorldData = false;
  worldDataRequests.clear();
}

} //namespace Peered

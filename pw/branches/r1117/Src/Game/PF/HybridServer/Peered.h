#pragma once

#include <Server/RPC/RPC.h>
#include "PeeredTypes.h"
#include "Server/Roll/RollTypes.h"
#include "Server/Statistic/StatisticsServerTypes.h"

#include "Network/TransportMulticastChannel.h"
#include "Network/LoginClientVersion.h"

namespace Peered
{

  typedef map<Transport::TServiceId, StrongMT<Transport::IMulticastChannel> >  TMulticastChannels;

struct EntityInfo : BriefEntityInfo
{
  short size;
};

struct AsyncInfo 
{
  uint clientId;
  uint crc;
};

namespace EDisconnectReason
{
  enum Enum
  {
    None                = 0,
    ClientPerfomance    = 1,
    NetworkPerfomance   = 2,
    ClientAway          = 3,
    GameFinished        = 4,
    ServerError         = 5,
  };
}

struct SHybridPongResult : public rpc::Data
{

  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  float pingTime;
  int worldStep;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&pingTime); f.Add(3,&worldStep); return 0; }
  
  //SHybridPongResult( float _ping, int _step ): pingTime(_ping), worldStep(_step) {}
  SHybridPongResult(): pingTime(0), worldStep(0) {}
};


struct WorldDataInfo
{
  int step;
  int partsCount;

  WorldDataInfo(int _step, uint _partsCount): step(_step), partsCount(_partsCount) {}
  WorldDataInfo() { clear(); }
  void clear() { step = -1; partsCount = 0; }
};

class RIGameServerReconnect;

REMOTE struct IGameClient : rpc::IRemoteEntity
{
  RPC_ID();
  NI_DECLARE_CLASS_1(IGameClient, rpc::IRemoteEntity);

  REMOTE virtual void Start(const ClientStartInfo& clientStartInfo, RIGameServerReconnect * gameServerReconnect)=0;
  REMOTE virtual void Step(
    int step, 
    int lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<BriefClientInfo>& statuses,
    const nstl::vector<GapInfo>& clientGaps,
    const Transport::MessageMiscInfo& __miscInfo__)=0;
  REMOTE virtual void StepLoading(
    int step, 
    int lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<BriefClientInfo>& statuses,
    const nstl::vector<GapInfo>& clientGaps)=0;
  REMOTE virtual void StepBatch(
    int lastConfirmedStep,
    const nstl::vector<ClientStepData>& stepData)=0;
  //REMOTE virtual void ApplySnapshot(int step, uint worldCrc, const nstl::vector<BriefEntityInfo>& entitiesIds, const nstl::vector<rpc::MemoryBlock>& entitiesData)=0;
  REMOTE virtual void OnAsync(int step, const nstl::vector<AsyncInfo>& async)=0;
  REMOTE virtual void OnStart(int step)=0;
  REMOTE virtual void OnTimeScaleChanged(float scale)=0;
  REMOTE virtual void OnChangeClientStatus(const nstl::vector<BriefClientInfo>& clientStatuses)=0;
  REMOTE virtual void OnDisconnect( int reason ) = 0; // EDisconnectReason::Enum
//  REMOTE virtual const nstl::vector<rpc::MemoryBlock>& GetSnapshot(uint step, const nstl::vector<uint>& entitiesIds)=0;
  REMOTE virtual void OnRejoin(uint clientId)=0;
  REMOTE virtual void RequestWorldData(RIGameServerReconnect * gameServerReconnect)=0;
  REMOTE virtual void RequestCrcData(int step)=0;
  REMOTE virtual void Award( const vector<roll::SAwardInfo> & _awards )=0;
  REMOTE virtual void OnSpectate( const SpectatorInfo& info )=0;
  REMOTE virtual void OnPlaySameTeamDecision(const Transport::TClientId clientId, const bool agreed) = 0;
  REMOTE virtual void OnBadBehaviourComplaint(const Transport::TClientId clientId, const Transport::TClientId reportedClientId, int reportItemId  ) = 0;
  REMOTE virtual void OnProtectionAsync(int step) = 0;
};

REMOTE struct IGameClientReconnect : public rpc::IRemoteEntity
{
  RPC_ID();
  NI_DECLARE_CLASS_1(IGameClientReconnect, rpc::IRemoteEntity);

  REMOTE virtual void ApplyWorldDataInfo(const WorldDataInfo& worldDataInfo)=0;
  REMOTE virtual void ApplyWorldDataPart(const rpc::MemoryBlock& worldDataPart)=0;
};

class RIGameClient;
class RIGameClientReconnect;

REMOTE struct IGameServer : public rpc::IRemoteEntity
{
  RPC_ID();

  NI_DECLARE_CLASS_1( IGameServer, rpc::IRemoteEntity );

  REMOTE virtual void AddClient(const char* name, uint clientId, const Login::ClientVersion& clientVersion, NI_LPTR IGameClient* _client)=0;
  REMOTE virtual void AddClientFast(int clientId, int clientIndex, NI_LPTR IGameClient* _client, int fromStep)=0;

  REMOTE virtual void SendCommand(int clientIndex, const rpc::MemoryBlock& command, bool isPlayerCommand)=0;
  REMOTE virtual void OnFinishStep(int clientIndex, uint step, uint worldCrc)=0;
  REMOTE virtual void OnClientReady(int clientIndex)=0;
  REMOTE virtual void SetTimeScale(int clientIndex, float scale)=0;
  REMOTE virtual SHybridPongResult& Ping( SHybridPongResult& time_step ){ return time_step; }
  REMOTE virtual void OnGameFinish(int clientIndex, int step, const StatisticService::RPC::SessionClientResults & finishInfo)=0;
  REMOTE virtual void RequestWorldData(int clientIndex)=0;
  REMOTE virtual bool OnGameLeave(int clientIndex) { return true; }
  REMOTE virtual void SendCrcData(int clientIndex, int step, const rpc::MemoryBlock& crcData)=0;
  REMOTE virtual void OnDisconnectAck(int clientIndex)=0;
  REMOTE virtual void DispatchPlaySameTeamDecision(int clientIndex, const bool agreed) = 0;
  REMOTE virtual void DispatchBadBehaviourComplaint(int clientIndex, const Transport::TClientId reportedClientId, const int reportItemId) = 0;
  REMOTE virtual void OnProtectionError(int clientIndex) = 0;
  REMOTE virtual void SendProtectionMagic(int clientIndex, int step, uint magic) = 0;
};



REMOTE struct IGameServerInternal : public rpc::IRemoteEntity
{
  RPC_ID();

  NI_DECLARE_CLASS_1( IGameServerInternal, rpc::IRemoteEntity );

  REMOTE virtual bool OnRejoinClient( uint clientId ) { return false; }
  REMOTE virtual void AddSpectator( uint clientId, const wstring& nickname )=0;
  REMOTE virtual void UserLeftTheGameInCastle( uint clientId ) = 0;
};


REMOTE struct IGameServerReconnect : public rpc::IRemoteEntity
{
  RPC_ID();
  NI_DECLARE_CLASS_1( IGameServerReconnect, rpc::IRemoteEntity );

  REMOTE virtual void SendWorldDataInfo(int clientIndex, const WorldDataInfo& worldDataInfo)=0;
  REMOTE virtual void SendWorldDataPart(int clientIndex, const rpc::MemoryBlock& worldDataPart)=0;
  REMOTE virtual void SetGameClientReconnect(int clientIndex, IGameClientReconnect * gameClientReconnect)=0;
};

struct IWorld
{
  virtual void AddEntity(BriefEntityInfo& info, const rpc::MemoryBlock& data)=0;
};

struct ICommandsHandler : IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(ICommandsHandler, IBaseInterfaceMT);
  virtual void OnCreate(IWorld*)=0;
  virtual void OnAddClient(int clientIndex, IGameClient* client, IWorld* )=0;
  virtual void OnRemoveClient(int clientIndex, int clientId, IGameClient* client, IWorld*)=0;
  virtual bool CheckCommand(IGameClient* client, const rpc::MemoryBlock& command, IWorld*)=0;
};

} //namespace Peered

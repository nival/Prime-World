#ifndef PEEREDTYPES_H_INCLUDED
#define PEEREDTYPES_H_INCLUDED

#include "Server/RPC/RPC.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "Server/LiveMMaking/LiveMMakingTypes.h"
#include "Core/GameTypes.h"

namespace Peered
{


typedef long long TSessionId;


enum Status
{
  Connecting                          = 0,
  Ready                               = 1,
  Active                              = 2,
  Away                                = 3,
  DisconnectedByClient                = 4,
  DisconnectedByServer                = 5,
  ConnectionTimedOut                  = 6,
  DisconnectedByCheatAttempt          = 7,
  DisconnectedByClientIntentionally   = 8,
  ConnectionTimedOutOnReconnect       = 9,
  DisconnectedByAsync                 = 10,
  RefusedToReconnect                  = 11,
  ForceDWORD                          = 0xFFFFFFFF,
};


inline bool IsDisconnectedStatus(int status)
{
  switch (status)
  {
  case DisconnectedByClient:
  case DisconnectedByClientIntentionally:
  case DisconnectedByServer:
  case DisconnectedByCheatAttempt:
  case ConnectionTimedOut:
  case ConnectionTimedOutOnReconnect:
  case DisconnectedByAsync:
  case RefusedToReconnect:
    return true;
  default:
    return false;
  }
}

inline bool IsConnectedStatus(int status)
{
  switch (status)
  {
  case Active:
  case Connecting:
  case Ready:
  case Away:
    return true;
  default:
    return false;
  }
}

inline bool IsPlayingStatus(int status)
{
  switch (status)
  {
  case Active:
  case Away:
    return true;
  default:
    return false;
  }
}


//WARNING: this enum is shared with statistics
namespace EGameFinishClientState
{
  enum Enum
  {
    NotConnected,  // Client was not connected to the game session
    FinishedGame,  // Client was connected and finished game session
    Disconnected,  // Client was disconnected before game finish
  };
}


struct SInstanceId : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  string    serviceId;
  string    instanceId;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&serviceId); f.Add(3,&instanceId); return 0; }

  bool Valid() const { return !serviceId.empty() && !instanceId.empty(); }
  void Clear() { serviceId.clear(); instanceId.clear(); }

  SInstanceId() {}
};



struct BriefEntityInfo
{
  uint id;
  uint crc;
};


struct SAuxUserData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  Transport::TClientId    clientId;
  lobby::ETeam::Enum      faction;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&faction); return 0; }

  SAuxUserData() : clientId( 0 ), faction( lobby::ETeam::None ) {}

  SAuxUserData( Transport::TClientId _clientId, lobby::ETeam::Enum _faction ) :
  clientId( _clientId ), faction( _faction ) {}
};


struct SAuxData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  lobby::EGameType::Enum  lobbyGameType;
  NDb::EMapType           mapType;
  mmaking::EBasket::Enum  mmBasket;
  lobby::TSocialGameId    socialLobbyGameId;
  bool                    hadPreGameLobby;
  bool                    customGame;
  nstl::string            mapDesc;      // AdvMapDesc DBID supposed
  lobby::GameGuildData    guildData;
  lobby::ETypeOfSession::Enum     sessiontype;
  vector<SAuxUserData>    users;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&lobbyGameType); f.Add(3,&mapType); f.Add(4,&mmBasket); f.Add(5,&socialLobbyGameId); f.Add(6,&hadPreGameLobby); f.Add(7,&customGame); f.Add(8,&mapDesc); f.Add(9,&guildData); f.Add(10,&sessiontype); f.Add(11,&users); return 0; }

  SAuxData() :
  lobbyGameType( lobby::EGameType::None ),
  mapType( (NDb::EMapType)0 ),
  mmBasket( mmaking::EBasket::Undefined ),
  socialLobbyGameId( 0 ),
  hadPreGameLobby( false ),
  customGame( false ),
  sessiontype( lobby::ETypeOfSession::SESSIONTYPE_USUALBATTLE )
  {}
};


struct SClientStatistics : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  Transport::TClientId      clientId; //FIXME: в принципе, это поле здесь не нужно; Надо бы попробовать избавится от него
  EGameFinishClientState::Enum  clientState;
  uint                      totalAfkSeconds; 
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&clientState); f.Add(4,&totalAfkSeconds); return 0; }

  SClientStatistics() : clientId(0), clientState(EGameFinishClientState::NotConnected), totalAfkSeconds(0) {}

  SClientStatistics( Transport::TClientId _clientId, EGameFinishClientState::Enum _clientState, uint _totalAfkSeconds ) :
  clientId(_clientId), clientState(_clientState), totalAfkSeconds(_totalAfkSeconds) {}
};


struct ClientInfo : rpc::Data
{
  SERIALIZE_ID();
  ZDATA
  ZNOPARENT( rpc::Data )
  Transport::TClientId  clientId;
  NCore::PlayerInfo     info;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&info); return 0; }

  ClientInfo() : clientId( 0 ) {}
  ClientInfo( Transport::TClientId _clId, const NCore::PlayerInfo & _info ) : clientId( _clId ), info( _info ) {}
};


struct ClientStartInfo : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  int index;
  TSessionId serverId;
  nstl::vector<Peered::ClientInfo> clientsInfos;
  int confirmFrequency;
  int snapshotChunkSize;
  bool isReconnecting;
  int snapshotSendPerStep;
  int stepsDelayMin;
  int stepsDelayMax;
  int stepsDelayFrame;
  bool crcDataRequestsEnabled;
  bool fastReconnectEnabled;
  NCore::ClientSettings clientSettings;
  int simulationStep;
  int protectionMagicConfirmFrequency;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&index); f.Add(3,&serverId); f.Add(4,&clientsInfos); f.Add(5,&confirmFrequency); f.Add(6,&snapshotChunkSize); f.Add(7,&isReconnecting); f.Add(8,&snapshotSendPerStep); f.Add(9,&stepsDelayMin); f.Add(10,&stepsDelayMax); f.Add(11,&stepsDelayFrame); f.Add(12,&crcDataRequestsEnabled); f.Add(13,&fastReconnectEnabled); f.Add(14,&clientSettings); f.Add(15,&simulationStep); f.Add(16,&protectionMagicConfirmFrequency); return 0; }

  ClientStartInfo()
    : index(0)
    , serverId(0)
    , confirmFrequency(0)
    , snapshotChunkSize(0)
    , isReconnecting(false)
    , snapshotSendPerStep(0)
    , stepsDelayMin(1)
    , stepsDelayMax(1)
    , stepsDelayFrame(0)
    , crcDataRequestsEnabled(0)
    , fastReconnectEnabled(0)
    , simulationStep(100)
    , protectionMagicConfirmFrequency(2)
  {}

  ClientStartInfo(
    int _index, 
    int _serverId, 
    const nstl::vector<Peered::ClientInfo> & _clientsInfos, 
    int _confirmFrequency, 
    int _snapshotChunkSize, 
    bool _isReconnecting, 
    int _snapshotSendPerStep, 
    int _stepsDelayMin, 
    int _stepsDelayMax, 
    int _stepsDelayFrame, 
    bool _crcDataRequestsEnabled, 
    bool _fastReconnectEnabled,
    int _simulationStep,
    int _protectionMagicConfirmFrequency)
    : index(_index)
    , serverId(_serverId)
    , clientsInfos(_clientsInfos)
    , confirmFrequency(_confirmFrequency)
    , snapshotChunkSize(_snapshotChunkSize)
    , isReconnecting(_isReconnecting)
    , snapshotSendPerStep(_snapshotSendPerStep)
    , stepsDelayMin(_stepsDelayMin)
    , stepsDelayMax(_stepsDelayMax)
    , stepsDelayFrame(_stepsDelayFrame)
    , crcDataRequestsEnabled(_crcDataRequestsEnabled)
    , fastReconnectEnabled(_fastReconnectEnabled)
    , simulationStep(_simulationStep)
    , protectionMagicConfirmFrequency(_protectionMagicConfirmFrequency)
  {}
};



struct SAllocationParams : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  uint                    allocid;
  TSessionId              sessionId;
  vector<ClientInfo>      clientsInfo;
  SAuxData                auxData;
  lobby::SGameParameters  gameParams;
  lobby::TGameLineUp      gameLineUp;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&allocid); f.Add(3,&sessionId); f.Add(4,&clientsInfo); f.Add(5,&auxData); f.Add(6,&gameParams); f.Add(7,&gameLineUp); return 0; }

  SAllocationParams() :
  allocid( 0 ),
  sessionId( 0 )
  {}
};


struct BriefClientInfo
{
  uint clientId;
  Status status;
  int step;
};


struct GapInfo
{
  uint clientId;
  uint confirmedStepsGap;
};


struct ClientStepData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT( rpc::Data )
  int step;
  nstl::vector<rpc::MemoryBlock> commands;
  nstl::vector<BriefClientInfo> statuses;
  nstl::vector<GapInfo> clientGaps;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&step); f.Add(3,&commands); f.Add(4,&statuses); f.Add(5,&clientGaps); return 0; }

  ClientStepData() : step(NCore::INVALID_STEP) {}
};

struct SpectatorInfo : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)

  Transport::TClientId clientId;
  wstring nickname;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&nickname); return 0; }

  SpectatorInfo()
    : clientId(0)
    , nickname()
  {

  }

  SpectatorInfo(const Transport::TClientId clientId, const wstring& nickname)
    : clientId(clientId)
    , nickname(nickname)
  {

  }
};

} //namespace Peered

#endif //PEEREDTYPES_H_INCLUDED

#ifndef LOBBYGAMESESSION_H_INCLUDED
#define LOBBYGAMESESSION_H_INCLUDED

#include "RPC/RPC.h"
#include "System/Thread.h"
#include "Server/LiveMMaking/LiveMMakingTypes.h"
#include "System/HPTimer.h"
#include "Server/LobbyPvx/ISessionHybridLink.h"
#include "Server/GameSession/GameBalancer/GameBalancerIface.h"
#include "Server/LobbySocial/SocialLobbyTypes.h"
#include "CommonTypes.h"
#include "LobbySocUserPrepare.h"
#include "LobbyConfig.h"
#include "System/EnumToString.h"
#include <map>
#include "Server/GameChatController/IGameChatController.h"

namespace NRandom
{
  class RandomGenerator;
}

namespace Transport
{
  _interface IChannel;
}

namespace GameBalancer
{
  class RIBalancer;
}


namespace Peered
{
  class RIGameServer;
  class RIGameServerInternal;
}


namespace mmaking
{
  class IHeroesTable;
}

namespace NWorld
{
  class PFResourcesCollection;
} // NWorld


namespace StatisticService
{
  class GameStatClient;

  namespace RPC
  {
    struct SessionClientResults;
  }
}

namespace lobby
{

namespace EGameState
{
  enum Enum
  {
    Empty,
    WaitingGameServer, //Waiting for hybrid server instance to be created and recieved
    WaitingLogSessionStartAck,
    InGame,
  };

  NI_ENUM_DECL_STD;
}


class ServerConnection;
class CustomGame;


class IGameSessionOwner : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IGameSessionOwner, IBaseInterfaceMT );

  virtual const mmaking::IHeroesTable * CustomGameHeroes() const = 0;
  virtual ISessionHybridLink * GameServerLink() const = 0;
  virtual void StartPreparingPvx( const SSocialUserPrepare & data ) = 0;
  virtual void SocialGameAborted( TGameId _gameId ) = 0;
  virtual Network::NetAddress GetSvcAddress( const Transport::TServiceId & _serviceId ) = 0;
};


typedef std::map<uint, std::string>  THeroIdMap;


class GameSession : public GameBalancer::IBalancerCallback, public gamechat::IOpenGameChatCallback, public HybridServer::IGameServerDispenserCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS( GameSession )
    NI_DECLARE_BASE( GameBalancer::IBalancerCallback )
    NI_DECLARE_BASE( gamechat::IOpenGameChatCallback )
    NI_DECLARE_BASE( HybridServer::IGameServerDispenserCallback )
    NI_DECLARE_BASE( BaseObjectMT )
  NI_DECLARE_END;

public:
  GameSession( IConfigProvider * _cfg, TGameId _gameId, const SGameParameters & _params, timer::Time _now,
      IGameSessionOwner * _owner,
      GameBalancer::RIBalancer * _gameBalancer,
      gamechat::IGameChatController * _chatControl,
      StatisticService::GameStatClient * _statistics );

  ~GameSession();

  void Poll( timer::Time now );

  EGameState::Enum State() const { return state; }

  TGameId Id() const { return gameId; }
  const string & StrId() const { return strGameId; }

  const SGameParameters & Params() const { return params; }

  timer::Time LastPlayerDisconnectTime() const { return lastDisconnectTime; }

  bool CanBeRemoved( timer::Time _now ) const;

  void SetupSocialMMaking( const mmaking::SGame & _game, const socialLobby::PvxGameDetails & _gameDetails, const string & _svcPath, const THeroIdMap & _heroIdMap );
  void SetupFromCustomGame( CustomGame * _customGame );
  EOperationResult::Enum ReconnectToCustomGame( ServerConnection * player );
  EOperationResult::Enum SpectateCustomGame( ServerConnection * player );
  EOperationResult::Enum AddPlayerToSocialGame( ServerConnection * player );
  void PlayerReconnects( socialLobby::TUserIdPvX clientid );
  void SpectatorReconnects( socialLobby::TUserIdPvX clientid, const string & login, const wstring& nickname );
  void OnRejoinClientAnswer( bool result );
  void UserLeftFromCastle( socialLobby::TUserIdPvX _userId );

  void AddToChatControl( Transport::TClientId clientId, ETeam::Enum team );

  void StartPreparingPvx( socialLobby::TUserIdPvX pvxUserId, const char * spectatorLogin );

  //Mirror of ISessionHybridLink
  void OnGameFinish( EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _info, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics );
  void OnGameCheated( uint _clientId, ECheatType::Enum _cheatType, const char * _clientIp ) { /*Nothing to do*/ }

  void Dump();

  NDb::EMapType GetMMGameType() { return socialGameData.mapType; }

private:
  void PollGSConnection( NHPTimer::FTime now );
  void ServeGameServer( const char * _balancerSvcPath );
  void SetupAuxGameServerData( Peered::SAuxData & gsAuxData );

  void OnAllocateGameSvcResult( int _result, int, rpc::CallStatus _st );

  //IBalancerCallback
  void OnGameSvcAllocated( Peered::TSessionId userctx, uint allocid, HybridServer::IGameServerDispenser * gs );

  //  gamechat::IOpenGameChatCallback
  void OnOpenSessionChat(gamechat::GameSessionId const & _gameid, int _rc);

  //HybridServer::IGameServerDispenserCallback
  void GameServerAllocated( Peered::RIGameServer * _clientsInterface, Peered::RIGameServerInternal * _internalInterface, const Peered::SInstanceId& _instId );

  void BeginNotifyStatistics();
  void OnStatisticsSessionNotify( bool _result );

  void Start();
  StrongMT<IGameSessionOwner> LockOwnerForSocialFeedback();
  void Cleanup();
  void AbortSocialGame();

#if defined( NV_WIN_PLATFORM )
  static __time32_t Timestamp();
#elif defined( NV_LINUX_PLATFORM )
  static nival::uint32_t Timestamp();
#endif

  StrongMT<IConfigProvider>       config;
  EGameState::Enum                state;
  TGameId                         gameId;
  string                          strGameId;
  TGameLineUp                     lineup;

  StrongMT<CustomGame>            customGame;

  SGameParameters                 params;
  mmaking::SGame                  socialGameData;
  socialLobby::PvxGameDetails     socialGameDetails;

  vector<Peered::ClientInfo>      gameServerData;

  set<socialLobby::TUserIdPvX>    spectators;

  WeakMT<IGameSessionOwner>       owner;

  StrongMT<GameBalancer::RIBalancer> gameSrvBalancer;
  StrongMT<Peered::RIGameServer>   gameServer;
  StrongMT<Peered::RIGameServerInternal> gameServerInternal;
  Peered::SInstanceId             gameSvcInstId;

  timer::Time                     asyncOpStartedTime;
  timer::Time                     lastDisconnectTime;

  StrongMT<gamechat::IGameChatController> chatControl;

  StrongMT<StatisticService::GameStatClient> statistics;

  timer::Time                     gameServerLostTime;

  struct SBotInfo
  {
    ETeam::Enum   team;
    string        hero;
    SBotInfo() : team( ETeam::None ) {}
    SBotInfo( ETeam::Enum _team, const string & _hero ) : team( _team ), hero( _hero ) {}
  };

  vector<SBotInfo>                botsToAdd;
};

} //namespace lobby

#endif //#LOBBYGAMESESSION_H_INCLUDED

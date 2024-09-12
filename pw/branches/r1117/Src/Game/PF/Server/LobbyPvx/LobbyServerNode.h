#ifndef NEWLOBBYSERVICE_H_INCLUDED
#define NEWLOBBYSERVICE_H_INCLUDED

#include "RPC/RPC.h"
#include "RPC/GateKeeper.h"
#include "RPC/IfaceRequester.h"
#include "Server/RPC/LocalEntityFactory.h"
#include "System/DebugVar.h"
#include "ServerAppBase/NivalService.h"

//#include "ZZima/BillingProcessor.h"
#include "LobbyConfig.h"
#include "LobbyGameSession.h"

#include "System/JobThread.h"
#include "System/RandomGenerator.h"

#include "Monitoring/PerfCounterProvider/PerfCounterProvider.h"
#include "UserManagerAgent/UserManagerAgent.h"
#include "Server/LobbySocial/ISocialLobbyPvxSvc.h"
#include <list>
#include <map>

namespace Billing
{
  _interface IBillingProcessor;
}

namespace gamechat
{
  class GameChatController;
}

namespace socialLobby
{
  class RIPvxInterface;
}


namespace mmaking
{
  class IHeroesTable;

  class RILiveMMakingNode;
  class RILiveMMaking;
}


namespace NWorld
{
  class PFResourcesCollection;
};


namespace StatisticService
{
  class GameStatClient;
}


namespace lobby
{

class Entrance;
class ServerConnection;
class GameSession;
class CustomGame;
class ISessionLoginWrapper;
class SocialLobbyProxy;
class SocialPvxInterface;

class RIServerInstance;
class RILobbyUser;


class ServerNode : public IGameSessionOwner, public Transport::BaseService
{
  NI_DECLARE_REFCOUNT_CLASS_2( ServerNode, IGameSessionOwner, Transport::BaseService );

public:
  typedef std::map<TGameId, StrongMT<GameSession> >  TGames;
  typedef std::map<TGameId, StrongMT<CustomGame> >  TCustomGames;

  ServerNode( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams );

  ~ServerNode();

  virtual void OnConfigReload();

  RIServerInstance * AddClient( RILobbyUser * user, int clientRevision );

  StrongMT<CustomGame> CreateCustomGame( const SGameParameters & _params, int autostartPlayers );
  void InsertGame( GameSession * _game );
  void InsertCustomGame( CustomGame * _game );

  EOperationResult::Enum JoinSocialGame( ServerConnection * connection );
  const TGames & Games() const { return games; }
  const TCustomGames & CustomGames() const { return customGames; }

  int GetGameRandom();

  //Mirror of ISessionHybridLink
  void OnGameFinish( Peered::TSessionId _sessionId, EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _info, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics );
  void OnGameCheated( Peered::TSessionId _sessionId, Transport::TClientId _clientId, ECheatType::Enum _cheatType, const char * _clientIp );
  void OnChangeClientStatus( Peered::TSessionId _sessionId, const nstl::vector<Peered::BriefClientInfo> & _clientInfos );

  //Mirror of socialLobby::IPvxSvc
  void NewGame( TSocialGameId _gameId, const mmaking::SGame & _game, const socialLobby::PvxGameDetails & _gameDetails );
  void NewReconnectingUser( TSocialGameId _gameId, socialLobby::TUserIdPvX _userId );
  void NewSpectator( TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, const string & _login, const wstring& nickname );
  void UserLeftTheGameInCastle( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId );

protected:
  //Transport::BaseService
  virtual void Poll( timer::Time _now );

  //rpc::IGateKeeperCallback
  virtual void OnNewNode( Transport::IChannel * channel, rpc::Node * node );
  virtual void OnChannelClosed( Transport::IChannel * channel, rpc::Node * node );
  virtual void OnCorruptData( Transport::IChannel * channel, rpc::Node * node );

  //IGameSessionOwner
  virtual const mmaking::IHeroesTable * CustomGameHeroes() const { return customGameHeroes; }
  virtual ISessionHybridLink * GameServerLink() const { return gameServerLink; }
  virtual void StartPreparingPvx( const SSocialUserPrepare & data );
  virtual void SocialGameAborted( TGameId _gameId );
  virtual Network::NetAddress GetSvcAddress( const Transport::TServiceId & _serviceId );

private:
  typedef std::map<Transport::TClientId, StrongMT<ServerConnection> > TConnections;
  typedef std::map<Transport::TClientId, WeakMT<GameSession> >  TSocialPlayerGames;
  typedef std::list<StrongMT<SocUserPrepareItem> >  TSocUserPrepareLine;

  StrongMT<IConfigProvider>         config;

  StrongMT<Transport::ITransportSystem> extClusterTransport;
  StrongMT<Transport::IAddressTranslator> extClusterAddrTranslator;
  StrongMT<rpc::GateKeeper>         extClusterGateKeeper;
  ScopedPtr<rpc::LocalEntityFactory> extClusterRpcFactory;
  StrongMT<Entrance>                entrance;
  StrongMT<ISessionHybridLink>      gameServerLink;

  StrongMT<SocialLobbyProxy>        socialLobbyProxy;
  StrongMT<SocialPvxInterface>      socialPvxInterface;

  StrongMT<rpc::IfaceRequester<GameBalancer::RIBalancer> > gameSrvBalancer;

  TConnections                      connections;
  TGames                            games;
  TCustomGames                      customGames;
  TGameId                           nextCustomGameId;
  TSocialPlayerGames                socialPlayers;
  TSocUserPrepareLine               socialUsersToPrepare;
  NDebug::DebugVar<int>             clientsCounter;

  timer::Time                       now;
  NRandom::RandomGenerator          random;
  timer::Ticks                      startTicks;

  StrongMT<gamechat::GameChatController> chatControl;

  StrongMT<mmaking::IHeroesTable>   customGameHeroes;

  StrongMT<ISessionLoginWrapper>    loginSvcAgent;

  timer::Time                       nextSocCleanup;

  StrongMT<StatisticService::GameStatClient> statistics;

  timer::Time                       nextStatusDump, nextFatStatusDump;

  THeroIdMap                        heroIdMap;

  StrongMT<UserManager::IUserManagerAgent>  userManagerAgent;

  void LoadHeroes();
  void GetClientUsername( Transport::TClientId userId, wstring & username );
  StrongMT<ServerConnection> NewConnection( Transport::TClientId clientId );
  TConnections::iterator GetConnectionForChannel( Transport::IChannel * channel, bool createIfNeeded );
  ServerConnection * FindConnection( Transport::TClientId clientId );
  void CloseConnection( ServerNode::TConnections::iterator it );

  void PollGames();
  void PollCustomGames();
  void PollSocPreparation();

  void PollChatChannels();
  GameSession * NewGameSession( TGameId id, const SGameParameters & params );
  void StartCustomGame( CustomGame * game );
  void CleanupSocialLists();
  GameSession * FindGame( TGameId _gameId );
  void LogGameFinish( Peered::TSessionId _sessionId, EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _info, const nstl::vector<Peered::SClientStatistics> & _clientsStatistics );
  int CountActiveConnections();
  void StatusDump();
  void CreateExtClusterTransport();
};

} //namespace lobby

#endif //NEWLOBBYSERVICE_H_INCLUDED

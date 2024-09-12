#ifndef LOBBYSERVERCONNECTION_H_INCLUDED
#define LOBBYSERVERCONNECTION_H_INCLUDED

#include "LobbyIServerInstance.h"
#include "LobbyConfig.h"

namespace lobby
{


class ServerNode;
class RILobbyUser;
//class GameSession;
class CustomGame;


namespace EConnectionStatus
{
  enum Enum {
    New,
    Established
  };
};



class ServerConnection : public IServerInstance, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( ServerConnection, IServerInstance, BaseObjectMT );

public:
  ServerConnection( IConfigProvider * _cfg, ServerNode * _server, Transport::TClientId _clientId );

  EConnectionStatus::Enum Status() const { return status; }
  Transport::TClientId ClientId() const { return clientId; }
  int ClientRevision() const { return clientRevision; }

  void JustConnected( StrongMT<rpc::Node> const & _node );
  void Established( RILobbyUser * _user, int _clientRevision );
  void Disconnected( NHPTimer::FTime now ); //Returns true to approve object destruction

  void SetCustomGame( CustomGame * _game );
  StrongMT<CustomGame> GetCustomGame();

  void SetUserInfo( const SUserInfo & info ) { userInfo = info; }
  const SUserInfo & UserInfo() const { return userInfo; }

  RILobbyUser * RemoteUser() const { return user; }
  void ForgetRemoteUser() { user = 0; }

protected:
  //IServerInstance
  virtual void SetDeveloperSex( int /*ESex::Enum*/ _sex );
  virtual void RequestGamesList();
  virtual EOperationResult::Enum JoinGame( int gameId );
  virtual EOperationResult::Enum ReconnectToCustomGame( int gameId, /*ETeam::Enum*/ int team, const string & heroId );
  virtual EOperationResult::Enum CreateCustomGame( int maxPlayers, int maxPlayersPerTeam, const string & mapId, int autostartPlayers );
  virtual EOperationResult::Enum SpectateCustomGame( int gameId );
  virtual void ChangeCustomGameSettings( /*ETeam::Enum*/ int team, /*ETeam::Enum*/ int faction, const string & heroId );
  virtual void SetReady( /*EGameMemberReadiness::Enum*/ int readiness );
  virtual EOperationResult::Enum JoinSocialGame();
  virtual void SetDeveloperParty( int party );

private:
  StrongMT<IConfigProvider> config;
  EConnectionStatus::Enum status;
  WeakMT<ServerNode>      server;
  Transport::TClientId    clientId;
  StrongMT<RILobbyUser>   user;
  WeakMT<CustomGame>      game;

  SUserInfo               userInfo;
  int                     clientRevision;
};

} //namespace lobby

#endif //LOBBYSERVERCONNECTION_H_INCLUDED

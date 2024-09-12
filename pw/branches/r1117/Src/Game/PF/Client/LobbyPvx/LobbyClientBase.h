#ifndef NEW_LOBBYCLIENTBASE_H_INCLUDED
#define NEW_LOBBYCLIENTBASE_H_INCLUDED

#include "RPC/RPC.h"
#include "RPC/GateKeeper.h"
#include "LobbyClientInterface.h"
#include "ClientAccountingGadget.h"
#include <RPC/IfaceRequester.h>


namespace rpc
{
  class GateKeeperClient;
  struct LocalEntityFactory;
  class Node;
}


namespace Lobby
{
  class RLobbyAccounting;
}


namespace lobby
{

class RIEntrance;
class RIServerInstance;



namespace EClientStatus
{
  enum Enum
  {
    Initial, 
    Error,
    Disconnected,
    WaitingEntrance,
    RequestingServerInstance,
    WaitingAccounting,
    Connected,
    InCustomLobby,
    ConnectingToGameSvc,
    InGameSession,
    GameFinished,
    LeavingServer
  };
}


namespace EClientError
{
  enum Enum
  {
    NoError,
    PrematureDisconnect,
    DataCorruption,
    ServiceTimeOut,
    ProtocolViolation,
    ServiceDenial
  };
}



_interface IClientNotify : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IClientNotify, IBaseInterfaceMT )

  virtual void OnStatusChange( EClientStatus::Enum oldStatus, EClientStatus::Enum newStatus ) = 0;
  virtual void OnLobbyDataChange() = 0;
};



class ClientBase : public ILobbyUser, public rpc::IGateKeeperCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( ClientBase, ILobbyUser, rpc::IGateKeeperCallback, BaseObjectMT );

public:
  typedef set<int>  TReadyPlayers;

  ClientBase( Transport::TClientId _clientId, bool _inSocialMode );
  ~ClientBase();

  void CleanUpRpcCyclicLinks();

  bool                      InSocialMode() const { return inSocialMode; }
  EClientStatus::Enum       Status() const { return status; }
  EClientError::Enum        ErrorCode() const { return errorCode; }
  EOperationResult::Enum    LastLobbyOperationResult() const { return lastLobbyOperationResult; }

  Transport::TClientId      ClientId() const { return clientId; }

  rpc::LocalEntityFactory * RpcFactory() const { return ::Get( rpcFactory ); }
  RIServerInstance *        LobbyServer() { return serverInst; }

  void                      PopGameList( TDevGamesList & buffer ) { buffer.clear(); buffer.swap( gamesList ); }
  const SGameParameters &   GameParams() const { return gameParams; }
  const TGameLineUp &       GameLineup() const { return gameLineUp; }
  const TReadyPlayers &     ReadyPlayers() const { return gameMembersReadiness; }
  TGameId                   GameSessionId() const { return gameSessionId; }

  Peered::RIGameServer *    GameServer() { return gameServer; }

  timer::Time               Now() const { return now; }

  __time32_t                ServerTimestamp() const { return serverTimestamp; }

  void SetNotify( IClientNotify * _notify ) { notify = _notify; } //TODO: implement multiple callbacks

  void Start( rpc::GateKeeperClient * _kateKeeper, const Transport::TServiceId & _fullLobbySvcId );
  void Poll();

  void LeaveGame(int clientIndex);

  void SetDeveloperSex( ESex::Enum _sex );
  void RefreshGamesList();
  void CreateGame( const char * mapId, int maxPlayers, int maxPlayersPerTeam, int autostartPlayers = -1 );
  void JoinGame( int gameId );
  void ReconnectGame( int gameId, int team, const string& heroId );
  void SpectateGame( int gameId );
  void ChangeCustomGameSettings( ETeam::Enum team, ETeam::Enum faction, const string & heroId );
  void SetReady( EGameMemberReadiness::Enum readiness );
  void SetDeveloperParty( int party );

  int GetTimeDelta() const { return timeDelta; };

protected:
  //rpc::IGateKeeperCallback
  virtual void OnNewNode( Transport::IChannel * channel, rpc::Node * node ) {}
  virtual void OnChannelClosed( Transport::IChannel * channel, rpc::Node * node );
  virtual void OnCorruptData( Transport::IChannel * channel, rpc::Node * node );

  friend class LobbyUserProxy;
  //ILobbyUser
  virtual void AddGameInfo( const SDevGameInfo & info );
  virtual void JoinCustomSession( const SGameParameters & params );
  virtual void UpdateClientStatus( /*EOperationResult::Enum*/ int status );

  virtual void AddCustomGameMember( const SGameMember & member );
  virtual void RemoveCustomGameMember( int userId );
  virtual void UpdateCustomGameMember( int userId, const SPlayerGameContext & params );
  virtual void UpdateCustomGameMemberReadiness( int userId, bool ready );

  virtual void StartSession( TGameId _sessionId, const SGameParameters & _params, const TGameLineUp & _gameLineUp, Peered::RIGameServer * _gameServerInstance, const Peered::SInstanceId & _gsInstId, unsigned timestamp32 );

  virtual void Award( const vector<roll::SAwardInfo> & _awards ) {}

  //Overridables
  virtual void OnStatusChange( EClientStatus::Enum newStatus );
  virtual void OnLobbyDataChange();

private:
  bool                            inSocialMode;
  EClientStatus::Enum             status;
  EClientError::Enum              errorCode;
  EOperationResult::Enum          lastLobbyOperationResult;

  Transport::TClientId            clientId;
  StrongMT<rpc::GateKeeperClient> gateKeeper;
  ScopedPtr<rpc::LocalEntityFactory> rpcFactory;
  WeakMT<IClientNotify>           notify;

  StrongMT<LobbyUserProxy>        lobbyUserProxy;
  StrongMT<rpc::IfaceRequester<RIEntrance>> entrance;
  StrongMT<RIServerInstance>      serverInst;

  timer::Time                     now;
  timer::Time                     statusTimeLimit;

  TDevGamesList                   gamesList;

  TGameId                         gameSessionId;
  SGameParameters                 gameParams;
  TGameLineUp                     gameLineUp;
  TReadyPlayers                   gameMembersReadiness;

  __time32_t                      serverTimestamp;
  int                             timeDelta;

  StrongMT<rpc::IfaceRequester<Peered::RIGameServer>> gameServerRequester; //RDP transport mode mode
  StrongMT<Peered::RIGameServer>  gameServer; //TCP/IP transport mode
  Peered::SInstanceId             gameSvcInstId;

  int                             leaveAckCounter;

  void OnEntrance();
  void OnGetServerInstance( RIServerInstance * svInst );
  void OnOperatioResult( EOperationResult::Enum result );
  void OnGameLeaveAnswer( bool );

  void ChangeStatus( EClientStatus::Enum newStatus );
  void SetError( EClientError::Enum code );
  void EnableStatusTimeout( float _to = 0 );
};

} //namespace lobby

#endif //NEW_LOBBYCLIENTBASE_H_INCLUDED

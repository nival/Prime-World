#ifndef GAMECONTEXT_H_FCE1B85D_782F_401F
#define GAMECONTEXT_H_FCE1B85D_782F_401F

#include "IGameContext.h"
#include "Network/ClientTransportSystemIntf.h"
#include "NewLobbyGameClientPW.h"
#include "NewLobbyClientPW.h"
#include "System/NiTimer.h"
#include "ReplayRunner.h"


namespace Network
{
  _interface INetworkDriver;
}


namespace Transport
{
  class ITransportSystem;
  _interface IChannel;
}


namespace NGameX
{
  class LoadingStatusHandler;
  _interface ISocialConnection;
}




namespace StatisticService
{
  namespace RPC
  {
    class RStatisticWriter;
    class RStatisticDebugWriter;
  }
}

namespace gamechat
{
  class IClient;
}


namespace Game
{
class NetworkStatusScreen;
class DebugVarsSender;
class LoadingScreen;


namespace EContextStatus
{
  enum Enum { Ready, Error, WaitingLogin, WaitingStatistics, WaitingLobbyClient, InGame, Cleanup };
}

namespace EGameStatStatus
{
  enum Enum;
}

class GameContext : public BaseObjectMT, public IGameContext, public lobby::IClientNotify, public rpc::IGateKeeperCallback
{
  NI_DECLARE_REFCOUNT_CLASS_4( GameContext, BaseObjectMT, IGameContextUiInterface, lobby::IClientNotify, rpc::IGateKeeperCallback )

public:
  GameContext( const char * _sessionKey, const char * _devLogin, const char * _mapId, NGameX::ISocialConnection * _socialConnection, NGameX::GuildEmblem* _guildEmblem, const bool _isSpectator, const bool _isTutorial );
  ~GameContext();

  //IGameContext
  virtual void Start();
  virtual int  Poll( float dt ); // returns number of commands in buffer
  virtual void Shutdown();
  virtual void OnAltTab(bool isActive);
  virtual StatisticService::GameStatistics * GameStatLogic() { return gameStatLogic; }

protected:
  //IGateKeeperCallback
  virtual void OnNewNode( Transport::IChannel * channel, rpc::Node * node ) {}
  virtual void OnChannelClosed( Transport::IChannel * channel, rpc::Node * node );
  virtual void OnCorruptData( Transport::IChannel * channel, rpc::Node * node );

  //IGameContextUiInterface
  virtual bool          LoginInProgress() const;
  virtual void          SetDeveloperSex( lobby::ESex::Enum _sex );
  virtual void          ConnectToCluster( const string & login, const string & password, Login::LoginType::Enum _loginType = Login::LoginType::ORDINARY );
  virtual NWorld::IMapCollection * Maps();
  virtual void          RefreshGamesList();
  virtual void          PopGameList( lobby::TDevGamesList & buffer );
  virtual lobby::EOperationResult::Enum LastLobbyOperationResult() const;
  virtual void          CreateGame( const char * mapId, int maxPlayers );
  virtual void          JoinGame( int gameId );
  virtual void          Reconnect( int gameId, int team, const string & heroId );
  virtual void          Spectate( int gameId );
  virtual void          ChangeCustomGameSettings( lobby::ETeam::Enum team, lobby::ETeam::Enum faction, const string & heroId );
  virtual void          SetReady( lobby::EGameMemberReadiness::Enum readiness );
  virtual void          SetDeveloperParty(int party);

  //lobby::IClientNotify
  virtual void OnStatusChange( lobby::EClientStatus::Enum oldStatus, lobby::EClientStatus::Enum newStatus );
  virtual void OnLobbyDataChange() {}
  
private:
  const bool                          socialMode;
  EContextStatus::Enum                status;

  StrongMT<Network::INetworkDriver>   networkDriver; 
  StrongMT<Transport::IClientTransportSystem>  clientTransportSystem;
  timer::Timer                        gameStatSetupTimer;
  StrongMT<StatisticService::GameStatClient>  gameStat;
  StrongMT<StatisticService::GameStatistics> gameStatLogic;
  StrongMT<rpc::GateKeeperClient>     gateKeeper;
  StrongMT<lobby::ClientPW>           lobbyClient;
  StrongMT<lobby::GameClientPW>       gameClient;
  Strong<DebugVarsSender>             debugVarsSender;
  Weak<ReplayRunner>                  replayRunner;

  Weak<NGameX::ISocialConnection>     socialConnection;
  Weak<NGameX::GuildEmblem>           guildEmblem;

  string                              socialLoginAddress;
  string                              socialLogin;
  string                              socialPassword;

  bool                                clientWasInitialized;
  const bool                          isSpectator;
  const bool                          isTutorial;

  Weak<LoadingScreen>                 loadingScreen;  
  Weak<NetworkStatusScreen>           networkStatusScreen;

  StrongMT<gamechat::IClient>         chatClient;

  StrongMT<lobby::FastReconnectCtxPW> fastReconnectCtx;

  string                              lastLogin;
  string                              devLogin;
  string                              mapId;    
  Weak<NGameX::LoadingStatusHandler>  loadingStatusHandler;

  StrongMT<Transport::IChannel>       inputChannel;

  void Init();
  void Cleanup();
  bool ParseSessionKey( const char * _sessKey );
  void StartFastReconnect();
  void RestartFastReconnect();
  void PollFastReconnect();
  void FastReconnectFailed();
  bool ShouldStartFastReconnect() const;
  void AcquireGameStat();
  void ReportPersistentEvents();
  void StartLobbyClient();
  void StartGameClient();
  void CreateChatClient(const nstl::wstring& nickName);
  void WaitForStatistics();
  void ContinueAfterStatistics( Game::EGameStatStatus::Enum gss );


  bool LoginOnServer( const char * name, const vector<wstring> & args );
  bool CustomGameCreate( const char * name, const vector<wstring> & args );
  bool CustomGameJoin( const char * name, const vector<wstring> & args );
  bool CustomGameReconnect( const char * name, const vector<wstring> & args );
  bool CustomGameSpectate( const char * name, const vector<wstring> & args );
  bool CustomGameSettings( const char * name, const vector<wstring> & args );
  bool CustomGameReady( const char * name, const vector<wstring> & args );
  bool LoadReplay( const char * name, const vector<wstring> & args );

  void StopAsyncMapLoadingJob();
};

} //namespace Game

#endif //#define GAMECONTEXT_H_FCE1B85D_782F_401F

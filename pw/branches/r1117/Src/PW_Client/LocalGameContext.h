#ifndef LOCALGAMECONTEXT_H_INCLUDED
#define LOCALGAMECONTEXT_H_INCLUDED

#include "IGameContext.h"
#include "System/JobThread.h"
#include "PF_GameLogic/GameControl.h"
#include "PF_GameLogic/ReplayInfo.h"



namespace NGameX
{
  class AdventureScreen;
  class PcbtMMakingScreen;
  class SelectGameModeScreen;
  class SelectHeroScreen;
  class ChatUiController;
  class IgnoreListController;
  class IgnoreListStorage;
}


namespace NWorld
{
  class MapLoadingJob;
  class MapDescriptionLoader;
  class PFResourcesCollection;
}


namespace NCore
{
  class ITransceiver;
  class ICommandScheduler;
  class ReplayWriter;
}


namespace Game
{

class LoadingScreen;
class LocalCmdScheduler;

namespace ELocalGameState
{
  enum Enum
  {
    Initial,
    InLobby,
    InCustomGame,
    ShowingLoadingScreen,
    StartingAdvScreen,
    LoadingMap,
    Playing,
    GameFinished
  };
}


class LocalGameContext : public IGameContext, public NGameX::IGameControl, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( LocalGameContext, IGameContext, NGameX::IGameControl, BaseObjectMT )

    friend class ReplayRunner;
public:
  LocalGameContext( bool _isSpectator );
  ~LocalGameContext();

  //IGameContext
  virtual void Start();
  virtual int  Poll( float dt ); // returns number of commands in buffer
  virtual void Shutdown();
  virtual void OnAltTab(bool isActive);
  virtual StatisticService::GameStatistics * GameStatLogic() { return 0; }

  virtual void SetTimeScale( float timescale );

protected:
  //IGameContextUiInterface
  virtual bool          LoginInProgress() const { return false; }
  virtual void          SetDeveloperSex( lobby::ESex::Enum _sex ) { developerSex = _sex; }
  virtual void          ConnectToCluster( const string & login, const string & password,  Login::LoginType::Enum _loginType = Login::LoginType::ORDINARY ) {}
  virtual NWorld::IMapCollection * Maps() { return mapCollection; }
  virtual void          RefreshGamesList() {}
  virtual void          PopGameList( lobby::TDevGamesList & buffer ) { buffer.clear(); }
  virtual lobby::EOperationResult::Enum LastLobbyOperationResult() const { return lobby::EOperationResult::Ok; }
  virtual void          CreateGame( const char * mapId, int maxPlayers );
  virtual void          JoinGame( int gameId ) {}
  virtual void          Reconnect( int gameId, int team, const string & heroId ) {}
  virtual void          Spectate( int gameId ) {}
  virtual void          ChangeCustomGameSettings( lobby::ETeam::Enum team, lobby::ETeam::Enum faction, const string & heroId );
  virtual void          SetReady( lobby::EGameMemberReadiness::Enum readiness );
  virtual void          SetDeveloperParty(int);

  //NGameX::IGameControl
  virtual void OnCombatScreenStarted( NCore::IWorldBase * _world, const NGameX::ReplayInfo & _replayInfo );
  virtual void OnVictory( const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo );
  virtual void LeaveGame();
  virtual bool IsGameReady();
  virtual bool IsWaitingLeaveAck() { return false; }
  virtual void DispatchPlaySameTeamDecision(const bool) {}
  virtual void DispatchBadBehaviourComplaint(const int, const int ) {}
  virtual void OnProtectionError() {}

  void OnLobbyDataChange();
  void UpdateCustomLobbyPlayers( const set<int> & hilitePlayers );
private:
  ELocalGameState::Enum             state;

  StrongMT<NWorld::IMapCollection>      mapCollection;
  StrongMT<NWorld::IMapLoader>          mapLoader;

  StrongMT<LocalCmdScheduler>       scheduler;

  Weak<NGameX::SelectGameModeScreen> lobbyScreen;
  Weak<NGameX::SelectHeroScreen>    heroScreen;

  Weak<Game::LoadingScreen>         loadingScreeen;
  Strong<NGameX::AdventureScreen>   advScreeen;
  Strong<NCore::ITransceiver>       transceiver;
  Weak<ReplayRunner>                replayRunner;
  StrongMT<NWorld::MapLoadingJob>   mapLoadingJob;
  StrongMT<threading::JobThread>    loadingThread;

  Strong<NGameX::ChatUiController>  chatController;

  int                               clientId;
  string                            mapId;
  int                               maxPlayers;
  bool                              isSpectator;

  lobby::TGameLineUp                gameLineup;
  NCore::MapStartInfo               mapStartInfo;

  typedef vector<pair<string, bool>> THeroes;
  THeroes                           heroes;

  lobby::ESex::Enum                 developerSex;
  Strong<NWorld::MapDescriptionLoader>      mapDescription;

  CObj<NWorld::PFResourcesCollection> resourceCollection;
  Strong<NGameX::IgnoreListStorage>           ignoreListStorage;
  StrongMT<NCore::ReplayWriter> replayWriter;

  void LoadHeroes();
  void GenerateLineup( int playersNumber );
  void StartGame();
  void ShowLoadingScreen();
  void LaunchGame();

  bool SetTimeScale( const char *name, const vector<wstring> &args );
  bool LoginOnServer( const char * name, const vector<wstring> & args ) { return true; }
  bool CustomGameCreate( const char * name, const vector<wstring> & args );
  bool CustomGameJoin( const char * name, const vector<wstring> & args ) { return true; }
  bool CustomGameReconnect( const char * name, const vector<wstring> & args ) { return true; }
  bool CustomGameSettings( const char * name, const vector<wstring> & args );
  bool CustomGameReady( const char * name, const vector<wstring> & args );
  bool LoadReplay( const char * name, const vector<wstring> & args );

  void StopAsyncMapLoadingJob();
  void PrepareReplayWriter();
};

} //namespace Game

#endif //LOCALGAMECONTEXT_H_INCLUDED

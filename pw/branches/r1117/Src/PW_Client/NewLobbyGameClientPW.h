#ifndef LOBBYSESSIONRUNNERPW_H_INCLUDED
#define LOBBYSESSIONRUNNERPW_H_INCLUDED

#include "Client/LobbyPvx/LobbyGameClient.h"
#include "LoadingScreenLogic.h"
#include "PF_GameLogic/GameControl.h"
#include "PF_GameLogic/ReplayInfo.h"
#include "System/JobThread.h"
namespace NGameX
{
  class AdventureScreen;
  class ChatUiController;
  class SmartChatController;
  _interface ISocialConnection;
  class GuildEmblem;
  class IgnoreListStorage;
}



namespace NWorld
{
  class MapLoadingJob;
  class SaveCompressThreadJob;
  class MapDescriptionLoader;
  class PFResourcesCollection;
}

namespace NDb
{
  struct AdvMap;
  struct AdvMapDescription;
  struct AdvMapSettings;
}


namespace Game
{
  class LoadingScreen;
  class NetworkStatusScreen;
  class DebugVarsSender;
}

namespace Chat
{
  class ChatClient;
}


namespace Peered
{
  namespace EDisconnectReason { enum Enum; }
}

namespace gamechat
{
  class IClient;
}


namespace lobby
{


namespace EMapLoading
{
  enum Enum
  {
    None,
    MainThreadLoading,
    ParallelLoading,
    MapLoaded,
    WaitForSnapshot,
    FinishLoading,
    Done
  };
}

class ClientPW;
class FastReconnectCtxPW;

class GameClientPW : public NGameX::IGameControl, public GameClient
{
  NI_DECLARE_REFCOUNT_CLASS_2( GameClientPW, NGameX::IGameControl, GameClient );

public:
  GameClientPW( ClientPW * _client, NWorld::IMapCollection * _mapCollection, Game::NetworkStatusScreen * _networkStatusScreen, FastReconnectCtxPW * _fastReconnectCtxPw, NGameX::ISocialConnection * _socialConnection, Game::LoadingScreen * _loadingScreen, NGameX::GuildEmblem* _guildEmblem, const bool _isSpectator, const bool _isTutorial );
  virtual ~GameClientPW(); 

  void SetChatClient( gamechat::IClient * chatClient );
  void SetDebugVarSender( Game::DebugVarsSender * sender ) { debugVarsSender = sender; }

  int Poll( float transceiverDeltaTime ); // returns number of commands in buffer

  void OnAltTab(bool isActive);

  Peered::EDisconnectReason::Enum GracefullDisconnectReason();

  void SetupFastReconnectCtx( FastReconnectCtxPW * ctx );

  void StopAsyncMapLoadingJob();

  void SetTimeScale(float timescale);

protected:
  //void PollClientStatusChange();
  void PollWorldRequest();
  void PollWorldData();

  virtual void ProcessAsyncStatus( NCore::ClientStatus & status );

  //GameClient
  virtual void ShowLoadingScreen();
  virtual void HideLoadingScreen();
  virtual void OnPlayerInfoLoaded();
  virtual void CreateAdventureScreen();
  virtual void SendTeam();
  virtual void StartMapLoading( NCore::IWorldBase * world );
  virtual void NotifyChatMuted();

  //NGameX::IGameControl
  virtual void OnCombatScreenStarted( NCore::IWorldBase * _world, const NGameX::ReplayInfo & _replayInfo );
  virtual void OnVictory( const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo );
  virtual void LeaveGame();
  virtual bool IsGameReady();
  virtual bool IsWaitingLeaveAck();
  virtual void DispatchPlaySameTeamDecision(const bool agreed);
  virtual void DispatchBadBehaviourComplaint(const int userId, const int reportItemId);
  virtual void OnProtectionError();

private:
  void UpdatePerPlayerProgress();
  void GetShowAllHeroes();

  void ProcessSpectatorJoin();
  void ProcessPlaySameTeamDecisions();
  void ProcessBadBehaviourComplaints();

  Weak<NGameX::AdventureScreen>     advScreeen;
  StrongMT<NWorld::MapLoadingJob>   mapLoadingJob;
  StrongMT<threading::JobThread>    loadingThread;
  EMapLoading::Enum                 mapLoadStatus;

  Weak<NGameX::ISocialConnection>   socialConnection;
  Weak<NGameX::GuildEmblem>         guildEmblem;

  Weak<Game::LoadingScreen>         loadingScreeen;
  Weak<Game::NetworkStatusScreen>   networkStatusScreen;

  StrongMT<ClientPW>                client;

  Strong<Game::DebugVarsSender>     debugVarsSender;
  
  Strong<NGameX::ChatUiController>  chatController;
  Strong<NGameX::SmartChatController> smartChatController;

  StrongMT<threading::JobThread>    saveCompressThread;
  StrongMT<NWorld::SaveCompressThreadJob> saveCompressJob;    
  int                               saveWorldStep;

  StrongMT<FastReconnectCtxPW>      fastReconnectCtxPw;
  CObj<NWorld::PFResourcesCollection> resourceCollection;
  Strong<NGameX::IgnoreListStorage>           ignoreListStorage;
  Game::TLineUpHeroesInfo  lineup_info;
  
  //Strong<NGameX::IIgnoreListController> ignoreListController;
  /* 
    при добавлении новых стронг-мемберов не забывайте прописать 
    их зануление в деструкторе в нужном порядке
  */
};  

} //namespace lobby

#endif //#define LOBBYSESSIONRUNNERPW_H_INCLUDED

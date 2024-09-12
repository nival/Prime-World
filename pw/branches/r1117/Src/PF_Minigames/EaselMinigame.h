#pragma once

#include "SingleMinigame.h"
#include "EaselScreensManager.h"

#include "DBEasel.h"

#include "Easel.h"
#include "EaselLocal.h"
#include "EaselRemote.h"

#include "../PF_GameLogic/GameMenuInterfaces.h"
#include "../PF_Core/WorldObject.h"


namespace PF_Minigames
{

// forward declaration
class Easel;
class EaselLocal;
class EaselRemote;
class EaselCommandsSender;

//////////////////////////////////////////////////////////////////////////
//
// base easel minigame interface, can be accesses only on
// original session client (same client the player plays from)
//
//////////////////////////////////////////////////////////////////////////
class EaselMinigame : public SingleMinigame, public NGameX::IGameMenuMinigameActions, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0xF467F401, EaselMinigame );

  // easel state flags
  enum EaselLocalState
  {
    STATE_DISABLED = 0,
    STATE_LOBBY,
    STATE_GAME,
    STATE_GAME_WON,
    STATE_GAME_FAILED
  };

public:
  EaselMinigame( PF_Core::IWorld* _pWorld, bool _local );

  bool StartLevelLocal( int _levelID, int _paintID );
  void StopLevelLocal();

  bool StartLevelWorld( int _levelID,int _paintID, int _seed );
  void OnWorldStopLevel();

  bool DoStep( uint _stepCount, short _inputX, short _inputY, bool _mouseLeft, bool _mouseRight );

  bool OnKeyboardEventLocal( EEaselKeyboardEvents::Enum event );
  void OnKeyboardEventCmd( EEaselKeyboardEvents::Enum event );

  void OnLevelWonLocal();
  void OnLevelFailedLocal();

  void OnRegenerateBoostsCmd( bool haveToBuy, int levelID, int seed );

  void OnTransferItemCmd( NWorld::PFBaseHero * target, int transactionId );

  void OnCheatDropCooldownsCommand();
  void OnCheatWinGameCommand();

  void InitiatePause( bool enablePause );

  void UpdateLevelAvailability();

  //ISingleMinigame
  virtual bool OnInit();
  virtual void OnPlacementChanged( const Placement& _oldPlacement, const Placement& _newPlacement );

  virtual bool Start( NWorld::PFMinigamePlace * place );
  virtual bool StartClient();
  
  virtual void Leave();

  virtual void OnStep( float deltaTime );
  virtual void Update( float deltaTime, bool gameOnPause ); 

  virtual void OnPause( bool _isPaused );

  virtual const NDb::DBID & GetDBID() const;

  virtual void PlaceUnderFogOfWar( bool underFogOfWar );

  virtual void CheatDropCooldowns();
  virtual void CheatWinGame();

  virtual void SendLeaveMinigameCommand( IWorldSessionInterface * _worldInterface );
  virtual void SendPauseMinigameCommand( IWorldSessionInterface * _worldInterface, bool enablePause );

  virtual void OnMapLoaded();

  virtual void Eject();

  //NGameX::IGameMenuMinigameActions
  virtual bool NeedToShowMinigameMenuItems();
  virtual bool OnGameMenuEscapeButton();
  virtual void OnGameMenuPopup();
  virtual void GameMenuClosed();
  virtual void AbortMinigameLevel();

public:
  // client specific methods
  Easel* GetLocalEasel() const { return localGame; }
  Easel* GetRemoteEasel() const { return remoteGame; }
  EaselScreenManager& GetScreensManager() { return screensManager; };

  EaselCommandsSender* GetCommandSender() { return sessionHatch; }

  int GetPaintID() const { return paintID; }
  int GetLevelID() const { return levelID; }

  // boosts operations ....
  bool RegenerateBoosts( bool haveToBuy, int levelID );

  void Local_StartItemTransfer( NWorld::PFBaseHero * target );
  bool Local_PopItemTransferResult( bool & isSuccessfull );

  void OnExitImmediate();

  void LogMinigameEvent( SessionEventType::EventType eventType, int param1, int param2 );

  int CalculateMaxAvailableLevel();
  int GetLevelForPaintID( int paintId );
  

  void OnAfterReset();
private:
  EaselMinigame() {}

  const NDb::DBID & GetDBID( Easel* easel ) const;

  int paintID;
  int levelID;

  // logic objects
  CObj<EaselLocal>  localGame;
  bool isLocal;

  int wonStreak;
  int failStreak;

  ZDATA_(PF_Core::WorldObjectBase)
  ZNOPARENT(SingleMinigame)
  ZNOPARENT(NGameX::IGameMenuMinigameActions)

  CObj<EaselRemote> remoteGame;
  bool remoteLevelStarted;

  CPtr<NWorld::PFEaselPlayer> player;

  ZONSERIALIZE

  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&remoteGame); f.Add(3,&remoteLevelStarted); f.Add(4,&player); OnSerialize( f ); return 0; }

  void OnSerialize( IBinSaver &f );

  // session negotiators
  CObj<EaselCommandsSender> sessionHatch;

  // state object
  EaselLocalState easelLocalState;

  int nextItemTransferId;
  set<int> pendingItemTransfers;

  typedef list< pair< int, bool > >  TCompletedItemTransfers;
  TCompletedItemTransfers completedItemTransfers;

  unsigned ejectStage;

  // screens manager
  EaselScreenManager screensManager;

  // operations
  void ShowLobbyScreen();
  bool ExitLobbyScreen(const bool force = false);

  bool LocalStopLevelImpl();
  bool StopGameImpl();

  void SendStartLevelWorldCommand( int _levelID, int _paintID, int _randomSeed );
  void SendStopLevelWorldCommand();

  // internal Step operations
  float stepReminder;   // internal step reminder

  void ProcessLocalStepFromUpdate( float _deltaTime );

  IWorldSessionInterface * GetSessionInterface();
};

int GenerateRandomSeed();   // randomisers setup

}
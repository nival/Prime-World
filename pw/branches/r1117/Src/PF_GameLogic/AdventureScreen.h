#pragma once

#include "AdventureScreenBase.h"
#include "PFUIEvent.h"
#include "UIEventHandler.h"
#include "BindsController.h"

#include "System/MainFrame.h"

#include "AdventureScreenFacets/GameOverEffect.h"
#include "ObjectSelector.h"

#include "Server/LobbyPvx/CommonTypes.h"
#include "Server/Roll/RollTypes.h"

#include "PFStatistics.h"
#include "System/StarForce/StarForce.h"
#include "PFClientVisibilityMap.h"

#include "SmartChatAntiSpam.h"

#include "DI/DI.hpp"


#define TempDebugTrace(msg) \
  if (NGlobal::GetVar( "use_temp_debug_trace", 0 ).GetInt64() != 0) \
    DebugTrace(msg);

#define EXIT_CODE_QUIT_CASTLE       "quitcastle"
#define EXIT_CODE_RETURN_TO_CASTLE  "returntocastle"

//spectator constants
const int SPECTATE_PLAYER1_IDX = 0;
const int SPECTATE_PLAYER2_IDX = 1;
const int SPECTATE_PLAYER3_IDX = 2;
const int SPECTATE_PLAYER4_IDX = 3;
const int SPECTATE_PLAYER5_IDX = 4;
const int SPECTATE_PLAYER6_IDX = 5;
const int SPECTATE_PLAYER7_IDX = 6;
const int SPECTATE_PLAYER8_IDX = 7;
const int SPECTATE_PLAYER9_IDX = 8;
const int SPECTATE_PLAYER10_IDX = 9;

namespace NScene 
{ 
  class SceneObject;
  _interface ICameraController;
  struct SCameraPosition;
}

namespace NCore 
{ 
  struct MapStartInfo;
  class WorldCommandQueue;
}

namespace StatisticService
{
  class IGameStatistics;
  class GameStatGuard;

  namespace RPC
  {
    struct SessionClientResults;
  }
}

namespace NMainLoop
{
  struct SScreenEvent;
}

namespace NGameX
{
  class ActionBar;
  class AdventureScreenLogic;
  class SessionStore;
  class Minimap;
  class ObjectsInfo2dLogic;
  class PlayerDataManager;
  class UIFlyTexts;
  class DamageBloodMask;
  class QueueSoundPlayer;
  _interface IGameControl;
  _interface IGameMenuMinigameActions;
  struct AnnouncementParams;
  class MarkersController;
  class UIBlockingController;
  _interface ISocialConnection;
  class GuildEmblem;
  class IgnoreListStorage;
  class GenericAbuseController;
  class ObjectInfoHelper;
}


namespace NActionBar
{
  class ActionBar;
};



namespace lobby
{
  namespace EGameType { enum Enum; }
}


namespace Peered { enum Status; }


namespace PF_Core
{
  class ColorModificationChannel;
}
namespace PF_Render
{
  class PostFXFader;
}
namespace NSound
{
  class AskCommands;
}


class AmbienceMap;

namespace NWorld
{
	class PFWorld;
  class PFBaseUnit;
  class PFBaseHero;
  class PFPlayer;
  class PFChest;
  class PFEaselPlayer;
  class ImpulsiveBuffsManager;
  struct HeroDamage;
  struct HeroOpponent;
  class PFHeroLocalStatistics;
  class PFFlagpole;
}

namespace NGameX
{

class ChatUiController; 
class SmartChatController; 
class Minimap;
class AdventureCameraController;
class AdvancedFreeCameraController;
class VisibilityMapClient;


struct GSClientSettings
{
  bool minigameEnabled;
  float logicParam1;
  bool showGuildEmblem;
  string shareUrl;
  bool aiForLeaversEnabled;
  int aiForLeaversThreshold;

  GSClientSettings() : minigameEnabled(true), logicParam1(0.0f), showGuildEmblem(false), shareUrl(""),
                        aiForLeaversEnabled(false), aiForLeaversThreshold(0) {}

  GSClientSettings(
    bool _minigameEnabled,
    float _logicParam1,
    bool _showGuildEmblem,
    string _shareUrl,
    bool _aiForLeaversEnabled,
    int _aiForLeaversThreshold)
    : minigameEnabled(_minigameEnabled)
    , logicParam1(_logicParam1)
    , showGuildEmblem(_showGuildEmblem)
    , shareUrl(_shareUrl)
    , aiForLeaversEnabled(_aiForLeaversEnabled)
    , aiForLeaversThreshold(_aiForLeaversThreshold)
  {}
};


  void ProcessUnitEvent( const NDb::UIEvent* pEvent, const NWorld::PFBaseUnit* pOwner );

  class AdventureScreen
    : public NGameX::AdventureScreenBase
    , public IUIEventHandler
    , public NMainFrame::ICloseApplicationHandler
    , public ISmartChatAntiSpam
    , public DI::SelfProvider<AdventureScreen>
  {
    friend class AdventureScreenLogic;

    NI_DECLARE_REFCOUNT_CLASS_4( AdventureScreen, NGameX::AdventureScreenBase, IUIEventHandler, NMainFrame::ICloseApplicationHandler, ISmartChatAntiSpam );

  public:
    enum Command
    {
      CMD_NA = -1,
      CMD_MOVE,
      CMD_STOP,
      CMD_ATTACK,
      CMD_ATTACK_AREA,
      CMD_HOLD,
      CMD_ITEM,
      CMD_TALENT_TALENT_PANEL,
      CMD_PORTAL,
      CMD_TOGGLE,
      CMD_PICKUP_OBJECT,
      CMD_SIGNAL,
      CMD_INIT_MINIGAME,
      CMD_VIEW,
      CMD_RAISEFLAG,
      CMD_INTERACT,
      CMD_LAST,
      CMD_KEEP_ALIVE,
      CMD_FORCEDWORD = 0x7FFFFFFF
    };

    enum StartBotsFilter
    {
      FilterAll,
      FilterSelf,
      FilterFriends,
      FilterHumans,
    };

  private:

		bool inited;

    bool mapLoaded;
    bool waitingLeaveAck;
    bool returnToCastle;
    bool skipTutorial;

    bool m_isShowChat;
    EPauseMode m_gamePause;

    GSClientSettings gsClientSettings;

  
    CObj<NWorld::PFWorld>          pWorld;
		Strong<AdventureScreenLogic>     pLogic;
		CObj<AdventureCameraController> pCameraController;
    CObj<AdvancedFreeCameraController> pFreeCameraController;
		CObj<NScene::IScene> pScene;     
		float rTimeDelta; 
    DWORD m_eventTimeLeft, m_resetEventTime;

    float towerDeathTimer;

    WeakMT<IGameControl>          gameControlCallback;

    ObjectSelector              objectSelector;

    CPtr<INaftaInfoProvider>    naftaInfoProvider;

    Strong<ObjectsInfo2dLogic>    objectsInfo2d;
    CObj<PlayerDataManager>     playersInfo;

    NDb::Ptr<NDb::DBUIData>     pUIData;

    CObj<VisibilityMapClient>   visibilityMap;

    CObj<DamageBloodMask>       bloodMask;

    CObj<Minimap>               minimap;
    bool                        isMinimapMoving;

    CObj<ObjectInfoHelper>      objectInfoHelper;

    lobby::EGameType::Enum   sessionType;
    ValueChangeSmoother<float>  saturationValue; 

    AutoPtr<PF_Render::PostFXFader> sceneFader;

    bool isHotkeysEnabled;
    bool isSelfCastOn;
    int blockedHotKeys;

    Weak<NGameX::ChatUiController> chatController;
    Weak<NGameX::SmartChatController> smartChatController;

    Strong<QueueSoundPlayer>    announcementSoundPlayer;
    Strong<MarkersController>   markersController;
    Weak<NGameX::IgnoreListStorage> ignoreListStorage;
    Strong<NGameX::BindsController> bindsController;

    AutoPtr<GenericAbuseController> pingAbuseController;
    AutoPtr<GenericAbuseController> smartChatAbuseController;

    NCore::ETeam::Enum leftFraction;
    bool isSpectator;
    bool isTutorial;

    struct UIPlayerStatus
    {
      int realStatus;
      bool showPresent;
    };

    typedef map<int, UIPlayerStatus> TUIPlayerStatuses;

    TUIPlayerStatuses playerStatuses;

	  bool channellingIsCancelling;
    
    enum State
    {
      STATE_NORMAL,
      STATE_TARGET
    };

		struct PickResult
		{
    public:
      PickResult();
      ~PickResult();
      PF_Core::WorldObjectBase* GetPickedPtr() const { return pickedObject.GetPtr(); }
      NScene::SceneObject  * GetScenePtr() const { return pickedSceneObject; }

      CVec3 const &GetPickedPos() const { return pickedPosition; }
      CVec3 const &GetPickedNormal() const { return pickedNormal; }
      CVec3 &PickedPos() { return pickedPosition; }
      CVec3 &PickedNormal() { return pickedNormal; }

      void SetPickedObjects(PF_Core::WorldObjectBase* pObject, NScene::SceneObject* pSceneObject);
      void SetSelectedObject(PF_Core::WorldObjectBase* pObject);
    protected:
      void addPreselectEffect();
      void removePreselectEffect();
    private:
      CVec3                       pickedPosition;
			CVec3                       pickedNormal;
			CPtr<PF_Core::WorldObjectBase> pickedObject;
			NScene::SceneObject*        pickedSceneObject;

      PF_Core::ColorModificationChannel*    pPreselectedCMC;
      CObj<PF_Core::BasicEffectAttached>    preSelectionEffect;
      Render::HDRColor                      preselectColor;
		};

		Command                               command;
    Command                               pushedCommand;
    bool                                  bCursorInScene;
    bool                                  isHotKeyDown;
		CVec2                                 vCursorPos;
		PickResult                            currentPick;
    CRay                                  cursorRay;
    CVec3                                 cursorPosOnTerrain;
    CPtr<PF_Core::WorldObjectBase>           selectedObject;
    NScene::SceneObject                   *selectedSceneObject;
		CObj<PF_Core::BasicEffectAttached>    selectionEffect;
    CObj<PF_Core::BasicEffectAttached>    selectionPickEffect;
    CObj<PF_Core::BasicEffectStandalone>  m_landEffect;
		bool         bShiftPressed;
		bool         minimapSignalKey;
    bool         bCtrlPressed;
    bool         mouse3Pressed;
    bool         m_updated;

    bool         isPlayingMinigame;

    bool         isSelectedOfSameFaction;
    bool         isPreselectedOfSameFaction;

    bool         bAdventureControlsEnabled;
    bool         bAlwaysShowCursor;
    bool         bCursorEnabled;

    bool         bCameraSwitchAttachControlled;

    int                    m_commandArguments[CMD_LAST];
    int                    m_abilityIndex;
    int                    m_talentLevel, m_talentSlot;
		CVec3					         m_targetPosition;
		CPtr<PF_Core::WorldObjectBase> m_targetObject;
    bool                   m_canExecuted;
    NDb::Ptr<NDb::AlternativeTarget> m_altTarget;
    
    bool firstCommonStep; 

    struct DirectionHintData
    {
      CVec3 targetPos;
      float maxSize;
      float minSize;
      float sizingDistance;
      bool  enabled;
      float offset;

      DirectionHintData() : targetPos(VNULL3), enabled(false), offset(0.0f) { Set(0.0f, 0.0f, 0.0f); }

      void Set(float _maxSize, float _minSize, float _sizingDistance)
      {
        maxSize         = _maxSize;
        minSize         = _minSize;
        sizingDistance  = _sizingDistance;
      }
    };

    DirectionHintData directionHintData;
   

    // for AOE etc
    float m_zoneRange;
    float m_zoneRangeMin;
    float m_zoneSize;
    NDb::EAbilityAOEVisual m_zoneType;
    unsigned m_abilityFlags;
    float m_abilityAOEHeight;
    int m_zonePassabilityCheckMode;

    //Billing system
    CObj<NWorld::ImpulsiveBuffsManager>  impulseBuffsManager;

    // Selection outline
    Render::HDRColor selectedOutlineColor;
    Render::HDRColor preselectedOutlineColor;

    //our faction
    NDb::EFaction heroFaction;

    bool isSessionStarted;
    lobby::TGameId sessionId;

    bool reviveFinished;
    bool enableAnnouncements;

    // blocking info
    Strong<UIBlockingController> uiBlockingController;
    
    // Complaints
    int                      complaintsToday;
    int                      complaintsMax;
    NCore::TComplaintInfo    complaintsInfo;

    bool isCustomSessionType;

	private:
    void CancelCommand(); // Cancel current command
    bool SetCommand(Command cmd);
    bool IsValidCommandTarget(Command cmd, CVec3 const &pos, PF_Core::WorldObjectBase const* pObj) const;
    bool IsValidCommandTarget(Command cmd, const CVec3& point) const;
    bool IsValidCommandTarget(Command cmd, const PF_Core::WorldObjectBase* object) const;
    bool SetCommandTarget(CVec3 const &pos, PF_Core::WorldObjectBase *pObj, bool bFromMinimap);

    void CheckCanExecuteCastTalent( NWorld::PFTalent* pTalent, const CVec3 & pos, NWorld::PFBaseHero * pHero );
    void CheckForTalentForExecute( const NWorld::PFTalent* pTalent, const CVec3 & pos, const NWorld::PFBaseHero * pHero, const bool bFromMinimap );
    void CheckForAbilityForExecute( const NWorld::PFAbilityData * pAbilityData, const CVec3 & pos, const NWorld::PFBaseHero * pHero, const bool bFromMinimap );
    bool InvulnerableFlagpoleReaction( NWorld::PFFlagpole* pFlagpole, NDb::EFaction faction );

    bool AdventureScreen::CastLimitationsHandler( const NWorld::PFAbilityData* pAbilityData, const NWorld::PFBaseUnit* pOwner, const NWorld::Target& target ) const;

    struct UnitAttitude
    {
      enum Type {
        NA,
        SELF,
        ALLY,
        HOSTILE
      };
    };

    UnitAttitude::Type GetUnitAttitude(NWorld::PFLogicObject const* pObject) const;
    void ProcessSelectionPickEffects(NWorld::PFLogicObject* pLogicObj);

		/**
		 * Execute world command
		 * @param cmd
		 * @param worldPosition 
		 * @param pObj Pointer to picked object May be NULL
		 * @param bAddToQueue
		*/
    void ExecuteCommand(Command cmd, int nParam = 0);
    void ExecuteCommand(Command cmd, CVec3 const &worldPos, PF_Core::WorldObjectBase *pObj, bool bAddToQueue = false, const NDb::AlternativeTarget * altTarget = 0 );

    /**
    */
    void UpdateSaturation( float deltaTime );

    CVec2 const & GetCurrentMapSize() { return pWorld->GetMapSize(); }
	
    void UpdateScrolling();
		void SetCursorPos(CVec2 const& _vCursorPos);
    void UpdatePick();
    void UpdateTerrainPick();
	  void ComputeCameraRect(CVec3 vaCorners[]);
    void UpdateState();

    bool MsgOnMouseMove( const Input::SSysParams & sysParams );
		bool MsgOnLMouseDown( const Input::SSysParams & sysParams );
		bool MsgOnRMouseDown( const Input::SSysParams & sysParams );
    bool MsgOnMouseDownImpl( const Input::SSysParams & sysParams, UI::EMButton::Enum action  );
    bool MsgOnKeyDown( const Input::SSysParams & sysParams );

    void MsgOnMouse3Down();
    void MsgOnMouse3Up();

		void MsgOnExitGame();

    void SelfCastOn();
    void SelfCastOff();

    void MsgOnImpulsiveBuffDown();

    void MsgOnShowStatistics();
    void MsgOnHideStatistics();

    void MsgOnShowCharStat();
    void MsgOnShowInventory();
    void MsgOnShowTalents();

    void MsgOnFullScreen();

    void MsgChatOpenClose();
    bool MsgChatOpenChannel(const NDb::EChatChannel & channelID);

    void MsgSmartChatOpen();

    void OnShowAGDebugInformation();
    void OnDumpStatesDebugInformation();
    void OnDumpStatesStack();

		void OnResetClientObjects();
		void OnSaveWorld();
		void OnLoadWorld();

    void ProcessSignal();

		void DebugAnimGraphSetPrevGraph();
		void DebugAnimGraphSetNextGraph();
		void DebugAnimGraphIncSpeed();
		void DebugAnimGraphDecSpeed();
		void DebugAnimGraphChangeSpeedDelta();
		void DebugAnimGraphChangeObject();
		
    void MsgShowHealthbars();
		void MsgHideHealthbars();
    void MsgToggleHealthbars();

    bool MsgSetCtrlDown() { bCtrlPressed=true;  return false; }
    bool MsgSetCtrlUp() { bCtrlPressed=false; return false; }

    bool MinimapSignalKeyDown() { minimapSignalKey = true;  return false; }
    bool MinimapSignalKeyUp() { minimapSignalKey = false; return false; }

    void CameraSwitchAttachModeDown();
    void CameraSwitchAttachModeUp();

    bool CmdCancel();

    void SetHint( const PF_Core::WorldObjectBase * pObject, NScene::SceneObject * pSceneObject, bool bShow );

    void UpdateSelectedObject(  );
    void UpdatePickedObject( );

    int GetHeroPrimeNafta();
    void PlayPickEffect(CVec3 const &pos, bool isGreen = true /*Green or Red marker*/);

    bool IsSameFaction( NWorld::PFLogicObject const *unit ) const;

    void TargetZoneSet(NWorld::PFAbilityData const *pAbilityData);
    void TargetZoneReset();
    void TargetZoneUpdate(CVec3 const *pPos = 0);

    bool LockActionBar(const int &lock);
       
    bool CmdActionBarHotKey( const int & slotIndex );

    //helper logging function
    void LogHeroEvent( const StatisticService::RPC::SessionEventInfo &params, NWorld::PFBaseHero const * hero, SessionEventType::EventType eventType );

  protected:
		bool OpenUILayout( UI::User * uiUser );

    void SetState(State newState);
    void SwitchState();

    State m_state;
    State m_newState;
    CPtr<NGameX::IGameMenuMinigameActions> gameMenuMinigameInterface;

    StrongMT<StatisticService::IGameStatistics>  gameStatistics;
    Strong<StatisticService::GameStatGuard> gameStatisticsGuard;
    Weak<ISocialConnection> socialServer;
    Weak<GuildEmblem> guildEmblem;
    
    vector<NCore::PlayerStartInfo> playersStartInfo;

    NDb::EFaction failedFaction;
    float happyCheckTimer;

    CObj<NWorld::PFHeroLocalStatistics> pHeroLocalStatistics;

    struct SessionEventData
    {
      SessionEventData(int worldStep, SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & eventParams)
        : step(worldStep)
        , type(eventType)
        , params(eventParams)
      {}

      int step;
      SessionEventType::EventType type;
      StatisticService::RPC::SessionEventInfo params;
    };

    typedef nstl::list<SessionEventData> SessionEvents;

    SessionEvents  worldSessionEvents;

    nstl::vector<nstl::string> vAmbientSoundParams;
    ScopedPtr<AmbienceMap> pAmbienceMap;

	public:
		AdventureScreen();
		virtual ~AdventureScreen();

    void SetLobbyCallback( IGameControl * _gameControl );

    //Функция должна зваться сразу после создания объекта; в этой функции проводятся операции, которые нельзя поместить в дефолтный конструктор
    //Почему не сделать НЕдефолтный конструктор - только потому, что тогда придется копипастить список инициализации на полстраницы
    void Construct( NGameX::ChatUiController * _chatController, NGameX::SmartChatController * _smartChatController, IgnoreListStorage* _ignoreListStorage, bool _isSpectator, bool _isTutorial );
    
    void PrecacheResources();

    bool GetControlStyle();

    void ActivateImpulsiveBuff();

    void ReservePureClientObjects( unsigned int n ) { pureClientObjects.reserve( n ); }
    void PushPureClientObject( PFPureClientObject* pPureClientObject )
      { pureClientObjects.push_back( pPureClientObject ); }

    virtual NDb::EFaction GetPlayerFaction() const { return heroFaction; }
    void SetPlayerFaction(NDb::EFaction faction) {heroFaction = faction;}

    VisibilityMapClient * GetClientVisibilityMap() const {return visibilityMap;}

    NWorld::PFBaseHero*       GetHero();
    NWorld::PFBaseHero const* GetHero() const;
    void SetLogicHero(NWorld::PFBaseHero * pHero);
    virtual void  SetNaftaInfoProvider(INaftaInfoProvider * _naftaInfoProvider) {naftaInfoProvider = _naftaInfoProvider;}

    NWorld::PFBaseHero*       GetHeroById(int heroId) const;
    NWorld::PFPlayer*         GetPlayer()  { return pWorld ? pWorld->GetPlayer(playerId) : NULL; } 
    NWorld::PFPlayer const *  GetPlayer() const { return pWorld ? pWorld->GetPlayer(playerId) : NULL; } 
    NWorld::PFAbilityData *   GetAbilityData(Command cmd, int index);
    const wstring&            GetPlayerName(int playerId) const;
    virtual NWorld::PFWorld*  GetWorld() { return pWorld; }
    virtual NScene::IScene*   GetScene() const { return pScene; }
    Command                   GetCommand() const { return command; }
    bool                      IsPlayingMinigame() const { return isPlayingMinigame; }

    bool                      IsSessionStarted() const { return isSessionStarted; }
    lobby::TGameId            GetSessionId() const { return sessionId; }
    bool                      IsSpectator() const { return isSpectator; }

    virtual void SetTimeScale(float timescale);
    virtual void OnTimeScaleChanged(float timescale);

    void SetGameMenuMinigameInterface( NGameX::IGameMenuMinigameActions * actions );
    NGameX::IGameMenuMinigameActions * GameMenuMinigameInterface() const { return gameMenuMinigameInterface; }

		void SendGameCommand( NCore::WorldCommand* command, bool isPlayerCommand = false );
    int GetLastPlayerActivityStep() const { return lastPlayerActivityStep; }

    const int GetLocalPlayerID() const { return playerId; }
    CRay const& GetCursorRay() const { return cursorRay; }

    bool InitAdventures( const NCore::MapStartInfo & startInfo, NCore::ITransceiver * _pTransceiver,
                          StatisticService::IGameStatistics * _gameStatistics,
                          lobby::EGameType::Enum _sessionType, int myPlayerId, 
                          NWorld::PFResourcesCollection* _pRCollection,  ISocialConnection * _socialConnection, 
                          GuildEmblem* _guildEmblem, int stepLength = DEFAULT_GAME_STEP_LENGTH );
    void InitPlayerNames(const NCore::MapStartInfo & startInfo, const int myUserId, const NDb::AdvMapDescription* pAdvMapDesc);


    void AddMessageToChat( wstring& msg );

    void OnMapLoaded( const NDb::AdvMapDescription * advMapDescription, const NDb::AdventureCameraSettings * cameraSettings );
    void OnSessionStart( lobby::TGameId sessionId, bool inReconnectState = false );
    void StartBots( StartBotsFilter filter, bool inverse, bool midOnly = false );

    virtual bool Init( UI::User * uiUser );

    virtual NMainLoop::EScreenLayer::Enum GetScreenLayer() const { return NMainLoop::EScreenLayer::BelowNormal; }

		virtual bool OnBeforeClose();

		virtual void CommonStep( bool bAppActive ); 
		virtual void Step( bool bAppActive );

    void HappyCreaturesStep( float dt );

		virtual void Draw( bool bAppActive );
		virtual bool ProcessUIEvent( const Input::Event & message );
    virtual bool ProcessSceneEvent( const Input::Event & message );
    void OnStatsIncreased();

    Render::HDRColor GetOutlineColor(NDb::EEffects effect) const;
      
    PF_Core::WorldObjectBase* GetCurrentPickedObject() const { return currentPick.GetPickedPtr(); }
    NScene::SceneObject* GetCurrentPickedSceneObject() const { return currentPick.GetScenePtr(); }
    Render::HDRColor GetCurrentPickedOutlineColor() const { return preselectedOutlineColor; }
    CVec3 const& GetCurrentPickedPos();
    NWorld::PFBaseUnit* GetCurrentSelectedObject() const;
    const CVec3& GetCurrentCursorPosOnTerrain();

    void ClearAllSelections();
    void SetSelectedObject( CPtr<PF_Core::WorldObjectBase> const &selectedObject_, NScene::SceneObject *selectedSceneObject_ );
    CPtr<PF_Core::WorldObjectBase> const& GetSelectedObject() { return selectedObject; }
    NScene::SceneObject* GetSelectedSceneObject() { return selectedSceneObject; }
    Render::HDRColor GetSelectedOutlineColor() const { return selectedOutlineColor; }
    float GetSelectedOutlineThickness() const { return IsValid(pUIData) ? pUIData->outlineThickness : 0.0f; }
    void ProcessSelectionEffects();

    CObj<AdventureCameraController> GetCamera() const { return pCameraController; }
    CPtr<AdvancedFreeCameraController> GetFreeCamera() const { return pFreeCameraController.GetPtr(); }

    void SetFreeCameraController( bool flag );
    void OnHeroSetActive();

    void SetChannellingCancelComplete() { channellingIsCancelling = false; }

		// modal screens doesn't pass steps and messages through them selfs
		virtual bool IsModal() const { return true; }
    virtual bool IsTransparent() const { return false; }
		virtual bool IsInited() const { return inited; }

    ObjectsInfo2dLogic * GetObjInfo2d(  ) const { return objectsInfo2d; }
    PlayerDataManager* GetPlayerDataMan() const { return playersInfo; }
    Minimap* GetMinimap() const { return minimap; }

    QueueSoundPlayer* GetAnnouncementSoundPlayer() { return announcementSoundPlayer; }
    MarkersController* GetMarkersController() const { return markersController; }

    AmbienceMap* GetAmbienceMap() const { return Get(pAmbienceMap); }
    
    void MoveCameraTo( const CVec3& pos, bool resetObserver = true );
    void SetCameraFree( const CVec3& rotation, const CVec3& position );
    void UnSetCameraFree();
    void MoveCameraTo( NWorld::PFBaseUnit const * pUnit, bool resetObserver = true );
    bool IsCameraLocked() const;
    bool IsObservingObject( NWorld::PFBaseUnit const * pUnit ) const;
    void SetObservingObject( NWorld::PFBaseUnit const * pUnit , bool forceObservation = false);

		static AdventureScreen * Instance();

    virtual void NotifyPushedLine(const NWorld::PFBuilding * quarter, const NWorld::PFBaseUnit * killer);// NDb::EFaction faction, NDb::ERoute routeId );
    virtual void NotifyOfSimpleUIEvent( NWorld::PFBaseHero * hero,  NDb::EErrorMessageType msg );
    virtual void NotifySoldiersFirstSpawned();
    virtual void SetDebugMessage(string const &msg);

    inline bool IsActiveChat(){ return m_isShowChat;}
    virtual void SetActiveChat(bool isActiveChat){ }//m_isShowChat = isActiveChat;}
    virtual NWorld::PFBaseUnit * GetMainUnit();
    
    inline bool IsGamePaused(){ return m_gamePause != PAUSE_OFF;}
    void ProcessGamePause(EPauseMode pauseMode, int playerWhoPressedPause);  //call to set the pause and show it on the screen.
    
    bool OnHeroAvatarMouseClick( NWorld::PFBaseUnit * pHero, int action );

    virtual void OnClientStatusChange( int userId, int newStatus, int step, NWorld::PFPlayer * player = 0 );

    void OnTowerDie();

    //IAdventureScreen
    //terrain heights
    virtual CArray2D<float> const& GetHeightsAsFloat() const;

    virtual void DisableRenderWarFog(const NWorld::PFBaseHero * hero, bool disable);

    //its a valid instance of adventure screen. means that we can create visual objects
    virtual bool CanCreateClients() { return true; }

    //precache effects in the resource tree
    virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName );
    virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const NDb::DbResource * excludePart );
    virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const nstl::list<const NDb::DbResource*>& excludes );
    virtual void PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const nstl::list<const NDb::DbResource*>& excludes, const nstl::string& skinId );

    //IAdventureScreen logging
    virtual void LogSessionEvent( NWorld::PFBaseHero const * hero, SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params );
    virtual void LogSessionEvent( NWorld::PFBaseHero const * hero, SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params, int worldStep );
  
    virtual void LogWorldSessionEvent( SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params );

    void FillSessionResults( StatisticService::RPC::SessionClientResults & _info, int _surrenderVotes );

    virtual void LogHeroDamage(const NWorld::HeroOpponent &opponent, unsigned int abilityId, const NWorld::HeroDamage &damage, bool dealt);

    NWorld::PFHeroLocalStatistics * GetHeroLocalStatistics() { return pHeroLocalStatistics; }

    virtual void OnTimeSlice();

    virtual void OnHeroDamaged( NWorld::PFBaseHero const * hero );

    STARFORCE_EXPORT virtual void OnVictory( NDb::EFaction _failedFaction, int _surrenderVotes );
    
    bool IsGameEnded();

    virtual void DumpState( const char* stateClass, const char* state );

    virtual NWorld::ImpulsiveBuffsManager * GetImpulseBuffsManager() {return impulseBuffsManager;}

    virtual NWorld::PFBaseHero * GetLoggerHero();

    virtual void StartGlobalSounds();
    virtual void StopGlobalSounds();
    virtual void StartAmbientSound();
    virtual void StopAmbientSound();
    virtual void UpdateAmbientSound(NScene::SCameraPosition const& camPos);
    void PlaceAskToAnnouncementQueue( NSound::AskCommands* ask, int priority );

    virtual bool GetCursor( string * id, const UI::Point & screenCoords ) const;

    //awards

    void AwardUser(const nstl::vector<roll::SAwardInfo> & _awards);

    //interface IUIEventHandler
    virtual bool OnTalentSetButtonClick(int level, int slot);
    virtual bool OnPortalClick();
    virtual bool OnUnitAvatarMouseClick(NWorld::PFBaseUnit *pUnit, int action);
    virtual bool OnUnitAvatarMouseDblClick(NWorld::PFBaseUnit *pUnit, int action);
    virtual void CancelObservingObject();
	  virtual void TargetZoneTooltip(NWorld::PFAbilityData const *pAbilityData);
    virtual bool TargetZoneUnit(const NWorld::PFBaseUnit* pUnit);
    virtual bool StartSpectate( const int& playerIdx );
    virtual bool StartSpectateById( const int& playerId );
    virtual void SetActivePlayer( const NWorld::PFPlayer* pl );

    virtual void MinimapActionBegin(UI::EMButton::Enum action, float x, float y);
    virtual void MinimapActionMove(float x, float y);
    virtual void MinimapActionEnd(UI::EMButton::Enum action, float x, float y);
    virtual void MinimapOver(bool over, float x, float y);
    virtual void MinimapSignalBtnActionEnd();
    virtual void LockCamera(bool lock);

    virtual bool OnShopButtonClick(int item);
    virtual void OnItemButtonClick(int item);

    virtual void ExitGame( bool returnToCastle );
    virtual void SkipTutorial();
    virtual void DisableHotkeys(bool disable);

    virtual void ResetTargetState();

    //interface ICloseApplicationHandler
    virtual bool OnCloseApplication();

    virtual void ContinueGame();
    virtual void OnEscMenuShow();
   
    void ActivateSessionSoundScene();

    void ApplyGSClientSettings(const GSClientSettings & _gsClientSettings) { gsClientSettings = _gsClientSettings; };
    const GSClientSettings & GetGSClientSettings() const { return gsClientSettings; }
    bool IsMinigameEnabled() const { return gsClientSettings.minigameEnabled; }
    bool IsShowGuildEmblem() const { return gsClientSettings.showGuildEmblem; }

    void SetDirectionHint(const char* materialFile, float size, float width, float offset);
    void SetDirectionHint(const char* materialFile, float size, float width);
    void SetDirectionHintPos(CVec3 const& directionHintPos) { directionHintData.targetPos = directionHintPos; }
    void SetDirectionHintSize(float maxSize, float minSize, float sizingDistance) { directionHintData.Set(maxSize, minSize, sizingDistance); }
    void ResetDirectionHint();

    // Tutorial stuff
    void ShowUIBlock( const char* id, bool show );
    void ShowAllUIBlocks( bool show );
    void BlockActionBar( bool block );
    void SetAdventureControlsEnabled( bool enabled, bool enabledCursor );
    bool GetAdventureControlsEnabled() const { return bAdventureControlsEnabled; }
    void UpdateCursor();
    // Highlight 
    void ShowTutorialTalentHighlight( int column, int raw, bool show );
    void ShowTutorialInventoryItemHighlight( int slot, bool show );
    void ShowTutorialShopItemHighlight( int slot, bool show );
    void ShowTutorialActionBarItemHighlight( int slot, bool show );
    void ShowTutorialElementHighlight( string elementName, bool show );
    void ShowTutorialHeroHighlight( int heroID, bool show );
    void ShowTutorialHeroLevelHighlight( int heroID, bool show );
    void ShowTutorialOvertipLevelHighlight( bool show, float x, float y );
    // Blocking
    UIBlockingController* GetUIBlockingController() { return uiBlockingController; }

    // Dialogs and cinematic stuff
    void StartDialog( const char* id, bool isCinematic );
    void StartHintDialog( const char* dialogId, const char* hintId, const char* hintImageId );
    void SetHintLine( const char* id, const char* bubbleViewType );
    bool IsDialogFinished( const char* id ) const;
    bool IsPhraseFinished( const char* id ) const;
    void PauseDialog( bool pause );
    // Quests
    void AddSessionQuest(string id, const NNameMap::Map* pMap);
    void RemoveSessionQuest(string id);
    bool UpdateSessionQuestCounter(string id, const int count);
    void UpdateSessionQuestText( string id, const NNameMap::Map* pMap );
    void SessionQuestRemoveSignal(string idQuest, string idSignal);
    void SessionQuestUpdateSignal(string idQuest, string idSignal, float x, float y);
    // Bubbles
    void ShowTalentBubble( int column, int row, bool show, string id, string bubbleViewType, int bubbleIndex );
    void ShowActionBarButtonBubble( int index, bool show, string id, string bubbleViewType, int bubbleIndex );
    void ShowInventoryBarButtonBubble( int index, bool show, string id, string bubbleViewType, int bubbleIndex );
    void ShowShopBarButtonBubble( int index, bool show, string id, string bubbleViewType, int bubbleIndex );
    void ShowHeroBubble( int playerId, bool show, string id, string bubbleViewType, int bubbleIndex );
    void ShowBubble( string elementName, bool show, string id, string bubbleViewType, int bubbleIndex );
    //Script message box
    void ShowScriptMessageBox( const string& headerId, const string& textId );
    int GetLastMessageBoxResult() const;
    //Script-controled scene fade effect
    void FadeScene( int destFade, float time );

    bool IsWindowVisible( int winId ) const;
    int GetInventoryItemActionBarIndex( int index ) const;
    int GetTalentActionBarIndex( int column, int row ) const;

    // Hero info control for Series map mode
    void AddHeroToInfoPanel( NWorld::PFBaseHero* pHero );

    // override hero id and skin in MapStartInfo. Effective while map is loading
    void OverrideHeroId( int playerID, uint overrideHeroId, const string& heroSkin, const wstring& nickname );
    void AddToInventory( int playerID, int id );
    void SetTalentInTS( int playerID, int key, int talId );

    bool GetEmblemTextureForTeam( int teamId, Render::Texture2DRef& tex );
    ISocialConnection* GetSocialConnection() { return socialServer; }
    
    void ShareFinalStatistics();

    virtual void PlaySameTeam(const bool agreed);

    void OnBadBehaviourComplaint(const int userId, const int reportItemId);

    void OnEscape();
    void HideCurrentTooltip();

    void SetCustomSessionType( bool isCustomGame ){ isCustomSessionType = isCustomGame; }
    bool IsCustomSessionType() {
      return ( sessionType == lobby::EGameType::SocialMMaking && isCustomSessionType ) ;
    }

    void HandlePlaySameTeamDecision(const CPtr<NWorld::PFPlayer>& player, const bool agreed);
    
    NGameX::IgnoreListStorage* GetIgnoreListStorage() { return ignoreListStorage; }
    void AddToComplList(const CPtr<NWorld::PFPlayer>& player);
    bool InComplList(const CPtr<NWorld::PFPlayer>& player) const;
  private:
    typedef nstl::vector<__int64> ComplList;
    ComplList  playerComplList;

    void MoveCameraByMinimap( float x, float y );
    
    // Event handlers
    bool OnKeyCommand(const Command & command);
    //bool OnAutoTarget(int cmd, int index);
    bool OnSelectionButtonMouseClick(CVec3 const &pickPosition,  bool usePicking);
    bool OnActionButtonMouseClick(CVec3 const &pickPosition, bool usePicking);
    void UpdateShopInfo( PF_Core::WorldObjectBase *pCanBeShop );

    void WaitLeaveAck();

    void UpdateBlockedKeys( const char* id, const bool show );

    void PlaySameTeamSocial(const bool agreed);

    

  public:
    
    virtual void OnPlayerDisconnected(NWorld::PFPlayer * player, int lastStep);
    virtual void OnStartAiForPlayer( NWorld::PFPlayer * player );

    STARFORCE_EXPORT virtual void OnProtectionError();

    virtual void OnReplayEnded();
    // TODO: remove when normal UI for replays will be implemented
    virtual void ShowReplaySpeed(float speed);
    virtual void ShowReplayPause();
    virtual void HideReplayMsg();

    bool OnEnterLeaveMinigame( NWorld::PFEaselPlayer * easelPlayer, bool bEnter );
    bool OnUIEvent( PFUIEvent * pEvent, NNameMap::Map const *pMap, AnnouncementParams * announcementParams = 0, bool skipCheckSignRecipients = false );
    void OnSpectatorJoin( const wstring& spectatorNickname );

    StatisticService::GameStatGuard* GetStatisticsGuard() {return gameStatisticsGuard;}

  private:


    enum CursorType
    {
      Pointer_Yellow,
      MiniMapAllert,
      Target_Green,
      Target_Yellow,
      Target_Red,
      Target_Normal,
      Pointer_Green,
      Pointer_Red,
      Pointer_Normal,

      Scroll_Cur_RightBottom,
      Scroll_Cur_LeftBottom,
      Scroll_Cur_RightTop,
      Scroll_Cur_LeftTop,

      Scroll_Cur_Top,
      Scroll_Cur_Bottom,
      Scroll_Cur_Right,
      Scroll_Cur_Left,

      Cur_Last
   };

    CursorType GetCurrentCursor( ) const;
    CursorType GetScrollCursor(CVec2 _scrollOffset) const;
    void InitUIEvents();


    vector<string> cursors;
    vector<CObj<PFPureClientObject>> pureClientObjects;

    map<int, NCore::TGuildAuid> teamToGuildAuid;
    map<NCore::TGuildAuid, Render::Texture2DRef> guildAuidToTexture;

    CVec2 scrollOffset;

    CObj<NGameX::PFUIEvent> evHeroReconnected;
    CObj<NGameX::PFUIEvent> evHeroDisconnected;
    CObj<NGameX::PFUIEvent> evHeroDisconnectedAFK;
    CObj<NGameX::PFUIEvent> evHeroLeft;
    CObj<NGameX::PFUIEvent> evHeroFriendReconnected;
    CObj<NGameX::PFUIEvent> evHeroFriendDisconnected;
    CObj<NGameX::PFUIEvent> evHeroFriendDisconnectedAFK;
    CObj<NGameX::PFUIEvent> evHeroFriendLeft;
    CObj<NGameX::PFUIEvent> evHeroAFK;
    CObj<NGameX::PFUIEvent> evHeroAFKEnded;
    CObj<NGameX::PFUIEvent> evBarrackDestroyed;
    CObj<NGameX::PFUIEvent> evFriendBarrackDestroyed;
    CObj<NGameX::PFUIEvent> evDefeat;
    CObj<NGameX::PFUIEvent> evVictory;
    CObj<NGameX::PFUIEvent> evSpectatorJoin;
    CObj<NGameX::PFUIEvent> evStartAiForPlayer;

    NDb::Ptr<NDb::UIEvent> evAddGold;

    AdventureScreenFacets::GameOverEffect gameOverEffect;
    SimpleTimer endGameTimer;
    int lastPlayerActivityStep;

    bool playSameTeamEnabled;
    bool playSameTeamSent;

    bool exitingGame;

  private:
    friend bool MoveCameraToMainBuilding( const char *name, const vector<wstring> &params );
    bool IsActionCmd( UI::EMButton::Enum action );
    bool IsSelectionCmd( UI::EMButton::Enum action );
    bool IsMinimapSignalCmd( UI::EMButton::Enum action );

    bool UseSmartChat();

    void OnToggleSharedVision();
  };
}

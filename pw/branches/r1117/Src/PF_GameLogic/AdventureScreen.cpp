#include "stdafx.h"

#include "AdventureScreen.h"
#include "GameControl.h"
#include "PFRenderInterface.h"
#include "SessionEventType.h"
#include "AdventureScreenLogic.h"
#include "FlyTexts.h"
#include "Minimap.h"
#include "ReplayInfo.h"
#include "ObjectsInfo2d.h"
#include "System/LogFileName.h"
#include "System/FileSystem/FileUtils.h"
#include "System/StrProc.h"
#include "Client/MainTimer.h"
#include "Core/Scheduler.h"
#include "Core/CoreFSM.h"
#include "Scene/CameraControllersContainer.h"
#include "Scene/FreeCameraController.hpp"
#include "Scene/CollisionGeometry.h"
#include "Scene/DiAnGr.h"
#include "AdventureCameraController.hpp"
#include "Terrain/Terrain.h"
#include "PF_Core/EffectsPool.h"
#include "HeroActions.h"
#include "PFAIContainer.h"
#include "PFChest.h"
#include "PFGlyph.h"
#include "PFHero.h"
#include "PFTalent.h"
#include "PFFlagpole.h"
#include "PFLogicDebug.h"
#include "PFMinigamePlace.h"
#include "PFClientHero.h"
#include "PFClientObjectHelpers.h"
#include "UI/Resolution.h"
#include "UI/FlashContainer2.h"
#include "DieTimer.h"
#include "TileMap.h"
#include "GameLogicStatisticsTypes.h"
#include "Server/Statistic/StatisticsCommonTypes.h"
#include "Client/ScreenCommands.h"

#include "PFCheat.h"
#include "PFDebug.h"

#include "IGameStatistics.h"
#include "System/InlineProfiler.h"

#include "NivalInput/Binds.h"

#include "PFMaleHero.h"
#include "libdb/dbid.h"
#include "libdb/DbResourceCache.h"

#include "PFStatistics.h"

#include "PFImpulsiveBuffs.h"

#include "NaftaInfoProvider.h"

#include "PFClientVisibilityMap.h"
#include "DamageBloodMask.h"

#include "Render/AOERenderer.h"
#include "PF_Core/SpectatorEffectsPool.h"

//new flash interface
#include "ActionBarController.h"
#include "ShopController.h"
#include "InventoryController.h"
#include "EscMenuController.h"
#include "AdventureFlashInterface.h"
#include "StatisticsController.h"
#include "ChatController.h"
#include "SmartChatController.h"
#include "DialogController.h"
#include "UIBlockingController.h"
#include "TeamInfoNew.h"

#include "GameMenuInterfaces.h"

#include "AdventureScreenEvents.h"
#include "AnnouncementParams.h"
#include "WarFog.h"

#define USE_NEW_AOE

#include "PF_GameLogic/DBSound.h"
#include "Scene/AmbienceMap.h"
#include "System/FlashWindow.h"
#include "DBUnit.h"
#include "DBHeroesList.h"
#include "QueueSoundPlayer.h"
#include "MarkersController.h"
#include "HeroTitleCalculator.h"
#include "HeroSpawn.h"
#include "HeroScoreWrapper.h"
#include "PFHeroStatistics.h"
#include "DBStats.h"

#include "TargetSelectorFormulaPars.h"

#include "PFPostFXFader.h"
#include "GenericAbuseController.h"
#include "GuildEmblem.h"
#include "ISocialConnection.h"
#include "ResourcesPreloader.h"

#include "PW_Client/GameStatGuard.h"

#include "AdventureTooltip.h"

#include "ClientVisibilityHelper.h"
#include "ObjectInfoHelper.h"

#include "PlayerBehaviourTracking.h"
#include "BadBehaviourComplaintCmd.hpp"
#include "TargetSelectorHelper.hpp"

extern "C" INTERMODULE_EXPORT void TooSmartCompiler()
{
}

//UGLY: Global to access "precache_session_data" var defined in HeroSpawn.cpp
extern bool G_GetPrechacheSessionData();

static NDebug::StringDebugVar g_selectedObject( "SelectedObject", "AdvScr" );
static NDebug::DebugVar<unsigned int>  terrain_Owner( "Owner data", "Terrain" );

static NDebug::StringDebugVar g_currentState( "CurrentState", "Logic" );
static NDebug::StringDebugVar g_prevState( "PrevState", "Logic" );
static NDebug::StringDebugVar g_prev2State( "Prev2State", "Logic" );

static NDebug::StringDebugVar ambienceDebugStr("AmbPercent", "AmbienceMap");

static bool g_mouseScrollingEnable = true;

static string g_enemyBots;
static string g_allyBots;
static bool g_hackE3Nicknames = false;
static int gShowUserInterface = 1;

struct DebugMouseDown
{
  DebugMouseDown() : time (-1), enabled (false) {}
  CVec3 vOnMouseMovePoint;
  CVec3 vOnMouseDownPoint;
  float time;
  bool enabled;
};
static DebugMouseDown debugMousePick;

static int updateMouseMode = 0;

// tmp, IgorKaa
namespace
{
DECLARE_NULL_RENDER_FLAG

int g_needHeroLink = -1;
int _nCommandLag   = 5;
}


// Camera user settings
static float s_camera_rod = -1.0f; // -1 == use map default value
REGISTER_VAR_PRED( "camera_rod", s_camera_rod, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(20.0f, 70.0f));
static float s_camera_pitch = -1.0f; // -1 == use map default value
REGISTER_VAR_PRED( "camera_pitch", s_camera_pitch, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(40.0f, 60.0f));



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_VAR( "camera_link_to_hero", g_needHeroLink, STORAGE_USER );

static int g_minimap_rotate = 0;
REGISTER_VAR( "minimap_rotate", g_minimap_rotate, STORAGE_USER );

static int useTempDebugTrace = 0;
REGISTER_DEV_VAR( "use_temp_debug_trace", useTempDebugTrace, STORAGE_NONE );

namespace 
{
static bool g_casualControlStyle = true;
REGISTER_VAR( "casual_control_style", g_casualControlStyle, STORAGE_USER );

const int minSelectionPriority = -MAX_INT;

static CVec2 CalcScrollOffset( SVector const &mousePos, float scrollSize )
{
  const CTPoint< int > scrRes = UI::GetUIScreenResolution();
  
  const float scrollWidth = scrollSize;
  const float scrollHeight = scrollSize;
  
  //≈сли убрать данную проверку то скроллинг будет нормально работать за границами окна
  if( mousePos.x < 0 || mousePos.y < 0 || 
      mousePos.x >= scrRes.x || mousePos.y >= scrRes.y )
    return VNULL2;
    
  CVec2 res(VNULL2);

  if ( mousePos.x > scrRes.x - scrollWidth )
  {
    res.x = 1;
  }
  else if( mousePos.x < scrollWidth )
  {
    res.x = -1;
  }

  if ( mousePos.y > scrRes.y - scrollHeight )
  {
    res.y = -1;
  }
  else if( mousePos.y < scrollHeight )
  {
    res.y = 1;
  }
  
  return res;
}

DiAnimGraph* DebugFindAnimGraph( NScene::SceneComponent* pRoot )
{
  DiAnimGraph* pResult = NULL;
  if ( pRoot )
  {
    NScene::SceneComponent* it = pRoot;
    do
    {
      if ( NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(it) )
        pResult = asc->GetMainAnimGraph();
      it = it->GetBrother();
    } while ( it && it != pRoot && !pResult );
  }
  return pResult;
}

void DebugEnableAGLog(PF_Core::WorldObjectBase *pickedObject, bool enableOnlyVisualLog = false)
{
  if(NWorld::PFBaseUnit const* pUnit = dynamic_cast<NWorld::PFBaseUnit const*>(pickedObject))
  {
    DiAnimGraph *pAG = DebugFindAnimGraph(pUnit->ClientObject()->GetSceneObject()->GetRootComponent());
    if (pAG != NULL)
    {
      DiAnimGraph::EnableLog(true, pAG, enableOnlyVisualLog);
      return;
    }
  }

  DiAnimGraph::EnableLog(false, NULL);
}

string GetHeroPersistentIdByPlayerInfo( const NCore::PlayerStartInfo & playerStartInfo, const NDb::AdvMapDescription* pAdvMapDesc )
{
  NDb::Ptr<NDb::HeroesDB>   heroesDb = NDb::SessionRoot::GetRoot()->logicRoot->heroes;

  NI_VERIFY( heroesDb, "", return 0 );

  const NDb::Hero* hero = NWorld::FindHero( heroesDb, pAdvMapDesc, playerStartInfo.playerInfo.heroId );
  if ( hero )
  {
    const NDb::HeroSkin* skin = NWorld::PFBaseHero::GetHeroSkin(hero, playerStartInfo.playerInfo.heroSkin);

    if ( skin && !skin->heroName.GetText().empty())
    {
      return skin->persistentId.c_str();
    }
    else
    {
      return hero->persistentId.c_str();
    }
  }
  //NI_ALWAYS_ASSERT( NStr::StrFmt( "Unknown hero id '%s'", heroId ) );
  return string();
}

wstring GetHeroNameByPlayerInfo( const NCore::PlayerStartInfo & playerStartInfo, const NDb::AdvMapDescription* pAdvMapDesc )
{
  NDb::Ptr<NDb::HeroesDB>   heroesDb = NDb::SessionRoot::GetRoot()->logicRoot->heroes;

  NI_VERIFY( heroesDb, "", return 0 );

  const NDb::Hero* hero = NWorld::FindHero( heroesDb, pAdvMapDesc, playerStartInfo.playerInfo.heroId );
  if ( hero )
  {
    const NDb::HeroSkin* skin = NWorld::PFBaseHero::GetHeroSkin(hero, playerStartInfo.playerInfo.heroSkin);

    if ( skin && !skin->heroName.GetText().empty())
    {
      return skin->heroName.GetText().c_str();
    }
    else
    {
      if ( playerStartInfo.teamID == NCore::ETeam::Team1 )
        return hero->heroNameA.GetText().c_str();
      else if ( playerStartInfo.teamID == NCore::ETeam::Team2)
        return hero->heroNameB.GetText().c_str();
      return wstring();
    }
  }
  //NI_ALWAYS_ASSERT( NStr::StrFmt( "Unknown hero id '%s'", heroId ) );
  return wstring();
}

} // namespace


namespace NGameX
{

void ProcessUnitEvent( const NDb::UIEvent* pEvent, NWorld::PFBaseUnit const* pOwner )
{
#ifndef VISUAL_CUTTED
  CObj<PFUIEvent> pUIEvent;
  if ( pEvent )
  {
    pUIEvent = new PFUIEvent( pEvent, pOwner );
  }

  SingleValueNameMapWstring nameMap( L"empty cast limitation message" );

  AdventureScreen::Instance()->OnUIEvent( pUIEvent, &nameMap );
#endif
}
  


static Weak<AdventureScreen> s_screenInstance;



AdventureScreen * AdventureScreen::Instance()
{
  return s_screenInstance;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  AdventureScreen::PickResult::PickResult() 
    : pickedPosition(VNULL3)
    , pickedNormal(VNULL3)
    , pickedObject(NULL)
    , pickedSceneObject(NULL)
    , pPreselectedCMC(NULL)
  {
    //UGLY: AdventureScreen owns a copy of NDb::DBUIData
    NDb::Ptr<NDb::DBUIData> pUIData =  NDb::Get<NDb::DBUIData>(NDb::DBID("UI/Content/_.UIDT.xdb"));
    preselectColor = pUIData->colorPreselect;
  }

  AdventureScreen::PickResult::~PickResult()
  {
    if (NULL != pPreselectedCMC)
      removePreselectEffect();
  }

  void AdventureScreen::PickResult::SetPickedObjects(PF_Core::WorldObjectBase* pObject, NScene::SceneObject* pSceneObject)
  {
    if (NULL != pPreselectedCMC)
      removePreselectEffect();

    pickedObject = pObject;
    pickedSceneObject = pSceneObject;

    if (pickedObject != NULL/* && pickedObject != AdventureScreen::Instance()->selectedObject*/) // the test is moved inside to enable outline [9/23/2010 paul.smirnov]
      addPreselectEffect();

  }

  void AdventureScreen::PickResult::SetSelectedObject(PF_Core::WorldObjectBase* pObject)
  {
    if (NULL != pObject && pObject == pickedObject)
    {
      if (NULL != pPreselectedCMC)
        removePreselectEffect();
    }
    else if (NULL == pPreselectedCMC)
      addPreselectEffect();
  }

  void AdventureScreen::PickResult::addPreselectEffect()
  {
    NI_ASSERT(NULL == pPreselectedCMC, "Preselection effect already exists");

    if( NWorld::PFLogicObject* pLO = IsValid(pickedObject) ? dynamic_cast<NWorld::PFLogicObject*>(pickedObject.GetPtr()) : NULL )
    {
      if (pLO->GetUnitType() != NDb::UNITTYPE_TREE && !AdventureScreen::Instance()->isPlayingMinigame)
      {
        bool pickedSelection = (pickedObject == AdventureScreen::Instance()->selectedObject);
        if ( !pickedSelection && pLO->ClientObject() )
        {
          pPreselectedCMC = pLO->ClientObject()->CreateColorModificationChannel(PF_Core::CMC_SELECTION);
          pPreselectedCMC->SetMixMode(PF_Core::CBM_Multiply);
          pPreselectedCMC->SetMulColor(preselectColor);
        }

        if(pickedSceneObject)
        {
          AdventureScreen* pScreen = AdventureScreen::Instance();
          NWorld::PFBaseHero* pOwnedHero = pScreen->GetHero();
          NWorld::PFBaseHero* pSelectedHero = dynamic_cast<NWorld::PFBaseHero*>(pLO);

          pScreen->isPreselectedOfSameFaction = pScreen->IsSameFaction(pLO);
          {
            // choose preselection effect
            NDb::EEffects effect = NDb::EFFECTS_PRESELECTIONAURAALLY;
            UnitAttitude::Type attitude = pScreen->GetUnitAttitude(pLO);
            switch (attitude)
            {
            case UnitAttitude::ALLY:
              effect = NDb::EFFECTS_PRESELECTIONAURAALLY;
              break;
            case UnitAttitude::HOSTILE:
              effect = NDb::EFFECTS_PRESELECTIONAURAHOSTILE;
              break;
            case UnitAttitude::SELF:
              effect = NDb::EFFECTS_PRESELECTIONAURASELF;
              break;
            default:
              NI_ALWAYS_ASSERT(NStr::StrFmt("Cannot choose preselection effect for unit attitude '%i'", (int)attitude));
            }

            if( NULL == pSelectedHero || pSelectedHero != pOwnedHero )
            {
              if (!pickedSelection)
              {
                preSelectionEffect   = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectAttached>(effect);
                preSelectionEffect->SetDeathType(NDb::EFFECTDEATHTYPE_MANUAL);
                preSelectionEffect->Attach(pickedSceneObject);
                pickedSceneObject->UpdateForced();
              }
              if ( pLO && !pLO->IsDead() )
                pScreen->preselectedOutlineColor = pScreen->GetOutlineColor(effect);
              else
                pScreen->preselectedOutlineColor = Render::HDRColor(1.0f,1.0f,1.0f,0.0f);
            }
            else
            {
              if ( pLO && !pLO->IsDead() )
                pScreen->preselectedOutlineColor = pScreen->GetOutlineColor(NDb::EFFECTS_PRESELECTIONAURASELF);
              else
                pScreen->preselectedOutlineColor = Render::HDRColor(1.0f,1.0f,1.0f,0.0f);
            }
          }
        }
      }
    }
  }

  void AdventureScreen::PickResult::removePreselectEffect()
  {
    if( NWorld::PFLogicObject* pLO = IsValid(pickedObject) ? dynamic_cast<NWorld::PFLogicObject*>(pickedObject.GetPtr()) : NULL )
			if ( pLO->ClientObject() )
				pLO->ClientObject()->RemoveColorModificationChannel(pPreselectedCMC);

		pPreselectedCMC = NULL;
    if (IsValid(preSelectionEffect))
      preSelectionEffect->Die();
  }



#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

AdventureScreen::AdventureScreen()
// please, specify in order they declared (to prevent bugs) [8/26/2010 smirnov]
: inited( false )
, m_isShowChat(false)
, m_gamePause(PAUSE_OFF)    
, pWorld()
, pLogic()
, pCameraController()
, pFreeCameraController()
, pScene()
, rTimeDelta(0.0f)
, m_eventTimeLeft ( 1600 )
, m_resetEventTime( 1500 )
, objectsInfo2d()
, playersInfo()
, pUIData(NULL)
, command(CMD_NA)
, pushedCommand(CMD_NA)
, bCursorInScene(false)
, vCursorPos(-1.f, -1.f)
, currentPick()
, cursorRay(VNULL3, VNULL3)
, selectedObject(NULL)
, selectedSceneObject(NULL)
, selectionEffect()
, m_landEffect()
, bShiftPressed(false)
, minimapSignalKey(false)
, bCtrlPressed(false)
, mouse3Pressed(false)
, m_updated(false)
, isPlayingMinigame(false)
, isSelectedOfSameFaction(false)
, isPreselectedOfSameFaction(false)
, bAdventureControlsEnabled(true)
, bAlwaysShowCursor(false)
, bCursorEnabled(true)
, objectSelector()
, m_abilityIndex(-1)
, m_talentLevel(-1)
, m_talentSlot(-1)
, m_targetPosition(VNULL3)
, m_canExecuted(false)
, m_zoneRange(0.0f)
, m_zoneRangeMin(0.0f)
, m_zoneSize(0.0f)
, m_zoneType(NDb::ABILITYAOEVISUAL_NONE)
, m_abilityFlags(0)
, m_abilityAOEHeight(0.0f)
, m_zonePassabilityCheckMode(NWorld::MAP_MODE_NONE)
, m_state(STATE_NORMAL)
, m_newState(STATE_NORMAL)
, gameMenuMinigameInterface()
, sessionType( lobby::EGameType::None )
, pHeroLocalStatistics()
, selectedOutlineColor(1.0f, 1.0f, 1.0f, 1.0f)
, preselectedOutlineColor(1.0f, 1.0f, 1.0f, 1.0f)
, failedFaction( NDb::FACTION_NEUTRAL )
, happyCheckTimer( 0.0f )
, isMinimapMoving(false)
, scrollOffset(VNULL2)
, gameOverEffect(this)
, cursorPosOnTerrain(VNULL3)
, isHotKeyDown( false )
, isHotkeysEnabled(true)
, blockedHotKeys(0)
, channellingIsCancelling(false)
, isSessionStarted(false)
, sessionId(0)
, reviveFinished(false)
, mapLoaded(false)
, waitingLeaveAck(false)
, returnToCastle(true)
, skipTutorial(false)
, firstCommonStep(true)
, enableAnnouncements(true)
, lastPlayerActivityStep(0)
, isSelfCastOn(false)
, towerDeathTimer(0.0f)
, bCameraSwitchAttachControlled(false)
, leftFraction( NCore::ETeam::COUNT )
, isCustomSessionType(false)
, playSameTeamEnabled(false)
, playSameTeamSent(false)
, exitingGame(false)
{
  ::memset(m_commandArguments, 0, sizeof(int) * CMD_LAST);

  NMainFrame::SetCloseHandler( this );

  uiBlockingController = new UIBlockingController();
  bindsController = new BindsController();
  pUIData = NDb::Precache<NDb::DBUIData>( NDb::DBID( "UI/Content/_.UIDT.xdb" ), 20 );

  objectInfoHelper = new ObjectInfoHelper();
}



void AdventureScreen::SetLobbyCallback( IGameControl * _gameControl )
{
  gameControlCallback = _gameControl;
}

void AdventureScreen::Construct( NGameX::ChatUiController * _chatController, NGameX::SmartChatController * _smartChatController, IgnoreListStorage* _ignoreListStorage, bool _isSpectator, bool _isTutorial )
{
  isSpectator = _isSpectator;
  isTutorial = _isTutorial;
  ignoreListStorage = _ignoreListStorage;
  chatController = _chatController;
  smartChatController = _smartChatController;

  if (IsValid(chatController))
  {
    chatController->SetBindsController(bindsController);
  }

  if (IsValid(smartChatController))
  {
    smartChatController->SetAntiSpam(this);
    smartChatController->SetBindsController(bindsController);
  }

  //FIXME: корректно распределить евенты между eventsUI и eventsScene
  //то есть 2D/UI событи€ регать в 'eventsUI', а относ€щиес€ к сцене - в 'eventsScene'
  eventsScene.AddSystemHandler( "win_mouse_move",             &AdventureScreen::MsgOnMouseMove );
	eventsScene.AddSystemHandler( "win_left_button_down",       &AdventureScreen::MsgOnLMouseDown );
	eventsScene.AddSystemHandler( "win_right_button_down",      &AdventureScreen::MsgOnRMouseDown );
	eventsScene.AddSystemHandler( "win_char",                   &AdventureScreen::MsgOnKeyDown );

  eventsUI.AddActivationHandler( "cs_show_healthbars",        &AdventureScreen::MsgShowHealthbars );
	eventsUI.AddActivationHandler( "cs_hide_healthbars",        &AdventureScreen::MsgHideHealthbars );
  eventsUI.AddActivationHandler( "cs_toggle_healthbars",      &AdventureScreen::MsgToggleHealthbars );

  //That is not a real Mouse Wheel, it's actually bind for RMB!
  eventsScene.AddActivationHandler("cs_mouse_wheel_down",     &AdventureScreen::MsgOnMouse3Down);
  eventsScene.AddActivationHandler("cs_mouse_wheel_up",       &AdventureScreen::MsgOnMouse3Up);

  eventsUI.AddActivationHandler( "cs_debug_ctrl_down",        &AdventureScreen::MsgSetCtrlDown );
  eventsUI.AddActivationHandler( "cs_debug_ctrl_up",          &AdventureScreen::MsgSetCtrlUp );

  eventsUI.AddActivationHandler( "minimap_signal_key_down",         &AdventureScreen::MinimapSignalKeyDown );
  eventsUI.AddActivationHandler( "minimap_signal_key_up",           &AdventureScreen::MinimapSignalKeyUp );

	eventsUI.AddActivationHandler( "exit_game",                 &AdventureScreen::MsgOnExitGame );

  eventsUI.AddActivationHandler( "cmd_action_bar_slot1", &AdventureScreen::CmdActionBarHotKey, 0 );
  eventsUI.AddActivationHandler( "cmd_action_bar_slot2", &AdventureScreen::CmdActionBarHotKey, 1 );
  eventsUI.AddActivationHandler( "cmd_action_bar_slot3", &AdventureScreen::CmdActionBarHotKey, 2 );
  eventsUI.AddActivationHandler( "cmd_action_bar_slot4", &AdventureScreen::CmdActionBarHotKey, 3 );
  eventsUI.AddActivationHandler( "cmd_action_bar_slot5", &AdventureScreen::CmdActionBarHotKey, 4 );
  eventsUI.AddActivationHandler( "cmd_action_bar_slot6", &AdventureScreen::CmdActionBarHotKey, 5 );
  eventsUI.AddActivationHandler( "cmd_action_bar_slot7", &AdventureScreen::CmdActionBarHotKey, 6 );
  eventsUI.AddActivationHandler( "cmd_action_bar_slot8", &AdventureScreen::CmdActionBarHotKey, 7 );
  eventsUI.AddActivationHandler( "cmd_action_bar_slot9", &AdventureScreen::CmdActionBarHotKey, 8 );
  eventsUI.AddActivationHandler( "cmd_action_bar_slot10",&AdventureScreen::CmdActionBarHotKey, 9 );

  eventsUI.AddActivationHandler( "self_cast_on",         &AdventureScreen::SelfCastOn);
  eventsUI.AddActivationHandler( "self_cast_off",        &AdventureScreen::SelfCastOff);

  
  eventsUI.AddActivationHandler( "actionbar_lock_off",   &AdventureScreen::LockActionBar, 0);
  eventsUI.AddActivationHandler( "actionbar_lock_on",    &AdventureScreen::LockActionBar, 1);

  if ( IsSpectator() )
  {
    eventsUI.AddActivationHandler( "cmd_spectate_player1", &AdventureScreen::StartSpectate, SPECTATE_PLAYER1_IDX );
    eventsUI.AddActivationHandler( "cmd_spectate_player2", &AdventureScreen::StartSpectate, SPECTATE_PLAYER2_IDX );
    eventsUI.AddActivationHandler( "cmd_spectate_player3", &AdventureScreen::StartSpectate, SPECTATE_PLAYER3_IDX );
    eventsUI.AddActivationHandler( "cmd_spectate_player4", &AdventureScreen::StartSpectate, SPECTATE_PLAYER4_IDX );
    eventsUI.AddActivationHandler( "cmd_spectate_player5", &AdventureScreen::StartSpectate, SPECTATE_PLAYER5_IDX );
    eventsUI.AddActivationHandler( "cmd_spectate_player6", &AdventureScreen::StartSpectate, SPECTATE_PLAYER6_IDX );
    eventsUI.AddActivationHandler( "cmd_spectate_player7", &AdventureScreen::StartSpectate, SPECTATE_PLAYER7_IDX );
    eventsUI.AddActivationHandler( "cmd_spectate_player8", &AdventureScreen::StartSpectate, SPECTATE_PLAYER8_IDX );
    eventsUI.AddActivationHandler( "cmd_spectate_player9", &AdventureScreen::StartSpectate, SPECTATE_PLAYER9_IDX );
    eventsUI.AddActivationHandler( "cmd_spectate_player10",&AdventureScreen::StartSpectate, SPECTATE_PLAYER10_IDX );
  }

  eventsUI.AddActivationHandler( "cmd_portal",&AdventureScreen::OnPortalClick);
  
  eventsUI.AddActivationHandler( "impulsive_buff_down",    &AdventureScreen::MsgOnImpulsiveBuffDown );

  eventsUI.AddActivationHandler( "show_statistics",    &AdventureScreen::MsgOnShowStatistics);
  eventsUI.AddActivationHandler( "hide_statistics",    &AdventureScreen::MsgOnHideStatistics);

  eventsUI.AddActivationHandler( "show_charstat",    &AdventureScreen::MsgOnShowCharStat);
  eventsUI.AddActivationHandler( "show_inventory",    &AdventureScreen::MsgOnShowInventory);
  eventsUI.AddActivationHandler( "show_talents",    &AdventureScreen::MsgOnShowTalents);


  eventsUI.AddActivationHandler("chat_open_close", &AdventureScreen::MsgChatOpenClose); 
	eventsUI.AddActivationHandler("chat_open_global", &AdventureScreen::MsgChatOpenChannel, NDb::CHATCHANNEL_BOTHTEAMS); 
	eventsUI.AddActivationHandler("chat_open_team", &AdventureScreen::MsgChatOpenChannel, NDb::CHATCHANNEL_MYTEAM);

	eventsUI.AddActivationHandler( "window_full_screen", &AdventureScreen::MsgOnFullScreen );  
  //handlers.AddActivationHandler( "chat_input_close", &NGameX::ChatScreenLogic::MsgChatClose );
  eventsUI.AddActivationHandler( "camera_switch_attach_mode_down", &AdventureScreen::CameraSwitchAttachModeDown );
  eventsUI.AddActivationHandler( "camera_switch_attach_mode_up",  &AdventureScreen::CameraSwitchAttachModeUp );


  ::memset(m_commandArguments, 0, sizeof(int) * CMD_LAST);
  m_commandArguments[CMD_STOP]        = 0;
  m_commandArguments[CMD_HOLD]        = 0;
  m_commandArguments[CMD_MOVE]        = NDb::SPELLTARGET_LAND | NDb::SPELLTARGET_SHOP;
  m_commandArguments[CMD_ATTACK]      = NDb::SPELLTARGET_LAND | NDb::SPELLTARGET_ALL | NDb::SPELLTARGET_ENEMY;
  m_commandArguments[CMD_ATTACK_AREA] = NDb::SPELLTARGET_LAND;
  m_commandArguments[CMD_SIGNAL]      = NDb::SPELLTARGET_LAND;

  SetState( STATE_NORMAL );

  s_screenInstance = this;

  pHeroLocalStatistics = new NWorld::PFHeroLocalStatistics();

  cursors.resize(Cur_Last);
  cursors[MiniMapAllert]    = "Cur_MiniMapAllert" ;
  cursors[Target_Green]     = "Cur_Target_Green" ;
  cursors[Target_Yellow]    = "Cur_Target_Yellow" ;
  cursors[Target_Red]       = "Cur_Target_Red" ;
  cursors[Target_Normal]    = "Cur_Target_Normal" ;
  cursors[Pointer_Green]    = "Cur_Pointer_Green" ;
  cursors[Pointer_Yellow]   = "Cur_Pointer_Yellow" ;
  cursors[Pointer_Red]      = "Cur_Pointer_Red" ;
  cursors[Pointer_Normal]   = "Cur_Pointer_Normal" ;

  cursors[Scroll_Cur_RightBottom]   = "Scroll_Cur_RightBottom" ;
  cursors[Scroll_Cur_LeftBottom]    = "Scroll_Cur_LeftBottom" ;
  cursors[Scroll_Cur_RightTop]      = "Scroll_Cur_RightTop" ;
  cursors[Scroll_Cur_LeftTop]       = "Scroll_Cur_LeftTop" ;

  cursors[Scroll_Cur_Top]        = "Scroll_Cur_Top" ;
  cursors[Scroll_Cur_Bottom]     = "Scroll_Cur_Bottom" ;
  cursors[Scroll_Cur_Right]      = "Scroll_Cur_Right" ;
  cursors[Scroll_Cur_Left]       = "Scroll_Cur_Left" ;
}



AdventureScreen::~AdventureScreen()
{
  NMainFrame::SetCloseHandler( 0 );

  s_screenInstance = 0;

  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  if(binds)
    binds->DeactivateSection( "adventure_screen" );

	PF_Core::EffectsPool::Term();
  PF_Core::SpectatorEffectsPool::Term();
  NScene::SceneObjectsPool::Term();
  NScene::CollisionGeometry::GetCollisionManager().Clear();
}



bool AdventureScreen::InitAdventures( const NCore::MapStartInfo & startInfo, NCore::ITransceiver * _pTransceiver,
                                     StatisticService::IGameStatistics * _gameStatistics,
                                     lobby::EGameType::Enum _sessionType, int myPlayerId,
                                     NWorld::PFResourcesCollection* _pRCollection,  
                                     ISocialConnection * _socialConnection, GuildEmblem* _guildEmblem,
                                     int stepLength )
{
  NI_PROFILE_FUNCTION_MEM

  //logging
  gameStatistics = _gameStatistics;
  sessionType = _sessionType;

  gameStatisticsGuard = new StatisticService::GameStatGuard();

  socialServer = _socialConnection;
  guildEmblem = _guildEmblem;
  playersStartInfo = startInfo.playersInfo;

  if ( guildEmblem && IsShowGuildEmblem())
  {
    int emblemHeroNeeds = -1;

    NDb::Ptr<NDb::AdvMapDescription> mapDescription = NDb::Get<NDb::AdvMapDescription>( NDb::DBID( startInfo.mapDescName ) );
    if ( IsValid( mapDescription ) )
    {
      NDb::Ptr<NDb::AdvMap> map = mapDescription->map;
      if ( IsValid( map ) )
      {
        NDb::Ptr<NDb::AdvMapSettings> settings = IsValid(mapDescription->mapSettings) ? (mapDescription->mapSettings) : (map->mapSettings);
        if ( IsValid(settings) )
        {
          emblemHeroNeeds = settings->emblemHeroNeeds;
        }
      }
    }

    if ( emblemHeroNeeds == -1 )
      emblemHeroNeeds = NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->baseEmblemHeroNeeds;

    struct LocalTeamInfo
    {
      NCore::TGuildAuid guildAuid;
      int teamId;
      uint iconId;
      nstl::string iconUrl;
      int count;
    };

    nstl::vector<LocalTeamInfo> lTeamInfo;
    typedef nstl::vector<LocalTeamInfo>::iterator Iterat;
    for ( int i = 0; i < playersStartInfo.size(); i++ )
    {
      NCore::TGuildAuid guildAuid = playersStartInfo[i].playerInfo.guildData.id;

      if ( guildAuid > 0 )
      {

        struct GuildAuidFinder
        {
          GuildAuidFinder( NCore::TGuildAuid _guildAuid, int _teamId ) : guildAuid(_guildAuid), teamId(_teamId) {}

          bool operator()( LocalTeamInfo& pItem )
          {
            if ( pItem.guildAuid == guildAuid && pItem.teamId == teamId )
              return true;
            return false;
          }

          NCore::TGuildAuid guildAuid;
          int teamId;
        } guildAuidFinder( guildAuid, playersStartInfo[i].teamID );

        Iterat it = nstl::find_if( lTeamInfo.begin(), lTeamInfo.end(), guildAuidFinder );
        if ( it == lTeamInfo.end() )
        {
          LocalTeamInfo lti;
          lti.teamId = playersStartInfo[i].teamID;
          lti.iconUrl = playersStartInfo[i].playerInfo.guildData.icon_url;
          lti.iconId = playersStartInfo[i].playerInfo.guildData.icon_number;
          lti.count = 1;
          lti.guildAuid = guildAuid;
          lTeamInfo.push_back( lti );
        }
        else
        {
          it->count++;
        }
      }
    }

    if ( startInfo.isCustomGame )
    {
      map<int, int> totalPlayersInTeam;

      for ( int i = 0; i < playersStartInfo.size(); i++ )
      {
        totalPlayersInTeam[playersStartInfo[i].teamID]++;
      }

      for ( Iterat it = lTeamInfo.begin(); it != lTeamInfo.end(); it++ )
      {
        if ( it->count > (totalPlayersInTeam[it->teamId] - it->count) )
        {
          teamToGuildAuid[it->teamId] = it->guildAuid;
          guildEmblem->StartDownload( it->guildAuid, it->iconId, it->iconUrl );
        }
      }
    }
    else
    {
      for ( Iterat it = lTeamInfo.begin(); it != lTeamInfo.end(); it++ )
      {
        if ( it->count >= emblemHeroNeeds )
        {
          teamToGuildAuid[it->teamId] = it->guildAuid;
          guildEmblem->StartDownload( it->guildAuid, it->iconId, it->iconUrl );
        }
      }
    }
  }

  pScene = NScene::CreateScene();
  pScene->Init( "", 1, CVec3( -128.f, -128.f, -128.f ), 1024.f, stepLength );

  NScene::SceneObjectsPool::Init();

  PF_Core::EffectsPool::Init( NDb::SessionRoot::GetRoot()->visualRoot->effects );
  PF_Core::SpectatorEffectsPool::Init<bool>( isSpectator );
  PreloadEffectsInResourceTree( NDb::SessionRoot::GetRoot()->visualRoot->effects.GetPtr(), BADNODENAME );

  PrecacheResources();

  NI_SYNC_FPU_START;
  pWorld = new NWorld::PFWorld( startInfo, pScene, this, _pRCollection, stepLength, gsClientSettings.aiForLeaversEnabled,
                                gsClientSettings.aiForLeaversThreshold );
  NI_SYNC_FPU_END;

  if ( PF_Render::Interface::Get() && PF_Render::Interface::Get()->GetDebugRender() )
    pWorld->SetDebugRender( PF_Render::Interface::Get()->GetDebugRender() );
  
  NWorld::PFAIContainer * AIcont = new NWorld::PFAIContainer( pWorld, _pTransceiver );
  pWorld->SetAIContainer( AIcont );
  
	UI::GetUIScript()->RegisterGlobals();

  AdventureScreenBase::InitAdventuresBase( startInfo, _pTransceiver, myPlayerId, IsSpectator() );

  NWorld::PFPlayer* humanPlayer = pWorld->GetPlayer(playerId);
	if(humanPlayer)
	{
		humanPlayer->SetIsLocal(true);
    
    NDb::EFaction faction = (humanPlayer->GetTeamID() == 0)? NDb::FACTION_FREEZE: NDb::FACTION_BURN;
    heroFaction = faction;
  }
 
  objectSelector.Init( pWorld, heroFaction );

  NSoundScene::SetScene( pScene );

  inited     = true;


  NI_ASSERT(IsValid(humanPlayer), "why playeris not valid? why why!");
  impulseBuffsManager = new NWorld::ImpulsiveBuffsManager( pWorld,  humanPlayer);

  // AnimGraph debug commands
#ifdef DIANGR_SCREEN_DEBUG_GENERAL
  eventsUI.AddActivationHandler( "cs_debug_ag_enable",       &AdventureScreen::OnShowAGDebugInformation );
  eventsUI.AddActivationHandler( "cs_debug_ag_prev_graph",   &AdventureScreen::DebugAnimGraphSetPrevGraph );
  eventsUI.AddActivationHandler( "cs_debug_ag_next_graph",   &AdventureScreen::DebugAnimGraphSetNextGraph );
  eventsUI.AddActivationHandler( "cs_debug_ag_inc_speed",    &AdventureScreen::DebugAnimGraphIncSpeed );
  eventsUI.AddActivationHandler( "cs_debug_ag_dec_speed",    &AdventureScreen::DebugAnimGraphDecSpeed );
  eventsUI.AddActivationHandler( "cs_debug_ag_change_delta", &AdventureScreen::DebugAnimGraphChangeSpeedDelta );
  eventsUI.AddActivationHandler( "cs_debug_ag_change_elem",  &AdventureScreen::DebugAnimGraphChangeObject );
#endif
  eventsUI.AddActivationHandler( "dump_states", &AdventureScreen::OnDumpStatesDebugInformation );
  eventsUI.AddActivationHandler( "dump_active_states", &AdventureScreen::OnDumpStatesStack );

	eventsUI.AddActivationHandler( "recreate_sos", &AdventureScreen::OnResetClientObjects );
	eventsUI.AddActivationHandler( "sw", &AdventureScreen::OnSaveWorld );
	eventsUI.AddActivationHandler( "lw", &AdventureScreen::OnLoadWorld );

  for ( int i = 0; i < startInfo.playersInfo.size(); i++ )
  {
    DebugTrace( "complaintsToday %d complaintsMax %d playerId %d userID %d", startInfo.playersInfo[i].playerInfo.complaintsToday, startInfo.playersInfo[i].playerInfo.complaintsMax, startInfo.playersInfo[i].playerID, startInfo.playersInfo[i].userID );

    if ( startInfo.playersInfo[i].playerID == playerId )
    {
      
      complaintsMax = startInfo.playersInfo[i].playerInfo.complaintsMax < 0 ? 0 : startInfo.playersInfo[i].playerInfo.complaintsMax;
      int c_compl = complaintsMax - startInfo.playersInfo[i].playerInfo.complaintsToday;
      complaintsToday = c_compl < 0? 0 : c_compl;
      const NCore::TComplaintInfo& info = startInfo.playersInfo[i].playerInfo.complaintsInfo;
      for ( NCore::TComplaintInfo::const_iterator it = info.begin(); it != info.end(); it++ )
      {
        string s;
        NStr::UTF8ToMBCS( &s, it->second );
        complaintsInfo[it->first] = s;
      }
    }
  }

  if (complaintsInfo.empty())
  {
    complaintsToday = 3;
    complaintsMax = 3;

    for (vector<NDb::ReportType>::const_iterator repIt = pUIData->reportTypes.begin(); repIt != pUIData->reportTypes.end(); ++repIt) 
    {
      nstl::string s;
      NStr::ToMBCS( &s, repIt->name.GetText() );//LOFIC HACK 
      complaintsInfo[repIt->id] = s.c_str();
    }
  }
	
	return true;
}



void AdventureScreen::InitPlayerNames( const NCore::MapStartInfo & startInfo, const int myUserId, const NDb::AdvMapDescription* pAdvMapDesc )
{
  playersInfo = new PlayerDataManager;

  for( int i = 0; i < startInfo.playersInfo.size(); ++i )
  {
    const NCore::PlayerStartInfo & psi = startInfo.playersInfo[i];

    bool useHeroName = false;

    if (!useHeroName && psi.nickname.empty())
      useHeroName = (psi.playerType == NCore::EPlayerType::Computer) || (isTutorial);
    if (!useHeroName && g_hackE3Nicknames)
      useHeroName = (psi.nickname.find(L"guest:") == 0);

    const wstring heroName = GetHeroNameByPlayerInfo(psi, pAdvMapDesc);
    const wstring nickname = useHeroName ? heroName : psi.nickname;
    const string heroPersistentId = GetHeroPersistentIdByPlayerInfo(psi, pAdvMapDesc);

    const int rating = static_cast<int>(floor(psi.playerInfo.heroRating));

    const PlayerData playerData(nickname, psi.userID, psi.playerInfo.heroExp, rating, psi.playerInfo.hasPremium, psi.playerInfo.fwod, psi.playerInfo.customGame, heroName, heroPersistentId);

    playersInfo->AddPlayerData(psi.playerID, playerData);

    const bool localPlayer = (psi.userID == myUserId);

    DebugTrace( "Player %s with hero %s team %d%s", NStr::ToMBCS(nickname), NStr::ToMBCS(heroName), static_cast<int>(psi.teamID), (localPlayer ? " (local)" : ""));
  }
}




bool AdventureScreen::SetCommand(Command cmd)
{
  if ( cmd == CMD_SIGNAL )
    pushedCommand = command;

  command = cmd;
  m_canExecuted = m_commandArguments[cmd] == 0;
  m_altTarget = 0;

  if ( m_commandArguments[cmd] == 0 )
  {
    m_targetObject = GetHero();
  }

  return m_canExecuted;
}



void AdventureScreen::CancelCommand()
{
  NSoundScene::EventStart( pUIData->soundEvents.targetCancelled );

  command = pushedCommand;
  pushedCommand = CMD_NA;
  m_canExecuted = false;
}



bool AdventureScreen::IsValidCommandTarget(Command cmd, CVec3 const &pos, PF_Core::WorldObjectBase const* pObj) const
{
  return
    IsValidCommandTarget(cmd, pos) ||
    IsValidCommandTarget(cmd, pObj);
}

bool AdventureScreen::IsValidCommandTarget(Command cmd, const CVec3& point) const
{
  const int flags = m_commandArguments[cmd];

  return (flags & NDb::SPELLTARGET_LAND) && (point != VNULL3);
}

bool AdventureScreen::IsValidCommandTarget(Command cmd, const PF_Core::WorldObjectBase* object) const
{
  const int flags = m_commandArguments[cmd];

  const NWorld::PFLogicObject* const target = dynamic_cast<const NWorld::PFLogicObject*>(object);

  if (!target)
    return false;

  if (target == GetHero())
    return (flags & NDb::SPELLTARGET_SELF);

  // NUM_TASK: нельз€ выбрать - нельз€ атаковать
  if (target->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDPICK))
    return false;

  {
    const int kind = target->GetUnitKind();

    if ((flags & (1 << kind)) == 0)
      return false;
  }

  if (target->GetUnitType() == NDb::UNITTYPE_FLAGPOLE)
  {
    if (target->GetFaction() == NDb::FACTION_NEUTRAL)
      return false;
  }

  return IsSameFaction(target)
    ? (flags & NDb::SPELLTARGET_ALLY)
    : (flags & NDb::SPELLTARGET_ENEMY);
}



bool AdventureScreen::CastLimitationsHandler( const NWorld::PFAbilityData* pAbilityData, const NWorld::PFBaseUnit* pOwner, const NWorld::Target& target ) const
{
  NDb::CastLimitation const* castLimitation = pAbilityData->CheckCastLimitations( target );
  if ( castLimitation )
  {
    ProcessUnitEvent( castLimitation->uiEvent, pOwner );
    return true;
  }

  return false;
}



bool AdventureScreen::SetCommandTarget( const CVec3 & pos, PF_Core::WorldObjectBase * pObj, const bool bFromMinimap )
{
  if ( command == CMD_NA )
    return false;

  if ( m_canExecuted )
    return false;

  NWorld::PFPlayer * pPlayer = pWorld->GetPlayer( playerId );
  NWorld::PFBaseHero * pHero = pPlayer ? pPlayer->GetHero() : 0;
  NI_ASSERT( pHero, "" );

  m_targetObject = 0;
  m_targetPosition = VNULL3;
  m_altTarget = 0;

  bool isValidTarget = false;

  if (IsValidCommandTarget(command, pObj))
  {
    isValidTarget = true;
    m_targetObject = pObj;
  }
  if (IsValidCommandTarget(command, pos))
  {
    isValidTarget = true;
    m_targetPosition = pos;
  }

  if ( !isValidTarget )
  {
    pLogic->SetErrorMessage( NDb::ERRORMESSAGETYPE_WRONGTARGET );
  }
  else
  {
    // Cast Limitations Check
    switch ( command )
    {
      case CMD_ITEM:
      {
        const int slot = m_abilityIndex;
        if ( pHero->CanUseConsumable( slot ))
        {
          const NWorld::PFConsumable* pConsumable = pHero->GetConsumable( slot );

          CheckForAbilityForExecute( pConsumable->GetAbility(), pos, pHero, bFromMinimap );
        }
      }
      break;

    
      case CMD_TALENT_TALENT_PANEL:
      {
        if ( NWorld::PFBaseMaleHero* pMaleHero = dynamic_cast<NWorld::PFBaseMaleHero*>( pHero ) )
        {
          int level = m_talentLevel;
          int slot  = m_talentSlot;
          if ( NWorld::PFTalent* pTalent = pMaleHero->GetTalent( level, slot ) )
          {
            CheckForTalentForExecute( pTalent, pos, pHero, bFromMinimap );
          }
        }
      }
      break;

      case CMD_PORTAL:
        {
          if ( NWorld::PFBaseMaleHero* pMaleHero = dynamic_cast<NWorld::PFBaseMaleHero*>( pHero ) )
          {
            if ( NWorld::PFTalent* pTalent = pMaleHero->GetPortal() )
            {
              CheckForTalentForExecute( pTalent, pos, pHero, bFromMinimap );
            }
          }
        }
        break;


      case CMD_RAISEFLAG:
      {
        if ( NWorld::PFFlagpole *pFlagpole = dynamic_cast<NWorld::PFFlagpole *> ( pObj ) )
        {
          const NDb::Ptr<NDb::Ability>& pDBAbility = pHero->GetWorld()->GetAIWorld()->GetAIParameters().raiseFlagAbility;
          const NWorld::PFAbilityData* pAbilityData = new NWorld::PFAbilityData( pHero, pDBAbility, NDb::ABILITYTYPEID_SPECIAL );
          CheckForAbilityForExecute( pAbilityData, pos, pHero, bFromMinimap );
        }
      }
      break;
      default:
      {
        m_canExecuted = true;
      }
    }
  }

  return m_canExecuted;
}


void AdventureScreen::CheckForTalentForExecute( const NWorld::PFTalent * pTalent, const CVec3 & pos, const NWorld::PFBaseHero * pHero, const bool bFromMinimap )
{
  if ( pTalent->IsActivated() && pTalent->CanBeUsed() )
  {
    CheckForAbilityForExecute( pTalent, pos, pHero, bFromMinimap );
  }
}

void AdventureScreen::CheckForAbilityForExecute( const NWorld::PFAbilityData * pAbilityData, const CVec3 & pos, const NWorld::PFBaseHero * pHero, const bool bFromMinimap )
{
  NWorld::PFLogicObject* pUnit = dynamic_cast<NWorld::PFLogicObject*>( m_targetObject.GetPtr() );

  const NWorld::Target target( pUnit, pos );

  if ( CastLimitationsHandler( pAbilityData, pHero, target ) )
    return;

  if (target.IsObject())
    m_canExecuted = NWorld::CheckValidAbilityTargetCondition()(target, pAbilityData);
  else
    m_canExecuted = true;

  if (m_canExecuted)
  {
    NWorld::Target newTarget;
    m_altTarget = pAbilityData->GetAlternativeTarget( target, bFromMinimap, newTarget );

    // Update target if found
    if ( newTarget.IsPosition() )
    {
      m_targetPosition = newTarget.GetPosition();
    }
    else if ( newTarget.IsObject() )
    {
      // NUM_TASK
      m_canExecuted = NWorld::CheckValidAbilityTargetCondition()(newTarget, pAbilityData);
      m_targetObject = newTarget.GetObject();
    }
  }

  if ( bFromMinimap && (pAbilityData->GetDBDesc()->flags & NDb::ABILITYFLAGS_MINIMAPTARGETMUSTBEALTERNATIVE) != 0 && ( !m_altTarget || !m_altTarget->updateTarget ) )
    m_canExecuted = false;

  if (!m_canExecuted)
    pLogic->SetErrorMessage( NDb::ERRORMESSAGETYPE_WRONGTARGET );
}



bool AdventureScreen::InvulnerableFlagpoleReaction( NWorld::PFFlagpole* pFlagpole, NDb::EFaction faction )
{
  if ( pFlagpole->IsVulnerable() )
  {
    return false;
  }

  if ( pFlagpole->IsProtectedByTower( faction ) )
  {
    pLogic->SetErrorMessage( NDb::ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYTOWER);
    return true;
  }
  else
  {
    if ( pFlagpole->IsProtectedByNext() )
    {
      pLogic->SetErrorMessage( NDb::ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYNEXT );
      return true;
    }
    else
    {
      return false;
    }
  }
}



void AdventureScreen::ExecuteCommand(Command cmd, int nParam /*= 0*/)
{
  NWorld::PFBaseHero *pHero = GetHero();
  if (!pHero)
    return;

  CObj<NCore::WorldCommand> pCommand;

  switch (cmd)
  {
  case CMD_PICKUP_OBJECT:
    pCommand = NWorld::CreateCmdPickupObject(pHero, nParam);
    break;
  case CMD_INIT_MINIGAME:
    {
      CDynamicCast<NWorld::PFEaselPlayer> easelPlayer= pHero;

      if ( IsValid( easelPlayer ) )
        pCommand = NWorld::CreateCmdInitMinigame( easelPlayer, nParam );
    }
    break;
  case CMD_KEEP_ALIVE:
    pCommand = NWorld::CreateCmdKeepAlive();
    break;
  }

  SendGameCommand( pCommand, true );
}




void AdventureScreen::ExecuteCommand(Command cmd, CVec3 const &worldPos, PF_Core::WorldObjectBase *pObj, bool bAddToQueue /*=false*/, const NDb::AlternativeTarget * altTarget /*=0*/ )
{
  NWorld::PFPlayer* pPlayer = pWorld->GetPlayer(playerId);
  NWorld::PFBaseHero* pHero = pPlayer ? pPlayer->GetHero() : NULL;

  if (!pHero)
    return;

  CObj<NCore::WorldCommand> pCommand;
  
  // play effect when targeted command is applied (for visual feedback)
  ProcessSelectionPickEffects(dynamic_cast<NWorld::PFLogicObject*>(pObj));

	switch (cmd)
	{ 
	case CMD_MOVE: 
    if( !reviveFinished && pHero->ClientObject()->GetFirstUpdateTime() > 0 )
    {
      NDb::AILogicParameters const& aiLogicParams = GetWorld()->GetAIWorld()->GetAIParameters();
        	  	 
      if( NMainLoop::GetTime() - pHero->ClientObject()->GetFirstUpdateTime() < max( aiLogicParams.heroAdvanceRespawnTime, EPS_VALUE ) )
        break;
      else 
        reviveFinished = true;
    }
    if (NWorld::PFBaseUnit *pUnit = dynamic_cast<NWorld::PFBaseUnit*>(pObj))
    {
#pragma REMINDER("http://SITE/jira/browse/NUM_TASK")
      //pCommand = NWorld::CreateCmdFollowUnit(pHero, pUnit, bAddToQueue); http://SITE/jira/browse/NUM_TASK
      PlayPickEffect(worldPos, true);
      pCommand = NWorld::CreateCmdMoveHero(pHero, worldPos.AsVec2D(), bAddToQueue);
    }
    else
    {
      PlayPickEffect(worldPos, true);
		  pCommand = NWorld::CreateCmdMoveHero(pHero, worldPos.AsVec2D(), bAddToQueue);
    }
		break;
	case CMD_STOP:
		pCommand = NWorld::CreateCmdStopHero(pHero);
		break;
  case CMD_HOLD:
    pCommand = NWorld::CreateCmdHold(pHero);
    break;
	case CMD_ATTACK:
		if(NWorld::PFBaseUnit* pTarget = dynamic_cast<NWorld::PFBaseUnit*>(pObj))
    {
      if (!IsUnitValid(pTarget))
        break;
      if ( !pTarget->IsVulnerable() )
      {
        if ( pLogic )
        {
          if ( NWorld::PFFlagpole *pFlagpole = dynamic_cast<NWorld::PFFlagpole *> ( pObj ) )
          {
            InvulnerableFlagpoleReaction( pFlagpole, pHero->GetFaction() );
          }
          else
          {
            pLogic->SetErrorMessage( NDb::ERRORMESSAGETYPE_INVULNERABLETARGET );
          }
        }
      }
      else
      {
        pCommand = NWorld::CreateCmdAttackTarget(pHero, pTarget, false);
      }
    }
		else
		{
			PlayPickEffect(worldPos, false);
			pCommand = NWorld::CreateCmdCombatMoveHero(pHero, worldPos.AsVec2D());
		}
		break;

  case CMD_ITEM:
    {
      if (pHero)
      {
        const int slot = m_abilityIndex;
        if ( pHero->CanUseConsumable( slot ) )
        {
          NWorld::PFLogicObject* pUnit = dynamic_cast<NWorld::PFLogicObject*>( pObj );
          pCommand = NWorld::CreateCmdUseConsumable(dynamic_cast<NWorld::PFBaseMaleHero*> (pHero), slot, NWorld::AbilityTarget( pUnit, worldPos, altTarget ) );
        }
      }
    }
    break;

 
  case CMD_TALENT_TALENT_PANEL:
    {
      if( NWorld::PFBaseMaleHero* pMaleHero = dynamic_cast<NWorld::PFBaseMaleHero*>(pHero) )
      {
        int level = m_talentLevel;
        int slot  = m_talentSlot;
        if (NWorld::PFTalent *pTalent = pMaleHero->GetTalent(level, slot))
        {
          if (pTalent->IsActivated() && pTalent->CanBeUsed())
          {
            NWorld::PFLogicObject* pUnit = dynamic_cast<NWorld::PFLogicObject*>(pObj);
            if ( !isPlayingMinigame )
            {
              pCommand = NWorld::CreateCmdUseTalent(pMaleHero, level, slot, NWorld::AbilityTarget( pUnit, worldPos, altTarget ), bAddToQueue );
            }
          }
        }
      }
    }
    break;

  case CMD_PORTAL:
    {
      if( NWorld::PFBaseMaleHero* pMaleHero = dynamic_cast<NWorld::PFBaseMaleHero*>(pHero) )
      {
        if (NWorld::PFTalent *pTalent = pMaleHero->GetPortal())
        {
          if (pTalent->IsActivated() && pTalent->CanBeUsed())
          {
            NWorld::PFLogicObject* pUnit = dynamic_cast<NWorld::PFLogicObject*>(pObj);
            pCommand = NWorld::CreateCmdUsePortal(pMaleHero, NWorld::AbilityTarget( pUnit, worldPos, altTarget ), false);
          }
        }
      }
    }
    break;

  case CMD_SIGNAL:
    {
      if ( !pingAbuseController->Use() )
      {
        // ≈сли ещЄ чего нужно будет пихать в нейммапу дл€ сообщени€, то имеет смысл сам контроллер отнаследовать от NameMap.
        SingleValueNameMapT<float> valuesMap( ceil( pingAbuseController->GetCooldown() ) );
        pLogic->SetErrorMessage( NDb::ERRORMESSAGETYPE_PINGRESTRICTED, true, &valuesMap );
        break;
      }

      NWorld::PFBaseUnit* pUnit = dynamic_cast<NWorld::PFBaseUnit*>(pObj);
      pCommand = NWorld::CreateCmdMinimapSignal(pHero, GetCurrentSelectedObject(), NWorld::Target( pUnit, worldPos ), pHero->GetFaction(), false);
    }
    break;

  case CMD_VIEW:
    if( isPlayingMinigame )
      break;

    if ( NWorld::PFBaseHero const * pHero = GetHero() )
    {
      MoveCameraTo( pHero, false );
    }
    break;
  case CMD_RAISEFLAG:
    {
      if (NWorld::PFFlagpole *pFlagpole = dynamic_cast<NWorld::PFFlagpole *> (pObj))
      {
        if ( pFlagpole->CanRaise( pHero->GetFaction() ) )
        {
          pCommand = CreateCmdRaiseFlag(GetHero(), pFlagpole, false);
        }
        else
        {
          if ( !InvulnerableFlagpoleReaction( pFlagpole, pHero->GetFaction() ) )
          {
            if ( !pFlagpole->IsOutermost( pHero->GetFaction() ) )
            {
              pLogic->SetErrorMessage( NDb::ERRORMESSAGETYPE_FLAGPOLETOOFAR);
            }
            else
            {
              if ( pFlagpole->IsRising() )
              {
                pLogic->SetErrorMessage( NDb::ERRORMESSAGETYPE_FLAGPOLECURRENTLYRISING);
              }
            }
          }
        }
      }
    }
    break;

  case CMD_INTERACT:
    {
      if ( NWorld::PFBaseUnit *pUnit = dynamic_cast<NWorld::PFBaseUnit*>(pObj) )
      {
        NDb::CastLimitation const* pDBCastLimitation = 0;
        if ( pUnit->CheckUseLimitations( pHero, pDBCastLimitation ) )
        {
          pCommand = CreateCmdUseUnit( GetHero(), pUnit );
        }
        else if ( pDBCastLimitation )
        {
          ProcessUnitEvent( pDBCastLimitation->uiEvent, pHero );
        }
      }
    }
    break;
	};

  if( IsValid( pCommand ) )
    SendGameCommand( pCommand, true );

  command       = pushedCommand;
  pushedCommand = CMD_NA;
  m_canExecuted = false;
}




void AdventureScreen::SetGameMenuMinigameInterface( NGameX::IGameMenuMinigameActions * actions )
{
  gameMenuMinigameInterface = actions;

  if ( IsValid( pLogic ) )
  {
    pLogic->GetEscMenuController()->SetMenuMinigameInterface(actions);
  }
}



void AdventureScreen::SendGameCommand( NCore::WorldCommand* _command, bool isPlayerCommand /*= false*/ )
{
  if ( !IsValid( pTransceiver ) )
    return;

  if ( !_command )
    return;

  CObj<NCore::WorldCommand> command( _command );
  pTransceiver->SendCommand( command, isPlayerCommand );
}



void AdventureScreen::SetState(State newState)
{
  if (m_newState == m_state)
    m_newState = newState;
}



void AdventureScreen::SwitchState()
{
  if (m_newState == m_state)
    return;

  m_state = m_newState;

  bool switchedToNormal = m_state == STATE_NORMAL;

  pLogic->SetErrorMessage(NDb::ERRORMESSAGETYPE_WAITINGFORTARGET, !switchedToNormal);

  if ( switchedToNormal )
    TargetZoneReset();
    
}



void AdventureScreen::OnMapLoaded( const NDb::AdvMapDescription * advMapDescription, const NDb::AdventureCameraSettings * cameraSettings )
{
  NI_PROFILE_FUNCTION;

  NI_VERIFY(advMapDescription, "Invalid map description to load", return);

  if (pLogic)
  {
    pLogic->UpdateDayNightState(GetWorld()->GetDayNightController());
    pLogic->SetDayNightWidgetVisible(!advMapDescription->map->dayNightSettings.hideDayNightWidget);
  }

  mapLoaded = true;

  if ( pWorld->GetMinigamesMain() )
    pWorld->GetMinigamesMain()->SetTransceiver( pTransceiver );

  visibilityMap = new VisibilityMapClient::Wrapped(pWorld);
  visibilityMap->SetSpectatorMode(IsSpectator());

  NWorld::PFBaseHero * pHero = GetHero();
  
  if ( pHero )
  {
    if (IsSpectator())
    {
      eventsUI.AddActivationHandler( "toggle_shared_vision", &AdventureScreen::OnToggleSharedVision);
    }
    else
    {
      // Unit dependent events
      eventsUI.AddActivationHandler( "cmd_move", &AdventureScreen::OnKeyCommand, CMD_MOVE);
      eventsUI.AddActivationHandler( "cmd_attack", &AdventureScreen::OnKeyCommand, CMD_ATTACK );
      eventsUI.AddActivationHandler( "cmd_stop", &AdventureScreen::OnKeyCommand, CMD_STOP );
      eventsUI.AddActivationHandler( "cmd_hold", &AdventureScreen::OnKeyCommand, CMD_HOLD );
      eventsUI.AddActivationHandler( "cmd_view", &AdventureScreen::OnKeyCommand, CMD_VIEW );
      eventsUI.AddActivationHandler( "cmd_smart_chat", &AdventureScreen::MsgSmartChatOpen );
    }

    {
      eventsUI.AddActivationHandler( "cmd_cancel", &AdventureScreen::CmdCancel );
    }

    NI_ASSERT(pHero->GetUnitType() == NDb::UNITTYPE_HEROFEMALE || pHero->GetUnitType() == NDb::UNITTYPE_HEROMALE, "Strange unit type");

    pHero->OnMapLoaded();
  }
  else
  {
    NI_ALWAYS_ASSERT("Failed to initialize: we do not have hero");
  }

  // init camera
  {
    NI_PROFILE_BLOCK( "Camera" );
    NScene::ICamera* camera = pScene->GetCamera();
    const Render::RenderMode& renderMode = Render::GetRenderer()->GetCurrentRenderMode();

    pFreeCameraController = new AdvancedFreeCameraController( pScene );
    pScene->GetCameraControllers()->AddCameraController( pFreeCameraController );
  
    pCameraController = new AdventureCameraController( pScene, pWorld->GetMapSize(), cameraSettings );
    pScene->GetCameraControllers()->AddCameraController( pCameraController );

    // Check if current user settings conflict with map settings and clamp accordingly
    const AdventureCameraController::CameraSettings& cs = pCameraController->GetSettings();
    float maxAllowedRod = cs.minRod + (cs.maxRod - cs.minRod) * cs.maxZoomFactor;
    if(s_camera_rod < 0.0f)
    {
      s_camera_rod = cs.maxRod;
    }
    else if(s_camera_rod > maxAllowedRod)
    {
      s_camera_rod = maxAllowedRod;
    }

    float pitch = ToRadian(-s_camera_pitch);
    float maxAllowedPitch = cs.minPitch + (cs.maxPitch - cs.minPitch) * (1.0f - cs.maxZoomFactor);
    if(s_camera_pitch < 0.0f)
    {
      pitch = cs.minPitch;
      s_camera_pitch = ToDegree(-pitch);
    }
    else if(pitch < maxAllowedPitch)
    {
      pitch = maxAllowedPitch;
      s_camera_pitch = ToDegree(-pitch);
    }

    pCameraController->SetInitialParameters(&s_camera_rod, &pitch);

    const float farPplane = 500.f;
    camera->SetPerspectiveTransform( pCameraController->GetFOV(), renderMode.width,  renderMode.height, 0.5f, 
                                      farPplane, pCameraController->GetFovCorrectionAngle() );
  }

  NDb::Ptr<NDb::AdvMapSettings> advMapSettings = 
    IsValid(advMapDescription->mapSettings) ? (advMapDescription->mapSettings) : (advMapDescription->map->mapSettings);

  if ( IsValid(advMapSettings) )
  {
    enableAnnouncements = advMapSettings->enableAnnouncements;

    minimap->InitAndSetImages( advMapSettings->overrideMinimapParams ? advMapSettings->overrideMinimapParams : pUIData->minimap, 
                                advMapDescription->map->minimapImages );

    objectsInfo2d->SetTooltipParams( advMapSettings->overrideTooltipParams );

    if ( pLogic )
    {
      pLogic->OnMapLoaded(advMapDescription, advMapSettings.GetPtr(),startInfo.isCustomGame);
      pLogic->SetComplains(complaintsToday,complaintsMax,complaintsInfo);
      pLogic->SetDialogs( pHero, advMapSettings->dialogsCollection, 
                            advMapSettings->hintsCollection, advMapSettings->questsCollection );
    }
  }
  SetLogicHero( GetHero() );


  OnHeroSetActive();
  GetMinimap()->SetWorldSize( GetWorld()->GetMapSize() );
  GetMinimap()->SetMinimapRotation( pCameraController->GetSettings().centerYaw );
  
  NMainFrame::FlashCurrentWindow();

  if ( advMapDescription->map->postEffect )
    PF_Render::Interface::Get()->SetPostFXParams( advMapDescription->map->postEffect );

  NDb::GetDbResourceCache().EnableAssertionLoadingFiles();
}



void AdventureScreen::OnSessionStart( lobby::TGameId _sessionId, bool inReconnectState /* false */ )
{
  isSessionStarted = true;
  sessionId = _sessionId;
  bindsController->SetEnabled(BindsController::Lua,true);
  bindsController->SetEnabled(BindsController::Chat,true);
  
  if (pLogic)
    pLogic->OnSessionStart( sessionId );

  if ( gameStatistics )
  {
    DebugTrace( "GameStatistics:LogPvxLogin" );
    gameStatistics->LogPvxLogin();
    gameStatistics->LogScreenResolution( UI::GetScreenResolution().x, UI::GetScreenResolution().y );
  }
  else
  {
    DebugTrace( "GameStatistics:NULL!" );
  }
  if ( GetHero() && !inReconnectState )
  {
    GetHero()->DoPetLogic();
  }
}


int FindNext( const string& str, const string& chars, int start )
{
  int result = string::npos;
  for( int i = 0; i < chars.size(); ++i )
  {
    int pos = str.find( chars[i], start );
    if ( pos != string::npos && ( pos < result || result == string::npos ) )
      result = pos;
  }
  return result;
}


void FillBots( const NDb::HeroesDB* heroes, const string& bots, hash_map<NDb::DBID, int>& lines )
{
  int start = 0;
  int line = 0;
  int pos = 0;

  if( bots.empty() ) 
    return;
  
  do
  {
    pos = FindNext( bots, ",;", start );
    if ( pos == string::npos )
      pos = bots.size();
    string id = bots.substr( start, pos - start );

    if( !id.empty() ) 
    {
      NDb::Ptr<NDb::BaseHero> hero = 0;
      for ( int i = 0; i < heroes->heroes.size(); ++i )
      {
        if ( heroes->heroes[i]->id == id )
        {
          hero = heroes->heroes[i];
          break;
        }
      }
      if ( !IsValid( hero ) )
      {
        NI_DATA_ASSERT( id.empty(), NStr::StrFmt( "Invalid hero name \"%s\"", id.c_str() ) );
      }
      else
        lines[hero->GetDBID()] = line;
    }
    
    if ( pos < bots.size() && bots[pos] == ';' )
      ++line;
    start = pos + 1;
  } while ( pos < bots.size() );
}


void AdventureScreen::StartBots( StartBotsFilter filter, bool inverse, bool midOnly /*= false*/)
{
	vector<CPtr<NWorld::PFBaseHero>> botsHeroes;
	int pairs[] = {-3, -3};
  for( int i = 0; i < pWorld->GetPlayersCount(); ++i )
  {
    NWorld::PFPlayer* player = pWorld->GetPlayer( i );
    if ( !IsValid( player ) || !IsValid( player->GetHero() ) )
      continue;

    NWorld::PFBaseHero* hero = player->GetHero();

    NCore::EPlayerType::Enum type = NCore::EPlayerType::Invalid;
    for( vector<NCore::PlayerStartInfo>::const_iterator it = startInfo.playersInfo.begin(); it != startInfo.playersInfo.end(); ++it )
    {
      if ( it->playerID == player->GetPlayerID() )
      {
        type = it->playerType;
        break;
      }
    }

    bool select = true;
    switch ( filter )
    {
    case FilterSelf:
      select = hero == GetHero();
      break;
    case FilterFriends:
      select = IsSameFaction( hero );
      break;
    case FilterHumans:
      select = type == NCore::EPlayerType::Human;
      break;
    }

    if ( inverse )
      select = !select;

    if ( select )
		{
			botsHeroes.push_back( hero );
			pairs[hero->GetTeamId()]++;
		}
  }

  hash_map<NDb::DBID, int> enemyBots, allyBots;
  FillBots( NDb::SessionRoot::GetRoot()->logicRoot->heroes, g_enemyBots, enemyBots );
  FillBots( NDb::SessionRoot::GetRoot()->logicRoot->heroes, g_allyBots, allyBots );

  int lines[] = {0, 0};
  int twoHeroesLine[] = {-1, -1};
	for( int i = 0; i < botsHeroes.size(); ++i )
	{
		if ( !IsValid( botsHeroes[i] ) )
			continue;

    // Add bots to 1 line if in midOnly mode
    if ( midOnly )
    {
      pWorld->AddAI( botsHeroes[i], 1 );
      continue;
    }

    int prefferedLine = -1;
    if ( IsSameFaction( botsHeroes[i] ) )
    {
      hash_map<NDb::DBID, int>::const_iterator pos = allyBots.find( botsHeroes[i]->GetDbHero()->GetDBID() );
      if ( pos != allyBots.end() )
        prefferedLine = pos->second;
    }
    else
    {
      hash_map<NDb::DBID, int>::const_iterator pos = enemyBots.find( botsHeroes[i]->GetDbHero()->GetDBID() );
      if ( pos != enemyBots.end() )
        prefferedLine = pos->second;
    }

    if ( prefferedLine >= 0 )
    {
      pWorld->AddAI( botsHeroes[i], prefferedLine );
    }
    else
    {
      const int teamId = botsHeroes[i]->GetTeamId();
      int& line = lines[teamId];

      int selectLine = 0;
      if ( !IsSameFaction(botsHeroes[i]) )
        selectLine = (line + 1) % 3; // order for enemy bots is 1 2 0
      else
        selectLine = (line + 2) % 3; // order for ally bots is 2 0 1

      pWorld->AddAI( botsHeroes[i], selectLine );
      if ( pairs[teamId] > 0 && ( !IsSameFaction(botsHeroes[i]) || selectLine != 1 ) ) // no pairs for ally bots at mid line
      {
		    for( int n = i + 1; n < botsHeroes.size(); ++n )
		    {
			    if ( IsValid( botsHeroes[n] ) && botsHeroes[n]->GetFaction() == botsHeroes[i]->GetFaction() && botsHeroes[n]->IsMale() != botsHeroes[i]->IsMale() )
			    {
				    pWorld->AddAI( botsHeroes[n], selectLine );
				    botsHeroes[n] = 0;
				    pairs[teamId]--;
            twoHeroesLine[teamId] = line;
				    break;
			    }
		    }
      }

		  line = (line + 1)%3;

      if ( line == twoHeroesLine[teamId] ) // skip line if it already has 2 heroes
        line = (line + 1)%3;
    }
	}
}



bool AdventureScreen::Init( UI::User * uiUser )
{
  NI_PROFILE_FUNCTION_MEM;

  if (pUIData->victoryDefeatImages.VictoryBurn)
    Render::Load2DTextureFromFile( pUIData->victoryDefeatImages.VictoryBurn->textureFileName.c_str() );
  if (pUIData->victoryDefeatImages.VictoryFreeze)
    Render::Load2DTextureFromFile( pUIData->victoryDefeatImages.VictoryFreeze->textureFileName.c_str() );
  if (pUIData->victoryDefeatImages.DefeatBurn)
    Render::Load2DTextureFromFile( pUIData->victoryDefeatImages.DefeatBurn->textureFileName.c_str() );
  if (pUIData->victoryDefeatImages.DefeatFreeze)
    Render::Load2DTextureFromFile( pUIData->victoryDefeatImages.DefeatFreeze->textureFileName.c_str() );

  AdventureScreenBase::Init( uiUser );
	
  saturationValue.Init( 1.0f, pUIData->bloodMaskParams.saturationChangeSpeed );

  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  if(binds)
    binds->ActivateSection( "adventure_screen" );

  announcementSoundPlayer = new QueueSoundPlayer();

	OpenUILayout( uiUser );

  objectsInfo2d = new ObjectsInfo2dLogic( 0 );
  objectsInfo2d->Init( uiUser );
  objectsInfo2d->SetSpectatorMode(IsSpectator());

  Reset( pingAbuseController, new GenericAbuseController( pUIData->pingAbuseSettings ) );
  Reset( smartChatAbuseController, new GenericAbuseController( pUIData->smartChatAbuseSettings ) );

  string fullFileName = NDebug::GenerateDebugFileName("replay", "rpl");
  NFile::CFilePath filePath = NFile::GetFilePath( fullFileName );
  if(!DoesFolderExist(filePath))
  {
    CreatePath( filePath );
  }
  string replayFname = startInfo.replayName;
  if(startInfo.replayName.empty())
    replayFname = fullFileName;

  // @todo Remove
  m_updated = false;

  InitUIEvents();

  isPlayingMinigame = false;


  //HACK: Scene must be updated once to function
  //TODO: Initialize scene properly
  pScene->Update( 0, 0, true );
  
  NGameX::ReplayInfo replayInfo;
  replayInfo.auid = startInfo.playersInfo[playerId].playerInfo.auid;
  replayInfo.mapName = GetWorld()->GetMapDescription()->GetDBID().GetFileName().c_str();
  replayInfo.heroId = playersInfo->GetPlayerData(playerId).GetHeroPersistentId().c_str();

  StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();
  if ( lgameControlCallback )
    lgameControlCallback->OnCombatScreenStarted( pWorld, replayInfo );

  //FIXME: Move this code _before_ 'OnCombatScreenStarted' call
  NI_ASSERT( IsValid( pTransceiver ), "" );
	return true;
}


void AdventureScreen::InitUIEvents()
{
  NDb::Ptr<NDb::UIEventsCustom> pCustomUiEvents = NDb::SessionRoot::GetRoot()->visualRoot->uiEvents;

  if ( !pCustomUiEvents )
    return;

  if ( pCustomUiEvents->evHeroDisconnected )
    evHeroDisconnected = new NGameX::PFUIEvent( pCustomUiEvents->evHeroDisconnected, 0 );

  if ( pCustomUiEvents->evHeroDisconnectedAFK )
    evHeroDisconnectedAFK= new NGameX::PFUIEvent( pCustomUiEvents->evHeroDisconnectedAFK, 0 );

  if ( pCustomUiEvents->evHeroLeft )
    evHeroLeft = new NGameX::PFUIEvent( pCustomUiEvents->evHeroLeft, 0 );

  if ( pCustomUiEvents->evHeroReconnected)
    evHeroReconnected = new NGameX::PFUIEvent( pCustomUiEvents->evHeroReconnected, 0 );

  if ( pCustomUiEvents->evHeroFriendDisconnected )
    evHeroFriendDisconnected = new NGameX::PFUIEvent( pCustomUiEvents->evHeroFriendDisconnected, 0 );

  if ( pCustomUiEvents->evHeroFriendDisconnectedAFK )
    evHeroFriendDisconnectedAFK = new NGameX::PFUIEvent( pCustomUiEvents->evHeroFriendDisconnectedAFK, 0 );

  if ( pCustomUiEvents->evHeroFriendLeft )
    evHeroFriendLeft = new NGameX::PFUIEvent( pCustomUiEvents->evHeroFriendLeft, 0 );

  if ( pCustomUiEvents->evHeroFriendReconnected)
    evHeroFriendReconnected = new NGameX::PFUIEvent( pCustomUiEvents->evHeroFriendReconnected, 0 );

  if ( pCustomUiEvents->evHeroAFK )
    evHeroAFK = new NGameX::PFUIEvent( pCustomUiEvents->evHeroAFK, 0 );

  if ( pCustomUiEvents->evHeroAFKEnded )
    evHeroAFKEnded = new NGameX::PFUIEvent( pCustomUiEvents->evHeroAFKEnded, 0 );

  if ( pCustomUiEvents->evBarrackDestroyed )
    evBarrackDestroyed = new NGameX::PFUIEvent( pCustomUiEvents->evBarrackDestroyed, 0 );

  if ( pCustomUiEvents->evFriendBarrackDestroyed )
    evFriendBarrackDestroyed = new NGameX::PFUIEvent( pCustomUiEvents->evFriendBarrackDestroyed, 0 );

  if ( pCustomUiEvents->evVictory )
    evVictory = new NGameX::PFUIEvent( pCustomUiEvents->evVictory, 0 );

  if ( pCustomUiEvents->evDefeat )
    evDefeat = new NGameX::PFUIEvent( pCustomUiEvents->evDefeat, 0 );

  if ( pCustomUiEvents->evSpectatorJoin)
    evSpectatorJoin = new NGameX::PFUIEvent( pCustomUiEvents->evSpectatorJoin, 0 );

  if ( pCustomUiEvents->evStartAiForPlayer )
    evStartAiForPlayer = new NGameX::PFUIEvent( pCustomUiEvents->evStartAiForPlayer, 0 );

  evAddGold = pCustomUiEvents->evGetNafta;
}



bool AdventureScreen::OnBeforeClose()
{
  NWorld::PFEaselPlayer *localPlayer = dynamic_cast<NWorld::PFEaselPlayer*>(GetHero());
  if (localPlayer)
    localPlayer->OnBeforeClose();

  StopGlobalSounds();

  if( IsValid(pWorld) )
    pWorld->OnDestroyContents(); // Cleanup world contents here, so it won't cause problems later

  pWorld = 0;
	pScene = 0;
  PF_Core::IUpdateable::ForcedClear();
  return AdventureScreenBase::OnBeforeClose();
}



void AdventureScreen::SetFreeCameraController( bool flag )
{
  NI_VERIFY( IsValid( pScene ), "Invalid scene!", return; );
  if (flag)
    pScene->GetCameraControllers()->AddCameraController( pFreeCameraController );
  else
    pScene->GetCameraControllers()->AddCameraController( pCameraController );
    
  gameOverEffect.setCameraCanBeMoved( !flag );
}

void AdventureScreen::Step( bool bAppActive )
{
  NI_PROFILE_FUNCTION

  {
    NI_PROFILE_BLOCK( "UI::Logic->DoCustomEvents" );

    float deltaTime = NMainLoop::GetTimeDelta();
    if ( pLogic &&  m_updated)
      pLogic->DoCustomEvents( deltaTime );
  }

  if (IsValid(pLogic) && GetWorld())
    pLogic->UpdateDayNightState(GetWorld()->GetDayNightController());

  NGameX::AdventureScreenBase::Step( bAppActive );
}

 

NWorld::PFBaseUnit* AdventureScreen::GetCurrentSelectedObject() const
{
  if (NWorld::PFBaseUnit *pUnit = dynamic_cast<NWorld::PFBaseUnit *>(selectedObject.GetPtr()) )
    return pUnit;

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float CalcCurSaturationLevel( const NDb::DamageBloodMaskParams &params, const NWorld::PFBaseHero *pHero, NDb::EFaction failedFaction )
{  
  if( pHero == 0 || pHero->GetFaction() == failedFaction )
    return params.afterLoseSaturation;
    
  if( pHero->IsResurrecting() )
    return params.lowHealthSaturation;
    
  if( pHero->IsDead() )
    return params.afterDeathSaturation;
  
  const float healthPercent = pHero->GetHealthPercent();
    
  if( healthPercent <= params.nearDeathLevel )
    return params.nearDeathSaturation;
    
  if( healthPercent <= params.lowHealthLevel )
    return params.lowHealthSaturation;
    
  return 1.0f;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float CalcCurSaturationChangeSpeed( const NDb::DamageBloodMaskParams &params, const NWorld::PFBaseHero *pHero, NDb::EFaction failedFaction )
{  
  if( pHero == 0 || pHero->GetFaction() == failedFaction )
    return params.saturationChangeSpeedAfterLose;

  return params.saturationChangeSpeed;
}


void AdventureScreen::UpdateSaturation( float deltaTime )
{
  Render::AOERenderer* pAOE = Render::GetAOERenderer();

  if ( uiBlockingController && uiBlockingController->IsBlocked() )
  {
    PF_Render::Interface::Get()->SetColorSaturation( uiBlockingController->GetFadeValue() );
    PF_Render::Interface::Get()->SetCustomSaturationColor( uiBlockingController->GetSaturationColor(), true );
    Render::GetUIRenderer()->SetSaturation( uiBlockingController->GetFadeValue(), uiBlockingController->GetSaturationColor(), true );

    if (pLogic)
    {
      pLogic->UpdateTooltipsSaturation();
    }

    if ( pAOE )
      pAOE->SetSaturation( uiBlockingController->GetFadeValue(), uiBlockingController->GetSaturationColor(), true );
  }
  else
  {
    saturationValue.Set( CalcCurSaturationLevel( pUIData->bloodMaskParams, GetHero(), failedFaction ) );
    saturationValue.SetSpeed( CalcCurSaturationChangeSpeed( pUIData->bloodMaskParams, GetHero(), failedFaction ));

    PF_Render::Interface::Get()->SetColorSaturation( saturationValue.Tick(deltaTime) );
    PF_Render::Interface::Get()->SetCustomSaturationColor( CVec4( 1.f, 1.f, 1.f, 1.f ), false );
    Render::GetUIRenderer()->SetSaturation( 1.f, CVec4( 1.f, 1.f, 1.f, 1.f ), false );

    if ( pAOE )
    {
      pAOE->SetSaturation( 1.f, CVec4( 1.f, 1.f, 1.f, 1.f ), false );
    }
  }
}

void AdventureScreen::CommonStep( bool bAppActive )
{
  NI_PROFILE_FUNCTION;

  UpdateScrolling();

  StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();
  if ( lgameControlCallback && !lgameControlCallback->IsGameReady() 
      || !lgameControlCallback && firstCommonStep )
  {
    return;
  }

  m_updated = true;

  if ( !IsValid( pScene ) )
    return;

  float curTime   = NMainLoop::GetTime();
  float deltaTime = NMainLoop::GetTimeDelta();

  UpdateSaturation( deltaTime );

  if ( NSoundScene::GetActiveSoundScene() == NDb::SOUNDSCENE_TOWERDEATH )
  {
    towerDeathTimer += deltaTime;
  }

  m_eventTimeLeft += deltaTime * 1000.0f;

  if (IsValid(visibilityMap))
    visibilityMap->Update(deltaTime);

  bool isAnimationsPaused =  m_gamePause == PAUSE_HARD || m_gamePause == PAUSE_PLAYER;
  {
    NI_PROFILE_BLOCK( "Client" );

    NDb::EFaction faction = NDb::FACTION_NEUTRAL;
    if ( NWorld::PFBaseHero const* pHero = GetHero() )
      faction = pHero->GetFaction();

    {
      //Init camera params here due to screen resolution can be changed on fly
      const Render::RenderMode& renderMode = Render::GetRenderer()->GetCurrentRenderMode();
      pScene->GetCamera()->SetScreenSize( renderMode.width,  renderMode.height );
    }                               

    NScene::SCameraPosition camPos;
    pScene->GetCamera()->GetPosition(&camPos);
    GetMinimap()->SetCameraPosition(camPos.GetCameraPos());
    if ( g_minimap_rotate )
      GetMinimap()->SetMinimapRotation( camPos.fYaw );

    // update ambience percents
    UpdateAmbientSound(camPos);

    NWorld::PFLogicObject const* pLO       = dynamic_cast<NWorld::PFLogicObject const*>( selectedObject.GetPtr() );
    NGameX::PFClientLogicObject const* pCO = pLO ? pLO->ClientObject() : NULL;
    if( NULL == pCO || !pCO->IsVisible() )
      SetSelectedObject(NULL, NULL);

    {
      if ( m_newState != m_state )
        SwitchState();

      UpdateState();

      GetMinimap()->BeginUpdate( deltaTime );

      if ( !isAnimationsPaused )
      {
        PF_Core::IUpdateable::ProceedUpdate( deltaTime * pWorld->GetSlowdownHint() );
      }
      else
      {
        PF_Core::IUpdateable::ProceedUpdate( 0.0f );   // PAUSE animations
      }
      GetMinimap()->EndUpdate();

      pLogic->SetSelectedUnit(dynamic_cast<NWorld::PFBaseUnit*>(selectedObject.GetPtr()));

    }

    markersController->Update( deltaTime );
    pingAbuseController->Update( deltaTime );
    smartChatAbuseController->Update( deltaTime );
  }

  // Support moving objects somehow
  {
    NI_PROFILE_BLOCK( "Pick" );
    if (vCursorPos.x != -1.f && vCursorPos.y != -1.f)
      UpdatePick();
  }

  // Update scene & scene objects in it
  {
    NI_PROFILE_BLOCK( "Scene" );
    //adventure screen IsGamePaused bugs if pause received from another node
    pScene->Update( curTime, deltaTime * pWorld->GetSlowdownHint(), isAnimationsPaused ) ;
    if ( !isAnimationsPaused )
    {
      PF_Core::IUpdateableAfterScene::ProceedUpdate( deltaTime * pWorld->GetSlowdownHint() ); 
    }
  }

  //UpdateCursors();
  TargetZoneUpdate();
  bCursorInScene = false;

  // Update fly text's logic
  {
    NI_PROFILE_BLOCK( "FlyTexts and Overtips" );

    pLogic->m_flyTexts->Update( deltaTime, pScene->GetCamera()->GetProjectiveMatrix() * pScene->GetCamera()->GetViewMatrix());

    if ( objectsInfo2d )
    {
        UpdatePickedObject();
        UpdateSelectedObject();

        objectsInfo2d->Update( deltaTime, pScene->GetCamera()->GetProjectiveMatrix() * pScene->GetCamera()->GetViewMatrix() );
    }
  }

  if ( pScene )
    Render::DebugRenderer::ImplementationSet3DProjection( pScene->GetCamera()->GetProjectiveMatrix() * pScene->GetCamera()->GetViewMatrix() );

  // No more XP
  // hero_Exp.SetValue( GetHero() ? GetHero()->GetExperience() : 0 );
  // hero_LExp.SetValue( GetHero() ? GetHero()->GetLevelMaxExperience() : 0 );
  if (debugMousePick.enabled)// && NMainLoop::GetTime() - debugMouseDown.time > 2) 
  {
    debugMousePick.time = NMainLoop::GetTime();
    Render::DebugRenderer::DrawCircle3D(debugMousePick.vOnMouseMovePoint, 1.0f, 15, Render::Color(10,255,10), true);
    Render::DebugRenderer::DrawCircle3D(debugMousePick.vOnMouseDownPoint, 1.3f, 15, Render::Color(10,10,255), true);
  }


  bloodMask->Update( deltaTime );

  impulseBuffsManager->Update( deltaTime );

  if ( uiBlockingController )
    uiBlockingController->Update( deltaTime );

  Render::GetUIRenderer()->SetViewMatrices( pScene->GetCamera()->GetViewMatrix(), pScene->GetCamera()->GetProjectiveMatrix() );

  // If we are at the beginning of the session - start ambient sound, which will play on the background all the time
  if (firstCommonStep)
  {
    StartGlobalSounds();
    gameOverEffect.UpdateBuildingsInfo( pWorld->GetAIWorld() );
    firstCommonStep = false;
  }

  if ( pWorld->GetAIWorld()->WasGameFinished() )
  {
    HappyCreaturesStep( deltaTime );
  }

  if (pCameraController && pLogic)
    pCameraController->EnableMouseZoom(!pLogic->IsMouseUnderWindow());

  gameOverEffect.Update(deltaTime);
  
  if( endGameTimer.Tick(deltaTime) && pLogic->IsGameEnded() )
  {
    if( GetHero()->GetFaction() != failedFaction )
      NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_WIN, false );
    else
      NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_DEFEAT, false );

    if (skipTutorial)
      ExitGame(true);
  }

  if ( sceneFader )
  {
    sceneFader->Tick( deltaTime );
    if ( objectsInfo2d )
      objectsInfo2d->GetBaseWindow()->Show(sceneFader->IsActive());
  }

  WaitLeaveAck();
}


void AdventureScreen::HappyCreaturesStep( float dt )
{
  NI_VERIFY( pWorld->GetAIWorld()->WasGameFinished(), "Game is not finished!", return );

  happyCheckTimer -= dt;

  if ( happyCheckTimer < 0.0f )
  {
    int winnedCreatures = 0;
    int happyCreatures  = 0;
    nstl::vector<NWorld::PFBaseUnit*> readyCreatures;

    struct HappyCounter
    {
      NDb::EFaction failedFaction;

      int* winnedCreatures;
      int* happyCreatures;
      nstl::vector<NWorld::PFBaseUnit*>* readyCreatures;

      HappyCounter( NDb::EFaction _failedFaction, int* _winnedCreatures, int* _happyCreatures, nstl::vector<NWorld::PFBaseUnit*>* _readyCreatures ) :
        failedFaction   ( _failedFaction   ),
        winnedCreatures ( _winnedCreatures ),
        happyCreatures  ( _happyCreatures  ),
        readyCreatures  ( _readyCreatures  ) { }

      void operator()( NWorld::PFBaseUnit& unit )
      {
        NWorld::PFBaseUnit* pUnit = &unit;
        bool canBeHappy = ( pUnit->GetUnitType() == NDb::UNITTYPE_HEROMALE ) || ( pUnit->GetUnitType() == NDb::UNITTYPE_SUMMON )     ||
                          ( pUnit->GetUnitType() == NDb::UNITTYPE_CREEP )    || ( pUnit->GetUnitType() == NDb::UNITTYPE_SIEGECREEP ) ||
                          ( pUnit->GetUnitType() == NDb::UNITTYPE_PET )      || ( pUnit->GetUnitType() == NDb::UNITTYPE_FACTIONCHAMPION );

        if ( canBeHappy && IsUnitValid( pUnit ) && ( pUnit->GetOppositeFaction() == failedFaction ) )
        {
          (*winnedCreatures)++;
          switch ( pUnit->ClientObject() ? pUnit->ClientObject()->GetHappyState() : EHappyState::Happy )
          {
          case EHappyState::Ready:
            readyCreatures->push_back( pUnit );
            break;
          case EHappyState::Happy:
            (*happyCreatures)++;
            break;
          }
        }
      }
    }happyCounter( failedFaction, &winnedCreatures, &happyCreatures, &readyCreatures );
    GetWorld()->GetAIWorld()->ForAllUnits( happyCounter );

    int happyCreaturesRequired = Round( winnedCreatures *
      GetWorld()->GetAIWorld()->GetAIParameters().creatureHappyStateParams.happyCreaturesPercent );
    int creaturesToMakeHappy = Min( happyCreaturesRequired - happyCreatures, readyCreatures.size() );

    if ( creaturesToMakeHappy > 0 )
    {
      for ( nstl::vector<NWorld::PFBaseUnit*>::iterator iter = readyCreatures.begin(); iter != readyCreatures.end(); iter++ )
      {
        if ( NRandom::Random( 1, readyCreatures.size() ) <= creaturesToMakeHappy )
        {
          (*iter)->SetHappy();
        }
      }
    }

    happyCheckTimer += GetWorld()->GetAIWorld()->GetAIParameters().creatureHappyStateParams.happyCheckTick;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawMapDebug(NWorld::PFWorld* pWorld);

void AdventureScreen::Draw( bool bAppActive )
{
  NI_PROFILE_FUNCTION


  StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();
  if ( lgameControlCallback )
    if ( !lgameControlCallback->IsGameReady() )
      return;

  if ( !IsValid( pScene ) )
    return;

  pScene->Draw();

  if ( gShowUserInterface > 0 && objectsInfo2d )
    objectsInfo2d->RenderWindows();

  if ( gShowUserInterface == 1 && pLogic )
    pLogic->RenderWindows();

  DrawMapDebug(pWorld);

  if (NWorld::FogOfWar const * pWarFog = pWorld->GetFogOfWar())
    pWarFog->DrawWarFogDebug(pWorld);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AdventureScreen::ProcessUIEvent( const Input::Event & message )
{
  if (exitingGame)
    return true;

  isHotKeyDown = false;
  StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();
  if ( lgameControlCallback )
    if ( !lgameControlCallback->IsGameReady() )
      return false;

  if ( !m_updated )
    return false;

	if ( bAdventureControlsEnabled && pScene && pScene->GetCameraControllers()->ProcessEvent( message ) )
		return true;

  if( pLogic->ProcessUIEvent( message ) )
    return true;

  return DefaultScreenBase::ProcessUIEvent( message );
}



bool AdventureScreen::ProcessSceneEvent( const Input::Event & message )
{
  if (exitingGame)
    return true;

  StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();
  if ( lgameControlCallback )
    if ( !lgameControlCallback->IsGameReady() )
      return false;

  return AdventureScreenBase::ProcessSceneEvent( message );
}



bool AdventureScreen::OpenUILayout( UI::User * uiUser )
{
	pLogic = new AdventureScreenLogic( chatController, smartChatController, bindsController );

  SetLogic( pLogic );
  pLogic->SetUser( uiUser );
	pLogic->LoadScreenLayout( "Combat" );
  pLogic->SetOwner( this, pUIData, playersStartInfo, socialServer );

  UI::Window * logicBaseWindow = pLogic->GetBaseWindow();
  UI::FlashContainer2 * flashWnd =  UI::GetChildChecked<UI::FlashContainer2>( logicBaseWindow, "FlashScreen", true );
  minimap = new Minimap( flashWnd, pLogic->GetFlashInterface());
  minimap->SetSpectatorMode(IsSpectator());
  markersController = new MarkersController( pUIData, minimap, heroFaction);

  bloodMask = new DamageBloodMask(UI::GetChildChecked<UI::ImageLabel>(  pLogic->GetBaseWindow(), "UIRedHit", true ), pUIData->bloodMaskParams);

  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();

  if(binds)
  {
    const Input::TBinds& tBind = binds->GetBindStrings();

    Input::TBinds::const_iterator binbsIter = tBind.begin();
    for(; binbsIter != tBind.end(); ++binbsIter)
    {
      Input::TBindStrings &bindStrings = binbsIter->second;
      Input::TBindStrings::const_iterator iter = bindStrings.begin();

      while(iter != bindStrings.end())
      {
        pLogic->GetFlashInterface()->SetBindString((*(iter++)));
      }
    }
  }

  if ( uiBlockingController )
  {
    uiBlockingController->SetFlashContainer( flashWnd );
    uiBlockingController->SetFlashInterface( pLogic->GetFlashInterface() );
    uiBlockingController->SetSaturationColor( CVec4( pUIData->blockSaturationColor.R, pUIData->blockSaturationColor.G, pUIData->blockSaturationColor.B, 1.f ) );
  }

  if (chatController)
  {
    chatController->LoadPlayerIcons(GetWorld()->GetMapDescription(), playersStartInfo);
  }

	return true;
}


void AdventureScreen::MsgOnExitGame()
{
  OnCloseApplication();
}


void AdventureScreen::UpdateScrolling()
{
  if ( !pLogic || !pLogic->IsMouseEnabled() || mouse3Pressed || !g_mouseScrollingEnable || !bAdventureControlsEnabled )
  {
    scrollOffset = VNULL2;
    return;  
  }

  const UI::Point uiMousePos = pLogic->GetWindowRegardlessMousePosition();
  const SVector mousePos( uiMousePos.x, uiMousePos.y );

  scrollOffset = CalcScrollOffset( mousePos, pUIData->mouseScrollingFieldSize );
    
  if ( scrollOffset != VNULL2 && GetCamera() )
    GetCamera()->AddOffsetToPosition( scrollOffset );
}

bool AdventureScreen::MsgOnMouseMove( const Input::SSysParams & sysParams )
{
  bCursorInScene = true;

  SetCursorPos( CVec2( sysParams.GetMouseX(), sysParams.GetMouseY() ) );

  return false;
}

bool AdventureScreen::IsActionCmd( UI::EMButton::Enum action )
{
  if( m_state == STATE_TARGET )
    return action == UI::EMButton::Right;
  else if( g_casualControlStyle )
    return action == UI::EMButton::Left;
  else 
    return action == UI::EMButton::Right;
}

bool AdventureScreen::IsSelectionCmd( UI::EMButton::Enum action )
{
  if( m_state == STATE_TARGET  )
    return action == UI::EMButton::Left;
  else if( g_casualControlStyle )
    return action == UI::EMButton::Right;
  else
    return action == UI::EMButton::Left;
}

bool AdventureScreen::IsMinimapSignalCmd( UI::EMButton::Enum action )
{
  return GetHero() != 0 && action == UI::EMButton::Left && ( minimapSignalKey || command == CMD_SIGNAL);
}

bool AdventureScreen::UseSmartChat()
{
  bool ok = true;

  if (smartChatAbuseController)
  {
    ok = smartChatAbuseController->Use();

    if (!ok)
    {
      const SingleValueNameMapFloat values(smartChatAbuseController->GetCooldown());

      pLogic->SetErrorMessage(NDb::ERRORMESSAGETYPE_SMARTCHATRESTRICTED, true, &values);
    }
  }

  return ok;
}

bool AdventureScreen::MsgOnMouseDownImpl( const Input::SSysParams & sysParams, UI::EMButton::Enum action  )
{
  if ( !bAdventureControlsEnabled )
    return false;

  
  if (debugMousePick.enabled)
  {
    if ( vCursorPos.x != -1.f && vCursorPos.y != -1.f )
      UpdateTerrainPick();

    CVec2 prevMousePos = vCursorPos;
    debugMousePick.vOnMouseMovePoint = currentPick.GetPickedPos();
    SetCursorPos( CVec2(sysParams.GetMouseX(), sysParams.GetMouseY()) );
    UpdateTerrainPick();
    debugMousePick.vOnMouseDownPoint = currentPick.GetPickedPos();
    
    if (updateMouseMode == 0)
    {
      SetCursorPos( prevMousePos );
      UpdateTerrainPick();
    }
  }
  else
  {
    if (updateMouseMode == 1)
    {
      SetCursorPos( CVec2(sysParams.GetMouseX(), sysParams.GetMouseY()) );
      UpdateTerrainPick();
    }
    else
    {
      if ( vCursorPos.x != -1.f && vCursorPos.y != -1.f )
        UpdateTerrainPick();
    }
  }
    

  
  if( currentPick.GetPickedNormal() == VNULL3 )
    return false;

  if( IsMinimapSignalCmd(action) )
    ExecuteCommand( CMD_SIGNAL, currentPick.GetPickedPos(), currentPick.GetPickedPtr() );
  else if( IsSelectionCmd(action) )
    OnSelectionButtonMouseClick( currentPick.GetPickedPos(), true );
  else if( IsActionCmd(action) )
    OnActionButtonMouseClick( currentPick.GetPickedPos(), true );  
  
  return false;
}

bool AdventureScreen::MsgOnLMouseDown( const Input::SSysParams & sysParams )
{
  return MsgOnMouseDownImpl( sysParams, UI::EMButton::Left );
}

bool AdventureScreen::MsgOnRMouseDown( const Input::SSysParams & sysParams ) //!! TEMPORARY
{
  return MsgOnMouseDownImpl( sysParams, UI::EMButton::Right );
}

void AdventureScreen::MsgOnMouse3Down()
{
  mouse3Pressed = true;
}



void AdventureScreen::MsgOnMouse3Up()
{
  mouse3Pressed = false;
}



bool AdventureScreen::CmdCancel()
{
  if ( m_state == STATE_NORMAL )
  {
    bool processed = false;
    if ( IsValid( gameMenuMinigameInterface ) )
      if ( gameMenuMinigameInterface->OnGameMenuEscapeButton() )
        processed = true;

    if ( !processed )
    {
      SetSelectedObject(NULL, NULL);
      processed = pLogic->GetFlashInterface()->OnEscape();
    }

    // Cancel channelling
    // isHotkeysEnabled check is a check for opened Esc menu; don't want to cancel channelling while esc menu is active
    // [11/08/2011] There is no other means to know whether esc menu is active or not
    if ( !processed && bAdventureControlsEnabled && isHotkeysEnabled && !channellingIsCancelling )
    {
      NWorld::PFBaseHero* pHero = GetHero();
      if ( pHero->IsInChannelling() )
      {
        SendGameCommand( NWorld::CreateCmdCancelChannelling( GetHero() ), true );
        channellingIsCancelling = true; // this flag prevents blocking of esc menu user call in case of delayed command execution
        processed = true;
      }
    }

    if (!processed)
    {
      // TEMP: NUM_TASK не показываем игровое меню, если активен какой-нибудь диалог
      if (pLogic->GetDialogController() && !pLogic->GetDialogController()->IsDialogFinished(NULL))
        ;
      else
        pLogic->GetFlashInterface()->OpenEscMenu();

      processed = true;
    }
   
  }
  else if ( m_state == STATE_TARGET )
  {
    CancelCommand();
    SetState(AdventureScreen::STATE_NORMAL);
  }

  return true;
}


  void AdventureScreen::OnShowAGDebugInformation()
  {
    DebugEnableAGLog(currentPick.GetPickedPtr(), minimapSignalKey);
  }

  void AdventureScreen::OnDumpStatesDebugInformation()
  {
    if (NULL == selectedObject || NULL == selectedSceneObject)
      return;

    if (NWorld::PFBaseUnit* pUnit = dynamic_cast<NWorld::PFBaseUnit*>(selectedObject.GetPtr()))
    {
      pUnit->SetDumpStates(!pUnit->IsDumpStates());
    }    
  }

  void AdventureScreen::OnDumpStatesStack()
  {
    if (NULL == selectedObject || NULL == selectedSceneObject)
      return;

    if (NWorld::PFBaseUnit* pUnit = dynamic_cast<NWorld::PFBaseUnit*>(selectedObject.GetPtr()))
    {    
      pUnit->SetDumpStates(true);
      pUnit->DumpAllStates();
    }    
  }

	void AdventureScreen::OnResetClientObjects()
	{
		if ( IsValid(pWorld) )
    {
			pWorld->ResetClientObjects();
    }
	}

	void AdventureScreen::OnSaveWorld()
	{
		if ( IsValid(pWorld) )
			pWorld->GetWorldChecker()->Save();
	}

	void AdventureScreen::OnLoadWorld()
	{
		if ( IsValid(pWorld) )
		{
			pWorld->GetWorldChecker()->Load();
			pWorld->ResetClientObjects();
		}
	}

	bool AdventureScreen::MsgOnKeyDown( const Input::SSysParams & sysParams )
	{ 
    // AT: if the user has the opened chat transfer all key messages to it 
    // Except ESC key : if ESC was pressed we should grant the ability to process it to any active window
    if ( IsActiveChat() && sysParams.first != 27 )
      return false;

    switch ( tolower( sysParams.first ) )
		{
      case 'v':
      {
        if(NWorld::PFBaseUnit const* pUnit = 
          dynamic_cast<NWorld::PFBaseUnit const*>(currentPick.GetPickedPtr()))
        {
          if(NWorld::PFPlayer const* pPlayer = pWorld->GetPlayer(playerId))
            NWorld::DumpUnitInfo(GetSystemLog(), pUnit);
        }
        break;
      }
    
#ifndef _SHIPPING
      case VK_CANCEL:		// Ctrl+C ...
      case 'c':
      {
        if ( bCtrlPressed )
          CreateCheatCmd("hero_set_active");
        break;
      }
#endif // #ifndef _SHIPPING
      case 'e':
      {
        //SendGameCommand( NWorld::CreateCmdEmote( GetHero(), NDb::EMOTION_HAPPY) );
        break;
      }

      case 'q':
      {
        if ( bCtrlPressed )
          DebugEnableAGLog(currentPick.GetPickedPtr(), minimapSignalKey);
        break;
      }
      default:
        break;
		}; // End of switch

    return false;
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureScreen::MsgOnImpulsiveBuffDown()
{
  if (!isHotkeysEnabled)
    return;

	if ( pLogic )
		pLogic->ActivateImpulsiveBuff();
}

void AdventureScreen::SelfCastOn()
{
  isSelfCastOn = true;
}

void AdventureScreen::SelfCastOff()
{
  isSelfCastOn = false;
}

void AdventureScreen::MsgOnShowStatistics()
{
  if (!isHotkeysEnabled || ( blockedHotKeys & ( 1 << FlashWindowsType::CurStatistics ) ) ) 
    return;

  if ( pLogic )
    pLogic->GetStatisticsController()->TabPressed(true);
}

void AdventureScreen::MsgOnHideStatistics()
{
  if (!isHotkeysEnabled || ( blockedHotKeys & ( 1 << FlashWindowsType::CurStatistics ) ) )
    return;

  if ( pLogic )
    pLogic->GetStatisticsController()->TabPressed(false);
}

void AdventureScreen::MsgOnShowCharStat()
{ 
  if (!isHotkeysEnabled || ( blockedHotKeys & ( 1 << FlashWindowsType::CharStat ) ) )
    return;

  AdventureFlashInterface * flashInterface = pLogic->GetFlashInterface();
  if (flashInterface)
    flashInterface->ShowHideWindow(FlashWindowsType::CharStat);
}

void AdventureScreen::MsgOnShowInventory()
{
  if (!isHotkeysEnabled || ( blockedHotKeys & ( 1 << FlashWindowsType::Inventory ) ) )
    return;

  AdventureFlashInterface * flashInterface = pLogic->GetFlashInterface();
  if (flashInterface)
    flashInterface->ShowHideWindow(FlashWindowsType::Inventory);
}


void AdventureScreen::MsgChatOpenClose()
{
  if (!isHotkeysEnabled || ( blockedHotKeys & ( 1 << FlashWindowsType::Chat ) ))
    return;

  pLogic->ActivateChat();
}


bool AdventureScreen::MsgChatOpenChannel(const NDb::EChatChannel & channelID )
{
  if (!isHotkeysEnabled || ( blockedHotKeys & ( 1 << FlashWindowsType::Chat ) ))
    return false;

  pLogic->ActivateChatChannel(channelID);

  return true;
}


void AdventureScreen::MsgSmartChatOpen()
{
  if (!isHotkeysEnabled || ( blockedHotKeys & ( 1 << FlashWindowsType::SmartChat ) ))
    return;

  pLogic->ActivateSmartChat();
}


void AdventureScreen::MsgOnShowTalents()
{
  if (!isHotkeysEnabled || ( blockedHotKeys & ( 1 << FlashWindowsType::Talents ) ) )
    return;

  AdventureFlashInterface * flashInterface = pLogic->GetFlashInterface();
  if (flashInterface)
    flashInterface->ShowHideWindow(FlashWindowsType::Talents);
}

void AdventureScreen::MsgShowHealthbars()
{
  if (isHotkeysEnabled)
    objectsInfo2d->ShowHealthBars( true );
}

void AdventureScreen::MsgOnFullScreen()
{
  NGlobal::SetVar("gfx_fullscreen",!NGlobal::GetVar("gfx_fullscreen").GetInt64(),STORAGE_USER);
  if( pLogic )
    pLogic->UpdatePreferences();
}


void AdventureScreen::MsgHideHealthbars()
{
  if (isHotkeysEnabled)
    objectsInfo2d->ShowHealthBars( false );
}



void AdventureScreen::MsgToggleHealthbars()
{
  if (isHotkeysEnabled)
    objectsInfo2d->ToggleShowHealthBars();
}

void AdventureScreen::CameraSwitchAttachModeDown()
{
  if (!isHotkeysEnabled || !bAdventureControlsEnabled)
    return;

  if (!IsUnitValid(GetHero()))
    return;

  const bool attachMode = NGlobal::GetVar( "lock_camera" ).Get<bool>();
  bCameraSwitchAttachControlled = true;

  if(attachMode || bCameraSwitchAttachControlled)
  {
    SetObservingObject( !attachMode ? ( IsValid( GetHero()->GetMount() ) ? GetHero()->GetMount() : GetHero() ) : 0, true );
    pLogic->GetFlashInterface()->SetCameraLock( !attachMode );
  }
}

void AdventureScreen::CameraSwitchAttachModeUp()
{
  if (!isHotkeysEnabled || !bAdventureControlsEnabled)
    return;

  const bool attachMode = NGlobal::GetVar( "lock_camera" ).Get<bool>();
  bCameraSwitchAttachControlled = false;

  if(attachMode || !bCameraSwitchAttachControlled)
  {
    SetObservingObject( attachMode ? ( IsValid( GetHero()->GetMount() ) ? GetHero()->GetMount() : GetHero() ) : 0, true );
    pLogic->GetFlashInterface()->SetCameraLock( attachMode );
  }
}


#ifdef DIANGR_SCREEN_DEBUG_GENERAL
  void AdventureScreen::DebugAnimGraphSetPrevGraph()
  {
    DiAnimGraph::DebugSetPrevGraph();
  }
  void AdventureScreen::DebugAnimGraphSetNextGraph()
  {
    DiAnimGraph::DebugSetNextGraph();
  }
  void AdventureScreen::DebugAnimGraphIncSpeed()
  {
    DiAnimGraph::DebugIncSpeed();
  }
  void AdventureScreen::DebugAnimGraphDecSpeed()
  {
    DiAnimGraph::DebugDecSpeed();
  }
  void AdventureScreen::DebugAnimGraphChangeSpeedDelta()
  {
    DiAnimGraph::DebugChangeSpeedCoeffPrecision();
  }
  void AdventureScreen::DebugAnimGraphChangeObject()
  {
    DiAnimGraph::DebugChangeObject();
  }
#else
  void AdventureScreen::DebugAnimGraphSetPrevGraph() {}
  void AdventureScreen::DebugAnimGraphSetNextGraph() {}
  void AdventureScreen::DebugAnimGraphIncSpeed() {}
  void AdventureScreen::DebugAnimGraphDecSpeed() {}
  void AdventureScreen::DebugAnimGraphChangeSpeedDelta() {}
  void AdventureScreen::DebugAnimGraphChangeObject() {}
#endif

  void AdventureScreen::ProcessSignal()
  {
    CancelCommand();
    SetCommand( CMD_SIGNAL );
    TargetZoneReset();
    SetState( AdventureScreen::STATE_TARGET );
  }

 void AdventureScreen::SetCursorPos(CVec2 const& _vCursorPos)
 {
	 vCursorPos = _vCursorPos;
   if ( pWorld )
    lastPlayerActivityStep = pWorld->GetStepNumber();
 }

  void AdventureScreen::UpdatePick()
  {
    NI_PROFILE_FUNCTION;

    if( !IsValid(pScene) )
      return;
    if ( isPlayingMinigame || !bAdventureControlsEnabled )
      return;

		NI_ASSERT(vCursorPos.x != -1 && vCursorPos.y != -1, "Uninitialized vCursorPos value");
    
    pScene->GetCamera()->GetProjectiveRay(&cursorRay.ptOrigin, &cursorRay.ptDir, vCursorPos);

    NScene::PickResult pickResult;
    pScene->PickObjects( &pickResult, cursorRay.ptOrigin, cursorRay.ptDir);

    CVec3 terainPick(VNULL3);
    if ( pScene->PickTerrain( terainPick, cursorRay.ptOrigin, cursorRay.ptDir ) )
    {
      cursorPosOnTerrain = terainPick;
    }

    currentPick.PickedPos()    = VNULL3;
    currentPick.PickedNormal() = VNULL3;

    CPtr<PF_Core::WorldObjectBase> pPO = NULL;
    NScene::SceneObject*        pPSO = NULL;
    int objectID = PF_Core::INVALID_OBJECT_ID;
    
    bool isMouseUnderWindow = pLogic? pLogic->IsMouseUnderWindow(): false;

    if (!isMouseUnderWindow)
    {
      if ( m_state == STATE_TARGET )
      {
        if ( m_talentLevel != -1 && m_talentSlot != -1 && GetHero()->GetTalent(m_talentLevel, m_talentSlot) )
        {
          NWorld::PFTalent *pTalent = GetHero()->GetTalent(m_talentLevel, m_talentSlot);
          objectID = objectSelector.GetBestObject( pickResult, cursorRay, true, pTalent );
        }
        else if ( m_abilityIndex != -1 && GetHero()->GetConsumable(m_abilityIndex) )
        {
          NWorld::PFAbilityData* ability = GetHero()->GetConsumable(m_abilityIndex)->GetAbility();
          objectID = objectSelector.GetBestObject( pickResult, cursorRay, true, ability );
        }
        else
        {
          objectID = objectSelector.GetBestObject( pickResult, cursorRay, false, 0 );
        }
      }
      else
      {
        objectID = objectSelector.GetBestObject( pickResult, cursorRay, false, 0 );
      }
    }

    if ( objectID != PF_Core::INVALID_OBJECT_ID)
    {
      pPO = pWorld->GetObjectById(objectID);
      pPSO = pPO->GetClientSceneObject();
    }
    if( pPO != currentPick.GetPickedPtr() )
    {
      currentPick.SetPickedObjects(pPO, pPSO);
    }
  }


  void AdventureScreen::UpdateTerrainPick()  
	{    
		if( !IsValid(pScene) )      
			return;		
		//NI_ASSERT(vCursorPos.x != -1 && vCursorPos.y != -1, "Uninitialized vCursorPos value");       
		pScene->GetCamera()->GetProjectiveRay(&cursorRay.ptOrigin, &cursorRay.ptDir, vCursorPos);    
		if ( pScene->PickTerrain( currentPick.PickedPos(), cursorRay.ptOrigin, cursorRay.ptDir ) )    
		{      
			pScene->GetHeightsController().GetHeight(currentPick.GetPickedPos().x, currentPick.GetPickedPos().y, 1,                                              
				&currentPick.PickedPos().z, &currentPick.PickedNormal() );    

#ifndef _SHIPPING
      // NatureMap DEBUG
      {
        Terrain::NatureMap &nm = pScene->GetTerrain()->GetNatureMap();
        Terrain::NatureMapElementId id = nm.LocateElement(currentPick.GetPickedPos().x, currentPick.GetPickedPos().y);
        if (id == Terrain::NATUREMAPELEMENTID_BAD)
        {
          terrain_Owner.SetValue( 0 );
        }
        else
        {
          terrain_Owner.SetValue( nm.GetElementInfo( id ).ownerData );
        }
      }
#endif
		}  
	}  



void AdventureScreen::UpdateState()
{
  NI_PROFILE_FUNCTION

  const NWorld::PFBaseHero * pHero = GetHero();

  if ( m_state == STATE_NORMAL )
  {
    if ( pHero && pHero->IsDead() ) 
    {
      SetObservingObject(0);
      TargetZoneReset();
      return;
    }
  }
  else if ( m_state == STATE_TARGET )
  {
    NI_ASSERT( pHero, "Invalid owned hero");
    if ( !pHero || pHero->IsDead() )
    {
      if ( command != CMD_SIGNAL )
        CancelCommand();

      SetObservingObject(0);
      TargetZoneReset();
      //SetState(STATE_DIE);
    }
    else
    {
      bool dropTargetState = false;

      switch ( command )
      {
        case CMD_ITEM:
        {
          const int slot = m_abilityIndex;
          if ( !pHero->CanUseConsumable( slot ) )
          {
            dropTargetState = true;
          }
        }
        break;

        case CMD_TALENT_TALENT_PANEL:
        {
          if ( NWorld::PFBaseMaleHero const* pMaleHero = dynamic_cast<NWorld::PFBaseMaleHero const*>( pHero ) )
          {
            int level = m_talentLevel;
            int slot  = m_talentSlot;
            if ( NWorld::PFTalent* pTalent = pMaleHero->GetTalent( level, slot ) )
            {
              if ( !pTalent->CanBeUsed() )
              {
                dropTargetState = true;
              }
            }
          }
        }
        break;

        case CMD_PORTAL:
          {
            if ( NWorld::PFBaseMaleHero const* pMaleHero = dynamic_cast<NWorld::PFBaseMaleHero const*>( pHero ) )
            {
              if ( NWorld::PFTalent* pTalent = pMaleHero->GetPortal() )
              {
                if ( !pTalent->CanBeUsed() )
                {
                  dropTargetState = true;
                }
              }
            }
          }
        break;
      }

      if ( dropTargetState )
      {
        CancelCommand();

        TargetZoneReset();
      }
    }

    if ( command == CMD_NA )
      SetState( STATE_NORMAL );
  }
}



	CVec3 const& AdventureScreen::GetCurrentPickedPos()  
	{    
    if (vCursorPos.x != -1.f && vCursorPos.y != -1.f)
    {
	   	UpdateTerrainPick();    
		  return currentPick.GetPickedPos();  
    }
    return VNULL3;
	}  

  void AdventureScreen::MoveCameraTo( const CVec3& pos, bool resetObserver /*= true*/ )
  {
	  NI_VERIFY( IsValid( pCameraController ), "Invalid camera controller!", return; );

	  if ( !IsValid( pScene ) )
      return;

    pCameraController->SetCameraAnchor( pos, resetObserver );
    if ( IsValid(pFreeCameraController) && !pFreeCameraController->IsObservingMode() )
      pFreeCameraController->SetCameraAnchor( pos );
  }

  void AdventureScreen::UnSetCameraFree()
  {
    if( NScene::FreeCameraController* controller = dynamic_cast<NScene::FreeCameraController*>( pFreeCameraController.GetPtr() ) )
      controller->Shutdown();
  }

  void AdventureScreen::SetCameraFree( const CVec3& rotation, const CVec3& position )
  {
    NScene::SCameraPosition savedPosition;
    
    NI_VERIFY( IsValid( pFreeCameraController ), "Invalid camera controller!", return; );
    NI_VERIFY( IsValid( pCameraController ), "Invalid camera controller!", return; );

    if ( !IsValid( pScene ) )
      return;

    pCameraController->GetCameraPosition( &savedPosition );

    if( NScene::FreeCameraController* controller = dynamic_cast<NScene::FreeCameraController*>( pFreeCameraController.GetPtr() ) )
      controller->SetManual( rotation, position, &savedPosition );
  }
  
  void AdventureScreen::MoveCameraTo( NWorld::PFBaseUnit const * pUnit, bool resetObserver /*= true*/ )
  {
    if (!pUnit || (pUnit!=GetHero() && IsCameraLocked()))
      return;

    MoveCameraTo( pUnit->GetPosition(), resetObserver );
  }

  bool AdventureScreen::IsCameraLocked() const 
  { 
    if ( !pCameraController )
      return false;

    return pCameraController->IsLocked(); 
  }

  bool AdventureScreen::IsObservingObject( NWorld::PFBaseUnit const * pUnit ) const
  {
    if ( pUnit == 0 || pUnit->ClientObject() == 0 )
      return false;

    return GetCamera() && GetCamera()->IsObservedObject( pUnit->ClientObject() );
  }

  void AdventureScreen::SetObservingObject( NWorld::PFBaseUnit const * pUnit, bool forceObservation )
  {
    if (IsCameraLocked() && !forceObservation)
      return;

    NWorld::PFBaseMovingUnit const * pMoving = dynamic_cast<NWorld::PFBaseMovingUnit const *>(pUnit);
    
    if (pUnit && !pUnit->IsDead())
    {
      if (!GetCamera()->IsObservingMode() || forceObservation)
      {
        if (pMoving)
        {
          GetCamera()->SetObservedObject(pMoving->ClientObject(), forceObservation);
        }
        else
        {
          MoveCameraTo( pUnit);
        }
      }
    }
    else
    {
      GetCamera()->SetObservedObject(0);
    }
  }

  void AdventureScreen::SetHint( PF_Core::WorldObjectBase const *pObject, NScene::SceneObject *pSceneObject, bool bShow )
  {
    if (!bShow)
      return;
    if (!pSceneObject)
      return;

    const bool selected = (selectedObject == pObject);
    const bool picked = (currentPick.GetPickedPtr() == pObject);

    objectsInfo2d->UpdateObject( pObject, selected, picked );
  }

  void AdventureScreen::UpdatePickedObject(  )
  {    
    NI_PROFILE_FUNCTION

    if (NULL == currentPick.GetPickedPtr() || NULL == currentPick.GetScenePtr())
      return;

    // show preselection hint every frame
    SetHint(currentPick.GetPickedPtr(), currentPick.GetScenePtr(), true);

    // re-initialize preselection if its faction has changed
    if( NWorld::PFLogicObject const* pLO = dynamic_cast<NWorld::PFLogicObject const*>(currentPick.GetPickedPtr()) )
    {
      bool const wasPreselectedOfSameFaction = isPreselectedOfSameFaction;
      isPreselectedOfSameFaction = IsSameFaction(pLO);
      if ( wasPreselectedOfSameFaction != isPreselectedOfSameFaction)
        currentPick.SetPickedObjects(currentPick.GetPickedPtr(), currentPick.GetScenePtr());
    }
  }

  void AdventureScreen::UpdateSelectedObject()
  {
    NI_PROFILE_FUNCTION

    if (NULL == selectedObject || NULL == selectedSceneObject)
      return;

    // forget about selection if it's already dead
    if (NWorld::PFBaseUnit const *pUnit = dynamic_cast<NWorld::PFBaseUnit const *>(selectedObject.GetPtr()))
    {
      if (pUnit->IsDead())
      {
        SetSelectedObject(NULL, NULL);
        return;
      }
    }
   
    // show selection hint every frame
    SetHint( selectedObject, selectedSceneObject, true );
    
    // re-initialize selection if its faction has changed
    if( NWorld::PFLogicObject const* pLO = dynamic_cast<NWorld::PFLogicObject const*>(selectedObject.GetPtr()) )
    {
      bool const wasSelectedOfSameFaction = isSelectedOfSameFaction;
      isSelectedOfSameFaction = IsSameFaction(pLO);
      if ( wasSelectedOfSameFaction != isSelectedOfSameFaction)
        ProcessSelectionEffects();
    }
  }

  typedef NWorld::TargetSelectorFormulaPars DummyAbilityPars;

  class GlobalConstantsPars : public DummyAbilityPars
  {
    const NWorld::PFAIWorld* pAIWorld;
  public:
    GlobalConstantsPars( const NWorld::PFAIWorld* _pAIWorld ) : NWorld::TargetSelectorFormulaPars(0), pAIWorld(_pAIWorld) {}
    virtual float GetConstant(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver) const
    { 
      NI_ASSERT(pSender, "pSender isn't valid");
      NI_VERIFY(pAIWorld, "AI world isn't valid.", return NULL;);
      const vector<NDb::Ptr<NDb::UnitConstant>>& glob = pAIWorld->GetAIParameters().globalConstants->vars;
      const NDb::UnitConstant* pConstant = 0;
      for( vector<NDb::Ptr<NDb::UnitConstant>>::const_iterator iConst = glob.begin(), iEnd = glob.end(); iConst != iEnd; ++iConst )
        if ( (*iConst) && (*iConst)->name == name )
        {
          pConstant = (*iConst).GetPtr();    
          break;
        }

      if (pConstant) 
        return pConstant->var(pSender, pReceiver, this);

      return 0.0f;
    }
  };
  


  bool ShowUnitAoe(const NWorld::PFBaseUnit* pUnit, NDb::ESelectionAoeVisualType type, bool saturate)
  {
    using Render::AOERenderer;
    AOERenderer* pAOE = Render::GetAOERenderer();

    const NDb::AoeVisual* aoeParams = pUnit->DbUnitDesc()->selectionAoe[type];
    GlobalConstantsPars gcPars ( pUnit->GetWorld()->GetAIWorld() );
    if ( aoeParams && aoeParams->enabled(pUnit, pUnit, &gcPars, true) )
    {
      // show ability range
      float zoneRange = aoeParams->size( pUnit, pUnit, &gcPars, 0.0f );
      if (zoneRange > 0.0f)
      {
        AOERenderer::ChannelType channelType = (type == NDb::SELECTIONAOEVISUALTYPE_PRIMARY ? AOERenderer::CHANNEL_UNIT_RANGE1 : AOERenderer::CHANNEL_UNIT_RANGE2); 
        pAOE->SetAreaParams(channelType, AOERenderer::AREA_DISK, aoeParams->material, zoneRange, 0.0f); 
        CVec3 vPos = pUnit->GetPosition();
        if (NGameX::PFClientLogicObject const* pClient = pUnit->ClientObject())
        {
          const Placement& place = pClient->GetPosition();
          vPos = place.pos;
        }

        pAOE->SetAreaPosition( channelType, vPos, V3_AXIS_X, !saturate );
        return true;
      }
    }

    return false;
  }

  bool AdventureScreen::TargetZoneUnit(const NWorld::PFBaseUnit* pUnit)
  {
    if (pUnit && IsSameFaction(pUnit) && !pUnit->DbUnitDesc()->selectionAoe.empty())// && !pAOE->IsActive(AOERenderer::CHANNEL_RANGE))
    {
      bool bSaturate = (m_state == STATE_TARGET || m_newState == STATE_TARGET);
      bool res = ShowUnitAoe(pUnit, NDb::SELECTIONAOEVISUALTYPE_PRIMARY, bSaturate);
      res = res || ShowUnitAoe(pUnit, NDb::SELECTIONAOEVISUALTYPE_SECONDARY, bSaturate);
      
      if (res) 
        return true;
    }

    using Render::AOERenderer;
    AOERenderer* pAOE = Render::GetAOERenderer();

    pAOE->ResetArea(AOERenderer::CHANNEL_UNIT_RANGE1);
    pAOE->ResetArea(AOERenderer::CHANNEL_UNIT_RANGE2);
    return false;
  }

  void AdventureScreen::TargetZoneTooltip(NWorld::PFAbilityData const *pAbilityData)
  {
    // ignore tooltips while targeting (will be changed in future)
    if (m_state == STATE_TARGET || m_newState == STATE_TARGET) // fix: m_newState tells that ability parameters were already set, do not lose them [10/20/2010 paul.smirnov]
      return;

    using Render::AOERenderer;
    AOERenderer* pAOE = Render::GetAOERenderer();

    bool displayOnMinimap = false;

    if (pAbilityData)
    {
      // show ability range
      m_zoneRangeMin = pAbilityData->GetDBDesc()->minUseRangeCorrection;
      m_zoneRange = pAbilityData->GetUseRange();
      if (m_zoneRange > 0.0f)
      {
        displayOnMinimap = pAbilityData->GetDBDesc()->aoeDisplayOnMinimap;

        // design changed, show cone and corridor if they are specified [1/26/2011 paul.smirnov] http://SITE
        NDb::Material const* pDBMaterial = NULL;
        NDb::EAbilityAOEVisual zoneType = pAbilityData->GetDBDesc()->aoeType;
        float zoneSize = pAbilityData->GetAoeSize();
        switch (zoneType)
        {
        case NDb::ABILITYAOEVISUAL_CONE:
        case NDb::ABILITYAOEVISUAL_ATTACHEDSECTOR:
          zoneSize = ToRadian(zoneSize);
          pDBMaterial = pAbilityData->GetDBDesc()->aoeMaterial; // NULL is ok, will not be rendered in this case
          pAOE->SetAreaParams(AOERenderer::CHANNEL_RANGE, AOERenderer::AREA_SECTOR, pDBMaterial, 1.5f * m_zoneRange, zoneSize);
          break;
        case NDb::ABILITYAOEVISUAL_UNATTACHEDSECTOR:
          zoneSize = ToRadian(zoneSize);
          pDBMaterial = pAbilityData->GetDBDesc()->aoeMaterial; // NULL is ok, will not be rendered in this case

          if( 0.f == zoneSize)
          {
            pDBMaterial = pAbilityData->GetDBDesc()->useRangeMaterial; // NULL is ok, will not be rendered in this case
            pAOE->SetAreaParams(AOERenderer::CHANNEL_RANGE, AOERenderer::AREA_DISK, pDBMaterial, m_zoneRange, 0.0f); 
          }
          else
          {
            pAOE->SetAreaParams(AOERenderer::CHANNEL_RANGE, AOERenderer::AREA_SECTOR, pDBMaterial, m_zoneRange, zoneSize);
          }
          break;
        case NDb::ABILITYAOEVISUAL_CORRIDOR:
        case NDb::ABILITYAOEVISUAL_CORRIDORMAX:
          zoneSize = 0.5f * zoneSize;
          pDBMaterial = pAbilityData->GetDBDesc()->aoeMaterial; // NULL is ok, will not be rendered in this case
          pAOE->SetAreaParams(AOERenderer::CHANNEL_RANGE, AOERenderer::AREA_LINE, pDBMaterial, m_zoneRange, zoneSize);
          break;
        default:
          pDBMaterial = pAbilityData->GetDBDesc()->useRangeMaterial; // NULL is ok, will not be rendered in this case
          pAOE->SetAreaParams(AOERenderer::CHANNEL_RANGE, AOERenderer::AREA_DISK, pDBMaterial, m_zoneRange, 0.0f); 
        }
      }
      else
        pAOE->ResetArea(AOERenderer::CHANNEL_RANGE);
    }
    else
      //TargetZoneReset();
    {
      m_zoneRange = 0.0f;
      m_zoneSize = 0.0f;
      m_zoneType = NDb::ABILITYAOEVISUAL_NONE;
      pAOE->ResetArea(AOERenderer::CHANNEL_RANGE);
    }

    if (displayOnMinimap)
    {
      // NOTE: assumed that pAbilityData and pAbilityData->GetDBDesc() are both valid at this point
      minimap->SetTargetZoneDisplay(true);
      minimap->SetTargetZoneRange(m_zoneRange);
    }
    else
    {
      minimap->SetTargetZoneDisplay(false);
    }
  }



  bool AdventureScreen::IsSameFaction( NWorld::PFLogicObject const *unit ) const
  {
    return GetHero() ? GetHero()->GetFaction() == unit->GetFaction() : true;
  }



  void AdventureScreen::TargetZoneSet(NWorld::PFAbilityData const *pAbilityData)
  {
    using Render::AOERenderer;
    AOERenderer* pAOE = Render::GetAOERenderer();

    bool displayOnMinimap = false;

    // show ability range
    m_zoneRange = pAbilityData->GetUseRange();
    m_zoneRangeMin = pAbilityData->GetDBDesc()->minUseRangeCorrection;
    if (m_zoneRange > 0.0f)
    {
      displayOnMinimap = pAbilityData->GetDBDesc()->aoeDisplayOnMinimap;

      NDb::Material const* pDBMaterial = pAbilityData->GetDBDesc()->useRangeMaterial; // NULL is ok, will not be rendered in this case
      pAOE->SetAreaParams(AOERenderer::CHANNEL_RANGE, AOERenderer::AREA_DISK, pDBMaterial, m_zoneRange, 0.0f); 
    }
    else
      pAOE->ResetArea(AOERenderer::CHANNEL_RANGE);

    // show ability target area
    NDb::Material const* pDBMaterial = pAbilityData->GetDBDesc()->aoeMaterial; // NULL is ok, will not be rendered in this case
    m_zoneType = pAbilityData->GetDBDesc()->aoeType;
    m_zoneSize = pAbilityData->GetAoeSize();
    m_abilityFlags = pAbilityData->GetFlags();
    m_abilityAOEHeight = pAbilityData->GetAOEHeight();
    if (m_zoneSize > 0.0f)
    {
      switch (m_zoneType)
      {
      case NDb::ABILITYAOEVISUAL_NONE:
        m_zoneSize = 0.0f;
        pAOE->ResetArea(AOERenderer::CHANNEL_TARGET);
        break;
      case NDb::ABILITYAOEVISUAL_DISK:
        pAOE->SetAreaParams(AOERenderer::CHANNEL_TARGET, AOERenderer::AREA_DISK, pDBMaterial, m_zoneSize, 0.0f);
        break;
      case NDb::ABILITYAOEVISUAL_CONE:
      case NDb::ABILITYAOEVISUAL_ATTACHEDSECTOR:
        m_zoneSize = ToRadian(m_zoneSize);
        pAOE->SetAreaParams(AOERenderer::CHANNEL_TARGET, AOERenderer::AREA_SECTOR, pDBMaterial, 1.5f * m_zoneRange, m_zoneSize);
        break;
      case NDb::ABILITYAOEVISUAL_UNATTACHEDSECTOR:
        m_zoneSize = ToRadian(m_zoneSize);
        pAOE->SetAreaParams(AOERenderer::CHANNEL_TARGET, AOERenderer::AREA_SECTOR, pDBMaterial, m_zoneRange, m_zoneSize);
        break;
      case NDb::ABILITYAOEVISUAL_CORRIDOR:
        if (NDb::Ability const * pAbilityDesc = pAbilityData->GetDBDesc())
        {
          NDb::ETraceMode passabilityCheckMode = pAbilityDesc->aoePassabilityCheckMode;

          if ( ( passabilityCheckMode & NDb::TRACEMODE_DYNAMIC ) != 0 )
            m_zonePassabilityCheckMode |= NWorld::MAP_MODE_DYNAMIC;
          if ( ( passabilityCheckMode & NDb::TRACEMODE_BUILDING ) != 0 )
            m_zonePassabilityCheckMode |= NWorld::MAP_MODE_BUILDING;
          if ( ( passabilityCheckMode & NDb::TRACEMODE_STATIC ) != 0 )
            m_zonePassabilityCheckMode |= NWorld::MAP_MODE_STATIC;
        }
        m_zoneSize = 0.5f * m_zoneSize;
        pAOE->SetAreaParams(AOERenderer::CHANNEL_TARGET, AOERenderer::AREA_LINE, pDBMaterial, m_zoneRange, m_zoneSize);
        break;

      case NDb::ABILITYAOEVISUAL_CORRIDORMAX:
        if (NDb::Ability const * pAbilityDesc = pAbilityData->GetDBDesc())
        {
          NDb::ETraceMode passabilityCheckMode = pAbilityDesc->aoePassabilityCheckMode;

          if ( ( passabilityCheckMode & NDb::TRACEMODE_DYNAMIC ) != 0 )
            m_zonePassabilityCheckMode |= NWorld::MAP_MODE_DYNAMIC;
          if ( ( passabilityCheckMode & NDb::TRACEMODE_BUILDING ) != 0 )
            m_zonePassabilityCheckMode |= NWorld::MAP_MODE_BUILDING;
          if ( ( passabilityCheckMode & NDb::TRACEMODE_STATIC ) != 0 )
            m_zonePassabilityCheckMode |= NWorld::MAP_MODE_STATIC;
        }

        m_zoneSize = 0.5f * m_zoneSize;
        pAOE->SetAreaParams(AOERenderer::CHANNEL_TARGET, AOERenderer::AREA_LINE, pDBMaterial, m_zoneRange, m_zoneSize);
        break;
      case NDb::ABILITYAOEVISUAL_WALL:
        {
          const float width = NDb::SessionRoot::GetRoot()->visualRoot->wallTargetZoneWidth;
          pAOE->SetAreaParams( AOERenderer::CHANNEL_TARGET, AOERenderer::AREA_WALL, pDBMaterial, m_zoneSize, width );
        }
        break;
      default:
        NI_ALWAYS_ASSERT(NStr::StrFmt("Unknown target zone type (%i) '%s'", m_zoneType, NDb::EnumToString(m_zoneType)));
      }
    }
    else
    {
      m_zoneSize = 0.0f;
      m_zoneType = NDb::ABILITYAOEVISUAL_NONE;
      pAOE->ResetArea(AOERenderer::CHANNEL_TARGET);
    }

    // it is guaranteed here that m_zoneSize is nonzero (>0), otherwise m_zoneType is NONE

    if (displayOnMinimap)
    {
      // NOTE: assumed that pAbilityData and pAbilityData->GetDBDesc() are both valid at this point
      minimap->SetTargetZoneDisplay(true);
      minimap->SetTargetZoneRange(m_zoneRange);
    }
    else
    {
      minimap->SetTargetZoneDisplay(false);
    }
  }

  void AdventureScreen::TargetZoneReset()
  {  
    NI_PROFILE_FUNCTION

    ActionBarController * actionBarController = pLogic->GetActionBarController();
    if (IsValid(actionBarController))
      actionBarController->DropTarget();

    InventoryController * inventoryController = pLogic->GetInventoryController();
    if (IsValid(inventoryController))
      inventoryController->DropTarget();


    using Render::AOERenderer;
    AOERenderer* pAOE = Render::GetAOERenderer();
    pAOE->ResetAll();
    m_zoneRange = 0.0f;
    m_zoneRangeMin = 0.0f;
    m_zoneSize = 0.0f;
    m_zoneType = NDb::ABILITYAOEVISUAL_NONE;
    m_abilityFlags = 0;
    m_abilityAOEHeight = 0.0f;
    m_zonePassabilityCheckMode = NWorld::MAP_MODE_NONE;

    minimap->SetTargetZoneDisplay(false);
  }

  void AdventureScreen::TargetZoneUpdate(CVec3 const *pPos /*= 0*/)
  {
    NI_PROFILE_FUNCTION;
    
    using Render::AOERenderer;
    AOERenderer* pAOE = Render::GetAOERenderer();

    NWorld::PFBaseUnit* pSelectedUnit = dynamic_cast<NWorld::PFBaseUnit*>( selectedObject.GetPtr() );
    TargetZoneUnit( pSelectedUnit );

    // determine hero position and orientation
    CVec3 vPos = pPos ? *pPos : GetCurrentPickedPos();
    CVec3 vHeroPos, vHeroDir;
    NWorld::PFBaseHero * pHero = GetHero();
    if (NGameX::PFClientLogicObject const* pClient = pHero ? pHero->ClientObject() : NULL)
    {
      const Placement& place = pClient->GetPosition();
      vHeroPos = place.pos;
      CVec2 vHeroDir2D = pClient->GetPosition().Get2DDirection();
      vHeroDir.Set(vHeroDir2D.x, vHeroDir2D.y, 0.0f);
    }
    else
    {
      vHeroPos = vPos;
      vHeroDir = V3_AXIS_X;
    }

    // Direction Hint Update (Tutorial feature)
    if (pHero && !pHero->IsDead() && directionHintData.targetPos != VNULL3 && directionHintData.enabled)
    {
      CVec3 dir = directionHintData.targetPos - CVec3( vHeroPos.AsVec2D(), 0.0f );
      if (directionHintData.maxSize != directionHintData.minSize && directionHintData.sizingDistance > 0.0f)
      {
        float size = (directionHintData.maxSize - directionHintData.minSize)*(fabs(dir)/directionHintData.sizingDistance)
                        + directionHintData.minSize;
        size = min(directionHintData.maxSize, size);
        pAOE->SetAreaRadius(AOERenderer::CHANNEL_DIRECTION, size);
      }
      Normalize( &dir );
      pAOE->SetAreaPosition(Render::AOERenderer::CHANNEL_DIRECTION, vHeroPos + directionHintData.offset * dir, dir, true, (2.0f - fabs(dir - vHeroDir))/2.0f);
    }
    // End of Direction Hint Update

    // update use range area
    if (m_zoneRange > 0.0f && pHero && !isPlayingMinigame)
      pAOE->SetAreaPosition(Render::AOERenderer::CHANNEL_RANGE, vHeroPos + CVec3( 0, 0, m_abilityAOEHeight ), vHeroDir, true);
    else
      pAOE->ResetArea(Render::AOERenderer::CHANNEL_RANGE);

    if (m_state != STATE_TARGET)
      return;

    if (m_zoneType == NDb::ABILITYAOEVISUAL_NONE || (!bCursorInScene && !pPos))
    {
      pAOE->ResetArea(Render::AOERenderer::CHANNEL_TARGET);
      return;
    }

    // some voodoo magic (=hack) to "fix" http://SITE
    if ( m_zoneType != NDb::ABILITYAOEVISUAL_DISK
      && m_zoneType != NDb::ABILITYAOEVISUAL_UNATTACHEDSECTOR
      && m_zoneType != NDb::ABILITYAOEVISUAL_WALL
      && !pPos && fabs(cursorRay.ptDir.z) > FP_EPSILON )
    {
      // re-project picked position
      float t = (vHeroPos.z + m_abilityAOEHeight - cursorRay.ptOrigin.z) / cursorRay.ptDir.z;
      if (t > 0)
        vPos = cursorRay.Get(t);
    }

    CVec3 vDir = pHero ? vPos - vHeroPos : V3_AXIS_X;
    vDir.z = 0.0f;
    float distance2 = fabs2(vDir);
    if (!Normalize(&vDir))
      vDir = V3_AXIS_X;
    
    // process sector snapping
    if (m_zoneType == NDb::ABILITYAOEVISUAL_ATTACHEDSECTOR)
    {
      vPos = vHeroPos;
    }
    else if (m_zoneType == NDb::ABILITYAOEVISUAL_CONE)
    {
      static const float threshold = m_zoneRange;
      if (distance2 < fabs2(threshold))
        vPos = vHeroPos;
      else
        vPos -= threshold * vDir;
    } 
    else if (m_zoneType == NDb::ABILITYAOEVISUAL_CORRIDOR)
    {
      float range = ClampFast(sqrt(distance2), m_zoneRangeMin, m_zoneRange);

      if (pHero && m_zonePassabilityCheckMode != NWorld::MAP_MODE_NONE)
      {
        CVec2 toPos = vPos.AsVec2D();
        CVec2 curPos = GetHero()->GetPosition().AsVec2D();

        float distFromStartPos = fabs(toPos - curPos);
        float dist = pHero->CheckStraightMove(GetCurrentPickedPos().AsVec2D(), m_zonePassabilityCheckMode);

        dist = min(dist, m_zoneRange);

        if (dist < distFromStartPos)
          range = ClampFast(dist, m_zoneRangeMin, m_zoneRange);
      }

      pAOE->SetAreaRadius(AOERenderer::CHANNEL_TARGET, range);
      vPos = vHeroPos;
    }
    else if (m_zoneType == NDb::ABILITYAOEVISUAL_CORRIDORMAX)
    {
      float range = m_zoneRange;

      if (pHero && m_zonePassabilityCheckMode != NWorld::MAP_MODE_NONE)
      {
        CVec2 dir = GetCurrentPickedPos().AsVec2D() - vHeroPos.AsVec2D();
        CVec2 toPos = vHeroPos.AsVec2D();
        toPos.Displace(dir, m_zoneRange);

        float dist = pHero->CheckStraightMove( toPos, m_zonePassabilityCheckMode);
        dist = min(dist, m_zoneRange);
        range = ClampFast(dist, 1.f, m_zoneRange);
      }

      pAOE->SetAreaRadius(AOERenderer::CHANNEL_TARGET, range);

      vPos = vHeroPos;
      vPos.z += m_abilityAOEHeight;
    }

    // detect if the ability is applicable at the point (rather useless)
    bool bApplicable = true;
    if (pHero && pHero->GetWorld() && pHero->GetWorld()->GetTileMap())
    {
      NWorld::TileMap* pTileMap = pHero->GetWorld()->GetTileMap();

      if(m_zoneType == NDb::ABILITYAOEVISUAL_CONE || m_zoneType == NDb::ABILITYAOEVISUAL_ATTACHEDSECTOR)
      {
        NWorld::MapModeChanger mode(NWorld::MAP_MODE_ALL_STATICS, pTileMap);
        SVector tile = pTileMap->GetTile(vPos.AsVec2D());
        bApplicable = pTileMap->CanUnitGo(pHero->GetUnitRadius(), pHero->GetUnitDynamicRadius(), tile);
      }
      else if(m_zoneType == NDb::ABILITYAOEVISUAL_UNATTACHEDSECTOR)
      {
        bApplicable = (vHeroPos - vPos).LengthSqr() <= m_zoneRange * m_zoneRange;
        
        if(!bApplicable)
        {
          NWorld::MapModeChanger mode(NWorld::MAP_MODE_ALL_STATICS, pTileMap);

          int radius = max(0, pTileMap->GetLenghtInTiles(m_zoneRange) - 1);
          int radiusSqr = radius * radius;
          SVector center = pTileMap->GetTile(vPos.AsVec2D());
          SVector corner = center - SVector(radius, radius);

          // Check if our hero can reach some of the tiles in range
          for(int y=0; y<radius * 2; ++y)
          {
            for(int x=0; x<radius * 2; ++x)
            {
              SVector tile(corner.x + x, corner.y + y);
              SVector d = center - tile;
              if((d.x*d.x + d.y*d.y) > radiusSqr)
              {
                continue;
              }

              if(pTileMap->CanUnitGo(pHero->GetUnitRadius(), pHero->GetUnitDynamicRadius(), tile))
              {
                bApplicable = true;
                break;
              }
            }
          }
        }
      }
    }

    if( m_zoneType == NDb::ABILITYAOEVISUAL_DISK && ( m_abilityFlags & NDb::ABILITYFLAGS_FOCUSONTARGET ) )
    {
      // check target by range
      if((currentPick.GetPickedPos().AsVec2D() - vHeroPos.AsVec2D()).LengthSqr() > m_zoneRange * m_zoneRange)
        bApplicable = false;
      else
      {
        // check target
        bApplicable = IsValidCommandTarget( command, currentPick.GetPickedPos(), currentPick.GetPickedPtr() );
      }
    }

    pAOE->SetAreaPosition(Render::AOERenderer::CHANNEL_TARGET, vPos, vDir, bApplicable);
}

bool AdventureScreen::GetCursor( string * id, const UI::Point & screenCoords ) const
{
  *id = cursors[GetCurrentCursor()];
  return true;
}


AdventureScreen::CursorType NGameX::AdventureScreen::GetScrollCursor( CVec2 _scrollOffset ) const
{
  if (_scrollOffset.x>0)
  {
    if (_scrollOffset.y<0)
      return Scroll_Cur_RightBottom;

    if (_scrollOffset.y>0)
      return Scroll_Cur_RightTop;
    
    return Scroll_Cur_Right;
  }

  if (_scrollOffset.x<0)
  {
    if (_scrollOffset.y<0)
      return Scroll_Cur_LeftBottom;

    if (_scrollOffset.y>0)
      return Scroll_Cur_LeftTop;

    return Scroll_Cur_Left;
  }

  return (_scrollOffset.y<0) ? Scroll_Cur_Bottom: Scroll_Cur_Top;
}

AdventureScreen::CursorType AdventureScreen::GetCurrentCursor() const
{
  if (scrollOffset != VNULL2 && !IsCameraLocked())
    return GetScrollCursor(scrollOffset);

  NWorld::PFPickupableObjectBase *pickupableObject = dynamic_cast<NWorld::PFPickupableObjectBase*>( currentPick.GetPickedPtr() );
  if ( pickupableObject && m_state == STATE_NORMAL )
    return Pointer_Yellow;

  bool isTargetState = m_state == STATE_TARGET;

  if (isTargetState && command == CMD_SIGNAL)
      return MiniMapAllert;

  AdventureScreen::CursorType sameFactionCursor = isTargetState? Target_Green: Pointer_Green;
  AdventureScreen::CursorType neutralFactionCursor = isTargetState? Target_Yellow: Pointer_Yellow;
  AdventureScreen::CursorType enemyFactionCursor = isTargetState? Target_Red: Pointer_Red;
  AdventureScreen::CursorType normalCursor = isTargetState? Target_Normal: Pointer_Normal;

  NWorld::PFBaseUnit *pickedUnit = dynamic_cast<NWorld::PFBaseUnit*>(currentPick.GetPickedPtr());

  if ( !IsValid(pickedUnit))// || isWindowBeneath)
    return normalCursor;

  if (pickedUnit->GetFaction() == NDb::FACTION_NEUTRAL || pickedUnit->IsUsableBy( GetHero() ) )
    return neutralFactionCursor;

  return IsSameFaction( pickedUnit )? sameFactionCursor : enemyFactionCursor;
}

  


NWorld::PFBaseHero * AdventureScreen::GetHero()
{
  return GetHeroById( playerId );
}



const NWorld::PFBaseHero * AdventureScreen::GetHero() const
{
  return GetHeroById( playerId );
}


NWorld::PFBaseHero * AdventureScreen::GetHeroById( int heroId ) const
{
  if( pWorld )
    if ( NWorld::PFPlayer * pPlayer = pWorld->GetPlayer( heroId ) )
      return pPlayer->GetHero();

  return 0;
}



void AdventureScreen::SetLogicHero( NWorld::PFBaseHero * pHero )
{
  if (NULL != pHero)
  {
    objectInfoHelper->SetLocalHero(pHero);

    pLogic->SetHero(pHero);
    minimap->SetLocalHero(pHero);
    objectsInfo2d->SetLocalHero(pHero);
  }
}

NWorld::PFAbilityData * AdventureScreen::GetAbilityData(Command cmd, int index)
{
  NWorld::PFBaseHero *pHero = GetHero();
  switch (cmd)
  {
  case CMD_ITEM:
    return pHero->GetConsumable(index) ? pHero->GetConsumable(index)->GetAbility() : NULL;
  case CMD_TALENT_TALENT_PANEL:
    break;
  }
  return NULL;
}



const wstring& AdventureScreen::GetPlayerName(int playerId) const
{
  if (IsValid(playersInfo))
    return playersInfo->GetPlayerData(playerId).GetPlayerName();

  static const wstring empty;

  return empty;
}



int AdventureScreen::GetHeroPrimeNafta()
{
  if ( NWorld::PFBaseHero* pHero = GetHero() )
    return IsValid(naftaInfoProvider)? naftaInfoProvider->GetNaftaAmount(): pHero->GetGold() ;
  
  return 0;
}

  void AdventureScreen::PlayPickEffect(CVec3 const &pos, bool isGreen /* = true */ )
  {
    if (IsValid(m_landEffect) && m_landEffect->IsActive())
      m_landEffect->Die();

    NDb::EPathMarker color = isGreen ? NDb::PATHMARKER_GREEN : NDb::PATHMARKER_RED;

		m_landEffect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>( NDb::EFFECTS_CLICKONTERRAIN );
    if (m_landEffect)
    {
      m_landEffect->ModifyColor(pUIData->pathMarkerColor[color].mul, pUIData->pathMarkerColor[color].add);
      Placement place(pos);
      m_landEffect->SetPosition(place);
      m_landEffect->AddToScene(pScene);
    }
  }

  void AdventureScreen::OnHeroSetActive()
  {
    if( NWorld::PFBaseHero const * pHero = GetHero() )
    {
      MoveCameraTo( pHero, false);
    }
  }

  void AdventureScreen::OnEscape()
  {
    if(pLogic && pLogic->GetFlashInterface())
      pLogic->GetFlashInterface()->OnEscape();
  }

  void AdventureScreen::HideCurrentTooltip()
  {
    AdventureTooltip::HideCurrentTooltip();
    TargetZoneTooltip(NULL);
  }

  bool ToggleFreeCamera( const char *name, const vector<wstring> &params )
  {
    bool freeCam = false;
    if ((params.size() < 1) || (params.size() > 2))
    {
      freeCam = true;
    }
    else
    {
      freeCam = (bool)NGlobal::VariantValue( params[0] ).GetFloat();
    }

    if ( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
    {
      pAdvScreen->SetFreeCameraController(freeCam);
    }

    return true;
  }  



void AdventureScreen::NotifyPushedLine(const NWorld::PFBuilding * quarter, const NWorld::PFBaseUnit * killer)// NDb::EFaction faction, NDb::ERoute routeId )
{
  if( !IsValid(killer) )
    return;

  AnnouncementParams announcementParams;
  announcementParams.killer = killer;

  NWorld::CustomEventNameMap eventData;
  eventData.SetOwner(killer);
  eventData.SetEnemyTeamName(killer->GetFactionName());

  if( !IsSameFaction( quarter ) )
  {
    if(evBarrackDestroyed)
    {
      evBarrackDestroyed->SetOwner(killer);
      OnUIEvent( evBarrackDestroyed, &eventData, &announcementParams);
    }
  }
  else
  {
    if(evFriendBarrackDestroyed)
    {
      evFriendBarrackDestroyed->SetOwner(killer);
      OnUIEvent( evFriendBarrackDestroyed, &eventData, &announcementParams);
    }
  }

  /*
  if ( !pLogic )
    return;

  bool first = ( faction == NDb::FACTION_BURN );

  const CTextRef * text = 0;

  switch ( routeId )
  {
    case NDb::ROUTE_TOP:
      text = first ? &pUIData->combatStatuses.firstPushedTopLine : &pUIData->combatStatuses.secondPushedTopLine;
      break;

    case NDb::ROUTE_CENTER:
      text = first ? &pUIData->combatStatuses.firstPushedCenterLine : &pUIData->combatStatuses.secondPushedCenterLine;
      break;

    case NDb::ROUTE_BOTTOM:
      text = first ? &pUIData->combatStatuses.firstPushedBottomLine : &pUIData->combatStatuses.secondPushedBottomLine;
      break;

    case NDb::ROUTE_TREE:
      text = first ? &pUIData->combatStatuses.firstPushedAllLines : &pUIData->combatStatuses.secondPushedAllLines;
      break;
  }

  if ( text )
    pLogic->SetMessage( text->GetText() );*/
}



void AdventureScreen::NotifyOfSimpleUIEvent( NWorld::PFBaseHero * hero,  NDb::EErrorMessageType msg )
{
  if ( !hero || hero == GetHero() )
    pLogic->SetErrorMessage(msg);
}

void AdventureScreen::NotifySoldiersFirstSpawned()
{
  const NDb::AdvMapSettings* advMapSettings = 
    IsValid(pWorld->GetMapDescription()->mapSettings) ? (pWorld->GetMapDescription()->mapSettings) : (pWorld->GetMapDescription()->map->mapSettings);

  const NDb::Ptr<NDb::SoundRoot>& soundRoot = NDb::SoundRoot::GetRoot();

  if ( GetPlayerFaction() == NDb::FACTION_FREEZE )
    NSoundScene::EventStart( soundRoot->timerSounds.startEventA );
  else
    NSoundScene::EventStart( soundRoot->timerSounds.startEventB );

  if ( advMapSettings->useCustomBattleStartAnnouncement )
  {
    NSoundScene::EventStart( advMapSettings->customBattleStartAnnouncement.battleStartSound );
  }
  else 
  {
    NSoundScene::EventStart( pUIData->battleStartAnnouncementParams.battleStartSound );
  }
}


void AdventureScreen::SetDebugMessage( string const &msg )
{
  if (pLogic)
    pLogic->SetDebugMessage( msg);
}



NWorld::PFBaseUnit * AdventureScreen::GetMainUnit()
{
  return GetHero();
}



  void AdventureScreen::ClearAllSelections()
  {
    currentPick.SetPickedObjects( 0, 0 );
  }

  void AdventureScreen :: SetSelectedObject( CPtr<PF_Core::WorldObjectBase> const &selectedObject_, NScene::SceneObject *selectedSceneObject_ )
  {
    NI_PROFILE_FUNCTION

    g_selectedObject.SetValue( "None" );
    if( selectedObject.GetPtr() == selectedObject_.GetPtr() )
      return;

    if (NWorld::PFBaseUnit *pUnit = dynamic_cast<NWorld::PFBaseUnit*>(selectedObject.GetPtr()))
    {
      pUnit->SetDumpStates(false);
    }

		if( !IsValid(selectedObject_) )
		{
			selectedObject      = 0;
			selectedSceneObject = 0;
		}
    else
    { 
      NI_ASSERT(selectedSceneObject_, "Scene object should present");
      
      selectedObject      = selectedObject_;
      selectedSceneObject = selectedSceneObject_;

      if ( selectedSceneObject && selectedSceneObject->GetRootComponent())
        g_selectedObject.SetValue( selectedSceneObject->GetRootComponent()->GetDBID().GetFileName() );
    }

    ProcessSelectionEffects();
    
    currentPick.SetSelectedObject(selectedObject);

#ifndef _SHIPPING
    if( !bCtrlPressed )
      NDebug::DebugObject::DeselectAll();

    if( NWorld::PFBaseUnit const* pUnit = dynamic_cast<NWorld::PFBaseUnit const*>( selectedObject.GetPtr() ) )
    {
      CObj<NDebug::DebugObject> const &pDO = pUnit->GetDebugObject();
      if ( IsValid(pDO) )
      {
        if (pDO->IsSelected())
          pDO->Deselect();
        else
          pDO->Select();
      }
    }
#endif
  } // End of SetSelectedObject

  Render::HDRColor AdventureScreen::GetOutlineColor(NDb::EEffects effect) const
  {
    float mul = 1.0f;

    if (IsValid(pUIData))
    {
      switch (effect)
      {
      case NDb::EFFECTS_SELECTIONAURAALLY:
        mul = 0.8f;
      case NDb::EFFECTS_PRESELECTIONAURAALLY:
        return mul * pUIData->outlineAllyColor;

      case NDb::EFFECTS_SELECTIONAURAHOSTILE:
        mul = 0.8f;
      case NDb::EFFECTS_PRESELECTIONAURAHOSTILE:
        return mul * pUIData->outlineHostileColor;

      case NDb::EFFECTS_SELECTIONAURASELF:
        mul = 0.8f;
      case NDb::EFFECTS_PRESELECTIONAURASELF:
        return mul * pUIData->outlineSelfColor;
      }
    }

    return Render::HDRColor::WHITE();
  }

  void AdventureScreen::ProcessSelectionEffects()
  {
    if( IsValid(selectionEffect) )
      selectionEffect->Die();
    
    NWorld::PFBaseHero* pOwnedHero = GetHero();
    NWorld::PFLogicObject* pLO     = dynamic_cast<NWorld::PFLogicObject*>( selectedObject.GetPtr() );
    
    // only alive units, pickables and glyphs can receive selection effect
    if (!pLO ||
        (pLO->GetUnitType() != NDb::UNITTYPE_PICKUPABLE &&
         pLO->GetUnitType() != NDb::UNITTYPE_SIMPLEOBJECT &&
         !IsUnitValid( pLO ) ) )
    {
      TargetZoneUnit(0);
      return;   
    }

    isSelectedOfSameFaction           = IsSameFaction(pLO);
    NWorld::PFBaseHero* pSelectedHero = dynamic_cast<NWorld::PFBaseHero*>(pLO);
    if ( pSelectedHero != NULL && pSelectedHero == pOwnedHero )
    {
      selectedOutlineColor = GetOutlineColor(NDb::EFFECTS_SELECTIONAURASELF);
    }
    else // selection is either non-hero at all or at least not myself
    {
      // choose selection effect
      NDb::EEffects effect = NDb::EFFECTS_SELECTIONAURAALLY;
      UnitAttitude::Type attitude = GetUnitAttitude(pLO);
      switch (attitude)
      {
      case UnitAttitude::ALLY:
        effect = NDb::EFFECTS_SELECTIONAURAALLY;
        break;
      case UnitAttitude::HOSTILE:
        effect = NDb::EFFECTS_SELECTIONAURAHOSTILE;
        break;
      case UnitAttitude::SELF:
        effect = NDb::EFFECTS_SELECTIONAURASELF;
        break;
      default:
        NI_ALWAYS_ASSERT(NStr::StrFmt("Cannot choose selection effect for unit attitude '%i'", (int)attitude));
      }

      // add selection effect (disk) of proper color
      selectionEffect   = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectAttached>(effect);
      selectionEffect->SetDeathType(NDb::EFFECTDEATHTYPE_MANUAL);
      selectionEffect->Attach(selectedSceneObject);

      const bool& isClientVisible = pLO->IsVisibleForFaction( pOwnedHero->GetFaction() );
      selectedSceneObject->UpdateForced(0.0f, false, isClientVisible);

      // update outline color
      selectedOutlineColor = GetOutlineColor(effect);
    }

    TargetZoneUnit(dynamic_cast<NWorld::PFBaseUnit*>(pLO));
  }

  //call to set the pause and show it on the screen.
  void AdventureScreen::ProcessGamePause(EPauseMode pauseMode, int playerWhoPressedPause)
  {
    bool pause = pauseMode != PAUSE_OFF;
    pWorld->PF_Core::World::SetPause(pause, playerWhoPressedPause);
    if ( pWorld->IsPaused() != pause )
      return;

    struct Func : public PF_Core::IUpdateableFunc 
    {
      Func( bool _enable ) : enable(_enable) {}
      virtual void operator()(PF_Core::IUpdateable *pObj)
      {
        IAnimatedClientObject *pAnimated = dynamic_cast<IAnimatedClientObject*>(pObj);
        if (pAnimated)
          pAnimated->SetCinematicPause( enable );
      }
      bool enable;
    };
    
    if ( m_gamePause == pauseMode )
      return;
    if ( m_gamePause == PAUSE_CINEMATIC )
    {
      Func f(false);
      PF_Core::IUpdateable::ForAll( f );
    }

    m_gamePause = pauseMode;
    pLogic->ShowPauseTimer(m_gamePause == PAUSE_PLAYER, GetHeroById(playerWhoPressedPause));

    if ( m_gamePause == PAUSE_CINEMATIC )
    {
      Func f(true);
      PF_Core::IUpdateable::ForAll( f );
    }
  }

  bool AdventureScreen::OnHeroAvatarMouseClick( NWorld::PFBaseUnit * pUnit, int action )
  {
    if ( !pUnit || pUnit->IsDead() )
      return false;

    if (UI::EMButton::Left == action)
    {
      if ( SetCommandTarget( VNULL3, pUnit, false ) )
      {
        ExecuteCommand(command, VNULL3, pUnit);
        return true;
      }

      if (GetSelectedObject() == pUnit)
        SetObservingObject(pUnit);
      else
        MoveCameraTo( pUnit);

      return true;
    }
    else if ( action == UI::EMButton::Right )
    {
      if (GetHero() == pUnit)
      {
        MoveCameraTo( pUnit );
      }
      else
      {
        if ( IsGamePaused() ) { return true; }

        if (NWorld::PFLogicObject *pObject = pUnit)
        {
          if ((pObject->GetFaction() != NDb::FACTION_NEUTRAL) && (pObject->GetFaction() != GetHero()->GetFaction()))
            ExecuteCommand(CMD_ATTACK, pObject->GetPosition(), pObject, bShiftPressed);
          else
            ExecuteCommand(CMD_MOVE, pObject->GetPosition(), pObject, bShiftPressed);
        }
      }
    }

    return true;
  }


  bool AdventureScreen::OnUnitAvatarMouseClick(NWorld::PFBaseUnit *pUnit, int action)
  {
    if ( !pUnit || pUnit->IsDead() || isPlayingMinigame )
      return false;

    if (UI::EMButton::Left == action)
    {

      if ( SetCommandTarget( VNULL3, pUnit, false ) )
      {
        ExecuteCommand(command, VNULL3, pUnit);
        return true;
      }

      // мы неможем выбрать юнит, который под варфогом или невидим
      if ( !pUnit->IsVisibleForFaction( GetHero()->GetFaction() ) )
        return false;
      // нельз€ выбрать юнит, который нельз€ выбрать (?)
      if (pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDPICK))
        return false;


      if (GetSelectedObject().GetPtr() == pUnit)
      {
        // This object already selected
        SetObservingObject(pUnit);
      }
      else
      {
        SetSelectedObject(pUnit, pUnit->GetClientSceneObject());
      }

      return true;
    } 
    else if (UI::EMButton::Right == action)
    {
      NWorld::PFBaseHero const *pHero = GetHero();
      if (!pHero || pHero->IsDead())
        return false;

      if ( IsGamePaused() ) { return true; }
      
      if (NWorld::PFFlagpole *pFlag = dynamic_cast<NWorld::PFFlagpole*> (pUnit))
      {
        if (pFlag->GetFaction() == NDb::FACTION_NEUTRAL)
        {
          ExecuteCommand( CMD_RAISEFLAG, VNULL3, pUnit );
          return true;
        }
      }

      if ( pUnit->IsUsableBy( pHero ) )
      {
        ExecuteCommand( CMD_INTERACT, VNULL3, pUnit );
        return true;
      }

      if (NWorld::PFLogicObject *pObject = pUnit)
      {
        if ((pObject->GetFaction() != NDb::FACTION_NEUTRAL) && (pObject->GetFaction() != pHero->GetFaction()))
          ExecuteCommand(CMD_ATTACK, pObject->GetPosition(), pObject, bShiftPressed);
        else
          ExecuteCommand(CMD_MOVE, pObject->GetPosition(), pObject, bShiftPressed);
      }
    }

    return true;
  }



bool AdventureScreen::OnUnitAvatarMouseDblClick(NWorld::PFBaseUnit *pUnit, int action)
{
  if ( !pUnit || isPlayingMinigame || IsCameraLocked())
    return false;

  if (!pUnit)
    return false;
  if (isPlayingMinigame)
    return false;
  if (IsCameraLocked())
    return false;

  switch (action)
  {
  case UI::EMButton::Left:
    if (pUnit->IsDead())
    {
      const CDynamicCast<NWorld::PFBaseHero> pHero(pUnit);

      if (!IsValid(pHero))
        return false;
      // TODO: ?
      if (pHero->GetPlayer()->GetTeamID() != GetPlayer()->GetTeamID())
        return false;

      MoveCameraTo(pHero->GetSpawnPosition());
    }
    else
    {
      if (!ClientVisibilityHelper::IsVisibleForPlayer(pUnit))
        return false;

      MoveCameraTo(pUnit);

      SetSelectedObject(pUnit, pUnit->GetClientSceneObject());
    }
    break;
  default:
    break;
  }

  return true;
}



void AdventureScreen::OnItemButtonClick(int item)
{
  if ( IsGamePaused() ) { return; }

  NWorld::PFBaseHero const *pHero = GetHero();
  if (!pHero || pHero->IsDead())
    return;

  if (pHero->GetGlobalPreparedness() != 1.0f)
    return; // Do not use items during global cooldown

  NWorld::PFConsumable const *pItem = pHero->GetConsumable(item);
  if (NULL == pItem)
    return;

  const NDb::Ability* pDBItem = pItem->GetAbility()->GetDBDesc();

  pLogic->SetLastItemClicked( pDBItem->GetDBID().GetFormatted() );

  m_commandArguments[CMD_ITEM] = pDBItem->targetType;
  m_abilityIndex               = item;

  m_talentLevel = -1;
  m_talentSlot = -1;

  if (SetCommand(AdventureScreen::CMD_ITEM))
  {
    ExecuteCommand(AdventureScreen::CMD_ITEM, VNULL3, GetHero());
  }
  else if ( pItem->GetAbility()->IsInstaCast() && isHotKeyDown )
  {
    ExecuteCommand(AdventureScreen::CMD_ITEM, GetCurrentCursorPosOnTerrain(), GetCurrentPickedObject());
  }
  else
  {
    TargetZoneReset();

    SetState(AdventureScreen::STATE_TARGET);
    TargetZoneSet(pItem->GetAbility());

    ActionBarController * actionBarController = pLogic->GetActionBarController();
    if(IsValid(actionBarController))
      actionBarController->DropTarget();

    InventoryController * inventoryController = pLogic->GetInventoryController();
    if(IsValid(inventoryController))
      inventoryController->SetTargetingItem(item);
  }
}



bool AdventureScreen::OnShopButtonClick(int item)
{
  if (STATE_NORMAL != m_state)
    return false;

  const NWorld::PFShop* pShop = pLogic->GetShopController()->GetShop();

  NI_VERIFY( IsValid(pShop), "", return false);
  NI_VERIFY(0 <= item && item < pShop->GetConsumablesShop()->items.size(), "UI: Slot is not exist!", return false);

  NDb::Ptr<NDb::Consumable> pConsumable = pShop->GetConsumablesShop()->items[item];
  NI_ASSERT(IsValid(pConsumable), "");

  NWorld::PFBaseHero * pHero = dynamic_cast< NWorld::PFBaseHero *>(GetHero());
  NI_VERIFY(IsValid(pHero), "", return false);


  SendGameCommand( NWorld::CreateCmdBuyConsumable( pHero, const_cast<NWorld::PFShop*>(pShop), item, -1 ), true );
  return true;
}




bool AdventureScreen::OnTalentSetButtonClick(int level, int slot)
{
  ActionBarController * actionBarController = pLogic->GetActionBarController();
  
  if (NWorld::PFBaseMaleHero *pMale = dynamic_cast<NWorld::PFBaseMaleHero*>(GetHero()))
  {
    if (NWorld::PFTalent *pTalent = pMale->GetTalent(level, slot))
    {
      if ( !pTalent->IsActivated() && pMale->CanActivateTalent(level, slot) == NWorld::ETalentActivation::Ok )
      {
        SendGameCommand(NWorld::CreateCmdActivateTalent(pMale, level, slot), true);
      }

      if( isPlayingMinigame ) // запрещаем использовать таланты игра€ в миниигру
        return false;

      if (pTalent->IsActivated() && pTalent->CanBeUsed() && pTalent->IsActive())
      {
        // When ability is switched on, no target is assumed when switching off.
        // Ability that uses current unit target doesn't require target selection too.
        bool bTalentUsesAttackTarget = ( pTalent->GetDBDesc()->flags & NDb::ABILITYFLAGS_USEATTACKTARGET ) != 0;
        if ( pTalent->IsOn() || bTalentUsesAttackTarget )
          m_commandArguments[CMD_TALENT_TALENT_PANEL] = 0;
        else
          m_commandArguments[CMD_TALENT_TALENT_PANEL] = pTalent->GetTargetType();

        m_talentLevel = level;
        m_talentSlot  = slot;

        if (SetCommand(CMD_TALENT_TALENT_PANEL))
        {
          // If required use target that hero is attacking now
          // Note that creatures and bots use microAI
          if ( bTalentUsesAttackTarget )
          {
            NWorld::PFBaseUnit* pTarget = pMale->GetCurrentTarget();

            if ( IsValid( pTarget ) )
            {
              ExecuteCommand(CMD_TALENT_TALENT_PANEL, VNULL3, pTarget );
            }
          }
          else
          {
            ExecuteCommand(CMD_TALENT_TALENT_PANEL, VNULL3, GetHero());
          }
        }
        else if ( pTalent->isInstaCast && isHotKeyDown )
        {
          if ( !isSelfCastOn ){

            CVec3 vPickPosFromMinimap;
            const bool fromMinimapCast = minimap->IsOver();
            if (fromMinimapCast){
              minimap->Ui2World( minimap->GetCursotPosition().x, minimap->GetCursotPosition().y, vPickPosFromMinimap );
              pScene->GetHeightsController().GetHeight(vPickPosFromMinimap.x, vPickPosFromMinimap.y, 1, &vPickPosFromMinimap.z, NULL );
            }
          
            const CVec3& posOnTerrain = fromMinimapCast ? vPickPosFromMinimap : GetCurrentCursorPosOnTerrain();

            if ( SetCommandTarget( posOnTerrain, fromMinimapCast ? NULL : GetCurrentPickedObject(), fromMinimapCast ) )
                ExecuteCommand( command, m_targetPosition, m_targetObject, false, m_altTarget );

          }
        }
        else
        {
          if ( m_state == STATE_TARGET && !isHotKeyDown )
          {
            if ( pTalent->GetFlags() & NDb::ABILITYFLAGS_SELFCASTING )
            {
              if( IsValid(actionBarController) )
              {
                SVector v = actionBarController->GetTargetingTalent();
                if ( v.x == slot && v.y == level )
                {
                  ExecuteCommand( command, GetHero()->GetPosition(), GetHero(), false, m_altTarget );
                }
              }
            }
          }

          InventoryController * inventoryController = pLogic->GetInventoryController();
          if(IsValid(inventoryController))
            inventoryController->DropTarget();

          if(IsValid(actionBarController))
            actionBarController->TalentWaitingForTarget(slot, level);

          TargetZoneReset();

          SetState(STATE_TARGET);
          TargetZoneSet(pTalent);
        }
      }
    }
  }
  return true;
}

bool NGameX::AdventureScreen::OnPortalClick()
{
  if (!isHotkeysEnabled || ( blockedHotKeys & ( 1 << FlashWindowsType::Portal ) ) )
    return false;

  ActionBarController * actionBarController = pLogic->GetActionBarController();

  if (NWorld::PFBaseMaleHero *pMale = dynamic_cast<NWorld::PFBaseMaleHero*>(GetHero()))
  {
    if (NWorld::PFTalent *pTalent = pMale->GetPortal())
    {
      if (pTalent->IsActivated() && pTalent->CanBeUsed() && pTalent->IsActive())
      {
   
        m_commandArguments[CMD_PORTAL] = pTalent->GetTargetType();
        SetCommand(CMD_PORTAL);

        //if (SetCommand(CMD_PORTAL))
        //{
        //  ExecuteCommand(CMD_PORTAL, VNULL3, GetHero());
        //}
        //else if ( pTalent->IsInstaCast() && isHotKeyDown )
        //{
        //  if ( pTalent->GetTargetType() == NDb::SPELLTARGET_LAND )
        //    ExecuteCommand(CMD_TALENT_TALENT_PANEL, GetCurrentCursorPosOnTerrain(), NULL);
        //  else
        //    ExecuteCommand(CMD_TALENT_TALENT_PANEL, GetCurrentCursorPosOnTerrain(), GetCurrentPickedObject());
        //}
        //else
        //{

        if(IsValid(actionBarController))
          actionBarController->SetPortalWaiting();

        TargetZoneReset();

        SetState(STATE_TARGET);
        TargetZoneSet(pTalent);
        //}
      }
    }
  }
  return true;

}


  bool AdventureScreen::OnKeyCommand(const Command & command)
  {
    if (!isHotkeysEnabled)
      return false;

    // AT: block all keyboard pressing and transfer all messages to chat
    if ( IsActiveChat() )
      return false;

    if (!IsValid(GetHero()) || GetHero()->IsDead())
      return true;

    if ( SetCommand(command) )
    {
      ExecuteCommand( command, VNULL3, NULL);
    }
    else
    {
      SetState(AdventureScreen::STATE_TARGET);
    }
    return true;
  }

  void AdventureScreen::OnToggleSharedVision()
  {
    if (!isHotkeysEnabled)
      return;

    NI_VERIFY(IsSpectator(), "Spectator mode required", return);

    if (!IsValid(visibilityMap))
      return;

#ifndef _SHIPPING
    switch (visibilityMap->GetMode())
    {
    case EVisMapMode::FactionN:
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
      VisibilityMapClient::SetVisMapMode(EVisMapMode::Combined);
      break;
    case EVisMapMode::Combined:
      VisibilityMapClient::SetVisMapMode(EVisMapMode::Undefined);
      break;
    default:
      break;
    }
#else
    switch (visibilityMap->GetMode())
    {
    case EVisMapMode::FactionN:
    case EVisMapMode::FactionA:
    case EVisMapMode::FactionB:
      visibilityMap->SetMode(EVisMapMode::Combined);
      break;
    case EVisMapMode::Combined:
      visibilityMap->SetMode(EVisMapMode::FromFaction(ClientVisibilityHelper::GetPlayerFaction()));
      break;
    default:
      break;
    }
#endif
  }

bool AdventureScreen::OnEnterLeaveMinigame( NWorld::PFEaselPlayer *easelPlayer, bool bEnter )
{
  if ( IsSpectator() )
    return true;

  NI_VERIFY( NULL != easelPlayer, "Pointer is NULL", return false );
  NWorld::PFEaselPlayer * localPlayer = dynamic_cast<NWorld::PFEaselPlayer *>( GetHero() );

  if ( easelPlayer != localPlayer )
    return true;


  isPlayingMinigame = bEnter;
  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();

  if (bEnter)
  {
    if(binds)
    {
      binds->DeactivateSection( "adventure_screen" );
      binds->ActivateSection( "minigame");
    }

    SetSelectedObject(NULL, NULL);
    ClearAllSelections();
    isMinimapMoving = false;
  }
  else
  {
    if(binds)
    {
      binds->ActivateSection( "adventure_screen");
      binds->DeactivateSection( "minigame" );
    }
  }

  AdventureFlashInterface * flashInterface = pLogic->GetFlashInterface();

  if (IsValid(flashInterface))
    bEnter? flashInterface->EnterMinigame(): flashInterface->LeaveMinigame();

  return true;
}


/*
bool AdventureScreen::OnAutoTarget(int cmd, int index)
{
  if (IsGamePaused())          // Do not cast ability if game paused
    return false;
  if (cmd != command || m_abilityIndex != index) // This is not valid command
    return false;

  if (NWorld::PFAbilityData *pAbilityData = GetAbilityData(command, index))
  {
    NWorld::Target target;
    if (pAbilityData->FindAutoTarget(target))
    {
      CVec3 worldPos                 = target.IsPosition() ? target.GetPosition() : VNULL3;
      NWorld::PFLogicObject *pObject = target.IsObject() ? target.GetObject() : NULL;

      if ( SetCommandTarget(worldPos, pObject) )
      {
        ExecuteCommand(command, worldPos, pObject, false);
      }
    }
    else
    {
      CancelCommand();
      SetState(AdventureScreen::STATE_NORMAL);
    }
  }

  return true;
}
*/

void AdventureScreen::UpdateShopInfo( PF_Core::WorldObjectBase *pCanBeShop )
{
  //show/hide shop info
  NWorld::PFShop * pShop = dynamic_cast<NWorld::PFShop *> (pCanBeShop);

  bool bIsFaction = IsValid(pShop) && NULL != GetHero() && (pShop->GetFaction() == GetHero()->GetFaction() || pShop->GetFaction() == NDb::FACTION_NEUTRAL);

  if (bIsFaction)
  {
    pLogic->GetShopController()->SetShop(pShop);
    //sessionStore->SetShop(SessionStore::BUYITEM_SELECT_MODE, pShop);
  }
  //else
  //{
    //sessionStore->SetShop(SessionStore::BUYITEM_SELECT_MODE, NULL);
  //}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AdventureScreen::OnSelectionButtonMouseClick( CVec3 const &vPickPos, bool usePicking )
{
  if ( m_state == STATE_NORMAL )
  {
    if ( isPlayingMinigame ) // Do nothing in minigames
      return false;

    if ( usePicking )
    {
      SetSelectedObject( currentPick.GetPickedPtr(), currentPick.GetScenePtr() );
      UpdateShopInfo( selectedObject.GetPtr() );
    }
    return false;
  }
  else
  {
    NI_ASSERT( m_state == STATE_TARGET, "Wront state");

    NSoundScene::EventStart( pUIData->soundEvents.targetSelected );

    if ( SetCommandTarget( vPickPos, usePicking ? currentPick.GetPickedPtr() : NULL, !usePicking ) )
    {
      if ( GetHero() )
        ExecuteCommand( command, m_targetPosition, m_targetObject, false, m_altTarget );
    }

    return true;
  }
}



bool AdventureScreen::OnActionButtonMouseClick(CVec3 const &vPickPos, bool usePicking)
{
  if (STATE_NORMAL == m_state)
  {
    if (!IsValid(GetHero()))
      return true;
    if (isPlayingMinigame)
      return false;

    if (GetHero()->IsDead())
    {
      ExecuteCommand( CMD_KEEP_ALIVE );
      return true;
    }

    CPtr<PF_Core::WorldObjectBase> pickedObject = usePicking ? currentPick.GetPickedPtr() : NULL;

    if (IsValid(pickedObject))
    {
      NWorld::PFBaseUnit const *pBaseUnit = dynamic_cast<NWorld::PFBaseUnit const*>(pickedObject.GetPtr());
      if (!pBaseUnit)
      {
        // This is not unit
        if (dynamic_cast<NWorld::PFPickupableObjectBase const*>(currentPick.GetPickedPtr()))
        {
          ExecuteCommand( CMD_PICKUP_OBJECT, currentPick.GetPickedPtr()->GetObjectId() );
        }
        return true;
      }

      if ( pBaseUnit->IsUsableBy( GetHero() ) )
      {
        ExecuteCommand( CMD_INTERACT, VNULL3, currentPick.GetPickedPtr() );
        return true;
      }

      {
        CDynamicCast<NWorld::PFEaselPlayer> easelPlayer = GetHero();
        CDynamicCast<NWorld::PFMinigamePlace> pMinigame = pBaseUnit;

        bool isMinigameOfSameFaction = IsValid( pMinigame ) && IsValid( easelPlayer ) && easelPlayer->GetFaction() == pMinigame->GetFaction() ;

        if ( isMinigameOfSameFaction )
        {
          if (!IsMinigameEnabled())
          {
            pLogic->SetErrorMessage(NDb::ERRORMESSAGETYPE_MINIGAMEDISABLED);
          }
          else if ( GetWorld()->GetAIWorld()->GetBattleStartDelay() > 0 )
          {
            pLogic->SetErrorMessage(NDb::ERRORMESSAGETYPE_MINIGAMENOTREADY);
          }
          else if (pMinigame->IsAvailable())
          {
            ProcessSelectionPickEffects(dynamic_cast<NWorld::PFLogicObject*>(pickedObject.GetPtr()));
            ExecuteCommand( CMD_INIT_MINIGAME, pMinigame->GetObjectId() );
          }
          else
          {
            pLogic->SetErrorMessage(NDb::ERRORMESSAGETYPE_MINIGAMEBUSY);
          }
          return true;
        }
      }

      if (NWorld::PFFlagpole *pFlag = dynamic_cast<NWorld::PFFlagpole*> (currentPick.GetPickedPtr()))
      {
        if (pFlag->GetFaction() == NDb::FACTION_NEUTRAL)
        {
          ExecuteCommand( CMD_RAISEFLAG, VNULL3, currentPick.GetPickedPtr() );
          return true;
        }
      }

      if( g_casualControlStyle )
        UpdateShopInfo( currentPick.GetPickedPtr() );

      if ((pBaseUnit->GetFaction() != GetHero()->GetFaction()) 
        && ( !GetHero()->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) || GetHero()->ControlsMount() ) )
      {
        // Enemy unit
        if ( IsValidCommandTarget(CMD_ATTACK, VNULL3, currentPick.GetPickedPtr()))
          ExecuteCommand(CMD_ATTACK, VNULL3, currentPick.GetPickedPtr());
        else if ( pBaseUnit->GetFaction() == NDb::FACTION_NEUTRAL )
          ExecuteCommand(CMD_MOVE, currentPick.GetPickedPos(), currentPick.GetPickedPtr());
        else
          ProcessSelectionPickEffects(dynamic_cast<NWorld::PFLogicObject*>(pickedObject.GetPtr()));
        return true;
      }
              
      ExecuteCommand(CMD_MOVE, currentPick.GetPickedPos(), currentPick.GetPickedPtr()); // Follow
      return true;
    }

    if ( vPickPos != VNULL3 )
    {
      ExecuteCommand( CMD_MOVE, vPickPos, NULL );
    }
    return true;
  }
  else
  {
    NI_ASSERT(STATE_TARGET == m_state, "Wrong state");

    CancelCommand();
  }
  return true;
}

class SpectatorNameMap : public NNameMap::Map
{
  NAMEMAP_DECLARE;
public:
  wstring spectatorNickname;
  
};

NAMEMAP_BEGIN(SpectatorNameMap)
  NAMEMAP_VAR_RO(spectatorNickname)  
NAMEMAP_END

void AdventureScreen::OnSpectatorJoin( const wstring& spectatorNickname )
{    
  AnnouncementParams announcementParams;
  SpectatorNameMap nm;
  nm.spectatorNickname = spectatorNickname;
  OnUIEvent( evSpectatorJoin, &nm, &announcementParams );
}

bool AdventureScreen::OnUIEvent( PFUIEvent *  pEvent, NNameMap::Map const *pMap , AnnouncementParams * announcementParams, bool skipCheckSignRecipients )
{                                         
  if (!pEvent)
    return false;

  wstring strOut;

  //process the signs for this event
  int idx = 0;
  PrecompiledTooltip tooltip;
  NDb::EMessage messageId;

  for ( vector<CObj<PFUISign>>::const_iterator iUISign = pEvent->GetEventData().signs.begin(), iEnd = pEvent->GetEventData().signs.end(); iUISign != iEnd; ++iUISign, ++idx )
  {     
    // check the sign participants.
    // All messages (sounds) will be sent to the specified recipients only!!!
    if ( !skipCheckSignRecipients && !pEvent->CheckSignRecipients(GetPlayer(), *iUISign) )
      continue;//skip this sign

    // change message ID due to game logic
    pEvent->ExtractLinearAchievement(GetPlayer(), *iUISign);
    messageId = pEvent->GetCurMessageID();

    switch((*iUISign)->signType)
    {
    case NDb::SIGN_SEND_MESSAGE_TO_CHAT:
    {
        PFUISignMessageToChat const *pSign = dynamic_cast<PFUISignMessageToChat const *>( (*iUISign).GetPtr() );
        if (!pSign)
          break;
        if ( !enableAnnouncements )
          break;

        if ( messageId >= 0 && (messageId  < NDb::KnownEnum<NDb::EMessage>::sizeOf) )
        {
          tooltip.Parse( pSign->messages[messageId] );
          tooltip.ResolveVariants( pMap );
          tooltip.MakeText( strOut );

          if (chatController)
            chatController->AddChatMessage(strOut, pSign->GetChannel());
        }
        break;
      }
    case NDb::SIGN_SEND_MESSAGE_TO_STATUS_LINE:
      {
        PFUISignMessageToStatusLine const *pSign = dynamic_cast<PFUISignMessageToStatusLine const *>( (*iUISign).GetPtr() );
        if (!pSign)
          break;

        if ( messageId >= 0 && (messageId < NDb::KnownEnum<NDb::EMessage>::sizeOf) )
        {
          tooltip.Parse( pSign->messages[messageId] );
          tooltip.ResolveVariants( pMap );
          tooltip.MakeText( strOut );

          if ( !strOut.empty() )
            pLogic->SetMessage( strOut );
        }
        break;
      }
    case NDb::SIGN_PLAY_SOUND:
      {
        PFUISignPlaySound const *pSign = dynamic_cast<PFUISignPlaySound const *>( ( *iUISign ).GetPtr() );
        if (!pSign)
          break;

        NSoundScene::EventStart(pSign->soundDesc);;
        break;
      }
    case NDb::SIGN_FLYOFF_TEXT:
      {
        const NWorld::PFBaseUnit * pOwnerUnit = pEvent->GetOwner();
        const NWorld::PFBaseHero * pLocalHero = GetHero();

        if (!pOwnerUnit || !pLocalHero)
          break;

        bool visibleForPlayer = true;

        if (pOwnerUnit != pLocalHero)
        {
          visibleForPlayer = pOwnerUnit->IsVisibleForEnemy(pLocalHero->GetFaction());

          if (!visibleForPlayer)
          {
            // NUM_TASK
            if (pEvent->GetEventData().dbEvent == evAddGold)
            {
              // NOTE: название метода противоречит семантике. возможно, это баг.
              // метод провер€ет, €вл€етс€ ли герой указанного игрока получателем.
              if (pEvent->IsCurrentHeroEventOwner(GetPlayer()))
              {
                pOwnerUnit = pLocalHero;
                visibleForPlayer = true;
              }
            }
          }
        }

        if (!visibleForPlayer)
          break;

        PFUISignFlyOffText const *pSign = dynamic_cast<PFUISignFlyOffText const *>( ( *iUISign ).GetPtr() );
        if (!pSign)
          break;

        if (pLogic && pLogic->m_flyTexts && pScene )
          pLogic->m_flyTexts->AddFlyText(pOwnerUnit, &pSign->text, pMap, pScene->GetCamera()->GetProjectiveMatrix() * pScene->GetCamera()->GetViewMatrix() );

        break;
      }
    case NDb::SIGN_ANNOUNCEMENT:
      {
        if (!m_updated)
          break;

        // No announcements if there is a playing dialog
        if ( !IsDialogFinished( 0 ) )
          break;

        PFUISignAnnouncement const *pSign = dynamic_cast<PFUISignAnnouncement const *>( ( *iUISign ).GetPtr() );
        if (!pSign)
          break;

        if(!pSign->pDBDesc->UseInTutorial && GetWorld()->GetAIWorld()->IsTutorial())
          break;
        if ( !enableAnnouncements )
          break;

        if (pLogic)
          pLogic->ShowAnnouncement(pSign, announcementParams);

        break;
      }
    default:
      NI_ALWAYS_ASSERT("Wrong UI sign type" )
        break;
    }
  }

  return true;
}


void AdventureScreen::PlaceAskToAnnouncementQueue( NSound::AskCommands* ask, int priority )
{
  if ( announcementSoundPlayer )
    announcementSoundPlayer->AddAskToQueue( ask, priority );
}

void NGameX::AdventureScreen::AddMessageToChat( wstring& msg )
{
  if (chatController)
    chatController->AddChatMessage(msg, NDb::CHATCHANNEL_SYSTEM);
}



// void AdventureScreen::ExitGameA()
// {
//   //AT: doesn't work as we want. Maybe we should use these lines for going to town.
//   NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( this ) );
// 
//   StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();
//   if ( lgameControlCallback )
//     lgameControlCallback->LeaveGame();
// }

void AdventureScreen::PrecacheResources()
{
  NI_PROFILE_FUNCTION;

  // ѕрекэш NDb::SessionRoot::GetRoot()->logicRoot->heroesLevelups->killExperienceModifiers ( NUM_TASK )
  NDb::Precache<NDb::HeroesLevelUps>( NDb::SessionRoot::GetRoot()->logicRoot->heroesLevelups->GetDBID(), 10, true );

  NDb::Ptr<NDb::GlyphsDB> pDBGlyphs = NDb::SessionRoot::GetRoot()->logicRoot->glyphsDB;

  NI_VERIFY( IsValid( pDBGlyphs ), "Cannot find glyphs DB!" , return; );

  for ( vector<NDb::GlyphEntry>::const_iterator iGlyph = pDBGlyphs->glyphs.begin(), iEnd = pDBGlyphs->glyphs.end(); iGlyph != iEnd; ++iGlyph )
  {
    const NDb::Glyph* pDBGlyph = (*iGlyph).glyph;
    if ( pDBGlyph && pDBGlyph->gameObject && pDBGlyph->gameObject->sceneObject )
      NScene::SceneObjectsPool::Get()->Reserve( pScene, pDBGlyph->gameObject->sceneObject, 1, BADNODENAME );
   PreloadEffectsInResourceTree( pDBGlyph, BADNODENAME );
  }

  gameOverEffect.PrecacheEffects();

  NSoundScene::PreCacheGroup( "Announcements/Male", true );
}

bool AdventureScreen::GetControlStyle() 
{
  return g_casualControlStyle; 
}

CArray2D<float> const& AdventureScreen::GetHeightsAsFloat() const
{
  return GetScene()->GetTerrain()->GetHeightManager().GetHeightsAsFloat();
}


void AdventureScreen::PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName )
{
  PreloadEffectsInResourceTree( resource, nodeName, 0 );
}

void AdventureScreen::PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const NDb::DbResource * excludePart )
{
  nstl::list<const NDb::DbResource*> excludes;
  if (excludePart)
    excludes.push_back(excludePart);
  PreloadEffectsInResourceTree( resource, nodeName, excludes, "" );
}

void AdventureScreen::PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const nstl::list<const NDb::DbResource*>& excludes )
{
  PreloadEffectsInResourceTree( resource, nodeName, excludes, "" );
}

void AdventureScreen::PreloadEffectsInResourceTree( const NDb::DbResource * resource, const nstl::string& nodeName, const nstl::list<const NDb::DbResource*>& excludes, const nstl::string& skinId )
{
  NI_PROFILE_FUNCTION_MEM;

  if ( !G_GetPrechacheSessionData() )
    return;

  NDb::Ptr<NDb::DbResource> dbPtr( resource );

  NI_ASSERT( pScene, "" );

  ResourcesPreloader functor( pScene, excludes, nodeName, skinId );

  dbPtr.Traverse(40, &functor);
}

//IAdventureScreen
void AdventureScreen::LogHeroEvent( const StatisticService::RPC::SessionEventInfo &params, NWorld::PFBaseHero const * hero, SessionEventType::EventType eventType )
{
}


void AdventureScreen::LogSessionEvent( NWorld::PFBaseHero const * hero, SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params )
{
  if (IsValid(pWorld))
  {
    LogSessionEvent(hero, eventType, params, pWorld->GetStepNumber());
  }
}

void AdventureScreen::LogSessionEvent( NWorld::PFBaseHero const * hero, SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params, int worldStep )
{
  // Check may be its not our hero, or some required objects are missing
  if (hero == GetHero() && IsValid(hero) && pWorld && gameStatistics )
  {
    StatisticService::RPC::SessionEventInfo info;

    info.intParam1 = params.intParam1;
    info.intParam2 = params.intParam2;
    info.intParam3 = params.intParam3;
    info.intParam4 = params.intParam4;
    info.strParam1 = params.strParam1;
    info.strParam2 = params.strParam2;

    gameStatistics->LogSessionEvent( worldStep, hero->GetPosition().x, hero->GetPosition().y, eventType, info );
  }
}



void AdventureScreen::LogWorldSessionEvent( SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params )
{
  NWorld::PFBaseHero * heroLogger = GetLoggerHero();

  if (heroLogger != GetHero())
  {
    if (IsValid(pWorld))
    {
      // If local hero is not a logger - store the message. We may have to report it, if the logger will be disconnected.
      worldSessionEvents.push_back(SessionEventData(pWorld->GetStepNumber(), eventType, params));
    }
  }
  else
  {
    LogSessionEvent(heroLogger, eventType, params);
  }
}


void AdventureScreen::FillSessionResults( StatisticService::RPC::SessionClientResults & _info, int _surrenderVotes )
{
  //Nasty types conversion!!!
  //NOTE: Inversion: one win another failes

  if ( failedFaction == NDb::FACTION_FREEZE )
    _info.sideWon = lobby::ETeam::Team2;
  else if ( failedFaction == NDb::FACTION_BURN )
    _info.sideWon = lobby::ETeam::Team1;
  else
    _info.sideWon = lobby::ETeam::None;

  _info.surrenderVote = _surrenderVotes;

  NWorld::PFBaseHero * hero = GetHero();
  NI_VERIFY(hero && hero->IsLocal(), "hero should be valid on session start", return);

  const NWorld::PFWorld * world = GetWorld();
  NI_VERIFY( world, "", return );

  _info.players.clear();
  _info.players.reserve( world->GetPlayersCount() );

  for ( int pi = 0; pi < world->GetPlayersCount(); ++pi )
  {
    const NWorld::PFPlayer * player = world->GetPlayer( pi );
    if ( !player || player->IsBot() )
      continue;
    NI_VERIFY( player->GetUserID() > 0, "", continue );
    const NWorld::PFBaseHero * hero = player->GetHero();
    NI_VERIFY( hero, "", continue );

    const NWorld::PFHeroStatistics & heroStatistics = *hero->GetHeroStatistics();

    _info.players.push_back( StatisticService::RPC::SessionClientResultsPlayer() );
    StatisticService::RPC::SessionClientResultsPlayer & dest = _info.players.back();

    dest.userid = player->GetUserID();
	
    dest.scoring.score = heroStatistics.GetScore(); 
    dest.scoring.specialPoints = heroStatistics.GetSpecialPoints(); 
    dest.scoring.finalLevel = hero->GetNaftaLevel();
    dest.scoring.kills = heroStatistics.GetTotalNumHeroKills();
    dest.scoring.deaths = heroStatistics.GetNumDeaths();
    dest.scoring.assists = heroStatistics.GetTotalNumHeroAssists();
    dest.scoring.enemyCreepsKilled = heroStatistics.GetCreepsKilled();
    dest.scoring.neutralCreepsKilled = heroStatistics.GetNeutralCreepsKilled();
    dest.scoring.totalNumTowersKilled = heroStatistics.GetTotalNumTowersKilled();
    dest.scoring.totalNumTowersAssisted = heroStatistics.GetTotalNumTowersAssisted();
    dest.scoring.flagsRaised = heroStatistics.GetFlagsRaised();
    dest.scoring.flagsDestroyed = heroStatistics.GetFlagsDestroyed();
    dest.scoring.timeInDeath = heroStatistics.GetTimeInDeath();

    dest.scoring.totalMedalsCountFailed = heroStatistics.GetTotalMedalsCount( EMinigameLevelStatus::Failed );
    dest.scoring.totalMedalsCountDone = heroStatistics.GetTotalMedalsCount( EMinigameLevelStatus::Done );
    dest.scoring.totalMedalsCountSilver = heroStatistics.GetTotalMedalsCount( EMinigameLevelStatus::Silver );
    dest.scoring.totalMedalsCountGold = heroStatistics.GetTotalMedalsCount( EMinigameLevelStatus::Gold );

    dest.scoring.damageDealedMagic = heroStatistics.GetDamageDealed().magic;
    dest.scoring.damageDealedMaterial = heroStatistics.GetDamageDealed().material;
    dest.scoring.damageDealedPure = heroStatistics.GetDamageDealed().pure;
    dest.scoring.damageDealedTotal = heroStatistics.GetDamageDealed().GetTotal();

    dest.scoring.damageReceivedMagic = heroStatistics.GetDamageReceived().magic;
    dest.scoring.damageReceivedMaterial = heroStatistics.GetDamageReceived().material;
    dest.scoring.damageReceivedPure = heroStatistics.GetDamageReceived().pure;
    dest.scoring.damageReceivedTotal = heroStatistics.GetDamageReceived().GetTotal();

    dest.scoring.sexHelp = heroStatistics.GetSexHelp();
    dest.scoring.healedAmount = heroStatistics.GetHealedAmount();
    dest.scoring.totalNumQuartersDestroyed = heroStatistics.GetTotalNumQuartersDestroyed();
    dest.scoring.numBossKillsAssist = heroStatistics.GetNumBossKillsAssist();
	dest.scoring.numCatKillAssist = heroStatistics.GetNumCatKillAssist();
	dest.scoring.numDragonKillAssist = heroStatistics.GetNumDragonKillAssist();
    dest.scoring.numKillsTotal = heroStatistics.GetNumKillsTotal();
    dest.scoring.money = heroStatistics.GetMoney();
    dest.scoring.currentKillSpree = heroStatistics.GetCurrentKillSpree();
    dest.scoring.currentDeathSpree = heroStatistics.GetCurrentDeathSpree();
    dest.scoring.saviourTime = heroStatistics.GetSaviourTime();
    dest.scoring.timeInIdle = heroStatistics.GetTimeInIdle();
    dest.scoring.killedByNeutrals = heroStatistics.GetKilledByNeutrals();
    dest.scoring.usedPotions = heroStatistics.GetUsedPotions();
    dest.scoring.timeAtHome = heroStatistics.GetTimeAtHome();
    dest.scoring.teleportsByAbility = heroStatistics.GetTeleportsByAbility();
    dest.scoring.glyphsPickuped = heroStatistics.GetGlyphsPickuped();
    dest.scoring.achievScore = heroStatistics.GetAchievScore();

    dest.scoring.damageReceivedFromHeroesMagic = heroStatistics.GetDamageReceivedFromHeroes().magic;
    dest.scoring.damageReceivedFromHeroesMaterial = heroStatistics.GetDamageReceivedFromHeroes().material;
    dest.scoring.damageReceivedFromHeroesPure = heroStatistics.GetDamageReceivedFromHeroes().pure;
    dest.scoring.damageReceivedFromHeroesTotal = heroStatistics.GetDamageReceivedFromHeroes().GetTotal();

    dest.scoring.damageDealedToHeroesMagic = heroStatistics.GetDamageDealedToHeroes().magic;
    dest.scoring.damageDealedToHeroesMaterial = heroStatistics.GetDamageDealedToHeroes().material;
    dest.scoring.damageDealedToHeroesPure = heroStatistics.GetDamageDealedToHeroes().pure;
    dest.scoring.damageDealedToHeroesTotal = heroStatistics.GetDamageDealedToHeroes().GetTotal();

    dest.scoring.grandScore = heroStatistics.GetGrandScore();
    dest.scoring.timeElapsed = int(world->GetTimeElapsed());

    dest.extra.tutorialSkipped = skipTutorial;

    PlayerBehaviourTracking::UpdatePlayerStatistics(player, dest);
  }

  DebugTrace( "Players statistics:" );
  for ( int i = 0; i < _info.players.size(); ++i ) {
    StatisticService::RPC::SessionClientResultsPlayer & plr = _info.players[i];
    DebugTrace( "  player %d got %d score, %d special points, %d level, %d + %d / %d KD, ",
      plr.userid, plr.scoring.score, plr.scoring.specialPoints, plr.scoring.finalLevel, plr.scoring.kills, plr.scoring.assists, plr.scoring.deaths );
  }
}



void AdventureScreen::LogHeroDamage(const NWorld::HeroOpponent &opponent, unsigned int abilityId, const NWorld::HeroDamage &damage, bool dealt)
{
  NWorld::PFBaseHero * hero = GetHero();
  NI_VERIFY(hero && hero->IsLocal(), "Invalid hero at logging local hero's damage!", return);
  NI_VERIFY(pWorld, "No world object at logging local hero's damage!", return);

  if ( gameStatistics )
  {
    StatisticService::RPC::SessionDamageInfo damageInfo;

    damageInfo.dealt          = dealt;
    damageInfo.opponentId     = opponent.opponentId;
    damageInfo.unitType       = opponent.opponentType;
    damageInfo.talentId       = abilityId;
    damageInfo.physicalDamage = damage.material;
    damageInfo.magicalDamage  = damage.magic;
    damageInfo.pureDamage     = damage.pure;

    gameStatistics->LogSessionDamage( damageInfo, pWorld->GetStepNumber() );
  }
}


void AdventureScreen::OnTimeSlice()
{
  if (IsValid(pHeroLocalStatistics))
  {
    pHeroLocalStatistics->LogDamage();
  }
}

bool AdventureScreen::IsGameEnded()
{ 
  return pLogic ? pLogic->IsGameEnded() : false;
}

void AdventureScreen::DumpState( const char* stateClass, const char* state )
{
  DebugTrace("DumpState(%d): %s %s", GetWorld()->GetStepNumber(), stateClass, state);

  static string lastUsedState;
  static int lastUsedStateCount = 0;
  string msg = NStr::StrFmt( "%s::%s", stateClass, state );
  if ( msg == lastUsedState )
   ++lastUsedStateCount;
  else
  {
    lastUsedStateCount = 0;
    lastUsedState = msg;
    g_prev2State.SetValue( g_prevState.GetValue() );
    g_prevState.SetValue( g_currentState.GetValue() );
  }
  g_currentState.SetValue( "%s (%d)", lastUsedState.c_str(), lastUsedStateCount );
}



void AdventureScreen::DisableRenderWarFog(const NWorld::PFBaseHero * hero, bool disable )
{
  if (IsValid(hero) && hero == GetHero() && PF_Render::Interface::Get())
    PF_Render::Interface::Get()->DisableWarFog(disable);
}



void AdventureScreen::OnHeroDamaged( NWorld::PFBaseHero const * hero )
{
  if (IsValid(hero) && hero == GetHero())
  {
    bloodMask->OnHeroDamaged(hero);
  }
}


bool AdventureScreen::LockActionBar(const int &lock)
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->TempUnlockActionBar(! ((bool)lock));

  return true;
}




bool AdventureScreen::CmdActionBarHotKey( const int & slotIndex )
{
  if (!isHotkeysEnabled)
    return false;

  if (debugMousePick.enabled)
  {
    debugMousePick.vOnMouseMovePoint = currentPick.GetPickedPos();
  }

  TempDebugTrace(NStr::StrFmt( "AdventureScreen::CmdActionBarHotKey() slotIndx=%d", slotIndex ));
  isHotKeyDown = true;
  ActionBarController * actionBarController = pLogic->GetActionBarController();
  if (IsValid(actionBarController))
    actionBarController->UseSlot(slotIndex);

  if ( isSelfCastOn && GetHero() && m_talentLevel != -1 && m_talentSlot != -1 )
  {
    if ( NWorld::PFTalent* pTalent = GetHero()->GetTalent( m_talentLevel, m_talentSlot ) )
    {
      if ( pTalent->GetFlags() & NDb::ABILITYFLAGS_SELFCASTING )
      {
        ExecuteCommand( command, GetHero()->GetPosition(), GetHero(), false, m_altTarget );
      }
    }
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////
//minimap
//////////////////////////////////////////////////////////////////////////
void AdventureScreen::MinimapActionBegin( UI::EMButton::Enum action, float x, float y )
{
  CVec3 vPickPos( 0, 0, 0 );
  minimap->Ui2World( x, y, vPickPos );

  if (pScene)
    pScene->GetHeightsController().GetHeight(vPickPos.x, vPickPos.y, 1, &vPickPos.z, NULL ); 

  if( IsMinimapSignalCmd(action) )
  {
    ExecuteCommand( CMD_SIGNAL, vPickPos, 0 );
  } 
  else if ( IsSelectionCmd(action) )
  {        
    if ( !OnSelectionButtonMouseClick( vPickPos, false ) && !IsPlayingMinigame() )
    {
      isMinimapMoving = true;
      MoveCameraByMinimap( x, y );
    }
  }
  else if ( IsActionCmd(action) )
  {  
    OnActionButtonMouseClick( vPickPos, false );
  }
}

void AdventureScreen::MinimapActionEnd( UI::EMButton::Enum action, float x, float y )
{
  isMinimapMoving = false;
}

void AdventureScreen::MinimapActionMove( float x, float y )
{
  CVec3 vPickPos;
  minimap->Ui2World( x, y, vPickPos );

  if (!pScene )
    return;

  pScene->GetHeightsController().GetHeight(vPickPos.x, vPickPos.y, 1, &vPickPos.z, NULL );    

  TargetZoneUpdate(&vPickPos);

  if ( isMinimapMoving )
  {
    MoveCameraByMinimap( x, y );
  }

  //return !IsPlayingMinigame();
}

void AdventureScreen::MinimapOver(bool over, float x, float y)
{
  if (over)
  {
    SetCursorPos(CVec2(-1.f, -1.f));
    ClearAllSelections();
  }
  else
  {
    isMinimapMoving = false;
  }
  minimap->SetOver(over);
  minimap->SetCursorPosition(x, y);
}

void AdventureScreen::MinimapSignalBtnActionEnd()
{
  ProcessSignal();
}

void AdventureScreen::MoveCameraByMinimap( float x, float y )
{
  if (IsCameraLocked())
    return;

  CVec3 pos = VNULL3;
  minimap->Ui2World( x, y, pos );

  MoveCameraTo( pos, false );
}



void AdventureScreen::CancelObservingObject()
{
  if (GetCamera()->IsObservingMode())
    SetObservingObject(NULL);
}

struct SpectatorViewSort
{
  NCore::ETeam::Enum leftFraction;

  SpectatorViewSort( NCore::ETeam::Enum leftFraction ) : leftFraction( leftFraction ) {}

  bool operator()( const NWorld::PFPlayer* pl1, const NWorld::PFPlayer* pl2 )
  {
    if ( pl1->GetTeamID() == pl2->GetTeamID() )
    {
      if ( leftFraction == NCore::ETeam::Team2 )
        return pl1->GetTeamID() == NCore::ETeam::Team1 ? pl1->GetPlayerID() > pl2->GetPlayerID() : pl1->GetPlayerID() < pl2->GetPlayerID();

      return pl1->GetTeamID() == NCore::ETeam::Team1 ? pl1->GetPlayerID() < pl2->GetPlayerID() : pl1->GetPlayerID() > pl2->GetPlayerID();
    }

    if ( leftFraction == NCore::ETeam::Team2 )
      return pl1->GetTeamID() > pl2->GetTeamID();

    return pl1->GetTeamID() < pl2->GetTeamID();
  } 
};

bool AdventureScreen::StartSpectate( const int& heroIdx )
{
  if ( !IsSpectator() )
    return true;

  const CPtr<NWorld::PFAIWorld> pAIWorld = pWorld->GetAIWorld();

  // ѕосле завершени€ игры - не можем переключать героев спектатором ( NUM_TASK )
  if ( !pWorld || (IsValid(pAIWorld) && pAIWorld->WasGameFinished()) )
    return true;

  Weak<AdventureFlashInterface> pFlashInterface = pLogic->GetFlashInterface();
  
  if ( pWorld && pFlashInterface)
  {
    int playerIdx = pFlashInterface->GetSpectatePlayerId(heroIdx);
    int numPlayers = pWorld->GetPlayersCount();

    if ( playerIdx >= 0 && playerIdx < numPlayers )
    {
      CPtr<NWorld::PFPlayer> pPlayer = pWorld->GetPlayer( playerIdx );

      if ( IsValid(pPlayer) && pPlayer->GetUserID() > 0 )
      {
        bool needReinit = false;
        needReinit = GetPlayer()->GetTeamID() != pPlayer->GetTeamID();
        SetActivePlayer( pPlayer );
        if ( needReinit )
        {
          PF_Core::SpectatorEffectsPool::Get()->ReinitAllEffectSwitchers();
          PF_Core::SpectatorEffectsPool::Get()->ReinitAllBasicEffectStandalones();
        }
      }
    }
  }

  return true;
}



bool AdventureScreen::StartSpectateById( const int& playerId )
{
  if ( !IsSpectator() )
    return true;

  const NWorld::PFPlayer* player = GetWorld()->GetPlayer(playerId);
  if (!player)
    return false;

  bool needReinit = false;
  needReinit = GetPlayer()->GetTeamID() != player->GetTeamID();
  SetActivePlayer( player );
  if ( needReinit )
  {
    PF_Core::SpectatorEffectsPool::Get()->ReinitAllEffectSwitchers();
    PF_Core::SpectatorEffectsPool::Get()->ReinitAllBasicEffectStandalones();
  }

  return true;
}


void AdventureScreen::SetActivePlayer( const NWorld::PFPlayer* pl )
{
  if (GetPlayer() != pl)
  {
    GetPlayer()->SetIsLocal( false );
    if ( GetHero() )
    {
      if( NGameX::PFBaseClientHero* pClient = GetHero()->ClientObject() )
        pClient->OnBecameLocal( false );
    }

    playerId = pl->GetPlayerID();
    GetPlayer()->SetIsLocal( true );
    if ( GetHero() )
    {
      if( NGameX::PFBaseClientHero* pClient = GetHero()->ClientObject() )
        pClient->OnBecameLocal( true );
    }

    SetLogicHero( GetHero() );
    SetPlayerFaction( (GetPlayer()->GetTeamID() == 0)? NDb::FACTION_FREEZE: NDb::FACTION_BURN );
  }

  OnHeroSetActive();
}

void AdventureScreen::ExitGame( bool _returnToCastle )
{
  NI_VERIFY(!exitingGame, "Already exiting game", return);

  exitingGame = true;

  NDb::GetDbResourceCache().EnableAssertionLoadingFiles(false);

  PlaySameTeam(false);

  // Update user camera params on exit 
  if(pCameraController)
  {
    s_camera_rod = pCameraController->GetUserRod();
    s_camera_pitch = ToDegree(-pCameraController->GetUserPitch());
  }

  returnToCastle = _returnToCastle;

  StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();

  if ( lgameControlCallback )
  {
    lgameControlCallback->LeaveGame();
    waitingLeaveAck = true;
  }
  else
  {
    if ( pLogic )
      pLogic->QuitApplicationEx( returnToCastle ? EXIT_CODE_RETURN_TO_CASTLE : EXIT_CODE_QUIT_CASTLE );
  }
}

void NGameX::AdventureScreen::SkipTutorial()
{
  skipTutorial = true;

  if (IsValid(pWorld))
    pWorld->GameFinish(GetPlayerFaction());
}

void AdventureScreen::WaitLeaveAck()
{
  if ( !waitingLeaveAck ) 
    return;

  StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();

  if ( lgameControlCallback )
  {
    if ( !lgameControlCallback->IsWaitingLeaveAck() )
    {
      waitingLeaveAck = false;

      if ( pLogic )
        pLogic->QuitApplicationEx( returnToCastle ? EXIT_CODE_RETURN_TO_CASTLE : EXIT_CODE_QUIT_CASTLE );
    }
  }
}

void AdventureScreen::DisableHotkeys( bool disable )
{
  isHotkeysEnabled = !disable;
}

void AdventureScreen::ResetTargetState()
{
  if ( m_state == STATE_TARGET )
    CancelCommand();
}

bool AdventureScreen::OnCloseApplication()
{
  if (!IsValid(pLogic))
    return false;

  AdventureFlashInterface * flashInterface = pLogic->GetFlashInterface();

  if ( flashInterface && mapLoaded && !waitingLeaveAck )
  {
    OnEscMenuShow();
    flashInterface->ShowTryExit();
    return true;
  }

  return false;
}

void AdventureScreen::ContinueGame()
{
  bAlwaysShowCursor = false;
  bindsController->SetEnabled(BindsController::EscMenu, /*!bAdventureControlsEnabled*/true);
  UpdateCursor();
}

void AdventureScreen::OnEscMenuShow()
{
  CameraSwitchAttachModeUp();
  
  bAlwaysShowCursor = true;
  bindsController->SetEnabled(BindsController::EscMenu,false);
  NMainFrame::ShowCursor( true );
}

void AdventureScreen::ActivateSessionSoundScene()
{
  if( GetWorld()->GetAIWorld()->IsTutorial() )
  {
    if (heroFaction == NDb::FACTION_FREEZE)
      NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_TUTORIALA, false );
    else
      NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_TUTORIALB, false );
    return;
  }
  if (heroFaction == NDb::FACTION_FREEZE)
    NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_SESSIONA, false );
  else
    NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_SESSIONB, false );
}

void AdventureScreen::SetDirectionHint(const char* materialFile, float size, float width, float offset)
{
  SetDirectionHint( materialFile, size, width );
  directionHintData.offset = offset;
}

void AdventureScreen::SetDirectionHint(const char* materialFile, float size, float width)
{
  if (Render::AOERenderer* pAOE = Render::GetAOERenderer())
  {
    NDb::Ptr<NDb::Material> dbObj = NDb::Get<NDb::Material>( NDb::DBID( materialFile ) );
    NI_DATA_VERIFY( IsValid( dbObj ), NStr::StrFmt( "Resource \"%s\" not found!", materialFile ), return; );

    pAOE->SetAreaParams(Render::AOERenderer::CHANNEL_DIRECTION, Render::AOERenderer::AREA_LINE, dbObj, size, width);

    directionHintData.enabled = true;
  }
}

void AdventureScreen::ResetDirectionHint()
{
  if (Render::AOERenderer* pAOE = Render::GetAOERenderer())
  {
    pAOE->ResetArea(Render::AOERenderer::CHANNEL_DIRECTION);
  }
};

void AdventureScreen::LockCamera( bool lock )
{
  if(lock || !bCameraSwitchAttachControlled)
  {
    SetObservingObject( lock ? ( IsValid( GetHero()->GetMount() ) ? GetHero()->GetMount() : GetHero() ) : 0, true );
    pLogic->GetFlashInterface()->SetCameraLock( lock );
  }
}


void AdventureScreen::OnClientStatusChange( int userId, int status, int step, NWorld::PFPlayer * player /*= 0*/ )
{
  if (!IsValid(pWorld))
    return;

  if (!player)
    player = pWorld->GetPlayerByUID(userId);

  if (!player)
    return;

  NWorld::PFBaseHero * hero = player->GetHero();

  AnnouncementParams announcementParams;
  announcementParams.killer = hero;
  
  int playerId = player->GetPlayerID();

  UIPlayerStatus oldStatus;
  TUIPlayerStatuses::iterator itStatus = playerStatuses.find(playerId);
  if (itStatus != playerStatuses.end())
  {
    oldStatus = itStatus->second;
  }
  else
  {
    oldStatus.realStatus = Peered::Connecting;
    oldStatus.showPresent = true;
    itStatus = playerStatuses.insert(playerId);
    itStatus->second.showPresent = true;
  }
  itStatus->second.realStatus = status;

  //Away UI event
  if (status == Peered::Away && oldStatus.realStatus != Peered::Away && evHeroAFK)
    OnUIEvent(evHeroAFK, player, &announcementParams);

  //return from afk
  if (status == Peered::Active && oldStatus.realStatus == Peered::Away && evHeroAFKEnded )
        OnUIEvent(evHeroAFKEnded, player, &announcementParams);

  AdventureFlashInterface * flashInterface = pLogic.Valid() ? pLogic->GetFlashInterface() : 0;

  NGameX::PFUIEvent * pUIEvent = 0;

  if (oldStatus.showPresent)
  {
    //player disconnected
    if (Peered::IsDisconnectedStatus(status))
    {
      itStatus->second.showPresent = false;

      if (flashInterface)
        flashInterface->MarkPlayerLeft(playerId,status == Peered::RefusedToReconnect? PlayerLeaveType::Left : PlayerLeaveType::Disconnected );

      if (isSessionStarted)
      {
        if( GetPlayer()->GetHero()->GetFaction() == announcementParams.killer->GetFaction() )
        {
          if (status == Peered::RefusedToReconnect)
            pUIEvent = evHeroFriendLeft;
          else if(status == Peered::DisconnectedByServer) // FIXME: NUM_TASK
            pUIEvent = evHeroFriendDisconnectedAFK;
          else
            pUIEvent = evHeroFriendDisconnected;
        }
        else
        {
          if (status == Peered::RefusedToReconnect)
            pUIEvent = evHeroLeft;
          else if(status == Peered::DisconnectedByServer) // FIXME: NUM_TASK
            pUIEvent = evHeroDisconnectedAFK;
          else
            pUIEvent = evHeroDisconnected;
        }
      }
    }
  }
  else
  {
    //reconnect
    if (status == Peered::Active || status == Peered::Connecting && !IsSessionStarted())
    {
      itStatus->second.showPresent = true;

      //welcome back buddy
      if (flashInterface)
        flashInterface->MarkPlayerReconnected(playerId);

      if (isSessionStarted)
      {
        if( GetPlayer()->GetHero()->GetFaction() == announcementParams.killer->GetFaction() )
          pUIEvent = evHeroFriendReconnected;
        else
          pUIEvent = evHeroReconnected;
      }
    }
    else if (status == Peered::RefusedToReconnect)
    {
      if (flashInterface)
        flashInterface->MarkPlayerLeft(playerId, PlayerLeaveType::Left);
    }
  }

  if (pUIEvent)
  {
    pUIEvent->SetOwner( announcementParams.killer );
    OnUIEvent(pUIEvent, player, &announcementParams);
  }
}

void AdventureScreen::OnTowerDie()
{
  if ( NSoundScene::GetActiveSoundScene() == NDb::SOUNDSCENE_SESSIONA || NSoundScene::GetActiveSoundScene() == NDb::SOUNDSCENE_SESSIONB )
  {
    NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_TOWERDEATH, false );
    towerDeathTimer = 0.0f;
  }
  else if ( NSoundScene::GetActiveSoundScene() == NDb::SOUNDSCENE_TOWERDEATH )
  {
    if ( towerDeathTimer > NDb::SoundRoot::GetRoot()->timeToTowerDeath )
    {
      NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_TOWERDEATH, true );
      towerDeathTimer = 0.0f;
    }
  }
};

// Handles a disconnected player. If that player was a logger before and local player is a logger 
// now - dump any events, added after the step, when disconnected player was last seen
void AdventureScreen::OnPlayerDisconnected(NWorld::PFPlayer * player, int lastStep)
{
   // Get current logger hero (before we mark the disconnected player)
  NWorld::PFBaseHero * heroLogger = GetLoggerHero();

  // Check if the logger is the disconnected player
  if (IsValid(heroLogger) && player == heroLogger->GetPlayer())
  {
    // Get the new logger hero (after we marked the disconnected player)
    NWorld::PFBaseHero * heroNewLogger = GetLoggerHero();
    NWorld::PFBaseHero * heroLocal = GetHero();

    // Do logging if the new logger is the local hero
    if (IsValid(heroNewLogger) && IsValid(heroLocal) && heroNewLogger == heroLocal)
    {
      SessionEvents::iterator itSe = worldSessionEvents.begin();
      SessionEvents::iterator itSeEnd = worldSessionEvents.end();

      // Go through all saved messages and log, if they was stored 
      // after the disconnected player was seen last time
      for (; itSe != itSeEnd; ++itSe)
      {
        if (lastStep < (*itSe).step)
        {
          LogSessionEvent(heroLocal, (*itSe).type, (*itSe).params, (*itSe).step);
        }
      }

      // Clear stored messages. We don't need them any more, if we are the logger now.
      worldSessionEvents.clear();
    }
  }
}


void AdventureScreen::OnStartAiForPlayer( NWorld::PFPlayer * player )
{
  if (evStartAiForPlayer && player && !player->IsBot())
  {
    AnnouncementParams announcementParams;
    announcementParams.killer = player->GetHero();
    evStartAiForPlayer->SetOwner( announcementParams.killer );
    OnUIEvent(evStartAiForPlayer, player, &announcementParams);
  }
}

#pragma code_seg(push, "~")

void AdventureScreen::OnProtectionError()
{
  STARFORCE_STOPWATCH();

  {
    static bool fired = false;

    if (fired)
      return;

    fired = true;
  }

  if (IsValid(socialServer))
  {
    socialServer->OnProtectionError();
  }

  if (const StrongMT<IGameControl> callback = gameControlCallback.Lock())
  {
    callback->OnProtectionError();
  }
}

#pragma code_seg(pop)

void AdventureScreen::OnReplayEnded()
{
  NotifyOfSimpleUIEvent(0, NDb::ERRORMESSAGETYPE_REPLAYENDED);
  if (pWorld)
    pWorld->StopMovingUnits();
}


// TODO: remove when normal UI for replays will be implemented
void AdventureScreen::ShowReplaySpeed(float speed)
{
  // Show message for 100500 seconds because we don't support infinite lifetime.
  // We need it infinite because we disable it manually after N real seconds.
  // We don't rely on built-in timer because it's timescale depended.
  pLogic->SetMessage( 
    NStr::StrFmtW( L"%s%.2f", pUIData->combatStatuses.replaySpeed.GetText().c_str(), speed ), false, 100500 );
}

// TODO: remove when normal UI for replays will be implemented
void AdventureScreen::ShowReplayPause()
{
  // Show message for 100500 seconds because we don't support infinite lifetime.
  // We need it infinite because we disable it manually after N real seconds.
  // We don't rely on built-in timer because it's timescale depended.
  pLogic->SetMessage( pUIData->combatStatuses.replayPause.GetText(), false, 100500 );
}

// TODO: remove when normal UI for replays will be implemented
void AdventureScreen::HideReplayMsg()
{
  pLogic->SetMessage( L"" );
}


// It's the code to pick only one player (actually his hero) from the whole group for logging global events
NWorld::PFBaseHero * AdventureScreen::GetLoggerHero()
{
  NWorld::PFBaseHero * heroLogger = 0;

  for (int i = 0, playersCount = pWorld->GetPlayersCount(); i < playersCount; i++)
  {
    NWorld::PFPlayer * player = pWorld->GetPlayer(i);

    // Choose the first valid hero of a valid player, which is not a bot and not dropped (disconnected)
    if ( player && !player->IsBot() && player->IsPlaying())
    {
      heroLogger = player->GetHero();

      if (IsValid(heroLogger))
        break;
    }
  }

  return heroLogger;
}

// Starts global sounds, which play permanently during the session
void AdventureScreen::StartGlobalSounds()
{
  const NDb::Ptr<NDb::SoundRoot> & soundRoot = NDb::SoundRoot::GetRoot();
  if (!IsValid(soundRoot))
    return;

  // Init and start hero's hertbeating sound
  const NWorld::PFBaseHero* hero=GetHero();
  if(hero && !hero->IsMale())
    NSoundScene::SetHeartBeatData(soundRoot->heartbeatFemale, soundRoot->heartbeatParamName);
  else
    NSoundScene::SetHeartBeatData(soundRoot->heartbeat, soundRoot->heartbeatParamName);
  NSoundScene::EnableHeartBeat(true);

  // Init and start ambient sound
  StartAmbientSound();
}

// Stops global sounds, which play permanently during the session
void AdventureScreen::StopGlobalSounds()
{
  NSoundScene::EnableHeartBeat(false);
  StopAmbientSound();
}

// Starts ambient sound effect
void AdventureScreen::StartAmbientSound()
{
  const NDb::Ptr<NDb::SoundRoot> & soundRoot = NDb::SoundRoot::GetRoot();

  if (IsValid(soundRoot))
  {
    NSoundScene::SetAmbientData(soundRoot->ambient);
    NSoundScene::EnableAmbient(true);

    // prepare color palette
    NI_DATA_ASSERT(NDb::KnownEnum<NDb::SoundAmbientGroup>::sizeOf == soundRoot->ambienceGroups.size(),
      NStr::StrFmt("There should be %i ambience groups but got only %i", NDb::KnownEnum<NDb::SoundAmbientGroup>::sizeOf, soundRoot->ambienceGroups.size()));
    nstl::vector<unsigned> colors(soundRoot->ambienceGroups.size());
    for (int i = 0, n = soundRoot->ambienceGroups.size(); i < n; ++i)
    {
      colors[i] = ((Render::Color)soundRoot->ambienceGroups[i].color).Dummy & 0xFFFFFF;
      NI_DATA_ASSERT(!soundRoot->ambienceGroups[i].paramName.empty(), "One of the ambient sound param names is empty!");
      vAmbientSoundParams.push_back(soundRoot->ambienceGroups[i].paramName);
    }
    
    // load ambience texture
    Reset(pAmbienceMap, new AmbienceMap());
    if( GetWorld()->GetAmbienceMap() )
      pAmbienceMap->Init(*( GetWorld()->GetAmbienceMap() ), pWorld->GetMapSize(), colors);

    // do we need the first update?
  }
}


// Stops ambient sound effect
void AdventureScreen::StopAmbientSound()
{
  NSoundScene::EnableAmbient(false);

  if (pAmbienceMap)
    Reset(pAmbienceMap, NULL);
}

void AdventureScreen::UpdateAmbientSound(NScene::SCameraPosition const& camPos)
{
  NI_PROFILE_FUNCTION

  if (pAmbienceMap)
  {
    pAmbienceMap->UpdateEnvironment(camPos.vAnchor, camPos.GetCameraDir()); // use smth like NSoundScene::EventSystemGetListener()? [1/25/2011 paul.smirnov]

    if(RENDER_DISABLED)
      return;

    nstl::vector<float> percents = pAmbienceMap->GetEnvironment();
    // Percents vector size must match the SoundAmbientGroup's size + 1, otherwise we may get an exception!
    NI_VERIFY(percents.size() == NDb::KnownEnum<NDb::SoundAmbientGroup>::sizeOf + 1,
      NStr::StrFmt("There should be %i values, but got only %i", NDb::KnownEnum<NDb::SoundAmbientGroup>::sizeOf + 1, percents.size()), return; );
    NI_ASSERT(fabs(percents[0]) < FP_EPSILON,
      NStr::StrFmt("It seems that AmbienceMap texture contains unclassified pixels around this world point"));

    // split forest and distribute between factions
    if (PF_Render::Interface* ri = dynamic_cast<PF_Render::Interface*>(PF_Render::Interface::Get()))
    {
      CVec4 forests = ri->GetVisibleNature();
      percents[1 + NDb::SOUNDAMBIENTGROUP_FORESTA] = forests.b * percents[1 + NDb::SOUNDAMBIENTGROUP_FORESTN];
      percents[1 + NDb::SOUNDAMBIENTGROUP_FORESTB] = forests.r * percents[1 + NDb::SOUNDAMBIENTGROUP_FORESTN];
      percents[1 + NDb::SOUNDAMBIENTGROUP_FORESTN] = forests.g * percents[1 + NDb::SOUNDAMBIENTGROUP_FORESTN];
    }

    // prepare debug string
#ifdef _DEBUG
    static const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE], *ptr = buffer;
    int bufferSizeLeft = BUFFER_SIZE;
    for (int i = 0, n = percents.size(); i < n && bufferSizeLeft > 0; ++i)
    {
      int written = sprintf_s(ptr, bufferSizeLeft, "%3.0f%% ",  percents[i] * 100.0f);
      if (written <= 0)
        break;
      ptr += written;
      bufferSizeLeft -= written;
    }
    ambienceDebugStr.SetValue("%s", buffer);
#endif

    // Update reverberation
    string reverbPresetName = "Ambient";
    float percent = 0.0f;
    const NDb::Ptr<NDb::SoundRoot> & soundRoot = NDb::SoundRoot::GetRoot();

    if ( GetHero() && GetHero()->IsDead() )
    {
      reverbPresetName = soundRoot->timerSounds.deadReverbName;
    }
    else
    {
      for ( int i = 0; i < soundRoot->ambienceGroups.size(); i++ )
      {
        if ( percents[1 + i] > percent )
        {
          reverbPresetName = soundRoot->ambienceGroups[i].reverbPresetName;
          percent = percents[1 + i];
        }
      }
    }

    NSoundScene::ApplyReverb( reverbPresetName );

    // Update ambient sound parameters
    if (vAmbientSoundParams.size() == NDb::KnownEnum<NDb::SoundAmbientGroup>::sizeOf)
    {
      NSoundScene::UpdateAmbient(vAmbientSoundParams[NDb::SOUNDAMBIENTGROUP_FORESTA].c_str(), percents[1 + NDb::SOUNDAMBIENTGROUP_FORESTA] * 100.0f);
      NSoundScene::UpdateAmbient(vAmbientSoundParams[NDb::SOUNDAMBIENTGROUP_FORESTB].c_str(), percents[1 + NDb::SOUNDAMBIENTGROUP_FORESTB] * 100.0f);
      NSoundScene::UpdateAmbient(vAmbientSoundParams[NDb::SOUNDAMBIENTGROUP_FORESTN].c_str(), percents[1 + NDb::SOUNDAMBIENTGROUP_FORESTN] * 100.0f);
      NSoundScene::UpdateAmbient(vAmbientSoundParams[NDb::SOUNDAMBIENTGROUP_BASEA].c_str(), percents[1 + NDb::SOUNDAMBIENTGROUP_BASEA] * 100.0f);
      NSoundScene::UpdateAmbient(vAmbientSoundParams[NDb::SOUNDAMBIENTGROUP_BASEB].c_str(), percents[1 + NDb::SOUNDAMBIENTGROUP_BASEB] * 100.0f);
      NSoundScene::UpdateAmbient(vAmbientSoundParams[NDb::SOUNDAMBIENTGROUP_WATER].c_str(), percents[1 + NDb::SOUNDAMBIENTGROUP_WATER] * 100.0f);
      NSoundScene::UpdateAmbient(vAmbientSoundParams[NDb::SOUNDAMBIENTGROUP_ROAD].c_str(), percents[1 + NDb::SOUNDAMBIENTGROUP_ROAD] * 100.0f);
    }
  }
}

void AdventureScreen::ActivateImpulsiveBuff()
{
  if ( pLogic )
  {
    pLogic->ActivateImpulsiveBuff();
  }
}

AdventureScreen::UnitAttitude::Type AdventureScreen::GetUnitAttitude(NWorld::PFLogicObject const* pObject) const
{
  NWorld::PFBaseHero const* pHero = GetHero();
  if (!pObject || !pHero)
    return UnitAttitude::NA;

  // detect owned hero
  if (pObject == pHero)
    return UnitAttitude::SELF;

  // usable units are displayed as friendly ones
  if ( pObject->IsUsableBy( pHero ) )
    return UnitAttitude::ALLY;

  // basic attitude depends on faction
  UnitAttitude::Type attitude = pObject->GetFaction() == pHero->GetFaction() ? UnitAttitude::ALLY : UnitAttitude::HOSTILE;

  // neutrals are friends if I can't attack them
  if (pObject->GetFaction() == NDb::FACTION_NEUTRAL && !IsValidCommandTarget(CMD_ATTACK, VNULL3, pObject))
    attitude = UnitAttitude::ALLY;

  // a unit under control is like myself
  if (NWorld::PFBaseUnit const* pUnit = dynamic_cast<NWorld::PFBaseUnit const*>(pObject))
    if (pUnit->GetMasterUnit().GetPtr() == pHero)
      attitude = UnitAttitude::SELF;

  return attitude;
}

void AdventureScreen::ProcessSelectionPickEffects(NWorld::PFLogicObject* pLogicObj)
{
  if (pLogicObj && (selectedObject.GetPtr() == pLogicObj || currentPick.GetPickedPtr() == pLogicObj))
  {
    // systemLog( NLogg::LEVEL_MESSAGE ) << "##### ExecuteCommand(" << cmd << ") @ " << pObj << "; SEL = " << selectedObject.GetPtr() << "; PRE = " << currentPick.GetPickedPtr() << endl;
    bool isBuilding = (dynamic_cast<NWorld::PFBuilding*>(pLogicObj) != NULL);

    // choose preselection effect
    NDb::EEffects effect = NDb::EFFECTS_EMPTY;
    UnitAttitude::Type attitude = GetUnitAttitude(pLogicObj);
    switch (attitude)
    {
    case UnitAttitude::ALLY:
      effect = !isBuilding ? NDb::EFFECTS_SELECTIONPICKALLY : NDb::EFFECTS_SELECTIONBUILDINGPICKALLY;
      break;
    case UnitAttitude::HOSTILE:
      effect = !isBuilding ? NDb::EFFECTS_SELECTIONPICKHOSTILE : NDb::EFFECTS_SELECTIONBUILDINGPICKHOSTILE;
      break;
    case UnitAttitude::SELF:
      effect = !isBuilding ? NDb::EFFECTS_SELECTIONPICKSELF : NDb::EFFECTS_SELECTIONBUILDINGPICKSELF;
      break;
    default:
      NI_ALWAYS_ASSERT(NStr::StrFmt("Cannot choose (pre)selection pick effect for unit attitude '%i'", (int)attitude));
    }

    if (effect != NDb::EFFECTS_EMPTY)
    {
      NScene::SceneObject* pSceneObject = (selectedObject.GetPtr() == pLogicObj) ? selectedSceneObject : currentPick.GetScenePtr();
      if (pSceneObject)
      {
        if (IsValid(selectionPickEffect))
          selectionPickEffect->Die();
        selectionPickEffect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectAttached>(effect);
        selectionPickEffect->Attach(pSceneObject);
        pSceneObject->UpdateForced();
      }
    }
  }
}

const CVec3& AdventureScreen::GetCurrentCursorPosOnTerrain()
{
  return cursorPosOnTerrain;
}

void AdventureScreen::AwardUser(const nstl::vector<roll::SAwardInfo> & _awards)
{
  if (pLogic)
    pLogic->AwardUser(_awards);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tutorial stuff
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureScreen::ShowUIBlock( const char* id, bool show )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  UpdateBlockedKeys( id, show );

  if ( IsValid( flashInterface ) )
    flashInterface->ShowUIBlock( id, show );
}

void AdventureScreen::UpdateBlockedKeys( const char* id, const bool show )
{
  if( strcmp( id, "ActionBarTalentBtn" ) == 0 )
  {
    if( !show )
      blockedHotKeys |= ( 1 << FlashWindowsType::Talents );
    else
      blockedHotKeys &= ~( 1 << FlashWindowsType::Talents );
  }

  if( strcmp( id, "PortalBtn" ) == 0 )
  {
    if( !show )
      blockedHotKeys |= ( 1 << FlashWindowsType::Portal );
    else
      blockedHotKeys &= ~( 1 << FlashWindowsType::Portal );
  }

  if( strcmp( id, "ActionBarCharStatBtn" ) == 0 )
  {
    if( !show )
      blockedHotKeys |= ( 1 << FlashWindowsType::CharStat );
    else
      blockedHotKeys &= ~( 1 << FlashWindowsType::CharStat );
  }

  if( strcmp( id, "ActionBarInventoryBtn" ) == 0 )
  {
    if( !show )
      blockedHotKeys |= ( 1 << FlashWindowsType::Inventory );
    else
      blockedHotKeys &= ~( 1 << FlashWindowsType::Inventory );
  }

  if( strcmp( id, "ActionBarQuestBtn" ) == 0 )
  {
    if( !show )
      blockedHotKeys |= ( 1 << FlashWindowsType::QuestLog );
    else
      blockedHotKeys &= ~( 1 << FlashWindowsType::QuestLog );
  }

  if( strcmp( id, "ActionBarSocialBtn" ) == 0 )
  {
    if( !show )
      blockedHotKeys |= ( 1 << FlashWindowsType::SocialBar );
    else
      blockedHotKeys &= ~( 1 << FlashWindowsType::SocialBar );
  }

  if( strcmp( id, "ActionBarStatisticBtn" ) == 0 )
  {
    if( !show )
      blockedHotKeys |= ( 1 << FlashWindowsType::CurStatistics );
    else
      blockedHotKeys &= ~( 1 << FlashWindowsType::CurStatistics );
  }
}

void AdventureScreen::BlockActionBar( bool block )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->BlockActionBar( block );
}

void AdventureScreen::ShowAllUIBlocks( bool show )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if( !show )
    blockedHotKeys = 0xffffffff;
  else
    blockedHotKeys = 0;

  if ( IsValid( flashInterface ) )
    flashInterface->ShowAllUIBlocks( show );
}

void AdventureScreen::ShareFinalStatistics()
{
  UI::FlashContainer2* flash = pLogic->GetFlashContainer();
  if ( IsValid( flash ) )
  {
    int width, height;
    int x, y;
    if ( flash->GetDisplayObjectSize( "finalStat.wframe_mc", width, height, x, y ) )
    {
      UI::Point size = UI::ConvertToScreen( UI::Point( width, height ) );
      UI::Point place = UI::ConvertToScreen( UI::Point( x, y ) );
      socialServer->Share( place.x, place.y, size.x, size.y );
      return;
    }
  }

  socialServer->Share();
}

void AdventureScreen::PlaySameTeam(const bool agreed)
{
  if (!IsGameEnded())
    return;

  if (!playSameTeamEnabled || playSameTeamSent)
    return;

  playSameTeamSent = true;

  const StrongMT<IGameControl> gameControl(gameControlCallback.Lock());

  if (gameControl)
    gameControl->DispatchPlaySameTeamDecision(agreed);

  if (socialServer)
    PlaySameTeamSocial(agreed);
}

void AdventureScreen::OnBadBehaviourComplaint(const int userId, const int reportItemId)
{
  if (IsGameEnded())
    return;

  const CPtr<NWorld::PFPlayer> sender(GetPlayer());

  if (!IsValid(sender))
  {
    DevTrace("OnBadBehaviourComplaint: Invalid sender");
    return;
  }

  const CPtr<NWorld::PFPlayer> receiver(pWorld->GetPlayerByUID(userId));

  if (!IsValid(receiver))
  {
    DevTrace("OnBadBehaviourComplaint: Invalid receiver");
    return;
  }

  SendGameCommand(PlayerBehaviourTracking::CreateBadBehaviourComplaintCmd(sender, receiver, reportItemId), true);
}

void AdventureScreen::PlaySameTeamSocial(const bool agreed)
{
  NI_VERIFY(!!socialServer, "SS connection must be valid!", return);

  NWorld::PFPlayer* const localPlayer = GetPlayer();

  NI_VERIFY(!!localPlayer, "Local player must be valid!", return);

  vector<__int64> teamPlayers;

  for (int i = 0, count = GetWorld()->GetPlayersCount(); i < count; ++i)
  {
    NWorld::PFPlayer* const player = GetWorld()->GetPlayer(i);

    if (!player)
      continue;
    if (!player->IsPlaying())
      continue;

    if (player->IsBot())
      continue;
    if (player->GetTeamID() != localPlayer->GetTeamID())
      continue;

    teamPlayers.push_back(player->GetUserID());
  }

  if (teamPlayers.empty())
    return;

  socialServer->ChoosePartyAgain(teamPlayers, GetSessionId(), pLogic->GetPlaySameTeamTimeLeft(), agreed);
}

void AdventureScreen::HandlePlaySameTeamDecision(const CPtr<NWorld::PFPlayer>& player, const bool agreed)
{
  NI_VERIFY(IsValid(player), "Invalid player!", return);

  if (pLogic)
    pLogic->HandlePlaySameTeamDecision(GetPlayer(), player, agreed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Highlight
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureScreen::ShowTutorialTalentHighlight( int column, int raw, bool show )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->ShowTutorialTalentHighlight( column, raw, show );
}

void AdventureScreen::ShowTutorialInventoryItemHighlight( int slot, bool show )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->ShowTutorialInventoryItemHighlight( slot, show );
}

void AdventureScreen::ShowTutorialShopItemHighlight( int slot, bool show )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->ShowTutorialShopItemHighlight( slot, show );
}

void AdventureScreen::ShowTutorialActionBarItemHighlight( int slot, bool show )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->ShowTutorialActionBarItemHighlight( slot, show );
}

void AdventureScreen::ShowTutorialElementHighlight( string elementName, bool show )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->ShowTutorialElementHighlight( elementName, show );
}

void AdventureScreen::ShowTutorialHeroHighlight( int heroID, bool show )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->ShowTutorialHeroHighlight( heroID, show );
}

void AdventureScreen::ShowTutorialHeroLevelHighlight( int heroID, bool show )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->ShowTutorialHeroLevelHighlight( heroID, show );
}

void AdventureScreen::ShowTutorialOvertipLevelHighlight( bool show, float x, float y )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
    flashInterface->ShowTutorialOvertipLevelHighlight( show, x, y );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dialogs and cinematic stuff
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureScreen::StartHintDialog( const char* dialogId, const char* hintId, const char* hintImageId )
{
  pLogic->GetDialogController()->StartHintDialog( dialogId, hintId, hintImageId );
}

void AdventureScreen::StartDialog( const char* id, bool isCinematic )
{
  pLogic->GetDialogController()->StartDialog( id, isCinematic );
}

bool AdventureScreen::IsDialogFinished( const char* id ) const
{
  return pLogic->GetDialogController()->IsDialogFinished( id );
}

bool AdventureScreen::IsPhraseFinished( const char* id ) const
{
  return pLogic->GetDialogController()->IsPhraseFinished( id );
}

void AdventureScreen::PauseDialog( bool pause )
{
  pLogic->GetDialogController()->PauseDialog( pause );
}

void AdventureScreen::SetHintLine( const char* id, const char* bubbleViewType )
{
  return pLogic->GetDialogController()->SetHint( id, bubbleViewType );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quests
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureScreen::AddSessionQuest(string id, const NNameMap::Map* pMap)
{
  pLogic->GetDialogController()->AddSessionQuest( id, pMap );
}

void AdventureScreen::RemoveSessionQuest(string id)
{
  pLogic->GetDialogController()->RemoveSessionQuest( id );
}

bool AdventureScreen::UpdateSessionQuestCounter(string id, const int count)
{
  return pLogic->GetDialogController()->UpdateSessionQuestCounter( id, count );
} 

void AdventureScreen::UpdateSessionQuestText( string id, const NNameMap::Map* pMap )
{
  return pLogic->GetDialogController()->UpdateSessionQuestText( id, pMap );
} 

void AdventureScreen::SessionQuestRemoveSignal(string idQuest, string idSignal)
{
  pLogic->GetQuestsController()->SessionQuestRemoveSignal( idQuest, idSignal );
}

void AdventureScreen::SessionQuestUpdateSignal(string idQuest, string idSignal, float x, float y)
{
  pLogic->GetQuestsController()->SessionQuestUpdateSignal( idQuest, idSignal, x, y );
}

void AdventureScreen::SetAdventureControlsEnabled( bool enabled, bool enabledCursor )
{
  bAdventureControlsEnabled = enabled;
  bCursorEnabled = enabledCursor;
  bindsController->SetEnabled(BindsController::Lua,enabled);

  if ( !enabled )
  { 
    CancelCommand();
    SetState(AdventureScreen::STATE_NORMAL);
    SetSelectedObject(NULL, NULL);
    ClearAllSelections();
    pLogic->SetSelectedUnit(NULL);
  }

  NMainFrame::ShowCursor( bAlwaysShowCursor ? true : enabledCursor );
}

void AdventureScreen::UpdateCursor()
{
  NMainFrame::ShowCursor( bAlwaysShowCursor ? true : bCursorEnabled );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Bubbles
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureScreen::ShowTalentBubble( int column, int row, bool show, string id, string bubbleViewType, int bubbleIndex )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
  {
    wstring hintText;
    pLogic->GetDialogController()->GetHintTextById( id, hintText );
    flashInterface->ShowTalentBubble( column, row, show, hintText, bubbleViewType, bubbleIndex );
  }
}

void AdventureScreen::ShowActionBarButtonBubble( int index, bool show, string id, string bubbleViewType, int bubbleIndex )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
  {
    wstring hintText;
    pLogic->GetDialogController()->GetHintTextById( id, hintText );
    flashInterface->ShowActionBarButtonBubble( index, show, hintText, bubbleViewType, bubbleIndex );
  }
}

void AdventureScreen::ShowInventoryBarButtonBubble( int index, bool show, string id, string bubbleViewType, int bubbleIndex )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
  {
    wstring hintText;
    pLogic->GetDialogController()->GetHintTextById( id, hintText );
    flashInterface->ShowInventoryBarButtonBubble( index, show, hintText, bubbleViewType, bubbleIndex );
  }
}

void AdventureScreen::ShowShopBarButtonBubble( int index, bool show, string id, string bubbleViewType, int bubbleIndex )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
  {
    wstring hintText;
    pLogic->GetDialogController()->GetHintTextById( id, hintText );
    flashInterface->ShowShopBarButtonBubble( index, show, hintText, bubbleViewType, bubbleIndex );
  }
}

void AdventureScreen::ShowHeroBubble( int playerId, bool show, string id, string bubbleViewType, int bubbleIndex )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
  {
    wstring hintText;
    pLogic->GetDialogController()->GetHintTextById( id, hintText );
    flashInterface->ShowHeroBubble( playerId, show, hintText, bubbleViewType, bubbleIndex );
  }
}


void AdventureScreen::ShowBubble( string elementName, bool show, string id, string bubbleViewType, int bubbleIndex )
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
  {
    wstring hintText;
    pLogic->GetDialogController()->GetHintTextById( id, hintText );
    flashInterface->ShowBubble( elementName, show, hintText, bubbleViewType, bubbleIndex );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Script message box
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureScreen::ShowScriptMessageBox( const string& headerId, const string& textId )
{
  pLogic->GetDialogController()->ShowMessageBox( headerId, textId );
}
int AdventureScreen::GetLastMessageBoxResult() const
{
  return pLogic->GetDialogController()->GetLastMessageBoxResult();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Script message box
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AdventureScreen::FadeScene( int destFade, float time )
{
  if ( !sceneFader )
    Reset(sceneFader, new PF_Render::PostFXFader() );
  sceneFader->FadeTo( destFade, time );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AdventureScreen::IsWindowVisible( int winId ) const
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
  {
    return flashInterface->IsWindowVisible( winId );
  }

  return false;
}

int AdventureScreen::GetTalentActionBarIndex( int column, int row ) const
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
  {
    return flashInterface->GetTalentActionBarIndex( column, row );
  }

  return -1;
}

int AdventureScreen::GetInventoryItemActionBarIndex( int index ) const
{
  AdventureFlashInterface* flashInterface = pLogic->GetFlashInterface();

  if ( IsValid( flashInterface ) )
  {
    return flashInterface->GetInventoryItemActionBarIndex( index );
  }

  return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureScreen::AddHeroToInfoPanel( NWorld::PFBaseHero* pHero )
{
  pLogic->GetTeamInfo()->ShowHeroPortrait( pHero );
}

void AdventureScreen::OverrideHeroId( int playerID, uint overrideHeroId, const string& heroSkin, const wstring& nickname )
{
  for( int i = 0; i < startInfo.playersInfo.size(); ++i )
  {
    if( startInfo.playersInfo[i].playerID != playerID )
      continue;
    startInfo.playersInfo[i].playerInfo.heroId = overrideHeroId;
    startInfo.playersInfo[i].nickname = nickname;
  }
}

void AdventureScreen::AddToInventory( int playerID, int id )
{
  for( int i = 0; i < startInfo.playersInfo.size(); ++i )
  {
    if( startInfo.playersInfo[i].playerID != playerID )
      continue;
    startInfo.playersInfo[i].playerInfo.inventory.push_back( id );
  }
}

void AdventureScreen::SetTalentInTS( int playerID, int key, int talId )
{
  for( int i = 0; i < startInfo.playersInfo.size(); ++i )
  {
    if( startInfo.playersInfo[i].playerID != playerID )
      continue;
    startInfo.playersInfo[i].usePlayerInfoTalentSet = true;
    startInfo.playersInfo[i].playerInfo.talents[key].id = talId;
  }
}

bool AdventureScreen::GetEmblemTextureForTeam( int teamId, Render::Texture2DRef& tex )
{
  if ( guildEmblem && guildEmblem->IsDownloaded() )
  {
    if ( teamToGuildAuid.find( teamId ) != teamToGuildAuid.end() )
    {
      if ( guildAuidToTexture.find( teamToGuildAuid[teamId] ) != guildAuidToTexture.end() )
      {
        tex = guildAuidToTexture[teamToGuildAuid[teamId]];
        return IsValid( tex );
      }
      else
      {
        nstl::vector<byte> texData;
        if ( guildEmblem->GetData( teamToGuildAuid[teamId], texData ) )
        {
          guildAuidToTexture[teamToGuildAuid[teamId]] = Render::CreateARGBTextureFromFileInMemory( (const char*)&texData[0], texData.size(), 0 );
          tex = guildAuidToTexture[teamToGuildAuid[teamId]];
          return IsValid( tex );
        }
      }
    }
  }
  return false;
}
void AdventureScreen::AddToComplList(const CPtr<NWorld::PFPlayer>& player)
{
  if (player)
    playerComplList.push_back(player->GetUserID());

}
bool AdventureScreen::InComplList(const CPtr<NWorld::PFPlayer>& player) const
{
  if (player){
    nstl::vector<ComplList>::iterator it;

    it = (nstl::vector<ComplList>::iterator)nstl::find(playerComplList.begin(), playerComplList.end(), player->GetUserID());
    if (it != (nstl::vector<ComplList>::iterator)playerComplList.end())
      return true;
    else
      return false;
  }
  return false;
}

#pragma code_seg(push, "~")


void AdventureScreen::SetTimeScale(float timescale)
{
  pWorld->SetTimeScale(timescale);

  StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();
  if ( lgameControlCallback )
    lgameControlCallback->SetTimeScale(timescale);
}

void AdventureScreen::OnTimeScaleChanged(float timescale)
{
  NMainLoop::SetTimeScale(timescale);
}

void AdventureScreen::OnVictory( NDb::EFaction _failedFaction, int _surrenderVotes )
{
  STARFORCE_STOPWATCH();

  // Disable asserts on loading reward talents (we may receive a talent which wasn't
  // loaded, because we don't load talents if they aren't present in any hero's talent set)
  NDb::GetDbResourceCache().EnableAssertionLoadingFiles(false);

  failedFaction = _failedFaction;

  DebugTrace( "Faction %d lost The Game", (int)_failedFaction );

  HeroTitleCalculator heroTitleCalculator = HeroTitleCalculator( pWorld );
  if ( pWorld )
  {
    NWorld::PFStatistics* pStatistics = pWorld->GetStatistics();
    pStatistics->SetLoserFaction( _failedFaction );
    pStatistics->CalculateFinalScore( &heroTitleCalculator );
  }

  StatisticService::RPC::SessionClientResults sessionResults;
  FillSessionResults( sessionResults, _surrenderVotes );

  NGameX::ReplayInfo replayInfo;
  replayInfo.isWon = GetHero()->GetFaction() != failedFaction;

  CObj<HeroScoreWrapper> heroScore = new HeroScoreWrapper();
  heroScore->SetHero(GetHero());
  replayInfo.kills = heroScore->GetHeroScore(NDb::SCORETYPE_HEROKILLCOUNT);
  replayInfo.assists = heroScore->GetHeroScore(NDb::SCORETYPE_ASSISTCOUNT);
  replayInfo.deaths = heroScore->GetHeroScore(NDb::SCORETYPE_DEATHCOUNT);
  
  //replayInfo.heroId = GetHero()

  StrongMT<IGameControl> lgameControlCallback = gameControlCallback.Lock();
  if ( lgameControlCallback )
    lgameControlCallback->OnVictory( sessionResults, replayInfo );
    //GetWorld()->GetMapDescription()->mapType - get mapTYpe - MAPTYPE_PVP
    //bool isWin = 

  if ( isPlayingMinigame )
  {
    NWorld::PFEaselPlayer * localPlayer = dynamic_cast<NWorld::PFEaselPlayer *>( GetHero() );
    if ( IsValid( localPlayer ) && localPlayer->GetMinigames() )
      localPlayer->GetMinigames()->LeaveMinigame();
  }

  const NWorld::PFPlayer * player = GetPlayer();
  const NWorld::PFBaseHero * hero = GetHero();

  if( IsValid( pCameraController ) )
    pCameraController->LockZoom( true );

  const NDb::AdvMapDescription* const mapDesc = pWorld->GetMapDescription();

  //TODO: захардкоженный параметр задержки перенести в аргумент флешовой GameEnd.  орзунов —емен.
  if (skipTutorial)
  {
    endGameTimer.Start(1.f);
  }
  else
  {
    endGameTimer.Start(4.f);
    gameOverEffect.Start(failedFaction);

    AnnouncementParams announcementParams;
    announcementParams.killer = hero;

    if (GetHero()->GetFaction() != failedFaction)
      OnUIEvent(evVictory, player, &announcementParams);
    else
      OnUIEvent(evDefeat, player, &announcementParams);

    // --- play same team
    {
      const bool enabled = !IsCustomSessionType();
      const bool available = pLogic->CanDecideToPlaySameTeam(mapDesc, player);

      playSameTeamEnabled = enabled && available;
      playSameTeamSent = false;

      pLogic->ConfigurePlaySameTeamFeature(mapDesc, available, enabled);
    }
  }

  const NDb::EMapType mapType = mapDesc->mapType;
  const bool dontShowFinalStatistics = 
    mapType == NDb::MAPTYPE_TUTORIAL ||
    mapType == NDb::MAPTYPE_SERIES;
  const bool dontShowDialog = skipTutorial;

  pLogic->ShowGameOverMessage( failedFaction, &heroTitleCalculator, dontShowFinalStatistics, dontShowDialog );

  pCameraController->SetObservedObject(0);
  pCameraController->Lock(true);

  if ( IsValid(visibilityMap) )
  {
    visibilityMap->Update( 0.0f );
  }

  //ResetState
  SetState(STATE_NORMAL);

  // Stop ambient and heartbeating sounds
  StopGlobalSounds();

  // exit_on_finish is needed here for sequential auto-testing of game logic
  if ( NGlobal::GetVar( "exit_on_finish", 0 ).GetFloat() != 0 )
    NMainFrame::Exit();
}

#pragma code_seg(pop)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NGameX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool AddAI( const char *name, const vector<wstring> &params )
{
  if ( params.size() == 0 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << name << " all|self|others|friends|enemies|humans|bots" << endl;
    return true;
  }

	NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
	if ( !IsValid( advScreen ) )
    return false;

  NWorld::PFWorld* world = advScreen->GetWorld();
  if ( !IsValid( world ) )
    return false;

  // game is not loaded yet
  if ( world->GetStepNumber() < 0 )
    return false;

  NGameX::AdventureScreen::StartBotsFilter filter = NGameX::AdventureScreen::FilterAll;
  bool inverse = false;
  bool midOnly = false;

  for( vector<wstring>::const_iterator it = params.begin(); it != params.end(); ++it )
  {
    if ( NStr::WCmp( it->c_str(), L"all" ) == 0 )
    {
      filter = NGameX::AdventureScreen::FilterAll;
      inverse = false;
    }
    else if ( NStr::WCmp( it->c_str(), L"self" ) == 0 )
    {
      filter = NGameX::AdventureScreen::FilterSelf;
      inverse = false;
    }
    else if ( NStr::WCmp( it->c_str(), L"others" ) == 0 )
    {
      filter = NGameX::AdventureScreen::FilterSelf;
      inverse = true;
    }
    else if ( NStr::WCmp( it->c_str(), L"friends" ) == 0 )
    {
      filter = NGameX::AdventureScreen::FilterFriends;
      inverse = false;
    }
    else if ( NStr::WCmp( it->c_str(), L"enemies" ) == 0 )
    {
      filter = NGameX::AdventureScreen::FilterSelf;
      inverse = true;
    }
    else if ( NStr::WCmp( it->c_str(), L"humans" ) == 0 )
    {
      filter = NGameX::AdventureScreen::FilterHumans;
      inverse = false;
    }
    else if ( NStr::WCmp( it->c_str(), L"bots" ) == 0 )
    {
      filter = NGameX::AdventureScreen::FilterHumans;
      inverse = true;
    }
    else if ( NStr::WCmp( it->c_str(), L"mid" ) == 0 )
    {
      midOnly = true;
    }
    else
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "invalid argument \"" << *it << " for " << name << " command" << endl;
      continue;
    }

  }

  advScreen->StartBots( filter, inverse, midOnly );

  return true;  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool StopAI( const char *name, const vector<wstring> &params )
{
	NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
	if ( !IsValid( advScreen ) )
    return false;

	NWorld::PFWorld* world = advScreen->GetWorld();
  if ( !IsValid( world ) )
    return false;

	NWorld::PFAIContainer* container = world->GetAIContainer();
  if ( !IsValid( container ) )
    return false;

  bool selected = params.size() == 1 && params.find( L"selected" ) >= 0;
  if ( selected )
  {
    NWorld::PFBaseHero* hero = dynamic_cast<NWorld::PFBaseHero*>( NGameX::AdventureScreen::Instance()->GetSelectedObject().GetPtr() );
    if ( IsValid( hero ) )
      container->Remove(hero);
    else
    {
      DebugTrace( "\"%s selected\" works only on selected hero", name );
    }
  }
  else
    container->RemoveAll();

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CommandWaitStep( const char *name, const vector<wstring> &params )
{
    if ( params.size() != 1)
    {
		  systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " <world step number>" << endl;
		  return true;
    }
    
    int step = (int)NGlobal::VariantValue( params[0] ).GetFloat();

    if ( NGameX::AdventureScreen::Instance() && NGameX::AdventureScreen::Instance()->GetWorld() && NGameX::AdventureScreen::Instance()->GetWorld()->GetStepNumber() >= step )
    {
      return true;
    }

    return false;
}

static bool DumpAmbienceString(const char *name, const vector<wstring> &paramsSet)
{
  systemLog( NLogg::LEVEL_MESSAGE ) << wstring(ambienceDebugStr.GetValue()) << endl;
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" INTERMODULE_EXPORT void TooSmartLinker()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NI_DEFINE_REFCOUNT( NGameX::AdventureScreen );


REGISTER_DEV_CMD( add_ai, AddAI );
REGISTER_DEV_CMD( stop_ai, StopAI );

#ifdef EXPOMODE
REGISTER_VAR( "enemy_bots", g_enemyBots, STORAGE_NONE )
REGISTER_VAR( "ally_bots", g_allyBots, STORAGE_NONE )
REGISTER_VAR( "hack_e3_nicknames", g_hackE3Nicknames, STORAGE_NONE )
#else
REGISTER_DEV_VAR( "enemy_bots", g_enemyBots, STORAGE_NONE )
REGISTER_DEV_VAR( "ally_bots", g_allyBots, STORAGE_NONE )
REGISTER_DEV_VAR( "hack_e3_nicknames", g_hackE3Nicknames, STORAGE_NONE )
#endif


REGISTER_DEV_CMD( wait_step, CommandWaitStep );
REGISTER_CMD( toggle_free_camera, NGameX::ToggleFreeCamera );
REGISTER_DEV_CMD(ambience, DumpAmbienceString);

BASIC_REGISTER_CLASS( NGameX::IGameMenuMinigameActions );
NI_DEFINE_REFCOUNT( NGameX::IUIEventHandler);
BASIC_REGISTER_CLASS( NGameX::INaftaInfoProvider);

NI_DEFINE_REFCOUNT(NGameX::IGameControl);

REGISTER_DEV_VAR( "mouse_scrolling", g_mouseScrollingEnable, STORAGE_NONE );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ToggleUserInterfaceCmd( const char *name, const vector<wstring>& params )
{
  if (!gShowUserInterface) 
    gShowUserInterface = 1;
  else  
    gShowUserInterface = 0;
  return true;
}

REGISTER_VAR( "ui_show_interface", gShowUserInterface, STORAGE_NONE );
REGISTER_CMD( toggle_ui, ToggleUserInterfaceCmd );
REGISTER_DEV_VAR( "debug_mouse_point", debugMousePick.enabled, STORAGE_NONE );
REGISTER_DEV_VAR( "update_mouse_pos_mode", updateMouseMode, STORAGE_NONE );

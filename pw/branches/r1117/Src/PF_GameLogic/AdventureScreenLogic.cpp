#include "stdafx.h"
#include <algorithm>

#include "PFImpulsiveBuffs.h"
#include "../UI/FlashContainer2.h"
#include "AdventureFlashInterface.h"
#include "AdventureScreen.h"
#include "AdventureScreenLogic.h"
#include "Render/TextureManager.h"
#include "Client/MainTimer.h"
#include "Core/CoreFSM.h"
#include "System/DebugVar.h"
#include "System/ConfigFiles.h"

#include "UnitNameMap.h"
#include "PrecompiledTooltips.h"

#include "AdventureCameraController.hpp"

#include "DieTimer.h"
#include "FlyTexts.h"

#include "Minimap.h"

//new flash intreface
#include "AdventureFlashInterface.h"
#include "UnitInfoNew.h"
#include "TeamInfoNew.h"
#include "TalentPanelNew.h"
#include "ActionBarController.h"
#include "MinimapController.h"
#include "ShopController.h"
#include "InventoryController.h"
#include "ImpulseBuffsController.h"
#include "EscMenuController.h"
#include "StatisticsController.h"
#include "CharInfoContainer.h"
#include "DebugCharStat.h"
#include "BuffsController.h"
#include "FinalStatisticsController.h"
#include "AnnouncementController.h"
#include "AwardsController.h"
#include "CommonCombatController.h"
#include "DialogController.h"
#include "CTE_Controller.h"
#include "FriendsController.h"
#include "ComplainController.h"
#include "HeroRankCalculator.h"

//chat
#include "ChatController.h"
#include "SmartChatController.h"

//world classes
#include "PFConsumable.h"
#include "PFAbilityData.h"
#include "PFTalent.h"
#include "PFHero.h"
#include "PFWorld.h"
#include "PFPlayer.h"
#include "PFCheat.h"
#include "PFClientHero.h"
#include "HeroSpawn.h"
#include "HeroActions.h"
#include "PFTower.h"
#include "UI/PreferencesProcessor.h"
#include "UI/Root.h"
#include "PFAIWorld.h"
#include "AIWorldFacets/VotingForSurrenderLogic.h"
#include "VotingForSurrenderController.h"
#include "IgnoreListController.h"
#include "IgnoreListStorage.h"
#include "DBGameLogic.h"
#include "../NivalInput/Binds.h"
#include "SocialConnection.h"
#include "System/CmdLineLite.h"

#include "../NivalInput/ControlsSet.h"
#include "../NivalInput/InputCommandInstance.h"

#include "PlayerInfoHelper.hpp"
#include "DayNightController.h"

#include "Version.h"

namespace
{
  static const float c_rMaxTimeRqst = 10.0f;
  static int g_commonGraphicsQuality = 1;
  
  static bool g_showIcons = false;

  REGISTER_DEV_VAR( "debug_show_speed_icons", g_showIcons, STORAGE_NONE );
}

namespace NGameX
{

map<int, int> g_mapCollor;
void SetMapCollor(int nPlayerIndex)
{
  if (g_mapCollor.size() >= 5)
    return;
  map<int, int>::iterator it = g_mapCollor.find(nPlayerIndex), end = g_mapCollor.end();
  if (it == end)
    g_mapCollor[nPlayerIndex] = g_mapCollor.size();
}

int PlayerIndex2Collor(int nPlayerIndex)
{
  map<int, int>::const_iterator it = g_mapCollor.find(nPlayerIndex), end = g_mapCollor.end();
  NI_VERIFY(it != end, "UI: Unknown id!", return -1;)
  return it->second;
}

//////////////////////////////////////////////////////////////////////////

#pragma warning(push)
#pragma warning(disable:4201)
#pragma pack(push, 1)

union PartyKey
{
  PartyKey()
    : team(0U)
    , party(0U)
  {

  }

  explicit PartyKey(const NCore::PlayerStartInfo& psi)
    : team(0U)
    , party(0U)
  {
    switch (psi.teamID)
    {
    case NCore::ETeam::Team1:
      team = 1U;
      break;
    case NCore::ETeam::Team2:
      team = 2U;
      break;
    default:
      team = 0U;
      break;
    }

    party = psi.playerInfo.partyId;
  }

  bool operator!() const
  {
    if (team == 0U)
      return true;
    if (party == 0U)
      return true;

    return false;
  }

  operator unsigned long() const
  {
    return key;
  }
private:
  struct
  {
    unsigned char team : 8;
    unsigned long party : 24;
  };

  unsigned long key;
};

#pragma pack(pop)
#pragma warning(pop)

unsigned GetPartyKey(const NCore::PlayerStartInfo& psi)
{
  const PartyKey pk(psi);

  return !!pk ? pk : 0U;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AdventureScreenLogic::PrefCommonGraphicsQuality: public NGlobal::IVariable, public CObjectBase
{
  OBJECT_BASIC_METHODS( PrefCommonGraphicsQuality );
public:
  PrefCommonGraphicsQuality() {}
  explicit PrefCommonGraphicsQuality( Weak<AdventurepreferencesProcessor> pPrefs ): pPrefs(pPrefs) {} 
   
  virtual NGlobal::VariantValue Get() 
  {  
    return NGlobal::VariantValue(g_commonGraphicsQuality); 
  }

  virtual void Set( const NGlobal::VariantValue &val )
  {  
    g_commonGraphicsQuality = val.Get<int>(); 
    
    if( pPrefs )
      pPrefs->RestorePreset( g_commonGraphicsQuality );

  }
private:
  Weak<AdventurepreferencesProcessor> pPrefs;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AdventureScreenLogic::AdventureScreenLogic( ChatUiController * _chatController, SmartChatController * _smartChatController, BindsController * _bindsController )
	: closeTag( CLOSE_NO )
  , debugMessageWindow(0)
  , m_selectedUnit(NULL)
  , m_heroState(HS_Invalid)
  , isGameEnded(false)
  , chatController( _chatController )
  , smartChatController( _smartChatController )
  , mapType(NDb::MAPTYPE_PVP)
  , bindsController(_bindsController)
{
}

AdventureScreenLogic::~AdventureScreenLogic()
{
  NGlobal::UnregisterVar( "prefs_common_graphics_quality" );
}


void AdventureScreenLogic::RenderWindows()
{
  if (m_flyTexts)
    m_flyTexts->Render();

  UI::ClientScreenUILogicBase::RenderWindows();
}

void AdventureScreenLogic::UpdatePreferences()
{
  if( preferencesProcessor )
  {
    preferencesProcessor->ApplyValuesOnly();
    preferencesProcessor->Apply(); 

    if(!m_owner->IsInReplayMode())
    {
      NGlobal::SaveConfig( NProfile::GetFullFilePath( "user.cfg", NProfile::FOLDER_USER ), STORAGE_USER );
#ifdef _SHIPPING
      Input::SaveInputConfig( NProfile::GetFullFilePath( "input.cfg", NProfile::FOLDER_USER ), L"input" );
#endif
    }
  }
}

void AdventurepreferencesProcessor::Apply()
{
  PreferencesProcessor::Apply();

  if(!NGameX::AdventureScreen::Instance()->IsInReplayMode())
  {
    NGlobal::SaveConfig( NProfile::GetFullFilePath( "user.cfg", NProfile::FOLDER_USER ), STORAGE_USER );
#ifdef _SHIPPING
    Input::SaveInputConfig( NProfile::GetFullFilePath( "input.cfg", NProfile::FOLDER_USER ), L"input" );
#endif
  }
}


void AdventurepreferencesProcessor::Cancel()
{
  PreferencesProcessor::Cancel();

  //так как при закрытии окна настроек без сохранения/подтверждения сбрасываются только настройки графики, то остальные изменнения тоже должны сохранятся в файл 
  if(!NGameX::AdventureScreen::Instance()->IsInReplayMode())
  {
    NGlobal::SaveConfig( NProfile::GetFullFilePath( "user.cfg", NProfile::FOLDER_USER ), STORAGE_USER );

#ifdef _SHIPPING
    Input::SaveInputConfig( NProfile::GetFullFilePath( "input.cfg", NProfile::FOLDER_USER ), L"input" );
#endif
  }
}

void AdventurepreferencesProcessor::ApplyShortcuts()
{
  PreferencesProcessor::ApplyShortcuts();

  //так как при закрытии окна настроек без сохранения/подтверждения сбрасываются только настройки графики, то остальные изменнения тоже должны сохранятся в файл 
  if(!NGameX::AdventureScreen::Instance()->IsInReplayMode())
  {
    // отправка изменённых биндов в интерфейс
    AdventureScreenLogic* advLogic = dynamic_cast<AdventureScreenLogic*>(AdventureScreen::Instance()->GetLogic());
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
          advLogic->GetFlashInterface()->SetBindString(*iter);
          iter++;
        }
      }
    }

#ifdef _SHIPPING
    Input::SaveInputConfig( NProfile::GetFullFilePath( "input.cfg", NProfile::FOLDER_USER ), L"input" );
#endif
  }
}


void AdventurepreferencesProcessor::ShortcutRebind( const wchar_t *command )
{
  NGlobal::RunCommand(command, L"input");
}

void AdventureScreenLogic::SetOwner( NGameX::AdventureScreen * owner, const NDb::DBUIData * _uiData, const vector<NCore::PlayerStartInfo> & _playersInfo, ISocialConnection * _socialConnection )
{
  m_owner = owner;
  uiData = _uiData;

  socialConnection = _socialConnection;
  playerStartInfos = _playersInfo;
  m_flyTexts = new UIFlyTexts();
  m_flyTexts->Init(User());

  CollectPartyInfos();

  if (!pBaseWindow)
    return;

  flashWnd = UI::GetChildChecked<UI::FlashContainer2>( pBaseWindow, "FlashScreen", true );
  NI_ASSERT(IsValid(flashWnd), "doesnt have FlashScreen in children, will crush!");
 
  debugMessageWindow = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "DebugMessage", true );
  NI_ASSERT(debugMessageWindow, "UI: DebugMessage layer not found");

  lowSpeedWnd = UI::GetChildChecked<UI::Window>( pBaseWindow, "LowSpeedIco", true );
  NI_ASSERT(IsValid(lowSpeedWnd), "doesnt have LowSpeedIco in children");

  noConnectWnd = UI::GetChildChecked<UI::Window>( pBaseWindow, "NoConnectIco", true );
  NI_ASSERT(IsValid(noConnectWnd), "doesnt have NoConnectIco in children");

  debugCharStat = new DebugCharStat(UI::GetChildChecked<UI::Window>( pBaseWindow, "UnitStatInfo",true ), uiData);

  flashInterface = new AdventureFlashInterface( flashWnd, "mainInterface" );  
      
  flashInterface->HideAllWindows();

  if ( owner->IsSpectator() )
    flashInterface->SwitchToSpectatorMode();
 
  //new UI
  generalTooltip = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "General_tooltip", true);
  actionBarTooltip =  UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "ABTooltip", true);

  selectionInfo = new SelectionInfo(flashWnd, flashInterface, owner);
  talentPanel = new TalentPanelNew( uiData, flashWnd, flashInterface, owner, generalTooltip );
  minimapController = new MinimapController(flashWnd, flashInterface, owner);
  escMenuController = new EscMenuController(flashWnd, flashInterface, m_owner);
  statisticsController = new StatisticsController(flashInterface, owner->GetWorld());
  ourHeroBuffs   = new BuffsController(flashWnd, generalTooltip, flashInterface, BuffsOwner::OurHero);
  selectionBuffs = new BuffsController(flashWnd, generalTooltip, flashInterface, BuffsOwner::Selection);
  finalStatisticsController = new FinalStatisticsController(flashWnd, generalTooltip, flashInterface, owner->GetWorld(),owner);
  announcementController = new AnnouncementController(flashInterface, uiData, owner->GetAnnouncementSoundPlayer() );
  dialogController = new DialogController(flashWnd, flashInterface, uiData, owner->GetWorld());
  complainController = new ComplainController(flashWnd, flashInterface, socialConnection, playerStartInfos, chatController, bindsController);
  charInfoContainer = new CharInfoContainer(flashWnd, generalTooltip, uiData, flashInterface, owner);
  commonCombatController = new CommonCombatController(flashWnd, flashInterface, owner);
 
  for( int i = 0; i < NCore::ETeam::COUNT; ++i )
  {  
    using namespace NWorld::AIWorldFacets;
    
    VotingForSurrenderLogic * const pVFS = owner->GetWorld()->GetAIWorld()->GetVotingForSurrender(i);
    
    if( pVFS->GetTeam() == owner->GetPlayer()->GetTeamID() )
    {                
      votingForSurrenderController = new VotingForSurrenderController(pVFS, UI::GetUIRoot()->votingForSurrender, flashWnd, "mainInterface" );
      break;
    }
  }

  InitErrorMessages(flashInterface, uiData);

  bool isMuted = false;
  bool isLeaver = false;
  bool isLeaverParty = false;

  {
    const NCore::PlayerStartInfo* const psi = PlayerInfoHelper::FindPlayerInfoByPlayerId(playerStartInfos, owner->GetLocalPlayerID());

    NI_ASSERT(!!psi, NStr::StrFmt("Player info not found! (playerId=%d)", owner->GetLocalPlayerID()));

    if (psi)
    {
      isMuted = psi->playerInfo.chatMuted;
      isLeaver = PlayerInfoHelper::IsLeaver(psi);
      isLeaverParty = isLeaver || PlayerInfoHelper::IsLeaverParty(playerStartInfos, psi);
    }
  }

  //chat
  if (IsValid(chatController))
  {
    chatController->AddChatUI(flashWnd, flashInterface, isMuted, isLeaver, isLeaverParty);

    ignoreListStorage = m_owner->GetIgnoreListStorage();
  }

  preferencesProcessor = new AdventurepreferencesProcessor( flashWnd, "PreferencesInterface" );
  NGlobal::RegisterVar( "prefs_common_graphics_quality", new PrefCommonGraphicsQuality(preferencesProcessor.Get()), STORAGE_NONE );
  preferencesProcessor->Init( *UI::GetUIRoot()->preferences );

  if (IsValid(smartChatController))
  {
    smartChatController->AddSmartChatUI(flashWnd, flashInterface);
  }

  m_pPauseTimer = AutoPtr<PauseTimer>(new PauseTimer(UI::GetChildChecked<UI::Window>(pBaseWindow, "Pause", true)));
}



void AdventureScreenLogic::SetHero(NWorld::PFBaseHero const *pHero) 
{ 
  NI_PROFILE_FUNCTION

  if (!IsValid(flashWnd))
    return;

  NWorld::PFBaseMaleHero *pMale = (NWorld::PFBaseMaleHero *) pHero;

  actionBarController = 0;
  shopController = 0;
  inventoryController = 0;
  impulseBuffsController = 0;
  newTeamInfo = 0;
  awardsController = 0;
  friendsController = 0;
  

  const NDb::AILogicParameters& aiLogic = m_owner->GetWorld()->GetAIWorld()->GetAIParameters();
  Strong<HeroRankCalculator> rankCalculator = new HeroRankCalculator(aiLogic.heroRanks);
  newTeamInfo = new TeamInfoNew(flashWnd, flashInterface, pHero, m_owner, uiData, rankCalculator);

  const PlayerDataManager * playersData = m_owner->GetPlayerDataMan();

  for (int i = 0; i < m_owner->pWorld->GetPlayersCount(); ++i)
  {
    const NWorld::PFPlayer * pPlayer = m_owner->pWorld->GetPlayer(i);
    if (IsValid(pPlayer) && IsValid(pPlayer->GetHero()))
    {
      bool isPremium = false;
      if (IsValid(playersData))
      {
        const PlayerData & playerData = playersData->GetPlayerData(pPlayer->GetPlayerID());
        isPremium = playerData.IsPremium();
      }

      newTeamInfo->AddHero(pPlayer->GetHero(), isPremium);

      switch( mapType )
      {
      case NDb::MAPTYPE_SERIES:
        if ( pHero->GetPlayer() == pPlayer )
          newTeamInfo->ShowHeroPortrait( pPlayer->GetHero() );
        break;
      case NDb::MAPTYPE_COOPERATIVE:
        if ( pHero->GetPlayer()->GetTeamID() == pPlayer->GetTeamID() )
          newTeamInfo->ShowHeroPortrait( pPlayer->GetHero() );
        break;
      default:
          newTeamInfo->ShowHeroPortrait( pPlayer->GetHero() );
        break;
      }
      charInfoContainer->AddHero( pPlayer->GetHero() );
    }
  }

  friendsController = new FriendsController(flashWnd, flashInterface, socialConnection, playerStartInfos, pHero->GetPlayer()->GetUserID());
  actionBarController = new ActionBarController( uiData, flashWnd, flashInterface, m_owner, pMale, actionBarTooltip );
  shopController = new ShopController( uiData, flashWnd, generalTooltip, flashInterface, m_owner, pMale );
  inventoryController = new InventoryController( flashWnd, generalTooltip,flashInterface, m_owner, pHero );
  impulseBuffsController = new ImpulseBuffsController( flashWnd, generalTooltip, flashInterface, uiData->impulsiveBuffsParams, m_owner->GetImpulseBuffsManager(), pHero );
  
  int heroExp = 0;
  int heroRating = 0;

  if (IsValid(playersData))
  {
    const PlayerData & playerData = playersData->GetPlayerData(pHero->GetPlayerId());
    heroExp = playerData.GetHeroExperience();
    heroRating = playerData.GetHeroRating();
  }

  awardsController = new AwardsController(flashWnd, m_owner->GetWorld()->GetAIWorld()->GetAIParameters(),  uiData, generalTooltip, flashInterface, m_owner->GetWorld()->GetResourcesCollection(), pHero->GetOriginalFaction(), heroExp, heroRating, rankCalculator, playersData );

  ourHeroBuffs->SetUnit(pHero);
  talentPanel->SetHero(pMale);

  charInfoContainer->SetOurHero(pHero);
  minimapController->Init();

}

void AdventureScreenLogic::OnMapLoaded( const NDb::AdvMapDescription * advMapDescription, const NDb::AdvMapSettings * settings,bool isCustomGame)
{
  mapType = advMapDescription->mapType;
	fwodVisualInfo = advMapDescription->FirstWinVisualInfo;

  //кастомные обработчики карт
  if ( flashInterface )
  {
    if ( mapType == NDb::MAPTYPE_CTE )
    {
      cteController = new CTE_Controller(flashInterface, dynamic_cast<const NDb::DbAdvMapCTESettings*> (settings), m_owner->GetWorld()->GetAIContainer());
    }
    else if ( mapType == NDb::MAPTYPE_TUTORIAL || mapType == NDb::MAPTYPE_SERIES )
    {
      flashInterface->SwitchToTutorialMode();
    }
    else if ( mapType == NDb::MAPTYPE_COOPERATIVE)
    {

      const NDb::StatisticBackgoundImages * statisticImages =  & (advMapDescription->statisticBackgroundImages);

      const char * win = statisticImages->win!=0? statisticImages->win->textureFileName.c_str(): "";
      const char * loose = statisticImages->loose!=0? statisticImages->loose->textureFileName.c_str(): "";
      const char * normal = statisticImages->normal!=0? statisticImages->normal->textureFileName.c_str(): "";
      flashInterface->SetStatisticBackImages(normal, loose, win);
    }

			flashInterface->RaitingPenaltyEnabled( (mapType == NDb::MAPTYPE_PVP || mapType == NDb::MAPTYPE_CTE) && !isCustomGame );
  }

  if ( settings->enableAnnouncements )
  {
    if ( settings->useCustomBattleStartAnnouncement )
      announcementController->ShowStartBattleAnnouncement( settings->customBattleStartAnnouncement );
    else
      announcementController->ShowStartBattleAnnouncement();
  }

	
}

void AdventureScreenLogic::SetComplains(int complaintsToday,int complaintsMax, NCore::TComplaintInfo const&  complaintsInfo)
{
	complainController->Init( complaintsToday, complaintsMax, complaintsInfo );
}

__int64 AdventureScreenLogic::GetPlayerAuid() const
{
  for (int i = 0; i< playerStartInfos.size(); i++)    
	{
		if ( playerStartInfos[i].playerID == m_owner->GetLocalPlayerID() )   
    {
      return playerStartInfos[i].userID;
    }
  }
  return 0;
}

void AdventureScreenLogic::SetDialogs( NWorld::PFBaseHero const *pHero, NDb::Ptr<NDb::DialogsCollection> const& dialogs, NDb::Ptr<NDb::HintsCollection> const& hints, NDb::Ptr<NDb::SessionQuestsCollection> const& quests )
{
  if ( !pHero || !dialogController )
    return;

  dialogController->Init( pHero, dialogs, hints, quests );

  if( !questsController && quests )
  {
    NI_ASSERT( IsValid(flashWnd), "doesnt have FlashScreen in children, will crush!" );
    questsController = new QuestsController( flashWnd, quests );
  }

}


void AdventureScreenLogic::DoCustomEvents( float deltaTime )
{
  NI_PROFILE_FUNCTION

	if ( !IsValid(pBaseWindow)  || !IsValid(m_owner->GetWorld()))
		return;

  NI_VERIFY(IsValid(m_owner->GetHero()), "InvalidHero for UI", return);

  CheckWasCrossAidsRiver();

  if (Get(m_pPauseTimer))
    m_pPauseTimer->Update(deltaTime);

  //chat
  if (chatController)
    chatController->Update();

  //new flash interface
  int _x = lastMousePosition.x, _y=lastMousePosition.y;
  
  talentPanel->Update(_x, _y);
  shopController->Update(_x, _y);
  inventoryController->Update(_x, _y);
  selectionBuffs->Update(_x, _y);
  ourHeroBuffs->Update(_x, _y);
  finalStatisticsController->Update(_x, _y);
  charInfoContainer->Update(_x, _y);
  impulseBuffsController->Update(deltaTime, _x, _y);
  awardsController->Update(_x, _y);

  announcementController->Update(deltaTime);
  newTeamInfo->Update();
  selectionInfo->Update();
  statisticsController->Update();
  votingForSurrenderController->Update(deltaTime);
  dialogController->Update( deltaTime );

  if (cteController)
    cteController->Update(deltaTime);

  NWorld::ImpulsiveBuffsManager * buffsManager = m_owner->GetImpulseBuffsManager();
  actionBarController->Update(m_owner->GetHeroPrimeNafta(), buffsManager->GetMoney());
  
  //DEBUG
  debugCharStat->Update();

  UpdateConnectionAndSpeedWindows();
}



void AdventureScreenLogic::CloseAdventureScreen()
{
	if ( closeTag == CLOSE_NO )
		closeTag = CLOSE_SCREEN;
}


void AdventureScreenLogic::SetMessage( const wstring & msg )
{
  SetMessage(msg, true, 3.0f);
}

void AdventureScreenLogic::SetMessage( const wstring & msg, bool playSound, float lifeTime )
{
  NI_VERIFY(flashInterface, "Invalid flashinterface!", return);
  flashInterface->ShowErrorEvent(msg, playSound, lifeTime);
}

void AdventureScreenLogic::InitErrorMessages( AdventureFlashInterface * _flashInterface, NDb::Ptr<NDb::DBUIData> dbUIData )
{
  NI_VERIFY(IsValid(dbUIData) && flashInterface, "invalid ui data", return);
  for (int i=0; i< dbUIData->errorMessageDescriptions.size(); i++)
  {
    const NDb::ErrorMessageDescription & desc = dbUIData->errorMessageDescriptions[i];
    flashInterface->SetErrorMessage((NDb::EErrorMessageType)i, desc.textMessage.GetText(), desc.shouldPlaySound, desc.lifeTime);
  }
}

void AdventureScreenLogic::UpdateErrorMessageTextByVariant( NDb::EErrorMessageType messageType, const NNameMap::Map* values )
{
  const NDb::ErrorMessageDescription & desc = uiData->errorMessageDescriptions[messageType];
  wstring newText;
  wstring const& message = desc.textMessage.GetText();

  NGameX::PrecompiledTooltip tooltip;
  tooltip.Init( values, message );
  tooltip.MakeText( newText );

  flashInterface->SetErrorMessage( messageType, newText, desc.shouldPlaySound, desc.lifeTime );
}

void AdventureScreenLogic::UpdateConnectionAndSpeedWindows()
{
  bool isLocalGame = NGlobal::GetVar( "local_game" ).Get<bool>() ;

  if (noConnectWnd)
  {
    bool hasTrancieverData = NDebug::GetDebugVarValue<bool>(L"HasTrancieverData");
    bool isInReplayMode = m_owner ? m_owner->IsInReplayMode() : false;

    noConnectWnd->Show(g_showIcons || !hasTrancieverData && !isLocalGame && !isGameEnded && !isInReplayMode );
  }
   
  if (lowSpeedWnd)
  {
    float fps = NDebug::GetDebugVarValue<float>(L"FPS");
    lowSpeedWnd->Show( g_showIcons || fps<=15 && !isLocalGame);
  }
}

void AdventureScreenLogic::SetErrorMessage( NDb::EErrorMessageType msgType, bool show /*= true*/, const NNameMap::Map* values /*= 0*/ )
{
  NI_VERIFY(flashInterface, "invalid flashinterface data", return);
  
  if ( values )
  {
    UpdateErrorMessageTextByVariant( msgType, values );
  }

  flashInterface->ShowErrorMessage(msgType, show);
}

void AdventureScreenLogic::ShowAnnouncement( PFUISignAnnouncement const * sign , AnnouncementParams * announcementParams )
{
  if (announcementController)
    announcementController->ShowAnnouncement(sign, announcementParams);
}


void AdventureScreenLogic::SetDebugMessage(string const & msg)
{
  NI_ASSERT(IsValid(debugMessageWindow), "DebugMessage window should be valid" );
  debugMessageWindow->SetCaptionTextA(msg.c_str());
  debugMessageWindow->Show(true);
}



void AdventureScreenLogic::ClearDebugMessage()
{
  NI_ASSERT(IsValid(debugMessageWindow), "DebugMessage window should be valid" );
  debugMessageWindow->Show(false);
}


void AdventureScreenLogic::EmulateImpulsiveBuffButton( bool on )
{
	if (impulseBuffsController)
		impulseBuffsController->BuyImpulse(true);
}



void AdventureScreenLogic::ActivateImpulsiveBuff()
{
  if (impulseBuffsController)
	  impulseBuffsController->BuyImpulse(true);
}



void AdventureScreenLogic::OnDenyTower(int action)
{
  return;

  /*if ( !m_owner)
    return;

  NWorld::PFTower * pTower = dynamic_cast<NWorld::PFTower*>(m_owner->GetSelectedObject().GetPtr());
  NWorld::PFBaseHero* pHero = dynamic_cast<NWorld::PFBaseHero*>( m_owner->GetHero() );
  if ( IsValid(pTower) && IsValid(pHero) && pTower->CanDenyBuilding(pHero) )
  {
    m_owner->SendGameCommand( CreateCmdDenyBuilding(pHero, pTower) );
  }*/
}


AdventureScreenLogic::HeroState AdventureScreenLogic::GetHeroState() const
{
  if( NULL != m_owner )
  {
    NWorld::PFBaseHero const* pHero = m_owner->GetHero();
    if( IsValid(pHero) )
      return pHero->IsDead() ? ( pHero->IsResurrecting() ? HS_Resurrecting : HS_Dead ) : HS_Living;
    else
    {
      NI_DATA_ALWAYS_ASSERT("UI: Invalid hero!");
    }
  }
  else
  {
    NI_DATA_ALWAYS_ASSERT("UI: Invalid screen logic!");
  }

  return HS_Invalid;
}

void AdventureScreenLogic :: CheckWasCrossAidsRiver()
{
  HeroState const state = GetHeroState();
  if( state != m_heroState )
  {
    if( HS_Living == state )
    {}
    else if( HS_Resurrecting == state)
      HeroStartedResurrect();
    else
      HeroDied();

    m_heroState = state;
  }
}


///////////////////////////////////////////////////////////////
void AdventureScreenLogic :: HeroStartedResurrect()
{
  if (m_owner)
  {
    if (NWorld::PFBaseHero const * pHero = m_owner->GetHero())
    {
      m_owner->MoveCameraTo(pHero, false);
    }
  }
}


///////////////////////////////////////////////////////////////
void AdventureScreenLogic :: HeroDied()
{
  //reset camera observer
  if (m_owner)
    m_owner->SetObservingObject(0);
}



void AdventureScreenLogic::ShowPauseTimer(bool bShow, NWorld::PFBaseHero const *pWho)
{
  if (Get(m_pPauseTimer))
    m_pPauseTimer->Show(bShow, pWho);
}


void AdventureScreenLogic::SetSelectedUnit( const NWorld::PFBaseUnit* pUnit )
{
  if ( pUnit != selectionInfo->GetUnit() )
  {
    NSoundScene::EventStart( uiData->soundEvents.selection );
    bool isEnemy = IsValid(pUnit) && IsValid(m_owner->GetHero()) ? pUnit->GetFaction() != m_owner->GetHero()->GetFaction(): false;

    selectionInfo->SetUnit(pUnit, isEnemy);
    debugCharStat->SetUnit(pUnit);
    selectionBuffs->SetUnit(pUnit);
    charInfoContainer->SetSelectionUnit(pUnit);
  }
}


void AdventureScreenLogic::OnSessionStart( lobby::TGameId sessionId )
{
  if (!flashInterface)
    return;
  
  const wchar_t * vesrion = NStr::StrFmtW( L"%S-%d.%d.%02d.%04d, session %016llx", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD, VERSION_REVISION, sessionId );

  wstring ver(vesrion);

  flashInterface->SetClientVersion(ver);

  const Strong<NGameX::IPlayerIdMapper> playerIdMapper(NGameX::PlayerIdMapper::Create(playerStartInfos));

  if (ignoreListStorage)
  {
    NGameX::IgnoreListController::CreateStruct ilc_cs;

    ilc_cs.flashContainer = flashWnd;
    ilc_cs.flashInterface = flashInterface;
    ilc_cs.playerIdMapper = playerIdMapper;
    ilc_cs.ignoreListStorage = ignoreListStorage;
    ilc_cs.uiData = uiData;

    const Strong<NGameX::IgnoreListController> ilc(new NGameX::IgnoreListController(ilc_cs));

    if (IsValid(chatController))
      chatController->SetIgnoreListController(ilc);

    ignoreListController = ilc;
    ignoreListController->InvalidateFlashInterface();
  }

  if (IsValid(chatController))
    chatController->SetPlayerIdMapper(playerIdMapper);
}


void AdventureScreenLogic::ShowGameOverMessage( NDb::EFaction failedFaction, HeroTitleCalculator const* heroTitleCalculator, bool dontShowStatistics, bool dontShowDialog /*= false */ )
{
  NWorld::PFBaseHero * ourHero= m_owner->GetHero();
  NI_VERIFY( ourHero, "", return );
  NDb::EFaction ourFaction = ourHero->GetFaction();

  isGameEnded = true;

  if (!uiData)
    return;

  const bool isVictory = (ourFaction != failedFaction);

  if (dontShowDialog)
  {
    flashInterface->GameEnd(isVictory, "", true, true);
  }
  else
  {
    const NDb::EFaction ourOriginalFaction = m_owner->GetHero()->GetOriginalFaction();

    NDb::Ptr<NDb::Texture> dbTexture;

    switch (ourOriginalFaction)
    {
    case NDb::FACTION_FREEZE:
      dbTexture = isVictory
        ? uiData->victoryDefeatImages.VictoryFreeze
        : uiData->victoryDefeatImages.DefeatFreeze;
      break;
    case NDb::FACTION_BURN:
      dbTexture = isVictory
        ? uiData->victoryDefeatImages.VictoryBurn
        : uiData->victoryDefeatImages.DefeatBurn;
      break;
    }

    const char* const endImage = IsValid(dbTexture) ? dbTexture->textureFileName.c_str() : "";

    flashInterface->GameEnd(isVictory, endImage, dontShowStatistics, false);
  }

  finalStatisticsController->FillFinalData( heroTitleCalculator );

  if (isVictory)
    SetFirstWinVisual(ourHero);
}



void AdventureScreenLogic::SetFirstWinVisual( NWorld::PFBaseHero * ourHero )
{
	PlayerDataManager * playersData = m_owner->GetPlayerDataMan();
	if (!IsValid(playersData))
		return;

	const PlayerData & playerData = playersData->GetPlayerData(ourHero->GetPlayerId());

	if (!playerData.IsFirstWin() || !fwodVisualInfo || playerData.IsCustomGame())
		return;

	const char * iconPath = fwodVisualInfo->icon? fwodVisualInfo->icon->textureFileName.c_str(): "";

	flashInterface->SetFirstWin(iconPath, fwodVisualInfo->sessionTooltip.GetText());
}


void AdventureScreenLogic::UpdateTooltipsSaturation( )
{
  bool forbidSaturate = false;

  if (flashWnd)
    forbidSaturate = flashWnd->IsMouseUnderUnblockedElement();

  if (generalTooltip)
    generalTooltip->ForbidSaturation(forbidSaturate);

  if (actionBarTooltip)
    actionBarTooltip->ForbidSaturation(forbidSaturate);
}



void AdventureScreenLogic::PressRemovePauseButton()
{
#ifndef _SHIPPING
  CheatData data;
  data.cheater = m_owner->GetHero();
  CreateCheatCmd( "set_pause", "false", data );
#endif
}

bool AdventureScreenLogic::IsMouseUnderWindow()
{ 
  return flashWnd? flashWnd->IsMouseUnderWindow() : false;
}

void AdventureScreenLogic::AwardUser( const nstl::vector<roll::SAwardInfo> & _awards )
{
  if (awardsController)
  {
    vector<AwardData> awards;

    for(int i = 0; i<_awards.size(); i++)
    {
      if ( !_awards[i].isOwnedByPlayer )
        continue;

      AwardData award;
  
      award.type            = _awards[i].type;
      award.id              = _awards[i].id;
      award.customCurrencyId= _awards[i].customCurrencyId;
      award.vendorCost      = _awards[i].vendorCost;
      award.isOwnedByPlayer = _awards[i].isOwnedByPlayer;
      award.count           = _awards[i].count;
			award.isTasty         = _awards[i].isTasty;
			award.giverUser				= _awards[i].giverUser;
      
      awards.push_back(award);
    }
    awardsController->AwardUser(awards);
  }

}

void AdventureScreenLogic::OnScreenResolutionChanged()
{
//  if ( m_owner.Valid() )
//    m_owner->GetMinimap()->InitializeMinimapTexture();
}

void AdventureScreenLogic::DebugAwardExperience( int experience, float raiting )
{
  if (awardsController)
  {
		vector<AwardData> awards(10);
  
    awards[0].type            = roll::EAwardType::Experience;
    awards[0].count           = experience;
    awards[0].isOwnedByPlayer = true;

    awards[1].type            = roll::EAwardType::Pearl;
    awards[1].count           = 2;
    awards[1].isOwnedByPlayer = true;
		awards[1].giverUser       = m_owner->GetHero()->GetPlayer()->GetUserID();

    awards[2].type            = roll::EAwardType::Silver;
    awards[2].count           = 100500;
    awards[2].isOwnedByPlayer = true;

    awards[3].type            = roll::EAwardType::Resource1;
    awards[3].count           = 10;
    awards[3].isOwnedByPlayer = true;

    awards[4].type            = roll::EAwardType::Resource2;
    awards[4].count           = 20;
    awards[4].isOwnedByPlayer = true;

    awards[5].type            = roll::EAwardType::Resource3;
    awards[5].count           = 30;
    awards[5].isOwnedByPlayer = true;

		awards[6].type            = roll::EAwardType::Resource3;
		awards[6].count           = 29;
		awards[6].isOwnedByPlayer = true;
		awards[6].isTasty					= true;


		awards[7].type            = roll::EAwardType::HeroRating;
		awards[7].count           = raiting;


    awards[8].type            = roll::EAwardType::MarketingEvent;
    awards[8].isOwnedByPlayer = true;
    awards[8].id              = Crc32Checksum().AddString("GoldLampItem_200").Get();;
    awards[8].count           = raiting;

    awards[9].type            = roll::EAwardType::RedPearl;
    awards[9].count           = 2;
    awards[9].isOwnedByPlayer = true;
    awards[9].giverUser       = m_owner->GetHero()->GetPlayer()->GetUserID();

		/*for (int i = 0; i<20; i++)
		{
			awards.push_back(AwardData());
			AwardData & awardData = awards.back();
			awardData.type = roll::EAwardType::Talent;
			awardData.count = 1;
			awardData.isOwnedByPlayer = true;
			awardData.id = 25313680;
		}*/


    awardsController->AwardUser(awards);
  }
}

#ifndef _SHIPPING
void AdventureScreenLogic::DebugAwardUser(const vector<AwardData> & _awards)
{
  awardsController->AwardUser(_awards);
}
#endif

void AdventureScreenLogic::ActivateChat()
{
  if (!IsValid(chatController))
    return;

  if (IsValid(smartChatController))
    if (smartChatController->IsActive())
      return;

  if (flashInterface)
    flashInterface->OpenCloseChat();
}

void AdventureScreenLogic::ActivateChatChannel(const NDb::EChatChannel channel)
{
  if (!IsValid(chatController))
    return;

  if (IsValid(smartChatController))
    if (smartChatController->IsActive())
      return;

  if (flashInterface)
    flashInterface->OpenChatChannel(channel);
}

void AdventureScreenLogic::ActivateSmartChat()
{
  if (!IsValid(smartChatController))
    return;

  if (IsValid(chatController))
    if (chatController->IsActive())
      return;

  if (flashInterface)
  {
    if (smartChatController->IsActive())
      flashInterface->SmartChatDeactivate();
    else
      flashInterface->SmartChatActivate();
  }
}

bool AdventureScreenLogic::ProcessUIEvent(const Input::Event& event)
{
  if (GetDialogController()->ProcessUIEvent(event))
    return true;

  if (IsValid(smartChatController))
    if (smartChatController->ProcessUIEvent(event))
      return true;

  return false;
}

void AdventureScreenLogic::ConfigurePlaySameTeamFeature(const NDb::AdvMapDescription* const advMapDescription, const bool available, const bool enabled)
{
  // available: может ли локальный игрок принимать решение
  // enabled: доступна ли фича

  if (!enabled)
  {
    flashInterface->ConfigurePlaySameTeamFeature(false, 0);

    playSameTeamDecisionDeadline = timer::Now();
  }
  else
  {
    flashInterface->ConfigurePlaySameTeamFeature(available, advMapDescription->playSameTeamTimeOut);

    playSameTeamDecisionDeadline = timer::Now() + timer::Time(advMapDescription->playSameTeamTimeOut);
  }
}

void AdventureScreenLogic::HandlePlaySameTeamDecision(const NWorld::PFPlayer* const localPlayer, const NWorld::PFPlayer* const player, const bool agreed)
{
  NI_VERIFY(!!localPlayer, "Invalid local player!", return);
  NI_VERIFY(!!player, "Invalid player!", return);

  // не показывать решения команды соперников
  if (localPlayer->GetTeamID() != player->GetTeamID())
    return;

  const PartyInfo* const partyInfo = GetPlayerPartyInfo(player);

  if (!partyInfo)
  {
    flashInterface->HandlePlaySameTeamDecision(player->GetPlayerID(), agreed);
    return;
  }

  const bool isPartyLeader = partyInfo->IsPartyLeader(player);

  if (!isPartyLeader)
    return;

  const PartyInfo::MemberVector& partyMembers = partyInfo->GetMembers();

  PartyInfo::MemberVector::const_iterator it = partyMembers.begin();
  PartyInfo::MemberVector::const_iterator it_end = partyMembers.end();
  for (; it != it_end; ++it)
  {
    flashInterface->HandlePlaySameTeamDecision(*it, agreed);
  }
}

bool AdventureScreenLogic::CanDecideToPlaySameTeam(const NDb::AdvMapDescription* const advMapDescription, const NWorld::PFPlayer* const localPlayer) const
{
  bool isPartyLeader = true;
  bool isRandomTeam = true;

  if (const PartyInfo* const partyInfo = GetPlayerPartyInfo(localPlayer))
  {
    isPartyLeader = partyInfo->IsPartyLeader(localPlayer);
    isRandomTeam = (advMapDescription->teamSize > partyInfo->GetMemberCount());
  }

  return (isRandomTeam ? isPartyLeader : false);
}

unsigned AdventureScreenLogic::GetPlaySameTeamTimeLeft() const
{
  const timer::Time now = timer::Now();

  if (now < playSameTeamDecisionDeadline)
    return static_cast<unsigned>(ceilf(playSameTeamDecisionDeadline - now));

  return 0U;
}

void AdventureScreenLogic::CollectPartyInfos()
{
  typedef vector<NCore::PlayerStartInfo> PlayerStartInfoVector;

  partyInfos.clear();

  PlayerStartInfoVector::const_iterator it_player = playerStartInfos.begin();
  PlayerStartInfoVector::const_iterator it_player_end = playerStartInfos.end();
  for (; it_player != it_player_end; ++it_player)
  {
    PlayerStartInfoVector::const_reference player = *it_player;

    if (player.playerType != NCore::EPlayerType::Human)
      continue;

    const unsigned key = GetPartyKey(player);

    if (key == 0U)
      continue;

    PartyInfo& partyInfo = partyInfos[key];

    partyInfo.AddMember(player);
  }
}


const PartyInfo* AdventureScreenLogic::GetPlayerPartyInfo(const NWorld::PFPlayer* const player) const
{
  if (!player)
    return NULL;

  PartyInfoMap::const_iterator it = partyInfos.begin();
  PartyInfoMap::const_iterator it_end = partyInfos.end();
  for (; it != it_end; ++it)
  {
    const PartyInfo& partyInfo = it->second;

    if (partyInfo.IsPartyMember(player))
      return &partyInfo;
  }

  return NULL;
}

void AdventureScreenLogic::UpdateDayNightState(const class NWorld::DayNightController* const dayNightController)
{
  if (!dayNightController)
    return;

  flashInterface->DayNightUpdateState(dayNightController->IsNight(), dayNightController->GetCurrentStateFraction());
}

void AdventureScreenLogic::SetDayNightWidgetVisible(const bool value)
{
  flashInterface->DayNightHideUI(!value);
}

//////////////////////////////////////////////////////////////////////////

PartyInfo::PartyInfo(const PartyInfo& other)
  : members(other.members)
{

}

PartyInfo::PartyInfo()
  : members()
{

}

PartyInfo& PartyInfo::operator=(const PartyInfo& other)
{
  members = other.members;
  return *this;
}

bool PartyInfo::IsMemberImpl(const int id) const
{
  if (!IsValidMemberId(id))
    return false;

  return (members.find(id) != members.end());
}

bool PartyInfo::IsLeaderImpl(const int id) const
{
  if (!IsValidMemberId(id))
    return false;

  if (members.empty())
    return false;

  return (members.front() == id);
}

void PartyInfo::AddMemberImpl(const int id, const bool leader)
{
  if (!IsValidMemberId(id))
    return;

  if (IsMemberImpl(id))
    return;

  if (!leader || members.empty())
    members.push_back(id);
  else
    members.insert(members.begin(), id);
}

bool PartyInfo::IsValidMemberId(const int id)
{
  if (id < 0)
    return false;

  return true;
}

int PartyInfo::GetMemberId(const NWorld::PFPlayer* const player)
{
  if (!player)
    return -1;

  return player->GetPlayerID();
}

int PartyInfo::GetMemberId(const NCore::PlayerStartInfo& psi)
{
  return psi.playerID;
}

bool PartyInfo::IsPartyMember(const NWorld::PFPlayer* const player) const
{
  return IsMemberImpl(GetMemberId(player));
}

bool PartyInfo::IsPartyLeader(const NWorld::PFPlayer* const player) const
{
  return IsLeaderImpl(GetMemberId(player));
}

const PartyInfo::MemberVector& PartyInfo::GetMembers() const
{
  return members;
}

int PartyInfo::GetMemberCount() const
{
  return members.size();
}

void PartyInfo::AddMember(const NCore::PlayerStartInfo& psi)
{
  AddMemberImpl(GetMemberId(psi), psi.playerInfo.partyLeader);
}

//////////////////////////////////////////////////////////////////////////

} //namespace NGameX

bool AwardExperience ( const char *name, const vector<wstring> &params )
{
  NGameX::AdventureScreen * advScreen = NGameX::AdventureScreen::Instance();
  if (!advScreen)
    return false;
  
  NGameX::AdventureScreenLogic *logic = (NGameX::AdventureScreenLogic *)advScreen->GetLogic();
  int experience = 0;
	float raiting = 0;

	if (params.size()> 0)
	{
		experience = NGlobal::VariantValue( params[0] ).GetFloat();
	}

	if (params.size()> 1)
	{
		raiting = NGlobal::VariantValue( params[1] ).GetFloat();
	}
	
  logic->DebugAwardExperience(experience, raiting);

  return true;
}

#ifndef _SHIPPING
bool TalentsAward ( const char *name, const vector<wstring> &params )
{

  NGameX::AdventureScreen * advScreen = NGameX::AdventureScreen::Instance();
  if (!advScreen)
    return false;

  NGameX::AdventureScreenLogic *logic = (NGameX::AdventureScreenLogic *)advScreen->GetLogic();
  string talentID;
  
  vector<NGameX::AwardData> _awards;

  int count = params.size();
  int startFrom = 0;

  enum EMode {RND, INC, DIRECT} mode = DIRECT;

  
  if (count == 0)
    return false;

  if (NGlobal::VariantValue( params[0] ).GetString() == L"rnd")
  {
    if (count < 2)
      return false;

    mode = RND;
    count = NGlobal::VariantValue( params[1] ).GetInt64();
  } 
  else if (NGlobal::VariantValue( params[0] ).GetString() == L"inc")
  {
    if (count < 2)
      return false;

    mode = INC;
    count = NGlobal::VariantValue( params[1] ).GetInt64();

    if (count >= 3)
      startFrom = NGlobal::VariantValue( params[2] ).GetInt64();
  }
  
  for( int i=0; i < count; i++)
  {
    _awards.push_back(NGameX::AwardData());
    NGameX::AwardData & awardData = _awards.back();
    awardData.type = roll::EAwardType::Talent;
    awardData.count = 1;
    awardData.isOwnedByPlayer = true;
    awardData.isTasty = false;
    awardData.id = -1;
    awardData.giverUser  = 0;

    CPtr<NWorld::PFResourcesCollection> resCollection = advScreen->GetWorld()->GetResourcesCollection();

    if (mode == RND)
    {
      int maxTalents = IsValid(resCollection) ? resCollection->GetTalents().size() : 25;
      int rnd = NRandom::Random(1,maxTalents);
      char buff[8];
      sprintf_s( buff, "G%03d", rnd );
      if (IsValid(IsValid(resCollection) ? resCollection->FindTalentById(buff) : NULL))
        awardData.persistentId = buff;
      else 
      { 
        i--;
        _awards.pop_back();
      }
    }
    else if (mode == INC)
    {
      char buff[8];
      sprintf_s( buff, "G%03d", startFrom + i );
      if (IsValid(IsValid(resCollection) ? resCollection->FindTalentById(buff) : NULL))
        awardData.persistentId = buff;
      else 
        _awards.pop_back();
    }
    else
      awardData.persistentId = NStr::ToMBCS( NGlobal::VariantValue( params[i] ).GetString() );
  }

  _awards.push_back(NGameX::AwardData());
  NGameX::AwardData & awardDataExperience = _awards.back();
  awardDataExperience.type            = roll::EAwardType::Experience;
  awardDataExperience.count           = 10;
  awardDataExperience.isOwnedByPlayer = true;
  awardDataExperience.giverUser       = 0;

  _awards.push_back(NGameX::AwardData());
  NGameX::AwardData & awardDataPearl = _awards.back();
  awardDataPearl.type            = roll::EAwardType::Pearl;
  awardDataPearl.count           = 1;
  awardDataPearl.isOwnedByPlayer = true;
  awardDataPearl.giverUser       = 0;//advScreen->GetHero()->GetPlayer()->GetUserID();
  
  _awards.push_back(NGameX::AwardData());
  NGameX::AwardData & awardDataHeroRating = _awards.back();
  awardDataHeroRating.type            = roll::EAwardType::HeroRating;
  awardDataHeroRating.count           = 1;
  awardDataHeroRating.isOwnedByPlayer = true;
  awardDataHeroRating.giverUser       = 0;

  _awards.push_back(NGameX::AwardData());
   NGameX::AwardData & awardDataClanWarsClanRating = _awards.back();
  awardDataClanWarsClanRating.type            = roll::EAwardType::ClanWarsClanRating;
  awardDataClanWarsClanRating.count           = 30;
  awardDataClanWarsClanRating.isOwnedByPlayer = true;
  awardDataClanWarsClanRating.giverUser       = 0;

  _awards.push_back(NGameX::AwardData());
  NGameX::AwardData & awardDataClanWarsPlayerRating = _awards.back();
  awardDataClanWarsPlayerRating.type            = roll::EAwardType::ClanWarsPlayerRating;
  awardDataClanWarsPlayerRating.count           = 70;
  awardDataClanWarsPlayerRating.isOwnedByPlayer = true;
  awardDataClanWarsPlayerRating.giverUser       = 0;

  _awards.push_back(NGameX::AwardData());
  NGameX::AwardData & awardDataRedPearl = _awards.back();
  awardDataRedPearl.type            = roll::EAwardType::RedPearl;
  awardDataRedPearl.count           = 1;
  awardDataRedPearl.isOwnedByPlayer = true;
  awardDataRedPearl.giverUser       = 0;

  _awards.push_back(NGameX::AwardData());
  NGameX::AwardData & awardDataCustomCurrency = _awards.back();
  awardDataCustomCurrency.type            = roll::EAwardType::CustomCurrency;
  awardDataCustomCurrency.customCurrencyId= "test_ticket";
  awardDataCustomCurrency.count           = 1;
  awardDataCustomCurrency.isOwnedByPlayer = true;
  awardDataCustomCurrency.giverUser       = 0;

  logic->DebugAwardUser(_awards);

  return true;
}

bool ChoosePartyAgain(const char *name, const vector<wstring> &params)
{
  NGameX::AdventureScreen * advScreen = NGameX::AdventureScreen::Instance();
  if (!advScreen)
    return false;

  NWorld::PFWorld *world = advScreen->GetWorld();
  if ( !world )
    return false;
  
  NWorld::PFPlayer* player = world->GetPlayer( advScreen->GetLocalPlayerID() );
  if ( !player )
    return 0;
  
  uint mainPartId = player->GetHero()->GetPartyId();
 
  if (mainPartId == 0)
      return false; 
  
  nstl::vector<__int64> auids;
  for(int i = 0; i< world->GetPlayersCount(); ++i)
  {
    NWorld::PFPlayer* p = world->GetPlayer( i );
    if (p && player->GetUserID() != p->GetUserID() && player->GetTeamID()== p->GetTeamID()){
      if (p->GetHero()->GetPartyId() == mainPartId)
          auids.push_back(p->GetUserID());
    }
  }
  if (auids.empty())
    return false; 
  Strong<NGameX::ISocialConnection> socialServer  =advScreen->GetSocialConnection();

  return socialServer->ChoosePartyAgain(auids, advScreen->GetSessionId(), 1, true);
}
  
#endif

REGISTER_VAR( "common_graphics_quality", g_commonGraphicsQuality, STORAGE_USER );
REGISTER_DEV_CMD( debug_award_exp, AwardExperience );
REGISTER_DEV_CMD( debug_talents_award, TalentsAward );
REGISTER_DEV_CMD( debug_choose_party_again, ChoosePartyAgain);
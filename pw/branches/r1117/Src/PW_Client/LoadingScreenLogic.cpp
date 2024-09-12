#include "stdafx.h"
#include "LoadingScreenLogic.h"

#include "../System/RandomGen.h"
#include "../UI/ImageLabel.h"
#include "../UI/FlashContainer2.h"
#include "PF_GameLogic/DBSessionRoots.h"
#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/DBUnit.h"
#include "PF_GameLogic/DBAdvMap.h"
#include "PF_GameLogic/DBGameLogic.h"
#include "PF_GameLogic/DBHeroesList.h"
#include "PF_GameLogic/ChatController.h"
#include "PF_GameLogic/IgnoreListController.h"
#include "PF_GameLogic/AdventureTooltip.h"
#include "PF_GameLogic/FlashFSCommands.h"
#include "PF_GameLogic/HeroRankCalculator.h"
#include "PF_GameLogic/DBHeroRanks.h"

#include "LoadingStatusHandler.h"
#include "LoadingFlashInterface.h"
#include "LoadingHeroes.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "HybridServer/PeeredTypes.h"
#include "PF_GameLogic/HeroSpawn.h"
#include "PF_GameLogic/PFHero.h"
#include "PF_GameLogic/AdventureScreen.h"


namespace 
{
  static int GetHeroLevel( int exp, vector<int> levels )
  {
    for ( int level = 0; level < levels.size(); ++level )
    {
      if ( exp < levels[level] )
        return level;
    }

    return levels.size();
  }

  // copy-paste from AdventureScreen.cpp
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

}


namespace Game
{

BEGIN_LUA_TYPEINFO( LoadingScreenLogic, UI::ScreenLogicBase )
END_LUA_TYPEINFO( LoadingScreenLogic )



LoadingScreenLogic::LoadingScreenLogic( NGameX::LoadingStatusHandler * statusHandler, const NDb::DBUIData* _uiData, const bool _isSpectator, const bool _isTutorial ) 
: loadingStatusHandler(statusHandler)
, uiData(_uiData)
, isSpectator( _isSpectator )
, isTutorial( _isTutorial )
, leftTeamForce(0), rightTeamForce(0),
isShowTeamForce(true),partyFlag(true),tamburFlag(true) 
{

  levelToExp = NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->levelToExperienceTable; 
}


LoadingScreenLogic::~LoadingScreenLogic()
{
  flashWnd->RemoveFSListner(FlashFSCommands::ConvertToString(FlashFSCommands::ModeDescriptionTooltip));
  flashWnd->RemoveFSListner(FlashFSCommands::ConvertToString(FlashFSCommands::ExitLoadingScreen));
}


void LoadingScreenLogic::OnLoadedScreenLayout()
{
  m_heroDb = NDb::SessionRoot::GetRoot()->logicRoot->heroes;

  rankCalculator = new NGameX::HeroRankCalculator(NDb::SessionRoot::GetRoot()->logicRoot->aiLogic->heroRanks);

  SetProgress( 0 );

  flashWnd = UI::GetChildChecked<UI::FlashContainer2>( pBaseWindow, "FlashScreen", true );
  //flashWnd->Show(false);
  NI_ASSERT(IsValid(flashWnd), "doesnt have FlashScreen in children, will crush!");
  flashInterface = new LoadingFlashInterface( flashWnd, "LoaderWindowInterface" );

  preferencesProcessor = new UI::PreferencesProcessor( flashWnd, "PreferencesInterface" );
  preferencesProcessor->Init( *UI::GetUIRoot()->preferences );

  if ( isSpectator )
    flashInterface->SwitchToSpectatorMode();

  loadingHeroes = new LoadingHeroes(flashInterface, m_heroDb);

  UI::ScreenLogicBase::OnLoadedScreenLayout();

  if (uiData)
  {
    int size = uiData->forceColors.forceColors.size();

    vector<int> force(size);
    vector<uint> colors(size);

    for (int i = 0; i< size; i++)
    {
      force[i] = uiData->forceColors.forceColors[i].force;
      colors[i] = uiData->forceColors.forceColors[i].color.Dummy;
    }
    flashInterface->SetForceColorTable(force, colors);
    

    
    manoeuvresModeDesc = uiData->mapModeCustomDescriptions.maneuvers;
    guardModeDesc = uiData->mapModeCustomDescriptions.guardBattle;
		guildModeDesc = uiData->mapModeCustomDescriptions.guildBattle;
    customGameDescription = uiData->mapModeCustomDescriptions.customBattle;
  }

  UI::ImageLabel * tooltipWindow = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "General_tooltip", false);
  NI_ASSERT(IsValid(tooltipWindow), "doesnt have tooltip in LoadingScreen, will crush!");
  tooltip = new NGameX::AdventureTooltip(tooltipWindow);

  tooltip->Show(false);

  flashWnd->AddFSListner(FlashFSCommands::ConvertToString(FlashFSCommands::ModeDescriptionTooltip), this);
  flashWnd->AddFSListner(FlashFSCommands::ConvertToString(FlashFSCommands::ExitLoadingScreen), this);

  if (loadingStatusHandler){
    loadingStatusHandler->SetFlashInterface(flashInterface);
  
  }

  if (uiData->tips.size()>0)
  {
    wstring tip = uiData->tips[NRandom::Random(0, uiData->tips.size() - 1)].tipText.GetText();
    flashInterface->SetTip(tip);
  }
     
  
}
void LoadingScreenLogic::ShowTeamForce()
{
  std::wostringstream sLeftForce;
  std::wostringstream sRightForce;
  if (isShowTeamForce)
  {
    sLeftForce << (leftTeamForce * 10)/advMapDescription->teamSize;
    sRightForce << (rightTeamForce * 10)/advMapDescription->teamSize;
  }
  else
  {
    sLeftForce << "";
    sRightForce << "";
  }
  
  flashInterface->SetTeamForce(sLeftForce.str().c_str(), sRightForce.str().c_str());

}

void LoadingScreenLogic::SetChat( const Strong<NGameX::IPlayerIdMapper>& playerIdMapper, NGameX::ChatUiController * _chatController, NGameX::IgnoreListStorage* _ignoreListStorage, const bool muted, const bool leaver, const bool leaverParty)
{
  NI_VERIFY(IsValid(flashInterface), "Invalid Flash interface!\nShould be called after loading UI layout.", return);
  NI_VERIFY(IsValid(flashWnd), "Invalid Flash window!\nShould be called after loading UI layout.", return);

  NI_VERIFY(!!_chatController, "Invalid chat controller!", return);

  chatController = _chatController;
  chatController->AddChatUI(flashWnd, flashInterface, muted, leaver, leaverParty);

  if (_ignoreListStorage)
  {
    NGameX::IgnoreListController::CreateStruct ilc_cs;

    ilc_cs.flashContainer = flashWnd;
    ilc_cs.flashInterface = flashInterface;
    ilc_cs.playerIdMapper = playerIdMapper;
    ilc_cs.ignoreListStorage = _ignoreListStorage;
    ilc_cs.uiData = uiData;

    const Strong<NGameX::IgnoreListController> ilc(new NGameX::IgnoreListController(ilc_cs));

    chatController->SetIgnoreListController(ilc);
  }

  chatController->SetPlayerIdMapper(playerIdMapper);
}



void LoadingScreenLogic::SetTempMapBack( const char* back, const char* logo )
{
  if (flashInterface)
    flashInterface->SetMapBack(back, logo);
}

void LoadingScreenLogic::SetMap( const NDb::AdvMapDescription * _advMapDescription, const NDb::AdvMapSettings * _advMapSettings )
{
  if (!flashInterface)
    return;

  if (_advMapSettings)
  {
    loadingHeroes->SetShowAllHeroes(_advMapSettings->showAllHeroes);
  }

  advMapDescription = _advMapDescription;

  if (!advMapDescription)
    return;

  loadingHeroes->SetMapDescription( advMapDescription );

  const char * back =  advMapDescription->loadingBackgroundImages.back? advMapDescription->loadingBackgroundImages.back->textureFileName.c_str() : "";
  const char * logo =  advMapDescription->loadingBackgroundImages.logo? advMapDescription->loadingBackgroundImages.logo->textureFileName.c_str() : "";

  flashInterface->SetMapBack(back, logo);

  if (advMapDescription->modeVisualDescription)
    AddModeVisual(advMapDescription->modeVisualDescription);
}

void LoadingScreenLogic::Step( float deltaTime )
{
  UI::ScreenLogicBase::Step( deltaTime );

  if (chatController)
    chatController->Update();

  if (tooltip && tooltip->IsVisible())
    tooltip->SetLocation(lastMousePosition.x , lastMousePosition.y);
}

void LoadingScreenLogic::SetProgress( float pro )
{
  if (loadingHeroes)
    loadingHeroes->SetMyProgress(pro);
}

void LoadingScreenLogic::recalcTeamForce(const HeroInfo& heroInfo)
{
  if (!advMapDescription->matchmakingSettings)
    return; 
  rankMMCalculator = new NGameX::HeroRankCalculator(advMapDescription->matchmakingSettings);
  uint val = (uint)heroInfo.force;
  
  if (heroInfo.partyId)
  {
    std::map<int, uint>::const_iterator it = forces.find(heroInfo.partyId);
    if (forces.find(heroInfo.partyId) != forces.end())
      forces[heroInfo.partyId] = Max(val,(uint)heroInfo.force);
    else 
      forces[heroInfo.partyId] = val;
    
    val = forces[heroInfo.partyId];
    partyFlag = false;
  }
  if (heroInfo.team ==NCore::ETeam::Team1)
      leftTeamForce += val;
  else if (heroInfo.team ==NCore::ETeam::Team2)
      rightTeamForce += val;

  const NDb::EMapType mapType = advMapDescription->mapType;
  
  tamburFlag = tamburFlag && rankMMCalculator->GetMMRank(heroInfo.raiting).useForceMM;
 
  isShowTeamForce = isShowTeamForce && (!heroInfo.isNovice && tamburFlag && mapType == NDb::MAPTYPE_PVP && heroInfo.basket != NCore::EBasket::Newbie && partyFlag ) ; 
}

void LoadingScreenLogic::AddPlayer( int userId, const NCore::PlayerStartInfo& info, 
                                   const HeroInfo& heroInfo )
{
  if (heroInfo.isBot)
  {
    wstring botNickname;
    bool isMale = true;

    NDb::Ptr<NDb::Hero> hero = NWorld::FindHero( m_heroDb, NULL, heroInfo.heroId );
    if (!hero)
      return;

    isMale = hero->gender == NDb::GENDER_MALE;

    const NDb::HeroSkin* currentSkin = NWorld::PFBaseHero::GetHeroSkin(hero.GetPtr(), info.playerInfo.heroSkin);
    if (currentSkin)
      isMale = currentSkin->gender == NDb::GENDER_MALE;

    string flagIcon;
    wstring flagTooltip;


    if(ConvertToFaction(heroInfo.team)==NDb::FACTION_FREEZE)
    {
      flagIcon = uiData->botFlags.doctDefaultFlag.icon->textureFileName;
      flagTooltip = uiData->botFlags.doctDefaultFlag.tooltip.GetText();
    }
    else
    {
      flagIcon = uiData->botFlags.adornianDefaultFlag.icon->textureFileName;
      flagTooltip=uiData->botFlags.adornianDefaultFlag.tooltip.GetText();
    }


    loadingHeroes->AddUser(userId , botNickname, isMale, info.teamID, info.originalTeamID, heroInfo, flagIcon, flagTooltip);
    recalcTeamForce(heroInfo);
    loadingHeroes->AddBot(userId);
    flashInterface->SetHeroLevel(userId, 1);
  }
  else
  {
    bool isMale = true;

    // expo mode feature
    if ( NGlobal::GetVar( "zzsex_is_gender" ).GetInt64() )
    {
      NDb::Ptr<NDb::Hero> hero = NWorld::FindHero( m_heroDb, NULL, heroInfo.heroId );
      if (!hero)
        return;

      isMale = hero->gender == NDb::GENDER_MALE;
    }
    else
    {
      isMale = info.zzimaSex == lobby::ESex::Male;
    }

    string flagIcon;
    wstring flagTooltip;


    if(!info.playerInfo.flagId.empty())
    {
      bool founded = false;

      for (vector<NDb::CountryFlag>::const_iterator it = uiData->countryFlags.begin(); it != uiData->countryFlags.end(); ++it )
      {
        if (it->id == info.playerInfo.flagId )
        {
          flagIcon = it->icon->textureFileName;
          flagTooltip = it->tooltip.GetText();
          founded = true;
        }
      }
      if (!founded)
      {
        for (vector<NDb::Ptr<NDb::CustomFlag>>::const_iterator it = uiData->customFlags.begin(); it != uiData->customFlags.end(); ++it )
        {
          if ((*it)->id == info.playerInfo.flagId )
          {
            flagIcon = (*it)->icon->textureFileName;
            flagTooltip = (*it)->tooltip.GetText();
            founded = true;
          }
        }
      }
      if (!founded)
      {
        for (vector<NDb::Ptr<NDb::CustomFlag>>::const_iterator it = uiData->adminFlags.begin(); it != uiData->adminFlags.end(); ++it )
        {
          if ((*it)->id == info.playerInfo.flagId )
          {
            flagIcon = (*it)->icon->textureFileName;
            flagTooltip = (*it)->tooltip.GetText();
            founded = true;
          }
        }
      }
    }
    else if( uiData->countryFlags.size()>0)
    {
      flagIcon = uiData->countryFlags[0].icon->textureFileName;
      flagTooltip = uiData ->countryFlags[0].tooltip.GetText();
    }

    const bool useHeroName =
      (isTutorial && info.nickname.empty());

    const wstring& name = useHeroName ? GetHeroNameByPlayerInfo(info, advMapDescription) : info.nickname;
    loadingHeroes->AddUser(info.userID, name, isMale, info.teamID, info.originalTeamID, heroInfo, flagIcon, flagTooltip );
    recalcTeamForce(heroInfo);
  }
}

void LoadingScreenLogic::SetPlayerProgress( int userId, float pro )
{
  if ( userId < 0 )
    return;

  loadingHeroes->SetPlayerProgress(userId, pro);
}

void LoadingScreenLogic::SetOurUserId( int userId, NCore::ETeam::Enum team, NCore::ETeam::Enum original_team, bool isGuardGame,bool isGuildGame, bool isCustomGame )
{
  if (loadingHeroes)
    loadingHeroes->SetOurUserId(userId, team, original_team);

  //if (manoeuvresTeam != NCore::ETeam::None)
  //  AddModeVisual(manoeuvresModeDesc);

  if (isGuardGame)
    AddModeVisual(guardModeDesc);

	if (isGuildGame)
		AddModeVisual(guildModeDesc);

  if (isCustomGame)
    AddModeVisual(customGameDescription);
}

void LoadingScreenLogic::MsgChatOpenClose()
{
  if (!flashInterface)
    return;

  flashInterface->OpenCloseChat();
}

void LoadingScreenLogic::OpenChanel(int channelID)
{
	if(!flashInterface)
		return;

	flashInterface -> OpenChanel(channelID);
}

bool LoadingScreenLogic::CmdCancel()
{
  if (!flashInterface)
    return false;

  flashInterface->OnEscape();
  return true;
}

void LoadingScreenLogic::DisconnectUser( int userId )
{
  if (loadingHeroes)
    loadingHeroes->DisconnectUser(userId);
}

void LoadingScreenLogic::ReconnectUser( int userId )
{
  if (loadingHeroes)
    loadingHeroes->ReconnectUser(userId);
}

void LoadingScreenLogic::SetHeroInfo( int userId, const HeroInfo & heroInfo, const NCore::ClientSettings & _clientSettings )
{
  if (!levelToExp || !flashInterface)
    return;

  if ( _clientSettings.showHeroLevel )
    flashInterface->SetHeroLevel(userId, GetHeroLevel(heroInfo.exp, levelToExp->Levels));

  if ( _clientSettings.showHeroForce )
    flashInterface->SetHeroForce(userId, heroInfo.force);

	flashInterface->SetHeroPremium(userId, heroInfo.isPremium, ConvertToFaction( heroInfo.originalTeam));

  //если изменения рейтинга нету просто его не показываем
  if ( _clientSettings.showHeroRating )
  {

    const NDb::Rank & rank = rankCalculator->GetRank(heroInfo.raiting);
    
    NDb::EFaction faction = ConvertToFaction(heroInfo.team);
      //heroInfo.team == lobby::ETeam::Team1? NDb::FACTION_FREEZE: NDb::FACTION_BURN;

    flashInterface->SetHeroRaiting(userId, heroInfo.raiting, heroInfo.winDeltaRaiting, heroInfo.loseDeltaRaiting, heroInfo.isNovice,  rankCalculator->GetRankIcon(faction, rank), rankCalculator->GetRankName(faction, rank));
  }
}


void LoadingScreenLogic::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
{
  using namespace FlashFSCommands;

  switch (ConvertToFSCommand(listenerID))
  {
  case ModeDescriptionTooltip:
    {
      if (!IsValid(tooltip))
        return;

      int show, index;
      sscanf_s(args,"%d %d",&show, &index);

      if (!show)
      {
        tooltip->Show(false);
        return;
      }

      if (index<0 || index>= modeDescriptions.size())
        return;

      tooltip->SetText(modeDescriptions[index]->tooltip.GetText());
      tooltip->Show(true);
   
      break;
    }
  case ExitLoadingScreen:
    {
      QuitApplication();
      break;
    }
  }


}

void LoadingScreenLogic::AddModeVisual( const NDb::AdvMapModeDescription * modeDescription )
{
  if (!modeDescription)
    return;

  if (!modeDescription->icon)
    return;

  flashInterface->AddModeDescription(modeDescription->icon->textureFileName.c_str(), modeDescriptions.size() );
  modeDescriptions.push_back(modeDescription);
}



} //namespace Game

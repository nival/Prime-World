#include "stdafx.h"
#include "LoadingScreen.h"

#include "System/LoadingProgress.h"

#include "../PF_GameLogic/StringExecutor.h"
#include "../PF_GameLogic/DBAdvMap.h"
#include "../PF_GameLogic/DBServer.h"
#include "../PF_GameLogic/IgnoreListStorage.h"
#include "../PF_GameLogic/IgnoreListController.h"
#include "../PF_GameLogic/ChatController.h"
#include "LoadingStatusHandler.h"
#include "LoadingFlashInterface.h"

#include "PF_GameLogic/PlayerInfoHelper.hpp"

namespace Game
{


LoadingScreen::LoadingScreen( const char * _back, const char * _logo, const bool _isSpectator, const bool _isTutorial )
: logo (_logo)
, back (_back)
, isSpectator( _isSpectator )
, isTutorial( _isTutorial )
{
  uiData =  NDb::Get<NDb::DBUIData>(NDb::DBID("UI/Content/_.UIDT.xdb"));
  loadingStatusHandler = new NGameX::LoadingStatusHandler(uiData);
}

void LoadingScreen::Setup(LoadingGameContext * _loadingGameContext   )
{
  loadingGameContext = _loadingGameContext;

  if (loadingGameContext && logic)
    InitLoadingUI();
}

void LoadingScreen::InitLoadingUI()
{
  NI_VERIFY(logic, " Should be called after creating LoadingScreenLogic ", return );
  NI_VERIFY(loadingGameContext, " Should be called after setting LoadingGameContext ", return );

  eventsUI.AddActivationHandler( "cmd_cancel", &LoadingScreen::CmdCancel );
  eventsUI.AddActivationHandler( "chat_open_close", &LoadingScreen::MsgChatOpenClose );  
	eventsUI.AddActivationHandler("chat_open_global", &LoadingScreen::MsgChatOpenChannel, NDb::CHATCHANNEL_BOTHTEAMS); 
	eventsUI.AddActivationHandler("chat_open_team", &LoadingScreen::MsgChatOpenChannel, NDb::CHATCHANNEL_MYTEAM);	

  bool isGuardGame = loadingGameContext->params.hadPreGameLobby;
  //bool                      isGuildGame = (loadingGameContext->params.sessiontype == lobby::ETypeOfSession::SESSIONTYPE_GUILDBATTLE);
  
  const NCore::TPlayersStartInfo& playersInfo = loadingGameContext->mapStartInfo.playersInfo;

	NCore::ETeam::Enum myTeam = NCore::ETeam::None;

  bool isMuted = false;
  bool isLeaver = false;
  bool isLeaverParty = false;

  if (!isSpectator)
  {
    using namespace NGameX;

    const NCore::PlayerStartInfo* const psi = PlayerInfoHelper::FindPlayerInfoByUserId(playersInfo, loadingGameContext->userId);

    NI_ASSERT(!!psi, NStr::StrFmt("Player info not found! (userId=%d)", loadingGameContext->userId));

    if (psi)
    {
      logic->SetOurUserId(psi->userID, psi->teamID, psi->originalTeamID, isGuardGame, psi->playerInfo.guildData.guidWarEventPass, loadingGameContext->params.customGame);

      myTeam = psi->teamID;

      isMuted = psi->playerInfo.chatMuted;
      isLeaver = PlayerInfoHelper::IsLeaver(psi);
      isLeaverParty = isLeaver || PlayerInfoHelper::IsLeaverParty(playersInfo, psi);
    }
  }

  logic->SetMap(loadingGameContext->advMapDescription, loadingGameContext->advMapSettings);

	string myLocale;
	string enemyLocale;
  for ( int i = 0; i < playersInfo.size(); ++i )
  {
    const NCore::PlayerStartInfo& playerInfo = playersInfo[i];
    int heroId = playerInfo.userID < 0 ? -i - 1000 : playerInfo.userID;
    TLineUpHeroesInfo::iterator info = loadingGameContext->lineup_info.find(playerInfo.playerID);
    if (info == loadingGameContext->lineup_info.end())
      continue;
    
    logic->AddPlayer( heroId, playerInfo, info->second );
    if (!info->second.isBot)
      SetHeroInfo(heroId, info->second);
		if (info->second.team == myTeam)
		{
			myLocale = info->second.locale;
		}
		else
		{
			enemyLocale = info->second.locale;
		}
  }
  logic->ShowTeamForce();
  ignoreListStorage = loadingGameContext->ignoreListStorage;

  const Weak<NGameX::ChatUiController> chatController(loadingGameContext->chatController);

  if (IsValid(chatController))
  {
    logic->SetChat(NGameX::PlayerIdMapper::Create(playersInfo), chatController, ignoreListStorage, isMuted, isLeaver, isLeaverParty);

    chatController->LoadPlayerIcons(loadingGameContext->advMapDescription, playersInfo);
  }

	NDb::Locale myTeamLocale;
	NDb::Locale enemyTeamLocale;

	for (int i = 0; i < uiData->locales.size(); ++i )
	{
		if (uiData->locales[i].locale==myLocale)
		{
			myTeamLocale = uiData->locales[i];
		}	
		if (uiData->locales[i].locale==enemyLocale)
		{
			enemyTeamLocale = uiData->locales[i];
		}
	}

	const char * myTeamLocaleImage = myTeamLocale.localeImage ? myTeamLocale.localeImage->textureFileName.c_str():"";
	const char * enemyTeamLocaleImage = enemyTeamLocale.localeImage?enemyTeamLocale.localeImage->textureFileName.c_str():"";

	if (clientSettings.showLocale)
	{
		logic->GetLoadingFlashInterface()->SetLocales(myTeamLocaleImage, myTeamLocale.tooltip.GetText(),enemyTeamLocaleImage,enemyTeamLocale.tooltip.GetText());
	}

  logic->GetLoadingFlashInterface()->SetLoadingState(false);

  //забываем про него. уже все проинициализировали
  loadingGameContext = 0;
}



bool LoadingScreen::Init( UI::User * uiUser )
{
  logic = new LoadingScreenLogic( loadingStatusHandler, uiData, isSpectator, isTutorial );
  SetLogic( logic );
  logic->SetUser( uiUser );
  logic->LoadScreenLayout( "Loading" );
  logic->SetTempMapBack(back.c_str(), logo.c_str());

  logic->GetLoadingFlashInterface()->SetLoadingState(true);

  if (loadingGameContext)
    InitLoadingUI();

  return true;
}



void LoadingScreen::Step( bool bAppActive )
{
  DefaultScreenBase::Step( bAppActive ) ;

  if ( progress )
    logic->SetProgress( progress->GetTotalProgress() );
}

void LoadingScreen::MsgChatOpenClose()
{
  if (logic)
    logic->MsgChatOpenClose();
}

bool LoadingScreen::MsgChatOpenChannel(const NDb::EChatChannel & channelID )
{
	if(logic)
		logic->OpenChanel(channelID);

	return true;
}


bool LoadingScreen::CmdCancel()
{
  if (logic)
    return logic->CmdCancel();
  return false;
}

void LoadingScreen::OnClientStatusChange( int userId, int newStatus, int step )
{
  if (!logic)
    return;

  if (Peered::IsDisconnectedStatus(newStatus))
    logic->DisconnectUser(userId);

  if (Peered::IsConnectedStatus(newStatus))
    logic->ReconnectUser(userId);
}

void LoadingScreen::ApplyClientSettings(const NCore::ClientSettings & _clientSettings)
{
  clientSettings = _clientSettings;
}

void LoadingScreen::SetHeroInfo( int userId, HeroInfo & heroInfo )
{

  heroesInfo[userId] = heroInfo;

  if (!logic)
    return;

  logic->SetHeroInfo( userId, heroesInfo[userId], clientSettings );
  heroesInfo[userId].isProcessed = true;
}

} //namespace Game

NI_DEFINE_REFCOUNT( Game::LoadingGameContext);
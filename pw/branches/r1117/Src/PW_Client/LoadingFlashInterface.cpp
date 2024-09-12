#include "StdAfx.h"
#include "LoadingFlashInterface.h"


#define FLASH_INTERFACE_ENTER_FUNCTION(_funcName) \
  CallMethod( _funcName

#define FLASH_INTERFACE_ENTER_FUNCTION_ISENEMY(_funcNameFriendly, _funcNameEnemy, isEnemy) \
  CallMethod( isEnemy ? _funcNameEnemy : _funcNameFriendly

#define PUSH_ARG(arg) \
  , arg

#define CALL_FUNCTION );


namespace Game
{

LoadingFlashInterface::LoadingFlashInterface( UI::FlashContainer2 * _flashWnd, const char* _className ):FlashInterface( _flashWnd, _className )
{

}


void LoadingFlashInterface::SetHeroIdentity( int heroID, NDb::EFaction faction, const wstring& heroName, const char * iconPath, int heroLevel, bool isMale, const char * classIcon, uint partyId, string & flagIcon, wstring & flagTooltip, bool isAnimatedAvatar, int leagueIndex)
{
	CallMethod( "SetHeroIdentity", heroID, (int)faction, heroName, iconPath, heroLevel, isMale,classIcon, (int)partyId, flagIcon, flagTooltip, isAnimatedAvatar, leagueIndex);
}

void LoadingFlashInterface::SetHeroLoadProgress( int heroId, float loadProgress, bool isLeftGame )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetHeroLoadProgress")
  PUSH_ARG(heroId)
  PUSH_ARG(loadProgress)
  PUSH_ARG(isLeftGame)
  CALL_FUNCTION;
}

void LoadingFlashInterface::SetOurHeroId( int heroID, NDb::EFaction faction )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetOurHeroId")
  PUSH_ARG(heroID)
  PUSH_ARG(faction)
  CALL_FUNCTION;
}

void LoadingFlashInterface::SetHeroLevel( int heroId, int level )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetHeroLevel")
  PUSH_ARG(heroId)
  PUSH_ARG(level)
  CALL_FUNCTION;
}

void LoadingFlashInterface::SetPlayersFaction( NDb::EFaction leftFaction, NDb::EFaction rightFaction )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetPlayersFaction")
  PUSH_ARG(leftFaction)
  PUSH_ARG(rightFaction)
  CALL_FUNCTION;
}

//IgnoreList
void LoadingFlashInterface::IgnoreUser( const int playerId )
{
  CallMethod("IgnoreUser", playerId);
}

void LoadingFlashInterface::RemoveIgnore( const int playerId )
{
  CallMethod("RemoveIgnore", playerId);
}

void LoadingFlashInterface::SetMapBack( const char* back, const char* logo )
{
  CallMethod( "SetMapBack", back, logo);
}

///////////////////////////////////////

void LoadingFlashInterface::SetForceColorTable( const vector<int> & forceTable,const vector<uint> & colorTable )
{
  CallMethod( "SetForceColors", forceTable, colorTable);
}

void LoadingFlashInterface::SetTeamForce(const wstring & forceLeft,const wstring & forceRight)
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetTeamForce")
    PUSH_ARG(forceLeft)
    PUSH_ARG(forceRight)
    CALL_FUNCTION;
    DevTrace( "SetTeamForce '%s', converted to '%s'", forceLeft.c_str(), forceRight.c_str() );
}

void LoadingFlashInterface::SetHeroForce( int heroId, int force )
{
  CallMethod( "SetHeroForce", heroId, force);
}

void LoadingFlashInterface::SetHeroRaiting( int heroId, int raiting, float deltaWin, float deltaLose, bool isNovice, const char* rankIcon, const wstring & rankName )
{
  CallMethod( "SetHeroRaiting", heroId, raiting, deltaWin, deltaLose, isNovice, rankIcon, rankName);
}


void LoadingFlashInterface::SetHeroPremium( int heroId, bool hasPremium, NDb::EFaction originalFraction )
{
	CallMethod( "SetHeroPremium", heroId, hasPremium, originalFraction);
}


void LoadingFlashInterface::AddModeDescription( const char * modeImage, int id )
{
  CallMethod( "AddModeDescription", modeImage, id);
}


void LoadingFlashInterface::SetLoadingStatusText( const wstring & statusText )
{
  CallMethod( "SetLoadingStatusText", statusText);
}


void Game::LoadingFlashInterface::SetLocales( const char* imageLeft,const wstring & toolTipLeft, const char* imageRight, const wstring & toolTipRight )
{
	
	CallMethod( "SetLocales", imageLeft,toolTipLeft,imageRight,toolTipRight);	
}



void LoadingFlashInterface::SetLoadingState( bool isPreloading )
{
  CallMethod( "SetLoadingState", isPreloading);
}

void Game::LoadingFlashInterface::SetTip( const wstring & tip )
{
  CallMethod( "SetTip", tip);
}


void Game::LoadingFlashInterface::SwitchToSpectatorMode()
{
  CallMethod( "SwitchToSpectatorMode");
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//chat
void LoadingFlashInterface::AddChannel( NDb::EChatChannel channel, const wstring & channelName, uint channelColor, bool showChannelName, bool showPlayerName, bool canWrite2Channel )
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddChannel")
  PUSH_ARG(channel)
  PUSH_ARG(channelName)
  PUSH_ARG(channelColor)
  PUSH_ARG(showChannelName)
  PUSH_ARG(showPlayerName)
  PUSH_ARG(canWrite2Channel)
  CALL_FUNCTION;
}


void LoadingFlashInterface::AddChannelShortCut( NDb::EChatChannel channel, const wstring & shortcut )
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddChannelShortCut")
  PUSH_ARG(channel)
  PUSH_ARG(shortcut)
  CALL_FUNCTION;
}

void LoadingFlashInterface::AddMessage( NDb::EChatChannel channel, const wstring & playerName, const wstring & message )
{
  CallMethod("AddMessage", channel, playerName, message);
}


void LoadingFlashInterface::AddMessage(NDb::EChatChannel channel, const wstring & playerName, const wstring & message, const int playerId)
{
  CallMethod("AddMessageEx", channel, playerName, message, playerId);
}


void LoadingFlashInterface::SetDefaultChannel( NDb::EChatChannel channelID )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetDefaultChannel")
  PUSH_ARG(channelID)
  CALL_FUNCTION;
}

void LoadingFlashInterface::SetChatVisible( bool visible )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetChatVisible")
  PUSH_ARG(visible)
  CALL_FUNCTION;
}

void LoadingFlashInterface::SetChatOff( bool isChatOff )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetChatOff")
  PUSH_ARG(isChatOff)
  CALL_FUNCTION;
}

void LoadingFlashInterface::SetPlayerIcon(const int playerId, const string& path)
{
  CallMethod("SetPlayerIcon", playerId, path);
}

void LoadingFlashInterface::SetPlayerHeroId(const int playerId, const int heroId, const int teamId)
{
  CallMethod("SetPlayerHeroId", playerId, heroId, teamId);
}

void LoadingFlashInterface::OpenCloseChat()
{
  FLASH_INTERFACE_ENTER_FUNCTION("EnterPressed")
  CALL_FUNCTION;
}

void LoadingFlashInterface::OpenChanel(int channelID)
{
	FLASH_INTERFACE_ENTER_FUNCTION("OpenChanel")
	PUSH_ARG(channelID)
	CALL_FUNCTION;
}

void LoadingFlashInterface::OnEscape()
{
  FLASH_INTERFACE_ENTER_FUNCTION("OnEscape")
  CALL_FUNCTION;
}





}


NI_DEFINE_REFCOUNT( Game::LoadingFlashInterface );


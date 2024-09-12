#include "StdAfx.h"
#include "LoadingHeroes.h"

#include "LoadingFlashInterface.h"
#include "PF_GameLogic/DBSessionRoots.h"
#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/DBUnit.h"
#include "PF_GameLogic/PFHero.h"
#include "PF_GameLogic/DBHeroesList.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "PF_GameLogic/HeroSpawn.h"
#include "LoadingScreenLogic.h"


namespace Game
{


NDb::EFaction ConvertToFaction(NCore::ETeam::Enum team)
{
	return team == NCore::ETeam::Team1? NDb::FACTION_FREEZE: NDb::FACTION_BURN;
}


LoadingHeroes::LoadingHeroes( LoadingFlashInterface * _flashInterface, NDb::Ptr<NDb::HeroesDB> _heroDb )
: flashInterface(_flashInterface)
, heroDb(_heroDb)
, ourUserId(0)
, showAllHeros(true)
{
  
}



void LoadingHeroes::AddUser( int userId, const wstring & playerName, 
                            bool isMale, NCore::ETeam::Enum team, NCore::ETeam::Enum manoeuvresTeam,
                            const HeroInfo& heroInfo, string & flagIcon, wstring & flagTooltip)
{
  if (loadingHeroes.find(userId) != loadingHeroes.end())
    return;

  char * iconPath = "";
	char * classIcon = "";

  // ѕытаемс€ ипользовать heroId из PlayerInfo. http://SITE
  
  //int newHeroId = heroInfo.heroId != 0 ? heroInfo.heroId : Crc32Checksum().AddString(heroId).Get();
  NDb::Ptr<NDb::Hero> hero = NWorld::FindHero( heroDb, advMapDescription,  heroInfo.heroId);
  DebugTrace(" AddUser: %d %s", heroInfo.heroId, hero.GetPtr() == 0 ? "not found" : hero->persistentId );

  if ( hero )
  {
    NCore::ETeam::Enum imageTeam = (manoeuvresTeam != NCore::ETeam::None) ? (manoeuvresTeam) : (team);
    NDb::EFaction faction = ConvertToFaction(imageTeam);

    const NDb::Texture* avatarImage = NWorld::PFBaseHero::GetUiAvatarImage( hero, faction, heroInfo.skinId );
    iconPath =  (avatarImage) ? avatarImage->textureFileName.c_str() : "";

    if ( imageTeam == NCore::ETeam::Team1 )
    {
      classIcon = hero->minimapIconA ? hero->minimapIconA->textureFileName.c_str(): "";
    }
    else if ( imageTeam == NCore::ETeam::Team2 )
    {
      classIcon = hero->minimapIconB ? hero->minimapIconB->textureFileName.c_str(): "";
    }
  }

  NDb::EFaction faction = ConvertToFaction(team);

  if( showAllHeros || userId == ourUserId )
  {
    LoadingHero * hero = new LoadingHero(flashInterface, userId, playerName, iconPath, faction, isMale, classIcon, heroInfo.partyId, flagIcon, flagTooltip, heroInfo.isAnimatedAvatar, heroInfo.leagueIndex);
    loadingHeroes[userId] = hero;
  }

}

void LoadingHeroes::SetPlayerProgress( int userId, float pro )
{
  if (loadingHeroes.find(userId) == loadingHeroes.end() && ourUserId!=userId)
    return;
  if( showAllHeros || userId == ourUserId )
    loadingHeroes[userId]->SetProgress( pro * 100 );
}

void LoadingHeroes::AddBot( int userId )
{
  bots.push_back(userId);
}

void LoadingHeroes::SetMyProgress( float progress )
{
  list<int>::iterator i;
  for (i=bots.begin(); i!=bots.end(); i++)
  {
    SetPlayerProgress(*i, progress);
  }

  if (loadingHeroes.find(ourUserId) == loadingHeroes.end() )
    return;

  loadingHeroes[ourUserId]->SetProgress( progress*100);
}

void LoadingHeroes::SetOurUserId( int userId, NCore::ETeam::Enum team, NCore::ETeam::Enum manoeuvreTeam)
{
  if (!flashInterface)
    return;

  ourUserId = userId;

  NDb::EFaction faction = ConvertToFaction(team);
  flashInterface->SetOurHeroId(userId, faction);
  flashInterface->SetPlayersFaction(NDb::FACTION_FREEZE, NDb::FACTION_BURN);
}


void LoadingHeroes::DisconnectUser( int userId )
{
  if (loadingHeroes.find(userId) == loadingHeroes.end())
    return;

  loadingHeroes[userId]->DisconnectUser();
}

void LoadingHeroes::ReconnectUser( int userId )
{
  if (loadingHeroes.find(userId) == loadingHeroes.end())
    return;

  loadingHeroes[userId]->ReconnectUser();
}
//////////////////////////////////////////////////////////////////////////


LoadingHero::LoadingHero( LoadingFlashInterface * _flashInterface, int _userId, const wstring & playerName, 
                         const char * heroIconPath, NDb::EFaction faction, bool isMale, const char * classIcon,uint partyId,
                         string & flagIcon, wstring & flagTooltip, bool isAnimatedAvatar, int leagueIndex)
: userId(_userId)
, flashInterface(_flashInterface)
, isLeftGame(false)
, cacheProgress(-1)
{
  if (!flashInterface)
    return;

  flashInterface->SetHeroIdentity(userId, faction, playerName , heroIconPath, 0, isMale, classIcon,partyId, flagIcon, flagTooltip, isAnimatedAvatar, leagueIndex);
  //SetProgress(0);
}

void LoadingHero::SetProgress( float progress )
{
  if (!flashInterface || isLeftGame)
    return;

  //DebugTrace( "LoadingHero::SetProgress for userId = %d, progress = %f", userId,  progress);
  if (cacheProgress!=progress)
    flashInterface->SetHeroLoadProgress(userId, progress, false);

  cacheProgress = progress;
}

void LoadingHero::DisconnectUser()
{
  if (!flashInterface || isLeftGame)
    return;

  isLeftGame = true;

  flashInterface->SetHeroLoadProgress(userId, 0, true);
}

void LoadingHero::ReconnectUser()
{
  if (!flashInterface)
    return;

  isLeftGame = false;

  flashInterface->SetHeroLoadProgress(userId, 0, false);
}
}

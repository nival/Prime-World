#pragma once

#include <Core/GameTypes.h>

namespace NWorld
{
  class PFWorld;
}

namespace NRandom
{
  class RandomGenerator;
}

namespace NScene
{
  _interface IScene;
}


class LoadingProgress;

namespace NWorld
{
  struct HeroSpawnInfo
  {
    int                         playerId;
    Placement                   placement;
    NDb::Ptr<NDb::HeroPlaceHolder> placeholder;
    NCore::PlayerInfo           playerInfo; 
    bool                        usePlayerInfoTalentSet; 

    HeroSpawnInfo() : playerId(-1), placeholder(NULL), usePlayerInfoTalentSet(false) {}
  };

  typedef vector<HeroSpawnInfo>  TTeamSpawnInfo;
  typedef vector<TTeamSpawnInfo> TSpawnInfo;

  bool SpawnHeroes( NWorld::PFWorld * pWorld, const NDb::AdvMapDescription* advMapDescription, const NCore::TPlayersStartInfo & players, const bool isTutorial, TSpawnInfo* pSpawnInfo, NScene::IScene * pScene, LoadingProgress * progress );
  const NDb::Hero * FindHero( const NDb::HeroesDB * db, const NDb::AdvMapDescription* advMapDesc, uint heroId );
  const wstring& FindHeroNickname( const NDb::AdvMapDescription* advMapDesc, const NDb::BaseHero * hero );
  string GetRandomHeroSkin( uint heroId, const NDb::AdvMapDescription* advMapDesc, NRandom::RandomGenerator& randGen, NCore::ETeam::Enum teamId );
}

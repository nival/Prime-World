#pragma once

#include "PFTower.h"
#include "System\StarForce\StarForce.h"

namespace NWorld
{

enum Const
{
  MAX_NUM_TOWERS = 20
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PerFactionStatistics
{
  PerFactionStatistics() :
    bWinner(false),
    towersCount(0),  
    numKills(0),
    numAssists(0),
    numBossKills(0),
	numBossKillsCat(0),
	numBossKillsDragon(0),
    score(0),
    sessionTime(0.f),
    bestKiller(0),
    bestAssistant(0)
    {

    }

  ZDATA
  bool bWinner;
  vector<int> destroyedTowersLevels;
  int towersCount;
  int numKills;
  int numAssists;
  int numBossKills;
  int numBossKillsCat;
  int numBossKillsDragon;
  int score;
  float sessionTime;
  int bestKiller;
  int bestAssistant;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&bWinner); f.Add(3,&destroyedTowersLevels); f.Add(4,&towersCount); f.Add(5,&numKills); f.Add(6,&numAssists); f.Add(7,&numBossKills); f.Add(8,&numBossKillsCat); f.Add(9,&numBossKillsDragon); f.Add(10,&score); f.Add(11,&sessionTime); f.Add(12,&bestKiller); f.Add(13,&bestAssistant); return 0; }

  void AddTower()
  {   
    ++towersCount;
  }

  void AddTowerDestroy( CPtr<PFTower> tower, NDb::Ptr<NDb::FactionScoringTable> const& scoring );
  void AddBossKill( NDb::Ptr<NDb::FactionScoringTable> const& scoring, bool bIsBossCat = false, bool bIsBossDragon = false );

  void SetWinner() { bWinner = true; }
  void SetBestKiller() { bestKiller = 1; }
  void SetBestAssistant() { bestAssistant = 1; }

  STARFORCE_EXPORT void  CalculateFinalScore(NDb::Ptr<NDb::FactionScoringTable> const& scoring);

  int   GetScore() const { return score; }
  int   GetTowersCount() const { return towersCount; }
  int   GetTowersLeftCount() const { return towersCount - destroyedTowersLevels.size(); }
};

}

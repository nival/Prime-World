#include "stdafx.h"
#include "PFFactionStatistics.h"
#include "PFStatisticsStuff.h"

#ifndef VISUAL_CUTTED
#include "AdventureScreen.h"
#endif

namespace NWorld
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PerFactionStatistics::AddTowerDestroy(CPtr<PFTower> tower, NDb::Ptr<NDb::FactionScoringTable> const& scoring)
{
  const int level = tower->GetStatValue( NDb::STAT_LEVEL );
  destroyedTowersLevels.push_back(level);

  score += scoring->towerDestroyedBase + level * scoring->towerDestroyedLevelMul;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PerFactionStatistics::AddBossKill(NDb::Ptr<NDb::FactionScoringTable> const& scoring, bool bIsBossCat, bool bIsBossDragon)
{
  ++numBossKills;

  if (bIsBossCat)
	  ++numBossKillsCat;
  if (bIsBossDragon)
	  ++numBossKillsDragon;

  if ( numBossKills * scoring->bossKill <= scoring->maxBossKillScore )
  {
    score += scoring->bossKill;
  } 
}

#pragma code_seg(push, "~")

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PerFactionStatistics::CalculateFinalScore(NDb::Ptr<NDb::FactionScoringTable> const& scoring)
{
  STARFORCE_STOPWATCH();

  score = 0;
  int tempscore = 0;

  // for towers destroyed
  for (int i = 0; i < destroyedTowersLevels.size(); ++i)
  {
    tempscore += scoring->towerDestroyedBase + destroyedTowersLevels[i] * scoring->towerDestroyedLevelMul;
  }
  DebugTrace( "   Destroyed Towers score: %d", tempscore );
  score += tempscore;

  tempscore = Min(numBossKills * scoring->bossKill, scoring->maxBossKillScore); // for boss kills
  DebugTrace( "   Boss Kill score: %d", tempscore );
  score += tempscore;

  if ( bWinner )
  {
    tempscore = scoring->win; // for victory
    DebugTrace( "   Victory score: %d", tempscore );
    score += tempscore;
  }
  else
  {
    tempscore = scoring->loose; // for loose (play)
    DebugTrace( "   Loose score: %d", tempscore );
    score += tempscore;
  }

  // for best kill (0 - none or equal)
  tempscore = scoring->topKills * bestKiller;
  DebugTrace( "   Top Killers team score: %d", tempscore );
  score += tempscore;

  // for best assist (0 - none or equal)
  tempscore = scoring->topAssists * bestAssistant;
  DebugTrace( "   Top Assisters team score: %d", tempscore );
  score += tempscore;
}

#pragma code_seg(pop)

} //namespace NWorld

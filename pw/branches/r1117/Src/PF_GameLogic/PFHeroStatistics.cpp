#include "stdafx.h"

#include "PFAchievement.h"
#include "PFHero.h"
#include "PFHeroStatistics.h"
#include "PFStatistics.h"
#include "PFStatisticsImpl.h"
#include "HeroTitleCalculator.h"
#include "AdventureScreen.h"

namespace
{
  const int _historyLengthInSeconds = 40;

  bool g_bestAwardOnly = true;

  struct Initer
  {
    Initer::Initer( CPtr<NWorld::PFBaseHero> hero, CPtr<NWorld::PFStatistics> stat ) { pHero = hero; pStat = stat; }
    void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->Init(pHero, pStat); }

    CPtr<NWorld::PFBaseHero> pHero;
    CPtr<NWorld::PFStatistics> pStat;
  };

  struct Resetter
  {
    Resetter() { }
    void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->OnOwnerDie(); }
  };
} // End of anonumous namespace

namespace NWorld
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroLocalStatistics::AddDamage(HeroOpponent opponent, unsigned int abilityId, HeroDamage damage, bool dealt)
{
  HeroDamageMap * targetHDM;

  if (dealt)
  {
    targetHDM = &damageDealt;
  }
  else
  {
    targetHDM = &damageReceived;
  }

  // Try to find existing record for that opponent type
  HeroDamageMap::iterator itHd = targetHDM->find(opponent);

  if (itHd != targetHDM->end())
  {
    // If we already have received any damage from that opponent type - try to find damage, dealt by same ability
    AbilityDamageMap::iterator itAd = (*itHd).second.find(abilityId);

    if (itAd != (*itHd).second.end())
    {
      // If we already have record of damage, dealt by same ability - add the new damage amounts to the existing
      (*itAd).second += damage;
    }
    else
    {
      // If such ability is being recorded for the firs time - add appropriate record
      itHd->second.insert(AbilityDamagePair(abilityId, damage));
    }
  }
  else
  {
    // If we didn't record any damage for that unit type - add a new record
    pair<HeroDamageMap::iterator, bool> ret;
    ret = targetHDM->insert(HeroDamagePair(opponent, AbilityDamageMap()));
    ret.first->second.insert(AbilityDamagePair(abilityId, damage));
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroLocalStatistics::LogDamage()
{
  _LogDamageInternal(damageDealt, true);
  _LogDamageInternal(damageReceived, false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroLocalStatistics::_LogDamageInternal(HeroDamageMap & sourceHDM, bool dealt)
{
  NGameX::AdventureScreen * adventureScreen = NGameX::AdventureScreen::Instance();
  if (!adventureScreen)
    return;

  HeroDamageMap::iterator itHdm = sourceHDM.begin();
  HeroDamageMap::iterator itHdmEnd = sourceHDM.end();

  for (; itHdm != itHdmEnd; ++itHdm)
  {
    AbilityDamageMap::iterator itAdm = (*itHdm).second.begin();
    AbilityDamageMap::iterator itAdmEnd = (*itHdm).second.end();

    for (; itAdm != itAdmEnd; ++itAdm)
    {
      // Log only if something was counted
      if ((*itAdm).second)
      {
        // Log the damage record         oponent         ability          damage    dealt/received
        adventureScreen->LogHeroDamage((*itHdm).first, (*itAdm).first, (*itAdm).second, dealt);
        (*itAdm).second.Clear();
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFHeroStatistics::PFHeroStatistics(PFBaseHero *_pHero , NDb::Ptr<NDb::ScoringTable> const &statisticData ) 
: PFWorldObjectBase( _pHero->GetWorld(), 0 )
, pHero(_pHero)
, scoring(statisticData->hero)
, history()
, numDeaths(0)
, numBossKillsAssist(0)
, numCatKillAssist(0)
, numDragonKillAssist(0)
, numKillsTotal(0)
, money(0.f)
, numCreepsKilled(0)
, score(0)
, lastSalvationTime(0.f)
, numNeutralCreepsKilled(0)
, moneyTSliceSalary(0.f)
, currentKillSpree(0)
, currentDeathSpree(0)
, flagsRaised(0)
, flagsDestroyed(0)
, healedAmount(0.0f)
, timeInDeath(0.0f)
, sexHelp(0)
, timeInIdle(0.0f)
, timesKiledByNeutrals(0)
, timesUsedPotions(0)
, timeAtHome(0.0f)
, teleportsByAbility(0)
, achievmentsEnabled(true)
, lastDealtDamageStep(-1)
, glyphsPickuped(0)
, achievScore(0)
, quartersDestroyed(0)
, specialPoints(0)
, afks(0)
, leaveStatus(0)
, distanceTraveled(0.f)
, lastMoveDelta(0.f, 0.f)
{
  heroKillTime.resize(10);
  StatisticsStuff::ClearArray_(heroKillTime.begin(), heroKillTime.size());

  heroAssistTime.resize(10);
  StatisticsStuff::ClearArray_(heroAssistTime.begin(), heroAssistTime.size());

  for ( vector<NDb::Ptr<NDb::AchievBase>>::const_iterator iAchiev = statisticData->achievementsList.begin(), iEnd = statisticData->achievementsList.end(); iAchiev != iEnd; ++iAchiev )
  {
    achievements.push_back( CObj<PFAchievBase>((*iAchiev)->Create(GetWorld())) );
  }

  // todo: init score with "hero of the day" bonus
  if (false)
  {
    score += scoring->heroOfTheDay;
  }

  // init stat data
  int data_size   = int(_historyLengthInSeconds / pWorld->GetStepLengthInSeconds()) + 1;
  history.create(data_size);
  int damage_size = int(10.0f / pWorld->GetStepLengthInSeconds()) * 2;
  damageHistory.create(damage_size);

  // init achiev
  Initer init(pHero, pHero->GetWorld()->GetStatistics());
  ForAllAchievements(init);

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFHeroStatistics::GetNumTowersKilled(NDb::ERoute route, bool countAssisted, bool countKilled) const
{                                
  int n = 0;
  if (countAssisted)
  {
      nstl::vector<NDb::ERoute>::const_iterator const end = towersAssisted.end();
      for(nstl::vector<NDb::ERoute>::const_iterator it = towersAssisted.begin(); it != end; ++it)
      {
        NDb::ERoute const r = *it;
        if (r == route)
        {
          ++n;
        }
      }
  }
  if (countKilled)
  {
      nstl::vector<NDb::ERoute>::const_iterator const end = towersKilled.end();
      for(nstl::vector<NDb::ERoute>::const_iterator it = towersKilled.begin(); it != end; ++it)
      {
        NDb::ERoute const r = *it;
        if (r == route)
        {
          ++n;
        }
      }
  }
  return n;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::AddFinalScore(PFStatistics &stat)
{
  DebugTrace( "Hero userid %d (playerid %d) has personal score: %d", pHero->GetPlayer()->GetUserID(), pHero->GetPlayerId(), score );
  score += stat.GetFactionStatistics(pHero->GetFaction()).GetScore();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::AddTitleScore( NGameX::HeroTitleCalculator const* heroTitleCalculator )
{
  int tempscore = heroTitleCalculator->GetHeroTitleScore( pHero );
  DebugTrace( "Hero userid %d (playerid %d) got title score: %d", pHero->GetPlayer()->GetUserID(), pHero->GetPlayerId(), tempscore );
  score += tempscore;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFHeroStatistics::GetTotalNumHeroKills() const
{
  int s = 0;
  for( map<int, int>::const_iterator it = numKilled.begin(), end = numKilled.end(); it != end; ++it)
  {
    s += it->second;
  }

  return s;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFHeroStatistics::GetTotalNumHeroAssists() const
{
  int s = 0;
  for( map<int, int>::const_iterator it = numAssisted.begin(), end = numAssisted.end(); it != end; ++it)
  {
    s += it->second;
  }

  return s;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFHeroStatistics::GetTotalNumHeroKillsInTime( float threshold ) const
{
  return StatisticsStuff::GetChainLength_( heroKillTime, threshold );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFHeroStatistics::GetTotalNumHeroAssistInTime( float threshold ) const
{
  return StatisticsStuff::GetChainLength_( heroAssistTime, threshold );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::ResetHeroKillTimes()
{
  StatisticsStuff::ClearArray_( heroKillTime.begin(), heroKillTime.size() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::ResetHeroAssistsTimes()
{
  StatisticsStuff::ClearArray_( heroAssistTime.begin(), heroAssistTime.size() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::SetNumTowersKilled(int num)
{
  for (int i = 0; i < num; i++)
    towersKilled.push_back(NDb::ROUTE_CENTER);

  if (num < 0)
  {
    num *= -1;
    if (num >= towersKilled.size())
      towersKilled.clear();
    else
      towersKilled.erase(towersKilled.begin(), towersKilled.begin() + num);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::AddTowerKill(NDb::ERoute route)
{
  ++numKillsTotal;

  towersKilled.push_back(route);

  if (IsValid(scoring))
  {
    score += scoring->towerKill;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::AddTowerAssist(NDb::ERoute route)
{
  towersAssisted.push_back(route);

  if (IsValid(scoring))
  {
    score += scoring->towerKill;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::AddHeroKill(int id)
{
  ++numKilled[id];

  if (const PFWorld * pWorld = GetWorld())
  {
    if (PFStatistics * pStatistics = pWorld->GetStatistics())
    {
      if (-1 == pStatistics->GetFirstMerciless() 
          && numKilled.size() == pWorld->GetPresentPlayersCount(pHero->GetOppositeFaction()))
      {
          pStatistics->SetFirstMerciless(pHero->GetPlayerId());
      }
    }
  }

  if ( IsValid(scoring) )
  {
    int killsAndAssists = numKilled[id] + numAssisted[id];

    if ( killsAndAssists * scoring->heroKill.score <= scoring->heroKill.maxScore )
    {
      score += scoring->heroKill.score;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::AddHeroAssist(int id)
{
  ++numAssisted[id];

  if ( IsValid(scoring) )
  {
    int killsAndAssists = numKilled[id] + numAssisted[id];

    if ( killsAndAssists * scoring->heroKill.score <= scoring->heroKill.maxScore )
    {
      score += scoring->heroKill.score;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::AddBossKillScore(bool bIsBossCat, bool bIsBossDragon)
{
  if (bIsBossCat || bIsBossDragon)
  {
	  ++numBossKillsAssist;

	  if (bIsBossCat) 
		  ++numCatKillAssist;
	  if (bIsBossDragon)
	    ++numDragonKillAssist;
  }

  if (IsValid(scoring))
  {
    if ( numBossKillsAssist * scoring->bossKill.score <= scoring->bossKill.maxScore )
    {
      score += scoring->bossKill.score;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::AddAchievementScore(int addScore)
{
  achievScore += addScore;
  score += addScore;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool PFHeroStatistics::AddHeartsFromMG( float hearts, float threshold )
//{
//  const float eps = 1e-4f;
//  if ( fabs( hearts ) < eps )
//    return false;
//
//  bool pre = heartsFromMG >= threshold - eps;
//  heartsFromMG += hearts;
//  bool post = heartsFromMG >= threshold - eps;
//
//  return post && !pre;
//}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFHeroStatistics::GetSilverMedalsCount( const NDb::DBID & game ) const
{
  TAllMinigamesLevelsStatus::iterator g = minigamesStatus.find( game );
  if ( g == minigamesStatus.end() )
    return 0;

  int count = 0;
  for ( TMinigameLevelsStatus::iterator lvl = g->second.begin(); lvl != g->second.end(); ++lvl )
    if ( lvl->second == EMinigameLevelStatus::Silver )
      ++count;

  return count;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFHeroStatistics::GetGoldMedalsCount( const NDb::DBID & game ) const
{
  TAllMinigamesLevelsStatus::iterator g = minigamesStatus.find( game );
  if ( g == minigamesStatus.end() )
    return 0;

  int count = 0;
  for ( TMinigameLevelsStatus::iterator lvl = g->second.begin(); lvl != g->second.end(); ++lvl )
    if ( lvl->second == EMinigameLevelStatus::Gold )
      ++count;

  return count;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFHeroStatistics::GetTotalMedalsCount( EMinigameLevelStatus::Enum medal ) const
{
  int count = 0;
  for( TAllMinigamesLevelsStatus::iterator g = minigamesStatus.begin(); g != minigamesStatus.end(); ++g )
    for ( TMinigameLevelsStatus::iterator lvl = g->second.begin(); lvl != g->second.end(); ++lvl )
      if ( lvl->second == medal )
        ++count;
  return count;
}

EMinigameLevelStatus::Enum PFHeroStatistics::GetMinigamesStatus(const NDb::DBID &game, int levelIndex)
{ 
  return minigamesStatus[game][levelIndex]; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::OnMinigameLevelEnd( const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum newStatus )
{
  EMinigameLevelStatus::Enum & status = minigamesStatus[game][levelIndex];

  if ( newStatus <= status )
    return;

  status = newStatus;

  if ( status == EMinigameLevelStatus::Gold )
  {
    int goldMedalsCount = 0;
    for ( TAllMinigamesLevelsStatus::const_iterator it = minigamesStatus.begin(); it != minigamesStatus.end(); ++it )
      goldMedalsCount += GetGoldMedalsCount( it->first );
    
    if ( goldMedalsCount * scoring->goldMedals.score <= scoring->goldMedals.maxScore )
      score += scoring->goldMedals.score;
  }
  else if ( status == EMinigameLevelStatus::Silver )
  {
    int silverMedalsCount = 0;
    for ( TAllMinigamesLevelsStatus::const_iterator it = minigamesStatus.begin(); it != minigamesStatus.end(); ++it )
      silverMedalsCount += GetSilverMedalsCount( it->first );
    
    if ( silverMedalsCount * scoring->silverMedals.score <= scoring->silverMedals.maxScore )
      score += scoring->silverMedals.score;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroStatistics::AddFlagRaised()
{
  ++flagsRaised;

  if ( flagsRaised % scoring->flagRaise.count == 0
    && flagsRaised / scoring->flagRaise.count * scoring->flagRaise.score <= scoring->flagRaise.maxScore )
  {
    score += scoring->flagRaise.score;
  }
}

void PFHeroStatistics::AddFlagDestroyed()
{
  ++flagsDestroyed;

  if ( flagsDestroyed % scoring->flagDrop.count == 0
    && flagsDestroyed / scoring->flagDrop.count * scoring->flagDrop.score <= scoring->flagDrop.maxScore )
  {
    score += scoring->flagDrop.score;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFHeroStatistics::OnStep( float dtInSeconds, float time  )
{
  for ( int i = 0; i < achievements.size(); i++ )
  {
    if ( IsValid(achievements[i]) )
      if ( achievements[i]->NeedToBeStepped() )
        achievements[i]->Step( dtInSeconds );
  }


  PFHeroHistoryData now;

  now.health = pHero->GetHealth();
  now.pos    = pHero->GetPosition();
  now.time   = time;

  RecryptImpl();

  history.push(now);

  UpdateDistanceTraveled(false);

  return true;
}

void PFHeroStatistics::OnDamage(CPtr<PFBaseUnit> const &pUnit, float damage)
{
  float time = pHero->GetWorld()->GetTimeElapsed();

  PFDamageHistoryData data(IsValid(pUnit->GetMasterUnit()) ? pUnit->GetMasterUnit() : pUnit, damage, time);

  damageHistory.push(data);
}

void PFHeroStatistics::NotifyTeleport()
{
  UpdateDistanceTraveled(true);

  // put notification into last 
  history.back().teleport = true;
}

// Очки которые "показываются по табу".
int PFHeroStatistics::GetGrandScore() const
{
  int grandScore = score;
  if ( IsValid(pHero) && !GetWorld()->GetAIWorld()->WasGameFinished() )
  {
    grandScore += GetWorld()->GetStatistics()->GetFactionStatistics(pHero->GetFaction()).GetScore();
  }
  return grandScore;
}

void PFHeroStatistics::UpdateDistanceTraveled(const bool teleport /*= false*/)
{
  if (history.size() < 2)
    return;

  // NOTE: implementation-specific. see OnStep, NotifyTeleport

  if (teleport)
  {
    /* placeholder */
  }
  else
  {
    const PFHeroHistoryData& last = history.back(1);
    const PFHeroHistoryData& now = history.back();

    const CVec2 pos0(last.pos.AsVec2D());
    const CVec2 pos1(now.pos.AsVec2D());

    lastMoveDelta.Sub(pos1, pos0);
  }

  const float distance = fabs(lastMoveDelta);

  if (teleport)
    distanceTraveled -= distance;
  else
    distanceTraveled += distance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WalkDistanceGetter::GetParam(NWorld::PFBaseHero& hero)
{
  return static_cast<int>(ceil(hero.GetHeroStatistics()->GetDistanceTraveled()));
}

} //namespace NWorld

REGISTER_SAVELOAD_CLASS_NM(PFHeroLocalStatistics, NWorld);
REGISTER_WORLD_OBJECT_NM(PFHeroStatistics, NWorld);

REGISTER_DEV_VAR( "score_stat_bestAwardOnly", g_bestAwardOnly, STORAGE_NONE );

#include "stdafx.h"
#include "HeroScoreWrapper.h"

#include "PFHero.h"
#include "PFHeroStatistics.h"
#include "PFAchievement.h"
#include "PFApplInstant.h"
#include "PFTriggerApplicator.h"


namespace
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct AchievmentsCounter
{
  AchievmentsCounter(): total(0) {}
  void operator()(const NWorld::PFAchievBase* p)
  { 
    if (IsValid(p) && p->count != 0)
    {
      ++total;
    }
  }

  unsigned total;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TowerDeniesCounter
{
  TowerDeniesCounter(): total(0) {}
  void operator()(const NWorld::PFAchievBase* p)
  { 
    if (IsValid(p) && p->count != 0 && p->GetDBBase()->achievType == NDb::ACHIEVEMENTTYPE_TOWERDENY)
    {
      total=p->count;
    }
  }

  unsigned total;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DamageCalculator
{
  DamageCalculator(): amount(0){}
  void operator()(const NWorld::PFBaseApplicator * pApp)
  {
    const NWorld::PFApplDamage * damageAppl = dynamic_cast<const NWorld::PFApplDamage *> (pApp);
    
    if (!damageAppl || !IsValidDamage(damageAppl))
      return;
      

    amount+=damageAppl->GetDamageDealed();
    
  }
  int amount;

protected:
  virtual bool IsValidDamage(const NWorld::PFApplDamage *appl) { return true;}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct EnergyDamageCalculator : DamageCalculator
{
  virtual bool IsValidDamage(const NWorld::PFApplDamage *appl) 
  { 
    return appl->GetDB().damageType == NDb::APPLICATORDAMAGETYPE_ENERGY;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MaterialDamageCalculator : DamageCalculator
{
  virtual bool IsValidDamage(const NWorld::PFApplDamage *appl) 
  { 
    return appl->GetDB().damageType == NDb::APPLICATORDAMAGETYPE_MATERIAL;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DamageDealedToHeroesCalculator : DamageCalculator
{
  virtual bool IsValidDamage(const NWorld::PFApplDamage *appl) 
  { 
    return dynamic_cast<const NWorld::PFBaseHero *> (appl->GetReceiver().GetPtr());
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DamageRecievedFromHeroesCalculator : DamageCalculator
{
  virtual bool IsValidDamage(const NWorld::PFApplDamage *appl) 
  { 
    return dynamic_cast<const NWorld::PFBaseHero *> (appl->GetAbilityOwner().GetPtr());
  }
};

} // namespace


namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroScoreWrapper::HeroScoreWrapper()
{
  InitScoreGetters();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroScoreWrapper::SetHero( const NWorld::PFBaseHero * _hero )
{
  hero = _hero;

  NI_VERIFY(IsValid(hero), "Invalid hero!", return);

  statistics = hero->GetHeroStatistics();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetHeroScore( NDb::EScoreType scoreType )
{
  if (!IsValid(hero) || !IsValid(statistics))
    return -1;

  if (scoreGetterers.find(scoreType) != scoreGetterers.end())
  {
    ScoreGetter method =  scoreGetterers[scoreType];
    return (this->*method)();
  }

  return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroScoreWrapper::InitScoreGetters()
{
  scoreGetterers[NDb::SCORETYPE_NEUTRALCREEPSCOUNT ] = &HeroScoreWrapper::GetCreepsNeutralKilled;
  scoreGetterers[NDb::SCORETYPE_HEROKILLCOUNT  ] = &HeroScoreWrapper::GetHeroKillCount;
  scoreGetterers[NDb::SCORETYPE_ASSISTCOUNT    ] = &HeroScoreWrapper::GetAssistCount;
  scoreGetterers[NDb::SCORETYPE_DEATHCOUNT     ] = &HeroScoreWrapper::GetDeathCount;
  scoreGetterers[NDb::SCORETYPE_SCORE          ] = &HeroScoreWrapper::GetScore;
  scoreGetterers[NDb::SCORETYPE_TOTALNAFTA     ] = &HeroScoreWrapper::GetTotalNafta;
  scoreGetterers[NDb::SCORETYPE_ACHIEVMENTCOUNT] = &HeroScoreWrapper::GetAchievmentCount;
  scoreGetterers[NDb::SCORETYPE_TOWERSDESTROYED] = &HeroScoreWrapper::GetTowersDestroyed;
  scoreGetterers[NDb::SCORETYPE_CREEPSKILLED   ] = &HeroScoreWrapper::GetCreepsKilled;
  scoreGetterers[NDb::SCORETYPE_TOWERSDENIED   ] = &HeroScoreWrapper::GetTowersDenied;
  scoreGetterers[NDb::SCORETYPE_MINIGAMELEVELSWON ] = &HeroScoreWrapper::GetMinigameLevelsWon;
  scoreGetterers[NDb::SCORETYPE_DAMAGEDEALED          ] = &HeroScoreWrapper::GetDamageDealed;
  scoreGetterers[NDb::SCORETYPE_DAMAGERECIEVED        ] = &HeroScoreWrapper::GetDamageRecieved;
  scoreGetterers[NDb::SCORETYPE_DANAGEHERODEALED      ] = &HeroScoreWrapper::GetHeroDamageDealed;
  scoreGetterers[NDb::SCORETYPE_DANAGEHERORECIEVED    ] = &HeroScoreWrapper::GetHeroDamageRecieved;
  scoreGetterers[NDb::SCORETYPE_DAMAGERECIEVED        ] = &HeroScoreWrapper::GetDamageRecieved;
  scoreGetterers[NDb::SCORETYPE_METERIALDAMAGEDEALED  ] = &HeroScoreWrapper::GetMeterialDamageDealed;
  scoreGetterers[NDb::SCORETYPE_METERIALDAMAGERECIEVED] = &HeroScoreWrapper::GetMeterialDamageRecieved;
  scoreGetterers[NDb::SCORETYPE_ENERGYDAMAGEDEALED    ] = &HeroScoreWrapper::GetEnergyDamageDealed;
  scoreGetterers[NDb::SCORETYPE_ENERGYDAMAGERECIEVED  ] = &HeroScoreWrapper::GetEnergyDamageRecieved;
  scoreGetterers[NDb::SCORETYPE_FLAGSRAISED    ] = &HeroScoreWrapper::GetFlagsRaised;
  scoreGetterers[NDb::SCORETYPE_FLAGSDESTROYED ] = &HeroScoreWrapper::GetFlagsDestroyed;
  scoreGetterers[NDb::SCORETYPE_TIMEINDEATH    ] = &HeroScoreWrapper::GetTimeInDeath;
  scoreGetterers[NDb::SCORETYPE_HELEADAMOUNT   ] = &HeroScoreWrapper::GetHeleadAmount;
  //scoreGetterers[NDb::SCORETYPE_SEXHELP        ] = &HeroScoreWrapper::GetSexHelp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetHeroKillCount()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetTotalNumHeroKills();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetDeathCount()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetTotalNumHeroDeaths();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetAssistCount()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetTotalNumHeroAssists();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetScore()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetScore();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetTotalNafta()
{
  NI_VERIFY( IsValid(statistics), "Hero object wasn't set!", return 0; );
  return hero->GetTotalNaftaEarned();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetAchievmentCount()
{ 
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );

  AchievmentsCounter achievmentsCounter;

  statistics->ForAllAchievements(achievmentsCounter);

  return achievmentsCounter.total;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetTowersDestroyed()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetTotalNumTowersKilled();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetCreepsKilled()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetCreepsKilled();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetCreepsNeutralKilled()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetNeutralCreepsKilled();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetTowersDenied()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );

  TowerDeniesCounter towerDeniesCounter;

  statistics->ForAllAchievements(towerDeniesCounter);

  return towerDeniesCounter.total;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetMinigameLevelsWon()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );

  int levelsWon = 0;

  const NWorld::PFHeroStatistics::TAllMinigamesLevelsStatus & allGamesStatuses = statistics->GetMinigamesStatus();
  NWorld::PFHeroStatistics::TAllMinigamesLevelsStatus::const_iterator allGamesIter; 

  for (allGamesIter = allGamesStatuses.begin(); allGamesIter!=allGamesStatuses.end(); allGamesIter++)
  {
    const NWorld::PFHeroStatistics::TMinigameLevelsStatus & levelStatuses = (*allGamesIter).second;
    NWorld::PFHeroStatistics::TMinigameLevelsStatus::const_iterator levelIter;

    for (levelIter=levelStatuses.begin(); levelIter!=levelStatuses.end(); levelIter++)
    {
      EMinigameLevelStatus::Enum levelStatus = (*levelIter).second;
      if (levelStatus != EMinigameLevelStatus::Failed)
        levelsWon++;
    }
  }

  return levelsWon;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetDamageDealed()
{
  NI_VERIFY( IsValid(statistics), "Hero object wasn't set!", return 0; );
  NWorld::HeroDamage const& hd = statistics->GetDamageDealed();
  return Round( hd.magic + hd.material + hd.pure );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetDamageRecieved()
{
  NI_VERIFY( IsValid(statistics), "Hero object wasn't set!", return 0; );
  NWorld::HeroDamage const& hd = statistics->GetDamageReceived();
  return Round( hd.magic + hd.material + hd.pure );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetHeroDamageDealed()
{
  NI_VERIFY( IsValid(statistics), "Hero object wasn't set!", return 0; );
  NWorld::HeroDamage const& hd = statistics->GetDamageDealedToHeroes();
  return Round( hd.magic + hd.material + hd.pure );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetHeroDamageRecieved()
{
  NI_VERIFY( IsValid(statistics), "Hero object wasn't set!", return 0; );
  NWorld::HeroDamage const& hd = statistics->GetDamageReceivedFromHeroes();
  return Round( hd.magic + hd.material + hd.pure );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetMeterialDamageDealed()
{
  NI_VERIFY( IsValid(statistics), "Hero object wasn't set!", return 0; );
  return Round( statistics->GetDamageDealed().material );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetMeterialDamageRecieved()
{
  NI_VERIFY( IsValid(statistics), "Hero object wasn't set!", return 0; );
  return Round( statistics->GetDamageReceived().material );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetEnergyDamageDealed()
{
  NI_VERIFY( IsValid(statistics), "Hero object wasn't set!", return 0; );
  return Round( statistics->GetDamageDealed().magic );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetEnergyDamageRecieved()
{
  NI_VERIFY( IsValid(statistics), "Hero object wasn't set!", return 0; );
  return Round( statistics->GetDamageReceived().magic );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetFlagsRaised()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetFlagsRaised();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetFlagsDestroyed()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetFlagsDestroyed();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetTimeInDeath()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return (int)statistics->GetTimeInDeath();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetHeleadAmount()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return (int)statistics->GetHealedAmount();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoreWrapper::GetSexHelp()
{
  NI_VERIFY( IsValid(statistics), "Hero's statistics object wasn't set!", return 0; );
  return statistics->GetSexHelp();
}




} // namespace NGameX

BASIC_REGISTER_CLASS(NGameX::HeroScoreWrapper);
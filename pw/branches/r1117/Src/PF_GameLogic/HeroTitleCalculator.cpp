#include "stdafx.h"
#include "HeroTitleCalculator.h"

#include "../System/RandomGen.h"

#include "PFWorld.h"
#include "PFStatistics.h"
#include "HeroScoreWrapper.h"
#include "PFAchievement.h"
#include "PFTalent.h"
#include "PFHeroStatistics.h"


namespace
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class ScoreGetter: public NWorld::IHeroParamGetter, public CObjectBase
{
  OBJECT_BASIC_METHODS(ScoreGetter);
  ScoreGetter() {};
public:

  ScoreGetter(NDb::EScoreType _scoreType, NGameX::HeroScoreWrapper *_scoreWrapper)
    : scoreType(_scoreType)
    , scoreWrapper(_scoreWrapper)
  {}
  
  virtual int GetParam(NWorld::PFBaseHero & hero)
  {
    scoreWrapper->SetHero(&hero);
    return scoreWrapper->GetHeroScore(scoreType);
  }

private:
  CPtr<NGameX::HeroScoreWrapper> scoreWrapper;
  NDb::EScoreType scoreType;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AchievementSpreeGetter: public NWorld::IHeroParamGetter, public CObjectBase
{
  OBJECT_BASIC_METHODS(AchievementSpreeGetter);
  AchievementSpreeGetter() {};
public:

  AchievementSpreeGetter(NDb::EAchievementType _achievementType)
    : achievementType(_achievementType)
  {}

  virtual int GetParam(NWorld::PFBaseHero & hero)
  {
    struct AchievementCounter
    {
      AchievementCounter(NDb::EAchievementType _achievementType)
        : maxSpree(0)
        , achievementType(_achievementType)
      {}
      void operator()(const NWorld::PFAchievBase* p)
      { 
        if (p->GetDBBase()->achievType != achievementType)
          return;

        const NWorld::PFAchievRuler * ruler = dynamic_cast<const NWorld::PFAchievRuler *> (p);

        if (IsValid(ruler) )
        {
          if ( ruler->count != 0 )
            maxSpree = ruler->maxSpree;
        }
        else
          maxSpree = p->count;
      }
      
      NDb::EAchievementType achievementType;
      unsigned maxSpree;
    } achievementCounter(achievementType);

    hero.GetHeroStatistics()->ForAllAchievements(achievementCounter);

    return achievementCounter.maxSpree;
  }

private:
  NDb::EAchievementType achievementType;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct UniqueBestScoreFinder
{
  UniqueBestScoreFinder & operator=( const UniqueBestScoreFinder & ) {}

  UniqueBestScoreFinder( NWorld::IHeroParamGetter * _paramGetter, bool _useBestResult = true ) 
    : score(_useBestResult? 0: INT_MAX)
    , unique(true)
    , paramGetter(_paramGetter)
    , useBestResult(_useBestResult)
  {}

  void operator()(NWorld::PFBaseHero & hero) 
  { 
    int heroParam = paramGetter->GetParam(hero);

    bool replaceScore = (useBestResult) ? (heroParam > score) : (heroParam < score);

    if (replaceScore)
    {
      score = heroParam;
      foundHero = &hero;
      unique = true;
    }
    else if (heroParam == score)
    {
        unique = false;
        foundHero = 0;
    }
  }

  int   score;
  bool  unique;
  CPtr<NWorld::PFBaseHero> foundHero;

private:

  CObj<NWorld::IHeroParamGetter> paramGetter;
  bool useBestResult;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TimesUsedPotionsGetter : public NWorld::IHeroParamGetter, public CObjectBase
{
  OBJECT_BASIC_METHODS(TimesUsedPotionsGetter);

public:

  virtual int GetParam(NWorld::PFBaseHero & hero)
  {
    return hero.GetHeroStatistics()->GetUsedPotions();
  }
};

} // namespace


namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroTitleCalculator::HeroTitleCalculator( NWorld::PFWorld* _world )
: world(_world)
{
   scoring = NDb::SessionRoot::GetRoot()->logicRoot->scoringTable; 
   heroScoreWrapper = new HeroScoreWrapper();
   InitTitleSuggesters();
   GiveTitlesToHeroes();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroTitleCalculator::HeroTitle::HeroTitle()
: titleType(NDb::HEROTITLE_NOVICE)
, priority(0)
{}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::EHeroTitle HeroTitleCalculator::GetHeroTitle( const NWorld::PFBaseHero * hero ) const
{
  if (!IsValid(hero))
    return NDb::HEROTITLE_NOVICE;

  int PlayerID = hero->GetPlayerId();

  HeroTitles::const_iterator it = heroTitles.find(PlayerID);
  if ( it == heroTitles.end() )
    return NDb::HEROTITLE_NOVICE;

  return it->second.titleType;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroTitleCalculator::GetHeroTitleScore( const NWorld::PFBaseHero * hero ) const
{
  // Float scores are needed only for precise priority. Statistics scoring gets integral number.
  return (int)GetTitlePriority( GetHeroTitle( hero ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroTitleCalculator::GiveTitlesToHeroes()
{
  if (!IsValid(world))
    return;

  // [AV]Crap for http://SITE
  // All "Crap!" to be removed after more titles would be implemented
  faction = NDb::FACTION_BURN;

  //TODO rewrite iteration
  for (int i = 0; i < NDb::KnownEnum<NDb::EHeroTitle>::sizeOf; ++i)
  {
    NDb::EHeroTitle titleType =  (NDb::EHeroTitle) i;

    if (titleSuggesters.find(titleType) != titleSuggesters.end())
    {
      TitleSuggester method =  titleSuggesters[titleType];
      const NWorld::PFBaseHero * heroToSuggest = (this->*method)();
      if (IsValid(heroToSuggest))
        GiveTitleToHero( heroToSuggest, titleType );
    }
  }

  // Crap!
  faction = NDb::FACTION_FREEZE;
  for (int i = 0; i < NDb::KnownEnum<NDb::EHeroTitle>::sizeOf; ++i)
  {
    NDb::EHeroTitle titleType =  (NDb::EHeroTitle) i;

    if (titleSuggesters.find(titleType) != titleSuggesters.end())
    {
      TitleSuggester method =  titleSuggesters[titleType];
      const NWorld::PFBaseHero * heroToSuggest = (this->*method)();
      if (IsValid(heroToSuggest))
        GiveTitleToHero( heroToSuggest, titleType );
    }
  }
  // End of Crap

  for ( HeroTitles::const_iterator it = heroTitles.begin(); it != heroTitles.end(); ++it )
  {
    DebugTrace( "Title %s awarded to playerId %d", NDb::EnumToString( it->second.titleType ), it->first );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroTitleCalculator::GiveTitleToHero( const NWorld::PFBaseHero * hero, NDb::EHeroTitle titleType )
{
  if (!IsValid(hero))
    return;

  int PlayerID = hero->GetPlayerId();

  HeroTitle & curTitle = heroTitles[PlayerID];
  
  float newTitlePriority = GetTitlePriority(titleType);

  bool replaceIfEquals = ( ( newTitlePriority == curTitle.priority ) && ( world->GetRndGen()->Roll( 50.0f ) ) );

  if (newTitlePriority > curTitle.priority || replaceIfEquals)
  {
    curTitle.titleType = titleType;
    curTitle.priority  = newTitlePriority;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float HeroTitleCalculator::GetTitlePriority( NDb::EHeroTitle titleType ) const
{
  if (!IsValid(scoring))
    return 0.0f;

  return scoring->heroTitles[titleType].score;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroTitleCalculator::InitTitleSuggesters()
{
  titleSuggesters[NDb::HEROTITLE_BESTKILLER       ] = &HeroTitleCalculator::ProcessBestKiller;
  titleSuggesters[NDb::HEROTITLE_BESTASSISTER     ] = &HeroTitleCalculator::ProcessBestAssister;
  titleSuggesters[NDb::HEROTITLE_TOPCREEPKILLS    ] = &HeroTitleCalculator::ProcessTopCreepsKill;
  titleSuggesters[NDb::HEROTITLE_TOPTOWERKILLS    ] = &HeroTitleCalculator::ProcessTopTowersKill;
  titleSuggesters[NDb::HEROTITLE_LEASTDEATHS      ] = &HeroTitleCalculator::ProcessLeastDeath;
  titleSuggesters[NDb::HEROTITLE_TOPNAFTA         ] = &HeroTitleCalculator::ProcessTopNafta;
  titleSuggesters[NDb::HEROTITLE_TOPNEUTRALKILLER ] = &HeroTitleCalculator::ProcessTopNeutralCreepsKill;
  titleSuggesters[NDb::HEROTITLE_TOPTOWERDENIER   ] = &HeroTitleCalculator::ProcessTopTowersDenier;

  titleSuggesters[NDb::HEROTITLE_TOPCEREMONIALKILLER] = &HeroTitleCalculator::ProcessTopCerimonialKill;
  titleSuggesters[NDb::HEROTITLE_TOPKILLSTREAKER    ] = &HeroTitleCalculator::ProcessTopKillStreak;
  titleSuggesters[NDb::HEROTITLE_SHINIGAMI          ] = &HeroTitleCalculator::ProcessTopMassKill;
  titleSuggesters[NDb::HEROTITLE_HUNTSMAN           ] = &HeroTitleCalculator::ProcessTopHuntsman;
  
  titleSuggesters[NDb::HEROTITLE_TOPONEHEROKILLER   ] = &HeroTitleCalculator::ProcessTopOneHeroKiller;
  titleSuggesters[NDb::HEROTITLE_ASCETIC            ] = &HeroTitleCalculator::ProcessAscetic;
  titleSuggesters[NDb::HEROTITLE_PAINTER_MG2        ] = &HeroTitleCalculator::ProcessPainterMG2;
  titleSuggesters[NDb::HEROTITLE_TELEPORTER         ] = &HeroTitleCalculator::ProcessTeleporter;
  titleSuggesters[NDb::HEROTITLE_WANDERER           ] = &HeroTitleCalculator::ProcessWanderer;
  titleSuggesters[NDb::HEROTITLE_AVENGER            ] = &HeroTitleCalculator::ProcessAvenger;
  
  titleSuggesters[NDb::HEROTITLE_DEDICATED_MG2        ] = &HeroTitleCalculator::ProcessDedicatedMG2;
  titleSuggesters[NDb::HEROTITLE_MERCILESS            ] = &HeroTitleCalculator::ProcessMerciless;
  titleSuggesters[NDb::HEROTITLE_STAY_AT_HOME         ] = &HeroTitleCalculator::ProcessStayAtHome;
  titleSuggesters[NDb::HEROTITLE_TOPCONSUMABLEUSER    ] = &HeroTitleCalculator::ProcessTopConsumableUser;
  titleSuggesters[NDb::HEROTITLE_LEASTCONSUMABLEUSER  ] = &HeroTitleCalculator::ProcessLeastConsumableUser;
  titleSuggesters[NDb::HEROTITLE_ADVENTURER           ] = &HeroTitleCalculator::ProcessAdventurer;
  titleSuggesters[NDb::HEROTITLE_LASTHITTOMAINBUILDING] = &HeroTitleCalculator::ProcessLastHitToMainBuilding;
  titleSuggesters[NDb::HEROTITLE_TOPIDLETIME          ] = &HeroTitleCalculator::ProcessTopIdleTime;
  titleSuggesters[NDb::HEROTITLE_DRAGONSLAYER         ] = &HeroTitleCalculator::ProcessDragonSlayer;
  titleSuggesters[NDb::HEROTITLE_LEGEND               ] = &HeroTitleCalculator::ProcessLegend;
  titleSuggesters[NDb::HEROTITLE_KAMIKAZE             ] = &HeroTitleCalculator::ProcessKamikaze;
  titleSuggesters[NDb::HEROTITLE_BOSSSLAYER           ] = &HeroTitleCalculator::ProcessBossSlayer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Crap!
NDb::EFaction HeroTitleCalculator::faction = NDb::FACTION_BURN;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * GetMinMaxParamHero(NWorld::PFStatistics *statistics, NWorld::IHeroParamGetter * paramGetter, bool max)
{
  UniqueBestScoreFinder bestScoreFinder(paramGetter, max);
  //statistics->ForAllHeroes(bestScoreFinder);
  // Crap
  statistics->GetWorld()->GetAIWorld()->ForAllHeroes(bestScoreFinder, HeroTitleCalculator::faction);
  //
  return bestScoreFinder.foundHero;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::GetMinMaxAchievementHero( NDb::EAchievementType achievType, bool max /*= true*/ )
{
  CObj<NWorld::IHeroParamGetter> achieveCountGetter =  new AchievementSpreeGetter(achievType);

  return GetMinMaxParamHero(world->GetStatistics(), achieveCountGetter, max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::GetMinMaxScoreHero( NDb::EScoreType _scoreType, bool max /*= true*/ )
{
  CObj<NWorld::IHeroParamGetter> scoreParamGetter =  new ScoreGetter(_scoreType, heroScoreWrapper);
  
  return GetMinMaxParamHero(world->GetStatistics(), scoreParamGetter, max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero *  HeroTitleCalculator::ProcessBestKiller()
{
  return GetMinMaxScoreHero(NDb::SCORETYPE_HEROKILLCOUNT);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessBestAssister()
{
  return GetMinMaxScoreHero(NDb::SCORETYPE_ASSISTCOUNT);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopCreepsKill()
{
  return GetMinMaxScoreHero(NDb::SCORETYPE_CREEPSKILLED);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopTowersKill()
{
  return GetMinMaxScoreHero(NDb::SCORETYPE_TOWERSDESTROYED);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessLeastDeath()
{
  return GetMinMaxScoreHero(NDb::SCORETYPE_DEATHCOUNT, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopNafta()
{
  return GetMinMaxScoreHero(NDb::SCORETYPE_TOTALNAFTA);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopNeutralCreepsKill()
{
  return GetMinMaxScoreHero(NDb::SCORETYPE_NEUTRALCREEPSCOUNT);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopTowersDenier()
{
  return GetMinMaxScoreHero(NDb::SCORETYPE_TOWERSDENIED);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopCerimonialKill()
{
  return GetMinMaxAchievementHero(NDb::ACHIEVEMENTTYPE_CEREMONIALKILL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopKillStreak()
{
  return GetMinMaxAchievementHero(NDb::ACHIEVEMENTTYPE_KILLINGSPREE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopHuntsman()
{
  return GetMinMaxAchievementHero(NDb::ACHIEVEMENTTYPE_MASTERCONTROL);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopOneHeroKiller()
{

  class OneHeroKillerGetter: public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(OneHeroKillerGetter);
  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      const nstl::map<int, int>& killMap = hero.GetHeroStatistics()->GetNumKilledMap();
      map<int, int>::const_iterator killMapIter;

      int killCount = 0;
      for (killMapIter = killMap.begin(); killMapIter!=killMap.end(); killMapIter++)
      {
        int newKillCount = killMapIter->second;
        killCount = max(killCount, newKillCount);
      }
   
      return killCount;
    }
    
  };

  CObj<NWorld::IHeroParamGetter> achieveCountGetter =  new OneHeroKillerGetter();

  return GetMinMaxParamHero(world->GetStatistics(), achieveCountGetter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessAscetic()
{
  class AsceticGetter: public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(AsceticGetter);
  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      struct BoughtTalentCount
      {
        BoughtTalentCount() : boughtCount(0) {}
        
        virtual void operator()(NWorld::PFTalent *pTalent, int level, int slot)
        {
          if (IsValid(pTalent)&&pTalent->IsActivated())  
            boughtCount++;
        }

        int boughtCount;

      } boughtTalentCounter;

      hero.ForAllTalents( boughtTalentCounter);

      return boughtTalentCounter.boughtCount;
    }

  };

  CObj<NWorld::IHeroParamGetter> asceticGetter =  new AsceticGetter();

  return GetMinMaxParamHero(world->GetStatistics(), asceticGetter, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessPainterMG2()
{
  class PainterGetter: public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(PainterGetter);
  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      int goldMedalsCount = 0;

      const NWorld::PFHeroStatistics::TAllMinigamesLevelsStatus & allGamesStatuses = hero.GetHeroStatistics()->GetMinigamesStatus();
      NWorld::PFHeroStatistics::TAllMinigamesLevelsStatus::const_iterator allGamesIter; 

      for (allGamesIter = allGamesStatuses.begin(); allGamesIter!=allGamesStatuses.end(); allGamesIter++)
      {
        const NWorld::PFHeroStatistics::TMinigameLevelsStatus & levelStatuses = (*allGamesIter).second;
        NWorld::PFHeroStatistics::TMinigameLevelsStatus::const_iterator levelIter;

        for (levelIter=levelStatuses.begin(); levelIter!=levelStatuses.end(); levelIter++)
        {
          EMinigameLevelStatus::Enum levelStatus = (*levelIter).second;
          if (levelStatus == EMinigameLevelStatus::Gold)
            goldMedalsCount++;
        }
      }

      return goldMedalsCount;
    }
   
  };

  CObj<NWorld::IHeroParamGetter> getter =  new PainterGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTeleporter()
{
  class TeleportCountGetter: public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(TeleportCountGetter);
  public:
    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      return hero.GetHeroStatistics()->GetTeleportsByAbility();
    }
  };

  CObj<NWorld::IHeroParamGetter> getter = new TeleportCountGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessWanderer()
{
  CObj<NWorld::IHeroParamGetter> getter =  new NWorld::WalkDistanceGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopMassKill()
{
  class MassKillGetter: public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(MassKillGetter);
  public:
    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      struct MassKillCounter
      {
        MassKillCounter()
          : maxSpree(0)
        {}

        void operator()(const NWorld::PFAchievBase* p)
        { 
          NDb::EAchievementType achievType = p->GetDBBase()->achievType;
          if ( achievType != NDb::ACHIEVEMENTTYPE_MASSKILL && achievType != NDb::ACHIEVEMENTTYPE_DOUBLEKILL )
            return;

          if ( p->count == 0 )
            return;

          if ( achievType == NDb::ACHIEVEMENTTYPE_DOUBLEKILL && maxSpree < 2 )
          {
            maxSpree = 2;
            return;
          }

          const NWorld::PFAchievMassKill * massKillAchiev = dynamic_cast<const NWorld::PFAchievMassKill *> (p);
          if ( IsValid(massKillAchiev) )
          {
            maxSpree = massKillAchiev->maxKillCount;
          }
        }

        int maxSpree;
      } massKillCounter;

      hero.GetHeroStatistics()->ForAllAchievements(massKillCounter);

      return massKillCounter.maxSpree;
    }
  };

  CObj<NWorld::IHeroParamGetter> getter =  new MassKillGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessAvenger()
{
  class AvengerGetter: public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(AvengerGetter);
  public:
    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      struct AvengerCounter
      {
        AvengerCounter() : count(0) {}

        void operator()(const NWorld::PFAchievBase* p)
        { 
          NDb::EAchievementType achievType = p->GetDBBase()->achievType;

          if (achievType != NDb::ACHIEVEMENTTYPE_AVENGE && achievType != NDb::ACHIEVEMENTTYPE_VENDETTA)
            return;

          if (IsValid(p) && p->count != 0 )
            count += p->count;
        }

        int count;
      } avengerCounter;

      hero.GetHeroStatistics()->ForAllAchievements(avengerCounter);

      return avengerCounter.count;
    }
  };

  CObj<NWorld::IHeroParamGetter> getter = new AvengerGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessDedicatedMG2()
{
  int firstMGAllLevelsWinner = world->GetStatistics()->GetFirstMGAllLevelsWinner();

  if ( firstMGAllLevelsWinner > -1 )
  {
    return NWorld::PFStatistics::GetHeroById( world->GetAIWorld(), firstMGAllLevelsWinner );
  }

  return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessMerciless()
{
  NWorld::PFBaseHero * pHero = NULL;

  int firstMerciless = world->GetStatistics()->GetFirstMerciless();

  if (firstMerciless > -1)
    if (NWorld::PFPlayer * pPlayer = world->GetPlayer(firstMerciless))
      pHero = pPlayer->GetHero();

  return pHero;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessStayAtHome()
{
  class StayAtHomeTimeGetter : public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(StayAtHomeTimeGetter);

  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      return (int)hero.GetHeroStatistics()->GetTimeAtHome();
    }
  };

  CObj<NWorld::IHeroParamGetter> getter = new StayAtHomeTimeGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopConsumableUser()
{
  CObj<NWorld::IHeroParamGetter> timesUsedPotionsGetter =  new TimesUsedPotionsGetter();

  return GetMinMaxParamHero(world->GetStatistics(), timesUsedPotionsGetter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessLeastConsumableUser()
{
  CObj<NWorld::IHeroParamGetter> timesUsedPotionsGetter =  new TimesUsedPotionsGetter();

  return GetMinMaxParamHero(world->GetStatistics(), timesUsedPotionsGetter, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessAdventurer()
{
  class TimesKilledByNeutralsGetter : public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(TimesKilledByNeutralsGetter);

  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      // Adventurer title is for males only
      if ( !hero.IsMale() )
      {
        return 0;
      }

      return hero.GetHeroStatistics()->GetKilledByNeutrals();
    }
  };

  CObj<NWorld::IHeroParamGetter> timesKilledByNeutralsGetter =  new TimesKilledByNeutralsGetter();

  return GetMinMaxParamHero(world->GetStatistics(), timesKilledByNeutralsGetter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessLastHitToMainBuilding()
{
  NWorld::PFBaseHero * pHero = NULL;

  int mainBuildingKiller = world->GetStatistics()->GetMainBuildingKiller();

  if (mainBuildingKiller > -1)
    if (NWorld::PFPlayer * pPlayer = world->GetPlayer(mainBuildingKiller))
      pHero = pPlayer->GetHero();

  return pHero;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessTopIdleTime()
{
  class TopIdleTimeGetter : public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(TopIdleTimeGetter);

  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      return (int)hero.GetHeroStatistics()->GetTimeInIdle();
    }
  };

  CObj<NWorld::IHeroParamGetter> getter = new TopIdleTimeGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessDragonSlayer()
{
  class DragonSlayerGetter : public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(DragonSlayerGetter);

  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      struct DragonSlayerTimeFinder
      {
        DragonSlayerTimeFinder()
          : time(INT_MAX) 
        {}

        void operator()(const NWorld::PFAchievBase* p)
        { 
          if (p->GetDBBase()->achievType != NDb::ACHIEVEMENTTYPE_DRAGONSLAYER)
            return;

          const NWorld::PFAchievDragonSlayer * achievDragonSlayer = dynamic_cast<const NWorld::PFAchievDragonSlayer *> (p);
          if (IsValid(achievDragonSlayer) && achievDragonSlayer->time > -1.0f)
          {
            time = (int)achievDragonSlayer->time;
          }
        }

        int time;

      } dragonSlayerTimeFinder;

      hero.GetHeroStatistics()->ForAllAchievements(dragonSlayerTimeFinder);

      return dragonSlayerTimeFinder.time;
    }
  };

  CObj<NWorld::IHeroParamGetter> getter =  new DragonSlayerGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessLegend()
{
  class LegendGetter : public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(LegendGetter);

  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      struct LegendTimeFinder
      {
        LegendTimeFinder()
          : time(INT_MAX) 
        {}

        void operator()(const NWorld::PFAchievBase* p)
        { 
          if (p->GetDBBase()->achievType != NDb::ACHIEVEMENTTYPE_LEGEND)
            return;

          const NWorld::PFAchievLegend * achievLegend = dynamic_cast<const NWorld::PFAchievLegend *> (p);
          if (IsValid(achievLegend) && achievLegend->time > -1.0f)
          {
            time = (int)achievLegend->time;
          }
        }

        int time;

      } legendTimeFinder;

      hero.GetHeroStatistics()->ForAllAchievements(legendTimeFinder);

      return legendTimeFinder.time;
    }
  };

  CObj<NWorld::IHeroParamGetter> getter =  new LegendGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessKamikaze()
{
  class KamikazeGetter : public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(KamikazeGetter);

  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      NWorld::PFHeroStatistics const * pHeroStatistics = hero.GetHeroStatistics();
      int kamikazeCount = 0;

      if (pHeroStatistics)
      {
        int killsAndAssists = pHeroStatistics->GetTotalNumHeroKills() 
                                + pHeroStatistics->GetTotalNumHeroAssists();
        if (killsAndAssists > 0)
        {
          kamikazeCount = pHeroStatistics->GetNumDeaths();
        }
      }

      return kamikazeCount;
    }
  };

  CObj<NWorld::IHeroParamGetter> kamikazeGetter =  new KamikazeGetter();

  return GetMinMaxParamHero(world->GetStatistics(), kamikazeGetter, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NWorld::PFBaseHero * HeroTitleCalculator::ProcessBossSlayer()
{
  class BossSlayerGetter : public NWorld::IHeroParamGetter, public CObjectBase
  {
    OBJECT_BASIC_METHODS(BossSlayerGetter);

  public:

    virtual int GetParam(NWorld::PFBaseHero & hero)
    {
      struct BSTimeFinder
      {
        BSTimeFinder()
          : time(INT_MAX) 
        {}

        void operator()(const NWorld::PFAchievBase* p)
        { 
          if (p->GetDBBase()->achievType != NDb::ACHIEVEMENTTYPE_BOSSSLAYER)
            return;

          const NWorld::PFAchievBossSlayer * achiev = dynamic_cast<const NWorld::PFAchievBossSlayer*> (p);
          if (IsValid(achiev) && achiev->time > -1.0f)
          {
            time = (int)achiev->time;
          }
        }

        int time;

      } bsTimeFinder;

      hero.GetHeroStatistics()->ForAllAchievements(bsTimeFinder);

      return bsTimeFinder.time;
    }
  };

  CObj<NWorld::IHeroParamGetter> getter =  new BossSlayerGetter();

  return GetMinMaxParamHero(world->GetStatistics(), getter, false);
}

} // namespace NGameX


BASIC_REGISTER_CLASS(NGameX::HeroTitleCalculator);
BASIC_REGISTER_CLASS(NWorld::IHeroParamGetter)
#pragma once


namespace NWorld
{
  class PFWorld;
  class PFBaseHero;
  class PFStatistics;
}


namespace NDb
{
  enum EHeroTitle;
  struct ScoringTable;
}


namespace NGameX
{
  class HeroScoreWrapper;
}


namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HeroTitleCalculator : public CObjectBase
{
  OBJECT_BASIC_METHODS(HeroTitleCalculator)

  HeroTitleCalculator(){}

public:
  HeroTitleCalculator( NWorld::PFWorld* _world );
  NDb::EHeroTitle GetHeroTitle(const NWorld::PFBaseHero * hero) const;
  int GetHeroTitleScore( const NWorld::PFBaseHero * hero ) const;

  // Crap!
  static NDb::EFaction faction;

private:
  void GiveTitlesToHeroes();
  void GiveTitleToHero(const NWorld::PFBaseHero * hero, NDb::EHeroTitle titleType );
  float GetTitlePriority(NDb::EHeroTitle titleType) const;
  void InitTitleSuggesters();

  struct HeroTitle 
  {
    HeroTitle();
    NDb::EHeroTitle titleType;
    float priority;
  };

  typedef const NWorld::PFBaseHero * (HeroTitleCalculator::*TitleSuggester)();
  typedef map<NDb::EHeroTitle, TitleSuggester> TitleSuggesters;

  TitleSuggesters titleSuggesters;

  NDb::Ptr<NDb::ScoringTable> scoring;

  typedef nstl::hash_map<int, HeroTitle> HeroTitles;
  HeroTitles heroTitles;
  
  CObj<HeroScoreWrapper>  heroScoreWrapper;

  CPtr<NWorld::PFWorld> world;

  //Titles suggesters

  const NWorld::PFBaseHero *  GetMinMaxScoreHero(NDb::EScoreType _scoreType, bool max = true);
  const NWorld::PFBaseHero *  GetMinMaxAchievementHero(NDb::EAchievementType achievType, bool max = true);
  
  const NWorld::PFBaseHero *  ProcessBestKiller();
  const NWorld::PFBaseHero *  ProcessBestAssister();
  const NWorld::PFBaseHero *  ProcessTopCreepsKill();
  const NWorld::PFBaseHero *  ProcessTopTowersKill();
  const NWorld::PFBaseHero *  ProcessTopTowersDenier();
  const NWorld::PFBaseHero *  ProcessLeastDeath();
  const NWorld::PFBaseHero *  ProcessTopNafta();
  const NWorld::PFBaseHero *  ProcessTopNeutralCreepsKill();
  
  const NWorld::PFBaseHero *  ProcessTopCerimonialKill();
  const NWorld::PFBaseHero *  ProcessTopKillStreak();
  const NWorld::PFBaseHero *  ProcessTopHuntsman();
    
  const NWorld::PFBaseHero *  ProcessTopOneHeroKiller();
  const NWorld::PFBaseHero *  ProcessAscetic();
  const NWorld::PFBaseHero *  ProcessPainterMG2();
  const NWorld::PFBaseHero *  ProcessTeleporter();
  const NWorld::PFBaseHero *  ProcessWanderer();
  const NWorld::PFBaseHero *  ProcessTopMassKill();
  const NWorld::PFBaseHero *  ProcessAvenger();

  const NWorld::PFBaseHero *  ProcessDedicatedMG2();
  const NWorld::PFBaseHero *  ProcessMerciless();
  const NWorld::PFBaseHero *  ProcessStayAtHome();
  const NWorld::PFBaseHero *  ProcessTopConsumableUser();
  const NWorld::PFBaseHero *  ProcessLeastConsumableUser();
  const NWorld::PFBaseHero *  ProcessAdventurer();
  const NWorld::PFBaseHero *  ProcessLastHitToMainBuilding();
  const NWorld::PFBaseHero *  ProcessTopIdleTime();
  const NWorld::PFBaseHero *  ProcessDragonSlayer();
  const NWorld::PFBaseHero *  ProcessLegend();
  const NWorld::PFBaseHero *  ProcessKamikaze();
  const NWorld::PFBaseHero *  ProcessBossSlayer();
};

} // namespace NGameX

#pragma once


namespace NWorld
{
  class PFBaseHero;
  class PFHeroStatistics;
}


namespace NDb
{
  enum EScoreType;
}


namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HeroScoreWrapper: public CObjectBase
{
  OBJECT_BASIC_METHODS(HeroScoreWrapper);

public:

  HeroScoreWrapper();

  void SetHero(const NWorld::PFBaseHero * _hero);

  int GetHeroScore(NDb::EScoreType scoreType);

private:

  void InitScoreGetters();

  typedef int (HeroScoreWrapper::*ScoreGetter)();
  typedef map<NDb::EScoreType, ScoreGetter> ScoreGetterers;

  ScoreGetterers scoreGetterers;
  
  ConstPtr<NWorld::PFBaseHero> hero;
  ConstPtr<NWorld::PFHeroStatistics> statistics;

  //score getters

  int GetHeroKillCount();
  int GetDeathCount();
  int GetAssistCount();
  int GetScore();
  int GetTotalNafta();
  int GetAchievmentCount();
  int GetTowersDestroyed();
  int GetCreepsKilled();
  int GetCreepsNeutralKilled();
  int GetTowersDenied();
  int GetMinigameLevelsWon();
  int GetDamageDealed();
  int GetHeroDamageDealed();
  int GetDamageRecieved();
  int GetHeroDamageRecieved();
  int GetMeterialDamageDealed();
  int GetMeterialDamageRecieved();
  int GetEnergyDamageDealed();
  int GetEnergyDamageRecieved();
  int GetFlagsRaised();
  int GetFlagsDestroyed();
  int GetTimeInDeath();
  int GetHeleadAmount();
  int GetSexHelp();
};

} // namespace NGameX 

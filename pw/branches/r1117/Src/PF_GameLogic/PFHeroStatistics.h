#ifndef PFHEROSTATISTICS_H_INCLUDED
#define PFHEROSTATISTICS_H_INCLUDED

#include "PFMinigameCommon.h"
#include "PFStatisticsStuff.h"
#include "System\StarForce\HiddenVars.h"

namespace NGameX
{
  class AdventureScreen;
  class HeroTitleCalculator;
}

namespace NWorld
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Holds hero's damage values (dealt or received) separated by damage type
struct HeroDamage
{
  HeroDamage()
    : material(0.0f)
    , magic(0.0f)
    , pure(0.0f)
  {}

  HeroDamage(float material, float magic, float pure)
    : material(material)
    , magic(magic)
    , pure(pure)
  {}

  HeroDamage & operator += (const HeroDamage &hd)
  {
    material += hd.material;
    magic += hd.magic;
    pure += hd.pure;

    return *this;
  }

  void Clear()
  {
    material = 0.0f;
    magic = 0.0f;
    pure = 0.0f;
  }

  float GetTotal() const
  {
    return material + magic + pure;
  }

  operator bool() const
  {
    return (material || magic || pure);
  }

ZDATA
  float material;
  float magic;
  float pure;
ZEND ZEND int operator&( IBinSaver &f ) { f.Add(2,&material); f.Add(3,&magic); f.Add(4,&pure); return 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Holds hero opponent ID (DB hash key) and type
struct HeroOpponent
{
  HeroOpponent()
    : opponentId(0)
    , opponentType(0)
  {}

  HeroOpponent(unsigned int opponentId, int opponentType)
    : opponentId(opponentId)
    , opponentType(opponentType)
  {}

  bool operator == (const HeroOpponent &ho) const
  {
    return (opponentId == ho.opponentId);
  }

  bool operator < (const HeroOpponent &ho) const
  {
    return (opponentId < ho.opponentId);
  }

  unsigned int opponentId;
  int          opponentType;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Holds hero's local statistic data, which is relevant only for specific client and reported only by that client
class PFHeroLocalStatistics : public CObjectBase
{
  OBJECT_METHODS(0x227C4440, PFHeroLocalStatistics);

private:

  typedef nstl::map<unsigned int, HeroDamage>        AbilityDamageMap;
  typedef nstl::pair<unsigned int, HeroDamage>       AbilityDamagePair;
  typedef nstl::map<HeroOpponent, AbilityDamageMap>  HeroDamageMap;
  typedef nstl::pair<HeroOpponent, AbilityDamageMap> HeroDamagePair;
  
  HeroDamageMap  damageDealt;     // Damage dealt by the local player's hero to any other unit
  HeroDamageMap  damageReceived;  // Damage received by the local player's hero from any other unit

public:

  void AddDamage(HeroOpponent opponent, unsigned int abilityId, HeroDamage damage, bool dealt);
  void LogDamage();

private:

  void _LogDamageInternal(HeroDamageMap & sourceHDM, bool dealt);
};

class PFBaseHero;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PFHeroHistoryData
{
  PFHeroHistoryData() : time(0.f), health(0.f), pos(VNULL3), teleport(false) {}
  ZDATA
  float time;
  Protection::HiddenVar<float, 25>::T health;
  Protection::HiddenVar<CVec3, 26>::T pos;
  bool teleport;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&time); f.Add(3,&health); f.Add(4,&pos); f.Add(5,&teleport); return 0; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PFDamageHistoryData
{
  PFDamageHistoryData() : appliedDamage(0.0f), time(0.0f) {}
  PFDamageHistoryData(CPtr<PFBaseUnit> const &_pHero, float _damage, float _time ) : pHero(_pHero), appliedDamage(_damage), time(_time) {}
  ZDATA
  CPtr<PFBaseUnit>     pHero;    
  float                appliedDamage;
  float                time;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&pHero); f.Add(3,&appliedDamage); f.Add(4,&time); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IHeroParamGetter: public IObjectBase
{
  virtual int GetParam(NWorld::PFBaseHero & hero) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFHeroStatistics : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS(0xB788C00, PFHeroStatistics);

  PFHeroStatistics(){}

  friend class PFStatistics;

public:
  typedef nstl::map<int, EMinigameLevelStatus::Enum> TMinigameLevelsStatus;
  typedef nstl::map<NDb::DBID, TMinigameLevelsStatus> TAllMinigamesLevelsStatus;

  // empty constructor so that nstl::map functions easily
  PFHeroStatistics(PFBaseHero *_pHero, NDb::Ptr<NDb::ScoringTable> const &statisticData);
	virtual bool NeedToBeStepped() { return false; }

private:
  ZDATA_(PFWorldObjectBase);
  CPtr<PFBaseHero> pHero;
	NDb::Ptr<NDb::HeroScoringTable> scoring;
  vector<CObj<PFAchievBase> > achievements;

  StatisticsStuff::circular_buffer<PFHeroHistoryData >  history;
  StatisticsStuff::circular_buffer<PFDamageHistoryData> damageHistory;

  int numDeaths;
  int numBossKillsAssist;
  int numCatKillAssist; // - засчитывает только убийства\ассисты босса кота Баюна
  int numDragonKillAssist; // - засчитывает только убийства\ассисты босса Горыныча
  int numKillsTotal;
  int numCreepsKilled;
  int numNeutralCreepsKilled;
  Protection::HiddenVar<float, 24>::T money;

  vector<NDb::ERoute> towersKilled;
  vector<NDb::ERoute> towersAssisted;

  vector<float> heroKillTime;
  vector<float> heroAssistTime;
  nstl::map<int, int> numKilledMe; // first = id of killer, second = how many times did he kill me.
  nstl::map<int, int> numKilled;   // first = id of victim, second = how many times I kill him
  nstl::map<int, int> numAssisted; // first = id of victim, second = how many times I assisted in killing him
  int score;

  vector<int> cannotDominate;
  float lastSalvationTime;
 
  TAllMinigamesLevelsStatus minigamesStatus;

  int currentKillSpree;
  int currentDeathSpree;

  int   flagsRaised;
  int   flagsDestroyed;

  int   afks;
  int   leaveStatus;

  float healedAmount;   // Total amount of health, which hero healed for himself during the session
  float timeInDeath;    // Total time in seconds, which hero spent being dead during the session
  int   sexHelp;        // Times hero used its gender ability during the session
  float timeInIdle;     // Total time in seconds, which hero spent being idle during the session
  int   timesKiledByNeutrals; // Times hero was killed by neutral creeps
  int   timesUsedPotions;     // Times hero used potion consumables
  float timeAtHome;     // Total time in seconds, which hero spent "at home" = near the fountain
  int   teleportsByAbility; // Teleports by abilities

  bool  achievmentsEnabled;
  int   lastDealtDamageStep;

  HeroDamage damageDealed;
  HeroDamage damageReceived;
  HeroDamage damageDealedToHeroes;
  HeroDamage damageReceivedFromHeroes;

  int glyphsPickuped;
  int achievScore;

  int quartersDestroyed;

  int specialPoints; // Для режима "Испытания". Если нужны дополнительные счётчики, то стоит заводить контейнер с соответствиями имя-счётчик.

  float distanceTraveled;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pHero); f.Add(3,&scoring); f.Add(4,&achievements); f.Add(5,&history); f.Add(6,&damageHistory); f.Add(7,&numDeaths); f.Add(8,&numBossKillsAssist); f.Add(9,&numCatKillAssist); f.Add(10,&numDragonKillAssist); f.Add(11,&numKillsTotal); f.Add(12,&numCreepsKilled); f.Add(13,&numNeutralCreepsKilled); f.Add(14,&money); f.Add(15,&towersKilled); f.Add(16,&towersAssisted); f.Add(17,&heroKillTime); f.Add(18,&heroAssistTime); f.Add(19,&numKilledMe); f.Add(20,&numKilled); f.Add(21,&numAssisted); f.Add(22,&score); f.Add(23,&cannotDominate); f.Add(24,&lastSalvationTime); f.Add(25,&minigamesStatus); f.Add(26,&currentKillSpree); f.Add(27,&currentDeathSpree); f.Add(28,&flagsRaised); f.Add(29,&flagsDestroyed); f.Add(30,&afks); f.Add(31,&leaveStatus); f.Add(32,&healedAmount); f.Add(33,&timeInDeath); f.Add(34,&sexHelp); f.Add(35,&timeInIdle); f.Add(36,&timesKiledByNeutrals); f.Add(37,&timesUsedPotions); f.Add(38,&timeAtHome); f.Add(39,&teleportsByAbility); f.Add(40,&achievmentsEnabled); f.Add(41,&lastDealtDamageStep); f.Add(42,&damageDealed); f.Add(43,&damageReceived); f.Add(44,&damageDealedToHeroes); f.Add(45,&damageReceivedFromHeroes); f.Add(46,&glyphsPickuped); f.Add(47,&achievScore); f.Add(48,&quartersDestroyed); f.Add(49,&specialPoints); f.Add(50,&distanceTraveled); return 0; }

private:
  void RecryptImpl()
  {
    Recrypt( money );
  }

  void UpdateDistanceTraveled(const bool teleport = false);

  // Not under ZDATA because time slice processing is not synchronous at all
  float moneyTSliceSalary;  // Gold earned as "salary" during the current time slice

  CVec2 lastMoveDelta;

public:
  bool OnStep ( float dtInSeconds, float time );
  void OnDamage( CPtr<PFBaseUnit> const &pUnit, float damage);
  void NotifyTeleport();
  CPtr<PFBaseHero> GetHero() const  { return pHero; }      
  int   GetNumDeaths() const        { return numDeaths; }
  int   GetNumBossKillsAssist() const     { return numBossKillsAssist; }
  int   GetNumCatKillAssist() const { return numCatKillAssist; }
  int   GetNumDragonKillAssist() const { return numDragonKillAssist; }
  int   GetNumKillsTotal() const    { return numKillsTotal; };
  int   GetCreepsKilled() const     { return numCreepsKilled; };
  int   GetNeutralCreepsKilled() const    { return numNeutralCreepsKilled; };
  float GetMoney() const            { return money; }
  float GetTSliceSalary() const     { return moneyTSliceSalary; }

  void SetTSliceSalary(float sallary) { moneyTSliceSalary = sallary; }
  void AddTSliceSalary(float sallary) { moneyTSliceSalary += sallary; }

  void SetNumKillsTotal(int numKills) { numKillsTotal = numKills; };
  void SetCreepsKilled (int numKills) { numCreepsKilled = numKills; };
  void SetNumTowersKilled(int num);

  void SetAchievmentsEnabled(bool _achievmentsEnabled) { achievmentsEnabled = _achievmentsEnabled; }
  bool GetAchievmentsEnabled() const { return achievmentsEnabled; }

  void SetLastDealtDamageStep(int _lastDealtDamageStep) { lastDealtDamageStep = _lastDealtDamageStep; }
  int  GetLastDealtDamageStep() const { return lastDealtDamageStep; }

  template <class F> void ForAllAchievements(F &f) const
  {
    if (achievmentsEnabled)
    {
      vector<CObj<PFAchievBase> >::const_iterator last = achievements.end();
      for (vector<CObj<PFAchievBase> >::const_iterator it = achievements.begin(); it != last; ++it)
        f((*it));
    }
  }

  const nstl::map<int, int>& GetNumKilledMeMap() const        { return numKilledMe; } // first = id of killer, second = how many times did he kill me.
  const nstl::map<int, int>& GetNumKilledMap() const          { return numKilled;}   // first = id of victim, second = how many times I kill him
  const nstl::map<int, int>& GetNumAssistedMap() const        { return numAssisted; }; // first = id of victim, second = how many times I assisted in killing him

  int GetNumTowersKilled(NDb::ERoute route, bool countAssisted = true, bool countKilled = true) const;
  
  int GetTotalNumTowersKilled() const { return towersKilled.size(); }
  int GetTotalNumTowersAssisted() const { return towersAssisted.size(); }

  int GetTotalNumQuartersDestroyed() const { return quartersDestroyed; }

  int GetTotalNumHeroKills() const;
  int GetTotalNumHeroAssists() const;

  int GetTotalNumHeroKillsInTime( float threshold ) const;
  int GetTotalNumHeroAssistInTime( float threshold ) const;

  void ResetHeroKillTimes();
  void ResetHeroAssistsTimes();

  int GetTotalNumHeroDeaths() const { return numDeaths; }

  int GetCurrentKillSpree() const { return currentKillSpree; }
  int GetCurrentDeathSpree() const { return currentDeathSpree; }

  void  SetSaviourTime (float time) { lastSalvationTime = time; }
  float GetSaviourTime () const     { return lastSalvationTime; }

  // notify about tower killed by me
  void AddTowerKill(NDb::ERoute route);
  // notify about tower killed by someone with my assistance
  void AddTowerAssist(NDb::ERoute route);
  // notify about hero killed by me
  void AddHeroKill(int id);
  // notify about hero killed by someone with my assistance
  void AddHeroAssist(int id);
  // notify about boss killed by me
  void AddBossKillScore(bool bIsBossCat = false, bool bIsBossDragon = false);
  void AddAchievementScore(int addScore);

  void AddFlagRaised();
  void AddFlagDestroyed();
  void AddHealedAmount(float amount) { healedAmount += amount; }
  void AddAfk()                      { afks++;                 }
  void SetLeaveStatus( int status )  { leaveStatus = status;   }
  void AddTimeInDeath(float time)    { timeInDeath += time;    }
  void AddSexHelp()                  { ++sexHelp;              }
  void AddTimeInIdle(float time)     { timeInIdle += time;     }
  void AddKilledByNeutral()          { ++timesKiledByNeutrals; }
  void AddUsedPotion()               { ++timesUsedPotions;     }
  void AddTimeAtHome(float time)     { timeAtHome += time;     }
  void AddTeleportsByAbility()       { ++teleportsByAbility;   }
  void AddGlyphPickuped()            { ++glyphsPickuped; }
  void AddQuartersDestroyed()        { ++quartersDestroyed; }

  void AddDamageReceivedFromHeroes( HeroDamage const& hd ) { damageReceivedFromHeroes += hd; }
  void AddDamageReceived( HeroDamage const& hd ) { damageReceived += hd; }
  void AddDamageDealedToHeroes( HeroDamage const& hd ) { damageDealedToHeroes += hd; }
  void AddDamageDealed( HeroDamage const& hd ) { damageDealed += hd; }

  int   GetFlagsRaised()      const { return flagsRaised;    }
  int   GetFlagsDestroyed()   const { return flagsDestroyed; }

  int   GetAfks()             const { return afks;           }
  int   GetLeaveStatus()      const { return leaveStatus;    }

  float GetHealedAmount()     const { return healedAmount;   }
  float GetTimeInDeath()      const { return timeInDeath;    }
  int   GetSexHelp()          const { return sexHelp;        }
  float GetTimeInIdle()       const { return timeInIdle;     }
  int   GetKilledByNeutrals() const { return timesKiledByNeutrals; }
  int   GetUsedPotions()      const { return timesUsedPotions;     }
  float GetTimeAtHome()       const { return timeAtHome;     }
  int   GetTeleportsByAbility() const { return teleportsByAbility; }
  int   GetGlyphsPickuped()   const { return glyphsPickuped; }
  int   GetAchievScore()      const { return achievScore; }

  const HeroDamage& GetDamageReceivedFromHeroes() const { return damageReceivedFromHeroes; }
  const HeroDamage& GetDamageReceived() const { return damageReceived; }
  const HeroDamage& GetDamageDealedToHeroes() const { return damageDealedToHeroes; }
  const HeroDamage& GetDamageDealed() const { return damageDealed; }

  int GetSilverMedalsCount( const NDb::DBID & game ) const;
  int GetGoldMedalsCount( const NDb::DBID & game ) const;
  int GetTotalMedalsCount( EMinigameLevelStatus::Enum medal ) const;

  const TAllMinigamesLevelsStatus & GetMinigamesStatus() const { return minigamesStatus; }
  EMinigameLevelStatus::Enum GetMinigamesStatus(const NDb::DBID &game, int levelIndex);

  void AddFinalScore(PFStatistics &stat);
  void AddTitleScore( NGameX::HeroTitleCalculator const* heroTitleCalculator );
  int GetScore() const {return score;}
  int GetGrandScore() const;

  void SetSpecialPoints( int _value ) { specialPoints = _value; }
  int  GetSpecialPoints() const { return specialPoints; }

  float GetDistanceTraveled() const { return distanceTraveled; }

  void OnMinigameLevelEnd( const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum newStatus );

  template< class F >
  void ForAllHistoryAfterTime( float time, F& f ) const
  {
    f.Init(history.back());

    for( int pos = 0, count = history.size(); pos < count; ++pos )
    {
      PFHeroHistoryData const& cur = history.back(pos);

      if( time > cur.time )
        break;

      f(cur);
    }
  }

  template< class F >
  void ForAllDamageHistoryAfterTime( float time, F& f ) const
  {
    for( int pos = 0, count = damageHistory.size(); pos < count; ++pos )
    {
      PFDamageHistoryData const& cur = damageHistory.back(pos);

      if( time > cur.time )
        break;

      f(cur);
    }
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WalkDistanceGetter: public IHeroParamGetter, public CObjectBase
{
  OBJECT_BASIC_METHODS(WalkDistanceGetter);
public:
  virtual int GetParam( NWorld::PFBaseHero& hero );
};

}

#endif //PFHEROSTATISTICS_H_INCLUDED

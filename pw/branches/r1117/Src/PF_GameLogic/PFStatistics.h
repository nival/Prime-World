#pragma once

#include "PFAIWorld.h"
#include "PFStatisticsStuff.h"
#include "PFFactionStatistics.h"
#include "PFHeroStatistics.h"
#include "PFUIEvent.h"
#include "PlayerData.h"
#include "PFStatisticsImpl.h"
#include "GameLogicStatisticsTypes.h"
#include "System/StarForce/StarForce.h"

namespace
{
class FirstEventChecker
{
  bool wasEvent;
  bool firstTime;
public:
  FirstEventChecker::FirstEventChecker () : wasEvent(0), firstTime(0) {}

  inline void Reset() { firstTime = false; }

  inline void Update()
  {
    firstTime = !wasEvent;
    wasEvent = true;
  }

  inline bool Get() { return firstTime; }
};

}

namespace NGameX
{
  class HeroTitleCalculator;
}

namespace NWorld
{

//=========================================================================================================================
// IgorKaa todo: remake this class (http://SITE)
class CustomEventNameMap : public NNameMap::Map
{
  NAMEMAP_DECLARE;

  ConstPtr<NWorld::PFBaseUnit>          m_pOwner;
  ConstPtr<NWorld::PFBaseUnit>          m_pVictim;
  vector<NWorld::PFBaseHero*>       m_eventAssistants;      
  wstring                           m_customParam;

  NGameX::PlayerData  ownerData;
  NGameX::PlayerData  victimData;

  wstring                           m_tmpString;
  wstring                           m_achievementCount;
  // Usual get it from m_pOwner. But we have the cases we should get it from different place.
  // For example when terrain is destroying the tower we are getting an enemy team name from the opposite faction.
  wstring                           m_enemyTeamName;  

public:
  CustomEventNameMap();

  void           Clear();                
  void           SetOwner (const NWorld::PFBaseUnit* owner);
  void           SetVictim(const NWorld::PFBaseUnit* victim);
  void           SetCustomParam( const wstring & str ) { m_customParam = str; }
  void           SetAssistants(const vector<NWorld::PFBaseHero*>& eventAssistants);
  const wstring& GetAssistanstsNames() const;
  const wstring& GetEventName() const;
  const wstring& GetAchievementCount() const;
  const wstring& GetEnemyTeamName() const;
  const wstring & GetCustomParameter() const { return m_customParam; }
  void           SetEnemyTeamName(const wstring& enemyTeamName);
  bool           IsVictimHero() const { return IsValid(m_pVictim) && m_pVictim->IsHero(); }
};

//////////////////////////////////////////////////////////////////////////

class PFStatistics : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS(0xCF6283C0, PFStatistics);

  PFStatistics() {};
public:
  PFStatistics(const CPtr<PFWorld> pWorld);
	virtual bool NeedToBeStepped() { return false; }

  // Purpose of this function is to guarantee presence of given hero
  // in perHeroStatistics map.
  // It is needed, in turn, to correctly enumerate all heroes by FillKillInstance_.

  STARFORCE_EXPORT void AddHeroDeath(CPtr<PFBaseHero> pVictim, CPtr<PFBaseUnit> pKiller);
  void AddKill(CPtr<PFBaseUnit> pVictim, CPtr<PFBaseHero> pKiller);
  void AddAssist(CPtr<PFBaseUnit> const& pVictim, CPtr<PFBaseUnit> const& pKiller, CPtr<PFBaseHero> const& pHeroAssistant);
  void AddMoney(CPtr<PFBaseHero> const& pHero, float money);    
 
  template <class F> void ForAllHeroes(F &f)
  {
    pWorld->GetAIWorld()->ForAllHeroes(f, NDb::FACTION_FREEZE);
    pWorld->GetAIWorld()->ForAllHeroes(f, NDb::FACTION_BURN);
  }
  void Dump();
  int GetNumKills(CPtr<PFBaseHero> pVictim, CPtr<PFBaseHero> pKiller, float minTime);
  float GetMoney(const PFBaseHero* const pHero) const;
  float GetTSliceSalary(const PFBaseHero* const pHero) const;
  void SetTSliceSalary(const PFBaseHero* const pHero, float salary);
  void AddTSliceSalary(const PFBaseHero* const pHero, float salary);
  //int GetNumAssists(CPtr<PFBaseHero> pVictim, CPtr<PFBaseHero> pAssistant, float minTime);
  float GetLastKillTime(CPtr<PFBaseHero> pVictim, CPtr<PFBaseHero> pKiller, bool ignoreLast);
  float GetLastAssistTime(CPtr<PFBaseHero> pVictim, CPtr<PFBaseHero> pKiller, bool ignoreLast);
  int GetDominate(CPtr<PFBaseHero> pHeroVictim, CPtr<PFBaseHero> pKiller, bool ignoreLast = false);
  void NoMoreDomination(CPtr<PFBaseHero> pPossibleKiller, CPtr<PFBaseHero> pPossibleVictim);
  bool CanDominate(CPtr<PFBaseHero> pPossibleKiller, CPtr<PFBaseHero> pPossibleVictim);
  void NoMoreFirstAssault();
  bool WasFirstAssault() const;
  
  int GetHeroAchievmentRank(CPtr<PFBaseHero> const& pHero, DWORD achievTypeId) const;

  //void AddTowerDestroyByTerrain(CPtr<PFTower> pTower);
  STARFORCE_EXPORT void AddTowerDestroy(CPtr<PFTower> tower, CPtr<PFBaseUnit> pKiller);  
  void AddQuartersDestroy( PFQuarters* pQuarters, CPtr<PFBaseUnit> pKiller );
  void AddTowerToFaction(NDb::EFaction faction){ perFactionStatistics[faction].AddTower(); }
  int GetTerrainOwnerID(PFTower const *tower) const;

  STARFORCE_EXPORT void AddFlagRaised(CPtr<PFBaseUnit> pRaiser);
  void AddFlagDestroyed(CPtr<PFBaseUnit> pDestroyer);
  void AddHealedAmount(CPtr<PFBaseHero> pHero, float amount);
  
  // for mini-games
  void MinigameComplete( const NDb::DBID &game, int player );
  void MinigameLevelEnded( const NDb::DBID &game, int player, int levelIndex, EMinigameLevelStatus::Enum status, bool lastLevel );

  void OnApplicatorApply(const PFBaseApplicator* pApplicator);

  PerFactionStatistics const &GetFactionStatistics(NDb::EFaction faction) { return perFactionStatistics[faction]; }

  void SetLoserFaction( NDb::EFaction loserFaction )
  {
    if (loserFaction == NDb::FACTION_BURN)
      perFactionStatistics[ NDb::FACTION_FREEZE ].SetWinner();
    else
      perFactionStatistics[ NDb::FACTION_BURN ].SetWinner();
  }

  STARFORCE_EXPORT void CalculateFinalScore( NGameX::HeroTitleCalculator const* heroTitleCalculator );
  int  GetScore(CPtr<PFBaseHero> pHero) const;

  bool isFirstKill         () const { return 1 == killInstances.size(); }
  bool isFirstTowerDestroy () const { return 1 == towersDestroyedCnt; }

  void SetTowersDestroyedCnt(int val) { towersDestroyedCnt = val; }
  int  GetTowersDestroyedCnt() const { return towersDestroyedCnt; }

  void SetMainBuildingKiller(CPtr<PFBaseUnit> pKiller);
  void SetMainBuildingKiller(int playerID) { mainBuildingKiller = playerID; };
  int  GetMainBuildingKiller() const { return mainBuildingKiller; }

  void SetFirstMerciless(int playerID);
  int  GetFirstMerciless() const { return firstMerciless; }

  void SetFirstMGAllLevelsWinner(int playerID);
  int  GetFirstMGAllLevelsWinner() const { return firstMGAllLevelsWinner; }

  void SetScoringTable( const NDb::ScoringTable * _scoringTable ) { scoring = _scoringTable; }
  NDb::ScoringTable const* GetScoringTable() { return scoring; }

protected:
  // ui events
  NDb::Ptr<NDb::UIEventsCustom> pCustomUiEvents;

  CObj<NGameX::PFUIEvent> pEventHeroKill;
  CObj<NGameX::PFUIEvent> pEventHeroKillByAI;
  CObj<NGameX::PFUIEvent> evHeroKillByNeutralAI;
  CObj<NGameX::PFUIEvent> pEventTowerDestroy;
  CObj<NGameX::PFUIEvent> pEventTowerDestroyByAI;
  CObj<NGameX::PFUIEvent> pEventCheat;

  ZDATA_(PFWorldObjectBase)
	CPtr<PFWorld> pWorld;
	NDb::Ptr<NDb::ScoringTable> scoring;
  nstl::vector<StatisticsStuff::HeroKillInstance> killInstances;
  nstl::vector<StatisticsStuff::HeroAssistInstance> assistInstances;
  StaticArray<PerFactionStatistics, NDb::KnownEnum<NDb::EFaction>::sizeOf> perFactionStatistics;
  int firstMiniGameWinner;
  int towersDestroyedCnt;

  nstl::map<int, nstl::vector<int> > towersHitByTerrain;

  int mainBuildingKiller;     // Player ID of the main building killer
  int firstMerciless;         // Player ID of the first player, who killed all heroes from the oposite faction
  int firstMGAllLevelsWinner; // Player ID of the first player, who finished all minigame levels
  bool wasFirstAssault;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pWorld); f.Add(3,&scoring); f.Add(4,&killInstances); f.Add(5,&assistInstances); f.Add(6,&perFactionStatistics); f.Add(7,&firstMiniGameWinner); f.Add(8,&towersDestroyedCnt); f.Add(9,&towersHitByTerrain); f.Add(10,&mainBuildingKiller); f.Add(11,&firstMerciless); f.Add(12,&firstMGAllLevelsWinner); f.Add(13,&wasFirstAssault); return 0; }

  bool OnStep ( float dtInSeconds );
  void NotifyTeleport ( PFBaseMovingUnit &pUnit );
  void NotifyTeleportByAbility( PFBaseMovingUnit* pUnit, NDb::Ability const* pDBAbility );

	virtual void Reset();

  void ResetUiEvents();

  const NDb::ScoringTable * DbScoring() const { return scoring; }

  const vector<StatisticsStuff::HeroKillInstance>   & GetKillInstances()   const { return killInstances; }
  const vector<StatisticsStuff::HeroAssistInstance> & GetAssistInstances() const { return assistInstances; }

 
  CVec2 const& GetWorldSize () const 
  { 
    if (IsValid(pWorld)) 
      return pWorld->GetMapSize();
    else
      return VNULL2;
  }

  void SendCheatMessage( PFBaseHero * hero );
  void NotifyItemTransfer( PFBaseHero * from, PFBaseHero * to, const NDb::Consumable * dbItem );

  static CPtr<NWorld::PFBaseHero> GetHeroById( const CPtr<NWorld::PFAIWorld>& pAIWorld, int id );
 
private:
  STARFORCE_EXPORT void AddHeroDeathImpl(CPtr<PFBaseHero> pVictim, CPtr<PFBaseUnit> pKiller);
};

} //namespace NWorld

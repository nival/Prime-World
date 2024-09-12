#pragma once

#include "DBStats.h"
#include "PFAICommon.h"
#include "PFVoxelMap.h"

#include "PFHero.h"
#include "PFFlagpole.h"
#include "AIWorldFacets/FemaleMaleAssistEffect.h"
#include "AIWorldFacets/VotingForSurrenderLogic.h"
#include "System/StarForce/StarForce.h"

#include "DBAdvMap.h"

namespace NDb
{
struct UnitLogicParameters;
struct UnitsLogicParameters;
struct AILogicParameters;
}

namespace NGameX
{
_interface IAdventureScreen;
}

namespace NWorld
{

class PFWorld;
class PFBaseUnit;
class PFBaseHero;
class PFBuilding;
class PFLogicObject;
class PFVoxelMap;
class PFBaseMaleHero;
class PFNatureGlyph;
class PFGlyphsManager;
class PFCreepSpawner;
class PFBaseCreep;
class PFApplDamage;

class PFAIWorld : public PFVoxelMap
{
  WORLD_OBJECT_METHODS(0x2C5AE340, PFAIWorld)
public:
   STARFORCE_EXPORT PFAIWorld( PFWorld * _world );

  typedef vector<CObj<PFLogicObject> >  Objects;
  typedef vector<CObj<PFBaseUnit> >     Units;

  struct StatsCoeffs
  {
    StatsCoeffs()
    {
      coeffsByFaction[0] = 1.0f;
      coeffsByFaction[1] = 1.0f;
      coeffsByFaction[2] = 1.0f;

      botsCoeffsByFaction[0] = 1.0f;
      botsCoeffsByFaction[1] = 1.0f;
      botsCoeffsByFaction[2] = 1.0f;
    }
    StaticArray<float,3> coeffsByFaction;
    StaticArray<float,3> botsCoeffsByFaction;
  };
  
  void RegisterUnit(PFBaseUnit* pUnit);
  void RegisterObject(PFLogicObject* pObject);
  void UnregisterObjectOrUnit(PFLogicObject* pObject); // Both for objects and units

  void Update(float dtInSeconds);

  const NDb::UnitLogicParameters& GetUnitParameters(NDb::EUnitType type) const;
  const NDb::AILogicParameters&   GetAIParameters() const { return *pAILogicParameters; }

  void RegisterCreepSpawner( NDb::EFaction faction, NDb::ERoute routeID, int spawnerObjectID );
  void OnBuildingCreate( NDb::EFaction faction, NDb::ERoute routeID, int level, const CPtr<PFBuilding>& pBuilding );
  void OnBuildingDestroy( NDb::EFaction faction, NDb::ERoute routeID, int level, int objectID, bool isQuarter );

  void AwardKillers(CPtr<PFBaseUnit> pVictim, CPtr<PFBaseUnit> pKiller) const;
  void SendUnitDieNotification(CPtr<PFBaseUnit> pVictim, CPtr<PFBaseUnit> pKiller, PFBaseUnitDamageDesc const* pDamageDesc ) const;

  void LogNaftaIncome(CPtr<PFBaseHero> pKiller, CPtr<PFBaseUnit> pVictim, float nafta, float naftaSpec, float teamNafta) const;

  int   GetMaxHeroLevel() const;
  int   GetHeroDevPoints4Level(int level) const;
  float GetHeroLevelDiffCoeff(int difference, bool useAlternateTable ) const;
  float GetMaxObjectSize() const;
  float GetBattleStartDelay() const { return battleStartDelay; }
  StatsCoeffs const& GetStatsCoeffs() const { return statsCoeffs; }
  void  SetMapData( NDb::AdvMapDescription const * advMapDescription, NDb::AdvMapSettings const * advMapSettings );
  int   GetAveragePriestessLvl( NDb::EFaction faction ) const;
  bool IsTutorial() const { return isTutorial; }
  bool CanUseSkins() const { return canUseSkins; }
  int GetCreepLevelCap() const { return creepLevelCap; }
  bool IsCreepLevelupPaused() const { return creepLevelupPaused; }
  void SetCreepLevelupPaused( bool paused ) { creepLevelupPaused = paused; }

  void OnGameFinished( const NDb::EFaction failedFaction );
  bool WasGameFinished() const { return wasGameFinished; }
  
  const PFCreepSpawner* GetSpawner(NDb::EFaction faction, NDb::ERoute routeID) const;

  // stubs for nature glyphs
  void OnNatureGlyphUsed( NDb::ERoute routeID, const CPtr<PFBaseMaleHero>& pHero);

  bool IsNeutralSpecialAwardingRequired( PFBaseUnit const* pVictim ) const;
  void GetKiller( CPtr<PFBaseUnit> const &pVictim, CPtr<PFBaseUnit> &pKiller ) const;
  void GetKiller( CPtr<PFBaseUnit> const &pVictim, CPtr<PFBaseUnit> &pKiller, PFApplDamage const*& pRefDamageApplicator ) const;
  void GetAssistants(CPtr<PFBaseUnit> pVictim, CPtr<PFBaseUnit> pAggressor, vector<PFBaseHero*> &assistants) const;
  template <class F> void ForAllHeroes(F &f, NDb::EFaction faction, NDb::ESpellTarget targetFlags = NDb::SPELLTARGET_ALL) const
  {
    const PFBaseHero::FactionRing *heroes = GetRingByFaction(faction);
    if (heroes)
      ForAllHeroesRing(f, *heroes, targetFlags);
  }

  template <class F> void ForAllFlagpoles(F &f, int factionMask) const
  {
    vector<PFFlagpole*> flagpoles;
    CollectFlagpoles( &flagpoles );
    for( vector<PFFlagpole*>::iterator it = flagpoles.begin(); it != flagpoles.end(); ++it ) 
    {
      if ( (factionMask & (1 << (*it)->GetFaction())) == 0 ) 
        continue;
      f(**it);
    }
  }

  void RegisterHero(PFBaseHero* pHero);
  void UnregisterHero(PFBaseHero* pHero);

  // colorising
  // yes, yes ... I know it`s a nasty hack to place it here ... 
  Render::HDRColor const& GetTeamColor(NDb::EFaction faction) const;
  Render::HDRColor const& GetHeroColor(NDb::EFaction faction, int id) const;
  const wstring&   GetFactionName(NDb::EFaction faction) const;
  friend bool TestFemaleMaleAssistEffect( const char *name, const vector<wstring> &params );
  void VotingForSurrenderStart( CPtr<PFPlayer> pPlayer );
  void VotingForSurrenderMakeDecision( CPtr<PFPlayer> pPlayer, bool vote );
  AIWorldFacets::VotingForSurrenderLogic *GetVotingForSurrender( int teamId );
  
  //force
  void ApplyForceModifiers( float forceOfMap, float trainingForceCoeff, NDb::EMapType mapType, PFBaseHero* trainingHero );
#ifndef _SHIPPING
  void ApplyForceModifiersCheat();
#endif //_SHIPPING

	void ClearVoxelMap(); //TODOLOF

  CPtr<PFGlyphsManager> GetGlyphsManager() const { return CPtr<PFGlyphsManager>(pGlyphsManager.GetPtr()); }

  struct BuildingsRoute
  {
    struct RouteLevel
    {
      ZDATA;
      int level;
      vector<int> towersIDs;
      vector<int> buildingsIDs;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&level); f.Add(3,&towersIDs); f.Add(4,&buildingsIDs); return 0; }
      RouteLevel(int level = 0) : level(level) {}
      inline bool operator==(int _level) { return level == _level; }
    };

    ZDATA;
    NDb::EFaction       faction;          // фракция
    NDb::ERoute         routeID;          // линия
    int                 spawnerObjectID;  // спавнер
    bool                quarterDestroyed; // барак на этой линии разрушен
    vector<RouteLevel>  levels;           // здания по уровням цепи
    CVec2               borderPoint;      // position of farthest tower(s) in the route
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&faction); f.Add(3,&routeID); f.Add(4,&spawnerObjectID); f.Add(5,&quarterDestroyed); f.Add(6,&levels); f.Add(7,&borderPoint); return 0; }

    // ~~~
    BuildingsRoute( NDb::EFaction _faction = NDb::FACTION_NEUTRAL, NDb::ERoute _routeID = NDb::ROUTE_CENTER ) : faction(_faction), routeID(_routeID), spawnerObjectID(PF_Core::INVALID_OBJECT_ID), quarterDestroyed(false), borderPoint(VNULL2)  {}
    bool operator==(NDb::ERoute _routeID) { return routeID == _routeID; }
    vector<RouteLevel>::iterator GetLevel(int level);
    int GetTowerIDByIndex( int index );
  };

  vector<BuildingsRoute>::iterator GetRoute( NDb::EFaction faction, NDb::ERoute routeID );
  CVec2 GetBorderAtRoute( NDb::EFaction faction, NDb::ERoute routeID ) const;
  void UpdateRouteBorderPoint( BuildingsRoute::RouteLevel const& borderLevel, BuildingsRoute& route );
  PFCreepSpawner* FindSpawnerWithRouteNearestToPoint( const CVec2& pos, const NDb::EFaction faction ) const;

  void SetSpawnCreeps(bool _spawnCreeps) { spawnCreeps = _spawnCreeps; }
  bool GetSpawnCreeps() const { return spawnCreeps; }
  void SetSpawnNeutralCreeps(bool _spawnNeutralCreeps) { spawnNeutralCreeps = _spawnNeutralCreeps; }
  bool GetSpawnNeutralCreeps() const { return spawnNeutralCreeps; }
  NDb::PrimeSettings const& GetPrimeSettings() const { return primeSettings; }
  NDb::Ptr<NDb::HeroNaftaParams> const& GetHeroNaftaParams() const { return heroNaftaParams; }
  bool IsNeutralCreepInAnnounceList( PFBaseCreep const* pNeutral ) const;
  NDb::Ptr<NDb::HeroRespawnParams> const& GetHeroRespawnParams() const { return pHeroRespawnParams; }
  void SetHeroRespawnParams( NDb::Ptr<NDb::HeroRespawnParams> const& newRespawnParams ) { pHeroRespawnParams = newRespawnParams; }
  const NDb::Talent* GetPortalTalent() const { return portalTalent; }

  int GetSurrenderVotes( NDb::EFaction _failedFaction ) const;

  const NDb::Ptr<NDb::BehaviourTrackerParams>& GetBahaviourTrackerParams() const { return pAILogicParameters->behaviourTrackerParams; }

private:
	explicit PFAIWorld() {}
  virtual void OnDestroyContents();
  virtual ~PFAIWorld();

	enum 
	{ 
		DEFAULT_FACTION_FLAGS = (1 << NDb::FACTION_BURN) | (1 << NDb::FACTION_FREEZE)
	};
	
  vector<BuildingsRoute>::const_iterator FindRoute( NDb::EFaction faction, NDb::ERoute routeID ) const;
  void SetRouteLevelVulnerable( BuildingsRoute::RouteLevel* level, bool bVulnerable );
  
  void CalculateStatsCoeffFromForce( float forceOfMap, float trainingForceCoeff, NDb::EMapType mapType, PFBaseHero* trainingHero );
  void UpdateUnitsStatsFromForce();
  void UpdateBotsStats( NDb::EFaction faction );
  void CollectFlagpoles( vector<PFFlagpole*>* pFlagpoles ) const;

  struct ExpandNatureInfo
  {
    bool operator==(const CPtr<PFBaseMaleHero>& pTargetHero) { return pHero == pTargetHero; }
    ZDATA;
    float liveTime;
    CPtr<PFBaseMaleHero> pHero;
    CObj<PFNatureGlyph>  pGlyphTop;
    CObj<PFNatureGlyph>  pGlyphCenter;
    CObj<PFNatureGlyph>  pGlyphBottom;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&liveTime); f.Add(3,&pHero); f.Add(4,&pGlyphTop); f.Add(5,&pGlyphCenter); f.Add(6,&pGlyphBottom); return 0; }
  };
  typedef nstl::list<ExpandNatureInfo> ExpandNatureInfoList;
  
  template <class F> void ForAllHeroesRing(F &f, const PFBaseHero::FactionRing &heroRing, NDb::ESpellTarget targetFlags = NDb::SPELLTARGET_ALL) const
  {                         
    PFBaseHero * const last = heroRing.last();
    for (PFBaseHero *hero = heroRing.first(); hero != last;)
    {
      PFBaseHero *heroNext = heroRing.next(hero);
			if ( (targetFlags & (1 << hero->GetUnitType())) != 0 ) 
				f(*hero);
      hero = heroNext;
    }
  }

	const PFBaseHero::FactionRing* GetRingByFaction(NDb::EFaction faction) const
  {
    if(faction == NDb::FACTION_FREEZE)
    {
      return &heroesOfFactionA;
    }
    else if(faction == NDb::FACTION_BURN)
    {
      return &heroesOfFactionB;
    }
    return 0;
  }

  NDb::PrimeSettings      primeSettings; // no need to serialize it
  NDb::Ptr<NDb::HeroNaftaParams> heroNaftaParams;
  NDb::Ptr<NDb::CreepAnnounceList> creepAnnounceList; // no need to serialize it
  NDb::Ptr<NDb::Talent> portalTalent; // no need to serialize it

#ifndef _SHIPPING
  float mapForce; // used for cheat only
  float trainingForceCoeff;
  CPtr<PFBaseHero> trainingHero;
  NDb::EMapType mapType;
#endif //_SHIPPING

  typedef CObj<AIWorldFacets::VotingForSurrenderLogic> VotingForSurrenderLogicPtr;

  ZDATA_(PFVoxelMap);
  vector<BuildingsRoute>  buildingsRoutes;
  CPtr<PFWorld>           pWorld;
  ExpandNatureInfoList    natureGlyphs;
  float                   maxVisibilityRange;
  float                   maxObjectSize;      // max size of logic object
  float                   battleStartDelay;
  float                   towersVulnerabilityDelay;
  PFBaseHero::FactionRing heroesOfFactionB;
  PFBaseHero::FactionRing heroesOfFactionA;
  CObj<PFGlyphsManager>   pGlyphsManager;
	NDb::Ptr<NDb::UnitsLogicParameters> pUnitLogicParameters;
	NDb::Ptr<NDb::AILogicParameters>    pAILogicParameters;
	NDb::Ptr<NDb::HeroesLevelUps>       pLevelUps; 
	NDb::Ptr<NDb::TeamsColoringScheme>  pColoringScheme;
	NDb::Ptr<NDb::DefaultFormulas>      pDefaultFormulasCache;
  bool                                wasGameFinished;
  AIWorldFacets::FemaleMaleAssistEffect femaleMaleAssistEffect;
  vector<VotingForSurrenderLogicPtr>  votingsForSurrender;
  StatsCoeffs statsCoeffs;
  bool spawnCreeps;
  bool spawnNeutralCreeps;
  bool isTutorial;
  NDb::Ptr<NDb::HeroRespawnParams>  pHeroRespawnParams;
  bool canUseSkins;
  int creepLevelCap;
  bool creepLevelupPaused;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFVoxelMap*)this); f.Add(2,&buildingsRoutes); f.Add(3,&pWorld); f.Add(4,&natureGlyphs); f.Add(5,&maxVisibilityRange); f.Add(6,&maxObjectSize); f.Add(7,&battleStartDelay); f.Add(8,&towersVulnerabilityDelay); f.Add(9,&heroesOfFactionB); f.Add(10,&heroesOfFactionA); f.Add(11,&pGlyphsManager); f.Add(12,&pUnitLogicParameters); f.Add(13,&pAILogicParameters); f.Add(14,&pLevelUps); f.Add(15,&pColoringScheme); f.Add(16,&pDefaultFormulasCache); f.Add(17,&wasGameFinished); f.Add(18,&femaleMaleAssistEffect); f.Add(19,&votingsForSurrender); f.Add(20,&statsCoeffs); f.Add(21,&spawnCreeps); f.Add(22,&spawnNeutralCreeps); f.Add(23,&isTutorial); f.Add(24,&pHeroRespawnParams); f.Add(25,&canUseSkins); f.Add(26,&creepLevelCap); f.Add(27,&creepLevelupPaused); return 0; }
};


class UnitsCollector : public NonCopyable
{
public:
  void operator()(PFBaseUnit &unit);
  UnitsCollector(PFAIWorld::Units &_result);

	bool TraverseObjects() const { return true; }
	bool TraverseUnits() const { return true; }

private:
  PFAIWorld::Units &result;
};


class UnitMaskingPredicate
{
public:
  UnitMaskingPredicate(int factionMask_, int unitTypeMask_ = NDb::SPELLTARGET_ALL | NDb::SPELLTARGET_FLYING, PFBaseUnit *_pOwner = 0)
    : factionMask(factionMask_), unitTypeMask(unitTypeMask_), pOwner(_pOwner)
  {}

	UnitMaskingPredicate(PFBaseUnit * _pOwner, NDb::ESpellTarget targetFilter);

  bool operator()(const PFLogicObject &pUnit) const;
	
  bool TraverseObjects() const { return (unitTypeMask & (NDb::SPELLTARGET_TREE | NDb::SPELLTARGET_PICKUPABLE)) != 0; }
	bool TraverseUnits() const 
	{ 
		return (unitTypeMask & ~(NDb::SPELLTARGET_ALLY | NDb::SPELLTARGET_ENEMY | NDb::SPELLTARGET_TREE | NDb::SPELLTARGET_PICKUPABLE)) != 0;
	}

private:
  int              factionMask;
  int              unitTypeMask;
	CPtr<PFBaseUnit> pOwner;
};

class CreaturePredicate
{
public:
  CreaturePredicate() {}
  bool operator()(const PFLogicObject& pLogicObject) const;
};


//////////////////////////////////////////////////////////////////////////
inline float PFAIWorld::GetMaxObjectSize() const
{
  return maxObjectSize;
}

}

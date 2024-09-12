#include "stdafx.h"
#include "PFAIWorld.h"
#include "PFBaseUnit.h"
#include "DBGameLogic.h"
#include "DBSound.h"


#include "PFCommonCreep.h"
#include "PFTower.h"
#include "TileMap.h"

#include "PFMaleHero.h"

#include "PFGlyph.h"
#include "PFWorldNatureMap.h"
#include "PFApplicatorHistoryAnalysis.h"
#include "PFApplInstant.h"
#include "PFAbilityInstance.h"
#include "PFAbilityData.h"
#include "PFApplAura.h"
#include "ForceCalc.h"

#include "PFRoadFlagpole.h"
#include "PFScriptedFlagpole.h"

#include "PFStatistics.h"

#include "PFGlyphManager.h"

#include "PFPredefinedUnitVariables.h"

#include "Scene/DiAnGr.h"

#include "IAdventureScreen.h"

#include "System/InlineProfiler.h"

#include "SessionEventType.h"

#include "Sound/EventScene.h"
#include "UI/Root.h"

#include "PFAIContainer.h"
#include "Scripts/FuncCallMacroses.h"

#include "TargetSelectorFormulaPars.h"

#include "PlayerBehaviourTracking.h"

#ifndef VISUAL_CUTTED
#include "AdventureScreen.h"    // for MEGA creeps
#else

// Ugly hack!!! @BVS@TODO
namespace Render
{
	Render::HDRColor HSV2RGB(const float h, const float s, const float v) { return HDRColor(h,s,v); }
}

#endif


namespace
{

  float g_battleStartDelay = -1;

#ifdef _SHIPPING
  static bool g_logNaftaAwards = false;
#else
  static bool g_logNaftaAwards = true;
#endif

} // namespace

REGISTER_DEV_VAR("log_nafta_awards", g_logNaftaAwards, STORAGE_NONE);

namespace NWorld
{

void PFAIWorld::OnDestroyContents()
{
  Clear(heroesOfFactionA);
  Clear(heroesOfFactionB);
  PFVoxelMap::OnDestroyContents();
}

PFAIWorld::~PFAIWorld()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::UnitLogicParameters& PFAIWorld::GetUnitParameters(NDb::EUnitType type) const
{
	return *pUnitLogicParameters->unitParameters[type];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::RegisterUnit(PFBaseUnit* pUnit)
{
  NI_VERIFY(pUnit, "Trying to register invalid unit!", return; );
  AddObject(*pUnit);
  
  {
    // Increasing maxVisibilityRange if needed
     float fRange = pUnit->GetVisibilityRange();
     if ( maxVisibilityRange < fRange )
       maxVisibilityRange = fRange;
     
     float fSize = pUnit->GetObjectSize();
     if ( maxObjectSize < fSize )
       maxObjectSize = fSize;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::RegisterObject(PFLogicObject* pObject)
{
	NI_VERIFY(pObject, "Trying to register invalid unit!", return; );
  AddObject(*pObject);

  {
    float fSize = pObject->GetObjectSize();
    if ( maxObjectSize < fSize )
      maxObjectSize = fSize;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::UnregisterObjectOrUnit(PFLogicObject* pObject)
{
	NI_VERIFY(pObject, "Trying to unregister invalid unit!", return; );
  RemoveObject(*pObject);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::Update(float dtInSeconds)
{
  NI_PROFILE_FUNCTION;

  const NDb::Ptr<NDb::SoundRoot>& soundRoot = NDb::SoundRoot::GetRoot();

  if ( battleStartDelay >= 0 )
  {
    if ( (int)(battleStartDelay-0.1f) != (int)(battleStartDelay-0.11f) && (battleStartDelay-0.11f) < soundRoot->timerSounds.timeToTickOnStart )
    {
      NSoundScene::EventStart( soundRoot->timerSounds.startTimerSound );
    }
    battleStartDelay -= dtInSeconds;
    if ( battleStartDelay <= 0 )
    {
      pWorld->GetIAdventureScreen()->NotifySoldiersFirstSpawned();
    }
  }

  if ( towersVulnerabilityDelay >= 0 ) // По умолчанию башни неуязвимы, так что даже при 0 надо обрабатывать
  {
    towersVulnerabilityDelay -= dtInSeconds;
    if ( towersVulnerabilityDelay <= EPS_VALUE )
    {
      SetRouteLevelVulnerable( GetRoute(NDb::FACTION_FREEZE,  NDb::ROUTE_BOTTOM)->GetLevel(0), true );
      SetRouteLevelVulnerable( GetRoute(NDb::FACTION_FREEZE,  NDb::ROUTE_CENTER)->GetLevel(0), true );
      SetRouteLevelVulnerable( GetRoute(NDb::FACTION_FREEZE,  NDb::ROUTE_TOP   )->GetLevel(0), true );
      SetRouteLevelVulnerable( GetRoute(NDb::FACTION_BURN  ,  NDb::ROUTE_BOTTOM)->GetLevel(0), true );
      SetRouteLevelVulnerable( GetRoute(NDb::FACTION_BURN  ,  NDb::ROUTE_CENTER)->GetLevel(0), true );
      SetRouteLevelVulnerable( GetRoute(NDb::FACTION_BURN  ,  NDb::ROUTE_TOP   )->GetLevel(0), true );
    }
  }
}

namespace
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetCreepSpawnLevel( const CPtr<PFWorld>& pWorld, int spawnerObjectID, PFCreepSpawner::CreepsPower level )
{
  PF_Core::WorldObjectBase* pObject = pWorld->GetObjectById( spawnerObjectID );
  if ( pObject )
  {
    PFCreepSpawner* pSpawner = dynamic_cast<PFCreepSpawner*>(pObject);
    if (pSpawner)
      pSpawner->SetCreepsPower(level);
  }
}

} // noname namespace

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<PFAIWorld::BuildingsRoute>::const_iterator PFAIWorld::FindRoute( NDb::EFaction faction, NDb::ERoute routeID ) const
{
  vector<BuildingsRoute>::const_iterator iRoute = buildingsRoutes.begin();
  for ( ; iRoute!=buildingsRoutes.end(); ++iRoute )
    if ( iRoute->faction == faction && iRoute->routeID == routeID )
      break;

  return iRoute;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<PFAIWorld::BuildingsRoute>::iterator PFAIWorld::GetRoute( NDb::EFaction faction, NDb::ERoute routeID )
{
  vector<BuildingsRoute>::iterator iRoute = buildingsRoutes.begin();
  for ( ; iRoute!=buildingsRoutes.end(); ++iRoute )
    if ( iRoute->faction == faction && iRoute->routeID == routeID )
      break;

  if ( buildingsRoutes.end() == iRoute )
  {
    buildingsRoutes.push_back( BuildingsRoute( faction, routeID ) );
    iRoute = &buildingsRoutes.back();
  }
  return iRoute;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 PFAIWorld::GetBorderAtRoute( NDb::EFaction faction, NDb::ERoute routeID ) const
{
  vector<BuildingsRoute>::const_iterator iRoute = FindRoute( faction ,routeID );
  if ( iRoute == buildingsRoutes.end() )
    return VNULL2;

  return iRoute->borderPoint;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::SetRouteLevelVulnerable( BuildingsRoute::RouteLevel* level, bool bVulnerable )
{
  NI_VERIFY( level, "Route level not found!", return; );

  // process towers of level
  for ( vector<int>::const_iterator iID = level->towersIDs.begin(), iEnd = level->towersIDs.end(); iID != iEnd; ++ iID )
  {
    PF_Core::WorldObjectBase* pObject = pWorld->GetObjectById( *iID );
    if ( pObject )
    {
      PFBaseUnit* pUnit = dynamic_cast<PFBaseUnit*>(pObject);
      if ( pUnit && pUnit->IsVulnerable() != bVulnerable )
        pUnit->SetVulnerable(bVulnerable);
    }
  }
  
  // process buildings of level
  for ( vector<int>::const_iterator iID = level->buildingsIDs.begin(), iEnd = level->buildingsIDs.end(); iID != iEnd; ++ iID )
  {
    PF_Core::WorldObjectBase* pObject = pWorld->GetObjectById( *iID );
    if ( pObject )
    {
      PFBaseUnit* pUnit = dynamic_cast<PFBaseUnit*>(pObject);
      if ( pUnit && pUnit->IsVulnerable() != bVulnerable )
        pUnit->SetVulnerable(bVulnerable);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<PFAIWorld::BuildingsRoute::RouteLevel>::iterator PFAIWorld::BuildingsRoute::GetLevel(int level)
{
  vector<RouteLevel>::iterator iLevel = find( levels.begin(), levels.end(), level );
  if ( iLevel == levels.end() )
  {
    levels.push_back( BuildingsRoute::RouteLevel(level) );
    iLevel = &levels.back();
  }
  return iLevel;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFAIWorld::BuildingsRoute::GetTowerIDByIndex( int index )
{
  // Enumerate Towers;
  int numLevels = 0;
  for ( int i = 0; i < levels.size(); ++i )
  {
    if ( !levels[i].towersIDs.empty() )
    {
      ++numLevels;
    }
  }

  vector<int> towerIDs;
  for ( int level = numLevels - 1; level >= 0; --level )
  {
    for ( int i = 0; i < levels.size(); ++i )
    {
      if ( levels[i].level == level )
      {
        for ( int j = 0; j < levels[i].towersIDs.size(); ++j )
        {
          towerIDs.push_back( levels[i].towersIDs[j] );
        }
        break;
      }
    }
  }

  return towerIDs[index];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::RegisterCreepSpawner( NDb::EFaction faction, NDb::ERoute routeID, int spawnerObjectID )
{
  NI_VERIFY( (routeID != NDb::ROUTE_UNASSIGNED) && (routeID != NDb::ROUTE_TREE) && (faction != NDb::FACTION_NEUTRAL), "Quarter is neutral or binded to wrong route!", return; );
  
  // спавнер должен быть привязан к баракам противоположной стороны;
  faction = (faction == NDb::FACTION_BURN) ? NDb::FACTION_FREEZE : NDb::FACTION_BURN;
  
  vector<BuildingsRoute>::iterator iRoute = GetRoute( faction, routeID );
  NI_VERIFY( buildingsRoutes.end() != iRoute && iRoute->spawnerObjectID==PF_Core::INVALID_OBJECT_ID, "Spawner already registered for this route!", return; );
  iRoute->spawnerObjectID = spawnerObjectID;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::UpdateRouteBorderPoint( BuildingsRoute::RouteLevel const& borderLevel, BuildingsRoute& route )
{
  if ( !borderLevel.towersIDs.empty() )
  {
    CVec2 borderPos(VNULL2);
    PFBaseUnit const* pTower = dynamic_cast<PFBaseUnit const*>(GetWorld()->GetObjectById( borderLevel.towersIDs[0] ));
    if ( pTower )
    {
      borderPos = pTower->GetPosition().AsVec2D();

      // find road point closest to the tower position
      if ( route.routeID < NDb::ROUTE_TREE )
      {
        vector<CVec2> const& road = GetWorld()->GetNatureMap()->GetLogicRoad( (NDb::ENatureRoad)route.routeID );
        if ( road.size() > 1 )
        {
          borderPos = GetNearestPathPoint( road, borderPos );
        }
      }
    }
    route.borderPoint = borderPos;
  }
  else
  {
    route.borderPoint = VNULL2; // no borders at this route
  }
  //DevTrace( "Route %d border is (%f, %f)", (int)route.routeID, route.borderPoint.x, route.borderPoint.y );
}

PFCreepSpawner* PFAIWorld::FindSpawnerWithRouteNearestToPoint( const CVec2& pos, const NDb::EFaction faction ) const
{
  float minDist = MAX_FLOAT;
  PFCreepSpawner* pNearestSpawner = 0;

  vector<BuildingsRoute>::const_iterator iRoute = buildingsRoutes.begin();
  for ( ; iRoute!=buildingsRoutes.end(); ++iRoute )
  {
    if ( iRoute->faction == faction ) // see RegisterCreepSpawner method for answers :)
      continue;

    PFCreepSpawner* pSpawner = dynamic_cast<PFCreepSpawner*>(GetWorld()->GetObjectById( iRoute->spawnerObjectID ));
    if ( pSpawner )
    {
      const vector<CVec2>& path = pSpawner->GetPath();
      int pathIndex;
      float dist = fabs( GetNearestPathPoint( path, pos, pathIndex ) - pos );

      if ( dist < minDist )
      {
        minDist = dist;
        pNearestSpawner = pSpawner;
      }
    }
  }

  return pNearestSpawner;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::OnBuildingCreate( NDb::EFaction faction, NDb::ERoute routeID, int level, const CPtr<PFBuilding>& pBuilding )
{
  if ( faction == NDb::FACTION_NEUTRAL || routeID == NDb::ROUTE_UNASSIGNED )
    return;
  
  const int objectID = pBuilding->GetObjectId();
  vector<BuildingsRoute>::iterator itRoute = GetRoute( faction, routeID );
  vector<BuildingsRoute::RouteLevel>::iterator iLevel = itRoute->GetLevel(level);

  NI_VERIFY( find( iLevel->towersIDs.begin(), iLevel->towersIDs.end(), objectID ) == iLevel->towersIDs.end(), "Tower already registered on that level of route!", return; );
  NI_VERIFY( find( iLevel->buildingsIDs.begin(), iLevel->buildingsIDs.end(), objectID ) == iLevel->buildingsIDs.end(), "Building already registered on that level of route!", return; );

  if ( pBuilding->GetUnitType() == NDb::UNITTYPE_TOWER )
    iLevel->towersIDs.push_back(objectID);
  else
    iLevel->buildingsIDs.push_back(objectID);
  
  // Make that building invulnerable
  pBuilding->SetVulnerable(false);

  // Set borderPoint
  // It is supposed that level 0 has a tower.
  if ( iLevel->level == 0 )
  {
    UpdateRouteBorderPoint( *iLevel, *itRoute );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::OnBuildingDestroy( NDb::EFaction faction, NDb::ERoute routeID, int level, int objectID, bool isQuarter )
{
  if ( faction == NDb::FACTION_NEUTRAL || routeID == NDb::ROUTE_UNASSIGNED )
    return;

  vector<BuildingsRoute>::iterator iRoute = GetRoute( faction, routeID );
  vector<BuildingsRoute::RouteLevel>::iterator iLevel = iRoute->GetLevel(level);
  
  vector<int>::iterator iObject = find(iLevel->towersIDs.begin(), iLevel->towersIDs.end(), objectID);
  if ( iObject != iLevel->towersIDs.end() )
  {
    NI_ASSERT(!isQuarter, "Internal error - tower is quarter!");
    iLevel->towersIDs.erase( iObject );
  }
  else
  {
    iObject = find(iLevel->buildingsIDs.begin(), iLevel->buildingsIDs.end(), objectID);
    NI_VERIFY( iObject != iLevel->buildingsIDs.end(), "Object not registered on that level of route!", return; );
    
    // Large & Mega creeps
    if ( isQuarter )
    {
      if ( iRoute->quarterDestroyed || iRoute->spawnerObjectID == PF_Core::INVALID_OBJECT_ID )
        DebugTrace( "No spawner for route %i", (int)routeID );

      // Creep-Route cleared, set spawn level for this route to "Large"
      SetCreepSpawnLevel( pWorld, iRoute->spawnerObjectID, NWorld::PFCreepSpawner::powerLarge );
      //pWorld->GetIAdventureScreen()->NotifyPushedLine( faction, routeID );

      iRoute->quarterDestroyed = true;

      // Make Towers of Main Building vulnerable
      SetRouteLevelVulnerable( GetRoute(faction, NDb::ROUTE_TREE)->GetLevel(0), true );

      // Check if all creep routes destroyed
      vector<BuildingsRoute>::iterator iRouteTop = GetRoute(faction, NDb::ROUTE_TOP);
      vector<BuildingsRoute>::iterator iRouteCenter = GetRoute(faction, NDb::ROUTE_CENTER);
      vector<BuildingsRoute>::iterator iRouteBottom = GetRoute(faction, NDb::ROUTE_BOTTOM);
      if (iRouteTop->quarterDestroyed && iRouteCenter->quarterDestroyed && iRouteBottom->quarterDestroyed)
      {
        // Set spawn level to "Mega"
        SetCreepSpawnLevel( pWorld, iRouteTop->spawnerObjectID, NWorld::PFCreepSpawner::powerMega );
        SetCreepSpawnLevel( pWorld, iRouteCenter->spawnerObjectID, NWorld::PFCreepSpawner::powerMega );
        SetCreepSpawnLevel( pWorld, iRouteBottom->spawnerObjectID, NWorld::PFCreepSpawner::powerMega );

        //pWorld->GetIAdventureScreen()->NotifyPushedLine( faction, NDb::ROUTE_TREE );
      }
    }
    
    // Remove building from level
    iLevel->buildingsIDs.erase(iObject);
  }

  if ( iLevel->towersIDs.empty() ) 
  {
    // all towers destroyed, make all buildings of next level vulnerable
    vector<BuildingsRoute::RouteLevel>::iterator iNextLevel = find(iRoute->levels.begin(), iRoute->levels.end(), level + 1);
    if ( iNextLevel != iRoute->levels.end() )
    {
      SetRouteLevelVulnerable( iNextLevel, true );

      // Update borderPoint.
      // Is is supposed that there are no route levels with missing towers between route levels containing ones.
      // But there still may present route levels with missing towers at the chain end.
      UpdateRouteBorderPoint( *iNextLevel, *iRoute );
    }
  }

}


namespace
{

struct AssistAppliedApplicatorsEnumerator_
{
  AssistAppliedApplicatorsEnumerator_(vector<PFBaseHero*> &heroes, CPtr<PFBaseUnit> pKiller, CPtr<PFBaseUnit> pVictim) 
		: heroes(heroes), pKiller(pKiller), pVictim(pVictim), aggressionStartTime(1.0e30f)
	{}
  void operator()(CObj<PFBaseApplicator> &applicator)
  {
    CPtr<PFBaseUnit> pAssistant = applicator->GetAbilityOwner();

    if (IsValid(pAssistant) && IsValid(pAssistant->GetMasterUnit()))
      pAssistant = pAssistant->GetMasterUnit(); // for summoned units

    if (IsValid(pAssistant) && pAssistant->IsTrueHero() )
    {
      PFBaseHero *pHeroAssistant = static_cast<PFBaseHero *>(pAssistant.GetPtr());

      // (1) skip auto assist and store aggression start time
      if (pHeroAssistant == pKiller)
      {
        aggressionStartTime = min(aggressionStartTime, applicator->GetMarkerTime());
        return;
      }

      // (2) skip assist from another team (while Boss killing for example
      if (pHeroAssistant->GetFaction() != pKiller->GetFaction())
      {
        return;
      }

      // (4) skip 'aura' applicators
      bool isAura = dynamic_cast<PFApplAura *>(applicator.GetPtr());

      CPtr<PFBaseApplicator> parentAppl = applicator->GetParentAppl();
      // search for aura applicators
      while (IsValid(parentAppl) && !isAura)
      {
        isAura |= (bool)dynamic_cast<NWorld::PFApplAura *>(parentAppl.GetPtr());
        parentAppl = parentAppl->GetParentAppl();
      }
      if ( isAura ) 
      {
        return;
      }

      // IKaa TODO: (3) & (4) conditions look too hacky
      // need to refactoring by adding some flag to determine is applicator should use for assist or not

			PushUnique(heroes, pHeroAssistant);
    }
  }  

  vector<PFBaseHero*> &heroes;
  CPtr<PFBaseUnit> pKiller;
  CPtr<PFBaseUnit> pVictim;
	float            aggressionStartTime;
private:
  AssistAppliedApplicatorsEnumerator_&operator=(AssistAppliedApplicatorsEnumerator_ const &);
};

struct FindCreepKiller
{
  FindCreepKiller(CPtr<PFBaseUnit> const &_pKiller) : pKiller(_pKiller), pDamageApplicator(NULL) {}

  void operator()(CObj<PFBaseApplicator> const &appl)
  {
    CPtr<PFBaseUnit> pOwner = appl->GetAbilityOwner();
    if ( (PFApplDamage::typeId == appl->GetTypeId()) && 
         ( pOwner->IsTrueHero() ) && 
         (pKiller->GetFaction() == pOwner->GetFaction()) )
    {
      if (!IsValid(pHero))
      {
        pHero = pOwner;
        pDamageApplicator = static_cast<PFApplDamage const*>(appl.GetPtr());
      }
    }
  }

  CPtr<PFBaseUnit> pKiller;
  CPtr<PFBaseUnit> pHero;
  PFApplDamage const* pDamageApplicator;
};

struct FindKillAndDeathHero
{
  FindKillAndDeathHero(CPtr<PFBaseUnit> const &_pKiller) : pKiller(_pKiller), found(false) {}

  void operator()(CObj<PFBaseApplicator> const &appl)
  {
    if (found)
      return;
    CPtr<PFBaseUnit> pOwner = appl->GetAbilityOwner();
    if ( (PFApplDamage::typeId == appl->GetTypeId()) && 
       ( pOwner->IsTrueHero() ) && 
       (pKiller->GetFaction() == pOwner->GetFaction()))
    {
      found = true;
      if (pOwner->IsDead())
        pHero = pOwner;
    }
  }

  bool found;
  CPtr<PFBaseUnit> pKiller;
  CPtr<PFBaseUnit> pHero;
};

struct FindNeutralDamage
{
  FindNeutralDamage() : damageSum(0.f) {}

  void operator()(CObj<PFBaseApplicator> const &appl)
  {
    CPtr<PFBaseUnit> pOwner = appl->GetAbilityOwner();

    if( pOwner->GetFaction() == NDb::FACTION_NEUTRAL )
    {
      if( PFApplDamage* applDamage = dynamic_cast<PFApplDamage*>( appl.GetPtr() ) )
      {
        if( applDamage->GetDamageDealed() > 0.0f )
          damageSum += applDamage->GetDamageDealed();
      }
    }
  }

  float            damageSum;
};

struct ComputeDamageAmountPerHero
{
  struct DamageCount
  {
    CPtr<PFBaseUnit> pHero;
    float            damage;

    DamageCount() : damage(0.0f) {}
  };

  void operator()(PFBaseHero &hero)
  {
    int id = hero.GetInTeamId();

    NI_VERIFY(0 <= id && id <= 5, "Unknown TeamId", return);
    damage[id].pHero  = static_cast<PFBaseUnit*>(&hero);
    damage[id].damage = 0.0f;
  }

  void operator()(PFDamageHistoryData const &data)
  {
    if (!data.pHero->IsTrueHero())
      return;

    if ( faction != data.pHero->GetFaction() )
      return;

    PFBaseHero *pHero = static_cast<PFBaseHero*>(data.pHero.GetPtr());
    int id = pHero->GetInTeamId();
    NI_VERIFY(0 <= id && id <= 5, "Unknown TeamId", return);

    damage[id].damage += data.appliedDamage;
  }

  ComputeDamageAmountPerHero(CPtr<PFBaseHero> const &pVictim, float timeInterval)
  {
    faction = pVictim->GetOppositeFaction();

    PFAIWorld *pAIWorld = pVictim->GetWorld()->GetAIWorld();

    pAIWorld->ForAllHeroes(*this, pVictim->GetOppositeFaction());

    if ( IsValid( pVictim->GetHeroStatistics() ) )
      pVictim->GetHeroStatistics()->ForAllDamageHistoryAfterTime(pVictim->GetWorld()->GetTimeElapsed() - timeInterval, *this);
  }

  CPtr<PFBaseUnit> const &GetMaxDamageUnit()
  {
    int idx = 0;
    for (int i = 0, count = damage.capacity(); i < count; ++i)
    {
      if (damage[i].damage > damage[idx].damage)
        idx = i;
    }
    return damage[idx].pHero;
  }

  float const &GetMaxDamage()
  {
    int idx = 0;
    for (int i = 0, count = damage.capacity(); i < count; ++i)
    {
      if (damage[i].damage > damage[idx].damage)
        idx = i;
    }
    return damage[idx].damage;
  }

  StaticArray<DamageCount, 6> damage;
  NDb::EFaction faction;
};

} // noname namespace

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIWorld::IsNeutralSpecialAwardingRequired( PFBaseUnit const* pVictim ) const
{
  if (!IsValid(primeSettings.neutralKillExperienceModifier))
    return false;

  if (pVictim->GetTypeId() != PFNeutralCreep::typeId)
    return false;

  // SpecialAwarding==true for creep means not to use "neutralKillExperienceModifier"
  return !static_cast<const PFNeutralCreep*>(pVictim)->HasSpecialAwarding();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void PFAIWorld::GetKiller(CPtr<PFBaseUnit> const &pVictim, CPtr<PFBaseUnit> &pKiller ) const
{
  PFApplDamage const* pDamageApplicator = 0;
  GetKiller( pVictim, pKiller, pDamageApplicator );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::GetKiller(CPtr<PFBaseUnit> const &pVictim, CPtr<PFBaseUnit> &pKiller, PFApplDamage const*& pRefDamageApplicator ) const
{
  NI_VERIFY(IsValid(pVictim), "Victim is not valid. Unable to compute killer", return);

  if ( !IsValid(pKiller) || pKiller->IsTrueHero() || pKiller->GetFaction() == NDb::FACTION_NEUTRAL )
    return;

  if ( pKiller->GetFaction() == pVictim->GetFaction())
    return;

  if ( IsValid( pKiller->GetMasterUnit() ) )
  {
    do
    {
      pKiller = pKiller->GetMasterUnit(); // for summoned units
    }
    while ( IsValid( pKiller->GetMasterUnit() ) );

    if ( pKiller->IsTrueHero() )
      return;
  }

  // Ok... pVictim was killed by non hero unit
  if (pVictim->IsTrueHero() )
  {
    FindKillAndDeathHero deathHeroFinder(pKiller);

    pVictim->ForAllAppliedApplicatorsInHistoryLess(deathHeroFinder, GetAIParameters().killTimeIntervals.heroKillerDeadInterval);

    if (deathHeroFinder.found && IsValid(deathHeroFinder.pHero))
    {
      pKiller = deathHeroFinder.pHero;
      return;
    }

    CPtr<PFBaseHero> pHero = static_cast<PFBaseHero*>(pVictim.GetPtr());
    ComputeDamageAmountPerHero damageFinder(pHero, GetAIParameters().killTimeIntervals.heroKillDamageInterval);
    CPtr<PFBaseUnit> const &pMaxDamager = damageFinder.GetMaxDamageUnit();
    if (IsValid(pMaxDamager))
    {
      FindNeutralDamage neutralDamageFinder;
      pVictim->ForAllAppliedApplicatorsInHistoryLess(neutralDamageFinder, GetAIParameters().killTimeIntervals.heroKillDamageInterval);

      if( damageFinder.GetMaxDamage() > neutralDamageFinder.damageSum )
      {
        pKiller = pMaxDamager;
        return;
      }
      else 
        return;
    }
  }
  else
  {
    FindCreepKiller finder(pKiller);

    bool victimIsBuilding = pVictim->GetUnitType() == NDb::UNITTYPE_BUILDING
          || pVictim->GetUnitType() == NDb::UNITTYPE_TOWER
          || pVictim->GetUnitType() == NDb::UNITTYPE_MAINBUILDING;

    const float timeInterval = victimIsBuilding ? GetAIParameters().killTimeIntervals.buildingKillInterval : GetAIParameters().killTimeIntervals.creepKillInterval;

    pVictim->ForAllAppliedApplicatorsInHistoryLess(finder, timeInterval);

    if (IsValid(finder.pHero))   
    {
      pKiller = finder.pHero;
      pRefDamageApplicator = finder.pDamageApplicator;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::GetAssistants(CPtr<PFBaseUnit> pVictim, CPtr<PFBaseUnit> pAggressor, vector<PFBaseHero* > &assistants) const
{
	// 1. those who were injuring victim
  AssistAppliedApplicatorsEnumerator_ eVictim(assistants, pAggressor, pVictim);
  EnumerateAppliedApplicators(pVictim, pAILogicParameters->assistAccountTime, eVictim);

  // 2. those who were assisting all victim's injurers (killer & current assisters)
	if (IsValid(pAggressor) && pAggressor != pVictim)
	{
		float aggressionTimeDelta = pWorld->GetTimeElapsed() - eVictim.aggressionStartTime;
		if (aggressionTimeDelta < 0.0f)
			aggressionTimeDelta = 0.0f;

		AssistAppliedApplicatorsEnumerator_ eAssister(assistants, pAggressor, pVictim);
    float startTime = min(aggressionTimeDelta, pAILogicParameters->assistAccountTime);

    vector<PFBaseUnit*> victimInjurers; 
    // store current assisters
    {
      vector<PFBaseHero* >::iterator last = assistants.end();
      for (vector<PFBaseHero*>::iterator it = assistants.begin(); it != last; ++it)
        victimInjurers.push_back((*it));
    }
    victimInjurers.push_back(pAggressor);

    vector<PFBaseUnit* >::iterator last = victimInjurers.end();
    for (vector<PFBaseUnit*>::iterator it = victimInjurers.begin(); it != last; ++it)
      EnumerateAppliedApplicators((*it), startTime, eAssister);
	}
}

namespace
{
  static inline CPtr<PFBaseHero> GetLocalHero()
  {
    if (NGameX::AdventureScreen* const advScreen = NGameX::AdventureScreen::Instance())
      return advScreen->GetHero();
    return CPtr<PFBaseHero>();
  }
}

// TODO: MOVE
namespace Murder
{
  struct MurderContextGuard : public MurderContext, public NonCopyable
  {
    explicit MurderContextGuard(PFBaseUnit* const victim)
      : victim(victim)
    {
      victim->SetMurderContext(this);
    }
    ~MurderContextGuard()
    {
      victim->SetMurderContext(0);
    }
  private:
    MurderContextGuard();

    PFBaseUnit* const victim;
  };

  // NOTE: adopted from AdventureScreen.cpp
  class GlobalConstantsPars
    : public TargetSelectorFormulaPars
    , public NonCopyable
  {
    const NWorld::PFAIWorld* const aiWorld;
  public:
    GlobalConstantsPars(const NWorld::PFAIWorld* const aiWorld)
      : TargetSelectorFormulaPars(0)
      , aiWorld(aiWorld)
    {
    }

    virtual float GetConstant(const char *name, IUnitFormulaPars const *sender, IUnitFormulaPars const* receiver) const
    {
      typedef nstl::vector<NDb::Ptr<NDb::UnitConstant>> UnitConstantVector;

      NI_ASSERT(sender, "pSender is invalid");
      NI_VERIFY(aiWorld, "AI world is invalid", return 0.f);

      NI_VERIFY(!!name, "Invalid name", return 0.f);
      NI_VERIFY(!!*name, "Empty name", return 0.f);

      const nstl::string str(name);
      const UnitConstantVector& constants = aiWorld->GetAIParameters().globalConstants->vars;

      UnitConstantVector::const_iterator it = constants.begin();
      UnitConstantVector::const_iterator it_end = constants.end();
      for (; it != it_end; ++it)
      {
        UnitConstantVector::const_reference constant = *it;

        if (!IsValid(constant))
          continue;

        if (constant->name == str)
          return constant->var(sender, receiver, this);
      }

      return 0.f;
    }
  };

  typedef nstl::vector<CPtr<PFBaseHero>> HeroVector;

  struct TrueHeroCollector : public NonCopyable
  {
    explicit TrueHeroCollector(HeroVector& heroes)
      : heroes(heroes)
    {
    }

    void operator()(NWorld::PFBaseUnit &unit)
    {
      if (!unit.IsTrueHero())
        return;

      PFBaseHero* const hero = static_cast<PFBaseHero*>(&unit);

      if (!IsUnitValid(hero))
        return;

      heroes.push_back(hero);
    }
  private:
    HeroVector& heroes;
  };

  namespace UnitKind
  {
    enum Enum
    {
      Unknown,
      Hero,
      LocalHero,
      Creep,
      Boss,
      Tower,
      Other,
    };
  }

  namespace NaftaSource
  {
    enum Enum
    {
      NaftaForKill,
      NaftaForAssist,
      NaftaSpecForKill,
      TeamNaftaForKill,
      TeamNaftaForPresence,

      COUNT,
    };
  }

  struct UnitRole
  {
    bool victim:1;          // 
    bool killer:1;          // naftaForKill
    bool assister:1;        // naftaForAssist
    bool spectator:1;       // naftaSpecForKill

    bool killerTeam:1;      // teamNaftaForKill
    bool presentTeam:1;     // teamNaftaForPresence

    bool active:1;          // игрок, которому назначен этот герой, в игре и не AFK

    UnitRole()
      : victim(false)
      , killer(false)
      , assister(false)
      , spectator(false)
      , killerTeam(false)
      , presentTeam(false)
      , active(false)
    {

    }
    UnitRole(const UnitRole& other)
      : victim(other.victim)
      , killer(other.killer)
      , assister(other.assister)
      , spectator(other.spectator)
      , killerTeam(other.killerTeam)
      , presentTeam(other.presentTeam)
      , active(other.active)
    {

    }
  };

  struct Participant
  {
    UnitKind::Enum kind;
    UnitRole role;

    CPtr<PFBaseUnit> unit;
    CPtr<PFBaseHero> hero;

    NaftaAward award;

    Participant()
      : kind(UnitKind::Unknown)
      , role()
      , unit()
      , hero()
      , award()
    {

    }
    Participant(const Participant& other)
      : kind(other.kind)
      , role(other.role)
      , unit(other.unit)
      , hero(other.hero)
      , award(other.award)
    {

    }

    bool IsHero() const
    {
      switch (kind)
      {
      case UnitKind::Hero:
      case UnitKind::LocalHero:
        return true;
      default:
        return false;
      }
    }

    bool IsLocalHero() const
    {
      switch (kind)
      {
      case UnitKind::LocalHero:
        return true;
      default:
        return false;
      }
    }

    bool IsTower() const
    {
      switch (kind)
      {
      case UnitKind::Tower:
        return true;
      default:
        return false;
      }
    }

    bool IsBoss() const
    {
      switch (kind)
      {
      case UnitKind::Boss:
        return true;
      default:
        return false;
      }
    }
  };

  struct HeroAwards
  {
    float kill;
    float spectate;
    float team;

    HeroAwards()
      : kill(0.f)
      , spectate(0.f)
      , team(0.f)
    {

    }
  };

  static inline void OverrideAward(float& value, const float withValue)
  {
    if (!(withValue < 0.f))
      value = withValue;
  }

  static inline CPtr<PFBaseHero> AsHero(PFBaseUnit* const unit)
  {
    return static_cast<PFBaseHero*>(unit);
  }

  static inline CPtr<PFBaseHero> AsHero(PFBaseHero* const hero)
  {
    return hero;
  }

  static inline CPtr<PFBaseHero> AsHero(const CPtr<PFBaseUnit>& unit)
  {
    return static_cast<PFBaseHero*>(unit.GetPtr());
  }

  struct Awarder : public NonCopyable
  {
    typedef nstl::vector<Participant> ParticipantVector;

    Participant victim;
    Participant killer;

    ParticipantVector participants;

    HeroAwards localHeroAwards;

    nstl::vector<PFBaseHero*> assisters;

    int assisterCount;
    int spectatorCount;
    int representativeCount;
    int presentTeamActiveMembers;

    bool specialNeutralAwarding;

    explicit Awarder(const PFAIWorld* const aiWorld)
      : world(aiWorld->GetWorld())
      , aiWorld(aiWorld)
      , primeSettings(aiWorld->GetPrimeSettings())
      , heroNaftaParams(aiWorld->GetHeroNaftaParams())
      , globalConstants(aiWorld)
    {
    }

    void Prepare(const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller)
    {
      NI_VERIFY(primeSettings.awardSpecRange > 0.f, "Value of primeSettings.awardSpecRange is invalid", return);
      NI_VERIFY(primeSettings.awardTeamRange > 0.f, "Value of primeSettings.awardTeamRange is invalid", return);

      aiWorld->GetAssistants(pVictim, pKiller, assisters);

      HeroVector team;
      HeroVector spectators;
      HeroVector representatives;

      GetTeamHeroes(pKiller, team);
      GetNearbyHeroes(pKiller, pVictim->GetPosition(), primeSettings.awardSpecRange, spectators);
      GetNearbyHeroes(pKiller, pVictim->GetPosition(), primeSettings.awardTeamRange, representatives);

      if (pKiller->IsTrueHero())
        assisters.remove(AsHero(pKiller));
      if (pKiller->IsTrueHero() && pVictim->IsTrueHero())
        spectators.remove(AsHero(pKiller));

      assisterCount = assisters.size();
      spectatorCount = spectators.size();
      representativeCount = representatives.size();
      presentTeamActiveMembers = 0;

      specialNeutralAwarding = aiWorld->IsNeutralSpecialAwardingRequired(pVictim);

      const bool killerTeamPresent = (representativeCount > 0);

      MakeParticipant(pVictim, victim);

      victim.role.victim = true;

      MakeParticipant(pKiller, killer);

      killer.role.killer = true;

      if (killer.IsHero())
      {
        killer.role.assister = (assisters.find(killer.hero) != assisters.end());
        killer.role.spectator = (spectators.find(killer.hero) != spectators.end());
        killer.role.killerTeam = true;
        killer.role.presentTeam = killerTeamPresent;
        killer.role.active = IsHeroPlayerActive(killer.hero);

        if (killer.role.active)
          ++presentTeamActiveMembers;
      }

      {
        HeroVector::const_iterator it = team.begin();
        HeroVector::const_iterator it_end = team.end();
        for (; it != it_end; ++it)
        {
          const CPtr<PFBaseHero> hero(*it);

          if (hero == killer.hero)
            continue;

          Participant& participant = participants.push_back();

          participant.unit = hero.GetPtr();
          participant.hero = hero;

          if (IsLocalHero(hero))
            participant.kind = UnitKind::LocalHero;
          else
            participant.kind = UnitKind::Hero;

          participant.role.assister = (assisters.find(participant.hero) != assisters.end());
          participant.role.spectator = (spectators.find(participant.hero) != spectators.end());
          participant.role.killerTeam = true;
          participant.role.presentTeam = killerTeamPresent;
          participant.role.active = IsHeroPlayerActive(participant.hero);

          if (participant.role.active)
            ++presentTeamActiveMembers;
        }
      }

      if (victim.IsHero())
      {
        MurderContextGuard murderContext(victim.unit.GetPtr());

        murderContext.assisterCount = assisterCount;
        murderContext.spectatorCount = spectatorCount;
        murderContext.presentTeamActiveMembers = presentTeamActiveMembers;

        CalculateAward(killer);

        ParticipantVector::iterator it = participants.begin();
        ParticipantVector::iterator it_end = participants.end();
        for (; it != it_end; ++it)
        {
          CalculateAward(*it);
        }
      }
      else
      {
        CalculateAward(killer);

        if (spectatorCount > 1)
          killer.award.toSpectator /= float(spectatorCount);

        if (presentTeamActiveMembers > 1)
          killer.award.toPresentTeam /= float(presentTeamActiveMembers);
      }
    }

    void Award()
    {
      AwardParticipant(killer, killer.award);

      ParticipantVector::const_iterator it = participants.begin();
      ParticipantVector::const_iterator it_end = participants.end();
      for (; it != it_end; ++it)
      {
        ParticipantVector::const_reference participant = *it;

        if (victim.IsHero())
          AwardParticipant(participant, participant.award);
        else
          AwardParticipant(participant, killer.award);
      }

      if (PlayerBehaviourTracking::ShouldTrackBehaviour(killer.hero))
      {
        if (killer.award.toKiller > 0.f)
          PlayerBehaviourTracking::DispatchEvent(killer.hero, EPlayerBehaviourEvent::GotNaftaForKill);

        if (killer.award.toKillerTeam > 0.f)
          PlayerBehaviourTracking::DispatchEvent(killer.hero, EPlayerBehaviourEvent::ServedTeamNaftaForKill);

        if (killer.award.toPresentTeam > 0.f)
          PlayerBehaviourTracking::DispatchEvent(killer.hero, EPlayerBehaviourEvent::ServedTeamNaftaForPresence);
      }
    }
  private:
    Awarder();

    bool IsLocalHero(const CPtr<PFBaseHero>& pHero) const
    {
      return pHero == GetLocalHero();
    }

    bool IsHeroPlayerActive(const CPtr<PFBaseHero>& pHero) const
    {
      const CPtr<PFPlayer>& player = pHero->GetPlayer();

      if (!IsValid(player))
        return false;

      return
        player->IsBot() ||
        player->IsActive();
    }

    void MakeParticipant(const CPtr<PFBaseUnit>& pUnit, Participant& participant) const
    {
      participant.unit = pUnit;

      if (participant.unit->IsTrueHero())
      {
        participant.hero = AsHero(pUnit);

        if (IsLocalHero(participant.hero))
          participant.kind = UnitKind::LocalHero;
        else
          participant.kind = UnitKind::Hero;
      }
      else if (StatisticsStuff::IsBoss(participant.unit.GetPtr()))
      {
        participant.kind = UnitKind::Boss;
      }
      else if (PFCreature* const creature = dynamic_cast<PFCreature*>(participant.unit.GetPtr()))
      {
        participant.kind = UnitKind::Creep;
      }
      else if (PFTower* const tower = dynamic_cast<PFTower*>(participant.unit.GetPtr()))
      {
        participant.kind = UnitKind::Tower;
      }
      else
      {
        participant.kind = UnitKind::Other;
      }
    }

    void GetNearbyHeroes(const CPtr<PFBaseUnit>& pAggressor, const CVec3& position, const float range, HeroVector& heroes) const
    {
      enum
      {
        UnitTypeMask =
          NDb::SPELLTARGET_HEROMALE |
          NDb::SPELLTARGET_HEROFEMALE |
          NDb::SPELLTARGET_AFFECTMOUNTED |
          NDb::SPELLTARGET_FLYING
      };

      heroes.clear();

      const int factionMask = (1 << pAggressor->GetFaction());

      TrueHeroCollector collector(heroes);
      UnitMaskingPredicate predicate(factionMask, UnitTypeMask);

      aiWorld->ForAllUnitsInRange(position, range, collector, predicate);
    }

    void GetTeamHeroes(const CPtr<PFBaseUnit>& pAggressor, HeroVector& heroes) const
    {
      heroes.clear();

      const int teamId = pAggressor->GetTeamId();

      if (teamId == NCore::ETeam::None)
        return;

      for (int i = 0, count = world->GetPlayersCount(); i < count; ++i)
      {
        PFPlayer* player = world->GetPlayer(i);

        if (player->GetTeamID() != teamId)
          continue;

        PFBaseHero* pHero = player->GetHero();

        if (!IsValid(pHero))
          continue;

        heroes.push_back(pHero);
      }
    }

    void CalculateAward(Participant& participant) const
    {
      if (victim.IsHero() && participant.IsHero() && IsValid(heroNaftaParams))
      {
        GetHeroAward(participant, participant.award);
        return;
      }

      if (victim.IsHero())
        GetDefaultHeroAward(participant.award);
      else
        GetUnitAward(participant.award);
    }

    void GetHeroAward(const Participant& participant, NaftaAward& award) const
    {
      if (participant.role.killer)
        award.toKiller = heroNaftaParams->naftaForKill(participant.hero, victim.hero, &globalConstants);
      else
        award.toKiller = 0.f;

      if (participant.role.assister)
        award.toAssister = heroNaftaParams->naftaForAssist(participant.hero, victim.hero, &globalConstants);
      else
        award.toAssister = 0.f;

      if (participant.role.spectator)
        award.toSpectator = heroNaftaParams->naftaSpecForKill(participant.hero, victim.hero, &globalConstants);
      else
        award.toSpectator = 0.f;

      award.toKillerTeam = victim.unit->GetTeamNaftaForKill();

      if (participant.role.presentTeam)
        award.toPresentTeam = heroNaftaParams->teamNaftaForPresence(participant.hero, victim.hero, &globalConstants);
      else
        award.toPresentTeam = 0.f;

      OverrideAward(award.toKiller, primeSettings.naftaForKill);
      OverrideAward(award.toAssister, primeSettings.naftaForAssist);
      OverrideAward(award.toSpectator, primeSettings.naftaSpecForKill);
      OverrideAward(award.toPresentTeam, primeSettings.teamNaftaForPresence);
    }

    void GetDefaultHeroAward(NaftaAward& award) const
    {
      award.toKiller = victim.hero->GetNaftaForKill();
      award.toAssister = victim.hero->GetNaftaForAssist();
      award.toSpectator = victim.hero->GetNaftaSpecForKill();
      award.toKillerTeam = victim.hero->GetTeamNaftaForKill();
      award.toPresentTeam = victim.hero->GetTeamNaftaForPresence();

      OverrideAward(award.toKiller, primeSettings.naftaForKill);
      OverrideAward(award.toAssister, primeSettings.naftaForAssist);
      OverrideAward(award.toSpectator, primeSettings.naftaSpecForKill);
      OverrideAward(award.toPresentTeam, primeSettings.teamNaftaForPresence);
    }

    void GetUnitAward(NaftaAward& award) const
    {
      award.toKiller = victim.unit->GetNaftaForKill();
      award.toAssister = victim.unit->GetNaftaForAssist();
      award.toSpectator = victim.unit->GetNaftaSpecForKill();
      award.toKillerTeam = victim.unit->GetTeamNaftaForKill();
      award.toPresentTeam = victim.unit->GetTeamNaftaForPresence();

      if (victim.unit->HasBehaviour())
        victim.unit->Behaviour()->GetKillerAward(killer.unit, award);
    }

    float GetHeroLevelDiffCoeff(const int diff, const bool altTable) const
    {
      return aiWorld->GetHeroLevelDiffCoeff(diff, altTable);
    }

    void AwardParticipant(const Participant& participant, const NaftaAward& award)
    {
      if (!participant.IsHero())
        return;

      if (participant.role.victim)
      {
        return;
      }

      if (participant.role.killer)
      {
        CountKill();

        const float multiplier = (1.0f + participant.hero->GetVariable(UnitVariables::szPrimeForKillMultiplier));
        const float bonus = participant.hero->GetVariable(UnitVariables::szLastHitPrimeBonus);
        const float nafta = award.toKiller * multiplier + bonus;

        GiveNafta(participant, nafta, true, localHeroAwards.kill, NaftaSource::NaftaForKill);
      }

      if (participant.role.assister)
      {
        CountAssist(participant);

        const float multiplier = (1.0f + participant.hero->GetVariable(UnitVariables::szPrimeForKillMultiplier));
        const float nafta = award.toAssister * multiplier;

        GiveNafta(participant, nafta, true, localHeroAwards.kill, NaftaSource::NaftaForAssist);
      }

      if (participant.role.spectator)
      {
        float toSpectator = award.toSpectator;

        if (!victim.IsHero())
        {
          if (!primeSettings.multipliers.empty())
          {
            toSpectator *= (primeSettings.multipliers.size() >= spectatorCount)
              ? (primeSettings.multipliers[spectatorCount - 1])
              : (primeSettings.multipliers.back());
          }

          toSpectator *= aiWorld->GetAIParameters().killAwardPartyMultiplier;

          if (specialNeutralAwarding)
          {
            const int victimLevel = victim.unit->GetStatValue(NDb::STAT_LEVEL);
            const int receiverLevel = participant.hero->GetNaftaLevel();

            if (victimLevel > 0)
              toSpectator *= aiWorld->GetHeroLevelDiffCoeff(victimLevel - receiverLevel, true);
          }
        }

        const float multiplier = (1.0f + participant.hero->GetVariable(UnitVariables::szPrimeSpecForKillMultiplier));
        const float nafta = toSpectator * multiplier;

        GiveNafta(participant, nafta, true, localHeroAwards.spectate, NaftaSource::NaftaSpecForKill);
      }

      if (participant.role.killerTeam)
      {
        GiveNafta(participant, award.toKillerTeam, false, localHeroAwards.team, NaftaSource::TeamNaftaForKill);
      }

      if (participant.role.presentTeam && participant.role.active)
      {
        GiveNafta(participant, award.toPresentTeam, false, localHeroAwards.team, NaftaSource::TeamNaftaForPresence);
      }
    }

    void GiveNafta(const Participant& participant, const float nafta, const bool fromVictim, float& localHeroNafta, const NaftaSource::Enum source) const
    {
      if (nafta > 0.f)
      {
        participant.hero->AwardForKill(victim.unit, nafta, fromVictim);

        if (participant.IsLocalHero())
          localHeroNafta += nafta;

        if (g_logNaftaAwards)
        {
          static const char* sourceNames[NaftaSource::COUNT] =
          {
            "NaftaForKill",
            "NaftaForAssist",
            "NaftaSpecForKill",
            "TeamNaftaForKill",
            "TeamNaftaForPresence",
          };

          DebugTrace("+++ player %s awarded with %0.2f [%s]", NStr::ToMBCS(participant.hero->GetPlayerName()), nafta, sourceNames[source]);
        }
      }
    }

    void CountKill()
    {
      if (killer.IsHero())
      {
        killer.hero->OnKill(victim.unit, (killer.award.toKiller > 0.f));

        if (!victim.IsTower())
        {
          if (IsValid(killer.hero->GetHeroStatistics()))
            world->GetStatistics()->AddKill(victim.unit, killer.hero);
        }
      }

      if (victim.IsHero())
      {
        PFBaseUnitHeroKillOrAssistEvent event(killer.unit);
        killer.unit->EventHappened(event);
      }
    }

    void CountAssist(const Participant& participant)
    {
      if (!participant.IsHero())
        return;

      if (victim.IsHero() || victim.IsBoss())
      {
        if (IsValid(participant.hero->GetHeroStatistics()))
          world->GetStatistics()->AddAssist(victim.unit, killer.unit, participant.hero);
      }

      if (victim.IsHero())
      {
        PFBaseUnitHeroKillOrAssistEvent event(participant.unit);
        participant.unit->EventHappened(event);
      }
    }

    const PFWorld* const world;

    const PFAIWorld* const aiWorld;

    const NDb::PrimeSettings& primeSettings;
    const NDb::Ptr<NDb::HeroNaftaParams>& heroNaftaParams;

    GlobalConstantsPars globalConstants;
  };
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::AwardKillers(CPtr<PFBaseUnit> pVictim, CPtr<PFBaseUnit> pKiller) const
{
  NI_ASSERT(IsValid(pKiller), "Killer must be valid");
  NI_ASSERT(IsValid(pVictim), "Victim must be valid");
  NI_ASSERT(NCore::ETeam::Team1 == 0, "Wrong Team1 ID!");
  NI_ASSERT(NCore::ETeam::Team2 == 1, "Wrong Team2 ID!");
  NI_VERIFY(pAILogicParameters, "Invalid AI parameters 'GameLogic/AILogic.AILP'!", return);

  GetKiller(pVictim, pKiller);

  if (pVictim == pKiller)
    return;
  if (pVictim->GetMasterUnit() == pKiller)
    return;

  pKiller->KilledTarget(pVictim);

  Murder::Awarder awarder(this);

  awarder.Prepare(pVictim, pKiller);
  awarder.Award();

  femaleMaleAssistEffect.OnUnitDie(pVictim, pKiller, awarder.assisters);

  const bool logLocalHeroIncome =
    awarder.localHeroAwards.kill > 0.f ||
    awarder.localHeroAwards.spectate > 0.f ||
    awarder.localHeroAwards.team > 0.f;

  if (logLocalHeroIncome)
  {
    LogNaftaIncome(GetLocalHero(), pVictim,
      awarder.localHeroAwards.kill,
      awarder.localHeroAwards.spectate,
      awarder.localHeroAwards.team);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::SendUnitDieNotification(CPtr<PFBaseUnit> pVictim, CPtr<PFBaseUnit> pKiller, PFBaseUnitDamageDesc const* pDamageDesc) const
{
  PFApplDamage const* pDamageApplicator = 0;
  CPtr<PFBaseUnit> pQualifiedKiller = pKiller;
  GetKiller( pVictim, pQualifiedKiller, pDamageApplicator );

  PFBaseUnitEventUnitDeath evt(pVictim, pKiller, pQualifiedKiller);
  for (ring::Range<PFBaseHero::FactionRing> it(heroesOfFactionA); it;)
  {
    PFBaseHero* pHero = &(*it);
    ++it;
    
    if ( pVictim.GetPtr() != pHero )
      pHero->EventHappened(evt);
  }

  for (ring::Range<PFBaseHero::FactionRing> it(heroesOfFactionB); it;)
  {
    PFBaseHero* pHero = &(*it);
    ++it;

    if ( pVictim.GetPtr() != pHero )
      pHero->EventHappened(evt);
  }

  pVictim->EventHappened(evt);

  if ( IsValid(pKiller) && !pKiller->IsTrueHero() )
  {
    pKiller->EventHappened( evt );
  }

  PFScript* pScript = GetWorld()->GetAIContainer()->GetLuaScript();
  if ( pScript )
  {
    DeathParamsInfo deathParamsInfo;

    if ( pDamageApplicator )
    {
      PFAbilityData const* pKillingAbility = pDamageApplicator->GetAbility()->GetData();
      deathParamsInfo.isAutoAttack = pKillingAbility->IsAutoAttack();
      deathParamsInfo.isMelee      = pKillingAbility->IsMelee();
    }
    else if ( pDamageDesc && pDamageDesc->pDealerApplicator && pDamageDesc->pDealerApplicator->GetAbility() )
    {
      PFAbilityData const* pKillingAbility = pDamageDesc->pDealerApplicator->GetAbility()->GetData();
      deathParamsInfo.isAutoAttack = pKillingAbility->IsAutoAttack();
      deathParamsInfo.isMelee      = pKillingAbility->IsMelee();
    }

    CALL_LUA_FUNCTION_ARG4( pScript, "OnUnitDie", false, pVictim->GetWOID()
      , IsValid(pQualifiedKiller) ? pQualifiedKiller->GetWOID() : -1
      , IsValid(pKiller)          ? pKiller->GetWOID()          : -1
      , deathParamsInfo );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::LogNaftaIncome(CPtr<PFBaseHero> pKiller, CPtr<PFBaseUnit> pVictim, float nafta, float naftaSpec, float teamNafta) const
{
  if (!IsValid(pKiller) || !IsValid(pVictim))
    return;

  SessionEventType::EventType   eventType = SessionEventType::EventType(-1);

  if (pVictim->IsHero())
  {
    eventType = SessionEventType::NaftaIncomeFromHero;
  }
  else
  {
    NDb::EUnitType  victimType = pVictim->GetUnitType();

    if (victimType == NDb::UNITTYPE_SUMMON || victimType == NDb::UNITTYPE_CREEP 
      || victimType == NDb::UNITTYPE_SIEGECREEP || victimType == NDb::UNITTYPE_NEUTRALCREEP 
      || victimType == NDb::UNITTYPE_NEUTRALBOSS || victimType == NDb::UNITTYPE_NEUTRALCHAMPION
      || victimType == NDb::UNITTYPE_FACTIONCHAMPION || victimType == NDb::UNITTYPE_DUMMYUNIT)
    {
      eventType = SessionEventType::NaftaIncomeFromCreature;
    }
    else if (victimType == NDb::UNITTYPE_TOWER || victimType == NDb::UNITTYPE_BUILDING 
      || victimType == NDb::UNITTYPE_MAINBUILDING || victimType == NDb::UNITTYPE_SHOP)
    {
      eventType = SessionEventType::NaftaIncomeFromBuilding;
    }
  }

  if (eventType != -1)
  {
    StatisticService::RPC::SessionEventInfo eventParams;

    eventParams.intParam1 = nafta;
    eventParams.intParam2 = naftaSpec;
    eventParams.intParam3 = teamNafta;

    if( eventType == SessionEventType::NaftaIncomeFromCreature )
    {
      if( PFNeutralCreep* creep = dynamic_cast<PFNeutralCreep *>( pVictim.GetPtr() ) )
      {
        if( creep->GetSpawner() )
        {
          eventParams.strParam1 = NStr::ToUnicode( creep->GetSpawner()->GetDBDesc()->GetDBID().GetFormatted() );
          eventParams.strParam2.assign( NStr::StrFmtW(L"x=%d, y=%d", (int)creep->GetSpawner()->GetSpawnPosition().pos.x, (int)creep->GetSpawner()->GetSpawnPosition().pos.y ) );
        }
      }
    }

    pKiller->LogSessionEvent(eventType, eventParams);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFAIWorld::GetMaxHeroLevel() const
{
  return pLevelUps ? max(pLevelUps->developmentPoints.size() - 1, 0) : 0;
}

void PFAIWorld::OnGameFinished( const NDb::EFaction failedFaction )
{
  wasGameFinished = true;

  struct VictoryForCreatures
  {
    NDb::EFaction failedFaction;
    bool heroesMode;

    VictoryForCreatures( const NDb::EFaction _failedFaction ) : failedFaction(_failedFaction), heroesMode(false) { }
    void operator()( PFBaseUnit& unit )
    {
      PFBaseUnit* pUnit = &unit;
      if ( IsValid( pUnit ) && ( heroesMode && pUnit->IsTrueHero() || !heroesMode && !pUnit->IsTrueHero() && !pUnit->IsDead() ) )
      {
        pUnit->OnGameFinished( failedFaction );
      }
    }
  }victoryForCreatures( failedFaction );

  ForAllUnits( victoryForCreatures );

  // ForAllUnits собирает только юнитов присутствующих в VoxelMap, мёртвые герои не обработаются. Так что используем ForAllHeroes.
  victoryForCreatures.heroesMode = true;
  ForAllHeroes( victoryForCreatures, NDb::FACTION_FREEZE );
  ForAllHeroes( victoryForCreatures, NDb::FACTION_BURN );
  
  for( int i = 0; i < votingsForSurrender.size(); ++i )
    votingsForSurrender[i]->Abort();
}

int PFAIWorld::GetHeroDevPoints4Level(int level) const
{
  const int maxLevel = GetMaxHeroLevel();
  if( pLevelUps && 0 < maxLevel )
  {
    NI_VERIFY(0 < level && level <= maxLevel, "Wrong level info requested!", return 0; );
    int res = pLevelUps->developmentPoints[level];
    return res;
  }
  
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFAIWorld::GetHeroLevelDiffCoeff( int difference, bool useAlternateTable ) const
{
  if( pLevelUps )
  {
    int minDiff = 0, maxDiff = 0;
    
    // Default table is used to calc modifiers from level diff of heroes only
    // Alternate table is used to calc modifiers from level diff of hero and neutral creep
    NDb::Ptr<NDb::KillExperienceModifier> pKillExpMod = useAlternateTable ? primeSettings.neutralKillExperienceModifier : pLevelUps->killExperienceModifiers;
    NI_VERIFY( pKillExpMod, "No KillExperienceModifier", return 0.0f );

    vector<NDb::LevelDiffModifier> const& differences = pKillExpMod->levelModifiers;
    for(vector<NDb::LevelDiffModifier>::const_iterator it = differences.begin(), end = differences.end();
      it != end; ++it)
    {
      if (difference == it->difference )
        return it->modifier * 1e-2f;

      minDiff = min(it->difference, minDiff);
      maxDiff = max(it->difference, maxDiff);
    }
    
    NI_VERIFY(difference < minDiff || maxDiff < difference, 
      NStr::StrFmt("No experienve modifier value for difference in levels: %i", difference), 
      return 0.0f; );

    return (difference < minDiff) ? pKillExpMod->otherDifferenceLessCoeff * 1e-2f : pKillExpMod->otherDifferenceGreaterCoeff * 1e-2f;
  }

  return 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::RegisterHero(PFBaseHero* pHero)
{
	PFBaseHero::FactionRing *heroes = const_cast<PFBaseHero::FactionRing*>(GetRingByFaction(pHero->GetFaction()));

  //unregister player
  PFBaseHero::FactionRing::safeRemove(pHero);

	if (heroes)
		heroes->addLast(pHero);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::UnregisterHero(PFBaseHero* pHero)
{
  //unregister player
  PFBaseHero::FactionRing::safeRemove(pHero);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PFCreepSpawner* PFAIWorld::GetSpawner(NDb::EFaction faction, NDb::ERoute routeID) const
{
	// returned spawner of the opposite faction!
	vector<BuildingsRoute>::const_iterator iRoute = FindRoute(faction, routeID);
  if ( iRoute == buildingsRoutes.end() )
    return 0;

  PF_Core::WorldObjectBase* object = pWorld->GetObjectById( iRoute->spawnerObjectID );
  return dynamic_cast<PFCreepSpawner*>( object );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::OnNatureGlyphUsed( NDb::ERoute routeID, const CPtr<PFBaseMaleHero>& pHero )
{
  NI_ASSERT( IsUnitValid(pHero), "Hero is invalid!" );
  NDb::ENatureRoad roadIndex = 
    routeID == NDb::ROUTE_TOP    ? NDb::NATUREROAD_TOP :
    routeID == NDb::ROUTE_CENTER ? NDb::NATUREROAD_CENTER : 
    /*routeID == NDb::ROUTE_BOTTOM ?*/ NDb::NATUREROAD_BOTTOM;
  NDb::EFaction faction = pHero->GetFaction();
  
  ExpandNatureInfoList::iterator iInfo = find( natureGlyphs.begin(), natureGlyphs.end(), pHero );
  NI_ASSERT( iInfo != natureGlyphs.end(), "ExpandNatureInfo not found for that hero!" );

  int expandRation = 3 * pAILogicParameters->expandNatureSegmentRation;
  pWorld->GetNatureMap()->Expand( faction, roadIndex, expandRation );
  
  // destroy all glyphs
  if ( routeID != NDb::NATUREROAD_BOTTOM )
    iInfo->pGlyphBottom->Destroy();
  if ( routeID != NDb::NATUREROAD_CENTER )
    iInfo->pGlyphCenter->Destroy();
  if ( routeID != NDb::NATUREROAD_TOP )
    iInfo->pGlyphTop->Destroy();
  
  natureGlyphs.erase( iInfo );
}

Render::HDRColor const& PFAIWorld::GetTeamColor(NDb::EFaction faction) const
{
  if( pColoringScheme && NDb::FACTION_NEUTRAL != faction)
  {
    return NDb::FACTION_FREEZE == faction ? 
      pColoringScheme->teamA.teamColors[NDb::TEAMCOLORID_TEAM] :
      pColoringScheme->teamB.teamColors[NDb::TEAMCOLORID_TEAM];
  }

  return Render::HDRColor::WHITE();
}

Render::HDRColor const& PFAIWorld::GetHeroColor(NDb::EFaction faction, int id) const
{
  if( pColoringScheme && NDb::FACTION_NEUTRAL != faction )
  {
    vector<Render::HDRColor> const& recolors = NDb::FACTION_FREEZE == faction ? 
      pColoringScheme->teamA.teamColors : pColoringScheme->teamB.teamColors;

    if( 0 < id && id < recolors.size() )
      return recolors[id];

    NI_ALWAYS_ASSERT("Wrong hero id!");
  }

  return Render::HDRColor::WHITE();
}

//===========================================================================================================
const wstring&  PFAIWorld::GetFactionName(NDb::EFaction faction) const
{
  vector<CTextRef> const& teamsNames = GetAIParameters().teamsNames;
  
  const wstring& name = teamsNames[faction].GetText();
  return !name.empty() ? name : NNameMap::wstrNoname;
}

//===========================================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFAIWorld::GetAveragePriestessLvl( NDb::EFaction faction ) const
{
  struct LvlsCounter
  {
    inline LvlsCounter() : lvlSum(0.0f), count(0) {}
    inline void operator()( PFBaseHero const& hero )
    {
      if ( hero.GetUnitType() == NDb::UNITTYPE_HEROFEMALE )
      {
        count += 1;
        lvlSum += static_cast<float>( hero.GetNaftaLevel() );
      }
    }
    float lvlSum;
    int   count;
  } counter;
  ForAllHeroes( counter, faction );
  
  if ( counter.count )
    return ceil(counter.lvlSum / static_cast<float>( counter.count ) );
  else
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::SetMapData( NDb::AdvMapDescription const * advMapDescription, NDb::AdvMapSettings const * advMapSettings)
{
  if ( g_battleStartDelay >= 0 )
    battleStartDelay = g_battleStartDelay;
  else
    battleStartDelay = advMapSettings->battleStartDelay;

  towersVulnerabilityDelay = advMapSettings->towersVulnerabilityDelay;

  primeSettings = advMapSettings->primeSettings;
  heroNaftaParams = primeSettings.heroNaftaParams;
  heroNaftaParams.Load();
  isTutorial = ( advMapDescription->mapType == NDb::MAPTYPE_TUTORIAL );

  creepAnnounceList = advMapSettings->creepAnnounceList;

  if ( advMapSettings->overridePortalTalent )
    portalTalent = advMapSettings->overridePortalTalent;
  else 
    portalTalent = GetAIParameters().portal;

  if ( advMapSettings->heroRespawnParams )
    pHeroRespawnParams = advMapSettings->heroRespawnParams;
  else
    pHeroRespawnParams = GetAIParameters().heroRespawnParams;
  NI_DATA_ASSERT( pHeroRespawnParams, "No HeroRespawnParams!" );

  pGlyphsManager->Init( advMapSettings->overrideGlyphSettings );

#ifndef _SHIPPING
  mapForce = advMapSettings->force; // used for cheat only
#endif // _SHIPPING

  canUseSkins = advMapDescription->canUseSkins;
   
  creepLevelCap = advMapSettings->creepLevelCap;
  if ( creepLevelCap < 0 )
    creepLevelCap = GetAIParameters().creepLevelCap;

  for( int i = 0; i < votingsForSurrender.size(); ++i )
    votingsForSurrender[i]->InitPerMissionData( advMapSettings->votingForSurrender );
}

bool PFAIWorld::IsNeutralCreepInAnnounceList( PFBaseCreep const* pCreep ) const
{
  if ( !IsValid( pCreep ) || !pCreep->GetSpawnerDBID() || !creepAnnounceList )
    return false;

  NDb::DBID const& neutralCreepDBID = pCreep->DbUnitDesc()->GetDBID();
  NDb::DBID const& spawnerDBID = *pCreep->GetSpawnerDBID();

  vector<NDb::CreepAnnounce> const& announceList = creepAnnounceList->list;
  for ( int i = 0; i < announceList.size(); i++ )
  {
    NDb::CreepAnnounce const& announce = announceList[i];
    if ( announce.spawner && announce.spawner->GetDBID() == spawnerDBID )
    {
      vector<NDb::Ptr<NDb::AdvMapCreep>> const& creepList = announce.creeps;
      for ( int ci = 0; ci < creepList.size(); ci++ )
      {
        if ( creepList[ci] && creepList[ci]->GetDBID() == neutralCreepDBID )
        {
          return true;
        }
      }
    }
  }
  return false;
}

void PFAIWorld::ClearVoxelMap()
{
	Clear(heroesOfFactionA);
	Clear(heroesOfFactionB);
	PFVoxelMap::OnDestroyContents();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFAIWorld::VotingForSurrenderStart( CPtr<PFPlayer> pPlayer )
{
  if( !IsValid(pPlayer) )
    return;
    
  const int team = pPlayer->GetTeamID();
  
  NI_ASSERT( team >= 0 && team < votingsForSurrender.size(), "" );   
  votingsForSurrender[team]->Start(pPlayer);  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFAIWorld::VotingForSurrenderMakeDecision( CPtr<PFPlayer> pPlayer, bool vote )
{
  if( !IsValid(pPlayer) )
    return;
    
  const int team = pPlayer->GetTeamID();
    
  typedef AIWorldFacets::VotingForSurrenderLogic VFS;
  
  NI_ASSERT( team >= 0 && team < votingsForSurrender.size(), "" ); 
  votingsForSurrender[team]->MakeDecision( pPlayer, vote ? VFS::VotedForSurrender : VFS::VotedForFight );  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AIWorldFacets::VotingForSurrenderLogic * PFAIWorld::GetVotingForSurrender( int teamId )
{
   NI_ASSERT( teamId >= 0 && teamId < votingsForSurrender.size(), "" );
   return &*votingsForSurrender[teamId];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::ApplyForceModifiers( float forceOfMap, float _trainingForceCoeff, NDb::EMapType _mapType, PFBaseHero* _trainingHero )
{
#ifndef _SHIPPING
  trainingForceCoeff = _trainingForceCoeff;
  trainingHero = _trainingHero;
  mapType = _mapType;
#endif
  // Calculate stats modifier for buildings and creeps
  CalculateStatsCoeffFromForce( forceOfMap, _trainingForceCoeff, _mapType, _trainingHero );
  UpdateUnitsStatsFromForce(); 

  if ( _mapType == NDb::MAPTYPE_TRAINING || _mapType == NDb::MAPTYPE_SERIES )
  {
    UpdateBotsStats( _trainingHero->GetOppositeFaction() );
    UpdateBotsStats( _trainingHero->GetFaction() );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING
void PFAIWorld::ApplyForceModifiersCheat()
{
  ApplyForceModifiers( mapForce, trainingForceCoeff, mapType, trainingHero );
}
#endif //_SHIPPING
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::CalculateStatsCoeffFromForce( float forceOfMap, float _trainingForceCoeff, NDb::EMapType _mapType, PFBaseHero* _trainingHero )
{
  NI_DATA_VERIFY( !GetAIParameters().forceParameters.IsEmpty(), "forceParameters is empty", return );

  // Считаем обычный пвп-шный коэффициент на статы
  Force::MapStatsCoeffCalculator statsCoeffCalculator( GetAIParameters().forceParameters, forceOfMap, _mapType == NDb::MAPTYPE_TRAINING );
  ForAllHeroes( statsCoeffCalculator, NDb::FACTION_BURN );
  ForAllHeroes( statsCoeffCalculator, NDb::FACTION_FREEZE );
  float statsCoeffFromForce = statsCoeffCalculator.GetResult();

  switch( _mapType )
  {
  case NDb::MAPTYPE_TRAINING:
    {
      float forceCoeff = statsCoeffCalculator.GetForce() / ( forceOfMap * _trainingForceCoeff ) - 1.0f;
      float botsStatsCoeff = 1.0f + forceCoeff * GetAIParameters().forceParameters->trainingBotsStatsMultiplier;
      statsCoeffs.coeffsByFaction[0] = statsCoeffFromForce;
      statsCoeffs.coeffsByFaction[1] = statsCoeffFromForce;
      statsCoeffs.coeffsByFaction[2] = statsCoeffFromForce;
      statsCoeffs.botsCoeffsByFaction[0] = botsStatsCoeff;
      statsCoeffs.botsCoeffsByFaction[1] = botsStatsCoeff;
      statsCoeffs.botsCoeffsByFaction[2] = botsStatsCoeff;
      DebugTrace( "Map StatsCoeff = %.3f", statsCoeffFromForce );
      DebugTrace( "Map Bots StatsCoeff = %.3f", botsStatsCoeff );
      break;
    }
  case NDb::MAPTYPE_SERIES:
    {
      // Don't count persistent stats in hero force
      float forceCoeff = _trainingHero->GetForce( false ) / forceOfMap - 1.0f;
      float statsCoeff = 1.0f + forceCoeff * GetAIParameters().forceParameters->seriesMapHabitantsStatsMultiplier;
      statsCoeffs.coeffsByFaction[0] = statsCoeff;
      statsCoeffs.coeffsByFaction[1] = statsCoeff;
      statsCoeffs.coeffsByFaction[2] = statsCoeff;
      statsCoeffs.botsCoeffsByFaction[0] = statsCoeff;
      statsCoeffs.botsCoeffsByFaction[1] = statsCoeff;
      statsCoeffs.botsCoeffsByFaction[2] = statsCoeff;
      DebugTrace( "Map StatsCoeff = %.3f", statsCoeff );
      break;
    }
  case NDb::MAPTYPE_COOPERATIVE:
    {
      float forceCoeff = 1.0f + ( 125 / forceOfMap - 1.0f ); // 125 - Must get rid of magic numbers
      statsCoeffs.coeffsByFaction[0] = forceCoeff;
      statsCoeffs.coeffsByFaction[1] = forceCoeff;
      statsCoeffs.coeffsByFaction[2] = forceCoeff;
      DebugTrace( "Map StatsCoeff = %.3f (fixed)", forceCoeff );
      break;
    }

  default:
    {
      statsCoeffs.coeffsByFaction[0] = statsCoeffFromForce;
      statsCoeffs.coeffsByFaction[1] = statsCoeffFromForce;
      statsCoeffs.coeffsByFaction[2] = statsCoeffFromForce;
      DebugTrace( "Map StatsCoeffFromForce = %.3f", statsCoeffFromForce );

      break;
    }
  }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIWorld::UpdateUnitsStatsFromForce()
{
  int unitFlags = NDb::SPELLTARGET_TOWER | NDb::SPELLTARGET_BUILDING | NDb::SPELLTARGET_MAINBUILDING 
    | NDb::SPELLTARGET_NEUTRALBOSS | NDb::SPELLTARGET_NEUTRALCHAMPION | NDb::SPELLTARGET_NEUTRALCREEP
    | NDb::SPELLTARGET_CREEP | NDb::SPELLTARGET_SIEGECREEP | NDb::SPELLTARGET_FACTIONCHAMPION;

  struct UnitsStatsUpdater
  {
    UnitsStatsUpdater( int unitFlag_ ) : unitFlag(unitFlag_) {}
    void operator()(PFLogicObject& object)
    {
      if ( ( (1 << object.GetUnitType()) & unitFlag ) != 0 )
      {
        PFBaseUnit* pUnit = dynamic_cast<PFBaseUnit*>(&object);

        if ( !pUnit )
          return;

        if (pUnit->GetTypeId() == PFNeutralCreep::typeId)
        {
          PFNeutralCreep* const creep = static_cast<PFNeutralCreep*>(pUnit);
          PFNeutralCreepSpawner* const spawner = creep->GetSpawner();

          if (spawner)
            creep->ModifyStatsByForce(spawner->GetMapForceStatModifierApplication());
          else
            creep->ModifyStatsByForce();
        }
        else
        {
          pUnit->ModifyStatsByForce();
        }
      }
    }
    int unitFlag;
  } unitsStatsUpdater( unitFlags );

  ForAllUnits(unitsStatsUpdater);
}

void PFAIWorld::UpdateBotsStats( NDb::EFaction faction )
{
  vector<NDb::StatBudget> const& vecStatBudgets = GetWorld()->GetAIWorld()->GetAIParameters().statsBudget->stats;

  struct HeroesStatsModifierer : NonCopyable
  {
    HeroesStatsModifierer( float statMultiplier, vector<NDb::StatBudget> const& vecStatBudgets ) 
      : statMultiplier(statMultiplier), vecStatBudgets(vecStatBudgets) {}
    void operator()( PFBaseHero& hero )
    {
      if ( !hero.GetPlayer() || !hero.GetPlayer()->IsBot() )
        return;

      for ( vector<NDb::StatBudget>::const_iterator itStatBudget = vecStatBudgets.begin(); itStatBudget != vecStatBudgets.end(); ++itStatBudget )
      {
        if ( !itStatBudget->upgradesWithForce )
          continue;

        NDb::EStat stat = itStatBudget->stat;

        StatValueWithModifiers* vwmStat = hero.GetStat( stat );
        if (vwmStat)
        {
          vwmStat->AddModifier( statMultiplier, 0.0f, PF_Core::FORCE_CHEAT_ID );
        }
      }
    }
    const float statMultiplier;
    vector<NDb::StatBudget> const& vecStatBudgets;
  } heroesStatsModifierer( statsCoeffs.botsCoeffsByFaction[faction], vecStatBudgets );

  ForAllHeroes( heroesStatsModifierer, faction );
}



int PFAIWorld::GetSurrenderVotes( NDb::EFaction _failedFaction ) const
{
  for ( int i = 0; i < votingsForSurrender.size(); ++i )
  {
    NDb::EFaction fact = TeamIdToFaction( votingsForSurrender[i]->GetTeam() );
    if ( fact == _failedFaction )
      return votingsForSurrender[i]->GetSurrenderVotes();
  }
  
  NI_ASSERT( false, "VotingForSurenders hasn't been found" );
  return 0;
}

void PFAIWorld::CollectFlagpoles( vector<PFFlagpole*>* pFlagpoles ) const
{
  PFRoadFlagpole::PushAll( pFlagpoles );
  PFScriptedFlagpole::PushAll( pFlagpoles );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitMaskingPredicate::UnitMaskingPredicate(PFBaseUnit * _pOwner, NDb::ESpellTarget targetFilter)
{
	factionMask  = MakeSpellTargetFactionFlags(*_pOwner, targetFilter);
	unitTypeMask = targetFilter;
  pOwner       = _pOwner;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UnitMaskingPredicate::operator()(const PFLogicObject &obj) const
{
  NI_PROFILE_FUNCTION

	// check mounted constraint
	if ( (unitTypeMask & NDb::SPELLTARGET_AFFECTMOUNTED) == 0 && obj.IsMounted() )
		return false;

	// check self constraint
	if (&obj == pOwner)
		return (unitTypeMask & NDb::SPELLTARGET_SELF) != 0;

  if ((unitTypeMask & NDb::SPELLTARGET_VULNERABLETARGETSONLY) != 0 && !obj.IsVulnerable() )
    return false;

  if ( obj.IsFlying() && ( unitTypeMask & NDb::SPELLTARGET_FLYING ) == 0 )
    return false;

  // check faction & unit type
  if ( (factionMask & (1 << obj.GetFaction())) == 0 || 
       (unitTypeMask & (1L << obj.GetUnitType())) == 0 )
       return false;

  if ((unitTypeMask & NDb::SPELLTARGET_VISIBLETARGETSONLY) != 0 && IsValid(pOwner) && 
    (pOwner->GetFaction() != obj.GetFaction()) && !obj.IsVisibleForEnemy( pOwner->GetFaction() ) )
    return false;

  if ((unitTypeMask & NDb::SPELLTARGET_LINEOFSIGHT)!=0 && IsValid(pOwner) && !pOwner->CanSee(obj))
    return false;

  
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitsCollector::operator()(PFBaseUnit &unit)
{
  if (!unit.IsDead())
    result.push_back(&unit);
}

UnitsCollector::UnitsCollector(PFAIWorld::Units &_result) : result(_result) 
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma code_seg(push, "~")

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFAIWorld::PFAIWorld( PFWorld * _world ) 
: PFVoxelMap( _world )
, pWorld( _world )
, maxVisibilityRange( 40.0f )
, maxObjectSize( 1.0f )
, battleStartDelay( 0 )
, towersVulnerabilityDelay( 0 )
, wasGameFinished( false )
, spawnCreeps( true )
, spawnNeutralCreeps( true )
, isTutorial(false)
, canUseSkins(true)
, creepLevelupPaused(false)
{
  STARFORCE_STOPWATCH();

  NI_PROFILE_FUNCTION

    NDb::Ptr<NDb::SessionRoot> pRoot = NDb::SessionRoot::GetRoot();

  pUnitLogicParameters = pRoot->logicRoot->unitLogicParameters;
  NI_VERIFY(pUnitLogicParameters, "Game logic DB should present", return; );
  NI_ASSERT(pUnitLogicParameters->unitParameters.size() == NDb::KnownEnum<NDb::EUnitType>::SizeOf(),
    NStr::StrFmt( "Missing parameters for some unit types: have parameters: %d, unit types count: %d", pUnitLogicParameters->unitParameters.size(), NDb::KnownEnum<NDb::EUnitType>::SizeOf()));

  pAILogicParameters = pRoot->logicRoot->aiLogic;
  NI_VERIFY(pAILogicParameters, "AI logic DB should present", return; );

  if ( pWorld->GetIAdventureScreen() )
    pWorld->GetIAdventureScreen()->PreloadEffectsInResourceTree(pRoot->logicRoot->aiLogic, REVIVENODE);

  pLevelUps = pRoot->logicRoot->heroesLevelups;
  NI_VERIFY(pLevelUps, "Levelup info must present!", return; );

  pDefaultFormulasCache = pRoot->logicRoot->defaultFormulas;

  pColoringScheme = pRoot->visualRoot->teamColoringScheme;
  pGlyphsManager  = new PFGlyphsManager(pWorld);

  for( int i = 0; i < NCore::ETeam::COUNT; ++i )
    votingsForSurrender.push_back( new AIWorldFacets::VotingForSurrenderLogic( _world, static_cast<NCore::ETeam::Enum>(i), UI::GetUIRoot()->votingForSurrender) );
}

#pragma code_seg(pop)

} // namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFAIWorld, NWorld);
REGISTER_DEV_VAR( "battle_start_delay", g_battleStartDelay, STORAGE_NONE );


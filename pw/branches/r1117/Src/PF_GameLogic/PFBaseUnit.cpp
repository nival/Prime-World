#include "stdafx.h"

#include "PFBaseUnit.h"
#include "PFApplInstant.h"
#include "WarFog.h"
#include "PFApplicator.h"
#include "PFTalent.h"
#include "PFBaseAttackData.h"
//#include "PFBaseUnitEvent.h"

//#include "PFFsm.h"


#include "PFUniTarget.h"

#include "PFGameLogicDebugVisual.h"
#include "PFGameLogicLog.h"
#include "PFLogicDebug.h"
#include "PFStatistics.h"
#include "PFSummoned.h"
#include "PFApplChannelling.h"
#include "PFApplAura.h"
#include "TileMap.h"
#include "PathMap.h"
#include "../System/InlineProfiler.h"

#include "DerStatsNameMap.h"

#ifndef VISUAL_CUTTED
#include "PFClientCreature.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

#include "PFBuildings.h"

#include "PFPredefinedUnitVariables.h"
#include "Scripts/lua.hpp"
#include "LuaScript.h"

#include "PFClientVisibilityMap.h"


#define GameLogicLogger ( NLogg::StreamBuffer( GetGameLogicLog(), NLogg::SEntryInfo( NLogg::LEVEL_MESSAGE, "", 1 ) ) )

namespace
{
  static bool g_bUseTestFindTargetMode = false;
  static bool g_bDebugNoDamage         = false;
  static bool g_showVisibilityRange    = false;
  static bool g_showAttackRange        = false;
  static bool g_showTargetRange        = false;
  static bool g_showTarget             = false;
  static bool g_immortalHeroes         = false;
  static bool g_debugTargetting        = false;
  static bool g_debugHeroAIStates      = false;
  static bool g_debugPrintHeroAIStates = false;
  static bool g_showLeashRange         = false;

#define DEBUG_TARGETTING(msg) if (g_debugTargetting) { DebugTrace( "DT-%d-%d:%s", GetObjectId(), (IsValid(pWorld))?(pWorld->GetStepNumber()):(0), msg ); }

  static const Render::Color g_visibilityRangeColor(0, 192, 0);
  static const Render::Color g_attackRangeColor(192, 0, 0);
  static const Render::Color g_targetRangeColor(192, 192, 0);
  static const Render::Color g_leashRangeColor(72, 61, 139);

  struct AbilityBoolFormulaVariant : public NNameMap::Variant, NonCopyable
  {
    AbilityBoolFormulaVariant(const NWorld::PFBaseUnit * _unit, ExecutableBoolString const& formula) 
      : unit(_unit) 
      , formula(formula) 
    {}

    virtual bool GetBool() const
    {
      return formula( unit, unit, 0, 0.0f );
    }

    virtual NNameMap::VariantType::Enum GetType() const { return NNameMap::VariantType::Bool; }
    virtual bool IsReadonly() const                     { return true; }

  private:
    ConstPtr<NWorld::PFBaseUnit> unit;
    ExecutableBoolString const& formula;
  };

  inline int GetSectorIndex(int i, int max)
  {
    return (i >= 0) ? (i % max) : (max + i % max);
  }
}

namespace NWorld
{

LUA_VALUE_SETTABLE_BEGIN(DeathParamsInfo, 2)
  LUA_VALUE_SETTABLE_PROPERTY( isAutoAttack )
  LUA_VALUE_SETTABLE_PROPERTY( isMelee )
LUA_VALUE_SETTABLE_END


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UnsummonCriterion::operator()( PFSummonBehaviour* pFirst, PFSummonBehaviour* pSecond )
{
  CPtr<PFBaseMovingUnit> const &pFirstUnit = pFirst->GetUnit();
  CPtr<PFBaseMovingUnit> const &pSecondUnit = pSecond->GetUnit();
  const float first = (*criterionFormula)( pOwner, pFirstUnit, pMisc );
  const float second = (*criterionFormula)( pOwner, pSecondUnit, pMisc );
  return first < second;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN(PFBaseUnit)
  NAMEMAP_VAR_RO(health)
  NAMEMAP_VAR_RO(energy)
  NAMEMAP_VAR_RO(gold)
  NAMEMAP_VAR_RO(maxHealth)
  NAMEMAP_VAR_RO(maxEnergy)
  NAMEMAP_FUNC_RO(name, &PFBaseUnit::GetDescription )
  NAMEMAP_FUNC_RO(teamName,  &PFBaseUnit::GetFactionName)
  NAMEMAP_SUBMAP(stats)
  NAMEMAP_SUBMAP(derStats)
  NAMEMAP_CUSTOM_VARIANT( lvl, NNameMap::CreateVariableVariant(naftaLevel, true), true)
  NAMEMAP_CUSTOM_SUBMAP(if, &condsResolver, &condsResolver)
NAMEMAP_END

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PFBaseUnit::AttackDataHelper
{
  static inline void SetAttackData(PFBaseUnit::AttackData& attackData, const CPtr<PFBaseUnit>& victim, const bool byAutoAttack, const NDb::EFaction originalFaction)
  {
    attackData.pVictim = victim;
    attackData.byAutoAttack = byAutoAttack;
    attackData.timePassed = 0.f;
    attackData.originalFaction = originalFaction;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseUnit::PFBaseUnit( PFWorld * _pWorld, const CVec3 &pos, const NDb::Unit * _dbUnitDesc )
  : PFLogicObject( _pWorld, pos, _dbUnitDesc )
  , dbUnitDesc( _dbUnitDesc )
  , pAttackAbility(NULL)
  , stats(new PFStatContainer( _pWorld ))
  , forbidFlags(NDb::KnownEnum<NDb::EUnitFlagType>::SizeOf(), 0)
  , bStrongTarget(false)
  , pCurrentTarget(NULL)
  , naftaLevel(0)
  , timeSinceLevelUp(-1.0f)
  , energy(0.0f)
  , targetRevisionTime(0.0f)
  , pMaster(NULL)
  , visibleForEnemy(true)
  , visibleForNeutral(true)
  , description()
  , gold(1e-3f)
  , canApplyDispatch(true)
  , isDumpStates(false)
  , isInCombat(false)
  , shouldRestoreStatusEffects(false)
  , shouldRestoreSceneObject(false)
  , sleepDelay(2.0f)
  , bSleep(false)
  , isInTaunt(false)
  , murderContext(0)
  , shield(0.f)
  , invalidAbilityTargetCounter(0U)
{
  if ( _dbUnitDesc && _dbUnitDesc->attackAbility )
    pAttackAbility = new PFBaseAttackData( CPtr<PFBaseUnit>(this), _dbUnitDesc->attackAbility );

  derivativeStatsContainer = _pWorld->GetAIWorld()->GetAIParameters().derivativeStats;

  summonedUnits[NDb::SUMMONTYPE_PRIMARY]   = new PFBehaviourGroup( _pWorld );
  summonedUnits[NDb::SUMMONTYPE_SECONDARY] = new PFBehaviourGroup( _pWorld );
  summonedUnits[NDb::SUMMONTYPE_PET]       = new PFBehaviourGroup( _pWorld );

  CreateAbilities(this, *dbUnitDesc);

  const float tileSize = _pWorld->GetTileMap()->GetTileSize();

  int sizeInTiles = dbUnitDesc.IsEmpty() ? 1 : ceil( dbUnitDesc->size / tileSize );
  int sizeDynamicInTiles = dbUnitDesc.IsEmpty() ? -1 : ceil( dbUnitDesc->sizeDynamic / tileSize );
  if ( sizeDynamicInTiles < 0 )
    sizeDynamicInTiles = sizeInTiles;
  float objectSize     = sizeInTiles * tileSize; // rounded up to tile size

  SetObjectSizes(objectSize, sizeInTiles, sizeDynamicInTiles);

  derStats = new NGameX::DerStatsNameMap(this);
  condsResolver.Init(this);

  attackSectorsCount = max( GetObjectSize() * FP_2PI / 2.0f, 3 ); // 3 sectors minimum
  InitAttackSectors(attackSectorsCount);

  visUnitData.resize( NDb::KnownEnum<NDb::EFaction>::SizeOf() );

  baseUnitTargetingParams = dbUnitDesc->targetingParams;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseUnit::PFBaseUnit()
: isDumpStates(false)
, murderContext(0)
, shield(0.f)
, invalidAbilityTargetCounter(0U)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseUnit::WarFogData::WarFogData() : warFogObjectID(WAR_FOG_BAD_ID), timeOut(0.0f), visRadius(0.0f)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::WarFogData::Clear()
{
  warFogObjectID = WAR_FOG_BAD_ID; timeOut = -1.0f; visRadius = 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::OccupyAttackSector(CPtr<PFBaseMovingUnit> const & attacker)
{
  if (!IsValid(attacker))
    return -1;

  CVec2 prefferedDir = attacker->GetPosition().AsVec2D() - GetPosition().AsVec2D();
  Normalize(&prefferedDir);
  float prefferedDirAngle = acos(prefferedDir.x);
  if (prefferedDir.y < 0) prefferedDirAngle = FP_2PI - prefferedDirAngle;
  int sector = floor(0.5f + prefferedDirAngle / attackSectorsAngle);
  int maxSectorsSearch = attackSectorsCount / 2;
  int sectorShift = (prefferedDirAngle - sector * attackSectorsAngle > 0) ? (1) : (-1);
  int mostFreeSector = GetSectorIndex(sector, attackSectorsCount);
  int i;

  for (i = 0; i <= maxSectorsSearch; ++i, sectorShift *= -1)
  {
    int shiftedIndex = sector + ((i+1)/2)*sectorShift;
    int sectorIndex = GetSectorIndex(shiftedIndex, attackSectorsCount);

    if (attackSectors[sectorIndex].attackers == 0)
    {
      ++attackSectors[sectorIndex].attackers;
      sector = sectorIndex;
      break;
    }
    else
    {
      if (attackSectors[sectorIndex].attackers < attackSectors[mostFreeSector].attackers)
      {
        mostFreeSector = sectorIndex;
      }
    }
  }

  if (i > maxSectorsSearch)
  {
    sector = mostFreeSector;
    ++attackSectors[sector].attackers;
  }

  return sector;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ReleaseAttackSector(int sector)
{
  if (sector >= 0 && sector < attackSectors.size() && attackSectors[sector].attackers != 0)
    --attackSectors[sector].attackers;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ClearAttackSectors()
{
  for (int i = 0, max = attackSectors.size(); i < max; ++i)
  {
    attackSectors[i].attackers = 0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 PFBaseUnit::GetAttackSectorDir(int sector) const
{
  if (sector >= 0 && sector < attackSectors.size())
    return attackSectors[sector].direction;

  return VNULL2;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec2 PFBaseUnit::GetAttackSectorOffset(CPtr<PFBaseMovingUnit> const & attacker, int sector) const
{
  if (sector >= 0 && sector < attackSectors.size() && IsValid(attacker))
  {
    return attackSectors[sector].direction * (attacker->GetObjectSize()/2.0f + GetObjectSize()/2.0f);
  }

  return VNULL2;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::InitAttackSectors(int count)
{
  if (count <= 0)
    return;

  attackSectors.resize(count);

  attackSectorsAngle = FP_2PI / count;

  for (int i = 0; i < count; ++i)
  {
    float sectorAngle = (float)i * attackSectorsAngle;

    attackSectors[i].attackers = 0;
    attackSectors[i].direction.x = cos(sectorAngle);
    attackSectors[i].direction.y = sin(sectorAngle);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::GetAttackSectorOccupies(int sector) const
{
  if (sector >= 0 && sector < attackSectors.size())
    return attackSectors[sector].attackers;

  return 0;
}

int PFBaseUnit::GetMaxAllowedSummons( NDb::SummonType type, const string& summonGroupName ) const
{
  map<string, int>::const_iterator it = maxAllowedSummons[type].find( summonGroupName );
  if ( it != maxAllowedSummons[type].end() )
    return it->second;

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::RemoveSummons( const int unsummonCount, const NDb::SummonType type /* = NDb::SUMMONTYPE_PRIMARY */, const string& summonGroupName
                              , const NDb::Creature* pDBUnit /*= 0*/, const int maxCount /*= 0*/, UnsummonCriterion* pUnsummonCriterion /*= 0*/ )
{
  typedef nstl::vector<PFSummonBehaviour*> SummonBehaviours;
  SummonBehaviours summons;

  struct AddFunc : NonCopyable
  {
    SummonBehaviours* pSummons;
    NDb::DBID const* dbid;
    const string& summonGroupName;

    AddFunc( SummonBehaviours* _pSummons, const string& _summonGroupName, NDb::DBID const* _dbid ) : pSummons(_pSummons), summonGroupName(_summonGroupName), dbid(_dbid) {}

    void operator()( PFSummonBehaviour* pBehaviour ) 
    {
      if ( summonGroupName == pBehaviour->GetGroupName() && ( !dbid || pBehaviour->GetUnit()->DbUnitDesc()->GetDBID() == *dbid ) )
        pSummons->push_back( pBehaviour );
    }
  } add( &summons, summonGroupName, pDBUnit ? &pDBUnit->GetDBID() : 0 );

  summonedUnits[type]->ForAllBehaviour( add );

  struct HealthComp
  {
    bool operator()( PFSummonBehaviour* pFirst, PFSummonBehaviour* pSecond )
    {
      // it is supposed that all compared summons have the same unsummon sorting params, otherwise it has little sense
      if ( pFirst->IsHealthPriority() && pSecond->IsHealthPriority() )
      {
        CPtr<PFBaseMovingUnit> const &pFirstUnit = pFirst->GetUnit();
        CPtr<PFBaseMovingUnit> const &pSecondUnit = pSecond->GetUnit();
        const float firstHealth = pFirstUnit->GetHealth() / pFirstUnit->GetMaxHealth();
        const float secondHealth = pSecondUnit->GetHealth() / pSecondUnit->GetMaxHealth();

        if ( firstHealth < secondHealth )
        {
          return true;
        }
        if ( firstHealth > secondHealth )
        {
          return false;
        }
      }

      return pFirst->GetLifeTime() > pSecond->GetLifeTime();
    }
  } comp;

  int totalCount = summons.size();

  if ( totalCount > 0 )
  {
    int count = maxCount > 0 ? max( 0, totalCount - maxCount + unsummonCount ) : unsummonCount;

    if ( count == 0 )
      return 0;

    NI_VERIFY( count <= totalCount, NStr::StrFmt("Can't remove more summons (%d) that actually are (%d)!", count, totalCount ), return 0 );

    if ( pUnsummonCriterion )
      nstl::sort( summons.begin(), summons.end(), *pUnsummonCriterion );
    else
      nstl::sort( summons.begin(), summons.end(), comp );

    for( int i = 0; i < count; i++ )
    {
      summons[i]->Unsummon();
    }

    return count;
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFBaseUnit::OnDestroyContents()
{
  DestroyAbilities();
  CleanupHistoryApplicators(); // „иним асинк NUM_TASK
  PFLogicObject::OnDestroyContents();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnDie()
{
  PFFsm::Cleanup();

  CleanupAfterDeath(true);

	eventListeners.clear();

  variablesRing.clear(ring::DeleteEraser<Variable>());

	RemoveBehaviour();

#ifndef _SHIPPING
  debugObject = 0;
#endif

  PFLogicObject::OnDie();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::InitializeLifeEnergy()
{
	maxHealth = GetStatValue(NDb::STAT_LIFE);
	maxEnergy = GetStatValue(NDb::STAT_ENERGY);

  health = maxHealth;
  energy = maxEnergy;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RegisterInAIWorld()
{
  NI_ASSERT(GetWorld()->GetAIWorld(), "No AI world!");
  GetWorld()->GetAIWorld()->RegisterUnit(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetAttackSpeedInternal() const
{
  return pAttackAbility ? pAttackAbility->GetSpeed() : 0.0f;
}

//////////////////////////////////////////////////////////////////////////
const NDb::UnitTargetingParameters& PFBaseUnit::GetTargetingParams() const
{
  return *GetTargetingParamsPtr(); 
}

const NDb::UnitTargetingParameters* PFBaseUnit::GetTargetingParamsPtr() const
{
  const NDb::UnitTargetingParameters* params = unitTargetingParams ? unitTargetingParams : dbUnitDesc->targetingParams.GetPtr();
  if ( params == NULL )
  {
    NI_ASSERT(GetWorld() && GetWorld()->GetAIWorld(), "Invalid world");
    params = GetWorld()->GetAIWorld()->GetUnitParameters( GetUnitType() ).targetingPars;
    NI_ASSERT(params != NULL, "Shoult be default params");
  }
  return params; 
}

//////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::HasAtackAbility() const
{
  return pAttackAbility ? true : false;
}



NDb::EApplicatorDamageType PFBaseUnit::GetBaseAttackDamageType() const
{
  return pAttackAbility ? pAttackAbility->GetDamageType() : NDb::APPLICATORDAMAGETYPE_MANA;
}


void PFBaseUnit::InitBaseAttack()
{
  if (pAttackAbility)
    pAttackAbility->LevelUp();
}


void PFBaseUnit::Initialize(InitData const& data)
{
  NI_PROFILE_FUNCTION

  NI_VERIFY( data.pObjectDesc, "Unable to initialize unit", return; );
  NDb::Ptr<NDb::Unit> pUnitDesc = dynamic_cast<NDb::Unit const*>( data.pObjectDesc );
  NI_DATA_VERIFY( pUnitDesc, NStr::StrFmt( "Object \"%s\" is not NDb::Unit", NDb::GetFormattedDbId( pUnitDesc->GetDBID() ).c_str() ), return; );
  NI_DATA_ASSERT( pUnitDesc->stats, NStr::StrFmt( "Unit \"%s\" has no stats", NDb::GetFormattedDbId( pUnitDesc->GetDBID() ).c_str() ) );
  NDb::AILogicParameters const& dbAILogicParams = GetWorld()->GetAIWorld()->GetAIParameters();
  stats->Load( pUnitDesc->stats, GetWorld()->GetAIWorld()->GetUnitParameters( data.type ).defaultStats, dbAILogicParams.globalConstants );

  PFLogicObject::Initialize( data );

	InitializeLifeEnergy();
  
  OpenWarFog();

  description       = pUnitDesc->description.GetText();
  pImage            = pUnitDesc->image;

  // precache
  if ( pImage )
  {
    CObj<Render::Texture> texture = pImage->Load();
    texture = 0;
  }

#ifndef _SHIPPING
  debugDescription = GetFormattedDbId(pUnitDesc->GetDBID());
  debugObject = CreateDebugObject();
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ModifyStatsByForce(const NDb::MapForceStatModifierApplication application /*= NDb::MAPFORCESTATMODIFIERAPPLICATION_ALL*/)
{
  const float statModifier = GetWorld()->GetAIWorld()->GetStatsCoeffs().coeffsByFaction[GetFaction()];
#ifndef _SHIPPING
  const float oldStatModifier = stats->GetIncrementForceModifier(); // used for update_map_force cheat
#endif // _SHIPPING

  if (application & NDb::MAPFORCESTATMODIFIERAPPLICATION_BASE)
  {
    vector<NDb::StatBudget> const& vecStatBudgets = GetWorld()->GetAIWorld()->GetAIParameters().statsBudget->stats;

    for ( vector<NDb::StatBudget>::const_iterator itStatBudget = vecStatBudgets.begin(); itStatBudget != vecStatBudgets.end(); ++itStatBudget )
    {
      if ( !itStatBudget->upgradesWithForce )
        continue;

      StatValueWithModifiers* stat = GetStat( itStatBudget->stat );

      if (!stat)
        continue;

#ifndef _SHIPPING
      stat->SetCoreValue( stat->GetCoreValue() * statModifier / oldStatModifier );
#else
      stat->SetCoreValue( stat->GetCoreValue() * statModifier );
#endif // _SHIPPING
    }
  }

  if (application & NDb::MAPFORCESTATMODIFIERAPPLICATION_LEVELUP)
  {
    stats->SetIncrementForceModifier( statModifier );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatValueWithModifiers* PFBaseUnit::GetStat( NDb::EStat const stat)
{
  return stats->Get(stat);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatValueWithModifiers const* PFBaseUnit::GetStat( NDb::EStat const stat) const
{
  return stats->Get(stat);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float PFBaseUnit::GetUnmodifiedValue( NDb::EStat const stat ) const
{
  return stats->GetUnmodifiedValue(stat);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float PFBaseUnit::GetStatValue( NDb::EStat const stat ) const
{
  return stats->GetValue(stat);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float PFBaseUnit::GetStatValue( NDb::EDerivativeStat const stat ) const
{
  return derivativeStatsContainer->derivativeStats[stat](this, 0, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copies stat modifiers from the specefied unit. Will copy only modifiers 
// of the specified provider or any if the requested provider is PF_Core::INVALID_OBJECT_ID.
void PFBaseUnit::CopyStatModifiersFrom(PFBaseUnit * sourceUnit, int provider /*= PF_Core::INVALID_OBJECT_ID*/)
{
  if (!sourceUnit)
    return;

  const int statsCount = NDb::KnownEnum<NDb::EStat>::sizeOf;

  for ( int statId = 0; statId < statsCount; ++statId)
  {
    NWorld::ValueWithModifiers * srcValue(sourceUnit->GetStat(NDb::EStat(statId)));
    NWorld::ValueWithModifiers * dstValue(GetStat(NDb::EStat(statId)));

    if (srcValue && dstValue)
    {
      srcValue->Retrieve(dstValue, provider);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ValueWithModifiers* PFBaseUnit::GetVariableVWM( char const* name )
{
	Variable *pVar = SearchVariable(name);
	if (pVar)
	{
		return &(pVar->var);
	}

	pVar = new Variable;
	pVar->name = name;
	variablesRing.addLast(pVar);
	return &(pVar->var);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ValueWithModifiers* PFBaseUnit::SearchVariableVWM( char const* name ) const
{
  Variable * pVar = SearchVariable(name);

  if (pVar)
  {
    return &(pVar->var);
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetVariableValue( char const* name ) const
{
	Variable *pVar = SearchVariable(name);
	if (pVar)
		return pVar->var.GetValue();
	else
		return 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::ModifyByVariable( char const* name, float value ) const
{
	Variable *pVar = SearchVariable(name);
	if (pVar)
  {
    ValueWithModifiers &var = pVar->var;
    var.SetBaseValue(value);
		return var.GetValue();
  }
	else
		return value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseUnit::Variable* PFBaseUnit::SearchVariable( char const* name ) const
{
	for (ring::Range<Variable::Ring> it(variablesRing); it; ++it)
	{
		if (it->name == name)
			return &(*it);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::AddStat( NDb::EStat stat, float amount )
{
  ValueWithModifiers* vwmStat = GetStat( stat );
  if (vwmStat)
  {
    vwmStat->SetBaseValue( vwmStat->GetBaseValue() + amount );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const IUnitFormulaPars* PFBaseUnit::GetObjectMaster() const
{
  return IsValid(pMaster) ? static_cast<const IUnitFormulaPars*>(pMaster.GetPtr()) : this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const IUnitFormulaPars* PFBaseUnit::GetObjectTarget() const
{
	return IsValid(pCurrentTarget) ? pCurrentTarget.GetPtr() : this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::GetNativeDefenceIndex() const
{
  return dbUnitDesc->nativeDefence == NDb::DAMAGETYPE_MATERIAL ? 0 : 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::GetNativeAttackIndex() const
{
  return dbUnitDesc->nativeAttack == NDb::DAMAGETYPE_MATERIAL ? 0 : 1;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GetDistanceToTarget( const PFBaseUnit* pOwner, const PFBaseUnit* pTarget, const PathMap* pMap, float maxDistance, float attackRange )
{
  if ( !pMap )
    return fabs( pOwner->GetPosition() - pTarget->GetPosition() );

  //const float attackDistance = attackRange + ( pOwner->GetObjectSize() + pTarget->GetObjectSize() ) * 0.5f;

  float pathLength;
  float unreachableDistance;

  if ( !pMap->GetDistance( pOwner->GetPosition().AsVec2D(), pathLength, unreachableDistance/*, attackDistance */) )
    return maxDistance;

  return pathLength + unreachableDistance;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN(PFBaseUnit::ConditionsResolver)
NAMEMAP_END;

NNameMap::Variant * PFBaseUnit::ConditionsResolver::ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
{
  NI_VERIFY( IsValid(unit), "invalid owner", return NULL; );
  
  NI_VERIFY( unit->GetWorld() && unit->GetWorld()->GetAIWorld(), "ConditionsResolver : World is invalid!", return NULL; )
    const NDb::AILogicParameters& aiParams = unit->GetWorld()->GetAIWorld()->GetAIParameters();

  for ( vector<NDb::Ptr<NDb::ConditionFormula>>::const_iterator iCond = aiParams.conditionFormulas.begin(), iEnd = aiParams.conditionFormulas.end(); iCond != iEnd; ++iCond )
    if ( (*iCond)->name == name )
      return new AbilityBoolFormulaVariant( unit, (*iCond)->condition );

  NI_ALWAYS_ASSERT( NStr::StrFmt("Condition '%s' not found in vector 'conditionFormulas' for der stats in GameLogic/AILogic.AIPL!", name ) );

  return NULL;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseAttackData* PFBaseUnit::GetAttackAbility()
{
	if ( IsValid(pAttackAbility) )
		return pAttackAbility;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PFBaseAttackData* PFBaseUnit::GetAttackAbility() const
{
  if ( IsValid(pAttackAbility) )
    return pAttackAbility;
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::IsAttackFinished() const
{
  if (pAttackAbility)
  {
    const PFBaseAttackData::AttackInstances & attackInstaces =  pAttackAbility->GetAttackInstances();

    for ( int i = 0; i < attackInstaces.size(); ++i )
    {
      if ( attackInstaces[i] && !attackInstaces[i]->IsAttackFinished() )
      {
        return false;
      }
    }
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetTargetWeight(const CPtr<PFBaseUnit>& pTarget, const NDb::UnitTargetingParameters &unitPars, PathMap* pPathMap) const
{
  struct Local
  {
    static inline bool IsUnleashedSummon(const PFBaseUnit* const unit)
    {
      if (!IsValid(unit))
        return false;

      if (!unit->HasBehaviour())
        return false;

      const CDynamicCast<const PFSummonBehaviour> behaviour(unit->GetBehaviour());

      if (!IsValid(behaviour))
        return false;

      return behaviour->IsUnleashed();
    }

    static const AttackData* const GetLastAttackData(const CPtr<PFBaseUnit>& unit)
    {
      if (!IsValid(unit))
        return 0;

      return unit->GetLastAttackData();
    }

    static const AttackData* const GetLastHeroAttackData(const CPtr<PFBaseUnit>& unit)
    {
      if (!IsValid(unit))
        return 0;

      return unit->GetLastHeroAttackData();
    }

    static inline bool IsAttackDataValid(const AttackData* const attackData, const NDb::UnitTargetingParameters& tp)
    {
      if (!attackData)
        return false;

      if (!IsValid(attackData->pVictim))
        return false;

      if (tp.maxTimeFromAttack < 0.f)
        return true;
      if (tp.maxTimeFromAttack > attackData->timePassed)
        return true;

      return false;
    }

    static inline bool IsAttackedUnitAlly(const PFBaseUnit* const unit, const AttackData* const attackData)
    {
      if (!attackData)
        return false;

      if (!IsValid(attackData->pVictim))
        return false;

      if (unit->GetBehaviour())
        return unit->GetBehaviour()->IsAttackedUnitAlly(attackData->pVictim, attackData->originalFaction);
      else
        return unit->IsAttackedUnitAlly(attackData->pVictim, attackData->originalFaction);
    }

    static inline const CPtr<PFBaseUnit>& GetMasterUnit(const CPtr<PFBaseUnit>& unit)
    {
      if (IsValid(unit))
      {
        if (unit->IsAlphaSummon())
          return unit->GetMasterUnit();
      }

      return unit;
    }

    static inline const CPtr<PFBaseUnit>& GetMasterUnit(const CPtr<PFBaseUnit>& unit, const bool condition)
    {
      if (IsValid(unit) && condition)
      {
        if (unit->IsAlphaSummon())
          return unit->GetMasterUnit();
      }

      return unit;
    }

    static inline bool IsLivingUnit(const CPtr<PFBaseUnit>& unit)
    {
      if (unit->GetMaxLife() < EPS_VALUE)
        return false;
      if (unit->GetLife() < EPS_VALUE)
        return false;

      return true;
    }

    static inline const CPtr<PFBaseUnit>& GetAttackedUnit(const AttackData* const attackData)
    {
      static const CPtr<PFBaseUnit> l_dummy;

      if (!attackData)
        return l_dummy;

      return attackData->pVictim;
    }

    static inline bool DidUnitAttackAllyUnit(const PFBaseUnit* const unit, const NDb::UnitTargetingParameters& unitPars, const CPtr<PFBaseUnit>& target)
    {
      const AttackData* const attackData = GetLastAttackData(target);

      if (!IsAttackDataValid(attackData, unitPars))
        return false;

      return IsAttackedUnitAlly(unit, attackData);
    }

    static inline bool DidUnitAttackAllyHero(const PFBaseUnit* const unit, const NDb::UnitTargetingParameters& unitPars, const CPtr<PFBaseUnit>& target)
    {
      const AttackData* const attackData = GetLastHeroAttackData(target);

      if (!IsAttackDataValid(attackData, unitPars))
        return false;

      return IsAttackedUnitAlly(unit, attackData);
    }
  };

  DEBUG_TARGETTING(NStr::StrFmt("GTW-tid=%d)", (IsValid(pTarget))?(pTarget->GetObjectId()):(0)))

  NI_VERIFY( IsUnitValid(pTarget), "Invalid target!", return 0.0f );
  if ( !CanAttackTarget( pTarget ) )
  {
    DEBUG_TARGETTING("GTW-cancel(tgt)")
    return 0.0f;
  }

  if ( unitPars.ignoreSiblingTarget )
  {
    struct SiblingChecker : public NonCopyable
    {
      SiblingChecker( NDb::DBID const& dbid_, NDb::EFaction const faction_ ) : dbid(dbid_), faction(faction_) {}

      bool operator()( PFBaseUnit const& unit ) const
      {
        return unit.GetFaction() == faction && unit.DbUnitDesc()->GetDBID() == dbid;
      }
      NDb::DBID const& dbid;
      NDb::EFaction const faction;
    } siblingChecker( dbUnitDesc->GetDBID(), GetFaction() );

    struct CounterPredicate : public NonCopyable
    {
      CounterPredicate() : found(0) {}

      void operator()( PFBaseUnit const& unit )
      {
        ++found;
      }
      int found;
    } counterPredicate;

    pTarget->ForAllAttackers( siblingChecker, counterPredicate );
    if ( counterPredicate.found > 0 )
      return -1.0f;
  }

  const float range = unitPars.targetingRange;

  float weight = 0.f;

  bool useUnitTypeWeight = true;

  // use masters of alphasummons if any
  CPtr<PFBaseUnit> const& pCurrentTargetNew = Local::GetMasterUnit(pCurrentTarget, !unitPars.isStationarySummon);
  CPtr<PFBaseUnit> const& pTargetNew = Local::GetMasterUnit(pTarget, !unitPars.isStationarySummon);

  if (pCurrentTargetNew != pTargetNew)
  {
    float aggroRange = unitPars.aggroRange;

    if (aggroRange < EPS_VALUE)
      aggroRange = range;

    if (fabs(GetPosition() - pTargetNew->GetPosition()) > aggroRange)
    {
      weight += unitPars.OutOfAggroWeight;
    }

    struct AllySameTarget : public NonCopyable
    {
      AllySameTarget( const CPtr<PFBaseUnit>& pTarget ) : pTarget(pTarget), allyHaveSameTarget(false) {}

      void operator() ( PFBaseUnit &unit )
      {
        if ( allyHaveSameTarget )
          return;

        const CPtr<PFBaseUnit> pUnit( &unit );

        if ( !IsUnitValid( pUnit ) )
          return;

        const CPtr<PFBaseUnit>& pAllyTarget = Local::GetMasterUnit(pUnit->GetCurrentTarget());

        allyHaveSameTarget = ( pAllyTarget == pTarget );
      }

      const CPtr<PFBaseUnit>& pTarget;
      bool allyHaveSameTarget;
    } targetFinder( pTargetNew );

    GetWorld()->GetAIWorld()->ForAllUnitsInRange( GetPosition(), GetScreamRange(), targetFinder, UnitMaskingPredicate( 1 << GetFaction() ) );

    if ( targetFinder.allyHaveSameTarget )
    {
      weight += unitPars.allyTargetWeight;
    }
  }
  
  // support hero-like units, they are treated as heroes in a weights table
  const NDb::EUnitType unitType = pTargetNew->GetUnitType();

  // If target is a summon and its master attacks allied hero
  {
    const bool summon =
      (unitType == NDb::UNITTYPE_SUMMON) &&
      (unitPars.attackerHeroSummonWeight > 0.f);

    if (summon && Local::DidUnitAttackAllyHero(this, unitPars, pTargetNew->GetMasterUnit()))
    {
      weight += unitPars.attackerHeroSummonWeight;

      useUnitTypeWeight = false;
    }
  }

  if (Local::IsLivingUnit(pTargetNew))
  {
    weight += unitPars.healthWeight * ( 1.0f - Clamp(pTargetNew->GetLife() / pTargetNew->GetMaxHealth(), 0.0f, 1.0f) );
  }

  // Targeting by Master
  if ( IsUnitValid(pMaster) )
  {
    // NUM_TASK не провер€ем дистанцию до мастера, если саммон спущен с поводка
    if (!Local::IsUnleashedSummon(this))
    {
      const float distanceToMasterThreshold2 = fabs2(GetChaseRange() + GetAttackRange());
      const float distanceToMaster2 = fabs2(GetPosition() - pMaster->GetPosition());

      // Check distance to Master
      // NOTE: благодар€ этой проверке возможно избежать реальной оценки. например, цель, котора€ не должна быть атакована вообще,
      // может просто стать целью с очень низким приоритетом и будет атакована, если р€дом нет ничего более интересного.
      if ( distanceToMaster2 > distanceToMasterThreshold2 )
        return 0.f; // too far away from master
    }

    // Master Target
    if ( pTargetNew == pMaster->GetCurrentTarget() )
    {
      weight += unitPars.masterTargetWeight;
    }
  }

  // Targeting by distance
  const float distanceToTarget = GetDistanceToTarget( this, pTargetNew, pPathMap, range, GetAttackRange() );

  if (unitPars.weightMaximumRangePersent < 0.9999f)
  {
    weight += unitPars.rangeWeight * Clamp( (range - distanceToTarget) / (range * (1.0f - unitPars.weightMaximumRangePersent)), 0.0f, 1.0f );
  }
  else
  {
    weight += unitPars.rangeWeight * Clamp( (range - distanceToTarget) / (range), 0.0f, 1.0f );
  }

  // Current target weight
  if ( pTargetNew == pCurrentTargetNew )
  {
    weight += unitPars.currentTargetWeight[unitType] * unitPars.currentTargetTableWeight;
  }

  // Targeting Attackers
  if (Local::DidUnitAttackAllyHero(this, unitPars, pTargetNew))
  {
    const AttackData* const pAttackData = Local::GetLastHeroAttackData(pTargetNew);

    if (pAttackData->byAutoAttack)
    {
      weight += unitPars.autoAttackWeight;
    }
    else
    {
      weight += unitPars.talentAttackWeight;
    }

    if (useUnitTypeWeight)
    {
      weight += unitPars.attackerHeroWeight[unitType] * unitPars.attackerHeroTableWeight;    // help ally hero

      if ( pTargetNew->IsAggressiveNeutralCreep() )
      {
        weight += unitPars.aggressiveNeutralAttackingHeroWeight;
      }

      if (GetUnitType() != NDb::UNITTYPE_TOWER)
        useUnitTypeWeight = false;
    }

    {
      weight += unitPars.attackerNearbyHeroWeight;
    }
  }
  else if (Local::DidUnitAttackAllyUnit(this, unitPars, pTargetNew))
  {
    const AttackData* const pAttackData = Local::GetLastAttackData(pTargetNew);
    const CPtr<PFBaseUnit>& pTargetOfTarget = Local::GetAttackedUnit(pAttackData);

    // TODO: IsLikeHero() может вернуть true только дл€ alpha-summon'ов. ”словие избыточно.
    const bool isLikeHero =
      pTargetOfTarget->IsTrueHero() ||
      pTargetOfTarget->IsLikeHero() ||
      pTargetOfTarget->IsAlphaSummon();

    if (pAttackData->byAutoAttack)
    {
      weight += unitPars.autoAttackWeight;
    }
    else
    {
      weight += unitPars.talentAttackWeight;
    }

    if ( pTargetOfTarget == pMaster )
    {
      weight += unitPars.attackerMasterWeight;  // help Master
    }
    else if ( pTargetOfTarget == this )
    {
      weight += unitPars.attackerMeWeight;      // help self
    }
    else if ( isLikeHero && useUnitTypeWeight )
    {
      weight += unitPars.attackerHeroWeight[unitType] * unitPars.attackerHeroTableWeight;    // help ally hero

      if ( pTargetNew->IsAggressiveNeutralCreep() )
      {
        weight += unitPars.aggressiveNeutralAttackingHeroWeight;
      }

      if (GetUnitType() != NDb::UNITTYPE_TOWER)
        useUnitTypeWeight = false;
    }
    else if (pTargetOfTarget->GetUnitType() == NDb::UNITTYPE_TOWER)
    {
      weight += unitPars.attackerTowerWeight;
    }
    else
    {
      weight += unitPars.attackerAllyWeight;    // help other ally unit
    }
  }

  // Targeting by type, only if target doesn't attack ally hero and it is not a summon whose master attacks ally hero
  if ( useUnitTypeWeight )
  {
    weight += unitPars.unitTargetWeight[unitType] * unitPars.unitTypeTableWeight;

    if ( pTargetNew->IsAggressiveNeutralCreep() )
    {
      weight += unitPars.aggressiveNeutralWeight;
    }
  }

  if ( GetAttackAbilityData() )
  {
    weight += unitPars.customWeight( this, pTarget, GetAttackAbilityData().GetPtr(), 0.0f ); // important: passing pTarget as pSecond, not pTargetNew!
  }

  if ( IsPriorityTarget(pTargetNew) )
  {
    weight += unitPars.attackerNearbyHeroWeight;
  }

  return weight;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TargetFinder : NonCopyable
{
public:
  TargetFinder(PFBaseUnit &owner, const NDb::UnitTargetingParameters &unitPars, float maxRange)
    : owner(owner)
    , maxWeight(-1.0f)
    , unitPars(unitPars)
    , maxRange(maxRange)
    , usePathMap( g_bUseTestFindTargetMode && (owner.GetAttackRange() < owner.GetObjectSize() * 2.0f) )
  {
    competingTargets.reserve( 16 );
  }
  void BuildPathMap()
  {
    if ( usePathMap && !pPathMap )
    {
      PFBaseMovingUnit* pMovingThis = const_cast<PFBaseMovingUnit*>( dynamic_cast<const PFBaseMovingUnit*>(&owner) );
      if (pMovingThis)
        pPathMap = AutoPtr<PathMap>( pMovingThis->BuildPathMap(maxRange) );
    }
  }

  const CPtr<PFBaseUnit>& GetTarget() { return pTarget; }

  vector<CPtr<PFBaseUnit>>& GetCompetingTargets() { return competingTargets; }

  void ProcessAdditionalTarget( const ScreamTarget& target, bool mustBeInRange )
  {
    const CPtr<PFBaseUnit>& pNewTarget = target.pTarget;

    // need to check distance between target and owner
    if ( ( mustBeInRange && !owner.IsTargetInRange( pNewTarget, maxRange ) ) ||
      pNewTarget->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDAUTOTARGETME ) )
    {
      return;
    }

    if ( !owner.CanSelectTarget( pNewTarget, false ) )
      return;

    BuildPathMap();

    float weight = owner.GetTargetWeight( pNewTarget, unitPars, Get( pPathMap ) );

    if ( weight > maxWeight )
    {
      maxWeight = weight;
      pTarget   = pNewTarget;
    }

    if ( pNewTarget->IsAlphaSummon() )
      competingTargets.push_back( pNewTarget );
  }

  void operator ()(PFBaseUnit &unit)
  {
    NI_PROFILE_FUNCTION

    const CPtr<PFBaseUnit> pUnit = &unit;

    // need to check distance between target and owner
    if ( !owner.IsTargetInRange( pUnit, maxRange ) )
      return;

		if ( !owner.CanSelectTarget(&unit, true) )
      return;

    BuildPathMap();

    float weight = owner.GetTargetWeight( pUnit, unitPars, Get(pPathMap) );
    if (weight > maxWeight)
    {
      maxWeight = weight;
      pTarget   = &unit;
    }

    if ( unit.IsAlphaSummon() )
      competingTargets.push_back( &unit );
  }

private:
  const PFBaseUnit                &owner;
  float                           maxWeight;
  CPtr<PFBaseUnit>                pTarget;
  const NDb::UnitTargetingParameters  &unitPars;
  const float                     maxRange;
  AutoPtr<NWorld::PathMap>        pPathMap;
  bool                            usePathMap;
  vector<CPtr<PFBaseUnit>>        competingTargets;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::IsRequireDirectSightToAttack()
{
  return pAttackAbility ? pAttackAbility->GetDBDesc()->requireLineOfSight : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::CanAttackFlying() const
{
  return pAttackAbility ? pAttackAbility->CanHitFlying() : false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::CanAttackTarget(PFBaseUnit const* pTarget, bool ignoreInvulnerability /*= false*/) const
{
  return IsUnitValid( pTarget ) && ( ignoreInvulnerability || pTarget->IsVulnerable() ) && ( !pTarget->IsFlying() || CanAttackFlying() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::CanSelectTarget(PFBaseUnit const* pTarget, bool mustSeeTarget) const
{
  bool isSelf = pTarget == this;
  bool visibilityTest = !mustSeeTarget || pTarget->IsVisibleForFaction( GetWarfogFaction() );
 
  return !IsDead() && !isSelf && CanAttackTarget( pTarget )
    && !pTarget->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDAUTOTARGETME ) 
    && visibilityTest && ( !GetBehaviour() || GetBehaviour()->CanSelectTarget( pTarget, mustSeeTarget ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPtr<PFBaseUnit> PFBaseUnit::FindTarget( float range, bool checkScreams, int targetFlags, bool checkForbid /*= true*/ )
{
  NI_PROFILE_FUNCTION

  DEBUG_TARGETTING(NStr::StrFmt("FT-r=%f,cs=%d,tf=%d", range, checkScreams, targetFlags))

  if ( checkForbid && CheckFlagType( NDb::UNITFLAGTYPE_FORBIDSELECTTARGET ) )
  {
    if ( IsValid( pCurrentTarget ) && !IsTargetInRange( pCurrentTarget, range ) )
    {
      DropTarget();
    }

    return pCurrentTarget;
  }

  NI_ASSERT( GetWorld() && GetWorld()->GetAIWorld(), "Invalid world" );
  PFAIWorld* pAIWorld = GetWorld()->GetAIWorld();

  // –адиус поиска увеличен на макс. размер юнита дл€ того, чтобы учесть размеры юнитов при вычислении дистанции между ними.
  // ј при проверке целей, из результатов поиска отсекаютс€ те, до которых слишком далеко (IsInAttackRange)
  float searchRadius = range + ( GetObjectSize() + pAIWorld->GetMaxObjectSize() ) * 0.5f;
  
  TargetFinder targetFinder( *this, GetTargetingParams(), range );

  // find flying targets too if can hit them
  int targetTypesToFind = NDb::SPELLTARGET_ALL;
  if ( CanAttackFlying() )
  {
    targetTypesToFind |= NDb::SPELLTARGET_FLYING;
  }

  if ( IsRequireDirectSightToAttack() )
    targetTypesToFind |= NDb::SPELLTARGET_LINEOFSIGHT;

  targetTypesToFind |= targetFlags;

  DEBUG_TARGETTING(NStr::StrFmt("FT-sr=%d,ef=%d", searchRadius, targetTypesToFind))

  pAIWorld->ForAllUnitsInRange( position, searchRadius, targetFinder, UnitMaskingPredicate( GetOppositeFactionFlags(), targetTypesToFind, this ) );

  if ( checkScreams )
  {
    for ( vector<ScreamTarget>::const_iterator iScream = screamTargets.begin(), iEnd = screamTargets.end(); iScream != iEnd; iScream++ )
    {
      if ( IsUnitValid( iScream->pTarget) )
      {
        DEBUG_TARGETTING(NStr::StrFmt("FT-ps:uid=%d,st=%d", (IsValid(iScream->pTarget))?(iScream->pTarget->GetObjectId()):(0), iScream->screamType))
        targetFinder.ProcessAdditionalTarget( *iScream, false );
      }
    }
    screamTargets.clear();
  }

  const CPtr<PFBaseUnit> unit = targetFinder.GetTarget();

  DEBUG_TARGETTING(NStr::StrFmt("FT-fuid=%d", IsValid(unit) ? (unit->GetObjectId()):(0)))

  if ( IsValid(unit) )
  {
    vector<CPtr<PFBaseUnit>>& competingTargets = targetFinder.GetCompetingTargets();
    CPtr<PFBaseUnit> const& pAlphaSummon = unit->GetAlphaSummon();

    if ( pAlphaSummon && competingTargets.find( pAlphaSummon ) != competingTargets.end() )
    {
      DEBUG_TARGETTING(NStr::StrFmt("FT-alpha-summon(id=%d)", (IsValid(pAlphaSummon))?(pAlphaSummon->GetObjectId()):(0)))
      return pAlphaSummon;
    }
  }

  return unit;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnBeingTargeted( PFBaseUnit &attacker )
{
	attackersRing.addLast(&attacker);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::StopAttackingMe( bool ignorePursueDispatches /*= true */ )
{
	for (ring::Range<AttackersRing> it(attackersRing); it; )
	{
		PFBaseUnit *pUnit = &(*it);
		++it;
		pUnit->DropTarget();
	}

  for (ring::Range<UnitDispatchesRing> it(inboundDispatches); it; )
  {
    PFDispatchUniformLinearMove *pDispatch = &(*it);
    ++it;
    if ( ignorePursueDispatches || pDispatch->GetDB().aiming != NDb::DISPATCHAIMING_PURSUE )
    {
      if(!IsUnitAlly(pDispatch->GetSender()))
        pDispatch->DropTarget();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::AssignTarget(const CPtr<PFBaseUnit> &pTarget, bool strongTarget)
{
  DEBUG_TARGETTING(NStr::StrFmt("AT-tid=%d,st=%d",(IsValid(pTarget))?(pTarget->GetObjectId()):(0), strongTarget))

  if ( !CanAttackTarget( pTarget ) || pCurrentTarget==pTarget )
    return;

  CPtr<PFBaseUnit> pLastTarget = pCurrentTarget;

  DropTarget();

	if (IsGameLogicLogEnabled(this, false) || IsGameLogicLogEnabled(pTarget, false))
	{
		GameLogicLogger << "Unit ";
		LogLogicObject(this, "", false);
		GameLogicLogger << " is now targeting at ";
		LogLogicObject(pTarget, "", true);
	}

  pCurrentTarget = pTarget;

  if(!IsValid( pCurrentTarget ))
    return;

  EventHappened( PFBaseUnitAssignTargetEvent(pTarget, pLastTarget, strongTarget) );

  pCurrentTarget->OnBeingTargeted(*this);

  bStrongTarget = strongTarget;
  targetRevisionTime = strongTarget ? 0.0f : GetTargetingParams().targetRevisionTime;
  DebugShowAttackEffect( this, pTarget, bStrongTarget ? 0 : targetRevisionTime );

  OnTargetAssigned();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::DropTarget()
{
  DEBUG_TARGETTING("DT")

  if (IsValid(pCurrentTarget))
  {
		if (IsGameLogicLogEnabled(this, false))
		{
			LogLogicObject(this, "Target is dropped\n", false);
		}

		AttackersRing::remove(this);
    pCurrentTarget = NULL;
    targetRevisionTime = 0.0f;
    bStrongTarget = false;

    OnTargetDropped();
  }
}

void PFBaseUnit::ClearScreamTargets()
{
  screamTargets.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::DoScream( const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st )
{
  NI_VERIFY( IsUnitValid(pTarget), "Invalid Target!", return; );
  NI_ASSERT( GetWorld() && GetWorld()->GetAIWorld(), "Invalid world" );
  NI_ASSERT( pTarget->IsVulnerable() && pTarget->GetFaction() != GetFaction(), "Target must be valid!" );

	// Don't scream on targets that we can't autotarget on
	if (pTarget->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDAUTOTARGETME))
		return;

  // Screaming
  if ( HasBehaviour() && Behaviour()->IsEnabled() )
    Behaviour()->DoScream( pTarget, st );
}

void PFBaseUnit::Stacked( const bool stacked/* = true */)
{
  // Stacked
  if ( HasBehaviour() && Behaviour()->IsEnabled() )
    Behaviour()->Stacked( stacked );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnScream( const CPtr<PFBaseUnit> pTarget, ScreamTarget::ScreamType st )
{
  NI_ASSERT( IsUnitValid( pTarget ), "OnScream : target must be valid!" );

  if ( bStrongTarget || ( pCurrentTarget == pTarget ) || CheckFlagType( NDb::UNITFLAGTYPE_FORBIDATTACK ) )
  {
    return; // target can not be changed
  }

  DebugShowScreamEffect( this, pTarget, st );

  ScreamTarget target = { st, pTarget } ;
  screamTargets.push_back( target );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::IsTargetInRange( const Target& target, float range ) const
{
  if ( target.IsObject() )
  {
    return IsObjectInRange( target.GetObject(), range );
  }
  else
  {
    return IsPositionInRange( target.GetPosition().AsVec2D(), range );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::IsTargetInAttackRange(const Target & target, bool useTargetInFormula /*= false*/) const
{
  if (useTargetInFormula && target.IsUnit())
  {
    return IsTargetInAttackRange(target.GetUnit(), useTargetInFormula);
  }

  return IsTargetInRange(target,  GetAttackRange());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::IsTargetInAttackRange(const PFLogicObject * pTarget, bool useTargetInFormula /*= false*/) const 
{
  NI_ASSERT(IsUnitValid(pTarget), "Invalid target!");

  if (useTargetInFormula)
  {
    if (const PFBaseAttackData *baseAttackData = GetAttackAbility())
    {
      if (const NDb::Ability *dbDesc = baseAttackData->GetDBDesc())
      {
        float range = dbDesc->useRange(this, pTarget, baseAttackData);
        if (range > 0.0f)
        {
          return IsTargetInRange(pTarget, range);
        }
      }
      else
      {
        NI_ALWAYS_ASSERT("No db descriptor!");
      }
    }
    else
    {
      NI_ALWAYS_ASSERT("No attack ability!");
    }
  }

  return IsTargetInRange(pTarget, GetAttackRange()); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
template< class TFloat1>
inline void StepRestorable( TFloat1& value, const float dt, const float regen, const float maxValue, const float minValue = 0.0f )
{
  value = Clamp(value + dt * regen, minValue, maxValue); // negative regen is allowed
}

template< class TFloat1, class TFloat2>
inline void UpdateValuesAccording2LimitChange( TFloat1 &value, TFloat2 &valueMax, const float newValueMax, const float minValue = 0.0f )
{
  if (!(std::abs(valueMax - newValueMax) > EPS_VALUE))
    return;

  const float factor = Clamp(valueMax > EPS_VALUE ? value / valueMax : 1.0f, 0.0f, 1.0f);

  value = Max(minValue, factor * newValueMax);
  valueMax = Max(minValue, newValueMax);
}



} //noname namespace

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::AutoTarget( float dt )
{
  NI_PROFILE_FUNCTION
  if ( !bStrongTarget && ( IsUnitValid(pCurrentTarget) || !screamTargets.empty() ) )
  {
    targetRevisionTime-=dt;
    if ( targetRevisionTime <= 0 || !screamTargets.empty() )
    {
      DEBUG_TARGETTING("AT")

      CPtr<PFBaseUnit> pTarget = FindTarget( GetTargetingRange(), true );
      if ( IsUnitValid(pTarget) && pTarget!=pCurrentTarget )
      {
        if ( IsValid(pCurrentTarget) )
          AssignTarget( pTarget, false );
        else
          OnTarget( pTarget, false );
      }
      targetRevisionTime = GetTargetingParams().targetRevisionTime;
    }
  }
  screamTargets.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PFAbilityInstance> PFBaseUnit::CreateAbilityInstance( PFAbilityData* pAbilityData, Target const& target )
{
  CObj<PFAbilityInstance> pInstance = pAbilityData->ApplyToTarget(target);
  if ( pInstance )
    abilityInstances.push_back(pInstance);
  return pInstance;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::UseAbilityWithMicroAI()
{
  // Update MicroAI
  if ( IsMicroAiEnabled() && !IsDead() && !HaveAbilityInProgress())
  {  
    for(int ability = NDb::ABILITY_ID_1; ability <= NDb::ABILITY_ID_4; ++ability)
    {
      if ( PFAbilityData *pAbility = GetAbility(ability) )
      {
        Target target;
        if (CanUseAbility(ability) && pAbility->CanBeUsed() && pAbility->FindMicroAITarget(target))
        {
          CObj<IPFState> pState = InvokeAbility(ability, target);
          if (IsValid(pState))
          {
            EnqueueState(pState, true);
            return true; // We can't cast two ore more abilities at same time
          }
        }
      }
    }
  } // End of if ( IsMicroAiEnabled() && !IsDead() )
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PFAbilityInstance> PFBaseUnit::UseAbility(int id, Target const &target)
{
  if( CanUseAbility(id, target) )
  {
    if( PFAbilityData* pAbility = GetAbility( id ) )
    {
      if ( !pAbility->IsMultiState() )
      {
        CObj<PFAbilityInstance> newInstance = CreateAbilityInstance( pAbility, target );
        if (newInstance)
        {
          ELookKind lookAtTarget = newInstance->IsCasterShouldLookAtTarget();
          if ( lookAtTarget != DontLook )
          {
            if ( PFBaseMovingUnit* pMovingUnit = dynamic_cast<PFBaseMovingUnit* >(this) )
            {
              pMovingUnit->SetMoveDirection( target.AcquirePosition().AsVec2D() );
            }
          }

          if ( NGameX::PFClientBaseUnit* pClient = ClientObject() )
          {
            pClient->OnUseAbility( pAbility->GetAbilityNode(), pAbility->GetAbilityMarker(),
              target, pAbility->GetTimeOffset( true ), lookAtTarget, pAbility->IsAbilitySupposedToStopUnit() );
          }

          EventHappened( PFBaseUnitAbilityStartEvent( newInstance.GetPtr() ) );
        }
        return newInstance;
      }
      else
      {
        pAbility->Toggle( target );

        return NULL;
      }
    }
  }

  return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<IPFState>  PFBaseUnit::InvokeAbility(int id, Target const &target)
{
  NI_ASSERT(false == IsAbilityInProgress(id), "Ability is already in progress");
  NI_ASSERT(CanUseAbility(id), "Ability could not be used");

  CObj<IPFState> pState (new PFBaseUnitUseAbilityState(GetWorld(), this, id, target));

  return pState;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PFAbilityInstance> PFBaseUnit::UseExternalAbility( NDb::Ptr<NDb::Ability> const& pDesc, Target const& target )
{
  CObj<PFAbilityData> pAbilityData = new PFAbilityData(this, pDesc, NDb::ABILITYTYPEID_SPECIAL, true, true );
  CObj<PFAbilityInstance> pAbilityInstance = CreateAbilityInstance( pAbilityData, target );
#ifndef VISUAL_CUTTED
  if ( IsValid( pAbilityInstance ) && ClientObject() )
  {
    if ( NGameX::PFClientCreature* pClientCreature = dynamic_cast<NGameX::PFClientCreature*>(ClientObject()) )
      pClientCreature->OnUseAbility( pAbilityData->GetAbilityNode(), pAbilityData->GetAbilityMarker(), target, pAbilityData->GetTimeOffset( true )
      , pAbilityInstance->IsCasterShouldLookAtTarget(), pAbilityData->IsAbilitySupposedToStopUnit() );
  }
#endif //VISUAL_CUTTED

  return pAbilityInstance;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RegisterExternalPassiveAbility( PFAbilityData* pAbilityData )
{
  externalPassiveAbilities.push_back( pAbilityData );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::UnregisterExternalPassiveAbility( PFAbilityData* pAbilityData )
{
  for( vector<CObj<PFAbilityData> >::iterator it = externalPassiveAbilities.begin(); it != externalPassiveAbilities.end(); ++it )
    if ( *it == pAbilityData )
    {
      externalPassiveAbilities.erase( it );
      return true;
    }
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PFBaseAttackData> PFBaseUnit::ReplaceBaseAttack(CObj<PFBaseAttackData> const & pNewBaseAttack, bool applyPassivePart /*= true*/)
{
	if ( pAttackAbility )
	{
		pAttackAbility->ApplyPassivePart(false);
		pAttackAbility->Cancel();
	}

	CObj<PFBaseAttackData> pTemp(pAttackAbility);
	pAttackAbility = pNewBaseAttack;

	if ( !pAttackAbility->HasPassiveInstance() )
		pAttackAbility->ApplyPassivePart(applyPassivePart);
	
  return pTemp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnStartedFighting()
{
  CALL_CLIENT(OnStartedFighting);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnFinishedFighting()
{
  CALL_CLIENT(OnFinishedFighting);
  OnTargetDropped();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnAttackDispatchStarted() const
{
  CALL_CLIENT(OnAttackDispatchStarted);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnGameFinished( const NDb::EFaction failedFaction )
{
  RemoveBehaviour();
  DropStates();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::UpdateExternalAbilities(float dtInSeconds)
{
  NI_PROFILE_FUNCTION;

  // Update external abilities instances
  struct AbilitiesInstancesUpdater
  {
    float dt;
    AbilitiesInstancesUpdater(float dt) : dt(dt) {}
    bool operator() ( CObj<PFAbilityInstance> const& pAbility ) { return !IsValid(pAbility) || pAbility->Update(dt); }
  } updater(dtInSeconds);

  abilityInstances.erase( remove_if(abilityInstances.begin(), abilityInstances.end(), updater), abilityInstances.end() );
}

void PFBaseUnit::WakeUp()
{
  sleepDelay = 10.0f;
  bSleep = false;
}

bool PFBaseUnit::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION;


  // go to sleep if this unit in idle and it is not visible for any faction 
  if ( GetFaction() == NDb::FACTION_NEUTRAL )
  {
    if ( sleepDelay <= 0.f )
    {
      if ( IsIdle() && !IsPlacementVisible( NDb::FACTION_BURN ) && !IsPlacementVisible( NDb::FACTION_FREEZE ) )
      {
        bSleep = true;
        return true;
      }
      else
      {
        // don't sleep during 10 seconds after wakeup
        WakeUp();
      }
    }
    else
      sleepDelay -= dtInSeconds;
  }

  UpdatePriorityTargets( dtInSeconds );

  UpdateNatureType();
  StepLastAttackData(dtInSeconds);

	if ( HasBehaviour() && Behaviour()->IsEnabled() )
		Behaviour()->OnStep(dtInSeconds);

  UpdateAbilities(dtInSeconds, isDead);

  if( pAttackAbility )
    pAttackAbility->Update(dtInSeconds, !IsDead());

  UpdateExternalAbilities(dtInSeconds);

  if ( !IsDead() )
  {
    AutoTarget(dtInSeconds);

    UpdateValuesAccording2LimitChange(health, maxHealth, GetStatValue(NDb::STAT_LIFE));
    UpdateValuesAccording2LimitChange(energy, maxEnergy, GetStatValue(NDb::STAT_ENERGY));
    
    if ( !CheckFlagType(NDb::UNITFLAGTYPE_FORBIDLIFERESTORE) )
    {
      StepRestorable(health, dtInSeconds, GetLifeRegenTotal(), maxHealth, 1.0f );
      if ( IsDead() )
        OnUnitDie( 0, UNITDIEFLAGS_NONE );
    }
    if ( !CheckFlagType(NDb::UNITFLAGTYPE_FORBIDENERGYRESTORE) )
    {
      StepRestorable(energy, dtInSeconds, GetEnergyRegenTotal(), maxEnergy );
    }
  }

  RecryptImpl();

  if ( !IsDead() )
  {
    FsmStep(dtInSeconds);

    StepWarFog(dtInSeconds);
  }

	StepApplicators(dtInSeconds);
  StepApplicatorsHistory();
  StepInvisibility();

  if ( shouldRestoreStatusEffects )
  {
    RestoreStatusEffects();
    shouldRestoreStatusEffects = false;
  }
  
  timeSinceLevelUp += 1 < naftaLevel ? dtInSeconds : 0.0f;

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::StepInvisibility()
{
  bool oldVisibleForEnemy = visibleForEnemy;

  visibleForEnemy = !CheckFlagType(NDb::UNITFLAGTYPE_INVISIBLE) || CheckFlagType(NDb::UNITFLAGTYPE_IGNOREINVISIBLE);
  visibleForNeutral = visibleForEnemy;

  if ( !visibleForEnemy )
  {
    //Unit is invisible. Looking for neighboor units
    NI_VERIFY(GetWorld() && GetWorld()->GetAIWorld(), "Wrong world ptr!", return);

    PFAIWorld* pAIWorld = GetWorld()->GetAIWorld();

    struct TrueSight
    {
      explicit TrueSight(CPtr<PFBaseUnit> const &self, bool _isNeutralOnly) : position(self->GetPosition().AsVec2D()), visibleByTrueSight(false), isNeutralOnly(_isNeutralOnly) {}

      void operator ()(PFBaseUnit &unit)
      {
        if (visibleByTrueSight || !unit.CheckFlag(NDb::UNITFLAG_CANSEEINVISIBLE))
          return;

        const bool neutralUnit = (unit.GetFaction() == NDb::FACTION_NEUTRAL);

        if (isNeutralOnly != neutralUnit)
          return;

        CVec2 dist = unit.GetPosition().AsVec2D() - position;

        float range = unit.GetVisibilityRange();

        if (fabs2(dist) < range * range)
          visibleByTrueSight = true;
      };

      CVec2 position;
      bool  visibleByTrueSight;
      bool isNeutralOnly;
    };

    // NUM_TASK
    const bool canBeSeenWithTrueSight = !CheckFlagType(NDb::UNITFLAGTYPE_INMINIGAME);

    if (canBeSeenWithTrueSight)
    {
      float const radius = pAIWorld->GetAIParameters().maxTrueSightRange;

      TrueSight trueSight(this, false);
      int targetsToFind = NDb::SPELLTARGET_ALL | NDb::SPELLTARGET_AFFECTMOUNTED | NDb::SPELLTARGET_FLYING;
      pAIWorld->ForAllUnitsInRange(GetPosition(), radius, trueSight, UnitMaskingPredicate(GetOppositeFactionFlags(), targetsToFind ));

      visibleForEnemy = trueSight.visibleByTrueSight;

      TrueSight trueSightNeutral(this, true);
      targetsToFind = NDb::SPELLTARGET_ALL | NDb::SPELLTARGET_AFFECTMOUNTED | NDb::SPELLTARGET_FLYING;
      pAIWorld->ForAllUnitsInRange(GetPosition(), radius, trueSightNeutral, UnitMaskingPredicate(GetOppositeFactionFlags(), targetsToFind ));

      visibleForNeutral = trueSightNeutral.visibleByTrueSight;
    }

    if (!visibleForEnemy && oldVisibleForEnemy)
      StopAttackingMe( false );
  }

  // Update visibility for the client
  CALL_CLIENT(UpdateVisibility);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::StepWarFog(float dtInSeconds)
{
  NI_PROFILE_FUNCTION

  PFWorld * pWorld = GetWorld();
  NI_VERIFY(pWorld, "Failed to get World!", return);
  FogOfWar * pWarFog = pWorld->GetFogOfWar();
  NI_VERIFY(pWarFog, "Failed to get War Fog!", return);
  TileMap * pTileMap = pWorld->GetTileMap();
  NI_VERIFY(pTileMap, "Failed to get Tile map!", return);

  NDb::EFaction warfogFaction = GetWarfogFaction();
  // Update visibility radius for the unit's faction
  if (visUnitData[warfogFaction].warFogObjectID != WAR_FOG_BAD_ID)
  {
    int visRadius = (int)GetVisibilityRange()/pTileMap->GetTileSize();
    pWarFog->ChangeVisibility(visUnitData[warfogFaction].warFogObjectID, visRadius);
    visUnitData[warfogFaction].visRadius = visRadius;
  }

  // Update, if needed, visibility for other faction
  for (int i=0; i < visUnitData.size(); ++i)
  {
    if (i != warfogFaction && visUnitData[i].warFogObjectID != WAR_FOG_BAD_ID)
    {
      if (visUnitData[i].timeOut > 0.0f)
        visUnitData[i].timeOut = max(0.0f, visUnitData[i].timeOut - dtInSeconds);

      if ( visUnitData[i].timeOut < EPS_VALUE )
      {
        pWarFog->RemoveObject(visUnitData[i].warFogObjectID);
        visUnitData[i].Clear();
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ResetWarFog()
{
  NI_VERIFY(faction < visUnitData.size(), "War Fog data not initialized or wrong faction!", return);

  vector<WarFogData> oldVisUnitData(visUnitData);

  // Close War Fog without adding a temp object
  CloseWarFog(true);

  for (int i = 0; i < oldVisUnitData.size(); ++i)
  {
    if (oldVisUnitData[i].warFogObjectID != WAR_FOG_BAD_ID)
      OpenWarFog((NDb::EFaction)i, oldVisUnitData[i].timeOut, oldVisUnitData[i].visRadius);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::OnDispatchApply( PFDispatch const &dispatch )
{
	PFBaseUnit *pSender = dispatch.GetSender();
	if ( IsValid(pSender) &&                 // @BVS@TODO: A bug - what if sender is already freed?
		   faction != pSender->GetFaction() && // Friendly dispatches always pass
			 dispatch.IsBaseAttack() &&
       (dispatch.GetDBBase()->flags & NDb::DISPATCHFLAGS_EVADABLE) != 0 )
	{
    //PF - 17421. For now missed and evaded are treated the same. TODO[SimonK] make a new UI event here 
    bool missed = pWorld->GetRndGen()->Next(100) < int(pSender->GetMissChance());
    bool evaded = pWorld->GetRndGen()->Next(100) < int(GetEvasion());

		if ( missed )
		{
      pSender->OnMiss( CPtr<PFBaseUnit>(this) );
      dispatch.OnMissed();
      EventHappened(PFBaseUnitDispatchEvent(NDb::BASEUNITEVENT_DISPATCHMISSED, &dispatch));
      return false;
     }

     if ( evaded)
     {
       pSender->OnMiss( CPtr<PFBaseUnit>(this) );
       dispatch.OnMissed();
       EventHappened(PFBaseUnitDispatchEvent(NDb::BASEUNITEVENT_DISPATCHEVADED, &dispatch));
       return false;
     }
	}

  {
    PFBaseUnitDispatchEvent evtDispatch(NDb::BASEUNITEVENT_DISPATCHAPPLIED, &dispatch);
    EventHappened(evtDispatch);
    if (evtDispatch.IsDispatchCancelled())
    {
      pSender->OnMiss( CPtr<PFBaseUnit>(this) );
      dispatch.OnMissed();
      EventHappened(PFBaseUnitDispatchEvent(NDb::BASEUNITEVENT_DISPATCHMISSED, &dispatch));
      return false;
    }
  }

  // Wakeup neutral on hostile dispatch application
  if ( GetFaction() == NDb::FACTION_NEUTRAL && pSender->GetFaction() != NDb::FACTION_NEUTRAL )
  {
    WakeUp();
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnMiss(CPtr<PFBaseUnit> const &pTarget)
{
	if (IsDead())
		return;

	// Show miss message
	CALL_CLIENT_1ARGS(OnMiss, pTarget);
}

void PFBaseUnit::CheckAppliedApplicators()
{
  nstl::vector<PFBaseApplicator*> applicators;

  struct CopyApplicatorToVector
  {
    CopyApplicatorToVector( nstl::vector<PFBaseApplicator*>* _vec ) { vec = _vec; }
    void operator()( const CObj<PFBaseApplicator>& pAppl )
    {
      if ( PFApplBuff* pApplBuff = dynamic_cast<PFApplBuff*>( pAppl.GetPtr() ) )
      {
        vec->push_back( pAppl.GetPtr() );
      }
    }
    nstl::vector<PFBaseApplicator*>* vec;
  }copyApplicatorToVector( &applicators );

  ForAllAppliedApplicators( copyApplicatorToVector );

  // Output
  //DebugTraceWithWorldStep( this, "applied applicators (%d):", applicators.size() );
  //for ( int i = 0; i < applicators.size(); ++i )
  //{
  //  {
  //    DebugTraceWithWorldStep( this, "\t%s", (applicators[i])->GetDBBase().GetPtr()->GetDBID().GetFormatted().c_str() );
  //  }
  //}
  //DebugTraceWithWorldStep( this, "" );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::PlanToRestoreSceneObject( NDb::Ptr<NDb::DBSceneObject>& sObj )
{
  shouldRestoreSceneObject = true;
  pOriginalSceneObject = sObj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RestoreStatusEffects()
{
  struct RestoreBuffApplicatorEffects
  {
    void operator()( const CObj<PFBaseApplicator>& pAppl )
    {
      if ( PFApplBuff* pApplBuff = dynamic_cast<PFApplBuff*>( pAppl.GetPtr() ) )
      {
        pApplBuff->RestartEffects();
      }
    }
  } restoreBuffApplicatorEffects;
  ForAllAppliedApplicators( restoreBuffApplicatorEffects );
}

void PFBaseUnit::RestoreSceneObject()
{
  if ( shouldRestoreSceneObject )
  {
    CALL_CLIENT_1ARGS( SetSceneObject, pOriginalSceneObject );
    shouldRestoreSceneObject = false;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ApplyDamageReduction(float & damage, NDb::EApplicatorDamageType damageType, DamageDesc const& desc)
{
  if (damageType == NDb::APPLICATORDAMAGETYPE_PURE || damageType == NDb::APPLICATORDAMAGETYPE_MANA)
    return;

  if ( damageType == NDb::APPLICATORDAMAGETYPE_ENERGY )
    damage = GetWorld()->GetAIWorld()->GetAIParameters().energyDamageReduction( desc.pSender, this, desc.pDealerApplicator, damage );
  else
    damage = GetWorld()->GetAIWorld()->GetAIParameters().physicalDamageReduction( desc.pSender, this, desc.pDealerApplicator, damage );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ApplyDrains( const DamageDesc &desc, float damage )
{
  if ( UnitCheck(UNITCHECKID_ISBUILDING) )
    return;

  if( IsUnitValid(desc.pSender) )
  {
    if( desc.damageMode & NDb::DAMAGEMODE_APPLYLIFEDRAINS && !desc.pSender->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDLIFERESTORE) )
    {
      const float lifeDrain   = min( GetHealth(), min (desc.pSender->GetLifeDrain(), damage) );
      if ( 0.0f < lifeDrain )
        desc.pSender->OnHeal( desc.pSender, lifeDrain );
    }

    if( desc.damageMode & NDb::DAMAGEMODE_APPLYENERGYDRAINS )
    {
      float energyDrain = min( desc.pSender->GetEnergyDrain(), damage );

      energyDrain = OnBurnEnergy( desc.pSender, energyDrain );

      if ( !desc.pSender->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDENERGYRESTORE) && 0.0f < energyDrain )
        desc.pSender->OnHealEnergy( desc.pSender, energyDrain );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::OnDamage(const DamageDesc &desc)
{
	if( !IsVulnerable() || g_bDebugNoDamage )
		return 0.0f;

  NI_VERIFY(0 <= desc.damageType && desc.damageType < NDb::KnownEnum<NDb::EApplicatorDamageType>::SizeOf(),
		"Invalid damage type", return 0.f);

  // “ут не должно приходить нативного дамага! ≈сли он пришЄл, ругаемс€ верифаем и хаком подставл€ем правильный тип..
  NI_VERIFY( desc.damageType != NDb::APPLICATORDAMAGETYPE_NATIVE, "Wrong damage type: NATIVE (internal PFBaseUnit::OnDamage() usage error!). Will be used sender native damage instead",
    const_cast<DamageDesc&>(desc).damageType = desc.pSender ? desc.pSender->GetNativeDamageType() : NDb::APPLICATORDAMAGETYPE_MATERIAL );

  if( const PFApplDamage* damageAppl = dynamic_cast<const PFApplDamage*>( desc.pDealerApplicator ) )
  {
    if( lastDamage.abilityDbid.GetHashKey() == damageAppl->GetDB().GetDBID().GetHashKey() )
    {
      if( damageAppl->GetDB().timeLimiter >= lastDamage.timeOver )
      {
        return(0.f);
      }
      else
      {
        lastDamage.timeOver = 0.f;
      }
    }
    else
    {
      lastDamage.abilityDbid = desc.pDealerApplicator->GetDBBase()->GetDBID();
      lastDamage.timeOver = 0.f;
    }
  }

	float damage = desc.amount;
 
  if ( !desc.ignoreDefences )
    ApplyDamageReduction(damage, static_cast<NDb::EApplicatorDamageType> (desc.damageType), desc );

  // Set damage event
  PFBaseUnitDamageEvent evt(desc, damage);
  EventHappened(evt);

  float damageChange = evt.damage2Deal - damage;

  damage = evt.damage2Deal;

  damage = max(damage, 0.f);

  // expo mode feature //
  if ( g_immortalHeroes && IsHero() )
  {
    PFBaseHero *pHero = static_cast<PFBaseHero*>(this);
    if ( pHero->GetPlayer() && !pHero->GetPlayer()->IsBot() ) // clones doesn't have attached players
    {
      damage *= GetWorld()->GetAIWorld()->GetAIParameters().expoModeParams.damageModifier( desc.pSender, this, desc.pDealerApplicator, 1.0f );
      damage = min( damage, GetHealth() - GetWorld()->GetAIWorld()->GetAIParameters().expoModeParams.minHeroLife );
    }
  }
  ///////////////////////

  damage = min(damage, GetHealth());

  ApplyDrains(desc, damage);

  // Store real damage in statistics
  if ( IsTrueHero() && damage > 0.0f)
  {
    PFBaseHero *pHero = static_cast<PFBaseHero*> (this);
    
    if ( IsValid( pHero->GetHeroStatistics() ) )
      pHero->GetHeroStatistics()->OnDamage(desc.pSender, damage);
  }

	if (IsGameLogicLogEnabled(this, false))
	{
		GameLogicLogger << "Unit ";
		LogLogicObject(this, "", false);
		GameLogicLogger << ": DAMAGED by ";
		LogLogicObject(desc.pSender, "", true);
		LogGameLogicString(NStr::StrFmt("\n%s: Clamp((%.2f)) + %.2f = %.2f\n", NDb::EnumToString( static_cast<NDb::EApplicatorDamageType>(desc.damageType) ), desc.amount, GetHealth(), damageChange, damage));
	}

	if (IsDead())
    return 0.0f;

  health -= damage;

  if ( !GetTargetingParams().onlyAutoTargeting && HasBehaviour() && Behaviour()->IsEnabled() )
    Behaviour()->OnDamage(desc);

  bool isDeathDeferred = false;
  bool liveAfterDeath = false;

  if ( IsDead() ) // last hit
  {
    liveAfterDeath = CheckFlag( NDb::UNITFLAG_LIVEAFTERDEATH );

    if ( CheckFlag( NDb::UNITFLAG_FORBIDDEATH  ) || liveAfterDeath )
    {
      health = 1.0f;
      isDeathDeferred = true;
    }

    PFBaseUnitLastHitEvent lastHitEvent( desc.pSender );
    EventHappened( lastHitEvent );

  }

  if(isDeathDeferred && liveAfterDeath)
  {
    OnUnitDie( desc.pSender, UNITDIEFLAGS_DEFERREDDEATH, &desc );
  }
	else if (IsDead())
  {
    int flags = UNITDIEFLAGS_NONE;
    bool isRewardsForbiden = CheckFlag( NDb::UNITFLAG_FORBIDREWARDS );

    if(isRewardsForbiden)
      flags &= UNITDIEFLAGS_FORBIDREWARDS;

    OnUnitDie( desc.pSender, flags, &desc );
  }
  else
	{
		CALL_CLIENT_2ARGS(OnDamage, health, damage);
	}


	return damage;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::OnHeal(CPtr<PFBaseUnit> pSender, float amount, bool ignoreHealingMods /*=false */ )
{
  if (IsGameLogicLogEnabled(this, false))
  {
    GameLogicLogger << "Unit ";
    LogLogicObject(this, "", false);
    GameLogicLogger << ": HEALED by ";
    LogLogicObject(pSender, "", true);
    GameLogicLogger << " for amount = " << amount << "\n";
  }

  if ( CheckFlag(NDb::UNITFLAG_FORBIDLIFERESTORE) )
    return 0.f;

  float curhealth = health;
  
  if ( !ignoreHealingMods )
  {
    amount *= ( 1.0f + GetVariable( UnitVariables::szHealingScale ) );
    health += GetVariable( UnitVariables::szHealingBias );
  }
  health += amount;

  if (health > GetMaxHealth())
  {
    health = GetMaxHealth();
  }
  else if ( IsDead() )
  {
		OnUnitDie( pSender, UNITDIEFLAGS_NONE );
  }

  return health - curhealth;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::OnBurnEnergy(CPtr<PFBaseUnit> pSender, float amount)
{
  if (IsGameLogicLogEnabled(this, false))
  {
    GameLogicLogger << "Unit ";
    LogLogicObject(this, "", false);
    GameLogicLogger << ": ENERGY BURNED by ";
    LogLogicObject(pSender, "", true);
    GameLogicLogger << " for amount = " << amount << "\n";
  }

  float const actual = min(energy, amount);

	energy -= actual;

  return actual;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::OnHealEnergy(CPtr<PFBaseUnit> pSender, float amount)
{
  if (IsGameLogicLogEnabled(this, false))
  {
    GameLogicLogger << "Unit ";
    LogLogicObject(this, "", false);
    GameLogicLogger << ": ENERGY HEALED by ";
    LogLogicObject(pSender, "", true);
    GameLogicLogger << " for amount = " << amount << "\n";
  }

  if ( CheckFlag(NDb::UNITFLAG_FORBIDENERGYRESTORE) )
    return 0.f;

  float curenergy = energy;

	energy += amount;
	float maxEnergy = GetMaxEnergy();
	if (energy > maxEnergy)
		energy = maxEnergy;

  return energy - curenergy;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnAddGold(CPtr<PFBaseUnit> pSender, float amount, bool showGold)
{
  if (IsGameLogicLogEnabled(this, false))
  {
    GameLogicLogger << "Unit ";
    LogLogicObject(this, "", false);
    GameLogicLogger << ": GOLD ADDED by ";
    LogLogicObject(pSender, "", true);
    GameLogicLogger << " for amount = " << amount << "\n";
  }

  gold += amount;

	if (showGold)
	{
		CALL_CLIENT_2ARGS(OnAddGold,pSender, amount);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::OnRemoveGold(CPtr<PFBaseUnit> pSender, float amount)
{
	float realAmount = Min(GetValue(gold), amount);

	if (IsGameLogicLogEnabled(this, false))
  {
    GameLogicLogger << "Unit ";
    LogLogicObject(this, "", false);
    GameLogicLogger << ": ATTEMPT GOLD REMOVED by ";
    LogLogicObject(pSender, "", true);
    GameLogicLogger << " for amount = " << amount << " actually = " << realAmount << endl;
  }
	gold -= realAmount;
  return realAmount;
}
//////////////////////////////////////////////////////////////////////////
void PFBaseUnit::CancelAbilities()
{
  if (pAttackAbility)
    pAttackAbility->Cancel();

  for ( AbilityInstances::iterator iInst = abilityInstances.begin(), iEnd = abilityInstances.end(); iInst != iEnd; ++iInst )
    (*iInst)->Cancel();
}

void PFBaseUnit::CancelAllDispatchFromUnit( const PFBaseUnit* unit )
{
	for (ring::Range<AttackersRing> it(attackersRing); it; )
	{
		PFBaseUnit *pUnit = &(*it);
		++it;
    if ( pUnit == unit )
		  pUnit->DropTarget();
	}

  for (ring::Range<UnitDispatchesRing> it(inboundDispatches); it; )
  {
    PFDispatchUniformLinearMove *pDispatch = &(*it);
    ++it;
    if ( pDispatch && pDispatch->GetSender() == unit )
    {
      pDispatch->DropTarget();
    }
  }  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::KillUnit(const CPtr<PFBaseUnit>& pKiller /* = NULL */, int flags /* = UNITDIEFLAGS_NONE */, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
  health = 0;
  OnUnitDie( pKiller, flags, pDamageDesc );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags /* = UNITDIEFLAGS_NONE */, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/)
{
  DropTarget();
  StopAttackingMe();
  CancelAbilities();

  bool isRewardsForbidden = ( (flags & UNITDIEFLAGS_FORBIDREWARDS) != 0 );
	
  if (!isRewardsForbidden && IsGameLogicLogEnabled(this, false) )
  {
    GameLogicLogger << "Unit ";
    LogLogicObject(this, "", false);
    GameLogicLogger << ": KILLED by ";
    LogLogicObject(pKiller, "", false);
    GameLogicLogger << "\n";
  }

  NI_ASSERT( IsValid(this), "Strange, unit already dead?");

  // Kill all primary summons
  PFSummonedUnitBehaviour::UnsummonFunc unsummon( this );
  summonedUnits[NDb::SUMMONTYPE_PRIMARY]->ForAllBehaviour(unsummon);
  summonedUnits[NDb::SUMMONTYPE_PET]->ForAllBehaviour(unsummon);

  // Switch off abilities
  for (int i = 0, count = GetAbilitiesCount(); i < count; ++i)
  {
    if ( GetAbility(i) && GetAbility(i)->IsOn() )
      GetAbility(i)->SwitchOff();
  }

  PFAIWorld * pAIWorld = GetWorld()->GetAIWorld();
  bool isDeathDeferred = ( (flags & UNITDIEFLAGS_DEFERREDDEATH) != 0 );

  if(!isDeathDeferred)
  {
    // There are no needs to keep dead units in AIWorld
    if ( ringField.isLinked() )
      pAIWorld->UnregisterObjectOrUnit(this);
  }

  if( !isRewardsForbidden )
  {
    if (IsValid(pKiller))
    {
      pAIWorld->AwardKillers(this, pKiller);
    }

    if ( 0 == ( flags & UNITDIEFLAGS_UNSUMMON ) ) // Do not send die notification on unsummon
    {
      pAIWorld->SendUnitDieNotification( this, pKiller, pDamageDesc );
    }
    else /*if(!isRewardsForbidden)*/
    {
      EventHappened( PFBaseUnitEventUnitDeath( this, 0, 0, true ) );
    }
  }

  if ( (flags & UNITDIEFLAGS_DONTPLAYDEATHANIMATION) == 0 && !isDeathDeferred )
  {
    if ( ( flags & UNITDIEFLAGS_UNSUMMON ) == UNITDIEFLAGS_UNSUMMON )
    {     
      CALL_CLIENT(OnUnsummon);
    }
    else
    {
		  CALL_CLIENT(OnUnitDie);
    }
  }

	if (HasBehaviour())
		Behaviour()->OnUnitDie(pKiller);

  PFFsm::Cleanup();

  if(!isDeathDeferred)
  {
    RemoveBehaviour();
    CloseWarFog();
    GetWorld()->StoreDeadUnit(this);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::CleanupAfterDeath( bool bFullCleanUp )
{
  if ( IsValid(pAttackAbility) )
  {
    pAttackAbility->Cancel();
    if ( bFullCleanUp )
      pAttackAbility->ApplyPassivePart(false);
  }

  if (bFullCleanUp)
  {
    for ( vector<CObj<PFAbilityData>>::const_iterator it = externalPassiveAbilities.begin(); it != externalPassiveAbilities.end(); ++it )
    {
      if ( *it )
        (*it)->ApplyPassivePart(false);
    }
    externalPassiveAbilities.clear();

    RemoveAppliedApplicators();
    RemoveSentApplicators();
    DestroyAbilities();
  }
  else
  {
    RemoveAppliedApplicatorsOnDeath();
    RemoveSentApplicatorsOnDeath();
  }

  CleanupTauntApplicatorsStack();
  ClearAttackSectors();
  CleanupHistoryApplicators();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::DoAttack( bool allowAllies /*= false*/)
{
  if ( CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
    return false;

  // if we are not ready or target is invalid -> we can`t perform attack
  if ( !IsUnitValid(pCurrentTarget) || !IsReadyToAttack() )
    return false;

  const float attackSpeed = GetAttackSpeedInternal();

  NI_ASSERT( EPS_VALUE < attackSpeed, NStr::StrFmt( "Detected too small attack speed (%.3f) in <%s>. Check value of stat <%s>!", attackSpeed, GetDebugDescription(), NDb::KnownEnum<NDb::EStat>::ToString(NDb::STAT_ATTACKSPEED) ) );

  if(pAttackAbility)
  {
    pAttackAbility->DoAttack( Target(pCurrentTarget), allowAllies );

    EventHappened(NDb::BASEUNITEVENT_ATTACK);

    if ( PFBaseMovingUnit* pMovingUnit = dynamic_cast<PFBaseMovingUnit* >(this) )
      pMovingUnit->SetMoveDirection( pCurrentTarget->GetPosition().AsVec2D() );
    // Pass attack to client object
    CALL_CLIENT_2ARGS( OnAttack, pAttackAbility->GetTimeOffset( true ), pCurrentTarget->GetPosition().AsVec2D() );
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget )
{
  DEBUG_TARGETTING(NStr::StrFmt("OT-tid=%d,st=%d", (IsValid(pTarget))?(pTarget->GetObjectId()):(0), bStrongTarget))

    if ( !GetTargetingParams().onlyAutoTargeting && HasBehaviour() && Behaviour()->IsEnabled() )
		  Behaviour()->OnTarget(pTarget, bStrongTarget);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::IsReadyToAttack() const
{
  return pAttackAbility ? (1.0f - pAttackAbility->GetPreparedness() < EPS_VALUE) : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CObj<PFAbilityInstance> PFBaseUnit::UseMagic(int id, Target const &target)
//{
//  return NULL;
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//@todo [Oleg] include IsAbilityAvailible to this function
const bool PFBaseUnit::CanUseAbility(int id) const
{
	NI_ASSERT(NDb::ABILITY_ID_1 <= id && id <= NDb::ABILITY_ID_4, "Unsupported ability index");
	return !CheckFlagType( static_cast<NDb::EUnitFlagType>(NDb::UNITFLAGTYPE_FORBID_ABILITY1 + id - 1) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool PFBaseUnit::CanUseAbility(int id, Target const &) const
{
  return CanUseAbility(id);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool PFBaseUnit::CanUseAbility(CPtr<PFAbilityData> const &pAbility) const
{
  NI_VERIFY(IsValid(pAbility) && IsValid(pAbility->GetOwner()), "Invalid ability", return false);
  NI_VERIFY(pAbility->GetOwner()->GetObjectId() == GetObjectId(), "ObjectId mistmatch! Unit is not the ability owner", return false);

  int  const abilityIndex    = pAbility->GetAbilityTypeId() - NDb::ABILITYTYPEID_ABILITY0;
  bool const isNormalAbility = NDb::ABILITY_ID_1 <= abilityIndex && abilityIndex <= NDb::ABILITY_ID_4;
  bool const canUse          = isNormalAbility ? CanUseAbility(abilityIndex) : true;

  return canUse;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetVisibilityRange( ) const
{
  return GetStatValue( NDb::STAT_VISIBILITYRANGE );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetChaseRange( ) const
{
	return GetTargetingParams().chaseRange;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetTargetingRange( ) const
{
  return GetTargetingParams().targetingRange;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetAttackRange( ) const
{
  return GetStatValue( NDb::STAT_RANGE );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetAggroRange( ) const
{
  return GetTargetingParams().aggroRange;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBaseUnit::GetScreamRange( ) const
{
	NI_ASSERT(GetWorld() && GetWorld()->GetAIWorld(), "Invalid world");

  PFAIWorld* pAIWorld = GetWorld()->GetAIWorld();
  const NDb::UnitLogicParameters &unitPars = pAIWorld->GetUnitParameters( type );

  return unitPars.screamRange;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float PFBaseUnit::GetManaPercent() const
{
  const float maxEnergy = GetMaxMana();
  return (EPS_VALUE < maxEnergy) ? (energy / maxEnergy) : 0.0f;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PFBaseUnit::HasMana() const
{
  return GetMaxMana() > EPS_VALUE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class TFloat1>
const bool ChangeParam(TFloat1 &par, float delta, float minVal, float maxVal)
{
  if (par + delta > maxVal)
  {
    par = maxVal;
    return false;
  }
  else if (par + delta < minVal)
  {
    par = minVal;
    return false;
  }
  else
    par += delta;

  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool PFBaseUnit::ChangeHealth(float delta)
{
  return ChangeParam(health, delta, 1, GetMaxHealth());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool PFBaseUnit::ChangeMana(float delta)
{
  return ChangeParam(energy, delta, 0, GetMaxMana());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::TakeMana(const float value)
{
  NI_ASSERT(value >= 0.f, "Value should be positive");

  energy = max( 0.0, energy - value );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// For abilities that spend unit's life instead energy
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::TakeHealth(const float value)
{
  NI_ASSERT(value >= 0.f, "Value should be positive");

  health = max( 0.01f, health - value ); // This method should not set health to zero!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::AddFlag(unsigned int flag)
{
  if (IsGameLogicLogEnabled(this, false))
  {
    GameLogicLogger << "Unit ";
    LogLogicObject(this, "", false);
		GameLogicLogger << " ADD FORBID FLAGS:";
  }

  const bool wasStunned = IsStunned();
  const bool wasFreezed = CheckFlagType(NDb::UNITFLAGTYPE_FREEZE);

  int const numForbidFlags = NDb::KnownEnum<NDb::EUnitFlagType>::SizeOf();
  for (int i = 0; i < numForbidFlags; ++i)
  {
    if (flag & (1 << i))
    {
      NI_VERIFY(forbidFlags[i] >= 0, "Invalid forbid flag state", continue );
      ++forbidFlags[i];

			if (IsGameLogicLogEnabled(this, false))
			{
				GameLogicLogger << NDb::KnownEnum<NDb::EUnitFlagType>::ToString(static_cast<NDb::EUnitFlagType>(i));
			}
    }
  }

  if( !wasStunned && IsStunned() )
  {
    if (!wasFreezed && CheckFlagType(NDb::UNITFLAGTYPE_FREEZE) )
    {
      CALL_CLIENT_1ARGS(OnFreeze, true );
    }
    else
    {
      CALL_CLIENT_1ARGS(OnStunned, true );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveFlag(unsigned int flag)
{
  if (IsGameLogicLogEnabled(this, false))
  {
    GameLogicLogger << "Unit ";
    LogLogicObject(this, "", false);
		GameLogicLogger << " REMOVE FORBID FLAG: " << endl;
  }

  const bool wasStunned = IsStunned();
  const bool wasFreezed = CheckFlagType(NDb::UNITFLAGTYPE_FREEZE);

  int const numForbidFlags = NDb::KnownEnum<NDb::EUnitFlagType>::SizeOf();
  for (int i = 0; i < numForbidFlags; ++i)
  {
    if (flag & (1 << i))
    {
      NI_VERIFY(forbidFlags[i] > 0, "Invalid forbid flag state", continue );
      --forbidFlags[i];
			if (IsGameLogicLogEnabled(this, false))
			{
				GameLogicLogger << "      " << NDb::KnownEnum<NDb::EUnitFlagType>::ToString(static_cast<NDb::EUnitFlagType>(i)) << endl;
			}
    }
  }

  if( wasStunned && !IsStunned() )
  {
    if ( wasFreezed && !CheckFlagType(NDb::UNITFLAGTYPE_FREEZE) )
    {
      CALL_CLIENT_1ARGS(OnFreeze, false );
    }
    else
    {
      CALL_CLIENT_1ARGS(OnStunned, false );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::CheckFlagType(NDb::EUnitFlagType type) const
{
  NI_VERIFY(type >= 0 && type < forbidFlags.size(), NStr::StrFmt("Wrong flag type (%d)", (int)type), return false);

	return forbidFlags[type] != 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::CheckFlag(unsigned int flag) const
{
  int check = 0;
  for (int i = 0, count = NDb::KnownEnum<NDb::EUnitFlagType>::SizeOf(); i < count; ++i)
  {
    if ( forbidFlags[i] )
      check |= (1 << i);
  }

  return (check & flag) == flag;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::CopyFlagsFrom( const PFBaseUnit* pOther, bool addNotReplace )
{
  for (int i = 0, count = NDb::KnownEnum<NDb::EUnitFlagType>::SizeOf(); i < count; ++i)
  {
    if ( addNotReplace )
      forbidFlags[i] += pOther->forbidFlags[i];
    else 
      forbidFlags[i] = pOther->forbidFlags[i];
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::IsStunned() const
{
  return CheckFlagType(NDb::UNITFLAGTYPE_STUN);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::UpgradeStats(int count, float statsBonusBudget /* = 0.0f */)
{
	stats->Upgrade(naftaLevel, count, statsBonusBudget);
	RecalculateApplicators();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::UpgradeHeroStats(const int count, const float statsBonusBudget, const float fraction)
{
  stats->Upgrade(naftaLevel, count, statsBonusBudget, fraction);
  RecalculateApplicators();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::DoLevelups(int count, float statsBonusBudget /* = 0.0f */)
{
	if (count < 1)
		return;

	UpgradeStats(count, statsBonusBudget);
	naftaLevel += count;
  timeSinceLevelUp = 0.0f;

  OnLevelUp();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnLevelUp()
{
  if (IsGameLogicLogEnabled(this, false))
  {
    GameLogicLogger << "Unit ";
    LogLogicObject(this, "", false);
    GameLogicLogger << ": LEVEL UP (" << naftaLevel << ")\n";
  }

  // play levelup visual effect only for levels 2 - ...
  if (1 < naftaLevel)
    CALL_CLIENT_1ARGS(OnLevelUp,naftaLevel);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::SetNaftaLevel( int level )
{
  NI_VERIFY( level > 0, NStr::StrFmt( "Can't set Nafta Level of \"%s\" to %d! Level should be positive!", NStr::ToMBCS( GetDescription() ).c_str(), level ), return );
  naftaLevel = level;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::SetMurderContext(const MurderContext* const context)
{
  murderContext = context;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::GetAssistersCount() const
{
  if (murderContext)
    return murderContext->assisterCount;
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::GetSpecCount() const
{
  if (murderContext)
    return murderContext->spectatorCount;
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFBaseUnit::GetPresentTeamActiveMembers() const
{
  if (murderContext)
    return murderContext->presentTeamActiveMembers;
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::CanSee(const CVec3 &pos) const
{
  return CanSee( pos.AsVec2D() );
}

bool PFBaseUnit::CanSee(const CVec2 &pos) const
{
	CVec2 dist = pos - position.AsVec2D();
	float range = GetVisibilityRange();
	if ( fabs2(dist) < fabs2( range + GetWorld()->GetAIWorld()->GetMaxObjectSize() * 0.5f ) )
  {
    SVector tilePos = GetWorld()->GetTileMap()->GetTile(pos);
    return GetWorld()->GetFogOfWar()->CanObjectSeePosition(visUnitData[GetWarfogFaction()].warFogObjectID, tilePos);
  }
	else
		return false;
}

bool PFBaseUnit::CanSee(const SVector& tile) const
{
  CVec2 dist = GetWorld()->GetTileMap()->GetPointByTile(tile) - position.AsVec2D();
  float range = GetVisibilityRange();
  if ( fabs2(dist) < fabs2( range + GetWorld()->GetAIWorld()->GetMaxObjectSize() * 0.5f ) )
  {
    return GetWorld()->GetFogOfWar()->CanObjectSeePosition(visUnitData[GetWarfogFaction()].warFogObjectID, tile);
  }
  else
    return false;
}

bool PFBaseUnit::CanSee(const PFLogicObject &obj) const
{
  // I can always see myself
  if ( this == &obj )
    return true;

  if (obj.GetFaction() != GetFaction())
    return obj.IsVisibleForEnemy( GetFaction() ) && CanSee(obj.GetPosition());

  return CanSee(obj.GetPosition());
}

bool PFBaseUnit::IsPlacementVisible( int faction ) const
{
  SVector tilePos = GetWorld()->GetTileMap()->GetTile( GetPosition().AsVec2D() );
  return GetWorld()->GetFogOfWar()->IsTileVisible( tilePos, faction );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::IsVisibleForEnemy( int faction ) const
{
  if ( faction == NDb::FACTION_NEUTRAL )
  {
    if ( visibleForNeutral )
      return IsPlacementVisible( faction );
    return visibleForNeutral;
  }

  if ( faction >= 0 && visibleForEnemy )
  {
		return IsPlacementVisible( faction );
  }

  return visibleForEnemy;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool PFBaseUnit::IsVisibleForFaction( int faction ) const
{
  return faction == GetFaction() || IsVisibleForEnemy( faction );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::IsVisibleForFactionInternal(const NDb::EFaction faction) const
{
  if (faction == GetFaction())
    return true;

  switch (faction)
  {
  case NDb::FACTION_NEUTRAL:
    return visibleForNeutral;
  case NDb::FACTION_FREEZE:
  case NDb::FACTION_BURN:
    return visibleForEnemy;
  default:
    return false;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::SetVulnerable(bool vulnerable)
{
  if(vulnerable)
    RemoveFlag(NDb::UNITFLAG_FORBIDTAKEDAMAGE);
  else
    AddFlag(NDb::UNITFLAG_FORBIDTAKEDAMAGE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::Hide(bool hide)
{
  if ( hide )
  {
    AddFlag(NDb::UNITFLAG_ISOLATED | NDb::UNITFLAG_INVISIBLE);
    CloseWarFog(true);
  }
  else
  {
    RemoveFlag(NDb::UNITFLAG_ISOLATED | NDb::UNITFLAG_INVISIBLE);
    OpenWarFog();
  }

  CALL_CLIENT_1ARGS(OnHide, hide);
  UpdateHiddenState( !hide );

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ChangeFaction( NDb::EFaction newFaction )
{
	if (faction == newFaction)
		return;

	// Drop target on faction change
	if (IsValid(pCurrentTarget))
		DropTarget();

	// Stop attacking me coz I might be your faction
	StopAttackingMe();

	// Call parent
	PFLogicObject::ChangeFaction(newFaction);

  // Reopen War Fog for a new faction
  CloseWarFog(true);
  OpenWarFog();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OpenWarFog()
{
  float visRange = GetVisibilityRange();
  if ( visRange > 0.0f )
    OpenWarFog(GetWarfogFaction(), -1.0f, visRange);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OpenWarFog(NDb::EFaction _faction, float timeout, float radius)
{
  if (IsDead()) // Dead unit does not open War Fog
    return;

  NI_VERIFY( _faction >= 0 && _faction < visUnitData.size(), 
              NStr::StrFmt("Wrong faction %d or not initialized IDs vector!", _faction), return );
  NI_VERIFY( timeout > 0.0f || timeout == -1.0f, 
              NStr::StrFmt("Wrong timout value for opening WarFog: %f! Should be > 0.", timeout), return );
  NI_VERIFY( radius > 0.0f, NStr::StrFmt("Wrong radius value for opening WarFog: %f! Should be > 0.", radius), return );

  PFWorld * pWorld = GetWorld();
  NI_VERIFY(pWorld, "Failed to get World!", return);
  FogOfWar * pWarFog = pWorld->GetFogOfWar();
  NI_VERIFY(pWarFog, "Failed to get War Fog!", return);
  TileMap * pTileMap = pWorld->GetTileMap();
  NI_VERIFY(pTileMap, "Failed to get Tile map!", return);

  SVector position = pTileMap->GetTile(GetPosition().AsVec2D());
  int visTileRange = pTileMap->GetLenghtInTiles(radius);

  if (visUnitData[_faction].warFogObjectID != WAR_FOG_BAD_ID)
    pWarFog->ChangeVisibility(visUnitData[_faction].warFogObjectID, visTileRange);
  else
    visUnitData[_faction].warFogObjectID = pWarFog->AddObject(position, _faction, visTileRange);

  visUnitData[_faction].visRadius = radius;
  visUnitData[_faction].timeOut = max(timeout, visUnitData[_faction].timeOut);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::CloseWarFog(bool immediately /*= false*/)
{
  PFWorld * pWorld = GetWorld();
  NI_VERIFY(pWorld, "Failed to get World!", return);
  FogOfWar * pWarFog = pWorld->GetFogOfWar();
  NI_VERIFY(pWarFog, "Failed to get War Fog!", return);

  SVector position;

  if (!immediately)
  {
    TileMap * pTileMap = pWorld->GetTileMap();
    const NDb::UnitDeathParameters* deathParams = GetDeathParams();
    if(pTileMap && deathParams)
    {
      position = pTileMap->GetTile(GetPosition().AsVec2D());
      visUnitData[faction].visRadius = pTileMap->GetLenghtInTiles(GetVisibilityRange());
      visUnitData[faction].timeOut = deathParams->observeOffset;
    }
    else
    {
      immediately = true;
    }
  }

  for (int i=0; i < visUnitData.size(); ++i)
  {
    if (visUnitData[i].warFogObjectID != WAR_FOG_BAD_ID)
    {
      // If not required to close immediately - add temp object to keep War Fog open for a while
      if (!immediately && visUnitData[i].timeOut > 0.0f)
        pWarFog->AddTempObject(position, i, visUnitData[i].visRadius, visUnitData[i].timeOut);

      pWarFog->RemoveObject(visUnitData[i].warFogObjectID);
      visUnitData[i].Clear();
    }
  }
}

//////////////////////////////////////////////////////////////////////////
const NDb::UnitDeathParameters* PFBaseUnit::GetDeathParams() const
{
  if (IsValid(dbUnitDesc) && IsValid(dbUnitDesc->deathParameters))
    return dbUnitDesc->deathParameters;

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const wstring& PFBaseUnit::GetFactionName() const
{
  NI_VERIFY( GetWorld() && GetWorld()->GetAIWorld(), "Invalid Player or World!", return NNameMap::wstrNoname; );

  return GetWorld()->GetAIWorld()->GetFactionName(faction);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFVoxelMap* PFBaseUnit::GetVoxelMap() const
{
	return GetWorld()->GetAIWorld();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TileMap* PFBaseUnit::GetTileMap() const
{
	return GetWorld()->GetTileMap();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::AILogicParameters& PFBaseUnit::GetAIParameters() const
{
	return GetWorld()->GetAIWorld()->GetAIParameters();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::SetLastAttackData(CPtr<PFBaseUnit> const & pVictim, const bool byAutoAttack, const NDb::EFaction originalFaction)
{
  AttackDataHelper::SetAttackData(lastAttack, pVictim, byAutoAttack, originalFaction);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::SetLastAttackDataEx(CPtr<PFBaseUnit> const & pVictim, const bool byAutoAttack, const bool byAggressiveDispatch, const NDb::EFaction originalFaction)
{
  struct Local
  {
    static inline bool IsLikeHero(const CPtr<PFBaseUnit>& victim)
    {
      switch (victim->GetUnitType())
      {
      case NDb::UNITTYPE_HEROMALE:
      case NDb::UNITTYPE_HEROFEMALE:
        return victim->IsTrueHero();
      case NDb::UNITTYPE_SUMMON:
        return victim->IsLikeHero();
      default:
        return false;
      }
    }
  };

  if (byAggressiveDispatch && Local::IsLikeHero(pVictim))
    AttackDataHelper::SetAttackData(lastHeroAttack, pVictim, byAutoAttack, originalFaction);
  else
    AttackDataHelper::SetAttackData(lastAttack, pVictim, byAutoAttack, originalFaction);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::StepLastAttackData(float dtInSeconds)
{
  struct Local
  {
    static inline bool CanChase(const PFBaseUnit* const unit, const PFBaseUnit* const target)
    {
      const float range = unit->GetChaseRange();

      if (range < EPS_VALUE)
        return true;

      return unit->IsTargetInRange(target, range);
    }

    static inline bool CanSee(const PFBaseUnit* const unit, const PFBaseUnit* const target)
    {
      return target->IsVisibleForEnemy(unit->GetFaction());
    }
  };

  if (IsValid(lastAttack.pVictim))
  {
    const bool canChase = Local::CanChase(lastAttack.pVictim, this);
    const bool canSee = Local::CanSee(lastAttack.pVictim, this);

    if ( canSee && canChase )
    {
      lastAttack.timePassed += dtInSeconds;
    }
    else
    {
      RemoveLastAttackData();
    }
  }

  if (IsValid(lastHeroAttack.pVictim))
  {
    const bool canChase = Local::CanChase(lastHeroAttack.pVictim, this);
    const bool canSee = Local::CanSee(lastHeroAttack.pVictim, this);

    if ( canSee && canChase )
    {
      lastHeroAttack.timePassed += dtInSeconds;
    }
    else
    {
      RemoveLastHeroAttackData();
    }
  }

  // update last damage time
  lastDamage.timeOver += dtInSeconds;
}


void PFBaseUnit::AddToPriorityTargets( const CPtr<PFBaseUnit>& pTarget ) 
{
  if ( !IsValid(pTarget) )
    return;

  const CPtr<PFBaseUnit>& pTargetNew = pTarget->IsAlphaSummon() ? pTarget->GetMasterUnit() : pTarget;

  if ( !IsValid(pTargetNew) )
    return;

  int targetId = pTargetNew->GetObjectId();
  TPriorityTargets::iterator it = priorityTargets.find( targetId );
  if ( it == priorityTargets.end() )
    priorityTargets[targetId] = PriorityTarget(pTargetNew, targetId, GetTargetingParams().maxTimeFromAttack);
  else
    it->second.timeOut = GetTargetingParams().maxTimeFromAttack;

}

void PFBaseUnit::UpdatePriorityTargets( float dt )
{
  list<int> toDelete;
  TPriorityTargets::iterator it = priorityTargets.begin();
  for ( ; it != priorityTargets.end(); ++it )
  { 
    PriorityTarget& pt = it->second;
    pt.timeOut -= dt;
    if (pt.timeOut <= 0 || !IsValid(pt.pTarget) )
      toDelete.push_back(pt.objectId);
  }

  list<int>::iterator key = toDelete.begin();
  for ( ; key != toDelete.end(); ++key )
    priorityTargets.erase(*key);
}

bool PFBaseUnit::IsPriorityTarget( const CPtr<PFBaseUnit>& pTarget ) const
{
  if ( !IsValid(pTarget) )
    return false;

  TPriorityTargets::const_iterator it = priorityTargets.find( pTarget->GetObjectId() );
  
  return it != priorityTargets.end();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveLastAttackData()
{
  lastAttack.Clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveLastHeroAttackData()
{
  lastHeroAttack.Clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnBecameIdle()
{
  if(NGameX::PFClientBaseUnit* pClient = ClientObject())
    pClient->OnBecameIdle();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ForceIdle()
{
  if(NGameX::PFClientBaseUnit* pClient = ClientObject())
    pClient->ForceIdle();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::Idle()
{
  if ( NGameX::PFClientCreature* pClient = dynamic_cast<NGameX::PFClientCreature*>(ClientObject()) )
    pClient->Idle();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MakeSpellTargetFactionFlags(const PFBaseUnit &unit, NDb::ESpellTarget spellTarget)
{
	NDb::EFaction faction = unit.GetFaction();

	int factionFlags = 0;
  if (spellTarget & NDb::SPELLTARGET_NEUTRAL)
    factionFlags |= (1L << NDb::FACTION_NEUTRAL);
	if (spellTarget & NDb::SPELLTARGET_ALLY)
		factionFlags |= (1L << faction);
	if (spellTarget & NDb::SPELLTARGET_ENEMY)
		factionFlags |= unit.GetOppositeFactionFlags();

	return factionFlags;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::DumpInfo(NLogg::CChannelLogger &stream) const
{
	// Forbid flags
	LogLogicInfo(stream)("  forbid flags:\n");
	for (int i = 0; i < NDb::KnownEnum<NDb::EUnitFlagType>::sizeOf; i++)
	{
		if (!forbidFlags[i])
			continue;

		LogLogicInfo(stream)("    %s: %i\n", NDb::EnumToString(NDb::EUnitFlagType(i)), forbidFlags[i]);
	}

	// Attackers
	LogLogicInfo(stream)("  attacked by:\n");
	for (ring::Range<AttackersRing> it(attackersRing); it; ++it)
	{
		LogLogicInfo(stream)("    %s @ %3.1f %3.1f\n", MakeUnitIDString(&(*it)), it->GetPosition().x, it->GetPosition().y);
	}

	// Variables
	LogLogicInfo(stream)("  variables:\n");
	for (ring::Range<Variable::Ring> it(variablesRing); it; ++it)
	{
		LogLogicInfo(stream)("    %s = %4.3f\n", it->name.c_str(), it->var.GetValue());
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ForAllSummons(ISummonAction &action, NDb::SummonType type)
{
  struct ForAll : public NonCopyable
  {
    ForAll(ISummonAction &action, PFBaseUnit const* master) : action(action), master(master) {}
    void operator()(PFSummonBehaviour *pBehaviour)
    {
      if ( pBehaviour->GetUnit()->GetMasterUnit() == master )
        action(pBehaviour->GetUnit());
    }
    ISummonAction &action;
    PFBaseUnit const* master;
  } f(action, this);
  summonedUnits[type]->ForAllBehaviour(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveBehaviour()
{
  while (!behaviourList.empty())
  {
    PFBaseBehaviour *pBehaviour = behaviourList.first();
    pBehaviour->OnStop();
    PFBaseBehaviour::UnitRing::safeRemove(pBehaviour);
  }
}

void PFBaseUnit::Reset()
{
	PFLogicObject::Reset();

  //ResetWarFog();

	description       = dbUnitDesc->description.GetText();
	pImage            = dbUnitDesc->image;

  derStats = new NGameX::DerStatsNameMap(this);
  condsResolver.Init(this);

#ifndef _SHIPPING
	debugDescription =  GetFormattedDbId(dbUnitDesc->GetDBID());
	debugObject = CreateDebugObject();
#endif
  
  shouldRestoreStatusEffects = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::OnAfterReset()
{
  PFLogicObject::OnAfterReset();
  UpdateClientColor();

  if ( NScene::SceneObject * pSObj = GetClientSceneObject() )
    pSObj->SetForbidPick( CheckFlag( NDb::UNITFLAG_FORBIDPICK ) );

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::CountAuraApplicators( int& allyAuraCount, int& enemyAuraCount )
{
  struct CountAuras
  {
    CountAuras() : allyAuraCount(0), enemyAuraCount(0) {}

    void operator()( const CObj<PFBaseApplicator>& pAppl )
    {
      if ( pAppl->GetTypeId() != PFApplAura::typeId )
        return;

      // Cast to aura
      PFApplAura* pAura = static_cast<PFApplAura*>( pAppl.GetPtr() );

      // Do not confuse with NDb::EAuraType!!!
      const NDb::EAuraVisualType& auraVisualType = pAura->GetDB().type;

      if ( auraVisualType == NDb::AURAVISUALTYPE_ALLY )
        allyAuraCount++;
      else if ( auraVisualType == NDb::AURAVISUALTYPE_ENEMY )
        enemyAuraCount++;
    }

    int allyAuraCount;
    int enemyAuraCount;

  } countAuras;

  ForAllAppliedApplicators( countAuras );

  allyAuraCount  = countAuras.allyAuraCount;
  enemyAuraCount  = countAuras.enemyAuraCount;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::ApplyTopBehaviour()
{
	PFBaseBehaviour *pBehaviour = Behaviour();

  PFSummonBehaviour *pSummonBehaviour = dynamic_cast<PFSummonBehaviour*>(pBehaviour);
  CPtr<PFBaseUnit> pNewMaster = pSummonBehaviour ? pSummonBehaviour->GetMaster() : 0;

  // Handle case when primary summon master is dead or master already has maximum summons of specified type
  if ( IsValid(pNewMaster) )
  {
    if ( PFSummonedUnitAIBehaviour *pSummonedUnitAIBehaviour = dynamic_cast<PFSummonedUnitAIBehaviour*>(pBehaviour) )
    {
      NDb::SummonType summonType = pSummonedUnitAIBehaviour->GetSummonType();
      if ( pNewMaster->IsDead() && summonType == NDb::SUMMONTYPE_PRIMARY
        || pNewMaster->GetSummonsCount( summonType, pSummonedUnitAIBehaviour->GetGroupName() ) == pNewMaster->GetMaxAllowedSummons( summonType, pSummonedUnitAIBehaviour->GetGroupName() ) )
      {
        pSummonedUnitAIBehaviour->Unsummon();
        return;
      }
    }
  }

	// Drop everything coz behaviour change is a shock =))
	DropStates();
	DropTarget();
  ClearScreamTargets();
  RemoveLastAttackData();
  RemoveLastHeroAttackData();

	// Replace faction
	if (GetFaction() != pBehaviour->GetFaction())
	{
		ChangeFaction(pBehaviour->GetFaction());
	}

	// Replace unit type
	if (GetUnitType() != pBehaviour->GetUnitType())
	{
		SetUnitType(pBehaviour->GetUnitType());
	}

  // add behavior to master's summoned group; summons count changes here
  pBehaviour->Resume();

  // Change master & color
	if (pMaster != pNewMaster)
	{
		SetMaster(pNewMaster);
		if (!UpdateClientColor() )
		{
			CALL_CLIENT(ResetColor);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBaseUnit::UpdateClientColor() 
{
  
  if ( IsValid(pMaster) && pMaster->IsHero()) 
  {
    const PFBaseHero* pHero = dynamic_cast<const PFBaseHero*>(pMaster.GetPtr()); // used for GetInTeamId() only ...
    NI_ASSERT(pHero, "pMaster must be a Hero");

    int   masterId  = pHero->GetInTeamId();
    Render::HDRColor const& masterColor = GetWorld()->GetAIWorld()->GetHeroColor(pMaster->GetFaction(), masterId);
    CALL_CLIENT_1ARGS(Recolor, masterColor);
    return true;
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::AddBehaviourOnTop( PFBaseBehaviour* pBehaviour)
{
  NI_PROFILE_FUNCTION

  if ( HasBehaviour() )
    Behaviour()->Suspend();

  behaviourList.addFirst(pBehaviour);
	ApplyTopBehaviour();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::RemoveBehaviour( PFBaseBehaviour* pBehaviour)
{
	if (IsDead()) // All behaviours was already removed
		return;

	bool isTopChanging = pBehaviour == Behaviour();
	behaviourList.safeRemove(pBehaviour);
	pBehaviour->OnStop();
	if (isTopChanging && HasBehaviour())
		ApplyTopBehaviour();
}

float PFBaseUnit::GetNormalLevelling() const
{
  NI_VERIFY( dbUnitDesc, NStr::StrFmt( "%s has invalid unit description!", GetDebugDescription() ), return 0.0f; )
  return dbUnitDesc->normalLevelling;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::CancelChannelling()
{
  EventHappened( PFBaseUnitEvent( NDb::BASEUNITEVENT_CHANNELINGCANCELED ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBaseUnit::SetHappy()
{
  CALL_CLIENT_1ARGS( SetHappyState, NGameX::EHappyState::Happy );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Usable
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::Ability* PFBaseUnit::GetExternalAbility() const
{
  return dbUnitDesc->interaction ? dbUnitDesc->interaction->externalAbility : 0;
}

bool PFBaseUnit::CheckUseLimitations( PFBaseUnit const* pUnit, NDb::CastLimitation const*& castLimitation ) const
{
  if ( !GetExternalAbility() )
    return false;

  CObj<PFAbilityData> pAbilityData = new PFAbilityData( const_cast<PFBaseUnit*>(pUnit), GetExternalAbility(), NDb::ABILITYTYPEID_SPECIAL, false );
  const Target target(const_cast<PFBaseUnit*>(this));
  castLimitation = pAbilityData->CheckCastLimitations( target );
  return castLimitation == 0;
}

// Can unit be used by a unit at the moment
bool PFBaseUnit::CanBeUsedBy( PFBaseUnit const* pUnit ) const
{
  NDb::CastLimitation const* tmp = 0;
  return !pUnit->IsMounted() && pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDINTERACT) == false && CheckUseLimitations( pUnit, tmp );
}

// Is unit usable by a unit in general
bool PFBaseUnit::IsUsableBy( PFBaseUnit const* pUnit ) const
{
  return IsValid(dbUnitDesc) && dbUnitDesc->interaction && dbUnitDesc->interaction->externalAbility && ( GetFactionMask( dbUnitDesc->interaction->allowedFactions ) & (1 << pUnit->GetFaction()) );
}

CObj<PFAbilityInstance> PFBaseUnit::Use( PFBaseUnit* pUser )
{
  if ( CanBeUsedBy( pUser ) )
  {
    CObj<PFAbilityInstance> pAbilityInstance = pUser->UseExternalAbility( GetExternalAbility(), (const Target)(this) );
    pUser->EventHappened( PFBaseUnitAbilityStartEvent( pAbilityInstance.GetPtr() ) );
    return pAbilityInstance;
  }
  return 0;
}

float PFBaseUnit::GetUseRange( PFBaseUnit* pUser ) const
{
  const NDb::Ability* pDBAbility = GetExternalAbility();
  NI_VERIFY( pDBAbility, "No external ability", return 0.0f );

  CObj<PFAbilityData> pAbility = new PFAbilityData( pUser, pDBAbility, NDb::ABILITYTYPEID_SPECIAL );
  return pDBAbility->useRange(pUser, this, pAbility, 0.0f);
}

bool PFBaseUnit::IsLikeHero() const
{
  if (!IsAlphaSummon())
    return false;

  const CDynamicCast<const PFSummonBehaviour> behaviour(GetBehaviour());

  if (!IsValid(behaviour))
    return false;

  return behaviour->IsLikeHero();
}

void PFBaseUnit::OnSerialize(IBinSaver& f)
{
  if (f.IsReading())
  {
    // NOTE: десериализаци€ контейнера переменных не уничтожает элементы
    variablesRing.clear(ring::DeleteEraser<Variable>());
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Debug code
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _SHIPPING

CObj<NDebug::DebugObject> PFBaseUnit::CreateDebugObject()
{
  //return CObj<NDebug::DebugObject>(0);
  return CObj<NDebug::DebugObject>(new PFBaseUnitDebug(this));
}

bool PFBaseUnitDebug::IsObjectValid() const { return IsValid(pOwner); }

namespace
{

struct ShowTarget : public NonCopyable
{
  ShowTarget(PFBaseUnit const &_owner, Render::IDebugRender *_pRender) : owner(_owner), pRender(_pRender) {};

  void operator ()(PFBaseUnit &unit)
  {
    const CPtr<PFBaseUnit> pUnit = &unit;

    bool bVisible = owner.CanSee(unit);

    pRender->DrawText3D( NI_STRFMT( "%.2f", owner.GetTargetWeight( pUnit, owner.GetTargetingParams(), 0 ) ), unit.GetPosition(), 15, Render::Color( 255, 0, 255 ) );
    
    if ( bVisible && owner.IsTargetInAttackRange( pUnit ) )
    {
      pRender->DrawPoint3D(unit.GetPosition(), 0.5f, g_attackRangeColor, false);
      return;
    }

    if (bVisible)
    {
      pRender->DrawPoint3D(unit.GetPosition(), 0.5f, g_visibilityRangeColor, false);
      return;
    }

    pRender->DrawPoint3D(unit.GetPosition(), 0.5f, g_targetRangeColor, false);
  }

  const PFBaseUnit &owner;
  Render::IDebugRender *pRender;
}; // Show target

}

bool PFBaseUnitDebug::Process(Render::IDebugRender* pRender)
{
  if (DebugObject::Process(pRender))
    return true;
  if (!IsValid(pOwner))
    return true;
  if (!IsSelected())
    return true;

  PFAIWorld* pAIWorld = pOwner->GetWorld()->GetAIWorld();

  CVec3 vPos = pOwner->GetVisualPosition3D();

  if (g_showVisibilityRange)
  {
    pRender->DrawCircle3D(vPos, pOwner->GetVisibilityRange(), 16, g_visibilityRangeColor, false);
  }
  if (g_showAttackRange)
  {
    pRender->DrawCircle3D(vPos, pOwner->GetAttackRange() + pOwner->GetObjectSize() / 2, 16, g_attackRangeColor, false);
  }
  if (g_showTargetRange)
  {
    pRender->DrawCircle3D(vPos, pOwner->GetTargetingRange() + pOwner->GetObjectSize() / 2, 16, g_targetRangeColor, false);
  }
  if (g_showTarget)
  {
    float range = pOwner->GetTargetingRange();

    // –адиус поиска увеличен на макс. размер юнита дл€ того, чтобы учесть размеры юнитов при вычислении дистанции между ними.
    // ј при проверке целей, из результатов поиска отсекаютс€ те, до которых слишком далеко (IsInAttackRange)
    float searchRadius = range + ( pOwner->GetObjectSize() + pAIWorld->GetMaxObjectSize() ) / 2;

    ShowTarget targetFinder(*pOwner.GetPtr(), pRender);

    // find flying targets too if can hit them
    int targetTypesToFind = NDb::SPELLTARGET_ALL | NDb::SPELLTARGET_FLYING;
    pAIWorld->ForAllUnitsInRange( pOwner->GetPosition(), searchRadius, targetFinder, UnitMaskingPredicate(pOwner->GetOppositeFactionFlags(), targetTypesToFind ) );

    if (IsValid(pOwner->GetCurrentTarget()))
      pRender->DrawPoint3D(pOwner->GetCurrentTarget()->GetPosition(), 0.5f, Render::Color(0,0,255), false);
  }
  if (g_debugHeroAIStates && pOwner->GetCurrentStateName())
  {
    CVec3 pos = pOwner->GetPosition();
    pos.z += 3.0f;
    Render::Color white( 255, 255, 255, 255 );
    Render::DebugRenderer::DrawText3D( pOwner->GetCurrentStateName(), pos, 20, white);

    //pos.z += 8.0f;
    //Render::DebugRenderer::DrawText3D( NStr::StrFmt("cp(x,y):(%f,%f)",pos.X(), pos.Y()) , pos, 20, white);

    if(g_debugPrintHeroAIStates)
      DevTrace(pOwner->GetCurrentStateName());
  }
  if(g_showLeashRange)
  {
    if(pOwner->HasBehaviour())
    {
      if(const PFBaseBehaviour* pBehaviour = pOwner->GetBehaviour())
      {
        const PFSummonedUnitAIBehaviour* pSummonedBehaviour = dynamic_cast<const PFSummonedUnitAIBehaviour*>(pBehaviour);
        if(pSummonedBehaviour)
        {
          float radius =  pSummonedBehaviour->GetLashRange() + pOwner->GetObjectSize() / 2;
          pRender->DrawCircle3D(vPos, radius, 16, g_leashRangeColor, false);          
        }
      }
    }
  }

  return false;
}
#endif // _SHIPPING

} // namespace NWorld

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFBaseUnit, NWorld)

BASIC_REGISTER_CLASS( NWorld::PFBaseUnitEventListener );


REGISTER_DEV_VAR("find_target_ext", g_bUseTestFindTargetMode, STORAGE_NONE);
REGISTER_DEV_VAR("debug_noDamage",  g_bDebugNoDamage,         STORAGE_NONE);
REGISTER_DEV_VAR("show_visibility_range", g_showVisibilityRange, STORAGE_NONE);
REGISTER_DEV_VAR("show_attack_range", g_showAttackRange, STORAGE_NONE);
REGISTER_DEV_VAR("show_target_range", g_showTargetRange, STORAGE_NONE);
REGISTER_DEV_VAR("show_target", g_showTarget, STORAGE_NONE);
REGISTER_DEV_VAR("debug_targeting", g_debugTargetting, STORAGE_NONE);
REGISTER_DEV_VAR("debug_hero_ai_states", g_debugHeroAIStates, STORAGE_NONE);
REGISTER_DEV_VAR("debug_print_hero_ai_states", g_debugPrintHeroAIStates, STORAGE_NONE);
REGISTER_DEV_VAR("show_leash_range", g_showLeashRange, STORAGE_NONE);

#ifdef EXPOMODE
REGISTER_VAR( "immortal_heroes", g_immortalHeroes, STORAGE_NONE )
#else
REGISTER_DEV_VAR( "immortal_heroes", g_immortalHeroes, STORAGE_NONE )
#endif

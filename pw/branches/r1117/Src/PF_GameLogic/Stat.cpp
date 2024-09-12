#include "stdafx.h"

#include "Stat.hpp"
#include "PFWorld.h"
#include "PFAIWorld.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace nstl
{
  // used in PFStatContainer::Load(...)
  inline bool operator==(const NDb::UnitStat& stat, const NDb::EStat& id)
  {
    return stat.statId == id;
  }
} //namespace nstl
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
  struct StatUpgradeLevelLess
  {
    bool operator () (NDb::StatUpgrade const& l, NDb::StatUpgrade const& r) const
    {
      return l.level < r.level;
    }
  };

  struct StatFormulaParams : public IMiscFormulaPars
  {
    StatFormulaParams(NDb::Ptr<NDb::UnitConstantsContainer> const &pConstants) : pConstants(pConstants) {}

    //parameters
    virtual bool  IsAbilityOn() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return false; }
    virtual int   GetRank() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual float GetDist2Target() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0.0f; }
    virtual float GetScale() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0.0f; }
    virtual float GetParentScale() const{ NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0.0f; }
    virtual float GetManaCost() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0.0f; }
    virtual float GetPreparedness() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0.0f; }
    virtual int   GetAbilityType() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual bool  Roll(float probability) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return false; }
    virtual int   GetTerrainType() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual int   GetRefineRate() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual int   GetTalentLevel() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual bool  IsTalentBought() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return false; }
    virtual int   GetTalentDevPoints() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual int   GetNaftaCost() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual float GetCooldown() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual int   GetScrollLevel() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual bool  IsNight() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return false; }
    virtual bool  CheckUpgradePerCastPerTarget() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return false; }

    //objects
    virtual const IUnitFormulaPars* GetObjectOwner() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return NULL; }
    virtual const IMiscFormulaPars* GetObjectParent() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return NULL; }     

    virtual const IUnitFormulaPars* GetObject( char const*) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return NULL; }
    
    virtual float GetVariable(const char *name) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0.0f; };

    virtual CVec2 GetTargetPos() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return VNULL2; };

    virtual int   GetRandom(int from, int to) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }

    virtual float GetConstant(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver) const;
    virtual float GetAbilityScale( bool isDamage, float statValue, EAbilityScaleMode abScaleMode, float valueLeft, float valueRight, bool bRound = true ) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0.0f; }
    virtual bool  GetSmartRoll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return false; }
    virtual int   GetSmartRandom( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; }
    virtual float GetRefineAbilityScale( float valueAtRefineLevel0, float valueAtRefineLevel6 ) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return 0; } 
    virtual int   GetAlternativeTargetIndex() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return -1; }
    virtual float GetTerrainPart(int faction) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return -1; }
    virtual int   GetActivatedWithinKit() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return -1; }
    virtual int   GetTalentsWithinKit() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return -1; }
    virtual float GetStatusDispellPriority( const IUnitFormulaPars* pUnitToCheck, bool returnDuration ) const { return 0.0f; };
    virtual CVec2 GetVectorVariable(const char *name) const { return VNULL2; }
    
    virtual int   GetTerrianTypeUnderCursor() const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return -1; }
    virtual int GetNatureTypeInPos(CVec2 pos) const { NI_ALWAYS_ASSERT("Only const variables may be used in Stats"); return -1; }

  protected:
    NDb::Ptr<NDb::UnitConstantsContainer> pConstants;
  };

  float StatFormulaParams::GetConstant(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver) const
  {
    NDb::UnitConstant const* pConstant = NULL;
    
    const vector<NDb::Ptr<NDb::UnitConstant>>& glob = pConstants->vars;
    for( vector<NDb::Ptr<NDb::UnitConstant>>::const_iterator iConst = glob.begin(), iEnd = glob.end(); iConst != iEnd; ++iConst )
    {
      if ( (*iConst) && (*iConst)->name == name )
      {
        pConstant = (*iConst).GetPtr();
        break;
      }
    }

    NI_DATA_VERIFY( pConstant, NStr::StrFmt( "Constant '%s' not found in globalConstants!", name ), return 0.0f; );

    return pConstant->var(pSender, pReceiver, this, 0.0f);
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatContainer::StatUpgradeInfo::Initialize( const NDb::UnitStat& desc, float incr )
{
  upgrades   = desc.levelUpgrades;
	increment  = incr;
  sort( upgrades.begin(), upgrades.end(), StatUpgradeLevelLess() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN(PFStatContainer)
  NAMEMAP_CUSTOM_SUBMAP( inc, &statIncProxy, &statIncProxy )
  NAMEMAP_CUSTOM_SUBMAP( incGE1, &statIncGE1Proxy, &statIncGE1Proxy )
NAMEMAP_END

NAMEMAP_BEGIN(PFStatContainer::StatIncrementProxy)
NAMEMAP_END;

NAMEMAP_BEGIN(PFStatContainer::StatIncrementGE1Proxy)
NAMEMAP_END;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFStatContainer::PFStatContainer( PFWorld* world )
  : PFWorldObjectBase( world, 0 )
  , totalIncrementBudget(0.0f)
  , incrementForceModifier(1.0f)
  , averageIncPercent(0.0f)
  , upgradedIncrementBudget(0.0f)
  , upgradeCounter(0)
{
	values.resize( NDb::KnownEnum<NDb::EStat>::sizeOf, StatValueWithModifiers() );
	upgrades.resize( NDb::KnownEnum<NDb::EStat>::sizeOf, StatUpgradeInfo() );
  Reset();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StatVariant : public NNameMap::Variant, NonCopyable
{
public:
  StatVariant(CPtr<PFStatContainer> const& pContainer, NDb::EStat eStat, bool bIncrement = false, bool bRetBool = false)
    : pContainer(pContainer)
    , eStat(eStat)
    , bIncrement(bIncrement)
    , bRetBool(bRetBool)
  {
  }
  
  virtual float GetFloat() const
  {
    if ( !IsValid(pContainer) )
      return 0.0f;
    if ( bIncrement )
      return pContainer->GetIncrementForUI(eStat);
    else
      return pContainer->GetValue(eStat);
  }

  // used with <if> tag to compare stat inc >= 1
  virtual bool GetBool() const
  {
    if ( !IsValid(pContainer) )
      return false;
    if ( bIncrement )
      return pContainer->GetIncrementForUI(eStat) >= 1.0f;
    else
      return pContainer->GetValue(eStat) >= 1.0f;
  }

  virtual NNameMap::VariantType::Enum GetType() const { return bRetBool ? NNameMap::VariantType::Bool : NNameMap::VariantType::Float; }
  virtual bool IsReadonly() const                     { return true; }

private:
  CPtr<PFStatContainer> pContainer;
  NDb::EStat            eStat;
  bool                  bIncrement;
  bool                  bRetBool;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NNameMap::Variant * PFStatContainer::ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
{
  NI_DATA_VERIFY( name && name[0], "Stat name shouldn't be empty", return 0; );
  NI_DATA_ASSERT( !argsLength, "Arguments are not supported in unit.stat" );
  NDb::EStat eStat = NDb::StringToEnum_EStat(name);
  return new StatVariant(this, eStat);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NNameMap::Variant * PFStatContainer::StatIncrementProxy::ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
{
  NI_DATA_VERIFY( name && name[0], "Stat name shouldn't be empty", return 0; );
  NI_DATA_ASSERT( !argsLength, "Arguments are not supported in unit.inc.stat" );
  NDb::EStat eStat = NDb::StringToEnum_EStat(name);
  return new StatVariant( pContainer, eStat, true );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NNameMap::Variant * PFStatContainer::StatIncrementGE1Proxy::ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
{
  NI_DATA_VERIFY( name && name[0], "Stat name shouldn't be empty", return 0; );
  NI_DATA_ASSERT( !argsLength, "Arguments are not supported in unit.inc.stat" );
  NDb::EStat eStat = NDb::StringToEnum_EStat(name);
  return new StatVariant( pContainer, eStat, true, true );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatContainer::Load( const NDb::StatsContainer* pStats, const NDb::Ptr<NDb::UnitConstantsContainer>& pConstants,
                           const NDb::Ptr<NDb::StatsEnhancersContainer>& pStatsEnhancers )
{
  if ( !pStats )
  {
    return;
  }

  StatFormulaParams params( pConstants );

  for ( vector<NDb::UnitStat>::const_iterator it = pStats->stats.begin(); it != pStats->stats.end(); ++it )
  {
    NI_DATA_ASSERT( nstl::count( pStats->stats.begin(), pStats->stats.end(), it->statId ) == 1,
      NStr::StrFmt( "Stat %s found more that once in container \"%s\"", NDb::EnumToString( it->statId ), NDb::GetFormattedDbId( pStats->GetDBID() ).c_str() ) );

    float value     = it->value( NULL, NULL, &params );
    float increment = it->increment( NULL, NULL, &params );

    if ( pStatsEnhancers != 0 )
    {
      for ( vector<NDb::StatEnhancer>::const_iterator enhancer = pStatsEnhancers->statsEnhancers.begin(); enhancer != pStatsEnhancers->statsEnhancers.end(); ++enhancer )
      {
        if ( enhancer->statId == it->statId )
        {
          value     = value     * enhancer->statMullModifier      + enhancer->statAddModifier;
          increment = increment * enhancer->incrementMullModifier + enhancer->incrementAddModifier;
          break;
        }
      }
    }

    if ( ( increment != 0 ) || !it->levelUpgrades.empty() )
    {
      upgrades[it->statId].Initialize( *it, increment );
    }

    vector<StatValueWithModifiers>::reference stat = values[it->statId];

    stat.SetCoreValue( value );

    // NUM_TASK: статы не должны быть отрицательными; регенерация может быть отрицательной
    // NUM_TASK: CritChanceBonus may be negative;
    switch (it->statId)
    {
    case NDb::STAT_LIFEREGENERATION:
    case NDb::STAT_LIFEREGENERATIONABSOLUTE:
    case NDb::STAT_ENERGYREGENERATION:
    case NDb::STAT_ENERGYREGENERATIONABSOLUTE:
    case NDb::STAT_CRITCHANCEBONUS:
      break;
    default:
      stat.AddModifier(0.f, 0.f, std::numeric_limits<int>::max(), true, NDb::STATCONSTRAINT_LOWERLIMIT);
      break;
    }

    // Accumulate total budget from stats' increments
    NDb::StatBudget const* statBudget = GetStatBudget( it->statId );
    if ( statBudget && statBudget->upgradesWithForce )
    {
      totalIncrementBudget += increment / statBudget->budget;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatContainer::Load( const NDb::StatsContainer* pStats, const NDb::StatsContainer* pDefaults, const NDb::Ptr<NDb::UnitConstantsContainer>& pConstants )
{
  Load( pDefaults, pConstants, 0 );
  Load( pStats, pConstants, 0 );

  CalculateTotalStatIncrements();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatContainer::Load( const NDb::StatsContainer* pStats, const NDb::StatsContainer* pDefaults, const NDb::Ptr<NDb::UnitConstantsContainer>& pConstants,
                            const NDb::Ptr<NDb::StatsEnhancersContainer>& pStatsEnhancers )
{
  Load( pDefaults, pConstants, pStatsEnhancers );
  Load( pStats, pConstants, pStatsEnhancers );

  CalculateTotalStatIncrements();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatValueWithModifiers const* PFStatContainer::Get( NDb::EStat const stat) const
{
  const int idx = static_cast<int>(stat);
  NI_VERIFY(0 <= idx && idx < NDb::KnownEnum<NDb::EStat>::SizeOf(), NStr::StrFmt( "Stat index %d out of bounds %d", idx, NDb::KnownEnum<NDb::EStat>::SizeOf() ), return 0; ) ;

  return &values[idx];
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatValueWithModifiers* PFStatContainer::Get( NDb::EStat const stat) 
{
  const int idx = static_cast<int>(stat);
  NI_VERIFY(0 <= idx && idx < NDb::KnownEnum<NDb::EStat>::SizeOf(), NStr::StrFmt( "Stat index %d out of bounds %d", idx, NDb::KnownEnum<NDb::EStat>::SizeOf() ), return 0; ) ;

  return &values[idx];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::StatBudget const* PFStatContainer::GetStatBudget( NDb::EStat stat ) const
{
  return GetStatBudget(&GetWorld()->GetAIWorld()->GetAIParameters(), stat);
}

NDb::StatBudget const* PFStatContainer::GetStatBudget( const NDb::AILogicParameters* pAIParams, NDb::EStat stat )
{
  NI_ASSERT( pAIParams, "aiParams is NULL" );
  vector<NDb::StatBudget> const& dbStatsBudgets = pAIParams->statsBudget->stats;
  for ( vector<NDb::StatBudget>::const_iterator it = dbStatsBudgets.begin(); it != dbStatsBudgets.end(); ++it )
  {
    if ( it->stat == stat )
      return it;
  }
  return NULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatContainer::Upgrade( const int oldLevel, const int count, const float statsBonusBudget /* = 0.0f */ )
{
  NI_VERIFY( count > 0, NStr::StrFmt( "Upgrades count (%d) must be greater than zero", count ), return; );
  for( int i = 0; i < upgrades.size(); ++i )    
  {
    float increment = GetStatUpgradeIncrement(static_cast<NDb::EStat>(i), oldLevel, count);

    // Calculate stat bonus from bonus budget (for hero) and modify increment (for others)
    float statBonus = 0.0f;
    NDb::StatBudget const* statBudget = GetStatBudget( (NDb::EStat)i );
    if ( statBudget && statBudget->upgradesWithForce )
    {
      if ( statsBonusBudget > 0.0f )
      {
        statBonus = increment * statsBonusBudget / totalIncrementBudget;
      }
      increment *= incrementForceModifier;
    }

    StatValueWithModifiers& value = values[i];

    value.SetCoreValue( value.GetCoreValue() + increment + statBonus );
  }

  upgradedIncrementBudget += statsBonusBudget;
  upgradeCounter++;

  averageIncPercent = upgradedIncrementBudget / upgradeCounter / totalIncrementBudget; 
}

void PFStatContainer::Upgrade(const int oldLevel, const int count, const float statsBonusBudget, const float fraction)
{
  NI_VERIFY( count > 0, NStr::StrFmt( "Upgrades count (%d) must be greater than zero", count ), return; );

  for( int i = 0; i < upgrades.size(); ++i )
  {
    float increment = totalStatIncrements[i] * fraction * count;

    // Calculate stat bonus from bonus budget (for hero) and modify increment (for others)
    float statBonus = 0.0f;

    const NDb::StatBudget* const statBudget = GetStatBudget( static_cast<NDb::EStat>(i) );

    if (statBudget && statBudget->upgradesWithForce)
    {
      if (statsBonusBudget > 0.f)
      {
        statBonus = GetStatUpgradeIncrement(static_cast<NDb::EStat>(i), oldLevel, count);

        statBonus *= statsBonusBudget;
        statBonus /= totalIncrementBudget;
      }

      increment *= incrementForceModifier;
    }

    StatValueWithModifiers& value = values[i];

    value.SetCoreValue(value.GetCoreValue() + increment + statBonus);
  }

  upgradedIncrementBudget += statsBonusBudget;
  upgradeCounter++;

  averageIncPercent = upgradedIncrementBudget / upgradeCounter / totalIncrementBudget; 
}

void PFStatContainer::Reset()
{
  statIncProxy.Init( this );
  statIncGE1Proxy.Init( this );
  values[NDb::STAT_ENERGY].SetCore( &coreEnergy );
  values[NDb::STAT_LIFE].SetCore( &coreLife );
}

void PFStatContainer::CalculateTotalStatIncrements(unsigned level /*= 0U*/)
{
  if (level < 1U)
    level = GetWorld()->GetAIWorld()->GetMaxHeroLevel();

  for (unsigned i = 0U, count = NDb::KnownEnum<NDb::EStat>::SizeOf(); i < count; ++i)
  {
    totalStatIncrements[i] = GetStatUpgradeIncrement(static_cast<NDb::EStat>(i), 0U, level);
  }
}

float NWorld::PFStatContainer::GetStatUpgradeIncrement(const NDb::EStat stat, const unsigned fromLevel, const unsigned count)
{
  const StatUpgradeInfo& upgrade = upgrades[stat];

  float increment = 0.f;

  if (upgrade.upgrades.empty())
  {
    increment = upgrade.increment * count;
  }
  else
  {
    float upgradeIncrement = 0.0f;

    vector<NDb::StatUpgrade>::const_iterator it_level_upgrade = upgrade.upgrades.begin();

    for (unsigned level = fromLevel + 1U, cap = fromLevel + count; level <= cap; ++level)
    {
      for (; it_level_upgrade != upgrade.upgrades.end(); ++it_level_upgrade)
      {
        if (static_cast<unsigned>(it_level_upgrade->level) > level)
          break;

        upgradeIncrement = it_level_upgrade->increment;
      }

      increment += upgradeIncrement;
    }
  }

  return increment;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NWorld
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_WORLD_OBJECT_NM(PFStatContainer, NWorld);

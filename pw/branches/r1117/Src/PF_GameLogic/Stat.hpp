#pragma once

#include "../System/NameMap.h"
#include "ValueWithModifiers.hpp"
#include "DBStats.h"
#include "PFWorldObjectBase.h"

namespace NDb
{
  struct UnitConstantsContainer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFStatContainer: public PFWorldObjectBase, public NNameMap::Map
{
  WORLD_OBJECT_METHODS( 0xE5CC4C1, PFStatContainer );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct StatUpgradeInfo
  {
    ZDATA
    float increment;
    vector<NDb::StatUpgrade> upgrades;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&increment); f.Add(3,&upgrades); return 0; }

    StatUpgradeInfo() : increment( 0.0f ) { }
		
	  void Initialize( const NDb::UnitStat& desc, float incr );
  };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct StatIncrementProxy : NNameMap::Map
  {
    NAMEMAP_DECLARE;
    virtual NNameMap::Variant* ResolveVariant( const char* name, int length, const char* args, int argsLength, void* prms, bool readonly );
  public:
    void Init( PFStatContainer* _pContainer ) { pContainer = _pContainer; }
  private:
    PFStatContainer* pContainer;
  };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct StatIncrementGE1Proxy : NNameMap::Map
  {
    NAMEMAP_DECLARE;
    virtual NNameMap::Variant* ResolveVariant( const char* name, int length, const char* args, int argsLength, void* prms, bool readonly );
  public:
    void Init( PFStatContainer* _pContainer ) { pContainer = _pContainer; }
  private:
    PFStatContainer* pContainer;
  };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  NAMEMAP_DECLARE;
private:
  void Load( const NDb::StatsContainer* pStats, const NDb::Ptr<NDb::UnitConstantsContainer>& pConstants );
  void Load( const NDb::StatsContainer* pStats, const NDb::Ptr<NDb::UnitConstantsContainer>& pConstants,
    const NDb::Ptr<NDb::StatsEnhancersContainer>& pStatsEnhancers );

protected:
  virtual NNameMap::Variant* ResolveVariant( const char* name, int length, const char* args, int argsLength, void* prms, bool readonly );
	PFStatContainer() {}

public:
	PFStatContainer( PFWorld* world );
	virtual bool NeedToBeStepped() { return false; }
    
  void Load( const NDb::StatsContainer* pStats, const NDb::StatsContainer* pDefaults, const NDb::Ptr<NDb::UnitConstantsContainer>& pConstants );
  void Load( const NDb::StatsContainer* pStats, const NDb::StatsContainer* pDefaults, const NDb::Ptr<NDb::UnitConstantsContainer>& pConstants,
    const NDb::Ptr<NDb::StatsEnhancersContainer>& pStatsEnhancers );

  const StatValueWithModifiers* Get( const NDb::EStat stat ) const;
  StatValueWithModifiers* Get( const NDb::EStat stat );

  float GetValue( const NDb::EStat stat ) const
  {
    const StatValueWithModifiers* value = Get( stat );
    return value ? value->GetValue() : 0.0f;
  }

  // Core value is modified only by stat upgrading (via levelup)
  float GetCoreValue( const NDb::EStat stat ) const
  {
    const StatValueWithModifiers* value = Get( stat );
    return value ? value->GetCoreValue() : 0.0f;
  }

  // Base value is a bonus part and modified for example by PermanentStatMod applicator
  float GetBaseValue( const NDb::EStat stat ) const
  {
    const StatValueWithModifiers* value = Get( stat );
    return value ? value->GetBaseValue() : 0.0f;
  }

  float GetUnmodifiedValue( const NDb::EStat stat ) const
  {
    const StatValueWithModifiers* value = Get( stat );
    return value ? value->GetUnmodifiedValue() : 0.0f;
  }

  // Get average stat increment accounting different force modifiers
  float GetIncrementForUI( const NDb::EStat stat ) const
  {
    return upgrades[stat].increment * (incrementForceModifier + averageIncPercent);
  }

  float GetStatIncrement( const NDb::EStat stat ) const
  {
    return upgrades[stat].increment;
  }

  NDb::StatBudget const* GetStatBudget( NDb::EStat stat ) const;
  static NDb::StatBudget const* GetStatBudget( const NDb::AILogicParameters* pAIParams, NDb::EStat stat );
  void Upgrade( const int oldLevel, const int count, const float statsBonusBudget = 0.0f );
  void Upgrade(const int oldLevel, const int count, const float statsBonusBudget, const float fraction);
  float GetIncrementForceModifier() const { return incrementForceModifier; }
  void  SetIncrementForceModifier( float incrementForceModifier_ ) { incrementForceModifier = incrementForceModifier_; }
  void SetAverageIncPercent( float averageStatBonusBudget ) { averageIncPercent = averageStatBonusBudget / totalIncrementBudget; }
  float GetTotalIncrementBudget() const { return totalIncrementBudget; }

  virtual void Reset();

private:
  ZDATA_(PFWorldObjectBase)
  ZNOPARENT(NNameMap::Map)
	vector<StatValueWithModifiers> values;
  //ZNOCRC
  vector<StatUpgradeInfo> upgrades;
  //ZNOCRCEND
  ValueWithModifiers coreEnergy;
  ValueWithModifiers coreLife;
  float totalIncrementBudget;
  float incrementForceModifier;
  float averageIncPercent; // used for correct stat increment display in ui
  float upgradedIncrementBudget;
  int   upgradeCounter;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&values); f.Add(3,&upgrades); f.Add(4,&coreEnergy); f.Add(5,&coreLife); f.Add(6,&totalIncrementBudget); f.Add(7,&incrementForceModifier); f.Add(8,&averageIncPercent); f.Add(9,&upgradedIncrementBudget); f.Add(10,&upgradeCounter); return 0; }
private:
  void CalculateTotalStatIncrements(unsigned level = 0U);
  float GetStatUpgradeIncrement(const NDb::EStat stat, const unsigned fromLevel, const unsigned count);

  StatIncrementProxy statIncProxy;
  StatIncrementGE1Proxy statIncGE1Proxy; // used with <if> tag to compare stat inc >= 1

  StaticArray<float, NDb::KnownEnum<NDb::EStat>::sizeOf> totalStatIncrements;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NWorld

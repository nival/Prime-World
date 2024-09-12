#pragma once

#include "PFCreature.h"

namespace NGameX { class PFCreep; }

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Basic creep
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseCreep : public PFCreature
{
  struct LevelUpInfo
  {
    ZDATA
    float timeLevelUpInterval;
    int   timeLevelUpIncrement;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&timeLevelUpInterval); f.Add(3,&timeLevelUpIncrement); return 0; }

    bool ShouldGainLevels() const { return ( ( timeLevelUpInterval > 0.0f ) && ( timeLevelUpIncrement > 0 ) ); }
    const LevelUpInfo( float _timeLevelUpInterval = 0.0f, int _timeLevelUpIncrement = 0 ) 
      : timeLevelUpInterval( _timeLevelUpInterval ), timeLevelUpIncrement( _timeLevelUpIncrement ) { }
  };

  WORLD_OBJECT_METHODS_WITH_CLIENT( 0x2C63F441, PFBaseCreep, NGameX::PFCreep);

public:
  PFBaseCreep( PFWorld* pWorld, const NDb::Creature& creepObj, NDb::EFaction faction, 
                NDb::EUnitType unitType, int playerId, const Placement& position, 
                float interval = 0.0f, int increment = 0, 
                bool bStartIdleAnimation = false,
                const NDb::MapForceStatModifierApplication mapForceStatModifierApplication = NDb::MAPFORCESTATMODIFIERAPPLICATION_ALL);
  explicit PFBaseCreep( PFWorld* pWorld, const CVec3 &pos, const CVec2 & direction, const NDb::Creature &unitDesc );
  virtual void Initialize(InitData const& data);
  virtual bool Step( float dtInSeconds );
	virtual void Reset();
  virtual float GetManaCostModifier( bool altCost = false ) const;
  virtual const NDb::DBID* GetSpawnerDBID() const { return NULL; }

  void MakeLevelupsForTimeDelta( float dtInSeconds );

  virtual void ChangeFaction( NDb::EFaction newFaction );
  void SetWarfogFaction( NDb::EFaction _faction );
  virtual NDb::EFaction GetWarfogFaction() const { return warfogFaction; }
protected:
  void InitializeSummonBehavior();
  virtual void OnDestroyContents();
  virtual void RemoveCorpse();
  bool ShouldApplyForce() { return type != NDb::UNITTYPE_SUMMON; }

  explicit PFBaseCreep() {}
  ZDATA_(PFCreature)
  float timeBeforeActivate;
  LevelUpInfo levelUpInfo;
  float levelUpTimer;
  NDb::EFaction warfogFaction; 
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFCreature*)this); f.Add(2,&timeBeforeActivate); f.Add(3,&levelUpInfo); f.Add(4,&levelUpTimer); f.Add(5,&warfogFaction); return 0; }
  bool ShouldGainLevels() const { return levelUpInfo.ShouldGainLevels(); }
  bool CanLevelUpNow() const;
  static NDb::EUnitType GetUnitTypeByCreepType( NDb::ECreepType creepType );
};

} // namespace

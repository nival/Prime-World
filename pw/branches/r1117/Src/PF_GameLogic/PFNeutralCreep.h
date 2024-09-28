#pragma once

#include "PFCreep.h"
#include "PFBaseSpawner.h"
#include "PFClientSpawner.h"

namespace NGameX
{
  class PFClientNeutralCreepSpawner;
}
namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Neutral creep
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PFNeutralCreepSpawner;

class PFNeutralCreep : public PFBaseCreep
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x2C5CC440, PFNeutralCreep, NGameX::PFCreep)
public:
  PFNeutralCreep( PFWorld* pWorld, const NDb::AdvMapCreep& creepObj, const Placement& placement, bool useSpawnerWalkLimit, float limitWalkDistance,
    PFNeutralCreepSpawner* parentSpawner, const vector<CVec2>& waypoints, float interval = 0.0f, int increment = 0, bool specialAwarding_ = false );

  virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags = UNITDIEFLAGS_NONE, PFBaseUnitDamageDesc const* pDamageDesc = 0 );
  virtual void DettachFromSpawner();
  virtual void DisableLevelUps();

  virtual bool GetNeedRotate() const { return needRotate; }
  virtual void SetNeedRotate( bool _needRotate ) { needRotate = _needRotate; }
  virtual void RotateIfNeeded();
  virtual void OnAfterReset();
  virtual void ChangeFaction( NDb::EFaction newFaction );

  virtual float GetWalkLimit() const { return walkLimit; };
  Placement const& GetInitialPlacement() const { return initialPlacement; }
  CVec2 const& GetPositionBySpawner() const { return positionBySpawner; }
  virtual PFNeutralCreepSpawner * GetSpawner() const { return IsValid(spawner) ? (spawner.GetPtr()) : (0); }
  virtual const NDb::DBID* GetSpawnerDBID() const;
  bool IsAttachedToSpawner() const { return attachedToSpawner; }
  bool HasSpecialAwarding() const { return specialAwarding; }
  void Summon() { InitializeSummonBehavior(); }
  void SetPositionBySpawner( CVec2 const& pos ) { positionBySpawner = pos; }

  const vector<CVec2>* GetWaypoints() const;

  bool SetCreepBehavior( const string& behavior, const vector<string>& params );

  virtual bool IsAggressiveNeutralCreep() const;
protected:
  explicit PFNeutralCreep() {}
  ZDATA_(PFBaseCreep)
  CPtr<PFNeutralCreepSpawner> spawner;
  bool needRotate;
  Placement initialPlacement;
  float walkLimit;
  bool attachedToSpawner;
  bool specialAwarding;
  CVec2 positionBySpawner;
  CPtr<PFBaseBehaviour> nativeBehaviour;
 public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseCreep*)this); f.Add(2,&spawner); f.Add(3,&needRotate); f.Add(4,&initialPlacement); f.Add(5,&walkLimit); f.Add(6,&attachedToSpawner); f.Add(7,&specialAwarding); f.Add(8,&positionBySpawner); f.Add(9,&nativeBehaviour); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Neutral creep spawner
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFNeutralCreepSpawner : public PFBaseSpawner
{
public:
  typedef list<CPtr<PFNeutralCreep>> TCreeps;

  PFNeutralCreepSpawner(PFWorld* pWorld, const NDb::AdvMapObject &dbObject);
  //virtual bool Step(float dtInSeconds);

  void AwardForCreepKill(NaftaAward& award) const;
  void DropCreep( PFNeutralCreep *pCreep);
  void DropAllCreeps();
  int  GetSpawnedCreepsCount() const { return creeps.size(); }
  float GetMinAttackRange() const { return minAttackRange; }
  virtual void Hide(bool hide);
  CPtr<PFBaseUnit> GetSpawnTarget( CPtr<PFBaseMovingUnit>& pUnit, float range, const bool checkRange = true );

  const TCreeps& GetCreeps() const  { return creeps; }

  NDb::MapForceStatModifierApplication GetMapForceStatModifierApplication() const;

private:
  explicit PFNeutralCreepSpawner() {}
  WORLD_OBJECT_METHODS_WITH_CLIENT( 0x22844480, PFNeutralCreepSpawner, NGameX::PFClientNeutralCreepSpawner )

  NDb::Ptr<NDb::AdvMapNeutralCreepSpawner> spawnerDesc;
 
  TCreeps creeps;
   
  ZDATA_(PFBaseSpawner)
  float minAttackRange;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseSpawner*)this); f.Add(2,&minAttackRange); f.Add(3,&creeps); return 0; }

  virtual NDb::AdvMapNeutralCreepSpawner const* GetDBDesc() const { return spawnerDesc; }

  virtual NDb::EFaction GetFaction() const { return NDb::FACTION_NEUTRAL; }

  template<class F>
  void ForAllCreeps( F& f );

  void InitializeCreep( PFNeutralCreep* neutralCreep, const Render::HDRColor& recolor );
  
private:
  virtual void SpawnCreeps();

  virtual bool CanSpawnWave() const;
  virtual void OnAfterReset();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class F>
void PFNeutralCreepSpawner::ForAllCreeps( F& f )
{
  TCreeps::iterator it = creeps.begin();
  for ( ; it != creeps.end(); ++it)
    f(*it);
}

} // namespace

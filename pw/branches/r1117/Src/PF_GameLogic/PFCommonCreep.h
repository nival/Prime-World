#pragma once

#include "PFCreep.h"
#include "PFBaseSpawner.h"
#include "PFNeutralCreepBehavior.h"

namespace NGameX { class PFCreep; }

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common creep
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFCommonCreep : public PFBaseCreep
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x1E59D441, PFCommonCreep, NGameX::PFCreep)
public:

  seDECLARE_CPTRRING(PFCommonCreep, creepsRingPart, CreepsRing);

  PFCommonCreep( PFWorld* pWorld, const NDb::AdvMapCreep& creepObj, NDb::EFaction faction, const Placement& position, const vector<CVec2>& targets, float interval = 0.0f, int increment = 0, PFCreepSpawner* parentSpawner = NULL );
  void SetPower(int level, const vector<float>& statFactors);

  void SetMinigameCreepID( int _minigameCreepID ) { minigameCreepID = _minigameCreepID; }
  int GetMinigameCreepID() const { return minigameCreepID; }
  virtual PFCreepSpawner * GetSpawner() const { return IsValid(spawner) ? (spawner.GetPtr()) : (0); }
  virtual void RotateIfNeeded();
  virtual float GetWalkLimit() const { return walkLimit; };
  virtual const NDb::DBID* GetSpawnerDBID() const;

protected:
  virtual void OnInvalidPath();
  virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc = 0);
  virtual void OnDestroyContents();
  explicit PFCommonCreep() {}
  ZDATA_(PFBaseCreep);
  int minigameCreepID;
  CPtr<PFCreepSpawner> spawner;
  float walkLimit;
  Placement initialPlacement;
private:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseCreep*)this); f.Add(2,&minigameCreepID); f.Add(3,&spawner); f.Add(4,&walkLimit); f.Add(5,&initialPlacement); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common creep behaviour
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFCommonCreepBehaviour : public PFBaseBehaviour
{
  WORLD_OBJECT_METHODS( 0x9E677480, PFCommonCreepBehaviour )
protected: 

  ZDATA_(PFBaseBehaviour)
  vector<CVec2> wayPoints;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseBehaviour*)this); f.Add(2,&wayPoints); return 0; }

  PFCommonCreepBehaviour(PFCommonCreep *pCreep_, const vector<CVec2>& targets_) 
  : PFBaseBehaviour(pCreep_), wayPoints(targets_) 
  {}
  PFCommonCreepBehaviour() {}

  virtual bool OnStep(float dtInSeconds);
  virtual void OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget );
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Evade creep behaviour
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFEvadeCreepBehaviour : public PFBaseBehaviour
{
  WORLD_OBJECT_METHODS( 0xEF938340, PFEvadeCreepBehaviour )
protected: 

  ZDATA_(PFBaseBehaviour)
  Placement initialPlacement;
  float     targetingRange;
  bool      useEvade;
  EvadeData evadeParams;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseBehaviour*)this); f.Add(2,&initialPlacement); f.Add(3,&targetingRange); f.Add(4,&useEvade); f.Add(5,&evadeParams); return 0; }

  PFEvadeCreepBehaviour( PFCommonCreep *pCreep, const Placement& _initialPlacement );
  PFEvadeCreepBehaviour() {}

  virtual bool OnStep( float dtInSeconds );
  virtual void OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget );
  virtual void OnDamage( const PFBaseUnitDamageDesc& desc );
  virtual bool CanSelectTarget( PFBaseUnit const* pTarget, bool mustSeeTarget = false ) const;
  bool IsCreepAtSpawner( float distInTiles ) const;
  virtual bool IsInDefaultState() const;
  PFCommonCreep* GetUnit() const { return static_cast<PFCommonCreep*>( pUnit.GetPtr() ); }
  virtual bool IsAttackedUnitAlly( const CPtr<PFBaseUnit>& pAttacked, NDb::EFaction originalAttackedFaction ) const;
  virtual void Resume();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (Common) creep spawner
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFCreepSpawner : public PFBaseSpawner
{
  WORLD_OBJECT_METHODS( 0x2C5AB400, PFCreepSpawner );
public:
  PFCreepSpawner(PFWorld* pWorld, const NDb::AdvMapObject &dbObject);

  enum CreepsPower
  {
    powerNormal,
    powerLarge,
    powerMega,
  };

  virtual bool  Step(float dtInSeconds);
  void          SetCreepsPower(CreepsPower power);
  
  CVec2 const&  GetFront() const { return farestCreepPosition; }

private:
  explicit PFCreepSpawner() {}

  virtual void OnDestroyContents();

  NDb::Ptr<NDb::AdvMapCreepSpawner> spawnerDesc;
  vector<CVec2> targets;

  ZDATA_(PFBaseSpawner);
  vector<float> statFactors;  // усиление статов крипов (используется при разрушении бараков)
  PFCommonCreep::CreepsRing creepsRing;
  float         farestCreepPositionUpdateOffset;
  CVec2         farestCreepPosition;
  bool          isOppositeBarracksDestroyed;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseSpawner*)this); f.Add(2,&statFactors); f.Add(3,&creepsRing); f.Add(4,&farestCreepPositionUpdateOffset); f.Add(5,&farestCreepPosition); f.Add(6,&isOppositeBarracksDestroyed); return 0; }

  virtual NDb::AdvMapCreepSpawner const* GetDBDesc() const { return spawnerDesc; }

  virtual NDb::EFaction GetFaction() const { return (spawnerDesc)?(spawnerDesc->faction):((NDb::EFaction)-1); }

  virtual void InitializeCreep( PFCommonCreep* pCreep, const Render::HDRColor& recolor );
  vector<CVec2> const& GetPath() { return targets; }
protected:
  virtual bool CanSpawnWave() const;

  virtual void SpawnCreeps();

  void StepFarestCreepPosition(float dtInSeconds);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Path utils
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<CVec2> GetRelativeTargets(const vector<CVec2>& targets, CVec3 const & unitRelativePos);
CVec2 GetRotatedRelativePos( CVec2 const & point1, CVec2 const & point2, CVec2 const & point3, CVec2 const & relative );



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NWorld


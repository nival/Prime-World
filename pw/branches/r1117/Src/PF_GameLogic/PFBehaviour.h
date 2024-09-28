#ifndef PFBEHAVIOUR_H_INCLUDED
#define PFBEHAVIOUR_H_INCLUDED

#include "DBUnit.h"

namespace NWorld
{

class  PFBaseUnit;
class  PFBaseMovingUnit;
struct PFBaseUnitDamageDesc;

struct NaftaAward;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ScreamTarget
{
  enum ScreamType
  {
    ScreamForHelp,
    ScreamAlert,
  };
  ZDATA
  ScreamType        screamType;
  CPtr<PFBaseUnit>  pTarget;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&screamType); f.Add(3,&pTarget); return 0; }
};

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit behaviour
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseBehaviour : public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0x9E677A83, PFBaseBehaviour )

protected:
	ZDATA_(PFWorldObjectBase)
	CPtr<PFBaseMovingUnit>     pUnit;
	NDb::EFaction        faction;
	NDb::EUnitType       unitType;
  bool                 isEnabled;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pUnit); f.Add(3,&faction); f.Add(4,&unitType); f.Add(5,&isEnabled); return 0; }

  seDECLARE_COBJRING(PFBaseBehaviour, unitRingPart, UnitRing);

	PFBaseBehaviour(PFBaseMovingUnit *_pUnit);
  PFBaseBehaviour() : pUnit(NULL), faction(NDb::FACTION_NEUTRAL), unitType(NDb::UNITTYPE_INVALID), isEnabled(true) {}

  void SetFaction(NDb::EFaction f) { faction = f; }
	NDb::EFaction GetFaction() const { return faction; }

	void SetUnitType(NDb::EUnitType t) { unitType = t; }
	NDb::EUnitType GetUnitType() const { return unitType; }

	CPtr<PFBaseMovingUnit> const & GetUnit() const { return pUnit; }

	virtual bool  OnStep(float dtInSeconds);
	virtual void  OnTarget( const CPtr<PFBaseUnit>& /*pTarget*/, bool /*bStrongTarget*/ ) {}
	virtual void  OnUnitDie( CPtr<PFBaseUnit> /*pKiller*/ ) {}
	virtual void  OnDamage(PFBaseUnitDamageDesc const & /* desc */);
	virtual void  OnStop() {}
  virtual void  Suspend() {}
  virtual void  Resume() {}
  virtual void  GetKillerAward(CPtr<PFBaseUnit> pKiller, NaftaAward& award) {}
  virtual bool CanSelectTarget( PFBaseUnit const* pTarget, bool mustSeeTarget = false ) const { return true; }
  virtual bool IsInDefaultState() const { return true; }
  virtual bool IsAttackedUnitAlly( const CPtr<PFBaseUnit>& pAttacked, NDb::EFaction originalAttackedFaction ) const;
  virtual void DoScream( const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st );
  virtual void Stacked( const bool stacked = true ) {}
  bool IsEnabled() const { return isEnabled; }
  void Enable();
  void Disable();
public:
  struct StopFunc { void operator()(PFBaseBehaviour *pBehavior) { pBehavior->OnStop(); } };
};

class PFSummonBehaviour : public PFBaseBehaviour
{
  WORLD_OBJECT_METHODS(0xB75CA40, PFSummonBehaviour);

public:
  enum SummonBehaviourFlags
  {
    BEHAVIOURFLAGS_NONE = 0,
    BEHAVIOURFLAGS_CONTROLLEDLIFETIME = 1 << 0,
    BEHAVIOURFLAGS_ESSENTIALSUMMON    = 1 << 1,
    BEHAVIOURFLAGS_ALPHASUMMON        = 1 << 2,
    BEHAVIOURFLAGS_NOHEALTHPRIORITY   = 1 << 3,
    BEHAVIOURFLAGS_LIKEHERO           = 1 << 4,
  };

  seDECLARE_CPTRRING(PFSummonBehaviour, groupRingPart, GroupRing);
protected:
  ZDATA_(PFBaseBehaviour)
  CPtr<PFBaseUnit>   pMaster;
  float              lifeTime;
  float              maxLifeTime;
  int                behaviourFlags;
  int                index;
  string             groupName;
  float              lashRange;
  float              responseRange;
  float              responseTime;
  NDb::Ptr<NDb::SummonBehaviourBase> pBehaviourDb;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseBehaviour*)this); f.Add(2,&pMaster); f.Add(3,&lifeTime); f.Add(4,&maxLifeTime); f.Add(5,&behaviourFlags); f.Add(6,&index); f.Add(7,&groupName); f.Add(8,&lashRange); f.Add(9,&responseRange); f.Add(10,&responseTime); f.Add(11,&pBehaviourDb); return 0; }

  PFSummonBehaviour();
  PFSummonBehaviour( PFBaseMovingUnit* _pUnit, PFBaseUnit* _pMaster, const NDb::SummonBehaviourBase* _pBehaviourData, float _maxLifeTime, int _behaviourFlags );

  virtual bool OnStep( float dtInSeconds );
  const CPtr<PFBaseUnit>& GetMaster() const { return pMaster; }
  void Unsummon();

  virtual void OnDamage( const PFBaseUnitDamageDesc& desc) {}
  int GetIndex() const { return index; }
  float GetLifeTime() const { return lifeTime; }
  void SetIndex( int _index ) { index = _index; }

  virtual bool IsEssentialSummon() const { return behaviourFlags & BEHAVIOURFLAGS_ESSENTIALSUMMON; }
  virtual bool IsHealthPriority() const { return (behaviourFlags & BEHAVIOURFLAGS_NOHEALTHPRIORITY) == 0; }
  virtual bool IsLikeHero() const { return behaviourFlags & BEHAVIOURFLAGS_LIKEHERO; }
  virtual bool IsUnleashed() const { return false; }

  const string& GetGroupName() const { return groupName; }
  void SetGroupName( const string& _groupName ) { groupName = _groupName; }

  float  GetLashRange( ) const; 
  float  GetResponseRange( ) const { return responseRange; } 
  float  GetResponseTime( ) const { return responseTime; } 

  void SetLashRange( float range ) { lashRange = range; } 
  void SetResponseRange( float range ) { responseRange = range; } 
  void SetResponseTime( float time ) { responseTime = time; } 

  const NDb::SummonBehaviourBase* GetDB(){ return pBehaviourDb; }

public:
  struct UnsummonFunc
  {
    UnsummonFunc( const PFBaseUnit* master ) : master( master ) {};
    void operator()( PFSummonBehaviour* pBehaviour );
    const PFBaseUnit* master;
  };
};

class PFBehaviourGroup : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS(0xB75C401, PFBehaviourGroup);

	PFBehaviourGroup() {}
protected:
  ZDATA_(PFWorldObjectBase)
  PFSummonBehaviour::GroupRing group;
  int                          groupSize;
  map<string, int>        namedGroupsSize; // Empty string as key is allowed
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&group); f.Add(3,&groupSize); f.Add(4,&namedGroupsSize); return 0; }

	PFBehaviourGroup( PFWorld* world ) : PFWorldObjectBase( world, 0 ), groupSize(0) {}

  void AddBehavior(CPtr<PFSummonBehaviour> const &behaviour);
  void RemoveBehavior(CPtr<PFSummonBehaviour> const &behaviour);

  int GetSize() const { return groupSize; }
  int GetSize( const string& summonGroupName ) const;
  int GetMaxSize() const { return group.empty() ? 0 : group.back()->GetIndex() + 1; }
public:
  template <class F> void ForAllBehaviour(F &f);
};

//////////////////////////////////////////////////////////////////////////
template <class F> 
void PFBehaviourGroup::ForAllBehaviour(F & f)
{
  PFSummonBehaviour::GroupRing processed;
  
  while (!group.empty())
  {
    PFSummonBehaviour *first = group.first();

    CObj<PFSummonBehaviour> behaviour(first);

    PFSummonBehaviour::GroupRing::remove(first);

    processed.addLast(first);

    f(first);
  }

  while (!processed.empty())
  {
    PFSummonBehaviour *first = processed.first();
    
    CObj<PFSummonBehaviour> behaviour(first);
    
    PFSummonBehaviour::GroupRing::remove(first);
    
    group.addLast(first);
  }
}

}

#endif
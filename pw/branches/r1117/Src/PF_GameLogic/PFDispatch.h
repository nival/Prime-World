#pragma once

#include "PFWorldObjectBase.h"
#include "PFApplicator.h"

namespace NGameX { class PFDispatch; }

namespace NWorld
{

class PFDispatchCreateParams : public NonCopyable
{
public:
  PFDispatchCreateParams(CObj<PFAbilityInstance> const &pAbility, Target const &target, Target const &source, int flagsForApplicators, CPtr<PFBaseApplicator> const& pParentApplicator)
    : pAbility(pAbility)
    , target(target)
    , source(source)
    , flagsForApplicators(flagsForApplicators)
    , pParentApplicator(pParentApplicator)
    , clientStartDelay( 0.0f )
  {}

  CObj<PFAbilityInstance> const &pAbility;
  NDb::Ptr<NDb::Dispatch> pDBDispatch;
  PFWorld* pWorld;
  CPtr<PFBaseUnit> pSender;
  Target const &source;
  Target const &target;
  int flagsForApplicators;
  CPtr<PFBaseApplicator> pParentApplicator;
  float clientStartDelay;
};

class PFDispatch: public PFWorldObjectBase, public PF_Core::IEffectEnableConditionCallback
{
  WORLD_OBJECT_METHODS(0x1E5964A1, PFDispatch)

protected:
  typedef PFDispatchCreateParams CreateParams;

  PFDispatch() {} // need for correct dying
public:
  enum State
  {
    STATE_INIT = 0,
    STATE_PROCEED,
    STATE_READY_TO_APPLY,
    STATE_WAIT_TO_APPLY,
    STATE_APPLIED,
  };

  PFDispatch(CreateParams const &cp)
    : PFWorldObjectBase(cp.pWorld, 1, true)
    , pDBDispatch(cp.pDBDispatch)
    , pSender(cp.pSender)
    , source(cp.source)
    , originalTarget(cp.target)
    , target(cp.target)
    , state(STATE_INIT)
    , pAbility(cp.pAbility)
    , flagsForApplicators(cp.flagsForApplicators)
    , pParentApplicator(cp.pParentApplicator)
    , targetFaction(NDb::FACTION_NEUTRAL)
    , targetWarfogFaction(NDb::FACTION_NEUTRAL)
    , pUpgraderAbilityData( IsValid(cp.pParentApplicator) ? cp.pParentApplicator->GetUpgraderAbilityData() : 0 )
  {}
  virtual void OnDie();

  virtual bool Step(float dtInSeconds);
  virtual void OnMove(CVec3 const &/*pos*/, bool /*isDone*/) {}

	virtual void Reset();

  virtual void CreateClientDispatch() {}

  NDb::Ptr<NDb::Dispatch> const&        GetDBBase() const { return pDBDispatch; }
  NDb::Ptr<NDb::Dispatch> &             GetDBBase() { return pDBDispatch; }
  CObj<PFAbilityInstance> const&        GetAbility() const { return pAbility; }
  CObj<PFBaseUnit> const&               GetSender() const { return pSender; }
  Target const&                         GetSource() const { return source; }
  Target const&                         GetTarget() const {return target;}
  Target const&                         GetOriginalTarget() const {return originalTarget;}
  PFBaseApplicator::AppliedRing const&  GetApplicators() const { return applicators; }
  PFAbilityData const*                  GetUpgraderAbilityData() const { return pUpgraderAbilityData; }
 
  virtual bool                          HasArrived() const { return state >= STATE_READY_TO_APPLY; }
	virtual CVec3                         GetCurrentPosition() const { return target.AcquirePosition(); }

  bool  IsBaseAttack() const;
  bool  IsAggressive() const;
  void  UpgradeBeforeApply();
  void  Start();
  void  Cancel() { if ( !IsObjectDead() ) Die(); }

  bool  Started() const { return (state >= STATE_PROCEED); }
  
  void  AddApplicator(CObj<PFBaseApplicator> app) {applicators.addLast(app);}
  void  AddApplicators( vector<NDb::Ptr<NDb::BaseApplicator>> const& newApplicators, PFAbilityData* upgrader = NULL );
  virtual void AddPersistentApplicators( vector<NDb::Ptr<NDb::BaseApplicator>> const& newPersistentApplicators, PFAbilityData* upgrader = NULL ) {}

  virtual void SetNewTarget( const Target & _target );
  virtual void OnMissed() const;

  virtual bool CheckEffectEnabled( const PF_Core::BasicEffect &effect );
private:
  void  _ApplyInternal();

protected:
  void  Apply( bool playApplyEffect = true );

  float RetrieveParam( const ExecutableFloatString& par, float defaultValue = 0.0f );

  virtual void  OnStart() {}

  void OpenWarFog();
  void RegisterAggression();

  ZDATA_(PFWorldObjectBase)
  ZNOPARENT(PF_Core::IEffectEnableConditionCallback)
  PFBaseApplicator::AppliedRing applicators;
  CObj<PFAbilityInstance>       pAbility;
  CObj<PFBaseUnit>              pSender;
  Target                        source;
  Target                        originalTarget;
  Target                        target;
  State                         state;
  int                           flagsForApplicators;
  CPtr<PFBaseApplicator>        pParentApplicator;
	NDb::Ptr<NDb::Dispatch>       pDBDispatch;
  NDb::EFaction                 targetFaction;
  CObj<PFAbilityData>           pUpgraderAbilityData;
  NDb::EFaction                 targetWarfogFaction;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&applicators); f.Add(3,&pAbility); f.Add(4,&pSender); f.Add(5,&source); f.Add(6,&originalTarget); f.Add(7,&target); f.Add(8,&state); f.Add(9,&flagsForApplicators); f.Add(10,&pParentApplicator); f.Add(11,&pDBDispatch); f.Add(12,&targetFaction); f.Add(13,&pUpgraderAbilityData); f.Add(14,&targetWarfogFaction); return 0; }
};

template <class T, class DBT>
PFDispatch* FCreateDispatch(DBT const &/*db*/, PFDispatchCreateParams const &cp)
{
	PFDispatch *pDispatch = new T(cp);
  if (pDispatch)
  {
    pDispatch->CreateClientDispatch();
  }
  return pDispatch;
}

}

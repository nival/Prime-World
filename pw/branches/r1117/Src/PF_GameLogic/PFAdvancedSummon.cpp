#include "stdafx.h"
#include "PFAdvancedSummon.h"
#include "PFBaseUnit.h"
#include "PFSummonState.h"
#include "PFBaseUnitStates.h"

namespace NWorld
{

  class AdvancedSummonChaseState
    : public PFBaseMovingUnitState
  {
    WORLD_OBJECT_METHODS(0x15D33DC0, AdvancedSummonChaseState);
  public:
    AdvancedSummonChaseState(const CPtr<PFBaseMovingUnit>& pOwner, const Target& anchor, const float maxChaseDistance)
      : PFBaseMovingUnitState(pOwner)
      , anchor(anchor)
      , maxChaseDistance(maxChaseDistance)
    {
    }
  protected:
    AdvancedSummonChaseState() {}

    virtual void OnEnter()
    {
      if (!IsValid(pOwner))
        return;

      pOwner->OnChasing(true);
    }

    virtual void OnLeave()
    {
      if (!IsValid(pOwner))
        return;

      pOwner->OnChasing(false);

      if (pOwner->IsMoving() && !pOwner->IsMovingSpecial())
        pOwner->Stop();
    }

    virtual bool OnStep(float dt)
    {
      if (!IsUnitValid(pOwner))
        return true;

      const CPtr<PFBaseUnit> pTarget(pOwner->GetCurrentTarget());

      if (!pOwner->CanAttackTarget(pTarget))
        return true;

      if (pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDMOVE))
        return pOwner->IsTargetInAttackRange(pTarget);

      const CVec2& targetPosition = pTarget->GetPosition().AsVec2D();

      // check distance to master only if have not strong target or forbid flag
      if ((maxChaseDistance > 0.f) && !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDSELECTTARGET))
      {
        if (!pTarget->IsTargetInRange(anchor, maxChaseDistance))
        {
          return true; // owner is too far from master
        }

        if (!pOwner->IsTargetInRange(pTarget, maxChaseDistance))
        {
          return true; // target is too far from master
        }
      }

      // Check distance to target
      if (pOwner->IsTargetInAttackRange(pTarget))
      {
        return true; // target reached
      }

      pOwner->MoveTo(targetPosition);

      return false;
    }
  private:
    ZDATA_(PFBaseMovingUnitState);
    Target              anchor;
    float               maxChaseDistance;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,&anchor); f.Add(3,&maxChaseDistance); return 0; }
  };

  class AdvancedSummonCombateState
    : public PFBaseMovingUnitState
  {
    WORLD_OBJECT_METHODS(0x15D33DC2, AdvancedSummonCombateState);
  public:
    AdvancedSummonCombateState(CPtr<PFBaseMovingUnit> const& pOwner, const Target& anchor, const float maxChaseDistance)
      : PFBaseMovingUnitState(pOwner)
      , anchor(anchor)
      , maxChaseDistance(maxChaseDistance)
    {
    }
  protected:
    AdvancedSummonCombateState() {}

    virtual bool OnStep(float dt)
    {
      if (!IsUnitValid(pOwner))
      {
        return true;
      }

      const CPtr<PFBaseUnit> pTarget(pOwner->GetCurrentTarget());

      if (!pOwner->CanAttackTarget(pTarget))
      {
        return true;
      }

      if ((maxChaseDistance > 0.f) && !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDSELECTTARGET))
      {
        if (!pTarget->IsTargetInRange(anchor, maxChaseDistance))
        {
          return true; // слишком далеко от мастера
        }
      }

      if (!pOwner->IsTargetInAttackRange(pTarget))
      {
        return true; // слишком далеко от цели
      }

      return pOwner->IsReadyToAttack() && !pOwner->DoAttack();
    }
  private:
    ZDATA_(PFBaseMovingUnitState);
    Target            anchor;
    float             maxChaseDistance;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,&anchor); f.Add(3,&maxChaseDistance); return 0; }
  };

  class AdvancedSummonAttackState
    : public PFBaseMovingUnitState
    , public PFHFSM
  {
    WORLD_OBJECT_METHODS(0x15D33DC3, AdvancedSummonAttackState);
  public:
    AdvancedSummonAttackState(const CPtr<PFSummonBehaviourAdvanced> behaviour, const CPtr<PFBaseMovingUnit> owner, const CPtr<PFBaseUnit> target, const bool strongTarget = true)
      : PFBaseMovingUnitState(owner)
      , behaviour(behaviour)
      , target(target)
      , strongTarget(strongTarget)
    {
    }
  protected:
    AdvancedSummonAttackState()
      : strongTarget(false)
    {
    }

    virtual void OnEnter()
    {
      if (!IsUnitValid(pOwner))
        return;
      if (target == pOwner)
        return;

      pOwner->AssignTarget(target, strongTarget);
    }

    virtual void OnLeave()
    {
      if (!IsUnitValid(pOwner))
        return;

      pOwner->DropTarget();
    }

    virtual bool OnStep(float dt)
    {
      if (!IsUnitValid(pOwner))
        return true;

      const CPtr<PFBaseUnit> pTarget(pOwner->GetCurrentTarget());

      NI_VERIFY(pOwner != pTarget, "Cannot attack self!", return true);

      if (!IsUnitValid(pTarget))
        return true;

      const bool isStationarySummon = pOwner->GetTargetingParams().isStationarySummon;

      if (!isStationarySummon && !pOwner->IsInTaunt())
      {
        if (!pTarget->IsTargetInRange(behaviour->GetAnchor(), behaviour->GetLashRange()))
          return true;
      }

      if (!GetCurrentState())
      {
        if (!pOwner->CanAttackTarget(pTarget))
          return true;

        if (isStationarySummon && !pOwner->IsTargetInAttackRange(pTarget))
          return true;

        const float range = pOwner->IsInTaunt() ? 0.f : pOwner->GetChaseRange();

        PushState(new AdvancedSummonCombateState(pOwner, behaviour->GetAnchor(), range));

        if (!isStationarySummon && !pOwner->IsChasing())
          PushState(new AdvancedSummonChaseState(pOwner, behaviour->GetAnchor(), range));
      }

      const IPFState* const pPrevious = GetCurrentState();

      FSMStep(dt);

      if (pPrevious != GetCurrentState())
      {
        FSMStep(0.0f);
      }

      return false;
    }
  private:
    ZDATA_(PFBaseMovingUnitState)
    ZPARENT(PFHFSM)
    CPtr<PFSummonBehaviourAdvanced> behaviour;
    CPtr<PFBaseUnit>              target;
    bool                          strongTarget;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,(PFHFSM*)this); f.Add(3,&behaviour); f.Add(4,&target); f.Add(5,&strongTarget); return 0; }
  };

}

namespace NWorld
{
  class PFSummonAdvancedGuardState
    : public PFBaseMovingUnitState
    , public PFHFSM
  {
    WORLD_OBJECT_METHODS(0x15D34940, PFSummonAdvancedGuardState);
  public:
    PFSummonAdvancedGuardState(const CPtr<PFSummonBehaviourAdvanced> behaviour, const CPtr<PFBaseMovingUnit> owner)
      : PFBaseMovingUnitState(owner)
      , behaviour(behaviour)
    {

    }
  protected:
    PFSummonAdvancedGuardState()
    {
    }

    virtual bool OnStep(float dt)
    {
      if (!IsUnitValid(pOwner))
        return true;

      NI_VERIFY(IsValid(behaviour), "Invalid behaviour!", return true);

      if (GetCurrentState())
      {

      }
      else
      {
        // TODO: искать цели, когда саммон находится в пределах leashRange от якоря?

        const bool isStationarySummon = pOwner->GetTargetingParams().isStationarySummon;

        bool moveToAnchor = false;

        if (isStationarySummon || pOwner->IsTargetInRange(behaviour->GetAnchor(), pOwner->GetObjectSize() * 0.5f))
        {
          const bool canAttack =
            !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDSELECTTARGET) &&
            !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK);

          if (canAttack)
          {
            const CPtr<PFBaseUnit> foundTarget(pOwner->FindTarget(behaviour->GetLashRange()));

            if (IsUnitValid(foundTarget))
              PushState(new AdvancedSummonAttackState(behaviour, pOwner, foundTarget, true));
          }
        }
        else
        {
          moveToAnchor = true;
        }

        if (moveToAnchor && !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDMOVE))
        {
          pOwner->MoveTo(behaviour->GetAnchor().AcquirePosition().AsVec2D(), pOwner->GetObjectSize() * 0.5f);
        }
      }

      const IPFState* const pPrevious = GetCurrentState();

      FSMStep(dt);

      if (pPrevious != GetCurrentState())
      {
        FSMStep(0.0f);
      }

      return false;
    }
  private:
    ZDATA_(PFBaseMovingUnitState)
    ZPARENT(PFHFSM)
    CPtr<PFSummonBehaviourAdvanced> behaviour;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,(PFHFSM*)this); f.Add(3,&behaviour); return 0; }
  };

  class PFSummonAdvancedChaseState
    : public PFBaseMovingUnitState
    , public PFHFSM
  {
    WORLD_OBJECT_METHODS(0x15D34941, PFSummonAdvancedChaseState);
  public:
    PFSummonAdvancedChaseState(const CPtr<PFSummonBehaviourAdvanced> behaviour, const CPtr<PFBaseMovingUnit> owner)
      : PFBaseMovingUnitState(owner)
      , behaviour(behaviour)
    {

    }
  protected:
    PFSummonAdvancedChaseState()
    {
    }

    virtual bool OnStep(float dt)
    {
      if (!IsUnitValid(pOwner))
        return true;

      NI_VERIFY(IsValid(behaviour), "Invalid behaviour!", return true);

      const Target& anchor = behaviour->GetAnchor();

      NI_VERIFY(anchor.IsUnitValid(true), "Invalid target!", return true);

      const CPtr<PFBaseUnit> target(anchor.GetUnit());

      if (lastTarget != target)
      {
        lastTarget = target;

        Cleanup(true);
      }

      if (target->IsDead())
      {
        behaviour->SetAnchor(Target());
        return true;
      }

      const bool isStationarySummon = pOwner->GetTargetingParams().isStationarySummon;

      if (!target->IsVisibleForEnemy(pOwner->GetFaction()))
      {
        if (isStationarySummon)
          behaviour->SetAnchor(Target());
        else
          behaviour->SetAnchor(Target(target->GetPosition()));
        return true;
      }

      const bool canAttack =
        !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDSELECTTARGET) &&
        !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK);

      const bool hasCurrentState = !!GetCurrentState();

      bool moveToTarget = false;

      if (pOwner->IsTargetInAttackRange(target))
      {
        const bool hasRequiredTarget = (pOwner->GetCurrentTarget() == target);

        if (canAttack && (!hasCurrentState || !hasRequiredTarget))
        {
          if (hasCurrentState)
            Cleanup(true);

          PushState(new AdvancedSummonAttackState(behaviour, pOwner, target, true));
        }
        else
        {
          // TODO: ?
          moveToTarget = true;
        }
      }
      else if (isStationarySummon)
      {
        if (canAttack && (!hasCurrentState))
        {
          const CPtr<PFBaseUnit> foundTarget(pOwner->FindTarget(behaviour->GetLashRange()));

          if (IsUnitValid(foundTarget))
            PushState(new AdvancedSummonAttackState(behaviour, pOwner, foundTarget, true));
        }
      }
      else
      {
        moveToTarget = true;
      }

      if (moveToTarget && !hasCurrentState && !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDMOVE))
      {
        pOwner->MoveTo(target, pOwner->GetAttackRange());
      }

      const IPFState* const pPrevious = GetCurrentState();

      FSMStep(dt);

      if (pPrevious != GetCurrentState())
      {
        FSMStep(0.0f);
      }

      return false;
    }
  private:
    ZDATA_(PFBaseMovingUnitState)
    ZPARENT(PFHFSM)
    CPtr<PFSummonBehaviourAdvanced> behaviour;
    CPtr<PFBaseUnit> lastTarget;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,(PFHFSM*)this); f.Add(3,&behaviour); f.Add(4,&lastTarget); return 0; }
  };
}

namespace NWorld
{

  PFSummonBehaviourDataAdvanced::PFSummonBehaviourDataAdvanced(const NDb::SummonBehaviourAdvanced& dbDesc)
    : PFSummonBehaviourDataBase(dbDesc)
    , dbDesc(&dbDesc)
  {

  }

  PFSummonedUnitBehaviour* PFSummonBehaviourDataAdvanced::CreateBehaviour(CPtr<PFBaseSummonedUnit> const& pSummonedUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase, float lifeTime, int behaviourFlags)
  {
    return new PFSummonBehaviourAdvanced(pSummonedUnit, pMaster, pBehaviourBase, dbDesc->summonType, lifeTime, behaviourFlags);
  }

  NDb::EUnitType PFSummonBehaviourDataAdvanced::GetSummonedUnitType() const
  {
    return NDb::UNITTYPE_SUMMON;
  }

}

namespace NWorld
{

  PFApplAdvancedSummonSetTarget::PFApplAdvancedSummonSetTarget(PFApplCreatePars const &cp)
    : Base(cp)
  {
  }

  bool PFApplAdvancedSummonSetTarget::Start()
  {
    if (PFBaseApplicator::Start())
      return true;

    struct TargetSetter : ISummonAction, NonCopyable
    {
      explicit TargetSetter(const Target& target)
        : target(target)
      {
      }

      virtual void operator()(PFBaseUnit * pUnit)
      {
        if (!pUnit->HasBehaviour())
          return;

        if (pUnit->GetBehaviour()->GetTypeId() != PFSummonBehaviourAdvanced::typeId)
          return;

        PFSummonBehaviourAdvanced* const behaviour = static_cast<PFSummonBehaviourAdvanced*>(pUnit->Behaviour());

        behaviour->SetAnchor(target);
      }
    private:
      const Target& target;
    };

    TargetSetter action(GetTarget());

    pReceiver->ForAllSummons(action, NDb::SUMMONTYPE_PRIMARY);
    pReceiver->ForAllSummons(action, NDb::SUMMONTYPE_SECONDARY);

    return true;
  }

  bool PFApplAdvancedSummonSetTarget::Step(float dtInSeconds)
  {
    return true;
  }

}

namespace NWorld
{

  PFSummonBehaviourAdvanced::PFSummonBehaviourAdvanced(PFBaseMovingUnit* pUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase, NDb::SummonType summonType, float lifeTime, int behaviourFlags)
    : PFSummonedUnitAIBehaviour(pUnit, pMaster, pBehaviourBase, summonType, lifeTime, behaviourFlags)
    , mode(EAdvancedSummonBehaviourMode::Undefined)
    , anchor()
    , delayedAnchor()
    , delayedAnchorPresent(false)
  {
    SetAnchor(Target());
  }

  void PFSummonBehaviourAdvanced::SetAnchor(const Target& _anchor)
  {
    if (!IsUnitValid(pUnit))
      return;

    if (mode != EAdvancedSummonBehaviourMode::Undefined)
    {
      const bool oldAnchorValid = (anchor.GetType() != Target::INVALID);
      const bool newAnchorValid = (_anchor.GetType() != Target::INVALID);

      if (oldAnchorValid && newAnchorValid)
      {
        if (_anchor == anchor)
          return;
      }
      else
      {
        if (oldAnchorValid == newAnchorValid)
          return;
      }

      if (pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDPLAYERCONTROL))
      {
        delayedAnchor = _anchor;
        delayedAnchorPresent = true;

        return;
      }
    }

    EAdvancedSummonBehaviourMode::Enum _mode = EAdvancedSummonBehaviourMode::Default;

    if (_anchor.IsUnit())
    {
      const CPtr<PFBaseUnit>& targetUnit = _anchor.GetUnit();
      const CPtr<PFBaseUnit>& masterUnit = pMaster;

      if (targetUnit == masterUnit)
      {
        _mode = EAdvancedSummonBehaviourMode::Default;
      }
      else
      {
        // TODO: guard ally?
        if (targetUnit->GetFaction() == masterUnit->GetFaction())
          return;

        NI_VERIFY(pUnit->CanAttackTarget(targetUnit), "Invalid advanced summon target!", return);

        _mode = EAdvancedSummonBehaviourMode::Chase;
      }
    }
    else if (_anchor.IsPosition())
    {
      _mode = EAdvancedSummonBehaviourMode::Guard;
    }

    const bool modeChanged = (_mode != mode);

    mode = _mode;

    switch (mode)
    {
    case EAdvancedSummonBehaviourMode::Default:
      anchor = Target();
      break;
    default:
      anchor = _anchor;
      break;
    }

    if (modeChanged)
    {
      ResetUnitStateAndStop();
    }

    pUnit->GetVariableVWM("AdvSummonMode")->SetBaseValue(static_cast<int>(mode));
  }

  bool PFSummonBehaviourAdvanced::OnStep(float dtInSeconds)
  {
    // PFSummonedUnitAIBehaviour::OnStep
    // TODO: should it be here?
    {
      const CDynamicCast<PFCreature> pCreature(pUnit);

      if (IsValid(pCreature) && pCreature->IsMicroAiEnabled())
      {
        if ( pCreature->HaveAbilityInProgress() )
          return true; // Do nothing during channeling
        if ( pCreature->UseAbilityWithMicroAI() )
          return true; // We cast ability on this step
      }
    }

    if (delayedAnchorPresent && !pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDPLAYERCONTROL))
    {
      SetAnchor(delayedAnchor);

      delayedAnchor = Target();
      delayedAnchorPresent = false;
    }

    if (IsUnitValid(pUnit))
    {
      ApplyBehaviourParams(false);
    }

    switch (mode)
    {
    case EAdvancedSummonBehaviourMode::Guard:
      return OnStepGuard(dtInSeconds);
    case EAdvancedSummonBehaviourMode::Chase:
      return OnStepChase(dtInSeconds);
    }

    return PFSummonedUnitAIBehaviour::OnStep(dtInSeconds);
  }

  void PFSummonBehaviourAdvanced::OnTarget(const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget)
  {
    if (mode == EAdvancedSummonBehaviourMode::Default)
    {
      PFSummonedUnitAIBehaviour::OnTarget(pTarget, bStrongTarget);
      return;
    }

    NI_VERIFY(IsUnitValid(pTarget) && pTarget->IsVulnerable(), "Invalid Target!", return);

    if (!IsUnitValid(pUnit))
      return;

    if (pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK))
      return; // Attack forbid flag not empty!

    pUnit->DropStates();
    pUnit->PushState(new AdvancedSummonAttackState(this, pUnit, pTarget, bStrongTarget));
  }

  unsigned int PFSummonBehaviourAdvanced::OnEvent(const PFBaseUnitEvent *pEvent)
  {
    if (mode == EAdvancedSummonBehaviourMode::Default)
    {
      return PFSummonedUnitAIBehaviour::OnEvent(pEvent);
    }

    return 0;
  }

  bool PFSummonBehaviourAdvanced::CanSelectTarget(PFBaseUnit const* pTarget, bool mustSeeTarget /*= false*/) const
  {
    if (mode == EAdvancedSummonBehaviourMode::Default)
    {
      return PFSummonedUnitAIBehaviour::CanSelectTarget(pTarget, mustSeeTarget);
    }

    if (pUnit->IsInTaunt())
      return true;

    const float lashRange = Min(GetLashRange(), pUnit->GetChaseRange());
    const float range = lashRange + pUnit->GetAttackRange();

    if (mode == EAdvancedSummonBehaviourMode::Guard)
    {
      return IsValid(pUnit) && (lashRange < EPS_VALUE || pTarget->IsTargetInRange(anchor, range));
    }

    if (mode == EAdvancedSummonBehaviourMode::Chase)
    {
      return IsValid(pUnit) && (lashRange < EPS_VALUE || pUnit->IsTargetInRange(pTarget, range));
    }

    NI_ALWAYS_ASSERT("Invalid advanced summon behaviour mode!");

    return true;
  }

  void PFSummonBehaviourAdvanced::SetBehaviourParams(const NDb::SummonBehaviourAdvanced& db, const bool reset)
  {
    NI_VERIFY(IsValid(pMaster), "Invalid master!", return);
    NI_VERIFY(IsValid(pUnit), "Invalid unit!", return);

    if (reset)
    {
      pUnit->OverrideTargetingParams(db.targetingParams);

      SetResponseTime(db.responseTime);
      SetResponseRange(db.responseRange);
    }

    {
      SetLashRange(db.lashRange(pMaster, pUnit, NULL, 15.f));
    }
  }

  void PFSummonBehaviourAdvanced::SetBehaviourParams(const NDb::SummonBehaviourCommonParams& db, const bool reset)
  {
    NI_VERIFY(IsValid(pMaster), "Invalid master!", return);
    NI_VERIFY(IsValid(pUnit), "Invalid unit!", return);

    if (reset)
    {
      pUnit->OverrideTargetingParams(db.targetingParams);

      SetResponseTime(db.responseTime);
      SetResponseRange(db.responseRange);
    }

    {
      SetLashRange(db.lashRange(pMaster, pUnit, NULL, 15.f));
    }
  }

  bool PFSummonBehaviourAdvanced::OnStepGuard(const float dt)
  {
    if (pUnit->GetCurrentState())
    {
    }
    else
    {
      pUnit->PushState(new PFSummonAdvancedGuardState(this, pUnit));
    }

    return PFSummonedUnitBehaviour::OnStep(dt);
  }

  bool PFSummonBehaviourAdvanced::OnStepChase(const float dt)
  {
    if (pUnit->GetCurrentState())
    {
    }
    else
    {
      pUnit->PushState(new PFSummonAdvancedChaseState(this, pUnit));
    }

    return PFSummonedUnitBehaviour::OnStep(dt);
  }

  void PFSummonBehaviourAdvanced::ResetUnitStateAndStop()
  {
    if (!IsUnitValid(pUnit))
      return;

    pUnit->DropTarget();
    pUnit->DropStates();
    pUnit->RemoveLastAttackData();
    pUnit->RemoveLastHeroAttackData();

    // TODO: mount/mounted?
    if (pUnit->IsMoving() && !pUnit->IsMovingSpecial())
      pUnit->Stop();

    ApplyBehaviourParams(true);
  }

  void PFSummonBehaviourAdvanced::ApplyBehaviourParams(const bool reset /*= true*/)
  {
    const NDb::SummonBehaviourAdvanced* const db = static_cast<const NDb::SummonBehaviourAdvanced*>(GetDB());

    switch (mode)
    {
    case EAdvancedSummonBehaviourMode::Default:
      SetBehaviourParams(*db, reset);
      break;
    case EAdvancedSummonBehaviourMode::Guard:
      SetBehaviourParams(db->guardBehaviourParams, reset);
      break;
    case EAdvancedSummonBehaviourMode::Chase:
      SetBehaviourParams(db->chaseBehaviourParams, reset);
      break;
    }
  }

  void PFSummonBehaviourAdvanced::Suspend()
  {
    PFSummonedUnitAIBehaviour::Suspend();
  }

  void PFSummonBehaviourAdvanced::Resume()
  {
    ResetUnitStateAndStop();

    PFSummonedUnitAIBehaviour::Resume();
  }

  CVec2 PFSummonBehaviourAdvanced::GetMasterOffset() const
  {
    if (mode == EAdvancedSummonBehaviourMode::Default)
    {
      return PFSummonedUnitAIBehaviour::GetMasterOffset();
    }

    return VNULL2;
  }

  CVec2 PFSummonBehaviourAdvanced::GetEscortPosition() const
  {
    if (mode == EAdvancedSummonBehaviourMode::Default)
    {
      return PFSummonedUnitAIBehaviour::GetEscortPosition();
    }

    return anchor.AcquirePosition().AsVec2D();
  }

}

REGISTER_WORLD_OBJECT_NM(PFSummonBehaviourDataAdvanced, NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplAdvancedSummonSetTarget, NWorld);
REGISTER_WORLD_OBJECT_NM(PFSummonBehaviourAdvanced, NWorld);
REGISTER_WORLD_OBJECT_NM(PFSummonAdvancedGuardState, NWorld);
REGISTER_WORLD_OBJECT_NM(PFSummonAdvancedChaseState, NWorld);

REGISTER_WORLD_OBJECT_NM(AdvancedSummonChaseState, NWorld);
REGISTER_WORLD_OBJECT_NM(AdvancedSummonCombateState, NWorld);
REGISTER_WORLD_OBJECT_NM(AdvancedSummonAttackState, NWorld);

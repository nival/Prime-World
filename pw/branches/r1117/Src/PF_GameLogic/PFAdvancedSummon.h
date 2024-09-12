#pragma once

#include "PFApplSummon.h"
#include "PFSummoned.h"

namespace NWorld
{
  class PFBaseUnitMoveToState;
}

namespace NWorld
{
  class PFSummonBehaviourDataAdvanced
    : public PFSummonBehaviourDataBase
  {
    WORLD_OBJECT_METHODS(0x15D32041, PFSummonBehaviourDataAdvanced)
  public:
    PFSummonBehaviourDataAdvanced(const NDb::SummonBehaviourAdvanced& dbDesc);

    virtual PFSummonedUnitBehaviour* CreateBehaviour(CPtr<PFBaseSummonedUnit> const& pSummonedUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase, float lifeTime, int behaviourFlags);
    virtual NDb::EUnitType GetSummonedUnitType() const;
  protected:
    PFSummonBehaviourDataAdvanced() {}

    ZDATA_(PFSummonBehaviourDataBase)
    ZNOCRC
    NDb::Ptr<const NDb::SummonBehaviourAdvanced> dbDesc;
    ZNOCRCEND
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFSummonBehaviourDataBase*)this);  if(!f.IsChecksum()){ f.Add(2,&dbDesc);  } return 0; }
  };

  class PFApplAdvancedSummonSetTarget : public DBLinker<PFBaseApplicator, NDb::SetAdvancedSummonTargetApplicator>
  {
    WORLD_OBJECT_METHODS(0x15D320C2, PFApplAdvancedSummonSetTarget)
  public:
    PFApplAdvancedSummonSetTarget(PFApplCreatePars const &cp);

    virtual bool Start();
    virtual bool Step(float dtInSeconds);
  protected:
    PFApplAdvancedSummonSetTarget() {}
  private:
    ZDATA_(DBLinker)
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
  };

  namespace EAdvancedSummonBehaviourMode
  {
    enum Enum
    {
      Undefined,
      Default,
      Guard,
      Chase,
    };
  }

  class PFSummonAdvancedGuardState;
  class PFSummonAdvancedChaseState;

  class PFSummonBehaviourAdvanced : public PFSummonedUnitAIBehaviour
  {
    WORLD_OBJECT_METHODS(0x15D320C0, PFSummonBehaviourAdvanced)
  public:
    PFSummonBehaviourAdvanced(PFBaseMovingUnit* pUnit, CPtr<PFBaseUnit> const& pMaster, const NDb::SummonBehaviourBase* pBehaviourBase, NDb::SummonType summonType, float lifeTime, int behaviourFlags);

    virtual bool IsUnleashed() const
    {
      switch (mode)
      {
      case EAdvancedSummonBehaviourMode::Guard:
      case EAdvancedSummonBehaviourMode::Chase:
        return true;
      default:
        return false;
      }
    }

    void SetAnchor(const Target& _anchor);

    EAdvancedSummonBehaviourMode::Enum GetMode() const { return mode; }
    const Target& GetAnchor() const { return anchor; }
  protected:
    PFSummonBehaviourAdvanced() {}

    virtual void Suspend();
    virtual void Resume();

    virtual CVec2 GetMasterOffset() const;
    virtual CVec2 GetEscortPosition() const;

    virtual bool OnStep(float dtInSeconds);
    virtual void OnTarget(const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget);
    virtual unsigned int OnEvent( const PFBaseUnitEvent *pEvent );

    virtual bool CanSelectTarget(PFBaseUnit const* pTarget, bool mustSeeTarget = false) const;
  private:
    void SetBehaviourParams(const NDb::SummonBehaviourAdvanced& db, const bool reset);
    void SetBehaviourParams(const NDb::SummonBehaviourCommonParams& db, const bool reset);

    bool OnStepGuard(const float dt);
    bool OnStepChase(const float dt);

    void ResetUnitStateAndStop();
    void ApplyBehaviourParams(const bool reset = true);

    ZDATA_(PFSummonedUnitAIBehaviour)

    EAdvancedSummonBehaviourMode::Enum mode;
    Target anchor;
    Target delayedAnchor;
    bool delayedAnchorPresent;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFSummonedUnitAIBehaviour*)this); f.Add(2,&mode); f.Add(3,&anchor); f.Add(4,&delayedAnchor); f.Add(5,&delayedAnchorPresent); return 0; }
  };
}

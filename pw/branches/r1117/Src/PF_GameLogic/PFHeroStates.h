#pragma once

#include "PFState.h"
#include "PFHero.h"
#include "PFMaleHero.h"
#include "PFBuildings.h"
#include "PFBaseMovingUnit.h"
#include "PFBaseUnitStates.h"
#include "ValueWithModifiers.hpp"
#include "PFUniTarget.h"
#include "PFBaseUseState.h"

namespace NWorld
{
  class PFFlagpole;
  class PFPickupableObjectBase;

  //////////////////////////////////////////////////////////////////////////
  class HeroStateFSM: public PFBaseHeroState, protected PFHFSM
  {
    ZDATA_(PFBaseHeroState);
    ZPARENT(PFHFSM)
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseHeroState*)this); f.Add(2,(PFHFSM*)this); return 0; }
    HeroStateFSM( PFBaseHero * pOwner): PFBaseHeroState(pOwner) {}
    virtual void DumpStateToConsole(int depths);
  protected:
    HeroStateFSM() {}
  };

  //////////////////////////////////////////////////////////////////////////
  class PFBaseUseHeroState : public PFBaseUseState
  {
  public:
    PFBaseUseHeroState( PFBaseMaleHero * _owner, Target const& _target );
    virtual void OnEnter();
    virtual void OnAfterLeave();
  protected:
    PFBaseUseHeroState() {}

    virtual void PlayAskSound() {};
    virtual bool IsRequireLineOfSight() const;
    virtual bool CanIgnoreVisibility() const;
    virtual bool NeedToGetClose() const;
    
    ZDATA_( PFBaseUseState );
    CPtr<PFBaseMaleHero> hero;
    bool waitForChanneling;
  private:
    bool approachRequired;
    bool wasInvisible;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,( PFBaseUseState *)this); f.Add(2,&hero); f.Add(3,&waitForChanneling); f.Add(4,&approachRequired); f.Add(5,&wasInvisible); return 0; }
  };

  //////////////////////////////////////////////////////////////////////////
  class PFHeroUseConsumableState : public PFBaseUseHeroState
  {
  public:
    PFHeroUseConsumableState( PFBaseMaleHero * _pOwner, int _slot, Target const& _target );
  protected:
    
    virtual bool OnStep( float dt );

  private:
    virtual float GetUseRange() const;
    virtual NDb::Ability const* GetDBDesc() const;
    const PFConsumable * GetConsumable() const;
    PFHeroUseConsumableState() {}

    WORLD_OBJECT_METHODS( 0xF5CC3C0, PFHeroUseConsumableState )
    ZDATA_(PFBaseUseHeroState)
    int                    slot;
    NDb::Ptr<NDb::Ability> pDBDesc;
   public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseUseHeroState*)this); f.Add(2,&slot); f.Add(3,&pDBDesc); return 0; }
  };

  class PFHeroUseTalentState : public PFBaseUseHeroState
  {
  public:
    // TODO: Need to use 1 state for consumables and talents!
    PFHeroUseTalentState( PFBaseMaleHero * _pOwner, PFTalent * _talent, Target const& _target );
    virtual NDb::Ability const* GetDBDesc() const;
  protected:
   
    virtual void OnEnter();
    virtual void OnLeave();
    virtual bool OnStep( float dt );

  private:
    virtual float GetUseRange() const;
    virtual void PlayAskSound();

    PFHeroUseTalentState() {} // CPtr/CObj support
     
    WORLD_OBJECT_METHODS( 0xF6C0AC0, PFHeroUseTalentState );
    ZDATA_( PFBaseUseHeroState );
    CPtr<PFTalent> talent;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,( PFBaseUseHeroState *)this); f.Add(2,&talent); return 0; }
  };

  class PFHeroFollowUnitState : public HeroStateFSM
  {
    WORLD_OBJECT_METHODS(0x2C6A2BC1, PFHeroFollowUnitState)

    ZDATA_(HeroStateFSM)
		float followRange;
    bool             moveInitiated;
    CPtr<PFBaseUnit> pUnit;
    CPtr<PFBaseUnit> pCurrentTarget;
    float forceFollowRange;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(HeroStateFSM*)this); f.Add(2,&followRange); f.Add(3,&moveInitiated); f.Add(4,&pUnit); f.Add(5,&pCurrentTarget); f.Add(6,&forceFollowRange); return 0; }
    PFHeroFollowUnitState(CPtr<PFBaseHero> const& pOwner, CPtr<PFBaseUnit> const& pUnit, float range = 0, float forceRange = 0);

  protected:
    PFHeroFollowUnitState(){}
    virtual void OnLeave();
    virtual bool OnStep(float dt);

    void DoMove();

  };

  class PFHeroHoldState : public HeroStateFSM
  {
    WORLD_OBJECT_METHODS(0x2C6BBB80, PFHeroHoldState)

    ZDATA_(HeroStateFSM)
    CPtr<PFWorld> pWorld;
    bool doStopOnEnter;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(HeroStateFSM*)this); f.Add(2,&pWorld); f.Add(3,&doStopOnEnter); return 0; }
    PFHeroHoldState( CPtr<PFWorld> const& pWorld,  CPtr<PFBaseHero> const& pOwner, bool stopOnEnter = true );

  protected:
    PFHeroHoldState(){}
    virtual bool OnStep(float dt);

    virtual void OnEnter();
    virtual void OnLeave();
  private:
    bool IsOwnerSuitable() const;
  };

  class PFMinigamePlace;

  //////////////////////////////////////////////////////////////////////////
  class PFInteractObjectState : public HeroStateFSM
  {
    WORLD_OBJECT_METHODS(0xE7A57440, PFInteractObjectState);

    ZDATA_(HeroStateFSM)
  protected:
    Target target;
    CObj<PFAbilityInstance> pActionInstance;
    float range;
    bool used;
    CObj<IPointChecking> pointChecking;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(HeroStateFSM*)this); f.Add(2,&target); f.Add(3,&pActionInstance); f.Add(4,&range); f.Add(5,&used); f.Add(6,&pointChecking); return 0; }

    PFInteractObjectState( PFBaseHero * _pOwner, const Target& _target );
    PFInteractObjectState(){}

    void NeedStopOnLeave( bool val );
  protected:
    virtual void OnEnter();
    virtual bool OnStep( float dt );
    virtual void DoAction() {}
    virtual float GetRange() const { return range; }
    virtual void OnLeave();
    virtual bool IsActionFinished() const;
    virtual bool CanBeInterrupted() const;
    virtual void ApproachObject();
    virtual bool IsObjectInRange() const;
  };

  class PFHeroUseUnitState : public PFInteractObjectState
  {
  public:
    PFHeroUseUnitState( PFBaseHero* _pOwner, PFBaseUnit* _pBuilding );

    PFBaseUnit * GetUnit() const { return pUnit; }

  protected:
    virtual void DoAction();
  private:
    WORLD_OBJECT_METHODS(0xE78B5BC0, PFHeroUseUnitState)
    PFHeroUseUnitState() {}

    ZDATA_( PFInteractObjectState );
    CPtr<PFBaseUnit> pUnit;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,( PFInteractObjectState *)this); f.Add(2,&pUnit); return 0; }
  };

  class PFCreatureRaiseFlagState : public PFInteractObjectState
  {
    WORLD_OBJECT_METHODS(0x49771500, PFCreatureRaiseFlagState);

    ZDATA_(PFInteractObjectState)
    CPtr<PFFlagpole> pFlagpole;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFInteractObjectState*)this); f.Add(2,&pFlagpole); return 0; }

    PFCreatureRaiseFlagState( PFBaseHero* pOwner, PFFlagpole* _pFlagpole );
    PFCreatureRaiseFlagState(){}
  protected:
    virtual void DoAction();
  };

  class PFHeroPickupObjectState : public PFInteractObjectState
  {
  public:
    PFHeroPickupObjectState( PFBaseHero* pOwner, PFPickupableObjectBase* _pPickupable);
  protected:
    virtual void DoAction();
    PFHeroPickupObjectState() {}
  private:
    WORLD_OBJECT_METHODS(0xA05CEB00, PFHeroPickupObjectState)

    ZDATA_(PFInteractObjectState)
    CPtr<PFPickupableObjectBase> pPickupable;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFInteractObjectState*)this); f.Add(2,&pPickupable); return 0; }
  };

  ///////////////////////////////////////////////////////////////////////////////

  class PFHeroSuspendState : public HeroStateFSM
  {
    WORLD_OBJECT_METHODS(0x5BACCBC0, PFHeroSuspendState)

    ZDATA_(HeroStateFSM)

    float suspendTimeout;
    float waitTime;
    bool isSuspendLong;

  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(HeroStateFSM*)this); f.Add(2,&suspendTimeout); f.Add(3,&waitTime); f.Add(4,&isSuspendLong); return 0; }
    PFHeroSuspendState( CPtr<PFBaseHero> const& pOwner, bool isLongSuspend);

    // ¬сегда покидает стек при пуше другого поверх него.
    virtual bool IsEscaping() const { return true; }

  protected:
    PFHeroSuspendState();
    virtual bool OnStep(float dt);

    virtual void OnEnter();
    virtual void OnLeave();
  private:
    bool IsOwnerSuitable() const;
  };
}

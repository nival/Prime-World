#pragma once

#include "PFNeutralCreep.h"
#include "PFBaseUnitStates.h"

namespace NWorld
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct EvadeData
  {
    ZDATA
      float waitForEvadeTime;
    float waitForNextTargetTime;
    float evadeTimeout;
    float restoreHealthPercent;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&waitForEvadeTime); f.Add(3,&waitForNextTargetTime); f.Add(4,&evadeTimeout); f.Add(5,&restoreHealthPercent); return 0; }

    EvadeData() : waitForEvadeTime(0.0f), waitForNextTargetTime(0.0f), evadeTimeout(0.0f), restoreHealthPercent(0.0f) {}

    void SetData(NDb::EvadeData const & evadeData)
    {
      waitForEvadeTime      = evadeData.waitForEvadeTime;
      waitForNextTargetTime = evadeData.waitForNextTargetTime;
      evadeTimeout          = evadeData.evadeTimeout;
      restoreHealthPercent  = evadeData.restoreHealthPercent;
    }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PFNeutralCreepEvadeState
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFNeutralCreepEvadeState : public MoveUnitStateFSM
  {
  public:
    PFNeutralCreepEvadeState(const CPtr<PFWorld>& pWorld, const CPtr<PFBaseMovingUnit>& pOwner, const Placement& _initialPlacement);
  protected:
    virtual void OnEnter();
    virtual void OnLeave();
    virtual bool OnStep(float dt);
    PFNeutralCreepEvadeState() {}
  private:
    WORLD_OBJECT_METHODS(0x22852BC0, PFNeutralCreepEvadeState);
    ZDATA_(MoveUnitStateFSM);
    Placement initialPlacement;
    CPtr<PFWorld> pWorld;
    float stateTimer;
    float stateTimeOut;
    float healTimer;
    float healPercent;
    float timeForHealing;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(MoveUnitStateFSM*)this); f.Add(2,&initialPlacement); f.Add(3,&pWorld); f.Add(4,&stateTimer); f.Add(5,&stateTimeOut); f.Add(6,&healTimer); f.Add(7,&healPercent); f.Add(8,&timeForHealing); return 0; }
  };


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PFNeutralCreepWaitState
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFNeutralCreepWaitState : public MoveUnitStateFSM
  {
  public:
    PFNeutralCreepWaitState(const CPtr<PFWorld>& pWorld, const CPtr<PFBaseMovingUnit>& pOwner, const Placement& _initialPlacement, float _stateTimeOut);
  protected:
    virtual bool OnStep(float dt);
    PFNeutralCreepWaitState() {}
  private:
    WORLD_OBJECT_METHODS(0x22852C80, PFNeutralCreepWaitState);
    ZDATA_(MoveUnitStateFSM);
    Placement initialPlacement;
    float targetingRange;
    CPtr<PFWorld> pWorld;
    float stateTimer;
    float stateTimeOut;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(MoveUnitStateFSM*)this); f.Add(2,&initialPlacement); f.Add(3,&targetingRange); f.Add(4,&pWorld); f.Add(5,&stateTimer); f.Add(6,&stateTimeOut); return 0; }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Neutral creep behaviour
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFNeutralCreepBehaviour : public PFBaseBehaviour
  {
    WORLD_OBJECT_METHODS( 0x9E678300, PFNeutralCreepBehaviour )
  protected: 

    ZDATA_(PFBaseBehaviour)
      Placement initialPlacement;
    float     targetingRange;
    bool      useEvade;
    EvadeData evadeParams;
    CPtr<PFBaseUnit> pLastTarget;
    float         timerMovingStacked;
    bool          stacked;
    bool          unsummoned;
    CPtr<PFNeutralCreep> pNeutralCreep;
    vector<CVec2> wayPoints;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseBehaviour*)this); f.Add(2,&initialPlacement); f.Add(3,&targetingRange); f.Add(4,&useEvade); f.Add(5,&evadeParams); f.Add(6,&pLastTarget); f.Add(7,&timerMovingStacked); f.Add(8,&stacked); f.Add(9,&unsummoned); f.Add(10,&pNeutralCreep); f.Add(11,&wayPoints); return 0; }

    PFNeutralCreepBehaviour( PFNeutralCreep *pCreep, const Placement& _initialPlacement, const vector<CVec2>& _wayPoints );
    PFNeutralCreepBehaviour() {}

    virtual bool OnStep( float dtInSeconds );
    virtual void OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget );
    virtual void OnDamage( const PFBaseUnitDamageDesc& desc );
    virtual bool CanSelectTarget( PFBaseUnit const* pTarget, bool mustSeeTarget = false ) const;
    bool IsCreepAtSpawner( float distInTiles ) const;
    virtual bool IsInDefaultState() const;
    PFNeutralCreep* GetUnit() const { return static_cast<PFNeutralCreep*>( pUnit.GetPtr() ); }
    virtual bool IsAttackedUnitAlly( const CPtr<PFBaseUnit>& pAttacked, NDb::EFaction originalAttackedFaction ) const;
    void DoScream( const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st );
    virtual void Resume();
    void Stacked( const bool _stacked = true ) { stacked = _stacked; }
    const vector<CVec2>& WayPoints() const { return wayPoints; }
    virtual void  GetKillerAward(CPtr<PFBaseUnit> pKiller, NaftaAward& award);
  };

  class PFNeutralCreepBaseMoveBehaviour : public PFBaseBehaviour
  {
    OBJECT_ABSTRACT_METHODS( PFNeutralCreepBaseMoveBehaviour )
  private: 

    ZDATA_(PFBaseBehaviour)
    float chaseRange;
    CVec2 lastMovePoint;
    float targetingDelay;
    CPtr<PFBaseUnit> pLastTarget;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseBehaviour*)this); f.Add(2,&chaseRange); f.Add(3,&lastMovePoint); f.Add(4,&targetingDelay); f.Add(5,&pLastTarget); return 0; }

    PFNeutralCreepBaseMoveBehaviour( PFNeutralCreep *pCreep, float chaseRange  );
    PFNeutralCreepBaseMoveBehaviour(): chaseRange(0.f), targetingDelay(0.f), lastMovePoint(0.f,0.f) {}

    virtual bool OnStep( float dtInSeconds );
    virtual void OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget );
    virtual void OnDamage( const PFBaseUnitDamageDesc& desc );
    virtual bool CanSelectTarget( PFBaseUnit const* pTarget, bool mustSeeTarget = false ) const;
    virtual bool IsInDefaultState() const;
  protected:
    PFNeutralCreep* GetUnit() const { return static_cast<PFNeutralCreep*>( pUnit.GetPtr() ); }
    virtual bool IsMoveFinished() const = 0;
    virtual void ContinueMove() = 0;
  };

  class PFNeutralCreepMoveToPointBehaviour : public PFNeutralCreepBaseMoveBehaviour
  {
    WORLD_OBJECT_METHODS( 0x9A9C94C1, PFNeutralCreepMoveToPointBehaviour )
  private: 

    ZDATA_(PFNeutralCreepBaseMoveBehaviour)
    CVec2 targetPoint;
    float targetRange;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFNeutralCreepBaseMoveBehaviour*)this); f.Add(2,&targetPoint); f.Add(3,&targetRange); return 0; }

    PFNeutralCreepMoveToPointBehaviour( PFNeutralCreep *pCreep,const CVec2& targetPoint, float targetRange, float chaseRange );
    PFNeutralCreepMoveToPointBehaviour():targetRange(0.f),targetPoint(0.f, 0.f) {}

    static PFNeutralCreepMoveToPointBehaviour* CreateWithParams( PFNeutralCreep *pCreep, const vector<string>& params );
  protected:
    virtual bool IsMoveFinished() const;
    virtual void ContinueMove();
  };

  class PFNeutralCreepMoveByPathBehaviour : public PFNeutralCreepBaseMoveBehaviour
  {
    WORLD_OBJECT_METHODS( 0x9A9C94C0, PFNeutralCreepMoveByPathBehaviour )
  private: 

    ZDATA_(PFNeutralCreepBaseMoveBehaviour)
    vector<CVec2> wayPoints;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFNeutralCreepBaseMoveBehaviour*)this); f.Add(2,&wayPoints); return 0; }

    PFNeutralCreepMoveByPathBehaviour( PFNeutralCreep *pCreep, const vector<CVec2>& wayPoints, float chaseRange );
    PFNeutralCreepMoveByPathBehaviour() {}

    static PFNeutralCreepMoveByPathBehaviour* CreateWithParams( PFNeutralCreep *pCreep, const vector<string>& params );
  protected:
    virtual bool IsMoveFinished() const;
    virtual void ContinueMove();
  };

  class PFNeutralCreepChaseBehaviour : public PFNeutralCreepBaseMoveBehaviour
  {
    WORLD_OBJECT_METHODS( 0x9A9C94C2, PFNeutralCreepChaseBehaviour )
  private: 

    ZDATA_(PFNeutralCreepBaseMoveBehaviour)
    CPtr<PFBaseUnit> pChaseTarget;
    float targetRange;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFNeutralCreepBaseMoveBehaviour*)this); f.Add(2,&pChaseTarget); f.Add(3,&targetRange); return 0; }

    PFNeutralCreepChaseBehaviour( PFNeutralCreep *pCreep, PFBaseUnit* pTarget, float targetRange, float chaseRange );
    PFNeutralCreepChaseBehaviour() {}

    static PFNeutralCreepChaseBehaviour* CreateWithParams( PFNeutralCreep *pCreep, const vector<string>& params );
  protected:
    virtual bool IsMoveFinished() const;
    virtual void ContinueMove();
  };
} // namespace

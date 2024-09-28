#pragma once 

#include "PFState.h"
#include "PFBaseUnit.h"
#include "PointChecking.h"

namespace NWorld
{
  class PFBaseMovingUnit;
  class PFFlagpole;
  class PFCreature;
  class PFBuilding;
  
  void PushAttackState( PFHFSM* fsm, PFBaseMovingUnit* owner, PFBaseUnit* target, bool strongTarget, bool scream, bool ignoreChaseRange = false );
  void EnqueueAttackState( PFBaseMovingUnit* owner, PFBaseUnit* target, bool strongTarget, bool scream, bool ignoreChaseRange = false );

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // base class for fsm state for MovingUnits
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class MoveUnitStateFSM: public PFBaseMovingUnitState, protected PFHFSM
  {
    ZDATA_(PFBaseMovingUnitState);
    ZPARENT(PFHFSM)
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,(PFHFSM*)this); return 0; }
    MoveUnitStateFSM( PFBaseMovingUnit * pOwner) : PFBaseMovingUnitState(pOwner) {}
    virtual void DumpStateToConsole(int depths);
  protected:
    MoveUnitStateFSM() {}
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Simple movement
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFBaseUnitMoveToState : public PFBaseMovingUnitState
  {
    WORLD_OBJECT_METHODS(0xF5CC381, PFBaseUnitMoveToState);

  public:
    PFBaseUnitMoveToState( PFBaseMovingUnit* _pUnit, const CVec2& _target, const float _range, bool _requireLOS = false );
    void SetNewParams( const CVec2& _target, const float _range, bool _requireLOS = false ) { target = _target; range = _range > 0.f ? _range : 1.0f; requireLineOfSight = _requireLOS; initiatedMove = false; }
  protected:
    virtual bool OnStep(float dt);
    virtual void OnEnter();
    virtual void OnLeave();
    PFBaseUnitMoveToState() {}
  private:
    ZDATA_(PFBaseMovingUnitState)
    float range;
    bool  initiatedMove;
    CVec2 target;
    bool requireLineOfSight;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,&range); f.Add(3,&initiatedMove); f.Add(4,&target); f.Add(5,&requireLineOfSight); return 0; }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Simple movement
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFBaseUnitMoveToBuildingState : public PFBaseMovingUnitState
  {
    WORLD_OBJECT_METHODS(0x8B795240, PFBaseUnitMoveToBuildingState);

  public:
    PFBaseUnitMoveToBuildingState(PFBaseMovingUnit * pUnit, PFBaseUnit * _targetBuilding, IPointChecking * _pointChecking, bool _requireLineOfSight = true);
    void NeedStopOnLeave( bool val ) { needStopOnLeave = val; }
  protected:
    virtual bool OnStep(float dt);
    virtual void OnLeave();
    PFBaseUnitMoveToBuildingState() {}
  private:
    ZDATA_(PFBaseMovingUnitState)
    CObj<IPointChecking> pointChecking;
    bool  initiatedMove;
    CPtr<PFBaseUnit> targetBuilding;
    bool requireLineOfSight;
    bool needStopOnLeave;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,&pointChecking); f.Add(3,&initiatedMove); f.Add(4,&targetBuilding); f.Add(5,&requireLineOfSight); f.Add(6,&needStopOnLeave); return 0; }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Path movement
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFBaseUnitPathMovingState : public PFBaseMovingUnitState
  {
    WORLD_OBJECT_METHODS(0x8D7C4480, PFBaseUnitPathMovingState);

  public:
    PFBaseUnitPathMovingState(CPtr<PFBaseMovingUnit> const& pUnit, vector<CVec2> const & _wayPoints, const float _range);
  protected:
    virtual bool OnStep(float dt);
    virtual void OnLeave();
    PFBaseUnitPathMovingState() {}
  private:
    const CVec2& GetNextWaypoint() const;

    ZDATA_(PFBaseMovingUnitState)
    vector<CVec2> wayPoints;
    CVec2 currentPoint;
    bool  isFirstMove;
    float range;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,&wayPoints); f.Add(3,&currentPoint); f.Add(4,&isFirstMove); f.Add(5,&range); return 0; }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Chase state
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFBaseUnitChaseState : public PFBaseMovingUnitState
  {
    WORLD_OBJECT_METHODS(0xF5CC382, PFBaseUnitChaseState);

  public:
    PFBaseUnitChaseState(PFBaseMovingUnit * pOwner, bool _requireLineOfSight, float attackRange, float chaseRange, PFBaseUnit * target, bool strongTarget, bool ignoreVisibility = false, bool useAttackRange = false);
  protected:
    virtual bool OnStep(float dt);
    virtual void OnLeave();
    virtual void OnDestroyContents();
    PFBaseUnitChaseState() {}
  private:
    ZDATA_(PFBaseMovingUnitState)
    CPtr<PFBaseUnit> targetUnit;
    CVec2 lastPos;
    float halfTargetSize;
    float attackRange;
    float chaseRange;
    bool  requireLineOfSight;
    bool strongTarget;
    int attackSector;
    bool ignoreVisibility;
    bool useAttackRange;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,&targetUnit); f.Add(3,&lastPos); f.Add(4,&halfTargetSize); f.Add(5,&attackRange); f.Add(6,&chaseRange); f.Add(7,&requireLineOfSight); f.Add(8,&strongTarget); f.Add(9,&attackSector); f.Add(10,&ignoreVisibility); f.Add(11,&useAttackRange); return 0; }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Attack state
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFBaseUnitAttackState : public MoveUnitStateFSM
  {
    WORLD_OBJECT_METHODS(0xF5CC383, PFBaseUnitAttackState);

  public:
    PFBaseUnitAttackState(CPtr<PFWorld> const& pWorld, CPtr<PFBaseMovingUnit> const& pOwner, const CPtr<PFBaseUnit>& pTarget, 
			                    bool strongTarget = true, bool ignoreChaseRange = false, bool ignoreVisibility = false, bool _allowAllies = false, bool _allowChase = true );

    const PFBaseUnit* GetTarget() const { return pTarget; }
  protected:
    virtual bool OnStep(float dt);
    PFBaseUnitAttackState() {}
    virtual void OnEnter();
    virtual void OnLeave();
    virtual bool IsBlocking() const;
    virtual void InformStatePassingThrough() { statePassedThrough = true; }
  private:
    bool isTargetDropped(const PFBaseUnit* pTarget);
    
    ZDATA_(MoveUnitStateFSM)
    CPtr<PFWorld>    pWorld;
    CPtr<PFBaseUnit> pTarget;
    bool             strongTarget;
    bool             ignoreChaseRange;
    bool             statePassedThrough;
    bool             ignoreVisibility;
    bool             allowAllies;
    bool             allowChase;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(MoveUnitStateFSM*)this); f.Add(2,&pWorld); f.Add(3,&pTarget); f.Add(4,&strongTarget); f.Add(5,&ignoreChaseRange); f.Add(6,&statePassedThrough); f.Add(7,&ignoreVisibility); f.Add(8,&allowAllies); f.Add(9,&allowChase); return 0; }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Combat move state
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFBaseUnitCombatMoveState: public MoveUnitStateFSM
  {
    WORLD_OBJECT_METHODS(0xF5CC384, PFBaseUnitCombatMoveState);

  public:
    PFBaseUnitCombatMoveState( const CPtr<PFWorld>& pWorld, const CPtr<PFBaseMovingUnit>& pOwner, const CVec2& target, float range = EPS_VALUE );
  protected:
    virtual bool OnStep(float dt);
    PFBaseUnitCombatMoveState() {}
    virtual void OnLeave();
  private:
    ZDATA_(MoveUnitStateFSM)
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(MoveUnitStateFSM*)this); return 0; }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Combat move to building state
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFBaseUnitCombatMoveToBuildingState : public MoveUnitStateFSM
  {
    WORLD_OBJECT_METHODS(0x15BA13C0, PFBaseUnitCombatMoveToBuildingState);
  public:
    PFBaseUnitCombatMoveToBuildingState(const CPtr<PFWorld>& pWorld, PFBaseMovingUnit* pUnit, PFBaseUnit* pTarget, IPointChecking* pPointChecking, bool requireLineOfSight = true);
  protected:
    PFBaseUnitCombatMoveToBuildingState() {}

    virtual bool OnStep(float dt);
    virtual void OnLeave();
  private:
    ZDATA_(MoveUnitStateFSM)

    CPtr<PFWorld> pWorld;
    CPtr<PFBaseUnit> pTarget;

    float targetSearchInterval;
    float targetSearchTimer;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(MoveUnitStateFSM*)this); f.Add(2,&pWorld); f.Add(3,&pTarget); f.Add(4,&targetSearchInterval); f.Add(5,&targetSearchTimer); return 0; }
  };

} // namespace NWorld
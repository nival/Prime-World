#pragma once

#include "PFBaseUnitStates.h"
#include "PFAIController.h"

namespace NWorld
{

  //static const char* EscapeFromTowerName = "EscapeFromTower";
  //static const char* BackToFrontName = "BackToWarFront";
  //static const char* AttackTowerName = "AttackingTower";
  //static const char* FlagRaisingName = "FlagRaising";

  //===========================================================================
  enum PFAIStatesEnum
  {
    NONE = 0,
    ESCAPEFROMTOWER,
    BACKTOWARFRONT,
    ATTACKINGTOWER,
    FLAGRAISING,
    COMBATMOVE,
    MOVE,
    HEALING,
    SHOPPING,
    TELEPORT,
    GOTOBUILDING,
    ATTACKUNIT,
    MOVELINEFORWARD,
    MOVELINEBACKWARD
  };

  const char *PFAIStatesEnum_ToString( const PFAIStatesEnum value );

  //===========================================================================

  class PFShop;
  class PFBaseMaleHero;
  class PFTalent;

  class AIBaseState;

  ///////////////////////////////////////////////////////////////////////////////
  //	AI states
  ///////////////////////////////////////////////////////////////////////////////

  class AIBaseState : public TPFState<PFBaseAIController>, public CObjectBase
  {
    OBJECT_METHODS( 0x8D7C44C0, AIBaseState )
      AIBaseState() : pHelper(0) {}
  public:
    AIBaseState( const CPtr<PFBaseAIController>& pUnit, PFAIStatesEnum state )
      :	TPFState( pUnit )
      , pHelper( &pUnit->GetHelper() )
      , stateType(state)
    {}

    void DumpState( const char* state )
    {
      if( IsValid( pOwner ) && pHelper && pOwner->IsDumpStates() && state )
        pHelper->GetWorld()->GetIAdventureScreen()->DumpState( GetObjectTypeName(), state );
    }

    //const char *stateName;
    PFAIStatesEnum stateType;
  protected:
    PFAIHelper *pHelper;
  };

  // Move to specified point
  class AIMoveToState : public AIBaseState
  {
  public:
    AIMoveToState( const CPtr<PFBaseAIController>& pUnit, const CVec2& _target, const float _range, bool _canCombat = false )
      :	AIBaseState( pUnit, _canCombat ? COMBATMOVE : MOVE )
      ,	target(_target)
      ,	range(_range)
      , canCombat(_canCombat)
      ,	delay(0)
    {}

  protected:
    virtual void OnEnter();
    virtual bool OnStep( float dt );
    virtual void OnLeave( )
    {
      #if LOG_AI_MOVE
        //CVec2 pos = pHelper->pUnit->GetPosition().AsVec2D();
        //DBGM( "AIMoveToState:OnLeave going to %g,%g (pos %g,%g, range = %g)", target.x, target.y, pos.x, pos.y, range  );
      #endif // LOG_AI_MOVE
    };

    CVec2		target;
    float		range;
    bool		canCombat;
    int			delay;
  };

  // Move along one of the world lines until its end. When "reverse" is true, opposite
  // line direction is used. There is a smart start point selection: when unit placed in
  // a middle of a line and it moved to AIMoveByLineState, it will start its movement
  // from nearest line point, not from its 1st point.
  class AIMoveByLineState : public AIBaseState, public PFHFSM
  {
  public:
    AIMoveByLineState( const CPtr<PFBaseAIController>& pUnit, const vector<CVec2>& _road, bool _reverse = false, PFAIController* ctrl = 0 );

  protected:
#if LOG_AI_MOVE
    //virtual void OnEnter() { DBGM( "AI line[%X]: started", (int)this ); }
    //virtual void OnLeave() { DBGM( "AI line[%X]: stopped", (int)this ); }
#endif // LOG_AI_MOVE

    bool PushNextWaypoint();

    virtual bool OnStep( float dt );

    vector<CVec2>		road;
    bool						canCombat;
    CPtr<PFAIController>  ctrl;
  };


  class AIHealingState : public AIBaseState
  {
  public:
    AIHealingState(const CPtr<PFBaseAIController>& pUnit)
      :	AIBaseState(pUnit, HEALING)
    {}

  protected:
    virtual void OnLeave();
    virtual bool OnStep( float dt );
  };


  class AIShoppingState : public AIBaseState
  {
  public:
    AIShoppingState(const CPtr<PFBaseAIController>& pUnit, PFShop* _pShop) : AIBaseState( pUnit, SHOPPING ), pShop( _pShop ) {}

  protected:
    virtual bool OnStep( float dt );

    CPtr<PFShop>  pShop;
  };

  class AIFlagRaisingState : public AIBaseState
    {
    public:
      AIFlagRaisingState(const CPtr<PFBaseAIController>& pUnit, PFFlagpole* _pFlag) :
          AIBaseState( pUnit, FLAGRAISING )
          ,pFlag( _pFlag )
          ,range(AiConst::MOVE_TO_FLAG_SENS())
          {}

    protected:
      virtual bool OnStep( float dt );

      CPtr<PFFlagpole>  pFlag;
      float range;
    };
    
  class AIUseTeleportState : public AIBaseState
  {
  public:
    AIUseTeleportState( PFAIController* ctrl, Target target ) :	AIBaseState( ctrl, TELEPORT ), target( target ), ctrl(ctrl) {}

  protected:
    virtual bool OnStep( float dt );
    virtual void OnLeave();
    Target target;
    CPtr<PFAIController>  ctrl;
  };

  class AIGoToObjectState : public AIBaseState
  {
  public:
    AIGoToObjectState(const CPtr<PFBaseAIController>& pUnit, PFBaseUnit* _pTarget)
      :	AIBaseState( pUnit, GOTOBUILDING )
      , pTarget( _pTarget )
      , delay(0)
    {}

    virtual void OnEnter();
    virtual bool OnStep( float dt );

    CPtr<PFBaseUnit> pTarget;
    int			         delay;
  };

  class AIAttackUnitState : public AIBaseState
  {
  public:
    //static const char* Name;
    AIAttackUnitState(const CPtr<PFBaseAIController>& pUnit, PFBaseUnit* _pTarget)
      :	AIBaseState( pUnit, ATTACKUNIT )
      , pTarget( _pTarget )
      , delay(0)
    {}

    virtual void OnEnter();
    virtual bool OnStep( float dt );

    CPtr<PFBaseUnit> pTarget;
    int			         delay;
  };

  class EscapeFromTowerState : public AIMoveToState
  {
    CPtr<PFBaseUnit> pTower;
    float checkTime;
  public:
    EscapeFromTowerState( 
      const CPtr<PFBaseAIController>& pUnit, 
      const CPtr<PFBaseUnit>& _pTower, 
      const CVec2& _target, const float _range ) : AIMoveToState(pUnit, _target, _range, false) 
    {
      checkTime = 1.0f;
      pTower = _pTower;
    }

    virtual bool OnStep( float dt );
  };

}
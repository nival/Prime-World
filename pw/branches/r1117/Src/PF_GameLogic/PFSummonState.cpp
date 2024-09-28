#include "stdafx.h"
#include "PFSummonState.h"
#include "PFBaseUnitStates.h"
#include "PFSummoned.h"

namespace NWorld
{

  const float RETURN_TO_MASTER_TIMEOUT = 2.0f;

  //////////////////////////////////////////////////////////////////////////
  // class PFSummonAIChaseState
  //////////////////////////////////////////////////////////////////////////
  class PFSummonAIChaseTargetState
    : public PFBaseMovingUnitState
  {
    WORLD_OBJECT_METHODS(0xF618480, PFSummonAIChaseTargetState);

  public:
    PFSummonAIChaseTargetState( CPtr<PFBaseMovingUnit> const& pOwner, float maxEscortDistance );
  protected:
    virtual void OnEnter();
    virtual bool OnStep(float dt);
    virtual void OnLeave();
    PFSummonAIChaseTargetState() {}

  private:
    ZDATA_(PFBaseMovingUnitState);
    CPtr<PFBaseUnit>     pMaster;
    float                maxChaseDistance;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,&pMaster); f.Add(3,&maxChaseDistance); return 0; }
  };

  PFSummonAIChaseTargetState::PFSummonAIChaseTargetState( CPtr<PFBaseMovingUnit> const& pOwner, float maxChaseDistance )
    : PFBaseMovingUnitState(pOwner)
    , maxChaseDistance(maxChaseDistance)
  {
    if ( IsUnitValid(pOwner) )
      pMaster = pOwner->GetMasterUnit();
  }

  bool PFSummonAIChaseTargetState::OnStep( float dt )
  {
    if ( !IsUnitValid( pOwner ) || !IsValid( pMaster ) )
    {
      return true;
    }

    CPtr<PFBaseUnit> pTarget = pOwner->GetCurrentTarget();
    if ( !pOwner->CanAttackTarget( pTarget ) )
    {
      return true;
    }

    if ( pOwner->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDMOVE ) )
    {
      return pOwner->IsTargetInAttackRange( pTarget );
    }

    const CVec2& targetPosition = pTarget->GetPosition().AsVec2D();

    // check distance to master only if have not strong target or forbid flag
    if ( maxChaseDistance && !pOwner->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDSELECTTARGET ) )
    {
      if ( !pMaster->IsTargetInRange( pOwner, maxChaseDistance ) )
      {
        return true; // owner is too far from master
      }
      if ( !pMaster->IsTargetInRange( pTarget, maxChaseDistance ) )
      {
        return true; // target is too far from master
      }
    }

    // Check distance to target
    if ( pOwner->IsTargetInAttackRange( pTarget ) )
    {
      return true; // target reached
    }

    pOwner->MoveTo( targetPosition );
    return false;
  }

  void PFSummonAIChaseTargetState::OnEnter()
  {
    pOwner->OnChasing(true);
  }

  void PFSummonAIChaseTargetState::OnLeave()
  {
    if( IsValid(pOwner) )
    {
      pOwner->OnChasing(false);

      if( pOwner->IsMoving() )
        pOwner->Stop();
    }
    
  }

  //////////////////////////////////////////////////////////////////////////
  // class PFSummonAICombateState
  //////////////////////////////////////////////////////////////////////////
  class PFSummonAICombateState
    : public PFBaseMovingUnitState
  {
    WORLD_OBJECT_METHODS(0xF618481, PFSummonAICombateState);

  public:
    PFSummonAICombateState( CPtr<PFBaseMovingUnit> const& pOwner, float maxEscortDistance );
  protected:
    virtual bool OnStep(float dt);
    PFSummonAICombateState() {}

  private:
    ZDATA_(PFBaseMovingUnitState);
    CPtr<PFBaseUnit> pMaster;
    float            maxChaseDistance;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseMovingUnitState*)this); f.Add(2,&pMaster); f.Add(3,&maxChaseDistance); return 0; }
  };

  PFSummonAICombateState::PFSummonAICombateState( CPtr<PFBaseMovingUnit> const& pOwner, float maxChaseDistance )
    : PFBaseMovingUnitState(pOwner)
    , maxChaseDistance(maxChaseDistance)
  {
    if ( IsUnitValid( pOwner ) )
      pMaster = pOwner->GetMasterUnit();
  }

  bool PFSummonAICombateState::OnStep( float /*dt*/ )
  {
    if( !IsUnitValid( pOwner ) || !IsValid( pMaster ) )
    {
      return true;
    }

    CPtr<PFBaseUnit> pTarget = pOwner->GetCurrentTarget();
    if ( !pOwner->CanAttackTarget( pTarget ) )
    {
      return true;
    }

    if ( maxChaseDistance && !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDSELECTTARGET) )
    {
      if ( !pMaster->IsTargetInRange( pOwner, maxChaseDistance ) )
      {
        return true; // слишком далеко от мастера
      }
    }

    if ( !pOwner->IsTargetInAttackRange( pTarget ) )
    {
      return true; // слишком далеко от цели
    }

    return pOwner->IsReadyToAttack() && !pOwner->DoAttack();
  }

  //////////////////////////////////////////////////////////////////////////
  // class PFSummonAIAttackState
  //////////////////////////////////////////////////////////////////////////
  PFSummonAIAttackState::PFSummonAIAttackState( CPtr<PFBaseMovingUnit> const& pOwner, CPtr<PFBaseUnit> pTarget, bool bStrongTarget )
    : PFBaseMovingUnitState(pOwner)
    , maxChaseDistance(0.0f)
    , bStrongTarget(bStrongTarget)
    , pTarget(pTarget)
    , isStationarySummon(false)
    , leashRange (0.f)
  {
    if ( IsUnitValid(pOwner) )
    {
      pMaster = pOwner->GetMasterUnit();
      maxChaseDistance = pOwner->GetChaseRange();
      //if( const PFBaseBehaviour* pBehaviour = pOwner->GetBehaviour())
      //{
      //  const PFSummonBehaviour* pSummonBehaviour = dynamic_cast<const PFSummonBehaviour*>(pBehaviour);
      //  leashRange = pSummonBehaviour ? pSummonBehaviour->GetLashRange(): pOwner->GetChaseRange();
      //}
      leashRange = maxChaseDistance;
      isStationarySummon = pOwner->GetTargetingParams().isStationarySummon;
    }
  }

  void PFSummonAIAttackState::OnEnter()
  {
    if ( IsUnitValid(pOwner) && pTarget != pOwner )
      pOwner->AssignTarget( pTarget, bStrongTarget );
  }

  void PFSummonAIAttackState::OnLeave()
  {
    if ( IsUnitValid(pOwner) )
      pOwner->DropTarget();
  }

  bool PFSummonAIAttackState::OnStep( float dt )
  {
    if ( !IsUnitValid( pOwner ) || !IsValid( pMaster ) )
    {
      return true;
    }

    CPtr<PFBaseUnit> pTarget = pOwner->GetCurrentTarget();
    NI_VERIFY( pOwner != pTarget, "Cannot attack self!", return true );

    if ( !IsUnitValid( pTarget ) )
    {
      return true;
    }


    if ( !isStationarySummon && !pOwner->IsInTaunt() )
    {
      if ( !pOwner->IsTargetInRange( pMaster, leashRange ) )
      {
        return true;
      }
      if ( !pMaster->IsTargetInRange( pTarget, maxChaseDistance ) )
      {
        return true; // target is too far from master
      }
    }

    if ( !GetCurrentState() )
    {
      if ( !pOwner->CanAttackTarget( pTarget) )
        return true;

      bool isTargetInAttackRange = pOwner->IsTargetInAttackRange( pTarget );

      if ( isStationarySummon && !isTargetInAttackRange )
        return true;

      //if(isTargetInAttackRange)
        PushState( new PFSummonAICombateState( pOwner, pOwner->IsInTaunt() ? 0 : maxChaseDistance ) );

      if ( !isStationarySummon && /*!isTargetInAttackRange &&*/ !pOwner->IsChasing() )
      {
        PushState( new PFSummonAIChaseTargetState( pOwner, pOwner->IsInTaunt() ? 0 : maxChaseDistance ) );
      }
    }

    const IPFState* pPrevious = GetCurrentState();

    FSMStep( dt );
    if( pPrevious != GetCurrentState() )
    {
      FSMStep( 0.0f );
    }

    return false;
  }


  //////////////////////////////////////////////////////////////////////////


  PFSummonAIBaseState::PFSummonAIBaseState( const CPtr<PFBaseMovingUnit>& pOwner )
    : PFBaseMovingUnitState( pOwner )
    , maxEscortDistance( 0.0f )
    , isStationarySummon(false)
    , lastMasterDestination( 0.0f, 0.0f )
    , masterDestination( 0.0f, 0.0f )
    , currentTask( ST_BACK_TO_FORMATION_PLACE )
    , returnToMasterTimeout(0.0f)
    , ignoreTargetsTimer(0.0f)
  {
    if ( IsUnitValid( pOwner ) )
    {
      pMaster = pOwner->GetMasterUnit();
      const PFSummonedUnitAIBehaviour* pB = static_cast<const PFSummonedUnitAIBehaviour*>( pOwner->GetBehaviour() );
      maxEscortDistance =  pB ? Min( pB->GetLashRange(), pOwner->GetChaseRange() ) : pOwner->GetChaseRange();
      //lastMasterDestination = pOwner->GetPosition().AsVec2D();
      isStationarySummon = pOwner->GetTargetingParams().isStationarySummon;
    }
  }

  bool PFSummonAIBaseState::OnStep( float dt )
  {
    // –ежим следовани€ за игроком. ѕеремещаемс€ в позицию р€дом с игроком
    // ≈сли в targetingRange по€вл€етс€ враг - переходим в спец. режим атаки

    if ( GetCurrentState() )
    {
      FSMStep( dt );
    }

    if ( !IsUnitValid( pOwner ) || !IsValid( pMaster ) )
    {
      return true;
    }

    if ( !GetCurrentState() )
    {
      if (ignoreTargetsTimer > 0)
        ignoreTargetsTimer -= dt;
      else
      {
        // »щем цель, только если находимс€ достаточно близко к мастеру
        if ( isStationarySummon || pMaster->IsTargetInRange( pOwner, maxEscortDistance ))
        {
          CPtr<PFBaseUnit> pTarget = pOwner->FindTarget( pOwner->GetTargetingRange() );
          //ѕровер€ем что цель валидна и от мастера находитс€ в дистанции чейза 
          if ( IsUnitValid( pTarget ) /*&& pMaster->IsTargetInRange( pTarget, pOwner->GetChaseRange() )*/ )
          {
            // јтакуем цель в области видимости
            pOwner->PushState( new PFSummonAIAttackState( pOwner, pTarget, false ) );
            return false;
          }
        }
      }


      if ( !isStationarySummon && !pOwner->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDMOVE ) )
      {
        const PFSummonedUnitAIBehaviour* pB = dynamic_cast<const PFSummonedUnitAIBehaviour*>( pOwner->GetBehaviour() );
        if ( pB )
        {
          CVec2 masterPosition = pMaster->GetPosition().AsVec2D();
          CVec2 escortOffset   = pB->GetMasterOffset();
          CVec2 targetPosition = masterPosition;

          if(!pMaster->IsMounted())
            targetPosition += escortOffset;

          returnToMasterTimeout -= dt;
          if ( returnToMasterTimeout <= 0.0f )
          {
            if ( !pOwner->IsPositionInRange( masterPosition, maxEscortDistance ) )
              //if (!pMaster->IsTargetInRange( pOwner, maxEscortDistance ))
            {
              //мы слишком далеко; идЄм к хоз€ину
              pOwner->MoveTo( targetPosition );
              currentTask = ST_RETURN_TO_LASH_RANGE;
              return false;
            }
            else
            {
              returnToMasterTimeout = RETURN_TO_MASTER_TIMEOUT;
              if (currentTask == ST_RETURN_TO_LASH_RANGE)
                currentTask = ST_BACK_TO_FORMATION_PLACE;
            }
          }

          PFBaseMovingUnit const* pMovingMaster = dynamic_cast<PFBaseMovingUnit const*>( pMaster.GetPtr() );
          if ( pMovingMaster )
          {
            if ( pMovingMaster->IsMoving() )
            {
              if(pMovingMaster->IsMounted())
              {
                lastMasterDestination = masterDestination = targetPosition;
                //currentTask = ST_MOVE_TO_MASTER_DESTINATION;
              }
              else
              {
                // двигаемс€ туда же, куда и хоз€ин
                masterDestination = pMovingMaster->GetDestination();
              }
            }

            if ( masterDestination != lastMasterDestination || 
              (!pMovingMaster->IsMounted() && pMovingMaster->IsMoving() && currentTask == ST_NONE ) )
            {
              targetPosition = masterDestination + escortOffset;

              // хоз€ин изменил направление движени€
              pOwner->MoveTo( targetPosition );
              lastMasterDestination = masterDestination;
              if (currentTask == ST_NONE)
                returnToMasterTimeout = RETURN_TO_MASTER_TIMEOUT;
              currentTask = ST_MOVE_TO_MASTER_DESTINATION;
              return false;
            }
          }

          /*bool bCanCangePos = !pOwner->IsMoving() && (pMovingMaster && !pMovingMaster->IsMoving());
          CVec2 pos = pOwner->GetPos();
          */
          if ( currentTask == ST_BACK_TO_FORMATION_PLACE )
          {
            currentTask = ST_NONE;
            if ( !pOwner->IsPositionInRange( targetPosition, 1.0f ) )
            {
              // идЄм в целевую точку
              pOwner->MoveTo( targetPosition );
              returnToMasterTimeout = RETURN_TO_MASTER_TIMEOUT;
              return false;
            }
          }
        }

      }
    }
    return false;
  }

  //////////////////////////////////////////////////////////////////////////
  /*

  PFSummonAIResponseState::PFSummonAIResponseState( CPtr<PFBaseMovingUnit> const& pOwner, const CVec2& masterDestination, float responseTime )
  : PFBaseMovingUnitState( pOwner )
  , masterDestination( masterDestination )
  , moveToDestination( false )
  , ignoreTargetsTimer( responseTime )
  {
  if ( IsUnitValid( pOwner ) )
  {
  pMaster = pOwner->GetMasterUnit();
  //ignoreTargetsTimer = pOwner->GetResponseTime();
  }
  }

  bool PFSummonAIResponseState::OnStep( float dt )
  {
  if ( GetCurrentState() )
  {
  FSMStep( dt );
  }

  if ( !IsUnitValid( pOwner ) || !IsValid( pMaster ) )
  {
  return true;
  }

  if (pOwner->GetTargetingParams().isStationarySummon)
  return true;

  ignoreTargetsTimer -= dt;
  if (ignoreTargetsTimer < 0)
  return true;

  if ( !GetCurrentState() )
  {

  if ( !pOwner->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDMOVE ) )
  {
  const PFSummonedUnitAIBehaviour* pB = static_cast<const PFSummonedUnitAIBehaviour*>( pOwner->GetBehaviour() );
  if ( pB )
  {
  CVec2 escortOffset   = pB->GetMasterOffset();
  CVec2 targetPosition = masterDestination + escortOffset;

  if ( pOwner->IsPositionInRange( targetPosition, 2.0f ) )
  return true;

  if ( !moveToDestination )
  {
  // идЄм в целевую точку
  pOwner->MoveTo( targetPosition );
  moveToDestination = true;
  }
  else
  {
  if (!pOwner->IsMoving())
  return true;
  }
  }
  }
  }
  else
  {
  if ( moveToDestination )
  moveToDestination = false;
  }

  return false;
  }
  */


} // namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFSummonAIBaseState,         NWorld);
REGISTER_WORLD_OBJECT_NM(PFSummonAIChaseTargetState,  NWorld);
REGISTER_WORLD_OBJECT_NM(PFSummonAICombateState,      NWorld);
REGISTER_WORLD_OBJECT_NM(PFSummonAIAttackState,       NWorld);
//REGISTER_WORLD_OBJECT_NM(PFSummonAIResponseState,     NWorld);

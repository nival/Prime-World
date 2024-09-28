#include "stdafx.h"
#include "PFBaseUnitStates.h"
#include "PFBaseMovingUnit.h"
#include "PFDispatchStrike1.h"
#include "PFApplicator.h"
#include "PFDispatchFactory.h"
#include "PFAIWorld.h"

#include "PathChecker.h"
#include "TileMap.h"

#include "PFFlagpole.h"
#include "PFCreature.h"
#include "PFBuildings.h"
#include "PFAbilityData.h"
#include "PFBaseAttackData.h"
#include "PFAbilityInstance.h"

#include "WarFog.h"

#include "DBGameLogic.h"
#include "PFClientBaseMovingUnit.h"

#include "RegionPointChecker.h"
#include "PFMinigamePlace.h"
#include "PFClientCreature.h"
#include "AdventureScreen.h"  // For TempDebugTrace. Remove, when unneeded

namespace
{
  static int g_useAttackSectors = 1;
};

namespace NWorld
{
  void PushAttackState( PFHFSM* fsm, PFBaseMovingUnit* owner, PFBaseUnit* target, bool strongTarget, bool scream, bool ignoreChaseRange /*= false*/ )
  {
    NI_VERIFY( IsValid( owner ) && IsValid( target ) && fsm, "invalid target to attack", return );

    if ( target->IsVulnerable() && ( target->GetFaction() != owner->GetFaction() ) )
    {
      fsm->PushState( new PFBaseUnitAttackState( owner->GetWorld(), owner, target, strongTarget, ignoreChaseRange ) );
      if ( scream )
      {
        owner->DoScream( target, ScreamTarget::ScreamAlert );
      }
    }
  }

  void EnqueueAttackState( PFBaseMovingUnit* owner, PFBaseUnit* target, bool strongTarget, bool scream, bool ignoreChaseRange /*= false*/ )
  {
    NI_VERIFY( IsValid( owner ) && IsValid( target ), "invalid target to attack", return );

    if ( target->IsVulnerable() && ( target->GetFaction() != owner->GetFaction() ) )
    {
      owner->EnqueueState( new PFBaseUnitAttackState( owner->GetWorld(), owner, target, strongTarget, ignoreChaseRange ), true );
      if ( scream )
      {
        owner->DoScream( target, ScreamTarget::ScreamAlert );
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Internal states
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFBaseUnitCombatState: public PFBaseUnitState
  {
    WORLD_OBJECT_METHODS(0xF5CC386, PFBaseUnitCombatState)

  public:
    PFBaseUnitCombatState(CPtr<PFWorld> const& pWorld, CPtr<PFBaseUnit> const& pOwner, bool ignoreVisibility = false, bool _allowAllies = false)
      : PFBaseUnitState(pOwner)
      , pWorld(pWorld)
      , ignoreVisibility(ignoreVisibility)
      , allowAllies(_allowAllies)
    {
      NI_ASSERT( IsUnitValid(pOwner) && pOwner->GetCurrentTarget(), "Owner or current target missed!" );
    }
  protected:
    virtual bool OnStep(float dt);
    virtual void OnEnter();
    virtual void OnLeave();
    PFBaseUnitCombatState() {}
  private:
    ZDATA_(PFBaseUnitState)
		CPtr<PFWorld>    pWorld;
    bool ignoreVisibility;
    bool allowAllies;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseUnitState*)this); f.Add(2,&pWorld); f.Add(3,&ignoreVisibility); f.Add(4,&allowAllies); return 0; }
  };

  void PFBaseUnitCombatState::OnEnter()
  {
    if( IsValid( pOwner ) )
      pOwner->OnStartedFighting();
  }

  void PFBaseUnitCombatState::OnLeave()
  {
    if( IsValid( pOwner ) )
      pOwner->OnFinishedFighting();
  }
  
  bool PFBaseUnitCombatState::OnStep( float /*dt*/ )
  {
    if( !IsUnitValid( pOwner ) )
    {
      return true;
    }

    CPtr<PFBaseUnit> pTarget = pOwner->GetCurrentTarget();
    if ( !pOwner->CanAttackTarget( pTarget ) || ( !allowAllies && pOwner->GetFaction() == pTarget->GetFaction() ) )
    {
      return true;
    }

    if ( !pOwner->IsTargetInAttackRange( pTarget, true ) )
    {
      return true;
    }

    if( !ignoreVisibility )
    {
      bool visibleTarget = pOwner->IsRequireDirectSightToAttack() ? pOwner->CanSee( *pTarget.GetPtr() ) : pTarget->IsVisibleForFaction( pOwner->GetFaction() );
      if (!visibleTarget)
      {
        return true;
      }
    }

    return ( pOwner->IsReadyToAttack() && !pOwner->DoAttack( allowAllies ) );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFBaseUnitAlertMoveState : public MoveUnitStateFSM
  {
    WORLD_OBJECT_METHODS(0xF5CC387, PFBaseUnitAlertMoveState)

  public:
    PFBaseUnitAlertMoveState( const CPtr<PFWorld>& pWorld, const CPtr<PFBaseMovingUnit>& pOwner, const CVec2& target, float _range = EPS_VALUE );
  protected:
    virtual bool OnStep(float dt);
    virtual void OnLeave() { pOwner->Stacked( false ); }
    PFBaseUnitAlertMoveState() {}
  private:
    ZDATA_(MoveUnitStateFSM);
    CVec2         vTarget;
    CPtr<PFWorld> pWorld;
    float         range;
    bool          inAttackState;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(MoveUnitStateFSM*)this); f.Add(2,&vTarget); f.Add(3,&pWorld); f.Add(4,&range); f.Add(5,&inAttackState); return 0; }
  };

  PFBaseUnitAlertMoveState::PFBaseUnitAlertMoveState( const CPtr<PFWorld>& pWorld, const CPtr<PFBaseMovingUnit>& pOwner, const CVec2& target, float _range /* = EPS_VALUE */ )
    : MoveUnitStateFSM( pOwner )
    , pWorld( pWorld )
    , vTarget( target )
    , range( Max(_range, 1.0f) )
    , inAttackState(false)
  {
  }
  
  bool PFBaseUnitAlertMoveState::OnStep(float dt)
  {
    // invalid state
    if( !IsUnitValid( pOwner ) || pOwner->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) )
    {
      return true;
    }

    FSMStep( dt );

    if(inAttackState && NULL == GetCurrentState()) return true;

    if ( NULL == GetCurrentState() )
    {
      PFBaseUnit* pTarget = 0;
      if ( !pOwner->CheckFlag( NDb::UNITFLAG_INVISIBLE ) )
      {
        pTarget = pOwner->FindTarget( pOwner->GetTargetingRange() );
      }

      if( pTarget )
      {
        PushState( new PFBaseUnitAttackState( pWorld, pOwner, pTarget, false ) );
        if(pOwner->IsTrueHero()) inAttackState = true;
      }
      else
      {
        if ( !pOwner->IsMoving() )
        {
          if ( pOwner->IsPositionInRange( vTarget, range ) )
          {
            return true; // we reached target point
          }
          
          pOwner->MoveTo( vTarget );
        }
      }
    }

    if( !pOwner->IsInCombat() && !pOwner->IsMoving() && !pOwner->IsPositionInRange(vTarget, range))
      pOwner->Stacked();
    else
      pOwner->Stacked( false );

    return false;
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Public states
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFBaseUnitMoveToState::PFBaseUnitMoveToState( PFBaseMovingUnit* _pUnit, const CVec2& _target, const float _range, bool _requireLOS )
    : PFBaseMovingUnitState( _pUnit )
    , target( _target )
    , range( _range > 0.f ? _range : 1.0f )
    , initiatedMove( false )
    , requireLineOfSight( _requireLOS )
  {}

  bool PFBaseUnitMoveToState::OnStep(float dt)
  {
    if ( !IsUnitValid( pOwner ) )
    {
      return true;
    }

    if ( pOwner->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) )
    {
      if ( pOwner->CheckFlag( NDb::UNITFLAG_CANTURNWHILEFORBIDMOVE ) )
      {
        pOwner->SetMoveDirection( target );
        if ( pOwner->ClientObject() )
        {
          pOwner->ClientObject()->LookTo( target );
        }
      }
      return true;
    }

    bool shouldMoveToSee = requireLineOfSight && !pOwner->CanSee( target );

		if ( pOwner->IsPositionInRange( target, range ) && !shouldMoveToSee )
    {
      return true;
    }
        
    if ( !initiatedMove || ( !pOwner->IsMoving() && !pOwner->IsMounted() ) )
    {
      // Move to the specific range from the target
      if ( !pOwner->MoveTo( target, requireLineOfSight ? pOwner->GetObjectSize() : range ) )
			{
				if ( !initiatedMove )
				{
          pOwner->EventHappened( PFBaseUnitEvent( NDb::BASEUNITEVENT_MOVE ) );
					NGameX::PFClientBaseMovingUnit* pClient = pOwner->ClientObject();
					if ( IsValid( pClient ) )
          {
            pClient->OnMoveFailed( target );
          }
				}
        return true;
			}

      initiatedMove = true;
    }

    return false;
  }

  void PFBaseUnitMoveToState::OnEnter()
  {
    TempDebugTrace("PFBaseUnitMoveToState::OnEnter()");
    PFBaseMovingUnitState::OnEnter();
  }

  void PFBaseUnitMoveToState::OnLeave()
  {
    TempDebugTrace("PFBaseUnitMoveToState::OnLeave()");
    if( IsValid( pOwner ) && pOwner->IsMoving() && !pOwner->IsMovingSpecial() && !pOwner->IsMounted() /*&& initiatedMove*/ )
    {
      pOwner->Stop();
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  PFBaseUnitMoveToBuildingState::PFBaseUnitMoveToBuildingState(PFBaseMovingUnit * pUnit, PFBaseUnit * _targetBuilding, IPointChecking * _pointChecking, bool _requireLineOfSight)
    : PFBaseMovingUnitState(pUnit)
    , targetBuilding(_targetBuilding)
    , initiatedMove(false)
    , pointChecking(_pointChecking)
    , requireLineOfSight(_requireLineOfSight)
    , needStopOnLeave( true )
  {}


  //its very similar to "move to state" may be combine it?.
  bool PFBaseUnitMoveToBuildingState::OnStep(float dt)
  {
    if( !IsUnitValid( pOwner ) || pOwner->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) || !IsValid( pointChecking ) || pOwner->IsHoldingPosition() )
    {
      return true;
    }

    TileMap * tileMap = pOwner->GetWorld()->GetTileMap();
    NI_VERIFY(IsValid(tileMap),"no tile map?", return true);

    if ( pointChecking->IsGoodTile( tileMap->GetTile( pOwner->GetPosition().AsVec2D() ) ) )
    {
      if ( requireLineOfSight && !pOwner->CanSee( *targetBuilding.GetPtr() ) )
      {
        return !pOwner->MoveTo( targetBuilding, pOwner->GetAttackRange() * 0.7f );
      }
      return true;
    }

    if ( !initiatedMove || ( !pOwner->IsMoving() && !pOwner->IsMounted() ) )
    {
      if ( !pOwner->MoveTo( targetBuilding, pOwner->GetAttackRange() * 0.7f ) )
      {
        if ( !initiatedMove )
        {
          pOwner->EventHappened( PFBaseUnitEvent( NDb::BASEUNITEVENT_MOVE ) );
          if ( NGameX::PFClientBaseMovingUnit* pClient = pOwner->ClientObject() )
          {
            pClient->OnMoveFailed( targetBuilding->GetPosition().AsVec2D() );
          }
        }
      }
      initiatedMove = true;
    }

    return false;
  }

  void PFBaseUnitMoveToBuildingState::OnLeave()
  {
    if( IsValid( pOwner ) && pOwner->IsMoving() && !pOwner->IsMovingSpecial() && !pOwner->IsMounted() && initiatedMove && needStopOnLeave )
    {
      pOwner->Stop();
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFBaseUnitPathMovingState::PFBaseUnitPathMovingState( CPtr<PFBaseMovingUnit> const& pUnit, vector<CVec2> const & _wayPoints, const float _range )
    : PFBaseMovingUnitState(pUnit)
    , wayPoints(_wayPoints)
    , range(_range)
    , isFirstMove(true)
		, currentPoint(VNULL2)
  {
    NI_ASSERT(!wayPoints.empty(), "way points cannot be empty");
  }

  bool PFBaseUnitPathMovingState::OnStep( float dt )
  {
    if( !IsUnitValid( pOwner ) || pOwner->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) )
    {
      return true;
    }

    if ( pOwner->IsPositionInRange( currentPoint, range ) || isFirstMove )
    {
      currentPoint = GetNextWaypoint();
      pOwner->MoveTo( currentPoint );

      //TODO: SimonK. this is stupid but how else can i start for the first time?
      isFirstMove = false;
    }

    //this restarts the movement. after teleport or such
    if ( !pOwner->IsMoving() )
    {
      pOwner->MoveTo( currentPoint );
    }
    

    //means that we reached the final point
    if ( pOwner->IsPositionInRange( currentPoint, range ) && ( currentPoint == wayPoints[wayPoints.size()-1] ) )
    {
      pOwner->Stop();
      return true;
    }

    return false;
  }

  const CVec2& PFBaseUnitPathMovingState::GetNextWaypoint() const
  {
    NI_VERIFY( !wayPoints.empty(), "Need to check waipoints exist before call GetNearestWaypoint!", return pOwner->GetPosition().AsVec2D() );

    const CVec2& vCurrentPosition = pOwner->GetPosition().AsVec2D();
    const float fWayPointRadius2 = fabs2(range);

    float fMinDistance = -1;
    vector<CVec2>::const_iterator iNearestTarget = wayPoints.begin();

    for ( vector<CVec2>::const_iterator iTarget = wayPoints.begin(), iEnd = wayPoints.end(); iTarget != iEnd; ++iTarget )
    {
      float distance2 = fabs2( *iTarget - vCurrentPosition );
      if ( fMinDistance < 0 || fMinDistance > distance2 )
      {
        fMinDistance = distance2;
        iNearestTarget = iTarget;
      }
    }

    vector<CVec2>::const_iterator iNextTarget = iNearestTarget + 1;
    while ( iNextTarget != wayPoints.end() && fMinDistance < fWayPointRadius2 )
    {
      fMinDistance = fabs2( *iNextTarget - vCurrentPosition );
      if ( fMinDistance >= fWayPointRadius2 )
        break;

      iNearestTarget = iNextTarget;
      iNextTarget++;
    }

    if ( iNextTarget == wayPoints.end() )
      return *iNearestTarget; // go to the last waypoint

    const CVec2 vCurrentWayPointPath = *iNearestTarget - vCurrentPosition;
    if ( fabs2(vCurrentWayPointPath) < fWayPointRadius2 )
      return *iNextTarget;

    const CVec2 vNextRouteSection = *iNextTarget - *iNearestTarget;
    if ( vNextRouteSection * vCurrentWayPointPath >= 0 )
      return *iNearestTarget;
    else
      return *iNextTarget;

  }

  void PFBaseUnitPathMovingState::OnLeave()
  {
    if( IsValid( pOwner ) && pOwner->IsMoving() && !pOwner->IsMovingSpecial() && !pOwner->IsMounted() )
    {
      pOwner->Stop();
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFBaseUnitChaseState::PFBaseUnitChaseState(PFBaseMovingUnit * pOwner, bool _requireLineOfSight, float _attackRange, float _chaseRange, PFBaseUnit * target, bool _strongTarget, bool ignoreVisibility /* = false*/, bool useAttackRange /* = false*/)
    : PFBaseMovingUnitState(pOwner)
    , attackRange(_attackRange)
    , chaseRange(_chaseRange)
    , targetUnit(target)
    , lastPos( VNULL2 )
    , requireLineOfSight(_requireLineOfSight)
    , strongTarget( _strongTarget )
    , attackSector(-1)
    , ignoreVisibility(ignoreVisibility)
    , useAttackRange(useAttackRange)
  {
    NI_VERIFY(IsValid(targetUnit), "Invalid target", return);
    //NI_ASSERT( ignoreVisibility || targetUnit->IsVisibleForFaction( pOwner->GetFaction() ) || chaseRange == 1e10f && targetUnit->IsVisibleForEnemy(), "Can't chase invisible units" );
    lastPos = targetUnit->GetPosition().AsVec2D();
    halfTargetSize = targetUnit->GetObjectSize() * 0.5f;
  }


  bool PFBaseUnitChaseState::OnStep( float /*dt*/ )
  {
    // State was not properly initialized
    if( !IsUnitValid( pOwner ) || pOwner->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) || (!strongTarget && pOwner->IsHoldingPosition()) )
    {
      return true;
    }

    // We do not cancel the chase state if the target is invalid but lastPos is set. 
    // That means, that the target was valid before and now obviously dead. In that 
    // case we have to resume moving to its last position, stored in lastPos.
    if ( !IsUnitValid( targetUnit ) && lastPos == VNULL2 || !strongTarget && targetUnit != pOwner->GetCurrentTarget() )
    {
      return true;
    }

    if( pOwner->GetBehaviour() && !pOwner->GetBehaviour()->CanSelectTarget( targetUnit ) )
      return true;
 
    // Try to move closer to the unit if needed
    if ( IsUnitValid( targetUnit ) && ( ignoreVisibility || targetUnit->IsVisibleForFaction( pOwner->GetFaction() ) ) )
    {
      lastPos = targetUnit->GetPosition().AsVec2D();

      bool shouldMoveToSee = ignoreVisibility ? false : ( requireLineOfSight && !pOwner->CanSee( *targetUnit.GetPtr() ) );
      bool shouldMoveToReach;

      // NUM_TASK
      if (useAttackRange)
        shouldMoveToReach = !pOwner->IsTargetInAttackRange( targetUnit, true );
      else
        shouldMoveToReach = !pOwner->IsTargetInRange( targetUnit, attackRange );

      if ( shouldMoveToSee || shouldMoveToReach )
      {
        if ( ( chaseRange < EPS_VALUE ) || pOwner->IsTargetInRange( targetUnit, chaseRange ) )
        {
          const float halfObjectSize = pOwner->GetObjectSize() * 0.5f;
          const float distanceToApproach = halfTargetSize + ( requireLineOfSight ? halfObjectSize : attackRange );

          if ( g_useAttackSectors && !pOwner->IsTrueHero() )
          {
            CVec2 pos = targetUnit->GetPosition().AsVec2D();

            if (PFBaseMovingUnit * targetBaseMovingUnit = dynamic_cast<PFBaseMovingUnit *>(targetUnit.GetPtr()))
            {
              targetUnit->ReleaseAttackSector(attackSector);
              attackSector = targetUnit->OccupyAttackSector(pOwner);
              pos = targetUnit->GetPosition().AsVec2D() + targetUnit->GetAttackSectorOffset(pOwner, attackSector);
            }

            pOwner->MoveTo( pos, distanceToApproach );
          }
          else
          {
            pOwner->MoveTo( targetUnit, distanceToApproach );
          }

          return false;
        }
      }
    }
    else // We do not see the target or it is dead, so we just continue approach last target position to attackRange distance
    {
      
      float range = pOwner->IsTrueHero() ? 0.0f : attackRange;
      
      if ( !pOwner->IsPositionInRange( lastPos, range ) )
      {
        pOwner->MoveTo( lastPos, range );
        return !pOwner->IsMoving();
      }
    }
    
    return true;
  }

  void PFBaseUnitChaseState::OnLeave()
  {
    if( IsValid( pOwner ) && pOwner->IsMoving() && !pOwner->IsMovingSpecial() )
    {
      pOwner->Stop();
    }
  }

  void PFBaseUnitChaseState::OnDestroyContents()
  {
    if (g_useAttackSectors)
    {
      if (IsUnitValid( targetUnit ))
        targetUnit->ReleaseAttackSector(attackSector);
    }

    PFBaseMovingUnitState::OnDestroyContents();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFBaseUnitCombatMoveState::PFBaseUnitCombatMoveState( const CPtr<PFWorld>& pWorld, const CPtr<PFBaseMovingUnit>& pOwner, const CVec2& target, float range /* = EPS_VALUE */ )
    : MoveUnitStateFSM( pOwner )
  {
    if( IsValid( pOwner ) )
    {
      PushState( new PFBaseUnitAlertMoveState( pWorld, pOwner, target, range ) );
    }
  }

  bool PFBaseUnitCombatMoveState::OnStep(float dt)
  {
    if ( !IsUnitValid( pOwner ) )
      return true;

    FSMStep(dt);

    return (NULL == GetCurrentState());
  }

  void PFBaseUnitCombatMoveState::OnLeave()
  {
		if( IsValid(pOwner) && pOwner->IsMoving() && !pOwner->IsMovingSpecial() && !pOwner->IsMounted() )
    {
      pOwner->Stop();
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFBaseUnitAttackState::PFBaseUnitAttackState(CPtr<PFWorld> const& pWorld, CPtr<PFBaseMovingUnit> const& pOwner, const CPtr<PFBaseUnit>& pTarget, 
		                                           bool strongTarget /*= true*/, bool ignoreChaseRange /*= false*/, bool ignoreVisibility /*= false*/, bool _allowAllies /*= false*/, bool _allowChase /*= true */ )
    : MoveUnitStateFSM(pOwner)
    , pWorld(pWorld)
    , pTarget(pTarget)
    , strongTarget(strongTarget)
		, ignoreChaseRange(ignoreChaseRange)
    , statePassedThrough(false)
    , ignoreVisibility(ignoreVisibility)
    , allowAllies(_allowAllies)
    , allowChase(_allowChase)
  {
  }

  void PFBaseUnitAttackState::OnEnter()
  {
    if ( IsUnitValid( pOwner ) && IsTargetValid( pTarget ) )
    {
      pOwner->OnEnterCombat();
      pOwner->AssignTarget( pTarget, strongTarget);
    }
  }

  void PFBaseUnitAttackState::OnLeave()
  {
    if ( IsUnitValid( pOwner ) )
    {
      pOwner->DropTarget();
      pOwner->OnLeaveCombat();
    }
  }

  bool PFBaseUnitAttackState::OnStep(float dt)
  {
    if( !IsUnitValid( pOwner ) )
    {
      return true;
    }

    PFBaseUnit* pTarget = pOwner->GetCurrentTarget();
    NI_VERIFY( pOwner != pTarget, "Cannot attack self!", return true );
    
    bool finished = false;
   
    if ( !GetCurrentState() )
    {
      // ѕровер€ем здесь в т.ч. на союзников в качестве цели, потому что стейт может пихатьс€ через EnqueueState (например аппликатор таунта герою).
      // Ќадо быть готовым к тому, что к следующему степу цель может оказатьс€ союзной,
      // а мы не хотим атаковать союзника (только если не указываем €вно, например, в аппликаторе AttackTarget).
      if ( !pOwner->CanAttackTarget( pTarget ) || ( !allowAllies && pOwner->GetFaction() == pTarget->GetFaction() ) )
      {
        pOwner->Stop( false );
        if ( pOwner->ClientObject() )
        {
          if ( NGameX::PFClientCreature* client = dynamic_cast<NGameX::PFClientCreature*>(pOwner->ClientObject()) )
          {
            if ( !client->IsInAttackNode() )
            {
              client->OnStop();
            }
          }
        }
        return true;
      }

      bool canMove = !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDMOVE) && !pOwner->IsHoldingPosition();
      bool requireLineOfSight = pOwner->IsRequireDirectSightToAttack();
      // Drop target, if owner can not move and target is too far away, or is not whithin required los
      // TODO: use IsTargetInAttackRange(pTarget, true) only for heroes?
      if ( !canMove && ( !pOwner->IsTargetInAttackRange( pTarget, true ) || requireLineOfSight && !pOwner->CanSee( *pTarget ) ) )
      {
        return true;
      }

		  const float chaseRange = ignoreChaseRange ? 1e10f : pOwner->GetChaseRange();

      // The long and ugly if-else mess below should be reorganized with proper respect to
      // canCase and allowChase checks. Though it should work as is, just ugly and unclear.

      //target is valid and is located within chase range
      const bool canSelectTarget = pOwner->GetBehaviour() ? pOwner->GetBehaviour()->CanSelectTarget( pTarget ) : true;
      bool canChase = IsTargetValid( pTarget ) && canSelectTarget && ( ignoreChaseRange || ( chaseRange < EPS_VALUE ) || pOwner->IsTargetInRange( pTarget, chaseRange ) );
      if( canChase )
      {
        bool pushCombatState = true;
        if ( canMove )
        {
          PFBaseUnit* target = strongTarget ? pTarget : pOwner->GetCurrentTarget();

          if ( PFBuilding* building = dynamic_cast<PFBuilding*>( target ) )
          {
            PushState( new PFBaseUnitCombatState( pWorld, CPtr<PFBaseUnit>( pOwner ), ignoreVisibility, allowAllies ) );
            pushCombatState = false; // Already pushed here

            const int tileAttackRange = pOwner->GetWorld()->GetTileMap()->GetLenghtInTiles(pOwner->GetAttackRange());
            IPointChecking* const pointChecking = new RegionPointChecker(pWorld, building->GetOccupiedTiles(), tileAttackRange);

            // NOTE: специальный случай
            const bool combatMove =
              pOwner->GetUnitType() == NDb::UNITTYPE_SIEGECREEP ||
              pOwner->GetUnitType() == NDb::UNITTYPE_FACTIONCHAMPION;

            if (combatMove)
              PushState( new PFBaseUnitCombatMoveToBuildingState( pWorld, pOwner, building, pointChecking, requireLineOfSight ) );
            else
              PushState( new PFBaseUnitMoveToBuildingState( pOwner, building, pointChecking, requireLineOfSight ) );
          }
          else if (allowChase)
          {
            // This check prevents chasing invisible units, but allows it when chase range is ignored and the unit is hidden only by the fog of war
            // TODO: is this condition correct?
            if ( ignoreVisibility || target->IsVisibleForFaction( pOwner->GetFaction() ) || ignoreChaseRange && target->IsVisibleForEnemy( pOwner->GetFaction() ) )
            {
              if (!pOwner->IsTargetInAttackRange(target, true))
              {
                if (const PFBaseAttackData *baseAttackData = pOwner->GetAttackAbility())
                {
                  if (const NDb::Ability *dbDesc = baseAttackData->GetDBDesc())
                  {
                    // Check for chasing permission on the ability's formula
                    canChase = dbDesc->allowChase(pOwner, target, baseAttackData, true);
                  }
                }
                if (canChase)
                {
                  // NUM_TASK
                  const bool useAttackRange = pOwner->IsTrueHero();

                  PushState( new PFBaseUnitCombatState( pWorld, CPtr<PFBaseUnit>( pOwner ), ignoreVisibility, allowAllies ) );
                  PushState( new PFBaseUnitChaseState( pOwner, requireLineOfSight, pOwner->GetAttackRange(), chaseRange, target, strongTarget, ignoreVisibility, useAttackRange ) );
                }
                // Either already pushed if canChase or should not be pushed
                pushCombatState = false;
              }
            }
            else
            {
              canChase = false;
            }
          }
          else
          {
            canChase = false;
          }
        }

        if (pushCombatState)
        {
          PushState( new PFBaseUnitCombatState( pWorld, CPtr<PFBaseUnit>( pOwner ), ignoreVisibility, allowAllies ) );
        }
      }

      finished = !canChase;
    }

    const IPFState* pPrevious = GetCurrentState();
    
    FSMStep( dt );

    if( pPrevious != GetCurrentState() )
    {
      FSMStep( 0.0f );
    }

    return finished;
  }

  bool PFBaseUnitAttackState::IsBlocking() const
  {
    return !pOwner->IsAttackFinished();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFBaseUnitCombatMoveToBuildingState::PFBaseUnitCombatMoveToBuildingState(const CPtr<PFWorld>& pWorld, PFBaseMovingUnit* pUnit, PFBaseUnit* pTarget, IPointChecking* pPointChecking, bool requireLineOfSight)
    : MoveUnitStateFSM(pUnit)
    , pWorld(pWorld)
    , pTarget(pTarget)
    , targetSearchInterval(0.2f)
    , targetSearchTimer(0.0f)
  {
    if (IsValid(pOwner))
    {
      PushState(new PFBaseUnitMoveToBuildingState(pUnit, pTarget, pPointChecking, requireLineOfSight));
    }
  }

  bool PFBaseUnitCombatMoveToBuildingState::OnStep(float dt)
  {
    if (!IsUnitValid(pOwner))
      return true;
    if (!IsUnitValid(pTarget))
      return true;

    if (pTarget->IsDead())
      return true;

    FSMStep(dt);

    if (IPFState* state = GetCurrentState())
    {
      if (state->GetTypeId() == PFBaseUnitMoveToBuildingState::typeId)
      {
        if (targetSearchTimer > 0.0f)
        {
          targetSearchTimer -= dt;
          return false;
        }
        else
        {
          targetSearchTimer = targetSearchInterval;
        }

        PFBaseUnit* target = 0;

        if (!pOwner->CheckFlag(NDb::UNITFLAG_INVISIBLE))
        {
          target = pOwner->FindTarget( pOwner->GetTargetingRange() );
        }

        if (!!target && target != pTarget)
        {
          PushState(new PFBaseUnitAttackState(pWorld, pOwner, target, false, false, false, false, false));
        }
      }

      return false;
    }

    return true;
  }

  void PFBaseUnitCombatMoveToBuildingState::OnLeave()
  {
    if (IsValid(pOwner) && pOwner->IsMoving() && !pOwner->IsMovingSpecial() && !pOwner->IsMounted())
    {
      pOwner->Stop();
    }
  }

} // namespace NWorld

REGISTER_DEV_VAR("use_attack_sectors",   g_useAttackSectors,   STORAGE_NONE);

REGISTER_WORLD_OBJECT_NM(PFBaseUnitMoveToState,     NWorld)
REGISTER_WORLD_OBJECT_NM(PFBaseUnitChaseState,      NWorld)
REGISTER_WORLD_OBJECT_NM(PFBaseUnitAttackState,     NWorld)
REGISTER_WORLD_OBJECT_NM(PFBaseUnitCombatMoveState, NWorld)
REGISTER_WORLD_OBJECT_NM(PFBaseUnitCombatState,     NWorld)
REGISTER_WORLD_OBJECT_NM(PFBaseUnitAlertMoveState,  NWorld)
REGISTER_WORLD_OBJECT_NM(PFBaseUnitPathMovingState,  NWorld)
REGISTER_WORLD_OBJECT_NM(PFBaseUnitMoveToBuildingState,  NWorld)
REGISTER_WORLD_OBJECT_NM(PFBaseUnitCombatMoveToBuildingState, NWorld)
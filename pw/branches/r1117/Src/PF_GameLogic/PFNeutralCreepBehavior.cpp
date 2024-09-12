#include "stdafx.h"

#include "PFNeutralCreepBehavior.h"
#include "PFCommonCreep.h"
#include "TileMap.h"
#include "PFClientBaseMovingUnit.h"
#include "PFAIContainer.h"

#include "Scripts/FuncCallMacroses.h"

#ifdef DEBUG_NEUTRALS_STATES
#define DEBUG_PRINT(a) DebugTrace("%s(%d):: %s", GetObjectTypeName(), GetObjectId(), (a));
#else
#define DEBUG_PRINT(a)
#endif

namespace
{
  float   g_fCreepWayPointRadius  = 7.5f;
}

namespace NWorld
{

  const float TIME_FOR_HEALING_DEFAULT = 1.f;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct Screamer : public NonCopyable
  {
    Screamer( const CPtr<PFBaseUnit>& pSender, const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st )
      : pSender( pSender ), pTarget( pTarget ), st( st ) {}

    void operator() ( CPtr<PFNeutralCreep> const& pUnit )
    {
      if ( ( pSender != pUnit )
        && IsUnitValid( pUnit )
        && pUnit->IsAttachedToSpawner() 
        && pUnit->GetBehaviour() && pUnit->GetBehaviour()->GetTypeId() == PFNeutralCreepBehaviour::typeId )
      {
        pUnit->OnScream( pTarget, st );
      }
    }

    CPtr<PFBaseUnit> pSender;
    CPtr<PFBaseUnit> pTarget;
    const ScreamTarget::ScreamType st;
  };
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFNeutralCreepEvadeState::PFNeutralCreepEvadeState(const CPtr<PFWorld>& pWorld, const CPtr<PFBaseMovingUnit>& pOwner, const Placement& _initialPlacement)
    : MoveUnitStateFSM(pOwner)
    , pWorld(pWorld)
    , initialPlacement(_initialPlacement)
    , stateTimer(0.0f)
    , stateTimeOut(0.0f)
    , healTimer(0.0f)
    , healPercent(0.0f)
    , timeForHealing(TIME_FOR_HEALING_DEFAULT)
  {

    if( PFNeutralCreep const * pCreep = dynamic_cast<PFNeutralCreep const *>(pOwner.GetPtr()) )
    {
      NI_VERIFY( pWorld && IsUnitValid(pOwner) , "Invalid parameters", return; );
      if (PFNeutralCreepSpawner const * pSpawner = pCreep->GetSpawner())
      {
        if (NDb::AdvMapNeutralCreepSpawner const * pSpawnerDesc = pSpawner->GetDBDesc())
        {
          stateTimeOut = pSpawnerDesc->evadeParams.evadeTimeout;
          healPercent  = pSpawnerDesc->evadeParams.restoreHealthPercent;
        }
      }
    }
    else if(  PFCommonCreep const * pCreep = dynamic_cast<PFCommonCreep const *>(pOwner.GetPtr()) )
    {
      NI_VERIFY( pWorld && IsUnitValid(pOwner) , "Invalid parameters", return; );
      if (PFCreepSpawner const * pSpawner = pCreep->GetSpawner())
      {
        if (NDb::AdvMapCreepSpawner const * pSpawnerDesc = pSpawner->GetDBDesc())
        {
          stateTimeOut = pSpawnerDesc->evadeParams.evadeTimeout;
          healPercent  = pSpawnerDesc->evadeParams.restoreHealthPercent;
        }
      }
    }
    else NI_VERIFY( true, "Invalid parameters", return; );

    NI_VERIFY( pWorld && IsUnitValid(pOwner) , "Invalid parameters", return; );

    if (!pOwner->IsPositionInRange(initialPlacement.pos.AsVec2D(), pOwner->GetTileMap()->GetTileSize() * 2.0f))
    {
      if (!pOwner->CheckFlag(NDb::UNITFLAG_FORBIDMOVE) && !pOwner->IsMoving())
      {
        DEBUG_PRINT("PushState PFBaseUnitCombatMoveState");
        PushState(new PFBaseUnitCombatMoveState( GetWorld(), pOwner, initialPlacement.pos.AsVec2D(), pOwner->GetTileMap()->GetTileSize() * 2.0f ));
        pOwner->SetNeedRotate(true);
      }
    }
    
    int stepLength = pWorld->GetStepLength();
    timeForHealing = round(stepLength * (TIME_FOR_HEALING_DEFAULT / stepLength));
  }

  void PFNeutralCreepEvadeState::OnEnter()
  {
    if ( IsUnitValid(pOwner) )
      pOwner->OnEvading(true);
  }

  void PFNeutralCreepEvadeState::OnLeave()
  {
    if ( IsUnitValid(pOwner) )
      pOwner->OnEvading(false);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFNeutralCreepEvadeState::OnStep(float dt)
  {
    if ( !IsUnitValid(pOwner) )
      return true;

    FSMStep(dt);

    if (GetCurrentState() == 0)
    {
      if (!pOwner->IsPositionInRange(initialPlacement.pos.AsVec2D(), pOwner->GetTileMap()->GetTileSize() * 2.0f))
      {
        if (!pOwner->CheckFlag(NDb::UNITFLAG_FORBIDMOVE)&& !pOwner->IsMoving())
        { 
          DEBUG_PRINT("OnStep PushState PFBaseUnitCombatMoveState");
          PushState(new PFBaseUnitCombatMoveState( GetWorld(), pOwner, initialPlacement.pos.AsVec2D(), pOwner->GetTileMap()->GetTileSize() * 2.0f ));
          pOwner->SetNeedRotate(true);
        }
      }
    }

    stateTimer += dt;
    healTimer += dt;

    if (healTimer >= timeForHealing)
    {
      pOwner->OnHeal(pOwner.GetPtr(), pOwner->GetMaxHealth() * healPercent);
      pOwner->OnHealEnergy(pOwner.GetPtr(), pOwner->GetMaxEnergy() * healPercent);
      healTimer = 0.0f;
    }

    if (stateTimer >= stateTimeOut || pOwner->IsInCombat() 
      || (pOwner->GetHealth() == pOwner->GetMaxHealth() && pOwner->GetEnergy() == pOwner->GetMaxEnergy()
      && pOwner->IsPositionInRange(initialPlacement.pos.AsVec2D(), pOwner->GetTileMap()->GetTileSize() * 2.0f)))
    {
      DEBUG_PRINT("OnStep cancel self");
      return true;
    }

    return false;
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFNeutralCreepWaitState::PFNeutralCreepWaitState(const CPtr<PFWorld>& pWorld, const CPtr<PFBaseMovingUnit>& pOwner, const Placement& _initialPlacement, float _stateTimeOut)
    : MoveUnitStateFSM(pOwner)
    , pWorld(pWorld)
    , targetingRange(0.0f)
    , initialPlacement(_initialPlacement)
    , stateTimer(0.0f)
    , stateTimeOut(_stateTimeOut)
  {
    NI_VERIFY( pWorld && IsUnitValid(pOwner), "Invalid parameters", return; );
    targetingRange = pOwner->GetTargetingRange();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFNeutralCreepWaitState::OnStep(float dt)
  {
    if ( !IsUnitValid(pOwner) )
      return true;

    FSMStep(dt);

    if( GetCurrentState() == NULL )
    {
      PFBaseUnit* pTarget = NULL;

      if ( targetingRange > 0.f )
      {
        pTarget = pOwner->FindTarget( targetingRange, false, 0, false );
      }

      if ( IsUnitValid( pTarget ) )
      {
        if ( !pOwner->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDSELECTTARGET ) && pOwner->HasAtackAbility() )
        {
          DEBUG_PRINT("OnStep EnqueueAttackState");
          EnqueueAttackState( pOwner, pTarget, false, true, true );
          pOwner->SetNeedRotate( true );
          return true;
        }
        else // there is a target available, but creep has target selection forbidden, so just do nothing in wait state
        {
          return false;
        }
      }
    }

    stateTimer += dt;

    if (stateTimer >= stateTimeOut)
    {
      DEBUG_PRINT("OnStep EnqueueState PFNeutralCreepEvadeState");
      pOwner->EnqueueState(new PFNeutralCreepEvadeState( GetWorld(), pOwner, initialPlacement), true);
      return true;
    }

    return false;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PFNeutralCreepBehaviour
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////
  PFNeutralCreepBehaviour::PFNeutralCreepBehaviour( PFNeutralCreep* pCreep, const Placement& _initialPlacement, const vector<CVec2>& _wayPoints )
    : PFBaseBehaviour( pCreep )
    , initialPlacement( _initialPlacement )
    , targetingRange( 0.0f )
    , useEvade( false )
    , timerMovingStacked(0.0f)
    , stacked(false)
    , unsummoned(false)
    , pNeutralCreep( pCreep )
    ,wayPoints(_wayPoints)
  {
    NI_VERIFY( IsValid( pCreep ), "invalid owner(paranoid?)", return );
    targetingRange = pCreep->GetTargetingRange();

    if (PFNeutralCreepSpawner const * pSpawner = pCreep->GetSpawner())
    {
      if (NDb::AdvMapNeutralCreepSpawner const * pSpawnerDesc = pSpawner->GetDBDesc())
      {
        useEvade = pSpawnerDesc->useEvade;

        if (useEvade)
        {
          evadeParams.SetData(pSpawnerDesc->evadeParams);
        }
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFNeutralCreepBehaviour::OnStep( float dtInSeconds )
  {
    NI_PROFILE_FUNCTION

      if (pUnit->IsDead())
        return true;  // Do nothing if dead

    if ( pUnit->IsMicroAiEnabled() )
    {
      if ( pUnit->HaveAbilityInProgress() )
      {
        return true; // Do nothing during channeling
      }
      if ( pUnit->UseAbilityWithMicroAI() )
      {
        if ( !IsValid(pLastTarget) )
        {
          pLastTarget = pUnit->GetCurrentTarget();
        }
        return true; // We cast ability on this step
      }
    }

    // Check original spawn pos
    CVec2 const& origSpawnPos = pNeutralCreep->GetPositionBySpawner();
    if ( origSpawnPos != initialPlacement.pos.AsVec2D() )
    {
      if ( pNeutralCreep->CanOccupyPosition( origSpawnPos ) )
      {
        initialPlacement.pos = CVec3( origSpawnPos, 0.0f );
      }
    }

    if (pUnit->GetCurrentState() == 0)
    {
      if ( !pUnit->GetCurrentTarget() )
      {
        if( IsValid( pLastTarget ) ) 
          pUnit->AssignTarget( pLastTarget, false );

        CPtr<PFBaseUnit> pTarget = pNeutralCreep->GetSpawner()->GetSpawnTarget( pUnit, targetingRange );

        if( IsValid( pTarget ) )
          pUnit->AssignTarget( pTarget, false );
      }
      pLastTarget = 0;

      PFBaseUnit* pTarget = NULL;

      if ( targetingRange > 0.f )
      {
        pTarget = pUnit->FindTarget( targetingRange );
      }

      if( !IsUnitValid( pTarget ) )
        pTarget = pUnit->GetCurrentTarget();

      if ( IsUnitValid( pTarget ) && pUnit->HasAtackAbility() )
      {
        DEBUG_PRINT("OnStep EnqueueAttackState");
        EnqueueAttackState( pUnit, pTarget, false, true, true );
        pUnit->SetNeedRotate( true );
        return true;
      }
      else
      {
        if ( !useEvade && !IsCreepAtSpawner( 4.0f ) && wayPoints.empty() )
        {
          if (!pUnit->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ))
          {
            DEBUG_PRINT("OnStep PushState PFBaseUnitCombatMoveState 1");
            pUnit->PushState( new PFBaseUnitCombatMoveState( GetWorld(), pUnit, initialPlacement.pos.AsVec2D(), pUnit->GetTileMap()->GetTileSize() * 4.0f ) );
            pUnit->SetNeedRotate( true );
            return true;
          }
        }
        else
        {
          pUnit->RotateIfNeeded();
        }
      }
    }

    const float movingTimerBlock = GetWorld()->GetAIWorld()->GetAIParameters().movingTimerBlock;

    if( stacked || unsummoned )
    {
      timerMovingStacked += dtInSeconds;

      if( !unsummoned && timerMovingStacked > movingTimerBlock )
      {
        pUnit->AddFlag(NDb::UNITFLAG_ISOLATED);
        if ( pUnit->ClientObject() )
          pUnit->ClientObject()->OnFakeUnsummon();
        unsummoned = true;
      }
    }
    else
    {
      if( !unsummoned )
        timerMovingStacked = 0.f;
    }

    float unsummonTime = 0.0f;
    if ( pUnit->GetDeathParams() )
      unsummonTime = pUnit->GetDeathParams()->unsummonTime;

    if( unsummoned && timerMovingStacked > movingTimerBlock + unsummonTime )
    {
      pUnit->TeleportTo( initialPlacement.pos.AsVec2D() );
      pUnit->RemoveFlag(NDb::UNITFLAG_ISOLATED);
      pUnit->DropStates();

      pNeutralCreep->Summon();

      stacked = false;

      unsummoned = false;

      // update initialPlacement if desired pos is blocked
      if ( pUnit->GetPosition().AsVec2D() != initialPlacement.pos.AsVec2D() )
        initialPlacement.pos = pUnit->GetPosition();
    }

    float walkLimit = pNeutralCreep->GetWalkLimit();

    bool evade = false;

    if( IsValid( pUnit->GetCurrentTarget()) )
    {
      if( !CanSelectTarget(pUnit->GetCurrentTarget() ) && !pUnit->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) )
        evade = true;
    }
    else
    {
      // If there is a walk limit set - do checks and send the creep back to the spawner if needed
      if (!pUnit->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) && walkLimit >= 0.0f && fabs2(walkLimit) < fabs2(pUnit->GetPosition().AsVec2D() - pNeutralCreep->GetSpawner()->GetSpawnPosition().pos.AsVec2D()))
        evade = true;
    }

    if( evade && !pUnit->IsEvading())
    {
      if (useEvade)
      {
        DEBUG_PRINT("OnStep EnqueueState PFNeutralCreepEvadeState");
        pUnit->EnqueueState(new PFNeutralCreepEvadeState( GetWorld(), pUnit, initialPlacement), true);
        return true;
      }
      else
      {
        if ( !wayPoints.empty() )
        {
          DEBUG_PRINT("OnStep PushState PFBaseUnitPathMovingState 1");
          CPtr<PFBaseMovingUnit> pMoving = GetUnit();
          pUnit->PushState( new PFBaseUnitPathMovingState(pMoving, wayPoints, g_fCreepWayPointRadius) );
          pUnit->FSMStep(0.0f);
        }
        else if ( !IsCreepAtSpawner( 2.0f ) )
        {
          DEBUG_PRINT("OnStep EnqueueState PFBaseUnitCombatMoveState 2");
          pUnit->EnqueueState( new PFBaseUnitCombatMoveState( GetWorld(), pUnit, initialPlacement.pos.AsVec2D(), pUnit->GetTileMap()->GetTileSize() * 2.0f ), true );
          pUnit->SetNeedRotate( true );
          return true;
        }
      }
    }

    {
      PFBaseUnit* pTarget = pUnit->FindTarget( pUnit->GetTargetingRange() );
      if ( IsUnitValid(pTarget) && pTarget->IsVulnerable() && pTarget->GetFaction() != pUnit->GetFaction()&& pUnit->HasAtackAbility() && !pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
      {
        if ( dynamic_cast<PFBaseUnitPathMovingState*>( pUnit->GetCurrentState() ) != 0 )
        {
          pUnit->DropStates();
          pUnit->PushState( new PFBaseUnitAttackState( pUnit->GetWorld(), pUnit, pTarget, false) );
          pUnit->DoScream( pTarget, ScreamTarget::ScreamAlert ); // scream alert!
        }
        return true;
      }
    }

    if ( pUnit->IsIdle() )
    {
      if ( useEvade && ( !IsCreepAtSpawner( 2.0f ) || pUnit->GetHealth() < pUnit->GetMaxHealth() || pUnit->GetEnergy() < pUnit->GetMaxEnergy() ) )
      {
        DEBUG_PRINT("OnStep PushState PFNeutralCreepWaitState");
        pUnit->PushState(new PFNeutralCreepWaitState( GetWorld(), pUnit, initialPlacement, evadeParams.waitForNextTargetTime));
      }
      else if ( !wayPoints.empty() && !pUnit->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDMOVE ) )
      {
        DEBUG_PRINT("OnStep PushState PFBaseUnitPathMovingState 2");
        CPtr<PFBaseMovingUnit> pMoving = GetUnit();
        pUnit->PushState( new PFBaseUnitPathMovingState(pMoving, wayPoints, g_fCreepWayPointRadius) );
        pUnit->FSMStep(0.0f);
      }
    }
    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFNeutralCreepBehaviour::OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget )
  {
    NI_VERIFY( IsUnitValid( pTarget ) && pTarget->IsVulnerable(), "Invalid Target!", return; );

    if ( pUnit->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDATTACK ) )
    {
      return; // Attack forbid flag not empty!
    }
    if ( pUnit->HaveAbilityInProgress() )
    {
      return;
    }
    if ( !pUnit->HasAtackAbility() )
      return;

    DEBUG_PRINT("OnTarget PushAttackState");
    pUnit->DropStates();
    PushAttackState( pUnit, pUnit, pTarget, bStrongTarget, false, true );
    pUnit->SetNeedRotate( true );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFNeutralCreepBehaviour::OnDamage( const PFBaseUnitDamageDesc& desc )
  {
    if ( useEvade)
    {
      // Don't counterattack here, as it currently happens in PFBaseBehaviour.
      // Neutral creep will autotarget using weights and then attack if needed
      if (!pUnit->IsDead() && pUnit->GetCurrentState() == 0)
      {
        DEBUG_PRINT("OnDamage PushState PFNeutralCreepWaitState");
        pUnit->PushState(new PFNeutralCreepWaitState( GetWorld(), pUnit, initialPlacement, evadeParams.waitForEvadeTime));
      }
    }
    else
    {
      if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
        return; // Attack forbid flag not empty!

      if (!pUnit->IsDead() && pUnit->GetCurrentState() == 0)
      {
        CPtr<PFBaseUnit> pSender = IsValid(desc.pSender) ? ( desc.pSender->IsMounted() ? desc.pSender->GetMountedOn() : desc.pSender ) : NULL;
        if ( IsTargetValid(pSender) && pSender->IsVisibleForFaction(pUnit->GetFaction()) && pUnit->HasAtackAbility() )
        {
          PushAttackState( pUnit, pUnit, pSender, false, !desc.dontAttackBack );
        }
      }
      else 
        PFBaseBehaviour::OnDamage( desc );
    }
  }


  bool PFNeutralCreepBehaviour::CanSelectTarget( PFBaseUnit const* pTarget, bool mustSeeTarget /*= false*/ ) const
  {
    if ( !IsValid( pTarget ) )
      return false;

    PFNeutralCreep * pNeutralCreep = static_cast<PFNeutralCreep*>( pUnit.GetPtr() );
    float walkLimit = pNeutralCreep->GetWalkLimit();
    if ( walkLimit < 0.0f )
      return true;

    PFNeutralCreepSpawner const* pSpawner = pNeutralCreep->GetSpawner();

    if ( !IsValid( pSpawner ) )
      return true;

    return fabs2( pTarget->GetPosition().AsVec2D() - pSpawner->GetSpawnPosition().pos.AsVec2D()) <= fabs2( walkLimit + pSpawner->GetMinAttackRange() );
  }

  bool PFNeutralCreepBehaviour::IsCreepAtSpawner( float distInTiles ) const
  {
    return pUnit->IsPositionInRange( initialPlacement.pos.AsVec2D(), pUnit->GetTileMap()->GetTileSize() * distInTiles );
  }

  bool PFNeutralCreepBehaviour::IsInDefaultState() const
  {
    return pUnit->IsIdle() && IsCreepAtSpawner( 4.0f );
  }

  bool PFNeutralCreepBehaviour::IsAttackedUnitAlly( const CPtr<PFBaseUnit>& pAttacked, NDb::EFaction originalAttackedFaction ) const
  {
    PFNeutralCreepSpawner const* pSpawner = GetUnit()->GetSpawner();
    if ( originalAttackedFaction == NDb::FACTION_NEUTRAL && GetUnit()->IsAttachedToSpawner() && pSpawner )
    {
      CDynamicCast<PFNeutralCreep> pAttackedNeutral(pAttacked);
      if ( pAttackedNeutral )
      {
        return pAttackedNeutral->GetSpawner() == pSpawner;
      }
    }

    return PFBaseBehaviour::IsAttackedUnitAlly( pAttacked, originalAttackedFaction );
  }

  void PFNeutralCreepBehaviour::DoScream( const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st )
  {
    Screamer screamer( pUnit.GetPtr(), pTarget, st );
    if ( GetUnit()->IsAttachedToSpawner() && GetUnit()->GetSpawner() )
      GetUnit()->GetSpawner()->ForAllCreeps( screamer );
  }

  void PFNeutralCreepBehaviour::Resume()
  {
    PFBaseBehaviour::Resume();

    if ( !GetUnit()->IsAttachedToSpawner() )
    {
      pUnit->KillUnit( 0, PFBaseUnit::UNITDIEFLAGS_UNSUMMON );
    }
  }
  void PFNeutralCreepBehaviour::GetKillerAward(CPtr<PFBaseUnit> pKiller, NaftaAward& award)
  {
    if (!GetUnit()->IsAttachedToSpawner())
      return;
    
    if (const PFNeutralCreepSpawner* const pSpawner = GetUnit()->GetSpawner())
    {
      pSpawner->AwardForCreepKill( award );

      // TODO: здесь этого быть не должно
      if(pSpawner->GetSpawnedCreepsCount() == 1)
      {
        if(PFWorld* pWorld = GetWorld())
          pWorld->NotifyCreepSpawnerCleaned( pSpawner, pKiller);
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  PFNeutralCreepBaseMoveBehaviour::PFNeutralCreepBaseMoveBehaviour( PFNeutralCreep *pCreep, float _chaseRange  )
    : PFBaseBehaviour( pCreep )
    , chaseRange( _chaseRange )
    , targetingDelay(0.f)
    , lastMovePoint(0.f,0.f)
  {

  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFNeutralCreepBaseMoveBehaviour::OnStep( float dtInSeconds )
  {
    NI_PROFILE_FUNCTION;

    if (pUnit->IsDead())
      return true;  // Do nothing if dead

    if ( pUnit->IsMicroAiEnabled() )
    {
      if ( pUnit->HaveAbilityInProgress() )
      {
        return true; // Do nothing during channeling
      }
      if ( pUnit->UseAbilityWithMicroAI() )
      {
        if ( !IsValid(pLastTarget) )
        {
          pLastTarget = pUnit->GetCurrentTarget();
        }
        return true; // We cast ability on this step
      }
    }

    if (pUnit->IsIdle())
    {
      if ( IsUnitValid(pLastTarget) && !pUnit->GetCurrentTarget() )
      {
        pUnit->AssignTarget( pLastTarget, false );
      }
      else 
      {
        if( PFBaseUnit* pTarget = pUnit->FindTarget( pUnit->GetTargetingRange() ) ) 
        {
          pUnit->AssignTarget( pTarget, false );        
        }
      }
      pLastTarget = pUnit->GetCurrentTarget();
      if( pUnit->HasAtackAbility() && IsUnitValid( pLastTarget ) && pLastTarget->IsVisibleForFaction( pUnit->GetFaction() ) )
      {
        DEBUG_PRINT("OnStep Idle->Attack");
        EnqueueAttackState( pUnit, pLastTarget, false, true, true );
        pUnit->SetNeedRotate( true );
        lastMovePoint = pUnit->GetPos();
      }
      else 
      {
        pLastTarget = 0;
        if ( !IsMoveFinished() && !pUnit->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDMOVE ) )
        {
          DEBUG_PRINT("OnStep Idle->MoveTo");
          ContinueMove();
        }
      }
      pUnit->FSMStep(0.0f);
    }

    if ( !IsUnitValid(pLastTarget) )
      pLastTarget = 0;

    if ( targetingDelay > 0.f )
    {
      targetingDelay -= dtInSeconds;
      return true;
    }

    bool bTaunt = pUnit->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDSELECTTARGET );

    if ( !IsValid(pLastTarget) && pUnit->IsMoving() && !bTaunt )
    {
      if( PFBaseUnit* pTarget = pUnit->FindTarget( pUnit->GetTargetingRange() ) ) 
      {
        if ( pUnit->HasAtackAbility() && pUnit->CanAttackTarget( pTarget ) )
        {
          pLastTarget = pTarget;
          DEBUG_PRINT("OnStep Move->Attack");
          EnqueueAttackState( pUnit, pLastTarget, false, true, true );
          pUnit->SetNeedRotate( true );
          lastMovePoint = pUnit->GetPos();
        }
      }
    }
    else if ( IsUnitValid(pLastTarget) && !bTaunt )
    {
      bool dropTarget = false;
      if ( chaseRange < 0 )
      {
        float range = Max( pUnit->GetTargetingRange(), pUnit->GetAttackRange() );
        if ( !pUnit->IsPositionInRange( pLastTarget->GetPos(), range ) )
          dropTarget = true;
      }
      else if ( chaseRange > 0 )
      {
        if ( !pUnit->IsPositionInRange( lastMovePoint, chaseRange ) )
          dropTarget = true;
      }

      if ( dropTarget )
      {
        DEBUG_PRINT("OnStep Attack->MoveTo");
        pUnit->DropStates();
        ContinueMove();
        targetingDelay = 1.f;
        pLastTarget = 0;
      }
    }

    return true;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFNeutralCreepBaseMoveBehaviour::OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget )
  {
    NI_VERIFY( IsUnitValid( pTarget ) && pTarget->IsVulnerable(), "Invalid Target!", return; );

    if ( pUnit->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDATTACK ) )
    {
      return; // Attack forbid flag not empty!
    }
    if ( pUnit->HaveAbilityInProgress() )
    {
      return;
    }
    if ( !pUnit->HasAtackAbility() )
      return;
    DEBUG_PRINT("OnTarget PushAttackState");
    pUnit->DropStates();
    PushAttackState( pUnit, pUnit, pTarget, bStrongTarget, false, true );
    pUnit->SetNeedRotate( true );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFNeutralCreepBaseMoveBehaviour::OnDamage( const PFBaseUnitDamageDesc& desc )
  {
    if ( pUnit->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
      return; // Attack forbid flag not empty!

    if ( !pUnit->HasAtackAbility() )
      return;

    if (!pUnit->IsDead() && pUnit->GetCurrentState() == 0)
    {
      CPtr<PFBaseUnit> pSender = IsValid(desc.pSender) ? ( desc.pSender->IsMounted() ? desc.pSender->GetMountedOn() : desc.pSender ) : NULL;
      if ( IsTargetValid(pSender) && pSender->IsVisibleForFaction(pUnit->GetFaction()) )
      {
        DEBUG_PRINT("OnDamage PushAttackState");
        PushAttackState( pUnit, pUnit, pSender, false, !desc.dontAttackBack );
      }
    }
    else 
      PFBaseBehaviour::OnDamage( desc );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFNeutralCreepBaseMoveBehaviour::CanSelectTarget( PFBaseUnit const* pTarget, bool mustSeeTarget /*= false*/ ) const
  {
    return true;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFNeutralCreepBaseMoveBehaviour::IsInDefaultState() const
  {
    return pUnit->IsIdle() && !IsValid(pLastTarget);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  PFNeutralCreepMoveToPointBehaviour::PFNeutralCreepMoveToPointBehaviour( PFNeutralCreep *pCreep,const CVec2& _targetPoint, float _targetRange, float _chaseRange )
    :PFNeutralCreepBaseMoveBehaviour( pCreep, _chaseRange)
    ,targetPoint(_targetPoint)
    ,targetRange(_targetRange)
  {
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFNeutralCreepMoveToPointBehaviour::IsMoveFinished() const
  {
    return pUnit->IsPositionInRange( targetPoint, targetRange );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFNeutralCreepMoveToPointBehaviour::ContinueMove()
  {
     pUnit->PushState( new PFBaseUnitMoveToState(pUnit, targetPoint, targetRange) );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFNeutralCreepMoveToPointBehaviour* PFNeutralCreepMoveToPointBehaviour::CreateWithParams( PFNeutralCreep *pCreep, const vector<string>& params )
  {
    NI_VERIFY( params.size() >= 2, NStr::StrFmt( "Too few parameters: %d, 2 to 4 needed", params.size() ), return 0 );

    CVec2 pos;
    float range = 0.f;
    float chaseRange = 0.f;
    pos.x = NStr::ToFloat( params[0] );
    pos.y = NStr::ToFloat( params[1] );
    if ( params.size() >= 3 )
      range = NStr::ToFloat( params[2] );
    if ( params.size() >= 4 )
      chaseRange = NStr::ToFloat( params[3] );

    CVec2 mapSize = pCreep->GetWorld()->GetMapSize(); 
    NI_VERIFY( pos.x > 0.f && pos.x < mapSize.x, NStr::StrFmt( "Invalid x coordinate: %s", params[0] ), return 0 );
    NI_VERIFY( pos.y > 0.f && pos.y < mapSize.y, NStr::StrFmt( "Invalid y coordinate: %s", params[1] ), return 0 );
    NI_VERIFY( range >= 0.f && range < mapSize.x, NStr::StrFmt( "Invalid range: %s", params[2] ), return 0 );
    NI_VERIFY( chaseRange < mapSize.x, NStr::StrFmt( "Invalid chase range: %s", params[3] ), return 0 );

    return new PFNeutralCreepMoveToPointBehaviour( pCreep, pos, range, chaseRange );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  PFNeutralCreepMoveByPathBehaviour::PFNeutralCreepMoveByPathBehaviour( PFNeutralCreep *pCreep, const vector<CVec2>& _wayPoints, float _chaseRange )
    :PFNeutralCreepBaseMoveBehaviour( pCreep, _chaseRange)
    ,wayPoints(_wayPoints)
  {
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFNeutralCreepMoveByPathBehaviour::IsMoveFinished() const
  {
    return pUnit->IsPositionInRange( wayPoints.back(), g_fCreepWayPointRadius );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFNeutralCreepMoveByPathBehaviour::ContinueMove()
  {
     pUnit->PushState( new PFBaseUnitPathMovingState(pUnit, wayPoints, g_fCreepWayPointRadius) );
     pUnit->FSMStep(0.f);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFNeutralCreepMoveByPathBehaviour* PFNeutralCreepMoveByPathBehaviour::CreateWithParams( PFNeutralCreep *pCreep, const vector<string>& params )
  {
    NI_VERIFY( params.size() >= 2, NStr::StrFmt( "Too few parameters: %d, 2 needed", params.size() ), return 0 );

    const vector<CVec2> *pPath = pCreep->GetWorld()->GetAIContainer()->GetScriptPath( params[0] );
    float chaseRange = 0.f;
    if ( params.size() >= 2 )
      chaseRange = NStr::ToFloat( params[1] );

    CVec2 mapSize = pCreep->GetWorld()->GetMapSize(); 
    NI_VERIFY( pPath, NStr::StrFmt( "Cannot find ScriptPath: %s", params[0] ), return 0 );
    NI_VERIFY( chaseRange < mapSize.x, NStr::StrFmt( "Invalid chase range: %s", params[1] ), return 0 );

    return new PFNeutralCreepMoveByPathBehaviour( pCreep, *pPath, chaseRange );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  PFNeutralCreepChaseBehaviour::PFNeutralCreepChaseBehaviour( PFNeutralCreep *pCreep, PFBaseUnit* _pTarget, float _targetRange, float _chaseRange )
    :PFNeutralCreepBaseMoveBehaviour( pCreep, _chaseRange )
    ,pChaseTarget(_pTarget)
    ,targetRange(_targetRange)
  {
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFNeutralCreepChaseBehaviour::IsMoveFinished() const
  {
    return IsUnitValid( pChaseTarget ) && pUnit->IsPositionInRange( pChaseTarget->GetPos(), targetRange );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFNeutralCreepChaseBehaviour::ContinueMove()
  {
    pUnit->PushState( new PFBaseUnitChaseState( pUnit, false, targetRange, 0.f, pChaseTarget, true, true ) );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFNeutralCreepChaseBehaviour* PFNeutralCreepChaseBehaviour::CreateWithParams( PFNeutralCreep *pCreep, const vector<string>& params )
  {
    NI_VERIFY( params.size() >= 2, NStr::StrFmt( "Too few parameters: %d, 2 or 3 needed", params.size() ), return 0 );

    PFBaseUnit* pTarget = pCreep->GetWorld()->GetAIContainer()->FindUnit( params[0].c_str() );
    float targetRange = NStr::ToFloat( params[1] );
    float chaseRange = 0.f;
    if ( params.size() >= 3 )
      chaseRange = NStr::ToFloat( params[2] );

    CVec2 mapSize = pCreep->GetWorld()->GetMapSize(); 
    NI_VERIFY( pTarget, NStr::StrFmt( "Unit %s not found", params[0] ), return 0 );
    NI_VERIFY( targetRange >= 0.f && targetRange < mapSize.x, NStr::StrFmt( "Invalid target range: %s", params[1] ), return 0 );
    NI_VERIFY( chaseRange < mapSize.x, NStr::StrFmt( "Invalid chase range: %s", params[2] ), return 0 );

    return new PFNeutralCreepChaseBehaviour( pCreep, pTarget, targetRange, chaseRange );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NWorld


REGISTER_WORLD_OBJECT_NM(PFNeutralCreepEvadeState, NWorld);
REGISTER_WORLD_OBJECT_NM(PFNeutralCreepWaitState,  NWorld);
REGISTER_WORLD_OBJECT_NM(PFNeutralCreepBehaviour,  NWorld);
REGISTER_WORLD_OBJECT_NM(PFNeutralCreepMoveToPointBehaviour,  NWorld);
REGISTER_WORLD_OBJECT_NM(PFNeutralCreepMoveByPathBehaviour,  NWorld);
REGISTER_WORLD_OBJECT_NM(PFNeutralCreepChaseBehaviour,  NWorld);


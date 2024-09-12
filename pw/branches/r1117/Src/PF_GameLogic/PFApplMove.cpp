#include "stdafx.h"
#include "PFBaseMovingUnit.h"
#include "PFMaleHero.h"
#include "PFAbilityInstance.h"
#include "PFClientApplicators.h"
#include "PFLogicDebug.h"
#include "PFBaseUnitStates.h"
#include "PFHeroStates.h"
#include "PFWorld.h"
#include "PFDispatch.h"
#include "PFAbilityData.h"
#include "PFApplMove.h"
#include "PFApplUtils.h"
#include "PFTargetSelector.h"
#include "TileMap.h"
#include "../PF_Core/EffectsPool.h"
#include "PFClientCreature.h"
#include "PFTalent.h"
#include "PFStatistics.h"

#ifndef VISUAL_CUTTED
#include "PFClientBaseMovingUnit.h"
#endif

namespace NWorld
{

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplMoveTo::MoveIt( const CVec2& pos )
  {
    if ( !IsUnitValid( pReceiver ) )
    {
      return true;
    }

    isMoveDirect = RetrieveParam( GetDB().isMoveDirect );
    isNotStackable = GetDB().isNotStackable;

    targetPosition = pos;

    CDynamicCast<PFBaseMovingUnit> pMoveable( pReceiver );
    if ( !pMoveable )
    {
      return true;
    }

    if ( GetDB().justRotate )
    {
      pMoveable->SetMoveDirection( pos );
#ifndef VISUAL_CUTTED
      if( NGameX::PFClientBaseMovingUnit* pClient = pMoveable->ClientObject() )
      {
        pClient->LookTo( pos );
      }
#endif

      return true;
    }

    if ( pMoveable->GetPosition().AsVec2D() == targetPosition )
    {
      // Move to self
      pMoveable->Stop();
      return true;
    }

    if ( isMoveDirect == false )
    {
      struct RemoveSameApplicator
      {
        void operator()( const CObj<PFBaseApplicator> &pAppl )
        {
          if ( pAppl->GetTypeId() == PFApplMoveTo::typeId && static_cast<const PFApplMoveTo*>(pAppl.GetPtr())->IsMoveDirect() == false )
          {
            pAppl->Stop();
            MemorizeApplicator(pAppl);
          }
        }
      } f;

      pReceiver->ForAllAppliedApplicators(f);

      moveState = new PFBaseUnitMoveToState( pMoveable, pos, 0.0f, false );
      pMoveable->PushState( moveState );

      // Start movement immediately
      if ( pMoveable->GetCurrentState() == moveState )
        pMoveable->FSMStep(0.0f);
    }
    else
    {
      if (isNotStackable == true)
      {
        struct RemoveSameApplicator
        {
          void operator()( const CObj<PFBaseApplicator> &pAppl )
          {
            if ( pAppl->GetTypeId() == PFApplMoveTo::typeId && static_cast<const PFApplMoveTo*>(pAppl.GetPtr())->IsNotStackable() == true )
            {
              pAppl->Stop();
              MemorizeApplicator(pAppl);
            }
          }
        } f;

        pReceiver->ForAllAppliedApplicators(f);
      }

      ghostMoveIndex = pMoveable->SetGhostMode( NDb::GHOSTMOVEMODE_IGNOREDYNAMIC, false );  // collide with static map objects only

      if ( pMoveable->MoveToSpecial( pos ) )
      {
        float moveSpeed = RetrieveParam( GetDB().moveSpeed, 0.0f );
        moveSpeed = pMoveable->SetUnitSpeed( moveSpeed ); // speed in MpS
        NI_VERIFY ( moveSpeed > 0, "returned invalid moveSpeed", return true );
        // note: flightSpeed value is different than passed to SetUnitSpeed() because
        // of some speed modifiers etc
        pMoveable->SetMoveFlags( MOVE_FLAG_NO_COLLIDE | MOVE_FLAG_OVERRIDE_SPEED );
      }
    }

    return false;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplMoveTo::Start()
  {
    if (PFApplBuff::Start())
      return true;

    /*if ( pReceiver->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDMOVE ) )
    {
    NotifyParent(NDb::PARENTNOTIFICATION_CANCEL);
    return true;
    }*/

    Target targ;
    MakeApplicationTarget(targ, GetDB().moveTarget);

    if ( !targ.IsValid() )
    {
      NotifyParent(NDb::PARENTNOTIFICATION_CANCEL);
      return true;
    }

    // setup coordinates relative to path (negative_Y pointing towards target)
    CVec2 tpos = targ.AcquirePosition().AsVec2D();
    CVec2 y = pReceiver->GetPosition().AsVec2D() - tpos;

    if (!Normalize(&y))
    {
      y = CVec2(0.f, 1.f);
    }
    CVec2 x = CVec2(y.y, -y.x);

    return MoveIt(tpos + GetDB().offset.x * x + GetDB().offset.y * y);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFApplMoveTo::Stop()
  {
    NI_PROFILE_FUNCTION

    CDynamicCast<PFBaseMovingUnit> pMoveable( pReceiver );

    if ( pMoveable && !pMoveable->IsDead() )
    {
      if ( !GetDB().justRotate )
      {
        if ( ghostMoveIndex > -1 )
        {
          if ( pMoveable )
            pMoveable->ResetGhostMode( ghostMoveIndex );
          ghostMoveIndex = -1;
        }

        if ( isMoveDirect == true )
        {
          pMoveable->Stop();
          // Now find free place for the unit, so it won't be eventually trapped in some obstacle
          if ( GetDB().pushUnits )
          {
            pMoveable->PlaceUnitWithPush( pMoveable->GetPosition().AsVec2D(), pMoveable->GetObjectSize() );
          }
          else
          {
            pMoveable->PlaceUnit( pMoveable->GetPosition().AsVec2D(), false, false, true );
          }
        }
        else
        {
          pMoveable->RemoveState( moveState );
        }
      }
      else // !GetDB().justRotate 
      {
        pMoveable->Stop();
      }
    }

    moveState = 0;

    PFApplBuff::Stop();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplMoveTo::Step(float dtInSeconds)
  {
    if (PFApplBuff::Step(dtInSeconds))
      return true;

    if ( GetDB().justRotate )
      return true;

    CVec2 d = pReceiver->GetPosition().AsVec2D() - targetPosition;
    if (d.Length() < (RetrieveParam(GetDB().moveRange) + 0.01f))
      return true;

    CDynamicCast<PFBaseMovingUnit> pMoveable(pReceiver);
    if (!pMoveable)
      return true;
    return !pMoveable->IsMoving();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplKickAway::Start()
  {
    if ( PFBaseApplicator::Start() )
    {
      return true;
    }

    CPtr<PFBaseMovingUnit> pTargetUnit = dynamic_cast<PFBaseMovingUnit*>( pReceiver.GetPtr() );
    NI_VERIFY( IsUnitValid( pTargetUnit ), ErrorStr( "Could be applied to PFBaseMovingUnit only" ), return true );

    if ( pTargetUnit->IsMounted() )
    {
      return true;
    }

    // Target pos
    const CVec2& pos     = pTargetUnit->GetPosition().AsVec2D();
    const CVec2& posTo   = GetAbility()->GetTarget().AcquirePosition().AsVec2D();
    const CVec2& posFrom = GetAbilityOwner()->GetPosition().AsVec2D();

    CVec2 moveDir = posTo - posFrom;

    float maxKickDistance = GetDB().distance;

    if ( fabs2( moveDir ) > 1.0e-8f )
    {
      Normalize( &moveDir );
      CVec2 ortDir( moveDir.y, -moveDir.x );
      CVec2 dir = pos - posFrom;
      float distanceFromMoveLine = dir.Dot( ortDir );

      if ( fabs( distanceFromMoveLine ) > maxKickDistance )
      {
        return true;
      }

      float kickDist;
      if ( distanceFromMoveLine > 0.0f )
      {
        kickDist = maxKickDistance - distanceFromMoveLine;
      }
      else
      {
        ortDir = -ortDir;
        kickDist = maxKickDistance + distanceFromMoveLine;
      }

      kickDist = pTargetUnit->CheckStraightMove( pos + ortDir * kickDist, MAP_MODE_ALL_STATICS );
      pTargetUnit->TeleportTo( pos + ortDir * kickDist, true, false );
    }
    else
    {
      // Kick from point
      CVec2 dir = pos - posFrom;
      const float dirLen2 = fabs2( dir );
      if ( dirLen2 > fabs2( maxKickDistance ) )
      {
        return true;
      }

      if ( dirLen2 < 1.0e-8f )
      {
        NI_ALWAYS_ASSERT("Don't know where to kick!");
        return true;
      }

      Normalize( &dir );

      const float kickDist = pTargetUnit->CheckStraightMove( posFrom + maxKickDistance * dir, MAP_MODE_ALL_STATICS );
      NI_ASSERT( kickDist <= maxKickDistance, "Logic failed" );
      pTargetUnit->TeleportTo( posFrom + kickDist * dir, true, false );
    }

    pTargetUnit->EventHappened( PFBaseUnitApplicatorEvent( NDb::BASEUNITEVENT_FORCEDMOVE, this ) );

    return true; // done.
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplKickAway::Step( float dtInSeconds )
  {
    NI_ALWAYS_ASSERT( "Must never get here" );
    return true;
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplShift::Start()
  {
    if (PFBaseApplicator::Start())
      return true;

    if (!pTargetSelector)
    {
      if (GetDB().targetSelector)
        pTargetSelector = static_cast<PFSingleTargetSelector*>(GetDB().targetSelector->Create( GetWorld() ));
    }
    NI_VERIFY(pTargetSelector, "PFApplShift requires targetSelector", return true);

    CPtr<PFBaseMovingUnit> pTargetUnit = dynamic_cast<PFBaseMovingUnit*>( pReceiver.GetPtr() );
    NI_VERIFY(IsUnitValid(pTargetUnit), ErrorStr("Could be applied to PFBaseMovingUnit only"), return true);

    if( pTargetUnit->IsMounted() || pTargetUnit->CheckFlag( NDb::UNITFLAG_FORBIDMOVESPECIAL ) )
      return true;

    Target targ;
    Target receiver(pReceiver);
    PFTargetSelector::RequestParams pars(*this, receiver);
    if (pTargetSelector->FindTarget(pars, targ))
    {
      if ( !targ.IsValid() )
      {
        NotifyParent(NDb::PARENTNOTIFICATION_CANCEL);
        return true;
      }
      CVec2 shiftPos = targ.AcquirePosition().AsVec2D();
      pTargetUnit->TeleportTo(shiftPos, true, false);
      pTargetUnit->EventHappened(PFBaseUnitApplicatorEvent(NDb::BASEUNITEVENT_FORCEDMOVE, this));
    }
    return true; // done.
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplShift::Step(float dtInSeconds)
  {
    NI_ALWAYS_ASSERT("Must never get here");
    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplThrow::Start()
  {
#ifndef VISUAL_CUTTED
    if (GetDB().lockRotation)
    {
      if (NGameX::PFClientLogicObject* const clientObject = pReceiver->ClientObject())
      {
        if (NScene::SceneObject* const sceneObject = clientObject->GetSceneObject())
        {
          sceneObject->LockRotation(true);
        }
      }
    }
#endif // VISUAL_CUTTED

    if ( PFBaseApplicator::Start() )
    {
      return true;
    }

    bStarted = CheckFly();
    if ( bStarted )
    {
      const NDb::ThrowApplicator &DB = GetDB();

      if (IsValid(DB.firstTargetToHit))
      {
        hitTargetSelector = static_cast<PFSingleTargetSelector*>(DB.firstTargetToHit->Create(GetWorld()));
      }

      const float maxDistance     = DB.maxDistance;
      const float distance        = ( GetReceiver()->GetPosition() - targ.AcquirePosition() ).Length();
      const float distancePercent = ( distance > maxDistance || maxDistance < FP_EPSILON ) ? 1.0 : distance / maxDistance;

      const float maxHeight = DB.maxHeight;
      float heightPercent = 1.0f;
      if ( DB.trajectory.IsAnimated() )
      {
        float maxAnimatedHeight = 0.0f;

        typedef vector<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear>::KeyValue>::const_iterator animIter;
        for ( animIter iter = DB.trajectory.begin(); iter != DB.trajectory.end(); iter++ )
        {
          float curHeight = DB.trajectory.GetPoint( iter ).y;
          if ( curHeight > maxAnimatedHeight )
          {
            maxAnimatedHeight = curHeight;
          }
        }

        if ( maxAnimatedHeight > EPS_VALUE )
        {
          heightPercent = maxHeight / maxAnimatedHeight;
        }
      }

      heightModifier = distancePercent * heightPercent;

      PrepareFlyEffect();

      if ( DB.flightType == NDb::THROWTYPE_JUMP )
      {
        // Prepare
        hasStartedTakeOff = true;
        ApplyFlyEffect();
      }
      if ( DB.takeOffTime == 0.0f )
      {
        return !StartFly();
      }
    }
    else
    {
      NotifyParent( NDb::PARENTNOTIFICATION_CANCEL );
    }

    return !bStarted;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplThrow::CheckFly()
  {
    pTargetUnit = dynamic_cast<PFCreature*>( pReceiver.GetPtr() );

    if(GetAbilityData()->DoesApplyToDead())
    {
      NI_VERIFY( IsValid( pTargetUnit ), ErrorStr( "Could be applied to PFCreature only" ), return false );
    }
    else
    {
      NI_VERIFY( IsUnitValid( pTargetUnit ), ErrorStr( "Could be applied to PFCreature only" ), return false );
    }

    if ( pTargetUnit->IsMounted() || pTargetUnit->CheckFlag( NDb::UNITFLAG_FORBIDMOVESPECIAL ) )
    {
      return false;
    }

    const NDb::ThrowApplicator &DB = GetDB();

    switch ( DB.flightType )
    {
    case NDb::THROWTYPE_JUMP:
    case NDb::THROWTYPE_THROW:
      {
        CObj<PFSingleTargetSelector> pTargetSelector;
        NI_VERIFY( DB.targetSelector, "Requires targetSelector", return false );
        pTargetSelector = static_cast<PFSingleTargetSelector*>( DB.targetSelector->Create( GetWorld() ) );
        NI_VERIFY( pTargetSelector, "Failed to create targetSelector", return false );

        if ( !pTargetSelector->FindTarget( PFTargetSelector::RequestParams( *this, GetTarget() ), targ ) )
        {
          return false;
        }
      }
      break;

    case NDb::THROWTYPE_FLIP:
      targ = GetTarget();
      break;

    default:
      NI_ALWAYS_ASSERT( "Unknown flightType" );
      return false;
    }

    return true;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplThrow::StartFly()
  {
    const NDb::ThrowApplicator& DB = GetDB();

    CVec2 movePos;

    float speed    = RetrieveParam( DB.moveSpeed, 0.0f );
    float flipTime = RetrieveParam( DB.flipTime,  1.0f );

    if ( pTargetUnit != pOwner && pTargetUnit->GetMasterUnit() != pOwner )
    {
      // Стремное место, тут просто Pop'ается стейт без OnLeave. Постоянный источник багов :( Подпирается кастомными if'ами
      lastTargetState = pTargetUnit->PopState();
      lastTargetTarget = pTargetUnit->GetCurrentTarget();
      pTargetUnit->DropTarget();

      IPFState* curTargetState = pTargetUnit->GetCurrentState();
      int stateId = 0;
      if (curTargetState)
        stateId = curTargetState->GetTypeId();

      if (stateId == PFHeroUseTalentState::typeId || stateId == PFHeroUseConsumableState::typeId )
      {
        if (IsValid(lastTargetState))
        {
          lastTargetState->DoLeave(true);
          lastTargetState = 0;
        }
      }

      if ( IsValid(lastTargetState) )
      {
        int stateId = lastTargetState->GetTypeId() ;
        if(stateId == PFCreatureUseAbilityState::typeId || stateId == PFHeroHoldState::typeId)
        {
          lastTargetState->DoLeave(true);
          lastTargetState = 0;
        }
      }

      pTargetUnit->ForceIdle();
    }

    pTargetUnit->Stop( false ); // just in case
    pTargetUnit->FSMStep( 0.0f );

    if ( GetDB().collisionFlags > 0 )
    {
      ghostMoveIndex = pTargetUnit->SetGhostMode( GetDB().collisionFlags, false );
    }

    flightTime = 0;
    switch ( DB.flightType )
    {
    case NDb::THROWTYPE_THROW:
    case NDb::THROWTYPE_JUMP:
      {
        movePos = targ.AcquirePosition().AsVec2D(); // world

        float distance = fabs( movePos - pTargetUnit->GetPosition().AsVec2D() );

        bool moving;
        pTargetUnit->SetForbidStop( true );
        if ( targ.IsUnit() && DB.trackTargetUnit )
        {
          moving = pTargetUnit->MoveToSpecial( targ.GetUnit(), false );
        }
        else
        {
          moving = pTargetUnit->MoveToSpecial( movePos, false );
        }

        if ( moving )
        {
          // use flipTime if moveSpeed is negative
          if ( speed < 0 )
          {
            flightTime = flipTime;
            speed = distance / flightTime;
          }
          if ( speed > 0 )
          {
            float flightSpeed = pTargetUnit->SetUnitSpeed( speed ); // speed in MpS
            NI_VERIFY ( flightSpeed > 0, "returned invalid flightSpeed", return false );
            if ( distance > 0 )
              flightTime = distance / flightSpeed;
            // note: flightSpeed value is different than passed to SetUnitSpeed() because
            // of some speed modifiers etc

            pTargetUnit->SetMoveFlags( MOVE_FLAG_OVERRIDE_SPEED );
            NGameX::PFClientCreature *pClientUnit = pTargetUnit->ClientObject();
            if ( pClientUnit && DB.surfaceSpeedFromAG )
            {
              originalSpeed = pClientUnit->GetCurAnimSetSurfSpeed();
              pClientUnit->SetCurAnimSetSurfSpeed( pClientUnit->GetSurfaceSpeedCurrentNode() );
            }
          }
        }
      }
      break;

    case NDb::THROWTYPE_FLIP:
      flightTime = flipTime;
      movePos    = pTargetUnit->GetPosition().AsVec2D(); // client
      break;
    }

    // cancel if flight is not possible for some reasons (distance == 0, for example)
    if ( flightTime <= 0 )
    {
      return false;
    }

    isFlying = true;
    animatedTime = 0;

    // disable some unit actions during flight
    pTargetUnit->AddFlag( NDb::UNITFLAG_FORBIDMOVE | NDb::UNITFLAG_FORBIDATTACK | NDb::UNITFLAG_FORBIDUSETALENTS | NDb::UNITFLAG_FORBIDUSECONSUMABLES |
      NDb::UNITFLAG_FORBID_ABILITY1 | NDb::UNITFLAG_FORBID_ABILITY2 | NDb::UNITFLAG_FORBID_ABILITY3 | NDb::UNITFLAG_FORBID_ABILITY4 |
      NDb::UNITFLAG_FORBIDINTERACT );
    if ( PFBaseMaleHero const* pHero = dynamic_cast<PFBaseMaleHero const*>(pTargetUnit.GetPtr()) )
    {
      struct DisableFunc : public NonCopyable
      {
        virtual void operator()(PFTalent *pTalent, int level, int slot)
        {
          pTalent->AddForbid();
        }
      } disableFunc;


      if (pHero->GetPortal())
        disableFunc(pHero->GetPortal(), 0 ,0 );

      pHero->ForAllTalents( disableFunc );
    }
    pTargetUnit->EnableDispatch( false );

    // Activate start spell to self
    SendSpell2Targets( this, GetDB().startSpell, NULL );

    pTargetUnit->EventHappened( PFBaseUnitApplicatorEvent( NDb::BASEUNITEVENT_FORCEDMOVE, this ) );

#ifndef VISUAL_CUTTED
    NGameX::PFClientBaseMovingUnit* pClientUnit = pTargetUnit->ClientObject();
    if ( pClientUnit )
    {
      // pClientUnit->Stand(); // stop all animations
      pClientUnit->StartFlying( DB.trajectory, DB.angle, flightTime, heightModifier, pTargetUnit->GetPosition().AsVec2D(), movePos, DB.flightType );
    }
#endif // VISUAL_CUTTED
    return true;
  }

  void PFApplThrow::Stop()
  {
    NI_PROFILE_FUNCTION

    //Just in case
    KillFlyEffect();

    if ( ( GetDB().collisionFlags > 0 ) && ( ghostMoveIndex > -1 ) )
    {
      pTargetUnit->ResetGhostMode( ghostMoveIndex );
      ghostMoveIndex = -1;
    }

    PFBaseApplicator::Stop();

    if ( IsValid( pTargetUnit ) )
      pTargetUnit->SetForbidStop( false );

    if ( isFlying )
    {
      // enable actions which were disabled
      pTargetUnit->RemoveFlag( NDb::UNITFLAG_FORBIDMOVE | NDb::UNITFLAG_FORBIDATTACK | NDb::UNITFLAG_FORBIDUSETALENTS | NDb::UNITFLAG_FORBIDUSECONSUMABLES |
        NDb::UNITFLAG_FORBID_ABILITY1 | NDb::UNITFLAG_FORBID_ABILITY2 | NDb::UNITFLAG_FORBID_ABILITY3 | NDb::UNITFLAG_FORBID_ABILITY4 |
        NDb::UNITFLAG_FORBIDINTERACT );
      if ( PFBaseMaleHero const* pHero = dynamic_cast<PFBaseMaleHero const*>(pTargetUnit.GetPtr()) )
      {
        struct EnableFunc : public NonCopyable
        {
          virtual void operator()(PFTalent *pTalent, int level, int slot)
          {
            pTalent->RemoveForbid();
          }
        } enableFunc;

        if (pHero->GetPortal())
          enableFunc(pHero->GetPortal(), 0 , 0);

        pHero->ForAllTalents( enableFunc );
      }
      pTargetUnit->EnableDispatch(true);

      if ( !pTargetUnit->IsDead() )
      {
        pTargetUnit->Stop();
        pTargetUnit->PlaceUnitWithPush( pTargetUnit->GetPosition().AsVec2D(), pTargetUnit->GetObjectSize(), true );

        if ( pTargetUnit != pOwner && IsValid(lastTargetState) )
        {
          if( IsUnitValid(lastTargetTarget) )
            pTargetUnit->AssignTarget(lastTargetTarget);
          pTargetUnit->PushState(lastTargetState);

          lastTargetState = 0;
          lastTargetTarget = 0;
        }
      }

#ifndef VISUAL_CUTTED
      NGameX::PFClientBaseMovingUnit *pClientUnit = pTargetUnit->ClientObject();
      if ( pClientUnit )
      {
        pClientUnit->StopFlying();
        if ( originalSpeed != 0.0f )
        {
          NGameX::PFClientCreature *pClientCreature = pTargetUnit->ClientObject();
          if ( pClientCreature )
          {
            pClientCreature->SetCurAnimSetSurfSpeed( originalSpeed );
          }
        }
      }
#endif // VISUAL_CUTTED
    }

    if ( IsValid( pTargetUnit ) && !pTargetUnit->IsDead() )
    {
      // Activate stop spell to self
      SendSpell2Targets( this, GetDB().stopSpell, NULL );
    }

#ifndef VISUAL_CUTTED
    if (GetDB().lockRotation)
    {
      if (NGameX::PFClientLogicObject* const clientObject = pReceiver->ClientObject())
      {
        if (NScene::SceneObject* const sceneObject = clientObject->GetSceneObject())
        {
          sceneObject->LockRotation(false);
        }
      }
    }
#endif // VISUAL_CUTTED
  }

  bool PFApplThrow::Step( float dtInSeconds )
  {
    if ( PFBaseApplicator::Step( dtInSeconds ) )
    {
      return true;
    }

    if (!IsEnabled() && (GetDBAppl<NDb::ThrowApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_STOPONDISABLE) != 0)
      return true;

    const bool hitTarget = CheckHit();

    const NDb::ThrowApplicator &DB = GetDB();
    animatedTime += dtInSeconds;
    bool stop = false;

    if ( isFlying )
    {
      if ( DB.flightType == NDb::THROWTYPE_JUMP )
      {
        const float landTime = DB.landTime;

        if ( animatedTime >= ( flightTime - landTime ) )
        {
          KillFlyEffect();
        }
      }

      stop = animatedTime >= flightTime;

      if ( stop || hitTarget )
      {
        KillFlyEffect();
        NotifyParent( NDb::PARENTNOTIFICATION_CANCEL );
      }
    }
    else // !isFlying
    {
      if ( ( DB.flightType == NDb::THROWTYPE_JUMP ) && !hasStartedTakeOff )
      {
        // Prepare
        hasStartedTakeOff = true;
        ApplyFlyEffect();
      }
      if ( ( DB.flightType != NDb::THROWTYPE_JUMP ) || ( hasStartedTakeOff && ( animatedTime >= DB.takeOffTime ) ) )
      {
        stop = !StartFly();
      }
    }

    return stop || hitTarget;
  }

  bool PFApplThrow::CheckHit() const
  {
    if (!IsValid(hitTargetSelector))
      return false;

    const Target requestor(pReceiver.GetPtr());
    const PFTargetSelector::RequestParams request(*this, requestor);

    Target hitTarget;

    return hitTargetSelector->FindTarget(request, hitTarget);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFApplThrow::PrepareFlyEffect()
  {
    const NDb::ThrowApplicator& DB = GetDB();

    int teamID = GetAbilityOwner()->GetOriginalTeamId();
    if ( teamID == -1 )
    {
      teamID = NDb::TEAMID_A;
    }
    if ( DB.flyEffect[teamID].IsEmpty() )
    {
      teamID = ( teamID == NDb::TEAMID_B ? NDb::TEAMID_A : NDb::TEAMID_B );
    }

    pFlyEffect = PF_Core::EffectsPool::Get()->Retrieve( DB.flyEffect[teamID] );
  }

  void PFApplThrow::ApplyFlyEffect()
  {
    if ( !pFlyEffect )
    {
      return;
    }

    NGameX::ApplyEffect( pFlyEffect, pTargetUnit.GetPtr(), pTargetUnit.GetPtr(), pTargetUnit.GetPtr(), this );
  }

  void PFApplThrow::KillFlyEffect()
  {
    if ( !pFlyEffect )
    {
      return;
    }

    NGameX::KillEffect( pFlyEffect, GetDBAppl<NDb::BuffApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_DONTREMOVEEFFECT );
  }

  bool PFApplThrow::NeedToStopOnDeath() const
  {
    CPtr<PFBaseUnit> const& pReceiver = GetReceiver();
    if ( (GetDBAppl<NDb::ThrowApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_DONTSTOPONDEATH)
      || ( bPassive && IsValid(pReceiver) && pOwner == pReceiver ) )
      return false;

    return PFBaseApplicator::NeedToStopOnDeath();
  }

  bool PFApplThrow::NeedToStopOnSenderDeath() const
  {
    CPtr<PFBaseUnit> const& pReceiver = GetReceiver();
    if ( (GetDBAppl<NDb::ThrowApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_DONTSTOPONSENDERDEATH)
      || ( bPassive && IsValid(pReceiver) && pOwner == pReceiver ) )
      return false;

    return PFBaseApplicator::NeedToStopOnSenderDeath();
  }

  bool PFApplThrow::NeedToDisableOnDeath() const
  {
    if (GetDBAppl<NDb::ThrowApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_ENABLEDONSENDERDEATH)
      return false;

    return PFBaseApplicator::NeedToDisableOnDeath();
  }

  bool PFApplThrow::CanBeAppliedOnDead()
  {
    return GetDBAppl<NDb::ThrowApplicator>().behaviorFlags & NDb::BUFFBEHAVIOR_APPLYTODEAD;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplFly::Start()
  {
    if ( PFBaseApplicator::Start() )
    {
      return true;
    }

    bStarted = CheckFly();
    if ( bStarted )
    {
      StartFly();
    }
    else
    {
      NotifyParent( NDb::PARENTNOTIFICATION_CANCEL );
    }

    return !bStarted;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplFly::CheckFly()
  {
    pTargetUnit = dynamic_cast<PFCreature*>( pReceiver.GetPtr() );
    NI_VERIFY( IsUnitValid( pTargetUnit ), ErrorStr( "Could be applied to PFCreature only" ), return false );

    if ( pTargetUnit->IsMounted() )
    {
      return false;
    }

    struct UpdateApplicator
    {
      UpdateApplicator( const PFApplFly* _pNewcomer, float _newLifeTime ) : pNewcomer( _pNewcomer ), newLifeTime( _newLifeTime ), found(false) { }

      void operator()(const CObj<PFBaseApplicator>&pAppl )
      {
        if ( pAppl->GetTypeId() == PFApplFly::typeId )
        {
          static_cast<PFApplFly*>( pAppl.GetPtr() )->UpdateLifeTime( newLifeTime );
          found = true;
        }
      }

      const PFApplFly* pNewcomer;
      float newLifeTime;
      bool found;
    } f( this, RetrieveParam( GetDB().lifeTime ) );

    pReceiver->ForAllAppliedApplicators( f );

    if ( f.found )
      return false;

    return true;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFApplFly::StartFly()
  {
    animatedTime = 0.0f;
    lifeTime = RetrieveParam( GetDB().lifeTime );

    const NDb::FlyApplicator &DB = GetDB();

    // If we are in moving state -> drop it
    pTargetUnit->Stop( false ); // just in case

    ghostMoveIndex = pTargetUnit->SetGhostMode( DB.collisionFlags, false );

    ClientStartFly();
  }

  void PFApplFly::ClientStartFly()
  {
    // Activate start spell to self
    SendSpell2Targets( this, GetDB().startSpell, NULL );

    ReplaceAnimations();


#ifndef VISUAL_CUTTED
    NGameX::PFClientCreature *pClientUnit = pTargetUnit->ClientObject();
    if ( pClientUnit )
    {
      // pClientUnit->Stand(); // stop all animations
      pClientUnit->StartFlying();
    }
#endif // VISUAL_CUTTED
  }

  void PFApplFly::Stop()
  {
    if ( ghostMoveIndex > -1 )
    {
      pTargetUnit->ResetGhostMode( ghostMoveIndex );
      ghostMoveIndex = -1;
    }

    PFBaseApplicator::Stop();

    if ( bStarted )
    {
      bStarted = false;

      //Just in case
      RollbackAnimations();

      const NDb::FlyApplicator& DB = GetDB();

      // Activate stop spell to self
      SendSpell2Targets( this, DB.stopSpell, NULL );

      pTargetUnit->Stop();
      if ( !pTargetUnit->IsDead() )
      {
        CVec2 foundPos;
        const bool placeFound = pTargetUnit->FindFreePlace( pTargetUnit->GetPosition().AsVec2D(), DB.radiusFixObstacle, foundPos );

        if ( DB.push )
        {
          if( placeFound )
            pTargetUnit->PlaceUnitWithPush( foundPos, pTargetUnit->GetObjectSize(), true );
        }
        else
        {
          if( placeFound )
            pTargetUnit->PlaceUnit( foundPos, false, false, true );
        }

        pTargetUnit->UpdateWarFog();
      }

#ifndef VISUAL_CUTTED
      NGameX::PFClientCreature* pClientUnit = pTargetUnit->ClientObject();
      if ( pClientUnit )
      {
        pClientUnit->Stand();
        pClientUnit->StopFlying();
      }
#endif // VISUAL_CUTTED
    }
  }

  void PFApplFly::Reset()
  {
    PFBaseApplicator::Reset();

    if (bStarted)
    {
      NGameX::PFClientCreature *pClientUnit = pTargetUnit->ClientObject();
      if ( pClientUnit )
      {
        ReplaceAnimations();
        pClientUnit->StartFlying();
      }
    }
  }

  void PFApplFly::ReplaceAnimations()
  {
    const NDb::FlyApplicator& DB = GetDB();
    CPtr<PFCreature> pCreature = pTargetUnit;

    if ( IsValid(pCreature) && pCreature->ClientObject() )
    {
      unsigned int curNode = pCreature->ClientObject()->GetNearestStateId();

      const int numAnims = DB.replaceAnimations.size();
      oldAnimations.resize( numAnims );

      for ( vector<int>::iterator i = oldAnimations.begin(); i != oldAnimations.end(); i++ )
      {
        vector<NDb::AnimStateChanger>::const_iterator j = DB.replaceAnimations.begin() + ( i - oldAnimations.begin() );
        NDb::EAnimStates state = j->oldAnimation.animState;
        if ( state != NDb::ANIMSTATES_INVALID )
        {
          unsigned int replNode = pCreature->ClientObject()->GetStateId( state );
          *i = pCreature->ReplaceAnimation( state, j->newAnimation.node.c_str(), j->newAnimation.marker.c_str(), false, false );
          if ( curNode == replNode )
          {
            pCreature->ClientObject()->SetAnimState( state );
          }
        }
        else
        {
          //if "state" field is empty or "invalid", use old node
          *i = pCreature->ReplaceAnimation( j->oldAnimation.node.c_str(), j->newAnimation.node.c_str(), j->newAnimation.marker.c_str(), false, false );
        }
      }
    }
  }

  void PFApplFly::RollbackAnimations()
  {
    const NDb::FlyApplicator &DB = GetDB();
    CPtr<PFCreature> pCreature = pTargetUnit;

    if ( IsValid(pCreature) && pCreature->ClientObject() )
    {
      for ( vector<int>::const_iterator i = oldAnimations.begin(); i != oldAnimations.end(); i++ )
      {
        if ( *i != -1 )
        {
          vector<NDb::AnimStateChanger>::const_iterator j = DB.replaceAnimations.begin() + ( i - oldAnimations.begin() );
          NDb::EAnimStates state = j->oldAnimation.animState;
          if ( state != NDb::ANIMSTATES_INVALID )
          {
            pCreature->RollbackAnimation( state, *i, false );
          }
          else
          {
            //if "state" field is empty or "invalid", use old node
            pCreature->RollbackAnimation( j->oldAnimation.node.c_str(), *i, false );
          }
        }
      }
      pCreature->ClientObject()->SetAnimState( NDb::ANIMSTATES_IDLE );
    }
  }

  bool PFApplFly::Step( float dtInSeconds )
  {
    if ( PFBaseApplicator::Step( dtInSeconds ) )
    {
      return true;
    }

    animatedTime += dtInSeconds;

#ifndef VISUAL_CUTTED
    NGameX::PFClientCreature *pClientUnit = pTargetUnit->ClientObject();
    if ( pClientUnit )
    {
      const NDb::FlyApplicator& DB = GetDB();
      const float startTime = DB.startTime;
      const float stopTime  = DB.stopTime;

      float heightProc = 1.0f;

      if ( animatedTime <= DB.startTime )
      {
        heightProc = ClampFast( animatedTime / startTime, 0.0f, 1.0f );
      }
      else
      {
        if ( animatedTime >= ( lifeTime - stopTime ) )
        {
          heightProc = ClampFast( ( lifeTime - animatedTime ) / stopTime, 0.0f, 1.0f );
        }
      }

      pClientUnit->SetFlightHeight( heightProc * DB.flightHeight, false );

      const float animatedStopTime  = DB.animatedStopTime;

      if ( animatedTime >= ( lifeTime - animatedStopTime ) )
      {
        RollbackAnimations();
      }
    }
#endif // VISUAL_CUTTED

    return animatedTime >= lifeTime;
  }

  //////////////////////////////////////////////////////////////////////////
  void PFApplFly::UpdateLifeTime( float newLifeTime )
  {
    lifeTime = newLifeTime + animatedTime;
  }

  //////////////////////////////////////////////////////////////////////////
  bool PFApplAttract::Start()
  {
    if ( PFBaseApplicator::Start() )
    {
      return true;
    }

    CPtr<PFBaseMovingUnit> pSenderUnit = dynamic_cast<PFBaseMovingUnit*>( GetAbilityOwner().GetPtr() );
    CPtr<PFBaseMovingUnit> pTargetUnit = dynamic_cast<PFBaseMovingUnit*>( pReceiver.GetPtr() );
    NI_VERIFY( IsUnitValid( pSenderUnit ), "Sender must be moving units!", return true; );
    if ( !IsUnitValid( pTargetUnit ) )
    {
      NotifyParent( NDb::PARENTNOTIFICATION_CANCEL );
      return true;
    }

    const float distance = GetDB().distance;

    CVec2 dir = pTargetUnit->GetPosition().AsVec2D() - pSenderUnit->GetPosition().AsVec2D();
    if ( fabs2( dir ) < fabs2( distance ) )
    {
      return true;
    }

    Normalize( &dir );
    dir *= distance;

    pTargetUnit->TeleportTo( pSenderUnit->GetPosition().AsVec2D() + dir, true, false );

    pTargetUnit->EventHappened( PFBaseUnitApplicatorEvent( NDb::BASEUNITEVENT_FORCEDMOVE, this ) );

    return true; //done
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplAttract::Step(float dtInSeconds)
  {
    NI_ALWAYS_ASSERT("Must never get here");
    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplAttackTarget::DoAttack()
  {
    // Skip if target is invalid
    if (!IsUnitValid(pTarget2Attack) || pTarget2Attack->IsMounted() )
    {
      if (IsValid(pParent))
        pParent->OnNotification(*this, NDb::PARENTNOTIFICATION_CANCEL);
      return false;
    }

    // Если на момент применения аппликатора цель - союзник, то считаем, что мы можем атаковать союзника.
    const bool canAttackAlly = pReceiver->GetFaction() == pTarget2Attack->GetFaction();

    if ( (pReceiver->IsIdle() || pReceiver->GetCurrentTarget() != pTarget2Attack) && pReceiver->CanAttackTarget( pTarget2Attack, canAttackAlly ) )
    {
      if ( !pReceiver->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDMOVE) && !pReceiver->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK) )
      {
        CPtr<PFBaseMovingUnit> pReceiverAsMovingUnit(static_cast<PFBaseMovingUnit*>(pReceiver.GetPtr()));
        pReceiver->DropStates();
        pReceiver->PushState( new PFBaseUnitAttackState(pReceiver->GetWorld(), pReceiverAsMovingUnit, pTarget2Attack, true, true, GetDB().ignoreVisibility, canAttackAlly) );
      }
    }

    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplAttackTarget::Start()
  {
    if (PFApplBuff::Start())
      return true;

    if ( !IsEnabled() )
      return true; // don't attack

    // Fill target unit pointer
    Target tgt;
    MakeApplicationTarget(tgt, GetDB().attackTarget);
    NI_VERIFY(tgt.IsUnit(), "Trying to attack on non-unit target", return true; );

    NI_VERIFY(tgt.GetUnit() != pReceiver, ErrorStr("Attack target applicator can't direct to attack self"), return true; );

    pTarget2Attack = tgt.GetUnit();

    // Attach to base unit as event listener to a target
    pTarget2Attack->AddEventListener(this);

    NI_VERIFY(dynamic_cast<PFBaseMovingUnit*>(pReceiver.GetPtr()), ErrorStr("Attack Target applicator is applied to non PFBaseMovingUnit"), return true; );

    return !DoAttack();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  unsigned int PFApplAttackTarget::OnEvent(const PFBaseUnitEvent *pEvent)
  {
    if (!pParent)
      return 0;

    if (pEvent->GetType() != NDb::BASEUNITEVENT_DISPATCHAPPLIED &&
      pEvent->GetType() != NDb::BASEUNITEVENT_DISPATCHEVADED)
      return 0;

    const PFBaseUnitDispatchEvent *pDispatchEvent = static_cast<const PFBaseUnitDispatchEvent*>(pEvent);
    if (pParent && pDispatchEvent->GetDispatch()->GetSender() == pReceiver)
    {
      if (pEvent->GetType() == NDb::BASEUNITEVENT_DISPATCHAPPLIED)
        event2Send = NDb::PARENTNOTIFICATION_DONE;
      else
        event2Send = NDb::PARENTNOTIFICATION_CANCEL;
    }

    return 0;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplAttackTarget::Step(float dtInSeconds)
  {
    if (PFApplBuff::Step(dtInSeconds))
      return true;

    if (event2Send != NDb::PARENTNOTIFICATION_NA)
      return true;

    return !DoAttack();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFApplAttackTarget::Stop()
  {
    if (IsValid(pParent))
    {
      if (event2Send != NDb::PARENTNOTIFICATION_NA)
      {
        pParent->OnNotification(*this, event2Send);
      }
      else
      {
        if (pReceiver->IsDead())
          pParent->OnNotification(*this, NDb::PARENTNOTIFICATION_CANCEL);
        else
          pParent->OnNotification(*this, NDb::PARENTNOTIFICATION_DONE);
      }
    }

    // Attach to base unit as event listener
    if (IsValid(pTarget2Attack))
      pTarget2Attack->RemoveEventListener(this);

    PFApplBuff::Stop();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFApplAttackTarget::DumpInfo(NLogg::CChannelLogger &logger) const
  {
    PFBaseApplicator::DumpInfo(logger);

    Target tgt;
    MakeApplicationTarget(tgt, GetDB().attackTarget);
    LogLogicInfo(logger)("      attack target: %s\n", MakeTargetString(tgt));
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFApplTeleport::Start()
  {
    if ( PFBaseApplicator::Start() )
    {
      return true;
    }

    if ( pReceiver->CheckFlag( NDb::UNITFLAG_FORBIDMOVESPECIAL ) )
    {
      NotifyParent( NDb::PARENTNOTIFICATION_CANCEL );
      return true;
    }

    CDynamicCast<PFBaseMovingUnit> pMovingUnit( pReceiver.GetPtr() );
    NI_VERIFY( pMovingUnit, ErrorStr( "applying to nonmoving unit" ), return true );

    // Teleport unit
    Target targ;
    MakeApplicationTarget( targ, GetDB().teleportTarget );

    if ( !targ.IsValid() )
    {
      NotifyParent( NDb::PARENTNOTIFICATION_CANCEL );
      return true;
    }

    CVec2 teleportPos = targ.AcquirePosition().AsVec2D();

    float maxDist = RetrieveParam( GetDB().maxDistance, 0.0f );
    if ( maxDist > 0.0f )
    {
      const CVec2& curPos = pReceiver->GetPosition().AsVec2D();
      CVec2 dir = teleportPos - curPos;
      float dist = fabs( dir );
      if ( dist > maxDist )
      {
        // Correct teleport pos
        dir = curPos + dir * maxDist / dist;
        teleportPos.x = dir.x;
        teleportPos.y = dir.y;
      }
    }

    // Play effects
    NGameX::PlayEffect(pReceiver, NDb::Ptr<NDb::EffectBase>( GetDB().disappearEffect ), GetAbilityOwner(), pReceiver, this );

    if ( GetDB().pushUnits )
    {
      pMovingUnit->PlaceUnitWithPush( teleportPos, pMovingUnit->GetObjectSize() );
      
      if(GetDB().notifyInboundDispatches)
      {
        pMovingUnit->NotifyDispatchesOnTargetTeleport();
      }
    }
    else
    {
      pMovingUnit->TeleportTo( teleportPos, true, GetDB().notifyInboundDispatches );
    }

    if ( pReceiver->IsTrueHero() )
    {
      GetWorld()->GetStatistics()->NotifyTeleportByAbility( pMovingUnit.GetPtr(), GetAbility()->GetData()->GetDBDesc() );
    }

    // Play effects
    NGameX::PlayEffect( pReceiver, NDb::Ptr<NDb::EffectBase>( GetDB().appearEffect ), GetAbilityOwner(), pReceiver, this );

    return true; //done
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool PFApplGhostMove::Start()
  {
    if ( Base::Start() )
      return true;

    NI_VERIFY(IsUnitValid(pReceiver), "Invalid unit", return true);

    PFBaseMovingUnit *pMovingUnit = dynamic_cast<PFBaseMovingUnit *>(pReceiver.GetPtr());

    NI_VERIFY(NULL != pMovingUnit, "Invalid unit", return true);

    ghostMoveIndex = pMovingUnit->SetGhostMode( GetDB().collisionFlags, false );

    return false;
  }

  void PFApplGhostMove::Stop()
  {

    NI_VERIFY(IsValid(pReceiver), "Invalid unit", return);

    PFBaseMovingUnit *pMovingUnit = dynamic_cast<PFBaseMovingUnit *>(pReceiver.GetPtr());

    NI_VERIFY(NULL != pMovingUnit, "Invalid unit", return);

    if ( ghostMoveIndex > -1 )
    {
      pMovingUnit->ResetGhostMode( ghostMoveIndex );
      ghostMoveIndex = -1;
    }

    if (!pMovingUnit->IsDead())
    {
      if ( GetDB().pushUnits )
      {
        pMovingUnit->PlaceUnitWithPush( pMovingUnit->GetPosition().AsVec2D(), pMovingUnit->GetObjectSize(), true, false );
      }
      else
      {
        pMovingUnit->TeleportTo( pMovingUnit->GetPosition().AsVec2D(), true, false );
      } 
    }
    Base::Stop();
  }

}

REGISTER_WORLD_OBJECT_NM(PFApplMoveTo,                NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplKickAway,              NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplShift,                 NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplThrow,                 NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplGhostMove,             NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplAttract,               NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplAttackTarget,          NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplTeleport,              NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplFly,                   NWorld);

#include "stdafx.h"
#include "PFHeroStates.h"
#include "PFBaseUnitStates.h"
#include "PFFlagpole.h"
#include "PFHero.h"
#include "PFMaleHero.h"
#include "PFClientHero.h"
#include "PFPickupable.h"
#include "PFConsumable.h"
#include "PFAbilityData.h"
#include "PFAbilityInstance.h"
#include "PFAIWorld.h"
#include "PFTalent.h"
#include "PathChecker.h"

#include "DBConsumable.h"

#include "RegionPointChecker.h"

#ifndef VISUAL_CUTTED
#include "PFMinigamePlace.h"
#endif

#include "AdventureScreen.h"  // For TempDebugTrace. Remove, when unneeded

namespace NWorld
{

  //////////////////////////////////////////////////////////////////////////
  //PFBaseUseHeroState
  //////////////////////////////////////////////////////////////////////////
  void PFBaseUseHeroState::OnEnter()
  {
    if ( !IsUnitValid( hero ) )
    {
      return;
    }

    if ( target.IsUnit() && ( !IsUnitValid( target.GetUnit() ) || !target.GetUnit()->IsVisibleForFaction( hero->GetFaction() ) ) )
    {
      return;
    }

    if ( ( GetAbilityFlags() & NDb::ABILITYFLAGS_WAITFORCHANNELING ) != 0 )
    {
      waitForChanneling = true;
    }

    wasInvisible = !pOwner->IsVisibleForEnemy( hero->GetFaction() );

    bool needToGetClose = NeedToGetClose();

    if ( needToGetClose && hero->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) )
    {
      return;
    }

    const float range = GetUseRange();
    if ( range < 0 )
      return;

    PlayAskSound();

    if ( needToGetClose )
    {
      // TODO: should use "get close to target" state
      approachRequired = true;
      if ( target.IsUnit() )
      {
        PushState( new PFBaseUnitChaseState(hero, IsRequireLineOfSight(), range, 1e10f, target.GetUnit(), true ) );
      }
      else 
      {
        PushState( new PFBaseUnitMoveToState( hero, target.AcquirePosition().AsVec2D(), range, IsRequireLineOfSight() ) );
      }
    }
  }

  void PFBaseUseHeroState::OnAfterLeave()
  {
    // proceed momentary logic only on successfull use
    if ( IsValid( pAbilityInstance ) && !hero->HasQueuedStates() )
    {
      const bool abilityMovesCaster = (GetAbilityFlags() & NDb::ABILITYFLAGS_MOVING) != 0;

      if ( target.IsUnit() )
      {
        if ( approachRequired || abilityMovesCaster || wasInvisible )
        {
          CPtr<PFBaseUnit> const& pTargetUnit = target.GetUnit();
          if ( IsValid( pTargetUnit ) )
          {
            if ( pTargetUnit->GetFaction() != hero->GetFaction() && (GetAbilityFlags() & NDb::ABILITYFLAGS_STAYINVISIBLE) == 0 )
            {
              if ( hero->CanAttackTarget( pTargetUnit ) )
              {
                hero->OnTarget( pTargetUnit, true );
              }
            }
            else if ( !approachRequired && !wasInvisible )
            {
              hero->Cleanup();
            }
          }
        }
      }
      else if ( abilityMovesCaster )
      {
        CPtr<PFBaseUnit> pTargetUnit = hero->FindTarget( hero->GetTargetingRange(), true );
        if ( IsUnitValid( pTargetUnit ) )
        {
          hero->Cleanup();
        }
      }
    }
  }

  PFBaseUseHeroState::PFBaseUseHeroState( PFBaseMaleHero * _owner, Target const& _target )
    : PFBaseUseState (_owner, _target)
    , hero(_owner)
    , approachRequired(false)
    , waitForChanneling(false)
    , wasInvisible(false)
  {
  }

  bool PFBaseUseHeroState::CanIgnoreVisibility() const
  {
    const NDb::Ability* dbAbility = GetDBDesc();
    if (!dbAbility)
      return false;

    if ((dbAbility->targetType & NDb::SPELLTARGET_VISIBLETARGETSONLY) != 0)
      return false;

    return true;
  }

  bool PFBaseUseHeroState::IsRequireLineOfSight() const
  {
    return GetDBDesc() ? GetDBDesc()->requireLineOfSight : false;
  }

  bool PFBaseUseHeroState::NeedToGetClose() const
  {
    bool needToGetClose = PFBaseUseState::NeedToGetClose();

    if (!needToGetClose && IsRequireLineOfSight())
    {
      needToGetClose = !hero->CanSee( target.AcquirePosition() );
    }

    return needToGetClose;
  }

  //////////////////////////////////////////////////////////////////////////
  //PFHeroUseConsumableState
  //////////////////////////////////////////////////////////////////////////
  PFHeroUseConsumableState::PFHeroUseConsumableState( PFBaseMaleHero * _pOwner, int _slot, Target const& _target )
    : PFBaseUseHeroState( _pOwner, _target )
    , slot( _slot )
    , pDBDesc( GetConsumable() ? GetConsumable()->GetDBDesc() : 0 )
  {
  }

  bool PFHeroUseConsumableState::OnStep( float dt )
  {
    if ( !IsUnitValid( pOwner ) )
    {
      return true;
    }

    // no target validation if ability instance is already started
    if ( !pAbilityInstance && ( !target.IsValid() || ( NeedToGetClose() && hero->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) ) ) )
    {
      // don't stop hero being moved special
      if ( !hero->IsMovingSpecial() )
      {
        hero->Stop();
      }
      return true;
    }

    FSMStep( dt );

    if ( GetCurrentState() )
    {
      return false;
    }

    bool useFailed = false;
    if ( !pAbilityInstance )
    {

      const PFConsumable* consumable = GetConsumable();
      if ( !consumable || !IsValid( consumable->GetAbility() ) || consumable->GetAbility()->IsAbilitySupposedToStopUnit() )
      {
        if ( hero->IsMoving() && !hero->IsMovingSpecial() )
        {
          hero->Stop();
        }
      }

      // is consumable can be actually used
      if ( !hero->CanUseConsumable( slot ) || NeedToGetClose() || ( target.IsUnit() && !target.GetUnit()->IsVisibleForFaction( hero->GetFaction() ) ) )
        return true;

      pAbilityInstance = hero->UseConsumable( slot, target, hero->IsLocal() ); // use artifact

      if ( !pAbilityInstance )
      {
        useFailed = true;
      }
    }

    if ( waitForChanneling && IsCastFinished() && dt > 0.0f )
    {
      waitForChanneling = false;
    }

    return ( !waitForChanneling && IsCastFinished() ) || useFailed;
  }


  float PFHeroUseConsumableState::GetUseRange() const
  {
    PFConsumable const* pConsumable = hero->GetConsumable( slot );
    if ( !pConsumable )
    {
      return -1;
    }

    const NDb::AlternativeTarget* const & pDBAltTarget = target.GetDBAlternativeTarget();
    if ( pDBAltTarget && pDBAltTarget->alternativeActivity )
      return pDBAltTarget->alternativeActivity->useRange( pOwner, pOwner, pConsumable->GetAbility() );

    return pConsumable->GetAbility()->GetUseRange();
  }

  NDb::Ability const* PFHeroUseConsumableState::GetDBDesc() const
  {
    return pDBDesc.GetPtr();
  }

  const PFConsumable * PFHeroUseConsumableState::GetConsumable() const
  {
    return IsUnitValid( hero ) ?  hero->GetConsumable( slot ) : NULL;
  }
  //////////////////////////////////////////////////////////////////////////
  //PFHeroUseTalentState
  //////////////////////////////////////////////////////////////////////////
  PFHeroUseTalentState::PFHeroUseTalentState( PFBaseMaleHero * _pOwner, PFTalent * _talent, Target const& _target )
    : PFBaseUseHeroState( _pOwner, _target )
    , talent( _talent)
  {
  }

  void PFHeroUseTalentState::OnEnter()
  {
    TempDebugTrace(NStr::StrFmt("PFHeroUseTalentState::OnEnter()"));
    PFBaseUseHeroState::OnEnter();
  }

  void PFHeroUseTalentState::OnLeave()
  {
    TempDebugTrace(NStr::StrFmt("PFHeroUseTalentState::OnLeave()"));
    PFBaseUseHeroState::OnLeave();
  }

  bool PFHeroUseTalentState::OnStep( float dt )
  {
    if ( !IsUnitValid( hero ) )
    {
      return true;
    }

    // no target validation if ability instance is already started
    if ( !pAbilityInstance && ( !target.IsValid() || ( NeedToGetClose() && hero->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) ) ) )
    {
      // don't stop hero being moved special
      if ( !hero->IsMovingSpecial() )
      {
        hero->Stop();
      }
      return true;
    }

    FSMStep( dt );

    if ( GetCurrentState() )
    {
      return false;
    }

    if ( !pAbilityInstance )
    {
      bool canUseTalent = hero->CanUseTalent( talent );
      // is talent can be actually used
      bool isTargetVisible = !target.IsUnit() || target.GetUnit()->IsVisibleForFaction( hero->GetFaction() );
      if ( !canUseTalent )
      {
        hero->Stop();
        return true;
      }
      if ( NeedToGetClose() )
      {
        return true;
      }
      if (!isTargetVisible && !CanIgnoreVisibility())
      {
        return true;
      }

      if ( !IsValid(talent) || talent->IsAbilitySupposedToStopUnit() )
      {
        if ( hero->IsMoving() && !hero->IsMovingSpecial() )
        {
          hero->Stop();
        }
      }

      pAbilityInstance = hero->UseTalent( talent, target );
      if ( !pAbilityInstance )
      {
        // cast failed
        return true;
      }
    }

    if ( IsValid(talent) && talent->IsMultiState() && !talent->IsOn() && pAbilityInstance->IsActivated() )
    {
      // toggle off
      return true;
    }

    bool isAbilityFinished = IsCastFinished();
    if ( IsValid(talent) && !talent->GetDBDesc()->isUnitFreeAfterCast )
    {
      isAbilityFinished = IsAbilityFinished();
    }

    if ( waitForChanneling && isAbilityFinished && dt > 0.0f )
    {
      waitForChanneling = false;
    }

    return !waitForChanneling && isAbilityFinished;
  }

  float PFHeroUseTalentState::GetUseRange() const
  {
    if ( !IsValid(talent) )
    {
      return -1;
    }
    const NDb::AlternativeTarget* const & pDBAltTarget = target.GetDBAlternativeTarget();
    if ( pDBAltTarget && pDBAltTarget->alternativeActivity )
      return pDBAltTarget->alternativeActivity->useRange( pOwner, pOwner, talent );

    return talent->GetUseRange(target);
  }

  void PFHeroUseTalentState::PlayAskSound()
  {
    if ( IsValid( talent ) )
    {
      PFBaseHero const * pTargetHero = 0;
      if (target.IsUnit())
        pTargetHero = dynamic_cast<PFBaseHero const *>(target.GetUnit().GetPtr());

      talent->PlayAck( pTargetHero );
    }
  }


  NDb::Ability const* PFHeroUseTalentState::GetDBDesc() const
  {
    return IsValid(talent)? talent->GetDBDesc() : 0;
  }
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  PFHeroPickupObjectState::PFHeroPickupObjectState( PFBaseHero* _pOwner, PFPickupableObjectBase* _pPickupable )
    : PFInteractObjectState( _pOwner, Target( _pPickupable ) )
    , pPickupable( _pPickupable )
  {
    NI_VERIFY( IsValid( pPickupable ), "Object is not pickapable, or can not be founded in the world!", return );

    if ( IsValid( pOwner ) )
    {
      if ( pPickupable->GetPickupAbility() )
      {
        const NDb::Ability* pDBAbility = pPickupable->GetPickupAbility();
        CObj<PFAbilityData> pAbility = new PFAbilityData( pOwner.GetPtr(), pDBAbility, NDb::ABILITYTYPEID_SPECIAL );

        range = pDBAbility->useRange(pOwner, pPickupable, pAbility, 0.0f);
      }
      else
      {
        range = pOwner->GetWorld()->GetAIWorld()->GetAIParameters().pickupItemRange;
      }
    }
  }

  void PFHeroPickupObjectState::DoAction()
  {
    if ( pPickupable->GetPickupAbility() )
    {
      NDb::Ability const* pDBAbility = pPickupable->GetPickupAbility();

      pActionInstance = pOwner->UseExternalAbility( pDBAbility, Target(pPickupable) );
      pOwner->EventHappened( PFBaseUnitAbilityStartEvent( pActionInstance.GetPtr() ) );
    }
    else
    {
      pPickupable->PickUp( pOwner );
    }
  }

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  PFHeroFollowUnitState::PFHeroFollowUnitState(CPtr<PFBaseHero> const& pOwner, CPtr<PFBaseUnit> const& pUnit, float range, float forceRange) 
    : HeroStateFSM(pOwner)
    , pUnit(pUnit) 
    , followRange(0.0f)
    , forceFollowRange(0)
    , moveInitiated(false)
  {
    if( IsValid(pOwner) )
    {
      if( range <= 0 )
        range = pOwner->GetWorld()->GetAIWorld()->GetAIParameters().followRange;
      //    else if( IsValid(pUnit) && pUnit->UnitCheck(UNITCHECKID_ISBUILDING)) -- UnitCheck is buggy
      else if( IsValid(pUnit) && dynamic_cast<PFBuilding*>(pUnit.GetPtr()) )
        range = 2.0;
      followRange = range;

      if ( forceRange > 0 && forceRange < range )
        forceRange = range;

      forceFollowRange = forceRange;
    }
  }

  void PFHeroFollowUnitState::OnLeave()
  {
    if( moveInitiated && IsUnitValid( pOwner ) )
      pOwner->Stop();
  }

  bool PFHeroFollowUnitState::OnStep(float dt)
  {
    if( !IsUnitValid( pUnit ) || !IsUnitValid( pOwner ) )
      return true;
    if( pOwner->IsMounted() )  // unit becomes mounted -> drop followed target
      return true;

    FSMStep(dt);

    if ( forceFollowRange > 0 )
    {
      if ( !pOwner->IsTargetInRange( pUnit, forceFollowRange ) )
      {
        DoMove();
        return false;
      }
    }

    CPtr<PFBaseUnit> pTarget = pUnit->GetCurrentTarget();
    if( pCurrentTarget != pTarget && GetCurrentState() )
      Cleanup();

    bool strongTarget = true;

    if( !IsTargetValid( pTarget ) )
    {
      pTarget = pOwner->FindTarget( pOwner->GetTargetingRange() );

      strongTarget = false;
    }

    pCurrentTarget = pTarget;

    if( NULL == GetCurrentState() )
    {
      if ( IsTargetValid(pTarget) && pTarget->GetFaction() != pOwner->GetFaction() && pOwner->CanSelectTarget( pTarget, true ) )
      {
        if( false == pOwner->CheckFlag( NDb::UNITFLAG_FORBIDSELECTTARGET) ) 
        {
          PushState( new PFBaseUnitAttackState( pOwner->GetWorld(), pOwner.GetPtr(), pTarget, strongTarget, true ) );
        }
      }
      else
      {
        if ( !pOwner->IsTargetInRange( pUnit, followRange ) )
          DoMove();
        else
        {
          pOwner->Stop();
          moveInitiated = false;
        }

      }
    }

    return false;
  }

  void NWorld::PFHeroFollowUnitState::DoMove()
  {
    moveInitiated = true;
    CObj<IPointChecking> pChecking = new ObjectRangeChecking( pUnit, pOwner, followRange );
    pOwner->MoveTo( pUnit, 0, pChecking );
  }


  PFHeroHoldState::PFHeroHoldState( CPtr<PFWorld> const& pWorld, CPtr<PFBaseHero> const& pOwner, bool stopOnEnter /*= true*/ )
    : HeroStateFSM( pOwner )
    , pWorld(pWorld)
    , doStopOnEnter(stopOnEnter)
  {
  }

  bool PFHeroHoldState::IsOwnerSuitable() const
  {
    return IsUnitValid( pOwner ) && !pOwner->IsMounted();
  }

  bool PFHeroHoldState::OnStep(float dt)
  {
    if( !IsOwnerSuitable() )
      return true;

    if(  !GetCurrentState()
      && !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDATTACK)
      && !pOwner->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDAUTOATTACK)  )
    {
      CPtr<PFBaseUnit> const& pTarget = pOwner->FindTarget( pOwner->GetAttackRange() );
      if(IsTargetValid(pTarget))
      {
        pOwner->PushState( new PFBaseUnitAttackState(pWorld, CPtr<PFBaseMovingUnit>(pOwner.GetPtr()), pTarget) );
      }
    }

    if(pOwner->IsMoving())
      return true;

    return false;
  }

  void PFHeroHoldState::OnEnter() 
  {

    if( IsOwnerSuitable() )
    {
      pOwner->OnHold(true);

      if(doStopOnEnter)
      {
        pOwner->Stop();
      }

      pOwner->Idle();
    }
  }

  void PFHeroHoldState::OnLeave() 
  {
    if( IsValid( pOwner ) )
    {
      pOwner->OnHold(false);
    }
  }

  //////////////////////////////////////////////////////////////////////////
  PFHeroUseUnitState::PFHeroUseUnitState( PFBaseHero* _pOwner, PFBaseUnit* _pUnit )
    : PFInteractObjectState( _pOwner, Target( _pUnit ) )
    , pUnit( _pUnit )
  {
    range = pUnit->GetUseRange( _pOwner );
  }

  void PFHeroUseUnitState::DoAction()
  {
    if ( !pOwner->CheckFlagType( NDb::UNITFLAGTYPE_FORBIDINTERACT ) )
      pActionInstance = pUnit->Use( pOwner );
  }

  //////////////////////////////////////////////////////////////////////////
  PFCreatureRaiseFlagState::PFCreatureRaiseFlagState( PFBaseHero* _pOwner, PFFlagpole* _pFlagpole ) 
    : PFInteractObjectState( _pOwner, Target( _pFlagpole ) )
    , pFlagpole(_pFlagpole)
  {
    NDb::Ptr<NDb::Ability> const& pDBAbility = _pOwner->GetWorld()->GetAIWorld()->GetAIParameters().raiseFlagAbility;

    CObj<PFAbilityData> pAbility = new PFAbilityData( _pOwner, pDBAbility, NDb::ABILITYTYPEID_SPECIAL);
    range = pDBAbility->useRange(_pOwner, pFlagpole, pAbility, 0.0f);
  }

  void PFCreatureRaiseFlagState::DoAction()
  {
    if (pFlagpole->GetFaction() != NDb::FACTION_NEUTRAL)
      return;

    NDb::Ptr<NDb::Ability> const& pDBAbility = pOwner->GetWorld()->GetAIWorld()->GetAIParameters().raiseFlagAbility;

    pActionInstance = pOwner->UseExternalAbility(pDBAbility, target);
    pOwner->EventHappened( PFBaseUnitAbilityStartEvent( pActionInstance.GetPtr() ) );
  }

  //////////////////////////////////////////////////////////////////////////
  PFInteractObjectState::PFInteractObjectState( PFBaseHero * _pOwner, const Target& _target )
    : HeroStateFSM( _pOwner )
    , target(_target)
    , range(0.0f)
    , used(false)
  {
    if ( target.IsUnitValid() )
    {
      if ( PFBuilding* pBuilding = dynamic_cast<PFBuilding*>(target.GetUnit().GetPtr()) )
      {
        pointChecking = new RegionPointChecker( GetWorld(), pBuilding->GetOccupiedTiles(), pOwner->GetObjectTileSize()+1 );
      }
    }
  }

  void PFInteractObjectState::OnEnter()
  {
    if ( !IsUnitValid( pOwner ) || !target.IsValid() )
      return;

    if ( !IsObjectInRange() )
    {
      ApproachObject();
    }
  }

  bool PFInteractObjectState::IsObjectInRange() const
  {
    if ( pointChecking )
    {
      TileMap * tileMap = GetWorld()->GetTileMap();
      return pointChecking->IsGoodTile( tileMap->GetTile( pOwner->GetPosition().AsVec2D() ) );
    }

    return pOwner->IsTargetInRange( target, range );
  }

  void PFInteractObjectState::ApproachObject()
  {
    if ( target.IsUnit() )
    {
      PFBaseUnit* pUnit = target.GetUnit();
      if ( IsUnitValid( pUnit ) )
      {
        if ( pointChecking )
        {
          PushState( new PFBaseUnitMoveToBuildingState( pOwner, pUnit, pointChecking ) );
        }
        else if ( pUnit->IsVisibleForFaction( pOwner->GetFaction() ) )
        {
          PushState( new PFBaseUnitChaseState( pOwner.GetPtr(), true, range, 0.0f, pUnit, true ) );
        }
      }
    }
    else 
    {
      PushState( new PFBaseUnitMoveToState( pOwner.GetPtr(), target.AcquirePosition().AsVec2D(), range ) );
    }
  }

  void PFInteractObjectState::NeedStopOnLeave( bool val )
  {
    if ( GetCurrentState() )
    {
      if ( PFBaseUnitMoveToBuildingState* st = dynamic_cast<PFBaseUnitMoveToBuildingState*>(GetCurrentState()) )
      {
        st->NeedStopOnLeave( val );
      }
    }
  }

  bool PFInteractObjectState::OnStep( float dt )
  {
    if ( !IsUnitValid( pOwner ) || !target.IsValid() )
      return true;

    FSMStep( dt );

    if ( GetCurrentState() )
      return false;

    if ( !used && IsObjectInRange() )
    {
      used = true;

      if ( pOwner->IsMoving() && !pOwner->IsMovingSpecial() )
      {
        pOwner->Stop();
      }

      DoAction();

      return false;
    }

    return IsActionFinished();
  }

  void PFInteractObjectState::OnLeave()
  {
    HeroStateFSM::OnLeave();

    if ( pActionInstance && IsValid(pOwner) )
      pOwner->EventHappened( PFBaseUnitEvent( NDb::BASEUNITEVENT_CHANNELINGCANCELED ) );
  }

  // Есть в PFBaseUseState
  bool PFInteractObjectState::IsActionFinished() const
  {
    return pActionInstance ? pActionInstance->IsActivated() && !pOwner->IsInChannelling() : true;
  }

  // Нужно?
  bool PFInteractObjectState::CanBeInterrupted() const
  {
    if ( pActionInstance )
      return !IsActionFinished();

    return HeroStateFSM::CanBeInterrupted();
  }

  ///////////////////////////////////////////////////////////////////////////////

  PFHeroSuspendState::PFHeroSuspendState( CPtr<PFBaseHero> const& pOwner, bool isLongSuspend )
    : HeroStateFSM( pOwner )
    , isSuspendLong(isLongSuspend)
    , suspendTimeout(0.f)
    , waitTime(0.f)
  {
  }

  PFHeroSuspendState::PFHeroSuspendState()
    : suspendTimeout(0.f)
    , waitTime(0.f)
    , isSuspendLong(false)
  { }

  bool PFHeroSuspendState::OnStep( float dt )
  {
    if( false == IsOwnerSuitable() )
      return true;

    waitTime += dt;

    if( suspendTimeout <= waitTime)
    {
      return true;
    }

    return false;
  }

  void PFHeroSuspendState::OnEnter()
  {
    if(IsOwnerSuitable())
    {
      const NDb::UnitTargetingParameters& tergetingParams = pOwner->GetTargetingParams();
      if(isSuspendLong)
        suspendTimeout = tergetingParams.longSuspendTimeout;
      else
        suspendTimeout = tergetingParams.sortSuspendTimeout;

      //pOwner->OnHold(true);
    }

  }

  void PFHeroSuspendState::OnLeave()
  {
    if(IsOwnerSuitable())
    {
      //pOwner->OnHold(false);
      pOwner->OnAfterSuspend(isSuspendLong);
    }
  }

  bool PFHeroSuspendState::IsOwnerSuitable() const
  {
    if(IsUnitValid(pOwner) && !pOwner->IsMounted())
      return true;

    return false;
  }

} // namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFHeroUseConsumableState,  NWorld)
REGISTER_WORLD_OBJECT_NM(PFHeroPickupObjectState,   NWorld)
REGISTER_WORLD_OBJECT_NM(PFHeroFollowUnitState,     NWorld)
REGISTER_WORLD_OBJECT_NM(PFHeroHoldState,           NWorld)
REGISTER_WORLD_OBJECT_NM(PFHeroUseTalentState,      NWorld)
REGISTER_WORLD_OBJECT_NM(PFHeroUseUnitState,        NWorld)
REGISTER_WORLD_OBJECT_NM(PFCreatureRaiseFlagState,  NWorld)
REGISTER_WORLD_OBJECT_NM(PFInteractObjectState,     NWorld)
REGISTER_WORLD_OBJECT_NM(PFHeroSuspendState,        NWorld)


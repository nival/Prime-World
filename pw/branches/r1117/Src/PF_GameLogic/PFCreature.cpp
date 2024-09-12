#include "stdafx.h"
#include "PFCreature.h"
#include "PFDeadBody.h"
#include "PFAIWorld.h"

#include "PFBaseUnitStates.h"
#include "PFAbilityData.h"
#include "PFAbilityInstance.h"

#ifndef VISUAL_CUTTED
#include "PFClientCreature.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

#include "ClientVisibilityHelper.h"

namespace NWorld
{

PFCreature::PFCreature(PFWorld* pWorld, const CVec3 &pos, const CVec2 & direction, const NDb::Creature &unitDesc)
  : PFBaseMovingUnit(pWorld, pos, direction, unitDesc)
  , unitFallUndergroundOffset(-1)
  , deadUnitLifeTime(-1)
  , observingTimeOffset(-1)
  , forcedAnimationTimeLeft(0.f)
{
  NI_DATA_VERIFY(IsValid(unitDesc.deathParameters), "Death parameters are not setted", return)
}


void PFCreature::Reset()
{
  PFBaseMovingUnit::Reset();
}

void PFCreature::OnAfterReset()
{
  PFBaseMovingUnit::OnAfterReset();

}

bool PFCreature::UpdateClientColor()
{
  if (PFBaseMovingUnit::UpdateClientColor())
    return true;

  const NDb::Creature* creepObj = dynamic_cast<const NDb::Creature*> (dbUnitDesc.GetPtr());
  if ( creepObj && creepObj->recolor.A > 0.0f )
  {
    CALL_CLIENT_1ARGS( Recolor, creepObj->recolor );
    return true;
  }

  return false;
}

bool PFCreature::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION;

  PFBaseMovingUnit::Step(dtInSeconds);
  
	const bool isDead = IsDead();

  if (isDead)
  {
    observingTimeOffset -= dtInSeconds;

    if ( unitFallUndergroundOffset  >= 0 && ( unitFallUndergroundOffset -= dtInSeconds ) < 0 )
    {
      if ( deadUnitLifeTime > 0 )
      {
        NI_DATA_VERIFY(GetDeathParams(), "Death parameters are not setted", return false)
        CALL_CLIENT_1ARGS(StartFallThrough, GetDeathParams()->fallSpeed );
      }
    }
    if ( deadUnitLifeTime >= 0 && ( deadUnitLifeTime-= dtInSeconds ) < 0 )
    {
      RemoveCorpse();
    }
  }
  else
  {
    CALL_CLIENT_1ARGS(SetMoveSpeed, GetUnitSpeed());
    CALL_CLIENT_1ARGS(SetAttackSpeed, GetAttackSpeedInternal());
  }

  if ( forcedAnimationTimeLeft > 0 )
  {
    forcedAnimationTimeLeft -= dtInSeconds;
    if ( forcedAnimationTimeLeft < EPS_VALUE )
    {
      StopForcedAnimation( false );
    }
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreature::OnUnitDie( CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
  PFBaseMovingUnit::OnUnitDie(pKiller, flags, pDamageDesc);

  NI_DATA_VERIFY(GetDeathParams(), "Death parameters are not setted", return;)

  observingTimeOffset = GetDeathParams()->observeOffset;

  if ( (flags & UNITDIEFLAGS_FORCEREMOVECORPSE) == UNITDIEFLAGS_FORCEREMOVECORPSE )
  {
    RemoveCorpse();
  }
  else
  {
    if ( (flags & UNITDIEFLAGS_UNSUMMON) == UNITDIEFLAGS_UNSUMMON)
      deadUnitLifeTime = GetDeathParams()->unsummonTime;
    else
      deadUnitLifeTime = GetDeathParams()->deathTime;
    
    if ( (flags & UNITDIEFLAGS_DONTPLAYDEATHANIMATION) == 0 && (flags & UNITDIEFLAGS_DEFERREDDEATH) == 0 )
    {
      if ( (flags & UNITDIEFLAGS_UNSUMMON) != UNITDIEFLAGS_UNSUMMON )
      {
        unitFallUndergroundOffset = GetDeathParams()->fallOffset;
        NI_ASSERT( unitFallUndergroundOffset <= deadUnitLifeTime, "Parameter unitFallUndergroundOffset delay in GameLogic/AILogic.AILP must be more or equal then deadUnitLifeTime!" );

        PlaceSkeleton( NGameX::ClientVisibilityHelper::IsVisibleForPlayer(this) );
      }
    }
  }
}

void PFCreature::OnRessurect()
{
  PFCreatureResurrectEvent evtResurrect;
  EventHappened( evtResurrect );
  DropAbilitiesProgress();
}

void PFCreature::PlaceSkeleton(bool playOnUnitDieEffect)
{
  NI_DATA_VERIFY(GetDeathParams(), "Death parameters are not setted", return;)
  PFDeadBody::Make( GetWorld(), GetPosition(), ClientObject(), GetDeathParams()->effect, GetDeathParams()->effectOffset, playOnUnitDieEffect );
}

int  PFCreature::ReplaceAnimSet( NDb::Ptr<NDb::AnimSet> pSet ) 
{
  return IsValid(ClientObject())? ClientObject()->ReplaceAnimSet(pSet): -1; 
} 

void PFCreature::RollbackAnimSet( int setId ) 
{
  CALL_CLIENT_1ARGS(RollbackAnimSet, setId); 
}

int  PFCreature::ReplaceAnimation( NDb::EAnimStates state, char const* name, char const* marker, bool upper, bool affectAllSets) 
{
  return IsValid(ClientObject())? ClientObject()->ReplaceAnimation(state, name, marker, upper, affectAllSets): -1;  
}

int  PFCreature::ReplaceAnimation( char const* oldName, char const* name, char const* marker, bool upper, bool affectAllSets)
{
  //TODO for NUM_TASK
  return 0;
}

void PFCreature::RollbackAnimation( NDb::EAnimStates state, int id, bool upper) 
{ 
  CALL_CLIENT_3ARGS(RollbackAnimation, state, id, upper); 
}

void PFCreature::RollbackAnimation( char const* oldName, int id, bool upper) 
{
  //TODO for NUM_TASK
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreature::OnAbilityDispatchStarted(PFAbilityData const* pData) const
{
  for( int i = NDb::ABILITY_ID_1, count = NDb::KnownEnum<NDb::EAbility>::SizeOf(); i < count; ++i)
  {
    if( pData == GetAbility(i) )
    {
      CALL_CLIENT_1ARGS( OnAbilityDispatchStarted, pData->GetAbilityMarker() );
      return;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<IPFState>  PFCreature::InvokeAbility(int id, Target const &target)
{
  NI_ASSERT(false == IsAbilityInProgress(id), "Ability is already in progress");
  NI_ASSERT(CanUseAbility(id), "Ability could not be used");

  CObj<IPFState> pState (new PFCreatureUseAbilityState(GetWorld(), this, id, target));
  
  return pState;
}
static const uint forceFlags = NDb::UNITFLAG_FORBID_ABILITY1 | NDb::UNITFLAG_FORBID_ABILITY2 | NDb::UNITFLAG_FORBID_ABILITY3 | NDb::UNITFLAG_FORBID_ABILITY4 |  
    NDb::UNITFLAG_FORBIDUSETALENTS | NDb::UNITFLAG_FORBIDMOVESPECIAL | 
    NDb::UNITFLAG_FORBIDINTERACT | NDb::UNITFLAG_FORBIDAUTOATTACK | NDb::UNITFLAG_IGNOREPUSH;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreature::ForceAnimation( const string& anim, int loopCount )
{
  if ( forcedAnimationTimeLeft == 0 )
    AddFlag( forceFlags );

  float duration = ClientObject() ? ClientObject()->ForceAnimation( anim ) : 0.0f;
  forcedAnimationTimeLeft = loopCount > 0 ? loopCount * duration : 1e10; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreature::StopForcedAnimation( bool checkForcedAnimTime /*=true*/)
{
  if ( checkForcedAnimTime && forcedAnimationTimeLeft < EPS_VALUE )
    return;

  CALL_CLIENT( StopForcedAnimation );
  RemoveFlag( forceFlags );
  forcedAnimationTimeLeft = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFCreatureUseAbilityState::PFCreatureUseAbilityState(CPtr<PFWorld> const& pWorld, CPtr<PFCreature> const& pOwner, int id, Target const &target) 
: PFBaseUnitUseAbilityState(pWorld, CPtr<PFBaseUnit>(pOwner), id, target)
, pCreature(pOwner)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFCreatureUseAbilityState::GetNumSubStates() const
{
  return PFHFSM::GetStackSize();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreatureUseAbilityState::OnEnter()
{
	if ( !IsUnitValid(pOwner) || !target.IsValid() )
		return;

  PFBaseUnitUseAbilityState::OnEnter();

	PFAbilityData const* pAbility = pOwner->GetAbility( abilityID );

	// we cast magic on ourself - nothing to do
	if ( target.IsUnit() && target.GetUnit() == pOwner)
	{
		NDb::EAbilityType type = pAbility ? pAbility->GetType() : NDb::ABILITYTYPE_SIMPLE;
		if( NDb::ABILITYTYPE_SWITCHABLE != type &&  NDb::ABILITYTYPE_PASSIVE != type )
		{
			if( !pCreature->IsMounted() )
				pCreature->Stop();
		}

		return;
	}

	// hacky solution :
	// only hero can cast magic now
	// if creep would can - Abilities container and accessors will be moved to base unit
	if( pAbility )
	{
		float range = pAbility->GetUseRange();
		abilityRange.SetBaseValue( range );

		const CVec2 targetPos = target.AcquirePosition().AsVec2D();

    CPtr<PFBaseMovingUnit> pMovingUnit(pCreature);
    if (!pOwner->CheckFlag(NDb::UNITFLAG_FORBIDMOVE) && fabs2(targetPos - pOwner->GetPosition().AsVec2D()) > range * range)
    {
		  if (target.IsUnit())
      {
        if ( IsUnitValid( target.GetUnit() ) && target.GetUnit()->IsVisibleForFaction( pMovingUnit->GetFaction() ) )
        {
			    PushState( new PFBaseUnitChaseState( pMovingUnit, pAbility->GetDBDesc()->requireLineOfSight, abilityRange.GetValue(), 0.0f, target.GetUnit(), true ) );
        }
      }
		  else if (target.IsPosition() || target.IsObject())
      {
			  PushState( new PFBaseUnitMoveToState( pMovingUnit, targetPos, range ) );
      }
		  else
		  {
			  NI_ALWAYS_ASSERT("Unknown target type");
		  }
    }
    if (pMovingUnit->IsMoving())
    {
      pMovingUnit->Stop();
    }
	}
}

void PFCreature::RemoveCorpse()
{
  deadUnitLifeTime = -1;
	if ( ClientObject() )
	{
    //Clear color in old SceneObject
    ClientObject()->ClearColorModifications();

		ClientObject()->CreateStandaloneEffect();

    //Clear color in new SceneObject
    ClientObject()->ClearColorModifications();
	}
}

}

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFCreature, NWorld)
REGISTER_WORLD_OBJECT_NM(PFCreatureUseAbilityState, NWorld)

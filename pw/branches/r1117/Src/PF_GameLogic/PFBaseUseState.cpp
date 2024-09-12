#include "stdafx.h"
#include "PFBaseUseState.h"
#include "PFBaseUnit.h"
#include "PFAbilityInstance.h"

namespace NWorld
{

PFBaseUseState::PFBaseUseState( CPtr<PFBaseUnit> const& _owner, Target const& _target )
: PFBaseUnitState( _owner )
, target( _target )
{
  NI_ASSERT( !target.IsUnit() || IsValid( target.GetUnit() ), "Invalid unit passed as target to UseState" );
}

bool PFBaseUseState::NeedToGetClose() const
{
  if ( !IsUnitValid( pOwner ) )
  {
    return false;
  }

  if ( target.IsUnit() && target.GetUnit() == pOwner )
    return false;
 
  const float range = GetUseRange();
  if ( ( GetAbilityFlags() & NDb::ABILITYFLAGS_CANUSEOUTOFRANGE ) != 0 || ( range <= 0.0f ) )
  {
    return false;
  }

  return !pOwner->IsTargetInRange( target, range );

}

bool PFBaseUseState::IsCastFinished() const
{
  return IsValid(pAbilityInstance) ? pAbilityInstance->IsCastFinished() && !pOwner->IsInChannelling() : false;
}

bool PFBaseUseState::IsAbilityFinished() const
{
  return IsValid(pAbilityInstance) ? pAbilityInstance->IsFinished() && !pOwner->IsInChannelling() : false;
}

bool PFBaseUseState::IsBlocking() const
{
  if ( !IsValid( pAbilityInstance ) )
  {
    return false;
  }

  const bool finished = pAbilityInstance->GetData()->GetDBDesc()->isUnitFreeAfterCast ? pAbilityInstance->IsCastFinished() : pAbilityInstance->IsFinished();
  return !finished;
}

bool PFBaseUseState::IsEjecting() const
{
  return (GetAbilityFlags() & NDb::ABILITYFLAGS_MOMENTARY) == 0;
}

void PFBaseUseState::OnLeave()
{
  if ( IsValid( pAbilityInstance ) )
  {
    pAbilityInstance->Cancel();
  }
}

unsigned int PFBaseUseState::GetAbilityFlags() const
{
  const NDb::Ptr<NDb::AlternativeActivity> pAltActivity = target.GetDBAlternativeTarget() ? target.GetDBAlternativeTarget()->alternativeActivity : 0;
  const NDb::Ptr<NDb::Ability> pAbility = GetDBDesc();

  return pAltActivity ? pAltActivity->flags : ( pAbility ? pAbility->flags : 0 );
}

}
#include "stdafx.h"

#include "Clinic.h"
#include "ClinicBonus.h"
#include "ClinicCreep.h"
#include "ClinicPlayer.h"

#include "ClinicBonusClientObject.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicPlayer::ClinicPlayer()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicPlayer::~ClinicPlayer()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicCreep* ClinicPlayer::GetCreep()
{
	return creep;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicBonus* ClinicPlayer::GetBonus()
{
	return bonus;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicCreep* ClinicPlayer::GiveToPlayer( ClinicPlace* _clinicPlace, ClinicCreep* _clinicCreep )
{
	if ( IsValid( bonus ) )
	{
		bonus->UseOnPlace( _clinicPlace );

		if ( bonus->UseOnCreep( _clinicCreep ) )
			_clinicCreep->OnWakeUp();

    bonus->GetHandheldCientObject()->SetVisible( false );
		bonus = 0;

		return _clinicCreep;
	}

	CPtr<ClinicCreep> oldCreep = creep;

	creep = _clinicCreep;

	if ( IsValid( creep ) )
	{
		creep->SetOwner( this );
		creep->SetAtPlayerHand( true );
	}

	if ( IsValid( oldCreep ) )
		oldCreep->SetAtPlayerHand( false );

	return oldCreep;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlayer::GiveToPlayer( ClinicBonus* _clinicBonus )
{
  if ( !IsValid( _clinicBonus ) )
  {
    if ( IsValid( bonus ) )
    {
      bonus->GetHandheldCientObject()->SetVisible( false );
      bonus = 0;
    }

    return;
  }

	if ( IsValid( creep ))
	{
		_clinicBonus->UseOnCreep( creep );
		return;
	}

	if ( _clinicBonus->IsTargeted() )
	{
		bonus = _clinicBonus;
    bonus->GetHandheldCientObject()->SetPlacement( GetPlacement() );
    bonus->GetHandheldCientObject()->SetVisible( true );
	}
	else
	{
		_clinicBonus->TryUse();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlayer::MoveTo( MinigameWorldObject* _targetObject, float _velocity, float _tolerance, bool pushBack /*= true*/ )
{
	DestDesc dest;

	dest.targetObject = _targetObject;
	dest.velocity = _velocity;
	dest.tolerance = _tolerance;

	if ( pushBack )
		destinations.push_back( dest );
	else
		destinations.push_front( dest );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlayer::CancelQueue()
{
  if ( destinations.empty() )
    return;

  DestDesc dest = destinations.front();

  destinations.clear();
  destinations.push_front( dest );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Placement& ClinicPlayer::GetTarget( bool& goInstantly ) const
{
  goInstantly = true;

  if ( destinations.empty() )
    return GetPlacement();

  const DestDesc& dest = destinations.front();

  if ( !IsValid( dest.targetObject ) )
    return GetPlacement();

  goInstantly = false;

  return dest.targetObject->GetPlacement();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ClinicPlayer::GetLinearVelocity() const
{
  if ( destinations.empty() )
    return 0.f;

  const DestDesc& dest = destinations.front();

  if ( !IsValid( dest.targetObject ) )
    return 0.f;
  
  float finalVelocity = dest.velocity;
  float speedUp = 1.f;

  if ( clinic->IsBonusBought( NDb::BONUSTYPE_FOOTPATHS ) )
    speedUp += clinic->GetBonusByType( NDb::BONUSTYPE_FOOTPATHS )->GetValue() / 100.f; 

  if ( clinic->IsBonusBought( NDb::BONUSTYPE_SPEEDBOOTS ) )
    speedUp += clinic->GetBonusByType( NDb::BONUSTYPE_SPEEDBOOTS )->GetValue() / 100.f; 

  finalVelocity *= speedUp;

  return finalVelocity;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlayer::Step( float deltaTime )
{
	if ( IsValid( bonus ) )
		bonus->GetHandheldCientObject()->SetPlacement( GetPlacement() );

	if ( destinations.empty() )
		return;

	DestDesc& dest = destinations.front();

	if ( !IsValid( dest.targetObject ) )
		return;

	const Placement& targetPlacement = dest.targetObject->GetPlacement();

	CVec3 movementDir = (targetPlacement.pos - placement.pos);	
  float distanceToTarget = fabs( movementDir ) - dest.tolerance;
  float distanceThisStep = deltaTime * GetLinearVelocity();

	if ( distanceToTarget <= distanceThisStep )
	{
		DestDesc oldDest = dest;
		destinations.pop_front();

		if ( !oldDest.targetObject->OnTouched( this ) )
			destinations.push_front( oldDest );
	}
	else
	{
		Normalize( &movementDir );
		placement.pos += movementDir * distanceThisStep;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlayer::Clear()
{
	creep = 0;
	bonus = 0;
}


} // namespace PF_Minigames
REGISTER_SAVELOAD_CLASS_NM( ClinicPlayer, PF_Minigames )
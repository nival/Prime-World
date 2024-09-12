#include "stdafx.h"

#include "DBClinic.h"
#include "Clinic.h"
#include "ClinicBonus.h"
#include "ClinicCreep.h"
#include "ClinicPlace.h"
#include "ClinicPlayer.h"
#include "MinigameClientObject.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicPlace::ClinicPlace() :
  isCreepWorking(false),

	soil(0.f),
	placeDesc(0),

	cleaning(false)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicPlace::~ClinicPlace()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlace::Step( float deltaTime )
{
	if ( cleaning )
	{
		float cleanSpeed = 1.f / ( clinic->GetBonusByType( NDb::BONUSTYPE_BROOM )->GetValue() );
		soil -= cleanSpeed * deltaTime;

		if ( soil <= 0.f )
		{
			soil = 0.f;
			cleaning = false;
		}

		return;
	}

	if ( clinic->IsCleaningStarted() )
	{
		soil -= (clinic->GetBonusByType( NDb::BONUSTYPE_SUPERCLEANER )->GetValue() / 100.f) * deltaTime;
		soil = Clamp( soil, 0.f, 1.f );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicPlace::OnClick()
{
  if ( ClinicItem::OnClick() )
    return true;

	clinic->MovePlayerTo( GetObjectID(), true );
  SetInRoute();
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicPlace::StartCleaning()
{
	if ( cleaning || NDb::PLACETYPE_CREEPPLACE == placeDesc->placeType || NDb::PLACETYPE_ENTRANCE == placeDesc->placeType )
 		return false;
 
	cleaning = true;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicPlace::OnTouched( MinigameWorldObject* _other )
{
  ClearInRoute();

  if ( IsValid( occupant ) )
	{
		if ( occupant->IsSleeping() )
		{
			occupant->OnWakeUp();
			return false;
		}
	}

	SetOccupied( clinic->GetPlayer()->GiveToPlayer( this, occupant ) );

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlace::SetCreepWorking( bool _creepWorking )
{
  isCreepWorking = _creepWorking;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicPlace::IsCreepWorking( float& _progress )
{
  if ( IsValid( occupant ) )
    return occupant->IsCreepWorking( _progress );

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlace::Clear()
{
	occupant = 0;
  cleaning = false;
  ClearInRoute();
  soil = 0.f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicPlace::IsAvailable( NDb::EPlaceType _placeType, float soilPersent ) const
{
	return ( IsBought() && placeDesc->placeType == _placeType && !IsValid( occupant ) && (1.f - soil >= soilPersent) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::EPlaceType ClinicPlace::GetType() const 
{ 
	return placeDesc->placeType; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlace::SetSoil( float _soil ) 
{ 
  soil = _soil; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlace::SetOccupied( ClinicCreep* _occupant ) 
{ 
#ifdef _DEBUG	 
	if ( IsValid( occupant ) )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "Occupant leave: " << occupant->GetName() << " | ";
	}
	else
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "Occupant leave: NULL | ";
	}
#endif

	if ( IsValid( occupant ) )
	{
		occupant->SetClinicPlace( 0 );
	}

	occupant = _occupant; 

	if ( IsValid( occupant ) )
	{
		occupant->SetOwner( this );
		occupant->SetClinicPlace( this );
		occupant->SetClinicPlaceType( placeDesc->placeType );
	}


#ifdef _DEBUG	 
	if ( IsValid( occupant ) )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "Occupant enter: " << occupant->GetName() << endl;
	}
	else
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "Occupant enter: NULL" << endl;
	}
#endif
}


} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM(ClinicPlace, PF_Minigames)

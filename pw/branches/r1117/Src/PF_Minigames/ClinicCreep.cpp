#include "stdafx.h"

#include "DBClinic.h"

#include "Clinic.h"
#include "ClinicBonus.h"
#include "ClinicCreep.h"
#include "ClinicPlace.h"
#include "CreepStates.h"
#include "ClinicScreen.h"
#include "MinigameClientObject.h"
#include "MinigamesMain.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicCreep::ClinicCreep() :
  creepBar(0.20f),
  goldMadeInLevel(0.f),
  award( EClinicCreepAward::None ),
	creepType(ECreepType::Melee),
  creepWish(NDb::CREEPWISH_NONE),
	creepWishAtStart(NDb::CREEPWISH_NONE),
	clinicPlaceType(NDb::PLACETYPE_NONE),
  isAtHand(false),
  goingOut(false),
  timeAtOnePlace(0.f),
  creepPhase(ECreepPhase::InGame),
	friendCreepID(-1),
	friendshipID(-1),
  poolID(-1)  
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicCreep::~ClinicCreep()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreep::SetCreepPhase( ECreepPhase::Enum _creepPhase ) 
{ 
	if ( creepPhase != _creepPhase )
	{
		creepPhase = _creepPhase;

		if ( ECreepPhase::InGame != creepPhase )
		{
			if ( IsValid( clinicPlace ) )
				clinicPlace->SetOccupied( 0 );

			if ( clinic->IsBonusBought( NDb::BONUSTYPE_BESTCLINIC ) && ECreepPhase::IsTrained == creepPhase )
			{
				AddBarValue( clinic->GetBonusByType( NDb::BONUSTYPE_BESTCLINIC )->GetValue() / 100.f );
				clinic->AddGold( clinic->GetBonusByType( NDb::BONUSTYPE_BESTCLINIC )->GetUseCost() );
			}

			CPtr<MinigameClientObject> clientObject = clinic->GetClientObject( GetObjectID() );
			clientObject->SetVisible( false );
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void ClinicCreep::SetBarValue( float _value )
{
	creepBar = _value;
	creepBar = Clamp( creepBar, 0.f, 1.f );
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ClinicCreep::GetBarValue()
{
	return creepBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring ClinicCreep::GetTypeDesc() const
{
	switch(creepType)
	{
	case ECreepType::Melee:
			return L"Melee";
		case ECreepType::Range:
			return L"Range";
		case ECreepType::Siege:
			return L"Siege";
		case ECreepType::Last:
			return L"Last";
	}
	return L"Unknown";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring ClinicCreep::GetStateDesc() const
{
	return creepState ? creepState->GetText() : L"Unknown";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreep::AddBarValue( float _value )
{
  float oldValue = creepBar;

	creepBar += _value;

	if ( creepBar > 1.f )
		creepBar = 1.f;

	if ( creepBar <= 0.f )
		goingOut = true;

  if ( creepBar >= 0.5f && oldValue < 0.5f )
    clinic->PlaySound( NDb::CLINICSOUNDS_CREEPBAR50 );
  else if ( creepBar >= 0.25f && oldValue < 0.25f )
    clinic->PlaySound( NDb::CLINICSOUNDS_CREEPBAR25 );
}	

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreep::TryFindFriend()
{
	if ( friendshipID != -1 || !IsValid( clinicPlace ) )
		return;

	friendshipID = clinic->FindFriend( GetObjectID(), clinicPlace->GetObjectID(), friendCreepID );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicCreep::CheckFriendIsNear()
{
	if ( friendshipID == -1 || !IsValid( clinicPlace ) )
		return false;

	return clinic->CheckFriendIsNear( clinicPlace->GetObjectID(), friendshipID );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreep::SetClinicPlace( ClinicPlace* _clinicPlace ) 
{ 
	if ( clinicPlace != _clinicPlace )
	{
		clinicPlace = _clinicPlace; 
		timeAtOnePlace = 0.f;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Placement& ClinicCreep::GetTarget( bool& goInstantly ) const
{
  goInstantly = false;

  if ( goingOut )
    return clinic->GetExitPlacement();

  if ( IsValid( owner ) )
    return owner->GetTarget( goInstantly );

  return GetPlacement();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ClinicCreep::GetLinearVelocity() const
{
  if ( goingOut )
    return clinic->GetPlayerVelocity();

  if ( IsValid( owner ) )
    return owner->GetLinearVelocity();

  return 0.f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreep::Step( float deltaTime )
{
	if ( ECreepPhase::InGame != creepPhase )
		return;

	if ( IsValid( clinicPlace ) )
	{
		if ( timeAtOnePlace > clinic->GetCreepBehaviourDesc()->timeBeforeSearchFriend )
			TryFindFriend();

		timeAtOnePlace += deltaTime;
	}

	if ( IsAtPlayerHand() && clinic->IsBonusBought( NDb::BONUSTYPE_VELVETGLOVES ) )
	{
		float value = clinic->GetBonusByType( NDb::BONUSTYPE_VELVETGLOVES )->GetValue() / 100.f;
		AddBarValue( value * deltaTime );
	}

	if ( goingOut )
	{
		CVec3 movementDir = (clinic->GetExitPlacement().pos - placement.pos);	

		if ( fabs( movementDir ) < deltaTime * clinic->GetPlayerVelocity() * 2.f )
		{
			SetCreepPhase( ECreepPhase::IsFled );
		}
		else
		{
			Normalize( &movementDir );
			placement.pos += movementDir * deltaTime * clinic->GetPlayerVelocity();
		}
	}
	else
	{
		if ( IsValid( owner ) )
			placement = owner->GetPlacement();
	}

	if ( !IsValid( creepState ) )
	{
		SetCreepWish( NDb::CREEPWISH_CARPET );
		creepState = new CreepWaits();
		creepState->SetCreep( this );
	}

	CreepState* newState = creepState->Step( deltaTime );

	if ( newState )
	{
		creepState = newState;
		creepState->SetCreep( this );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreep::WantAtAnyPlace()
{
	if ( IsValid(creepState) )
		creepState->WantAtAnyPlace();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreep::OnWakeUp()
{
	if ( IsValid(creepState) )
		creepState->OnWakeUp();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicCreep::IsSleeping()
{
	if ( IsValid(creepState) )
		return creepState->IsSleeping();

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicCreep::OnClick()
{
  MinigameWorldObject::OnClick();

	if ( IsValid( clinicPlace ) )
		clinicPlace->OnClick();
  else if ( IsValid( owner ) )
    owner->OnClick();
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ClinicCreep::GetTimeAtOnePlace()
{
	return timeAtOnePlace;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicCreep* ClinicCreep::GetFriend()
{
	if ( ( -1 != friendshipID ) && ( -1 == friendCreepID ) )
	{
		friendCreepID = clinic->FindExistedFriend( this );
	}

	return dynamic_cast<ClinicCreep*>( clinic->GetWorldObject( GetFriendCreepID() ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicCreep::Clear()
{
	creepState = 0;
	clinicPlace = 0;
	owner = 0;
  goldMadeInLevel = 0;
  award = EClinicCreepAward::None;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicCreep::ReceiveClicks()
{
  if ( IsValid( owner ) )
    return owner->ReceiveClicks();

  return IsValid( clinicPlace );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicCreep::IsCreepWaiting( float& _progrees )
{
  if ( IsValid( creepState ) )
  {
    if ( creepState->IsWaiting() )
    {
      _progrees = creepState->GetStateProgress();
      return true;
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicCreep::IsCreepWorking( float& _progrees )
{
  if ( IsValid( creepState ) )
  {
    if ( creepState->IsWorking() )
    {
      _progrees = creepState->GetStateProgress();
      return true;
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicCreep::IsInPlaceCreepWants()
{
  if (IsValid(creepState))
    return creepState->IsInPlaceCreepWants();
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ClinicCreep::GetSoilPersent() 
{ 
	float valueSoil = 1.f;

	switch(creepType)
	{
	case ECreepType::Melee:
		valueSoil = clinic->GetClinicDesc()->soilPersentMelee / 100.f;
		break;
	case ECreepType::Range:
		valueSoil = clinic->GetClinicDesc()->soilPersentRange / 100.f;
		break;
	case ECreepType::Siege:
		valueSoil = clinic->GetClinicDesc()->soilPersentSiege / 100.f;
		break;
	}

  if ( clinic->IsBonusBought( NDb::BONUSTYPE_BOOTCOVERS ) )
    valueSoil -= clinic->GetBonusByType( NDb::BONUSTYPE_BOOTCOVERS )->GetValue() / 100.f;

  if ( 10 == clinic->GetCurrentLevel() )
		valueSoil *= clinic->GetClinicDesc()->level11_soilIncrease / 100.f;

	if ( 11 == clinic->GetCurrentLevel() )
		valueSoil *= clinic->GetClinicDesc()->level12_soilIncrease / 100.f;

	return valueSoil;
}

} // namespace PF_Minigames
REGISTER_SAVELOAD_CLASS_NM(ClinicCreep, PF_Minigames)
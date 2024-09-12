#include "stdafx.h"

#include "DBClinic.h"
#include "Clinic.h"
#include "ClinicBonus.h"
#include "ClinicCreep.h"
#include "ClinicPlace.h"
#include "ClinicPlayer.h"
#include "ClinicBonusClientObject.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicBonus::ClinicBonus() :
bonusDesc(NULL),
bonusType(NDb::BONUSTYPE_BROOM),
canBeBought(true),
isBeeingCooled(false),
timeCooled(0.f),
isWorking(false),
timeWorking(0.f)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicBonus::~ClinicBonus()
{

}

ClinicDecorationClientObject * ClinicBonus::GetHandheldCientObject()
{
  if ( !IsValid( handheldClientObject ) )
		handheldClientObject = clinic->CreateDecoration(  bonusDesc->sceneObject );

	return handheldClientObject;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring ClinicBonus::GetName() const
{
  return bonusDesc->name.GetText(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring ClinicBonus::GetDescription() const
{
  return bonusDesc->description.GetText();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClinicBonus::GetUseCost() const 
{ 
	return bonusDesc->useCost; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::EBonusType ClinicBonus::GetType() const
{
	return bonusType;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ClinicBonus::GetValue() const
{
	return bonusDesc->value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicBonus::TryUse()
{
	if ( isBeeingCooled )
		return false;

  if ( clinic->GetGold() < bonusDesc->useCost )
    return false;

  clinic->TakeGold( bonusDesc->useCost );

  clinic->PlayBonusSound( bonusType );
	isBeeingCooled = true;
	timeCooled = 0.f;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicBonus::HasCooldownPeriod()
{
	switch ( bonusType )
	{
	case NDb::BONUSTYPE_BROOM : 
	case NDb::BONUSTYPE_WHIP :
	case NDb::BONUSTYPE_SPEEDBOOTS :
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicBonus::UseOnCreep( ClinicCreep* _clinicCreep, bool _forceUse /*= false*/ )
{
	if ( !IsValid( _clinicCreep ) )
		return false;

	if ( isBeeingCooled && !_forceUse )
		return false;

	switch ( bonusType )
	{
	case NDb::BONUSTYPE_BOOKLET :
		if ( TryUse() )
		  _clinicCreep->WantAtAnyPlace();
		return true;
	case NDb::BONUSTYPE_CANDY :
    if ( _forceUse )
    {
  		_clinicCreep->AddBarValue( bonusDesc->value );
    }
    else if ( TryUse() )
    {
      _clinicCreep->AddBarValue( bonusDesc->value );
    }

		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicBonus::UseOnPlace( ClinicPlace* _clinicPlace )
{
	if ( !IsValid( _clinicPlace ) || isBeeingCooled )
		return false;

	switch ( bonusType )
	{
	case NDb::BONUSTYPE_BROOM :
		if ( _clinicPlace->StartCleaning() )
		{
      TryUse();
			return true;
		}
	}

	return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicBonus::IsTargeted() const
{
	switch ( bonusType )
	{
	case NDb::BONUSTYPE_BROOM : 
	case NDb::BONUSTYPE_BOOKLET :
	case NDb::BONUSTYPE_CANDY :
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicBonus::OnClick()
{
  if(ClinicItem::OnClick())
    return true;

	switch ( bonusType )
	{
	case NDb::BONUSTYPE_BROOM : 
	case NDb::BONUSTYPE_BOOKLET :
	case NDb::BONUSTYPE_CANDY :
	case NDb::BONUSTYPE_BELL : 
	case NDb::BONUSTYPE_SUPERCLEANER : 
	case NDb::BONUSTYPE_STAR : 
		clinic->MovePlayerTo( GetObjectID(), true );
    SetInRoute();
		return true;

	case NDb::BONUSTYPE_WHIP :
	case NDb::BONUSTYPE_SPEEDBOOTS :
		return true;
	}

  clinic->PlayBonusSound( bonusType );
	isBeeingCooled = true;
	timeCooled = 0.f;

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicBonus::OnTouched( MinigameWorldObject* _other )
{
  ClearInRoute();

  if ( clinic->GetPlayer()->GetBonus() == this )
  {
    clinic->GetPlayer()->GiveToPlayer( 0 );
    return true;
  }

	if ( isBeeingCooled )
		return true;

  StartBonus();

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicBonus::StartBonus()
{
  if ( clinic->GetGold() < bonusDesc->useCost )
    return false;

  switch ( bonusType )
	{
	case NDb::BONUSTYPE_BELL : 
		clinic->OnStartBell( true ); 
		isWorking = true;
		timeWorking = 0.f;
		break;
	case NDb::BONUSTYPE_SUPERCLEANER : 
		clinic->OnCleanAll( true ); 
		isWorking = true;
		timeWorking = 0.f;
		break;

	case NDb::BONUSTYPE_STAR : 
		clinic->OnStarBonus(); 
		break;

	case NDb::BONUSTYPE_BROOM : 
    clinic->GetPlayer()->NotifyClient("bonusBroom");
    //continue 'case' intentionaly:
	case NDb::BONUSTYPE_BOOKLET :
	case NDb::BONUSTYPE_CANDY :
		clinic->GetPlayer()->GiveToPlayer( this );
		return true;

	default:
		return true;
	}

  clinic->PlayBonusSound( bonusType );
	isBeeingCooled = true;
	timeCooled = 0.f;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicBonus::OnWorkDone()
{
	switch ( bonusType )
	{
	case NDb::BONUSTYPE_BELL : clinic->OnStartBell( false ); break;
	case NDb::BONUSTYPE_SUPERCLEANER : clinic->OnCleanAll( false ); break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicBonus::Step( float deltaTime )
{
	if ( isBeeingCooled )
	{
		if ( timeCooled > bonusDesc->cooldown )
		{
			isBeeingCooled = false;
		}

		timeCooled += deltaTime;
	}

	if ( isWorking )
	{
		if ( timeWorking > bonusDesc->duration )
		{
			OnWorkDone();
			isWorking = false;
		}

		timeWorking += deltaTime;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ClinicBonus::GetCooldownPersent()
{
	if ( isBeeingCooled && bonusDesc->cooldown > 0.f )
		return (timeCooled / bonusDesc->cooldown);

	return 0.f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicBonus::Cooldown()
{
	isBeeingCooled = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicBonus::Clear()
{
  Cooldown();

  if ( IsValid( handheldClientObject ) )
    handheldClientObject->SetVisible( false );
}

} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM(ClinicBonus, PF_Minigames)
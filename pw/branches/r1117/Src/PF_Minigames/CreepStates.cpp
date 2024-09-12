#include "stdafx.h"

#include "../System/RandomGen.h"

#include "DBClinic.h"
#include "ClinicBonus.h"
#include "ClinicCreep.h"
#include "ClinicPlace.h"
#include "CreepStates.h"
#include "ClinicPlayer.h"

#include "Clinic.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepState::CreepState() :
	currentTime(0.f)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepState::~CreepState()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepState::SetCreep( ClinicCreep* _creep )
{
	creep = _creep;
	Init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepState::Init()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepState::WantAtAnyPlace()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepState::OnWakeUp()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CreepState::IsSleeping() const
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepThinks::CreepThinks() :
	duration(3.f),
	wantToAnyPlace(false)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepThinks::~CreepThinks()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepThinks::Init()
{
	CPtr<Clinic> clinic = creep->GetClinic();

	if ( 2 == clinic->GetCurrentLevel() )
	{
		duration = clinic->GetRandom()->Random( clinic->GetClinicDesc()->level3_phase1Min, 
																						clinic->GetClinicDesc()->level3_phase1Max );
	}
	else
	{
		duration = clinic->GetRandom()->Random( clinic->GetClinicDesc()->minThinkTime, 
                                            clinic->GetClinicDesc()->maxThinkTime );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring CreepThinks::GetText() const
{
	return L"Thinks...";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepThinks::WantAtAnyPlace()
{
	wantToAnyPlace = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepState* CreepThinks::Step( float deltaTime )
{
	if ( wantToAnyPlace )
	{
		creep->SetCreepWish( NDb::CREEPWISH_ANY );
		return new CreepWaits();
	}

	if ( currentTime > duration )
	{
		WishProbabilities probabilities;
		creep->GetClinic()->GetWishProbabilities( probabilities, creep->GetCreepWish() );

		if ( probabilities[NDb::CREEPWISH_EXIT] > 0.f )
		{
			creep->SetCreepWish( NDb::CREEPWISH_EXIT );
			return new CreepWantsOut();
		}

		if ( NDb::CREEPWISH_NONE != creep->GetCreepFirstWish() )
		{
			creep->SetCreepWish( creep->GetCreepFirstWish() );
			creep->SetCreepFirstWish( NDb::CREEPWISH_NONE );

      CObj<CreepState> nextState1 = new CreepWaits();
      nextState1->SetCreep( creep );
      CObj<CreepState> nextState2 = nextState1->Step(0.f);
      
      return IsValid( nextState2 ) ? nextState2.Extract() : nextState1.Extract();
		}
		else
		{
			float rnd = creep->GetClinic()->GetRandom()->Random( 0.f, 0.99f );
			float probSum = 0.f;

			for ( int i = 0 ; i < NDb::KnownEnum<NDb::ECreepWish>::sizeOf; ++i )
			{
				probSum += probabilities[i];

				if ( rnd < probSum )
				{
          creep->SetCreepWish( static_cast<NDb::ECreepWish>(i) );

          CObj<CreepState> nextState1 = new CreepWaits();
          nextState1->SetCreep( creep );
          CObj<CreepState> nextState2 = nextState1->Step(0.f);

          return IsValid( nextState2 ) ? nextState2.Extract() : nextState1.Extract();
				}
			}
		}
	}

	currentTime += deltaTime;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepWaits::CreepWaits() : 
	durationWaitPhase(30.f),
	durationUntilAsleep(5.f),
	durationUntilWakeup(3.f),
	wakingUp(false),
	currentTimeUntilSleep(0.f),
	currentTimeUntilWakeup(0.f),
	comfortableCarpetUsed(false)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepWaits::~CreepWaits()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepWaits::Init()
{
	CPtr<Clinic> clinic = creep->GetClinic();

	durationWaitPhase = clinic->GetClinicDesc()->waitTime;

	if ( 11 ==  clinic->GetCurrentLevel() )
	{
		float value = clinic->GetClinicDesc()->level12_waitDecrease;

		if ( value > 0.f )
			durationWaitPhase /= value;
	}

	if ( 4 ==  clinic->GetCurrentLevel() )
		durationUntilAsleep = clinic->GetClinicDesc()->level5_fallAsleepTime;
	else
		durationUntilAsleep = clinic->GetClinicDesc()->fallAsleepTime;

	durationUntilWakeup = clinic->GetClinicDesc()->wakeupTime;

	if ( clinic->IsBonusBought( NDb::BONUSTYPE_WHIP ) )
		durationUntilWakeup -= clinic->GetBonusByType( NDb::BONUSTYPE_WHIP )->GetValue();

	if ( durationUntilWakeup <= 0.f )
		durationUntilWakeup = 0.f;

  switch ( creep->GetType() )
  {
  case ECreepType::Melee : clinic->PlaySound( NDb::CLINICSOUNDS_CREEPWISHMELEE ); break;
  case ECreepType::Range : clinic->PlaySound( NDb::CLINICSOUNDS_CREEPWISHRANGED ); break;
  case ECreepType::Siege : clinic->PlaySound( NDb::CLINICSOUNDS_CREEPWISHSIEGE ); break;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepWaits::WantAtAnyPlace()
{
	creep->SetCreepWish( NDb::CREEPWISH_ANY );

	currentTime = 0.f;
	currentTimeUntilSleep = 0.f;
	wakingUp = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepWaits::OnWakeUp()
{
	if ( !wakingUp )
	{
		wakingUp = true;
		currentTimeUntilWakeup = 0.f;

    Clinic * clinic = creep->GetClinic();
    if(clinic->IsBonusBought( NDb::BONUSTYPE_WHIP ))
      clinic->GetPlayer()->NotifyClient("creepWokeUpWWhip");
    else
      clinic->GetPlayer()->NotifyClient("creepWokeUp");

    creep->GetClinic()->PlaySound( NDb::CLINICSOUNDS_CREEPWAKEUP );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CreepWaits::IsSleeping() const
{
	return currentTimeUntilSleep > durationUntilAsleep && !creep->GetClinic()->IsBellChiming();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring CreepWaits::GetText() const
{
	if ( wakingUp )
		return L"Waking up...";

	if ( IsSleeping() )
		return L"Lazy...";

  NDb::ECreepWish creepWish = creep->GetCreepWish();

	switch ( creepWish )
	{
	case NDb::CREEPWISH_SLEEP : return L"SLEEP";
	case NDb::CREEPWISH_WASH : return L"WASH";
	case NDb::CREEPWISH_EAT : return L"EAT";
	case NDb::CREEPWISH_PLAY : return L"PLAY";
	case NDb::CREEPWISH_ANY : return L"ANY";
	case NDb::CREEPWISH_CARPET : return L"CARPET";
	}

	return L"NOTHING";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CreepWaits::IsInPlaceCreepWants() const
{
  NDb::ECreepWish wish = creep->GetCreepWish();

	switch ( creep->GetClinicPlaceType() )
	{
	case NDb::PLACETYPE_NONE:
		return false;

	case NDb::PLACETYPE_TABLE: return (NDb::CREEPWISH_EAT == wish) || (NDb::CREEPWISH_ANY == wish);
	case NDb::PLACETYPE_BAD: return (NDb::CREEPWISH_SLEEP == wish) || (NDb::CREEPWISH_ANY == wish);
	case NDb::PLACETYPE_WASHTAB: return (NDb::CREEPWISH_WASH == wish) || (NDb::CREEPWISH_ANY == wish);
	case NDb::PLACETYPE_GAMEPLACE: return (NDb::CREEPWISH_PLAY == wish) || (NDb::CREEPWISH_ANY == wish);
	case NDb::PLACETYPE_CREEPPLACE: return (NDb::CREEPWISH_CARPET == wish);

	case NDb::PLACETYPE_ENTRANCE: NI_ALWAYS_ASSERT("Must be catched earlier"); return false;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepState* CreepWaits::Step( float deltaTime )
{
	if ( wakingUp )
	{
		currentTimeUntilWakeup += deltaTime;
		
		if ( currentTimeUntilWakeup > durationUntilWakeup )
		{
			wakingUp = false;
			currentTimeUntilSleep = 0.f;
		}
	}

	if ( creep->GetClinicPlace() )
	{
		if ( IsInPlaceCreepWants() && creep->GetClinicPlace()->GetSoil() < 1.f )
		{
			if ( NDb::CREEPWISH_CARPET == creep->GetCreepWish() )
				return new CreepThinks();
			else
				return new CreepWorks();
		}
	}

  bool gameEnded = (NDb::CREEPWISH_EXIT == creep->GetCreepWish() ) || (creep->GetClinic()->GetGameMode() != EClinicGameMode::Game );

	if ( gameEnded || ( !creep->IsAtPlayerHand() && !creep->CheckFriendIsNear() ) )
	{
		currentTime += deltaTime;
		currentTimeUntilSleep += deltaTime;
	}

	if ( !comfortableCarpetUsed && creep->GetClinic()->IsBonusBought( NDb::BONUSTYPE_COMFORTABLECARPET ) && creep->GetClinicPlace() )
	{
		if ( IsSleeping() && NDb::PLACETYPE_CREEPPLACE == creep->GetClinicPlace()->GetType() )
		{
			float addTime = creep->GetClinic()->GetBonusByType( NDb::BONUSTYPE_COMFORTABLECARPET )->GetValue();
			currentTimeUntilSleep -= addTime;
			comfortableCarpetUsed = true;

			systemLog( NLogg::LEVEL_MESSAGE ) << "Comfortable carpet used. Added time: " << addTime << endl;
		}
	}

	if ( currentTime < durationWaitPhase )
		return 0;

	float minusValue = 0;

	if ( creep->GetClinic()->IsBonusBought( NDb::BONUSTYPE_TOYBOX ) )
		minusValue = -creep->GetClinic()->GetBonusByType( NDb::BONUSTYPE_TOYBOX )->GetValue() / 100.f;
	else
		minusValue = -creep->GetClinic()->GetClinicDesc()->failBonus;
	
	systemLog( NLogg::LEVEL_MESSAGE ) << "Th Wish was not satisfied, bar loose: " << minusValue << endl;
	creep->AddBarValue( minusValue );

  creep->NotifyClient("creepWishUnsatisfied");
  creep->GetClinic()->PlaySound( NDb::CLINICSOUNDS_CREEPLOOSEWISH );

	return new CreepThinks();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CreepWaits::GetStateProgress()
{
  if ( durationWaitPhase <= FLT_EPSILON )
    return 0.f;

  return ( currentTime / durationWaitPhase );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepWorks::CreepWorks() :
	friendNearChecked(false),
  durationWorkPhase(5.f)
{


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepWorks::Init()
{
	durationWorkPhase = creep->GetClinic()->GetClinicDesc()->workTime;

	if ( 7 == creep->GetClinic()->GetCurrentLevel() )
	{
		float reduction = creep->GetClinic()->GetClinicDesc()->level8_timeReduction;

		if ( reduction <= 0.f ) 
			reduction = 1.f;

		durationWorkPhase /= reduction;
	}

  switch ( creep->GetClinicPlace()->GetType() )
  {
  case NDb::PLACETYPE_BAD : creep->GetClinic()->PlaySound( NDb::CLINICSOUNDS_USEBAD ); break;
  case NDb::PLACETYPE_TABLE : creep->GetClinic()->PlaySound( NDb::CLINICSOUNDS_USETABLE ); break;
  case NDb::PLACETYPE_WASHTAB : creep->GetClinic()->PlaySound( NDb::CLINICSOUNDS_USEWASHTAB ); break;
  case NDb::PLACETYPE_GAMEPLACE : creep->GetClinic()->PlaySound( NDb::CLINICSOUNDS_USEPLAYGROUND ); break;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring CreepWorks::GetText() const
{
	return L"Works...";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepWorks::~CreepWorks()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepState* CreepWorks::Step( float deltaTime )
{
	if ( creep->IsAtPlayerHand() )
		return new CreepWaits();

	currentTime += deltaTime;

	if ( !friendNearChecked )
	{
		friendNearChecked = creep->CheckFriendIsNear();

		if ( friendNearChecked )
    {
			creep->AddBarValue( creep->GetClinic()->GetCreepBehaviourDesc()->friendshipBonus );
    }
	}

	if ( currentTime > durationWorkPhase )
	{
		if ( IsValid( creep->GetClinicPlace() ) )
			creep->GetClinicPlace()->SetSoil( creep->GetClinicPlace()->GetSoil() + creep->GetSoilPersent() );

		float addValue = creep->GetClinic()->GetClinicDesc()->workBonus;

		switch ( creep->GetCreepWish() )
		{
		case NDb::CREEPWISH_SLEEP : 
			if ( creep->GetClinic()->IsBonusBought( NDb::BONUSTYPE_COMFORTABLEPILLOW ) )
			{
				float value = creep->GetClinic()->GetBonusByType( NDb::BONUSTYPE_COMFORTABLEPILLOW )->GetValue();
				systemLog( NLogg::LEVEL_MESSAGE ) << "Compfortable pillow acts: +" << value << "%" << endl;
				addValue += value / 100.f;
			}
		case NDb::CREEPWISH_EAT : 
			if ( creep->GetClinic()->IsBonusBought( NDb::BONUSTYPE_COMFORTABLETABLE ) )
			{
				float value = creep->GetClinic()->GetBonusByType( NDb::BONUSTYPE_COMFORTABLETABLE )->GetValue();
				systemLog( NLogg::LEVEL_MESSAGE ) << "Compfortable table acts: +" << value << "%" << endl;
				addValue += value / 100.f;
			}
		}
		
		if ( 7 == creep->GetClinic()->GetCurrentLevel() )
			addValue *= creep->GetClinic()->GetClinicDesc()->level8_bonusReduction / 100.f;

		if ( 11 == creep->GetClinic()->GetCurrentLevel() )
			addValue *= creep->GetClinic()->GetClinicDesc()->level12_bonusReduction / 100.f;

		creep->AddBarValue( addValue );

    creep->GetClinic()->OnCreepSatisfied();

		if ( creep->GetClinic()->IsBonusBought( NDb::BONUSTYPE_TALISMAN ) )
		{
			CPtr<ClinicCreep> friendCreep = creep->GetFriend();

			if ( IsValid( friendCreep ) )
			{
				float friendBonus = creep->GetClinic()->GetBonusByType( NDb::BONUSTYPE_TALISMAN )->GetValue() / 100.f;
				friendBonus *= addValue;
				systemLog( NLogg::LEVEL_MESSAGE ) << "Friend receive bonus too: " << friendBonus << endl;
				friendCreep->AddBarValue( friendBonus );
			}
		}

    creep->NotifyClient("creepWishSatisfied");

    switch ( creep->GetType() )
    {
    case ECreepType::Melee : creep->GetClinic()->PlaySound( NDb::CLINICSOUNDS_CREEPWISHDESIREDMELEE ); break;
    case ECreepType::Range : creep->GetClinic()->PlaySound( NDb::CLINICSOUNDS_CREEPWISHDESIREDRANGED ); break;
    case ECreepType::Siege : creep->GetClinic()->PlaySound( NDb::CLINICSOUNDS_CREEPWISHDESIREDSIEGE ); break;
    }

		return new CreepThinks();
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float CreepWorks::GetStateProgress()
{
  if ( durationWorkPhase <= FLT_EPSILON )
    return 0.f;

  return ( currentTime / durationWorkPhase );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepWantsOut::CreepWantsOut() : 
	durationWaitPhase(30.f)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepWantsOut::~CreepWantsOut()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreepWantsOut::Init()
{
	durationWaitPhase = creep->GetClinic()->GetClinicDesc()->waitTime;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wstring CreepWantsOut::GetText() const
{
	return L"TO EXIT";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepState* CreepWantsOut::Step( float deltaTime )
{
	currentTime += deltaTime;

	if ( currentTime < durationWaitPhase )
		return 0;

	creep->AddBarValue( -1.0f );

	return 0;
}


} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( CreepThinks, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( CreepWaits, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( CreepWantsOut, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( CreepWorks, PF_Minigames )





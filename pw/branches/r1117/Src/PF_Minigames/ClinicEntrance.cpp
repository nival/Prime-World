#include "stdafx.h"

#include "ClinicEntrance.h"

#include "../System/RandomGen.h"

#include "DBClinic.h"

#include "Clinic.h"
#include "ClinicBonus.h"
#include "ClinicCreep.h"
#include "ClinicPlayer.h"

#include "MinigameClientObject.h"
#include "MinigamesMain.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicEntrance::CreepInQueueDesc::CreepInQueueDesc() : 
	type( ECreepType::Melee ), 
	friendshipID(-1)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicEntrance::CreepInQueueDesc::CreepInQueueDesc( ECreepType::Enum _type ) : 
	type(_type), 
	friendshipID(-1)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicEntrance::ClinicEntrance() :
	timeToNextCreep(0.f),
	queueStoped(false),
	creepsOut(0),
  isInRoute(false)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicEntrance::~ClinicEntrance()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicEntrance::SetCreepsNumber( int _numMelee, int _numRange, int _numSiege )
{
	int number[ECreepType::Last];

	number[ECreepType::Melee] = _numMelee;
	number[ECreepType::Range] = _numRange;
	number[ECreepType::Siege] = _numSiege;

	while ( number[ECreepType::Melee] + number[ECreepType::Range] + number[ECreepType::Siege] > 0 )
	{
		ECreepType::Enum nextType = static_cast<ECreepType::Enum>( clinic->GetRandom()->Random(ECreepType::Melee, ECreepType::Range) );

		if ( number[nextType] > 0 )
		{
			creepsQueue.push_back( CreepInQueueDesc( nextType ) ); 
			number[nextType]--;
		}
		else
		{
			if ( number[ECreepType::Melee] > 0 )
			{
				creepsQueue.push_back( CreepInQueueDesc( ECreepType::Melee ) ); 
				number[ECreepType::Melee]--;
			}
			else if ( number[ECreepType::Range] > 0 )
			{
				creepsQueue.push_back( CreepInQueueDesc( ECreepType::Range ) ); 
				number[ECreepType::Range]--;
			}
			else
			{
				creepsQueue.push_back( CreepInQueueDesc( ECreepType::Siege ) ); 
				number[ECreepType::Siege]--;
			}
		}
	}

	if ( 1 == clinic->GetCurrentLevel() )
	{
		CreepsQueue::iterator it = creepsQueue.begin();
		CreepsQueue::iterator last = creepsQueue.end();

		for (; it != last; ++it)
		{
			if (it->friendshipID != -1)
				continue;

			CreepsQueue::iterator it2 = it;

			for (++it2; it2 != last; ++it2)
			{
				if (it->friendshipID != -1)
					break;

				if (it2->friendshipID != -1)
					continue;

				if ( it->type != it2->type )
					it->friendshipID = it2->friendshipID = clinic->GetNextFriendshipID();
			}
		}
	}

	timeToNextCreep = 0.f;
	queueStoped = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicEntrance::Step( float deltaTime )
{
  if ( EClinicGameMode::Shop == clinic->GetGameMode() )
    return;

  if ( queueStoped )
		return;

  if( IsValid ( creepAtEntrance ) )
  {
    if ( creepAtEntrance->GetCreepPhase() == ECreepPhase::IsFled )
      creepAtEntrance = NULL;
  }
  else
    timeToNextCreep -= deltaTime;

	if ( timeToNextCreep <= 0.f && !creepsQueue.empty() && !IsValid( creepAtEntrance ) )
	{
		timeToNextCreep = clinic->GetRandom()->Random( clinic->GetClinicDesc()->minTimeBetweenCreeps, clinic->GetClinicDesc()->maxTimeBetweenCreeps );

		creepAtEntrance = clinic->InitCreepOfType( creepsQueue.front().type, GetPlacement() );
		creepAtEntrance->SetFriendshipID( creepsQueue.front().friendshipID );
		creepAtEntrance->SetOwner( this );

		if ( 3 == clinic->GetCurrentLevel() && creepsOut < 3 )
      creepAtEntrance->SetCreepFirstWish( NDb::CREEPWISH_WASH );
		else if ( 8 == clinic->GetCurrentLevel())
			creepAtEntrance->SetCreepFirstWish( NDb::CREEPWISH_WASH );
		else 
			creepAtEntrance->SetCreepFirstWish( NDb::CREEPWISH_NONE );

		if ( 0 == clinic->GetCurrentLevel() ) // Level 1 feature
		{
			float value = clinic->GetClinicDesc()->level1_BarValue / 100.f;
			systemLog( NLogg::LEVEL_MESSAGE ) << "Level 1 bonus : " << value << endl;
			creepAtEntrance->AddBarValue( value );
		}

		if ( clinic->IsBonusBought( NDb::BONUSTYPE_ADVENCEDENTRACE ))
		{
			float value = clinic->GetBonusByType( NDb::BONUSTYPE_ADVENCEDENTRACE )->GetValue() / 100.f;
			systemLog( NLogg::LEVEL_MESSAGE ) << "Additional bonus at start : " << value << endl;
			creepAtEntrance->AddBarValue( value );
		}

		creepsQueue.pop_front();
		++creepsOut;
	}

  if ( creepsQueue.empty() && !IsValid( creepAtEntrance ) )
    clinic->GetClientObject( GetObjectID() )->SetVisible( false );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicEntrance::OnClick()
{
  if ( EClinicGameMode::Shop == clinic->GetGameMode() )
    return false;

  clinic->MovePlayerTo( GetObjectID(), true );
  isInRoute = true;
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicEntrance::StopQueue() 
{ 
	queueStoped = true; 

	if ( IsValid( creepAtEntrance ) )
	{
		creepAtEntrance->SetCreepPhase( ECreepPhase::IsFled );
		creepAtEntrance = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicEntrance::Clear()
{
	creepsOut = 0;
	creepAtEntrance = 0;
  creepsQueue.clear();
	clinic->GetClientObject( GetObjectID() )->SetVisible( true );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicEntrance::OnTouched( MinigameWorldObject* _other )
{
  isInRoute = false;

  ClinicCreep* creepAtHand =  clinic->GetPlayer()->GetCreep();
	ClinicBonus* bonusAtHand =  clinic->GetPlayer()->GetBonus();

	if ( queueStoped )
	{
		if ( IsValid( creepAtHand ) )
		{
			if ( NDb::CREEPWISH_EXIT == creepAtHand->GetCreepWish() )
			{
				creepAtEntrance = clinic->GetPlayer()->GiveToPlayer( 0, 0 );
				creepAtEntrance->SetCreepPhase( ECreepPhase::IsTrained );
				creepAtEntrance = 0;
			}
		}
	}
	else
	{
		if ( IsValid( bonusAtHand ) )
		{
			clinic->GetPlayer()->GiveToPlayer( 0, creepAtEntrance );
		}
		else if ( !IsValid( creepAtHand ) && IsValid( creepAtEntrance ) )
		{
			if ( creepAtEntrance->IsSleeping() )
			{
				creepAtEntrance->OnWakeUp();
				return false;
			}

			timeToNextCreep = clinic->GetRandom()->Random( clinic->GetClinicDesc()->minTimeBetweenCreeps, clinic->GetClinicDesc()->maxTimeBetweenCreeps );

			clinic->GetPlayer()->GiveToPlayer( 0, creepAtEntrance );

			creepAtEntrance = 0;
		}
	}

	return true;
}

} // namespace PF_Minigames
REGISTER_SAVELOAD_CLASS_NM( ClinicEntrance, PF_Minigames )
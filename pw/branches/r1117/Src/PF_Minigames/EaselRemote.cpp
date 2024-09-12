#include "stdafx.h"
#include "EaselRemote.h"

#include "EaselWorld.h"
#include "EaselView.h"

#include "MinigameSessionInterface.h"
#include "EaselMinigame.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// class EaselRemote implementation
//
//////////////////////////////////////////////////////////////////////////
EaselRemote::EaselRemote( PF_Core::IWorld* _pWorld, IRemoteToLocalLink * localLink, bool _nullView ) :
Easel( _pWorld ),
localLink( localLink ),
nullView( _nullView )
{
}


EaselRemote::~EaselRemote()
{
}


void EaselRemote::StartLevel( int paintId, int levelID, int seed, NWorld::PFEaselPlayer * player )
{
  Easel::StartLevel( paintId, levelID, seed, player );
}



void EaselRemote::StopLevel()
{
  Easel::StopLevel();

  //TODO its the worst place ever to update levels but we need world money for this
  IMinigames * mgs = GetWorldSessionInterface()->GetMinigames();
  EaselMinigame * minigame = dynamic_cast<EaselMinigame*>(  mgs->GetMinigame( "Easel" ) );;

  if (IsValid(minigame))
    minigame->UpdateLevelAvailability();
}



void EaselRemote::StepM( const EaselStepInfo& info )
{
  Easel::StepM( info.deltaTime );
  GetWorld()->StepM(info);
}

//void EaselRemote::CheatWinGame()
//{
//  DevTrace("EaselRemote::CheatWinGame()");
//}


bool EaselRemote::ProcessMouseMove(const CVec2& _pos)
{
  return true;  // nothing to do
}

bool EaselRemote::ProcessMouseEvent( EEaselMouseEvents::Enum _key )
{
  return true;  // nothing to do
}



bool EaselRemote::TransferItem( NWorld::PFBaseHero * target, int transactionId )
{
  const NDb::Consumable * item = GetWorld()->GetPriestessProxy()->GetRewardItem();

  if ( !item )
    return true;

  if ( GetWorldSessionInterface()->AddItemToHero( target, item, 1 ) )
  {
    GetWorld()->GetPriestessProxy()->ClearRewardItem();
    return true;
  }
  else
    return false;
}



// creation overloads
EaselWorld* EaselRemote::CreateWorldObject()
{
  return new EaselWorldRemote( PF_Core::WorldObjectBase::GetWorld() , localLink );
}

EaselView* EaselRemote::CreateViewObject( Easel* _easel )
{
  if ( nullView )
    return new EaselNullView( _easel );
  else
    return new EaselView( _easel );
}

void EaselRemote::OnAfterReset()
{
  Easel::OnAfterReset();

  if ( IsValid( localGame ) )
    localGame->Copy( this );
}



}

REGISTER_SAVELOAD_CLASS_NM( EaselRemote, PF_Minigames )

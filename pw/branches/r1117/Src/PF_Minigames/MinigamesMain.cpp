#include "stdafx.h"

#include "../Core/GameCommand.h"
#include "../Core/WorldBase.h"
#include "../Core/Scheduler.h"

#include "MinigamesMain.h"

#include "Minigames.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigamesMain::MinigamesMain() :
nextCreepID(1),
sessionTime( 0 )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigamesMain::MinigamesMain( const NDb::DBMinigamesCommon & resource ) :
nextCreepID( 1 ),
commonDBData( &resource ),
sessionTime( 0 )
{
  InitPersonalCreeps();
}



void MinigamesMain::Set( NScene::IScene* _scene, NCore::IWorldBase* _worldBase )
{
  scene = _scene;
  world = _worldBase;
}



void MinigamesMain::SetTransceiver( NCore::ITransceiver * _pTransceiver )
{
  pTransceiver = _pTransceiver;
}



IMinigames * MinigamesMain::ProduceMinigamesObject( NWorld::PFWorld* _pWorld, IWorldSessionInterface * worldInterf, bool _isLocal )
{
  Minigames * mgs = new PF_Minigames::Minigames( _pWorld );

  mgs->SetLocal( _isLocal );
  mgs->SetSessionInterface( worldInterf);
  mgs->SetMinigamesMain( this );
  mgs->InitGames();

  return mgs;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamesMain::SendWorldCommand( NCore::WorldCommand* _worldCommand )
{
  CObj<NCore::WorldCommand> pCommand = _worldCommand;
  if ( IsValid( pTransceiver ) )
    pTransceiver->SendCommand( pCommand, true );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamesMain::Step( float deltaTime )
{
  sessionTime += deltaTime;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamesMain::InitPersonalCreeps()
{
  NI_DATA_ASSERT( commonDBData, "Db resource is not loaded" );

  ParseCreepNames( commonDBData->namePoolMelee, ECreepType::Melee );
  ParseCreepNames( commonDBData->namePoolRange, ECreepType::Range );
  ParseCreepNames( commonDBData->namePoolSiege, ECreepType::Siege );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamesMain::ParseCreepNames( const CTextRef& names, ECreepType::Enum creepType )
{
  vector<wstring> strings;

  NStr::SplitString( names.GetText(), &strings, L"\n" );

  vector<wstring>::iterator it = strings.begin();
  vector<wstring>::iterator last = strings.end();

  for (; it != last; ++it )
  {
    personalCreepStack.insert( nstl::make_pair(nextCreepID, MinigameCreepDesc(*it, nextCreepID, creepType ) ) );
    nextCreepID++;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MinigamesMain::GetCreepDesc( int creepID, MinigameCreepDesc& creepDesc )
{
  PersonalCreeps::iterator it = personalCreepStack.find( creepID );

  if ( it != personalCreepStack.end() )
  {
    creepDesc = it->second;
    return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamesMain::GetFreeCreep( int playerID, ECreepType::Enum creepType, MinigameCreepDesc& creepDesc )
{
  NI_VERIFY( ECreepType::Last != creepType, "Unknown creep type", return );

  PersonalCreeps::iterator it = personalCreepStack.begin();
  PersonalCreeps::iterator last = personalCreepStack.end();

  for (; it != last; ++it)
  {
    if ( !it->second.isOut && (creepType == it->second.type) && ( -1 == it->second.ownerPlayerID || playerID == it->second.ownerPlayerID ) )
    {
      it->second.isOut = true;
      creepDesc = it->second;
      it->second.ownerPlayerID = playerID;
      return;
    }
  }

  creepDesc.type = creepType;
  creepDesc.creepID = nextCreepID;
  creepDesc.instant = true;
  creepDesc.name = L"Instant creep";
  creepDesc.isOut = true;
  creepDesc.ownerPlayerID = playerID;

  personalCreepStack.insert( nstl::make_pair( nextCreepID, creepDesc ) );

  nextCreepID++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamesMain::ReturnCreep( int _creepID  )
{
  PersonalCreeps::iterator it = personalCreepStack.find( _creepID );

  if ( it != personalCreepStack.end() )
  {
    if ( it->second.instant )
      personalCreepStack.erase( _creepID );
    else
      it->second.isOut = false;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamesMain::RegisterCreepSpawner( NDb::EFaction faction, NDb::ERoute routeID, int spawnerObjectID )
{
  spawners[faction][routeID] = spawnerObjectID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigamesMain::GetSpawnerID( NDb::EFaction faction, NDb::ERoute routeID ) const
{
  Spawners::iterator it = spawners.find( faction );

  if ( it == spawners.end() )
    return -1;

  RouteSpawners::iterator itS = it->second.find( routeID );

  if ( itS == it->second.end() )
    return -1;

  return itS->second;
}

} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM(MinigamesMain, PF_Minigames)

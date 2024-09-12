#include "stdafx.h"

#include "../Client/ScreenCommands.h"

#include "../UI/DBUI.h"

#include "DBClinic.h"
#include "Clinic.h"
#include "ClinicEntrance.h"
#include "ClinicBonus.h"
#include "ClinicCreep.h"
#include "ClinicPlace.h"
#include "ClinicPlayerClientObject.h"
#include "ClinicPlaceClientObject.h"
#include "ClinicBonusClientObject.h"
#include "ClinicCreepClientObject.h"
#include "ClinicEntranceClientObject.h"
#include "ClinicPlayer.h"
#include "ClinicLobbyScreen.h"
#include "MinigameWorldObject.h"
#include "MinigamesMain.h"
#include "MinigameSessionInterface.h"
#include "Minigames.h"

#include "../PF_GameLogic/PFStatistics.h"
#include "../PF_GameLogic/PFMinigamePlace.h"


namespace PF_Minigames
{

static bool gClinicShopNoRestrictions = false;
REGISTER_DEV_VAR( "clinic_shop_no_restrictions", gClinicShopNoRestrictions,  STORAGE_NONE );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::IsShopCheatOn()
{
	return gClinicShopNoRestrictions;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Clinic::Clinic() :
  clientInitialized(false),
  nextObjectID(1),
  nextDecorID(-1),
  levelDuration(1.f),
  currentLevelTime(0.f),
  placePos(VNULL3),
  placeScale(1, 1, 1),
  isBellChiming(false),
  isCleaningStated(false),
  nextFriendshipID(0),
  levelID(0),
  nextLevelID(0),
  gameMode(EClinicGameMode::None)
{
  for (int i = 0; i < NDb::KnownEnum<NDb::EPlaceType>::sizeOf; ++i)
	{
		placeTypesBought[i] = 0;
	}

	for (int i = 0; i < NDb::KnownEnum<NDb::EBonusType>::sizeOf; ++i)
	{
		bonusTypeBought[i] = false;
	}

  for (int i = 0; i < NDb::KnownEnum<NDb::EClinicSounds>::sizeOf; ++i )
  {
    sounds[i] = 0;
  }

  for (int i = 0; i < NDb::KnownEnum<NDb::EBonusType>::sizeOf; ++i )
  {
    soundsForBonus[i] = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::Clear()
{
	WorldObjects::iterator it = worldObjects.begin();
	WorldObjects::iterator last = worldObjects.end();

	for (; it != last; ++it)
		it->second->Clear();

  giftedPlaces.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Clinic::~Clinic()
{
  for (int i = 0; i < NDb::KnownEnum<NDb::EClinicSounds>::sizeOf; ++i )
  {
    if ( sounds[i] )
    {
      delete sounds[i]; 
      sounds[i] = 0;
    }
  }

  for (int i = 0; i < NDb::KnownEnum<NDb::EBonusType>::sizeOf; ++i )
  {
    if ( soundsForBonus[i] )
    {
      delete soundsForBonus[i]; 
      soundsForBonus[i] = 0;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::RemoveWorldObject( int _objectID )
{
	worldObjects.erase( _objectID );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::RemoveClientObject( int _objectID )
{
	clientObjects.erase( _objectID );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::RetrieveAllItems(ClinicItems * pDest) const
{
  pDest->clear();

  for( ClinicBonuses::iterator it = clinicBonuses.begin(); it != clinicBonuses.end(); ++it )
    pDest->insert( static_cast<ClinicItem *>( it->second ) );

  for( ClinicPlaces::iterator it = clinicPlaces.begin(); it != clinicPlaces.end(); ++it )
    pDest->insert( static_cast<ClinicItem *>( it->second ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::Init( Minigames* _minigames, NScene::IScene* _scene )
{
  if( !MinigameBase::Init( _minigames, _scene ) )
    return false;

	pDBClinic = NDb::Get<NDb::DBMinigame_Clinic>( NDb::DBID( "Minigames/MiniGame01/Description/ClinicDescription.xdb" ) );

	NI_VERIFY( !pDBClinic.IsEmpty(), "DB resource for 'Clinic' minigame should be valid", return false );

  levelCompletion.resize(pDBClinic->levels.size());

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::ItemCanBeBought(ClinicItem * clinicItem, bool ignorePrice) const
{
  if(clinicItem->IsBought())
    return false;
  if(IsShopCheatOn())
    return true;
  if(!ignorePrice)
    if(clinicItem->GetCost() > GetGold())
      return false;
  return clinicItem->GetAccessibility() <= GetMaxAvailableLevel();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::BuyItem(ClinicItem * clinicItem, bool correctOther /*= true*/)
{
  if(!ItemCanBeBought(clinicItem, false))
    return false;

	TakeGold( clinicItem->GetCost() );

	clinicItem->SetBought( true );

  RecalcPurchasedBonusesAndPlaces();

	if ( correctOther )
		PrepareClientObjectsForShop( true );

	MinigameClientObject * clientObject = GetClientObject( clinicItem->GetObjectID() );
	clientObject->SetMulColor( Render::HDRColor(1.f, 1.f, 1.f, 1.f) );
	clientObject->SetVisible( true );
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::RecalcPurchasedBonusesAndPlaces()
{
  for(int i = 0; i < NDb::KnownEnum<NDb::EPlaceType>::sizeOf; ++i)
    placeTypesBought[i] = 0;
	for(int i = 0; i < NDb::KnownEnum<NDb::EBonusType>::sizeOf; ++i)
		bonusTypeBought[i] = false;

  for(ClinicPlaces::iterator it = clinicPlaces.begin(); it != clinicPlaces.end(); ++it)
    if(it->second->IsBought())
      placeTypesBought[it->second->GetType()]++;

  for( ClinicBonuses::iterator it = clinicBonuses.begin(); it != clinicBonuses.end(); ++it )
    if( it->second->IsBought() )
      bonusTypeBought[it->second->GetType()] = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Clinic::GetClickBonusValue()
{
	return pDBClinic->clickBonusValue;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Clinic::GetPlayerVelocity()
{
	return pDBClinic->player.velocity;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::CreepBehaviourDesc* Clinic::GetCreepBehaviourDesc()
{
	return &pDBClinic->creepBehaviourDesc;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::DBMinigame_Clinic* Clinic::GetClinicDesc()
{
	return pDBClinic;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::InitGeometry( const CVec3& _pos, const CVec3& _scale )
{
	placePos = _pos;
	placeScale = _scale;

	// player
	{
    EraseClientObject( player );

		Placement placement = NULLPLACEMENT;
		GetWorldPlacement( pDBClinic->player.startPosition, placement );

    if( !IsValid( player ) )
    {
		  player = CreateWorldObject<ClinicPlayer>();
		  player->SetClinic( this );
    }
    player->SetPlacement( placement );

    //Players do not need DbSceneObjects, they do take it from session
		ClinicPlayerClientObject * playerClient =
      InitClientObject<ClinicPlayerClientObject>( player, 0, pDBClinic->player.startPosition, false );
    playerClient->InitClinicPlayer( player );
	}

	// places
	nstl::vector<int> logicToWorldIDMap( pDBClinic->places.size(), -1 );

	for ( int i = 0; i < pDBClinic->places.size(); ++i )
	{
		Placement placement = NULLPLACEMENT;
		GetWorldPlacement( pDBClinic->places[i].position, placement );

 		if ( NDb::PLACETYPE_ENTRANCE == pDBClinic->places[i].placeType )
 		{
      EraseClientObject( entrance );
      if( !IsValid( entrance ) )
      {
 			  entrance = CreateWorldObject<ClinicEntrance>();
 			  entrance->SetClinic( this );
        entrance->SetPlaceDesc( &pDBClinic->places[i] );
      }
      entrance->SetPlacement( placement );

 			ClinicEntranceClientObject * clientEntrance = 
        InitClientObject<ClinicEntranceClientObject>( entrance, pDBClinic->places[i].sceneObject, pDBClinic->places[i].position );
      clientEntrance->InitClinicEntrance( entrance );

			logicToWorldIDMap[i] = entrance->GetObjectID();
 		}
 		else
		{
      ClinicPlaces::iterator it = clinicPlaces.find( i );
      CPtr<ClinicPlace> clinicPlace = ( it == clinicPlaces.end() ) ? 0 : it->second;

      EraseClientObject( clinicPlace );

      if( !IsValid( clinicPlace ) )
      {
        clinicPlace = CreateWorldObject<ClinicPlace>();
			  clinicPlace->SetPlaceDesc( &pDBClinic->places[i] );
			  clinicPlace->SetClinic( this );
			  clinicPlace->SetBought( pDBClinic->places[i].accessibility == -1 );
      }
      clinicPlace->SetPlacement( placement );

			if (clinicPlace->IsBought())
				placeTypesBought[clinicPlace->GetType()]++;

      NI_ASSERT( IsValid( pDBClinic->places[i].sceneObjectDirty50 ) && IsValid( pDBClinic->sceneObjectDirty100 ), "Dirty Objects are not defined" );

			ClinicPlaceClientObject * clientPlace = 
        InitClientObject<ClinicPlaceClientObject>( clinicPlace, pDBClinic->places[i].sceneObject, pDBClinic->places[i].position );
      clientPlace->InitClinicPlace( clinicPlace, pDBClinic->places[i].sceneObjectDirty50, pDBClinic->sceneObjectDirty100 );
      clinicPlaces.insert( ClinicPlaces::value_type( i, clinicPlace ) );

		  logicToWorldIDMap[i] = clinicPlace->GetObjectID();

      clientPlace->SetVisible( pDBClinic->places[i].accessibility == -1 );
		}
	}

  // neighbourhood
  if( neighbours.empty() )
	{
    neighbours.reserve(2 * pDBClinic->neighbourhood.size());

		for (int i = 0; i < pDBClinic->neighbourhood.size(); ++i)
		{
      int first = logicToWorldIDMap[pDBClinic->neighbourhood[i].first];
      int second = logicToWorldIDMap[pDBClinic->neighbourhood[i].second];

			NI_ASSERT( first != -1 && second != -1, "Can't find neighbour");

      neighbours.push_back( TNeighbours::value_type( first, second ) );
			neighbours.push_back( TNeighbours::value_type( second, first ) );
		}
	}

	// bonuses
  NI_VERIFY( pDBClinic->bonuses.size() == NDb::KnownEnum<NDb::EBonusType>::sizeOf, "Invalid clinic bonuses data", return );
  for( int i = 0; i < pDBClinic->bonuses.size(); ++i )
    InitBonusObject( (NDb::EBonusType)i, &pDBClinic->bonuses[i] );

  // decorations
	for ( int i = 0; i < pDBClinic->decorations.size(); ++i)
		InitClientObject<ClinicDecorationClientObject>( 0, pDBClinic->decorations[i].sceneObject, pDBClinic->decorations[i].position, false );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicBonus* Clinic::InitBonusObject( NDb::EBonusType _type, const NDb::BonusDesc* _bonusDesc )
{
	Placement placement;
	GetWorldPlacement( _bonusDesc->position, placement );

  ClinicBonuses::iterator it = clinicBonuses.find( _type );
  CPtr<ClinicBonus> clinicBonus = ( it == clinicBonuses.end() ) ? 0 : it->second;

  EraseClientObject( clinicBonus );

  if ( !IsValid( clinicBonus ) )
  {
	  clinicBonus = CreateWorldObject<ClinicBonus>();
    clinicBonus->SetClinic( this );
    clinicBonus->SetBonusDesc( _type, _bonusDesc );
    clinicBonus->SetBought( _bonusDesc->accessibility == -1 );
	  clinicBonus->SetCanBeBought( _bonusDesc->accessibility != -2 );
  }

	clinicBonus->SetPlacement( placement );

  bonusTypeBought[ _type ] = clinicBonus->IsBought();
	bonuses[ _type ] = clinicBonus;

	ClinicBonusClientObject * clientObject =
    InitClientObject<ClinicBonusClientObject>( clinicBonus, _bonusDesc->sceneObject, _bonusDesc->position );
  clinicBonus->SetClientObject( clientObject );
  clientObject->InitClinicBonus( clinicBonus );
	clientObject->SetVisible( _bonusDesc->accessibility < 0 );

  clinicBonuses.insert( ClinicBonuses::value_type( _type,  clinicBonus ) );

	return clinicBonus;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::UpdateAllPositions( const CVec3 & _pos, const CVec3 & _scale )
{
  placePos = _pos;
	placeScale = _scale;

  //Player
  {
    NI_ASSERT( IsValid( player ), "" );
    Placement placement = NULLPLACEMENT;
		GetWorldPlacement( pDBClinic->player.startPosition, placement );

		player->SetPlacement( placement );

    MinigameClientObject * clPlayer = GetClientObject( player->GetObjectID() );
    NI_ASSERT( clPlayer, "" );

    clPlayer->SetPlacement( placement );
  }

  //GetClientObject();

  //Reset docarations
  for( ClientObjects::iterator it = clientObjects.begin(); it != clientObjects.end(); )
    if( it->first < 0 )
      it = clientObjects.erase( it );
    else
      ++it;

  for ( int i = 0; i < pDBClinic->decorations.size(); ++i)
		InitClientObject<ClinicDecorationClientObject>( 0, pDBClinic->decorations[i].sceneObject, pDBClinic->decorations[i].position, false );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::GetWorldPlacement( const CVec3& localGamePos, Placement& worldPlacement )
{
	CVec3 correctPos;

	correctPos.x = localGamePos.y;
	correctPos.y = -localGamePos.x;
	correctPos.z = localGamePos.z;

	worldPlacement.pos.Mul( placeScale, correctPos );
	worldPlacement.pos += placePos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicDecorationClientObject* Clinic::CreateDecoration( const NDb::DBSceneObject* _DBSceneObject )
{
  return InitClientObject<ClinicDecorationClientObject>( 0, _DBSceneObject, VNULL3, false );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::IsMinigameSceneObject( NScene::SceneObject* sceneObject )
{
	return minigameSceneObjects.find( sceneObject ) != minigameSceneObjects.end();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::InsertMinigameSceneObject( NScene::SceneObject* sceneObject )
{
  minigameSceneObjects.insert( sceneObject );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameWorldObject* Clinic::GetWorldObject( int _objectID )
{
	WorldObjects::iterator it = worldObjects.find( _objectID );

	if ( it != worldObjects.end() )
		return it->second;

	return 0 ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::MovePlayerTo( int _objectID, bool pushFront )
{
	CVec3 radius1 = GetClientObject( _objectID )->GetWorldAABB().halfSize;
	CVec3 radius2 = VNULL3; //GetClientObject( player->GetObjectID() )->GetWorldAABB().halfSize;

	radius1.z = 0.f;
	radius2.z = 0.f;

	float tolerance = fabs( radius1 ) + fabs( radius2 ); 

	player->MoveTo( GetWorldObject( _objectID ), pDBClinic->player.velocity, tolerance, pushFront );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::CancelPlayerQueue()
{
  player->CancelQueue();

  for ( ClinicBonuses::iterator it = clinicBonuses.begin(); it != clinicBonuses.end(); ++it )
    it->second->ClearInRoute();

  for ( ClinicPlaces::iterator it = clinicPlaces.begin(); it != clinicPlaces.end(); ++it)
    it->second->ClearInRoute();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clinic::FindExistedFriend( ClinicCreep* _creep )
{
	ClinicCreeps::iterator it = clinicCreeps.begin();
	ClinicCreeps::iterator last = clinicCreeps.end();

	for (; it != last; ++it)
	{
		if ( (*it)->GetObjectID() != _creep->GetObjectID() && (*it)->GetFriendshipID() == _creep->GetFriendshipID() )
			return (*it)->GetObjectID();
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clinic::FindFriend( int _creepID, int _placeID, int& _friendID )
{
  for(int i = 0; i < neighbours.size(); ++i)
  {
    if( neighbours[i].first != _placeID )
      continue;

    CDynamicCast<ClinicPlace> secondPlace = GetWorldObject( neighbours[i].second );

	  if ( !IsValid( secondPlace ) )
		  continue;

	  CDynamicCast<ClinicCreep> firstCreep = GetWorldObject( _creepID );

	  if ( !IsValid( firstCreep ) )
		  continue;

	  CPtr<ClinicCreep> otherCreep = secondPlace->GetOccupied();

	  if ( !IsValid( otherCreep ) )
		  continue;

	  if ( firstCreep->GetType() == otherCreep->GetType() )
		  continue;

	  if ( otherCreep->GetFriendshipID() == -1 && 
		  otherCreep->GetTimeAtOnePlace() > pDBClinic->creepBehaviourDesc.timeBeforeSearchFriend )
	  {
		  _friendID = otherCreep->GetObjectID();

		  otherCreep->SetFriendCreepID( _creepID );
		  otherCreep->SetFriendshipID( nextFriendshipID );

		  int _nextFriendshipID = nextFriendshipID;
		  nextFriendshipID++;

      PlaySound( NDb::CLINICSOUNDS_CREEPFRIENDSHIP );

		  return _nextFriendshipID;
	  }
  }

	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::CheckFriendIsNear( int _placeID, int _friendshipID )
{
  for(int i = 0; i < neighbours.size(); ++i)
  {
    if( neighbours[i].first != _placeID )
      continue;

    CDynamicCast<ClinicPlace> secondPlace = GetWorldObject( neighbours[i].second );

	  if ( !IsValid( secondPlace ) )
		  continue;

	  CPtr<ClinicCreep> otherCreep = secondPlace->GetOccupied();

	  if ( !IsValid( otherCreep ) )
		  continue;

	  if(otherCreep->GetFriendshipID() == _friendshipID)
      return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::EPlaceType Clinic::GetPlaceType( int _placeID )
{
	ClinicPlaces::iterator it = clinicPlaces.begin();
	ClinicPlaces::iterator last = clinicPlaces.end();

	for (; it != last; ++it)
	{
		if ( it->second->GetObjectID() == _placeID )
			return it->second->GetType();
	}

	return NDb::PLACETYPE_NONE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::StartClient()
{
	Strong<ClinicLobbyScreen> clinicLobbyScreen = new ClinicLobbyScreen();

	clinicLobbyScreen->SetMinigames( GetMinigames() );

	NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( clinicLobbyScreen ) );
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::Start( NWorld::PFMinigamePlace * place )
{
  NI_VERIFY( IsValid( place ), "Clinic: start minigame failed - minigame place is invalid", return false );
  Placement _placement = place->GetMinigamePlacement();
  _placement.scale *= 5;

  InitGeometry( _placement.pos, _placement.scale);

  if ( !clientInitialized )
  {
    InitSounds();
    clientInitialized = true;
  }
  else
  {
    for ( ClientObjects::iterator it = clientObjects.begin(); it != clientObjects.end(); ++it )
      it->second->SetVisible( true );

    PrepareClientObjectsForShop( false );
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::PrepareClientObjectForShop( int _objectID, bool _init, int _cost, int _accessLevel )
{
	CPtr<MinigameClientObject> clientObject = GetClientObject( _objectID );

	if ( IsValid( clientObject ) )
	{
    clientObject->SetVisible( false );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::PrepareClientObjectsForShop( bool _init )
{
	for ( ClinicPlaces::iterator it = clinicPlaces.begin(); it != clinicPlaces.end(); ++it )
	{
		if ( !it->second->IsBought() )
			PrepareClientObjectForShop( it->second->GetObjectID(), _init, it->second->GetCost(), it->second->GetAccessibility() );
	}

	for (ClinicBonuses::iterator it = clinicBonuses.begin(); it != clinicBonuses.end(); ++it)
	{
    ClinicBonus * bonus = it->second;
		if ( !bonus->IsBought() && bonus->CanBeBought() )
			PrepareClientObjectForShop( bonus->GetObjectID(), _init, bonus->GetCost(), bonus->GetAccessibility() );
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::FillCreepSpawnResults( MinigameCreeps& _spawnCreeps )
{
  CPtr<MinigamesMain> mgMain = GetMinigames()->GetNativeMain();

  ClinicCreeps::iterator it = clinicCreeps.begin();
  ClinicCreeps::iterator last = clinicCreeps.end();

  for (; it != last; ++it)
  {
    float barValue = (*it)->GetBarValue();

    MinigameCreepDesc creepDesc;

    if ( mgMain->GetCreepDesc( (*it)->GetPoolID(), creepDesc ) )
    {
      if ( barValue < 0.5f || gameMode != EClinicGameMode::GameIsWon || (*it)->GetCreepPhase() != ECreepPhase::IsTrained )
        creepDesc.isOut = false;
      else if ( barValue < 0.59f )
        creepDesc.statsModifiers = pDBClinic->trainingBonuses.statLifeBar50;
      else if ( barValue < 0.69f )
        creepDesc.statsModifiers = pDBClinic->trainingBonuses.statLifeBar59;
      else if ( barValue < 0.79f )
        creepDesc.statsModifiers = pDBClinic->trainingBonuses.statLifeBar69;
      else if ( barValue < 0.89f )
        creepDesc.statsModifiers = pDBClinic->trainingBonuses.statLifeBar79;
      else if ( barValue < 0.99f )
        creepDesc.statsModifiers = pDBClinic->trainingBonuses.statLifeBar89;
      else
        creepDesc.statsModifiers = pDBClinic->trainingBonuses.statLifeBar100;

      nstl::vector<float>::iterator itF = creepDesc.statsModifiers.begin();
      nstl::vector<float>::iterator lastF = creepDesc.statsModifiers.end();

      for (; itF != lastF; ++itF)
      {
        if ( *itF <= EPS_VALUE )
        {
          systemLog( NLogg::LEVEL_ASSERT ) << "Creep stats modifier in clinic is wrong" << endl;
          *itF = 1.f;
        }
      }

      _spawnCreeps.push_back( creepDesc );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::SpawnCreepsAtSession( const MinigameCreeps& _spawnCreeps )
{
  CPtr<MinigamesMain> mgMain = GetMinigames()->GetNativeMain();

  MinigameCreeps modifiedCreeps = _spawnCreeps;

  MinigameCreeps::iterator it = modifiedCreeps.begin();
  for ( ; it != modifiedCreeps.end(); )
  {
    if ( !it->isOut )    
    {
      mgMain->ReturnCreep( it->creepID );
      it = modifiedCreeps.erase( it );
    }
    else
    {
      ++it;
    }
  }

  //GetMinigames()->GetWorldSessionInterface()->SpawnCpreepWave( modifiedCreeps );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::Leave()
{
  for ( ClientObjects::iterator it = clientObjects.begin(); it != clientObjects.end(); ++it )
		it->second->SetVisible( false );

  // Pavel<GnoM>Cherniavski:
  // need to implement on external game end
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::ClearCreeps()
{
	ClinicCreeps::iterator it = clinicCreeps.begin();
	ClinicCreeps::iterator last = clinicCreeps.end();

	for (; it != last; ++it)
	{
		int objectID = (*it)->GetObjectID();

		RemoveWorldObject( objectID );
		RemoveClientObject( objectID );
	}

	clinicCreeps.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::InitSounds()
{
  for ( int i = 0; i < NDb::KnownEnum<NDb::EClinicSounds>::sizeOf; ++i )
  {
    if ( pDBClinic->sounds[i].IsEmpty() )
      continue;

    NI_DATA_VERIFY( !pDBClinic->sounds[i]->soundFile.empty(),
      NStr::StrFmt( "Sound file is not set in Sound2D resource for: <%s>", NDb::EnumToString( static_cast<NDb::EClinicSounds>(i) ) ),
      continue )
    sounds[i] = new NSound::Sound2D( pDBClinic->sounds[i]->soundFile, pDBClinic->sounds[i]->cycleCount, pDBClinic->sounds[i]->offset );
  }

  for ( int i = 0; i < NDb::KnownEnum<NDb::EBonusType>::sizeOf; ++i )
  {
    if ( pDBClinic->bonusSounds[i].IsEmpty() )
      continue;


    NI_DATA_VERIFY( !pDBClinic->bonusSounds[i]->soundFile.empty(),
      NStr::StrFmt( "Sound file is not set in Sound2D resource for: <%s>", NDb::EnumToString( static_cast<NDb::EClinicSounds>(i) ) ),
      continue )

    soundsForBonus[i] = new NSound::Sound2D( pDBClinic->bonusSounds[i]->soundFile, pDBClinic->bonusSounds[i]->cycleCount, pDBClinic->bonusSounds[i]->offset );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::PlaySound( NDb::EClinicSounds clinicSound )
{
  if ( !GetMinigames()->IsLocal() )
    return;

  if ( sounds[ clinicSound ] )  
    sounds[ clinicSound ]->Play();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::PlayBonusSound( NDb::EBonusType bonusSound )
{
  if ( !GetMinigames()->IsLocal() )
    return;

  if ( soundsForBonus[ bonusSound ] )  
    soundsForBonus[ bonusSound ]->Play();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::StartShop()
{
  NI_ASSERT(gameMode == EClinicGameMode::None, "");

	gameMode = EClinicGameMode::Shop;
	PrepareClientObjectsForShop( true );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::StartLevel( int _levelID )
{
  NI_ASSERT(gameMode == EClinicGameMode::None, "");

	if ( !IsValid( pDBClinic ) )
		return false;

	if ( _levelID < 0 || _levelID >= pDBClinic->levels.size() )
		return false;

	Clear();

	levelID = _levelID;

  levelCompletion[levelID].lastStatus = EClinicLevelStatus::Incomplete;
  levelCompletion[levelID].goldMade = 0;

	const NDb::LevelDesc& levelDesc = pDBClinic->levels[levelID];

	entrance->SetCreepsNumber( levelDesc.numberOfMelee, levelDesc.numberOfRange, levelDesc.numberOfSiege );

	levelDuration = pDBClinic->levels[levelID].duration;
	currentLevelTime = 0.f;
	nextFriendshipID = 0;
	isBellChiming = false;
	isCleaningStated = false; 

	LevelSpecificInit();

	gameMode = EClinicGameMode::Game;

  StartLevelClient();

	return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::StopLevel( const MinigameCreeps& _spawnCreeps )
{
  NI_ASSERT(gameMode != EClinicGameMode::None, "");

	if ( gameMode == EClinicGameMode::Shop )
		PrepareClientObjectsForShop( false );

  SpawnCreepsAtSession( _spawnCreeps );
  Clear();
	ClearCreeps();

	gameMode = EClinicGameMode::None;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::LevelSpecificInit()
{
	switch ( levelID )
	{
	case 5:
		{
			ClinicPlaces::iterator it = clinicPlaces.begin();
			ClinicPlaces::iterator last = clinicPlaces.end();

			for (; it != last; ++it)
			{
				if ( NDb::PLACETYPE_CREEPPLACE != it->second->GetType() && NDb::PLACETYPE_ENTRANCE != it->second->GetType() )
					it->second->SetSoil( pDBClinic->level6_soilAtStart / 100.f );
			}

			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::StartLevelClient()
{
  PlaySound( NDb::CLINICSOUNDS_STARTLEVEL );

  if( IsValid( overtips ) )
  {
    //Create overtips for places
    for( ClinicPlaces::iterator place = clinicPlaces.begin(); place != clinicPlaces.end(); ++place )
      if( MinigameClientObject * clPlace = GetClientObject( place->second->GetObjectID() ) )
        clPlace->CreateOvertip( overtips, place->second->GetPlaceDesc()->overtip );

    //Create overtips for Entrance
    if( IsValid( entrance ) )
      if( MinigameClientObject * clEntr = GetClientObject( entrance->GetObjectID() ) )
        clEntr->CreateOvertip( overtips, entrance->GetPlaceDesc()->overtip );

    //Create overtips for bonuses
    for( ClinicBonuses::iterator bonus = clinicBonuses.begin(); bonus != clinicBonuses.end(); ++bonus )
      if( MinigameClientObject * clBonus = GetClientObject( bonus->second->GetObjectID() ) )
        clBonus->CreateOvertip( overtips, bonus->second->GetBonusDesc()->overtip );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameClientObject* Clinic::GetClientObject( int objID ) const
{
	ClientObjects::const_iterator found = clientObjects.find( objID );

	if ( found != clientObjects.end() )
		return found->second;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameWorldObject* Clinic::GetWorldObject( int objID ) const
{
	WorldObjects::const_iterator found = worldObjects.find( objID );

	if ( found != worldObjects.end() )
		return found->second;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::EraseClientObjectById( int objId )
{
  ClientObjects::iterator found = clientObjects.find( objId );

	if ( found != clientObjects.end() )
    clientObjects.erase( found );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::EraseClientObject( MinigameWorldObject * worldObject )
{
  if( !IsValid( worldObject ) )
    return;
  EraseClientObjectById( worldObject->GetObjectID() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicCreep*  Clinic::InitCreepOfType( ECreepType::Enum type, const Placement& placement )
{
	MinigameCreepDesc creepDesc;

  int priestessID = GetMinigames()->GetWorldSessionInterface()->GetPriestessID();

	GetMinigames()->GetNativeMain()->GetFreeCreep( priestessID, type, creepDesc );

	if ( -1 == creepDesc.creepID )
		return 0;

	CPtr<ClinicCreep> newCreep = CreateWorldObject<ClinicCreep>();
	newCreep->SetClinic( this );
	newCreep->SetType( type );
	newCreep->SetPlacement( placement );
	newCreep->SetName( creepDesc.name );
  newCreep->SetPoolID( creepDesc.creepID );

  ClinicCreepClientObject * clientObject = NULL;

	switch (type)
	{
	case ECreepType::Melee:
		clientObject = InitClientObject<ClinicCreepClientObject>( newCreep, pDBClinic->creepsDesc.sceneObjectMelee, placement.pos, true ); 
    break;
	case ECreepType::Range:
		clientObject = InitClientObject<ClinicCreepClientObject>( newCreep, pDBClinic->creepsDesc.sceneObjectRange, placement.pos, true ); 
    break;
	case ECreepType::Siege:
		clientObject = InitClientObject<ClinicCreepClientObject>( newCreep, pDBClinic->creepsDesc.sceneObjectSiege, placement.pos, true ); 
    break;
	}

  if (clientObject)
  {
    clientObject->InitClinicCreep( newCreep );
    clientObject->SetPlacement( placement );
    if ( IsValid( overtips ) )
      clientObject->CreateOvertip( overtips, pDBClinic->creepsDesc.overtip );
  }

  clinicCreeps.push_back( newCreep );

	return newCreep;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::BaseUIMaterial* Clinic::GetImageOfCreepType( ECreepType::Enum type ) const
{
  switch (type)
	{
	  case ECreepType::Melee:
      return pDBClinic->creepsDesc.imageMeleeMaterial;
	  case ECreepType::Range:
      return pDBClinic->creepsDesc.imageRangeMaterial;
	  case ECreepType::Siege:
      return pDBClinic->creepsDesc.imageSiegeMaterial;
	}

  return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::Step( float deltaTime )
{
	if ( EClinicGameMode::None == gameMode )
		return;

  {
		WorldObjects::iterator it = worldObjects.begin();
		WorldObjects::iterator last = worldObjects.end();

		for (; it != last; ++it)
		{
			it->second->Step( deltaTime );
		}
	}

	if ( ( currentLevelTime >	levelDuration ) && ( EClinicGameMode::Game == gameMode ) )
	{
		gameMode = EClinicGameMode::GameFinished;
		entrance->StopQueue();
		GetClientObject( entrance->GetObjectID() )->SetVisible( true );
	}

	if ( EClinicGameMode::Game == gameMode )
		currentLevelTime += deltaTime;

	CheckGameMode();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::Update( float deltaTime, bool gameOnPause )
{
  ClientObjects::iterator it = clientObjects.begin();
  ClientObjects::iterator last = clientObjects.end();

  for (; it != last; ++it)
  {
    it->second->Update( deltaTime, gameOnPause );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::DBID & Clinic::GetDBID() const
{
  if( pDBClinic )
    return pDBClinic->GetDBID();
  else
    return MinigameBase::getDBID();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::PlaceUnderFogOfWar( bool underFogOfWar )
{
  //TODO:...
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::CheatDropCooldowns()
{
  //TODO:...
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::SessionFinished( bool victory )
{
  //TODO:...
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::CheckGameMode()
{
	if ( EClinicGameMode::Shop == gameMode )
		return true;

  if ( EClinicGameMode::GameIsWon == gameMode || EClinicGameMode::GameIsLosed == gameMode )
    return false;

  int numCreepsFled = 0;
	int numCreepsTrained = 0;

	ClinicCreeps::iterator it = clinicCreeps.begin();
	ClinicCreeps::iterator last = clinicCreeps.end();

	for (; it != last; ++it)
	{
		if ( ECreepPhase::IsFled == (*it)->GetCreepPhase() )
			numCreepsFled++;

		if ( ECreepPhase::IsTrained == (*it)->GetCreepPhase() )
			numCreepsTrained++;
	}

  if ( ( gameMode == EClinicGameMode::GameFinished ) && ( numCreepsFled + numCreepsTrained ) >= clinicCreeps.size() )
	{
		if ( numCreepsFled == clinicCreeps.size())
		{
			gameMode = EClinicGameMode::GameIsLosed;
		}
		else
		{
      bool giveOutAwards = (gameMode == EClinicGameMode::GameFinished); //Time has ran out
			gameMode = EClinicGameMode::GameIsWon;
      OnLevelIsWon(giveOutAwards);
		}

		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::OnLevelIsWon( bool giveOutAwards )
{
  float levelGoldMade = pDBClinic->levels[levelID].levelFinishMoney;

	AddGold(levelGoldMade);
	//AddExperience( pDBClinic->levels[levelID].levelFinishBonus );
	
  int goldMeds = 0, silverMeds = 0;
	for (ClinicCreeps::iterator it = clinicCreeps.begin(); it != clinicCreeps.end(); ++it)
	{
    ClinicCreep * creep = *it;
    float barValue = creep->GetBarValue();

    float gold = 0;
    if ( giveOutAwards && barValue >= pDBClinic->creepsDesc.goldMedalValue )
    {
      creep->SetAward(EClinicCreepAward::GoldMedal);
      gold = pDBClinic->levels[levelID].creepMedalMoney * 1.25f;
      ++goldMeds;
    }
    else if ( giveOutAwards && barValue >= pDBClinic->creepsDesc.silverMedalValue )
    {
      creep->SetAward(EClinicCreepAward::SilverMedal);
      gold = pDBClinic->levels[levelID].creepMedalMoney;
      ++silverMeds;
    }
    else
      creep->SetAward(EClinicCreepAward::None);

    if(gold)
    {
      AddGold(gold);
      creep->SetGoldMadeInLevel(gold);
    }
	}

  //FIXME: one can use floats?
  SLevelCompletionInfo & levelInfo = levelCompletion[levelID];
  if ( goldMeds * 2 >= clinicCreeps.size() )
  {
    levelInfo.lastStatus = EClinicLevelStatus::GoldMedal;
    PlaySound( NDb::CLINICSOUNDS_LEVELWINWITHMEDAL );
  }
  else if( ( silverMeds + goldMeds ) * 2 >= clinicCreeps.size() )
  {
    levelInfo.lastStatus = EClinicLevelStatus::SilverMedal;
    PlaySound( NDb::CLINICSOUNDS_LEVELWINWITHMEDAL );
  }
  else
  {
    levelInfo.lastStatus = EClinicLevelStatus::Complete;
    PlaySound( NDb::CLINICSOUNDS_LEVELWINWITHOUTMEDAL );
  }

  //Session statistics notification
  EMinigameLevelStatus::Enum pfMgLevelStatus = EMinigameLevelStatus::Failed;
  switch ( levelInfo.lastStatus )
  {
    case EClinicLevelStatus::GoldMedal:
      pfMgLevelStatus = EMinigameLevelStatus::Gold;
      break;
    case EClinicLevelStatus::SilverMedal:
      pfMgLevelStatus = EMinigameLevelStatus::Silver;
      break;
    case EClinicLevelStatus::Complete:
      pfMgLevelStatus = EMinigameLevelStatus::Done;
      break;
    case EClinicLevelStatus::Incomplete:
      pfMgLevelStatus = EMinigameLevelStatus::Failed;
      break;
  }

  bool lastLevel = (levelID == pDBClinic->levels.size() - 1);

  GetStatistics()->MinigameLevelEnded( pDBClinic->GetDBID(), GetPriestessId(), levelID, pfMgLevelStatus, lastLevel );

  //ѕроверим, не победили ли мы всю клинику
  if( levelID == levelCompletion.size() - 1 )
    if( ( levelInfo.bestStatus == EClinicLevelStatus::Incomplete ) && ( levelInfo.lastStatus != EClinicLevelStatus::Incomplete ) )
      GetStatistics()->MinigameComplete( pDBClinic->GetDBID(), GetPriestessId() );

  //Update status
  levelInfo.bestStatus = Max(levelInfo.bestStatus, levelInfo.lastStatus);

  levelInfo.goldMade = levelGoldMade;

	if ( levelID == nextLevelID )
		nextLevelID = min(nextLevelID + 1, pDBClinic->levels.size() - 1);

	AutoBuyPlacesBonuses();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::OnCreepSatisfied()
{
  //AddExperience( pDBClinic->levels[levelID].creepTraindedBonus );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::AutoBuyPlacesBonuses()
{
  giftedPlaces.clear();

	{
		ClinicPlaces::iterator it = clinicPlaces.begin();
		ClinicPlaces::iterator last = clinicPlaces.end();

		for (; it != last; ++it)
		{
			if ( !it->second->IsBought() && it->second->GetCost() == 0 && it->second->GetAccessibility() <= GetMaxAvailableLevel() )
        if(BuyItem( it->second, false ))
          giftedPlaces.insert(*it);
		}
	}

// 	{
// 		ClinicBonuses::iterator it = clinicBonuses.begin();
// 		ClinicBonuses::iterator last = clinicBonuses.end();
// 
// 		for (; it != last; ++it)
// 		{
// 			if ( !(*it)->IsBought() && (*it)->GetCost() == 0 && (*it)->GetAccessibility() <= GetMaxAvailableLevel() )
// 				BuyBonus(*it);
// 		}
// 	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::OnWakeAll()
{
	ClinicCreeps::iterator it = clinicCreeps.begin();
	ClinicCreeps::iterator last = clinicCreeps.end();

	for (; it != last; ++it)
	{
		(*it)->OnWakeUp();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::OnStartBell( bool start )
{
	isBellChiming = start;

	if (isBellChiming)
		OnWakeAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::OnCleanAll( bool start )
{
	isCleaningStated = start;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::OnStarBonus()
{
  bonuses[NDb::BONUSTYPE_BELL]->StartBonus();
  bonuses[NDb::BONUSTYPE_SUPERCLEANER]->StartBonus();

	ClinicCreeps::iterator it = clinicCreeps.begin();
	ClinicCreeps::iterator last = clinicCreeps.end();

	for (; it != last; ++it)
	{
		bonuses[NDb::BONUSTYPE_CANDY]->UseOnCreep( *it, true );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clinic::GetLevelNumber()
{
	return  pDBClinic->levels.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::GetLevelUIDesc(ClinicLevelUIDesc * pLevelDesc, int _levelID)
{
  if(_levelID < 0)
    _levelID = levelID;
	pLevelDesc->name = pDBClinic->levels[_levelID].name.GetText();
	pLevelDesc->desc = pDBClinic->levels[_levelID].description.GetText();
  pLevelDesc->lastStatus = levelCompletion[_levelID].lastStatus;
  pLevelDesc->bestStatus = levelCompletion[_levelID].bestStatus;
	//pLevelDesc->available = ( GetExperience() >= pDBClinic->levels[_levelID].expToOpen );
  pLevelDesc->goldMade = levelCompletion[_levelID].goldMade;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clinic::GetMaxAvailableLevel() const
{
	int numLevels = pDBClinic->levels.size();

	for ( int i = 0; i < numLevels; ++i)
	{
/*		if ( pDBClinic->levels[i].expToOpen > GetExperience() )
		{
			return i;
		}*/
	}

	return numLevels;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicPlayer* Clinic::GetPlayer()
{
	return player;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Placement& Clinic::GetExitPlacement()
{
	return entrance->GetPlacement();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::FillCreepResults( ClinicCreepsUIDesc & _descriptions )
{
	_descriptions.resize( clinicCreeps.size() );

	ClinicCreepsUIDesc::iterator dest = _descriptions.begin();

	for (ClinicCreeps::iterator it = clinicCreeps.begin(); it != clinicCreeps.end(); ++it, ++dest)
	{
    ClinicCreep * creep = *it;
    dest->creepName = creep->GetName();
    dest->imageMaterial = GetImageOfCreepType(creep->GetType());
		dest->barValue = creep->GetBarValue();
    dest->goldMade = creep->GetGoldMadeInLevel();
		dest->isFled = (ECreepPhase::IsFled == creep->GetCreepPhase());
    dest->award = creep->GetAward();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Clinic::IsWishAvailable( NDb::EPlaceType _placeType, NDb::ECreepWish _wishType )
{
  if ( placeTypesBought[_placeType] <= 0 )
    return false;

  if ( !pDBClinic->levels[levelID].casualWishGeneration )
    return placeTypesBought[_placeType] > 0;

  int wishCount[NDb::KnownEnum<NDb::EPlaceType>::sizeOf];

  for (int i = 0; i < NDb::KnownEnum<NDb::EPlaceType>::sizeOf; ++i)
  {
    wishCount[i] = 0;
  }

  ClinicCreeps::iterator it = clinicCreeps.begin();
  ClinicCreeps::iterator last = clinicCreeps.end();

  for (; it != last; ++it)
  {
    ++wishCount[(*it)->GetCreepWish()];
  }

  if ( wishCount[_wishType] < placeTypesBought[_placeType] )  
    return true;

  bool allIsOccupied = (wishCount[NDb::CREEPWISH_EAT] >= placeTypesBought[NDb::PLACETYPE_TABLE]);
  allIsOccupied &= (wishCount[NDb::CREEPWISH_SLEEP] >= placeTypesBought[NDb::PLACETYPE_BAD]);
  allIsOccupied &= (wishCount[NDb::CREEPWISH_WASH] >= placeTypesBought[NDb::PLACETYPE_WASHTAB]);
  allIsOccupied &= (wishCount[NDb::CREEPWISH_PLAY] >= placeTypesBought[NDb::PLACETYPE_GAMEPLACE]);

  return allIsOccupied; // if all is occupied then use any
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::GetWishProbabilities( WishProbabilities _wishProbabilities, NDb::ECreepWish exclude )
{
	for (int i = 0; i < NDb::KnownEnum<NDb::ECreepWish>::sizeOf; ++i)
		_wishProbabilities[i] = 0.f;

	if ( EClinicGameMode::GameFinished == gameMode )
	{
		_wishProbabilities[NDb::CREEPWISH_EXIT] = 1.f;
		return;
	}

	float numDifferentTypes = 0.f;

  if ( NDb::CREEPWISH_CARPET != exclude ) numDifferentTypes += 1.f;
	if ( IsWishAvailable(NDb::PLACETYPE_TABLE, NDb::CREEPWISH_EAT) && NDb::CREEPWISH_EAT != exclude ) numDifferentTypes += 1.f;
	if ( IsWishAvailable(NDb::PLACETYPE_BAD, NDb::CREEPWISH_SLEEP) && NDb::CREEPWISH_SLEEP != exclude ) numDifferentTypes += 1.f;
  if ( IsWishAvailable(NDb::PLACETYPE_WASHTAB, NDb::CREEPWISH_WASH) && NDb::CREEPWISH_WASH != exclude ) 
    numDifferentTypes += ( 3 == levelID ) ? pDBClinic->level4_washProbTimes  : 1.f;
  if ( IsWishAvailable(NDb::PLACETYPE_GAMEPLACE, NDb::CREEPWISH_PLAY) && NDb::CREEPWISH_PLAY != exclude ) 
    numDifferentTypes += ( 9 == levelID ) ? pDBClinic->level10_playProbTimes  : 1.f;

	if ( numDifferentTypes > 0.f )
	{
		if ( 8 == levelID && numDifferentTypes > 1.f && IsWishAvailable(NDb::PLACETYPE_WASHTAB, NDb::CREEPWISH_WASH) )
			numDifferentTypes = 0.2f / (numDifferentTypes - 1.f); 
		else
			numDifferentTypes = 1.f / numDifferentTypes; 

    if ( NDb::CREEPWISH_CARPET != exclude ) _wishProbabilities[NDb::CREEPWISH_CARPET] = numDifferentTypes;

    if ( IsWishAvailable(NDb::PLACETYPE_TABLE, NDb::CREEPWISH_EAT) && NDb::CREEPWISH_EAT != exclude ) _wishProbabilities[NDb::CREEPWISH_EAT] = numDifferentTypes;
		if ( IsWishAvailable(NDb::PLACETYPE_BAD, NDb::CREEPWISH_SLEEP) && NDb::CREEPWISH_SLEEP != exclude ) _wishProbabilities[NDb::CREEPWISH_SLEEP] = numDifferentTypes;
		if ( IsWishAvailable(NDb::PLACETYPE_WASHTAB, NDb::CREEPWISH_WASH) && NDb::CREEPWISH_WASH != exclude )
		{
			if ( 8 == levelID )
			{
				_wishProbabilities[NDb::CREEPWISH_WASH] = pDBClinic->level9_washProb / 100.f;
			}
			else
			{
				_wishProbabilities[NDb::CREEPWISH_WASH] = numDifferentTypes;

				if ( 3 == levelID )
					_wishProbabilities[NDb::CREEPWISH_WASH] *= pDBClinic->level4_washProbTimes;
			}
		}

		if ( IsWishAvailable(NDb::PLACETYPE_GAMEPLACE, NDb::CREEPWISH_PLAY) && NDb::CREEPWISH_PLAY != exclude ) 
		{
	  	_wishProbabilities[NDb::CREEPWISH_PLAY] = numDifferentTypes;

			if ( 9 == levelID )
				_wishProbabilities[NDb::CREEPWISH_PLAY] *= pDBClinic->level10_playProbTimes;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::AddGold( int _amount ) 
{ 
  GetMinigames()->GetWorldSessionInterface()->AddGold( _amount );
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Clinic::GetGold() const 
{ 
  return GetMinigames()->GetWorldSessionInterface()->GetGold(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clinic::TakeGold( int _amount ) const
{
  GetMinigames()->GetWorldSessionInterface()->TakeGold( _amount );
}


} // namespace PF_Minigames
BASIC_REGISTER_CLASS(PF_Minigames::IClinicBuyUIRequest)
REGISTER_SAVELOAD_CLASS_NM(Clinic, PF_Minigames)

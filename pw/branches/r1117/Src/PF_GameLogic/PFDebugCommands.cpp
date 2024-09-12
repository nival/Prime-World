#include "stdafx.h"
#include "../System/Commands.h"
#include "AdventureScreen.h"

#include "PFCommonCreep.h"
#include "PFClientCreep.h"
#include "PFTower.h"
#include "PFMainBuilding.h"
#include "PFPlayer.h"
#include "../Core/WorldCommand.h"

#ifndef _SHIPPING

#define CUSTOM_PARAMS_BASE 5

namespace
{
  bool GetBool( wstring const& wstr )
  {
    wstring selected;
    NStr::ToLower( &selected, wstr );
    return ( L"1" == selected || L"true" == selected );
  }
}

namespace NWorld
{

DEFINE_3_PARAM_CMD(0x2C739C00, CmdCreateUnit, vector<wstring>, params, CVec3, pickedPos, int, playerId);

class UnitCreator : NScene::ISceneObjectUpdateHook
{
  map<int, CPtr<PFLogicObject> > waitingSelection;

  UnitCreator() {}
  UnitCreator(UnitCreator const&);
  UnitCreator& operator = (UnitCreator const&);
  
  virtual bool OnSceneObjectBecomeVisible(NScene::SceneObject& sceneObject, float /*timeBeingInvisible*/);
  virtual void OnSceneObjectBecomeInvisible(NScene::SceneObject& /*sceneObject*/) {} 

  PFBaseUnit* CreateCreep( PFWorld* pWorld, NDb::Ptr<NDb::Unit> pDBUnit, CVec3 spawnPos, NDb::EFaction faction, vector<wstring> const& params );
  PFBaseUnit* CreateHero( PFWorld* pWorld, NDb::Ptr<NDb::Unit> pDBUnit, CVec3 spawnPos, NDb::EFaction faction, vector<wstring> const& params, int const localPlayerId );
  PFBaseUnit* CreateBuilding( PFWorld* pWorld, NDb::Ptr<NDb::Unit> pDBUnit, CVec3 spawnPos, NDb::EFaction faction, vector<wstring> const& params);
public:
  static UnitCreator& Instance() 
  { 
    static UnitCreator theInstance;
    return theInstance;
  }

  void CreateUnit( PFWorld* pWorld, vector<wstring> const& params, CVec3 const& pickedPos, int const playerId);
};

bool UnitCreator::OnSceneObjectBecomeVisible(NScene::SceneObject& sceneObject, float /*timeBeingInvisible*/)
{
  map<int, CPtr<PFLogicObject> >::iterator it = waitingSelection.find( sceneObject.GetOwnerID() );
  if( waitingSelection.end() != it )
  {
    if( NGameX::AdventureScreen* pAdvScreen =  NGameX::AdventureScreen::Instance() )
      pAdvScreen->SetSelectedObject( it->second.GetPtr(), &sceneObject);

    sceneObject.SetUpdateHook( NULL );
    waitingSelection.erase( it );
  }

  return true;
}

PFBaseUnit* UnitCreator::CreateCreep( PFWorld* pWorld, NDb::Ptr<NDb::Unit> pDBUnit, CVec3 spawnPosition, NDb::EFaction faction, vector<wstring> const& params )
{
  vector<CVec2> targets;
  for( int start = CUSTOM_PARAMS_BASE ; start + 2 <= params.size(); start += 2)
  {    
    targets.push_back();
    targets.back().x = NStr::ToFloat( params[ start ] );
    targets.back().y = NStr::ToFloat( params[ start + 1 ] );
  }

  return new PFCommonCreep( pWorld, *(dynamic_cast<NDb::AdvMapCreep const*>(pDBUnit.GetPtr())), faction, spawnPosition, targets );
}

PFBaseUnit* UnitCreator::CreateHero( PFWorld* pWorld, NDb::Ptr<NDb::Unit> pDBUnit, CVec3 spawnPos, NDb::EFaction faction, vector<wstring> const& params, int const localPlayerId )
{ 
  const int playersCount = pWorld->GetPlayersCount();
  int playerID = CUSTOM_PARAMS_BASE + 1 <= params.size() ? NStr::ToInt( params[CUSTOM_PARAMS_BASE] ) : -1;
  if( playersCount <= playerID )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Invalid player id <" << playerID << ">, defaulting to local" << endl;
    playerID = localPlayerId;
  }
  
  PFPlayer const* pLocalPlayer = pWorld->GetPlayer(localPlayerId);
  if(NULL == pLocalPlayer)
  {
    NI_ALWAYS_ASSERT("At least local player must present!");
    return NULL;
  }

  int inTeamId = CUSTOM_PARAMS_BASE + 2 <= params.size() ? NStr::ToInt( params[CUSTOM_PARAMS_BASE + 1] ) : NDb::TEAMCOLORID_HERO1;
  
  if( inTeamId < 0 || NDb::KnownEnum<NDb::ETeamColorID>::sizeOf <= inTeamId)
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Invalid teamId <" << inTeamId << ">, defaulting to \'hero1\'(" << NDb::TEAMCOLORID_HERO1 << ")!"<< endl;
    inTeamId = NDb::TEAMCOLORID_HERO1;
  }
    

  PFPlayer* pPlayer = (playerID < 0 || playersCount <= playerID ) ? NULL : pWorld->GetPlayer(playerID);
    
  PFBaseHero::SpawnInfo info;
  info.pHero     = dynamic_cast<NDb::BaseHero const*>(pDBUnit.GetPtr());
  info.playerId  = static_cast<NDb::EPlayerID>(playerID);
  info.placement = Placement(spawnPos, QNULL, CVec3(1.0f, 1.0f, 1.0f) );
  info.faction   = NDb::FACTION_NEUTRAL != faction ? faction : ( 0 == pLocalPlayer->GetTeamID() ? NDb::FACTION_FREEZE : NDb::FACTION_BURN );
  info.inTeamId  = inTeamId;
	info.isClone   = false;
  
  PFBaseHero* pOldHero = NULL;
  
  if( pPlayer )
  {
    NWorld::PFBaseHero* pOldHero = pPlayer->GetHero();
    pOldHero->DetachFromPlayer();
    pPlayer->DetachHero();
  }
  
  PFBaseHero* pNewHero = NWorld::CreateHero(pWorld, info);
  if( pPlayer )
  {
    if( NULL == pOldHero )
    {
      pPlayer->AttachHero(pOldHero);
      pOldHero->AttachToPlayer(pPlayer);
    }
    else
      pOldHero->DebugDie();
  }
  
  return pNewHero;
}

PFBaseUnit* UnitCreator::CreateBuilding( PFWorld* pWorld, NDb::Ptr<NDb::Unit> pDBUnit, CVec3 spawnPos, NDb::EFaction faction, vector<wstring> const& params )
{
  PFBaseUnit* pUnit = NULL;

  NDb::AdvMapObject fakeDBObject;
  fakeDBObject.gameObject = pDBUnit;
  fakeDBObject.offset     = spawnPos;
  
  const bool forceVulnerable = GetBool( CUSTOM_PARAMS_BASE + 1 <= params.size() ? params[CUSTOM_PARAMS_BASE] : L"1" );

  switch( pDBUnit->GetObjectTypeID() )
  {
  case NDb::Tower::typeId:
    pUnit = new PFTower( pWorld, fakeDBObject);
    break;
  case NDb::Quarter::typeId:
    pUnit = new PFQuarters( pWorld, fakeDBObject );
    break;
  case NDb::MainBuilding::typeId:
    pUnit = new PFMainBuilding( pWorld, fakeDBObject );
    break;
  case NDb::Fountain::typeId:
    pUnit = new PFFountain( pWorld, fakeDBObject );
    break;
  case NDb::Shop::typeId:
    pUnit = new PFShop( pWorld, fakeDBObject );
    break;
  case NDb::Building::typeId:
    pUnit = new PFSimpleBuilding( pWorld, fakeDBObject );
    break;
  default:
    systemLog( NLogg::LEVEL_MESSAGE ) << "Unsupported building type!" << endl;
  }
  
  if( pUnit && forceVulnerable )
    pUnit->SetVulnerable( true );

  return pUnit;
}


void UnitCreator::CreateUnit( PFWorld* pWorld, vector<wstring> const& params, CVec3 const& pickedPos, int const playerId)
{
  NDb::Ptr<NDb::Unit> pDBUnit = NDb::Get<NDb::Unit>( NDb::DBID( NStr::ToMBCS( params[0] ) ) );
  if( !IsValid( pDBUnit ) )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "resource <" <<  params[0] << "> doesn`t exist or is not unit derived!" << endl;
    return;
  }
  
  // prepare params
  // 1. acquire spawn position
  CVec3 spawnPosition = pickedPos;
  if( 3 <= params.size() )
  {
    spawnPosition.x = NStr::ToFloat( params[1] );
    spawnPosition.y = NStr::ToFloat( params[2] );
  }
  if( -1.0f == spawnPosition.x && -1.0f == spawnPosition.y )
    spawnPosition = pickedPos;

  // 2. get faction
  NDb::EFaction faction = NDb::FACTION_NEUTRAL;
  if( 4 <= params.size() )
  {
    if( L"A" == params[3] )
      faction = NDb::FACTION_FREEZE;
    else
    if( L"B" == params[3] )
      faction = NDb::FACTION_BURN;
    else
    if( L"N" == params[3] )
      faction = NDb::FACTION_NEUTRAL;
  }

  // 3. check if it need to be selected
  const bool select = GetBool( 5 <= params.size() ? params[4] : L"" );
  
  PFBaseUnit* pUnit = NULL;
  switch( pDBUnit->GetObjectTypeID() )
  {
  case NDb::AdvMapCreep::typeId:
    pUnit = CreateCreep(pWorld, pDBUnit, spawnPosition, faction, params );
    break;
  case NDb::Hero::typeId:
    pUnit = CreateHero( pWorld, pDBUnit, spawnPosition, faction, params, playerId );
    break;
  case NDb::Tower::typeId:
  case NDb::Quarter::typeId:
  case NDb::MainBuilding::typeId:
  case NDb::Fountain::typeId:
  case NDb::Shop::typeId:
  case NDb::Building::typeId:
    pUnit = CreateBuilding( pWorld, pDBUnit, spawnPosition, faction, params );
    break;
  default:
    systemLog( NLogg::LEVEL_MESSAGE ) << "Unsupported unit type!"<< endl;
    return;
  }
  
  if( pUnit && select )
  {
    NScene::SceneObject* pSO = pUnit ? ( pUnit->GetClientSceneObject() ) : NULL;
    if( pSO )
    {
      waitingSelection[pUnit->GetObjectId()] = pUnit;
      pSO->SetUpdateHook(this);
    }
  }
}

void CmdCreateUnit::Execute( NCore::IWorldBase* pIWorld )
{
  PFWorld* pWorld = dynamic_cast<PFWorld*>(pIWorld);
  if( NULL == pWorld )
    return;
  
  if( params.empty() )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: create_unit <path_to_unit_desc> [x y] [faction (A/B/N)] [selected] [[custom_params]...]" << endl;
    return;
  }
  
  UnitCreator::Instance().CreateUnit(pWorld, params, pickedPos, playerId);
}

bool CreateUnit( char const* name, vector<wstring> const& params )
{
  if( NGameX::AdventureScreen* pAdvScreen =  NGameX::AdventureScreen::Instance() )
    pAdvScreen->SendGameCommand( new CmdCreateUnit( params, pAdvScreen->GetCurrentPickedPos(), pAdvScreen->GetLocalPlayerID() ) );

  return true;
}

}; // namespace NWorld

REGISTER_DEV_CMD(create_unit, NWorld::CreateUnit );
REGISTER_SAVELOAD_CLASS_NM( CmdCreateUnit, NWorld )

#endif
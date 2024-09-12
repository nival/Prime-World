/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PFAdvMapObject.h"
#include "PFTree.h"
#include "TileMap.h"
#include "../Terrain/Terrain.h"
#include "WarFog.h"

#include "WarFog.h"

#ifndef VISUAL_CUTTED
#include "PFClientTree.h"
#else
#include "../Game/PF/Audit/ClientStubs.h"
#endif


namespace
{
  float g_fTreeGrowDelay    = 5.0f;
  float g_fTreeWaitFogDelay = 5.0f;
  bool  g_bOptimizeCRC      = true;
}

namespace NWorld
{

/////////////////////////////////////////////////////////////////////////////////
// Methods
/////////////////////////////////////////////////////////////////////////////////
PFTree::PFTree(PFWorld *pWorld, const NDb::AdvMapObject &dbObject)
  : PFLogicObject(pWorld, dbObject.offset.GetPlace().pos, static_cast<NDb::TreeObject const*>(dbObject.gameObject.GetPtr()))
  , currentState(stateNormal)
  , cooldown(0.0f)
  , dbObjectCopy(dbObject)
  , lastUpdateStepNum(0)
  , prevNatureType(0) // neutral
  , prevNight(false)
  , treeObjectTileSize(0.0f)
  , treeObjectDynTileSize(0)
  , treeObjectSize(0)
{
  NI_ASSERT( dynamic_cast<NDb::TreeObject const*>( dbObject.gameObject.GetPtr() ), "Bad cast to NDb::TreeObject!" );
  NDb::TreeObject const * pDesc = static_cast<NDb::TreeObject const*>( dbObject.gameObject.GetPtr() );

  const bool night = GetWorld()->IsNight();

  PFLogicObject::UpdateNatureType();
  PFLogicObject::UpdateDayNightState(night);
  CreateClientObject<NGameX::PFClientTree>( dbObject, pWorld->GetScene(), GetTerrainType() );

	CTRect<int> tileRegion;
 
  MarkObject(pWorld->GetTileMap(), dbObject, occupiedTiles, &tileRegion);
  pWorld->GetTileMap()->MarkObject(occupiedTiles, true, MAP_MODE_STATIC);
  pWorld->GetFogOfWar()->AddObstacle(occupiedTiles);

	InitData id;
  id.faction = NDb::FACTION_NEUTRAL;
  id.playerId = -1;
  id.pObjectDesc = pDesc;
  id.type = NDb::UNITTYPE_TREE;
  Initialize(id);

  wonderfulTree = pDesc->wonderfulTree;

  health = 1.0f;
  
  UpdateNatureType();
  UpdateDayNightState(night);

  CalculateSize(pWorld);
  UpdateSize(true);
}

void PFTree::Reset()
{
  if (currentState != stateNormal)
  {
    NGameX::PFClientTree* clientTree = static_cast<NGameX::PFClientTree*>( ClientObject() );
    if (clientTree)
    {
      clientTree->Switch2StubImmediately();
    }
  }

  // TODO: prevNatureType and prevNight ?
  CALL_CLIENT_2ARGS(SetState, natureType, GetWorld()->IsNight());
}

void PFTree::Hide( bool hide )
{
  MarkObject( GetWorld()->GetTileMap(), dbObjectCopy, occupiedTiles );
  GetWorld()->GetTileMap()->MarkObject( occupiedTiles, !hide, MAP_MODE_STATIC );

  if ( hide )
    GetWorld()->GetFogOfWar()->RemoveObstacle( occupiedTiles );
  else
    GetWorld()->GetFogOfWar()->AddObstacle( occupiedTiles );

  CALL_CLIENT_1ARGS(Hide, hide);
}

void PFTree::DropTree( const CVec2& dir, const CPtr<NWorld::PFBaseUnit>& pUnitThatDropsTree )
{
  if ( currentState != stateNormal )
  {
    return;
  }

  NGameX::PFClientTree* clientTree = static_cast<NGameX::PFClientTree*>( ClientObject() );
  clientTree->DropTree( dir, pUnitThatDropsTree );
  // unlock place on TileMap
  //!! NOTE: should use the same MAP_MODE_... as when marking tree on TileMap
  //   from function PFWorld::AddMapObject()
  GetWorld()->GetTileMap()->MarkObject( occupiedTiles, false, MAP_MODE_STATIC );
  GetWorld()->GetFogOfWar()->RemoveObstacle( occupiedTiles );
  cooldown = g_fTreeGrowDelay;
  currentState = stateGrowDelay;

  lastUpdateStepNum = GetWorld()->GetStepNumber();

	// I want to be stepped for some time
	GetWorld()->SubscribeObject( this );

  UpdateSize( false );

  health = 0.0f;
}

void PFTree::RestoreTree()
{
  NGameX::PFClientTree *clientTree = (NGameX::PFClientTree*)ClientObject();
  clientTree->RestoreTree();
  // lock place on TileMap
  GetWorld()->GetTileMap()->MarkObject(occupiedTiles, true, MAP_MODE_STATIC);
  GetWorld()->GetFogOfWar()->AddObstacle(occupiedTiles);
  currentState = stateNormal;

  lastUpdateStepNum = GetWorld()->GetStepNumber();

	// Don't want to recieve step
	GetWorld()->UnsubscribeObject(this);

  UpdateSize(true);

  health = 1.0f;
}

void PFTree::UpdateNatureType()
{
  PFLogicObject::UpdateNatureType();

  if (prevNatureType == natureType)
    return;

  prevNatureType = natureType;

  CALL_CLIENT_2ARGS(SetState, prevNatureType, prevNight);
}

void PFTree::UpdateDayNightState(const bool night)
{
  PFLogicObject::UpdateDayNightState(night);

  if (prevNight == night)
    return;

  prevNight = night;

  CALL_CLIENT_2ARGS(SetState, prevNatureType, prevNight);
}

bool PFTree::Step(float dtInSeconds)
{
  NI_PROFILE_FUNCTION
  
  if ( currentState == stateGrowDelay )
  {
    cooldown -= dtInSeconds;
    if (cooldown < 0)
    {
      currentState = stateWaitForFog;
      cooldown = g_fTreeWaitFogDelay;
    }
  }
  else if ( currentState == stateWaitForFog )
  {
      if ( wonderfulTree )
        RestoreTree();
      else
      {
        cooldown -= dtInSeconds;
        if (cooldown < 0)
        {
          FogOfWar * warfog = GetWorld()->GetFogOfWar();
          SVector pos = GetWorld()->GetTileMap()->GetTile(position.AsVec2D());
          bool anyoneSeeUs = warfog->IsTileVisible(pos, NDb::FACTION_FREEZE) || warfog->IsTileVisible(pos, NDb::FACTION_BURN);

          if ( anyoneSeeUs )
            cooldown = g_fTreeWaitFogDelay; // restart cooldown if stay visible
          else
            RestoreTree();
        }
      }
  }

  return true;
}

bool PFTree::NeedToSerialize()
{
  return (!g_bOptimizeCRC) || ( lastUpdateStepNum == GetWorld()->GetStepNumber() );
}

void PFTree::CalculateSize(PFWorld *pWorld)
{
  NDb::TreeObject const * pTreeObject = dynamic_cast<NDb::TreeObject const*>( dbObjectCopy.gameObject.GetPtr() );
  NI_VERIFY( pTreeObject, "Failed to downcast GameObject to TreeObject in PFTree!", return; );

  float fObjectSize = pTreeObject->lockMask.tileSize;

  if (fObjectSize <= 0)
  {
    NI_DATA_VERIFY( pTreeObject->sceneObjects.size() > 0 &&
                      pTreeObject->sceneObjects[0] && 
                      pTreeObject->sceneObjects[0]->attached.size() > 0 && 
                      pTreeObject->sceneObjects[0]->attached[0].component,
                      "Failed to retreive StaticSceneComponent from TreeObject!", 
                      return; );

    NDb::DBStaticSceneComponent const * pdbStaticSceneComponent;
    pdbStaticSceneComponent = dynamic_cast<NDb::DBStaticSceneComponent const *>(pTreeObject->sceneObjects[0]->attached[0].component.GetPtr());

    NI_VERIFY( pdbStaticSceneComponent,
                 "Failed to downcast first component of the TreeObject to StaticSceneComponent!", 
                 return; );

    NDb::AABB const * pAABB = &pdbStaticSceneComponent->aabb;

    if (pAABB->maxX != -666 && pAABB->minX != 666 && pAABB->maxY != -666 && pAABB->minY != 666)
    {
      fObjectSize = sqrt( fabs2(pAABB->maxX - pAABB->minX) + fabs2(pAABB->maxY - pAABB->minY) );
    }
  }

  const float fTileSize   = pWorld->GetTileMap()->GetTileSize();

  treeObjectTileSize    = (fTileSize == 0.0f) ? (0) : (ceil( fObjectSize / fTileSize ));
  treeObjectDynTileSize = treeObjectTileSize;
  treeObjectSize        = treeObjectTileSize * fTileSize; // rounded up to tile size
}

// bNormal=false means the tree is droped, so it should 
// report size=0, which is checked for units movment calculation
void PFTree::UpdateSize(bool bNormal)
{
  if (bNormal)
  { 
    SetObjectSizes(treeObjectSize, treeObjectTileSize, treeObjectDynTileSize);
  }
  else
  {
    SetObjectSizes(0.0f, 0, 0);
  }
}

bool PFTree::IsVisibleForFaction( int faction ) const
{
  SVector tilePos = GetWorld()->GetTileMap()->GetTile( GetPosition().AsVec2D() );
  return GetWorld()->GetFogOfWar()->IsTileVisible( tilePos, faction );
}


} // name space

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFTree, NWorld)
REGISTER_DEV_VAR("tree_grow_delay", g_fTreeGrowDelay, STORAGE_NONE);
REGISTER_DEV_VAR("tree_optimize_crc", g_bOptimizeCRC, STORAGE_NONE);
REGISTER_DEV_VAR("tree_wait_fog_delay", g_fTreeWaitFogDelay, STORAGE_NONE);
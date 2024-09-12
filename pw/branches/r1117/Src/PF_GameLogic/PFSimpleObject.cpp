#include "stdafx.h"
#include "PFAdvMapObject.h"
#include "PFSimpleObject.h"
#include "TileMap.h"
#include "WarFog.h"

#ifndef VISUAL_CUTTED
#include "PFSimpleObjectClient.h"
#include "PFClientMultistateObject.h"
#else
#include "PFLogicObject.h"
#include "../Game/pf/Audit/ClientStubs.h"
#endif
#include "System/InlineProfiler.h"

namespace NWorld
{

#define MARK_OBJECT_TILES_AND_WARFOG(pADO,mark)                                  \
  vector<SVector> occupiedTiles;                                                 \
  MarkObject(GetWorld()->GetTileMap(), dbObject, occupiedTiles);                 \
  GetWorld()->GetTileMap()->MarkObject(occupiedTiles, mark, MAP_MODE_BUILDING);  \
  if(pADO && pADO->opaque)                                                       \
  {                                                                              \
    if ( mark )                                                                  \
      GetWorld()->GetFogOfWar()->AddObstacle(occupiedTiles);                     \
    else                                                                         \
      GetWorld()->GetFogOfWar()->RemoveObstacle(occupiedTiles);                  \
  }

  
PFSimpleObject::PFSimpleObject(PFWorld* pWorld, const NDb::AdvMapObject &_dbObject)
: PFWorldObjectBase( pWorld, 1 )
, dbObject( _dbObject )
, isHidden(false)
{
  NDb::SimpleObject const *pSO = dynamic_cast<NDb::SimpleObject const *>(dbObject.gameObject.GetPtr());
  MARK_OBJECT_TILES_AND_WARFOG(pSO, true);

  CreateClientObject<NGameX::PFClientSimpleObject>(dbObject, pWorld->GetScene());
}

void PFSimpleObject::Hide(bool _hide)
{
  if (isHidden ^ _hide)
  {
    NDb::SimpleObject const *pSO = dynamic_cast<NDb::SimpleObject const *>(dbObject.gameObject.GetPtr());
    MARK_OBJECT_TILES_AND_WARFOG(pSO, !_hide);

    CALL_CLIENT_1ARGS(Hide, _hide);

    isHidden = _hide;
  }
}

void PFSimpleObject::Reset()
{
  // [AZ] no need to recreate client for SO
  if (isHidden)
  {
    CALL_CLIENT_1ARGS(Hide, isHidden);
  }
}

bool PFSimpleObject::Step( float )
{
  NI_PROFILE_FUNCTION
  
	CALL_CLIENT(DoFreeze);
	return true;
}

PFMultiStateObject::PFMultiStateObject(PFWorld* pWorld, const NDb::AdvMapObject &_dbObject)
: PFLogicObject(pWorld, _dbObject.offset.GetPlace().pos, _dbObject.gameObject)
, prevNatureType(0)
, prevNight(false)
, dbObject( _dbObject )
, isHidden(false)
{
  NDb::MultiStateObject const *pMSO = dynamic_cast<NDb::MultiStateObject const *>(dbObject.gameObject.GetPtr());
  MARK_OBJECT_TILES_AND_WARFOG(pMSO, true);

  const bool night = GetWorld()->IsNight();

  PFLogicObject::UpdateNatureType();
  PFLogicObject::UpdateDayNightState(night);
  CreateClientObject<NGameX::PFClientMultiStateObject>(pWorld->GetScene(), dbObject, GetTerrainType());
  
  InitData id;
  id.faction = NDb::FACTION_NEUTRAL;
  id.playerId = -1;
  id.pObjectDesc = dbObject.gameObject.GetPtr();
  id.type = NDb::UNITTYPE_SIMPLEOBJECT;
  Initialize(id);

  health = 1.0f;

  UpdateNatureType();
  UpdateDayNightState(night);

  NDb::DBSceneComponent const * pdbSceneComponent = GetDBSceneComponent();
  
  NDb::DBStaticSceneComponent const * pdbStaticSceneComponent;
  pdbStaticSceneComponent = dynamic_cast<NDb::DBStaticSceneComponent const *>(pdbSceneComponent);

  NDb::AABB const * pAABB = NULL;

  if (pdbStaticSceneComponent)
  {
    pAABB = &pdbStaticSceneComponent->aabb;
  }
  else
  {
    NDb::DBAnimatedSceneComponent const * pdbAnimatedSceneComponent;
    pdbAnimatedSceneComponent = dynamic_cast<NDb::DBAnimatedSceneComponent const *>(pdbSceneComponent);

    if (pdbAnimatedSceneComponent)
    {
      pAABB = &pdbAnimatedSceneComponent->aabb;
    }
    else
    {
      NDb::DBParticleSceneComponent const * pdbParticleSceneComponent;
      pdbParticleSceneComponent = dynamic_cast<NDb::DBParticleSceneComponent const *>(pdbSceneComponent);

      if (pdbParticleSceneComponent)
      {
        pAABB = &pdbParticleSceneComponent->aabb;
      }
    }
  }

  NI_VERIFY( pAABB, NStr::StrFmt("Failed to get AABB from MultiStateOnject! %s", pMSO->GetDBID().GetFileName().c_str()), return; );

  float fObjectSize = 0.0f;

  if (pAABB->maxX != -666 && pAABB->minX != 666 && pAABB->maxY != -666 && pAABB->minY != 666)
  {
    fObjectSize = sqrt( pow(pAABB->maxX - pAABB->minX, 2) + pow(pAABB->maxY - pAABB->minY, 2) );
  }

  const float fTileSize   = pWorld->GetTileMap()->GetTileSize();

  int objectTileSize    = (fTileSize == 0.0f) ? (0) : (ceil( fObjectSize / fTileSize ));
  int objectDynTileSize = objectTileSize;
  float objectSize      = objectTileSize * fTileSize; // rounded up to tile size

  SetObjectSizes(objectSize, objectTileSize, objectDynTileSize);
}

NDb::DBSceneComponent const * PFMultiStateObject::GetDBSceneComponent()
{
  NDb::MultiStateObject const *pMSO = dynamic_cast<NDb::MultiStateObject const *>(dbObject.gameObject.GetPtr());
  NDb::DBSceneObject const * pdbSceneObject;

  if (pMSO->sceneObjects.size() > 0 && !pMSO->sceneObjects[0].IsEmpty())
  {
    pdbSceneObject = pMSO->sceneObjects[0];
  }
  else if (pMSO->sceneObjects.size() > 1 && !pMSO->sceneObjects[1].IsEmpty())
  {
    pdbSceneObject = pMSO->sceneObjects[1];
  }
  else if (pMSO->sceneObjects.size() > 2 && !pMSO->sceneObjects[2].IsEmpty())
  {
    pdbSceneObject = pMSO->sceneObjects[2];
  }
  else
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt("Failed to retreive any SceneObject from MultiStateObject! %s", pMSO->GetDBID().GetFileName().c_str()) );
    return 0;
  }

  NI_DATA_VERIFY( pdbSceneObject->attached.size() > 0 && pdbSceneObject->attached[0].component,
    NStr::StrFmt("Failed to retreive SceneObjects from MultiStateObject! %s", pMSO->GetDBID().GetFileName().c_str()), 
    return 0; );

  return pdbSceneObject->attached[0].component.GetPtr();
}

bool PFMultiStateObject::NeedToBeStepped()
{
  NDb::DBStaticSceneComponent const * pdbStaticSceneComponent = dynamic_cast<NDb::DBStaticSceneComponent const *>(GetDBSceneComponent());
  if (pdbStaticSceneComponent)
    return false;
  
  return true;
}

void PFMultiStateObject::Reset()
{
  // [AZ] no need to recreate client for MSO
  CALL_CLIENT_2ARGS(SetState, natureType, GetWorld()->IsNight());

  if ( isHidden )
  {
    CALL_CLIENT_1ARGS(Hide, true);
  }
}

void PFMultiStateObject::Hide(bool hide)
{
  if (isHidden ^ hide)
  {
    isHidden = hide;
    NDb::MultiStateObject const *pMSO = dynamic_cast<NDb::MultiStateObject const *>(dbObject.gameObject.GetPtr());
    MARK_OBJECT_TILES_AND_WARFOG(pMSO, !hide);

    CALL_CLIENT_1ARGS(Hide, hide);
    UpdateNatureType();
    UpdateDayNightState(GetWorld()->IsNight());
  }
}

void PFMultiStateObject::UpdateNatureType()
{
  if (isHidden)
    return;

  PFLogicObject::UpdateNatureType();

  if (prevNatureType == natureType)
    return;

  prevNatureType = natureType;

  CALL_CLIENT_2ARGS(SetState, prevNatureType, prevNight);
}

void PFMultiStateObject::UpdateDayNightState(const bool night)
{
  if (isHidden)
    return;

  PFLogicObject::UpdateDayNightState(night);

  if (prevNight == night)
    return;

  prevNight = night;

  CALL_CLIENT_2ARGS(SetState, prevNatureType, prevNight);
}

bool PFMultiStateObject::Step( float )
{
  NI_PROFILE_HEAVY_FUNCTION
  
	CALL_CLIENT(DoFreeze);
	return true;
}


PFAdvMapObstacle::PFAdvMapObstacle(PFWorld* pWorld, const NDb::AdvMapObject &_dbObject)
: PFWorldObjectBase( pWorld, 1 )
, dbObject( _dbObject )
{
  NDb::AdvMapObstacle const *pADO = dynamic_cast<NDb::AdvMapObstacle const *>(dbObject.gameObject.GetPtr());
  MARK_OBJECT_TILES_AND_WARFOG(pADO, pADO->LockMode == NDb::BOOLEANLOCKMODE_LOCK);
}

void PFAdvMapObstacle::Hide(bool hide)
{
  NDb::AdvMapObstacle const *pADO = dynamic_cast<NDb::AdvMapObstacle const *>(dbObject.gameObject.GetPtr());
  MARK_OBJECT_TILES_AND_WARFOG(pADO, !hide);
}

PFWarFogUnblock::PFWarFogUnblock(PFWorld* pWorld, const NDb::AdvMapObject &_dbObject)
: PFWorldObjectBase( pWorld, 1 )
, dbObject( _dbObject )
{
  NDb::WarFogUnblock const *pObst = dynamic_cast<NDb::WarFogUnblock const *>(dbObject.gameObject.GetPtr());
  if(pObst && pObst->radius!=0)
  {
    const Placement &place = dbObject.offset.GetPlace();
    const SVector tile = pWorld->GetTileMap()->GetTile( place.pos.AsVec2D() );
    
    FogOfWar* fog = pWorld->GetFogOfWar();

    if((pObst->faction & NDb::FACTIONFLAGS_NEUTRAL) != 0)
    {
      fog->FillVisibilityMap(tile, pObst->radius, NDb::FACTION_NEUTRAL);
    }
    if((pObst->faction & NDb::FACTIONFLAGS_FACTIONFREEZE) != 0)
    {
      fog->FillVisibilityMap(tile, pObst->radius, NDb::FACTION_FREEZE);
    }
    if((pObst->faction & NDb::FACTIONFLAGS_FACTIONBURN) != 0)
    {
      fog->FillVisibilityMap(tile, pObst->radius, NDb::FACTION_BURN);
    }
  }
}

} //namespace NWorld

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM( PFSimpleObject, NWorld )
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM( PFMultiStateObject, NWorld )
REGISTER_WORLD_OBJECT_NM( PFAdvMapObstacle, NWorld )
REGISTER_WORLD_OBJECT_NM( PFWarFogUnblock, NWorld )

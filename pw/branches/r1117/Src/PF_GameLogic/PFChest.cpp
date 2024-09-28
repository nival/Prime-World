#include "stdafx.h"
#include "PFChest.h"

#include "DBConsumable.h"
#include "DBStats.h"

#include "PFAdvMapObject.h"
#include "PFAIWorld.h"
#include "PFHero.h"
#include "TileMap.h"

#ifndef VISUAL_CUTTED
#include "PFClientChest.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN(PFConsumableChest)
  NAMEMAP_FUNC_RO(name, &PFConsumableChest::GetName )
NAMEMAP_END
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FreePlaceForChestChecker
{
  FreePlaceForChestChecker( PFWorld const* pWorld, CVec3 position, float objectSize, float searchRadius )
    : pMap( pWorld->GetTileMap() )
    , pAIWorld( pWorld->GetAIWorld() )
    , fTileSize( pWorld->GetTileMap()->GetTileSize() )
    , objectSize2( objectSize * objectSize )
    , mapModeChanger( MAP_MODE_ALL, pWorld->GetTileMap() )
  {
    objectTileSize = ceil( objectSize / fTileSize );
    pAIWorld->ForAllObjectsInRange( position, searchRadius, *this );
  }
  bool operator()( CVec2 const& pos )
  {
    SVector tile = pMap->GetTile(pos);
    if ( !pMap->CanUnitGo(objectTileSize, tile) )
      return false;
    
    for( vector<CVec2>::const_iterator iObject = nearestObjects.begin(), iEnd = nearestObjects.end(); iObject != iEnd; ++iObject )
    {
      if ( objectSize2 > fabs2((*iObject) - pos) )
        return false;
    }
    return true;
  }
  void operator()( const PFLogicObject & obj )
  {
    PFLogicObject const* pObject = &obj;
    if ( PFConsumableChest const* pChest = dynamic_cast<PFConsumableChest const*>(pObject) )
      nearestObjects.push_back( pObject->GetPosition().AsVec2D() );
  }
private:
  TileMap*    pMap;
  PFAIWorld*  pAIWorld;
  float       fTileSize;
  int         objectTileSize;
  float       objectSize2;
  vector<CVec2> nearestObjects;
  MapModeChanger mapModeChanger;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CObj<PFConsumableChest> PFConsumableChest::Create(PFWorld* pWorld, NDb::Ptr<NDb::Consumable> const& dbConsumable, const CVec2& pos, int quantity, NDb::GameObject const* gameObject /* = NULL */)
{
  NI_VERIFY( dbConsumable, "Invalid consumable to place into chest!", return NULL; );

  NDb::AdvMapObject amChest;
  amChest.gameObject = gameObject ? gameObject : pWorld->GetAIWorld()->GetAIParameters().chestGameObject;
  NI_VERIFY( amChest.gameObject, "Invalid game object in 'chestGameObject' member of 'GameLogic/AILogic.AILP'!", return NULL; );

  float fObjectSize = amChest.gameObject->lockMask.tileSize;

  if (fObjectSize <= 0)
  {
    NDb::SingleStateObject const * pSingleStateObject; 
    pSingleStateObject = dynamic_cast<NDb::SingleStateObject const *>(amChest.gameObject.GetPtr());
    NI_VERIFY( pSingleStateObject, "Failed to downcast game object in 'chestGameObject' member of 'GameLogic/AILogic.AILP'!", return NULL; );

    NI_VERIFY( pSingleStateObject->sceneObject && 
                  pSingleStateObject->sceneObject->attached.size() > 0 &&
                  pSingleStateObject->sceneObject->attached[0].component,
                  "Failed to access attached object's first component in 'chestGameObject->sceneObject' member of 'GameLogic/AILogic.AILP'!", return NULL; );

    NDb::DBSceneComponent const * pdbSceneComponent;
    pdbSceneComponent = pSingleStateObject->sceneObject->attached[0].component.GetPtr();

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

    NI_VERIFY( pAABB, "Failed to get AABB from 'chestGameObject->sceneObject' member of 'GameLogic/AILogic.AILP'!", return NULL; );
    
    if (pAABB->maxX != -666 && pAABB->minX != 666 && pAABB->maxY != -666 && pAABB->minY != 666)
    {
      fObjectSize = sqrt( pow(pAABB->maxX - pAABB->minX, 2) + pow(pAABB->maxY - pAABB->minY, 2) );
    }
  }

  FreePlaceForChestChecker checker = FreePlaceForChestChecker( pWorld, CVec3( pos, 0.0f ), fObjectSize, 100.0f );
  amChest.offset = CPlacement( PFLogicObject::GetFreePlaceForObject(CVec3( pos, 0.0f ), fObjectSize, checker ), QNULL, CVec3(1.f, 1.f, 1.f) );

  CObj<PFConsumableChest> pChest( new PFConsumableChest(pWorld, dbConsumable, quantity, amChest ) );

  const float fTileSize   = pWorld->GetTileMap()->GetTileSize();

  int objectTileSize    = (fTileSize == 0.0f) ? (0) : (ceil( fObjectSize / fTileSize ));
  int objectDynTileSize = fObjectSize;
  float objectSize      = fObjectSize * fTileSize; // rounded up to tile size

  pChest->SetObjectSizes(objectSize, objectTileSize, objectDynTileSize);

  vector<SVector> occupiedTiles;
  MarkObject(pWorld->GetTileMap(), amChest, occupiedTiles);
  pWorld->GetTileMap()->MarkObject(occupiedTiles, true, MAP_MODE_BUILDING);

  return pChest;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFConsumableChest::PFConsumableChest(PFWorld* pWorld, NDb::Ptr<NDb::Consumable> const& dbConsumable, int quantity, const NDb::AdvMapObject &_dbObject)
: PFPickupableObjectBase(pWorld, _dbObject.offset.GetPlace().pos, _dbObject.gameObject )
, consumable(dbConsumable)
, quantity(quantity)
, dbObject(_dbObject)
{
  NI_VERIFY( dbObject.gameObject, "Need gameObject to create Chest!", return; );
  CreateClientObject<NGameX::PFClientChest>( NGameX::PFClientChest::CreatePars( pWorld->GetScene(), BADNODENAME, dbObject ) );
}

void PFConsumableChest::Reset()
{
	PFPickupableObjectBase::Reset();
	CreateClientObject<NGameX::PFClientChest>( NGameX::PFClientChest::CreatePars( GetWorld()->GetScene(), BADNODENAME, dbObject ) );
}

bool PFConsumableChest::CanBePickedUpBy( CPtr<PFBaseHero> const& pPicker ) const
{
  if ( !IsUnitValid(pPicker) )
    return false;
    
  return pPicker->CanTakeConsumable(consumable, quantity);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFConsumableChest::OnPickedUp( const CPtr<PFBaseHero>& pPicker )
{
  NI_VERIFY( IsUnitValid(pPicker), "Hero must be valid!", return; );
  NI_VERIFY( pPicker->TakeConsumable( consumable, quantity, NDb::CONSUMABLEORIGIN_PICKUPABLE ), "Can not pick up consumable from chest (CanBePickedUpBy work wrong?)", ; );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const wstring& PFConsumableChest::GetName() const
{
  return consumable ? consumable->name.GetText() : NNameMap::wstrNoname;
}

} // End of namespace NWorld

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFConsumableChest, NWorld)

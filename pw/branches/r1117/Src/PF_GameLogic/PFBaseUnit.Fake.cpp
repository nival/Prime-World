#include "stdafx.h"

#include "PFBaseUnit.Fake.h"
#include "TileMap.h"
#include "PFVoxelMap.h"
#include "PFBaseMovingUnit.h"

namespace NWorld
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFWorld::PFWorld( const SVector& mapSize, float baseMoveSpeed ) :
	rnd( 0 )
{
	aiParams.baseMoveSpeed = baseMoveSpeed;

	tileMap = new TileMap( this );
	tileMap->Prepare( mapSize.x, mapSize.y, 10.0f / 16.0f );

	voxelMap = new PFVoxelMap();
	voxelMap->SetVoxelMapSizes( tileMap );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::RegisterObject( PF_Core::WorldObjectBase* pObject, bool immediately )
{
	objects.push_back( pObject );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::RegisterInAIWorld( PFBaseUnit* pObject)
{
	if ( voxelMap && pObject )
		voxelMap->AddObject( *pObject );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorld::UnregisterObject( PF_Core::WorldObjectBase* pObject )
{
	PFLogicObject* unit = dynamic_cast<PFLogicObject*>( pObject );
	if ( voxelMap && unit )
		voxelMap->RemoveObject( *unit );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFWorld::Step( float dtInSeconds, float dtLocal )
{
	MovingUnit::UpdateMovements( GetVoxelMap(), GetTileMap(), dtInSeconds, dtLocal );
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFLogicObject::PFLogicObject( PFWorld* pWorld, const CVec3& pos ) :
	PF_Core::WorldObjectBase( pWorld ),
	position( pos )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseUnit::PFBaseUnit( PFWorld* pWorld, const CVec3& pos, const NDb::Unit* unitDesc ) :
	PFLogicObject( pWorld, pos ),
	objectTileSize( unitDesc->objectTileSize ),
	objectSize( unitDesc->objectSize ),
	isRounded( unitDesc->isRounded )
{
	GetWorld()->RegisterInAIWorld( this );
	CreateClientObject<NGameX::PFClientBaseMovingUnit>();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TileMap* PFWorld::GetTileMap() const { return tileMap; }
PFVoxelMap* PFWorld::GetVoxelMap() const { return voxelMap; }
}

REGISTER_WORLD_OBJECT_NM(PFBaseUnit, NWorld)
REGISTER_SAVELOAD_CLASS_NM(PFDispatchUniformLinearMove, NWorld)
REGISTER_SAVELOAD_CLASS_NM(PFWorld, NWorld)
REGISTER_SAVELOAD_CLASS_NM(PFClientBaseMovingUnit, NGameX)
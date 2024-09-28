#include "stdafx.h"
#include "Utility.h"
#include "EditorScene.h"
#include "TerrainElement.h"
#include "TerrainUtils.h"

typedef Terrain::TerrainGeometryManager TerrainGeometryManager;

using namespace System::Drawing;

using namespace EditorNative;
using namespace EditorNative::Terrain;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainElement::TerrainElement( Vector3^ location, float _angle, libdb::DB::DBID^ _meshId )
:	meshId( _meshId ),
	id( -1 ),
	angle( _angle )
{
	Location = location;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainElement::~TerrainElement()
{
	this->!TerrainElement();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainElement::!TerrainElement()
{
	Scene = nullptr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TerrainElement::IsIntersectWith( float terrainX, float terrainY, Vector3^ pickLocation )
{
  return terrainX >= Location->X - TerrainUtils::PatchSize / 2 &&
				 terrainX <= Location->X + TerrainUtils::PatchSize / 2 &&
				 terrainY >= Location->Y - TerrainUtils::PatchSize / 2 &&
				 terrainY <= Location->Y + TerrainUtils::PatchSize / 2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElement::Draw()
{
	if ( IsSelected )
	{
		float height;
		if ( Scene->NativeScene->GetTerrain()->GetHeight( Location->X, Location->Y, &height ) )
		{
			const float s = TerrainUtils::CursorGranularity;
      CVec3 pos(Location->X, Location->Y, height);
      CVec3 offset[5];
      offset[0] = CVec3(     0 * s,     0 * s,    1 * s );
      offset[1] = CVec3(  0.3f * s,     0 * s, 0.3f * s );
      offset[2] = CVec3( -0.3f * s,     0 * s, 0.3f * s );
      offset[3] = CVec3(     0 * s,  0.3f * s, 0.3f * s );
      offset[4] = CVec3(     0 * s, -0.3f * s, 0.3f * s );

      DrawLine3D( pos, pos + offset[0], Color::Red );
      DrawLine3D( pos, pos + offset[1], Color::Red );
      DrawLine3D( pos, pos + offset[2], Color::Red );
      DrawLine3D( pos, pos + offset[3], Color::Red );
      DrawLine3D( pos, pos + offset[4], Color::Red );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElement::SetMeshId( libdb::DB::DBID^ value )
{
	if ( !ReferenceEquals( Scene, nullptr ) && !meshId->Equals( value ) )
	{
		meshId = value;
		Scene->NativeScene->DeleteTerrainElement( id );
		AddTerrainElement();
		Scene->SceneTerrain->Changed = true;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElement::AddTerrainElement()
{
  NDb::TerrainElementInstance instance;
	instance.position = Location->Native;
	instance.angle = angle;
	instance.scale = Vector3::Ones->Native;
  instance.terrainObject = GetObject<NDb::StaticMesh>( meshId );
  instance.material = instance.terrainObject->materialsReferences.empty()? 0 : instance.terrainObject->materialsReferences[0];
	id = Scene->NativeScene->AddTerrainElement( instance, instance.terrainObject->geometryFileName );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElement::Angle::set( float value )
{
	if ( !ReferenceEquals( Scene, nullptr ) && angle != value )
	{
		angle = value;
		Scene->NativeScene->DeleteTerrainElement( id );
		AddTerrainElement();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElement::OnBeforeOwnerChanged()
{
	if ( !ReferenceEquals( Scene, nullptr ) && id >= 0 )
	{
		Scene->NativeScene->DeleteTerrainElement( id );
		id = -1;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElement::OnOwnerChanged()
{
	if ( !ReferenceEquals( Scene, nullptr ) )
	{
		AddTerrainElement();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

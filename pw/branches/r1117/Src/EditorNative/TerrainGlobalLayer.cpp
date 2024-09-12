#include "stdafx.h"
#include "Utility.h"
#include "EditorScene.h"
#include "TerrainGlobalLayer.h"

using namespace System;
using namespace libdb::DB;
using namespace EditorNative::Terrain;
using namespace EditorNative::Terrain::Layers;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainGlobalLayer::TerrainGlobalLayer( libdb::DB::DBID^ _terrainTypeInfoId )
:	TerrainMaterialLayer( ),
	terrainTypeInfoId( _terrainTypeInfoId )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainGlobalLayer::TerrainTypeInfoId::set( libdb::DB::DBID^ value )
{
	terrainTypeInfoId = value;
	if ( TerrainLayer::IsValid/*TerrainMaterialLayer::IsValid*/ )
	{
		if ( DataBase::IsExists( MaterialId ) )
		{
			NDb::Ptr<NDb::TerrainMaterial> pMaterial = GetObject<NDb::TerrainMaterial>( MaterialId );
			if ( pMaterial != nullptr )
			{
				if ( Index >= 0 )
				{
					Owner->Native->ReplaceLayer( Index, pMaterial );
				}
				else
				{
					AddToScene( pMaterial );
				}
			}
			else
			{
				RemoveFromScene();
			}
		}
		else
		{
			if ( Index >= 0 )
			{
				RemoveFromScene();
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainGlobalLayer::OnBeforeOwnerChanged()
{
	if ( IsValid )
	{
		RemoveFromScene();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainGlobalLayer::OnOwnerChanged()
{
	if ( TerrainLayer::IsValid && DataBase::IsExists( MaterialId ) )
	{
		NDb::Ptr<NDb::TerrainMaterial> pMaterial = GetObject<NDb::TerrainMaterial>( MaterialId );
		if ( pMaterial != nullptr )
		{
			AddToScene( pMaterial );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
libdb::DB::DBID^ TerrainGlobalLayer::MaterialId::get()
{
	return DataBase::IsExists( terrainTypeInfoId ) ?
		DataBase::Get<DBTypes::TerrainTypeInfo^>( terrainTypeInfoId )->Get()->pDBMaterial->DBId : DBID::Empty;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainGlobalLayer::AddToScene( NDb::Ptr<NDb::TerrainMaterial> pMaterial )
{
	Index = Owner->Native->AddLayer( pMaterial );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainGlobalLayer::RemoveFromScene()
{
	Owner->Native->RemoveLayer( Index );
	Index = -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

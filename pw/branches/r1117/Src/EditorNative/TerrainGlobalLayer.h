#pragma once

#include "TerrainMaterialLayer.h"

namespace EditorNative {
namespace Terrain {
namespace Layers {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class TerrainGlobalLayer : TerrainMaterialLayer
	{
	private:
		libdb::DB::DBID^ terrainTypeInfoId;

	public:
		TerrainGlobalLayer( libdb::DB::DBID^ terrainTypeInfoId );

	public:
		property libdb::DB::DBID^ TerrainTypeInfoId
		{
			libdb::DB::DBID^ get() { return terrainTypeInfoId; }
			void set( libdb::DB::DBID^ value );
		}

	protected:
		virtual void OnBeforeOwnerChanged() override sealed;
		virtual void OnOwnerChanged() override sealed;

	private:
		void AddToScene( NDb::Ptr<NDb::TerrainMaterial> pMaterial );
		void RemoveFromScene();

		property libdb::DB::DBID^ MaterialId
		{
			libdb::DB::DBID^ get();
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Layers
}	// namespace Terrain
}	// namespace EditorNative

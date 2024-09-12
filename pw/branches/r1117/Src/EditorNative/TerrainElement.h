#pragma once

#include "SceneElement.h"
#include "TcvMarker.h"

namespace EditorNative {
namespace Terrain {
	typedef ::Terrain::TerrainElementId TerrainElementId;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public ref class TerrainElement : SceneElements::SceneElement, SceneElements::IPickableSceneElement
	{
	private:
		libdb::DB::DBID^ meshId;
		float angle;
		TerrainElementId id;

	public:
		TerrainElement( Vector3^ location, float angle, libdb::DB::DBID^ meshId );
		~TerrainElement();
		!TerrainElement();
    virtual bool IsIntersectWith( float terrainX, float terrainY, Vector3^ pickLocation );
    virtual void Draw() override;

	protected:
		void SetMeshId( libdb::DB::DBID^ value );

	internal:

		property TerrainElementId ElementId
		{
			TerrainElementId get() { return id; }
		}

	protected:
		virtual void OnBeforeOwnerChanged() override sealed;
		virtual void OnOwnerChanged() override sealed;

		property float Angle
		{
			float get() { return angle; }
			void set( float value );
		}

	private:
		void AddTerrainElement();
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Terrain
}	// namespace EditorNative

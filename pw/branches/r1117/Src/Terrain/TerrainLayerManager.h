#pragma once

#include "../System/2Darray.h"
#include "../System/BitData.h"
#include "../System/fixedvector.h"
#include "../Render/MaterialSpec.h"
#include "../Render/RenderResourceManager.h"
#include "../Render/aabb.h"
#include "../System/BoundCalcer.h"
#include "../MeshConverter/MeshHeader.h"
#include "TerrainElementManager.h"


namespace NDb
{
  struct TerrainLayers;
	struct TerrainMaterial;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// There's need for several different words for "grouping" concepts. Like "terrain type, terrain kind..."
// Thesaurus: type, kind, form, sort, variety, style, flavor, version, variation, variant, edition, nature.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Terrain
{
	class Terrain;
	struct GridConstants;

	typedef CArray2D<unsigned char> TerrainLayerMask;

	struct TerrainLayer
	{
		Render::BaseMaterial* pMaterial;
	};

	typedef hash_map<int, TerrainLayer> TerrainLayerList;

	struct TerrainLayerRegion : public BoundCalcer
	{
		void Clear()
		{
			ptMin.Set(1e38f, 1e38f, 1e38f);
			ptMax.Set(-1e38f, -1e38f, -1e38f);
		}

		void SetToWorld()
		{
			ptMin.Set(0.0f, 0.0f, -1.0f);
			ptMax.Set(1.0f, 1.0f, 1.0f);
		}
	
		void GetWorldAABB(GridConstants const& params, Render::AABB& bounds) const;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class TerrainLayerManager
	{
	public:
		enum ReservedLayers
		{
			HOLES_LAYER = 0,
			LOCAL_LAYER,
			RESERVED_LAYERS_COUNT,
		};

		enum NatureType
		{
			NATURE_0, // neutral lands
			NATURE_A, // "FROZEN" or "MATERIAL" or whatever
			NATURE_B, // "BURNED" or "ELEMENTAL" or whatever

			_NATURE_TYPE_COUNT_
		};

    static const int MAX_NUM_LAYERS = 4;

	public:
		// Initialization
		TerrainLayerManager();
		virtual ~TerrainLayerManager();

		void SetOwner(Terrain* owner) { pOwner = owner; }
		void Initialize();

		int GetMaskXSize() const { return maskXSize; }
		int GetMaskYSize() const { return maskYSize; }

		// Serialization
		void Load( const NDb::TerrainLayers& layers, const string& maskFileName );
		void SaveLayerMask( const nstl::string& filename );
		void LoadLayerMask( const nstl::string& filename, bool forceUpdate = true );

		// Creation
		int AddLayer( const NDb::Material* pMaterial );
		void ReplaceLayer( int index, const NDb::Material* pMaterial );
		void RemoveLayer( int index );

		// Modification
		void WriteLayerValue(int layerIndex, int row, int column);
		unsigned char ReadLayerValue(int layerIndex, int row, int column);
		unsigned char ReadLayerValue(int row, int column) { return layerMask[row][column]; }
    void WriteLayerValue( unsigned char byte, int row, int column ) { layerMask[row][column] = byte; }
		void InvalidateLayers();
		void NotifyElementChange(TerrainElementId id);
		void MarkPixelsAsDirty() { areIndicesDirty = true; }
		TerrainLayerRegion& GetUpdateRegion() { return updateRegion; }

		void Update();

		void NotifyNatureChange(TerrainElementId id);
		
		TerrainLayerMask const& GetLayerMask() /*const*/ { return layerMask; } // smirnov [2008/11/27]: hash_map doesn't support const
		Render::Texture* GetLayerTexture( int layerNumber, NatureType natureType, Render::BaseMaterial* localMaterial ) const;
		CVec4 const& GetLayerDebugColor( int layerNumber );

    // for internal use
    unsigned char FindMostUsedLayerAround(unsigned row, unsigned col, nstl::vector<pair<int, int>> const &validLayers);
    int GetLastWrittenLayer() const { return lastWrittenLayer; }

	private:
		TerrainLayerManager& operator=(TerrainLayerManager const&);

	private:
		Terrain* pOwner; // smirnov [2008/12/11]: CPtr<> is not possible here

		TerrainLayerList layers;
		int maskXSize, maskYSize;
		TerrainLayerMask layerMask;
		TerrainLayerRegion updateRegion;
		bool areIndicesDirty;

		bool isNatureMapDirty;

    nstl::vector<CVec4> debugPalette;
    int lastWrittenLayer;
	};
};
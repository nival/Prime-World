#pragma once

#include "../System/noncopyable.h"
#include "../System/2Darray.h"
#include "SpeedGrass.h"
#include "GrassRenderManager.h"
#include "DBTerrain.h"

namespace Render
{
	class Texture2D;
};

namespace Terrain { class Terrain; }

namespace Grass
{
	//class GrassRenderManager;

	class GrassLayersManager
		: private NonCopyable
		, private CSpeedGrassRT

	{
	public:
		typedef int LayerId;

		struct GrassLayer
		{
			typedef CArray2D<unsigned char> GrassDensity;
			typedef CArray2D<bool> ChangingCache;

			///< grass material
			Render::BaseMaterial* pMaterial;
			///< mask with density of grass 
			GrassDensity density;
			///< blade per density
			unsigned int bladesPerDensity;
			///< changing flags, used demand VB generation
			ChangingCache dirtyRegions;
			///< layer id
			LayerId id;

			GrassLayer( int _id, int x, int y, unsigned int blasdes, Render::BaseMaterial* _pMaterial );
			~GrassLayer();

			void Resize( int x, int y );
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	private:		
		int sizeX, sizeY;

		typedef hash_map<LayerId, GrassLayer*> GrassLayersContainer;
		GrassLayersContainer grassLayers;

		GrassRenderManager& renderManager;
		Terrain::Terrain* pTerrain;

		typedef hash_map<int, GrassRenderManager::GrassRegionId> RegionsContainer;
		typedef hash_map<LayerId, RegionsContainer> LayerRegionsContainer;
		LayerRegionsContainer layerRegions;

		///< height version for which grass has been generated 
		mutable uint heightVersion;

	public:
		///< pixels per tile
		static const int RESOLUTION = 4;
		static const int TILES_PER_REGION = 4;
		static const float GRASS_TILE_SIZE;

	public:
		GrassLayersManager( GrassRenderManager& renderManager );
		~GrassLayersManager();

		void SetHeightsController( Terrain::Terrain* _pTerrain ) { pTerrain = _pTerrain; }

		/** init mask buffer, used map size in tiles */
		void Resize( int mapSizeX, int mapSizeY );

		LayerId AddLayer( const NDb::GrassMaterial* pMaterialDescription, unsigned int bladesPerDensity );
		bool RemoveLayer( LayerId id );

		unsigned char GetLayerDensity( LayerId id, int column, int row ) const;
		void SetLayerDensity( LayerId id, int column, int row, unsigned char density );

		bool ChangeMaterial( LayerId id, const NDb::GrassMaterial* pMaterialDescription );
		bool ChangeBladesPerDensity( LayerId id, unsigned int blades );

		bool SaveLayer( const nstl::string& filename, LayerId id ) const;
		bool LoadLayer( const nstl::string& filename, LayerId id, unsigned char defaultValue );

		bool Load( const vector<NDb::GrassLayer>& grassLayers );
		LayerId LoadLayer( const NDb::GrassLayer& layer );

		/** add demand request to update for given layer */
		void MakeUpdateRequest( LayerId id );
		/** add demand request to all layers */
		void MakeUpdateRequest();

		uint GetVersion() const { return heightVersion; }

		/** regenerate grass geometry using density mask for given layer */
		bool Update( LayerId id );
		/** regenerate grass geometry using density mask for all layers */
		bool Update();

	private:
		//bool IsDirty( LayerId id ) const;
		Render::BaseMaterial* GetMaterial( LayerId id ) const;
		LayerId GetFreeLayerId() const;

		/** generate grass by density */
		void GenerateBlades( const GrassLayer& layer );
		bool GenerateBlades( const GrassLayer& layer, int column, int row );
		SBlade GenerateBlade( const CVec2& position );
		/** generate geometry */
		void GenerateGeometry( Render::BaseMaterial*, LayerId layerId );
		bool ReleaseLayerGeometry( LayerId id );
		bool ReleaseRegionGeometry( LayerId id, int region );
 
		/** get height by x, y projection */
		CVec4 GetHeightAndNormal( float x, float y ) const;
	};
}
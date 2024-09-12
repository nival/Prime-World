#pragma once

#include "TerrainElement.h"
#include "TerrainElementManager.h"
#include "TerrainLayerManager.h"
#include "TerrainGeometryManager.h"
#include "TerrainHeightManager.h"
#include "TerrainMaterialCache.h"
#include "GrassLayersManager.h"
#include "GrassRenderManager.h"
#include "NatureMap.h"
#include "NatureMapVisual.h"
#include "TerrainTextureCache.h"

#include "../Scene/RenderableScene.h"
#include "../Render/ShadowReceiverVolume.h"

namespace Terrain
{
//	static const float TERRAIN_TILE_SIZE = 2.5f; // smirnov [2008/12/4]: use GridConstants.metersPerTile instead

	struct GridConstants
	{
		// pair of ints
		struct int2 { int x, y; };

		// if the constants were filled
		bool valid;

		// given values
		float metersPerElement;
		int2 sizeInElements;
		int tilesPerElement;
		int texelsPerElement;

		// derived values
		float metersPerTile;
		float metersPerTexel;
		int2 sizeInTiles;
		int2 sizeInTexels;
		CVec3 worldSize;

		GridConstants() { memset(this, 0, sizeof(*this)); }
	};

  class Terrain : public CObjectBase, public Render::IShadowReceiverVolume
	{
		OBJECT_BASIC_METHODS(Terrain);

		TerrainLayerManager layerManager;
		TerrainHeightManager heightManager;
		TerrainElementManager elemManager;
#ifndef VISUAL_CUTTED
		TerrainGeometryManager geometryManager;
		TerrainMaterialCache materialCache;

    int textureCacheSize;
    ScopedPtr<TerrainTextureCache> pTextureCache;
    ScopedPtr<class TEGetter> pTEGetter;
    Render::BatchQueueSorter batchQueueSorter;

		/** grass parameters */
    Grass::GrassRenderManager grassRenderManager;
		Grass::GrassLayersManager grassManager;
    ScopedPtr<Render::BaseMaterial> aoeMaterial;
    Render::DeviceLostWrapper<NatureMapVisual> natureMap;
    vector<TerrainElementId> nmTerrainElements;
    vector<NatureMapElementId> teNatureMapElements;
    vector<int> nmToTe, teToNm;

 		CArray1Bit natureMapDirty; // the size of tile map
#else
		NatureMap natureMap;
#endif

    NatureMapVisual::NatureMapElementIdList modifiedElems;

		GridConstants gridConstants;

		bool editable;

		bool  aoeEnabled;
		CVec3 aoeCenter;
		float aoeRadius;

		int layerDisplayMode;

    // dummy constructor for CObjectBase
    Terrain();

	public:
		explicit Terrain(bool editable_);
		virtual ~Terrain();

		bool IsEditable() const { return editable; }

		TerrainLayerManager& GetLayerManager() { return layerManager; }
		TerrainHeightManager& GetHeightManager() { return heightManager; }
		const TerrainHeightManager& GetHeightManager() const { return heightManager; }
		TerrainElementManager& GetElementManager() { return elemManager; }
#ifndef VISUAL_CUTTED
		TerrainGeometryManager& GetGeometryManager() { return geometryManager; }
		TerrainMaterialCache& GetMaterialCache() { return materialCache; }
    TerrainTextureCache* GetTextureCache() const { return ::Get(pTextureCache); }
#endif
    NatureMap& GetNatureMap() { return natureMap; }
		GridConstants const& GetGridConstants() const { return gridConstants; }

		int GetLayerDisplayMode() const { return layerDisplayMode; }
		void SetLayerDisplayMode(int mode) { layerDisplayMode = mode; }

    void LoadTerrain( const NDb::Terrain* pDBTerrain );   // in-game only
		void CreateTerrain( const NDb::Terrain* pDBTerrain ); // in-editor only

		void Update();

#ifndef VISUAL_CUTTED
    // next 2 methods are used for runtime reconfiguration
    void InvalidateRenderResources();
    void RestoreRenderResources();

    void InitNatureMapParams();
    void UpdateTerrainElements();

		void StartRendering();
		void StopRendering();

    void FillCache(Render::BatchQueue &_queue, class IRenderableScene *_pScene);
    void OnRender(const Render::BatchQueue &_queue, bool _doTerrainZPrepass);
		void RenderWithMaterial( Render::AABB const& bbox, Render::BatchQueue& queue, Render::BaseMaterial* pMaterial );
		void ForAllElements(IObjectFunctor &func)
		{
			elemManager.ForAllElements( func );
			grassRenderManager.ForAllElements( func ); 
		}

    void SetAOEMaterial_Deprecated(NDb::Material const *pMaterial);
    void SetAOESelection_Deprecated(CVec3 const& center, float radius);
		void ClearAOESelection_Deprecated() { aoeEnabled = false; }
		void RenderAOESelection_Deprecated(Render::BatchQueue& queue);

    void RecalculateLighting();

		/**
		 * get terrain height by projected x and y, return true if can do it
		 */
		bool GetHeight(float x, float y, float* height, CVec3* normal = NULL ) const { return heightManager.GetHeight(x, y, height, normal); }
		uint GetHeightsCounter() const { return heightManager.GetHeightsVersion(); }

		void NotifyNatureChange(int row, int column) { layerManager.NotifyNatureChange(elemManager.LocateElement(unsigned(row), unsigned(column))); }

		// Layer methods.
		void WriteLayerValue( int layerIndex, int row, int column, unsigned char val ) { if (val) layerManager.WriteLayerValue( layerIndex, row, column ); }
		unsigned char ReadLayerValue( int layerIndex, int row, int column ) { return layerManager.ReadLayerValue( layerIndex, row, column ); }
		void InvalidateLayers() { layerManager.InvalidateLayers(); }
		int AddLayer( const NDb::TerrainMaterial* pMaterial ) { return layerManager.AddLayer( pMaterial ); }
		void ReplaceLayer( int index, const NDb::TerrainMaterial* pMaterial ) { layerManager.ReplaceLayer( index, pMaterial ); }
		void RemoveLayer( int index ) { layerManager.RemoveLayer( index ); }
		void SaveLayerMask( const nstl::string& filename ) { layerManager.SaveLayerMask( filename ); }
		void LoadLayerMask( const nstl::string& filename ) { layerManager.LoadLayerMask( filename ); }

		// Geometry methods.
		TerrainElementId AddTerrainElement( const NDb::TerrainElementInstance& descriptor, const string& fileName ) { return geometryManager.AddTerrainElement( descriptor, fileName ); }
		bool DeleteTerrainElement( TerrainElementId id ) { return geometryManager.DeleteTerrainElement( id ); }
		void SetTCV( int column, int row, const Matrix43& basis ) { geometryManager.SetTCV( column, row, basis ); }
		const Matrix43& GetTCV( int column, int row ) const { return geometryManager.GetTCV( column, row ); }
		void SaveTCV( const string& fileName );
		void LoadTCV( const string& fileName, bool applyInstuntly );
		/** bake terrain elements in file, order of elements must be coincide, return number of baked elements */		
		int BakeTerrainGeometry( const vector<TerrainElementId>& elements, const string& backedFileName ) const;
    void WeldVertices() const { geometryManager.WeldVertices(true); }

		void SaveHeightmap(const nstl::string& filename) { heightManager.Save(filename); }
		void LoadHeightmap(const nstl::string& filename) { heightManager.Load(filename); }

    void SaveNatureMap(const nstl::string& filename) { natureMap.Save(filename); }

		/** grass methods */
		Grass::GrassLayersManager::LayerId AddGrassLayer( const NDb::GrassMaterial* pDescription, int blades ) { return grassManager.AddLayer( pDescription, blades ); }
		bool RemoveGrassLayer( Grass::GrassLayersManager::LayerId id ) { return grassManager.RemoveLayer( id ); }
		unsigned char GetLayerDensity( Grass::GrassLayersManager::LayerId id, int column, int row ) const { return grassManager.GetLayerDensity( id, column, row ); }
		void SetLayerDensity( Grass::GrassLayersManager::LayerId id, int column, int row, unsigned char density ) { grassManager.SetLayerDensity( id, column, row, density ); }
		bool ChangeGrassMaterial( Grass::GrassLayersManager::LayerId id, const NDb::GrassMaterial* pDescription) { return grassManager.ChangeMaterial( id, pDescription ); }
		bool ChangeBladesPerDensity( Grass::GrassLayersManager::LayerId id, unsigned int blades ) { return grassManager.ChangeBladesPerDensity( id, blades ); }
		bool SaveGrassLayer( const nstl::string& filename, Grass::GrassLayersManager::LayerId id ) { return grassManager.SaveLayer( filename, id ); }
		bool LoadGrassLayer( const nstl::string& filename, Grass::GrassLayersManager::LayerId id, unsigned char defaultValue ) { return grassManager.LoadLayer( filename, id, defaultValue ); }

    void ShowNatureAttackTexture();
#endif
    /** project to height map virtual grid */
    bool IntersectWithGrid( CVec2* pPoint, const CVec2& dir ) const;

    // from IShadowReceiverVolume
    virtual void GetBoundsInCamera( const Render::AABB& _cameraAABB, Render::AABB& _receiversAABB );

  private :
#ifndef VISUAL_CUTTED
    struct InitNatureMapParamsHelper;
#endif

	private:
    void Initialize( const NDb::Terrain* pDBTerrain );
	};
};

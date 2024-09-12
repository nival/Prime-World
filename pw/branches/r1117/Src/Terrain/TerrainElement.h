#pragma once

#ifndef VISUAL_CUTTED
#include "../Render/dipdescriptor.h"
#include "../Render/primitive.h"
#include "../Render/RenderComponent.h"
#include "../Render/MeshResource.h"
#include "../Scene/RenderableScene.h"
#include "PatchCacheParams.h"
#endif

namespace Terrain
{
	class Terrain;

	class TerrainElement
#ifndef VISUAL_CUTTED
		: public Render::RenderComponent, public RenderableSceneObj
#endif
	{
#ifndef VISUAL_CUTTED
		REPLACE_DEFAULT_NEW_DELETE(TerrainElement);
#endif
	public:
		static const unsigned int firstPassMask = 0x80000000;
		static const unsigned int indexMask = 0x00FFFFFF;
		static const unsigned int layerIndexMask = 0x7F;
		static const unsigned int layerIndexShift = 24;
		
		static const unsigned int MAX_LAYER_COUNT = 4;

		// render stats
		static int statElementCreated;
		static int statElementCount;
		static int statLayerCount[MAX_LAYER_COUNT+1];
		static int statNatureCount[3/*TerrainLayerManager::_NATURE_TYPE_COUNT_*/+1];
		static int statOverrideCount;

#ifndef VISUAL_CUTTED
		Render::AABB          worldAABB;
		Render::Primitive     mesh;
		Render::BaseMaterial* pLocalMaterial;

    static CVec4  s_cacheScaleShift;

    mutable PatchCacheParams cacheParams;

    void ClearCachingState() const
    {
      cacheParams.pin = NDb::CACHINGPIN_ORDINARY;
      cacheParams.layer1_element2 = cacheParams.layer1_element = PatchCacheParams::NON_CACHED_OR_SINGLE;
    }

    virtual const Render::AABB& GetAABB(bool *_pIsLocal) const { *_pIsLocal = false; return worldAABB; }
#endif
		vector<int>             layerIndices;
		Terrain                *pOwner;
		unsigned                natureBits;
	
		explicit TerrainElement(Terrain* owner);
		~TerrainElement();

#ifndef VISUAL_CUTTED
		void RenderWithMaterial( Render::BatchQueue& queue, Render::BaseMaterial* pMaterial );

		// From RenderableSceneObj
		virtual void Render( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter = GROUPFLAGS_ALL );
		virtual const Render::AABB &GetWorldAABB() const { return worldAABB; }

  		// From Render::RenderComponent
		virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;
    Render::OcclusionQueries* GetQueries() const { return 0; }

    virtual void DebugDraw( Render::IDebugRender* _debugRenderer ) {}

    static void SetCacheScaleShift(CVec4 &_scaleShift);
#endif
	};
};

// This macro assures that supplied pointer points to object of type "type"
#define CHECK_TYPE_1(type, pointer, func_name) NI_ASSERT(dynamic_cast<type>(pointer), __TEXT(func_name) __TEXT("wrong type_cast"));
#ifdef _DEBUG
#define CHECK_TYPE(type, pointer) CHECK_TYPE_1(type*, pointer, __FUNCTION__)
#else
#define CHECK_TYPE(type, pointer)
#endif // _DEBUG

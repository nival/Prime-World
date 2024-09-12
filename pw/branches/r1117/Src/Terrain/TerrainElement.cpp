#include "stdafx.h"

#include "../Render/material.h"
#include "../Render/batch.h"
#include "../Render/smartrenderer.h"

#include "TerrainElement.h"
#include "Terrain.h"
#include "../Render/GlobalMasks.h"
#include <Scene\SceneComponent.h>

#ifdef _DEBUG
#define TERRAIN_DEBUG_ENABLE
#endif

static int g_terrain_debug = 0;

namespace Terrain
{
#ifndef VISUAL_CUTTED
	DECLARE_INSTANCE_COUNTER(TerrainElement);
#endif

  CVec4 TerrainElement::s_cacheScaleShift;

	int TerrainElement::statElementCreated;
	int TerrainElement::statElementCount;
	int TerrainElement::statLayerCount[MAX_LAYER_COUNT+1];
	int TerrainElement::statNatureCount[3/*TerrainLayerManager::_NATURE_TYPE_COUNT_*/+1];
	int TerrainElement::statOverrideCount;

#pragma warning(disable:4201) // warning C4201: nonstandard extension used : nameless struct/union
	namespace {
    enum MaterialMode {
      OVERRIDDE_MODE,
      NORMAL_MODE,
      DEBUG_MODE
    };

		struct ElementNumber {
			union {
				unsigned int asUInt;
				struct {
					TerrainLayerManager::NatureType natureType : 24;
					MaterialMode materialMode : 8; // 0 - material overridden, 1 - normal, 2 - use debug colors
				};
			};
			explicit ElementNumber(unsigned int asUInt_) : asUInt(asUInt_) {}
			explicit ElementNumber(TerrainLayerManager::NatureType natureType_, MaterialMode materialMode_ = NORMAL_MODE)
        : natureType(natureType_), materialMode(materialMode_) {}

			operator unsigned int() { return asUInt; }
		};
	}
#pragma warning(default:4201)

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TerrainElement::TerrainElement(Terrain* owner) : pOwner(owner), natureBits(0xFFFFFF)
	{
#ifndef VISUAL_CUTTED
		worldAABB.center   = CVec3(0.0f, 0.0f, 0.0f);
		worldAABB.halfSize = CVec3(5.0f, 5.0f, 5.0f);
    cacheParams.pin = NDb::CACHINGPIN_ORDINARY;
    cacheParams.layer1_element2 = cacheParams.layer1_element = PatchCacheParams::NON_CACHED_OR_SINGLE;
#endif
		TerrainElement::statElementCreated++;
	}

	TerrainElement::~TerrainElement()
	{
		TerrainElement::statElementCreated--;
#ifndef VISUAL_CUTTED
		delete pLocalMaterial;
#endif
	}

#ifndef VISUAL_CUTTED

  using namespace Render;

	void TerrainElement::Render(BatchQueue& queue, const SceneConstants& sceneConstants, int groupFlagsFilter)
	{
		SET_INSTANCE_COUNTER(TerrainElement);
		queue.SetCurrentSortingValue( 0.0f );

#ifndef _SHIPPING
    {
      const bool isClean = cacheParams.pin == NDb::CACHINGPIN_ORDINARY &&
                           cacheParams.layer1_element2 == PatchCacheParams::NON_CACHED_OR_SINGLE &&
                           (cacheParams.layer1_element == PatchCacheParams::NON_CACHED_OR_SINGLE
                            || groupFlagsFilter == NScene::SceneComponent::GROUPFLAGS_CASTSHADOW);
      NI_ASSERT(isClean, "TerrainElement caching state wasn't cleaned");
    }
#endif // _SHIPPING

		TerrainElement::statElementCount++;

		unsigned int activeLayerCount = layerIndices.size();
#ifdef TERRAIN_DEBUG_ENABLE
		// warn if it is not possible to render exactly as requested
		static int warnCounter = 5;
		if (activeLayerCount > 4 || activeLayerCount < 1)
		{
			TerrainElement::statLayerCount[0]++;
			if (warnCounter)
			{
				warnCounter--;
				systemLog( NLogg::LEVEL_ASSERT ) << "Terrain element at " << worldAABB.center.x << "," << worldAABB.center.y << " references unsupported number of materials (" << activeLayerCount << ", not 1..4)" << endl;
				if (!warnCounter)
				{
					systemLog( NLogg::LEVEL_ASSERT ) << "Terrain element warnings suppressed..." << endl;
				}
			}
		}
		else
		{
			TerrainElement::statLayerCount[activeLayerCount]++;
		}
#endif // TERRAIN_DEBUG_ENABLE

		// render mesh
		activeLayerCount = Min(4U, activeLayerCount);
		if (activeLayerCount)
		{
			// access proper material
			NDb::TerrainUVSetPin pinUVSet = (NDb::TerrainUVSetPin)(layerIndices[0] == TerrainLayerManager::LOCAL_LAYER);
			NDb::TextureCountPin pinTexCount = (NDb::TextureCountPin)(activeLayerCount - 1);
			BaseMaterial* pMaterial = pOwner->GetMaterialCache().GetMaterial(pinTexCount, pinUVSet);
			bool useColors = (pOwner->GetLayerDisplayMode() == 1 || (pOwner->GetLayerDisplayMode() == 2 && layerIndices.size() > 4)
#ifdef TERRAIN_DEBUG_ENABLE
			|| (g_terrain_debug == 1 || g_terrain_debug == 2 && layerIndices.size() > 4)
#endif // TERRAIN_DEBUG_ENABLE
			);
			if (useColors)
				pMaterial = pOwner->GetMaterialCache().GetDebugMaterial();

			// render element several times
			NI_ASSERT((natureBits & 0xFF000000) == 0, "Unexpected nature map bits"); // unknown nature type
			NI_STATIC_ASSERT(TerrainLayerManager::_NATURE_TYPE_COUNT_ == 3, UNEXPECTED_NATURE_TYPE_COUNT);
			int priority = NDb::MATERIALPRIORITY_TERRAINLAYER0;
			int natureCount = 0;
			for (int natureType = 0; natureType < TerrainLayerManager::_NATURE_TYPE_COUNT_; ++natureType)
			{
				if (natureBits & (0xFF << (natureType * 8)))
				{
          const MaterialMode mode = useColors ? DEBUG_MODE : NORMAL_MODE;
					queue.Push(priority, this, &mesh, ElementNumber(TerrainLayerManager::NatureType(natureType), mode), pMaterial);
					natureCount++;
					priority = NDb::MATERIALPRIORITY_TERRAINLAYER1;
				}
			}
			TerrainElement::statNatureCount[natureCount]++;
		}
	}

	void TerrainElement::RenderWithMaterial( BatchQueue& queue, BaseMaterial* pMaterial )
	{
		// SET_INSTANCE_COUNTER(TerrainElement); // smirnov [2008/12/17]: wtf?
		queue.SetCurrentSortingValue(0.0f);
		queue.Push(NDb::MATERIALPRIORITY_TERRAINDECALS, this, &mesh,
               ElementNumber(TerrainLayerManager::NatureType(0), OVERRIDDE_MODE), pMaterial);
		TerrainElement::statOverrideCount++;
	}


  static inline CVec4& AsVec4(CTRect<float>& _src)
  {
    NI_STATIC_ASSERT(sizeof(CVec4) == sizeof(_src), CTRect2CVec4_bad_cast);
    return (CVec4&)_src;
  }

  static inline void SetAlphaTest(NDb::RenderModePin _renderModeValue, NDb::CachingPin _cachingPin)
  {
    RenderStatesManager &statesManager = *GetStatesManager();
    RenderState state = statesManager.GetCurrentState();
    const bool doAlphaTest = (_renderModeValue != NDb::RENDERMODEPIN_RENDERSHAPEONLY) && (_cachingPin != NDb::CACHINGPIN_FILL);
    state.SetAlphaTest(doAlphaTest ? NDb::ONOFFSTATE_ON : NDb::ONOFFSTATE_OFF);
    statesManager.SetState(state);
  }


	void TerrainElement::PrepareRendererAfterMaterial( unsigned int elementNumber ) const
	{
		Renderer* renderer = GetRenderer();
    const NDb::RenderModePin renderModeValue(GetRuntimePins().RenderModeValue);
    SetAlphaTest(renderModeValue, cacheParams.pin);

		// extract nature type for the element
		ElementNumber data(elementNumber);
    // number of textures used in the element - 1 if we are rendering shadow map, 0 otherwise (normal render will be setup later);
    unsigned int activeLayerCount = int(renderModeValue == NDb::RENDERMODEPIN_RENDERTOSHADOW && data.materialMode == NORMAL_MODE);
    TerrainLayerManager& layerManager = pOwner->GetLayerManager();

      // only setup for ordinary rendering (not material override)
    if(renderModeValue == NDb::RENDERMODEPIN_RENDERNORMAL && data.materialMode != OVERRIDDE_MODE)
    {
      ConstantProtectionBlock block(CCONTEXT_TERRAIN);

      static const CVec4 weights[] = { CVec4(0.0f, 1.0f, 0.0f, 0.0f), CVec4(0.0f, 0.0f, 1.0f, 0.0f), CVec4(1.0f, 0.0f, 0.0f, 0.0f) };
      renderer->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST1, weights[data.natureType]);

      if(data.materialMode == DEBUG_MODE)
      {
        CVec4 layerColors[4];

        const uint activeLayerCount = Min(4, layerIndices.size());
        for(uint i = 0; i < activeLayerCount; ++i)
          layerColors[i] = layerManager.GetLayerDebugColor(layerIndices[i]);

        renderer->SetPixelShaderConstants(PSHADER_LOCALCONST2, 4, layerColors);
      }
      else {
        const Texture2D *pTex = 0;

        switch(cacheParams.pin)
        {
        case NDb::CACHINGPIN_FILL:  // Set coeffs for texture caching
          cacheParams.scaleShift.z = -floor(s_cacheScaleShift.x * worldAABB.center.x) + s_cacheScaleShift.z;
          cacheParams.scaleShift.w = -floor(s_cacheScaleShift.y * worldAABB.center.y) + s_cacheScaleShift.w;
          break;
        case NDb::CACHINGPIN_USE3:
          { // Set local texture
            TerrainLayerManager::NatureType const natureType = ElementNumber(cacheParams.layer1_element2).natureType;
            ASSERT(natureType != data.natureType);
            Texture* const pTexture = layerManager.GetLayerTexture(0, natureType, pLocalMaterial);
            ASSERT(pTexture && cacheParams.layer1_element2 >= 0);
            SmartRenderer::BindTexture(3, pTexture);
            renderer->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST3, weights[natureType]);
          }
        case NDb::CACHINGPIN_USE2:
          { // Set local texture
            TerrainLayerManager::NatureType const natureType = ElementNumber(cacheParams.layer1_element).natureType;
            ASSERT(natureType != data.natureType);
            Texture* const pTexture = layerManager.GetLayerTexture(0, natureType, pLocalMaterial);
            ASSERT(pTexture && cacheParams.layer1_element >= 0);
            SmartRenderer::BindTexture(2, pTexture);
            renderer->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST2, weights[natureType]);
          }
        case NDb::CACHINGPIN_USE:   // Set coeffs for texture caching
          ASSERT(cacheParams.layer1_element == PatchCacheParams::NON_CACHED_OR_SINGLE
                 || cacheParams.pin == NDb::CACHINGPIN_USE2 || cacheParams.pin == NDb::CACHINGPIN_USE3);
          cacheParams.scaleShift.z = 0.f;
          cacheParams.scaleShift.w = 0.f;
          if( TerrainTextureCache* const pTextureCache = pOwner->GetTextureCache() )
            pTex = pTextureCache->GetTexture( &worldAABB.center.AsVec2D() );
        }

        cacheParams.scaleShift.x = s_cacheScaleShift.x;
        cacheParams.scaleShift.y = s_cacheScaleShift.y;
        renderer->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST2, cacheParams.scaleShift);

        if(pTex) {
          SmartRenderer::BindTexture(1, pTex);
          activeLayerCount = 1; // TODO: activeLayerCount = int(TerrainUVSetPinValue);
        }
        else
          activeLayerCount = Min( 4, layerIndices.size() );
      }
    }

    for(unsigned int i = 0; i < activeLayerCount; ++i)
    {
      unsigned char layerIndex = layerIndices[i];
      ASSERT(layerIndex > 0);
      Texture* pTexture = layerManager.GetLayerTexture(layerIndex, data.natureType, pLocalMaterial);
      ASSERT(pTexture);
      SmartRenderer::BindTexture(i, pTexture);
    }
	}


  void TerrainElement::SetCacheScaleShift(CVec4 &_scaleShift)
  {
    s_cacheScaleShift = _scaleShift;
  }
#endif

} // namespace Terrain

#ifdef TERRAIN_DEBUG_ENABLE
REGISTER_VAR( "terrain_debug", g_terrain_debug, STORAGE_NONE );
#endif // TERRAIN_DEBUG_ENABLE

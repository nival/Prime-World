#error "This file was deprecated 28.05.2008"

#include "stdafx.h"

#include "TerrainLayerManager.h"
#include "UberElement.h"
#include "../Render/d3d9texture2D.h"

#include <D3dx9tex.h>

static bool showTE = false;

static const float c = 0.5f;

static CVec4 colors[] = 
{
	CVec4(  c, 0.f, 0.f, 1.f),
	CVec4(0.f,   c, 0.f, 1.f),
	CVec4(0.f, 0.f,   c, 1.f),
	CVec4(  c,   c, 0.f, 1.f),
	CVec4(0.f,   c,   c, 1.f),
	CVec4(  c, 0.f,   c, 1.f),
};

namespace Terrain
{
	UberElement::UberElement(const TerrainLayerManager& layers) 
		: layerManager(layers) 
	{ 
		worldAABB.center   = CVec3( 0.0f, 0.0f, 0.0f );
		worldAABB.halfSize = CVec3( 100000.0f, 100000.0f, 100000.0f );
	}

	void UberElement::PrepareToBeRendered( const Render::SceneConstants& sceneConstants )
	{
		layerManager.FlushMaskLayer();
	}

	void UberElement::RenderToQueue( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants )
	{
		queue.SetCurrentSortingValue( 0.0f );

		for( int elementNumber = 0; elementNumber < fragments.size(); ++elementNumber )
		{
			const TerrainFragment* pDummy = fragments[elementNumber];
			unsigned int activeMaterialCount = pDummy->materialIDcache.size();
			if(activeMaterialCount == 0)
				continue;
			
			unsigned char materialID = pDummy->materialIDcache[0];
			if(materialID == TerrainLayerManager::LOCAL_LAYER )
			{
				if(pDummy->pLocalMaterial)
					queue.Push( Render::PRIORITY_TERRAIN_LAYER0, this, pDummy, elementNumber | (TerrainLayerManager::LOCAL_LAYER << layerIndexShift), pDummy->pLocalMaterial );
			}
			else
			{
				Render::Materials::TerrainMaterial* pTerrainMaterial = layerManager.GetLayerMaterial(materialID);
				queue.Push( Render::PRIORITY_TERRAIN_LAYER0, this, pDummy, elementNumber | (materialID << layerIndexShift) , pTerrainMaterial );
			}
			for(unsigned int i = 1; i < activeMaterialCount; ++i)
			{
				materialID = pDummy->materialIDcache[i];
				ASSERT(materialID > 1);
				Render::Materials::TerrainMaterial* pTerrainMaterial = layerManager.GetLayerMaterial(materialID);
				queue.Push( Render::PRIORITY_TERRAIN_LAYER1, this, pDummy, elementNumber| (materialID << layerIndexShift), pTerrainMaterial );
			}
		}
		//NDebug::SetDebugVar( "TerrainFragmentsPushed", counter, false );
		flag = true;
	}

	void UberElement::PrepareRendererAfterMaterial( unsigned int elementNumber ) const
	{
		if(flag)
		{
			Render::SmartRenderer::BindTexture( 13, layerManager.GetLayerGPUMask(0) );
			static int hackcounter = 0;
			if (hackcounter<3)
			{
				D3DXSaveTextureToFile( NStr::StrFmt( "test%d.pfm", hackcounter++), D3DXIFF_PFM, ((Render::D3D9::D3D9Texture2D*)layerManager.GetLayerGPUMask(0))->GetDirect3DTexture(), 0);
			}
			flag = false;
		}
		const unsigned int index = elementNumber & indexMask;

		SHMatrix world;
		Copy( &world, fragments[index]->worldMatrix );

		Render::Renderer::SetVertexShaderConstants( 4, 4, &world );

		if(showTE)
		{
			const unsigned int subindex = index % (sizeof(colors)/sizeof(colors[0]));
			Render::Renderer::SetPixelShaderConstants( 30, 1, &colors[subindex] );
		}
		else
		{
			CVec4 color( 1.f, 1.f, 1.f, 1.f);
			Render::Renderer::SetPixelShaderConstants( 30, 1, &color );
		}

		int layerIndex = (elementNumber >> layerIndexShift) & layerIndexMask;
		Render::SmartRenderer::BindTexture( 15, layerManager.GetLayerGPUMask(layerIndex) );
	}
};

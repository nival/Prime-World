#error "This file was deprecated 28.05.2008"
#pragma once

#include "DummyElement.h"
#include "TerrainLayerManager.h"
#include "../Render/batch.h"
#include "../Render/TerrainMaterial.h"
#include "../Render/ConvexVolume.h"



namespace Terrain
{
	class UberElement : public Render::RenderComponent
	{
		UberElement(const UberElement&);
		UberElement& operator=(const UberElement&);
		mutable bool flag;
	public:
		
		vector< const TerrainFragment* > fragments;


		static const unsigned int firstPassMask = 0x80000000;
		static const unsigned int indexMask = 0x00FFFFFF;
		static const unsigned int layerIndexMask = 0x7F;
		static const unsigned int layerIndexShift = 24;

		const TerrainLayerManager& layerManager;

		UberElement(const TerrainLayerManager& layers);

		~UberElement() {}

		void PrepareToBeRendered( const Render::SceneConstants& sceneConstants  );
		void RenderToQueue( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants );
		void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;
	};
};


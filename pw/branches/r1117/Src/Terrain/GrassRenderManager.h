#pragma once

#include "../System/noncopyable.h"
#include "../Render/dipdescriptor.h"
#include "../Render/MaterialSpec.h"
#include "../Render/RenderComponent.h"
#include "../Scene/RenderableScene.h"

class IRenderableScene;
namespace Render 
{ 
	class IVertexBuffer;
	class IIndexBuffer;
}

namespace Grass
{
	struct GrassRegion;

	/**
	 * Should be used in the same thread that and grass layer manager
	 */
	class GrassRenderManager
		: private NonCopyable
	{
	public:
		typedef int GrassRegionId;

		/** raw region data */
		struct RegionInformation
		{
			///< vertec buffer information
			char* vertexBuffer;
			unsigned int vertexBufferSize;
			///< index buffer information		
			char* indexBuffer;		
			unsigned int indexBufferSize;
			///< DIP descriptor
			Render::DipDescriptor dipDescriptor;
		};
		
	private:
		typedef hash_map<GrassRegionId, GrassRegion*> GrassRegionsContainer;
		GrassRegionsContainer regions;

	public:
		GrassRenderManager() {}
		~GrassRenderManager();

		/** add new region */
		GrassRegionId AddRegion( const RegionInformation& info, Render::BaseMaterial* pMaterial, const Matrix43& basis );
		/** generate new geometry */
		bool ChangeRegion( GrassRegionId id, const RegionInformation& info );
		/** change material */
		bool ChangeRegion( GrassRegionId id, Render::BaseMaterial* pMaterial );
		/** remove specified region */
		bool RemoveRegion( GrassRegionId id );

    void ForAllElements(IObjectFunctor &func);

		/** push batches */
		virtual void RenderToQueue( class Render::BatchQueue& queue, const Render::AABB &worldAABB, 
																const struct Render::SceneConstants& sceneConstants );

	private:
		GrassRegion* CreateRegion( DXVertexBufferRef const & pVB, DXIndexBufferRef const & pIB, const Render::DipDescriptor& dipDescriptor, Render::BaseMaterial* pMaterial, const Matrix43& basis ) const;
		/** generate new region id */
		GrassRegionId GetFreeRegionId() const;
	};
}

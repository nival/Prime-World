#include "stdafx.h"

#include "GrassRenderManager.h"
#include "GrassRegion.h"
#include "../Scene/RenderableScene.h"
#include "../Render/renderresourcemanager.h"
#include "SpeedGrass.h"

namespace
{
	///< debug var to drawing grass
	bool showGrass = true;
	REGISTER_DEV_VAR( "show_grass", showGrass, STORAGE_NONE );
}

namespace Grass
{
	GrassRenderManager::~GrassRenderManager()
	{
		GrassRegionsContainer::const_iterator it = regions.begin();
		const GrassRegionsContainer::const_iterator itEnd = regions.end();
		for (; it != itEnd; ++it )
			delete it->second;
		regions.clear();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassRenderManager::GrassRegionId GrassRenderManager::AddRegion( const RegionInformation& info, Render::BaseMaterial* pMaterial, const Matrix43& basis )
	{
		DXVertexBufferRef pVB = Render::CreateVB( info.vertexBufferSize, Render::RENDER_POOL_MANAGED, info.vertexBuffer );
		DXIndexBufferRef pIB = Render::CreateIB( info.indexBufferSize, Render::RENDER_POOL_MANAGED, (unsigned int*)info.indexBuffer );

		NI_ASSERT( Get(pVB) && Get(pIB), "Can't create DX resources!" );
		GrassRegion* pRegion = CreateRegion( pVB, pIB, info.dipDescriptor, pMaterial, basis );

		// recalculate AABB
		const int stride = GrassRegion::VertexStride::GetVertexStreamStride();
		const int numberOfPoints = info.dipDescriptor.numVertices;
		pRegion->localAABB.Calculate( numberOfPoints, reinterpret_cast<CVec3*>( info.vertexBuffer ), stride );
		pRegion->UpdateWorldAABB();
	
		// generate id for new region
		GrassRegionId id = GetFreeRegionId();
		regions[id] = pRegion;

		//systemLog( NLogg::LEVEL_DEBUG ) << "Added grass region, id: " << id << endl;

		return id;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassRegion* GrassRenderManager::CreateRegion( DXVertexBufferRef const &pVB, DXIndexBufferRef const & pIB,
		const Render::DipDescriptor& dipDescriptor, Render::BaseMaterial* pMaterial, const Matrix43& basis ) const
	{
		GrassRegion* pRegion = new GrassRegion( pVB, pIB, dipDescriptor, pMaterial, basis );
		return pRegion;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassRenderManager::ChangeRegion( GrassRegionId id, const RegionInformation& info )
	{
		// find existed region
		GrassRegionsContainer::const_iterator it = regions.find( id );
		NI_VERIFY( it != regions.end() && it->second, NStr::StrFmt( "Can't find and change region, id: %d!", id ), return false; );

		DXVertexBufferRef pVB = Render::CreateVB( info.vertexBufferSize, Render::RENDER_POOL_MANAGED, info.vertexBuffer );
		DXIndexBufferRef  pIB = Render::CreateIB( info.indexBufferSize, Render::RENDER_POOL_MANAGED, (unsigned int*)info.indexBuffer );

		// replace geometry
		NI_ASSERT( Get(pVB) && Get(pIB), "Can't create DX resources!" );
		GrassRegion* pRegion = it->second;
		pRegion->ChangeGeometry( pVB, pIB, info.dipDescriptor );
		
		// recalculate AABB
		const int stride = GrassRegion::VertexStride::GetVertexStreamStride();
		const int numberOfPoints = info.dipDescriptor.numVertices;
		pRegion->localAABB.Calculate( numberOfPoints, reinterpret_cast<CVec3*>( info.vertexBuffer ), stride );
		pRegion->UpdateWorldAABB();

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassRenderManager::ChangeRegion( GrassRegionId id, Render::BaseMaterial* pMaterial )
	{
		// find existed region
		GrassRegionsContainer::const_iterator it = regions.find( id );
		NI_VERIFY( it != regions.end() && it->second, NStr::StrFmt( "Can't find and change region, id: %d!", id ), return false; );

		it->second->pMaterial = pMaterial;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassRenderManager::RemoveRegion( GrassRegionId id )
	{
		// find existed region
		GrassRegionsContainer::iterator it = regions.find( id );
		NI_VERIFY( it != regions.end() && it->second, NStr::StrFmt( "Can't find and remove region, id: %d!", id ), return false; );
		
		delete it->second;
		regions.erase( it );

		//systemLog( NLogg::LEVEL_DEBUG ) << "Removed grass region, id: " << id << endl;

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void GrassRenderManager::ForAllElements(IObjectFunctor &func)
  {
		if( !showGrass )
			return;

		GrassRegionsContainer::const_iterator it = regions.begin();
		const GrassRegionsContainer::const_iterator itEnd = regions.end();
		for (; it != itEnd; ++it )
		{
      func(*(it->second));
		}
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void GrassRenderManager::RenderToQueue( class Render::BatchQueue& queue, const Render::AABB &worldAABB, const struct Render::SceneConstants& sceneConstants )
	{
		if( !showGrass )
			return;

		GrassRegionsContainer::const_iterator it = regions.begin();
		const GrassRegionsContainer::const_iterator itEnd = regions.end();
		for (; it != itEnd; ++it )
		{
      it->second->RenderToQueue( queue );
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassRenderManager::GrassRegionId GrassRenderManager::GetFreeRegionId() const
	{
		GrassRegionId id = -1;
		while( regions.find( ++id ) != regions.end() );
		return id;
	}
}
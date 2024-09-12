#include "stdafx.h"

#include "GrassLayersManager.h"
#include "GrassRenderManager.h"
#include "GrassRegion.h"

#include "../System/Array2DWrapper.h"
#include "../System/Win32Random.h"

#include "../Render/texture.h"
#include "../Render/renderer.h"

#include "Terrain.h"

namespace Grass
{

	const float GrassLayersManager::GRASS_TILE_SIZE = 2.5f; // should correspond to [Terrain::GridConstants.metersPerTile] in Terrain.h

	GrassLayersManager::GrassLayer::GrassLayer( int _id, int x, int y,  unsigned int blades, Render::BaseMaterial* _pMaterial )
		: density( x, y )
		, dirtyRegions( x / ( RESOLUTION * TILES_PER_REGION ), y / ( RESOLUTION * TILES_PER_REGION ) )
		, pMaterial( _pMaterial )
		, id( _id )
		, bladesPerDensity( blades )
	{
		ASSERT( x && y );
		ASSERT( pMaterial != 0 );
		density.FillZero();
		dirtyRegions.FillZero();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassLayersManager::GrassLayer::~GrassLayer()
	{
		delete pMaterial;
		pMaterial = 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassLayersManager::GrassLayersManager( GrassRenderManager& _renderManager )
		: sizeX( 0 ), sizeY( 0 )
		, renderManager( _renderManager )
    , heightVersion( INT_MAX )
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassLayersManager::~GrassLayersManager()
	{
		GrassLayersContainer::iterator it = grassLayers.begin();
		GrassLayersContainer::const_iterator itEnd = grassLayers.end();
		for(; it != itEnd; ++it )
			delete it->second;

		grassLayers.clear();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GrassLayersManager::Resize( int xsize, int ysize )
	{
		if( sizeX != xsize && sizeY != ysize )
		{
			sizeX = xsize * RESOLUTION;
			sizeY = ysize * RESOLUTION;

			// resize existed layers
			GrassLayersContainer::iterator it = grassLayers.begin();
			GrassLayersContainer::const_iterator itEnd = grassLayers.end();
			for(; it != itEnd; ++it )
			{
				GrassLayer& layer = *it->second;
				layer.density.SetSizes( sizeX, sizeY );
				layer.density.FillZero();
				layer.dirtyRegions.FillZero();				
			}

			// speed grass
			m_nNumRegionCols = xsize / TILES_PER_REGION + ( xsize % TILES_PER_REGION ? 1 : 0 ); 
			m_nNumRegionRows = ysize / TILES_PER_REGION+ ( ysize % TILES_PER_REGION ? 1 : 0 );

			m_vRegions.clear();
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	unsigned char GrassLayersManager::GetLayerDensity( LayerId id, int column, int row ) const
	{
		GrassLayersContainer::const_iterator it = grassLayers.find( id );
		NI_ASSERT( it != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );
		const unsigned char& data = it->second->density[column][row];
		return data;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GrassLayersManager::SetLayerDensity( LayerId id, int column, int row, unsigned char density )
	{
		GrassLayersContainer::const_iterator it = grassLayers.find( id );
		NI_ASSERT( it != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );
		unsigned char& data = it->second->density[column][row];
		data = density;
		grassLayers[id]->dirtyRegions[column / ( RESOLUTION * TILES_PER_REGION )][row / ( RESOLUTION * TILES_PER_REGION )] = true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GrassLayersManager::MakeUpdateRequest( LayerId id )
	{
		NI_ASSERT( grassLayers.find( id ) != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );
		grassLayers[id]->dirtyRegions.FillEvery( true );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GrassLayersManager::MakeUpdateRequest()
	{
		GrassLayersContainer::iterator it = grassLayers.begin();
		GrassLayersContainer::const_iterator itEnd = grassLayers.end();
		for(; it != itEnd; ++it )
		{
			GrassLayer* pLayer = it->second;
			pLayer->dirtyRegions.FillEvery( true );
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassLayersManager::Update( LayerId id )
	{
		NI_ASSERT( grassLayers.find( id ) != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );

		m_vRegions.clear();

		bool densityChanged = false;

		GrassLayer& layer = *grassLayers[id];
		for( int i = layer.dirtyRegions.GetSizeX() - 1; i >= 0; --i )
			for( int j = layer.dirtyRegions.GetSizeY() - 1; j >= 0; --j )
			{
				bool& dirty = layer.dirtyRegions[i][j];
				if( dirty )
				{
					GenerateBlades( layer, i, j );
					dirty = false;
					densityChanged = true;
				}
			}

		// generate VB
		if( densityChanged )
			GenerateGeometry( layer.pMaterial, layer.id );

		if( pTerrain )
			heightVersion = pTerrain->GetHeightsCounter();

		return densityChanged;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassLayersManager::Update()
	{
		bool updated = false;

		GrassLayersContainer::iterator it = grassLayers.begin();
		GrassLayersContainer::const_iterator itEnd = grassLayers.end();
		for(; it != itEnd; ++it )
			updated |= Update( it->first );

		return updated;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Render::BaseMaterial* GrassLayersManager::GetMaterial( LayerId id ) const
	{
		GrassLayersContainer::const_iterator it = grassLayers.find( id );
		NI_ASSERT( it != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );
		return it->second->pMaterial;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	bool GrassLayersManager::SaveLayer( const nstl::string& filename, LayerId id ) const
	{
		GrassLayersContainer::const_iterator it = grassLayers.find( id );
		NI_ASSERT( it != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );

		CObj<Stream> pStream = RootFileSystem::OpenFile( filename, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
		NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open file for writing %s", filename ), return false; );
		//
		GrassLayer::GrassDensity& density = it->second->density;
		const int length = density.GetSizeX() * density.GetSizeY();
		return pStream->Write( &density[0][0], length ) == length;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassLayersManager::LoadLayer( const nstl::string& filename, LayerId id, unsigned char defaultValue )
	{
		NI_ASSERT( grassLayers.find( id ) != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );

		GrassLayer& layer = *grassLayers[id];
		GrassLayer::GrassDensity& density = layer.density;

		CObj<Stream> pStream = RootFileSystem::OpenFile( filename, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
		if ( IsValid( pStream ) && pStream->IsOk() )
		{
			const int length = density.GetSizeX() * density.GetSizeY();
			const bool result = pStream->Read( &density[0][0], length ) == length;
			layer.dirtyRegions.FillEvery( result );
		}
		else
		{
			for( int x = 0; x < density.GetSizeX(); ++x )
				for( int y = 0; y < density.GetSizeY(); ++y )
					density[x][y] = defaultValue;

			layer.dirtyRegions.FillEvery( true );
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassLayersManager::LayerId GrassLayersManager::LoadLayer( const NDb::GrassLayer& description )
	{
		LayerId id = AddLayer( description.material, description.bladesPerDensity );
		const unsigned char defaultDensity = 128;
		LoadLayer( description.densityFileName, id, defaultDensity );
		return id;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassLayersManager::Load( const vector<NDb::GrassLayer>& grassLayers )
	{
		const int numberOfLayers = grassLayers.size();
		for( int i = 0; i < numberOfLayers; ++i )
			LoadLayer( grassLayers[i] );
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassLayersManager::LayerId GrassLayersManager::GetFreeLayerId() const
	{
		LayerId id = 0;
		while( grassLayers.find( ++id ) != grassLayers.end() );
		return id;
	}


	GrassLayersManager::LayerId GrassLayersManager::AddLayer( const NDb::GrassMaterial* pMaterialDescription, unsigned int blades )
	{
		Render::BaseMaterial* pMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( pMaterialDescription ) );

		// get new id
		const LayerId id = GetFreeLayerId();

		GrassLayer* pLayer = new GrassLayer( id, sizeX, sizeY, blades, pMaterial );
		grassLayers[id] = pLayer;
		return id;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassLayersManager::ChangeBladesPerDensity( LayerId id, unsigned int blades )
	{
		NI_ASSERT( grassLayers.find( id ) != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );
		
		grassLayers[id]->bladesPerDensity = blades;
		grassLayers[id]->dirtyRegions.FillEvery( true );
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassLayersManager::RemoveLayer( LayerId id )
	{
		GrassLayersContainer::iterator it = grassLayers.find( id );
		NI_ASSERT( it != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );

		ReleaseLayerGeometry( id );

		delete it->second;
		grassLayers.erase( it );

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassLayersManager::ChangeMaterial( LayerId id, const NDb::GrassMaterial* pMaterialDescription )
	{
		NI_ASSERT( grassLayers.find( id ) != grassLayers.end(), NStr::StrFmt( "Invalid layer id: %d", id ) );
		ASSERT( pMaterialDescription );
		GrassLayer* pLayer = grassLayers[id];
		delete pLayer->pMaterial;
		pLayer->pMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( pMaterialDescription ) );
		
		RegionsContainer::iterator it = layerRegions[id].begin();
		RegionsContainer::const_iterator itEnd = layerRegions[id].end();
		for (; it != itEnd; ++it )
			renderManager.ChangeRegion( it->second, pLayer->pMaterial );

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct SeedHelper
	{
		int seed;
		SeedHelper( int newSeed ) : seed( NWin32Random::GetSeed() ) { NWin32Random::Seed( newSeed ); }
		~SeedHelper() { NWin32Random::Seed( seed ); }
	};

	bool GrassLayersManager::GenerateBlades( const GrassLayer& layer, int column, int row )
	{
		bool result = false;
		const int regionIndex = GetRegionIndex( row, column );

		for( int i = 0; i < TILES_PER_REGION * RESOLUTION; ++i )
			for( int j = 0; j < TILES_PER_REGION * RESOLUTION; ++j )
			{
				const int n = column * TILES_PER_REGION * RESOLUTION + i;
				const int m = row * TILES_PER_REGION * RESOLUTION + j;

				// set seed
				const int seed = n + ( m << 16 );
				SeedHelper helper( seed );

				const float density = layer.density[n][m];
				const float totalBlades = density / 255 * layer.bladesPerDensity;
				int numberOfBlades = ceilf( totalBlades );
				numberOfBlades += ( NWin32Random::Random( 0.f, 1.f ) < ( totalBlades - numberOfBlades ) ? 1 : 0 );

				result |= numberOfBlades > 0;

				const float x = ( n + 0.5f ) * GRASS_TILE_SIZE / RESOLUTION;
				const float y = ( m + 0.5f ) * GRASS_TILE_SIZE / RESOLUTION;
				const CVec2 cellPosition( x, y );

				for(; numberOfBlades > 0; --numberOfBlades )
				{
					const SBlade blade = GenerateBlade( cellPosition );

					// store all blades together
					m_vRegions[regionIndex].m_vBlades.push_back( blade );					
				}				
			}

		//if( !m_vRegions[regionIndex].m_vBlades.empty() )
		//{
		//	systemLog( NLogg::LEVEL_DEBUG ) << " ---- layer: " << layer.id << ", region: " << regionIndex << endl;
		//	for( int i = 0; i < m_vRegions[regionIndex].m_vBlades.size(); ++i )
		//	{
		//		const SBlade& blade = m_vRegions[regionIndex].m_vBlades[i];
		//		systemLog( NLogg::LEVEL_DEBUG ) << " blade " << i << ": pos: " << blade.m_afPos[0] << " : " << blade.m_afPos[1] << " : " << blade.m_afPos[2] 
		//			<< ", size: " << blade.m_fSize << endl;
		//	}
		//}
		if( !result )
			m_vRegions[regionIndex] = SRegion();

		return result;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassLayersManager::SBlade GrassLayersManager::GenerateBlade( const CVec2& position )
	{
		SBlade sBlade;

		const float offset = GRASS_TILE_SIZE / RESOLUTION * 0.5f;
		sBlade.m_afPos[0] = position.x + NWin32Random::Random( -offset, offset );
		sBlade.m_afPos[1] = position.y + NWin32Random::Random( -offset, offset );

		const bool flip = NWin32Random::Random( -1.f, 1.f ) < 0;

		sBlade.uv[0] = !flip ? 1.0f : 0.0f;
		sBlade.uv[1] = 0.0f;
		sBlade.uv[2] = !flip ? 0.0f : 1.0f;
		sBlade.uv[3] = 0.0f;
		sBlade.uv[4] = !flip ? 0.0f : 1.0f;
		sBlade.uv[5] = 1.0f;
		sBlade.uv[6] = !flip ? 1.0f : 0.0f;
		sBlade.uv[7] = 1.0f;	 		
		
		CVec4 normailAndHeight = GetHeightAndNormal( position.x, position.y );
		sBlade.m_afPos[2] = normailAndHeight.w;

		sBlade.m_afNormal[0] = normailAndHeight.x;
		sBlade.m_afNormal[1] = normailAndHeight.y;
		sBlade.m_afNormal[2] = normailAndHeight.z;


		sBlade.m_fSize = NWin32Random::Random( c_fMinBladeSize, c_fMaxBladeSize );

		// compute wind effects
		sBlade.m_fThrow = NWin32Random::Random( c_fMinBladeThrow, c_fMaxBladeThrow );

		return sBlade;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CVec4 GrassLayersManager::GetHeightAndNormal( float x, float y ) const
	{
		// TODO: implement terrain height getting
		NI_VERIFY( pTerrain, "Invalid heights controller!", return VNULL4; );

		CVec3 normal;
		float height;
		pTerrain->GetHeight( x, y, &height, &normal );
		return CVec4( normal, height );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassLayersManager::ReleaseLayerGeometry( LayerId id )
	{
		if( layerRegions.find( id ) == layerRegions.end() )
			return false;

		RegionsContainer::iterator it = layerRegions[id].begin();
		RegionsContainer::iterator itEnd = layerRegions[id].end();
		for(; it != itEnd; ++it )
		{
			const bool result = renderManager.RemoveRegion( it->second );
			NI_ASSERT( result, NStr::StrFmt( "Can't remove region (id: %d) from rander!", it->second ) );
		}
			
		layerRegions.erase( id );
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GrassLayersManager::ReleaseRegionGeometry( LayerId id, int regionId )
	{
		if( layerRegions.find( id ) == layerRegions.end() )
			return false;

		RegionsContainer::iterator it = layerRegions[id].find( regionId );
		if( it != layerRegions[id].end() )
		{
			const bool result = renderManager.RemoveRegion( it->second );
			NI_ASSERT( result, NStr::StrFmt( "Can't remove region (id: %d) from rander!", it->second ) );
			layerRegions[id].erase( it );
		}
		
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TO, typename FROM> TO BitCast( FROM value ) { return *(TO*)( (void*)&value ); }

	void GrassLayersManager::GenerateGeometry( Render::BaseMaterial* pMaterial, LayerId layerId )
	{
		// prepare static vertex buffers
		hash_map<int, SRegion>::iterator itRegion = m_vRegions.begin();
		hash_map<int, SRegion>::iterator itEnd = m_vRegions.end();
		for ( ; itRegion != itEnd; ++itRegion )
		{
			SRegion* pRegion = &itRegion->second;

			// setup up temporary buffer to copy later
			const int c_nNumCorners = 4;
			unsigned int uiNumBlades = (unsigned int)pRegion->m_vBlades.size( );
			unsigned int uiNumVertices = uiNumBlades * c_nNumCorners;
			unsigned int uiBufferSize = uiNumVertices * sizeof( GrassRegion::VertexStride );
			char* pBuffer = new char[uiBufferSize];

			// setup initial pointers for individual attribute copying
			GrassRegion::VertexStride* pVertex = reinterpret_cast<GrassRegion::VertexStride*>( pBuffer );

			//const CVec3 regionTranslation( pRegion->m_afCenter[0], pRegion->m_afCenter[1], pRegion->m_afCenter[2] );
			//const Matrix43 regionBasis( QNULL, regionTranslation );
			const Matrix43 regionBasis = IDENTITY_MATRIX;

			for ( vector<SBlade>::const_iterator iBlade = pRegion->m_vBlades.begin( ); iBlade != pRegion->m_vBlades.end( ); ++iBlade )
			{
				for ( int nCorner = 0; nCorner < c_nNumCorners; ++nCorner, ++pVertex )
				{
					// position
					//const CVec3 worldPosition( iBlade->m_afPos[0], iBlade->m_afPos[1], iBlade->m_afPos[2] );
					//pVertex->position = worldPosition - regionTranslation;
					pVertex->position.Set( iBlade->m_afPos[0], iBlade->m_afPos[1], iBlade->m_afPos[2] );

					// normal
					pVertex->normal.Set( iBlade->m_afNormal[0], iBlade->m_afNormal[1], iBlade->m_afNormal[2] );

					// texcoord 0
					pVertex->uv.x = iBlade->uv[nCorner * 2];
					pVertex->uv.y = iBlade->uv[nCorner * 2 + 1];

					// texcoord 1
					pVertex->params.x = (float)nCorner;

					if (nCorner < 2)
						pVertex->params.y = iBlade->m_fThrow;
					else
						pVertex->params.y = 0.0f;

					pVertex->params.z = iBlade->m_fSize;
				}
			}

			// check if we created region on this place
			RegionsContainer::iterator it = layerRegions[layerId].find( itRegion->first );

			if ( uiNumVertices > 0 )
			{
				// fill up index buffer
				const unsigned int indexBufferSize = pRegion->m_vBlades.size() * 6;
				unsigned int* pIndexBuffer = new unsigned int[indexBufferSize];
				for ( int uiBlade = 0; uiBlade < pRegion->m_vBlades.size( ); ++uiBlade )
				{
					unsigned int uiStart = uiBlade * 4;
					
					pIndexBuffer[uiBlade * 6 + 0] = uiStart;
					pIndexBuffer[uiBlade * 6 + 1] = uiStart + 1;
					pIndexBuffer[uiBlade * 6 + 2] = uiStart + 2;
					pIndexBuffer[uiBlade * 6 + 3] = uiStart;
					pIndexBuffer[uiBlade * 6 + 4] = uiStart + 2;
					pIndexBuffer[uiBlade * 6 + 5] = uiStart + 3;
				}

				GrassRenderManager::RegionInformation info;
				
				// setup buffers
				info.vertexBufferSize = uiBufferSize;
				info.vertexBuffer = pBuffer;
				info.indexBufferSize = indexBufferSize * sizeof( unsigned int );
				info.indexBuffer = reinterpret_cast<char*>( pIndexBuffer );

				// setup dip descriptor
				info.dipDescriptor.numVertices = uiNumVertices;
				info.dipDescriptor.startIndex = 0;
				info.dipDescriptor.minIndex = 0;
				info.dipDescriptor.baseVertexIndex = 0;
				info.dipDescriptor.primitiveCount = pRegion->m_vBlades.size() * 2;
				info.dipDescriptor.primitiveType = Render::RENDERPRIMITIVE_TRIANGLELIST;

				//{
				//	systemLog( NLogg::LEVEL_DEBUG ) << " ---- generated geometry, region: " << i << endl
				//		<< "primitiveCount: " << info.dipDescriptor.primitiveCount << endl
				//		<< "numVertices: " << info.dipDescriptor.numVertices << endl;
				//}
				
				if( it == layerRegions[layerId].end() )
				{
					// create new one
					const GrassRenderManager::GrassRegionId id = renderManager.AddRegion( info, pMaterial, regionBasis );
					layerRegions[layerId][itRegion->first] = id;
				}
				else
				{
					// change geometry
					const bool result = renderManager.ChangeRegion( it->second, info );
					NI_ASSERT( result, NStr::StrFmt( "Can't change region (layer: %d, region id: %d) in rander!", layerId, it->second ) );
				}

				delete[] pIndexBuffer;
			}
			else
			{
				// check if we should delete created regions
				if( it != layerRegions[layerId].end() )
				{
					const bool result = renderManager.RemoveRegion( it->second );
					NI_ASSERT( result, NStr::StrFmt( "Can't delete region (layer: %d, region id: %d) from rander!", layerId, it->second ) );
					layerRegions[layerId].erase( it );
				}
			}

			delete [] pBuffer;
		}
	}
}

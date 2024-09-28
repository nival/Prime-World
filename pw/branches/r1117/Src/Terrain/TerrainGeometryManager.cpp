#include "stdafx.h"

#ifndef VISUAL_CUTTED

#include "TerrainGeometryManager.h"
#include "Terrain.h"
#include "BezierSurface.h"
#include "ArraySampler.h"

#include "../System/noncopyable.h"

#include "TerrainElement.h"
#include "TerrainLayerManager.h"
#include "../MeshConverter/MeshHeader.h"
#include "../Render/MeshResource.h"
#include "../Render/renderresourcemanager.h"
#include "../System/lerp.h"
#include "../System/Geom.h"
#include "../Render/light.h"
#include "../Render/debugrenderer.h"

#include "../System/Win32Random.h"
#include "../libdb/XmlSaver.h"

#include "../Scene/LightingScene.h"

static NDebug::PerformanceDebugVar render_TerrainLoadTime( "TerrainLoadTime", "RenderOffline", 10, 10, false );
static NDebug::PerformanceDebugVar render_TerrainUpdateTime( "TerrainUpdateTime", "RenderOffline", 10, 10, false );

#define BAKED_TERRAIN_FILE_VERSION 0x01
#define BAKED_TERRAIN_FILE_SIGN  MAKELONG('ET', BAKED_TERRAIN_FILE_VERSION)

namespace Terrain
{
	namespace
	{
		class LayerSamplerProxy
		{
		public:
			typedef unsigned char ArgType;
			typedef CVec4 ValueType;

			explicit LayerSamplerProxy(unsigned char _id[]) : id(_id) {}

			ValueType operator()(ArgType x)
			{
				return CVec4(float(x == id[2]), float(x == id[1]), float(x == id[0]), float(x == id[3]));
			}

		private:
			unsigned char* id;
		};

	}	// anonymous namespace

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TerrainGeometryManager::TerrainGeometryManager()
    : pOwner(NULL)
    , controlVertexes()
    , patchesOrigin( VNULL3 )
    , weldThreshold(0.0f)
    , weldLookupSize(0.0f)
    , TCVs()
    , changedTCVs()
    , TCV2TerrainElement()
    , requests() // don't need to free, pData is always 0
    , geometryPlacement()
    , geometryInformations() // contains copy of fileToOriginalGeometry members, so don't need to free
    , fileToOriginalGeometry()
    , modifiedGeometry()
    , lightingScene(NULL)
    , modificationCallbacks()
  {
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TerrainGeometryManager::~TerrainGeometryManager()
	{
    // free original geometries
		FileToOriginalGeometryAssociation::iterator it = fileToOriginalGeometry.begin();
		const FileToOriginalGeometryAssociation::const_iterator itEnd = fileToOriginalGeometry.end();
		for( ; it != itEnd; ++it )
    {
			delete it->second.pOriginaVertexBuffer;
      it->second.pOriginaVertexBuffer = NULL; // in case of non-trivial destructor
    }
		fileToOriginalGeometry.clear();

    // free modified geometries
		TerrainElementModifiedContainer::iterator modifiedIt = modifiedGeometry.begin();
		const TerrainElementModifiedContainer::const_iterator modifiedItEnd = modifiedGeometry.end();
		for( ; modifiedIt != modifiedItEnd; ++modifiedIt )
		{
			Render::TerrainElementGeometryRaw& rawData = modifiedIt->second;
			//delete rawData.rawData;
      Aligned_Free(rawData.rawData);
      rawData.rawData = NULL; // in case of non-trivial destructor
		}
		modifiedGeometry.clear();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::Initialize( const NDb::TerrainGeometry& descriptor )
	{
    ASSERT(pOwner->IsEditable());
    weldThreshold = descriptor.weldThreshold;
    weldLookupSize = descriptor.weldLookupSize;
    
    patchesOrigin = CVec3(0.0f, 0.0f, 0.0f);

		//TCVManager tcvManager( controlVertexes );

		// init CVs
		for( int u = 0; u < MAXIMUM_INDEX_OF_TCV; ++u )
			for( int v = 0; v < MAXIMUM_INDEX_OF_TCV; ++v )
			{
				Matrix43& tcvPosition = TCVs[v][u];
				const CVec3 basis( Patch::SIZE_OF_PATCH * u + patchesOrigin.x, Patch::SIZE_OF_PATCH * v + patchesOrigin.y, patchesOrigin.z );
				tcvPosition.Set( QNULL, basis, CVec3( 1.f, 1.f, 1.f ) );
				//
				//tcvManager.Set( u, v, tcvPosition );
				changedTCVs[v][u] = true;
			}		
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CVec3 TerrainGeometryManager::ComputeVertex( const CVec3& vertex ) const
	{
    ASSERT(pOwner->IsEditable());
		// find influencing patch
		const float xInPatchSpace = vertex.x / Patch::SIZE_OF_PATCH;
		const float yInPatchSpace = vertex.y / Patch::SIZE_OF_PATCH;
		const int U = static_cast<int>( xInPatchSpace );
		const int V = static_cast<int>( yInPatchSpace );

		// get normalized u and v
		// u/v are in interval [0, 1)
		const float u = xInPatchSpace - U;
		const float v = yInPatchSpace - V;

		static StaticArray<StaticArray<ControlVertex, Patch::NUMBER_OF_CV>, Patch::NUMBER_OF_CV> buffer;

    CVec3 result;
    {
      const Matrix43& basisTCV = TCVs[V][U];
      result.x = basisTCV._14 + u * Patch::SIZE_OF_PATCH;
      result.y = basisTCV._24 + v * Patch::SIZE_OF_PATCH;
    }

		for( int i = 0; i < Patch::NUMBER_OF_CV; ++i )
    {
			for( int j = 0; j < Patch::NUMBER_OF_CV; ++j )
			{
				const int tcvU = i <= 1 ? U : U + 1;
				const int tcvV = j <= 1 ? V : V + 1;
				const Matrix43& basisTCV = TCVs[tcvV][tcvU];
				
				ControlVertex& cv = buffer[j][i];
				const int u = i <= 1 ? i : i - (Patch::NUMBER_OF_CV - 1);
				const int v = j <= 1 ? j : j - (Patch::NUMBER_OF_CV - 1);
				cv.Set( 
					u * Patch::DISTANCE_BETWEEN_CV,
					v * Patch::DISTANCE_BETWEEN_CV,
					vertex.z );

        cv = Transform( cv, basisTCV );
			}
    }

    Patch patch;
    for ( int i = 0; i < Patch::NUMBER_OF_CV; i++ )
    {
      patch.SetRow( &buffer[i][0], i );
    }

    result.z = patch.ComputeVertex(u, v).z;
    return result;
	}

	bool TerrainGeometryManager::Load( const NDb::TerrainGeometry& descriptor )
	{
		NDebug::PerformanceDebugVarGuard render_TerrainLoadTimeGuard( render_TerrainLoadTime, true );

    // load all terrain elements...
		// if baked geometry exist load it
		bool bakedInformationExist = RootFileSystem::GetFileInfo( 0, descriptor.bakedTerrainFileName );

    if (pOwner->IsEditable())
    {
    }
    else
    {
      NI_ASSERT(bakedInformationExist, NStr::StrFmt("Can't find file '%s', unable to load terrain", descriptor.bakedTerrainFileName.c_str()));
    }

    if (bakedInformationExist)
    {
      if (LoadBakedGeometry(descriptor))
        return true;
    }

    if (pOwner->IsEditable())
    {
      if (LoadRawGeometry(descriptor))
        return true;
    }

    return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool TerrainGeometryManager::BakeTerrainElement( TerrainElementId id, Stream* pBakedStream ) const
	{
    ASSERT(pOwner->IsEditable());
		NI_VERIFY( pBakedStream, "Invalid storage stream!", return false; );

		// write modified data to stream
    const Render::TerrainElementGeometryRaw* elementRawData = GetElement(id);
    NI_VERIFY( elementRawData != NULL, "Can't find modified data for terrain element!", return false; );
		pBakedStream->Write( elementRawData->rawData, elementRawData->rawDataSize );
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TerrainElementId TerrainGeometryManager::AddTerrainElement( const NDb::TerrainElementInstance& descriptor, const string& fileName )
	{
    ASSERT(pOwner->IsEditable());

		// load raw data
		Render::TerrainElementGeometryRaw elementRawData;
		CPtr<Stream> pFileStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    NI_VERIFY(pFileStream.GetPtr(), NStr::StrFmt("Unable to open file '%s'", fileName.c_str()), return TERRAINELEMENTID_BAD; );

		if (!Render::RenderResourceManager::CreateTerrainElementRawData(pFileStream, &elementRawData))
			return TERRAINELEMENTID_BAD;

    if (!Render::RenderResourceManager::CheckTerrainElementGeometryRawDataVersion(elementRawData))
      return TERRAINELEMENTID_BAD;

    // get original vertex buffer data
    const OriginalGeometryInformation& info = GetOriginalGeometryInformation( fileName, elementRawData );

    // TODO: replace separate components => matrix
    const CQuat quat( ToRadian( descriptor.angle ), 0.f, 0.f );
    Matrix43 basis( quat, descriptor.position, descriptor.scale );

		TerrainElementStrideNew* pVertices = (TerrainElementStrideNew*)elementRawData.vertexBuffer;
		Modify(pVertices, pVertices, elementRawData.vertexBufferSize, basis);
  
		
    elementRawData.pMaterial = dynamic_cast<const NDb::TerrainMaterial*>(descriptor.material.GetPtr());
    // pass loaded information to render manager
    Render::BaseMaterial* pMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( descriptor.material.GetPtr() ) );
		const TerrainElementId id = pOwner->GetElementManager().AddElement( elementRawData, pMaterial, basis );
		pOwner->GetHeightManager().MarkAsDirty();
		pOwner->GetLayerManager().NotifyElementChange(id);

		// store placement
		geometryPlacement[id] = basis;

		// save actual information about geometry
		geometryInformations[id] = info;

		// store modified information
		modifiedGeometry[id] = elementRawData;

		// associate TE and patch
		AssociateTerrainElementAndTCV( id );

    return id;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TerrainElementId TerrainGeometryManager::AddTerrainElement(const NDb::TerrainElementInstance& descriptor, Stream* pFileStream )
	{
		// load raw data
		Render::TerrainElementGeometryRaw elementRawData;
    NI_VERIFY( pFileStream, "Invalid stream!", return TERRAINELEMENTID_BAD; );

		if (!Render::RenderResourceManager::GetTerrainElementGeometryRawData(pFileStream, &elementRawData))
			return TERRAINELEMENTID_BAD;

    if (!Render::RenderResourceManager::CheckTerrainElementGeometryRawDataVersion(elementRawData))
      return TERRAINELEMENTID_BAD;

		// TODO: replace separate components => matrix
		CQuat quat( ToRadian( descriptor.angle ), 0.f, 0.f );
		Matrix43 basis( quat, descriptor.position, descriptor.scale );

    const bool cleanGeometry = (NGlobal::GetVar("clean_terrain_geometry").GetInt64() != 0);
    if(cleanGeometry)
      Render::RenderResourceManager::CopyElementGeometry(&elementRawData/*, false*/);

    Render::BaseMaterial* pMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( descriptor.material.GetPtr() ) );
		const TerrainElementId id = pOwner->GetElementManager().AddElement( elementRawData, pMaterial, basis );

    if(cleanGeometry)
      Aligned_Free(elementRawData.rawData);

		pOwner->GetHeightManager().MarkAsDirty();
		pOwner->GetLayerManager().MarkPixelsAsDirty();

		return id;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const TerrainGeometryManager::OriginalGeometryInformation& TerrainGeometryManager::GetOriginalGeometryInformation( const string& fileName, const Render::TerrainElementGeometryRaw& rawData )
	{
    ASSERT(pOwner->IsEditable());

		FileToOriginalGeometryAssociation::const_iterator it = fileToOriginalGeometry.find( fileName );
		if( it == fileToOriginalGeometry.end() )
		{
			NI_ASSERT( rawData.vertexBufferSize, "Loaded vertex buffer is empty!" );

			char* pBuffer = new char[rawData.vertexBufferSize];
			memcpy( pBuffer, rawData.vertexBuffer, rawData.vertexBufferSize );

			const OriginalGeometryInformation info( rawData.vertexBufferSize, pBuffer );
			it = fileToOriginalGeometry.insert( make_pair( fileName, info ) ).first;
		}
		return it->second;
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool TerrainGeometryManager::LoadBakedGeometry(const NDb::TerrainGeometry& descriptor)
  {
    MessageTrace("Loading baked geometry from file: %s", descriptor.bakedTerrainFileName);

    CObj<Stream> pBakedStream(RootFileSystem::OpenFile(descriptor.bakedTerrainFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING));

    NI_VERIFY(pBakedStream && pBakedStream->IsOk(), NStr::StrFmt("Can't open file: %s", descriptor.bakedTerrainFileName), return false);

    {
      unsigned sign;

      const bool sign_read = (pBakedStream->Read(&sign, sizeof(sign)) == sizeof(sign));

      NI_DATA_VERIFY(sign_read, "Invalid baked terrain file!", return false);
      NI_DATA_VERIFY(sign == BAKED_TERRAIN_FILE_SIGN, "Invalid baked terrain file format!", return false);
    }

    // load baked geometry
    const int numberOfElements = descriptor.terrainElements.size();

    for (int i = 0; i < numberOfElements; ++i)
    {
      const NDb::TerrainElementInstance& instance = descriptor.terrainElements[i];
      AddTerrainElement(instance, pBakedStream);
    }

    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool TerrainGeometryManager::LoadRawGeometry(const NDb::TerrainGeometry& descriptor)
  {
    Initialize(descriptor);

    const int numberOfElements = descriptor.terrainElements.size();

    for (int i = 0; i < numberOfElements; ++i)
    {
      const NDb::TerrainElementInstance& instance = descriptor.terrainElements[i];
      AddTerrainElement(instance, instance.terrainObject->geometryFileName);
    }

    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::AssociateTerrainElementAndTCV( TerrainElementId id )
	{
    ASSERT(pOwner->IsEditable());

		GeometryInformationContainer::iterator it = geometryInformations.find( id );
		NI_VERIFY( it != geometryInformations.end(), "Invalid terrain element id!", return; );
		const OriginalGeometryInformation& info = it->second;

		TerrainElementPlacementContainer::iterator itPlacement = geometryPlacement.find( id );
		NI_VERIFY( itPlacement != geometryPlacement.end(), "Invalid terrain element id!", return; );
		const Matrix43& basis = itPlacement->second;

		// get original geometry
		const TerrainElementStrideNew* pTEGeometry = reinterpret_cast<const TerrainElementStrideNew*>( info.pOriginaVertexBuffer );
		const int numberOfVertexes = info.bufferSize / sizeof( TerrainElementStrideNew );

		StaticArray<StaticArray<bool, MAXIMUM_INDEX_OF_TCV>, MAXIMUM_INDEX_OF_TCV> usedTCVs;
		// unsafe {
		::memset( &usedTCVs[0][0], false, MAXIMUM_NUMBER_OF_PATCHES * MAXIMUM_NUMBER_OF_PATCHES );
		// unsafe }

		for( int k = 0; k < numberOfVertexes; ++k )
		{
			const CVec3 vertex = Transform( pTEGeometry[k].position, basis );

			// find influencing TCVs
			const float xInPatch = ( vertex.x - patchesOrigin.x ) / Patch::SIZE_OF_PATCH;
			const float yInPatch = ( vertex.y - patchesOrigin.y ) / Patch::SIZE_OF_PATCH;

			const int i = static_cast<int>( xInPatch );
			const int j = static_cast<int>( yInPatch );

      NI_VERIFY( j < MAXIMUM_INDEX_OF_TCV && i < MAXIMUM_INDEX_OF_TCV, NStr::StrFmt( "Invalid vertex coordinates (%d x %d) in patch %d", i, j, id ), continue );
			//usedTCVs[j][i] = true;
			//usedTCVs[j + 1][i] = true;
			//usedTCVs[j + 1][i + 1] = true;
			//usedTCVs[j][i + 1] = true;

			const float epsilon = 0.5f;
			if( xInPatch - i >= epsilon )
			{
				if( yInPatch - j >= epsilon )
					usedTCVs[j + 1][i + 1] = true;
				else
					usedTCVs[j][i + 1] = true;
			}
			else
			{
				if( yInPatch - j >= epsilon )
					usedTCVs[j + 1][i] = true;
				else
					usedTCVs[j][i] = true;
			}
		}

		for( unsigned int j = 0; j < usedTCVs.capacity(); ++j )
			for( unsigned int i = 0; i < usedTCVs[j].capacity(); ++i )
				if( usedTCVs[j][i] )
				{
					NI_ASSERT( find( TCV2TerrainElement[j][i].begin(), TCV2TerrainElement[j][i].end(), id ) == TCV2TerrainElement[j][i].end(), "Second registration!" );
					TCV2TerrainElement[j][i].push_back( id );
				}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool TerrainGeometryManager::DeleteTerrainElement( TerrainElementId id )
	{
    ASSERT(pOwner->IsEditable());

		// remove TE from requests
		RequestsContainer::iterator it = requests.begin();
		RequestsContainer::iterator itEnd = requests.end();

		for(; it != itEnd; )
		{
			if( it->id == id )
				it = requests.erase( it );
			else
				++it;
		}

		// remove from geometry information
		geometryInformations.erase( id );

		geometryPlacement.erase( id );

		// remove TE from TCV <=> TE association
		for( unsigned int j = 0; j < TCV2TerrainElement.capacity(); ++j )
		{
			for( unsigned int i = 0; i < TCV2TerrainElement[j].capacity(); ++i )
			{
				vector<TerrainElementId>& elements = TCV2TerrainElement[j][i];
				vector<TerrainElementId>::iterator it = find( elements.begin(), elements.end(), id );
				if( it != elements.end() )
					elements.erase( it );
			}
		}

		// remove TE from render manager
		pOwner->GetElementManager().RemoveElement( id );

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::Update()
	{
		NDebug::PerformanceDebugVarGuard render_TerrainUpdateTimeGuard( render_TerrainUpdateTime, true );

		// apply changed TCV
		CheckTCV();

		// apply changed layer masks (after TCV)
		CheckMasks();

		// process modification requests
		ProcessModificationRequests();
/*
    // show TCV bias
    for( int u = 0; u < MAXIMUM_INDEX_OF_TCV; ++u )
      for( int v = 0; v < MAXIMUM_INDEX_OF_TCV; ++v )
      {
        Matrix43& tcvPosition = TCVs[v][u];

        // locate nearest seam
        float const patchSize = 10.0f;
        float x = tcvPosition._14;
        float x0 = (float)Round(x / patchSize) * patchSize;
        float y = tcvPosition._24;
        float y0 = (float)Round(y / patchSize) * patchSize;
        float z = tcvPosition._34;
        if (fabs(x - x0) > FLT_EPSILON || fabs(y - y0) > FLT_EPSILON)
        {
          int t = 255 - ClampFast((int)(255.0f * Max(fabs(x - x0), fabs(y - y0))), 0, 255);
          Render::DebugRenderer::DrawPoint3D(CVec3(x0,y0,z), 1.0f, Render::Color(255,t,0,255), false);
        }
      }
*/
/*
    // show patch normals
    if (g_curpick.x * g_curpick.y > 0.0f)
    {
      TerrainElementId id = pOwner->GetElementManager().LocateElement(g_curpick.x, g_curpick.y);
      TerrainElement* pElement = pOwner->GetElementManager().GetElement(id);
      if (pElement)
      {
        TerrainElementStrideNew* pVertex = Render::LockVB<TerrainElementStrideNew>(Get(pElement->mesh.GetVertexBuffer()), D3DLOCK_READONLY);
        unsigned numVertices = pElement->mesh.GetDipDescriptor().numVertices;
        for (unsigned i = 0; i < numVertices; i++, pVertex++)
        {
          CVec3 pos(pVertex->position);
          pos.Displace(pVertex->normal, 2.0f);
          Render::DebugRenderer::DrawLine3D(pVertex->position, pos, Render::Color(255,255,255,255), Render::Color(255,0,0,255), true);
        }
      }
    }
*/
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::InvalidateElement(TerrainElementId id, int flags)
	{
    ASSERT(pOwner->IsEditable());
		TerrainElement* pElement = pOwner->GetElementManager().GetElement(id);
		NI_ASSERT( pElement, "no such id!" );

    // find & remove previous modification requests for this element
    RequestsContainer::iterator it = requests.begin();
    while ( it != requests.end() )
    {
      if ( it->id == id )
      {
        flags |= it->flags; // absorb invalidate flags from previous request
        it = requests.erase(it);
      }
      else
      {
        ++it;
      }
    }

		requests.push_back().Set( id, flags, &pElement->worldAABB );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::ProcessModificationRequests()
	{
		if ( requests.empty() )
			return;

    static int updateID = 0;
    updateID++;

    ASSERT(pOwner->IsEditable());

		int allFlags = 0;

    RequestsContainer::iterator it = requests.begin();
    RequestsContainer::iterator last = requests.end();

    for ( ; it != last; ++it )
		{
			ModificationRequestData& request = *it;
			
      allFlags |= request.flags;

			TerrainElement* pElement = pOwner->GetElementManager().GetElement(request.id);
      request.pData = Render::LockVB<unsigned char>(Get(pElement->mesh.GetVertexBuffer()), 0);

			const int id = request.id;
			GeometryInformationContainer::iterator it = geometryInformations.find( id );
			NI_VERIFY( it != geometryInformations.end(), "Invalid terrain element id!", continue; );
			const OriginalGeometryInformation& info = it->second;

			TerrainElementPlacementContainer::iterator itPlacement = geometryPlacement.find( id );
			NI_VERIFY( itPlacement != geometryPlacement.end(), "Invalid terrain element id!", continue; );
			const Matrix43& basis = itPlacement->second;

			if (request.flags & INVALID_GEOMETRY)
			{
				Modify( (TerrainElementStrideNew*)( request.pData ), reinterpret_cast<const TerrainElementStrideNew*>( info.pOriginaVertexBuffer ), info.bufferSize, basis );
				request.pAABB->Calculate( info.bufferSize / sizeof(TerrainElementStrideNew), (CVec3*)request.pData, sizeof(TerrainElementStrideNew) );
				pOwner->GetHeightManager().MarkAsDirty();
			}

      if (request.flags & INVALID_LIGHTING)
      {
        CalculateLightingEx(id, (TerrainElementStrideNew*)( request.pData ), info.bufferSize, NDb::LIGHTENVIRONMENT_DAY);
        CalculateLightingEx(id, (TerrainElementStrideNew*)( request.pData ), info.bufferSize, NDb::LIGHTENVIRONMENT_NIGHT);
      }

			if (request.flags & INVALID_MASKS)
				CopyMasks(id, (TerrainElementStrideNew*)( request.pData ), info.bufferSize);

			// for editor cache modified geometry
			Render::TerrainElementGeometryRaw* data = GetElement( request.id );
			if ( data != NULL )
			{
				memcpy( data->vertexBuffer, (void*)request.pData, data->vertexBufferSize );
			}

			request.finished = true;

			pElement->mesh.GetVertexBuffer()->Unlock();

      // notify about geometry modification
    }


    ModificationCallbackList::iterator itM = modificationCallbacks.begin();
    ModificationCallbackList::iterator lastM = modificationCallbacks.end();

    for (; itM != lastM; ++itM )
    {
      RequestsContainer::iterator itR = requests.begin();
      RequestsContainer::iterator lastR = requests.end();

      ((ModificationCallback)itM->first)( itM->second, allFlags, 0, EModification::First );

      for ( ; itR != lastR; ++itR )
      {
        ((ModificationCallback)itM->first)( itM->second, allFlags, itR->id, EModification::Next );
      }

      ((ModificationCallback)itM->first)( itM->second, allFlags, 0, EModification::Last );
    }

    requests.clear();
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::SaveTCV( Stream* pStream )
	{
    ASSERT(pOwner->IsEditable());
		const bool reading = false;
		Serialize( pStream, reading );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::LoadTCV( Stream* pStream, bool applyInstuntly )
	{
    ASSERT(pOwner->IsEditable());
		const bool reading = true;
		Serialize( pStream, reading, applyInstuntly );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void TerrainGeometryManager::DoubleSizeConverter( int fromSize )
  {
    TCVContainer oldTCVs;

    for ( int i = 0; i < MAXIMUM_INDEX_OF_TCV; i++ )
    {
      for ( int j = 0; j < MAXIMUM_INDEX_OF_TCV; j++ )
      {
        oldTCVs[i][j] = TCVs[i][j];
      }
    }

    for ( int i = 0; i < fromSize; i++ )
    {
      for ( int j = 0; j < fromSize; j++ )
      {
        if ( i == 0 && j == 0 )
        {
          TCVs[i][j] = oldTCVs[i][j];
        }
        else if ( i == 0 )
        {
          TCVs[i][j*2] = oldTCVs[i][j];
          TCVs[i][j*2-1] = (TCVs[i][j*2-2]+TCVs[i][j*2])/2.0f;
        }
        else if ( j == 0)
        {
          TCVs[i*2][j] = oldTCVs[i][j];
          TCVs[i*2-1][j] = (TCVs[i*2-2][j]+TCVs[i*2][j])/2.0f;
        }
        else
        {
          TCVs[i*2][j*2] = oldTCVs[i][j];

          TCVs[i*2][j*2-1] = (TCVs[i*2][j*2-2]+TCVs[i*2][j*2])/2.0f;
          TCVs[i*2-1][j*2] = (TCVs[i*2-2][j*2]+TCVs[i*2][j*2])/2.0f;
          TCVs[i*2-1][j*2-1] = (TCVs[i*2-2][j*2]+TCVs[i*2][j*2]+TCVs[i*2][j*2-2]+TCVs[i*2-2][j*2-2])/4.0f;
        }
      }
    }

  }

    void TerrainGeometryManager::Serialize( Stream* pStream, bool reading, bool applyInstuntly )
    {
      ASSERT(pOwner->IsEditable());
      NI_VERIFY( pStream, "Invalid stream!", return; );
      CObj<IXmlSaver> pSaver( CreateXmlSaver( pStream, reading ) );

      // TODO: implement in separate class/struct and in binary format
      pSaver->StartChunk( "TerrainControlVertices", 0 );

      pSaver->Add( "origin", &patchesOrigin );

      pSaver->StartChunk( "transforms", 0 );

      const unsigned int numberOfRows = TCVs.capacity();

      for( unsigned int v = 0; v < numberOfRows; ++v )
      {
        for( unsigned int u = 0; u < numberOfRows; ++u )
        {
          Matrix43& basis = TCVs[v][u];
          pSaver->Add( "Item", &basis, v * numberOfRows + u + 1 );

          if( reading )
            changedTCVs[v][u] = applyInstuntly;
        }
      }

      pSaver->FinishChunk(); // transforms 
      pSaver->FinishChunk(); // TerrainControlVertices 

      MessageTrace( "TerrainGeometryManager::Serialize done" );
    }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::SetTCV( int column, int row, const Matrix43& basis )
	{
		// mark TCV as changed
		TCVs[row][column] = basis;
		changedTCVs[row][column] = true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::CheckTCV()
	{
		const int numberOfRows = changedTCVs.capacity();
		for( int row = 0; row < numberOfRows; ++row )
		{
			const int numberOfcolumns = changedTCVs[row].capacity();
			for( int column = 0; column < numberOfcolumns; ++column )
			{
				if( changedTCVs[row][column] )
				{
					ApplyTCV( row, column );
					changedTCVs[row][column] = false;
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/** get TCV basis for modification */
	const Matrix43& TerrainGeometryManager::GetTCV( int column, int row ) const
	{
		return TCVs[row][column];
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::ApplyTCV( int row, int column )
	{
		vector<TerrainElementId>& elements = TCV2TerrainElement[row][column];

		for ( int k = elements.size() - 1; k >= 0; --k )
		{
			const TerrainElementId id = elements[k];

			int invalidate = INVALID_GEOMETRY;
      if (lightingScene && lightingScene->IsImmediateUpdateOn())
      {
        invalidate |= INVALID_LIGHTING;
      }

      // send notification to render
			InvalidateElement(id, invalidate);
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::CheckMasks()
	{
		TerrainLayerRegion& updateRegion = pOwner->GetLayerManager().GetUpdateRegion();
		if (!updateRegion.IsEmpty())
		{
      ASSERT(pOwner->IsEditable());
			struct MaskInvalidateFunctor
			{
				TerrainGeometryManager* pGeometryManager;
				void operator()(TerrainElementInfo const& elem)
				{
					// send notification to render
					pGeometryManager->InvalidateElement(elem.id, INVALID_MASKS);
				}
      } invalidateMasks = {this};

			Render::AABB bounds;
			updateRegion.GetWorldAABB(pOwner->GetGridConstants(), bounds);
			pOwner->GetElementManager().ForAllElementInfosAABB(invalidateMasks, bounds);
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::Modify( TerrainElementStrideNew* out, const TerrainElementStrideNew* in, unsigned int bufferSize, const Matrix43& basis ) const
	{
    ASSERT(pOwner->IsEditable());

		const unsigned int numberOfElements = bufferSize / sizeof( TerrainElementStrideNew );
		for( unsigned int i = 0; i < numberOfElements; ++i )
		{
			const CVec3 inPosition = Transform( in[i].position, basis );

			// compute NURBS vertex
			const CVec3 vertex = inPosition - patchesOrigin;
			const CVec3 nurbsVertex = ComputeVertex( vertex );

			out[i].position = nurbsVertex;

			// calculate normal for NURBS vertex
			const float delta = 0.05f;
			CVec3 vector1;
			CVec3 vector2;
			//
			if( vertex.x + delta < Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES )
				vector1 = ComputeVertex( CVec3( vertex.x + delta, vertex.y, vertex.z ) ) - nurbsVertex;
			else
				vector1 = ComputeVertex( CVec3( vertex.x - delta, vertex.y, vertex.z ) ) - nurbsVertex;

			if( vertex.y + delta < Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES )
				vector2 = ComputeVertex( CVec3( vertex.x, vertex.y + delta, vertex.z ) ) - nurbsVertex;
			else
				vector2 = ComputeVertex( CVec3( vertex.x, vertex.y - delta, vertex.z ) ) - nurbsVertex;

			CVec3 nurbsNormal;
			if( (vertex.x + delta < Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES && vertex.y + delta >= Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES ) ||
				(vertex.x + delta >= Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES && vertex.y + delta < Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES ) )
				nurbsNormal= vector2 ^ vector1;
			else
				nurbsNormal= vector1 ^ vector2;
			Normalize( &nurbsNormal );

			//NI_VERIFY( nurbsNormal.z > 0.f, "invalid computed vertex", continue; );
			
			// trasform NURBS initial and current normals to local TE space // smirnov [2009/7/23]: it is world space now
			CVec3 initialNormal = CVec3( 0.f, 0.f, 1.0f );

      out[i].normal = Rotate( in[i].normal, basis );

			// make shortest arc
			CQuat quat = ShortestArc( initialNormal, nurbsNormal );

			Normalize( &initialNormal );
			Normalize( &out[i].normal );
			const float dot = initialNormal * out[i].normal;

			float angle;
			CVec3 axis;
			quat.DecompAngleAxis( &angle, &axis );
			//angle *= acos( dot ) / FP_PI2;
			angle *= dot;
			quat.FromAngleAxis( angle, axis );
			
			// get modified normals
			quat.Rotate( &out[i].normal, out[i].normal );
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TerrainGeometryManager::CopyMasks( TerrainElementId id, TerrainElementStrideNew* out, unsigned int bufferSize )
	{
    ASSERT(pOwner->IsEditable());
		const unsigned int vertexCount = bufferSize / sizeof( TerrainElementStrideNew );

		// access fragment
		TerrainElement* pFragment = pOwner->GetElementManager().GetElement(id);
		ASSERT(pFragment);
		CVec2 worldscale(1.0f / pOwner->GetGridConstants().worldSize.x, 1.0f / pOwner->GetGridConstants().worldSize.y);

		// go through all layers of the fragment
		unsigned int materialCount = pFragment->layerIndices.size();
		//ASSERT(materialCount <= 4);
		static int warnCounter = 5;
		if (materialCount > 4 && warnCounter)
		{
			warnCounter--;
			systemLog( NLogg::LEVEL_ASSERT ) << "Terrain fragment " << id << " references too many materials (" << materialCount << ")" << endl;
			if (!warnCounter)
			{
				systemLog( NLogg::LEVEL_ASSERT ) << "Terrain fragment warnings suppressed..." << endl;
			}
		}

		// smirnov [2008/12/12]: todo: replace vector with this array in TerrainElement to avoid copying
		unsigned char layerIDs[4] = {0};
		materialCount = Min(4U, materialCount);
		for(unsigned int materialIdx = 0; materialIdx < materialCount; ++materialIdx)
			layerIDs[materialIdx] = pFragment->layerIndices[materialIdx];

		TerrainLayerMask const& mask = pOwner->GetLayerManager().GetLayerMask();
		LayerSamplerProxy proxy(layerIDs);

		// go through all vertices
		TerrainElementStrideNew* pVertex = out;
		for( unsigned int vertexIdx = 0; vertexIdx < vertexCount; ++vertexIdx, ++pVertex )
		{
			CVec3 inPosition = pVertex->position;
			CVec2 uv(inPosition.x * worldscale.x, inPosition.y * worldscale.y);

			CVec4 maskValue = ArraySampler::Bilinear(mask, uv.u, uv.v, proxy);
			pVertex->mask = Render::Color(maskValue.r * 255.0f, maskValue.g * 255.0f, maskValue.b * 255.0f, maskValue.a * 255.0f);
		}
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void TerrainGeometryManager::CalculateLighting( TerrainElementId id, TerrainElementStrideNew* out, unsigned int bufferSize )
  {
    CalculateLightingEx(id, out, bufferSize, NDb::LIGHTENVIRONMENT_DAY);
  }

  void TerrainGeometryManager::CalculateLightingEx(TerrainElementId id, TerrainElementStrideNew* out, unsigned int bufferSize, const NDb::ELightEnvironment selector)
  {
    const Render::SceneConstants& sceneConstants = lightingScene->GetSceneConstants(selector);

    Render::HDRColor const &ambientColor = sceneConstants.ambientColor;

    const unsigned int vertexCount = bufferSize / sizeof( TerrainElementStrideNew );

    TerrainElement* pFragment = pOwner->GetElementManager().GetElement(id);
    ASSERT(pFragment);


    Render::HDRColor matDiffuseColor = Render::HDRColor(1.f, 1.f, 1.f, 1.f);
    float matLightIntensity = 1.f;

    const NDb::Material *pDBMat = pFragment->pLocalMaterial->GetDBMaterial();
    if (pDBMat->GetObjectTypeID() == NDb::BasicMaterial::typeId)
    {
      const NDb::BasicMaterial *pDBBaseMat = static_cast<const NDb::BasicMaterial*>(pDBMat);
      matDiffuseColor = pDBBaseMat->diffuseColor;
      matLightIntensity = pDBBaseMat->lightingIntencity;
    }


    // collect lights affecting this element
    Render::PointLightsCollector clf(selector);

    Render::GetLightsManager()->ForLightsAffectingBBox( pFragment->worldAABB, clf );

    TerrainElementStrideNew* pV = out;

    Render::Color TerrainElementStrideNew::*const colorTarget = (selector == NDb::LIGHTENVIRONMENT_DAY) ? &TerrainElementStrideNew::color0 : &TerrainElementStrideNew::color1;

    for (unsigned int i = 0; i < vertexCount; ++i, ++pV)
    {
      CVec3 pos = pV->position;
      CVec3 n = pV->normal;

      // calculate environment lighting
      Render::HDRColor sceneEnvLight;
      EvaluateLightingBySHShaderConstants(sceneConstants.envLighting, n, sceneEnvLight);

      // calculate lighting by point lights
      Render::HDRColor c = Render::HDRColor(0.f, 0.f, 0.f, 1.f);
      for (int j = 0; j < clf.lights.size(); ++j)
      {
        Render::PointLight const &pl = *clf.lights[j];

        CVec3 d = pl.GetLocation() - pos;
        float t = 1.f;

        float l = d.Length();
        if (l > 0.f)
        {
          t = n.Dot(d) * pl.GetAttenuation(l) / l;
          t = Clamp(t, 0.f, 1.f);
        }

        t *= pl.m_diffuseIntensity;

        c.Mad(pl.m_diffuseColor, Render::HDRColor(t,t,t,1.f), c);
      }

      c = ( ambientColor + (sceneEnvLight + c) * matLightIntensity ) * matDiffuseColor;

      Render::HDRColor const &minBakedColor = sceneConstants.minBakedColor;
      Render::HDRColor const &maxBakedColor = sceneConstants.maxBakedColor;
      c.R = Clamp(c.R, minBakedColor.R, Min(255.f, maxBakedColor.R));
      c.G = Clamp(c.G, minBakedColor.G, Min(255.f, maxBakedColor.G));
      c.B = Clamp(c.B, minBakedColor.B, Min(255.f, maxBakedColor.B));

      // adaptive scaling to allow HDR
      float max = Max(c.R, c.G);
      max = ceil(Max(max, c.B));
      float scale = 255.f / max;

      pV->*colorTarget = Render::Color(c.R * scale, c.G * scale, c.B * scale, max);
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  Render::TerrainElementGeometryRaw const* TerrainGeometryManager::GetElement(TerrainElementId id) const
  {
    TerrainElementModifiedContainer::const_iterator it = modifiedGeometry.find( id );
    if (it == modifiedGeometry.end())
      return NULL;
    return &it->second;
  }

  Render::TerrainElementGeometryRaw* TerrainGeometryManager::GetElement(TerrainElementId id)
  {
    TerrainElementModifiedContainer::iterator it = modifiedGeometry.find( id );
    if (it == modifiedGeometry.end())
      return NULL;
    return &it->second;
  }

  static __forceinline CVec2 Wrap(const CVec2 &coords)
  {
    return CVec2( coords.x - floor(coords.x), coords.y - floor(coords.y) );
  }

  class Welder
  {
  public:
    explicit Welder(float patchSize_, float roughSize_, float seamSize_, int seamCount_)
      : patchSize(patchSize_), stripSize(roughSize_), seamSize(seamSize_), seamList(seamCount_)
    {
      SetAxisX();
    }

    void SetAxisX()
    {
      xyzFirst = &CVec3::x;
      xyzNext = &CVec3::y;
    }

    void SetAxisY()
    {
      xyzFirst = &CVec3::y;
      xyzNext = &CVec3::x;
    }

    void Add(Render::TerrainElementGeometryRaw const* pGeometry)
    {
      ASSERT(pGeometry && pGeometry->pMaterial);
      const CTRect<float> &srcRect = pGeometry->pMaterial->grassRect;
      const CTRect<float> grassRect(srcRect.left, 1.f - srcRect.bottom, srcRect.right, 1.f - srcRect.top);
      const bool noGrass = grassRect.IsEmpty();
      TerrainElementStrideNew* pVertex = (TerrainElementStrideNew*)pGeometry->vertexBuffer;
      unsigned int vertexCount = pGeometry->vertexBufferSize / sizeof(TerrainElementStrideNew);
      for (unsigned i = 0; i < vertexCount; i++, pVertex++)
        if( noGrass || !grassRect.IsInside(Wrap(pVertex->texcoord0)) )
          Add(pVertex);
    }

    void Add(TerrainElementStrideNew* pVertex)
    {
      // locate nearest seam
      float& val = pVertex->position.*xyzFirst;
      int seamId = Round(val / patchSize);
      float val0 = (float)seamId * patchSize;

      // if it's inside
      if (fabs(val - val0) < stripSize)
        StoreVertex(pVertex, seamId);
    }

    void Weld()
    {
      SeamList::iterator const itSeamEnd = seamList.end();
      for (SeamList::iterator itSeam = seamList.begin(); itSeam != itSeamEnd; itSeam++)
        Weld(*itSeam);
    }

    void Reset()
    {
      SeamList::iterator const itSeamEnd = seamList.end();
      for (SeamList::iterator itSeam = seamList.begin(); itSeam != itSeamEnd; itSeam++)
        itSeam->clear();
    }

  private:
    typedef vector<TerrainElementStrideNew*> VertexList;
    typedef vector<VertexList> SeamList;
    typedef vector<CVec3*> Positions;

    void StoreVertex(TerrainElementStrideNew* pVertex, int seamId)
    {
      NI_ASSERT(0 <= seamId && seamId < seamList.size(), "Vertex is outside the world?!");
      VertexList& vertexList = seamList[seamId];
      vertexList.reserve((vertexList.size() / 100 + 1) * 100);
      vertexList.push_back(pVertex);
    }

    void Weld(VertexList& vertexList)
    {
      if (vertexList.size() < 2)
        return;

      // sort vertices
      struct VertexLess : public binary_function<TerrainElementStrideNew*, TerrainElementStrideNew*, bool> {
        float CVec3::*xyz;
        bool operator()(TerrainElementStrideNew* left_, TerrainElementStrideNew* right_) {
          return left_->position.*xyz < right_->position.*xyz;
        }
      } vertexLess;
      vertexLess.xyz = xyzNext;
      sort(vertexList.begin(), vertexList.end(), vertexLess);

      // align boundary vertices
      VertexList::iterator const itEnd = vertexList.end();
      for(VertexList::iterator itA = vertexList.begin(); itA != itEnd; ++itA)
      {
        float& majorCoord = (*itA)->position.*xyzFirst;
        float roundedVal = int(Round(majorCoord/patchSize)) * patchSize;
        if(fabs(roundedVal - majorCoord) < seamSize)
          majorCoord = roundedVal;
      }

      // merge neighbours
      const float seamSize2 = seamSize * seamSize;
      for(VertexList::iterator itA = vertexList.begin(); itA != itEnd; ++itA)
      {
        CVec3 aFirst = (*itA)->position;
        CVec3 *pLast = &((*itA)->position);
        CVec3 avgNorm = (*itA)->normal;

        // detect group of vertices
        VertexList::iterator itB = itA;
        while(++itB != itEnd) {
          CVec3& b = (*itB)->position;
          // stop if too far away
          if(b.*xyzNext - aFirst.*xyzNext >= seamSize)
            break;

          if(fabs2(aFirst - b) < seamSize2) {
            pLast = &b;
            temp.push_back(*itB);
            avgNorm += (*itB)->normal;
          }
        }

        // fill the group with averages
        if( !temp.empty() ) {
          // find averages
          CVec3 avgPos;
          avgPos.Lerp(0.5f, aFirst, *pLast);

          Normalize(&avgNorm);

          temp.push_back(*itA);
          for(VertexList::iterator it = temp.begin(); it != temp.end(); ++it)
          {
            TerrainElementStrideNew &el = **it;
            el.position = avgPos;
            el.normal = avgNorm;
          }

          temp.clear();
        }
      }
    }

  private:
    float CVec3::*xyzFirst;
    float CVec3::*xyzNext;
    float patchSize;
    float stripSize;
    float seamSize;
    SeamList seamList;
    VertexList temp;
  };

  // rather slow method to deal with shifted TCVs
  void TerrainGeometryManager::WeldVertices(bool syncVisual) const
  {
    GridConstants const& cc = pOwner->GetGridConstants();
    TerrainElementManager& em = pOwner->GetElementManager();
    float stripSize = weldLookupSize + weldThreshold;
    unsigned n = em.GetMaxRow();
    unsigned m = em.GetMaxColumn();

    // weld "vertical" seams
    {
      Welder welder(cc.metersPerElement, stripSize, weldThreshold, cc.sizeInElements.x + 1);
      welder.SetAxisX();
      welder.Reset();
      for (unsigned i = 0; i < n; i++)
      {
        for (unsigned j = 0; j < m; j++)
        {
          Render::TerrainElementGeometryRaw const* pRaw = GetElement(em.LocateElement(i,j));
          if (pRaw)
            welder.Add(pRaw);
        }
      }
      welder.Weld();
    }

    // weld "horizontal" seams
    {
      Welder welder(cc.metersPerElement, stripSize, weldThreshold, cc.sizeInElements.y + 1);
      welder.SetAxisY();
      welder.Reset();
      for (unsigned j = 0; j < m; j++)
      {
        for (unsigned i = 0; i < n; i++)
        {
          Render::TerrainElementGeometryRaw const* pRaw = GetElement(em.LocateElement(i,j));
          if (pRaw)
            welder.Add(pRaw);
        }
      }
      welder.Weld();
    }

    // copy vertices to vertex buffers
    if (syncVisual)
    {
      TerrainElementModifiedContainer::const_iterator const itEnd = modifiedGeometry.end();
      for (TerrainElementModifiedContainer::const_iterator it = modifiedGeometry.begin(); it != itEnd; it++)
      {
        TerrainElementId id = it->first;
        const Render::TerrainElementGeometryRaw& elementRawData = it->second;
        TerrainElementStrideNew* pSrc = (TerrainElementStrideNew*)elementRawData.vertexBuffer;
        TerrainElement* pElement = pOwner->GetElementManager().GetElement(id);
        TerrainElementStrideNew* pDst = Render::LockVB<TerrainElementStrideNew>(Get(pElement->mesh.GetVertexBuffer()), 0);
        memcpy(pDst, pSrc, elementRawData.vertexBufferSize);
        pElement->mesh.GetVertexBuffer()->Unlock();
      }
    }

    MessageTrace( "TerrainGeometryManager::WeldVertices done" );
  }

  unsigned TerrainGeometryManager::GetBakedTerrainFileSignature() const
  {
    return BAKED_TERRAIN_FILE_SIGN;
  }

} // namespace Terrain

#endif

// MeshConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define TOOLSET_IS_PRESENT
#include "MeshHeader.h"
#include "SkeletonHeader.h"
#include <d3d9types.h>
#include "../Render/vertexelementdescriptor.h"
#include "../Render/DBRenderResources.h"

#include "MeshLoader.h"
#include "SkeletalAnimationHeader.h"

#include "ParticleNewHeader.h"

#include "UberHeader.h"
#include "../Scene/CollisionGeometry.h"
#include "../System/BinChunkSerializer.h"

// Uncomment this define to enable vertex duplication and merge for correct
// object expansion (for outline rendering). Index buffer is twice as big.
#define MERGE_EQUAL_VERTICES

#ifdef _WINDLL
extern "C"
{
	//geometry
	__declspec( dllexport ) __int32 __stdcall ConvertStaticMeshGeometry( const void* mayaFileData, int mayaFileDataSize, void* h6FileBuffer, int h6BufferSize, int* h6FileActualLength, unsigned int _ConvertTagentAndBinormal, int _ConvertColors, unsigned char _UVChannels, NDb::AABB* pAABB );

	//collision geometry
	__declspec( dllexport ) __int32 __stdcall ConvertCollisionGeometry( const void* mayaFileData, int mayaFileDataSize, void* geometryFileBuffer, int geometryBufferSize, int* geometryFileActualLength );

	// work with skeletal mesh only, break material into fragments if it has more than 70 joints
	__declspec( dllexport ) __int32 __stdcall ConvertSkeletalMeshGeometrySafe( const char* mayaFileName, const char* h6fileName, const char* skeletonName, unsigned int _ConvertTagentAndBinormal, int _NumColorChannels, unsigned char _UVChannels, unsigned int jointsCountPerVertex, float* pAABB );
	__declspec( dllexport ) __int32 __stdcall ConvertSkeletalMeshFromMemory( const void* const pReader, unsigned int readerLength, void* const pWriter, 
			unsigned int writerMaxLenght, unsigned int& payloadSize, unsigned char jointsPerVertex, const void* pSkel, 
			FileStream& writerStream, unsigned int _ConvertTagentAndBinormal, int _NumColorChannels );

	//skeleton
	__declspec( dllexport ) __int32 __stdcall ConvertSkeletonSafe( const char* pAncherFileName, const char* pGameFileName );
	__declspec( dllexport ) __int32 __stdcall ConvertSkeletonFromMemory( const void* const pReader, unsigned int readerLength, void* const pWriter, unsigned int writerMaxLenght, unsigned int& payloadSize, FileStream& filestream  );

	//skeletal animation
	__declspec( dllexport ) __int32 __stdcall ConvertSkeletalAnimationSafe( const char* pAncherFileName, const char* pGameFileName );
	__declspec( dllexport ) __int32 __stdcall ConvertSkeletalAnimationFromMemory( const void* const pReader, unsigned int readerLength, void* const pWriter, unsigned int writerMaxLenght, unsigned int& payloadSize );

	//particle fx
	__declspec( dllexport ) __int32 __stdcall ConvertParticleSafe( const char* pAncherFileName, const char* pGameFileName );
	__declspec( dllexport ) __int32 __stdcall ConvertParticleFromMemory( const void* const pReader, unsigned int readerLength, void* const pWriter, unsigned int writerMaxLenght, int& payloadSize, unsigned int& maxSpriteID );
}
#endif

static const float FPS = 30.0f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
static bool TestForConstTrack( const T* pos, unsigned int size )
{
	if ( size == 0 )
		return false;

	T origPos = pos[0];
	for ( unsigned int i = 0; i < size; i++ )
	{
		if ( fabs(origPos.Data-pos[i].Data) > 0.001f )
			return false;
	}

	return true;
}

void InitAABB(NDb::AABB &aabb)
{
	aabb.minX = FLT_MAX;
	aabb.minY = FLT_MAX;
	aabb.minZ = FLT_MAX;
	aabb.maxX = -FLT_MAX;
	aabb.maxY = -FLT_MAX;
	aabb.maxZ = -FLT_MAX;
}

void AddVertex2AABB(NDb::AABB &aabb, CVec3 const &vtx)
{
	if (aabb.minX > vtx.x)
		aabb.minX = vtx.x;
	if (aabb.maxX < vtx.x)
		aabb.maxX = vtx.x;
	if (aabb.minY > vtx.y)
		aabb.minY = vtx.y;
	if (aabb.maxY < vtx.y)
		aabb.maxY = vtx.y;
	if (aabb.minZ > vtx.z)
		aabb.minZ = vtx.z;
	if (aabb.maxZ < vtx.z)
		aabb.maxZ = vtx.z;
}

void AddAABB2AABB(NDb::AABB &aabb, NDb::AABB const &aabbIn)
{
	aabb.minX = __min(aabb.minX, aabbIn.minX);
	aabb.minY = __min(aabb.minY, aabbIn.minY);
	aabb.minZ = __min(aabb.minZ, aabbIn.minZ);
	aabb.maxX = __max(aabb.maxX, aabbIn.maxX);
	aabb.maxY = __max(aabb.maxY, aabbIn.maxY);
	aabb.maxZ = __max(aabb.maxZ, aabbIn.maxZ);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall ConvertSkeletalAnimationFromMemory( const void* const pReader, unsigned int readerLength, void* const pWriter, unsigned int writerMaxLenght, unsigned int& payloadSize )
{
	NI_VERIFY( pReader, "pointer to reader stream is not valid", return -1; );
	NI_VERIFY( pWriter, "pointer to writer stream is not valid", return -1; );

	const MayaSkeletalAnimationHeader* pMayaSkeletalAnimationHeader = reinterpret_cast<const MayaSkeletalAnimationHeader*>(pReader); 
	NI_VERIFY( pMayaSkeletalAnimationHeader->boneCount < 256, NStr::StrFmt( "too many bones: %d", pMayaSkeletalAnimationHeader->boneCount ), return -1; );

	DummyAllocator allocator(writerMaxLenght);
	SkeletalAnimationData* pSkeletalAnimationData = reinterpret_cast<SkeletalAnimationData*>( allocator.Allocate(sizeof(SkeletalAnimationData), 16));
	*(int*)(&pSkeletalAnimationData->signature[0]) = *(int*)(&pMayaSkeletalAnimationHeader->signature[0]);
	pSkeletalAnimationData->tracks.resize(pMayaSkeletalAnimationHeader->boneCount, &allocator);
	const unsigned int* pCurrentTrackSize = reinterpret_cast<const unsigned int*>(pMayaSkeletalAnimationHeader+1);

	for (unsigned int boneNumber = 0; boneNumber < pMayaSkeletalAnimationHeader->boneCount; ++boneNumber)
	{
		const TMayaPosition* pMayaPosition = reinterpret_cast<const TMayaPosition*>(pCurrentTrackSize+1);
		for ( unsigned int i = 0; i < *pCurrentTrackSize; ++i )
		{
			if( pSkeletalAnimationData->minTime > ((float)pMayaPosition[i].frameNumber / FPS) )
				pSkeletalAnimationData->minTime = (float)pMayaPosition[i].frameNumber / FPS;
			if( pSkeletalAnimationData->maxTime < ((float)pMayaPosition[i].frameNumber / FPS) )
				pSkeletalAnimationData->maxTime = (float)pMayaPosition[i].frameNumber / FPS;
		}

		if ( TestForConstTrack(pMayaPosition, *pCurrentTrackSize) )
		{
			pSkeletalAnimationData->tracks[boneNumber].positionTrack.resize(1, &allocator);
			pSkeletalAnimationData->tracks[boneNumber].positionTrack.trackData[0] = pMayaPosition[0].Data;
		}
		else
		{
			pSkeletalAnimationData->tracks[boneNumber].positionTrack.resize(*pCurrentTrackSize, &allocator);
			for ( unsigned int i = 0; i < *pCurrentTrackSize; ++i )
			{
				pSkeletalAnimationData->tracks[boneNumber].positionTrack.trackData[i] = pMayaPosition[i].Data;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		pCurrentTrackSize = reinterpret_cast<const unsigned int*>( pMayaPosition + *pCurrentTrackSize );
		const TMayaRotation* pMayaRotation = reinterpret_cast<const TMayaRotation*>(pCurrentTrackSize+1);

		if ( TestForConstTrack(pMayaRotation, *pCurrentTrackSize) )
		{
			pSkeletalAnimationData->tracks[boneNumber].rotationTrack.resize(1, &allocator);
			pSkeletalAnimationData->tracks[boneNumber].rotationTrack.trackData[0] = pMayaRotation[0].Data;
		}
		else
		{
			pSkeletalAnimationData->tracks[boneNumber].rotationTrack.resize(*pCurrentTrackSize, &allocator);
			for ( unsigned int i = 0; i < *pCurrentTrackSize; ++i )
			{
				NI_VERIFY(pMayaRotation[i].Data.w <= 1.f , NStr::StrFmt( "w component of rotatetion should be less or equal 1.f: bone# %d, rotation track# %d", boneNumber, i), return -1; );
				pSkeletalAnimationData->tracks[boneNumber].rotationTrack.trackData[i] = pMayaRotation[i].Data;
				if( i == (*pCurrentTrackSize-1))
				{
					NI_VERIFY( (float)((float)pMayaRotation[i].frameNumber / FPS) == pSkeletalAnimationData->maxTime, "wrong end time", return -1; );
				}
			}
		}

		pCurrentTrackSize = reinterpret_cast<const unsigned int*>( pMayaRotation + *pCurrentTrackSize );
		const TMayaScale* pMayaScale = reinterpret_cast<const TMayaScale*>(pCurrentTrackSize+1);

		if ( TestForConstTrack(pMayaScale, *pCurrentTrackSize) )
		{
			pSkeletalAnimationData->tracks[boneNumber].scaleTrack.resize(1, &allocator);
			pSkeletalAnimationData->tracks[boneNumber].scaleTrack.trackData[0] = pMayaScale[0].Data;
		}
		else
		{
			pSkeletalAnimationData->tracks[boneNumber].scaleTrack.resize(*pCurrentTrackSize, &allocator);
			for ( unsigned int i = 0; i < *pCurrentTrackSize; ++i )
			{
				pSkeletalAnimationData->tracks[boneNumber].scaleTrack.trackData[i] = pMayaScale[i].Data;
				if( i == (*pCurrentTrackSize-1))
				{
					NI_VERIFY( ((float)((float)(pMayaScale[i].frameNumber) / FPS)) == pSkeletalAnimationData->maxTime, "wrong end time", return -1; );
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		pCurrentTrackSize = reinterpret_cast<const unsigned int*>( pMayaScale + *pCurrentTrackSize );
	}
	allocator.Normalize(512);
	payloadSize = allocator.GetSize();
	memcpy(pWriter, allocator.GetData(), allocator.GetSize());
	return pMayaSkeletalAnimationHeader->boneCount;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall ConvertSkeletalAnimationSafe( const char* pAncherFileName, const char* pGameFileName )
{
	NI_VERIFY( pAncherFileName != pGameFileName, "names should be different", return -1 );

	NI_VERIFY( pAncherFileName, "pointer to c-style string with AncherFileName is not valid", return -1; );
	NI_VERIFY( strnlen(pAncherFileName, MAX_FILE_NAME_LENGTH+1) < MAX_FILE_NAME_LENGTH, ("file name too long (probably you pointed to the junk): " + nstl::string(pAncherFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1; );

	NI_VERIFY( pGameFileName, "pointer to c-style string with GameFileName is not valid", return -1; );
	NI_VERIFY( strnlen(pGameFileName, MAX_FILE_NAME_LENGTH+1) < MAX_FILE_NAME_LENGTH, ("file name too long (probably you pointed to the junk): " + nstl::string(pGameFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1; );

	FileStream ancherFileStream( pAncherFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	NI_VERIFY( ancherFileStream.IsOk(), ("Cannot open file with Ancher's skeletal animation data" + nstl::string(pAncherFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1 );

	FileStream gameFileStream( pGameFileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
	NI_VERIFY( gameFileStream.IsOk(), ("Cannot open file with game's skeletal animation data" + nstl::string(pGameFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1 );

	unsigned int maxWriterSize = 1024*1024+ancherFileStream.GetSize();
	void* const pNewData = Aligned_MAlloc(maxWriterSize, 512);
	unsigned int payloadSize = 0;

	int jointsCount = ConvertSkeletalAnimationFromMemory( ancherFileStream.GetBuffer(), ancherFileStream.GetSize(), pNewData, maxWriterSize, payloadSize );

	gameFileStream.Write( pNewData, payloadSize );
  Aligned_Free(pNewData);
	return jointsCount;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// convert geometry from intermediate (ancher's) format to game's one
// return value is the "submesh" count on success or less than zero over wise
int __stdcall ConvertSkeletalMeshGeometrySafe( const char* pAncherFileName
																							, const char* pGameFileName
																							, const char* h6skeletonFileName
																							, unsigned int _ConvertTagentAndBinormal
																							, int _NumColorChannels
																							, unsigned char _UVChannels
																							, unsigned int jointsCountPerVertex
																							, float* pAABB)
{

	NI_VERIFY( pAncherFileName != pGameFileName, "names should be different", return -1 );

	NI_VERIFY( pAncherFileName, "pointer to c-style string with AncherFileName is not valid", return -1; );
	NI_VERIFY( strnlen(pAncherFileName, MAX_FILE_NAME_LENGTH+1) < MAX_FILE_NAME_LENGTH, ("file name too long (probably you pointed to the junk): " + nstl::string(pAncherFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1; );

	NI_VERIFY( pGameFileName, "pointer to c-style string with GameFileName is not valid", return -1; );
	NI_VERIFY( strnlen(pGameFileName, MAX_FILE_NAME_LENGTH+1) < MAX_FILE_NAME_LENGTH, ("file name too long (probably you pointed to the junk): " + nstl::string(pGameFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1; );

	NI_VERIFY( h6skeletonFileName, "pointer to c-style string with h6skeletonFileName is not valid", return -1; );
	NI_VERIFY( strnlen(h6skeletonFileName, MAX_FILE_NAME_LENGTH+1) < MAX_FILE_NAME_LENGTH, ("file name too long (probably you pointed to the junk): " + nstl::string(h6skeletonFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1; );

	FileStream ancherFileStream( pAncherFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	NI_VERIFY( ancherFileStream.IsOk(), ("Cannot open file with Ancher's data" + nstl::string(pAncherFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1 );

	FileStream gameFileStream( pGameFileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
	NI_VERIFY( gameFileStream.IsOk(), ("Cannot open file with game's pGameFileName  data" + nstl::string(pGameFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1 );

	FileStream skeletonFileStream( h6skeletonFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	NI_VERIFY( skeletonFileStream.IsOk(), ("Cannot open file with game's h6skeletonFileName data" + nstl::string(h6skeletonFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1  );

	unsigned int maxWriterSize = 1024*1024+ancherFileStream.GetSize();
	void* const pNewData = Aligned_MAlloc(maxWriterSize, 512);
	unsigned int payloadSize = 0;

	int materialCount = ConvertSkeletalMeshFromMemory( ancherFileStream.GetBuffer(), ancherFileStream.GetSize(), pNewData, maxWriterSize, 
																										 payloadSize, (unsigned char)jointsCountPerVertex, (const void*)skeletonFileStream.GetBuffer(), 
																										 gameFileStream, _ConvertTagentAndBinormal, _NumColorChannels);

	int currentSize = gameFileStream.GetPosition();
	const int fileSizeAlignment = 1024;
	int wantedSize = currentSize + (fileSizeAlignment - (currentSize & ( fileSizeAlignment - 1 )) );
	systemLog( NLogg::LEVEL_MESSAGE ) << "File size " << wantedSize/1024 << " KB" << endl;
	systemLog( NLogg::LEVEL_MESSAGE ) << "Export completed" << endl;
	gameFileStream.SetSize( wantedSize );
	//gameFileStream.Write( pNewData, payloadSize );
  Aligned_Free(pNewData);
	return materialCount;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef MERGE_EQUAL_VERTICES
template <class VERTEX> void MergeEqualVertices(nstl::vector< nstl::vector<VERTEX> >& fragmentsVB, nstl::vector< nstl::vector<unsigned int> >& fragmentsIB)
{
  NI_ASSERT(fragmentsVB.size() == fragmentsIB.size(), NStr::StrFmt("Different number of vertex and index buffers (%i vs %i)", fragmentsVB.size() != fragmentsIB.size()));
  unsigned int fragmentCount = fragmentsVB.size();
  
  unsigned int totalVerticesBefore = 0, totalVerticesAfter = 0;
  unsigned int totalIndicesBefore = 0, totalIndicesAfter = 0;

  static float mergeTolerance = 1.0e-6f; // 10^(-6) = one millimeter squared
  for (unsigned int fragmentNumber = 0; fragmentNumber < fragmentCount; ++fragmentNumber)
  {
    nstl::vector<VERTEX>& fragVertices = fragmentsVB[fragmentNumber];
    nstl::vector<unsigned int>& fragIndices = fragmentsIB[fragmentNumber];
    nstl::vector<unsigned int> fragParents(fragVertices.size(), 0xFFFFFFFFU);
    nstl::vector<unsigned int> fragDuplicates(fragVertices.size(), 0U);
    nstl::vector<VERTEX> fragAddonVertices;
    nstl::vector<unsigned int> fragAddonReindex(fragVertices.size(), 0xFFFFFFFFU);

    // loop through all positions
    for (unsigned int idxThis = 0; idxThis < (unsigned)fragVertices.size(); ++idxThis )
    {
      CVec3 const& posThis = fragVertices[idxThis].position;

      // find similar position in the same list
      unsigned int idxParent = idxThis; // unique by default
      for (unsigned int idxOther = 0; idxOther < idxThis; ++idxOther )
      {
        CVec3 const& posOther = fragVertices[idxOther].position;
        if (fabs2(posOther - posThis) < mergeTolerance)
        {
          idxParent = idxOther;
          break;
        }
      }

      // store index of the similar vertex
      fragParents[idxThis] = idxParent;

      // accumulate components for averaging
      if (idxParent != idxThis)
      {
        // shorten path, find the first ancestor (if several positions are near to each other)
        while (fragParents[idxParent] != idxParent)
        {
          NI_ASSERT(fragParents[idxParent] < idxParent, NStr::StrFmt("Parent index [%u] is supposed to be less than original [%u] unless it's equal to it", fragParents[idxParent], idxParent));
          idxParent = fragParents[idxParent];
        }

        // !!! at this point idxParent contains the "grandparent" index of idxThis [11/23/2010 paul.smirnov]

        // on the first duplicate...
        if (fragDuplicates[idxParent] == 0)
        {
          // ...add the original
          NI_ASSERT(fragAddonReindex[idxParent] == 0xFFFFFFFFU, NStr::StrFmt("Reindex value is already filled with %u, expected 0xFFFFFFFFU", fragAddonReindex[idxParent]));
          fragAddonReindex[idxParent] = fragAddonVertices.size();
          fragAddonVertices.push_back(fragVertices[idxParent]);
        }
        fragDuplicates[idxParent]++;

        // add components
        NI_ASSERT(fragAddonReindex[idxParent] != 0xFFFFFFFFU, "Reindex value is not yet filled");
        NI_ASSERT(fragAddonReindex[idxThis] == 0xFFFFFFFFU, NStr::StrFmt("Reindex value is already filled with %u, expected 0xFFFFFFFFU", fragAddonReindex[idxThis]));
        unsigned int reidx = fragAddonReindex[idxThis] = fragAddonReindex[idxParent];
        VERTEX& accum = fragAddonVertices[reidx];
        accum.normal += fragVertices[idxThis].normal;
        // do not accumulate position, tangent, binormal, color, etc... since we don't need this for outline/silhouette [11/23/2010 paul.smirnov]
      }
    }

    // at this point either 
    // - fragParents[i] == i (for uniques or for the first "grandparent" entry of duplicated vertex family), or
    // - fragParents[i]  < i (for a duplicate to be replaced)
    // and
    // - fragDuplicates[i] == 0 (for uniques or all duplicates except for original "grandparent" vertex), or
    // - fragDuplicates[i]  > 0 (for the first "grandparent" entry of duplicated vertex family)

    // append the merged vertex buffer
    unsigned int vertexCount = fragVertices.size();
    fragVertices.reserve(vertexCount + fragAddonVertices.size());
    for (unsigned int i = 0, n = fragAddonVertices.size(); i < n; ++i)
    {
      VERTEX& accum = fragAddonVertices[i];
      Normalize(&accum.normal);
      fragVertices.push_back(accum);
    }

    // append a copy of index buffer
    unsigned int indexCount = fragIndices.size();
    fragIndices.resize(indexCount * 2);

    // fill corrected indices
    for (unsigned int i = 0; i < indexCount; ++i)
    {
      unsigned int idx = fragIndices[i];
      unsigned int similarIndex = fragParents[idx];
      if (idx == similarIndex && fragDuplicates[idx] == 0)
        fragIndices[i + indexCount] = idx; // just copy
      else
        fragIndices[i + indexCount] = vertexCount + fragAddonReindex[similarIndex]; // point to averaged copy
    }

    totalVerticesBefore += vertexCount;
    totalVerticesAfter += fragVertices.size();
    totalIndicesBefore += indexCount;
    totalIndicesAfter += fragIndices.size();
  }

  systemLog( NLogg::LEVEL_MESSAGE ) << NStr::StrFmt("Merge statistics: %u->%u vertices (%.0f%%), %u->%u indices, %u fragments", 
    totalVerticesBefore, totalVerticesAfter, totalVerticesBefore > 0 ? (100.0f * (float)totalVerticesAfter / (float)totalVerticesBefore) : 0.0f,
    totalIndicesBefore, totalIndicesAfter, fragmentCount) << endl;
}
#endif // MERGE_EQUAL_VERTICES
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall ConvertSkeletalMeshFromMemory( const void* const pReader, unsigned int readerLength, void* const pWriter, unsigned int writerMaxLenght, 
																						unsigned int& payloadSize, unsigned char jointsPerVertex, const void* pSkel, FileStream& writerStream, 
																						unsigned int convertTagentAndBinormal, int numColorChannels)
{
	const SkeletonData* pSkeletonData = reinterpret_cast<const SkeletonData*>( pSkel );
	const unsigned char* pMayaBuffer = reinterpret_cast<const unsigned char*>( pReader );
	const MayaStaticMeshFileHeader* pMayaHeader = reinterpret_cast<const MayaStaticMeshFileHeader*>(pMayaBuffer);
	//const MayaVertexStrideStatic* pStaticVertex = reinterpret_cast<const MayaVertexStrideStatic*>(pMayaBuffer + sizeof(MayaStaticMeshFileHeader) );
	const MayaVertexStrideSkeletal* pSkeletalVertexStride = reinterpret_cast<const MayaVertexStrideSkeletal*>(pMayaBuffer + sizeof(MayaStaticMeshFileHeader) );
	//const MayaIndexHeader* pMayaStaticIndexHeader = reinterpret_cast<const MayaIndexHeader*>(pStaticVertex + pMayaHeader->vertexCount);
	const MayaIndexHeader* pMayaSkeletalIndexHeader = reinterpret_cast<const MayaIndexHeader*>(pSkeletalVertexStride + pMayaHeader->vertexCount);
	const unsigned int maxMaterials = 8;
	const MayaIndexBufferHeader* pIndexBufferHeaders[maxMaterials];
	const unsigned __int32* ptr = reinterpret_cast<const unsigned __int32*>(pMayaSkeletalIndexHeader+1);
	const unsigned int subMeshCount = pMayaSkeletalIndexHeader->subMeshCount;
	NI_VERIFY( subMeshCount < maxMaterials, "too many fragments", return -1; );
	unsigned int indexCount = 0;
	unsigned int firstIndex[maxMaterials];
	for (unsigned int i = 0; i < subMeshCount; ++i)
	{
		pIndexBufferHeaders[i] = reinterpret_cast<const MayaIndexBufferHeader*>(ptr + indexCount + 2*i);
		firstIndex[i] = indexCount;
		indexCount += pIndexBufferHeaders[i]->triangleCount*VERTEX_PER_TRIANGLE;
	}
	//systemLog( NLogg::LEVEL_MESSAGE ) << "joints per vertex = " << jointsPerVertex << endl;

	nstl::vector< nstl::vector<MayaTriangle> > mayaTriangles(subMeshCount);

	//nstl::vector< nstl::vector<MayaTriangleWeight> > mayaTriangleJointWeight(subMeshCount);


	nstl::vector< nstl::hash_map<unsigned short, unsigned short> > materialJointsIndices(subMeshCount);

	nstl::vector< nstl::vector<TriangleJoints> > triangleJoints(subMeshCount);
	//const int gggg = sizeof(TriangleJoints);

	ASSERT(jointsPerVertex > 0 && jointsPerVertex < 5 );

	const int maxJointsPerMaterial = 70;

	nstl::vector<unsigned short> jointTree(256);
	jointTree.resize(0);


	jointTree.push_back((unsigned short)0);

	PushChilds(jointTree, 0, pSkeletonData->parentsIDs);



	nstl::hash_map<unsigned short, unsigned short> jointOrder;
	for(int i = 0; i < jointTree.size(); ++i)
		jointOrder.insert( nstl::pair<unsigned short, unsigned short>( jointTree[i], i ) );

  systemLog( NLogg::LEVEL_MESSAGE ) << "Total joints count: " << pSkeletonData->jointsCount << endl;

	//bool overfull[maxMaterials];
	for (unsigned int materialNumber = 0; materialNumber < subMeshCount; ++materialNumber)
	{
		//overfull[materialNumber] = false;
		unsigned int indexCount = pIndexBufferHeaders[materialNumber]->triangleCount*VERTEX_PER_TRIANGLE;
		mayaTriangles[materialNumber].resize(pIndexBufferHeaders[materialNumber]->triangleCount);
		triangleJoints[materialNumber].resize(pIndexBufferHeaders[materialNumber]->triangleCount);
		//mayaTriangleJointWeight[materialNumber].resize(pIndexBufferHeaders[materialNumber]->triangleCount);
		for (unsigned int indexNumber = 0; indexNumber < indexCount; indexNumber+=3)
		{
			const unsigned int* pVertexIndex = (((unsigned int*)(pIndexBufferHeaders[materialNumber]+1))+indexNumber);
			mayaTriangles[materialNumber][indexNumber/3].a = *pVertexIndex;
			mayaTriangles[materialNumber][indexNumber/3].b = *(pVertexIndex+1);
			mayaTriangles[materialNumber][indexNumber/3].c = *(pVertexIndex+2);


			//////////////////////////////////////////////////////////////////////////
			for(int i = 0; i < jointsPerVertex; ++i)
			{
				if(pSkeletalVertexStride[*pVertexIndex].weights[i] > 0.f)
				{
					materialJointsIndices[materialNumber][ pSkeletalVertexStride[*pVertexIndex].indices[i] ]  = 0;
					triangleJoints[materialNumber][indexNumber/3].jointsID[triangleJoints[materialNumber][indexNumber/3].jointCount++] = pSkeletalVertexStride[*pVertexIndex].indices[i]; 
				}
				if(pSkeletalVertexStride[*(pVertexIndex+1)].weights[i] > 0.f)
				{
					materialJointsIndices[materialNumber][  pSkeletalVertexStride[*(pVertexIndex+1)].indices[i] ] = 0;
					triangleJoints[materialNumber][indexNumber/3].jointsID[triangleJoints[materialNumber][indexNumber/3].jointCount++] = pSkeletalVertexStride[*(pVertexIndex+1)].indices[i]; 
				}
				if(pSkeletalVertexStride[*(pVertexIndex+2)].weights[i] > 0.f)
				{
					materialJointsIndices[materialNumber][ pSkeletalVertexStride[*(pVertexIndex+2)].indices[i] ] = 0;
					triangleJoints[materialNumber][indexNumber/3].jointsID[triangleJoints[materialNumber][indexNumber/3].jointCount++] = pSkeletalVertexStride[*(pVertexIndex+2)].indices[i]; 
				}
			}
			//MakeWeight(mayaTriangles[materialNumber][indexNumber/3], mayaTriangleJointWeight[materialNumber][indexNumber/3], jointsPerVertex);
			//mayaTriangleJointWeight[materialNumber][indexNumber/3].triangleID = indexNumber/3;
		}
	}

	nstl::vector< nstl::vector< nstl::hash_map<unsigned short, unsigned short> > > jointTriangles(subMeshCount);


	for (unsigned int materialNumber = 0; materialNumber < subMeshCount; ++materialNumber )
	{
		jointTriangles[materialNumber].resize(256);
		for( int triangleNumber = 0; triangleNumber < triangleJoints[materialNumber].size(); ++triangleNumber)
		{
			//if(triangleJoints[materialNumber][triangleNumber].jointCount > 11)
			//	__debugbreak();
			for (unsigned char j = 0; j < triangleJoints[materialNumber][triangleNumber].jointCount; ++j )
			{
				ASSERT( triangleJoints[materialNumber][triangleNumber].jointsID[j] < 256 );
				jointTriangles[materialNumber][ triangleJoints[materialNumber][triangleNumber].jointsID[j] ] [triangleNumber] = 0;
			}
		}
	}

  int influenced = 0;
	for (unsigned int materialNumber = 0; materialNumber < subMeshCount; ++materialNumber)
	{
    influenced += materialJointsIndices[materialNumber].size();
  }
	systemLog( NLogg::LEVEL_MESSAGE ) << "Influenced joints count: " << influenced << endl;

	systemLog( NLogg::LEVEL_MESSAGE ) << "Materials count " << subMeshCount << endl;


	//for (unsigned int materialNumber = 0; materialNumber < subMeshCount; ++materialNumber)
	//	nstl::sort( mayaTriangleJointWeight[materialNumber].begin(), mayaTriangleJointWeight[materialNumber].end(), CompareMayaTriangleWeight );


	nstl::vector< nstl::vector< nstl::vector<unsigned short> > > fragmentJoints(subMeshCount);

	for (unsigned int materialNumber = 0; materialNumber < subMeshCount; ++materialNumber)
	{
		if(materialJointsIndices[materialNumber].size() > maxJointsPerMaterial)
		{
			int idealFragmentCount = materialJointsIndices[materialNumber].size() / maxJointsPerMaterial + 1;
			//systemLog( NLogg::LEVEL_MESSAGE ) << "material #" << materialNumber << " has more than " << maxJointsPerMaterial << " : " << materialJointsIndices[materialNumber].size()  << endl;
			nstl::vector<JointIndexPair> indexOrder(256);
			indexOrder.resize(0);

			for (nstl::hash_map<unsigned short, unsigned short>::const_iterator it = materialJointsIndices[materialNumber].begin(); it != materialJointsIndices[materialNumber].end(); ++it)
				indexOrder.push_back( JointIndexPair(it->first, jointOrder[it->first]) );

			nstl::sort(indexOrder.begin(), indexOrder.end(), CompareOrdered );

			nstl::hash_map<unsigned short, unsigned short> trunk;

			int currentJointIndex = 0;
			int oldJointIndex = 0;
			int fragmentCounter = -1;

			
			while( currentJointIndex < indexOrder.size() )
			{

				nstl::hash_map<unsigned short, unsigned short> branch;
				branch.clear();
				unsigned short currentJointValue = indexOrder[currentJointIndex].original;

				ASSERT( materialJointsIndices[materialNumber].find( currentJointValue )  != materialJointsIndices[materialNumber].end() );

				branch[ currentJointValue ] = 0;

				//const nstl::hash_map<unsigned short, unsigned short>& triangles = jointTriangles[materialNumber][indexOrder[currentJointIndex].original];
				//for(nstl::hash_map<unsigned short, unsigned short>::const_iterator triangleID = triangles.begin(); triangleID != triangles.end(); ++triangleID)
				for( int triangleNumber = 0; triangleNumber < mayaTriangles[materialNumber].size(); ++triangleNumber )
				{
					//const TriangleJoints& tj = triangleJoints[materialNumber][triangleID->first];
					//for (int j = 0; j < tj.jointCount; ++j)
					//{
					//	branch[ tj.jointsID[j] ] = 0;
					//}
					const MayaTriangle& triangle = mayaTriangles[materialNumber][triangleNumber];
					bool containCurrentJoint = false;

					for (unsigned char j = 0; j < jointsPerVertex; ++j)
					{
						if( (pSkeletalVertexStride[triangle.a].weights[j] > 0.f) && (pSkeletalVertexStride[triangle.a].indices[j] == currentJointValue) )
							containCurrentJoint = true;
						if( (pSkeletalVertexStride[triangle.b].weights[j] > 0.f) && (pSkeletalVertexStride[triangle.b].indices[j] == currentJointValue) )
							containCurrentJoint = true;
						if( (pSkeletalVertexStride[triangle.c].weights[j] > 0.f) && (pSkeletalVertexStride[triangle.c].indices[j] == currentJointValue) )
							containCurrentJoint = true;
					}
					
					if(!containCurrentJoint)
						continue;

					for (unsigned char j = 0; j < jointsPerVertex; ++j)
					{
						if(pSkeletalVertexStride[triangle.a].weights[j] > 0.f)
							branch[pSkeletalVertexStride[triangle.a].indices[j]];
						if(pSkeletalVertexStride[triangle.b].weights[j] > 0.f)
							branch[pSkeletalVertexStride[triangle.b].indices[j]];
						if(pSkeletalVertexStride[triangle.c].weights[j] > 0.f)
							branch[pSkeletalVertexStride[triangle.c].indices[j]];
					}

				}
				//int added = branch.size();
				//systemLog( NLogg::LEVEL_MESSAGE ) << "branch.size():" << branch.size() << endl;

				unsigned short newJointCounter = 0;
				for(nstl::hash_map<unsigned short, unsigned short>::const_iterator joint = branch.begin(); joint != branch.end(); ++joint)
				{
					if( trunk.find( joint->first ) == trunk.end() )
						++newJointCounter;
				}
				if( (trunk.size() + newJointCounter) > maxJointsPerMaterial )
				{
					fragmentCounter++;
					//systemLog( NLogg::LEVEL_MESSAGE ) << "#" << fragmentCounter << " fallback at: " << currentJointIndex << " trunk.size:" << trunk.size() << "+" << newJointCounter << endl;

					fragmentJoints[materialNumber].push_back();
					for(int j = oldJointIndex; j < currentJointIndex; ++j)
						fragmentJoints[materialNumber][fragmentCounter].push_back( indexOrder[j].original );

					oldJointIndex = currentJointIndex;
					trunk.clear();
					continue;
				}
				//
				for(nstl::hash_map<unsigned short, unsigned short>::const_iterator joint = branch.begin(); joint != branch.end(); ++joint)
				{
					trunk[ joint->first ] = 0;
				}
				//systemLog( NLogg::LEVEL_MESSAGE ) << "trunk.size():" << trunk.size() << endl;
				currentJointIndex++;
			}
			fragmentCounter++;
			//DumpJoints( trunk, fragmentJoints[materialNumber] );
			fragmentJoints[materialNumber].push_back();
			for(int j = oldJointIndex; j < currentJointIndex; ++j)
				fragmentJoints[materialNumber][fragmentCounter].push_back( indexOrder[j].original );
			//systemLog( NLogg::LEVEL_MESSAGE ) << "#" << fragmentCounter << " end at: " << currentJointIndex << " trunk.size:" << trunk.size() << "+0" << endl;
			if( idealFragmentCount < (fragmentCounter+1) )
			{
				systemLog( NLogg::LEVEL_MESSAGE ) << "bad breaking!!!" << endl;
				systemLog( NLogg::LEVEL_MESSAGE ) << "it is strongly recommended to break this material by yourself!!!" << endl;
			}
			//else
			//{
			//	systemLog( NLogg::LEVEL_MESSAGE ) << "good breaking!!!" << endl;
			//}

			NI_VERIFY( fragmentCounter < 5, "cant break this material", return -1; );

		}//		if(materialJointsIndices[materialNumber].size() > maxJointsPerMaterial)
		else
		{
			fragmentJoints[materialNumber].push_back();
			for(nstl::hash_map<unsigned short, unsigned short>::const_iterator it = materialJointsIndices[materialNumber].begin(); it != materialJointsIndices[materialNumber].end(); ++it)
				fragmentJoints[materialNumber][0].push_back(it->first);
		}
	}
  for ( int matIdx = 0; matIdx < fragmentJoints.size(); matIdx++ )
  {
    for ( int fragmentIdx = 0; fragmentIdx < fragmentJoints[matIdx].size(); fragmentIdx++ )
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "Material " << matIdx << " fragment " << fragmentIdx << " joints " << fragmentJoints[matIdx][fragmentIdx].size() << endl;
    }
  }

	//////////////////////////////////////////////////////////////////////////
	//systemLog( NLogg::LEVEL_MESSAGE ) << "now dumping triangles! ..."  << endl;

	nstl::vector< nstl::vector<unsigned short> > fragmentsReindex;
	nstl::vector< nstl::vector<unsigned int> > fragmentsIB;
	nstl::vector< nstl::vector<H6SkeletalMeshVertexStride> > fragmentsVB;
	nstl::vector< unsigned char > materialID;

	for (unsigned int materialNumber = 0; materialNumber < subMeshCount; ++materialNumber )
	{
		//systemLog( NLogg::LEVEL_MESSAGE ) << "material #" << materialNumber << " has " << fragmentJoints[materialNumber].size() << " fragments" << "; tri: " << mayaTriangles[materialNumber].size() << endl; 
		for (int fragmentNumber = 0; fragmentNumber < fragmentJoints[materialNumber].size(); ++fragmentNumber)
		{
			materialID.push_back((unsigned char)materialNumber);
			nstl::set<unsigned int> triangleIndexList;
      BuildMayaTrianglesList(fragmentJoints[materialNumber][fragmentNumber], triangleIndexList, mayaTriangles[materialNumber], pSkeletalVertexStride, jointsPerVertex );
			//int triangleCount = BuildMayaTrianglesList(fragmentJoints[materialNumber][fragmentNumber], triangleIndexList, mayaTriangles[materialNumber], pSkeletalVertexStride, jointsPerVertex );
			//systemLog( NLogg::LEVEL_MESSAGE ) << "fragment #" << fragmentNumber << ";  tri: " << triangleCount << endl;
			BuildVBIB( triangleIndexList, mayaTriangles[materialNumber], fragmentsVB.push_back(), fragmentsIB.push_back(), fragmentsReindex.push_back(), pSkeletalVertexStride, jointsPerVertex );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	ASSERT(fragmentsReindex.size() == materialID.size());
	ASSERT(fragmentsIB.size() == materialID.size());
	ASSERT(fragmentsVB.size() == materialID.size());
	unsigned int h6fragmentCount = materialID.size();
	//////////////////////////////////////////////////////////////////////////

  // determine presense of vertex colols
  // -1 means "0 or 1 depending on the presence of colors in maya geometry"
  // If all colors in maya geometry are (1,1,1,1) it is the same as if they are absent.
  if (numColorChannels == -1)
  {
    numColorChannels = 0;

    for (unsigned int fragmentNumber = 0; fragmentNumber < h6fragmentCount; ++fragmentNumber)
    {
      for (int vertexNumber = 0; vertexNumber < fragmentsVB[fragmentNumber].size(); ++vertexNumber )
      {
        unsigned int c = fragmentsVB[fragmentNumber][vertexNumber].color;
        if ( c != 0xFFFFFFFF )
        {
          numColorChannels = 1;
          break;
        }
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Merge vertices with similar positions even when other data differs. Append these merged vertices to the end of 
  // the vertex buffer and prepare a modified copy of the index buffer.
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef MERGE_EQUAL_VERTICES
  MergeEqualVertices(fragmentsVB, fragmentsIB);
#endif // MERGE_EQUAL_VERTICES
/*
  // inflate geometry to test merge right in the editor [11/25/2010 paul.smirnov]
  for (unsigned int fragmentNumber = 0; fragmentNumber < h6fragmentCount; ++fragmentNumber)
  {
    nstl::vector<H6SkeletalMeshVertexStride>& fragVertices = fragmentsVB[fragmentNumber];
    for (unsigned int idxA = 0; idxA < (unsigned)fragVertices.size(); ++idxA )
    {
      CVec3& posA = fragVertices[idxA].position;
      CVec3 const& nrmA = fragVertices[idxA].normal;
      posA += myOffset * nrmA;
    }
  }
*/
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // End of merge
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  DummyAllocator allocator(writerMaxLenght);
	H6GeometryFileHeader* pH6GeometryFileHeader = reinterpret_cast<H6GeometryFileHeader*>(allocator.Allocate(sizeof(H6GeometryFileHeader), 16));
	pH6GeometryFileHeader->signature = pMayaHeader->signature;
	pH6GeometryFileHeader->fragmentCount = h6fragmentCount;
	pH6GeometryFileHeader->materialCount = subMeshCount;
	///
	pH6GeometryFileHeader->jointsCount = pSkeletonData->jointsCount;
	pH6GeometryFileHeader->fragments.resize( h6fragmentCount, &allocator );

	unsigned int vboffset = 0;
	unsigned int iboffset = 0;
	unsigned int strideSize = 0;

	for (unsigned int fragmentNumber = 0; fragmentNumber < h6fragmentCount; ++fragmentNumber)
	{
		H6FragmentHeader& fragmentHeader = pH6GeometryFileHeader->fragments[fragmentNumber];

		StaticVector<Render::VertexElementDescriptor> &ved = fragmentHeader.vertexElementDescriptor;

		//
		unsigned int strideElementsCount = 5;
		if (convertTagentAndBinormal)
			strideElementsCount += 2;
		if (numColorChannels)
			strideElementsCount++;
		ved.resize( strideElementsCount, &allocator );	

		// Stride
		strideSize = 0;
		unsigned int ndx = 0;
		ved[ndx++] = Render::VertexElementDescriptor(0, strideSize,	Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_POSITION, 0);
		strideSize += 12;
		if (convertTagentAndBinormal)
		{
			ved[ndx++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_TANGENT, 0);
			strideSize += 12;
			ved[ndx++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_BINORMAL,	0);
			strideSize += 12;
		}
		ved[ndx++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_NORMAL, 0);
		strideSize += 12;
		if (numColorChannels > 0) // Only one color channel is supported
		{
			ved[ndx++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_COLOR, 0);
			strideSize += 4;
		}
		ved[ndx++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT2, Render::VERETEXELEMENTUSAGE_TEXCOORD, 0);
		strideSize += 8;
		ved[ndx++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT4, Render::VERETEXELEMENTUSAGE_BLENDWEIGHT, 0);
		strideSize += 16;
		ved[ndx++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_BLENDINDICES, 0);
		strideSize += 4;
		/// 
		fragmentHeader.vertexStrideSizeInBytes = strideSize;
		fragmentHeader.baseVertexIndex = vboffset;
		fragmentHeader.minIndex = 0;
		fragmentHeader.numVertices = fragmentsVB[fragmentNumber].size();
		fragmentHeader.startIndex = iboffset;
		fragmentHeader.primitiveCount = fragmentsIB[fragmentNumber].size() / VERTEX_PER_TRIANGLE;
		fragmentHeader.materialID = materialID[fragmentNumber];
		fragmentHeader.streamOffset = 0;
		/// 
		vboffset += fragmentsVB[fragmentNumber].size();
		iboffset += fragmentsIB[fragmentNumber].size();

#ifdef MERGE_EQUAL_VERTICES
		// there's a copy of index buffer at the second half [10/4/2010 paul.smirnov]
		fragmentHeader.primitiveCount /= 2;
		// fragmentHeader.startIndex += fragmentsIB[fragmentNumber].size() / 2;
#endif // MERGE_EQUAL_VERTICES
	}

	pH6GeometryFileHeader->commonIndexBufferSizeInBytes = sizeof(unsigned int) * iboffset;
	pH6GeometryFileHeader->commonVertexBufferSizeInBytes = strideSize * vboffset;
	/// 
	allocator.Normalize(16);
	payloadSize = allocator.GetSize();
	pH6GeometryFileHeader->vbOffset = payloadSize;
	pH6GeometryFileHeader->ibOffset = pH6GeometryFileHeader->vbOffset + pH6GeometryFileHeader->commonVertexBufferSizeInBytes;
	pH6GeometryFileHeader->reindexOffset = pH6GeometryFileHeader->ibOffset + pH6GeometryFileHeader->commonIndexBufferSizeInBytes;
	///

	writerStream.Reserve(1024*1024);

	writerStream.Write( allocator.GetData(), payloadSize );

	ASSERT( writerStream.GetPosition() == (int)pH6GeometryFileHeader->vbOffset );

	for (unsigned int fragmentNumber = 0; fragmentNumber < h6fragmentCount; ++fragmentNumber)
	{
		for (int vertexNumber = 0; vertexNumber < fragmentsVB[fragmentNumber].size(); ++vertexNumber )
		{
			nstl::vector<H6SkeletalMeshVertexStride>& fragment = fragmentsVB[fragmentNumber];
			if (convertTagentAndBinormal)
			{
				writerStream.Write(&fragment[vertexNumber].position, 48); //pos+tbn
			}
			else
			{
				writerStream.Write(&fragment[vertexNumber].position, 12);
				writerStream.Write(&fragment[vertexNumber].normal, 12);
			}

			if (numColorChannels)
			{
				writerStream.Write(&fragment[vertexNumber].color, 4);
			}

			CVec2 uv = fragment[vertexNumber].texcoord[0];
			uv.y *= -1.f;
			writerStream.Write(&uv, 8);
			ASSERT(fragment[vertexNumber].weights[0] < 1.00001f);
			ASSERT(fragment[vertexNumber].weights[1] < 0.50001f);
			writerStream.Write(&fragment[vertexNumber].weights[0], 16);
			ASSERT(fragment[vertexNumber].indices[0] < maxJointsPerMaterial);
			ASSERT(fragment[vertexNumber].indices[1] < maxJointsPerMaterial);
			ASSERT(fragment[vertexNumber].indices[2] < maxJointsPerMaterial);
			ASSERT(fragment[vertexNumber].indices[3] < maxJointsPerMaterial);
			Render::Color indices(fragment[vertexNumber].indices[0], fragment[vertexNumber].indices[1], fragment[vertexNumber].indices[2], fragment[vertexNumber].indices[3]);
			writerStream.Write(&indices, 4);

		}
	}

	ASSERT( writerStream.GetPosition() == (int)pH6GeometryFileHeader->ibOffset );



	for (unsigned int fragmentNumber = 0; fragmentNumber < h6fragmentCount; ++fragmentNumber)
	{
		nstl::vector<unsigned int>& fragment = fragmentsIB[fragmentNumber];
		writerStream.Write( &fragment[0], fragment.size()*4 ); 
	}

	ASSERT( writerStream.GetPosition() == (int)pH6GeometryFileHeader->reindexOffset );

	allocator.Clear();

	GeometryReindex* pGeometryReindex = reinterpret_cast<GeometryReindex*>( allocator.Allocate(sizeof(GeometryReindex), 16) );


	pGeometryReindex->reindex.resize(h6fragmentCount, &allocator);
	for (unsigned int fragmentNumber = 0; fragmentNumber < h6fragmentCount; ++fragmentNumber)
	{
		pGeometryReindex->reindex[fragmentNumber].resize(fragmentsReindex[fragmentNumber].size(), &allocator);
		for(int i = 0; i < fragmentsReindex[fragmentNumber].size(); ++i )
			pGeometryReindex->reindex[fragmentNumber][i] = fragmentsReindex[fragmentNumber][i];
	}
	writerStream.Write( allocator.GetData(), allocator.GetSize() );

	return subMeshCount;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall ConvertSkeletonFromMemory( const void* const pReader, unsigned int readerLength, void* const pWriter, unsigned int writerMaxLenght, unsigned int& payloadSize  )
{
	//HANDLE fileHandle = CreateFileA( _filename.c_str(), GENERIC_READ, 0,	0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN |	FILE_FLAG_NO_BUFFERING, 0);
	//FileStream fileStream( _filename, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	//NI_VERIFY( fileStream.IsOk(), "Cannot open file with some data", return false );

  if(pReader == 0 || readerLength == 0)
    return -1;

	const unsigned char* pBuffer = reinterpret_cast<const unsigned char*>( pReader );

	const unsigned int numBones = *reinterpret_cast<const unsigned int*>( &pBuffer[4] );

	unsigned int curPos = 8;

	nstl::vector< unsigned __int32 > mayaParentID;
	nstl::vector< NameIndexPair > bonesNames;
	nstl::vector< Matrix43 > bindMatricies;


	//systemLog( NLogg::LEVEL_MESSAGE ) << "parsing ancher's file ..." << endl;
	mayaParentID.resize(numBones);
	bonesNames.resize(numBones);
	bindMatricies.resize(numBones);
	for	( unsigned int i = 0; i < numBones; ++i )
	{
		//names
		const char* str = reinterpret_cast< const char* >( &pBuffer[curPos] );
		unsigned int len = strnlen( str, MAX_BONE_NAME_LENGTH + 1 );
		NI_VERIFY( len < (MAX_BONE_NAME_LENGTH + 1), "original skeleton file corrupted", return -1 );
		nstl::string name( str );
		bonesNames[i].name = name;
		bonesNames[i].index = i;
		curPos += len + 1;

		//IDs
		mayaParentID[i] = *reinterpret_cast< const unsigned int* >( &pBuffer[curPos] );
		curPos += 4;

		//inverted bindpose matrix
		bindMatricies[i] = *reinterpret_cast< const Matrix43* >( &pBuffer[curPos] );
		curPos += 12 * sizeof(float);
	}

	//systemLog( NLogg::LEVEL_MESSAGE ) << "sorting names ..." << endl;
	nstl::sort( bonesNames.begin(), bonesNames.end(), CompareNameIndexPair );
	//for ( int i = 0; i < bonesNames.size(); ++i)
	//{
	//	systemLog( NLogg::LEVEL_MESSAGE ) << bonesNames[i].name << endl;
	//}

	//systemLog( NLogg::LEVEL_MESSAGE ) << "building new file ..." << endl;

  DummyAllocator allocator(writerMaxLenght);
	SkeletonData* pSkeletonData = reinterpret_cast<SkeletonData*>( allocator.Allocate(sizeof(SkeletonData), 16));
	pSkeletonData->jointsCount = numBones;
	allocator.Normalize(64);
	pSkeletonData->invertedBindPoseBones.resize( numBones, &allocator );
	pSkeletonData->jointsNames.resize( numBones, &allocator );
	pSkeletonData->namesOrder.resize( numBones, &allocator );
	pSkeletonData->parentsIDs.resize( numBones, &allocator );
	for (unsigned int i = 0; i < numBones; ++i)
	{
		pSkeletonData->jointsNames[i].Construct( bonesNames[i].name.c_str(), bonesNames[i].name.length(), &allocator);
		pSkeletonData->invertedBindPoseBones[i] = bindMatricies[i];
		pSkeletonData->namesOrder[i] = bonesNames[i].index;
		pSkeletonData->parentsIDs[i] = mayaParentID[i];
	}

	allocator.Normalize(512);
	payloadSize = allocator.GetSize();
	memcpy(pWriter, allocator.GetData(), allocator.GetSize());
	//systemLog( NLogg::LEVEL_MESSAGE ) << "looks like all is ok!" << endl;
	return numBones;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall ConvertSkeletonSafe( const char* pAncherFileName
																	, const char* pGameFileName )
{
	NI_VERIFY( pAncherFileName != pGameFileName, "names should be different", return -1 );

	NI_VERIFY( pAncherFileName, "pointer to c-style string with AncherFileName is not valid", return -1; );
	NI_VERIFY( strnlen(pAncherFileName, MAX_FILE_NAME_LENGTH+1) < MAX_FILE_NAME_LENGTH, ("file name too long (probably you pointed to the junk): " + nstl::string(pAncherFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1; );

	NI_VERIFY( pGameFileName, "pointer to c-style string with GameFileName is not valid", return -1; );
	NI_VERIFY( strnlen(pGameFileName, MAX_FILE_NAME_LENGTH+1) < MAX_FILE_NAME_LENGTH, ("file name too long (probably you pointed to the junk): " + nstl::string(pGameFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1; );

	FileStream ancherFileStream( pAncherFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	NI_VERIFY( ancherFileStream.IsOk(), NStr::StrFmt( "Cannot open file with Ancher's skeleton %s", pAncherFileName), return -1 );

	FileStream gameFileStream( pGameFileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
	NI_VERIFY( gameFileStream.IsOk(), NStr::StrFmt( "Cannot open file with game's skeleton %s", pGameFileName), return -1 );

	unsigned int maxWriterSize = 1024*1024+ancherFileStream.GetSize();
	void* const pNewData = Aligned_MAlloc(maxWriterSize, 512);
	unsigned int payloadSize = 0;

	//systemLog( NLogg::LEVEL_MESSAGE ) << "streams are opened ..." << endl;

  int res = ConvertSkeletonFromMemory( ancherFileStream.GetBuffer(), ancherFileStream.GetSize(), pNewData, maxWriterSize, payloadSize );

	if( res < 0 )
		return -1;
	gameFileStream.Write( pNewData, payloadSize );
  Aligned_Free(pNewData);
	return res;
}
//////////////////////////////////////////////////////////////////////////
static float GetRealFrame(unsigned int frameNumber, unsigned int keyNumber)
{
  //return keyNumber ? (frameNumber + 1) : frameNumber;
  return frameNumber;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall ConvertParticleFromMemory( const void* const pReader, unsigned int readerLength, void* const pWriter, unsigned int writerMaxLenght, int& payloadSize, unsigned int& maxSpriteID  )
{
	const MayaPFXHeader* pHeader = reinterpret_cast<const MayaPFXHeader*>(pReader);
	const MayaPFXTrackHeader* pCurrentTrack = reinterpret_cast<const MayaPFXTrackHeader*>(pHeader+1);
  DummyAllocator allocator(writerMaxLenght);
	NewPFXBinaryFile* pFile = reinterpret_cast<NewPFXBinaryFile*>(allocator.Allocate(sizeof(NewPFXBinaryFile), 16));
	pFile->header.duration = pHeader->duration;
	const float frameRate = pHeader->frameRate;
	const float epsilon = 0.0001f;
	const float duration = pHeader->duration + epsilon;
	pFile->particlesTracks.resize( pHeader->particlesCount, &allocator );
	unsigned int keyNumber;
  maxSpriteID = 0;
	for (unsigned int particleNumber = 0; particleNumber < pHeader->particlesCount; ++particleNumber)
	{
		// track header
		//systemLog( NLogg::LEVEL_MESSAGE ) << "#" << particleNumber << ": " << pCurrentTrack->firstFrame << "-" << pCurrentTrack->lastFrame << endl;
		pFile->particlesTracks[particleNumber].beginTime = pCurrentTrack->firstFrame / frameRate;
		pFile->particlesTracks[particleNumber].endTime = (pCurrentTrack->lastFrame+1) / frameRate;
		ASSERT( pFile->particlesTracks[particleNumber].beginTime >= 0);
		ASSERT( pFile->particlesTracks[particleNumber].beginTime < pHeader->duration);
		NI_VERIFY( pFile->particlesTracks[particleNumber].endTime <= duration, NStr::StrFmt("track #%d : %f, %f",particleNumber,  pFile->particlesTracks[particleNumber].endTime, duration),return -1;);
		// position
		const unsigned int* pPositionTrackSize = reinterpret_cast<const unsigned int*>(pCurrentTrack+1);
		const TMayaPFXPosition* pTrackData = reinterpret_cast<const TMayaPFXPosition*>(pPositionTrackSize+1);
		pFile->particlesTracks[particleNumber].positionTrack.resize( *pPositionTrackSize+1, &allocator );
		for (keyNumber = 0; keyNumber < *pPositionTrackSize; ++keyNumber)
		{
			ASSERT( pTrackData[keyNumber].frameNumber / frameRate <= duration);
			pFile->particlesTracks[particleNumber].positionTrack.timeData[keyNumber] = GetRealFrame(pTrackData[keyNumber].frameNumber, keyNumber) / frameRate;
			pFile->particlesTracks[particleNumber].positionTrack.trackData[keyNumber] = pTrackData[keyNumber].Data; 
		}
    if ( keyNumber > 0 )
    {
      pFile->particlesTracks[particleNumber].positionTrack.timeData[keyNumber] = GetRealFrame(pTrackData[keyNumber-1].frameNumber+1, keyNumber-1) / frameRate;
      pFile->particlesTracks[particleNumber].positionTrack.trackData[keyNumber] = pTrackData[keyNumber-1].Data; 
    }
		
		// scale and rotation
		const unsigned int* pSRSize = (const unsigned int*)&pTrackData[keyNumber];
		const TMayaPFXScaleRotation* pSRTrackData = reinterpret_cast<const TMayaPFXScaleRotation*>(pSRSize+1);
		pFile->particlesTracks[particleNumber].rotationAndScaleTrack.resize( *pSRSize+1, &allocator );
		for (keyNumber = 0; keyNumber < *pSRSize; ++keyNumber)
		{
			ASSERT( pSRTrackData[keyNumber].frameNumber / frameRate <= duration);
			pFile->particlesTracks[particleNumber].rotationAndScaleTrack.timeData[keyNumber] =  GetRealFrame(pSRTrackData[keyNumber].frameNumber, keyNumber) / frameRate;
			pFile->particlesTracks[particleNumber].rotationAndScaleTrack.trackData[keyNumber] = pSRTrackData[keyNumber].Data; 
		}
    if ( keyNumber > 0 )
    {
      pFile->particlesTracks[particleNumber].rotationAndScaleTrack.timeData[keyNumber] =  GetRealFrame(pSRTrackData[keyNumber-1].frameNumber+1, keyNumber-1) / frameRate;
      pFile->particlesTracks[particleNumber].rotationAndScaleTrack.trackData[keyNumber] = pSRTrackData[keyNumber-1].Data; 
    }

		//color
		const unsigned int* pColorSize = (const unsigned int*)&pSRTrackData[keyNumber];
		const TMayaPFXColor* pColorTrackData = reinterpret_cast<const TMayaPFXColor*>(pColorSize+1);
		pFile->particlesTracks[particleNumber].colorTrack.resize( *pColorSize+1, &allocator );
		for (keyNumber = 0; keyNumber < *pColorSize; ++keyNumber)
		{
			ASSERT( pColorTrackData[keyNumber].frameNumber / frameRate <= duration);
			pFile->particlesTracks[particleNumber].colorTrack.timeData[keyNumber] =  GetRealFrame(pColorTrackData[keyNumber].frameNumber, keyNumber) / frameRate;
			pFile->particlesTracks[particleNumber].colorTrack.trackData[keyNumber] = pColorTrackData[keyNumber].Data; 
		}
    if ( keyNumber > 0 )
    {
      pFile->particlesTracks[particleNumber].colorTrack.timeData[keyNumber] =  GetRealFrame(pColorTrackData[keyNumber-1].frameNumber+1, keyNumber-1) / frameRate;
      pFile->particlesTracks[particleNumber].colorTrack.trackData[keyNumber] = pColorTrackData[keyNumber-1].Data; 
    }

		//sprite
		const unsigned int* pSpriteSize = (const unsigned int*)&pColorTrackData[keyNumber];
		const TMayaPFXSprite* pSpriteTrackData = reinterpret_cast<const TMayaPFXSprite*>(pSpriteSize+1);
		pFile->particlesTracks[particleNumber].uvTrack.resize( *pSpriteSize+1, &allocator );
		for (keyNumber = 0; keyNumber < *pSpriteSize; ++keyNumber)
		{
			ASSERT( pSpriteTrackData[keyNumber].frameNumber / frameRate <= duration);
			pFile->particlesTracks[particleNumber].uvTrack.timeData[keyNumber] =  GetRealFrame(pSpriteTrackData[keyNumber].frameNumber, keyNumber) / frameRate;
			pFile->particlesTracks[particleNumber].uvTrack.trackData[keyNumber] = pSpriteTrackData[keyNumber].Data; 
      if ( maxSpriteID < pSpriteTrackData[keyNumber].Data )
      {
        maxSpriteID = pSpriteTrackData[keyNumber].Data;
      }
		}
    if ( keyNumber > 0 )
    {
      pFile->particlesTracks[particleNumber].uvTrack.timeData[keyNumber] =  GetRealFrame(pSpriteTrackData[keyNumber-1].frameNumber+1, keyNumber-1) / frameRate;
      pFile->particlesTracks[particleNumber].uvTrack.trackData[keyNumber] = pSpriteTrackData[keyNumber-1].Data; 
    }

		pCurrentTrack = (const MayaPFXTrackHeader*)&pSpriteTrackData[keyNumber];
	}

	allocator.Normalize(1024);
	payloadSize = allocator.GetSize();
	memcpy(pWriter, allocator.GetData(), allocator.GetSize());
	//systemLog( NLogg::LEVEL_MESSAGE ) << "looks like all is ok!" << endl;
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall ConvertParticleSafe( const char* pAncherFileName
																	, const char* pGameFileName )
{
	NI_VERIFY( pAncherFileName != pGameFileName, "names should be different", return -1 );

	NI_VERIFY( pAncherFileName, "pointer to c-style string with AncherFileName is not valid", return -1; );
	NI_VERIFY( strnlen(pAncherFileName, MAX_FILE_NAME_LENGTH+1) < MAX_FILE_NAME_LENGTH, ("file name too long (probably you pointed to the junk): " + nstl::string(pAncherFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1; );

	NI_VERIFY( pGameFileName, "pointer to c-style string with GameFileName is not valid", return -1; );
	NI_VERIFY( strnlen(pGameFileName, MAX_FILE_NAME_LENGTH+1) < MAX_FILE_NAME_LENGTH, ("file name too long (probably you pointed to the junk): " + nstl::string(pGameFileName, MAX_FILE_NAME_LENGTH)).c_str(), return -1; );

	FileStream ancherFileStream( pAncherFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	NI_VERIFY( ancherFileStream.IsOk(), NStr::StrFmt( "Cannot open file with Ancher's particle data %s", pAncherFileName), return -1 );

	FileStream gameFileStream( pGameFileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
	NI_VERIFY( gameFileStream.IsOk(), NStr::StrFmt( "Cannot open file with game's particle data %s", pGameFileName), return -1 );

	unsigned int maxWriterSize = 10*1024*1024+ancherFileStream.GetSize();
	void* const pNewData = Aligned_MAlloc(maxWriterSize, 512);
	int payloadSize = 0;
  uint spriteID = 0;

	//systemLog( NLogg::LEVEL_MESSAGE ) << "streams are opened ..." << endl;

	int res = ConvertParticleFromMemory( ancherFileStream.GetBuffer(), ancherFileStream.GetSize(), pNewData, maxWriterSize, payloadSize, spriteID );

	if( res < 0 )
		return -1;
	gameFileStream.Write( pNewData, payloadSize );
  Aligned_Free(pNewData);
	return res;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VERTEX> unsigned int GetColor(VERTEX const& v)
{
	return MakeColor(v.color);
}

template <> unsigned int GetColor<MayaVertexStrideStaticOld>(MayaVertexStrideStaticOld const& v)
{
	return 0xFFFFFFFF;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VERTEX>
int ConvertStaticMeshGeometryTemplate( const unsigned char* pMayaBuffer, int mayaFileDataSize, 
	void* h6FileBuffer, int h6BufferSize, int* h6FileActualLength, 
	unsigned int _ConvertTagentAndBinormal, int _ConvertColors, unsigned char _UVChannels, 
	NDb::AABB* pAABBs )
{
	FixedMemoryStream h6FileStream( h6FileBuffer, h6BufferSize );

	//systemLog( NLogg::LEVEL_MESSAGE ) << "streams are opened ..." << endl;
	//////////////////////////////////////////////////////////////////////////
	//systemLog( NLogg::LEVEL_MESSAGE ) << "parsing ancher's file header ..." << endl;
	NI_VERIFY(pAABBs, "pointer to AABB is null", return -1; );
	const MayaStaticMeshFileHeader* pMayaHeader = reinterpret_cast<const MayaStaticMeshFileHeader*>(pMayaBuffer);
	const VERTEX* pStaticVertex = reinterpret_cast<const VERTEX*>(pMayaBuffer + sizeof(MayaStaticMeshFileHeader) );
	const MayaIndexHeader* pMayaStaticIndexHeader = reinterpret_cast<const MayaIndexHeader*>(pStaticVertex + pMayaHeader->vertexCount);

	const MayaIndexBufferHeader* pIndexBufferHeaders[16];
	const unsigned __int32* ptr = reinterpret_cast<const unsigned __int32*>(pMayaStaticIndexHeader+1);
	const unsigned int subMeshCount = pMayaStaticIndexHeader->subMeshCount ;
	NI_VERIFY( subMeshCount < 16, "too many fragments", return -1);
	unsigned int indexCount = 0;

	for (unsigned int i = 0; i < subMeshCount; ++i)
	{
		pIndexBufferHeaders[i] = reinterpret_cast<const MayaIndexBufferHeader*>(ptr + indexCount + 2*i);
		indexCount += pIndexBufferHeaders[i]->triangleCount*VERTEX_PER_TRIANGLE;
	}

	nstl::vector< nstl::vector<MayaTriangle> > mayaVertexIndices(subMeshCount);
	nstl::vector< nstl::set<unsigned int, less> > mayaUniqIndices(subMeshCount);
	nstl::vector< nstl::hash_map<unsigned int, unsigned int> > oldNewIndices(subMeshCount);

	//struct LeaveVertex
	//{
	//	CVec3 center;
	//	CVec2 offset;
	//};
	//nstl::vector< nstl::hash_map<unsigned int, LeaveVertex> > centers( subMeshCount );
	nstl::vector< nstl::hash_map<unsigned int, CVec3> > centers( subMeshCount );

	for (unsigned int materialNumber = 0; materialNumber < subMeshCount; ++materialNumber)
	{
		unsigned int indexCount = pIndexBufferHeaders[materialNumber]->triangleCount*VERTEX_PER_TRIANGLE;
		mayaVertexIndices[materialNumber].resize(indexCount/VERTEX_PER_TRIANGLE);
		for (unsigned int indexNumber = 0; indexNumber < indexCount; indexNumber+=3 )
		{
			MayaTriangle& triangle = mayaVertexIndices[materialNumber][indexNumber/VERTEX_PER_TRIANGLE];
			unsigned int* pIndex = ((unsigned int*)(pIndexBufferHeaders[materialNumber]+1))+indexNumber;
			triangle.a = *pIndex;
			triangle.b = *(pIndex+1);
			triangle.c = *(pIndex+2);
			ASSERT( (triangle.a < pMayaHeader->vertexCount) && (triangle.b < pMayaHeader->vertexCount) && (triangle.c < pMayaHeader->vertexCount) );
			mayaUniqIndices[materialNumber].insert(triangle.a);
			mayaUniqIndices[materialNumber].insert(triangle.b);
			mayaUniqIndices[materialNumber].insert(triangle.c);
		}
	}
	/// 
	for (unsigned int materialNumber = 0; materialNumber < subMeshCount; ++materialNumber)
	{
		unsigned int counter = 0;
		for (nstl::set<unsigned int, less>::const_iterator it = mayaUniqIndices[materialNumber].begin(); it != mayaUniqIndices[materialNumber].end(); ++it )
		{
			oldNewIndices[materialNumber][*it] = counter++;
		}
	}
	///

  // -1 means "0 or 1 depending on the presence of colors in maya geometry"
  // If all colors in maya geometry are (1,1,1,1) it is the same as if they are absent.
  if (_ConvertColors == -1)
  {
    _ConvertColors = 0;

    for (unsigned int i = 0; i < pMayaHeader->vertexCount; ++i)
    {
      unsigned int c = GetColor(pStaticVertex[i]);
      if ( c != 0xFFFFFFFF )
      {
        _ConvertColors = 1;
        break;
      }
    }
  }

	// Prepare vertex structure
	unsigned int const STRIDE_ELEMENTS_COUNT_MAX = 8;
	unsigned int strideElementsCount = 0;
	unsigned int strideSize = 0;
	Render::VertexElementDescriptor desc[STRIDE_ELEMENTS_COUNT_MAX];
	desc[strideElementsCount++]   = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_POSITION, 0);
	strideSize += 12;
	if (_ConvertTagentAndBinormal)
	{
		desc[strideElementsCount++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_TANGENT, 0);
		strideSize += 12;
		desc[strideElementsCount++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_BINORMAL,	0);
		strideSize += 12;
	}
	desc[strideElementsCount++]   = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_NORMAL, 0);
	strideSize += 12;
	
  ASSERT(0 <= _ConvertColors && _ConvertColors <= 2);
  for (int k = 0; k < _ConvertColors; ++k)
	{
		desc[strideElementsCount++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_COLOR, k);
		strideSize += 4;
	}

	desc[strideElementsCount++]   = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT2, Render::VERETEXELEMENTUSAGE_TEXCOORD, 0);
	strideSize += 8;
	if (_UVChannels == 2)
	{
		desc[strideElementsCount++] = Render::VertexElementDescriptor(0, strideSize, Render::VERTEXELEMENTTYPE_FLOAT2, Render::VERETEXELEMENTUSAGE_TEXCOORD, 1);
		strideSize += 8;
	}

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // make the same arrays as in animated case [11/25/2010 paul.smirnov]
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  nstl::vector< nstl::vector<unsigned int> > fragmentsIB;
  nstl::vector< nstl::vector<VERTEX> > fragmentsVB;
  for (unsigned int fragmentNumber = 0; fragmentNumber < subMeshCount; ++fragmentNumber)
  {
    // copy vertices
    nstl::vector<VERTEX>& fragVetrices = fragmentsVB.push_back();
    for (nstl::set<unsigned int, less>::const_iterator it = mayaUniqIndices[fragmentNumber].begin(); it != mayaUniqIndices[fragmentNumber].end(); ++it )
      fragVetrices.push_back(pStaticVertex[*it]);

    // copy indices
    nstl::vector<unsigned int>& fragIndices = fragmentsIB.push_back();
    for (int triangleNumber = 0; triangleNumber < mayaVertexIndices[fragmentNumber].size(); ++triangleNumber)
    {
      MayaTriangle& triangle = mayaVertexIndices[fragmentNumber][triangleNumber];
      fragIndices.push_back(oldNewIndices[fragmentNumber][triangle.a]);
      fragIndices.push_back(oldNewIndices[fragmentNumber][triangle.b]);
      fragIndices.push_back(oldNewIndices[fragmentNumber][triangle.c]);
    }
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Merge vertices with similar positions even when other data differs. Append these merged vertices to the end of 
  // the vertex buffer and prepare a modified copy of the index buffer.
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef MERGE_EQUAL_VERTICES
  MergeEqualVertices(fragmentsVB, fragmentsIB);
#endif // MERGE_EQUAL_VERTICES
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // End of merge
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  DummyAllocator allocator(20*1024*1024);
	H6GeometryFileHeader* pH6GeometryFileHeader = reinterpret_cast<H6GeometryFileHeader*>(allocator.Allocate(sizeof(H6GeometryFileHeader), 16));
	pH6GeometryFileHeader->signature = pMayaHeader->signature;
	pH6GeometryFileHeader->fragmentCount = subMeshCount;
	pH6GeometryFileHeader->materialCount = subMeshCount;
	///
	pH6GeometryFileHeader->jointsCount = 0;
	pH6GeometryFileHeader->fragments.resize( subMeshCount, &allocator );

	unsigned int vboffset = 0;
	unsigned int iboffset = 0;

	for (unsigned int fragmentNumber = 0; fragmentNumber < subMeshCount; ++fragmentNumber)
	{
		H6FragmentHeader& fragmentHeader = pH6GeometryFileHeader->fragments[fragmentNumber];
		/// 
		fragmentHeader.vertexElementDescriptor.resize( strideElementsCount, &allocator );	
		for (unsigned int i = 0; i < strideElementsCount; ++i)
			fragmentHeader.vertexElementDescriptor[i] = desc[i];

		/// 
		fragmentHeader.vertexStrideSizeInBytes = strideSize;
		fragmentHeader.baseVertexIndex = vboffset;
		fragmentHeader.minIndex = 0;
		fragmentHeader.numVertices = fragmentsVB[fragmentNumber].size();
		fragmentHeader.startIndex = iboffset;
		fragmentHeader.primitiveCount = fragmentsIB[fragmentNumber].size() / VERTEX_PER_TRIANGLE;
		fragmentHeader.materialID = fragmentNumber;
		fragmentHeader.streamOffset = 0;
		/// 
    vboffset += fragmentsVB[fragmentNumber].size();
    iboffset += fragmentsIB[fragmentNumber].size();

#ifdef MERGE_EQUAL_VERTICES
		// there's a modified copy of index buffer at the second half [10/4/2010 paul.smirnov]
		fragmentHeader.primitiveCount /= 2;
		// fragmentHeader.startIndex += fragmentsIB[fragmentNumber].size() / 2;
#endif // MERGE_EQUAL_VERTICES
	}

	pH6GeometryFileHeader->commonIndexBufferSizeInBytes = sizeof(unsigned int) * iboffset;
	pH6GeometryFileHeader->commonVertexBufferSizeInBytes = strideSize * vboffset;
	/// 
	allocator.Normalize(16);
	pH6GeometryFileHeader->vbOffset = allocator.GetSize();
	pH6GeometryFileHeader->ibOffset = pH6GeometryFileHeader->vbOffset + pH6GeometryFileHeader->commonVertexBufferSizeInBytes;
	pH6GeometryFileHeader->reindexOffset = 0;
	///

	h6FileStream.Write( allocator.GetData(), allocator.GetSize() );

	ASSERT( h6FileStream.GetPosition() == (int)pH6GeometryFileHeader->vbOffset );

	InitAABB( pAABBs[0] );
	for (unsigned int fragmentNumber = 0; fragmentNumber < subMeshCount; ++fragmentNumber)
	{
    nstl::vector<VERTEX>& fragVertices = fragmentsVB[fragmentNumber];

		InitAABB( pAABBs[fragmentNumber + 1] );
		for (int i = 0, n = fragVertices.size(); i < n; i++)
		{
			//float disp = 
			//if( materials && materials[fragmentNumber] == 0x1054B340 /*NDb::TreeLeavesMaterial::typeId*/ )
			//	WritePosition( h6FileStream, centers[fragmentNumber][*it].center );
			//else
			WritePosition(h6FileStream, fragVertices[i].position);

			AddVertex2AABB( pAABBs[fragmentNumber + 1], fragVertices[i].position );

			WriteTBN( h6FileStream, fragVertices[i], (bool)_ConvertTagentAndBinormal );

      for (int k = 0; k < _ConvertColors; ++k)
	    {
		    unsigned int c = GetColor(fragVertices[i]);
        h6FileStream.Write(&c, 4);
	    }

			CVec2 uv = fragVertices[i].texcoord[0];
			uv.y *= -1.f;
			h6FileStream.Write( &uv, 8 );
			if(_UVChannels == 2)
			{
				uv = fragVertices[i].texcoord[1];
				uv.y *= -1.f;
				h6FileStream.Write( &uv, 8 );
			}
		}
		AddAABB2AABB( pAABBs[0], pAABBs[fragmentNumber + 1] );
	}

	ASSERT( h6FileStream.GetPosition() == (int)pH6GeometryFileHeader->ibOffset );

	for (unsigned int fragmentNumber = 0; fragmentNumber < subMeshCount; ++fragmentNumber)
	{
    nstl::vector<unsigned int>& fragIndices = fragmentsIB[fragmentNumber];
    h6FileStream.Write( &fragIndices[0], fragIndices.size()*4 ); 
	}

	ASSERT( h6FileStream.GetPosition() == (int)(pH6GeometryFileHeader->ibOffset + pH6GeometryFileHeader->commonIndexBufferSizeInBytes) );

	//systemLog( NLogg::LEVEL_MESSAGE ) << "looks like everything ok!" << endl;

	int currentSize = h6FileStream.GetPosition();
	const int fileSizeAlignment = 1024;
	int wantedSize = currentSize + (fileSizeAlignment - (currentSize & ( fileSizeAlignment - 1 )) );
	systemLog( NLogg::LEVEL_MESSAGE ) << "File size " << wantedSize/1024 << " KB" << endl;
	systemLog( NLogg::LEVEL_MESSAGE ) << "Export completed" << endl;
	h6FileStream.SetSize( wantedSize );

	*h6FileActualLength = wantedSize <= h6BufferSize ? wantedSize : -1;

	return subMeshCount;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall ConvertStaticMeshGeometry( const void* mayaFileData, int mayaFileDataSize, void* h6FileBuffer, int h6BufferSize, int* h6FileActualLength,
	unsigned int _ConvertTagentAndBinormal, int _ConvertColors, unsigned char _UVChannels, NDb::AABB* pAABBs )
{
	const unsigned char* pMayaBuffer = reinterpret_cast<const unsigned char*>( mayaFileData );
	const MayaStaticMeshFileHeader* pMayaHeader = reinterpret_cast<const MayaStaticMeshFileHeader*>(pMayaBuffer);

	if (pMayaHeader->signature == Signs::statSIGNOld)
	{
		return ConvertStaticMeshGeometryTemplate<MayaVertexStrideStaticOld>(pMayaBuffer, mayaFileDataSize, h6FileBuffer, h6BufferSize, h6FileActualLength, 
			_ConvertTagentAndBinormal, _ConvertColors, _UVChannels, pAABBs);
	}
	else if (pMayaHeader->signature == Signs::statSIGN)
	{
		return ConvertStaticMeshGeometryTemplate<MayaVertexStrideStatic>(pMayaBuffer, mayaFileDataSize, h6FileBuffer, h6BufferSize, h6FileActualLength, 
			_ConvertTagentAndBinormal, _ConvertColors, _UVChannels, pAABBs);
	}
	else
	{
    //systemLog( NLogg::LEVEL_MESSAGE ) << "invalid static mesh file sign..." << endl;
		NI_ALWAYS_ASSERT("invalid static mesh file sign");
		return -1;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall ConvertCollisionGeometry( const void* mayaFileData
																			 , int mayaFileDataSize
																			 , void* geometryFileBuffer
																			 , int geometryBufferSize
																			 , int* geometryFileActualLength )
{
	const unsigned char* pMayaBuffer = reinterpret_cast<const unsigned char*>( mayaFileData );
	FixedMemoryStream geometryFileStream( geometryFileBuffer, geometryBufferSize );

	const MayaStaticMeshFileHeader* pMayaHeader = reinterpret_cast<const MayaStaticMeshFileHeader*>( pMayaBuffer );
	const MayaVertexStrideStatic* pStaticVertex = reinterpret_cast<const MayaVertexStrideStatic*>( pMayaHeader + 1 );
	const MayaIndexHeader* pMayaStaticIndexHeader = reinterpret_cast<const MayaIndexHeader*>( pStaticVertex + pMayaHeader->vertexCount );
	const MayaIndexBufferHeader* pIndexBufferHeader = reinterpret_cast<const MayaIndexBufferHeader*>( pMayaStaticIndexHeader + 1 );

	const unsigned int indexCount = pIndexBufferHeader->triangleCount * VERTEX_PER_TRIANGLE;

	int newIndex = 0;
	nstl::hash_map<unsigned int, unsigned int> indicesMap;
	for ( unsigned int indexNumber = 0; indexNumber < indexCount; ++indexNumber )
	{
		unsigned int* pIndex = ((unsigned int*)( pIndexBufferHeader+1 )) + indexNumber;
		if ( indicesMap.find( *pIndex ) == indicesMap.end() )
			indicesMap[*pIndex] = newIndex++;
	}

	nstl::vector<CVec3> points;
	points.resize( newIndex );
	for ( nstl::hash_map<unsigned int, unsigned int>::const_iterator it = indicesMap.begin(); it != indicesMap.end(); ++it )
		points[it->second] = pStaticVertex[it->first].position;

	nstl::vector<NScene::CollisionGeometry::Triangle> triangles;
	triangles.reserve( indexCount / VERTEX_PER_TRIANGLE );
	for ( unsigned int indexNumber = 0; indexNumber < indexCount; indexNumber += 3 )
	{
		unsigned int* pIndex = ((unsigned int*)( pIndexBufferHeader+1 )) + indexNumber;
		triangles.push_back( NScene::CollisionGeometry::Triangle( indicesMap[*pIndex], indicesMap[*(pIndex+1)], indicesMap[*(pIndex+2)] ) );
	}

	NScene::CollisionGeometry geometry;
	geometry.Create( points, triangles );

	CObj<IBinSaver> pSaver = CreateWriteBinSaver( &geometryFileStream, 0, false );
	geometry&( *pSaver );
	pSaver = 0;

	*geometryFileActualLength = geometryFileStream.GetPosition();

	return 0;
}
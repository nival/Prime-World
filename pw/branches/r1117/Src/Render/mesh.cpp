#include "stdafx.h"
#include "mesh.h"
#include "renderresourcemanager.h"

#include "smartrenderer.h"

#include "../MeshConverter/MeshHeader.h"

namespace Render
{
struct StaticMeshFileHeader
{
	int signature;
	unsigned int vertexCount;
	unsigned int uvSetsCount;
	unsigned int bonesPerVertex;
};

/*
// вер, инд
struct StaticMeshVertex
{
	float posX;
	float posY;
	float posZ;

	float normalX;
	float normalY;
	float normalZ;

	float tangentX;
	float tangentY;
	float tangentZ;

	float binormalX;
	float binormalY;
	float binormalZ;

	float texccordU;
	float texccordV;
};
*/
//void Mesh::Draw()
//{
//	for (int i = 0; i < subMeshes.size(); ++i )
//	{
//		subMeshes[i]->Bind();
//		subMeshes[i]->Draw(); // FIXME!
//	}
//}

void Mesh::LoadFromFile(const nstl::string& file)
{
	//NVFS::IVFS* fs = NVFS::GetMainVFS();

	//CDataStream* stream = fs->OpenFile(file);

//	FILE* stream = fopen(file.c_str(), "rb");
//
//	fseek(stream, 0, SEEK_END);
//
//	fpos_t pos;
//	fgetpos(stream, &pos);
//
//	fseek(stream, 0, SEEK_SET);
//
//	unsigned int size = pos;//stream->GetSize();
//	unsigned char* data = new unsigned char [size];//stream->GetBuffer();
//	fread( reinterpret_cast<void*>(data), size, 1, stream );
//
//	const StaticMeshFileHeader* header = reinterpret_cast<const StaticMeshFileHeader*>(data);
//	const unsigned int bonesPerVertex = header->bonesPerVertex;
//
//	unsigned int vertexSizeInFile = 12 + 36 + header->uvSetsCount * 8 + header->bonesPerVertex * 8;
//	unsigned int vertexDataSize = header->vertexCount * vertexSizeInFile;
//	unsigned int vertexCount = header->vertexCount;
//
//	//nstl::vector<StaticMeshVertex> vertexBufferData;
//	nstl::vector< float > vertexBufferData;
//	unsigned int vertexSizeInVBInFloats = (3 + 9 + 2 + /*header->bonesPerVertex * 2*/5);
//	vertexBufferData.resize( vertexCount * vertexSizeInVBInFloats );
//
//	for (unsigned int i = 0; i < vertexCount; ++i)
//	{
//		const unsigned char* pCurrentVertex = &data[sizeof(StaticMeshFileHeader) + i * vertexSizeInFile];
//
////		StaticMeshVertex vertex;
//
//		// position
//		vertexBufferData[i * vertexSizeInVBInFloats + 0] = *reinterpret_cast<const float*>(&pCurrentVertex[0 * sizeof(float)]);
//		vertexBufferData[i * vertexSizeInVBInFloats + 1] = *reinterpret_cast<const float*>(&pCurrentVertex[1 * sizeof(float)]);
//		vertexBufferData[i * vertexSizeInVBInFloats + 2] = *reinterpret_cast<const float*>(&pCurrentVertex[2 * sizeof(float)]);
//
//		// normal
//		vertexBufferData[i * vertexSizeInVBInFloats + 3] = *reinterpret_cast<const float*>(&pCurrentVertex[3 * sizeof(float)]);
//		vertexBufferData[i * vertexSizeInVBInFloats + 4] = *reinterpret_cast<const float*>(&pCurrentVertex[4 * sizeof(float)]);
//		vertexBufferData[i * vertexSizeInVBInFloats + 5] = *reinterpret_cast<const float*>(&pCurrentVertex[5 * sizeof(float)]);
//
//		// tangent
//		vertexBufferData[i * vertexSizeInVBInFloats + 6] = *reinterpret_cast<const float*>(&pCurrentVertex[6 * sizeof(float)]);
//		vertexBufferData[i * vertexSizeInVBInFloats + 7] = *reinterpret_cast<const float*>(&pCurrentVertex[7 * sizeof(float)]);
//		vertexBufferData[i * vertexSizeInVBInFloats + 8] = *reinterpret_cast<const float*>(&pCurrentVertex[8 * sizeof(float)]);
//
//		// binormal
//		vertexBufferData[i * vertexSizeInVBInFloats + 9] = *reinterpret_cast<const float*>(&pCurrentVertex[9 * sizeof(float)]);
//		vertexBufferData[i * vertexSizeInVBInFloats + 10] = *reinterpret_cast<const float*>(&pCurrentVertex[10 * sizeof(float)]);
//		vertexBufferData[i * vertexSizeInVBInFloats + 11] = *reinterpret_cast<const float*>(&pCurrentVertex[11 * sizeof(float)]);
//
//		// texcoord
//		vertexBufferData[i * vertexSizeInVBInFloats + 12] = *reinterpret_cast<const float*>(&pCurrentVertex[12 * sizeof(float)]);
//		vertexBufferData[i * vertexSizeInVBInFloats + 13] = 1 - *reinterpret_cast<const float*>(&pCurrentVertex[13 * sizeof(float)]);
//
//		// 4 weights
//		float totalWeightVal = 0;
//		for ( unsigned int j = 0; j < 4; j++)
//		{
//			float weight = *reinterpret_cast<const float*>(&pCurrentVertex[(14 + j) * sizeof(float)]);
//			if ( j < header->bonesPerVertex )	
//			{
//				vertexBufferData[i * vertexSizeInVBInFloats + 14 + j] = weight;
//				totalWeightVal += weight;
//			}
//			else vertexBufferData[i * vertexSizeInVBInFloats + 14 + j] = 0;
//		}
//
//		NI_ASSERT(fabs(totalWeightVal - 1.0f) < 0.01f, "Invalid weights summ != 0 ");
//
//		// 4 indices
//		float ind = 0;
//		unsigned char* pInd = reinterpret_cast< unsigned char* >(&ind);
//		for ( unsigned int j = 0; j < header->bonesPerVertex; j++)
//		{
//			unsigned int indVal = *reinterpret_cast<const unsigned int*>(&pCurrentVertex[ ( (14 + j + header->bonesPerVertex) * sizeof(float) ) ]);
//			pInd[j] = static_cast< unsigned char >(indVal);
//		}
//		for ( unsigned int j = header->bonesPerVertex; j < 4; j++) pInd[j] = 0;
//		vertexBufferData[i * vertexSizeInVBInFloats + 14 + 4] = ind;
//
///*
//		vertex.posX = *reinterpret_cast<const float*>(&pCurrentVertex[0 * sizeof(float)]);
//		vertex.posY = *reinterpret_cast<const float*>(&pCurrentVertex[1 * sizeof(float)]);
//		vertex.posZ = *reinterpret_cast<const float*>(&pCurrentVertex[2 * sizeof(float)]);
//
//		vertex.normalX = *reinterpret_cast<const float*>(&pCurrentVertex[3 * sizeof(float)]);
//		vertex.normalY = *reinterpret_cast<const float*>(&pCurrentVertex[4 * sizeof(float)]);
//		vertex.normalZ = *reinterpret_cast<const float*>(&pCurrentVertex[5 * sizeof(float)]);
//
//		vertex.tangentX = *reinterpret_cast<const float*>(&pCurrentVertex[6 * sizeof(float)]);
//		vertex.tangentY = *reinterpret_cast<const float*>(&pCurrentVertex[7 * sizeof(float)]);
//		vertex.tangentZ = *reinterpret_cast<const float*>(&pCurrentVertex[8 * sizeof(float)]);
//
//		vertex.binormalX = *reinterpret_cast<const float*>(&pCurrentVertex[9 * sizeof(float)]);
//		vertex.binormalY = *reinterpret_cast<const float*>(&pCurrentVertex[10 * sizeof(float)]);
//		vertex.binormalZ = *reinterpret_cast<const float*>(&pCurrentVertex[11 * sizeof(float)]);
//
//		vertex.texccordU = *reinterpret_cast<const float*>(&pCurrentVertex[12 * sizeof(float)]);
//		vertex.texccordV = 1 - *reinterpret_cast<const float*>(&pCurrentVertex[13 * sizeof(float)]);
//
//		vertexBufferData.push_back(vertex);*/
//	}
//
//	const unsigned char* currentPos = &data[sizeof(StaticMeshFileHeader) + vertexCount * vertexSizeInFile];
//	const unsigned int subMeshesCount = *reinterpret_cast<const unsigned int*>(currentPos);
//	currentPos += sizeof(unsigned int); 
//
//	nstl::vector< nstl::vector<unsigned int> > indexBuffersData;
//	nstl::vector< unsigned int > unicVertexCountsInSubmeshes;
//	indexBuffersData.resize(subMeshesCount);
//	unicVertexCountsInSubmeshes.resize(subMeshesCount);
//
//	for	(unsigned int subMeshIndex = 0; subMeshIndex < subMeshesCount; subMeshIndex++)
//	{
//		unsigned int indexesCountInSubMesh = *reinterpret_cast<const unsigned int*>(currentPos) * 3;
//		currentPos += sizeof(unsigned int);
//
//		unicVertexCountsInSubmeshes[subMeshIndex] = *reinterpret_cast<const unsigned int*>(currentPos);
//		currentPos += sizeof(unsigned int);
//
//		indexBuffersData[subMeshIndex].reserve(indexesCountInSubMesh);
//
//		for (unsigned int currentIndexNumber = 0; currentIndexNumber < indexesCountInSubMesh; currentIndexNumber++)
//		{
//			indexBuffersData[subMeshIndex].push_back(*reinterpret_cast<const unsigned int*>(currentPos));
//			currentPos += sizeof(unsigned int);
//		}
//	}
//
//	delete[] data;
//
//	unsigned int vertexBufferSizeInBytes = vertexSizeInVBInFloats * sizeof(float) * vertexCount;
//	IVertexBuffer* vertexBuffer = RenderResourceManager::CreateVertexBuffer(vertexBufferSizeInBytes, RENDER_POOL_MANAGED);
//
//	unsigned char* vbLockData = vertexBuffer->Lock(0, vertexBufferSizeInBytes, LOCK_DEFAULT);
//	memcpy(vbLockData, &vertexBufferData[0], vertexBufferSizeInBytes);	
//	vertexBuffer->Unlock();
//
//	for (unsigned int i = 0; i < subMeshesCount; i++)
//	{
//		SubMesh* subMesh = new SubMesh;
//
//		unsigned int indexBufferSizeInBytes = indexBuffersData[i].size() * sizeof(unsigned int);
//
//		IIndexBuffer* indexBuffer = RenderResourceManager::CreateIndexBuffer(indexBufferSizeInBytes, RENDER_POOL_MANAGED);
//
//		unsigned char* ibLockData = indexBuffer->Lock(0, indexBufferSizeInBytes, LOCK_DEFAULT);
//		memcpy(ibLockData, &indexBuffersData[i][0], indexBufferSizeInBytes);
//		indexBuffer->Unlock();
//
//		subMesh->SetIndexBuffer(indexBuffer);
//		subMesh->AddVertexBuffer(vertexBuffer);
//
//		DipDescriptor dipDescr;
//		dipDescr.AddVertexStreamDescriptor( VertexStreamDescriptor(0, 56 + 5 * 4) );
//
//		VertexFormatDescriptor formatDescriptor;
//		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0,	VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_POSITION, 0) );
//		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 12, VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_NORMAL,	 0) );
//		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 24, VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_TANGENT,	0) );
//		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 36, VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_BINORMAL, 0) );
//		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 48, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_TEXCOORD, 0) );
//		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 56, VERTEXELEMENTTYPE_FLOAT4, VERETEXELEMENTUSAGE_BLENDWEIGHT, 0) );
//		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 72, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_BLENDINDICES, 0) );
//
//		dipDescr.pVertexFormatDeclaration = SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);
//
//		dipDescr.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
//		dipDescr.baseVertexIndex = 0;
//		dipDescr.startIndex = 0;
//		dipDescr.numVertices = unicVertexCountsInSubmeshes[i];
//		dipDescr.primitiveCount = indexBuffersData[i].size() / 3;
//
//		subMesh->SetDipDescriptor(dipDescr);
//		subMeshes.push_back(subMesh);
//	}
//
//// delete stream;
//	fclose(stream);

	//DWORD start = GetTickCount();
	//systemLog( NLogg::LEVEL_DEBUG ) << "************************* before" << start << endl;
	nstl::string _filename = file + ".bin";
	FILE* stream = 0;
	if( fopen_s( &stream, _filename.c_str(), "rb" ) )
	{
		NI_ALWAYS_ASSERT("can't load bin file");
	}
	fseek( stream, 0, SEEK_SET );
	H6StaticMeshFileHeader fileHeader;
	fread( &fileHeader, sizeof(H6StaticMeshFileHeader), 1, stream );
	nstl::vector<H6StaticMeshFragmentHeader> fragments;
	fragments.resize(fileHeader.fragmentCount);
	fread( &fragments[0], sizeof(H6StaticMeshFragmentHeader), fileHeader.fragmentCount, stream );

	nstl::vector<VertexElementDescriptor> elementDescriptors;
	elementDescriptors.resize(fragments[0].vertexElementCount);
	fread(&elementDescriptors[0], sizeof(VertexElementDescriptor), 7, stream );

	const int vbsize = fileHeader.commonVertexBufferSizeInBytes;
	IVertexBuffer* vertexBuffer = RenderResourceManager::CreateVertexBuffer( vbsize, RENDER_POOL_MANAGED );
	void* vbLockData = vertexBuffer->Lock( 0, vbsize, LOCK_DEFAULT );
	fread(vbLockData, 1, vbsize, stream );
	vertexBuffer->Unlock();

	const int ibsize = fileHeader.commonIndexBufferSizeInBytes;
	IIndexBuffer* indexBuffer = RenderResourceManager::CreateIndexBuffer( ibsize, RENDER_POOL_MANAGED );
	void* ibLockData = indexBuffer->Lock( 0, ibsize, LOCK_DEFAULT );
	fread(ibLockData, sizeof(unsigned __int32), fileHeader.commonIndexCount, stream );
	indexBuffer->Unlock();

	DipDescriptor dipDescr;
	dipDescr.AddVertexStreamDescriptor( VertexStreamDescriptor(0, fragments[0].vertexStrideSizeInBytes) );
	VertexFormatDescriptor formatDescriptor;
	formatDescriptor.AssignVertexElements( elementDescriptors[0], fragments[0].vertexElementCount );
	dipDescr.pVertexFormatDeclaration = SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);
	dipDescr.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
	dipDescr.baseVertexIndex = 0;
	int counter = 0;
	for(unsigned int i = 0; i < fileHeader.fragmentCount; ++i)
	{
		SubMesh* subMesh = new SubMesh;
		subMesh->SetIndexBuffer(indexBuffer);
		subMesh->AddVertexBuffer(vertexBuffer);
		

		dipDescr.numVertices = fragments[i].numVertices;
		dipDescr.primitiveCount = fragments[i].indexCount / 3;
		
		dipDescr.startIndex = fragments[i].firstIndexNumber;
		subMesh->SetDipDescriptor(dipDescr);
		counter += fragments[i].indexCount;

		subMeshes.push_back(subMesh);
	}
	fclose(stream);
	//systemLog( NLogg::LEVEL_DEBUG ) << "************************* after" << (GetTickCount() - start) << endl;

}
}; // namespace Render
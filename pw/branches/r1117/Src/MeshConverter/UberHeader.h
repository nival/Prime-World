#pragma once

static const unsigned __int32 VERTEX_PER_TRIANGLE = 3;
static const int MAX_BONE_NAME_LENGTH = 1024;
static const int MAX_FILE_NAME_LENGTH = 1024;
static const int UV_SET_SIZE = 8;
static const int POSITION_SIZE = 12;
static const int NORMAL_SIZE = 12;
static const int TB_SIZE = 24;
static const int FOUR_JOINT_INDEX = 4;
static const int FOUR_JOINT_WEIGHT = 16;

static const float floatnull = 0.f;
static const float epsilonPosition = (float)1e-7;
static const float epsilonNormal = (float)1e-30;
//////////////////////////////////////////////////////////////////////////
struct MayaTriangle
{
	unsigned int a, b, c;
};
//////////////////////////////////////////////////////////////////////////
struct MayaTriangleWeight
{
	float weightSum;
	unsigned short jointID;
	unsigned short triangleID;
};
//////////////////////////////////////////////////////////////////////////
__declspec(align(16)) struct TriangleJoints
{
	TriangleJoints() : jointCount(0) { }
	unsigned short jointsID[12];
	unsigned char jointCount;
};
//////////////////////////////////////////////////////////////////////////
struct JointIndexPair
{
	unsigned short original;
	unsigned short ordered;
	JointIndexPair(unsigned short _original,	unsigned short _ordered)
	{
		original = _original;
		ordered = _ordered;
	}
	//////////////////////////////////////////////////////////////////////////
	JointIndexPair()
	{
		original = 0;
		ordered = 0;
	}

};
//////////////////////////////////////////////////////////////////////////
int BuildMayaTrianglesList(const nstl::vector<unsigned short>& jointList
																	, nstl::set<unsigned int>& triangleList
																	, const nstl::vector<MayaTriangle>& mayaTriangles
																	, const MayaVertexStrideSkeletal* pSkeletalVertexStride
																	, unsigned char jointsPerVertex )
{
	for (nstl::vector<unsigned short>::const_iterator it = jointList.begin(); it != jointList.end(); ++it)
	{
		//const nstl::hash_map<unsigned short, unsigned short>& triangles = jointTriangles[*it];
		unsigned int currentJointValue = *it;

		for( int triangleNumber = 0; triangleNumber < mayaTriangles.size(); ++triangleNumber )
		{
			//const TriangleJoints& tj = triangleJoints[materialNumber][triangleID->first];
			//for (int j = 0; j < tj.jointCount; ++j)
			//{
			//	branch[ tj.jointsID[j] ] = 0;
			//}
			const MayaTriangle& triangle = mayaTriangles[triangleNumber];
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

			triangleList.insert(triangleNumber);


		}



	}
	return triangleList.size();
}

bool CompareOrdered( const JointIndexPair& left, const JointIndexPair& right)
{
	return left.ordered < right.ordered;
}

//////////////////////////////////////////////////////////////////////////
void PushChilds( nstl::vector<unsigned short>& jointTree, unsigned short jointID, const StaticVector<unsigned int>& parentID)
{
	int oldSize = jointTree.size();

	for(unsigned int i = 0; i < parentID.size(); ++i)
	{
		if( parentID[i] == jointID )
		{
			jointTree.push_back((unsigned short)i);
		}
	}

	//int childCount = jointTree.size() - oldSize;
	int currentSize = jointTree.size();
	for(int i = oldSize; i < currentSize; i++)
	{
		PushChilds(jointTree, jointTree[i], parentID);
	}
}

//////////////////////////////////////////////////////////////////////////
unsigned __int32 MakeColor(CVec4 const &mayaColor)
{
	Render::Color c = Render::Color((unsigned char)(mayaColor.r * 255.0f), (unsigned char)(mayaColor.g * 255.0f), 
																	(unsigned char)(mayaColor.b * 255.0f), (unsigned char)(mayaColor.a * 255.0f));
	return c.Dummy;
}

//////////////////////////////////////////////////////////////////////////

float WritePosition( Stream &h6FileStream, const CVec3& vertex )
{
	h6FileStream.Write( abs(vertex.x) < epsilonPosition ? &floatnull : &vertex.x, 4 );
	h6FileStream.Write( abs(vertex.y) < epsilonPosition ? &floatnull : &vertex.y, 4 );
	h6FileStream.Write( abs(vertex.z) < epsilonPosition ? &floatnull : &vertex.z, 4 );
	return  vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float WritePosition( Stream &h6FileStream, const MayaVertexStrideSkeletal& pVertex )
{
	h6FileStream.Write( abs(pVertex.position.x) < epsilonPosition ? &floatnull : &pVertex.position.x, 4 );
	h6FileStream.Write( abs(pVertex.position.y) < epsilonPosition ? &floatnull : &pVertex.position.y, 4 );
	h6FileStream.Write( abs(pVertex.position.z) < epsilonPosition ? &floatnull : &pVertex.position.z, 4 );
	float disp_squared = pVertex.position.x*pVertex.position.x
		+pVertex.position.y*pVertex.position.y
		+pVertex.position.z*pVertex.position.z;
	return disp_squared;
}
//////////////////////////////////////////////////////////////////////////
float WritePosition( H6SkeletalMeshVertexStride& stride, const MayaVertexStrideSkeletal& vertex )
{

	// 	h6FileStream.Write( abs(pVertex.position.x) < epsilonPosition ? &floatnull : &pVertex.position.x, 4 );
	// 	h6FileStream.Write( abs(pVertex.position.y) < epsilonPosition ? &floatnull : &pVertex.position.y, 4 );
	// 	h6FileStream.Write( abs(pVertex.position.z) < epsilonPosition ? &floatnull : &pVertex.position.z, 4 );
	// 	float disp_squared = pVertex.position.x*pVertex.position.x
	// 		+pVertex.position.y*pVertex.position.y
	// 		+pVertex.position.z*pVertex.position.z;
	// 	return disp_squared;
	stride.position = vertex.position;
	return -1;
}
//////////////////////////////////////////////////////////////////////////
float WriteUVSet( H6SkeletalMeshVertexStride& stride, const MayaVertexStrideSkeletal& vertex )
{
	for(unsigned char i = 0; i < 4; ++i)
	{
		stride.texcoord[i].u = vertex.texcoord[i].u;
		stride.texcoord[i].v = vertex.texcoord[i].v;
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////
float WriteJW( H6SkeletalMeshVertexStride& stride, const MayaVertexStrideSkeletal& vertex,
							unsigned char jointsPerVertex, nstl::hash_map<unsigned short, unsigned short>& oldNewJointIndices
							, unsigned int& normalizedCounter )
{
	//
	//stride.weights[0] = 1.f;
	//stride.indices[0] = vertex.indices[0];

	//for(unsigned char i = 1; i < 8; ++i)
	//{
	//	stride.weights[i] = 0;
	//	stride.indices[i] = 0;
	//}
	//return 0;
	//reindex
	float weighSum = 0;
	for(unsigned char i = 0; i < jointsPerVertex; ++i)
	{
		if(vertex.weights[i] > 0)
		{
			stride.weights[i] = vertex.weights[i];
			weighSum += stride.weights[i]; 
			ASSERT( oldNewJointIndices.find( vertex.indices[i]) != oldNewJointIndices.end() );
			stride.indices[i] = oldNewJointIndices[ vertex.indices[i] ];
		}
		else
		{
			stride.weights[i] = 0;
			stride.indices[i] = 0;
		}
	}
	for(unsigned char i = jointsPerVertex; i < 8; ++i)
	{
		stride.weights[i] = 0;
		stride.indices[i] = 0;
	}
	ASSERT(weighSum > 0.f);
	ASSERT(weighSum < 1.1f);
	if( (1.f - weighSum) > 0.0001f )
	{
		++normalizedCounter;
		//DebugTrace( "old: %.4f : %.4f %.4f %.4f %.4f ", weighSum, stride.weights[0], stride.weights[1], stride.weights[2], stride.weights[3] );
		float normalizedWeighSum = 0;
		for(unsigned char i = 0; i < jointsPerVertex; ++i)
		{
			stride.weights[i] /= weighSum;
			normalizedWeighSum += stride.weights[i]; 
		}
		//DebugTrace( "new: %.4f : %.4f %.4f %.4f %.4f ", normalizedWeighSum, stride.weights[0], stride.weights[1], stride.weights[2], stride.weights[3] );
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////

void WriteTBN( H6SkeletalMeshVertexStride& stride, const MayaVertexStrideSkeletal& vertex )
{
	////tangent
	//h6FileStream.Write( abs(pVertex.tangent.x) < epsilonNormal ? &floatnull : &pVertex.tangent.x, 4 );
	//h6FileStream.Write( abs(pVertex.tangent.y) < epsilonNormal ? &floatnull : &pVertex.tangent.y, 4 );
	//h6FileStream.Write( abs(pVertex.tangent.z) < epsilonNormal ? &floatnull : &pVertex.tangent.z, 4 );

	////binormal
	//h6FileStream.Write( abs(pVertex.binormal.x) < epsilonNormal ? &floatnull : &pVertex.binormal.x, 4 );
	//h6FileStream.Write( abs(pVertex.binormal.y) < epsilonNormal ? &floatnull : &pVertex.binormal.y, 4 );
	//h6FileStream.Write( abs(pVertex.binormal.z) < epsilonNormal ? &floatnull : &pVertex.binormal.z, 4 );

	////normal
	//h6FileStream.Write( abs(pVertex.normal.x) < epsilonNormal ? &floatnull : &pVertex.normal.x, 4 );
	//h6FileStream.Write( abs(pVertex.normal.y) < epsilonNormal ? &floatnull : &pVertex.normal.y, 4 );
	//h6FileStream.Write( abs(pVertex.normal.z) < epsilonNormal ? &floatnull : &pVertex.normal.z, 4 );
	stride.tangent = vertex.tangent;
	stride.binormal = vertex.binormal;
	stride.normal = vertex.normal;
}
//////////////////////////////////////////////////////////////////////////

template <typename VERTEX>
void WriteTBN( Stream &h6FileStream, const VERTEX& pVertex, bool writeTB )
{
	if (writeTB)
	{
		//tangent
		h6FileStream.Write( abs(pVertex.tangent.x) < epsilonNormal ? &floatnull : &pVertex.tangent.x, 4 );
		h6FileStream.Write( abs(pVertex.tangent.y) < epsilonNormal ? &floatnull : &pVertex.tangent.y, 4 );
		h6FileStream.Write( abs(pVertex.tangent.z) < epsilonNormal ? &floatnull : &pVertex.tangent.z, 4 );

		//binormal
		h6FileStream.Write( abs(pVertex.binormal.x) < epsilonNormal ? &floatnull : &pVertex.binormal.x, 4 );
		h6FileStream.Write( abs(pVertex.binormal.y) < epsilonNormal ? &floatnull : &pVertex.binormal.y, 4 );
		h6FileStream.Write( abs(pVertex.binormal.z) < epsilonNormal ? &floatnull : &pVertex.binormal.z, 4 );
	}

	//normal
	h6FileStream.Write( abs(pVertex.normal.x) < epsilonNormal ? &floatnull : &pVertex.normal.x, 4 );
	h6FileStream.Write( abs(pVertex.normal.y) < epsilonNormal ? &floatnull : &pVertex.normal.y, 4 );
	h6FileStream.Write( abs(pVertex.normal.z) < epsilonNormal ? &floatnull : &pVertex.normal.z, 4 );
}

//////////////////////////////////////////////////////////////////////////
//static void BuildVB( nstl::set)
static void BuildVBIB( const nstl::set<unsigned int>& triangleIndexList
											, const nstl::vector<MayaTriangle>& mayaTriangles
											, nstl::vector<H6SkeletalMeshVertexStride>& fragmentVB
											, nstl::vector<unsigned int>& fragmentIB
											, nstl::vector<unsigned short>& fragmentReindex
											, const MayaVertexStrideSkeletal* pSkeletalVertexStride
											, unsigned char jointPerVertex )
{

	nstl::set<unsigned short> usedJointIndex;
	for (nstl::set<unsigned int>::const_iterator it = triangleIndexList.begin(); it != triangleIndexList.end(); ++it)
	{
		const MayaTriangle& triangle = mayaTriangles[*it];
		for (int j = 0; j < jointPerVertex; ++j)
		{
			if(pSkeletalVertexStride[triangle.a].weights[j] > 0.f)
				usedJointIndex.insert(pSkeletalVertexStride[triangle.a].indices[j]);
			if(pSkeletalVertexStride[triangle.b].weights[j] > 0.f)
				usedJointIndex.insert(pSkeletalVertexStride[triangle.b].indices[j]);
			if(pSkeletalVertexStride[triangle.c].weights[j] > 0.f)
				usedJointIndex.insert(pSkeletalVertexStride[triangle.c].indices[j]);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//systemLog( NLogg::LEVEL_MESSAGE ) << "used uniq joints: " << usedJointIndex.size() << endl;
	for (nstl::set<unsigned short>::const_iterator it = usedJointIndex.begin(); it != usedJointIndex.end(); ++it)
		fragmentReindex.push_back(*it);

	nstl::hash_map<unsigned short, unsigned short> oldNewJointIndices;
	for (int j = 0; j < fragmentReindex.size(); ++j)
		oldNewJointIndices[fragmentReindex[j]] = j;

	//////////////////////////////////////////////////////////////////////////
	nstl::set<unsigned int> vertexIndexSet;
	for (nstl::set<unsigned int>::const_iterator it = triangleIndexList.begin(); it != triangleIndexList.end(); ++it)
	{
		vertexIndexSet.insert( mayaTriangles[*it].a );
		vertexIndexSet.insert( mayaTriangles[*it].b );
		vertexIndexSet.insert( mayaTriangles[*it].c );
	}
	nstl::hash_map<unsigned int, unsigned int> oldNewVertexIndices;
	unsigned int newIndex = 0;
	for (nstl::set<unsigned int>::const_iterator it = vertexIndexSet.begin(); it != vertexIndexSet.end(); ++it)
		oldNewVertexIndices.insert( pair<unsigned int, unsigned int>(*it, newIndex++) );




	for (nstl::set<unsigned int>::const_iterator it = triangleIndexList.begin(); it != triangleIndexList.end(); ++it)
	{
		fragmentIB.push_back( oldNewVertexIndices[ mayaTriangles[*it].a ] ); 
		fragmentIB.push_back( oldNewVertexIndices[ mayaTriangles[*it].b ] ); 
		fragmentIB.push_back( oldNewVertexIndices[ mayaTriangles[*it].c ] ); 
	}



	//systemLog( NLogg::LEVEL_MESSAGE ) << "vertex stride size: " << strideSize << " bytes" << endl;

	unsigned int normalizedCounter = 0;
	for (nstl::set<unsigned int>::const_iterator it = vertexIndexSet.begin(); it != vertexIndexSet.end(); ++it)
	{
		H6SkeletalMeshVertexStride& stride = fragmentVB.push_back();
		WritePosition( stride, pSkeletalVertexStride[*it] );
		WriteTBN( stride, pSkeletalVertexStride[*it] );
		WriteUVSet( stride, pSkeletalVertexStride[*it] );
		WriteJW( stride, pSkeletalVertexStride[*it], jointPerVertex, oldNewJointIndices, normalizedCounter );
		stride.color = MakeColor(pSkeletalVertexStride[*it].color);
	}

	//systemLog( NLogg::LEVEL_MESSAGE ) << "normalizedCounter: " << normalizedCounter << " vertices or " << normalizedCounter/(float)vertexIndexSet.size() << "%" << endl;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

float WritePosition( Stream &h6FileStream, const MayaVertexStrideStatic& pVertex )
{
	h6FileStream.Write( abs(pVertex.position.x) < epsilonPosition ? &floatnull : &pVertex.position.x, 4 );
	h6FileStream.Write( abs(pVertex.position.y) < epsilonPosition ? &floatnull : &pVertex.position.y, 4 );
	h6FileStream.Write( abs(pVertex.position.z) < epsilonPosition ? &floatnull : &pVertex.position.z, 4 );
	float disp_squared = pVertex.position.x*pVertex.position.x
		+pVertex.position.y*pVertex.position.y
		+pVertex.position.z*pVertex.position.z;
	return disp_squared;
}
//////////////////////////////////////////////////////////////////////////

void WriteTBN( Stream &h6FileStream, const MayaVertexStrideStatic& pVertex )
{
	//tangent
	//float flipped_y = -pVertex.tangent.y;
	h6FileStream.Write( abs(pVertex.tangent.x) < epsilonNormal ? &floatnull : &pVertex.tangent.x, 4 );
	h6FileStream.Write( abs(pVertex.tangent.y) < epsilonNormal ? &floatnull : &pVertex.tangent.y, 4 );
	h6FileStream.Write( abs(pVertex.tangent.z) < epsilonNormal ? &floatnull : &pVertex.tangent.z, 4 );

	//binormal
	//flipped_y = -pVertex.binormal.y;
	h6FileStream.Write( abs(pVertex.binormal.x) < epsilonNormal ? &floatnull : &pVertex.binormal.x, 4 );
	h6FileStream.Write( abs(pVertex.binormal.y) < epsilonNormal ? &floatnull : &pVertex.binormal.y, 4 );
	h6FileStream.Write( abs(pVertex.binormal.z) < epsilonNormal ? &floatnull : &pVertex.binormal.z, 4 );

	//normal
	//flipped_y = -pVertex.normal.y;
	h6FileStream.Write( abs(pVertex.normal.x) < epsilonNormal ? &floatnull : &pVertex.normal.x, 4 );
	h6FileStream.Write( abs(pVertex.normal.y) < epsilonNormal ? &floatnull : &pVertex.normal.y, 4 );
	h6FileStream.Write( abs(pVertex.normal.z) < epsilonNormal ? &floatnull : &pVertex.normal.z, 4 );
}

// CRAP {
template <typename VERTEX>
void PatchCenter( Stream &h6FileStream, const VERTEX& pVertex, const CVec3& center )
{
	// center (tangent)
	h6FileStream.Write( abs(center.x) < epsilonPosition ? &floatnull : &center.x, 4 );
	h6FileStream.Write( abs(center.y) < epsilonPosition ? &floatnull : &center.y, 4 );
	h6FileStream.Write( abs(center.z) < epsilonPosition ? &floatnull : &center.z, 4 );

	//binormal
	//flipped_y = -pVertex.binormal.y;
	h6FileStream.Write( abs(pVertex.binormal.x) < epsilonNormal ? &floatnull : &pVertex.binormal.x, 4 );
	h6FileStream.Write( abs(pVertex.binormal.y) < epsilonNormal ? &floatnull : &pVertex.binormal.y, 4 );
	h6FileStream.Write( abs(pVertex.binormal.z) < epsilonNormal ? &floatnull : &pVertex.binormal.z, 4 );

	//normal
	//flipped_y = -pVertex.normal.y;
	h6FileStream.Write( abs(pVertex.normal.x) < epsilonNormal ? &floatnull : &pVertex.normal.x, 4 );
	h6FileStream.Write( abs(pVertex.normal.y) < epsilonNormal ? &floatnull : &pVertex.normal.y, 4 );
	h6FileStream.Write( abs(pVertex.normal.z) < epsilonNormal ? &floatnull : &pVertex.normal.z, 4 );
}
// CRAP }
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
int WriteStaticMeshVertexBuffer( const MayaStaticMeshFileHeader* pMayaHeader
																, FileStream &h6FileStream
																, const MayaVertexStrideStatic* pVertex
																, const void* pMayaIndexHeader
																, unsigned int uvSetCount
																, const nstl::vector<unsigned int>& mayaUniqVertex
																, float* pAABB)
{
	unsigned int vertexIndex = 0;

	float maxDisp = 0;


	for (vertexIndex = 0; vertexIndex < pMayaHeader->vertexCount; ++vertexIndex)
	{
		float disp = WritePosition(h6FileStream, pVertex[vertexIndex] );
		//crap
		if(pVertex[vertexIndex].position.x < pAABB[0] )
				pAABB[0] = pVertex[vertexIndex].position.x;
		if(pVertex[vertexIndex].position.x > pAABB[1] )
			pAABB[1] = pVertex[vertexIndex].position.x;
		//
		if(pVertex[vertexIndex].position.y < pAABB[2] )
			pAABB[2] = pVertex[vertexIndex].position.y;
		if(pVertex[vertexIndex].position.y > pAABB[3] )
			pAABB[3] = pVertex[vertexIndex].position.y;
		//
		if(pVertex[vertexIndex].position.z < pAABB[4] )
			pAABB[4] = pVertex[vertexIndex].position.z;
		if(pVertex[vertexIndex].position.z > pAABB[5] )
			pAABB[5] = pVertex[vertexIndex].position.z;

		if(disp > maxDisp)
			maxDisp = disp;


		WriteTBN(h6FileStream, pVertex[vertexIndex]);
		h6FileStream.Write( &pVertex[vertexIndex].texcoord[0].x, 8*uvSetCount );
	}

	systemLog( NLogg::LEVEL_MESSAGE ) << "max squared displacement from origin: " << maxDisp << endl;

	return vertexIndex;
}


int WriteSkeletalMeshVertexBuffer( const MayaIndexBufferHeader** pIndexBufferHeaders
																	, unsigned int subMeshCount
																	, const MayaStaticMeshFileHeader* pMayaHeader
																	, FileStream &h6FileStream
																	, const MayaVertexStrideSkeletal* pVertex
																	, const void* pMayaIndexHeader
																	, nstl::vector< nstl::hash_map<unsigned short, unsigned short> >& submeshIndicesSorted 
																	, nstl::vector< nstl::hash_map<unsigned int, unsigned int> >& oldNewVertexIndices
																	, const nstl::vector<unsigned int>& mayaUniqVertexIndices
																	, unsigned char joinsPerVertex
																	, unsigned int mayaFullVertexCount)
{

	//unsigned int vertexIndex = 0;



	unsigned int actuallyCount = 0;
	unsigned int fullNormalizedCounter = 0;


	for (unsigned int i = 0; i < subMeshCount; ++i)
	{
		//newFragmentIndex[i].reserve(10000);
		unsigned int normalizedCounter = 0;
		nstl::set<unsigned int> handledIndex;
		float maxDisp = 0;
		unsigned int indexCount = pIndexBufferHeaders[i]->triangleCount*VERTEX_PER_TRIANGLE;
		systemLog( NLogg::LEVEL_MESSAGE ) << "writing fragment #" << i << " (index count = " << indexCount << ") ..." << endl;
		unsigned int newIndex = 0;
		unsigned int newIndexBase = actuallyCount;
		for (unsigned int indexNumber = 0; indexNumber < indexCount; ++indexNumber)
		{
			unsigned int vertexIndex = *(((unsigned int*)(pIndexBufferHeaders[i]+1))+indexNumber);
			//if (indexNumber < 10 || indexNumber > (indexCount-10) )
			//{
			//	systemLog( NLogg::LEVEL_MESSAGE ) << indexNumber << ": " << vertexIndex << endl;
			//}
			//////////////////////////////////////////////////////////////////////////
			nstl::set<unsigned int, less>::const_iterator it = handledIndex.find(vertexIndex);
			if( it != handledIndex.end() )
				continue;
			handledIndex.insert(vertexIndex);
			oldNewVertexIndices[i][vertexIndex] = newIndexBase + newIndex;
			++newIndex;
			//////////////////////////////////////////////////////////////////////////

			//position
			float disp = WritePosition(h6FileStream, pVertex[vertexIndex] );
			if(disp > maxDisp)
				maxDisp = disp;


			WriteTBN(h6FileStream, pVertex[vertexIndex]);


			//texcoord
			NI_VERIFY(pVertex[vertexIndex].texcoord[0].x <= 1.f, "tiling?", return -1 );
			NI_VERIFY(pVertex[vertexIndex].texcoord[0].y <= 1.f, "tiling?", return -1 );
			h6FileStream.Write( &pVertex[vertexIndex].texcoord[0].x, 8 );

			//bones weights

			//pVertex[vertexIndex].weights[0] + pVertex[vertexIndex].weights[1];

			NI_VERIFY(pVertex[vertexIndex].weights[0] <= 1.f, "weight should be less than 1", return -1 );
			NI_VERIFY(pVertex[vertexIndex].weights[1] <= 1.f, "weight should be less than 1", return -1 );
			NI_VERIFY(pVertex[vertexIndex].weights[2] <= 1.f, "weight should be less than 1", return -1 );
			NI_VERIFY(pVertex[vertexIndex].weights[3] <= 1.f, "weight should be less than 1", return -1 );

			float weight = 0;
			for (char k = 0; k < joinsPerVertex; ++k)
			{
				weight += pVertex[vertexIndex].weights[k];
			}


			bool bNeedNormilizeJointsWeight = false;

			if( abs( weight - 1.0000000f ) > 0.0001f )
			{
				//systemLog( NLogg::LEVEL_MESSAGE ) << "" << endl;
				//systemLog( NLogg::LEVEL_MESSAGE ) << "weights (" << joinsPerVertex << ":";
				//DebugTrace( "sum of weights should be near 1.f (%d:%.8f) : ", joinsPerVertex, weight );
				//for (char k = 0; k < 8; ++k )
				//{
				//	systemLog( NLogg::LEVEL_MESSAGE ) << pVertex[vertexIndex].weights[k] << " ";
				//	
				//}
				//systemLog( NLogg::LEVEL_MESSAGE ) << endl;

				bNeedNormilizeJointsWeight = true;
				++normalizedCounter;
			}

			if (!bNeedNormilizeJointsWeight)
			{
				for (unsigned int boneIndex = 0; boneIndex < 4; ++boneIndex)
				{
					h6FileStream.Write(&pVertex[vertexIndex].weights[boneIndex], 4);
				}
			}
			else
			{
				float fullnormalized = 0;
				for (unsigned int boneIndex = 0; boneIndex < joinsPerVertex; ++boneIndex)
				{
					float normalized = pVertex[vertexIndex].weights[boneIndex] / weight;
					fullnormalized += normalized;
					h6FileStream.Write(&normalized, 4);
				}
				for (unsigned int boneIndex = joinsPerVertex; boneIndex < 4; ++boneIndex)
				{
					float normalized = 0;
					//fullnormalized += normalized;
					h6FileStream.Write(&normalized, 4);
				}
				//DebugTrace( "fullnormalized : %.8f", fullnormalized);
			}

			//bones indices
			NI_VERIFY(pVertex[vertexIndex].indices[0] < 256, "index should be less than 256", return -1 );
			NI_VERIFY(pVertex[vertexIndex].indices[1] < 256, "index should be less than 256", return -1 );
			NI_VERIFY(pVertex[vertexIndex].indices[2] < 256, "index should be less than 256", return -1 );
			NI_VERIFY(pVertex[vertexIndex].indices[3] < 256, "index should be less than 256", return -1 );

			Render::Color color( submeshIndicesSorted[i][ pVertex[vertexIndex].indices[0] ]
			, submeshIndicesSorted[i][ pVertex[vertexIndex].indices[1] ]
			, submeshIndicesSorted[i][ pVertex[vertexIndex].indices[2] ]
			, submeshIndicesSorted[i][ pVertex[vertexIndex].indices[3] ]
			);
			h6FileStream.Write(&color.Dummy, 4);
			++actuallyCount;

		}

		//actuallyCount += handledIndex.size();
		NI_VERIFY( (int)mayaUniqVertexIndices[i] == handledIndex.size(), NStr::StrFmt( "count of uniq vertices in fragment #%d and vertices pointed by index buffer for this fragment is diffrent!", i), return -1 );
		systemLog( NLogg::LEVEL_MESSAGE ) << "actually has been written: " << handledIndex.size() << endl;
		systemLog( NLogg::LEVEL_MESSAGE ) << "normalized weights: " << normalizedCounter << "(" << normalizedCounter*100/(float)handledIndex.size() << "%)" <<  endl;
		systemLog( NLogg::LEVEL_MESSAGE ) << "vertex used in this fragment: " << mayaUniqVertexIndices[i] << endl;
		systemLog( NLogg::LEVEL_MESSAGE ) << "max squared displacement from origin: " << maxDisp << endl;
		fullNormalizedCounter += normalizedCounter;
	}

	//NI_VERIFY( (int*)(pVertex+vertexIndex) == (int*)pMayaIndexHeader, "something wrong", return -1 );
	//////////////////////////////////////////////////////////////////////////
	systemLog( NLogg::LEVEL_MESSAGE ) << "//////////////////////////////////////////////////////////////////////////"<< endl;
	systemLog( NLogg::LEVEL_MESSAGE ) << "full vertex count: " << actuallyCount << endl;
	systemLog( NLogg::LEVEL_MESSAGE ) << "full normalized weights: " << fullNormalizedCounter<< "(" << fullNormalizedCounter*100/(float)actuallyCount << "%)" <<  endl;
	NI_VERIFY(actuallyCount == mayaFullVertexCount, NStr::StrFmt( "maya claims %d, but IBs referenced for %d", mayaFullVertexCount, actuallyCount), return -1 );
	return actuallyCount;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WriteMeshHeader( const MayaStaticMeshFileHeader* pMayaHeader
										, unsigned int subMeshCount
										, unsigned int indexCount
										, unsigned int *firstIndex
										, const MayaIndexBufferHeader** pIndexBufferHeaders
										, FileStream &h6FileStream
										, unsigned int jointsCount
										, nstl::vector< nstl::set<unsigned short, less> > submeshIndices
										, unsigned int uvSetCount
										, nstl::vector<unsigned int>& uniqVertexIndices
										, unsigned int& fullVertexCount)
{
	NI_VERIFY( !(uvSetCount == 2 && jointsCount > 0 ), "doesn't support yet", return -1; );
	DummyAllocator allocator( 1024*1024 );
	H6GeometryFileHeader* pH6GeometryFileHeader = reinterpret_cast<H6GeometryFileHeader*>(allocator.Allocate(sizeof(H6GeometryFileHeader), 16));
	pH6GeometryFileHeader->signature = pMayaHeader->signature;
	pH6GeometryFileHeader->fragmentCount = subMeshCount;
	//pH6GeometryFileHeader->bUniformVertexFormat = 1; 
	//pH6GeometryFileHeader->commonVertexCount = pMayaHeader->vertexCount;
	fullVertexCount = pMayaHeader->vertexCount;

	const unsigned int vertexStrideSize = jointsCount ? sizeof(H6SkeletalMeshVertexStride) : (sizeof(H6StaticMeshVertexStride) + + (uvSetCount-1)*8);
	const unsigned int strideElementsCount = jointsCount ? (6+uvSetCount) : (4 + uvSetCount) ;
	pH6GeometryFileHeader->commonVertexBufferSizeInBytes = pMayaHeader->vertexCount * vertexStrideSize;

	systemLog( NLogg::LEVEL_MESSAGE ) << "header:" << "maya vertex count: " << pMayaHeader->vertexCount << endl;

	//pH6GeometryFileHeader->commonIndexCount = indexCount;
	pH6GeometryFileHeader->commonIndexBufferSizeInBytes = indexCount*4;

	systemLog( NLogg::LEVEL_MESSAGE ) << "header:" <<"maya index count: " << indexCount << endl;


	pH6GeometryFileHeader->fragments.resize(subMeshCount, &allocator);

	pH6GeometryFileHeader->jointsCount = jointsCount;

	//systemLog( NLogg::LEVEL_MESSAGE ) << "fragment #" << i << " uses " << submeshIndices[i].size() << " unique bones" << endl;

	for (unsigned int i = 0; i < subMeshCount; ++i)
	{
		pH6GeometryFileHeader->fragments[i].startIndex = firstIndex[i];
		//systemLog( NLogg::LEVEL_MESSAGE ) << "header:" << "fragment #" << i << " has first index = "<< firstIndex[i] << endl;
		pH6GeometryFileHeader->fragments[i].vertexStrideSizeInBytes = vertexStrideSize;
		NI_VERIFY(pIndexBufferHeaders[i]->unicVertexCountsInSubmeshes > 2, "vb/ib is null", return -1; )
			pH6GeometryFileHeader->fragments[i].numVertices = pIndexBufferHeaders[i]->unicVertexCountsInSubmeshes;
		//systemLog( NLogg::LEVEL_MESSAGE ) << "header:" << "fragment #" << i << " uses " << pIndexBufferHeaders[i]->unicVertexCountsInSubmeshes << " unique indices" << endl;
		uniqVertexIndices[i] = pIndexBufferHeaders[i]->unicVertexCountsInSubmeshes;
		pH6GeometryFileHeader->fragments[i].primitiveCount = pIndexBufferHeaders[i]->triangleCount;
		pH6GeometryFileHeader->fragments[i].vertexElementDescriptor.resize( strideElementsCount, &allocator );
		pH6GeometryFileHeader->fragments[i].vertexElementDescriptor[0] = Render::VertexElementDescriptor(0, 0,	Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_POSITION, 0) ;
		pH6GeometryFileHeader->fragments[i].vertexElementDescriptor[1] = Render::VertexElementDescriptor(0, 12, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_TANGENT,	 0) ;
		pH6GeometryFileHeader->fragments[i].vertexElementDescriptor[2] = Render::VertexElementDescriptor(0, 24, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_BINORMAL,	0) ;
		pH6GeometryFileHeader->fragments[i].vertexElementDescriptor[3] = Render::VertexElementDescriptor(0, 36, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_NORMAL, 0) ;
		pH6GeometryFileHeader->fragments[i].vertexElementDescriptor[4] = Render::VertexElementDescriptor(0, 48, Render::VERTEXELEMENTTYPE_FLOAT2, Render::VERETEXELEMENTUSAGE_TEXCOORD, 0) ;
		if(uvSetCount == 2 && jointsCount == 0)
		{
			pH6GeometryFileHeader->fragments[i].vertexElementDescriptor[5] = Render::VertexElementDescriptor(0, 56, Render::VERTEXELEMENTTYPE_FLOAT2, Render::VERETEXELEMENTUSAGE_TEXCOORD, 1) ;
		}
		if(jointsCount > 0)
		{
			pH6GeometryFileHeader->fragments[i].vertexElementDescriptor[5] = Render::VertexElementDescriptor(0, 56, Render::VERTEXELEMENTTYPE_FLOAT4, Render::VERETEXELEMENTUSAGE_BLENDWEIGHT, 0) ;
			pH6GeometryFileHeader->fragments[i].vertexElementDescriptor[6] = Render::VertexElementDescriptor(0, 72, Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_BLENDINDICES, 0) ;
		}
	}
	allocator.Normalize(16);
	pH6GeometryFileHeader->vbOffset = allocator.GetSize();
	pH6GeometryFileHeader->ibOffset = pH6GeometryFileHeader->vbOffset + pH6GeometryFileHeader->commonVertexBufferSizeInBytes;
	if(jointsCount)
		pH6GeometryFileHeader->reindexOffset = pH6GeometryFileHeader->ibOffset + pH6GeometryFileHeader->commonIndexBufferSizeInBytes;
	h6FileStream.Write( allocator.GetData(), allocator.GetSize() );
	return 1;
}
//////////////////////////////////////////////////////////////////////////
int WriteStaticMeshIndexBuffer( unsigned int subMeshCount, FileStream &h6FileStream, const MayaIndexBufferHeader** pIndexBufferHeaders, const nstl::vector<unsigned int>& uniqVertexIndices, unsigned int& fullvertexcount )
{
	unsigned int counter = 0;
	for (unsigned int i = 0; i < subMeshCount; ++i)
	{
		nstl::set<unsigned int, less> uniqIndices;
		h6FileStream.Write(pIndexBufferHeaders[i]+1,pIndexBufferHeaders[i]->triangleCount*VERTEX_PER_TRIANGLE*4);
		unsigned int indexCount = pIndexBufferHeaders[i]->triangleCount*VERTEX_PER_TRIANGLE;
		//systemLog( NLogg::LEVEL_MESSAGE ) << "fragment #" << i << " uses " << pIndexBufferHeaders[i]->triangleCount << " indices ( " << indexCount << " )" << endl;
		for (unsigned int indexNumber = 0; indexNumber < indexCount; ++indexNumber)
		{
			unsigned int oldIndex = *(((unsigned int*)(pIndexBufferHeaders[i]+1))+indexNumber);
			uniqIndices.insert(oldIndex);
		}
		//systemLog( NLogg::LEVEL_MESSAGE ) << "fragment #" << i << " uses " << uniqVertexIndices[i] << " or " <<  uniqIndices.size() << " unique indices" << endl;
		NI_VERIFY( (int)uniqVertexIndices[i] == uniqIndices.size() , NStr::StrFmt( "count of uniq vertices in fragment #%d and vertices pointed by index buffer for this fragment is diffrent!", i), return -1 );
		counter += uniqIndices.size();
	}
	NI_VERIFY( fullvertexcount == counter,  NStr::StrFmt( "maya claims %d, but IBs referenced for %d", fullvertexcount, counter), return -1 );
	return 1;
}
//////////////////////////////////////////////////////////////////////////
int WriteSkeletalMeshIndexBuffer( unsigned int subMeshCount
																 , FileStream &h6FileStream
																 , const MayaIndexBufferHeader** pIndexBufferHeaders
																 , nstl::vector< nstl::hash_map<unsigned int, unsigned int> >& oldNewVertexIndices )
{
	for (unsigned int i = 0; i < subMeshCount; ++i)
	{
		unsigned int indexCount = pIndexBufferHeaders[i]->triangleCount*VERTEX_PER_TRIANGLE;
		systemLog( NLogg::LEVEL_MESSAGE ) << "hash: fragment #" << i << indexCount << " index count" << endl;
		systemLog( NLogg::LEVEL_MESSAGE ) << "hash: fragment #" << i << " uses " << oldNewVertexIndices[i].size() << " unique indices" << endl;
		for (unsigned int indexNumber = 0; indexNumber < indexCount; ++indexNumber)
		{
			unsigned int oldIndex = *(((unsigned int*)(pIndexBufferHeaders[i]+1))+indexNumber);
			unsigned int newIndex = oldNewVertexIndices[i][oldIndex];
			//if( indexNumber < 10 ||  indexNumber > (indexCount - 10) )
			//{
			//	systemLog( NLogg::LEVEL_MESSAGE ) << "hash: " << oldIndex << " : " << newIndex << endl;
			//}
			h6FileStream.Write(&newIndex, 4);
		}
	}
	return 1;
}

//////////////////////////////////////////////////////////////////////////
int WriteJointsReindexToFile( FileStream& h6fileStream, unsigned int jointsCount, unsigned int subMeshCount
														 , const nstl::vector< nstl::set<unsigned short, less> >& submeshJointsReindex)
{
	DummyAllocator allocator(1024*1024);
	GeometryReindex* pGeometryReindex = reinterpret_cast<GeometryReindex*>( allocator.Allocate(sizeof(allocator), 16) );
	if(jointsCount && subMeshCount >= 1 )
	{
		//pH6GeometryFileHeader->jointsCount = jointsCount;
		pGeometryReindex->reindex.resize(subMeshCount, &allocator);
		for (unsigned int i = 0; i < subMeshCount; ++i)
		{
			pGeometryReindex->reindex[i].resize(submeshJointsReindex[i].size(), &allocator);
			unsigned int _counter = 0;
			for (nstl::set<unsigned short, less>::const_iterator it = submeshJointsReindex[i].begin(); it != submeshJointsReindex[i].end(); ++it )
				pGeometryReindex->reindex[i][_counter++] = *it;
		}
	}
	else
	{
		NI_ALWAYS_ASSERT("something wrong: there is only no one submesh therefore we don't need to make reindex");
	}
	h6fileStream.Write( allocator.GetData(), allocator.GetSize() );
	return 1;
}
//////////////////////////////////////////////////////////////////////////
int WriteJointsReindexToTemporaryBuffers( unsigned int subMeshCount
																				 , const MayaIndexBufferHeader** pIndexBufferHeaders
																				 , const MayaVertexStrideSkeletal* pVertex
																				 , nstl::vector< nstl::hash_map<unsigned short, unsigned short> >& submeshJointsReindexSorted
																				 , nstl::vector< nstl::set<unsigned short, less> >& submeshJointsReindex)
{
	nstl::set<unsigned short, less> fullJointIndexList;
	for (unsigned int i = 0; i < subMeshCount; ++i)
	{
		unsigned int indexCount = pIndexBufferHeaders[i]->triangleCount*VERTEX_PER_TRIANGLE;
		for (unsigned int indexNumber = 0; indexNumber < indexCount; ++indexNumber)
		{
			unsigned int indexValue = *(((unsigned int*)(pIndexBufferHeaders[i]+1))+indexNumber);

			NI_VERIFY(pVertex[indexValue].indices[0] < 256, "index should be less than 256", return -1 );
			NI_VERIFY(pVertex[indexValue].indices[1] < 256, "index should be less than 256", return -1 );
			NI_VERIFY(pVertex[indexValue].indices[2] < 256, "index should be less than 256", return -1 );
			NI_VERIFY(pVertex[indexValue].indices[3] < 256, "index should be less than 256", return -1 );

			submeshJointsReindex[i].insert( pVertex[indexValue].indices[0] );
			submeshJointsReindex[i].insert( pVertex[indexValue].indices[1] );
			submeshJointsReindex[i].insert( pVertex[indexValue].indices[2] );
			submeshJointsReindex[i].insert( pVertex[indexValue].indices[3] );

			fullJointIndexList.insert( pVertex[indexValue].indices[0] );
			fullJointIndexList.insert( pVertex[indexValue].indices[1] );
			fullJointIndexList.insert( pVertex[indexValue].indices[2] );
			fullJointIndexList.insert( pVertex[indexValue].indices[3] );
		}

		//systemLog( NLogg::LEVEL_MESSAGE ) << "fragment #" << i << " uses " << submeshJointsReindex[i].size() << " unique bones" << endl;
	}

	int max = 0;
	int fragmentNumber = 0;
	for (unsigned int i = 0; i < subMeshCount; ++i)
	{
		unsigned short counter = 0;
		if( max < submeshJointsReindex[i].size() )
		{
			max = submeshJointsReindex[i].size();
			fragmentNumber = i;
		}
		for (nstl::set<unsigned short, greater>::const_iterator it = submeshJointsReindex[i].begin(); it != submeshJointsReindex[i].end(); ++it)
		{
			submeshJointsReindexSorted[i][*it] = counter++;
		}
	}

	systemLog( NLogg::LEVEL_MESSAGE ) << "max bone count per fragment = " << max << "( fragment #" << fragmentNumber << " )" << endl;
	systemLog( NLogg::LEVEL_MESSAGE ) << "all fragments use " << fullJointIndexList.size() << " joints" << endl;
	return fullJointIndexList.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct NameIndexPair
{
	nstl::string name;
	unsigned int index;
};
//////////////////////////////////////////////////////////////////////////
static bool CompareNameIndexPair( const NameIndexPair &p1, const NameIndexPair &p2 )
{
	return p1.name < p2.name;
}

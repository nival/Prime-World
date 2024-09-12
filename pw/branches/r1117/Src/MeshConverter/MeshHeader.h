#pragma once

#include "../Render/vertexformatdescriptor.h"
#include "../System/staticstring.h"
#include "../System/staticvector.h"

namespace Signs
{
	static const unsigned statSIGN = 0x54415458;
	static const unsigned skinSIGN = 0x4e494b58;
	static const unsigned skelSIGN = 0x4c454b53;
	static const unsigned animSIGN = 0x4d494e41;
	static const unsigned partSIGN = 0x54524150;
	static const unsigned lghtSIGN = 0x5448474c;
	static const unsigned statSIGNOld = 0x54415453;
	static const unsigned skinSIGNOld = 0x4e494b53;
  static const unsigned telmSIGN = 0x4c455458; // XTEL - terrain element
}

//////////////////////////////////////////////////////////////////////////

struct TerrainElementStride
{
	CVec3 position;
	CVec3 normal;
  Render::Color color;
	Render::Color mask;
	CVec2 texcoord0;
};

struct TerrainElementStrideNew
{
  CVec3 position;
  CVec3 normal;
  CVec2 texcoord0;
  Render::Color color0;
  Render::Color color1;
  Render::Color mask;
};

struct TerrainElementAddonStride
{
	Render::Color color;
};

//////////////////////////////////////////////////////////////////////////
struct H6FragmentHeader
{
	unsigned __int32 vertexStrideSizeInBytes;
	__int32 baseVertexIndex;
	unsigned __int32 minIndex;
	unsigned __int32 numVertices;
	unsigned __int32 startIndex;
	unsigned __int32 primitiveCount;
	unsigned __int32 materialID;
	unsigned __int32 streamOffset;
	StaticVector< Render::VertexElementDescriptor > vertexElementDescriptor;
};
//////////////////////////////////////////////////////////////////////////
struct H6GeometryFileHeader
{
	unsigned __int32 signature;
	unsigned __int32 fragmentCount;
	unsigned __int32 materialCount; 
	//unsigned __int32 commonVertexCount;
	unsigned __int32 commonVertexBufferSizeInBytes;
	//unsigned __int32 commonIndexCount;
	unsigned __int32 commonIndexBufferSizeInBytes;
	unsigned __int32 vbOffset;
	unsigned __int32 ibOffset;
	unsigned __int32 reindexOffset;
	unsigned __int32 jointsCount;
	StaticVector< H6FragmentHeader > fragments;
};
//////////////////////////////////////////////////////////////////////////


struct CubeVertexStride
{
	float X, Y, Z;
	unsigned char a, r, g, b;
};

struct MayaStaticMeshFileHeader
{
	unsigned __int32 signature;
	unsigned __int32 vertexCount;
};

struct MayaSkeletalMeshFileHeader
{
	unsigned __int32 signature;
	unsigned __int32 vertexCount;
};

struct H6StaticMeshFileHeader
{
	unsigned __int32 signature;
	unsigned __int32 fragmentCount;
	unsigned __int32 commonVertexCount;
	unsigned __int32 commonVertexBufferSizeInBytes;
	unsigned __int32 commonIndexCount;
	unsigned __int32 commonIndexBufferSizeInBytes;
};

struct H6StaticMeshFragmentHeader
{
	unsigned __int32 vertexElementCount; // took into account D3DDECL_END 
	unsigned __int32 vertexStrideSizeInBytes;
	unsigned __int32 numVertices;
	//unsigned __int32 vertexCount;
	unsigned __int32 firstIndexNumber;
	unsigned __int32 indexCount;
};

struct MayaVertexStride
{
	CVec3 position;
	CVec3 normal;
	CVec3 tangent;
	CVec3 binormal;
	CVec2 texcoord0;
	CVec2 weights;
	unsigned __int32 indices[2];
};

struct MayaVertexStrideStaticOld
{
	CVec3 position;
	CVec3 normal;
	CVec3 tangent;
	CVec3 binormal;
	CVec2 texcoord[4];
};

struct MayaVertexStrideStatic
{
	CVec3 position;
	CVec4 color;
	CVec3 normal;
	CVec3 tangent;
	CVec3 binormal;
	CVec2 texcoord[4];
};

template <typename Base>
struct MayaVertexStrideSkeletalTemplate : public Base
{
	float weights[8];
	unsigned __int32 indices[8];
};

typedef MayaVertexStrideSkeletalTemplate<MayaVertexStrideStaticOld> MayaVertexStrideSkeletalOld;
typedef MayaVertexStrideSkeletalTemplate<MayaVertexStrideStatic> MayaVertexStrideSkeletal;

struct MayaVertexStrideNew
{
	CVec3 position;
	CVec3 normal;
	CVec3 tangent;
	CVec3 binormal;
	CVec2 texcoord[4];
	float weights[8];
	unsigned __int32 indices[8];
};


__declspec(align(16)) struct H6SkeletalMeshVertexStride
{
	CVec3 position;
	CVec3 tangent;
	CVec3 binormal;
	CVec3 normal;
	unsigned __int32 color;
	CVec2 texcoord[4];
	float weights[8];
	unsigned char indices[8];
};



struct H6StaticMeshVertexStride
{
	CVec3 position;
	CVec3 tangent;
	CVec3 binormal;
	CVec3 normal;
	CVec2 texcoord0;
	//CVec4 weights;
	//unsigned char boneIndices[4];
};

struct MayaIndexHeader
{
	unsigned __int32 subMeshCount;
};

struct MayaIndexBufferHeader
{
	unsigned __int32 triangleCount;
	unsigned __int32 unicVertexCountsInSubmeshes;
};

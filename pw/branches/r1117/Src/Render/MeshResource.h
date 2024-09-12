#pragma once

#include "primitive.h"
#include "../MeshConverter/MeshHeader.h"
#include "../System/fixedvector.h"

struct GeometryReindex;
namespace Render
{

struct MeshGeometry : NonCopyable // The "primitives" member requires special care
{
	nstl::vector<Primitive*> primitives;
	const GeometryReindex* pReindex;
	unsigned short materialCount;
	unsigned short fragmentCount;
  unsigned int triangleCount;
	unsigned short materialID[16];
	bool           colorStreamAppended;

  /// 
	MeshGeometry() : pReindex(0), materialCount(0), fragmentCount(0), triangleCount(0), colorStreamAppended(false) { primitives.reserve(8); }
	~MeshGeometry() 
	{
		for (nstl::vector<Primitive*>::iterator it = primitives.begin(); it != primitives.end(); ++it)
			delete *it;
		//primitives.clear();
	}

  void Swap(MeshGeometry *_pDest)
  {
    swap(primitives, _pDest->primitives);
    swap(pReindex, _pDest->pReindex);
    swap(materialCount, _pDest->materialCount);
    swap(fragmentCount, _pDest->fragmentCount);
    swap(triangleCount, _pDest->triangleCount);

    for(int i = 0, endI = ARRAY_SIZE( materialID ); i != endI; ++i)
      swap( materialID[i], _pDest->materialID[i] );

    swap(colorStreamAppended, _pDest->colorStreamAppended);
  }

};

//bool operator==(const MeshGeometry &_lhs, const MeshGeometry &_rhs)
//{
//  if( _lhs.materialCount != _rhs.materialCount )
//    return false;
//  for(int i = 0; i < _lhs.materialCount; ++i)
//    if( _lhs.materialID[i] != _rhs.materialID[i] )
//      return false;
//
//  if( _lhs.primitives.size() != _rhs.primitives.size() )
//    return false;
//
//  typedef nstl::vector<Primitive*>::const_iterator PrimCIter;
//  PrimCIter it_l = _lhs.primitives.begin(), it_r = _rhs.primitives.begin();
//  ;
//  for(PrimCIter const end_l = _lhs.primitives.end(); it_l < end_l; ++it_l, ++it_r)
//    if( **it_l != **it_r )
//      return false;
//
//  return (_lhs.fragmentCount == _rhs.fragmentCount) && (_lhs.triangleCount == _rhs.triangleCount);
//}


inline void swap( MeshGeometry &m1, MeshGeometry &m2 )
{
  m1.Swap(&m2);
}


/**
 *	raw data of terrain element geometry
 */
struct TerrainElementGeometryRaw
{
  unsigned version;
  NDb::Ptr<const NDb::TerrainMaterial> pMaterial;
	///< all raw data with header
	char* rawData;
	unsigned int rawDataSize;
	///< vertex buffer information
	char* vertexBuffer;
	unsigned int vertexBufferSize;
	unsigned int vertexBufferStride;
	///< index buffer information		
	char* indexBuffer;
	unsigned int indexBufferSize;
	///< DIP descriptor
	DipDescriptor dipDescriptor;
	///< Vertex declaration
	DXVertexDeclarationRef pVtxDecl;
};

}; // namespace Render

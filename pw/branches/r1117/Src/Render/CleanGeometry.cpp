#include "stdafx.h"
#include "CleanGeometry.h"
#include <Render\renderflagsconverter.h>
#include <System/InlineProfiler.h>

namespace Render {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// наглый копипаст
template<class T, size_t size>
static void insertSort(T (&a)[size])
{
  T x;
  long i, j;

  // цикл проходов, i - номер прохода
  for ( i = 0; i < size; i++ ) 
  {
    x = a[i];

    // поиск места элемента в готовой последовательности 
    for ( j = i - 1; j >= 0 && x < a[j]; j-- )
    {
      a[j+1] = a[j];  	// сдвигаем элемент направо, пока не дошли
    }

    // место найдено, вставить элемент
    a[j+1] = x;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename INDEX>
struct OrderedTriangle
{
  INDEX indices[3];

  struct Hash {
    size_t operator()(const OrderedTriangle& _s) const
    {
      return _s.indices[0] ^ 17 * (_s.indices[1] ^ 17 * _s.indices[2]);
    }
  };

  typedef hash_set<OrderedTriangle, typename OrderedTriangle::Hash> Set;

  OrderedTriangle(INDEX _i0, INDEX _i1, INDEX _i2)
  {
    indices[0] = _i0;
    indices[1] = _i1;
    indices[2] = _i2;
    insertSort(indices);
  }

  bool operator==(const OrderedTriangle &_rhs) const
  {
    return indices[0] == _rhs.indices[0] && indices[1] == _rhs.indices[1] && indices[2] == _rhs.indices[2];
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GeneralVtx::Hasher GeneralVtx::hasher;

void GeneralVtx::Hasher::Init(const VertexFormatDescriptor &_formatDescriptor, bool _skipColors)
{ // vertex descriptor shouldn't have holes
  chunks.clear();
  if( _formatDescriptor.GetVertexElementsCount() )
    chunks.push_back();

  for(UINT n = 0; n < _formatDescriptor.GetVertexElementsCount(); ++n)
  {
    const VertexElementDescriptor& veDesc = _formatDescriptor.GetVertexElement(n);
    NI_ASSERT(0 == veDesc.stream, "GeneralVtx::Hasher: only single-stream vertices supported");

    Chunk &lastChunk = chunks.back();
    const UINT lastEnd = lastChunk.offset + lastChunk.size;
    NI_ASSERT(lastEnd * sizeof(UINT) == veDesc.offset, "GeneralVtx::Hasher: unsupported vertex descriptor");

    const UINT veSize = Render::GetVertexElementSize(veDesc.type) / sizeof(UINT);
    if(_skipColors && veDesc.type == VERTEXELEMENTTYPE_D3DCOLOR)
    {
      // TODO: ?
      if (n + 1U >= _formatDescriptor.GetVertexElementsCount())
        continue;

      const UINT nextChunkOffset = _formatDescriptor.GetVertexElement(n + 1).offset / sizeof(UINT);
      if(lastChunk.size)
        chunks.push_back( Chunk(nextChunkOffset, 0) );
      else
        lastChunk.offset = nextChunkOffset;
    }
    else
      lastChunk.size += veSize;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline size_t GeneralVtx::Hasher::operator()(const GeneralVtx& _s) const
{
  UINT result = 0;
  typedef vector<Chunk>::const_iterator CIt;
  CIt const end = chunks.end();
  for(CIt it = chunks.begin(); it != end; ++it)
  {
    const UINT* pCurr = _s.pData + it->offset;
    for(const UINT* const pEnd = pCurr + it->size; pCurr != pEnd; ++pCurr)
      result ^= *pCurr + (result << 6) + (result >> 2);
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool GeneralVtx::operator==(const GeneralVtx& _rhs) const
{
#ifdef _DEBUG
  NI_ASSERT(!hasher.chunks.empty(), "Uninitialized hasher used");
#endif // _DEBUG

  typedef vector<Hasher::Chunk>::const_iterator CIt;
  CIt const end = hasher.chunks.end();
  for(CIt it = hasher.chunks.begin(); it != end; ++it)
  {
    const Hasher::Chunk &chunk = *it;
    if( memcmp(pData + chunk.offset, _rhs.pData + chunk.offset, chunk.size * sizeof(UINT)) )
      return false;
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename INDEX>
UINT RemoveDuplicateTriangles(INDEX* _pIndices, UINT _numIndices)
{ // OrderedTriangle doesn't account for different triangle winding (CULL_CW/CULL_CCW). Hence this function will break dual-sided meshes
  typedef OrderedTriangle<INDEX> OTriangle;

  NI_VERIFY(0 == _numIndices % 3, "Wrong index buffer", _numIndices = (_numIndices / 3) * 3);

  OTriangle::Set tris;
  INDEX *pLast = _pIndices;
  const INDEX * const pEnd = _pIndices + _numIndices;
  for(const INDEX *pCurr = pLast; pCurr != pEnd; pCurr += 3)
  {
    OTriangle triangle(pCurr[0], pCurr[1], pCurr[2]);

    if( tris.find(triangle) == tris.end() ) {
      tris.insert(triangle);
      if(pLast != pCurr)
        memcpy(pLast, pCurr, 3 * sizeof(INDEX));
      pLast += 3;
    }
  }

  return pLast - _pIndices;
}

// Explicit instantiation
template INTERMODULE_EXPORT unsigned RemoveDuplicateTriangles(unsigned* _pIndices, UINT _numIndices);
template INTERMODULE_EXPORT unsigned RemoveDuplicateTriangles(unsigned short* _pIndices, UINT _numIndices);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename INDEX>
UINT RemoveDuplicateVertices(const char *_pVerticesIn, char *_pVerticesOut, UINT _stride,  UINT _size,
                             const INDEX *_pIndicesIn, char *_pIndicesOut, UINT _indicesSize, UINT _numBuckets)
{
  NI_PROFILE_FUNCTION
  UINT _numVertices = _size / _stride;
  NI_VERIFY(_numVertices * _stride == _size, "RemoveDuplicateVertices: inconsistent size/stride", _size = _numVertices * _stride);

  UINT _numIndices = _indicesSize / sizeof(INDEX);
  NI_VERIFY(_numIndices * sizeof(INDEX) == _indicesSize, "RemoveDuplicateVertices: wrong _indicesSize",
            _indicesSize = _numIndices * sizeof(INDEX));

  vector<unsigned> reindex(_numVertices);
  GeneralVtx::Map vertexMap(_numBuckets, GeneralVtx::hasher);

  int i = 0;
  char *pLast = _pVerticesOut;
  const char *pCurr = _pVerticesIn;
  for(const char* const pEnd = pCurr + _size; pCurr != pEnd; pCurr += _stride)
  {
    size_t idx;
    GeneralVtx::Map::iterator const it = vertexMap.find( GeneralVtx(pCurr) );
    if(vertexMap.end() == it) {
      memmove(pLast, pCurr, _stride);
      idx = vertexMap.size();
      vertexMap[GeneralVtx(pLast)] = idx;
      pLast += _stride;
    }
    else {
      idx = it->second;
#ifdef _DEBUG
      ASSERT(GeneralVtx(pCurr) == it->first);
#endif // _DEBUG
    }

    reindex[i++] = idx;
  }
  ASSERT((int)_numVertices >= vertexMap.size() && int(vertexMap.size() * _stride) == pLast - _pVerticesOut);

  INDEX* const pIndices = (INDEX*)_pIndicesOut;
  uint idx_min = UINT_MAX;
  uint idx_max = 0;
  for(UINT i = 0; i < _numIndices; ++i) {
    NI_VERIFY(_pIndicesIn[i] < _numVertices, "RemoveDuplicateVertices: wrong indices", pIndices[i] = 0; continue);
    if(idx_min > _pIndicesIn[i])
      idx_min = _pIndicesIn[i];
    else if(idx_max < _pIndicesIn[i])
      idx_max = _pIndicesIn[i];

    pIndices[i] = reindex[_pIndicesIn[i]];
  }
  ASSERT(idx_max < _numVertices && idx_min == 0);

  return vertexMap.size();
}

// Explicit instantiation
template INTERMODULE_EXPORT UINT RemoveDuplicateVertices(const char *_pVerticesIn, char *_pVerticesOut, UINT _stride, UINT _size,
                                                         const unsigned *_pIndicesIn, char *_pIndicesOut, UINT _indicesSize, UINT _numBuckets);
template INTERMODULE_EXPORT UINT RemoveDuplicateVertices(const char *_pVerticesIn, char *_pVerticesOut, UINT _stride, UINT _size,
                                                         const unsigned short *_pIndicesIn, char *_pIndicesOut, UINT _indicesSize, UINT _numBuckets);

} // namespace Render

#pragma once
//#pragma warning(disable: 4521) // multiple copy constructors
namespace Render {

class GeneralVtx
{
public:
  struct Hasher
  { // displacement and size - all in DWORD units.
    struct Chunk {
      UINT offset;
      UINT size;

      Chunk() : offset(0), size(0) {}
      Chunk(UINT _offset, UINT _size) : offset(_offset), size(_size) {}
    };

    vector<Chunk> chunks;

    Hasher() {}
    Hasher(const Hasher &_src) { chunks = _src.chunks; }
    Hasher(const class VertexFormatDescriptor &_desc, bool _skipColors = false) { Init(_desc, _skipColors); }

    void Init(const class VertexFormatDescriptor &_desc, bool _skipColors = false);

    size_t operator()(const GeneralVtx& _s) const;
  };

  static Hasher hasher;

  typedef hash_map<GeneralVtx, UINT, Hasher> Map;

  GeneralVtx(const void* _pData) : pData((const UINT*)_pData) {}
  GeneralVtx(const GeneralVtx& _rhs) : pData(_rhs.pData) {}

  bool operator==(const GeneralVtx& _rhs) const;

private:
  GeneralVtx& operator=(const GeneralVtx& _rhs); // non-copyable
  const UINT* const pData;
};

// Remove duplicate vertices and reindex _pIndices accordingly. Return number of vertices survived
// _hasher provides hash-function and GeneralVtx::operator=()
template<typename INDEX>
UINT RemoveDuplicateVertices(const char *_pVerticesIn, char *_pVerticesOut, UINT _stride,  UINT _size,
                             const INDEX *_pIndicesIn, char *_pIndicesOut, UINT _indicesSize, UINT _numBuckets = 257);

// Return number of indices survived
template<typename INDEX>
UINT RemoveDuplicateTriangles(INDEX* _pIndices, UINT _numIndices);

} // namespace Render
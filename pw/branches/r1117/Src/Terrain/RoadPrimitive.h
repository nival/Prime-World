#pragma once

#include "RoadGeometryVertex.h"
#include "PatchCacheParams.h"

namespace Terrain
{

struct PatchMapping
{
  struct Patch
  {
    ushort start;
    ushort size;  // Actually, size - 1
    union {
      size_t patch;
      const PatchCacheParams *pParams;
    };

    Patch(ushort _start, ushort _size, unsigned _patch) : start(_start), size(_size), patch(_patch) {}
    bool operator<(const Patch &_rhs) const
    {
      if(patch == _rhs.patch)
        return start < _rhs.start;

      return patch < _rhs.patch;
    }
  };

  typedef uint Index;
  typedef vector<Patch> Map;
  Map patches;

  PatchMapping(const Render::MeshGeometry *_pGeometry); // this function relies upon assumption that Map IS vector

private:
  void CreatePatches( const uint* _pIDsStart, uint _numTris);
  void MergePatches(Index* _pIndices, const Index* _pTemp);
};


class RoadPrimitive : public Render::IRenderablePrimitive, public NonCopyable
{
  const Render::Primitive* const pPrimitive;
  const PatchMapping* const pPatchMapping;
  void FillCache() const;
  void DrawWithCache() const;
public:
  RoadPrimitive(const Render::Primitive *_pPrimitive, const PatchMapping *_pMapping)
    : pPrimitive(_pPrimitive), pPatchMapping(_pMapping) {}

  void Bind() const { pPrimitive->Bind(); }
  void Draw() const;
  Render::GeometryBuffers  GetBuffers() const { return pPrimitive->GetBuffers(); }
  Render::GeometryStatistics GetStats() const { return pPrimitive->GetStats(); }

  static void SetTEGetter(class TEGetter* _pGetter);
};

}

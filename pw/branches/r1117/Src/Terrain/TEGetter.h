#pragma once

#include "PatchCacheParams.h"

namespace Terrain
{

class TerrainElement;

class TEGetter : public NonCopyable
{
  typedef hash_map<uint, const TerrainElement*> TEMap;
  TEMap teMap;
  const float scale, scale3;

public:
  TEGetter(float _patchSize) : scale(1.f/_patchSize), scale3( 1.f/(3.f*_patchSize) ) {}

  void AddElement(const TerrainElement* _element);
  const PatchCacheParams* GetCacheParams(uint _patchID) const;

  uint GetPatchID(const CVec2 &_point)
  {
    return MAKELONG(int(_point.x * scale) + SHRT_MAX,
                    int(_point.y * scale) + SHRT_MAX);
  }

  uint GetScaledPatchID(const CVec2 &_point)
  {
    return MAKELONG(int(_point.x * scale3) + SHRT_MAX,
                    int(_point.y * scale3) + SHRT_MAX);
  }
};

}
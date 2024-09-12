#pragma once

namespace Terrain
{

struct PatchCacheParams
{
  enum { NON_CACHED_OR_SINGLE = -1 }; 

  CVec4 scaleShift;
  // as pLocalMaterial differs from actual material used for render, we need those members here
  NDb::CachingPin pin;
  int layer1_element;
  int layer1_element2;

  //PatchCacheParams(void) {}
};

}
#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////
#include "RayPixels.h"
#include "../System/ScopedArray.h"


namespace NWorld
{


// One circle rays
class CircleRays
{
public:
  CircleRays();

  static CircleRays  *CreateCircleForRadius(int radius);
  int                 GetNumRays() { return numRays; }
  RayPixels          *GetRay(int rayIndex) { return Get(pRays) + rayIndex; }

private:
  int                     numRays;
  ScopedArray<RayPixels>  pRays;
};


} // namespace NWorld

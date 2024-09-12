#include "stdafx.h"
#include "EaselMath.h"

namespace PF_Minigames
{

int64 CalculateDistance(const SVector &refA,const SVector &refB)
{
  // calculating line length
  double deltaX = abs(refA.x-refB.x);
  double deltaY = abs(refA.y-refB.y);

  return sqrt(deltaX*deltaX+deltaY*deltaY);
}

}

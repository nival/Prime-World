/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RayPixels.h"


/////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
// Methods
/////////////////////////////////////////////////////////////////////////////////


namespace NWorld
{


RayPixels::RayPixels()
{
  numPixels     = 0;
  inBuild       = false;
}

void  RayPixels::CreateRay(int xStart, int yStart, int xEnd, int yEnd)
{
  int i;
  int *dest;
  int x, y;

  NI_ASSERT(xStart < 65535, "Too far line start");
  NI_ASSERT(yStart < 65535, "Too far line start");
  NI_ASSERT(xEnd   < 65535, "Too far line end");
  NI_ASSERT(yEnd   < 65535, "Too far line end");

  BuildRayStart(xStart, yStart, xEnd, yEnd);
  NI_VERIFY(rayLen < 512, "Too long line", return;)
  
  numPixels = rayLen;
  if (rayLen == 0)
  {
    Reset(pPixelOffset, new int[1]);
    Get(pPixelOffset)[0] = xStart | (yStart << 16);
    BuildRayEnd();
    return;
  }
  if (rayLen == 1)
  {
    Reset(pPixelOffset, new int[2]);
    Get(pPixelOffset)[0] = (xStart & 0xffff) | (yStart << 16);
    Get(pPixelOffset)[1] = (xEnd   & 0xffff) | (yEnd   << 16);
    BuildRayEnd();
    return;
  }
  
  // allocate new
  Reset(pPixelOffset, new int[numPixels + 1]);
  // fill array
  dest = Get(pPixelOffset);
  for (i = 0; i <= numPixels; i++, dest++)  
  {
    GetRayPoint(x, y);
    *dest = (x & 0xffff) | (y << 16);
    MakeRayStep();
  }
}

} // namespace


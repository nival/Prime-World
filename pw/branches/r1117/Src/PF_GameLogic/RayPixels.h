#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////
#include "../System/2Darray.h"
#include "../System/ScopedArray.h"


/////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////
#define ACCURACY_BITS     14
#define ACCURACY_HALF     (1<<(ACCURACY_BITS-1))

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////

namespace NWorld
{

// One ray brezenham data
class RayPixels
{
public:
  RayPixels();
  
  void  CreateRay(int xStart, int yStart, int xEnd, int yEnd);
  int   GetNumPixels()  { return numPixels; }
  void  GetPixel(int index, int &x, int &y)
  {
    int packed = Get(pPixelOffset)[index];
    x = packed & 0xffff; 
    x <<= 16; x >>= 16; /// save sign
    y = (packed >> 16);
  }
  
  void  BuildRayStart(int xStart, int yStart, int xEnd, int yEnd)
  {
    NI_ASSERT(!inBuild, "BuildRay Start/End fail");
    inBuild = true;
    
    int sDX = xEnd - xStart;
    int sDY = yEnd - yStart;
    int uDX = (sDX > 0)?   sDX : -sDX;
    int uDY = (sDY > 0)?   sDY : -sDY;
    rayLen  = (uDX > uDY)? uDX : uDY;
    
    xStep = (sDX << ACCURACY_BITS) / rayLen;
    yStep = (sDY << ACCURACY_BITS) / rayLen;
    xAcc  = (xStart << ACCURACY_BITS);
    yAcc  = (yStart << ACCURACY_BITS);
    yAcc += ACCURACY_HALF;
    xAcc += ACCURACY_HALF;
  }
  
  void  GetRayPoint(int &x, int &y)
  {
    x = xAcc >> (ACCURACY_BITS);
    y = yAcc >> (ACCURACY_BITS);
  }
  
  void  MakeRayStep()
  {
    xAcc += xStep;
    yAcc += yStep;
  }
  
  void  BuildRayEnd()
  {
    inBuild = false;
  }

private:    
  int   numPixels;	
  ScopedArray<int>  pPixelOffset;   // 16:16 for x,y offset (x - lowest)
  
  // Data for step-by-step Brezenham line trace
  bool  inBuild;
  int   rayLen;
  int   xStep, yStep;
  int   xAcc, yAcc;
  
};

} // namespace NWorld

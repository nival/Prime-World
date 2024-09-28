#pragma once

#include "Defines.h"

namespace Input
{
  struct SSysParams;
};


namespace Render
{
	struct AABB;
}


namespace UI
{


const int UI_RESOLUTION_WIDTH = 1280;
const int UI_RESOLUTION_HEIGHT = 1024;


namespace ESnapOptions
{
  const static unsigned RoundOff        = 1;
  const static unsigned PreserveWidth   = 2;
  const static unsigned PreserveHeight  = 4;
  const static unsigned PreserveSize    = PreserveWidth | PreserveHeight;
  const static unsigned KeepRight       = 8;
  const static unsigned KeepBottom      = 16;
};


void UpdateScreenResolution( const int width, const int height, const bool editor );


const Point& GetUIScreenResolution();
const Point& GetScreenResolution();
const float GetUIScreenRatio();

Point ConvertToScreen( const Point & ui );
Point ConvertFromScreen( const Point & ui );

float SnapToScreenPixelX( float uiCoordX, unsigned options = ESnapOptions::RoundOff );
float SnapToScreenPixelY( float uiCoordY, unsigned options = ESnapOptions::RoundOff );
void SnapRectToScreenPixels( Rect & rect, unsigned options = ESnapOptions::RoundOff );

Point ExtractMsgCoords( const Input::SSysParams & eventSysParams );

//Returns depth
float GetWindowPlacement( Rect * result, Render::AABB const & aabb, const SHMatrix & projectionMatrix );

//Returns minimal depth of 8 AABB points
float GetWindowPlacement( Point * result, LinearCoord * resultSize, const CVec3 & posWorld, float size, const SHMatrix & projectionMatrix );

} //namespace UI

#pragma once

#include "../System/nalgoritm.h"
#include "../System/Bresenham.h"

namespace NScene
{

class PointSelector
  : NonCopyable
{
  float gridStep;
  CVec2 error;

  CVec2 origin;
  CVec2 dir;

  CVec2 in;
  CVec2 out;

public:
  PointSelector( const CVec2 _origin, const CVec2& _dir, float step ) 
    : gridStep( step )
    , error( -1.0f, -1.0f )
    , origin( _origin.x / gridStep, _origin.y / gridStep )
    , dir( _dir )
  {
    dir *= 2;
  }

  /** grid scan functor */
  bool operator() ( int x, int y, float xEnter, float yEnter, float xLeave, float yLeave )
  {
    const bool swapX = xLeave < xEnter;
    const bool inRange = !swapX ? origin.x <= xEnter : origin.x >= xEnter; 

    if( inRange )
    {
      in.Set( xEnter * gridStep, yEnter * gridStep );
      out.Set( xLeave * gridStep, yLeave * gridStep );
      origin.Set( xLeave, yLeave );

      // process only first cell
      return false;
    }
    else
      // process next
      return true;
  }

  /** point selector */
  void operator () ( CVec2* in, CVec2* out )
  {
    NI_VERIFY( in && out, "Invalid result storage!", return; );

    this->in = error;
    this->out = error;

    ScanCoveredGridCells( origin.x, origin.y, origin.x + dir.x, origin.y + dir.y, *this );				

    *in = this->in;
    *out = this->out;
  }
};

}


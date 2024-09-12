using System;
using System.Collections.Generic;
using System.Text;

namespace EditorPlugins.Mathematics
{
  internal class InterpolatingSpline
  {
    private float a, b, c, d;
    private bool setup = false;

    public void Setup( float y0, float y1, float y2, float y3 )
    {
      a = 0.5f * y3 - 1.5f * y2 + 1.5f * y1 - 0.5f * y0;
      b = -0.5f * y3 + 2 * y2 - 2.5f * y1 + y0;
      c = ( y2 - y0 ) / 2;
      d = y1;

      setup = true;
    }

    public float Get( float t )
    {
      if ( !setup )
        return 0;

      if ( t < 0 )
        return Get( 0 );

      if ( t > 1 )
        return Get( 1 );

      return a * t * t * t + b * t * t + c * t + d;
    }
  }
}

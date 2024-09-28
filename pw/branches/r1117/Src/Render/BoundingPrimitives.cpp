#include "stdafx.h"
#include "BoundingPrimitives.h"


namespace Render
{
  void BoundingBox::Merge(const D3DXVECTOR3 &point)
  {
    minPt.x = min(minPt.x, point.x);
    minPt.y = min(minPt.y, point.y);
    minPt.z = min(minPt.z, point.z);
    maxPt.x = max(maxPt.x, point.x);
    maxPt.y = max(maxPt.y, point.y);
    maxPt.z = max(maxPt.z, point.z);
  }

  bool BoundingBox::Intersect(float* hitDist, const D3DXVECTOR3 &origPt, const D3DXVECTOR3 &dir)
  {
    D3DXPLANE sides[6] = { D3DXPLANE( 1, 0, 0,-minPt.x), D3DXPLANE(-1, 0, 0, maxPt.x),
      D3DXPLANE( 0, 1, 0,-minPt.y), D3DXPLANE( 0,-1, 0, maxPt.y),
      D3DXPLANE( 0, 0, 1,-minPt.z), D3DXPLANE( 0, 0,-1, maxPt.z) };

    *hitDist = 0.f;  // safe initial value
    D3DXVECTOR3 hitPt = origPt;

    bool inside = false;

    for ( int i=0; (i<6) && !inside; i++ )
    {
      float cosTheta = D3DXPlaneDotNormal(&sides[i], &dir);
      float dist = D3DXPlaneDotCoord(&sides[i], &origPt);

      //  if we're nearly intersecting, just punt and call it an intersection
      if ( ALMOST_ZERO(dist) ) return true;
      //  skip nearly (&actually) parallel rays
      if ( ALMOST_ZERO(cosTheta) ) continue;
      //  only interested in intersections along the ray, not before it.
      *hitDist = -dist / cosTheta;
      if ( *hitDist < 0.f ) continue;

      hitPt = (*hitDist) * dir + origPt;

      inside = true;

      for ( int j=0; (j<6) && inside; j++ )
      {
        if ( j==i )
          continue;
        float d = D3DXPlaneDotCoord( &sides[j], &hitPt );

        inside = ((d + 0.00015) >= 0.f);
      }
    }

    return inside;        
  }
  //  Transform an axisVS-aligned bounding box by the specified matrix, and compute a new axisVS-aligned bounding box
  void XFormBoundingBox( BoundingBox* result, const BoundingBox &src, const D3DXMATRIX &matrix )
  {
    D3DXVECTOR3  pts[8];
    pts[0] = D3DXVECTOR3( src.minPt.x, src.minPt.y, src.minPt.z );
    pts[1] = D3DXVECTOR3( src.minPt.x, src.minPt.y, src.maxPt.z );
    pts[2] = D3DXVECTOR3( src.minPt.x, src.maxPt.y, src.minPt.z );
    pts[3] = D3DXVECTOR3( src.minPt.x, src.maxPt.y, src.maxPt.z );
    pts[4] = D3DXVECTOR3( src.maxPt.x, src.minPt.y, src.minPt.z );
    pts[5] = D3DXVECTOR3( src.maxPt.x, src.minPt.y, src.maxPt.z );
    pts[6] = D3DXVECTOR3( src.maxPt.x, src.maxPt.y, src.minPt.z );
    pts[7] = D3DXVECTOR3( src.maxPt.x, src.maxPt.y, src.maxPt.z );

    result->minPt = D3DXVECTOR3(3.3e33f, 3.3e33f, 3.3e33f);
    result->maxPt = D3DXVECTOR3(-3.3e33f, -3.3e33f, -3.3e33f);

    for (int i=0; i<8; i++)
    {
      D3DXVECTOR3 tmp;
      D3DXVec3TransformCoord(&tmp, &pts[i], &matrix);
      result->minPt.x = min(result->minPt.x, tmp.x);
      result->minPt.y = min(result->minPt.y, tmp.y);
      result->minPt.z = min(result->minPt.z, tmp.z);
      result->maxPt.x = max(result->maxPt.x, tmp.x);
      result->maxPt.y = max(result->maxPt.y, tmp.y);
      result->maxPt.z = max(result->maxPt.z, tmp.z);
    }
  }
}

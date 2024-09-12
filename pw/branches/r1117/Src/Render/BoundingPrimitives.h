#pragma once

#define FLT_AS_DW(F) (*(DWORD*)&(F))
#define ALMOST_ZERO(F) ((FLT_AS_DW(F) & 0x7f800000L)==0)

namespace Render
{
  struct BoundingBox
  {
    D3DXVECTOR3 minPt;
    D3DXVECTOR3 maxPt;

    BoundingBox() { Invalidate(); }
    BoundingBox( const BoundingBox& other ): minPt(other.minPt), maxPt(other.maxPt) { }

    explicit BoundingBox( const vector<BoundingBox> &boxes )
    {
      Invalidate();
      for ( int i = 0; i < boxes.size(); i++ ) 
      {
        Merge(boxes[i].maxPt);
        Merge(boxes[i].minPt);
      }
    }

    explicit BoundingBox( const vector<D3DXVECTOR3> &points)
    {
      Invalidate();
      Merge( &points[0], points.size() );
    }

    explicit BoundingBox( const D3DXVECTOR3* points, int numPoints)
    {
      Invalidate();
      Merge(points, numPoints);
    }

    void Invalidate()
    {
      minPt.x = minPt.y = minPt.z = 1e33f;
      maxPt.x = maxPt.y = maxPt.z = -1e33f;
    }

    bool IsValid() { return minPt.x <= maxPt.x && minPt.y <= maxPt.y && minPt.z <= maxPt.z; }

    void Centroid(D3DXVECTOR3* vec) const { *vec = 0.5f*(minPt+maxPt); }

    void Merge(const D3DXVECTOR3 &point);
    void Merge(const D3DXVECTOR3 *points, int numPoints)
    {
      for(int i = 0; i < numPoints; i++)
        Merge( points[i] );
    };

    bool Intersect(float* hitDist, const D3DXVECTOR3 &origPt, const D3DXVECTOR3 &dir);
  };

  struct BoundingSphere
  {
    D3DXVECTOR3 centerVec;
    float       radius;

    BoundingSphere(): centerVec(), radius(0.f) { }
    BoundingSphere(const BoundingSphere& other): centerVec(other.centerVec), radius(other.radius) { }
    explicit BoundingSphere(const BoundingBox &box)
    {
      D3DXVECTOR3 radiusVec;
      centerVec = 0.5f * (box.maxPt + box.minPt);
      radiusVec = box.maxPt - centerVec;
      float len = D3DXVec3Length(&radiusVec);
      radius = len;
    }
  };

  void XFormBoundingBox(BoundingBox* result, const BoundingBox &src, const D3DXMATRIX &matrix);
} // namespace Render

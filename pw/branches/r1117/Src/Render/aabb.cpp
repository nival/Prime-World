#include "stdafx.h"
#include <float.h>
#include "aabb.h"

namespace Render
{

void AABB::Init2Empty()
{
	center = CVec3(0.0f, 0.0f, 0.0f);
	halfSize = CVec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
}

bool AABB::IsValid() const
{
	return center.IsFinite() && halfSize.IsFinite() &&
         halfSize.x >= 0.0f && halfSize.y >= 0.0f && halfSize.z >= 0 &&
				 fabsf(center.x) < 10000.0f && fabsf(center.y) < 10000.0f && fabsf(center.z) < 10000.0f;
}


void AABB::Transform( const Matrix43 &mtx, const AABB &src )
{
  //if( src.IsEmpty() )
  //{
  //  *this = src;
  //  return;
  //}

	center = ::Transform( src.center, mtx );
	
	// Transform AABB size/2 value
	// ---------------------------
	// Lets assume vP - any on 8 corners of transformed AABB. This can be written as follows:
	// vP(s1,s2,s3) = s1*vR*vD.x + s2*vU*vD.y + s3*vA*vD.z
	// Here
	//   vR, vU, vA = vRight, vUp, vAt  - matrix axes
	//   vD = vDelta                    - size/2 value
	//   s1, s2, s3 = +1/-1             - sign values
	// So what is max of vP?
	// Obviously: vPmax = |vR*vD.x| + |vU*vD.y| + |vA*vD.z|
	halfSize.x = fabsf(mtx._11 * src.halfSize.x) + 
						 fabsf(mtx._12 * src.halfSize.y) + 
						 fabsf(mtx._13 * src.halfSize.z);
	halfSize.y = fabsf(mtx._21 * src.halfSize.x) + 
						 fabsf(mtx._22 * src.halfSize.y) + 
				   fabsf(mtx._23 * src.halfSize.z);
	halfSize.z = fabsf(mtx._31 * src.halfSize.x) + 
						 fabsf(mtx._32 * src.halfSize.y) + 
						 fabsf(mtx._33 * src.halfSize.z);
}

void AABB::Set( float minX, float maxX, float minY, float maxY, float minZ, float maxZ )
{
	center.x = ( maxX + minX ) * 0.5f;
	center.y = ( maxY + minY ) * 0.5f;
	center.z = ( maxZ + minZ ) * 0.5f;
	halfSize.x = ( maxX - minX ) * 0.5f;
	halfSize.y = ( maxY - minY ) * 0.5f;
	halfSize.z = ( maxZ - minZ ) * 0.5f;
}

void AABB::Set( const NDb::AABB &dbAABB ) 
{
	Set( dbAABB.minX, dbAABB.maxX, dbAABB.minY, dbAABB.maxY, dbAABB.minZ, dbAABB.maxZ );
}

void AABB::Set( const CVec3 &vmin, const CVec3 &vmax )
{
	Set( vmin.x, vmax.x, vmin.y, vmax.y, vmin.z, vmax.z );
}

void AABB::Assign( const CVec3 &_center, const CVec3 &_halfSize )
{
  center = _center;
  halfSize = _halfSize;
}

void AABB::AddPoint( const CVec3 &pnt )
{
  if( IsEmpty() )
  {
    center = pnt;
    halfSize.Set(0, 0, 0);
    return;
  }
	CVec3 minV = center - halfSize; 
	CVec3 maxV = center + halfSize; 

  if (pnt.x < minV.x)
	  minV.x = pnt.x;
  else if (pnt.x > maxV.x)
	  maxV.x = pnt.x;

  if (pnt.y < minV.y)
	  minV.y = pnt.y;
  else if (pnt.y > maxV.y)
	  maxV.y = pnt.y;

  if (pnt.z < minV.z)
	  minV.z = pnt.z;
  else if (pnt.z > maxV.z)
	  maxV.z = pnt.z;

  center   = (minV + maxV) * 0.5f;
  halfSize = (maxV - minV) * 0.5f;
}

void AABB::Calculate( int numPoints, const CVec3 *pPoints, int stride	)
{
	CVec3 minV( pPoints[0] ); 
	CVec3 maxV( pPoints[0] ); 

	pPoints = (const CVec3*)( ((const char*)pPoints) + stride );
	for (int i = 1; i < numPoints; ++i)
	{
		CVec3 const &pnt = pPoints[0];
		pPoints = (const CVec3*)( ((const char*)pPoints) + stride );

		if (pnt.x < minV.x)
			minV.x = pnt.x;
		else if (pnt.x > maxV.x)
			maxV.x = pnt.x;

		if (pnt.y < minV.y)
			minV.y = pnt.y;
		else if (pnt.y > maxV.y)
			maxV.y = pnt.y;

		if (pnt.z < minV.z)
			minV.z = pnt.z;
		else if (pnt.z > maxV.z)
			maxV.z = pnt.z;
	}

	center   = (minV + maxV) * 0.5f;
	halfSize = (maxV - minV) * 0.5f;
}

void AABB::Grow( const AABB& aabb )
{
	if( IsEmpty() )
	{
		center   = aabb.center;
		halfSize = aabb.halfSize;
	}
	else
	{
		CVec3 minpos1 = center-halfSize;
		CVec3 maxpos1 = center+halfSize;

		CVec3 minpos2 = aabb.center-aabb.halfSize;
		CVec3 maxpos2 = aabb.center+aabb.halfSize;

		CVec3 minpos( min ( minpos1.x, minpos2.x ), min ( minpos1.y, minpos2.y ), min ( minpos1.z, minpos2.z ) );
		CVec3 maxpos( max ( maxpos1.x, maxpos2.x ), max ( maxpos1.y, maxpos2.y ), max ( maxpos1.z, maxpos2.z ) );

		center   = (minpos + maxpos) * 0.5f;
		halfSize = (maxpos - minpos) * 0.5f;
	}
}

void AABB::Intersect(AABB const& aabb)
{
  if (!IsValid() || !aabb.IsValid())
    Init2Empty();
  else
  {
    CVec3 minpos = center - halfSize;
    CVec3 maxpos = center + halfSize;

    minpos.Maximize(aabb.center - aabb.halfSize);
    maxpos.Minimize(aabb.center + aabb.halfSize);

    center   = (minpos + maxpos) * 0.5f;
    halfSize = (maxpos - minpos) * 0.5f;
  }
}

bool AABB::IsIntersectedBy(const AABB &aabb) const
{
	CVec3 minpos1 = center-halfSize;
	CVec3 maxpos1 = center+halfSize;

	CVec3 minpos2 = aabb.center-aabb.halfSize;
	CVec3 maxpos2 = aabb.center+aabb.halfSize;

return maxpos2.x >= minpos1.x &&
	   minpos2.x <= maxpos1.x &&
	   maxpos2.y >= minpos1.y &&
	   minpos2.y <= maxpos1.y &&
	   maxpos2.z >= minpos1.z &&
	   minpos2.z <= maxpos1.z;
}

}
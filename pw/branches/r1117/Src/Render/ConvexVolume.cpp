#include "stdafx.h"
#include "ConvexVolume.h"
#include "../System/GeomMisc.h"
#include "../Render/debugrenderer.h"
#include "../Render/sceneconstants.h"

#define SIGN_BIT (~(1 << 31))
static __m128 SSE_SIGN_MASK;
static float __mask;

#include "aabb.h"

static float s_Displace = 0.0f;
REGISTER_DEV_VAR("frustumDisplace", s_Displace, STORAGE_NONE)


static struct SRegister_hack
{
	SRegister_hack()
	{
		*(unsigned int*)(&__mask) = 0x7FFFFFFF;
		SSE_SIGN_MASK = _mm_set_ps( __mask, __mask, __mask, __mask );
	}
} _hack;

#define VectorAbs( Vec )				_mm_and_ps(Vec, SSE_SIGN_MASK)

namespace Render
{
	namespace
	{
    __forceinline float invSqrt( float F )
    {

      static const __m128 fThree = _mm_set_ss( 3.0f );
      static const __m128 fOneHalf = _mm_set_ss( 0.5f );
      __m128 Y0, X0, Temp;
      float temp;

      Y0 = _mm_set_ss( F );
      X0 = _mm_rsqrt_ss( Y0 );	// 1/sqrt estimate (12 bits)

      // Newton-Raphson iteration (X1 = 0.5*X0*(3-(Y*X0)*X0))
      Temp = _mm_mul_ss( _mm_mul_ss(Y0, X0), X0 );	// (Y*X0)*X0
      Temp = _mm_sub_ss( fThree, Temp );				// (3-(Y*X0)*X0)
      Temp = _mm_mul_ss( X0, Temp );					// X0*(3-(Y*X0)*X0)
      Temp = _mm_mul_ss( fOneHalf, Temp );			// 0.5*X0*(3-(Y*X0)*X0)
      _mm_store_ss( &temp, Temp );

      return temp;
    }


		__forceinline void MakeFrustumPlane( float A, float B, float C, float D, FPlane& OutPlane )
		{
			const float epsilon = 0.00001f;
			const float	LengthSquared = A * A + B * B + C * C;
			ASSERT(LengthSquared > epsilon*epsilon);
			const float	InvLength = invSqrt(LengthSquared);
			OutPlane = FPlane(-A * InvLength,-B * InvLength,-C * InvLength,D * InvLength);
		}

		__forceinline void GetFrustumNearPlane( FPlane& OutPlane, const SHMatrix& M )
		{
			MakeFrustumPlane(
				M.m[0][2],
				M.m[1][2],
				M.m[2][2],
				M.m[3][2],
				OutPlane
				); 
		}

		__forceinline void GetFrustumFarPlane( FPlane& OutPlane, const SHMatrix& M )
		{
			MakeFrustumPlane(
				M.m[0][3] - M.m[0][2],
				M.m[1][3] - M.m[1][2],
				M.m[2][3] - M.m[2][2],
				M.m[3][3] - M.m[3][2],
				OutPlane
				);
		}

		__forceinline void GetFrustumLeftPlane( FPlane& OutPlane, const SHMatrix& M )
		{
			MakeFrustumPlane(
				M.m[0][3] + M.m[0][0],
				M.m[1][3] + M.m[1][0],
				M.m[2][3] + M.m[2][0],
				M.m[3][3] + M.m[3][0],
				OutPlane
				);
		}

		__forceinline void GetFrustumRightPlane( FPlane& OutPlane, const SHMatrix& M )
		{
			MakeFrustumPlane(
				M.m[0][3] - M.m[0][0],
				M.m[1][3] - M.m[1][0],
				M.m[2][3] - M.m[2][0],
				M.m[3][3] - M.m[3][0],
				OutPlane
				);
		}

		__forceinline void GetFrustumTopPlane( FPlane& OutPlane, const SHMatrix& M )
		{
			MakeFrustumPlane(
				M.m[0][3] - M.m[0][1],
				M.m[1][3] - M.m[1][1],
				M.m[2][3] - M.m[2][1],
				M.m[3][3] - M.m[3][1],
				OutPlane
				);
		}

		__forceinline void GetFrustumBottomPlane( FPlane& OutPlane, const SHMatrix& M )
		{
			MakeFrustumPlane(
				M.m[0][3] + M.m[0][1],
				M.m[1][3] + M.m[1][1],
				M.m[2][3] + M.m[2][1],
				M.m[3][3] + M.m[3][1],
				OutPlane
				);
		}
	}

  void FPlane::SetFromPoints(const CVec3& pt0, const CVec3& pt1, const CVec3& pt2)
  {
    //const float adj0 = pt1.y * pt2.z - pt2.y * pt1.z;
    //const float adj1 = pt2.y * pt0.z - pt0.y * pt2.z;
    //const float adj2 = pt0.y * pt1.z - pt2.y * pt0.z;
    //X = adj0 + adj1 + adj2;
    //Y = pt0.z * (pt1.x - pt2.x) + pt1.z * (pt2.x - pt0.x) + pt2.z * (pt0.x - pt1.x);
    //Z = pt0.x * (pt1.y - pt2.y) + pt1.x * (pt2.y - pt0.y) + pt2.x * (pt0.y - pt1.y);
    //W = -(pt0.x * adj0 + pt1.x * adj1 + pt2.x * adj2);
    CVec3 dir1 = pt1 - pt0;
    CVec3 dir2 = pt2 - pt0;
    CVec3 normal = dir2 ^ dir1;
    X = normal.x;
    Y = normal.y;
    Z = normal.z;
    W = -normal.Dot(pt0);
  }

  void FPlane::Normalize()
  {
    MakeFrustumPlane(X, Y, Z, W, *this);
  }

	void ConvexVolume::BuildFrustum( const SHMatrix& viewProjectionMatrix )
	{
		viewProjection = viewProjectionMatrix;
		SHMatrix matrix;
		Transpose(&matrix, viewProjectionMatrix);
		BuildPlanes(matrix);
		BuildPermutedPlanes();
	}

  bool Transform(CVec3 *_pRes, const SHMatrix &_matrix, const CVec3 &_arg)
  {
    CVec4 result;
    _matrix.RotateHVector(&result, _arg);
    if(fabs(result.w) < 1.e-30f)
      return false;
    *_pRes = result.AsVec3D() / result.w;
    return true;
  }

  void ConvexVolume::BuildFrustum(const Render::SceneConstants &sceneConstants, const RECT& visibleRect,
                                  float screenWidth, float screenHeight)
  {
    //Transpose(&viewProjection, sceneConstants.viewProjection);
    SHMatrix matrix;
    viewProjection = sceneConstants.viewProjection;
    Invert(&matrix, viewProjection);

#define POINT3D(x, y) CVec3((2.f * x)/screenWidth - 1.f, 1.f - (2.f * y)/screenHeight, 1.f)

    //const CVec3 cornersSS[4] = { CVec3(-1, 1, 0), CVec3(-1, -1, 0), CVec3(1, -1, 0), CVec3(1, 1, 0) };
    const CVec3 cornersSS[4] = { POINT3D(visibleRect.left, visibleRect.top),
                                 POINT3D(visibleRect.left, visibleRect.bottom),
                                 POINT3D(visibleRect.right, visibleRect.bottom),
                                 POINT3D(visibleRect.right, visibleRect.top) };

#undef POINT3D

    CVec3 pointsWS[4];
    Transform(pointsWS + 0, matrix, cornersSS[0]);
    Transform(pointsWS + 1, matrix, cornersSS[1]);
    Transform(pointsWS + 2, matrix, cornersSS[2]);
    Transform(pointsWS + 3, matrix, cornersSS[3]);

    planes.setsize(4);
    planes[0].SetFromPoints(sceneConstants.campos, pointsWS[0], pointsWS[1]); 
    planes[0].Normalize();                                                 
    planes[1].SetFromPoints(sceneConstants.campos, pointsWS[2], pointsWS[3]); 
    planes[1].Normalize();                                                 
    planes[2].SetFromPoints(sceneConstants.campos, pointsWS[3], pointsWS[0]); 
    planes[2].Normalize(); 
    planes[3].SetFromPoints(sceneConstants.campos, pointsWS[1], pointsWS[2]); 
    planes[3].Normalize();                                                 
    BuildPermutedPlanes();
  }

	void ConvexVolume::BuildNearAndFarPlanes( const SHMatrix& ViewProjectionMatrix )
	{
		FPlane	Temp;

		// Near clipping plane.
		GetFrustumNearPlane(Temp, ViewProjectionMatrix);
		planes.push_back(Temp);

		// Far clipping plane.
		GetFrustumFarPlane(Temp, ViewProjectionMatrix);
		planes.push_back(Temp);
	}


	void ConvexVolume::BuildPlanes( const SHMatrix& ViewProjectionMatrix )
	{
		FPlane	Temp;

		planes.clear();

		// Left clipping plane.
		GetFrustumLeftPlane(Temp, ViewProjectionMatrix);
		planes.push_back(Temp);

		// Right clipping plane.
		GetFrustumRightPlane(Temp, ViewProjectionMatrix);
		planes.push_back(Temp);

		// Top clipping plane.
		GetFrustumTopPlane(Temp, ViewProjectionMatrix);
		planes.push_back(Temp);

		// Bottom clipping plane.
		GetFrustumBottomPlane(Temp, ViewProjectionMatrix);
		planes.push_back(Temp);
	}

  void ConvexVolume::BuildPermutedPlanes()
	{
		ASSERT(planes.size());
		
		const int numToAdd = planes.size() / 4;
		const int numRemaining = planes.size() % 4;
    for(unsigned n = 0; n < planes.size(); ++n)
      planes[n].W += s_Displace;

		// Presize the array
		//permutedPlanes.reserve(numToAdd * 4 + (numRemaining ? 4 : 0));
		// For each set of four planes
		permutedPlanes.clear();
		for (int Count = 0, Offset = 0; Count < numToAdd; Count++, Offset += 4)
		{
			// Add them in SSE ready form
			permutedPlanes.push_back( FPlane(planes[Offset + 0].X,planes[Offset + 1].X,planes[Offset + 2].X,planes[Offset + 3].X) );
			permutedPlanes.push_back( FPlane(planes[Offset + 0].Y,planes[Offset + 1].Y,planes[Offset + 2].Y,planes[Offset + 3].Y) );
			permutedPlanes.push_back( FPlane(planes[Offset + 0].Z,planes[Offset + 1].Z,planes[Offset + 2].Z,planes[Offset + 3].Z) );
			permutedPlanes.push_back( FPlane(planes[Offset + 0].W,planes[Offset + 1].W,planes[Offset + 2].W,planes[Offset + 3].W) );
		}
		// Pad the last set so we have an even 4 planes of vert data
		if (numRemaining)
		{
			FPlane Last1, Last2, Last3, Last4;
			// Read the last set of verts
			switch (numRemaining)
			{
			case 3:
				{
					Last1 = planes[numToAdd * 4 + 0];
					Last2 = planes[numToAdd * 4 + 1];
					Last3 = planes[numToAdd * 4 + 2];
					Last4 = Last1;
					break;
				}
			case 2:
				{
					Last1 = planes[numToAdd * 4 + 0];
					Last2 = planes[numToAdd * 4 + 1];
					Last3 = Last4 = Last1;
					break;
				}
			case 1:
				{
					Last1 = planes[numToAdd * 4 + 0];
					Last2 = Last3 = Last4 = Last1;
					break;
				}
			default:
				{
					Last1 = FPlane();
					Last2 = Last3 = Last4 = Last1;
					break;
				}
			}
			// Add them in SIMD ready form
			permutedPlanes.push_back( FPlane(Last1.X,Last2.X,Last3.X,Last4.X) );
			permutedPlanes.push_back( FPlane(Last1.Y,Last2.Y,Last3.Y,Last4.Y) );
			permutedPlanes.push_back( FPlane(Last1.Z,Last2.Z,Last3.Z,Last4.Z) );
			permutedPlanes.push_back( FPlane(Last1.W,Last2.W,Last3.W,Last4.W) );
		}
	}

	bool ConvexVolume::IntersectSphere( const CVec3& Origin, const float Radius ) const
	{
		int planeCount = permutedPlanes.size();
		ASSERT(0 < planeCount && planeCount <= 12);
		ASSERT(planeCount % 4 == 0);

		// Load the origin & radius
		__m128 Orig = _mm_loadu_ps((const float*)&Origin);
		__m128 VRadius = _mm_load1_ps(&Radius);
		// Splat origin into 3 vectors
		__m128 OrigX = _mm_shuffle_ps( Orig, Orig, _MM_SHUFFLE(0,0,0,0) );
		__m128 OrigY = _mm_shuffle_ps( Orig, Orig, _MM_SHUFFLE(1,1,1,1) );
		__m128 OrigZ = _mm_shuffle_ps( Orig, Orig, _MM_SHUFFLE(2,2,2,2) );
		// Since we are moving straight through get a pointer to the data
		const FPlane* __restrict PermutedPlanePtr = (const FPlane*)&permutedPlanes[0];
		// Process four planes at a time until we have < 4 left

		for (INT Count = 0; Count < planeCount; Count += 4)
		{
			// Load 4 planes that are already all Xs, Ys, ...
			__m128 PlanesX = _mm_load_ps((const float*)PermutedPlanePtr);
			PermutedPlanePtr++;
			__m128 PlanesY = _mm_load_ps((const float*)PermutedPlanePtr);
			PermutedPlanePtr++;
			__m128 PlanesZ = _mm_load_ps((const float*)PermutedPlanePtr);
			PermutedPlanePtr++;
			__m128 PlanesW = _mm_load_ps((const float*)PermutedPlanePtr);
			PermutedPlanePtr++;
			// Calculate the distance (x * x) + (y * y) + (z * z) - w
			__m128 DistX = _mm_mul_ps(OrigX,PlanesX);
			__m128 DistY = _mm_add_ps( _mm_mul_ps(OrigY,PlanesY),DistX);
			__m128 DistZ = _mm_add_ps( _mm_mul_ps(OrigZ,PlanesZ),DistY);
			__m128 Distance = _mm_sub_ps(DistZ,PlanesW);

			// Check for completely outside
			if (_mm_movemask_ps(_mm_cmpgt_ps(Distance,VRadius)))
			{
				return false;
			}
		}
		return true;
	}

	float CalculateSegmentIntersectionParameter(const FPlane &plane, const CVec3 &v0, const CVec3 &v1)
	{
		const CVec3 &planeNorm = *((const CVec3*)&plane);
		float dot0 = planeNorm * v0;
		float dot1 = planeNorm * v1;
		return (dot0 - plane.W) / (dot0 - dot1);
	}

	int ConvexVolume::CalculateClipCodes(const CVec3 &vtx) const
	{
		// $BVS$ The loop must be unrolled for performance reasons
		int ccode = 0;
		for (unsigned int i = 0; i < planes.size(); ++i)
		{
			FPlane const &plane = planes[i];
			float distance = plane.W - (plane.X * vtx.x + plane.Y * vtx.y + plane.Z * vtx.z);
			ccode |= (FP_BITS(distance) & 0x80000000) >> (31 - i);
		}
		return ccode;
	}

	int ConvexVolume::DoesSegmentIntersect(const CVec3 &v0, int c0, const CVec3 &v1, int c1) const
	{
		float tLeft  = 0.0f;
		int   leftCCode = 0;
		float tRight = 1.0f;
		int   rightCCode = 0;
		int mask = 1;
		for (unsigned int i = 0; i < planes.size(); ++i, mask <<= 1)
		{
			if (c0 & mask)
			{
				float t = CalculateSegmentIntersectionParameter(planes[i], v0, v1);
				ASSERT(0.f <= t && t <= 1.00001f);
				if (tLeft < t)
				{
					tLeft = t;
					leftCCode = mask;
				}
			} else if (c1 & mask)
			{
				float t = CalculateSegmentIntersectionParameter(planes[i], v0, v1);
				ASSERT(0.f <= t && t <= 1.00001f);
				if (t < tRight)
				{
					tRight = t;
					rightCCode = mask;
				}
			}
		}

		return tRight > tLeft ? (leftCCode | rightCCode) : 0;
	}

	bool ConvexVolume::BuildFrustumAndPolyExtrusionIntersection( const ConvexVolume &frustum, 
																															 int numPoints, const CVec3 *pPoints, const CVec3 &camPos )
	{
		// We can't have too much points
		NI_VERIFY( numPoints < 128, "Too many points in polygon passed.", return false );
		ASSERT( numPoints > 2 );
		// Calculate clipcodes
		int clipCodes[128];
		int clipCodesAND = 0xFFFFFFFF;
		int clipCodesOR = 0;
		for (int i = 0; i < numPoints; ++i)
		{
			int ccode = frustum.CalculateClipCodes(pPoints[i]);
			clipCodes[i]  = ccode;
			clipCodesAND &= ccode;
			clipCodesOR  |= ccode;
		}
		// Check clip codes
		if (clipCodesAND != 0) // Intersection is empty?
			return false; 

		// Determine where camera is placed (in relation to poly plane)
		CVec3 polyNormal = (pPoints[2] - pPoints[0]) ^ (pPoints[1] - pPoints[0]);
		float sgn = Sign( polyNormal * ( camPos - pPoints[0] ) );

		// Push near plane
		planes.clear();
		//planes.push_back( frustum.planes[PLANE_NEAR] );

		// Special case - add all polygon lines
		if (clipCodesOR == 0)
		{
			for (int begNdx = numPoints - 1, endNdx = 0; endNdx < numPoints; begNdx = endNdx, ++endNdx)
			{
				CVec3 normal = sgn * (pPoints[endNdx] - camPos) ^ (pPoints[begNdx] - camPos);
				Normalize(&normal);
				planes.push_back( FPlane(normal.x, normal.y, normal.z, (normal * pPoints[endNdx])) );
			}
			//planes.push_back( frustum.planes[PLANE_FAR] );

      BuildPermutedPlanes();
			return true;
		}

		// Force adding far plane
		int frustumClipCodesOR = 0; //(1L << PLANE_FAR); 

		// Camera direction - average of camera plane normals
		CVec3 camDir(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < frustum.planes.size(); i++)
		{
			camDir.x += frustum.planes[i].X;
			camDir.y += frustum.planes[i].Y;
			camDir.z -= frustum.planes[i].Z; // Because of strange difference in coordinate systems
		}

		// Perform intersection
		bool bIntersects = false;
		bool bCameraDirectionInsidePolygon = true;
		for (int begNdx = numPoints - 1, endNdx = 0; endNdx < numPoints; begNdx = endNdx, ++endNdx)
		{
			// Check camera direction versus polygon planes
			CVec3 normal = sgn * (pPoints[endNdx] - camPos) ^ (pPoints[begNdx] - camPos);
			if (normal.Dot(camDir) < 0.0f)
				bCameraDirectionInsidePolygon = false;

			// Skip segment if it out of frustum
			int cAND = clipCodes[begNdx] & clipCodes[endNdx];
			if (cAND)
			{
				frustumClipCodesOR |= cAND; // Add these planes to resulting frustum
				continue;
			}

			if ( (clipCodes[begNdx] | clipCodes[endNdx]) != 0 )
			{
				int ccodes = frustum.DoesSegmentIntersect(pPoints[begNdx], clipCodes[begNdx], pPoints[endNdx], clipCodes[endNdx]);
				if (ccodes == 0) // no intersection 
					continue;

				frustumClipCodesOR |= ccodes; // Add these planes to resulting frustum
			}
			
		  // Add segment to resulting frustum
			Normalize(&normal);
			planes.push_back( FPlane(normal.x, normal.y, normal.z, (normal * pPoints[endNdx])) );

			// Frustum really intersect the convex
			bIntersects = true;
		}

		// No real intersection detected
 		if (!bIntersects)
		{
 			if (bCameraDirectionInsidePolygon)
 				frustumClipCodesOR = 0xFFFFFFFF; // Frustum is totally inside the polygon
 			else
      {
        NI_ASSERT(planes.size() == 0, NStr::StrFmt("Must be totally outside but %i planes found", planes.size()));
				return false; // Frustum is totally outside the polygon
      }
		}

		// Add the rest of planes from original frustum
		for (unsigned int i = 0; i < frustum.planes.size(); ++i)
		{
			if (frustumClipCodesOR & (1 << i))
				planes.push_back( frustum.planes[i] );
		}
	
		// Prepare optimization
		BuildPermutedPlanes();

		return true;
	}

	bool ConvexVolume::IntersectBox( const Render::AABB &aabb/*const CVec3& Origin, const CVec3& Extent*/ ) const
	{
		int planeCount = permutedPlanes.size();
		NI_ASSERT(0 < planeCount && planeCount <= 12, NStr::StrFmt("Invalid plane count (%i) for convex volume", planeCount));
		ASSERT(planeCount % 4 == 0);
		// Load the origin & extent
		ASSERT( (((uint)(void*)(&aabb)) & 0xF) == 0);
		__m128 Orig = _mm_load_ps((const float*)&aabb.center);
		__m128 Ext = _mm_load_ps((const float*)&aabb.halfSize);
		// Splat origin into 3 vectors
		__m128 OrigX = _mm_shuffle_ps(Orig, Orig, _MM_SHUFFLE(0,0,0,0));
		__m128 OrigY = _mm_shuffle_ps(Orig, Orig, _MM_SHUFFLE(1,1,1,1));
		__m128 OrigZ = _mm_shuffle_ps(Orig, Orig, _MM_SHUFFLE(2,2,2,2));
		//// Splat extent into 3 vectors
		//__m128 ExtentX = _mm_shuffle_ps(Ext, Ext, _MM_SHUFFLE(0,0,0,0));
		//__m128 ExtentY = _mm_shuffle_ps(Ext, Ext, _MM_SHUFFLE(1,1,1,1));
		//__m128 ExtentZ = _mm_shuffle_ps(Ext, Ext, _MM_SHUFFLE(2,2,2,2));
		// Splat the abs for the pushout calculation
		//__m128 AbsExt = _mm_and_ps(Ext, SSE_SIGN_MASK);
		__m128 AbsExtentX = _mm_shuffle_ps(Ext, Ext, _MM_SHUFFLE(0,0,0,0));
		__m128 AbsExtentY = _mm_shuffle_ps(Ext, Ext, _MM_SHUFFLE(1,1,1,1));
		__m128 AbsExtentZ = _mm_shuffle_ps(Ext, Ext, _MM_SHUFFLE(2,2,2,2));
		// Since we are moving straight through get a pointer to the data
		const FPlane* __restrict PermutedPlanePtr = (const FPlane*)&permutedPlanes[0];
		// Process four planes at a time until we have < 4 left
		for (int Count = 0; Count < planeCount; Count += 4)
		{
			// Load 4 planes that are already all Xs, Ys, ...
			__m128 PlanesX = _mm_load_ps((const float*)PermutedPlanePtr);
			PermutedPlanePtr++;
			__m128 PlanesY = _mm_load_ps((const float*)PermutedPlanePtr);
			PermutedPlanePtr++;
			__m128 PlanesZ = _mm_load_ps((const float*)PermutedPlanePtr);
			PermutedPlanePtr++;
			__m128 PlanesW = _mm_load_ps((const float*)PermutedPlanePtr);
			PermutedPlanePtr++;
			// Calculate the distance (x * x) + (y * y) + (z * z) - w
			__m128 DistX = _mm_mul_ps(OrigX,PlanesX);
			__m128 DistY = _mm_add_ps( _mm_mul_ps(OrigY,PlanesY),DistX);
			__m128 DistZ = _mm_add_ps( _mm_mul_ps(OrigZ,PlanesZ),DistY);
			__m128 Distance = _mm_sub_ps(DistZ,PlanesW);
			// Now do the push out Abs(x * x) + Abs(y * y) + Abs(z * z)
			__m128 ggg = VectorAbs(PlanesX);
			__m128 PushX = _mm_mul_ps(AbsExtentX,ggg);
			__m128 PushY = _mm_add_ps( _mm_mul_ps(AbsExtentY,VectorAbs(PlanesY)),PushX);
			__m128 PushOut = _mm_add_ps( _mm_mul_ps(AbsExtentZ,VectorAbs(PlanesZ)),PushY);

			//// Check for completely outside
			if( _mm_movemask_ps(_mm_cmpgt_ps(Distance,PushOut)) )
				return false;
		}
		return true;
	}

	float ConvexVolume::EstimateScreenSpaceSize( const Render::AABB& aabb ) const
	{
		CVec4 res;
		viewProjection.RotateHVector(&res, aabb.center);
		const float radius = fabs2(aabb.halfSize);
		return radius/res.w;
	}

  void TestConvexVolume()
	{
		ConvexVolume frustum;

		SHMatrix viewMtx;
		Identity( &viewMtx );

		SHMatrix projMtx;
		CreatePerspectiveProjectionMatrixRH( &projMtx, FP_PI2, 1.0f, 1.0f, 32.0f);

		// Build frustum finally
		SHMatrix viewProj = projMtx * viewMtx;
		frustum.BuildFrustum(viewProj);

		//
		CVec3 camPos( 0.0f, 0.0f, 0.0f );

		CVec3 points[4] = { CVec3(-1.f, 0.f, -1.f), CVec3(-1.f, 0.f, 1.f), CVec3(1.f, 0.f, 1.f), CVec3( 1.f, 0.f, -1.f) };
		for (int i = 0; i < 4; i++)
		{
			points[i].Mul(points[i], CVec3(10.0f, 10.0f, 10.0f));
			points[i] += CVec3(0.0f, 4.0f, 20.0f);
		}
		//CVec3 points[4] = { CVec3(-10.f, 0.f, 10.f), CVec3(-10.f, 0.f, 30.f), CVec3(35.f, 0.f, 30.f), CVec3( 15.f, 0.f, 0.f) };
		//CVec3 points[4] = { CVec3(-1.f, -0.1f, 0.f), CVec3(-25.f, -0.1f, 30.f), CVec3(5.f, -0.1f, 35.f), CVec3( 15.f, -0.1f, 10.f) };
		
		ConvexVolume intersection;
		intersection.BuildFrustumAndPolyExtrusionIntersection( frustum, 4, points, camPos );
	}

};

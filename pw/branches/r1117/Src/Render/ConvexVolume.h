#pragma once

#include "../System/fixedvector.h"
#include "../MemoryLib/NewDelete.h"

namespace Render
{
	struct AABB;
  struct SceneConstants;

	__declspec(align(16))
	struct FPlane
	{
		float X, Y, Z, W;
		FPlane() : X(0), Y(0), Z(0), W(0) {}
		FPlane(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
    FPlane(const CVec3& pt0, const CVec3& pt1, const CVec3& pt2)
    {
      SetFromPoints(pt0, pt1, pt2);
    }

    // Calculate plane from 3 points belonging to it
    void SetFromPoints(const CVec3& pt0, const CVec3& pt1, const CVec3& pt2);
    void Normalize(); // Normalize CVec3(X, Y, Z)
  };

	__declspec(align(16))
	class ConvexVolume
	{
		enum
		{
			PLANE_NEAR = 0,
			PLANE_LEFT,
			PLANE_RIGHT,
			PLANE_TOP,
			PLANE_BOTTOM,
			PLANE_FAR,
			PLANE_COUNT,
		};

		__declspec(align(16)) FixedVector<FPlane, 12> planes;
		__declspec(align(16)) FixedVector<FPlane, 12> permutedPlanes;
		__declspec(align(16)) SHMatrix viewProjection;

		void BuildPlanes(const SHMatrix& ViewProjectionMatrix);
		void BuildNearAndFarPlanes( const SHMatrix& ViewProjectionMatrix );
		void BuildPermutedPlanes();

		int  DoesSegmentIntersect(const CVec3 &v0, int c0, const CVec3 &v1, int c1) const;

	public:
		DECLARE_NEWDELETE_ALIGN16(ConvexVolume)

		bool Initialized() const { return planes.size(); }

		void BuildFrustum( const SHMatrix& viewProjectionMatrix );
    void BuildFrustum( const SceneConstants &sceneConstants, const RECT& visibleRect,
                       float screenWidth, float screenHeight );

    int  CalculateClipCodes(const CVec3 &vtx) const;

		bool BuildFrustumAndPolyExtrusionIntersection( const ConvexVolume &frustum, 
			                                             int numPoints, const CVec3 *pPoints, const CVec3 &camPos );
	
		bool IntersectSphere( const CVec3& origin, const float radius ) const;
		bool IntersectBox( const Render::AABB &aabb ) const;
		float EstimateScreenSpaceSize( const Render::AABB& aabb ) const;
	};

	// $BVS$ Test function! To be removed!
	//void TestConvexVolume();
};
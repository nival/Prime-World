#pragma once

#include "StaticMesh.h"

namespace Render
{
	class WaterConvexes
	{
	private:
		int   numConvexes;
		int   *pCounts; // Array of counts
		CVec2 *pPoints; // Array of points

		enum { MAX_POINTS_IN_CONVEX = 64 };

	public:
		struct FileHeader
		{
			int numConvexes;
			int numPoints;
		};

		WaterConvexes() 
			: numConvexes(0)
			, pCounts(0)
			, pPoints(0)
		{}

		~WaterConvexes() 
		{
			if (pCounts)
				delete [] pCounts;
		}

		void Create(const NDb::AABB &aabb);

		void Read(Stream &stream);

		void TransformConvex(CVec3 *pPointsOut, int numPoints, CVec2 const *pPoints, Matrix43 const &worldMatrix, float level);

		template <class F> void ForAll(F &f, Matrix43 const &worldMatrix, float level)
		{			
			CVec3 pointsStorage[MAX_POINTS_IN_CONVEX];
			
			CVec2 *pPnt = pPoints;
			for (int i = 0; i < numConvexes; i++)
			{
				// $BVS$ This could be optimized (move transform on OnWorldMatrixChange(), when present =)
				// Transform points in world coordinate system
				ASSERT( pCounts[i] <= MAX_POINTS_IN_CONVEX );
				int numPoints = Min(int(MAX_POINTS_IN_CONVEX), pCounts[i]);
				TransformConvex( pointsStorage, numPoints, pPnt, worldMatrix, level );
				// Call functor
				f(numPoints, pointsStorage);
				// Next convex
				pPnt += pCounts[i];
			}
		}

	};

} //namespace Render
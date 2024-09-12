#include "stdafx.h"
#include "WaterConvexes.h"

namespace Render
{
	void WaterConvexes::Create(const NDb::AABB &aabb)
	{
		// Allocate memory
		numConvexes = 1;
		pCounts = (int*)new char[ sizeof(int) + 4 * sizeof(CVec2) ];
		pPoints = (CVec2*)(pCounts + 1);
		// Init in CW order
		pCounts[0] = 4;
		pPoints[0].x = aabb.minX;
		pPoints[0].y = aabb.minY;
		pPoints[1].x = aabb.minX;
		pPoints[1].y = aabb.maxY;
		pPoints[2].x = aabb.maxX;
		pPoints[2].y = aabb.maxY;
		pPoints[3].x = aabb.maxX;
		pPoints[3].y = aabb.minY;
	}

	void WaterConvexes::Read(Stream &stream)
	{
		FileHeader *pHeader = (FileHeader*)stream.GetBuffer();
		numConvexes = pHeader->numConvexes;

		// Copy the rest of file
		int size = numConvexes * sizeof(int) + pHeader->numPoints * sizeof(CVec2);
		pCounts = (int*)new char[ size ];
		pPoints = (CVec2*)(pCounts + numConvexes);
		memcpy(pCounts, (int*)(pHeader + 1), size);
	}

	void WaterConvexes::TransformConvex(CVec3 *pPointsOut, int numPoints, CVec2 const *pPoints, Matrix43 const &worldMatrix, float level)
	{
		for (int i = 0; i < numPoints; ++i)
		{
			pPointsOut[i] = Transform( CVec3(pPoints[i].x, pPoints[i].y, level), worldMatrix );
		}
	}

} //namespace Render
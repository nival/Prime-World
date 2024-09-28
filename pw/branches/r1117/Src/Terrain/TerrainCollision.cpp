#include "stdafx.h"
#include "Terrain.h"
#include "TerrainLayerManager.h"

namespace Terrain
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool Terrain::IntersectWithGrid( CVec2* pPoint, const CVec2& dir ) const
    {
        NI_VERIFY( pPoint, "Invalid result storage!", return false; );
        
        // project point to grid space
        const float resolution = GetGridConstants().metersPerTile;

        const Array2DWrapper<TerrainAttributes const>& heights = heightManager.GetHeights();
        CVec2& point = *pPoint;
        const float epsilon = 0.0001f;
        const float topX = heights.GetSizeX() * resolution - epsilon;
        const float topY = heights.GetSizeY() * resolution - epsilon;

        if( point.x < -epsilon || point.y < -epsilon || point.x > topX || point.y > topY )
        {
            // ищем пересечение с верхней правой четвертью
            float t[4];
            t[0] = dir.y != 0 ? - point.y / dir.y : -1; // y = 0; OX
            t[1] = dir.x != 0 ? - point.x / dir.x : -1; // x = 0; OY
            t[2] = dir.y != 0 ? ( topY - point.y ) / dir.y : -1;
            t[3] = dir.x != 0 ? ( topX - point.x ) / dir.x : -1;

            float currentT = FP_MAX_VALUE;
            for( int i = 0; i < 4; ++i )
            {
                if( t[i] >= 0.f && currentT > t[i] )
                {
                    CVec2 temp = point + dir * t[i];
                    if( temp.x >= -epsilon && temp.y >= -epsilon && temp.x <= topX && temp.y <= topY )
                        currentT = t[i];
                }
            }

            if( currentT >= 0.f && currentT != FP_MAX_VALUE )
            {
                point += dir * currentT;
                return true;
            }

            return false;
        }
        else
            return true;
    }
}

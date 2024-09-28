#pragma once

#include "../System/staticarray.h"

namespace Terrain
{
  /**
  * NURBS patch with 16 CV
  * used regular grid for CV (initial state in Z = 0) 
  */
  struct Patch
  {
    ///< patch used 16 CV
    static const unsigned int NUMBER_OF_CV = 4;
    ///< distance between CV [m]
    static const float DISTANCE_BETWEEN_CV;
    ///< size of patch [m]
    static const float SIZE_OF_PATCH;
    ///< degree of NURBS
    static const int DEGREE = 3;

    ///< control vertexes
    const CVec3* pCVs[Patch::NUMBER_OF_CV];

    void SetRow( const CVec3* row, int index );

    /** compute NURBS point, passed normalized parameter values [0, 1) */
    CVec3 ComputeVertex( float u, float v ) const;

  private:
    float ComputeBSpline( int degree, int i, float t ) const;
  };
}

#include "stdafx.h"

#include "BezierSurface.h"
#include "../System/noncopyable.h"

namespace Terrain
{
  const float Patch::SIZE_OF_PATCH = 10.f;
  const float Patch::DISTANCE_BETWEEN_CV = Patch::SIZE_OF_PATCH / ( Patch::NUMBER_OF_CV - 1 );
  float knots[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void Patch::SetRow( const CVec3* row, int index )
  {
    pCVs[index] = row;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CVec3 Patch::ComputeVertex( float u, float v ) const
  {
    /*
    A NURBS-surface is define:

    S(u, v) = sum(i = 0, n)sum(j = 0, m) P_i,j * R_i,k, j,l(u, v) ,

    where
    w_i,j * N_i,k(u) * N_j,l(v)
    R_i,k,j,l(u, v) = ---------------------------------------------------------
    sum(r = 0, n){sum(s = 0, m){w_r,s * N_r,k(u) * N_s,l(v)}}
    */

    if( u < 0 ) u = 0.f;
    else if( u > 1.f ) u = 1.f;

    if( v < 0 ) v = 0.f;
    else if( v > 1.f ) v = 1.f;

    CVec3 vertex = VNULL3;
    static StaticArray<float, Patch::NUMBER_OF_CV> rationalBSplineResultsU;
    static StaticArray<float, Patch::NUMBER_OF_CV> rationalBSplineResultsV;

    for( int n = 0; n < NUMBER_OF_CV; ++n )
    {
      rationalBSplineResultsU[n] = ComputeBSpline( Patch::DEGREE, n, u );
      rationalBSplineResultsV[n] = ComputeBSpline( Patch::DEGREE, n, v );
    }

    for( int i = 0; i < NUMBER_OF_CV; ++i )
    {
      for( int j = 0; j < NUMBER_OF_CV; ++j )
      {
        vertex.Displace( pCVs[j][i], rationalBSplineResultsU[i]*rationalBSplineResultsV[j] );
      }
    }

    //
    return vertex;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  float Patch::ComputeBSpline( int degree, int i, float u ) const
  {
    //                      u - t_i
    // N_i,k(u) = ----------- * N_i,k-1(u) +
    //                       t_i+k - t_i

    //      t_i+k+1 - u
    // + ---------------  * N_i+1,k-1(u)    (2)
    //      t_i+k+1 - t_i+1

    // and

    //                          / 1, if t_i <= u < t_i+1
    // N_i,0(u) = <
    //                          \ 0, else

    // where t_i are the knots forming a knot vector
    // U = { t_0, t_1, ... , t_m }.

    if( degree != 0 )
    {
      const float temp1 = knots[i + degree] - knots[i];
      const float temp2 = knots[i + degree + 1] - knots[i + 1];
      //
      float res1 = 0.0f;
      if ( temp1 != 0.f )
      {
        float a = (u - knots[i]) / temp1;
        float currentBasis = ComputeBSpline( degree - 1, i, u );
        res1 = a * currentBasis;
      }

      float res2 = 0.0f;
      if ( temp2 != 0.0f )
      {
        float b = (knots[i + degree + 1] - u) / temp2;
        float nextBasis = ComputeBSpline( degree - 1, i + 1, u );
        res2 = b * nextBasis;
      }

      return res1 + res2;
    }
    else
    {
      if( knots[i] <= u && u < knots[i + 1] ) 
        return 1.0f;
      else 
        return 0.0f;
    }
  }
}

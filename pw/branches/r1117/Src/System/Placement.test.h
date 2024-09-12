//!Component("System/Math")
#include "cxxtest/TestSuite.h"
#include "stdafx.h"
#include "Placement.h"
#include "matrix43.h"

class PlacementTestSuite : public CxxTest::TestSuite 
{
public:
  void testAddition( void )
  {
    for ( int i = 0; i < 10000; i++ )
    {
      Placement a;
      Placement b;

      a.pos.x = (float)rand()/(float)RAND_MAX*10.0f;
      a.pos.y = (float)rand()/(float)RAND_MAX*10.0f;
      a.pos.z = (float)rand()/(float)RAND_MAX*10.0f;

      b.pos.x = (float)rand()/(float)RAND_MAX*10.0f;
      b.pos.y = (float)rand()/(float)RAND_MAX*10.0f;
      b.pos.z = (float)rand()/(float)RAND_MAX*10.0f;

      a.rot.x = (float)rand()/(float)RAND_MAX;
      a.rot.y = (float)rand()/(float)RAND_MAX;
      a.rot.z = (float)rand()/(float)RAND_MAX;
      a.rot.w = (float)rand()/(float)RAND_MAX;
      a.rot.Normalize();

      b.rot.x = (float)rand()/(float)RAND_MAX;
      b.rot.y = (float)rand()/(float)RAND_MAX;
      b.rot.z = (float)rand()/(float)RAND_MAX;
      b.rot.w = (float)rand()/(float)RAND_MAX;
      b.rot.Normalize();

      a.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
      a.scale.y = a.scale.x;
      a.scale.z = a.scale.x;
      while ( a.scale.x < 1.0e-1f )
      {
        a.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
        a.scale.y = a.scale.x;
        a.scale.z = a.scale.x;
      }

      b.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
      b.scale.y = b.scale.x;
      b.scale.z = b.scale.x;
      while ( b.scale.x < 1.0e-1f )
      {
        b.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
        b.scale.y = b.scale.x;
        b.scale.z = b.scale.x;
      }

      Placement fromMatrix;
      Placement res;

      Matrix43 a_m;
      Matrix43 b_m;
      Matrix43 res_m;
      a.GetMatrix( &a_m );
      b.GetMatrix( &b_m );
      res_m = a_m*b_m;
      fromMatrix.FromMatrix( res_m );

      res = a + b;

      res.rot.Normalize();
      if ( res.rot.w < 0 )
      {
        res.rot.Negate();
      }
      fromMatrix.rot.Normalize();
      if ( fromMatrix.rot.w < 0 )
      {
        fromMatrix.rot.Negate();
      }


      if ( fabs(res.rot.x - fromMatrix.rot.x) > 1.0e-3f
        || fabs(res.rot.y - fromMatrix.rot.y) > 1.0e-3f
        || fabs(res.rot.z - fromMatrix.rot.z) > 1.0e-3f
        || fabs(res.rot.w - fromMatrix.rot.w) > 1.0e-3f
        || fabs(res.pos.x - fromMatrix.pos.x) > 1.0e-3f
        || fabs(res.pos.y - fromMatrix.pos.y) > 1.0e-3f
        || fabs(res.pos.z - fromMatrix.pos.z) > 1.0e-3f
        || fabs(res.scale.x - fromMatrix.scale.x) > 1.0e-3f
        || fabs(res.scale.y - fromMatrix.scale.y) > 1.0e-3f
        || fabs(res.scale.z - fromMatrix.scale.z) > 1.0e-3f
        )
      {
        TS_FAIL("Bad add");
        return;
      }
    }
  }

  void testSub( void )
  {
    for ( int i = 0; i < 10000; i++ )
    {
      Placement a;
      Placement b;

      a.pos.x = (float)rand()/(float)RAND_MAX*10.0f;
      a.pos.y = (float)rand()/(float)RAND_MAX*10.0f;
      a.pos.z = (float)rand()/(float)RAND_MAX*10.0f;

      b.pos.x = (float)rand()/(float)RAND_MAX*10.0f;
      b.pos.y = (float)rand()/(float)RAND_MAX*10.0f;
      b.pos.z = (float)rand()/(float)RAND_MAX*10.0f;

      a.rot.x = (float)rand()/(float)RAND_MAX;
      a.rot.y = (float)rand()/(float)RAND_MAX;
      a.rot.z = (float)rand()/(float)RAND_MAX;
      a.rot.w = (float)rand()/(float)RAND_MAX;
      a.rot.Normalize();

      b.rot.x = (float)rand()/(float)RAND_MAX;
      b.rot.y = (float)rand()/(float)RAND_MAX;
      b.rot.z = (float)rand()/(float)RAND_MAX;
      b.rot.w = (float)rand()/(float)RAND_MAX;
      b.rot.Normalize();

      a.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
      a.scale.y = a.scale.x;
      a.scale.z = a.scale.x;
      while ( a.scale.x < 1.0e-1f )
      {
        a.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
        a.scale.y = a.scale.x;
        a.scale.z = a.scale.x;
      }

      b.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
      b.scale.y = b.scale.x;
      b.scale.z = b.scale.x;
      while ( b.scale.x < 1.0e-1f )
      {
        b.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
        b.scale.y = b.scale.x;
        b.scale.z = b.scale.x;
      }

      Placement fromMatrix;
      Placement res;

      Matrix43 a_m;
      Matrix43 b_m;
      Matrix43 res_m;
      a.GetMatrix( &a_m );
      b.GetMatrix( &b_m );
      res_m = a_m*b_m.GetInversed();
      fromMatrix.FromMatrix( res_m );

      res = a - b;

      res.rot.Normalize();
      if ( res.rot.w < 0 )
      {
        res.rot.Negate();
      }
      fromMatrix.rot.Normalize();
      if ( fromMatrix.rot.w < 0 )
      {
        fromMatrix.rot.Negate();
      }


      if ( fabs(res.rot.x - fromMatrix.rot.x) > 1.0e-3f
        || fabs(res.rot.y - fromMatrix.rot.y) > 1.0e-3f
        || fabs(res.rot.z - fromMatrix.rot.z) > 1.0e-3f
        || fabs(res.rot.w - fromMatrix.rot.w) > 1.0e-3f
        || fabs(res.pos.x - fromMatrix.pos.x) > 1.0e-3f
        || fabs(res.pos.y - fromMatrix.pos.y) > 1.0e-3f
        || fabs(res.pos.z - fromMatrix.pos.z) > 1.0e-3f
        || fabs(res.scale.x - fromMatrix.scale.x) > 1.0e-3f
        || fabs(res.scale.y - fromMatrix.scale.y) > 1.0e-3f
        || fabs(res.scale.z - fromMatrix.scale.z) > 1.0e-3f
        )
      {
        TS_FAIL("Bad sub");
        return;
      }
    }
  }
  void testConsist( void )
  {
    for ( int i = 0; i < 10000; i++ )
    {
      Placement a;
      Placement b;

      a.pos.x = (float)rand()/(float)RAND_MAX*10.0f;
      a.pos.y = (float)rand()/(float)RAND_MAX*10.0f;
      a.pos.z = (float)rand()/(float)RAND_MAX*10.0f;

      b.pos.x = (float)rand()/(float)RAND_MAX*10.0f;
      b.pos.y = (float)rand()/(float)RAND_MAX*10.0f;
      b.pos.z = (float)rand()/(float)RAND_MAX*10.0f;

      a.rot.x = (float)rand()/(float)RAND_MAX;
      a.rot.y = (float)rand()/(float)RAND_MAX;
      a.rot.z = (float)rand()/(float)RAND_MAX;
      a.rot.w = (float)rand()/(float)RAND_MAX;
      a.rot.Normalize();

      b.rot.x = (float)rand()/(float)RAND_MAX;
      b.rot.y = (float)rand()/(float)RAND_MAX;
      b.rot.z = (float)rand()/(float)RAND_MAX;
      b.rot.w = (float)rand()/(float)RAND_MAX;
      b.rot.Normalize();

      a.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
      a.scale.y = a.scale.x;
      a.scale.z = a.scale.x;
      while ( a.scale.x < 1.0e-1f )
      {
        a.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
        a.scale.y = a.scale.x;
        a.scale.z = a.scale.x;
      }

      b.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
      b.scale.y = b.scale.x;
      b.scale.z = b.scale.x;
      while ( b.scale.x < 1.0e-1f )
      {
        b.scale.x = (float)rand()/(float)RAND_MAX*10.0f;
        b.scale.y = b.scale.x;
        b.scale.z = b.scale.x;
      }

      Placement res;
      Placement res2;

      res = a - b + b;
      res2 = a + b - b;

      if ( fabs(res.rot.x - res2.rot.x) > 1.0e-3f
        || fabs(res.rot.y - res2.rot.y) > 1.0e-3f
        || fabs(res.rot.z - res2.rot.z) > 1.0e-3f
        || fabs(res.rot.w - res2.rot.w) > 1.0e-3f
        || fabs(res.pos.x - res2.pos.x) > 1.0e-3f
        || fabs(res.pos.y - res2.pos.y) > 1.0e-3f
        || fabs(res.pos.z - res2.pos.z) > 1.0e-3f
        || fabs(res.scale.x - res2.scale.x) > 1.0e-3f
        || fabs(res.scale.y - res2.scale.y) > 1.0e-3f
        || fabs(res.scale.z - res2.scale.z) > 1.0e-3f
        || fabs(res.rot.x - a.rot.x) > 1.0e-3f
        || fabs(res.rot.y - a.rot.y) > 1.0e-3f
        || fabs(res.rot.z - a.rot.z) > 1.0e-3f
        || fabs(res.rot.w - a.rot.w) > 1.0e-3f
        || fabs(res.pos.x - a.pos.x) > 1.0e-3f
        || fabs(res.pos.y - a.pos.y) > 1.0e-3f
        || fabs(res.pos.z - a.pos.z) > 1.0e-3f
        || fabs(res.scale.x - a.scale.x) > 1.0e-3f
        || fabs(res.scale.y - a.scale.y) > 1.0e-3f
        || fabs(res.scale.z - a.scale.z) > 1.0e-3f
        )
      {
        TS_FAIL("Bad consist");
        return;
      }
    }
  }

  void testForInvert()
  {
    Placement a;
    Placement b;

    a.pos.x = 0.0f;
    a.pos.y = 0.0f;
    a.pos.z = 0.0f;

    b.pos.x = 5.0f;
    b.pos.y = 0.0f;
    b.pos.z = 0.0f;

    a.rot.x = 0.0f;
    a.rot.y = 0.0f;
    a.rot.z = 0.0f;
    a.rot.w = 1.0f;
    a.rot.Normalize();

    b.rot.x = 0.0f;
    b.rot.y = 0.0f;
    b.rot.z = 0.0f;
    b.rot.w = 1.0f;
    b.rot.Normalize();

    a.scale.x = 2.0f;
    a.scale.y = a.scale.x;
    a.scale.z = a.scale.x;

    b.scale.x = 1.0f;
    b.scale.y = b.scale.x;
    b.scale.z = b.scale.x;

    Placement res;

    res = a + b;

    Placement res2 = -a + res;

    if ( fabs(b.rot.x - res2.rot.x) > 1.0e-3f
      || fabs(b.rot.y - res2.rot.y) > 1.0e-3f
      || fabs(b.rot.z - res2.rot.z) > 1.0e-3f
      || fabs(b.rot.w - res2.rot.w) > 1.0e-3f
      || fabs(b.pos.x - res2.pos.x) > 1.0e-3f
      || fabs(b.pos.y - res2.pos.y) > 1.0e-3f
      || fabs(b.pos.z - res2.pos.z) > 1.0e-3f
      || fabs(b.scale.x - res2.scale.x) > 1.0e-3f
      || fabs(b.scale.y - res2.scale.y) > 1.0e-3f
      || fabs(b.scale.z - res2.scale.z) > 1.0e-3f
      )
    {
      TS_FAIL("Bad invert");
      return;
    }
  }

  void testForInvert2()
  {
    Placement a;
    Placement b;

    a.pos.x = 10.0f;
    a.pos.y = 0.0f;
    a.pos.z = 0.0f;

    b.pos.x = 5.0f;
    b.pos.y = 0.0f;
    b.pos.z = 0.0f;

    a.rot.x = 0.0f;
    a.rot.y = 0.0f;
    a.rot.z = 0.0f;
    a.rot.w = 1.0f;
    a.rot.Normalize();

    b.rot.x = 0.0f;
    b.rot.y = 0.0f;
    b.rot.z = 0.0f;
    b.rot.w = 1.0f;
    b.rot.Normalize();

    a.scale.x = 2.0f;
    a.scale.y = a.scale.x;
    a.scale.z = a.scale.x;

    b.scale.x = 1.0f;
    b.scale.y = b.scale.x;
    b.scale.z = b.scale.x;

    Placement res;

    res = a + b;

    Placement res2 = -a + res;

    if ( fabs(b.rot.x - res2.rot.x) > 1.0e-3f
      || fabs(b.rot.y - res2.rot.y) > 1.0e-3f
      || fabs(b.rot.z - res2.rot.z) > 1.0e-3f
      || fabs(b.rot.w - res2.rot.w) > 1.0e-3f
      || fabs(b.pos.x - res2.pos.x) > 1.0e-3f
      || fabs(b.pos.y - res2.pos.y) > 1.0e-3f
      || fabs(b.pos.z - res2.pos.z) > 1.0e-3f
      || fabs(b.scale.x - res2.scale.x) > 1.0e-3f
      || fabs(b.scale.y - res2.scale.y) > 1.0e-3f
      || fabs(b.scale.z - res2.scale.z) > 1.0e-3f
      )
    {
      TS_FAIL("Bad invert");
      return;
    }
  }

  void CheckPlacementTransform(const Placement& pl, const CVec3& v)
  {
    Matrix43 m;
    pl.GetMatrix(&m);

    CVec3 outPos;
    pl.Transform(v, outPos);

    CVec3 pos2 = Transform(v, m);

    //TS_ASSERT( fabs(outPos - pos2) < 1.0e-3f );
  }

  void testTransformPlacement()
  {
    CVec3 vecs[] ={ CVec3(0, 0, 0), CVec3(1, 0, 0), CVec3(0, 1, 0), CVec3(0, 0, 1), CVec3(1, 1, 0), CVec3(1, 0, 1), CVec3(0, 1, 1), CVec3(1, 1, 1) };
    int numVecs = ARRAY_SIZE(vecs);

    CQuat rotations[] ={ 
          CQuat(0, 0, 0)
        , CQuat(FP_PI2, 0, 0)
        , CQuat(0, FP_PI2, 0)
        , CQuat(0, 0, FP_PI2)
        , CQuat(FP_PI2, 0, FP_PI2)
        , CQuat(FP_PI2, FP_PI2, 0)
        , CQuat(FP_PI2, FP_PI2, FP_PI2)
    };
    int numRotations = ARRAY_SIZE(rotations);

    CVec3 scales[] ={ CVec3(1, 1, 1), CVec3(2, 1, 1), CVec3(1, 2, 1), CVec3(1, 1, 2), CVec3(2, 2, 1), CVec3(2, 1, 2), CVec3(1, 2, 2), CVec3(-1, 1, 1) };
    int numScales = ARRAY_SIZE(scales);

    for(int v =0; v < numVecs; ++v)
    {
      for(int p = 0; p < numVecs; ++p)
      {
        for(int r = 0; r < numRotations; ++r)
        {
          for(int s = 0; s < numScales; ++s)
          {
            CheckPlacementTransform( Placement(vecs[p], rotations[r], scales[s]), vecs[v] );
          }
        }
        
      }
    }
  }
};

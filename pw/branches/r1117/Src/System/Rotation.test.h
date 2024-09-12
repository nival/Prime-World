//!Component("System/Math")
//!Component("System/Commands")
#include "cxxtest/TestSuite.h"
#include "stdafx.h"
#include "Placement.h"
#include "matrix43.h"

static const int NUM_ITER = 100000;

class RotationTestSuite : public CxxTest::TestSuite 
{
public:
  void testConvertFromEulerToQuatBoth( void )
  {
    for ( int i = 0; i < NUM_ITER; i++ )
    {
      CQuat rot;
      CQuat final;

      rot.x = (float)rand()/(float)RAND_MAX;
      rot.y = (float)rand()/(float)RAND_MAX;
      rot.z = (float)rand()/(float)RAND_MAX;
      rot.w = (float)rand()/(float)RAND_MAX;
      rot.Normalize();

      float yaw, pitch, roll;
      rot.DecompEulerAngles( &yaw, &pitch, &roll );
      final.FromEulerAngles( yaw, pitch, roll );


      if ( fabs(rot.x - final.x) > 1.0e-3f
        || fabs(rot.y - final.y) > 1.0e-3f
        || fabs(rot.z - final.z) > 1.0e-3f
        || fabs(rot.w - final.w) > 1.0e-3f
        )
      {
        TS_FAIL("Bad Euler/Quat transform");
        return;
      }
    }
  }

  void testSlerp( void )
  {
    for ( int i = 0; i < NUM_ITER; i++ )
    {
      float factor;
      factor = (float)rand()/(float)RAND_MAX;

      CQuat rot;
      float yaw, pitch, roll;
      yaw = (float)rand()/(float)RAND_MAX*3.1415f;
      pitch = 1.0f;
      roll = 1.0f;
      rot.FromEulerAngles( yaw, pitch, roll );
      rot.Normalize();

      CQuat final;
      float finalyaw, finalpitch, finalroll;
      finalyaw = (float)rand()/(float)RAND_MAX*3.1415f;
      finalpitch = 1.0f;
      finalroll = 1.0f;
      final.FromEulerAngles( finalyaw, finalpitch, finalroll );
      final.Normalize();

      CQuat slrot;
      slrot.Slerp( factor, rot, final );
      
      float rotyaw, rotpitch, rotroll;
      float eueyaw, euepitch, eueroll;

      slrot.DecompEulerAngles( &rotyaw, &rotpitch, &rotroll );
      eueyaw = yaw*(1.0f-factor)+finalyaw*factor;
      euepitch = pitch*(1.0f-factor)+finalpitch*factor;
      eueroll = roll*(1.0f-factor)+finalroll*factor;

      TS_ASSERT_DELTA(eueyaw,rotyaw,1.0e-2f);
      TS_ASSERT_DELTA(euepitch,rotpitch,1.0e-2f);
      TS_ASSERT_DELTA(eueroll,rotroll,1.0e-2f);
    }
  }

  void testFromQuatToQuat()
  {
    for ( int i = 0; i < NUM_ITER; i++ )
    {
      CQuat rot;

      rot.x = (float)rand()/(float)RAND_MAX;
      rot.y = (float)rand()/(float)RAND_MAX;
      rot.z = (float)rand()/(float)RAND_MAX;
      rot.w = (float)rand()/(float)RAND_MAX;
      rot.Normalize();

      if ( rot.w < 0.01f ) continue;

      Matrix43 mat;
      Placement pl(VNULL3,rot,CVec3(1.0f,1.0f,1.0f));
      pl.GetMatrix(&mat);
      Placement finpl;
      finpl.FromMatrix(mat);

      if ( fabs(rot.x - finpl.rot.x) > 1.0e-3f && fabs(rot.x + finpl.rot.x) > 1.0e-3f )
      {
        TS_FAIL( "Quat to Matrix and to Quat test failed!" );
      }
      if ( fabs(rot.y - finpl.rot.y) > 1.0e-3f && fabs(rot.y + finpl.rot.y) > 1.0e-3f )
      {
        TS_FAIL( "Quat to Matrix and to Quat test failed!" );
      }
      if ( fabs(rot.z - finpl.rot.z) > 1.0e-3f && fabs(rot.z + finpl.rot.z) > 1.0e-3f )
      {
        TS_FAIL( "Quat to Matrix and to Quat test failed!" );
      }
      if ( fabs(rot.w - finpl.rot.w) > 1.0e-3f && fabs(rot.w + finpl.rot.w) > 1.0e-3f )
      {
        TS_FAIL( "Quat to Matrix and to Quat test failed!" );
      }

    }
  }
};

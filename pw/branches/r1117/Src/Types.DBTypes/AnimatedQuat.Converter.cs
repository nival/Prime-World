using libdb.Animated;
using System;

namespace DBTypes
{
  public sealed partial class AnimatedQuat
  {
		public static class MatrixUtils
		{
      public static void ToEuler( Quat rotation, out float x, out float y, out float z )
      {
        // Неверный код, но под него забиты данные! 
        bool isAllOk = true;
        {
          float x2 = rotation.x*rotation.x;
          float y2 = rotation.y*rotation.y;
          float z2 = rotation.z*rotation.z;
          float w2 = rotation.w*rotation.w;

          x = 180.0f/(float) Math.PI*
              (float) Math.Atan2( 2.0*(rotation.z*rotation.y + rotation.w*rotation.x), w2 + z2 - x2 - y2 );
          y = -180.0f/(float) Math.PI*(float) Math.Asin( 2.0*(rotation.z*rotation.x - rotation.w*rotation.y) );
          z = 180.0f/(float) Math.PI*
              (float) Math.Atan2( 2.0*(rotation.w*rotation.z + rotation.x*rotation.y), w2 - z2 + x2 - y2 );

          if ( float.IsNaN( x ) || float.IsNaN( y ) || float.IsNaN( z ) || float.IsInfinity( x ) || float.IsInfinity( y ) || float.IsInfinity( z ) )
          {
            // Все плохо, будем использовать правильный код!
            isAllOk = false;
          }
        }
        
        // Правильный код с http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
        if ( !isAllOk )
        {
          double sqw = rotation.w*rotation.w;
          double sqx = rotation.x*rotation.x;
          double sqy = rotation.y*rotation.y;
          double sqz = rotation.z*rotation.z;
          double unit = sqx + sqy + sqz + sqw;
          double test = rotation.x*rotation.y + rotation.z*rotation.w;
          if( test > 0.499*unit )
          {
            // singularity at north pole
            y = 180.0f/(float) Math.PI*(float) (2.0f*Math.Atan2( rotation.x, rotation.w ));
            z = 180.0f/(float) Math.PI*(float) Math.PI/2;
            x = 0;
            return;
          }
          if( test < -0.499*unit )
          {
            // singularity at south pole
            y = 180.0f/(float) Math.PI*(float) (-2.0*Math.Atan2( rotation.x, rotation.w ));
            z = 180.0f/(float) Math.PI*(float) -Math.PI/2;
            x = 0;
            return;
          }
          y = 180.0f/(float) Math.PI*
              (float) Math.Atan2( 2.0*rotation.y*rotation.w - 2.0*rotation.x*rotation.z, sqx - sqy - sqz + sqw );
          z = 180.0f/(float) Math.PI*(float) Math.Asin( 2.0*test/unit );
          x = 180.0f/(float) Math.PI*
              (float) Math.Atan2( 2.0*rotation.x*rotation.w - 2.0*rotation.y*rotation.z, -sqx + sqy - sqz + sqw );
        }
      }

		  public static void FromEuler(out Quat rotation, float x, float y, float z)
			{
				rotation = new Quat();

				float yaw = x / 180.0f * (float)Math.PI;
				float pitch = y / 180.0f * (float)Math.PI;
				float roll = z / 180.0f * (float)Math.PI;

				float fHalfYaw = yaw * 0.5f;
				float fHalfPitch = pitch * 0.5f;
				float fHalfRoll = roll * 0.5f;

				float fCosYaw = (float)Math.Cos(fHalfYaw);
				float fSinYaw = (float)Math.Sin(fHalfYaw);
				float fCosPitch = (float)Math.Cos(fHalfPitch);
				float fSinPitch = (float)Math.Sin(fHalfPitch);
				float fCosRoll = (float)Math.Cos(fHalfRoll);
				float fSinRoll = (float)Math.Sin(fHalfRoll);

				rotation.x = fSinRoll * fCosPitch * fCosYaw - fCosRoll * fSinPitch * fSinYaw;
				rotation.y = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
				rotation.z = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
				rotation.w = fCosRoll * fCosPitch * fCosYaw + fSinRoll * fSinPitch * fSinYaw;
			}
		}

    public struct Converter : IComplexConverter<Quat, float>
    {

      public Quat ConvertTo( float[] tracks )
      {
        float anglesZ, anglesY, anglesX;

        anglesZ = tracks[0];
        anglesY = tracks[1];
        anglesX = tracks[2];

        Quat result = new Quat();

        MatrixUtils.FromEuler( out result, anglesX, anglesY, anglesZ );

        return result;
      }

      public void ConvertFrom<TAlgorithm>( int index, Quat value, AnimatedTracks<float, TAlgorithm> tracks ) where TAlgorithm : IAnimatedAlgorithm<float>
      {
				float anglesZ, anglesY, anglesX;

				MatrixUtils.ToEuler(value, out anglesX, out anglesY, out anglesZ);

				tracks[0].SetValue(index, anglesX);
				tracks[1].SetValue(index, anglesY);
				tracks[2].SetValue(index, anglesZ);
      }

      public int TrackCount { get { return 3; } }
    }
  }
}
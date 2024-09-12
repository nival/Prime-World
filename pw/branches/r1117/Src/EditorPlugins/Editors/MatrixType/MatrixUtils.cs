using System;

namespace EditorPlugins.Editors.MatrixType
{
	internal static class MatrixUtils
	{
		internal static void ToEuler( DBTypes.Quat rotation, out float x, out float y, out float z )
		{
			float x2 = rotation.x * rotation.x;
			float y2 = rotation.y * rotation.y;
			float z2 = rotation.z * rotation.z;
			float w2 = rotation.w * rotation.w;

			x = 180.0f / (float)Math.PI * (float)Math.Atan2( 2.0 * (rotation.w * rotation.z + rotation.x * rotation.y), w2 - z2 + x2 - y2 );
			y = -180.0f / (float)Math.PI * (float)Math.Asin( 2.0 * (rotation.z * rotation.x - rotation.w * rotation.y) );
			z = 180.0f / (float)Math.PI * (float)Math.Atan2( 2.0 * (rotation.z * rotation.y + rotation.w * rotation.x), w2 + z2 - x2 - y2 );
		}

		internal static void FromEuler( out DBTypes.Quat rotation, float x, float y, float z )
		{
			rotation = new DBTypes.Quat( null );

			float yaw = x / 180.0f * (float)Math.PI;
			float pitch = y / 180.0f * (float)Math.PI;
			float roll = z / 180.0f * (float)Math.PI;

			float fHalfYaw = yaw * 0.5f;
			float fHalfPitch = pitch * 0.5f;
			float fHalfRoll = roll * 0.5f;

			float fCosYaw = (float)Math.Cos( fHalfYaw );
			float fSinYaw = (float)Math.Sin( fHalfYaw );
			float fCosPitch = (float)Math.Cos( fHalfPitch );
			float fSinPitch = (float)Math.Sin( fHalfPitch );
			float fCosRoll = (float)Math.Cos( fHalfRoll );
			float fSinRoll = (float)Math.Sin( fHalfRoll );

			rotation.x = fSinRoll * fCosPitch * fCosYaw - fCosRoll * fSinPitch * fSinYaw;
			rotation.y = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
			rotation.z = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
			rotation.w = fCosRoll * fCosPitch * fCosYaw + fSinRoll * fSinPitch * fSinYaw;
		}

		internal static void Compose( out DBTypes.Matrix source, DBTypes.Vec3 translation, DBTypes.Quat rotation, float scale )
		{
			source = new DBTypes.Matrix( null );
			source.w1 = translation.x;
			source.w2 = translation.y;
			source.w3 = translation.z;

			float tx = rotation.x + rotation.x;
			float ty = rotation.y + rotation.y;
			float tz = rotation.z + rotation.z;
			float twx = tx * rotation.w;
			float twy = ty * rotation.w;
			float twz = tz * rotation.w;
			float txx = tx * rotation.x;
			float txy = ty * rotation.x;
			float txz = tz * rotation.x;
			float tyy = ty * rotation.y;
			float tyz = tz * rotation.y;
			float tzz = tz * rotation.z;

			source.x1 = 1.0f - (tyy + tzz);
			source.y1 = txy - twz;
			source.z1 = txz + twy;

			source.x2 = txy + twz;
			source.y2 = 1.0f - (txx + tzz);
			source.z2 = tyz - twx;

			source.x3 = txz - twy;
			source.y3 = tyz + twx;
			source.z3 = 1.0f - (txx + tyy);

			source.x1 *= scale;
			source.x2 *= scale;
			source.x3 *= scale;
			source.y1 *= scale;
			source.y2 *= scale;
			source.y3 *= scale;
			source.z1 *= scale;
			source.z2 *= scale;
			source.z3 *= scale;
		}

		internal static void Decompose( DBTypes.Matrix source, out DBTypes.Vec3 translation, out DBTypes.Quat rotation, out float scale )
		{
			translation = new DBTypes.Vec3( null );
			rotation = new DBTypes.Quat( null );

			// extract translation
			translation.x = source.w1;
			translation.y = source.w2;
			translation.z = source.w3;

			// extract scale
			scale = (float)Math.Sqrt( source.x1 * source.x1 + source.x2 * source.x2 + source.x3 * source.x3 );

			// extract rotation
			if ( 1.0f + source.x1 + source.y2 + source.z3 > 10e-6f )
			{
				rotation.w = (float)Math.Sqrt( 1.0f + source.x1 / scale + source.y2 / scale + source.z3 / scale ) / 2.0f;
				rotation.x = (source.z2 / scale - source.y3 / scale) / (4.0f * rotation.w);
				rotation.y = (source.x3 / scale - source.z1 / scale) / (4.0f * rotation.w);
				rotation.z = (source.y1 / scale - source.x2 / scale) / (4.0f * rotation.w);
			}
			else if ( source.x1 > source.y2 && source.x1 > source.z3 )
			{
				rotation.x = (float)Math.Sqrt( 1.0f + source.x1 / scale - source.y2 / scale - source.z3 / scale ) / 2.0f;
				rotation.y = (source.x2 / scale + source.y1 / scale) / (4.0f * rotation.x);
				rotation.z = (source.x3 / scale + source.z1 / scale) / (4.0f * rotation.x);
				rotation.w = (source.z2 / scale - source.y3 / scale) / (4.0f * rotation.x);
			}
			else if ( source.y2 > source.z3 )
			{
				rotation.y = (float)Math.Sqrt( 1.0f + source.y2 / scale - source.x1 / scale - source.z3 / scale ) / 2.0f;
				rotation.x = (source.x2 / scale + source.y1 / scale) / (4.0f * rotation.y);
				rotation.z = (source.y3 / scale + source.z2 / scale) / (4.0f * rotation.y);
				rotation.w = (source.x3 / scale - source.z1 / scale) / (4.0f * rotation.y);
			}
			else
			{
				rotation.z = (float)Math.Sqrt( 1.0f + source.z3 / scale - source.x1 / scale - source.y2 / scale ) / 2.0f;
				rotation.x = (source.x3 / scale + source.z1 / scale) / (4.0f * rotation.z);
				rotation.y = (source.y3 / scale + source.z2 / scale) / (4.0f * rotation.z);
				rotation.w = (source.y1 / scale - source.x2 / scale) / (4.0f * rotation.z);
			}

			// renormalize rotation quaternion
			float len = (float)Math.Sqrt( rotation.x * rotation.x + rotation.y * rotation.y + rotation.z * rotation.z + rotation.w * rotation.w );
			rotation.x *= -len;
			rotation.y *= -len;
			rotation.z *= -len;
			rotation.w *= len;
		}

    internal static void Decompose(DBTypes.Matrix source, out DBTypes.Placement placement)
    {
      DBTypes.Vec3 translation = new DBTypes.Vec3(null);
      DBTypes.Quat rotation = new DBTypes.Quat(null);
      float scale;

      Decompose(source, out translation, out rotation, out scale);

      placement = new DBTypes.Placement();
      placement.location = translation;
      placement.rotation = rotation;
      placement.scale.x = scale;
      placement.scale.y = scale;
      placement.scale.z = scale;
    }
  }
}

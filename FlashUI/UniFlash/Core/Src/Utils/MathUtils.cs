using System;
using UnityEngine;

namespace Flash.Utils
{
  public class MathUtils
  {
    private static Vector3[] _rowsCache = new Vector3[3];
    public static bool DecomposeMatrix( Matrix4x4 matrix, ref DecomposedMatrix tran )
    {
      // Set identity
      tran.scale = Vector3.one;

      Matrix4x4 locmat = matrix;

      if ( locmat[3, 3] == 0 )
        return false;

      int i, j;

      for ( i = 0; i < 4; ++i )
        for ( j = 0; j < 4; ++j )
          locmat[i, j] /= locmat[3, 3];

      // pmat is used to solve for perspective, but it also provides
      // an easy way to test for singularity of the upper 3x3 component.

      Matrix4x4 pmat = locmat;

      for ( i = 0; i < 3; i++ )
        pmat[3, i] = 0;

      pmat[3, 3] = 1;

      if ( GetMatrixDeterminant( pmat ) == 0 )
        return false;

      // First, isolate perspective.  This is the messiest.

      if ( locmat[3, 0] != 0 || locmat[3, 1] != 0 || locmat[3, 2] != 0 )
      {
        Vector4 prhs, psol;

        //  prhs is the right hand side of the equation.

        prhs.x = locmat[3, 0];
        prhs.y = locmat[3, 1];
        prhs.z = locmat[3, 2];
        prhs.w = locmat[3, 3];

        // Solve the equation by inverting pmat and multiplying
        // prhs by the inverse.  (This is the easiest way, not
        // necessarily the best.)
        // inverse function (and det4x4, above) from the Matrix
        // Inversion gem in the first volume.

        Matrix4x4 invpmat = pmat.inverse;
        Matrix4x4 tinvpmat = invpmat.transpose;
        psol = tinvpmat.MultiplyPoint( prhs );

        tran.perspX = psol.x;
        tran.perspY = psol.y;
        tran.perspZ = psol.z;
        tran.perspW = psol.w;

        // Clear the perspective partition.
        locmat[3, 0] = 0;
        locmat[3, 1] = 0;
        locmat[3, 2] = 0;
        locmat[3, 3] = 0;
      }
      else // No perspective. 
        tran.perspX = tran.perspY = tran.perspZ = tran.perspW = 0;

      // Next take care of translation (easy).
      tran.position.x = locmat[0, 3];
      locmat[0, 3] = 0;
      tran.position.y = locmat[1, 3];
      locmat[1, 3] = 0;
      tran.position.z = locmat[2, 3];
      locmat[2, 3] = 0;

      // Now get scale and shear.

      for ( i = 0; i < 3; i++ )
      {
        _rowsCache[i].x = locmat[0, i];
        _rowsCache[i].y = locmat[1, i];
        _rowsCache[i].z = locmat[2, i];
      }

      // Compute X scale factor and normalize first row. 
      tran.scale.x = _rowsCache[0].magnitude;
      _rowsCache[0].Normalize();

      // Compute XY shear factor and make 2nd row orthogonal to 1st.
      tran.shearXY = Vector3.Dot( _rowsCache[0], _rowsCache[1] );
      _rowsCache[1] = _rowsCache[1] - _rowsCache[0] * tran.shearXY;

      // Now, compute Y scale and normalize 2nd row.
      tran.scale.y = _rowsCache[1].magnitude;
      _rowsCache[1].Normalize();
      tran.shearXY /= tran.scale.y;

      // Compute XZ and YZ shears, orthogonalize 3rd row.
      tran.shearXZ = Vector3.Dot( _rowsCache[0], _rowsCache[2] );
      _rowsCache[2] = _rowsCache[2] - _rowsCache[0] * tran.shearXZ;
      tran.shearYZ = Vector3.Dot( _rowsCache[1], _rowsCache[2] );
      _rowsCache[2] = _rowsCache[2] - _rowsCache[1] * tran.shearYZ;

      // Next, get Z scale and normalize 3rd row.
      tran.scale.z = _rowsCache[2].magnitude;
      _rowsCache[2].Normalize();
      tran.shearXZ /= tran.scale.z;
      tran.shearYZ /= tran.scale.z;

      // At this point, the matrix (in rows[]) is orthonormal.
      // Check for a coordinate system flip.  If the determinant
      // is -1, then negate the matrix and the scaling factors.
      Vector3 pdum3;
      pdum3 = Vector3.Cross( _rowsCache[1], _rowsCache[2] );
      if ( Vector3.Dot( _rowsCache[0], pdum3 ) < 0 )
      {
        tran.scale.x *= -1;
        tran.scale.y *= -1;
        tran.scale.z *= -1;
        for ( i = 0; i < 3; i++ )
        {
          _rowsCache[i] *= -1;
        }
      }

      // Now, get the rotations out, as described in the gem.
      tran.rotation.y = Mathf.Asin( -_rowsCache[0].z );
      if ( Mathf.Cos( tran.rotation.y ) != 0 )
      {
        tran.rotation.x = Mathf.Atan2( _rowsCache[1].z, _rowsCache[2].z );
        tran.rotation.z = Mathf.Atan2( _rowsCache[0].y, _rowsCache[0].x );
      }
      else
      {
        tran.rotation.x = Mathf.Atan2( -_rowsCache[2].x, _rowsCache[1].y );
        tran.rotation.z = 0;
      }

      tran.rotation *= Mathf.Rad2Deg;

      return true;
    }
    public static bool DecomposeMatrixNoShear( Matrix4x4 source, ref DecomposedMatrix tran )
    {
      // To row style
      source = source.transpose;

      Vector3 translation = Vector3.zero;
      Quaternion rotation = Quaternion.identity;
      Vector3 scale = Vector3.one;

      // extract translation
      translation[0] = source[3, 0];
      translation[1] = source[3, 1];
      translation[2] = source[3, 2];

      // extract scale
      scale[0] = new Vector3( source[0, 0], source[0, 1], source[0, 2] ).magnitude;
      scale[1] = new Vector3( source[1, 0], source[1, 1], source[1, 2] ).magnitude;
      scale[2] = new Vector3( source[2, 0], source[2, 1], source[2, 2] ).magnitude;

      // extract rotation
      if ( 1 + source[0, 0] + source[1, 1] + source[2, 2] > Single.Epsilon/* std::numeric_limits<T>::epsilon()*/)
      {
        rotation.w = Mathf.Sqrt( 1 + source[0, 0] / scale[0] + source[1, 1] / scale[1] + source[2, 2] / scale[2] ) / 2;
        rotation.x = ( source[2, 1] / scale[2] - source[1, 2] / scale[1] ) / ( 4 * rotation.w );
        rotation.y = ( source[0, 2] / scale[0] - source[2, 0] / scale[2] ) / ( 4 * rotation.w );
        rotation.z = ( source[1, 0] / scale[1] - source[0, 1] / scale[0] ) / ( 4 * rotation.w );
      }
      else if ( source[0, 0] > source[1, 1] && source[0, 0] > source[2, 2] )
      {
        rotation.x = Mathf.Sqrt( 1 + source[0, 0] / scale[0] - source[1, 1] / scale[1] - source[2, 2] / scale[2] ) / 2;
        rotation.y = ( source[0, 1] / scale[0] + source[1, 0] / scale[1] ) / ( 4 * rotation.x );
        rotation.z = ( source[0, 2] / scale[0] + source[2, 0] / scale[2] ) / ( 4 * rotation.x );
        rotation.w = ( source[2, 1] / scale[2] - source[1, 2] / scale[1] ) / ( 4 * rotation.x );
      }
      else if ( source[1, 1] > source[2, 2] )
      {
        rotation.y = Mathf.Sqrt( 1 + source[1, 1] / scale[1] - source[0, 0] / scale[0] - source[2, 2] / scale[2] ) / 2;
        rotation.x = ( source[0, 1] / scale[0] + source[1, 0] / scale[1] ) / ( 4 * rotation.y );
        rotation.z = ( source[1, 2] / scale[1] + source[2, 1] / scale[2] ) / ( 4 * rotation.y );
        rotation.w = ( source[0, 2] / scale[0] - source[2, 0] / scale[2] ) / ( 4 * rotation.y );
      }
      else
      {
        rotation.z = Mathf.Sqrt( 1 + source[2, 2] / scale[2] - source[0, 0] / scale[0] - source[1, 1] / scale[1] ) / 2;
        rotation.x = ( source[0, 2] / scale[0] + source[2, 0] / scale[2] ) / ( 4 * rotation.z );
        rotation.y = ( source[1, 2] / scale[1] + source[2, 1] / scale[2] ) / ( 4 * rotation.z );
        rotation.w = ( source[1, 0] / scale[1] - source[0, 1] / scale[0] ) / ( 4 * rotation.z );
      }

      // renormalize rotation quaternion
      //rotation = Normalize(rotation);

      tran.position = translation;
      tran.rotation = rotation.eulerAngles;
      tran.scale = scale;

      return true;
    }
    public static float GetMatrixDeterminant( Matrix4x4 m )
    {
      return
       m[0, 3] * m[1, 2] * m[2, 1] * m[3, 0] - m[0, 2] * m[1, 3] * m[2, 1] * m[3, 0] -
       m[0, 3] * m[1, 1] * m[2, 2] * m[3, 0] + m[0, 1] * m[1, 3] * m[2, 2] * m[3, 0] +
       m[0, 2] * m[1, 1] * m[2, 3] * m[3, 0] - m[0, 1] * m[1, 2] * m[2, 3] * m[3, 0] -
       m[0, 3] * m[1, 2] * m[2, 0] * m[3, 1] + m[0, 2] * m[1, 3] * m[2, 0] * m[3, 1] +
       m[0, 3] * m[1, 0] * m[2, 2] * m[3, 1] - m[0, 0] * m[1, 3] * m[2, 2] * m[3, 1] -
       m[0, 2] * m[1, 0] * m[2, 3] * m[3, 1] + m[0, 0] * m[1, 2] * m[2, 3] * m[3, 1] +
       m[0, 3] * m[1, 1] * m[2, 0] * m[3, 2] - m[0, 1] * m[1, 3] * m[2, 0] * m[3, 2] -
       m[0, 3] * m[1, 0] * m[2, 1] * m[3, 2] + m[0, 0] * m[1, 3] * m[2, 1] * m[3, 2] +
       m[0, 1] * m[1, 0] * m[2, 3] * m[3, 2] - m[0, 0] * m[1, 1] * m[2, 3] * m[3, 2] -
       m[0, 2] * m[1, 1] * m[2, 0] * m[3, 3] + m[0, 1] * m[1, 2] * m[2, 0] * m[3, 3] +
       m[0, 2] * m[1, 0] * m[2, 1] * m[3, 3] - m[0, 0] * m[1, 2] * m[2, 1] * m[3, 3] -
       m[0, 1] * m[1, 0] * m[2, 2] * m[3, 3] + m[0, 0] * m[1, 1] * m[2, 2] * m[3, 3];
    }
    public static UInt16 ReverseBytes( UInt16 value )
    {
      return (UInt16)( ( value & 0xFFU ) << 8 | ( value & 0xFF00U ) >> 8 );
    }
    public static UInt32 ReverseBytes( UInt32 value )
    {
      return ( value & 0x000000FFU ) << 24 | ( value & 0x0000FF00U ) << 8 |
             ( value & 0x00FF0000U ) >> 8 | ( value & 0xFF000000U ) >> 24;
    }
    public static UInt64 ReverseBytes( UInt64 value )
    {
      return ( value & 0x00000000000000FFUL ) << 56 | ( value & 0x000000000000FF00UL ) << 40 |
             ( value & 0x0000000000FF0000UL ) << 24 | ( value & 0x00000000FF000000UL ) << 8 |
             ( value & 0x000000FF00000000UL ) >> 8 | ( value & 0x0000FF0000000000UL ) >> 24 |
             ( value & 0x00FF000000000000UL ) >> 40 | ( value & 0xFF00000000000000UL ) >> 56;
    }
    public static Int16 ReverseBytes( Int16 value )
    {
      return (Int16)( ( value & 0x00FF ) << 8 | ( value & 0xFF00 ) >> 8 );
    }
    public static float FixedToFloat( UInt32 value )
    {
      return value / 65536.0F;
    }
    public static UInt32 ConcatShort( UInt16 left, UInt16 right )
    {
      return ( (UInt32)left << 16 ) | (UInt32)right;
    }
    public static void DecomposeLong( UInt32 value, out UInt16 left, out UInt16 right )
    {
      right = (UInt16)value;
      left = (UInt16)( value >> 16 );
    }
  }

  public struct DecomposedMatrix
  {
    public Vector3 position;
    public Vector3 rotation;
    public Vector3 scale;
    public float shearXY;
    public float shearXZ;
    public float shearYZ;
    public float perspX;
    public float perspY;
    public float perspZ;
    public float perspW;

    public new string ToString()
    {
      string translate = position.ToString( "f5" );
      string rotate = rotation.ToString( "f5" );
      string sc = scale.ToString( "f5" );
      string shear = " shearXY : " + shearXY.ToString( "f5" ) + " shearXZ : " + shearXZ.ToString( "f5" ) + " shearYZ : " + shearYZ.ToString( "f5" );
      return string.Format( "Translate: {0}\nRotate: {1}\nScale: {2}\nShear: {3}", translate, rotate, sc, shear );
    }
  }
}
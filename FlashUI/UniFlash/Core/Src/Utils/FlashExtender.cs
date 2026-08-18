using System.Drawing;
using System.IO;
using UnityEngine;

namespace Flash.Utils
{
  internal static class FlashExtender
  {
    public static UnityEngine.Event Clone( this UnityEngine.Event source )
    {
      return new UnityEngine.Event( source );
    }

    public static Vector4 Mul( this Vector4 lhs, Vector4 rhs )
    {
      return new Vector4( lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w );
    }

    public static bool LoadFromBytes( this Texture2D texture, byte[] buffer )
    {
      //GIF loading doesn't works on OSX because GDI+ interface is unaccessible.
      //Reported to unity premium support 12.12.2012
      try
      {
        var bitmap = new Bitmap( new MemoryStream( buffer ) );

        texture.Reinitialize( bitmap.Width, bitmap.Height );

        for ( int j = 0; j < texture.height; ++j )
        {
          for ( int i = 0; i < texture.width; ++i )
          {
            texture.SetPixel( i, j, FlashToUnityConverter.ConvertColor( bitmap.GetPixel( i, ( bitmap.Height - 1 ) - j ) ) );
          }
        }

        texture.Apply();
      }
      catch ( System.Exception e )
      {
        Debug.LogError( e.GetType().Name + ": " + e.Message );
        return false;
      }

      return true;
    }
  }
}
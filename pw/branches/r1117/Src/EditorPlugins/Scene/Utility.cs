using System;
using System.Drawing;
using EditorNative;
using EditorNative.Terrain;
using libdb.DB;

namespace EditorPlugins.Scene
{
  internal static class Utility
  {
    internal static string GetResourceName( DBID dbid )
    {
      string[] names = dbid.FileName.Split( '/', '\\' );
      string res = "";
      for ( int i = names.Length - 2; i < names.Length && i >= 0; i++ )
      {
        res += "/" + names[i];
      }
      if ( res.Length > 0 )
        res = res.Remove( 0, 1 );
      return res;
    }
    internal static float CalculateDiscreetAngle( Quaternion rotation, out bool valid )
    {
      const double COS_45 = 0.70710678118654752440084436210485;

      Vector3 rotated = rotation.Rotate( Vector3.AxisX );
      Vector3 projected = new Vector3( rotated.X, rotated.Y, 0 );
      if ( projected.Abs > float.Epsilon )
      {
        valid = true;
        Vector3 normalized = projected.Normalized;

        float cosA = normalized.X;
        float sinA = normalized.Y;

        if ( cosA >= COS_45 )
        {
          return 0;
        }
        else if ( cosA <= -COS_45 )
        {
          return (float)( Math.PI );
        }
        else if ( sinA > 0 )
        {
          return (float)( Math.PI / 2 );
        }
        else
        {
          return (float)( -Math.PI / 2 );
        }
      }
      else
      {
        valid = false;
        return 0;
      }
    }
    internal static float CalculateAngle( Vector3 rotated )
    {
      Vector3 normalized = new Vector3( rotated.X, rotated.Y, 0 ).Normalized;

      float cosA = normalized.X;
      float sinA = normalized.Y;

      if ( sinA >= 0 )
      {
        return (float)Math.Acos( cosA );
      }
      else
      {
        return (float)( -Math.Acos( cosA ) );
      }
    }
    internal static int GetRealSize( int size, int mipmaplevel )
    {
      int divided = 1;
      for ( int i = 0; i < mipmaplevel; i++ )
      {
        divided *= 2;
      }
      return size / divided;
    }
    internal static Color[] AreaColors
    {
      get
      {
        return new Color[]
					{
						Color.Transparent,
						Color.Red,
						Color.Green,
						Color.Blue,
						Color.Cyan,
						Color.Yellow,
						Color.Magenta,
						Color.White,
						Color.YellowGreen,
						Color.Brown,
						Color.Aqua,
						Color.Violet,
						Color.Orange,
						Color.Pink,
						Color.YellowGreen,
						Color.Silver,
						Color.OrangeRed,
						Color.PapayaWhip,
						Color.Navy,
						Color.Olive,
						Color.MintCream,
						Color.AntiqueWhite,
						Color.DodgerBlue,
						Color.LightGoldenrodYellow,
						Color.MintCream,
						Color.Tomato
					};
      }
    }
    internal static void DrawCircleOnTerrain( Vector3 point, float radius, int segments, System.Drawing.Color color, EditorTerrain terrain, bool depthTesting )
    {
      float stepAngle = (float)( 2 * Math.PI ) / segments;
      for ( int i = 0; i < segments; ++i )
      {
        float angle = i * stepAngle;
        Vector3 p0 = new Vector3( (float)Math.Sin( angle ), (float)Math.Cos( angle ), 0 ) * radius + point;
        float angle2 = ( i + 1 ) * stepAngle;
        Vector3 p1 = new Vector3( (float)Math.Sin( angle2 ), (float)Math.Cos( angle2 ), 0 ) * radius + point;

        // Project On Terrain
        float z0 = 0;
        terrain.TryGetHeight( p0.X, p0.Y, ref z0 );
        p0.Z = z0;
        float z1 = 0;
        terrain.TryGetHeight( p1.X, p1.Y, ref z1 );
        p1.Z = z1;

        EditorRender.DrawLine3D( p0, p1, color, depthTesting );
      }
    }
  }
}

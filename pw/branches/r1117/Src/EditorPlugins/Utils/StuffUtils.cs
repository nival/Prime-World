using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using DBTypes;
using EditorNative.Terrain;

namespace EditorPlugins.Utils
{
  public static class StuffUtils
  {
    private static PointF ConvertPoint( FlatSplineControlPointDesc point, Placement2 offset, PointF mult )
    {
      return new PointF( ( point.location.x + offset.translateX ) * mult.X, ( point.location.y + offset.translateY ) * mult.Y );
    }

    public static void StoreAdvMapWaterZone( AdvMap resource, int maskSize )
    {
      PointF mapSize = new PointF( resource.terrain.Get().elemXCount * TerrainUtils.PatchSize,
                                   resource.terrain.Get().elemYCount * TerrainUtils.PatchSize );
      PointF mult = new PointF( maskSize / mapSize.X, maskSize / mapSize.Y );
      using ( Bitmap mask = new Bitmap( maskSize, maskSize, PixelFormat.Format32bppArgb ) )
      {
        using ( Graphics graphics = Graphics.FromImage( mask ) )
        {
          graphics.FillRectangle( Brushes.Black, new Rectangle( 0, 0, maskSize, maskSize ) );
          using ( Brush brush = new SolidBrush( System.Drawing.Color.FromArgb( 64, System.Drawing.Color.White ) ) )
          {
            foreach ( AdvMapObject obj in resource.objects )
            {
              if ( obj.gameObject != null && obj.gameObject.Get() is AdvMapWaterZone )
              {
                AdvMapWaterZone water = obj.gameObject.Get<AdvMapWaterZone>();
                List<PointF> points = new List<PointF>( water.area.points.Count + 1 );
                for ( int i = 0; i < water.area.points.Count; ++i )
                  points.Add( ConvertPoint( water.area.points[i], obj.offset, mult ) );
                EditorPlugins.Mathematics.CompositeBSpline sampler = new EditorPlugins.Mathematics.CompositeBSpline();
                EditorPlugins.Mathematics.CompositeBSpline.SampleSpline( points, true, sampler.SimplestSampleFunctor );
                graphics.FillPolygon( brush, sampler.sampledPoints.ToArray() );
              }
            }
          }
        }
        //mask.Save( "c:\\Home\\watermask.png", System.Drawing.Imaging.ImageFormat.Png );
        BitmapData maskData = mask.LockBits( new Rectangle( 0, 0, maskSize, maskSize ),
                                             System.Drawing.Imaging.ImageLockMode.ReadOnly, mask.PixelFormat );
        PF_EditorNative.WaterMap.StoreAdvMapWaterZone( maskData.Scan0, mapSize.X, mapSize.Y, maskSize,
                                                       resource.waterMapFileName );
        //System.Runtime.InteropServices.Marshal.Copy( maskData.Scan0, buffer, 0, mask.Width * mask.Height );
        mask.UnlockBits( maskData );
      }
    }
  }
}
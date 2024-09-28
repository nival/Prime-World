using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using System.Text;
using System.Drawing;
using libdb.DB;

namespace EditorPlugins.Importer.Texture
{
	public class Atlas
	{
		const int atlasSize = 4096;
		const int badSize = 128;
		const int maxSize = 256;
    const int numMips = 0;
    const int boundSize = 1 << numMips;

		private class BitmapInfo
		{
			public string name;
			public Bitmap bitmap;
			public RectangleF rect;
			public bool isPlaced;
      public float scale;
			public float uvStartX;
			public float uvStartY;
			public float uvEndX;
			public float uvEndY;
			public static int CompareBySize( BitmapInfo x, BitmapInfo y )
			{
				if ( x.rect.Width * x.rect.Height < y.rect.Width * y.rect.Height )
				{
					return 1;
				}
				if ( x.rect.Width * x.rect.Height > y.rect.Width * y.rect.Height )
				{
					return -1;
				}
				return 0;
			}
		}

		private Bitmap resultAtlas;
		private List<BitmapInfo> bitmaps = new List<BitmapInfo>();

		private void CopyBitmap( BitmapInfo bitmapinfo, int curX, int curY, Bitmap image )
		{
      bool clearAlpha = bitmapinfo.scale == 0;
      //bool scaleColor = bitmapinfo.scale != 1.0f && !clearAlpha;
      float scale = clearAlpha ? 1.0f : 0.5f / bitmapinfo.scale;

      // We should duplicate boundary pixels for proper atlas work. However,
      // in particles atlas all boundary pixels should be poor black anyway.
      for (int x = 0; x < (int)bitmapinfo.rect.Width; x++)
			{
				for ( int y = 0; y < (int)bitmapinfo.rect.Height; y++ )
				{
          Color pixColor = bitmapinfo.bitmap.GetPixel(x, y);
          //if(scaleColor) {
          //  float currScale = scale * pixColor.A / (float)0xff;
          //  pixColor = Color.FromArgb(pixColor.A, (int)(pixColor.R * currScale),
          //                                        (int)(pixColor.G * currScale),
          //                                        (int)(pixColor.B * currScale));
          //}
          if (clearAlpha)
            pixColor = Color.FromArgb(0, pixColor);

          image.SetPixel(curX + x, curY + y, pixColor);
				}
			}
      if ( (bitmapinfo.rect.Height % 2) == 1
        || (bitmapinfo.rect.Width % 2) == 1 )
      {
        Log.TraceError( "Bad bitmap size {0}x{1} {2}", bitmapinfo.rect.Width, bitmapinfo.rect.Height, bitmapinfo.name );
      }
			bitmapinfo.isPlaced = true;
			bitmapinfo.uvStartX = curX;
			bitmapinfo.uvStartY = curY + bitmapinfo.rect.Height;
			bitmapinfo.uvEndX = curX + bitmapinfo.rect.Width;
			bitmapinfo.uvEndY = curY;
		}

		private bool GetBitmapByName( string name, out BitmapInfo bitinfo )
		{
			for ( int i = 0; i < bitmaps.Count; i++ )
			{
				if ( bitmaps[i].name == name )
				{
					bitinfo = bitmaps[i];
					return true;
				}
			}
			bitinfo = new BitmapInfo();
			return false;
		}

    public bool AddBitmap(Bitmap bitmap, string name, float scale)
		{
			BitmapInfo info = new BitmapInfo();
			if ( GetBitmapByName( name, out info ) )
			{
				return true;
			}
			GraphicsUnit units = GraphicsUnit.Point;
			RectangleF rect = bitmap.GetBounds( ref units );
			if ( rect.Width > maxSize || rect.Height > maxSize )
			{
				Log.TraceError( "Size of bitmap \"{0}\" ({1}x{2}) cannot exceed {3}x{3}", name, rect.Width, rect.Height, maxSize );
				return false;
			}

			if ( rect.Width > badSize || rect.Height > badSize )
				Log.TraceWarning( "Size of bitmap \"{0}\" ({1}x{2}) exceed {3}x{3}", name, rect.Width, rect.Height, badSize );

			info.bitmap = bitmap;
			info.rect = rect;
			info.isPlaced = false;
			info.name = name;
      info.scale = scale;
			bitmaps.Add( info );

      if ( !TestForAllPlaced() )
      {
        bitmaps.Remove( info );
        return false;
      }

      return true;
		}

    public bool TestForAllPlaced()
    {
      int curX = 0;
      int curY = 0;
      int maxX = 0;
      int maxY = 0;
      bool isAllPlaced = false;

      bitmaps.Sort( BitmapInfo.CompareBySize );

      while ( !isAllPlaced )
      {
        for ( int i = 0; i < bitmaps.Count; i++ )
        {
          if ( bitmaps[i].isPlaced )
            continue;
          if ( curY + bitmaps[i].rect.Height > atlasSize )
          {
            for ( int k = 0; k < bitmaps.Count; k++ )
            {
              bitmaps[k].isPlaced = false;
            }
            return false;
          }
          if ( curX + bitmaps[i].rect.Width <= atlasSize )
          {
            bitmaps[i].isPlaced = true;
            curX += (int)bitmaps[i].rect.Width;
            if ( maxY < bitmaps[i].rect.Height )
            {
              maxY = (int)bitmaps[i].rect.Height;
            }
            if ( maxX < curX )
            {
              maxX = curX;
            }
          }
        }

        isAllPlaced = true;
        for ( int i = 0; i < bitmaps.Count; i++ )
        {
          if ( !bitmaps[i].isPlaced )
          {
            isAllPlaced = false;
            curX = 0;
            curY += maxY;
            maxY = 0;
            break;
          }
        }
      }

      for ( int i = 0; i < bitmaps.Count; i++ )
      {
        bitmaps[i].isPlaced = false;
      }

      return true;
    }

		public void BuildAtlas()
		{
			bitmaps.Sort( BitmapInfo.CompareBySize );

      //int minX = int.MaxValue;
      //int minY = int.MaxValue;
      //foreach (BitmapInfo info in bitmaps)
      //{
      //  if (minX > (int)info.rect.Width)
      //    minX = (int)info.rect.Width;
      //  if (minY > (int)info.rect.Height)
      //    minY = (int)info.rect.Height;
      //}
      //minX <<= 1;
      //minY <<= 1;
      //int doubleBound = Math.Max(boundSize * 2, 4); // 4 == sizeof DXT block
      int doubleBound = boundSize * 2;

      int curX = 0;
      int curY = 0;
      int maxX = 0;
      int maxY = 0;
      bool isAllPlaced = false;

			Bitmap atlas = new Bitmap( atlasSize, atlasSize );
			while ( !isAllPlaced )
			{
				for ( int i = 0; i < bitmaps.Count; i++ )
				{
					if ( bitmaps[i].isPlaced ) continue;
					if ( curY + bitmaps[i].rect.Height > atlasSize )
					{
						Log.TraceError( "Atlas is too small for these textures" );
						return;
					}
					if ( curX + bitmaps[i].rect.Width <= atlasSize )
					{
            //if ( ((curY % 2) == 1) || ((curX % 2) == 1) )
            //  Log.TraceWarning( "X or Y is odd" );

						CopyBitmap( bitmaps[i], curX, curY, atlas );
            curX += (int)bitmaps[i].rect.Width + doubleBound;// +minX;
						if ( maxY < bitmaps[i].rect.Height )
						{
							maxY = (int)bitmaps[i].rect.Height;
						}
						if ( maxX < curX )
						{
							maxX = curX;
						}
					}
				}

				isAllPlaced = true;
        for ( int i = 0; i < bitmaps.Count; i++ )
				{
					if ( !bitmaps[i].isPlaced )
					{
						isAllPlaced = false;
						curX = 0;
            curY += maxY + doubleBound;// + minY;
						maxY = 0;
						break;
					}
				}
			}

      maxX -= doubleBound;
      if (maxX < 1)
      {
        Log.TraceError("wrong maxX");
        return;
      }
      maxY -= doubleBound;
      if (maxY < 1)
      {
        Log.TraceError("wrong maxY");
        return;
      }
      int atlasX = 1;
			while ( atlasX < maxX )
			{
				atlasX *= 2;
			}

			int atlasY = 1;
			while ( atlasY < curY + maxY )
			{
				atlasY *= 2;
			}

			resultAtlas = new Bitmap( atlasX, atlasY );
			for ( int x = 0; x < (int)atlasX; x++ )
			{
				for ( int y = 0; y < (int)atlasY; y++ )
				{
					resultAtlas.SetPixel( x, y, atlas.GetPixel( x, y ) );
				}
			}
		}

		public DBTypes.UVPair TryGetUVForBitmap( string name )
		{
			GraphicsUnit units = GraphicsUnit.Point;
			RectangleF rect = resultAtlas.GetBounds( ref units );

			DBTypes.UVPair pair = new DBTypes.UVPair();
			BitmapInfo info = new BitmapInfo();
			if ( GetBitmapByName( name, out info ) )
			{
				if ( info.isPlaced )
				{
					pair.uvTopLeft.x = info.uvStartX / rect.Width;
					pair.uvTopLeft.y = 1.0f - info.uvStartY / rect.Height;
					pair.uvBottomRight.x = info.uvEndX / rect.Width;
					pair.uvBottomRight.y = 1.0f - info.uvEndY / rect.Height;
          if ( pair.uvTopLeft.x < 0.0f || pair.uvTopLeft.y < 0.0f
            || pair.uvBottomRight.x < 0.0f || pair.uvBottomRight.y < 0.0f )
          {
            Log.TraceWarning( "UV < 0" );
          }

					return pair;
				}
			}

			Log.TraceWarning( "Can't extract UV for texture \"{0}\"", name );
			return pair;
		}

		public Bitmap GetAtlas()
		{
			return resultAtlas;
		}

		public bool IsEmpty { get { return bitmaps.Count == 0 || resultAtlas == null; } }
	}
}

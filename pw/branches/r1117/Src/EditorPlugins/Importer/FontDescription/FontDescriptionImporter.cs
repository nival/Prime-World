using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Extensions;
using libdb.DB;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Text;
using System.IO;
using libdb.IO;
using System.Diagnostics;
using EditorPlugins.Importer.Texture;

namespace EditorPlugins.Importer.FontDescriptionExporter
{
	public sealed class FontDescriptionImporter : Importer<DBTypes.Font>
	{
		[StructLayout( LayoutKind.Sequential, Pack = 1, Size = 32 )]
    private struct AlphabetHeader
		{
			public UInt32 charsCount;

			public UInt16 textureWidth;
			public UInt16 textureHeight;

			public Int16 height;
			public Int16 ascent;
			public Int16 externalLeading;
			public Int16 internalLeading;
			public Int16 descent;
      public Int16 reserved;

			public Int32 kerningPairsCount;
			public Int32 reserved3;
			public Int32 reserved4;

      public AlphabetHeader(UInt32 charsCount, Int32 texWidth, int texHeight, Int32 height, Int32 ascent, Int32 externalLeading, Int32 internalLeading, Int32 descent, Int32 kerningPairsCount)
			{
				this.charsCount = charsCount;
				this.textureWidth = (UInt16)texWidth;
				this.textureHeight = (UInt16)texHeight;
				this.height = (Int16)height;
				this.ascent = (Int16)ascent;
				this.externalLeading = (Int16)externalLeading;
				this.internalLeading = (Int16)internalLeading;
				this.descent = (Int16)descent;
        this.reserved = 0;
        this.kerningPairsCount = kerningPairsCount;
				this.reserved3 = 0;
				this.reserved4 = 0;
			}
		}

		[StructLayout( LayoutKind.Sequential, Pack = 1, Size = 16 )]
		private struct Glyph
		{
			public UInt16 u, v;
			public UInt16 width;
			public Int16 offset; // from after A
			public Int16 A;
			public Int16 B;
			public Int16 C;
			public Int16 reserved;

			public Glyph( UInt16 _u, UInt16 _v, UInt16 _width, Int16 _offset, Int16 _A, Int16 _B, Int16 _C )
			{
				u = _u;
				v = _v;
				width = _width;
				offset = _offset;
				A = _A;
				B = _B;
				C = _C;
				reserved = 0;
			}
		}

		private static byte[] RawSerialize<T>( T managedData )
		{
			int unmanagedDataSize = Marshal.SizeOf( managedData );
			byte[] unmanagedData = new byte[unmanagedDataSize];
			GCHandle handle = GCHandle.Alloc( unmanagedData, GCHandleType.Pinned );
			Marshal.StructureToPtr( managedData, handle.AddrOfPinnedObject(), false );
			handle.Free();
			return unmanagedData;
		}

		private static Font CreateFont( string faceName, int size, bool bold, bool italic )
		{
			FontStyle style = FontStyle.Regular;
			if ( bold )
				style |= FontStyle.Bold;
			if ( italic )
				style |= FontStyle.Italic;

			return new Font( faceName, (float)size, style, GraphicsUnit.Pixel );
		}

		private Bitmap GenerateChars( Font font, SimpleCharsInfo charsInfo, bool antiAliased, out List<Glyph> glyphs, string resName, int resFontSize )
		{
			Size size = SquareImageSize.FindBestSize( charsInfo );
			Bitmap image = new Bitmap( size.Width, size.Height, System.Drawing.Imaging.PixelFormat.Format32bppArgb );
			float imageWidth = (float)size.Width;
			float imageHeight = (float)size.Height;

			Graphics graphics = Graphics.FromImage( image );

			float ddy = -0.1f;
			float mdy = 0.3f;
			float sdy = 0.05f;
			float ddybest = 0;
			double ddyweightbest = 0;
			bool lastRender = false;
			bool finished = false;

			int totalSteps = 90;
			int stepCycles = charsInfo.chars.Count;
			int currentCycle = 0;
			int currentStep = 0;

			float dx0 = -0.1f;
			float dxstep = 0.05f;
			float dx1 = 0.3f;

			if ( !antiAliased )
			{
				totalSteps = 1;
				lastRender = true;
				ddy = 0;
				dx0 = 0;
				dxstep = 1;
				dx1 = 0;
			}

			glyphs = new List<Glyph>();

			while ( !finished )
			{
				double ddyweight = 0;

				graphics.Clear( Color.Transparent );
				graphics.PageUnit = GraphicsUnit.Pixel;
				graphics.TextRenderingHint = antiAliased ? TextRenderingHint.AntiAlias : TextRenderingHint.SingleBitPerPixelGridFit;
				graphics.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.HighQuality;

				SolidBrush brush = new SolidBrush( Color.White );

				const int pixelMargin = 3;
				const int x0 = pixelMargin * 2;
				int x = x0;
				int y = 2;
			
				foreach ( KeyValuePair<char, SimpleCharInfo> c in charsInfo.chars )
				{
					if ( x + c.Value.maxWidth + pixelMargin > size.Width )
					{
						x = x0;
						y += charsInfo.height + pixelMargin;
						//if ( y % 2 == 1 ) ++y;
					}

					{
						string chr = string.Empty + c.Key;

						Int16 A = (Int16)c.Value.a;
						Int16 B = (Int16)c.Value.b;
						Int16 C = (Int16)c.Value.c;

						Int16 offset = 0;

						int rx = x + Math.Max( 0, -A );
						int ry = y;
						int rh = charsInfo.height;
						int rw = 0; // should be estimated

						float dxbest = 0;
						float dybest = 0;

						{
							int rwmax = (int)(imageWidth - x + pixelMargin);

              //Optimize: limit scan area
              rwmax = Math.Min(rwmax, charsInfo.maxWidth + pixelMargin);

							Rectangle rect = new Rectangle( rx-1, ry-1, rwmax+1, rh+1 );
							graphics.SetClip( rect );

							double weightbest = -1;
							int rxmaxbest = 0;
							int rxminbest = 0;
							float dy = ddy;
							{
								for ( float dx = dx0; dx <= dx1; dx += dxstep )
								{
									graphics.Clear( Color.Transparent );
									graphics.DrawString( chr, font, brush, rx + dx, ry + dy, StringFormat.GenericTypographic );
									graphics.Flush( System.Drawing.Drawing2D.FlushIntention.Sync );

									double weight = 0.0;

									int amin = 255;
									int amax = 0;
									int asum = 0;
									int asumCount = 0;
									int dcount = 0;
									int lastRowMaxAlpha = 0;

									int rxmax = rx;
									int rxmin = rx;
									for ( int ty = ry-1; ty < ry+rh+1; ++ty )
									{
										int rowPixels = 0;
										int rowMaxAlpha = 0;

										for ( int tx = rx-1; tx < rx+rwmax+2; ++tx )
										{
											if ( tx < 0 || tx >= image.Width )
												continue;

											Color color = image.GetPixel( tx,ty );

											if ( color.R > 0 || color.A > 0 )
											{
												if ( rxmax < tx )
													rxmax = tx;
												if ( rxmin > tx )
													rxmin = tx;

												++rowPixels;
												rowMaxAlpha = Math.Max( rowMaxAlpha, color.A );
											}

											if ( color.A > 0 && color.A < amin )
												amin = color.A;
											if ( color.A > amax )
												amax = color.A;

											if ( color.A > 4 )
											{
												asum += color.A;
												++asumCount;
											}

											if ( color.A < 32 )
												++dcount;

											weight += color.A * color.A;
										}

										if ( rowPixels > 0 )
											lastRowMaxAlpha = rowMaxAlpha;
									}

									int aest = ( asumCount > 0 ? asum / asumCount : 0 );
									int ajmp = Math.Abs( amax - aest );
									if ( ajmp > 110 )
										weight = ( weight * 110 ) / ajmp;

									int dmax = ( rxmax * rh ) / 20;
									if ( dcount > dmax )
										weight = ( weight * dmax ) / dcount;

									if ( lastRowMaxAlpha < 64 )
										weight /= 2;

									if ( weight > weightbest )
									{
										weightbest = weight;
										dxbest = dx;
										dybest = dy;
										rxmaxbest = rxmax;
										rxminbest = rxmin;
									}

									if ( ++currentCycle >= stepCycles )
									{
										currentCycle = 0;
										++currentStep;
										Progress( string.Format( "Import font \"{0}\". Size {1} - step {2} of {3} ({4} cycles in step)...", resName, resFontSize, currentStep, totalSteps, stepCycles ), 50 );
									}
								}
							}

							graphics.Clear( Color.Transparent );
							graphics.ResetClip();

							offset = (Int16)(rxminbest - rx - 1);
							rw = 1 + (rxmaxbest - rxminbest + 1) + 1;

							ddyweight += weightbest;
						}

						if ( lastRender )
						{
							UInt16 u = (UInt16)(rx + offset);
							UInt16 v = (UInt16)ry;
							UInt16 w = (UInt16)rw;

								// debug: mark bkg
							//graphics.FillRectangle( Brushes.DarkGreen, u, v, w, charsInfo.height );

							graphics.DrawString( chr, font, brush, rx + dxbest, ry + dybest, StringFormat.GenericTypographic );
							glyphs.Add( new Glyph( u, v, w, offset, A,B,C ) );
						}
						
						x += rw + pixelMargin;
						//if ( x % 2 == 1 ) ++x;
					}
				}

				if ( lastRender )
				{
					finished = true;
					break;
				}

				if ( ddyweight > ddyweightbest )
				{
					ddyweightbest = ddyweight;
					ddybest = ddy;
				}

				ddy += sdy;
				if ( ddy > mdy )
				{
					lastRender = true;
					ddy = ddybest;
				}
			}

			return image;
		}

		protected override bool KnownDuration { get { return true; } }
		//protected override string CommandCaption() { return "Import Font"; }

		private static int CompareAlphabetGenerationInfo( DBTypes.AlphabetGenerationInfo a, DBTypes.AlphabetGenerationInfo b )
		{
			return a.size - b.size;
		}

		protected override bool Process( DBPtr<DBTypes.Font> resource, EditorLib.IEditorCommonApplication application, bool fast )
		{
			Progress( string.Format( "Import font \"{0}\"", resource.DBId.Name ) );
			DBTypes.Font fontDescription = resource.Get();
			
			// collect old imported files
			Progress( string.Format( "Import font \"{0}\". Remove old imported files ...", resource.DBId.Name ), 0 );
			foreach ( var font in fontDescription.fontDescriptions )
			{
				application.FileSystem.DeleteFile( font.binaryFileName );
				application.FileSystem.DeleteFile( font.textureFileName );
			}

			fontDescription.fontDescriptions.Clear();
			string rootPath = FileUtils.FixFolderName( Path.GetDirectoryName( resource.DBId.FileName ) );

			CharsRange[] charsRanges = new CharsRange[ 1 + fontDescription.generationInfo.chars.Count ];
			charsRanges[0] = new CharsRange( 32, 127 );
			int index = 1;
			foreach ( var charsRange in fontDescription.generationInfo.chars )
			{
				charsRanges[index] = new CharsRange( charsRange.first, charsRange.last );
				++index;
			}

			char[] chars = CharsRange.GetChars( charsRanges );

			List<DBTypes.AlphabetGenerationInfo> sizes = new List<DBTypes.AlphabetGenerationInfo>();
			sizes.AddRange( fontDescription.generationInfo.sizes );
			sizes.Sort( CompareAlphabetGenerationInfo );
			foreach ( var genInfo in sizes )
			{
				Progress( string.Format( "Import font \"{0}\". Size {1} ...", resource.DBId.Name, genInfo.size ), 50 );
				Font font = CreateFont( fontDescription.generationInfo.originalFaceName, genInfo.size, fontDescription.generationInfo.bold, fontDescription.generationInfo.italic );
				SimpleCharsInfo charsInfo = new SimpleCharsInfo( font, chars );

				List<Glyph> glyphs = null;
				Bitmap image = GenerateChars( font, charsInfo, genInfo.antialised, out glyphs, resource.DBId.Name, genInfo.size );

				DBTypes.Alphabet alphabet = new DBTypes.Alphabet();

				alphabet.size = genInfo.size;
				// store image
				alphabet.textureFileName = rootPath + fontDescription.faceName + "_" + genInfo.size.ToString() + ".dds";
				DdsImage.Save( application.FileSystem, alphabet.textureFileName, DdsFileFormat.DDS_FORMAT_A8R8G8B8, 0, image );
				EditorNative.EditorRender.ResetTexture( alphabet.textureFileName );

				//Stream imageStream = application.FileSystem.CreateFile( alphabet.textureFileName );
				//image.Save( imageStream, System.Drawing.Imaging.ImageFormat.Png );
				//imageStream.Close();

				// store binary image info
				alphabet.binaryFileName = rootPath + fontDescription.faceName + "_" + genInfo.size.ToString() + ".uv";
				Stream glyphsStream = application.FileSystem.CreateFile( alphabet.binaryFileName );
				BinaryWriter glyphsWriter = new BinaryWriter( glyphsStream );

				AlphabetHeader header = new AlphabetHeader(
          (UInt32)charsInfo.chars.Count,
          image.Width,
          image.Height,
          charsInfo.height,
          charsInfo.ascent,
          charsInfo.externalLeading,
          charsInfo.internalLeading,
          charsInfo.descent,
          (charsInfo.kerningPairs == null) ? 0 : charsInfo.kerningPairs.Count
          );
				glyphsWriter.Write( RawSerialize( header ) );

				foreach( char c in chars )
					glyphsWriter.Write( (short)c );

				foreach ( Glyph glyph in glyphs )
					glyphsWriter.Write( RawSerialize( glyph ) );

        if(charsInfo.kerningPairs != null)
          foreach (Win32.KERNINGPAIR pair in charsInfo.kerningPairs)
            glyphsWriter.Write(RawSerialize(pair));

        glyphsWriter.Close();

				fontDescription.fontDescriptions.Add( alphabet );
			}

			EditorNative.EditorRender.ReloadFont( resource.DBId );
			return true;
		}
	}
}

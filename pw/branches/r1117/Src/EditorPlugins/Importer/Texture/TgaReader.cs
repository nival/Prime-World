using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

namespace EditorPlugins.Importer.Texture
{
	public static class TgaReader
	{
		public enum TgaType : byte
		{
			Null = 0,
			Map = 1,
			Rgb = 2,
			Mono = 3,
			RleMap = 9,
			RleRgb = 10,
			RleMono = 11,
			CompMap = 32,
			CompMap4 = 33
		}

		[StructLayout( LayoutKind.Sequential )]
		public struct TgaHeader
		{
			public byte idLength;            // Image ID Field Length
			public byte cmapType;            // Color Map Type
			public TgaType imageType;        // Image Type

			public ushort cmapIndex;         // First Entry Index
			public ushort cmapLength;        // Color Map Length
			public byte cmapEntrySize;       // Color Map Entry Size

			public ushort xOrigin;           // X-origin of Image
			public ushort yOrigin;           // Y-origin of Image
			public ushort imageWidth;        // Image Width
			public ushort imageHeight;       // Image Height
			public byte pixelDepth;          // Pixel Depth
			public byte imageDesc;           // Image Descriptor

			public void Write( Stream output )
			{
				output.WriteByte( this.idLength );
				output.WriteByte( this.cmapType );
				output.WriteByte( (byte)this.imageType );

				Utility.WriteUInt16( output, this.cmapIndex );
				Utility.WriteUInt16( output, this.cmapLength );
				output.WriteByte( this.cmapEntrySize );

				Utility.WriteUInt16( output, this.xOrigin );
				Utility.WriteUInt16( output, this.yOrigin );
				Utility.WriteUInt16( output, this.imageWidth );
				Utility.WriteUInt16( output, this.imageHeight );
				output.WriteByte( this.pixelDepth );
				output.WriteByte( this.imageDesc );
			}

			public static bool ReadHeader( Stream input, ref TgaHeader header )
			{
        int byteRead = input.ReadByte();
				if ( byteRead == -1 )
					return false;
				header.idLength = (byte)byteRead;

				byteRead = input.ReadByte();
				if ( byteRead == -1 )
					return false;
				header.cmapType = (byte)byteRead;

				byteRead = input.ReadByte();
				if ( byteRead == -1 )
					return false;
				header.imageType = (TgaType)byteRead;

				int shortRead = Utility.ReadUInt16( input );
				if ( shortRead == -1 )
					return false;
				header.cmapIndex = (ushort)shortRead;

				shortRead = Utility.ReadUInt16( input );
				if ( shortRead == -1 )
					return false;
				header.cmapLength = (ushort)shortRead;

				byteRead = input.ReadByte();
				if ( byteRead == -1 )
					return false;
				header.cmapEntrySize = (byte)byteRead;

				shortRead = Utility.ReadUInt16( input );
				if ( shortRead == -1 )
					return false;
				header.xOrigin = (ushort)shortRead;

				shortRead = Utility.ReadUInt16( input );
				if ( shortRead == -1 )
					return false;
				header.yOrigin = (ushort)shortRead;

				shortRead = Utility.ReadUInt16( input );
				if ( shortRead == -1 )
					return false;
				header.imageWidth = (ushort)shortRead;

				shortRead = Utility.ReadUInt16( input );
				if ( shortRead == -1 )
					return false;
				header.imageHeight = (ushort)shortRead;

				byteRead = input.ReadByte();
				if ( byteRead == -1 )
					return false;
				header.pixelDepth = (byte)byteRead;

				byteRead = input.ReadByte();
				if ( byteRead == -1 )
					return false;
				header.imageDesc = (byte)byteRead;

				return true;
			}
		}
		private static Color[] CreateGrayPalette()
		{
			Color[] palette = new Color[256];

			for ( int i = 0; i < palette.Length; ++i )
			{
				palette[i] = Color.FromArgb( 255, (byte)i, (byte)i, (byte)i );
			}

			return palette;
		}

		private static Color[] LoadPalette( Stream input, int count )
		{
			Color[] palette = new Color[count];

			for ( int i = 0; i < palette.Length; ++i )
			{
				int blue = input.ReadByte();
				if ( blue == -1 )
					return null;

				int green = input.ReadByte();
				if ( green == -1 )
					return null;

				int red = input.ReadByte();
				if ( red == -1 )
					return null;

				palette[i] = Color.FromArgb( 255, (byte)red, (byte)green, (byte)blue );
			}

			return palette;
		}

		private static Color ReadColor( Stream input, int pixelDepth, Color[] palette )
		{
			switch ( pixelDepth )
			{
				case 32:
					{
						long colorInt = Utility.ReadUInt32( input );

						if ( colorInt == -1 )
							return Color.White;

						return Color.FromArgb( (byte)((colorInt >> 24) & 0xff), (byte)((colorInt >> 16) & 0xff), (byte)((colorInt >> 8) & 0xff), (byte)(colorInt & 0xff) );
					}

				case 24:
					{
						int colorInt = Utility.ReadUInt24( input );

						if ( colorInt == -1 )
							return Color.White;

						return Color.FromArgb( 255, (byte)((colorInt >> 16) & 0xff), (byte)((colorInt >> 8) & 0xff), (byte)(colorInt & 0xff) );
					}

				case 15:
				case 16:
					{
						int colorWord = Utility.ReadUInt16( input );

						if ( colorWord == -1 )
							return Color.White;

						return Color.FromArgb( 255, (byte)((colorWord & 0x1f) * 8), (byte)((colorWord >> 2) & 0xf8), (byte)((colorWord >> 7) & 0xf8) );
					}

				case 8:
					{
						int colorByte = input.ReadByte();

						if ( colorByte == -1 || colorByte < palette.Length )
							return Color.White;

						return palette[colorByte];
					}

				default:
					return Color.White;
			}
		}

		private static void ExpandUncompressedLine( byte[] dst, int dstIndex, ref TgaHeader header, Stream input, int width, int y, int xoffset, Color[] palette )
		{
			for ( int i = 0; i < width; ++i )
			{
				Color color = ReadColor( input, header.pixelDepth, palette );
				dst[0 + dstIndex] = color.B;
				dst[1 + dstIndex] = color.G;
				dst[2 + dstIndex] = color.R;
				dst[3 + dstIndex] = color.A;
				dstIndex += 4;
			}
		}

		private static byte ExpandCompressedLine( byte[] dst, int dstIndex, ref TgaHeader header, Stream input, int width, int y, byte rleLeftOver, Color[] palette )
		{
			byte rle;
			long filePos = 0;

			int x = 0;
			while ( x < width )
			{
				if ( rleLeftOver != 255 )
				{
					rle = rleLeftOver;
					rleLeftOver = 255;
				}
				else
				{
					int byte1 = input.ReadByte();
					if ( byte1 == -1 )
						return 0;
					rle = (byte)byte1;
				}

				if ( (rle & 128) != 0 )
				{
					// RLE Encoded packet
					rle -= 127; // calculate real repeat count

					if ( (x + rle) > width )
					{
						rleLeftOver = (byte)(128 + (rle - (width - x) - 1));
						filePos = input.Position;
						rle = (byte)(width - x);
					}

					Color color = ReadColor( input, header.pixelDepth, palette );

					for ( int ix = 0; ix < rle; ++ix )
					{
						int index = dstIndex + (ix * 4);

						dst[0 + index] = color.B;
						dst[1 + index] = color.G;
						dst[2 + index] = color.R;
						dst[3 + index] = color.A;
					}

					if ( rleLeftOver != 255 )
						input.Position = filePos;
				}
				else
				{
					// Raw packet
					rle += 1; // calculate real repeat count

					if ( (x + rle) > width )
					{
						rleLeftOver = (byte)(rle - (width - x) - 1);
						rle = (byte)(width - x);
					}

					ExpandUncompressedLine( dst, dstIndex, ref header, input, rle, y, x, palette );
				}

				dstIndex += rle * 4;
				x += rle;
			}

			return rleLeftOver;
		}
	
		public static Bitmap LoadImage( Stream stream )
		{

			TgaHeader header = new TgaHeader();
			if ( !TgaHeader.ReadHeader( stream, ref header ) )
				return null;

			bool compressed = false;

			switch ( header.imageType )
			{
				case TgaType.Map:
				case TgaType.Rgb:
				case TgaType.Mono:
					compressed = false;
					break;

				case TgaType.RleMap:
				case TgaType.RleRgb:
				case TgaType.RleMono:
					compressed = true;
					break;

				default:
					return null;
			}

			if ( header.imageWidth == 0 ||
					header.imageHeight == 0 ||
					header.pixelDepth == 0 ||
					header.cmapLength > 256 )
			{
				return null;
			}

			if ( header.pixelDepth != 8 &&
					header.pixelDepth != 15 &&
					header.pixelDepth != 16 &&
					header.pixelDepth != 24 &&
					header.pixelDepth != 32 )
			{
				return null;
			}

			if ( header.idLength > 0 )
			{
				stream.Position += header.idLength; // skip descriptor
			}


			Color[] palette = null;
			if ( header.cmapType != 0 )
			{
				palette = LoadPalette( stream, header.cmapLength );
			}

			if ( header.imageType == TgaType.Mono ||
					header.imageType == TgaType.RleMono )
			{
				palette = CreateGrayPalette();
			}

			// Bits 0 - 3 of the image descriptor byte describe number of bits used for alpha channel
			// For loading, we won't worry about this. Not all TGA implementations are correct (such
			// as older Paint.NET TGA implementations!) and we don't want to lose all their alpha bits.

			// Bits 4 & 5 of the image descriptor byte control the ordering of the pixels
			bool xReversed = ((header.imageDesc & 16) == 16);
			bool yReversed = ((header.imageDesc & 32) == 32);

			byte rleLeftOver = 255; // for images with illegal packet boundary

			Bitmap result = new Bitmap( header.imageWidth, header.imageHeight, System.Drawing.Imaging.PixelFormat.Format32bppArgb );
			BitmapData pixels = result.LockBits( new Rectangle( 0, 0, result.Width, result.Height ), System.Drawing.Imaging.ImageLockMode.WriteOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb );
			byte[] dst = new byte[pixels.Stride];

			for ( int y = 0; y < header.imageHeight; ++y )
			{
				if ( compressed )
					rleLeftOver = ExpandCompressedLine( dst, 0, ref header, stream, header.imageWidth, y, rleLeftOver, palette );
				else
					ExpandUncompressedLine( dst, 0, ref header, stream, header.imageWidth, y, 0, palette );

				IntPtr dstRow;

				if ( yReversed )
					dstRow = new IntPtr( pixels.Scan0.ToInt32() + pixels.Stride * y );
				else
					dstRow = new IntPtr( pixels.Scan0.ToInt32() + pixels.Stride * (header.imageHeight - y - 1) );

				System.Runtime.InteropServices.Marshal.Copy( dst, 0, dstRow, pixels.Stride );
			}

			result.UnlockBits( pixels );

			return result;
		}
	}
}

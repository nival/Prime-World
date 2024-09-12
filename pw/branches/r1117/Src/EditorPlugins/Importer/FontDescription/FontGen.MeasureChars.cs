using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Runtime.InteropServices;

namespace EditorPlugins.Importer.FontDescriptionExporter
{
	partial class FontGen
	{
		public struct SimpleCharInfo
		{
			public readonly int a;
			public readonly int b;
			public readonly int c;
			public readonly int bc;
			public readonly int width;

			public SimpleCharInfo( int _a, int _b, int _c )
			{
				a = _a;
				b = _b;
				c = _c;
				bc = _b + _c;
				width = _b;// +Math.Max(_c, 0);
			}
		}

		public struct SimpleCharsInfo
		{
			public readonly int height;
			public readonly int internalLeading;
			public readonly int externalLeading;
			public readonly int ascent;

			public readonly char defaultChar;
			public readonly int spaceWidth;

			public Dictionary<char, SimpleCharInfo> chars;

			public SimpleCharsInfo( int _height, int _internalLeading, int _externalLeading, int _ascent, char _defaultChar, int _spaceWidth )
			{
				height = _height;
				internalLeading = _internalLeading;
				externalLeading = _externalLeading;
				ascent = _ascent;
				defaultChar = _defaultChar;
				spaceWidth = _spaceWidth;

				chars = new Dictionary<char, SimpleCharInfo>();
			}
		}

		private static SimpleCharInfo MeasureChar( IntPtr hdc, char c )
		{
			Win32.ABC abc = new Win32.ABC();
			if ( Win32.GDI.GetCharABCWidthsW( hdc, (int)c, (int)c, ref abc ) != 0 )
				return new SimpleCharInfo( abc.abcA, abc.abcB, abc.abcC );
			else
				return new SimpleCharInfo( 0, 0, 0 );
		}

		private static SimpleCharsInfo MeasureChars( Font font, char[] chars )
		{

			Bitmap image = new Bitmap( 16, 16, System.Drawing.Imaging.PixelFormat.Format32bppArgb );
			Graphics graphics = Graphics.FromImage( image );
			IntPtr hdc = graphics.GetHdc();

			IntPtr hFont = font.ToHfont();
			Win32.GDI.SelectObject( hdc, hFont );
			Win32.TEXTMETRIC metrics = new Win32.TEXTMETRIC();
			Win32.GDI.GetTextMetrics( hdc, ref metrics );

			SimpleCharInfo space = MeasureChar( hdc, ' ' );

			SimpleCharsInfo result = new SimpleCharsInfo( metrics.tmHeight, metrics.tmInternalLeading, metrics.tmExternalLeading, metrics.tmAscent,
				(char)metrics.tmDefaultChar, space.width );

			foreach ( char c in chars )
			{
				if ( !result.chars.ContainsKey( c ) )
				{
					SimpleCharInfo charInfo = MeasureChar( hdc, c );
					if ( charInfo.width > 0 )
						result.chars.Add( c, charInfo );
				}
			}

			graphics.ReleaseHdc( hdc );
			return result;
		}
	}
}
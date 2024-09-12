using System;
using System.Text;
using System.Drawing;

namespace EditorPlugins.Importer.FontDescriptionExporter
{
	public static class SquareImageSize
	{
		const int pixelMargin = 2;

		private static void UpdateSize( ref Size size, bool increment )
		{
			if ( increment )
			{
				if ( size.Width == size.Height )
					size.Height *= 2;
				else
					size.Width *= 2;
			}
			else
			{
				if ( size.Width == size.Height )
					size.Width /= 2;
				else
					size.Height /= 2;
			}
		}

		private static int Sqrt( int area )
		{
			for ( int size = 2; size < int.MaxValue / 2; size *= 2 )
			{
				if ( size * size > area )
					return size;
			}

			return 0;
		}

		private static bool IsFitting( SimpleCharsInfo charsInfo, Size size )
		{
			int height = charsInfo.height + charsInfo.internalLeading + charsInfo.externalLeading;

			if ( size.Height < height )
				return false;

			int x = 0;
			int y = 0;
			foreach ( SimpleCharInfo c in charsInfo.chars.Values )
			{
				x += c.maxWidth + pixelMargin * 3;
				if ( x > size.Width )
				{
					x = c.maxWidth + pixelMargin * 3;
					y += height + pixelMargin;
					if ( y + height > size.Height )
						return false;
				}
			}

			return true;
		}

		public static Size FindBestSize( SimpleCharsInfo charsInfo )
		{
			int totalWidth = 0;
			foreach ( SimpleCharInfo c in charsInfo.chars.Values )
				totalWidth += c.maxWidth + pixelMargin * 3;
			int height = charsInfo.height + 1;// +charsInfo.internalLeading + charsInfo.externalLeading;
			int sideSize = Sqrt( totalWidth * height );

			Size size = new Size( sideSize, sideSize );
			if ( IsFitting( charsInfo, size ) )
			{
				UpdateSize( ref size, false );
				while ( IsFitting( charsInfo, size ) )
					UpdateSize( ref size, false );
				UpdateSize( ref size, true );
			}
			else
			{
				UpdateSize( ref size, true );
				while ( !IsFitting( charsInfo, size ) )
					UpdateSize( ref size, true );
			}

			return size;
		}
	}
}
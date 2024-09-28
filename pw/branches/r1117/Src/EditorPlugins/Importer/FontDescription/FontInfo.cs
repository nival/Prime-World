using System;
using System.Collections.Generic;
using System.IO;

namespace EditorPlugins.Importer.FontDescriptionExporter
{
	[Serializable]
	public class FontInfo
	{
		[Serializable]
		public struct CharInfo
		{
			public readonly int a;
			public readonly int bc;
			public readonly int width;
			public readonly int x;
			public readonly int y;

			public static CharInfo Empty = new CharInfo( 0, 0, 0, 0, 0 );

			public CharInfo( int _a, int _bc, int _width, int _x, int _y )
			{
				a = _a;
				bc = _bc;
				width = _width;
				x = _x;
				y = _y;
			}
		}

		[Serializable]
		public struct CharsInfo
		{
			public readonly int height;
			public readonly int internalLeading;
			public readonly int externalLeading;
			public readonly int ascent;
			public readonly char defaultChar;

			public readonly int spaceWidth;

			public Dictionary<char, CharInfo> chars;

			public static CharsInfo Empty = new CharsInfo( 0, 0, 0, 0 );

			private CharsInfo( int _height, int _internalLeading, int _externalLeading, int _ascent )
			{
				height = _height;
				internalLeading = _internalLeading;
				externalLeading = _externalLeading;
				ascent = _ascent;
				defaultChar = char.MinValue;
				spaceWidth = 0;

				chars = null;
			}

			public CharsInfo( int _height, int _internalLeading, int _externalLeading, int _ascent, char _defaultChar, int _spaceWidth )
			{
				height = _height;
				internalLeading = _internalLeading;
				externalLeading = _externalLeading;
				ascent = _ascent;
				defaultChar = _defaultChar;
				spaceWidth = _spaceWidth;

				chars = new Dictionary<char, CharInfo>();
			}

			public static int CompareCharsInfo( CharsInfo charsInfo1, CharsInfo charsInfo2 )
			{
				return charsInfo1.height - charsInfo2.height;
			}
		}

		private readonly List<CharsInfo> fontData = new List<CharsInfo>();

		public void AddCharsInfo( CharsInfo charsInfo )
		{
			fontData.Add( charsInfo );
			fontData.Sort( CharsInfo.CompareCharsInfo );
		}
	}
}

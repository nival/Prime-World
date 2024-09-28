using System;
using System.Collections.Generic;

namespace EditorPlugins.Importer.FontDescriptionExporter
{
	public class FontsTable
	{
		public class Font
		{
			[FlagsAttribute]
			public enum GenerationOptions
			{
				None = 0,
				AntiAliased = 1,
				Italic = 2,
				Bold = 4,
			}

			public string faceName = "Tahoma";
			public string fontName = "Default";
			public GenerationOptions options = GenerationOptions.AntiAliased;

			public int[] sizes = new int[] { 24, 32, 48, 64 };

			public Font() { }

			public Font( string _fontName, string _faceName, GenerationOptions _options )
			{
				fontName = _fontName;
				faceName = _faceName;
				options = _options;
			}

			public void SetSizes( params int[] _sizes )
			{
				sizes = new int[_sizes.Length];
				for ( int i = 0; i < _sizes.Length; ++i )
					sizes[i] = _sizes[i];
			}

			public bool AntiAliased { get { return (options & GenerationOptions.AntiAliased) == GenerationOptions.AntiAliased; } }
			public bool Italic { get { return (options & GenerationOptions.Italic) == GenerationOptions.Italic; } }
			public bool Bold { get { return (options & GenerationOptions.Bold) == GenerationOptions.Bold; } }
		}

		public List<Font> fonts = new List<Font>();
		public string outputDir = string.Empty;
	}
}

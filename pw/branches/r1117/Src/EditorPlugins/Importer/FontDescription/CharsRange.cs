using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace EditorPlugins.Importer.FontDescriptionExporter
{
	public class CharsRange
	{
		private readonly char min = (char)0;
		private readonly char max = (char)0;

		public CharsRange() { min = (char)0; max = (char)0; }
		public CharsRange( char _min, char _max ) { min = _min; max = _max; }
		public CharsRange( int _min, int _max ) { min = (char)_min; max = (char)_max; }

		private static int Compare( CharsRange range1, CharsRange range2 )
		{
			if ( range1.min < range2.min )
				return -1;
			else if ( range1.min == range2.min )
				return range1.max - range2.max;
			else
				return 1;
		}

		private static void Sort( List<CharsRange> ranges )
		{
			ranges.Sort( Compare );
			for ( int i = 1; i < ranges.Count; ++i )
			{
				if ( ranges[i].min <= ranges[i - 1].max + 1 )
					ranges[i] = new CharsRange( ranges[i - 1].min, ranges[i].max );
			}

			ranges.Sort( Compare );
			for ( int i = 0; i < ranges.Count - 1; ++i )
			{
				if ( ranges[i].max >= ranges[i + 1].min - 1 )
					ranges[i] = new CharsRange( ranges[i].min, ranges[i + 1].max );
			}

			for ( int i = 1; i < ranges.Count; )
			{
				if ( ranges[i].min == ranges[i - 1].min && ranges[i].max == ranges[i - 1].max )
					ranges.RemoveAt( i );
				else
					++i;
			}
		}

		public static char[] GetChars( IEnumerable<CharsRange> _ranges )
		{
			List<CharsRange> ranges = new List<CharsRange>();
			ranges.AddRange( _ranges );

			Sort( ranges );

			List<char> chars = new List<char>();
			foreach ( CharsRange range in ranges )
			{
				for ( char c = range.min; c <= range.max; ++c )
				{
					if ( !char.IsControl( c ) )
						chars.Add( c );
				}
			}

			return chars.ToArray();
		}
	}
}
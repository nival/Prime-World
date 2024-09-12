using System;

namespace DBCodeGen.Utils
{
	public static class FormatHelper
	{
		private static string GetIndentString( int indent )
		{
      return new string( '\t', indent );
		}

		public static string FormatString( int indent, string str )
		{
			return string.Format( "{0}{1}", GetIndentString( indent ), str );
		}

		public static string FormatString( int indent, string format, params object[] objects )
		{
			return FormatString( indent, string.Format( format, objects ) );
		}

		public static string CommentLine { get { return "///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////"; } }

		public static string[] ConvertPatternToLines( string pattern )
		{
			return pattern.Split( new string[] { "\r\n" }, StringSplitOptions.None );
		}
	}
}

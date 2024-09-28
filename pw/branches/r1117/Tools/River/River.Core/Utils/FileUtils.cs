using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace River.Core.Utils
{
	public static class FileUtils
	{
		public static string Combine( params string[] paths )
		{
			if ( paths == null || paths.Length == 0 )
				return string.Empty;
			if ( paths.Length == 1 )
				return paths[0];

			string result = paths[0];
			for ( int i = 1; i < paths.Length; ++i )
				result = Path.Combine( result, paths[i] );

			return result;
		}
	}
}

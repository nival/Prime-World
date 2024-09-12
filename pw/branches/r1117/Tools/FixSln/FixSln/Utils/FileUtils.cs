using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace FixSln.Utils
{
	public static class FileUtils
	{
		public static bool IsPathSeparator( char c ) { return c == Path.DirectorySeparatorChar || c == Path.AltDirectorySeparatorChar; }

		public static string FixFileName( string filePath )
		{
			if ( string.IsNullOrEmpty( filePath ) )
				return string.Empty;

			char[] resultFileName = filePath.ToCharArray();
			int shift = 0;
			int length = resultFileName.Length;
			bool lastCharIsSeparator = false;
			for ( int i = 0; i + shift < length; )
			{
				if ( IsPathSeparator( resultFileName[i + shift] ) )
				{
					if ( !lastCharIsSeparator )
					{
						lastCharIsSeparator = true;
						resultFileName[i] = Path.DirectorySeparatorChar;
						++i;
					}
					else
					{
						++shift;
					}
				}
				else
				{
					resultFileName[i] = resultFileName[i + shift];
					++i;
					lastCharIsSeparator = false;
				}
			}

			string result = new string( resultFileName, 0, length - shift );
			return result;
		}

		public static string FixFolderName( string folderPath )
		{
			string result = FixFileName( folderPath );
			if ( !string.IsNullOrEmpty( result ) && !IsPathSeparator( result[result.Length - 1] ) )
				result += Path.DirectorySeparatorChar;

			return result;
		}

		private static string[] SimplifyPath( string[] path )
		{
			List<string> result = new List<string>();
			foreach ( string element in path )
			{
				if ( element == ".." && result.Count > 0 && result[result.Count - 1] != ".." )
					result.RemoveAt( result.Count - 1 );
				else 
					result.Add( element );
			}

			return result.ToArray();
		}

		public static string GetRelativePath( string absolutePath, string relativeTo )
		{
			string[] absoluteDirectories = SimplifyPath( FixFileName( absolutePath ).Split( Path.DirectorySeparatorChar ) );
			string[] relativeDirectories = SimplifyPath( FixFileName( relativeTo ).Split( Path.DirectorySeparatorChar ) );

			//Get the shortest of the two paths
			int length = Math.Min( absoluteDirectories.Length, relativeDirectories.Length );

			//Use to determine where in the loop we exited
			int lastCommonRoot = 0;
			for ( lastCommonRoot = 0; lastCommonRoot < length; ++lastCommonRoot )
			{
				if ( string.Compare( absoluteDirectories[lastCommonRoot], relativeDirectories[lastCommonRoot], StringComparison.InvariantCultureIgnoreCase ) != 0 )
					break;
			}

			if ( lastCommonRoot == 0 )
				return relativeTo;

			StringBuilder relativePath = new StringBuilder();

			//Add on the ..
			for ( int i = lastCommonRoot; i < absoluteDirectories.Length; ++i )
				relativePath.Append( ".." + Path.DirectorySeparatorChar );

			//Add on the folders
			for ( int i = lastCommonRoot; i < relativeDirectories.Length - 1; ++i )
				relativePath.Append( relativeDirectories[i] + Path.DirectorySeparatorChar );

			if ( relativePath.Length == 0 )
				relativePath.Append( "." + Path.DirectorySeparatorChar );
			relativePath.Append( relativeDirectories[relativeDirectories.Length - 1] );

			return relativePath.ToString();
		}

		public static string FixCaseInPath( string path )
		{
			string[] elements = FixFileName( path ).Split( Path.DirectorySeparatorChar );

			StringBuilder result = new StringBuilder();
			string realPath = Path.GetFullPath( ".\\" );

			foreach ( string element in elements )
			{
				if ( string.IsNullOrEmpty( element ) )
					continue;

				if ( element.Length == 2 && element[1] == ':' )
				{
					realPath = element.ToUpperInvariant() + Path.DirectorySeparatorChar;
					result.Append( element.ToUpperInvariant() );
					continue;
				}

				string newRealPath = Path.Combine( realPath, element );
				if ( result.Length != 0 )
					result.Append( Path.DirectorySeparatorChar );

				if ( element == "." || element == ".." )
					result.Append( element );
				else if ( Directory.Exists( newRealPath ) )
				{
					string fullElementPath = Directory.GetDirectories( realPath, element )[0];
					result.Append( fullElementPath.Substring( fullElementPath.Length - element.Length ) );
				}
				else if ( File.Exists( newRealPath ) )
				{
					string fullElementPath = Directory.GetFiles( realPath, element )[0];
					result.Append( fullElementPath.Substring( fullElementPath.Length - element.Length ) );
				}
				else
					result.Append( element );

				realPath = newRealPath;
			}

			return result.ToString();
		}
	}
}

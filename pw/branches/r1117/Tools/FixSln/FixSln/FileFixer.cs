using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using FixSln.Utils;
using System.Text.RegularExpressions;

namespace FixSln
{
	public static class FileFixer
	{
		private const string slnProjectRegExp = "Project\\(\"\\{([0-9A-Za-z]{8}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{12})}\"\\)\\s*=\\s*\"([a-zA-Z_0-9\\.\\\\\\/]+)\"\\s*,\\s*\"([a-zA-Z_0-9\\.\\\\\\/]*)\"\\s*,\\s*\"\\{([0-9A-Za-z]{8}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{4}-?[0-9A-Za-z]{12})}";
		private const string vcProjAddDir = "([ \t]*)(AdditionalIncludeDirectories|AdditionalLibraryDirectories)[ \t]*=[ \t]*\"([^\"]*)\"(.*)";
		private const string vcProjRelPath = "([ \t]*)RelativePath[ \t]*=[ \t]*\"([^\"]*)\"(.*)";

		private static string FixSlnLine( string line, string filePath, FileMover mover )
		{
			Match match = Regex.Match( line, slnProjectRegExp );
			if ( match.Success && new Guid( match.Groups[1].Value ) != SolutionStruct.SolutionFolder.SolutionFolderTypeGuid )
			{
				string projectFilePath = FileUtils.GetRelativePath( Path.GetDirectoryName( filePath ), mover.GetNewReferencedName( filePath, match.Groups[3].Value ) );
				return string.Format( "Project(\"{{{0}}}\") = \"{1}\", \"{2}\", \"{{{3}}}\"", match.Groups[1].Value, match.Groups[2].Value, projectFilePath, match.Groups[4].Value );
			}
			else
				return line;
		}

		private static string FixVCProjnLine( string line, string filePath, FileMover mover )
		{
			Match match = Regex.Match( line, vcProjAddDir );
			if ( match.Success )
			{
				string[] files = match.Groups[3].Value.Split( ';' );
				for ( int i = 0; i < files.Length; ++i )
				{
					int vendorVendorIndex = files[i].IndexOf( "vendor\\vendor", StringComparison.InvariantCultureIgnoreCase );
					if ( vendorVendorIndex < 0 )
						vendorVendorIndex = files[i].IndexOf( "vendor/vendor", StringComparison.InvariantCultureIgnoreCase );
					if ( vendorVendorIndex >= 0 )
						files[i] = files[i].Substring( 0, vendorVendorIndex ) + "Vendor" + files[i].Substring( vendorVendorIndex + 13 );

					string dirPath = FileUtils.GetRelativePath( Path.GetDirectoryName( filePath ), mover.GetNewReferencedName( filePath, files[i] ) );
					files[i] = dirPath;
				}
				return string.Format( "{0}{1}=\"{2}\"{3}", match.Groups[1].Value, match.Groups[2].Value, string.Join( ";", files ), match.Groups[4].Value );
			}

			match = Regex.Match( line, vcProjRelPath );
			if ( match.Success )
			{
				string relFilePath = FileUtils.GetRelativePath( Path.GetDirectoryName( filePath ), mover.GetNewReferencedName( filePath, match.Groups[2].Value ) );
				return string.Format( "{0}RelativePath=\"{1}\"{2}", match.Groups[1].Value, relFilePath, match.Groups[3].Value );
			}

			return line;
		}

		private delegate string LineConvertor( string line, string filePath, FileMover mover );
		private static void FixLineByLine( string filePath, FileMover mover, LineConvertor convertor )
		{
			List<string> lines = new List<string>();
			using ( StreamReader file = new StreamReader( new FileStream( filePath, System.IO.FileMode.Open, System.IO.FileAccess.Read, System.IO.FileShare.ReadWrite ) ) )
			{
				string line = null;
				while ( ( line = file.ReadLine() ) != null )
					lines.Add( convertor( line, filePath, mover ) );
			}

			using ( StreamWriter file = new StreamWriter( new FileStream( filePath, System.IO.FileMode.Create, System.IO.FileAccess.Write, System.IO.FileShare.None ), Encoding.UTF8 ) )
			{
				foreach ( string line in lines )
					file.WriteLine( line );

				file.Flush();
				file.Close();
			}
		}

		public static void FixFile( string filePath, FileMover mover )
		{
			string ext = Path.GetExtension( filePath ).ToLowerInvariant();
			if ( ext == ".sln" )
				FixLineByLine( filePath, mover, FixSlnLine );
			else if ( ext == ".vcproj" )
				FixLineByLine( filePath, mover, FixVCProjnLine );
		}
	}
}

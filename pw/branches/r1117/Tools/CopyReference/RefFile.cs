using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace CopyReference
{
	public class RefFile
	{
		string refFile;
		string projDir;
		string configName;
		string outputDir;

		List<string> fileStrs = new List<string>();
		int curStrLine;

		public RefFile( string _refFile, string _projDir, string _configName, string _outputDir )
		{
			refFile = _refFile;
			projDir = _projDir;
			configName = _configName;
			outputDir = _outputDir;
			curStrLine = 0;

			using ( StreamReader sr = new StreamReader( refFile ) )
			{
				string s = "";
				while ( ( s = sr.ReadLine() ) != null )
				{
					fileStrs.Add( s );
				}
			}
		}

		public void Do()
		{
			if ( fileStrs.Count == 0 )
				return;

			int beginLine = curStrLine;
			int endLine = beginLine+1;

			while ( true )
			{
				int i = beginLine + 1;
				for ( ; i < fileStrs.Count; i++ )
				{
					if ( fileStrs[i].IndexOf( "[" ) != -1 )
					{
						break;
					}
				}
				endLine = i;
				if ( beginLine+1 == endLine )
					break;

				DoJob( beginLine, endLine );
				
				beginLine = endLine;
			}

		}

		private void DoJob( int beginLine, int endLine )
		{
			string configuration = fileStrs[beginLine].Replace( '[', ' ' ).Replace( ']', ' ' ).Trim().ToLower();

			if ( configuration.IndexOf( configName ) == -1 )
				return;

			for ( int i = beginLine+1; i < endLine; i++ )
			{
				DoLine( i );
			}
		}

		private void DoLine( int strIdx )
		{
			string[] s = { "=>" };
			string[] strs = fileStrs[strIdx].Split( s, StringSplitOptions.RemoveEmptyEntries );
			if ( strs.Length != 1 && strs.Length != 2 )
				return;

			string addingDir = "";

			if ( strs.Length == 2 )
			{
				addingDir = strs[1];
			}

			string finalDir = Path.Combine( Path.Combine( projDir, outputDir ), addingDir );

			if ( !Directory.Exists( finalDir ) )
				Directory.CreateDirectory( finalDir );
			
			string[] fullfilesPath = Directory.GetFiles( Path.Combine( projDir, Path.GetDirectoryName( strs[0] ) ), Path.GetFileName( strs[0] ) );
			foreach ( string f in fullfilesPath )
			{
				File.Copy( f, Path.Combine( finalDir, Path.GetFileName( f ) ), true );
			}
		}

	}
}
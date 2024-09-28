using FixSln.Diagnostics;
using FixSln.SolutionStruct;
using System;
using System.IO;
using System.Collections.Generic;
using SharpSvn;
using FixSln.Utils;
using System.Text.RegularExpressions;

namespace FixSln
{
	class Program
	{
		private static string GetComponentFilter( Project project, string filePath )
		{
			string content;
			using ( TextReader reader = new StreamReader( filePath ) )
			{
				content = reader.ReadToEnd();
				reader.Close();
			}

			Match m = Regex.Match( content, ".*sources[\\s\n]*=[\\s\n]*\\[[\\s\n]*'([\\d\\w_\\.]+)'", RegexOptions.Singleline | RegexOptions.Multiline );
			if ( !m.Success )
				return string.Empty;

			Project.File file = project.FindFile( Path.GetFullPath( Path.Combine( Path.GetDirectoryName( filePath ), m.Groups[1].Value ) ) );
			if ( file == null )
				return string.Empty;

			return file.Filter;
		}

		private static void AppendUnlinkedFiles( FileMover svn, Project project, string folderPath, List<string> unusedFiles )
		{
			foreach ( string folder in Directory.GetDirectories( folderPath ) )
			{
				if ( folder.IndexOf( ".svn" ) >= 0 )
					continue;

				AppendUnlinkedFiles( svn, project, folder, unusedFiles );
			}

			foreach ( string file in Directory.GetFiles( folderPath ) )
			{
				if ( project.FindFile( file ) != null )
					continue;
				if ( string.Compare( project.FilePath, file, StringComparison.InvariantCultureIgnoreCase ) == 0 )
					continue;

				//if ( string.Compare( Path.GetExtension( file ), ".component", StringComparison.InvariantCultureIgnoreCase ) == 0 && project is VCProject )
				//{
				//  if ( string.Compare( Path.GetFileNameWithoutExtension( file ), "all", StringComparison.InvariantCultureIgnoreCase ) == 0 )
				//    ( project as VCProject ).AddFileToVCProject( string.Empty, FileUtils.GetRelativePath( project.Path, file ) );
				//  else
				//    ( project as VCProject ).AddFileToVCProject( GetComponentFilter( project, file ), FileUtils.GetRelativePath( project.Path, file ) );
				//}
				//else if ( string.Compare( Path.GetExtension( file ), ".h", StringComparison.InvariantCultureIgnoreCase ) == 0 ||
				//  string.Compare( Path.GetExtension( file ), ".cpp", StringComparison.InvariantCultureIgnoreCase ) == 0 )
				//  svn.Move( file, file + ".backup" );
				//else
					project.AddFile( FileUtils.GetRelativePath( project.Path, file ), string.Empty ); // just for move file with project's folder

				unusedFiles.Add( file );
			}
		}

		private static void AppendUnlinkedFiles( FileMover svn, Solution solution, bool show )
		{
			List<string> unlinkedFiles = new List<string>();
			foreach ( Project project in solution )
			{
				if ( project.FilesCount == 0 )
					continue;

				AppendUnlinkedFiles( svn, project, project.Path, unlinkedFiles );
				if ( project is VCProject )
					( project as VCProject ).StoreVCProj();
			}
			if ( !show )
				return;

			foreach ( string filePath in unlinkedFiles )
				Log.TraceWarning( "File not linked to project's tree: \"{0}\"", filePath );
			Log.TraceMessage( "Summary", unlinkedFiles.Count );
			Log.TraceMessage( "  Unlinked items: {0}", unlinkedFiles.Count );
			Dictionary<string, int> unlinkedFilesCounts = new Dictionary<string, int>();
			foreach ( string filePath in unlinkedFiles )
			{
				string ext = Path.GetExtension( filePath ).ToLower();
				if ( !unlinkedFilesCounts.ContainsKey( ext ) )
					unlinkedFilesCounts.Add( ext, 1 );
				else
					++unlinkedFilesCounts[ext];
			}

			List<KeyValuePair<string, int>> unlinkedFilesCountsList = new List<KeyValuePair<string, int>>( unlinkedFilesCounts );
			unlinkedFilesCountsList.Sort( ( KeyValuePair<string, int> a, KeyValuePair<string, int> b ) => { return a.Value == b.Value ? string.Compare( a.Key, b.Key ) : b.Value - a.Value; } );
			foreach ( var unlinkedFilesCount in unlinkedFilesCountsList )
				Log.TraceMessage( "    {0}: {1}", unlinkedFilesCount.Key, unlinkedFilesCount.Value );
		}

		static void Main( string[] args )
		{
			Log.AttachDumper( new DebuggerDumper( false, true ) );
			Log.AttachDumper( new ConsoleDumper() );

			try
			{
				FileMover mover = new FileMover( null ); // new FileMover( new SvnClient() );
				Solution solution = new Solution( args[0] );
					
				AppendUnlinkedFiles( mover, solution, true );

				foreach ( Project project in solution )
					project.Move( Path.Combine( solution.Path, Path.Combine( project.Filter, project.Name ) ), mover );

				foreach ( Project project in solution )
				{
					foreach( Project.File file in project )
						FileFixer.FixFile( Path.Combine( Path.Combine( solution.Path, project.Path ), Path.Combine( file.Path, file.Name ) ), mover );
				}

				FileFixer.FixFile( solution.FilePath, mover );
				//mover.CheckMaps();
				//mover.CheckFiles( "c:\\Home\\pf-mirror\\Src2\\", "c:\\Home\\pf-mirror\\Src3\\" );
			}
			catch ( Exception e )
			{
				Log.TraceError( e.Message );
			}
		}
	}
}

using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using System.IO;
using System.Windows.Forms;
using EditorLib.Menu;
using libdb.IO;
using SharpSvn;

namespace EditorLib.IO
{
	public sealed class SourceFileSystem : IMenuUpdater
	{
		private readonly SourceFileSystemConfig config;

		public SourceFileSystem( SourceFileSystemConfig config )
		{
			this.config = config;
			if ( !Directory.Exists( config.RootPath ) )
				config.RootPath = string.Empty;//Environment.GetFolderPath( Environment.SpecialFolder.Personal );
		}

		public Stream OpenFile( string fileRelativePath )
		{
			if ( IsFileExists( fileRelativePath ) )
			{
				return File.OpenRead( GetFullFileName( fileRelativePath ) );
			}
			else
			{
				return null;
			}
		}

		public void AddFolder( string folderRelativePath, string sourcePath, string extension, bool overwrite )
		{
			string[] files = GetFileNames( sourcePath, extension, SearchOption.TopDirectoryOnly );
			foreach ( string file in files )
			{
				AddFile( FileUtils.Combine( folderRelativePath, FileUtils.GetFileName( file ) ), file, overwrite );
			}
		}

		public void AddFile( string fileRelativePath, string sourcePath, bool overwrite )
		{
			if ( !File.Exists( sourcePath ) )
			{
				Log.TraceError( "Cannot add file: source file is not exist." );
				return;
			}

			var fileName = GetFullFileName( fileRelativePath );
			if ( !overwrite && File.Exists( fileName ) )
			{
				Log.TraceWarning(
					"Add file \"{0}\", file with this name already exists. Replaced.",
					fileName
					);
			}

			if ( !Directory.Exists( GetFullFileDirectory( fileRelativePath ) ) )
			{
				var directoryName = GetFullFileDirectory( fileRelativePath );
				Log.TraceWarning(
					"Directory \"{0}\" is not exists. Created.",
					directoryName
					);
				Directory.CreateDirectory( directoryName );
			}

			PerformIoOperation(
				() => File.Copy( sourcePath, fileName, overwrite ),
				() => string.Format( "Error creating file: \"{0}\"", fileName )
				);
		}

		public void AddFile( string fileRelativePath, Stream stream, bool overwrite )
		{
			if ( ReferenceEquals( stream, null ) )
			{
				Log.TraceError( "Cannot add file: stream is null reference." );
				return;
			}

			var fileName = GetFullFileName( fileRelativePath );

			if ( !overwrite && File.Exists( fileName ) )
			{
				Log.TraceWarning(
					"Add file \"{0}\", file with this name already exists. Replaced.",
					fileName
					);
				DeleteFile( fileRelativePath );
			}

			if ( !Directory.Exists( GetFullFileDirectory( fileRelativePath ) ) )
			{
				var directoryName = GetFullFileDirectory( fileRelativePath );
				Log.TraceWarning(
					"Directory \"{0}\" is not exists. Created.",
					directoryName
					);
				Directory.CreateDirectory( directoryName );
			}

			PerformIoOperation(
				() =>
				{
					byte[] buffer = new byte[stream.Length];
					stream.Read( buffer, 0, (int)stream.Length );
					File.WriteAllBytes( fileName, buffer );
				},
				() => string.Format( "Error creating file: \"{0}\"", fileName )
				);
		}

		public void DeleteFile( string fileRelativePath )
		{
			var fileName = GetFullFileName( fileRelativePath );
			if ( File.Exists( fileName ) )
			{
				PerformIoOperation(
					() => File.Delete( fileName ),
					() => string.Format( "Error deleting file: \"{0}\"", fileName )
					);
			}
			else
			{
				Log.TraceError(
					"Cannot delete file \"{0}\": file not exists.",
					fileName
					);
			}
		}

		public void RenameFile( string oldFileRelativePath, string newFileRelativePath )
		{
			var oldFileName = GetFullFileName( oldFileRelativePath );
			if ( File.Exists( oldFileName ) )
			{
				var newFileName = GetFullFileName( newFileRelativePath );
				if ( File.Exists( newFileName ) )
				{
					Log.TraceWarning(
						"Rename file \"{0}\" to \"{1}\", file with new name already exists. Replaced.",
						oldFileName,
						newFileName
						);
					PerformIoOperation(
						() => File.Delete( oldFileName ),
						() => string.Format( "Error deleting file: \"{0}\"", oldFileName )
						);
				}
				PerformIoOperation(
					() => File.Move( oldFileName, newFileName ),
					() => string.Format( "Error moving file: \"{0}\" to \"{1}\"", oldFileName, newFileName )
					);
			}
			else
			{
				Log.TraceError(
					"Cannot rename file \"{0}\": file not exists.",
					oldFileName
					);
			}
		}

		public string GetRelativePath( string path )
		{
			if ( path.StartsWith( RootPath ) )
			{
				return FileUtils.FixFileName( path ).Substring( RootPath.Length );
			}
			else
			{
				return path;
			}
		}

		public string[] GetFileNames( string directoryRelativePath, string extensions, SearchOption opt )
		{
			var path = FileUtils.Combine( RootPath, directoryRelativePath );

			if ( Directory.Exists( path ) )
			{
				List<string> result = new List<string>();
				string[] exts = Array.ConvertAll( extensions.Split( ';' ), ext => ext.Trim() );
				foreach ( string ext in exts )
					result.AddRange( Directory.GetFiles( path, ext, opt ) );

				for ( int i = 0; i < result.Count; ++i )
					result[i] = GetRelativePath( FileUtils.FixFileName( result[i] ) );

        result.Sort();
				return result.ToArray();
			}
			else
			{
				return new string[0];
			}
		}

		public string[] GetDirectories( string directoryRelativePath, SearchOption opt )
		{
			return GetDirectories( directoryRelativePath, opt, "*" );
		}

		/// <param name="mask">Use * to ignore mask. Use ; to set several masks</param>
		public string[] GetDirectories( string directoryRelativePath, SearchOption opt, string mask)
		{
			var path = FileUtils.Combine( RootPath, directoryRelativePath );
			var masks = mask.Split( new []{';'}, StringSplitOptions.RemoveEmptyEntries );
			if ( Directory.Exists( path ) )
			{
				List<string> result = new List<string>();
				foreach(var m in masks)
				 result.AddRange( Directory.GetDirectories( path, m, opt )); 

				for ( int i = 0; i < result.Count; ++i )
					result[i] = GetRelativePath( FileUtils.FixFileName( result[i] ) );

				return result.ToArray();
			}
			else
			{
				return new string[0];
			}
		}

		public string GetFullDirectory( string relativeDirectoryPath )
		{
			return FileUtils.Combine( RootPath, relativeDirectoryPath );
		}

		public string GetFullFileDirectory( string relativeFilePath )
		{
			return FileUtils.GetFolderName( GetFullFileName( relativeFilePath ) );
		}

		public string GetFullFileName( string relativeFilePath )
		{
			return FileUtils.Combine( RootPath, relativeFilePath );
		}

		public bool IsFileExists( string fileRelativePath )
		{
			return File.Exists( GetFullFileName( fileRelativePath ) );
		}

		public bool IsFolderExists( string fileRelativePath )
		{
			return Directory.Exists( GetFullFileName( fileRelativePath ) );
		}

		public bool IsFileModified( SrcFile file )
		{
			if ( file == null || string.IsNullOrEmpty( file.FileName ) )
				return false;

			if ( !IsFileExists( file.FileName ) )
				return false;

			return file.Checksum != Crc32ChecksumGenerator.GenerateChecksum( GetFullFileName( file.FileName ) );
		}

		public void UpdateChecksum( SrcFile file )
		{
			if ( file == null || string.IsNullOrEmpty( file.FileName ) )
				return;

			if ( !IsFileExists( file.FileName ) )
				return;

			file.SetChecksum( Crc32ChecksumGenerator.GenerateChecksum( GetFullFileName( file.FileName ) ) );
		}

		public void UpdateMenu( IEditorWinApplication application )
		{
			application.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.ToolsMenuGroupGuid, 13, new SourceFileSystemCommand( this ), Keys.Alt | Keys.F );
		}


		public string RootPath
		{
			get
			{
				return string.IsNullOrEmpty( config.RootPath ) ?
									FileUtils.FixFileName( Environment.GetFolderPath( Environment.SpecialFolder.Personal ) )
									: config.RootPath;
			}
			set
			{
				if ( Directory.Exists( value ) )
					config.RootPath = FileUtils.FixFileName( value );
				else
					Log.TraceError( "Cannot set root path \"{0}\" for source file system: directory not exists.", value );
			}
		}

		public bool IsRootPathSet
		{
			get { return config.RootPath != string.Empty; }
		}

		private static void PerformIoOperation( Operation operation, Function<string> errorMessage )
		{
			try
			{
				operation();
			}
			catch ( System.Exception excp )
			{
				Log.TraceError(
					"{0}\n" +
					"Exception {1}\n" +
					"\"{2}\"\n" +
					"{3}",
					errorMessage(),
					excp.GetType().FullName,
					excp.Message,
					excp.StackTrace
					);
			}
		}
	}
}

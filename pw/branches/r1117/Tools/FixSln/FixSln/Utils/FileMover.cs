using System;
using System.Collections.Generic;
using System.Text;
using SharpSvn;
using FixSln.Diagnostics;
using System.IO;

namespace FixSln.Utils
{
	public sealed class FileMover
	{
		private readonly SvnClient svn = null;
		private readonly Dictionary<string, string> oldNewMap = new Dictionary<string, string>();
		private readonly Dictionary<string, string> newOldMap = new Dictionary<string, string>();

		public FileMover( SvnClient svn ) { this.svn = svn; }

		private void RegisterMoveItem( string _sourcePath, string _toPath )
		{
			string sourcePath = _sourcePath.ToLowerInvariant();
			string toPath = _toPath.ToLowerInvariant();

			string oldName = string.Empty;
			if ( newOldMap.TryGetValue( sourcePath, out oldName ) )
			{
				oldNewMap[oldName] = toPath;
				newOldMap.Remove( sourcePath );
				newOldMap[toPath] = sourcePath;
			}
			else
			{
				oldNewMap[sourcePath] = toPath;
				newOldMap[toPath] = sourcePath;
			}
		}

		private void RegisterMoveFolder( string sourcePath, string toPath )
		{
			foreach ( string folderPath in Directory.GetDirectories( sourcePath ) )
			{
				string folder = folderPath.Substring( sourcePath.Length );
				if ( string.Compare( folder, ".svn", StringComparison.InvariantCultureIgnoreCase ) == 0 )
					continue;

				RegisterMoveFolder( FileUtils.FixFolderName( Path.Combine( sourcePath, folder ) ), FileUtils.FixFolderName( Path.Combine( toPath, folder ) ) );
			}

			foreach ( string filePath in Directory.GetFiles( sourcePath ) )
				RegisterMoveItem( filePath, Path.Combine( toPath, Path.GetFileName( filePath ) ) );
		}

		private void MoveFile( string sourcePath, string toPath )
		{
			RegisterMoveItem( sourcePath, toPath );

			if ( svn != null )
				svn.Move( sourcePath, toPath, new SvnMoveArgs() { CreateParents = true } );
			else
			{
				Directory.CreateDirectory( Path.GetDirectoryName( toPath ) );
				File.Move( sourcePath, toPath );
			}
		}

		private void MoveFolder( string sourcePath, string toPath )
		{
			RegisterMoveFolder( sourcePath, toPath );

			if ( svn != null )
				svn.Move( sourcePath.Substring( 0, sourcePath.Length - 1 ), toPath.Substring( 0, toPath.Length - 1 ), new SvnMoveArgs() { CreateParents = true } );
			else
			{
				Directory.CreateDirectory( Path.GetDirectoryName( toPath.Substring( 0, toPath.Length - 1 ) ) );
				Directory.Move( sourcePath.Substring( 0, sourcePath.Length - 1 ), toPath.Substring( 0, toPath.Length - 1 ) );
			}
		}

		private void MoveFiles( ICollection<string> sourcePaths, string toPath )
		{
			foreach ( string sourcePath in sourcePaths )
				RegisterMoveItem( sourcePath, Path.Combine( toPath, Path.GetFileName( sourcePath ) ) );

			if ( svn != null )
				svn.Move( sourcePaths, toPath, new SvnMoveArgs() { CreateParents = true } );
			else
			{
				foreach ( string sourcePath in sourcePaths )
					MoveFile( sourcePath, Path.Combine( toPath, Path.GetFileName( sourcePath ) ) );
			}
		}

		/// <summary>
		/// Rename a file or folder
		/// </summary>
		/// <param name="sourcePath">The name of file or folder to rename</param>
		/// <param name="toPath">The new name of file of folder</param>
		public void Move( string _sourcePath, string _toPath )
		{
			string sourcePath = FileUtils.FixCaseInPath( Path.GetFullPath( _sourcePath ) );
			string toPath = FileUtils.FixCaseInPath( Path.GetFullPath( _toPath ) );
			if ( string.Compare( sourcePath, toPath, StringComparison.InvariantCultureIgnoreCase ) == 0 )
				return;

			if ( Directory.Exists( sourcePath ) )
				MoveFolder( FileUtils.FixFolderName( sourcePath ), FileUtils.FixFolderName( toPath ) );
			else if ( File.Exists( sourcePath ) )
				MoveFile( sourcePath, toPath );
		}

		/// <summary>
		/// Move files to specified path
		/// </summary>
		/// <param name="sourcePaths">List of files to move</param>
		/// <param name="toPath">The new path for files</param>
		public void Move( ICollection<string> _sourcePaths, string _toPath )
		{
			string toPath = FileUtils.FixCaseInPath( FileUtils.FixFolderName( Path.GetFullPath( _toPath ) ) );
			List<string> sourcePaths = new List<string>();
			foreach ( var sourcePath in _sourcePaths )
			{
				if ( string.Compare( Path.GetFullPath( Path.GetDirectoryName( sourcePath ) ), Path.GetFullPath( toPath ), StringComparison.InvariantCultureIgnoreCase ) == 0 )
					continue;

				if ( !File.Exists( Path.GetFullPath( sourcePath ) ) )
				{
					Log.TraceWarning( "File not found: \"{0}\"", sourcePath );
					continue;
				}

				sourcePaths.Add( FileUtils.FixCaseInPath( sourcePath ) );
			}

			if ( sourcePaths.Count == 0 )
				return;

			if ( svn != null )
			{
				if ( Directory.Exists( Path.GetFullPath( toPath ) ) )
				{
					foreach ( string sourcePath in sourcePaths )
						MoveFile( sourcePath, Path.Combine( toPath, Path.GetFileName( sourcePath ) ) );
				}
				else if ( sourcePaths.Count == 1 )
					MoveFile( sourcePaths[0], Path.Combine( toPath, Path.GetFileName( sourcePaths[0] ) ) );
				else
					MoveFiles( sourcePaths, toPath );
			}
		}

		public string GetNewReferencedName( string _refFrom, string _oldRef )
		{
			string refFrom = FileUtils.FixFileName( Path.GetFullPath( _refFrom ) );
			string oldRefFrom = string.Empty;
			if ( !newOldMap.TryGetValue( refFrom.ToLowerInvariant(), out oldRefFrom ) )
				oldRefFrom = refFrom;

			string oldRef = FileUtils.FixFileName( Path.Combine( Path.GetDirectoryName( oldRefFrom ), _oldRef ) );
			oldRef = oldRef.Replace( ".\\", string.Empty );
			string newRef = oldRef;
			if ( oldNewMap.TryGetValue( oldRef.ToLowerInvariant(), out newRef ) )
				return FileUtils.FixCaseInPath( newRef );

			if ( !FileUtils.IsPathSeparator( oldRef[oldRef.Length - 1] ) && oldNewMap.TryGetValue( oldRef.ToLowerInvariant() + Path.DirectorySeparatorChar, out newRef ) )
				return FileUtils.FixCaseInPath( newRef );

			return FileUtils.FixCaseInPath( oldRef );
		}

		public void CheckMaps()
		{
			if ( Log.Assert( oldNewMap.Count == newOldMap.Count ) )
				return;
			foreach ( var oldNew in oldNewMap )
			{
				string old = string.Empty;
				if ( Log.Assert( newOldMap.TryGetValue( oldNew.Value, out old ) ) )
					return;
				if ( Log.Assert( oldNew.Key == old ) )
					return;
			}

			foreach ( var oldNew in oldNewMap )
			{
				if ( FileUtils.IsPathSeparator( oldNew.Value[oldNew.Value.Length - 1] ) )
				{
					if ( Log.Assert( Directory.Exists( oldNew.Value.Substring( 0, oldNew.Value.Length - 1 ) ) ) )
						return;
				}
				else if ( Log.Assert( File.Exists( oldNew.Value ) ) )
					return;
			}
		}

		private bool IsSameFiles( string file1, string file2 )
		{
			const int length = 1024 * 1024;
			byte[] buffer1 = new byte[length];
			byte[] buffer2 = new byte[length];
			using ( Stream reader1 = new FileStream( file1, FileMode.Open, FileAccess.Read ) )
			{
				using ( Stream reader2 = new FileStream( file2, FileMode.Open, FileAccess.Read ) )
				{
					int readen1 = length;
					int readen2 = length;
					while ( readen1 == length )
					{
						readen1 = reader1.Read( buffer1, 0, length );
						readen2 = reader2.Read( buffer2, 0, length );
						if ( readen1 != readen2 )
							return false;
						for ( int i = 0; i < readen1; ++i )
							if ( buffer1[i] != buffer2[i] )
								return false;
					}
				}
			}

			return true;
		}

		public void CheckFiles( string _originalPath, string _copyPath )
		{
			string originalPath = FileUtils.FixCaseInPath( FileUtils.FixFolderName( Path.GetFullPath( _originalPath ) ) );
			string copyPath = FileUtils.FixCaseInPath( FileUtils.FixFolderName( Path.GetFullPath( _copyPath ) ) );

			foreach ( var oldNew in oldNewMap )
			{
				if ( FileUtils.IsPathSeparator( oldNew.Value[oldNew.Value.Length - 1] ) )
					continue;

				if ( Log.Assert( IsSameFiles( copyPath + oldNew.Key.Substring( originalPath.Length ), oldNew.Value ) ) )
					return;
			}
		}
	}
}

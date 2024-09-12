using System;
using System.IO;
using libdb.Diagnostics;
using System.Collections.Generic;
using libdb.IO;
using System.Windows.Forms;

namespace EditorLib.IO
{
	/// <summary>
	/// File system on specified root directory
	/// </summary>
	public class WinFileSystem : IConfigFileSystem
	{
		protected string fileSystemRoot = null;
		protected bool writable = true;

		public string RootPath { get { return fileSystemRoot; } }

		public WinFileSystem( string _fileSystemRoot, bool _writable )
		{
			fileSystemRoot = FileUtils.FixFolderName( _fileSystemRoot );
			writable = _writable;
		}

		public WinFileSystem()
		{
		}

		private string[] RemoveFileSystemRootFromFiles( string[] items )
		{
			string[] result = new string[items.Length];

			for ( int i = 0; i < items.Length; ++i )
				result[i] = FileUtils.FixFileName( items[i].Substring( fileSystemRoot.Length ) );

			return result;
		}

		private string[] RemoveFileSystemRootFromDirs( string[] items )
		{
			string[] result = new string[items.Length];

			for ( int i = 0; i < items.Length; ++i )
				result[i] = FileUtils.FixFolderName( items[i].Substring( fileSystemRoot.Length ) );

			return result;
		}

		protected string CombinePath( string path )
		{
			if ( string.IsNullOrEmpty( path ) )
				return fileSystemRoot;

			return FileUtils.Combine( fileSystemRoot, path );
		}

		#region IFileSystem Members

    public virtual string[] GetFolders( string root )
    {
      return GetFolders(root, "*.*");
    }

		public virtual string[] GetFolders( string root, string mask )
		{
			string fullPath = FileUtils.FixFolderName( CombinePath( root ) );
			List<string> folders = new List<string>();
			if ( Directory.Exists( fullPath ) )
			{
				foreach ( string folder in Directory.GetDirectories( fullPath, mask ) )
				{
					if ( (File.GetAttributes( folder ) & FileAttributes.Hidden) != FileAttributes.Hidden && !deletedFolders.ContainsKey( folder.ToLower() ) )
						folders.Add( folder );
				}
			}

			string fullPathLower = fullPath.ToLower();
			foreach ( KeyValuePair<string, string> folder in createdFolders )
			{
				if ( folder.Key.StartsWith( fullPathLower ) )
				{
					int slashPos = folder.Key.IndexOf( FileUtils.PathSeparatorChar, fullPathLower.Length );
					if ( slashPos >= 0 )
						folders.Add( folder.Value.Substring( 0, slashPos + 1 ) );
				}
			}

			return RemoveFileSystemRootFromDirs( folders.ToArray() );
		}

		public string[] GetFiles( string root, string mask )
		{
			string fullPath = CombinePath( root );
			if ( Directory.Exists( fullPath ) )
				return RemoveFileSystemRootFromFiles( Directory.GetFiles( CombinePath( root ), mask ) );
			else
				return new string[0];
		}

		public FileInformation GetFileInfo( string _fileName )
		{
			string fileName = CombinePath( _fileName );
			if ( File.Exists( fileName ) )
				return new FileInformation( File.GetLastWriteTime( fileName ), 0, this );
			if ( Directory.Exists( fileName ) )
				return new FileInformation( File.GetLastWriteTime( fileName ), 0, this, true );
			else
				return new FileInformation();
		}

		public Stream OpenFile( string _fileName )
		{
			string fileName = CombinePath( _fileName );
			try
			{
				return new FileStream( fileName, FileMode.Open, FileAccess.Read, FileShare.ReadWrite );
			}
			catch ( Exception e )
			{
        Log.TraceWarning("OpenFile: Cannot open file \"{0}\". {1}", fileName, e.Message);
				return null;
			}
		}

		public virtual Stream CreateFile( string _fileName )
		{
			if ( !CanCreateFile )
			{
				Log.TraceWarning( "WinFileSystem with root \"{0}\" is read only", fileSystemRoot );
				return null;
			}
			
			try
			{
				if(!Directory.Exists(CombinePath(FileUtils.GetFolderName( _fileName ))))
					CreatePhysicalDirectory(FileUtils.GetFolderName( _fileName ));

				return new FileStream( CombinePath( _fileName ), FileMode.Create, FileAccess.Write, FileShare.Read );
			}
			catch ( Exception e )
			{
				Log.TraceWarning( "Cannot create file \"{0}\". {1}", _fileName , e.Message );
				return null;
			}
		}

		public virtual void DeleteFile( string _fileName )
		{
			if ( !CanCreateFile )
			{
				Log.TraceWarning( "WinFileSystem with root \"{0}\" is read only", fileSystemRoot );
				return;
			}

			string fileName = CombinePath( _fileName );
			try
			{
				File.Delete( fileName );
			}
			catch ( Exception e )
			{
				Log.TraceWarning( "Cannot delete file \"{0}\". {1}", fileName, e.Message );
			}
		}

		public bool CanCreateFile { get { return writable; } }

		public string UserFriendlyName { get { return fileSystemRoot; } }

		public virtual void Serialize( System.Xml.XmlWriter writer )
		{
			writer.WriteStartElement( "fileSystemRoot" );
			if ( fileSystemRoot != null )
				writer.WriteValue( fileSystemRoot );
			
			writer.WriteEndElement();
		}

		public virtual void Deserialize( System.Xml.XmlReader reader )
		{
			reader.ReadStartElement( "fileSystemRoot" );
			fileSystemRoot = reader.ReadString();
			reader.ReadEndElement();
		}

		public virtual bool Configure()
		{
			RootDirectory form = new RootDirectory();
			form.fileSystemRoot.Text = fileSystemRoot;
			if(form.ShowDialog()!=DialogResult.OK) return false;
			fileSystemRoot = FileUtils.FixFolderName( form.fileSystemRoot.Text );
			return true;
		}

		public virtual string GetRealFileName( string fileName )
		{
			return CombinePath( fileName );
		}

		private readonly Dictionary<string, string> deletedFolders = new Dictionary<string, string>();

		public void DeleteFolder( string folderName )
		{
			string fullPath = FileUtils.FixFolderName( CombinePath( folderName ) );
			string fullPathLower = fullPath.ToLower();
			if ( createdFolders.ContainsKey( fullPathLower ) )
				createdFolders.Remove( fullPathLower );
			else if ( !deletedFolders.ContainsKey( fullPathLower ) )
				deletedFolders.Add( fullPathLower, fullPath );
		}
		
		private readonly Dictionary<string, string> createdFolders = new Dictionary<string, string>();

		public void CreateFolder( string folderName )
		{
			string fullPath = FileUtils.FixFolderName( CombinePath( folderName ) );
			string fullPathLower = fullPath.ToLower();
			if ( deletedFolders.ContainsKey( fullPathLower ) )
				deletedFolders.Remove( fullPathLower );
			else if ( !createdFolders.ContainsKey( fullPathLower ) )
				createdFolders.Add( fullPathLower, fullPath );
		}
		// нужно для оверрайда
		public virtual void CreatePhysicalDirectory(string folderName)
		{
			Directory.CreateDirectory( CombinePath(folderName) );
		}

		// нужно для оверрайда
		public virtual void DeletePhysicalDirectory( string folderName )
		{
			Directory.Delete( CombinePath(folderName), true );
		}

		public void Store()
		{
			foreach ( string folderName in createdFolders.Values )
			{
				if ( !Directory.Exists( folderName ) )
					CreatePhysicalDirectory( folderName );
			}

			foreach ( string folderName in deletedFolders.Values )
			{
				if ( Directory.Exists( folderName ) )
				{
					try
					{
						DeletePhysicalDirectory( folderName );
					}
					catch
					{
						Log.TraceError( "Cannot delete: {0}", folderName );
					}
				}
				else
				{
					Log.TraceWarning( "This folder ({0}) not exists", folderName );
				}
			}
			deletedFolders.Clear();
			createdFolders.Clear();
		}

		#endregion
	}
}

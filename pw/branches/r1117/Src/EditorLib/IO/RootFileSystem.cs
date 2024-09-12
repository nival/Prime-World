using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using System.Xml;
using EditorLib.Menu;
using EditorLib.Settings;
using libdb.Diagnostics;
using libdb.IO;

namespace EditorLib.IO
{
	/// <summary>
	/// File system based on many others file systems
	/// </summary>
	[ConfigObject( false, 2 )]
	public sealed class RootFileSystem : IFileSystem, IConfigObject, IMenuUpdater
	{
		private readonly Dictionary<string, ConstructorInfo> fileSystemTypes = new Dictionary<string, ConstructorInfo>();
		private readonly List<IFileSystem> fileSystems = new List<IFileSystem>();
		private IFileSystem writeFileSystem = null;


		#region IFileSystem members

		public string RootPath
		{
			get { return writeFileSystem.RootPath; }
		}

		public string[] GetFolders( string root )
		{
		  return GetFolders( root, "*.*" );
		}

		public string[] GetFolders( string root, string mask )
		{
			List<string> dirs = new List<string>();
			foreach ( IFileSystem fileSystem in fileSystems )
				dirs.AddRange( fileSystem.GetFolders( root, mask ) );

			for ( int i = 0; i < dirs.Count; ++i )
				dirs[i] = FileUtils.FixFolderName( dirs[i] );

			return RemoveDuplicates( dirs );
		}

		public string[] GetFiles( string root, string mask )
		{
			List<string> files = new List<string>();
			foreach ( IFileSystem fileSystem in fileSystems )
				files.AddRange( fileSystem.GetFiles( root, mask ) );

			for ( int i = 0; i < files.Count; ++i )
				files[i] = FileUtils.FixFileName( files[i] );

			return RemoveDuplicates( files );
		}

		public FileInformation GetFileInfo( string fileName )
		{
			FileInformation fileInfo = new FileInformation();
			foreach ( IFileSystem fileSystem in fileSystems )
			{
				FileInformation thisFileInfo = fileSystem.GetFileInfo( fileName );
				if ( (thisFileInfo.IsFileExists || thisFileInfo.IsFolderExists) && thisFileInfo.Time > fileInfo.Time )
					fileInfo = thisFileInfo;
			}
			return fileInfo;
		}

		public Stream OpenFile( string fileName )
		{
			FileInformation fileInfo = GetFileInfo( fileName );

			if ( fileInfo.IsFileExists )
				return fileInfo.OwnerFileSystem.OpenFile( fileName );
			else
				return null;
		}

		public Stream CreateFile( string fileName )
		{
			if ( CanCreateFile )
				return writeFileSystem.CreateFile( fileName );
			else
			{
				Log.TraceWarning( "Root file system cannot create any file" );
				return null;
			}
		}

		public void DeleteFile( string fileName )
		{
			if ( CanCreateFile )
				writeFileSystem.DeleteFile( fileName );
			else
			{
				Log.TraceWarning( "Root file system cannot create any file" );
			}
		}

		public bool CanCreateFile { get { return writeFileSystem != null; } }

		public void DeleteFolder( string folderName )
		{
			if ( CanCreateFile )
			{
				WriteFileSystem.DeleteFolder( folderName );
			}
			else
			{
				Log.TraceWarning( "Root file system cannot create any file" );
			}
		}

		public void CreateFolder( string folderName )
		{
			if ( CanCreateFile )
			{
				WriteFileSystem.CreateFolder( folderName );
			}
			else
			{
				Log.TraceWarning( "Root file system cannot create any file" );
			}
		}

		public void Store()
		{
			if ( !ReferenceEquals( WriteFileSystem, null ) )
			{
				WriteFileSystem.Store();
			}
			else
			{
				MessageBox.Show( "Current file system is not writable.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error );
			}
		}

		#endregion

		public void UpdateMenu( EditorLib.IEditorWinApplication application )
		{
			application.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.ToolsMenuGroupGuid, 12, new RootFileSystemCommand(), Keys.Control | Keys.F );
			foreach ( IFileSystem fileSystem in FileSystems )
			{
				IMenuUpdater menuUpdate = fileSystem as IMenuUpdater;
				if ( menuUpdate != null )
					menuUpdate.UpdateMenu( application );
			}
		}

		public string UserFriendlyName { get { return string.Empty; } }

		public string GetRealFileName( string fileName )
		{
			FileInformation fileInfo = GetFileInfo( fileName );

			if ( fileInfo.IsFileExists )
				return fileInfo.OwnerFileSystem.GetRealFileName( fileName );
			else
				return string.Empty;
		}

		public void RegisterFileSystem( IFileSystem fileSystem )
		{
			if ( !fileSystems.Contains( fileSystem ) )
			{
				fileSystems.Add( fileSystem );
				ObjectsRootFolder.Root.Reset();
			}
		}

		public Dictionary<string, ConstructorInfo> FileSystemTypes { get { return fileSystemTypes; } }

		public void RegisterFileSystemType( Type fileSystemType )
		{
			if ( fileSystemTypes.ContainsKey( fileSystemType.FullName ) )
				Log.TraceWarning( "File system \"{0}\" registring twice", fileSystemType.Name );
			else if ( fileSystemType != GetType() && !fileSystemType.IsInterface )
			{
				ConstructorInfo constrcutor = fileSystemType.GetConstructor( Type.EmptyTypes );
				if ( constrcutor == null )
					Log.TraceWarning( "File system \"{0}\" doesn't has default constructor", fileSystemType.Name );
				else
					fileSystemTypes.Add( fileSystemType.FullName, constrcutor );
			}
		}

		public void UnregisterFileSystem( IFileSystem fileSystem )
		{
			if ( fileSystems.Remove( fileSystem ) )
			{
				if ( WriteFileSystem == fileSystem )
					WriteFileSystem = null;
				ObjectsRootFolder.Root.Reset();
			}
		}

		public IFileSystem WriteFileSystem
		{
			get { return writeFileSystem; }
			set
			{
				if ( value != null && !fileSystems.Contains( value ) )
					Log.TraceWarning( "Root file system doesn't contain file system \"{0}\"", value.UserFriendlyName );
				else
					writeFileSystem = value;
			}
		}

		public void AddFile( string sourcePath, string newFileRelativePath )
		{
			FileInformation fileInfo = GetFileInfo( newFileRelativePath );
			if ( fileInfo.IsFileExists )
			{
				DeleteFile( newFileRelativePath );
			}

			using ( var writer = new BinaryWriter( CreateFile( newFileRelativePath ) ) )
			{
				if ( Path.IsPathRooted( sourcePath ) )
				{
					// Absolute path.
					if ( File.Exists( sourcePath ) )
					{
						writer.Write( File.ReadAllBytes( sourcePath ) );
					}
					else
					{
						Log.TraceError( "Cannot add file to file system: source file \"{0}\"is not exist.", sourcePath );
					}
				}
				else
				{
					// Relative path.
					if ( File.Exists( Path.Combine( Environment.CurrentDirectory, sourcePath ) ) )
					{
						// File in local visible file system.
						writer.Write( File.ReadAllBytes( Path.Combine( Environment.CurrentDirectory, sourcePath ) ) );
					}
					else if ( GetFileInfo( sourcePath ).IsFileExists )
					{
						// File in destination file system.
						using ( var reader = new BinaryReader( OpenFile( sourcePath ) ) )
						{
							writer.Write( reader.ReadBytes( (int)reader.BaseStream.Length ) );
						}
					}
					else
					{
						// Invalid path.
						Log.TraceError( "Cannot add file to file system: source file \"{0}\"is not exist.", sourcePath );
					}
				}
			}
		}

		public bool FileExists( string fileRelativePath )
		{
			return GetFileInfo( fileRelativePath ).IsFileExists;
		}

		public IList<IFileSystem> FileSystems
		{
			get { return fileSystems; }
		}

		private static string[] RemoveDuplicates( List<string> strings )
		{
			strings.Sort();

			List<string> result = new List<string>();
			string prevStr = string.Empty;
			foreach ( string str in strings )
			{
				if ( prevStr != str )
					result.Add( str );
				prevStr = str;
			}

			return result.ToArray();
		}

		#region IConfigObject Members

		public void Serialize( System.Xml.XmlWriter writer, libdb.DB.ConfigFile file )
		{
			writer.WriteStartElement( GetType().Name );
			foreach ( IConfigFileSystem fileSystem in fileSystems )
			{
				writer.WriteStartElement( fileSystem.GetType().FullName );
				if ( fileSystem == writeFileSystem )
					writer.WriteAttributeString( "write", "true" );
				fileSystem.Serialize( writer );
				writer.WriteEndElement();
			}
			writer.WriteEndElement();
		}

		public bool Deserialize( XmlReader reader )
		{
		  if(!reader.ReadToFollowing(GetType().Name))
		  {
        reader.Skip();
        return false;
		  }

      if ( reader.IsEmptyElement )
      {
        reader.Skip();
        return true;
      }

      writeFileSystem = null;
      fileSystems.Clear();

      reader.ReadStartElement( GetType().Name );

		  while (reader.ReadState == ReadState.Interactive)
      {
        if ( !reader.IsStartElement() )
          break;

        ConstructorInfo constructor = null;
        if ( !fileSystemTypes.TryGetValue( reader.Name, out constructor ) )
        {
          Log.TraceWarning( "File system \"{0}\" not registred", reader.Name );
        }
        else
        {
          IConfigFileSystem fileSystem = (IConfigFileSystem)constructor.Invoke( new object[0] );

          bool write = reader.GetAttribute( "write" ) == "true";

          reader.ReadStartElement();//start xFileSystem   
          fileSystem.Deserialize( reader );
          reader.ReadEndElement();//end xFileSystem

          RegisterFileSystem( fileSystem );
          if ( write )
          {
            if ( WriteFileSystem != null )
              Log.TraceWarning( "Several file systems has write attribute in configuration file" );
            else
              WriteFileSystem = fileSystem;
          }
        }
      }

      if ( WriteFileSystem == null )
        Log.TraceWarning( "File system for writing not specified. Editor works in read-only mode" );

      reader.ReadEndElement();//end RootFileSystem
		  return true;
		}
                  
		#endregion
	}
}

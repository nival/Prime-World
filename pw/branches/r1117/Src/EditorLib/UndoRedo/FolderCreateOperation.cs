using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.IO;
using libdb.IO;
using libdb.DB;

namespace libdb.UndoRedo
{
  internal sealed class FolderCreateOperation : IUndoRedoOperation
	{
		private readonly ObjectsFolder parentFolder;
		private readonly string folderName;

		public FolderCreateOperation( ObjectsFolder parentFolder, string folderName )
		{
			this.parentFolder = parentFolder;
			this.folderName = folderName;
			Redo();
		}

		public void Undo()
		{
			parentFolder.RemoveFolder( folderName );
		}
		public void Redo()
		{
			parentFolder.AddFolder( folderName );
		}

		public string DefaultCaption { get { return string.Format( "Create \"{0}\"", folderName ); } }
    public DBResource GetOwner() { return null; }
	}

  internal sealed class FolderRenameOperation : IUndoRedoOperation
	{
		private readonly ObjectsFolder folder;
		private readonly string oldName;
		private readonly string newName;

		public FolderRenameOperation( ObjectsFolder folder, string newName )
		{
			this.folder = folder;
			this.newName = newName;
			this.oldName = folder.Name;

			Redo();
		}

		private void RenameFolder( string name )
		{
			string oldFolderName = folder.FullName;
			string newFodlerName = FileUtils.Combine( folder.Parent.FullName, name );

			List<ObjectsFolder> foldersToRename = new List<ObjectsFolder>();
			List<DBID> olds = new List<DBID>();
			List<DBID> news = new List<DBID>();
			foldersToRename.Add( folder );
			while ( foldersToRename.Count > 0 )
			{
				ObjectsFolder lookFolder = foldersToRename[0];
				foldersToRename.RemoveAt( 0 );

				foldersToRename.AddRange( lookFolder.Folders );
				foreach ( DBID dbid in lookFolder.Items )
				{
					olds.Add( dbid );
					news.Add( DBID.FromFileName( FileUtils.Combine( newFodlerName, dbid.FileName.Substring( oldFolderName.Length ) ), false ) );
				}
			}

			for ( int i = 0; i < olds.Count; ++i )
			{
				DataBase.Rename( news[i], olds[i] );
			}

			DataBase.FileSystem.DeleteFolder( oldFolderName );
			DataBase.FileSystem.CreateFolder( newFodlerName );
			ObjectsRootFolder.Root.RemoveFolder( oldFolderName );

			//ObjectsRootFolder.Root.RemoveFolder( oldFolderName );
			//ObjectsRootFolder.Root.RemoveFolder( newFodlerName );
		}

		public void Undo()
		{
			RenameFolder( oldName );
		}
	
		public void Redo()
		{
			RenameFolder( newName );
		}

		public string DefaultCaption { get { return string.Format( "Rename fodler \"{0}\" to \"{1}\"", oldName, newName ); } }
    public DBResource GetOwner() { return null; }
	}

	internal sealed class FolderRemoveOperation : IUndoRedoOperation
	{
		private readonly ObjectsFolder parentFolder;
		private readonly string folderName;

		public FolderRemoveOperation( ObjectsFolder parentFolder, string folderName )
		{
			this.parentFolder = parentFolder;
			this.folderName = folderName;
		}

		public void Undo()
		{
			parentFolder.AddFolder( folderName );
		}
		public void Redo()
		{
			parentFolder.RemoveFolder( folderName );
		}

		public string DefaultCaption { get { return string.Format( "Create \"{0}\"", folderName ); } }
    public DBResource GetOwner() { return null; }
  }
}

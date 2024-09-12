using libdb.DB;
using libdb.IO;

namespace EditorLib.IO
{
	public sealed class ObjectsRootFolder : ObjectsFolder
	{
		private IFileSystem fileSystem { get { return application.FileSystem; } }
		private readonly IEditorCommonApplication application;
		private ObjectsRootFolder( IEditorCommonApplication application )
			: base( null, string.Empty, application )
		{
			this.application = application;
			DataBase.CreateDBResourceEvent += OnCreateDBResource;
			DataBase.DeleteDBResourceEvent += OnDeleteDBResource;
			DataBase.RenameDBResourceEvent += OnRenameDBResource;
		}

		private void OnCreateDBResource( DBID dbid )
		{
			ObjectsFolder folder = AddFolder( FileUtils.GetFolderName( dbid.FileName ) );
			if ( folder != null )
				folder.AddItem( dbid );
		}

		private void OnDeleteDBResource( DBID dbid )
		{
			ObjectsFolder folder = GetFolder( FileUtils.GetFolderName( dbid.FileName ) );
			if ( folder != null )
				folder.RemoveItem( dbid );
		}

		private void OnRenameDBResource( DBID dbid, DBID oldDbid )
		{
			ObjectsFolder oldFolder = GetFolder( FileUtils.GetFolderName( oldDbid.FileName ) );
			if ( oldFolder != null )
				oldFolder.RemoveItem( oldDbid );
			
			ObjectsFolder folder = AddFolder( FileUtils.GetFolderName( dbid.FileName ) );
			if ( folder != null )
				folder.AddItem( dbid );
		}

		protected override void OnAddFolder( ObjectsFolder parent, ObjectsFolder folder )
		{
			if ( Loaded )
				fileSystem.CreateFolder( folder.FullName );
			if ( AddFolderEvent != null )
				AddFolderEvent( parent, folder );
		}

		protected override void OnRemoveFolder( ObjectsFolder parent, ObjectsFolder folder )
		{
			if ( Loaded )
				fileSystem.DeleteFolder( folder.FullName );
			if ( RemoveFolderEvent != null )
				RemoveFolderEvent( parent, folder );
		}

		protected override void OnAddItem( ObjectsFolder parent, DBID item )
		{
			if ( AddItemEvent != null )
				AddItemEvent( parent, item );
		}

		protected override void OnRemoveItem( ObjectsFolder parent, DBID item )
		{
			if ( RemoveItemEvent != null )
				RemoveItemEvent( parent, item );
		}

		protected override void OnReset()
		{
			if ( RefreshFolderEvent != null )
				RefreshFolderEvent();
		}

		protected override void LoadContent( ObjectsFolder folder )
		{
			string folderRoot = folder.FullName;
			foreach ( string dir in fileSystem.GetFolders( folderRoot, "*.*" ) )
			{
				int lastSlashPos = dir.LastIndexOf( FileUtils.PathSeparatorChar, dir.Length - 2 ) + 1;
				folder.AddFolderInternal( dir.Substring( lastSlashPos, dir.Length - lastSlashPos - 1 ) );
			}

			foreach ( string file in fileSystem.GetFiles( folderRoot, "*.xdb" ) )
				folder.AddItem( DBID.FromFileName( file, false ) );
		}

		public delegate void UpdateFolderEventHandler( ObjectsFolder parent, ObjectsFolder folder );
		public event UpdateFolderEventHandler AddFolderEvent = null;
		public event UpdateFolderEventHandler RemoveFolderEvent = null;

		public delegate void UpdateItemEventHandler( ObjectsFolder parent, DBID item );
		public event UpdateItemEventHandler AddItemEvent = null;
		public event UpdateItemEventHandler RemoveItemEvent = null;

		public delegate void RefreshFolderEventHandler();
		public event RefreshFolderEventHandler RefreshFolderEvent = null;

		private static ObjectsRootFolder root = null;

		public static void Initialize( IEditorCommonApplication application ) 
		{ 
			root = new ObjectsRootFolder( application ); 
			root.LoadContent( root ); 
		}
		
		public static ObjectsRootFolder Root { get { return root; } }
	}
}

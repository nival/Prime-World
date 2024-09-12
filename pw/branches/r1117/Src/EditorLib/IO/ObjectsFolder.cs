using System.Collections.Generic;
using libdb.DB;
using libdb.IO;
using libdb.UndoRedo;

namespace EditorLib.IO
{
	public class ObjectsFolder
	{
		private readonly IEditorCommonApplication application;
		private Dictionary<string, ObjectsFolder> folders = new Dictionary<string, ObjectsFolder>();
		private Dictionary<DBID, bool> items = new Dictionary<DBID, bool>();
		private bool loaded = false;
		private bool loading = false;
		private string name = string.Empty;
		private ObjectsFolder parent = null;

		protected ObjectsFolder(ObjectsFolder parent, string name, IEditorCommonApplication application)
		{
			this.application = application;
			this.parent = parent;
			this.name = name;
		}

		protected bool Loaded
		{
			get { return loaded; }
		}

		public string FullName
		{
			get
			{
				string result = Name + FileUtils.PathSeparatorChar;
				ObjectsFolder folder = Parent;
				while ( folder != null )
				{
					result = folder.Name + FileUtils.PathSeparatorChar + result;
					folder = folder.Parent;
				}

				return result;
			}
		}

		public int DepthLevel
		{
			get
			{
				int result = 0;
				ObjectsFolder folder = Parent;
				while ( folder != null )
				{
					++result;
					folder = folder.Parent;
				}

				return result;
			}
		}

		public ObjectsFolder Parent
		{
			get { return parent; }
		}

		public string Name
		{
			get { return name; }
		}

		public ICollection<ObjectsFolder> Folders
		{
			get
			{
				Load();
				return folders.Values;
			}
		}

		public ICollection<DBID> Items
		{
			get
			{
				Load();
				return items.Keys;
			}
		}

		protected virtual void OnAddFolder(ObjectsFolder parent, ObjectsFolder folder)
		{
		}

		public ObjectsFolder AddFolderInternal(string name)
		{
			ObjectsFolder folder = null;
			if ( folders.TryGetValue( CorrectFolderName(name), out folder ) )
				return folder;

			folder = new ObjectsFolder( this, name, application );
      folders.Add( CorrectFolderName(name), folder );
			if ( !loading )
				ObjectsRootFolder.Root.OnAddFolder( this, folder );
			return folder;
		}

		public ObjectsFolder AddFolder(string name)
		{
			if ( string.IsNullOrEmpty( name ) )
				return this;

			string[] foldersNames = name.Split( FileUtils.PathSeparatorChar );
			ObjectsFolder folder = this;
			foreach (string folderName in foldersNames)
			{
				if ( string.IsNullOrEmpty( folderName ) )
					continue;

				ObjectsFolder nextFolder = null;
				if ( !folder.folders.TryGetValue( CorrectFolderName(folderName), out nextFolder ) )
					nextFolder = folder.AddFolderInternal( folderName );

				folder = nextFolder;
			}

			return folder;
		}

    private string CorrectFolderName(string _name)
    {
      if( string.IsNullOrEmpty( _name ) )
        return name;

      return _name.TrimEnd( '/', '\\' ).ToLowerInvariant() + FileUtils.PathSeparatorChar;
    }

		public ObjectsFolder GetFolder(string name)
		{
			if ( string.IsNullOrEmpty( name ) )
				return this;

			ObjectsFolder result = null;
			if ( !TryGetFolder( name, out result ) )
				return null;

			return result;
		}

		protected virtual void OnRemoveFolder(ObjectsFolder parent, ObjectsFolder folder)
		{
		}

		public bool RemoveFolder(string name)
		{
			ObjectsFolder folder = null;
			if ( TryGetFolder( name.ToLowerInvariant(), out folder ) )
			{
				if ( folder.items.Count > 0 )
				{
					// не "рефакторить" :) Database.Delete изменяет коллекцию items
					var toDelete = new List<DBID>();
					foreach ( var dbid in folder.items.Keys )
						toDelete.Add( dbid );
					
					foreach(var dbid in toDelete)
						DataBase.Delete( dbid );
				}

				if ( folder.folders.Count > 0 )
				{
					// не "рефакторить" :) UndoRedo.AddOperation( изменяет коллекцию folders
					var ops = new List<FolderRemoveOperation>();
					foreach (ObjectsFolder innerFolder in folder.folders.Values)
						ops.Add( new FolderRemoveOperation( folder, innerFolder.Name ) );

					foreach (var op in ops)
						application.UndoRedo.AddOperation( op );
				}

				bool result = folder.Parent.folders.Remove( CorrectFolderName(folder.Name) );
				if ( result )
					ObjectsRootFolder.Root.OnRemoveFolder( folder.Parent, folder );
				return result;
			}

			return false;
		}

		public bool TryGetFolder(string name, out ObjectsFolder folder)
		{
			folder = null;
			if ( string.IsNullOrEmpty( name ) )
				return false;

			Load();

			ObjectsFolder result = this;
			string[] folderNames = name.Split( FileUtils.PathSeparatorChar );
			foreach (string folderName in folderNames)
			{
				if ( string.IsNullOrEmpty( folderName ) )
					continue;
				result.Load();
				if ( !result.folders.TryGetValue( CorrectFolderName(folderName), out result ) )
					return false;
			}

			folder = result;
			return true;
		}

		public bool IsFolderExists(string name)
		{
			if ( name == null ) return false;
			Load();
      return folders.ContainsKey( CorrectFolderName(name) );
		}
    
    public bool IsPathExists( string path )
    {
      if( string.IsNullOrEmpty( path ) )
        return false;

      if( this.FullName == path )
        return true;

      string[] pathFolders = path.Trim( '/', '\\' ).Split( new[] { '/', '\\' } );

      ObjectsFolder objectFolder = this;

      foreach( string folder in pathFolders )
      {
        if( !objectFolder.IsFolderExists( folder ) )
        {
          return false;
        }

        objectFolder = objectFolder.GetFolder( folder );
      }

      return true;
    }

		public bool IsItemExistsHere(DBID name)
		{
			Load();
			return items.ContainsKey( name );
		}

		public bool IsItemExistsRecursive(DBID dbid)
		{
			string folderName = FileUtils.GetFolderName( dbid.FileName );
			ObjectsFolder folder = null;
			if ( !TryGetFolder( folderName, out folder ) )
				return false;

			return folder.IsItemExistsHere( dbid );
		}

		protected virtual void OnAddItem(ObjectsFolder parent, DBID item)
		{
		}

		public void AddItem(DBID item)
		{
			DBID fileNameDbid = DBID.FromDBID( item, false );
			if ( !items.ContainsKey( fileNameDbid ) )
			{
				items.Add( fileNameDbid, false );
				if ( !loading )
					ObjectsRootFolder.Root.OnAddItem( this, fileNameDbid );
			}
		}

		protected virtual void OnRemoveItem(ObjectsFolder parent, DBID item)
		{
		}

		public bool RemoveItem(DBID item)
		{
			if ( items.Remove( item ) )
			{
				ObjectsRootFolder.Root.OnRemoveItem( this, item );
				return true;
			}

			return false;
		}

		protected virtual void LoadContent(ObjectsFolder folder)
		{
		}

		private void Load()
		{
			if ( loaded )
				return;

			loading = true;
			ObjectsRootFolder.Root.LoadContent( this );
			loading = false;
			loaded = true;
		}

		protected virtual void OnReset()
		{
		}

		public void Reset()
		{
			foreach (ObjectsFolder folder in Folders)
				folder.Reset();

			folders.Clear();
			items.Clear();
			loaded = false;
			OnReset();
		}

		public override string ToString()
		{
			if ( parent == null )
				return "Root";
			else
				return Name;
		}

		public static int Compare(ObjectsFolder folderA, ObjectsFolder folderB)
		{
			return string.Compare( folderA.Name, folderB.Name );
		}
	}
}
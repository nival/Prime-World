using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using EditorLib.Extensions;
using EditorLib.IO;
using libdb.DB;
using libdb.IO;
using libdb.UndoRedo;
using Win32;

namespace EditorLib.ObjectsBrowser
{

  public partial class ObjectsBrowserControl : ListView
  {
    #region Nested Types

    private enum EEditState
    {
      NoEdit,
      CreateItem,
      CreateFolder,
      Rename
    }

    private class ObjectsBrowserComparer : IComparer<ListViewItem>, IComparer
    {
      private readonly ObjectsBrowserSort sortingType;

      public ObjectsBrowserComparer( ObjectsBrowserSort _sortingType )
      {
        sortingType = _sortingType;
      }

      public int Compare( ListViewItem x, ListViewItem y )
      {
        if ( x == null && y == null ) return 0;

        if ( x == null ) return -1;

        if ( y == null ) return 1;

        if ( x.Text == ".." ) return -1;

        if ( y.Text == ".." ) return 1;

        //папки всегда вначале
        if ( IsFolder( x ) && IsFolder( y ) )
        {
          ObjectsFolder folderX = (ObjectsFolder)x.Tag;
          ObjectsFolder folderY = (ObjectsFolder)y.Tag;

          return ObjectsFolder.Compare( folderX, folderY );
        }

        if ( IsFolder( x ) && !IsFolder( y ) )
          return -1;

        if ( !IsFolder( x ) && IsFolder( y ) )
          return 1;

        //сортируем файлы по sortType
        DBID dbIdX = x.Tag as DBID;
        DBID dbIdY = y.Tag as DBID;

        //сортируем файлы по имени
        if ( sortingType == ObjectsBrowserSort.ByName )
          return DBID.Compare( dbIdX, dbIdY );

        //сортируем файлы по расширению
        if ( dbIdX == null && dbIdY == null ) return 0;

        if ( dbIdX == null ) return -1;

        if ( dbIdY == null ) return 1;

        string extX = Path.GetExtension( dbIdX.FileName ).TrimStart( '.' );
        string extY = Path.GetExtension( dbIdY.FileName ).TrimStart( '.' );

        //order by type
        int result = string.Compare( extX, extY );

        if ( result == 0 )//then by name
          result = DBID.Compare( dbIdX, dbIdY );

        return result;
      }

      int IComparer.Compare( object x, object y )
      {
        return Compare( x as ListViewItem, y as ListViewItem );
      }

      private static bool IsFolder( ListViewItem _item )
      {
        if ( _item == null )
          return false;

        return _item.Tag is ObjectsFolder;
      }
    }

    #endregion

    private static IEditorWinApplication application = null;

    private EEditState editState = EEditState.NoEdit;

    private ObjectsFolder createdFolder = null;
    private DBID createdItem = null;

    internal event EventHandler ChangeCurrentFolderEvent = null;
    public event EventHandler ChangeSelectedFolderEvent = null;
    public event EventHandler ChangeSelectedItemEvent = null;
    public event EventHandler<DBIDEventArgs> OpenItemEvent = null;

    private ObjectsBrowserViewState _viewState = ObjectsBrowserViewState.FoldersAndFiles;
    public ObjectsBrowserViewState ViewState
    {
      get { return _viewState; }
      set 
      { 
        _viewState = value; 
        RefreshList();
      }
    }

    public ObjectsBrowserControl()
    {
      DoubleBuffered = true;
      InitializeComponent();

      View = View.Details;
      HideSelection = false;

      Columns.Add( "Name" );
      HeaderStyle = ColumnHeaderStyle.None;
      SmallImageList = new ImageList();
      SmallImageList.ColorDepth = ColorDepth.Depth32Bit;

      SHFILEINFO shinfo = new SHFILEINFO();
      Shell.SHGetFileInfo( string.Empty, Kernel.FILE_ATTRIBUTE_DIRECTORY, ref shinfo, Marshal.SizeOf( shinfo ), Shell.SHGFI_ICON | Shell.SHGFI_SMALLICON | Shell.SHGFI_USEFILEATTRIBUTES );
      Icon folderIcon = Icon.FromHandle( shinfo.hIcon );
      SmallImageList.Images.Add( folderIcon );
      SmallImageList.Images.Add( folderIcon );

      Shell.SHGetFileInfo( ".xml", Kernel.FILE_ATTRIBUTE_NORMAL, ref shinfo, Marshal.SizeOf( shinfo ), Shell.SHGFI_ICON | Shell.SHGFI_SMALLICON | Shell.SHGFI_USEFILEATTRIBUTES );
      Icon fileIcon = Icon.FromHandle( shinfo.hIcon );
      SmallImageList.Images.Add( fileIcon );

      if ( application != null )
      {
        ImageList typedImageList = application.Application.Extensions.GetTypesImageList();
        if ( typedImageList != null )
          foreach ( Image img in typedImageList.Images )
            SmallImageList.Images.Add( img );
      }

      ListViewItemSorter = new ObjectsBrowserComparer( ObjectsBrowserSort.ByName );

      AfterLabelEdit += OnAfterLabelEdit;

      if ( ObjectsRootFolder.Root != null )
      {
        ObjectsRootFolder.Root.AddFolderEvent += OnAddFolder;
        ObjectsRootFolder.Root.AddItemEvent += OnAddItem;
        ObjectsRootFolder.Root.RemoveFolderEvent += OnRemoveFolder;
        ObjectsRootFolder.Root.RemoveItemEvent += OnRemoveItem;
        ObjectsRootFolder.Root.RefreshFolderEvent += OnRefreshFolder;
      }
    }

    public static void SetApplication( IEditorWinApplication _application ) { application = _application; }

    public void Reset()
    {
      CurrentFolder.Reset();
      RefreshList();
    }

    public void ReloadCurrentFolder()
    {
      if ( CurrentFolder != null )
        CurrentFolder.Reset();
      RefreshList();
    }

    private void InvokeSafe( Delegate method )
    {
      if ( IsHandleCreated )
        Invoke( method );
    }

    private void InvokeSafe( Delegate method, params object[] args )
    {
      if ( IsHandleCreated )
        Invoke( method, args );
    }

    private void OnRefreshFolder()
    {
      InvokeSafe( new Operation( RefreshList ) );
    }

    private void OnAddFolder( ObjectsFolder parent, ObjectsFolder folder )
    {
      if ( parent == CurrentFolder )
      {
        createdFolder = folder;
        InvokeSafe( new Operation( RefreshList ) );
      }
    }

    private void OnAddItem( ObjectsFolder parent, DBID obj )
    {
      if ( parent == CurrentFolder )
      {
        createdItem = obj;
        InvokeSafe( new Operation( RefreshList ) );
      }
    }

    private void OnRemoveFolder( ObjectsFolder parent, ObjectsFolder folder )
    {
      if ( parent == CurrentFolder )
      {
        InvokeSafe( new Operation( RefreshList ) );
      }
    }

    private void OnRemoveItem( ObjectsFolder parent, DBID obj )
    {
      if ( parent == CurrentFolder )
      {
        InvokeSafe( new Operation( RefreshList ) );
      }
    }

    public void RefreshList()
    {
      BeginUpdate();
      Items.Clear();

      AddFolders();

      if( ViewState == ObjectsBrowserViewState.FoldersAndFiles )
        AddItems();
      
      Sort();
      EndUpdate();

      createdFolder = null;
      createdItem = null;
    }

    private void AddFolders()
    {
      if( CurrentFolder == null )
        return;

      if ( CurrentFolder.Parent != null )
      {
        ListViewItem newFolder = Items.Add( "..", 1 );
        newFolder.Tag = CurrentFolder.Parent;
      }

      foreach ( ObjectsFolder folder in CurrentFolder.Folders )
      {
        ListViewItem newFolder = Items.Add( string.Format( folder.Name ), 0 );
        newFolder.Tag = folder;
        if ( folder == createdFolder )
        {
          SelectItem( newFolder.Index );
        }
      }
    }

    private void AddItems()
    {
      if ( CurrentFolder == null )
        return;

      foreach ( DBID obj in CurrentFolder.Items )
      {
        DBPtr<DBResource> ptr = DataBase.Get<DBResource>( obj );
        if ( ptr != null )
        {
          DBResource resource = ptr.Get();
          if ( resource != null )
          {
            string ext = Path.GetExtension( obj.FileName );
            if(!string.IsNullOrEmpty(ext))
              ext = ext.TrimStart( '.' );
              
            //если расширения нет, файл отображается всегда!!!
            if ( !string.IsNullOrEmpty( ext ) && !ExtensionsFilter.Contains( ext ) )
              continue;

            if ( filterType != null && !TypeUtils.IsSubclassOf( resource.GetType(), filterType ) )
              continue;

            int imgIndex = application.Application.Extensions.GetTypeIconIndex( resource.GetType(), true );
            if ( imgIndex < 0 )
              imgIndex = 2;
            else
              imgIndex += 3;

            string name = FileUtils.GetFileName( obj.FileName );

            if ( application.Application.Extensions.GetEditorsCount( resource.GetType() ) > 0 )
            {
              name += "°";
            }

            ListViewItem newItem = Items.Add( name, imgIndex );
            newItem.Tag = obj;
          }
        }
      }
    }

    private void SelectItem( int _itemIndex )
    {
      if ( _itemIndex < 0 || Items.Count <= _itemIndex )
        return;

      Items[_itemIndex].Selected = true;
      EnsureVisible( _itemIndex );
    }

    protected override void OnMouseDoubleClick( MouseEventArgs e )
    {
      base.OnMouseDoubleClick( e );
      OpenSelectedItem();
    }

    protected override void WndProc( ref Message message )
    {
      const int WM_PAINT = 0xf;

      // if the control is in details view mode and columns
      // have been added, then intercept the WM_PAINT message
      // and reset the last column width to fill the list view
      switch ( message.Msg )
      {
      case WM_PAINT:
        if ( editState == EEditState.NoEdit && this.View == View.Details && this.Columns.Count > 0 )
          this.Columns[this.Columns.Count - 1].Width = -2;
        break;
      }

      // pass messages on to the base control for processing
      base.WndProc( ref message );
    }

    private void OpenSelectedItem()
    {
      if ( SelectedItems.Count == 1 )
      {
        ObjectsFolder selectedFolder = SelectedItems[0].Tag as ObjectsFolder;
        if ( selectedFolder != null )
        {
          CurrentFolder = selectedFolder;
        }
        else
        {
          if ( OpenItemEvent != null )
          {
            DBID dbid = SelectedItems[0].Tag as DBID;
            bool newInstance = ( ( ModifierKeys & Keys.Control ) == Keys.Control );
            OpenItemEvent( this, new DBIDEventArgs( dbid, newInstance ) );
          }
        }
      }
    }

    protected override void OnSelectedIndexChanged( EventArgs e )
    {
      ObjectsFolder currentSelectedFolder = SelectedFolder;
      DBID currentSelectedItem = SelectedObject;

      base.OnSelectedIndexChanged( e );
      selectedFolders.Clear();
      selectedObjects.Clear();

      foreach ( int index in SelectedIndices )
      {
        ListViewItem obj = Items[index];
        //don't include root folder in search
        if ( index == 0 && CurrentFolder != ObjectsRootFolder.Root )
          continue;
        if ( obj.Tag is ObjectsFolder )
          selectedFolders.Add( obj.Tag as ObjectsFolder );
        else if ( obj.Tag is DBID )
          selectedObjects.Add( obj.Tag as DBID );
      }

      if ( SelectedFolder != currentSelectedFolder && ChangeSelectedFolderEvent != null )
        ChangeSelectedFolderEvent( this, EventArgs.Empty );

      if ( SelectedObject != currentSelectedItem && ChangeSelectedItemEvent != null )
        ChangeSelectedItemEvent( this, EventArgs.Empty );
    }

    private void Select( ObjectsFolder folder, DBID obj )
    {
      int index = 0;
      if ( folder != null )
      {
        foreach ( ListViewItem item in Items )
        {
          ObjectsFolder itemFolder = item.Tag as ObjectsFolder;
          if ( itemFolder == null )
            continue;

          if ( ObjectsFolder.Compare( itemFolder, folder ) == 0 )
          {
            index = item.Index;
            break;
          }
        }
      }
      else if ( !DBID.IsNullOrEmpty( obj ) )
      {
        if ( !selectedObjects.Contains( obj ) )
          selectedObjects.Add( obj );
        foreach ( ListViewItem item in Items )
        {
          DBID itemObject = item.Tag as DBID;
          if ( DBID.IsNullOrEmpty( itemObject ) )
            continue;

          if ( DBID.Compare( itemObject, obj ) == 0 )
          {
            index = item.Index;
            break;
          }
        }
      }

      try
      {
        BeginUpdate();
        SelectedItems.Clear();
        SelectItem( index );
      }
      finally
      {
        EndUpdate();
      }
    }

    private ObjectsFolder currentFolder = null;
    public ObjectsFolder CurrentFolder
    {
      get { return currentFolder; }
      set
      {
        currentFolder = value;
        InvokeSafe( new Operation( RefreshList ) );
        InvokeSafe( new Operation<int>( SelectItem ), 0 );

        if ( ChangeCurrentFolderEvent != null )
          ChangeCurrentFolderEvent( this, EventArgs.Empty );
      }
    }

    private List<ObjectsFolder> selectedFolders = new List<ObjectsFolder>();
    private List<DBID> selectedObjects = new List<DBID>();

    public IEnumerable<ObjectsFolder> SelectedFolders { get { return selectedFolders; } }
    public IEnumerable<DBID> SelectedObjects { get { return selectedObjects; } }

    public ObjectsFolder SelectedFolder
    {
      get { return selectedFolders.Count == 1 ? selectedFolders[0] : null; }
      set { Select( value, DBID.Empty ); }
    }

    public DBID SelectedObject
    {
      get { return selectedObjects.Count == 1 ? selectedObjects[0] : null; }
      set { Select( null, value ); }
    }

    private List<string> extensionsFilter = new List<string>( DataBase.KnownResourcesExtensions );
    public List<string> ExtensionsFilter
    {
      get { return extensionsFilter; }
      set
      {
        extensionsFilter = value;
        RefreshList();
      }
    }

    private Type filterType = null;
    public Type FilterType
    {
      get { return filterType; }
      set
      {
        filterType = value;
        RefreshList();
      }
    }

    public void Sort( ObjectsBrowserSort _sort )
    {
      ListViewItemSorter = new ObjectsBrowserComparer( _sort );
    }

    private void OnAfterLabelEdit( object sender, LabelEditEventArgs e )
    {
      object tag = Items[e.Item].Tag;
      if ( string.IsNullOrEmpty( e.Label ) || application == null )
      {
        e.CancelEdit = true;
        if ( editState != EEditState.Rename )
          Items.RemoveAt( e.Item );
        else if ( tag is ObjectsFolder )
          Items[e.Item].Text = Items[e.Item].Text;
        else
          Items[e.Item].Text = FileUtils.GetFileName( ( tag as DBID ).FileName );

        LabelEdit = false;
        editState = EEditState.NoEdit;


        return;
      }

      switch ( editState )
      {
      case EEditState.CreateFolder:
        {
          if ( CurrentFolder.IsFolderExists( e.Label ) )
          {
            e.CancelEdit = true;
            Items[e.Item].BeginEdit();
            return;
          }

          e.CancelEdit = true;
          editState = EEditState.NoEdit;
          Items.RemoveAt( e.Item );
          application.Application.UndoRedo.AddOperation( new FolderCreateOperation( CurrentFolder, e.Label ) );
          LabelEdit = false;
        }

        break;
      case EEditState.CreateItem:
        {
          if ( !( tag is DBResource ) )
            return;

          DBID dbid = null;
          if ( !DBID.TryCreateDBID( CurrentFolder.FullName, e.Label, tag.GetType(), out dbid ) )
          {
            e.CancelEdit = true;
            Items[e.Item].BeginEdit();
            return;
          }

          e.CancelEdit = true;
          editState = EEditState.NoEdit;
          Items.RemoveAt( e.Item );

          var createResult = application.Application.Extensions.Wizards.CreateResource( dbid, tag.GetType(), application, (DBResource)tag );
          if ( createResult == ResourceCreationResult.Failed_InvalidName )
          {
            e.CancelEdit = true;
            Items[e.Item].BeginEdit();
            return;
          }
          LabelEdit = false;
        }

        break;
      case EEditState.Rename:
        {
          ObjectsFolder folder = tag as ObjectsFolder;
          DBID dbid = null;
          if ( folder != null )
          {
            string oldFolderName = folder.FullName;
            string newFodlerName = FileUtils.Combine( folder.Parent.FullName, e.Label );

            if ( CurrentFolder.IsFolderExists( e.Label ) )
            {
              e.CancelEdit = true;
              Items[e.Item].BeginEdit();
              return;
            }

            e.CancelEdit = true;
            editState = EEditState.NoEdit;
            //Items.RemoveAt( e.Item );
            application.Application.UndoRedo.Start( string.Format( "Rename folder \"{0}\" to \"{1}\"", folder.Name, e.Label ) );
            DataBase.AddOperation( new FolderRenameOperation( folder, e.Label ) );
            application.Application.UndoRedo.Commit();
            LabelEdit = false;
          }
          else if ( !DBID.IsNullOrEmpty( dbid = tag as DBID ) )
          {
            DBResource resource = DataBase.Get<DBResource>( dbid ).Get();

            DBID newDbid = null;
            if ( !DBID.TryCreateDBID( CurrentFolder.FullName, e.Label, resource.GetType(), out newDbid ) )
            {
              e.CancelEdit = true;
              Items[e.Item].BeginEdit();
              return;
            }

            e.CancelEdit = true;
            editState = EEditState.NoEdit;
            Items.RemoveAt( e.Item );
            DataBase.Rename( newDbid, dbid );
            LabelEdit = false;
          }
        }

        break;
      }
      application.Toolbar.UpdateToolbars();
      application.MainMenu.UpdateMenu();
      Refresh();
    }

    internal void CreateNewFolder()
    {
      int index = Items.Count;
      foreach ( ListViewItem obj in Items )
      {
        if ( obj.Tag is DBID )
        {
          index = obj.Index;
          break;
        }
      }

      ListViewItem newFolderItem = Items.Insert( index, string.Empty, 0 );

      LabelEdit = true;
      SelectedItems.Clear();
      editState = EEditState.CreateFolder;

      newFolderItem.BeginEdit();
    }

    internal void CreateNewItem( Type type )
    {
      if ( type == null )
        return;

      int index = Items.Count;

      ListViewItem newItem = Items.Insert( index, string.Empty, 2 );
      newItem.Tag = TypeUtils.CreateInstance( type );

      LabelEdit = true;
      SelectedItems.Clear();
      editState = EEditState.CreateItem;

      newItem.BeginEdit();
    }

    internal void RenameItem()
    {
      if ( SelectedItems.Count == 0 )
        return;

      if ( AreItemsReferredByEditors() )
        return;

      ListViewItem obj = SelectedItems[0];
      if ( SelectedFolder != null )
        obj.Text = obj.Text.TrimStart( '[' ).TrimEnd( ']' );
      else if ( SelectedObject != null )
        obj.Text = GeneratedCodeUtilities.GetOnlyFileName( obj.Text );
      else
        return;

      LabelEdit = true;
      editState = EEditState.Rename;
      obj.BeginEdit();
    }

    internal void DeleteItem()
    {
      if ( SelectedItems.Count == 0 )
        return;

      if ( AreItemsReferredByEditors() )
        return;

      foreach ( ListViewItem obj in SelectedItems )
      {
        DBID id = obj.Tag as DBID;
        if ( id != null )
        {
          Dictionary<DBID, int> links;
          Dictionary<DBID, int> backlinks;
          DataBase.Get<DBResource>( id ).CollectLinks( out links, out backlinks );

          if ( backlinks.Count > 0 )
          {
            List<string> backlinkNames = new List<string>();
            foreach ( DBID backlink in backlinks.Keys )
            {
              if ( backlinkNames.Count == 3 )
              {
                backlinkNames.Add( "..." );
                break;
              }
              else
                backlinkNames.Add( "\"" + backlink.Name + "\"" );
            }

            switch ( MessageBox.Show( string.Format( "There are some links to resource \"{0}\" from {1}. Do you want delete this resource (all links will be nulled)?", id, string.Join( ", ", backlinkNames.ToArray() ) ),
              "Found Links To Resource", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question ) )
            {
            case DialogResult.No:
              continue;
            case DialogResult.Cancel:
              return;
            }
          }
          CurrentFolder.RemoveItem( id );
          DataBase.Delete( id );
        }
        else
        {
          ObjectsFolder folder = obj.Tag as ObjectsFolder;
          if ( null == folder )
            return;

          bool folderHasBacklinks = HasFolderBacklinks( folder, folder.FullName );

          if ( folderHasBacklinks )
          {
            // Show warning
            switch ( MessageBox.Show( string.Format( "There are some outside links to resources inside folder \"{0}\".\n Do you want delete this folder (all links will be nulled)?", folder.Name ),
              "Found Links To Resource", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question ) )
            {
            case DialogResult.No:
              continue;
            case DialogResult.Cancel:
              return;
            }
            folderHasBacklinks = false;
          }

          if ( !folderHasBacklinks )
          {
            //@Ivn@TODO: Currently remove folders from Objects Browser can be dangerous
            if ( application.Application.UndoRedo.IsCommandStarted )
              application.Application.UndoRedo.AddOperation( new FolderRemoveOperation( CurrentFolder, folder.Name ) );
            else
            {
              application.Application.UndoRedo.Start( "FolderRemoveOperation" );
              application.Application.UndoRedo.AddOperation( new FolderRemoveOperation( CurrentFolder, folder.Name ) );
              application.Application.UndoRedo.Commit();
            }
          }
        }
      }
      application.Toolbar.UpdateToolbars();
      application.MainMenu.UpdateMenu();
    }

    private bool AreItemsReferredByEditors()
    {
      if ( EditorsPool.Count == 0 )
        return false;

      foreach ( ListViewItem obj in SelectedItems )
      {
        DBID id = obj.Tag as DBID;
        if ( id != null )
        {
          if ( IsReferredByEditors( id ) )
          {
            MessageBox.Show( "Object is referred by active editors. Unable to proceed.", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
            return true;
          }
        }
        else
        {
          ObjectsFolder folder = obj.Tag as ObjectsFolder;
          if ( null == folder )
            continue;

          if ( IsFolderReferredByEditors( folder ) )
          {
            MessageBox.Show( "Object is referred by active editors. Unable to proceed.", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
            return true;
          }
        }
      }
      return false;
    }

    private bool IsReferredByEditors( DBID id )
    {
      if ( EditorsPool.Count == 0 )
        return false;

      Dictionary<DBID, bool> editorTargets = new Dictionary<DBID, bool>();
      foreach ( AbstractEditor editor in EditorsPool.GetAllEditorInstances() )
        if ( !editor.TargetDBID.IsEmpty )
          editorTargets[editor.TargetDBID] = true;

      if ( editorTargets.ContainsKey( id ) )
        return true;

      bool isReferred = false;
      id.ProcessBacklinks( ( dbid ) => { if ( editorTargets.ContainsKey( dbid ) ) { isReferred = true; return false; } return true; } );

      return isReferred;
    }

    private bool IsFolderReferredByEditors( ObjectsFolder folder )
    {
      if ( EditorsPool.Count == 0 )
        return false;

      foreach ( DBID itemDBID in folder.Items )
      {
        if ( IsReferredByEditors( itemDBID ) )
          return true;
      }

      foreach ( ObjectsFolder item in folder.Folders )
      {
        if ( IsFolderReferredByEditors( item ) )
          return true;
      }
      return false;
    }

    private bool HasFolderBacklinks( ObjectsFolder folder, string baseFolder )
    {
      foreach ( DBID itemDBID in folder.Items )
      {
        DBPtr<DBResource> objPtr = DataBase.Get<DBResource>( itemDBID );
        Dictionary<DBID, int> backlinks = objPtr.GetBackLinks();
        foreach ( var item in backlinks )
        {
          if ( !item.Key.FileName.Contains( baseFolder ) )
            return true;
        }
      }

      foreach ( ObjectsFolder item in folder.Folders )
      {
        if ( HasFolderBacklinks( item, baseFolder ) )
          return true;
      }
      return false;
    }

    private void ChangeResourceType()
    {
      DBID oldDbid = SelectedObject;
      ChangeTypeForm form = new ChangeTypeForm( SelectedObject );
      form.ShowDialog();
      if ( form.DialogResult == DialogResult.OK )
      {
        SelectedObject = null;
        SelectedObject = oldDbid;
      }
    }

    #region Internal clipboard

    private struct ClipboardItemInfo
    {
      public readonly ObjectsFolder rootFolder;
      public readonly bool cut;

      public ClipboardItemInfo( ObjectsFolder rootFolder, bool cut ) { this.rootFolder = rootFolder; this.cut = cut; }
    }

    private Dictionary<DBID, ClipboardItemInfo> internalClipboard = new Dictionary<DBID, ClipboardItemInfo>();
    private List<ObjectsFolder> internalRemoveFolders = new List<ObjectsFolder>();

    private void FillClipboardFromFolder( Dictionary<DBID, ClipboardItemInfo> clipboard, List<ObjectsFolder> foldersToRemove, ObjectsFolder searchFolder, ObjectsFolder root, bool cut )
    {
      foreach ( ObjectsFolder folder in searchFolder.Folders )
        FillClipboardFromFolder( clipboard, foldersToRemove, folder, root, cut );
      foreach ( DBID obj in searchFolder.Items )
      {
        if ( !clipboard.ContainsKey( obj ) )
          clipboard.Add( obj, new ClipboardItemInfo( root, cut ) );
      }
      if ( cut )
        foldersToRemove.Add( searchFolder );
    }

    private void CopyPathsFromSelection()
    {
      StringBuilder paths = new StringBuilder();

      for ( int i = 0; i < SelectedItems.Count; i++  )
      {
        ListViewItem selected = SelectedItems[i];
        if ( selected.Tag is ObjectsFolder )
        {
          ObjectsFolder folder = (ObjectsFolder)selected.Tag;
          if ( i == SelectedItems.Count-1 )
            paths.Append( folder.FullName );
          else
            paths.AppendLine( folder.FullName );
        }
        else if ( selected.Tag is DBID )
        {
          DBID dbId = (DBID)selected.Tag;

          if ( !dbId.IsEmpty )
          {
            if ( i == SelectedItems.Count - 1 )
              paths.Append( dbId.FileName );
            else
              paths.AppendLine( dbId.FileName );
          }
        }
      }

      if ( paths.Length > 0 )
      {
        try
        {
          Clipboard.SetText( paths.ToString() );
        }
        catch
        {
          //Log.TraceWarning( "Cannot place \"{0}\" to clipboard. {1}", paths.ToString(), e.Message );
        }
      }
    }

    private void ShowInExplorer()
    {
      if ( SelectedItems.Count > 0 )
      {
        object selected = SelectedItems[0].Tag;

        string root = Path.GetFullPath( application.Application.FileSystem.RootPath );
        if ( selected is ObjectsFolder )
        {
          ObjectsFolder folder = (ObjectsFolder)selected;
          string pathToFolder = Path.Combine( root, folder.FullName.Trim( '/', '\\' ).Replace( '/', '\\' ) );

          if ( Directory.Exists( pathToFolder ) )
            System.Diagnostics.Process.Start( string.Format( "\"{0}\"", pathToFolder ) );
        }
        else if ( selected is DBID )
        {
          DBID dbId = (DBID)selected;

          if ( !dbId.IsEmpty )
          {
            string pathToFile = Path.Combine( root, dbId.GetFullFileName().Trim( '/', '\\' ).Replace( '/', '\\' ) );

            if ( File.Exists( pathToFile ) )
              System.Diagnostics.Process.Start( "explorer.exe", string.Format( "/select,\"{0}\"", pathToFile ) );
          }
        }
      }
    }

    private void FillClipboardFromSelection( bool cut )
    {
      internalClipboard.Clear();
      internalRemoveFolders.Clear();
      foreach ( ListViewItem selected in SelectedItems )
      {
        ObjectsFolder selectedFolder = selected.Tag as ObjectsFolder;
        DBID selectedItem = null;
        if ( selectedFolder != null )
          FillClipboardFromFolder( internalClipboard, internalRemoveFolders, selectedFolder, CurrentFolder, cut );
        else if ( !DBID.IsNullOrEmpty( selectedItem = selected.Tag as DBID ) )
        {
          if ( !internalClipboard.ContainsKey( selectedItem ) )
            internalClipboard.Add( selectedItem, new ClipboardItemInfo( CurrentFolder, cut ) );
        }
      }
    }

    private void PasteFromClipboard( Dictionary<DBID, ClipboardItemInfo> clipboard, List<ObjectsFolder> foldersToRemove, bool deepCopy )
    {
      using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Paste" ) )
      {
        List<DBID> objectsToRemoveFromClipboard = new List<DBID>();
        foreach ( KeyValuePair<DBID, ClipboardItemInfo> obj in clipboard )
        {
          string dbidRelativePath = obj.Key.FileName;
          string folderFullName = obj.Value.rootFolder != null ? FileUtils.FixFolderName( obj.Value.rootFolder.FullName ) : string.Empty;
          if ( dbidRelativePath.StartsWith( folderFullName, StringComparison.InvariantCultureIgnoreCase ) )
            dbidRelativePath = dbidRelativePath.Substring( folderFullName.Length );

          if ( obj.Value.cut )
          {
            DBID newDbid = DBID.FromFileName( FileUtils.Combine( CurrentFolder.FullName, dbidRelativePath ), false );
            if ( newDbid != obj.Key )
            {
              DataBase.Rename( newDbid, obj.Key );
              objectsToRemoveFromClipboard.Add( obj.Key );
            }
          }
          else
          {
            string rootPath = FileUtils.GetFolderName( FileUtils.Combine( CurrentFolder.FullName, dbidRelativePath ) );
            DBID newDbid = DBID.GenerateUnique( rootPath, GeneratedCodeUtilities.GetOnlyFileName( obj.Key.FileName ), DataBase.Get<DBResource>( obj.Key ).Get().GetType() );
            DataBase.Copy( newDbid, obj.Key );
          }
        }

        foreach ( ObjectsFolder folder in foldersToRemove )
          DataBase.FileSystem.DeleteFolder( folder.FullName );

        foreach ( DBID obj in objectsToRemoveFromClipboard )
          clipboard.Remove( obj );
        foldersToRemove.Clear();

        trans.Commit();
      }

      application.Toolbar.UpdateToolbars();
    }

    #endregion

    #region Context menu and keyboard shortcuts

    protected override void OnKeyDown( KeyEventArgs e )
    {
      if ( ( e.KeyData & Keys.KeyCode ) == Keys.X && e.Control )
        FillClipboardFromSelection( true );
      else if ( ( e.KeyData & Keys.KeyCode ) == Keys.C && e.Control && e.Shift )
        CopyPathsFromSelection();
      else if ( ( e.KeyData & Keys.KeyCode ) == Keys.C && e.Control )
        FillClipboardFromSelection( false );
      else if ( ( e.KeyData & Keys.KeyCode ) == Keys.V && e.Control )
        PasteFromClipboard( internalClipboard, internalRemoveFolders, false );
      else if ( ( e.KeyData & Keys.KeyCode ) == Keys.V && e.Control && e.Shift )
        PasteFromClipboard( internalClipboard, internalRemoveFolders, true );
      else if ( ( e.KeyData & Keys.KeyCode ) == Keys.F2 )
        RenameItem();
      else if ( ( e.KeyData & Keys.KeyCode ) == Keys.Delete )
        DeleteItem();
      else if ( ( e.KeyData & Keys.KeyCode ) == Keys.Enter )
        OpenSelectedItem();
      else
        base.OnKeyDown( e );
    }

    protected override void OnMouseClick( MouseEventArgs e )
    {
      base.OnMouseClick( e );
      if ( e.Button != MouseButtons.Right )
        return;

      if ( SelectedItems.Count == 1 )
      {
        if ( SelectedItems[0].Tag is ObjectsFolder )
          SelectedFolder = SelectedItems[0].Tag as ObjectsFolder;
        else if ( SelectedItems[0].Tag is DBID )
          SelectedObject = SelectedItems[0].Tag as DBID;
      }

      ContextMenu contextMenu = null;

      if ( ( SelectedItems.Count == 1 ) && !DBID.IsNullOrEmpty( SelectedObject ) && application != null )
      {
        contextMenu = application.ContextMenu.CreateContextMenu( DataBase.Get<DBResource>( SelectedObject ).Get(), null );
        contextMenu.MenuItems.Add( "-" );
      }

      MenuItem itemMenu = null;

      if ( contextMenu == null )
      {
        contextMenu = new ContextMenu();

        if ( SelectedItems.Count == 1 )
        {
          itemMenu = new MenuItem( "Recursive Import...", RunRecursiveImport );
          itemMenu.Tag = SelectedFolder;
          contextMenu.MenuItems.Add( itemMenu );

          contextMenu.MenuItems.Add( "-" );
        }
      }

      if ( SelectedItems.Count == 1 )
      {
        itemMenu = new MenuItem( "Rename", ( sender, eventArgs ) => RenameItem(), Shortcut.F2 );
        contextMenu.MenuItems.Add( itemMenu );
      }

      itemMenu = new MenuItem( "Delete", ( sender, eventArgs ) => DeleteItem(), Shortcut.Del );
      contextMenu.MenuItems.Add( itemMenu );
      itemMenu.Enabled = SelectedItems.Count > 0;

      if ( SelectedItems.Count == 1 && SelectedObject != null )
      {
        itemMenu = new MenuItem( "Change Type...", ( sender, eventArgs ) => ChangeResourceType(), Shortcut.None );
        contextMenu.MenuItems.Add( itemMenu );
      }

      contextMenu.MenuItems.Add( "-" );

      itemMenu = new MenuItem( "Copy", ( sender, eventArgs ) => FillClipboardFromSelection( false ), Shortcut.CtrlC );
      contextMenu.MenuItems.Add( itemMenu );
      itemMenu.Enabled = SelectedItems.Count > 0;

      itemMenu = new MenuItem( "Copy as Path", ( sender, eventArgs ) => CopyPathsFromSelection(), Shortcut.CtrlShiftC );
      contextMenu.MenuItems.Add( itemMenu );
      itemMenu.Enabled = SelectedItems.Count > 0;

      itemMenu = new MenuItem( "Cut", ( sender, eventArgs ) => FillClipboardFromSelection( true ), Shortcut.CtrlX );
      contextMenu.MenuItems.Add( itemMenu );
      itemMenu.Enabled = SelectedItems.Count > 0;

      itemMenu = new MenuItem( "Paste", ( sender, eventArgs ) => PasteFromClipboard( internalClipboard, internalRemoveFolders, false ), Shortcut.CtrlV );
      contextMenu.MenuItems.Add( itemMenu );
      itemMenu.Enabled = internalClipboard.Count > 0;

      itemMenu = new MenuItem( "Paste With Full Copy", ( sender, eventArgs ) => PasteFromClipboard( internalClipboard, internalRemoveFolders, true ), Shortcut.CtrlShiftV );
      contextMenu.MenuItems.Add( itemMenu );
      itemMenu.Enabled = internalClipboard.Count > 0;

      contextMenu.MenuItems.Add( "-" );

      itemMenu = new MenuItem( "Show in Explorer", ( sender, eventArgs ) => ShowInExplorer() );
      contextMenu.MenuItems.Add( itemMenu );
      itemMenu.Enabled = SelectedItems.Count == 1;

      contextMenu.Show( this, new Point( e.X, e.Y ) );
    }

    private void RunRecursiveImport( object sender, EventArgs e )
    {
      MenuItem item = sender as MenuItem;
      if ( item == null )
        return;

      ObjectsFolder objFolder = item.Tag as ObjectsFolder;
      if ( objFolder == null )
        return;

      ImportRecursive form = new ImportRecursive( objFolder );
      form.ShowDialog();
    }

    #endregion
  }

  public class DBIDEventArgs : EventArgs
  {
    public readonly DBID dbid;
    public readonly bool newInstance = false;

    public DBIDEventArgs( DBID _dbid, bool _newInstance )
    {
      dbid = _dbid;
      newInstance = _newInstance;
    }
  }

  public enum ObjectsBrowserSort
  {
    ByName,
    ByType
  }

  public enum ObjectsBrowserViewState
  {
    FoldersAndFiles,
    Folders
  }
}

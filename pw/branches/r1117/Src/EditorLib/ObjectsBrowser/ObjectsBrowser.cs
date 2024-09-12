using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using DBTypes;
using EditorLib.IO;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using Win32;

namespace EditorLib.ObjectsBrowser
{
  public partial class ObjectsBrowser : UserControl
  {
    #region Initialization

    public ObjectsBrowser()
    {
      InitializeComponent();
    }

    #endregion

    #region class NewItemsCobmoBoxItem

		private class NewItemsCobmoBoxItem
		{
			public readonly string Name;
			public readonly Type Type = null;
      public readonly TemplateDefinition Template = null;
			public NewItemsCobmoBoxItem( string name, Type type )
			{
				Name = name;
				Type = type;
			}
      public NewItemsCobmoBoxItem( string name, TemplateDefinition template )
      {
        Name = name;
        Template = template;
      }
      public override string ToString()
			{
				return Name;
			}
		}
		
    #endregion

	  #region class ToolStripListBox

		private class ToolStripListBox : ToolStripControlHost
		{
			public ToolStripListBox() : base( new ListBox() )
			{
			}

			public ListBox ListBoxControl
			{
				get
				{
					return Control as ListBox;
				}
			}
		}

		#endregion
	
    internal delegate void ChangeSelectedFolderEventHandler( ObjectsBrowser control, ObjectsFolder folder );
		internal event ChangeSelectedFolderEventHandler ChangeSelectedFolderEvent = null;
    
    public delegate void ChangeSelectedItemEventHandler( ObjectsBrowser control, DBID item );
		public event ChangeSelectedItemEventHandler ChangeSelectedItemEvent = null;
    public event EventHandler<DBIDEventArgs> OpenItemEvent = null;

		private readonly FolderHistory history = new FolderHistory();
		private FolderBookmarks folderBookmarks;
		private NewItemTypesConfig newItemsConfig;
		private ToolStripListBox newItemsList;

    [Browsable(false)]
    public string CurrentFolder
		{
			get 
      {
        if( objectsBrowserControl.CurrentFolder == null )
          return string.Empty;
        
        return objectsBrowserControl.CurrentFolder.FullName; 
      }
			set
			{
        if( DesignMode )
          return;

				ObjectsFolder folder;
				if ( ObjectsRootFolder.Root.TryGetFolder( value, out folder ) )
					objectsBrowserControl.CurrentFolder = folder;
        else
          objectsBrowserControl.CurrentFolder = ObjectsRootFolder.Root;
			}
		}

    [Browsable(false)]
    public DBID SelectedObject 
    {
      get { return objectsBrowserControl.SelectedObject; }
      set { objectsBrowserControl.SelectedObject = value; }
    }

		public void SelectItem( DBID dbid )
		{
      if( DBID.IsNullOrEmpty( dbid ) )
        return;

			if ( ObjectsRootFolder.Root.IsItemExistsRecursive( dbid ) )
			{
				CurrentFolder = FileUtils.GetFolderName( dbid.FileName );
				objectsBrowserControl.SelectedObject = dbid;
			}
		}

    public void ReselectCurrentItem()
    {
			RaiseChangeSelectedItemEvent();
    }

		public void Reset()
		{
			objectsBrowserControl.Reset();
		}

		protected override void WndProc( ref Message m )
		{
			base.WndProc( ref m );
			if ( m.Msg == User.WM_APPCOMMAND )
			{
				if ( User.GET_APPCOMMAND_LPARAM( (int)( m.LParam.ToInt64() ) ) == User.APPCOMMAND_BROWSER_BACKWARD )
					btnBack_ButtonClick( null, EventArgs.Empty );
				else if ( User.GET_APPCOMMAND_LPARAM( (int)( m.LParam.ToInt64() ) ) == User.APPCOMMAND_BROWSER_FORWARD )
					btnForward_ButtonClick( null, EventArgs.Empty );
			}
		}

		private void OnLoad( object sender, EventArgs e )
		{
      if( DesignMode )
        return;

      // здесь все правильно, при иниц. не надо через пропертю this.CurrentFolder гнать(по крайней мере до ближайшего рефактора)
      if( objectsBrowserControl.CurrentFolder == null )
        objectsBrowserControl.CurrentFolder = ObjectsRootFolder.Root;
      else
        objectsBrowserControl.CurrentFolder = objectsBrowserControl.CurrentFolder;

			objectsBrowserControl.ExtensionsFilter = new List<string>( DataBase.KnownResourcesExtensions );

		  AddCurrentFolderToHistory();

			newItemsList = new ToolStripListBox();
			tsNewItemButton.DropDown.Items.Insert( 2, newItemsList );
			newItemsList.ListBoxControl.IntegralHeight = true;
			newItemsList.ListBoxControl.SelectionMode = SelectionMode.One;
			newItemsList.ListBoxControl.Width = 220;
			newItemsList.ListBoxControl.Height = 250;
			newItemsList.ListBoxControl.MaximumSize = new Size( 220, 250 );
			newItemsList.ListBoxControl.MinimumSize = new Size( 220, 30 );
			newItemsList.ListBoxControl.MouseClick += newItemsListBoxMouseClick;
			newItemsList.ListBoxControl.KeyUp += tsNewItemSearchTb_KeyUp;
			newItemsList.ListBoxControl.SelectedIndexChanged +=
				(sender1, e1) => tsNewItemButton.DropDown.Items[0].ImageIndex = GetImageIndex( newItemsList.ListBoxControl.SelectedItem.ToString() );
						
					
			
			tsNewItemSearchTb.TextBox.MouseWheel += (sender1, e1) => newItemsList.ListBoxControl.TopIndex += e1.Delta > 0 ? -6 : 6;
			tsNewItemButton.DropDown.ImageList = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypesImageList();

      newItemsConfig = EditorCommonApplication.ApplicationSingleton.Settings.Get<NewItemTypesConfig>();
			newItemsConfig.UpdateKnownTypes( DataBase.KnownResources );
			FillRecentNewItems();
			FillNewItemsDropDown( string.Empty );

			ConstructBookmarksMenu();
		}

		private void OnNewFolderButtonClick( object sender, EventArgs e )
		{
			objectsBrowserControl.CreateNewFolder();
		}

		private void OnCurrentFolderChanged( object sender, EventArgs e )
		{
      //Recent folders
      ToolStripItem item = tsbBookmarks.DropDownItems[0];

      if ( folderBookmarks.IsBookMarked( CurrentFolder ) )
        item.Text = "Remove bookmark";
      else
        item.Text = "Bookmark current folder";

      //History
      AddCurrentFolderToHistory();
		}

		private void OnChangeSelectedFolder( object sender, EventArgs e )
		{
			if ( ChangeSelectedFolderEvent != null )
				ChangeSelectedFolderEvent( this, objectsBrowserControl.SelectedFolder );
		}

		private void OnChangeSelectedItem( object sender, EventArgs e )
		{
			RaiseChangeSelectedItemEvent();
		}

    private void OnOpenItem( object sender, DBIDEventArgs args )
		{
      if( OpenItemEvent != null )
        OpenItemEvent( sender, args );

      folderBookmarks.RegisterRecentFolder( CurrentFolder );
      FillBookmarks();
    }

		private void RaiseChangeSelectedItemEvent()
		{
			if (ChangeSelectedItemEvent != null)
				ChangeSelectedItemEvent(this, objectsBrowserControl.SelectedObject);
		}

		#region NEW ITEMS MENU

		private void toolStripComboBox1_TextUpdate( object sender, EventArgs e )
		{
			FillNewItemsDropDown( tsNewItemSearchTb.Text );
		}

		void FillRecentNewItems()
		{
			for ( int i = tsNewItemButton.DropDown.Items.Count-1; i >4 ; i-- )
				tsNewItemButton.DropDown.Items.RemoveAt( i );
			
			foreach ( var item in newItemsConfig.recentTypes )
			{
				var i = tsNewItemButton.DropDown.Items.Add( item );
				i.ImageIndex = GetImageIndex( item );
				i.Click += RecentItemClick;
			}
		}

		static int GetImageIndex(string type)
		{
			Type t;
			DataBase.TryGetType( type, out t );
			return EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( t, true );
		}

		void RecentItemClick(object sender, EventArgs e)
		{
			CreateNewItem( (sender as ToolStripDropDownItem).Text );
		}

		void FillNewItemsDropDown( string searchString )
		{
			newItemsList.ListBoxControl.BeginUpdate();
			newItemsList.ListBoxControl.Items.Clear();
			foreach ( string name in newItemsConfig.allTypes )
			{
				Type type = null;
				if ( DataBase.TryGetType( name, out type ) && name.IndexOf( searchString, StringComparison.InvariantCultureIgnoreCase ) != -1 )
					newItemsList.ListBoxControl.Items.Add( new NewItemsCobmoBoxItem( name, type ) );
			}

      ObjectsFolder folder = ObjectsRootFolder.Root.GetFolder( "Templates" );
      if ( folder != null && folder.Items != null )
      {
        foreach ( DBID item in folder.Items )
        {
          DBPtr<TemplateDefinition> template = DataBase.Get<TemplateDefinition>( item );
          if ( template == null || template.Get() == null )
            continue;

          newItemsList.ListBoxControl.Items.Add( new NewItemsCobmoBoxItem( "* " + template.Get().name, template.Get() ) );
        }
      }

			newItemsList.ListBoxControl.EndUpdate();
		}

		private void tsNewItemSearchTb_KeyUp( object sender, KeyEventArgs e )
		{
			int indMoveCoeff = 0;
			switch ( e.KeyCode )
			{
				case Keys.Enter:
          if ( newItemsList.ListBoxControl.SelectedIndex > -1 )
            CreateNewItem( newItemsList.ListBoxControl.SelectedItem as NewItemsCobmoBoxItem );
          else
            CreateNewItem( tsNewItemSearchTb.Text );
					break;
				case Keys.Down:
					indMoveCoeff = 1;
					break;
				case Keys.Up:
					indMoveCoeff = -1;
					break;
			}

			if ( indMoveCoeff == 0 || newItemsList.ListBoxControl.Items.Count < 0 || sender is ListBox )
				return;
				
			if ( newItemsList.ListBoxControl.SelectedIndex == -1 )
				newItemsList.ListBoxControl.SelectedIndex = indMoveCoeff == 1 ? 0 : newItemsList.ListBoxControl.Items.Count - 1;
			else
			{
				int newind = newItemsList.ListBoxControl.SelectedIndex + indMoveCoeff;
				if ( newind > newItemsList.ListBoxControl.Items.Count - 1 )
					newind = 0;
				else if ( newind < 0 )
					newind = newItemsList.ListBoxControl.Items.Count - 1;
				newItemsList.ListBoxControl.SelectedIndex = newind;
			}
		}

		private void newItemsListBoxMouseClick(object sender, MouseEventArgs e)
		{
			CreateNewItem( newItemsList.ListBoxControl.SelectedItem.ToString() );
		}

    private void CreateNewItem( NewItemsCobmoBoxItem listItem )
    {
      if ( null == listItem )
        return;

      if ( listItem.Type != null )
        CreateNewItem( listItem.Type );
      else
      {
        //NewObjectTemplateForm form = new NewObjectTemplateForm( application, template );
        //form.ShowDialog();

      }
    }

		private void CreateNewItem( string type )
		{
			Type t;
			if ( DataBase.TryGetType( type, out t ) )
			{
				objectsBrowserControl.CreateNewItem( t );
				newItemsConfig.AddRecentItem( type );
				FillRecentNewItems();
				tsNewItemButton.DropDown.Close();
			}
			else
				Log.TraceWarning( "Cannot create item with type: {0}", type );
		}

    private void CreateNewItem( Type type )
    {
      if ( null != type )
      {
        objectsBrowserControl.CreateNewItem( type );
        newItemsConfig.AddRecentItem( type.Name );
        FillRecentNewItems();
        tsNewItemButton.DropDown.Close();
      }
    }

		private void tsNewItemButton_DropDownOpened( object sender, EventArgs e )
		{
			tsNewItemSearchTb.Focus();
		}

		#endregion

		#region BOOKMARKS
		
		private void ConstructBookmarksMenu()
		{
			objectsBrowserControl.ChangeCurrentFolderEvent += OnCurrentFolderChanged;
			folderBookmarks = EditorCommonApplication.ApplicationSingleton.Settings.Get<FolderBookmarks>();
			FillBookmarks();
      folderBookmarks.FolderBookmarksChangedEvent += BookmarksChangedEvent;
		}

		private void BubbleSortBookmarks( List<ToolStripMenuItem> items )
		{
      for ( int i = items.Count - 1; i > 0; --i )
			{
				for ( int j = 0; j < i; j++ )
				{
					if ( ( items[j] ).ShortcutKeys > ( items[j + 1] ).ShortcutKeys )
					{
						ToolStripMenuItem item = items[j];
						items.RemoveAt( j );
						items.Insert( j + 1, item );
					}
					else if ( ( items[j] ).Text.CompareTo( ( items[j + 1] ).Text ) > 0 )
					{
						ToolStripMenuItem item = items[j];
						items.RemoveAt( j );
						items.Insert( j + 1, item );
					}
				}
			}
		}

		private void BookmarksChangedEvent()
		{
      FillBookmarks();
    }

    private void FillBookmarks()
		{
      tsbBookmarks.DropDownItems.Clear();
      ToolStripMenuItem setOrRemove = null;
      if ( folderBookmarks.IsBookMarked( CurrentFolder ) )
        setOrRemove = new ToolStripMenuItem( "Remove bookmark" );
      else
        setOrRemove = new ToolStripMenuItem( "Bookmark current folder" );
      setOrRemove.Click += SetOrRemoveBookmarkItemClick;
      tsbBookmarks.DropDownItems.Add( setOrRemove );

      tsbBookmarks.DropDownItems.Add( new ToolStripSeparator() );
      tsbBookmarks.DropDownItems.Add( new ToolStripMenuItem 
      { 
        Text = "Bookmarks", 
        Image = EditorLibResources.bookmarks,
        ForeColor = System.Drawing.Color.Gray, 
        Font = new Font( "Tahoma", 8.25F, FontStyle.Bold )
      } );
      tsbBookmarks.DropDownItems.Add( new ToolStripSeparator() );

      List<ToolStripMenuItem> bookmarkList = new List<ToolStripMenuItem>();
      foreach ( FolderBookmarks.BookmarkInfo info in folderBookmarks.bookmarks )
			{
				ToolStripMenuItem item = new ToolStripMenuItem( info.folderPath );
				item.ShortcutKeys = (Keys)info.hotKey;
				item.Click += BookMarkDropDownItemClick;
        bookmarkList.Add( item );
			}

			BubbleSortBookmarks( bookmarkList );
      foreach ( ToolStripMenuItem item in bookmarkList )
        tsbBookmarks.DropDownItems.Add( item );

      tsbBookmarks.DropDownItems.Add( new ToolStripSeparator() );
      tsbBookmarks.DropDownItems.Add( new ToolStripMenuItem
      {
        Text = "Recent folders", 
        Image = EditorLibResources.history,
        ForeColor = System.Drawing.Color.Gray,
        Font = new Font( "Tahoma", 8.25F, FontStyle.Bold )
      });
      tsbBookmarks.DropDownItems.Add( new ToolStripSeparator() );

      foreach ( FolderBookmarks.BookmarkInfo info in folderBookmarks.recentFolders )
      {
        ToolStripMenuItem item = (ToolStripMenuItem)tsbBookmarks.DropDownItems.Add( info.folderPath );
        item.Click += BookMarkDropDownItemClick;
      }
    }

		private void SetOrRemoveBookmarkItemClick( object sender, EventArgs e )
		{
			if ( folderBookmarks.IsBookMarked( CurrentFolder ) )
				folderBookmarks.RemoveBookmark( CurrentFolder );
			else
				folderBookmarks.SetBookmark( CurrentFolder, Shortcut.None );
		}

		public void KeyPressProcess( object sender, KeyEventArgs e )
		{
			if ( e.Control && e.Shift && ( (int)e.KeyCode > (int)Keys.D0 && (int)e.KeyCode < (int)Keys.D9 ) )
			{
				folderBookmarks.SetBookmark( ( (ObjectsBrowserPanel)sender ).CurrentFolder, (Shortcut)( Keys.Control | e.KeyCode ) );
			}
			else
			{
        foreach ( ToolStripItem item in tsbBookmarks.DropDownItems )
        {
          if ( !( item is ToolStripMenuItem ) )
            continue;
          if ( (int)( e.KeyCode & Keys.KeyCode ) == (int)( ( item as ToolStripMenuItem ).ShortcutKeys & Keys.KeyCode ) )
            BookMarkDropDownItemClick( item, EventArgs.Empty );
        }
			}
		}

		private void BookMarkDropDownItemClick( object sender, EventArgs e )
		{
			string folder = ( (ToolStripMenuItem)sender ).Text;

			if ( ObjectsRootFolder.Root.GetFolder( folder ) != null )
				CurrentFolder = folder;
			else
				folderBookmarks.RemoveBookmark( folder );
		}

		#endregion

		#region HISTORY

		private void btnBack_ButtonClick( object sender, EventArgs e )
		{
      string folder = history.GoBack();
		  GoToFolder( folder );
      UpdateHistoryNavigation();
		}

		private void OnDropDownItemClicked( object sender, ToolStripItemClickedEventArgs e )
		{
		  string folder = e.ClickedItem.Text;
		  int index = (int)e.ClickedItem.Tag;
		  NavigateToFolder( folder, index );
		  UpdateHistoryNavigation();
		}

		private void btnForward_ButtonClick( object sender, EventArgs e )
		{
			string folder = history.GoForward();
		  GoToFolder( folder );
      UpdateHistoryNavigation();
		}

    private void btnBack_DropDownOpening( object sender, EventArgs e )
    {
      UpdateDropDown( btnBack.DropDown.Items, history.GetBackwardItems() );
    }

    private void btnForward_DropDownOpening( object sender, EventArgs e )
    {
      UpdateDropDown( btnForward.DropDown.Items, history.GetForwardItems() );
    }

    private void AddCurrentFolderToHistory()
    {
      if( CurrentFolder != history.CurrentItem )
      {
        history.Add( CurrentFolder );
        UpdateHistoryNavigation();        
      }
    }

    private void RemoveNonexistent(string _folder)
    {
      Log.TraceWarning( "Папки '{0}' больше не существует, элемент удален из истории", _folder );
      history.Remove( _folder );
    }

    private void UpdateDropDown( ToolStripItemCollection _dropdownItems, IEnumerable<KeyValuePair<string, int>> _historyItems )
    {
      _dropdownItems.Clear();

      foreach( KeyValuePair<string, int> historyItem in _historyItems )
      {
        var item = new ToolStripMenuItem
        {
          Text = historyItem.Key,
          Tag = historyItem.Value
        };

        _dropdownItems.Add( item );
      }
    }

    private void UpdateHistoryNavigation()
    {
      btnBack.Enabled = history.CanGoBack;
      btnForward.Enabled = history.CanGoForward;
    }

    private void GoToFolder(string _folder)
    {
      if( ObjectsRootFolder.Root.GetFolder( _folder ) != null )
        CurrentFolder = _folder;
      else
        RemoveNonexistent( _folder );
    }

    private void NavigateToFolder(string _folder, int _index)
    {
      if( ObjectsRootFolder.Root.GetFolder( _folder ) != null )
        CurrentFolder = history.NavigateTo( _index );
      else
        RemoveNonexistent( _folder );
    }

    #endregion

		#region Filter

		private void tsbFilter_ButtonClick(object sender, EventArgs e)
		{
			ShowFilterDialog();
		}

		private void mnuClearFilter_Click(object sender, EventArgs e)
		{
			objectsBrowserControl.ExtensionsFilter = new List<string>(DataBase.KnownResourcesExtensions);
			tsbFilter.Image = EditorLibResources.filterOff;
		}

		private void mnuEditFilter_Click(object sender, EventArgs e)
		{
			ShowFilterDialog();
		}

		private void ShowFilterDialog()
		{
			ItemSelectorForm<string> form = new ItemSelectorForm<string>(DataBase.KnownResourcesExtensions, objectsBrowserControl.ExtensionsFilter);
		  form.Text = "Select Extensions";

			Point location = PointToScreen(tsbFilter.Owner.Location);
			location.X += 100;
			location.Y += 20;
			form.Location = location;

			if (form.ShowDialog() == DialogResult.OK)
			{
				objectsBrowserControl.ExtensionsFilter = form.SelectedItems;
				tsbFilter.Image = form.IsAllSelected ? EditorLibResources.filterOff : EditorLibResources.filterOn;
			}
		}		
		#endregion

		#region Sorting

		private void mnuSortByName_Click(object sender, EventArgs e)
		{
			objectsBrowserControl.Sort(ObjectsBrowserSort.ByName);
			tsbSort.Image = EditorLibResources.sortByName;
		}

		private void mnuSortByType_Click(object sender, EventArgs e)
		{
			objectsBrowserControl.Sort(ObjectsBrowserSort.ByType);
			tsbSort.Image = EditorLibResources.sortByType;
		}

		#endregion

    #region Type filtering

    public Type FilterType
    {
      get { return objectsBrowserControl.FilterType; }
      set { objectsBrowserControl.FilterType = value; }
    }

    #endregion

    private void tsbRefresh_Click( object sender, EventArgs e )
    {
      objectsBrowserControl.ReloadCurrentFolder();
    }
  }
}

using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using System.Windows.Forms;

namespace EditorLib.Menu
{
	public sealed class EditorMenu
	{
		private Dictionary<Guid, MenuItem> groups = new Dictionary<Guid, MenuItem>();
		private List<MenuItem> items = new List<MenuItem>();
		
		private MenuStrip menu = null;
		
		public void RecreateMenu()
		{
			if ( menu != null )
			{
				menu.Items.Clear();
				UpdateMenuItems( menu.Items, items );
			}
		}

    public void UpdateMenu()
    {
      if ( menu == null )
        return;

      UpdateMenuItemStates( items );
    }

    private void UpdateMenuItemStates( List<MenuItem> _items )
    {
      foreach ( MenuItem item in _items )
      {
        if ( null != item.Control )
        {
          item.Control.Enabled = item.Enabled;
          item.Control.Visible = item.Visible;

          if(item is MenuCommand)
          {
            item.Control.Image = ( item as MenuCommand ).Image;
            item.Control.Checked = ( item as MenuCommand ).IsChecked;  
          }          
        }

        if ( item.Items.Count > 0 )
          UpdateMenuItemStates( item.Items );
      }
    }

		private void UpdateMenuItems( ToolStripItemCollection _menuItems, List<MenuItem> _items )
		{
			bool openedSeparator = false;

      foreach(MenuItem item in _items)
      {
        if( !item.Visible )
          continue;

        if( string.IsNullOrEmpty( item.Name ) )
        {
          openedSeparator = true;
          if( _menuItems.Count > 0 )
          {
            _menuItems.Add( new ToolStripSeparator() );
          }
          UpdateMenuItems( _menuItems, item.Items );
        }
        else
        {
          if( openedSeparator )
          {
            _menuItems.Add( new ToolStripSeparator() );
            openedSeparator = false;
          }

          ToolStripMenuItem menuItem = new ToolStripMenuItem( item.Name );
          menuItem.Enabled = item.Enabled;

          MenuCommand command = item as MenuCommand;

          if( command != null )
          {
            menuItem.ShortcutKeys = command.WantedHotkey;
            //menuItem.Click += new EventHandler( command.Execute );
            menuItem.Tag = command;
            menuItem.Click += OnClick;
            menuItem.Image = command.Image;
            menuItem.Checked = command.IsChecked;
          }

          item.Control = menuItem;
          _menuItems.Add( menuItem );


          if( item.Items.Count > 0 )
          {
            UpdateMenuItems( menuItem.DropDownItems, item.Items );
          }
        }
      }
		}

		private void OnClick( object sender, EventArgs e )
		{
		  ToolStripMenuItem menuItem = sender as ToolStripMenuItem;

      if( menuItem != null )
      {
        MenuCommand command = menuItem.Tag as MenuCommand;

        if(command != null && application != null)
        {
          command.Execute( application );
        }
			}

			RecreateMenu();
		}
		
		public void AssignMenu( System.Windows.Forms.MenuStrip _menu )
		{
			menu = _menu;
			RecreateMenu();
		}
		
		private EditorLib.IEditorWinApplication application = null;
		public void Initialize( EditorLib.IEditorWinApplication _application )
		{
			application = _application;
		}
		
		private void InsertGroup( Guid groupGuid, string _groupName, List<MenuItem> _items, int _sortIndex )
		{
			int insertBeforeIndex = _items.Count;
			for ( int i = 0; i < _items.Count; i++ )
			{
				if ( (_items[i] as MenuItem).SortIndex > _sortIndex )
				{
					insertBeforeIndex = i;
					break;
				}
			}
			MenuItem newMenuItem = new MenuGroup( groupGuid, _sortIndex, _groupName );

			groups.Add( groupGuid, newMenuItem );
			if ( insertBeforeIndex < _items.Count )
			{
				_items.Insert( insertBeforeIndex, newMenuItem );
			}
			else
			{
				_items.Add( newMenuItem );
			}
		}

		public void ClearMenuGroup( Guid groupGuid )
		{
			MenuItem group = null;
			if ( !groups.TryGetValue( groupGuid, out group ) )
			{
				Log.TraceWarning( "Group \"{0}\" not found", groupGuid );
				return;
			}

			group.Items.Clear();
		}

		public void RegisterMenuGroup( Guid groupGuid, string _groupName, Guid parentGroup, int _sortIndex )
		{
			//Если Root Menu
			if ( parentGroup == Guid.Empty )
			{
				if ( _groupName == null || _groupName == string.Empty )
				{
					Log.TraceWarning( "No-named Group is not valid for root menu " + groupGuid.ToString() );
					return;
				}

				InsertGroup( groupGuid, _groupName, items, _sortIndex );
				return;
			}

			MenuItem parentItem;
			if ( !groups.TryGetValue( parentGroup, out parentItem ) )
			{
				Log.TraceWarning( " Menu don't know about group: " + parentGroup.ToString() );
				return;
			}
			InsertGroup( groupGuid, _groupName, (parentItem as MenuGroup).Items, _sortIndex );
		}
		
		private ShortcutsInterceptor shortcutsInterceptor = null;
		
		public void RegisterShortcutsInterceptor( ShortcutsInterceptor _shortcutsInterceptor )
		{
			shortcutsInterceptor = _shortcutsInterceptor;
		}
		
		public void RegisterMenuCommand( Guid parentGroup, int _sortIndex, IEditorCommand _command, Keys wantedHotkey )
		{
			if ( parentGroup == Guid.Empty )
			{
				Log.TraceWarning( "Commands are not valid for root menu " + _command.ToString() );
				return;
			}

			MenuItem parentItem;
			if ( !groups.TryGetValue( parentGroup, out parentItem ) )
			{
				Log.TraceWarning( "Menu don't know about group: " + parentGroup.ToString() );
				return;
			}

			InsertCommand( (parentItem as MenuGroup).Items, _sortIndex, _command, wantedHotkey );
		}

		private void InsertCommand( List<MenuItem> _items, int _sortIndex, IEditorCommand _command, Keys wantedHotkey )
		{
			int insertBeforeIndex = _items.Count;
			for ( int i = 0; i < _items.Count; i++ )
			{
				if ( (_items[i] as MenuItem).SortIndex > _sortIndex )
				{
					insertBeforeIndex = i;
					break;
				}
			}
			if ( shortcutsInterceptor  != null )
				shortcutsInterceptor.RegisterShortcutCommand( _command, wantedHotkey );
			MenuCommand newMenuItem = new MenuCommand( _sortIndex, _command, wantedHotkey );
			
			if ( insertBeforeIndex < _items.Count )
			{
				_items.Insert( insertBeforeIndex, newMenuItem );
			}
			else
			{
				_items.Add( newMenuItem );
			}
		}

		public bool ProcessCmdKey( ref Message msg, Keys keyData )
		{
			if ( menu != null )
				return menu.PreProcessMessage( ref msg );
			return false;
		}
	}
}

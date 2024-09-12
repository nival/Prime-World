using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace EditorLib.Menu
{
	public sealed class EditorToolbar
	{
		private EditorLib.IEditorWinApplication application = null;
		public void Initialize( EditorLib.IEditorWinApplication _application )
		{
			application = _application;
		}
		private Panel toolbarContainer = null;
		internal class Toolbar
		{
			public readonly string name = string.Empty;
			public Toolbar(string name)
			{
				this.name = name;
			}
			public void AddGroup( Guid guid, int sortIndex, EditorLib.IEditorWinApplication _application )
			{
				groups.Add( guid, new Group( sortIndex, _application ) );
				int insertFrom = 0;

				for ( int i = 0; i < indexedGroups.Count; i++ )
				{
					Group group = null;
					if ( groups.TryGetValue( guid, out group ) )
					{
						if ( group.sortIndex > sortIndex )
						{
							break;
						}
					}
					insertFrom = i;
				}
				indexedGroups.Insert( insertFrom, guid );
			}
			public bool UnregisterGroup( Guid guid )
			{
				Group group = null;
				if( groups.TryGetValue( guid, out group ) && group.HasCommands())
				{
					groups.Remove( guid );
					indexedGroups.Remove( guid );
					return true;
				}
				return false;
			}
			public void UnRegisterCommand( Guid parentGroup, IEditorCommand command )
			{
				if ( groups.ContainsKey( parentGroup ) )
				{
					ToolStripItem  item = groups[parentGroup].UnRegisterCommand( command );
					toolStrip.Items.Remove( item );
				}
			}
			public void AddCommand( Guid parentGroup, int sortIndex, IEditorCommand command )
			{
				if ( groups.ContainsKey( parentGroup ) )
				{
					groups[parentGroup].AddCommand( sortIndex, command );
				}
			}
			private ToolStrip toolStrip = new ToolStrip();
			public ToolStrip GetToolStrip()
			{
				toolStrip.Items.Clear();
				int i = 0;
				/*
				foreach( Group group in groups.Values)
				{
					ToolStripItem[] items = group.GetItems();
					if( items != null)
					{
						if( i++ > 0 )
						{
							group.group.Visible = group.Visible;
							toolStrip.Items.Add( group.group );
						}
						toolStrip.Items.AddRange( items );
					}
				}*/
				foreach(Guid guid in indexedGroups)
				{
					Group group = null;
					if( groups.TryGetValue(guid, out group))
					{
						ToolStripItem[] items = group.GetItems();
						if ( items != null )
						{
							if ( i++ > 0 )
							{
								group.group.Visible = group.Visible;
								toolStrip.Items.Add( group.group );
							}
							toolStrip.Items.AddRange( items );
						}
					}
				}
				return toolStrip;
			}
			//private List<KeyValuePair<Guid, Group>> groups = new List<KeyValuePair<Guid, Group>>();
			List<Guid> indexedGroups = new List<Guid>();
			private Dictionary<Guid, Group> groups = new Dictionary<Guid, Group>();
		}
		internal class Group
		{
			public readonly ToolStripSeparator group = new ToolStripSeparator();
			private EditorLib.IEditorWinApplication application = null;
			public Group( int sortIndex, EditorLib.IEditorWinApplication application )
			{
				this.sortIndex = sortIndex;
				this.application = application;
			}
			public bool Visible 
			{
				get 
				{
					foreach ( KeyValuePair<int, IEditorCommand> command in commands )
					{
						if ( command.Value.Visible )
						{
							return true;
						}
					}
				return false;
				}
			}

			public ToolStripItem UnRegisterCommand( IEditorCommand _command )
			{
				ToolStripItem item = null;
				for(int i = 0; i <commands.Count; i++ )
				{
					if ( commands[i].Value == _command )
					{
						commands.Remove( commands[i] );
						i--;
						if ( itemsVsCommands.ContainsKey( _command ) )
						{
							item = itemsVsCommands[_command];
							itemsVsCommands.Remove( _command );
						}
						break;
					}
				}
				return item;
			}

			public void AddCommand( int sortIndex, IEditorCommand command )
			{
        int insertAt = commands.Count;
				
				for ( int i = 0; i < commands.Count; i++ )
				{
					if ( commands[i].Key > sortIndex )
					{
            insertAt = i;
            break;
					}
				}
				commands.Insert( insertAt, new KeyValuePair<int, IEditorCommand>( sortIndex, command ) );
				itemsVsCommands.Add( command, null );
			}

			private Dictionary<IEditorCommand, ToolStripItem> itemsVsCommands = new Dictionary<IEditorCommand, ToolStripItem>();
			public ToolStripItem[] GetItems()
			{
				List<ToolStripItem> list= new List<ToolStripItem>();
				foreach ( KeyValuePair<int, IEditorCommand> command in commands )
				{
					ToolStripItem item = new ToolStripButton( command.Value.Image );
					item.Click += new EventHandler( OnClick );
					item.Tag = command.Value;
				  item.Text = command.Value.Name;
					item.ToolTipText = command.Value.TooltipText;
					item.Visible = command.Value.Visible;
          item.Enabled = command.Value.Enabled;
					list.Add( item );
					itemsVsCommands[command.Value] = item;
				}
				return list.Count > 0 ? list.ToArray() : null;
			}
			public readonly int sortIndex = 0;
			private List<KeyValuePair<int, IEditorCommand>> commands = new List<KeyValuePair<int, IEditorCommand>>();
			public bool HasCommands()
			{
				return commands.Count > 0;
			}
			private void OnClick( object sender, EventArgs e )
			{
				if ( sender is ToolStripItem && (sender as ToolStripItem).Tag is IEditorCommand && application != null )
				{
					((sender as ToolStripItem).Tag as IEditorCommand).Execute( application );
				}
			}
		}
	
	/*	public void AssignToolbarContainer( ToolStripContainer _toolbarContainer )
		{
			toolbarContainer = _toolbarContainer;
			UpdateToolbars();
		}*/
		public void AssignToolbarContainer( Panel _toolbarContainer )
		{
			toolbarContainer = _toolbarContainer;
			RecreateToolbars();
		}
		private Dictionary<Guid, Toolbar> toolbars = new Dictionary<Guid, Toolbar>();
		public void RegisterToolbar( Guid guid, string name )
		{
			if ( !toolbars.ContainsKey( guid ) )
			{
				toolbars.Add( guid, new Toolbar(name) );
			}
		}
		
		public void RegisterToolbarGroup( Guid parentToolbar, Guid guid, int sortIndex )
		{
			if ( toolbars.ContainsKey( parentToolbar ) )
			{
				toolbars[parentToolbar].AddGroup( guid, sortIndex, application );
			}
		}
		public void RegisterToolbarCommand( Guid parentGroup, int sortIndex, IEditorCommand command )
		{
			foreach ( KeyValuePair<Guid, Toolbar> toolbar in toolbars )
			{
				toolbar.Value.AddCommand( parentGroup, sortIndex, command );
			}
		}
		public void UnRegisterToolbar( Guid guid )
		{
			if ( toolbars.ContainsKey( guid ) )
			{
				Toolbar toolbar = null;
				if ( toolbars.TryGetValue( guid, out toolbar ) )
				{
					Control controlForDelete = null;
					foreach ( Control control in toolbarContainer.Controls )
					{
						if ( control.Tag is Toolbar && (control.Tag as Toolbar) == toolbar )
						{
							controlForDelete = control;
							break;
						}
					}
					if ( controlForDelete != null)
						toolbarContainer.Controls.Remove( controlForDelete );
				}
				toolbars.Remove( guid );
			}
		}
		public void UnRegisterToolbarGroup( Guid parentToolbar, Guid guid )
		{
			if ( toolbars.ContainsKey( parentToolbar ) )
			{
				toolbars[parentToolbar].UnregisterGroup( guid );
			}
		}
		public void UnRegisterToolbarCommand( Guid parentGroup, IEditorCommand command )
		{
			foreach ( KeyValuePair<Guid, Toolbar> toolbar in toolbars )
			{
				toolbar.Value.UnRegisterCommand( parentGroup, command );
				
			}
		}
		public void RecreateToolbars()
		{
			toolbarContainer.Controls.Clear();
			int dX = 0;
			foreach ( KeyValuePair<Guid, Toolbar> toolbar in toolbars )
			{
				Control control = toolbar.Value.GetToolStrip();
				control.Tag = toolbar;
				control.Dock = DockStyle.None;
				
				toolbarContainer.Controls.Add( control );
				control.SetBounds( control.Location.X + dX, control.Location.Y, control.Size.Width, control.Size.Height );
				dX += control.Size.Width;
			}
		}
    public void UpdateToolbars()
    {
      foreach ( Control toolbarCtl in toolbarContainer.Controls )
      {
        if ( !( toolbarCtl is ToolStrip ) )
          continue;

        ToolStrip toolbar = toolbarCtl as ToolStrip;
        foreach ( var item in toolbar.Items )
        {
          if ( !( item is ToolStripButton ) )
            continue;

          ToolStripButton btn = item as ToolStripButton;
          if ( btn.Tag == null || !( btn.Tag is IEditorCommand ) )
            continue;

          IEditorCommand cmd = btn.Tag as IEditorCommand;
          btn.Text = cmd.Name;
          btn.ToolTipText = cmd.TooltipText;
          btn.Visible = cmd.Visible;
          btn.Enabled = cmd.Enabled;
        }
      }
    }
	}
}

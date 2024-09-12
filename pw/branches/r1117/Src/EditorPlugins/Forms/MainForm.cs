using System;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Forms;
using EditorLib;
using EditorLib.OutputPanel;
using EditorPlugins.Binds;
using EditorLib.Menu;
using EditorPlugins.Commands;
using EditorLib.ObjectsBrowser;
using EditorLib.Panels;
using EditorLib.PropertiesEditor;
using EditorPlugins.Scene;
using EditorLib.ToolBox;
using EditorPlugins.Wizards;
using libdb.DB;
using WeifenLuo.WinFormsUI.Docking;
//using EditorPlugins.Templates;

namespace EditorPlugins.Forms
{
	public partial class MainForm : Form
	{
		#region Private static members.

		public readonly static Guid UndoRedoMenuGroupGuid = new Guid( "e19ea252-380c-4690-9b33-b991e5291198" );
		public readonly static Guid OtherPanelsMenuGroupGuid = new Guid( "65206698-4720-49a8-8082-5a16c9e4b313" );
		public readonly static Guid ExitMenuGroupGuid = new Guid( "4700ce20-a16c-426d-be12-b2a48ddc2ce8" );
		public readonly static Guid CommonPanelsMenuGroup = new Guid( "bf1a704a-5f38-4ac3-b23a-f61014c9540f" );
		public readonly static Guid ViewersPanelsMenuGroup = new Guid( "0791c8dc-fbf0-4a20-ab26-3179e685fe56" );
		public readonly static Guid EditorsPanelsMenuGroup = new Guid( "850D4F89-A68C-45a3-95FE-E6F92CA690F3" );
		public readonly static Guid LayoutEditorPanelsMenuGroup = new Guid( "7d183bfd-0d30-4401-acf5-dc63f65f339b" );
		public readonly static Guid ReloadMenuGroup = new Guid( "24774745-A29D-48d9-8AFD-6B17F025FB6A" );

    private static EventWaitHandle cancelCloseEvent = new EventWaitHandle(false, EventResetMode.AutoReset, "PFEditorCancelCloseEvent");

		#endregion

		#region Private members.

		private readonly EditorWinApplication editorApplication;

		private bool statusPanelProgressBarKnownDuration = false;
		private string label;

		#endregion

		#region Initialization.

    public MainForm() : this( null ) { }

		public MainForm( EditorWinApplication editorApplication )
		{
			this.editorApplication = editorApplication;
			InitializeComponent();

      editorApplication.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.ToolsMenuGroupGuid, 19, new MayaConfigurationCommand(), Keys.None  );
      editorApplication.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.ToolsMenuGroupGuid, 20, new MayaBindsCommand( editorApplication ), Keys.Control | Keys.Shift | Keys.U );
      editorApplication.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.ToolsMenuGroupGuid, 21, new CasualBindsCommand( editorApplication ), Keys.Control | Keys.Shift | Keys.I );
      editorApplication.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.ToolsMenuGroupGuid, 23, new Scene.PostFXCommand( editorApplication ), Keys.None );
			editorApplication.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.ToolsMenuGroupGuid, 24, new Scene.CollisionSelectionCommand( editorApplication ), Keys.None );
		}

		#endregion

		#region Protected properties.

		protected EditorWinApplication Application
		{
			get { return editorApplication; }
		}

		#endregion

		#region Methods and properties to override.

		protected virtual Type[] AdditionalCommonPanelTypes { get { return Type.EmptyTypes; } }
    protected virtual Type[] ViewerPanelTypes { get { return Type.EmptyTypes; } }
    protected virtual Type[] EditorPanelTypes { get { return Type.EmptyTypes; } }

    protected virtual IEditorCommand OpenCommand { get { return null; } }

		#endregion

		#region Event handlers.

		void OnSetStatusLabelEvent( string value )
		{
      if ( statusBarProgressBar.Visible )
        label = value;
      else
        Invoke((MethodInvoker)delegate { statusBarLabel.Text = value; });    
		}

		void OnSetStatusPanelEvent( Control panel )
		{
			if ( panel == null )
			{
				statusBarPanel.Visible = false;
				statusBarPanel.Controls.Clear();
			}
			else
			{
				statusBarPanel.Visible = true;
				statusBarPanel.Controls.Add( panel );
				statusBarPanel.Width = panel.Width;
				panel.Dock = DockStyle.Fill;
			}
		}

		void OnStartOperationEvent( bool knownDuration, bool blockInterface )
		{
			Invoke( new StartProgressCallBack( StartProgress ), knownDuration, blockInterface );
		}

		void OnProgressOperationEvent( string messagge, int progress )
		{
			Invoke( new ProgressCallBack( Progress ), messagge, progress );
		}

		void OperationExecutor_FinishOperationEvent( bool success )
		{
			Invoke( new EndProgressCallBack( EndProgress ), success );
		}

		public delegate void StartProgressCallBack( bool knownDuration, bool blockInterface );
		void StartProgress( bool knownDuration, bool blockInterface )
		{
			label = statusBarLabel.Text;
			if ( blockInterface )
				Enabled = false;

			statusPanelProgressBarKnownDuration = knownDuration;
			statusBarProgressBar.Visible = true;
		}

		public delegate void ProgressCallBack( string messagge, int progress );
		void Progress( string messagge, int progress )
		{
			statusBarLabel.Text = messagge;
			if ( statusPanelProgressBarKnownDuration )
			{
				statusBarProgressBar.Value = progress;
			}
		}

		public delegate void EndProgressCallBack( bool success );
		void EndProgress( bool success )
		{
			statusBarLabel.Text = label;
			statusBarProgressBar.Value = 0;
			Enabled = true;
			statusBarProgressBar.Visible = false;
		}

		private void OnLoad( object sender, EventArgs e )
		{
			editorApplication.MainMenu.AssignMenu( mainMenuStrip );
			InitializeMenu();

			InitializeViewMenu();
			editorApplication.MainMenu.RecreateMenu();
			editorApplication.Toolbar.AssignToolbarContainer( toolbars );
			InitializeToolbar();
			editorApplication.Toolbar.RecreateToolbars();
			InitializeStatusPanel();
			editorApplication.Panels.UpdateSingletonPanelEvent += new PanelsManager.UpdateSingletonPanelEventHandler( OnUpdateSingletonPanel );

      editorApplication.Settings.Get<MainFormConfig>().ApplyToForm( this, dockPanel, GetContentFromPersistString );

			editorApplication.Panels.SetDockPanel( dockPanel );

      System.Windows.Forms.Application.ApplicationExit += new EventHandler( OnApplicationExit );
		}

    private void OnApplicationExit( object sender, EventArgs e )
    {
      editorApplication.Terminate();
    }

		private void OnExitClick( object sender, EventArgs e )
		{
			Close();
		}

		private void OnViewSingletonPanelClick( object sender, EventArgs e )
		{
			ToolStripItem item = sender as ToolStripItem;
			if ( item == null )
				return;

			EditorPanel panel = item.Tag as EditorPanel;
			if ( panel == null )
				return;

			if ( panel.DockState == DockState.Unknown || panel.DockState == DockState.Hidden )
				editorApplication.Panels.ShowSingletonPanel( panel );
			else
				editorApplication.Panels.HideSingletonPanel( panel );
		}

		private void OnUpdateSingletonPanel( EditorPanel panel, bool show )
		{
			editorApplication.MainMenu.RecreateMenu();
		}

		private void OnUndoClick( object sender, EventArgs e )
		{
			editorApplication.UndoRedo.Undo();
		}

		private void onRedoClick( object sender, EventArgs e )
		{
			editorApplication.UndoRedo.Redo();
		}

		private void OnFormClosing( object sender, FormClosingEventArgs e )
		{
      e.Cancel = false;

			if ( DataBase.IsModified )
			{
				DialogResult rez = MessageBox.Show("Some resources are modified. Do you want to save chages before exit?", 
          "Database Changed", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question );

        if (rez == DialogResult.Yes)
        {
          new SaveEditorCommand().Execute(editorApplication);
        }
        else if (rez == DialogResult.Cancel)
        {
          cancelCloseEvent.Set();
          e.Cancel = true;
        }
			}
    }

    protected override void OnClosed(EventArgs e)
    {
			editorApplication.Settings.Get<MainFormConfig>().GetFromForm( this, dockPanel );
      base.OnClosed(e);
    }

		#endregion

		#region Private helper methods.

		private void InitializeToolbar()
		{
      EditorToolbar toolbar = editorApplication.Toolbar;

      toolbar.RegisterToolbar( ToolbarGuids.DefaultToolbarGuid, "Default Toolbar" );
      toolbar.RegisterToolbarGroup( ToolbarGuids.DefaultToolbarGuid, CommandGroups.FileMenuGroupGuid, 1 );
      toolbar.RegisterToolbarCommand( CommandGroups.FileMenuGroupGuid, 1, new SaveEditorCommand() );
    }

		private void AddShowPanelCommand( Guid guid, Type panelType, Dictionary<EditorPanel, bool> panels, int sortIndex )
		{
			AddShowPanelCommand( guid, editorApplication.Panels.GetSingletonPanel( panelType ), panels, sortIndex );
		}

		private void AddShowPanelCommand( Guid guid, EditorPanel panel, Dictionary<EditorPanel, bool> panels, int sortIndex )
		{
			if ( panel != null )
			{
				editorApplication.MainMenu.RegisterMenuCommand( guid, sortIndex, new ShowPanelCommand( panel ), Keys.None );
				if ( panels != null )
					panels.Remove( panel );
			}
		}

		private static int CompareEditorPanels( EditorPanel panelA, EditorPanel panelB )
		{
			return string.Compare( panelA.TabText, panelB.TabText );
		}

		private void InitializeViewMenu()
		{
			Dictionary<EditorPanel, bool> panels = new Dictionary<EditorPanel, bool>();
			foreach ( EditorPanel panel in editorApplication.Panels.SingletonPanels )
				panels.Add( panel, false );

			Operation<int, Guid, IList<Type>> addShowPanelCommands =
				( groupIndex, groupId, panelTypes ) =>
					{
						editorApplication.MainMenu.RegisterMenuGroup( groupId, null, EditorLib.Menu.CommandGroups.ViewMenuGroupGuid, groupIndex );
						for ( int index = 0; index < panelTypes.Count; ++index )
						{
							AddShowPanelCommand( groupId, panelTypes[index], panels, index + 1 );
						}
					};

			var commonPanelTypes = new Type[]
				{
					typeof( ObjectsBrowserPanel ),
					typeof( PropertiesEditorPanel ),
					typeof( OutputPanel ),
					typeof( ToolBoxPanel )
				};

			addShowPanelCommands( 1, CommonPanelsMenuGroup, CollectionUtils.Concat( commonPanelTypes, AdditionalCommonPanelTypes ) );
			addShowPanelCommands( 2, ViewersPanelsMenuGroup, ViewerPanelTypes );
			addShowPanelCommands( 3, EditorsPanelsMenuGroup, EditorPanelTypes );

			if ( panels.Count > 0 )
			{
				if ( panels.Count > 3 )
					editorApplication.MainMenu.RegisterMenuGroup( OtherPanelsMenuGroupGuid, "Other Panels", EditorLib.Menu.CommandGroups.ViewMenuGroupGuid, int.MaxValue );
				else
					editorApplication.MainMenu.RegisterMenuGroup( OtherPanelsMenuGroupGuid, null, EditorLib.Menu.CommandGroups.ViewMenuGroupGuid, int.MaxValue );

				List<EditorPanel> otherPanels = new List<EditorPanel>();
				foreach ( EditorPanel otherPanel in panels.Keys )
					otherPanels.Add( otherPanel );

				otherPanels.Sort( CompareEditorPanels );
				int i = 1;
				foreach ( EditorPanel otherPanel in otherPanels )
				{
					AddShowPanelCommand( OtherPanelsMenuGroupGuid, otherPanel, null, i++ );
				}
			}
		}

		private void InitializeMenu()
		{
			editorApplication.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.FileMenuGroupGuid, 1, new SaveEditorCommand(), Keys.Control | Keys.S );
			//editorApplication.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.FileMenuGroupGuid, 2, new SaveAndCommitCommand(), Keys.Control | Keys.Alt | Keys.S );
			editorApplication.MainMenu.RegisterMenuGroup( ExitMenuGroupGuid, null, EditorLib.Menu.CommandGroups.FileMenuGroupGuid, int.MaxValue );
			editorApplication.MainMenu.RegisterMenuCommand( ExitMenuGroupGuid, int.MaxValue, new ExitEditorCommand( this ), Keys.Alt | Keys.F4 );

			editorApplication.MainMenu.RegisterMenuGroup( UndoRedoMenuGroupGuid, null, EditorLib.Menu.CommandGroups.EditMenuGroupGuid, 1 );
			editorApplication.MainMenu.RegisterMenuCommand( UndoRedoMenuGroupGuid, 1, new UndoEditorCommand(), Keys.Control | Keys.Z );
			editorApplication.MainMenu.RegisterMenuCommand( UndoRedoMenuGroupGuid, 2, new RedoEditorCommand(), Keys.Control | Keys.Y );

			editorApplication.MainMenu.RegisterMenuGroup( ReloadMenuGroup, null, EditorLib.Menu.CommandGroups.ToolsMenuGroupGuid, int.MaxValue - 10000 );
			editorApplication.MainMenu.RegisterMenuCommand( ReloadMenuGroup, int.MaxValue - 1, new ReloadShadersCommand(), Keys.Control | Keys.Shift | Keys.S );
			editorApplication.MainMenu.RegisterMenuCommand( ReloadMenuGroup, int.MaxValue - 2, new ReloadGeometryCommand(), Keys.Control | Keys.Shift | Keys.G );
			editorApplication.MainMenu.RegisterMenuCommand( ReloadMenuGroup, int.MaxValue - 3, new ReloadPFXCommand(), Keys.Control | Keys.Shift | Keys.P );	

			//editorApplication.MainMenu.RegisterMenuCommand( EditorLib.Menu.CommandGroups.ToolsMenuGroupGuid, int.MaxValue - 1000, new ResetUserConfigurationCommand(), Keys.None );
		}

		private void InitializeStatusPanel()
		{
			editorApplication.OperationExecutor.StartOperationEvent += new EditorLib.Operations.Executor.StartOperationEventHandler( OnStartOperationEvent );
			editorApplication.OperationExecutor.ProgressOperationEvent += new EditorLib.Operations.Executor.ProgressOperationEventHandler( OnProgressOperationEvent );
			editorApplication.OperationExecutor.FinishOperationEvent += new EditorLib.Operations.Executor.FinishOperationEventHandler( OperationExecutor_FinishOperationEvent );
			editorApplication.SetStatusPanelEvent += OnSetStatusPanelEvent;
			editorApplication.SetStatusLabelEvent += OnSetStatusLabelEvent;
		}

		private IDockContent GetContentFromPersistString( string persistString )
		{
			foreach ( EditorPanel panel in editorApplication.Panels.SingletonPanels )
			{
				if ( persistString == panel.GetType().ToString() )
					return panel;
			}

			return null;
		}

		#endregion

    private void OnScriptTimerTick( object sender, EventArgs e )
    {
      Application.Scripts.Step();
    }
  }
}

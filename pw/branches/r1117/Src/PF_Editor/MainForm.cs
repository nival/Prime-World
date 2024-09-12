using System;
using System.Reflection;
using System.Windows.Forms;
using EditorLib.Menu;
using EditorLib.Wizards;
using EditorLib.Wizards.TableDataEditing;
using EditorPlugins.Commands.Help;
using EditorPlugins.Editors.AnimatedCurves;
using EditorPlugins.Scene;
using EditorPlugins.Scene.Editors.Drawing.TerrainLayers;
using EditorPlugins.Scene.Viewers;
using EditorPlugins.Templates;
using EditorPlugins.Wizards;
using libdb.DB;
using PF_Editor.Map.Wizard;
using PF_EditorNative;
using Tools.MayaExeInteraction;

namespace PF_Editor
{
  internal partial class MainForm : EditorPlugins.Forms.MainForm
  {
	  public readonly static Guid TemplateMenuGroupGuid = new Guid( "a87b2934-ff05-495b-9db2-075dcc513803" );
	  private string[] arguments = null;

	  public MainForm( EditorApplication editorApplication, string[] arguments )
	    : base( editorApplication )
	  {
	    InitializeComponent();
      Text = editorApplication.ApplicationTitle + editorApplication.ApplicationVersion;

	    this.arguments = arguments;
	  }

	  protected override Type[] ViewerPanelTypes
	  {
	    get
	    {
		  return new Type[]
					  {
						  typeof( SkinsSelectionPanel ),
						  typeof( DebugVarsPanel )
					  };
	    }
	  }

	  protected override Type[] EditorPanelTypes
	  {
	    get
	    {
		  return new Type[]
					  {
						  typeof( TerrainLayersEditorPanel ),
              typeof( SceneHierarchyPanel ),
              typeof( AnimatedCurvesPanel ),
              typeof( EditorPlugins.Editors.AnimGraph.AnimGraphPanel ),
							typeof( TableDataPanel )
					  };
	    }
	  }

	  protected override void OnLoad( EventArgs e )
	  {
	    base.OnLoad( e );

	    Application.MainMenu.RegisterMenuCommand( CommandGroups.FileMenuGroupGuid, 0, new ImportWizardMenuItem(), Keys.None );        
        Application.MainMenu.RegisterMenuGroup( WizardsManager.ImportRecentMenuGroupGuid, "Import Recent", CommandGroups.FileMenuGroupGuid, 0 );
        WizardsManager.UpdateImportRecentMenu( Application.MainMenu, Application.Application.Settings );

	    Application.MainMenu.RegisterMenuGroup( TemplateMenuGroupGuid, string.Empty,CommandGroups.FileMenuGroupGuid, 0 );
		Application.MainMenu.RegisterMenuCommand( TemplateMenuGroupGuid, 0, new NewTemplateMenuItem(), Keys.None );
	    Application.MainMenu.RegisterMenuGroup( NewTemplateMenuItem.NewObjectFromTemplateMenuGroupGuid,"Create Object From Template", TemplateMenuGroupGuid, 1 );
	    TemplateUtils.UpdateTemplatesMenu( Application.MainMenu );

        Application.MainMenu.RegisterMenuCommand( CommandGroups.FileMenuGroupGuid, 0, new CreateMapCommand(), Keys.None );        	
        Application.MainMenu.RegisterMenuCommand( CommandGroups.FileMenuGroupGuid, 2, new EditorPlugins.Committer.DualCommitCommand(), Keys.None );
        Application.MainMenu.RegisterMenuCommand( CommandGroups.FileMenuGroupGuid, 3, new ExportToSocial.ExportToSocialCommand(), Keys.None );
        Application.MainMenu.RegisterMenuCommand( CommandGroups.FileMenuGroupGuid, 4, new ExportToSocial.ExportToSocialAsCommand(), Keys.None );
        Application.MainMenu.RegisterMenuCommand( CommandGroups.FileMenuGroupGuid, 5, new ExportToSocial.ExportToSocialServerAsCommand(), Keys.None);	

        Application.MainMenu.RegisterMenuCommand( CommandGroups.ToolsMenuGroupGuid, 23, new EditorPlugins.Importer.AtlasCommand.CreateAtlasCommand(), Keys.None );
        Application.MainMenu.RegisterMenuCommand( CommandGroups.ToolsMenuGroupGuid, 24, new EditorPlugins.MipMapCommand.MipMapCommand(), Keys.Control | Keys.M );
        Application.MainMenu.RegisterMenuCommand( CommandGroups.ToolsMenuGroupGuid, 25, new EditorPlugins.SymmetricalCommand.SymmetricalCommand(), Keys.None );
           
	  	Application.MainMenu.RegisterMenuCommand( CommandGroups.HelpMenuGroupGuid, 0, new HotkeysMenuCommand(), Keys.None );

        Application.MainMenu.RecreateMenu();

        EditorToolbar toolbar = Application.Toolbar;
        toolbar.RegisterToolbar( ToolbarGuids.ArtistToolbarGuid, "Artists Toolbar" );
        toolbar.RegisterToolbarGroup( ToolbarGuids.ArtistToolbarGuid, CommandGroups.ToolsMenuGroupGuid, 1 );
        toolbar.RegisterToolbarCommand( CommandGroups.ToolsMenuGroupGuid, 1, new ImportWizardMenuItem() );
        toolbar.RegisterToolbarCommand( CommandGroups.ToolsMenuGroupGuid, 2, new EditorPlugins.Committer.DualCommitCommand() );        

        toolbar.RegisterToolbar( ToolbarGuids.UndoRedoToolbarGuid, "UndoRedo Toolbar" );
        toolbar.RegisterToolbarGroup( ToolbarGuids.UndoRedoToolbarGuid, CommandGroups.EditMenuGroupGuid, 2 );
        toolbar.RegisterToolbarCommand( CommandGroups.EditMenuGroupGuid, 1, new EditorPlugins.Commands.UndoEditorCommand() );
        toolbar.RegisterToolbarCommand( CommandGroups.EditMenuGroupGuid, 2, new EditorPlugins.Commands.BrowseUndoRedoCommand() );
        toolbar.RegisterToolbarCommand( CommandGroups.EditMenuGroupGuid, 3, new EditorPlugins.Commands.RedoEditorCommand() );
        toolbar.RegisterToolbarCommand( CommandGroups.EditMenuGroupGuid, 4, new ExportToSocial.ExportToSocialCommand() );
        toolbar.RegisterToolbarCommand( CommandGroups.EditMenuGroupGuid, 5, new ExportToSocial.ExportToSocialAsCommand() );
        toolbar.RegisterToolbarCommand( CommandGroups.EditMenuGroupGuid, 6, new ExportToSocial.ExportToSocialServerAsCommand() );
        toolbar.RecreateToolbars();

			var conf = Application.Settings.Get<MayaProcessConfig>();
	  	MayaOperationsUtility.PathToMaya = conf.PathToMaya;

		  EditorLib.IO.SVNFileSystem.BindSVNAuthDialogToForm( this );

	    EffectsPool.Initialize();

	    if ( arguments != null && arguments.Length > 0 )
	    {
        int result;
		    Application.Commands.TryExecute( Application, arguments, out result );
	    }

	    DataBase.ChangeDBResourceEvent += OnDBResourceChanged;
	  }

    private void OnDBResourceChanged( DBID _dbid )
    {
      Invoke( (MethodInvoker)delegate
      {
        Application.StatusLabel = string.Format( "Last modified: \"{0}\"", _dbid.FileName );
        Application.Toolbar.UpdateToolbars();
        Application.MainMenu.UpdateMenu();
      } ); 
    }

    //to avoid memory leaks (http://forum.memprofiler.com/viewtopic.php?t=1160)
    protected override void OnMdiChildActivate( EventArgs e )
    {
      base.OnMdiChildActivate( e );
      try
      {
        typeof( Form ).InvokeMember( "FormerlyActiveMdiChild",
          BindingFlags.Instance | BindingFlags.SetProperty |
          BindingFlags.NonPublic, null,
          this, new object[] { null } );
      }
      catch ( Exception )
      {
        // Something went wrong. Maybe we don't have enough permissions
        // to perform this or the "FormerlyActiveMdiChild" property 
        // no longer exists.
      }
    }

    protected override void OnClosed( EventArgs e )
    {
      base.OnClosed( e );

      DataBase.ChangeDBResourceEvent -= OnDBResourceChanged;

      MayaOperationsUtility.Terminate();
      EffectsPool.Release();
    }
  }

}

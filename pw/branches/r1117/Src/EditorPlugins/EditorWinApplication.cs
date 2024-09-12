using System;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using EditorLib.Binds;
using EditorLib.ContextMenus;
using EditorLib.Menu;
using EditorLib.ObjectsBrowser;
using EditorLib.Operations;
using EditorLib.Panels;
using libdb.DB;
using libdb.Diagnostics;
using EditorLib;
using EditorLib.OutputPanel;

namespace EditorPlugins
{
	public abstract class EditorWinApplication : EditorNativeApplication, IEditorWinApplication
	{
		private SingleThreadExecutor operationExecutor = new SingleThreadExecutor();
		private PanelsManager panels = null;
		private ItemContextMenu contextMenu = null;
		private EditorMenu mainMenu = new EditorMenu();
		private EditorToolbar toolbar = new EditorToolbar();
		private ShortcutsInterceptor shortcutsInterceptor = null;
    private BindsManager bindsManager;
    
    protected EditorWinApplication()
		{
			panels = new PanelsManager( this );
			contextMenu = new ItemContextMenu( this );
			shortcutsInterceptor = new ShortcutsInterceptor( this );
			OutputPanel.InitializeTraceListener();
			ObjectsBrowserControl.SetApplication( this );
      bindsManager = new BindsManager( this );
		}

		protected override void RegisterExtensions()
		{
			// toolbar and main menu should be initialized before register extensions
			toolbar.Initialize( this );
			mainMenu.Initialize( this );
			System.Windows.Forms.Application.AddMessageFilter( shortcutsInterceptor );
			mainMenu.RegisterShortcutsInterceptor( shortcutsInterceptor );
      Extensions.RegisterAssemblyWithIcons( IconAssembly );
      Extensions.RegisterExtensions( this );
    }

    private void InitMenuFromExtensions(System.Collections.Generic.IEnumerable<string> extensionAssembliesFiles)
    {
      string entryAssemblyPath = Path.GetDirectoryName( Assembly.GetEntryAssembly().Location );
      foreach (string extensionAssemblyFile in extensionAssembliesFiles)
      {
        string fullExtensionAssemblyFile = Path.Combine(entryAssemblyPath, extensionAssemblyFile);
        if (!File.Exists(fullExtensionAssemblyFile))
          fullExtensionAssemblyFile = Path.GetFullPath(extensionAssemblyFile);
        if (!File.Exists(fullExtensionAssemblyFile))
        {
          continue;
        }
        //load IMenuUpdater from plug-ins library
        Assembly assembly = null;
        try
        {
          assembly = Assembly.LoadFile(fullExtensionAssemblyFile);
          if (assembly == null)
            continue;
        }
        catch (ReflectionTypeLoadException e)
        {
          var info = e.LoaderExceptions;
        }
        Type[] assTypes = assembly.GetTypes();
        foreach (Type AssemblyType in assTypes)
        {
          if (AssemblyType.IsInterface == false)
          {
            Type[] Interfaces = AssemblyType.GetInterfaces();
            if (Interfaces.Length > 0)
            {
              foreach (Type ItfType in Interfaces)
              {
                if (ItfType.Name == "IMenuUpdater")
                {
                  MethodInfo myMemberInfo = ItfType.GetMethod("UpdateMenu", BindingFlags.Public | BindingFlags.Instance, null,
                  CallingConventions.Any, new Type[] { typeof(IEditorWinApplication) }, null);

                  ConstructorInfo constInfo = AssemblyType.GetConstructor(BindingFlags.Instance | BindingFlags.Public, null, Type.EmptyTypes, null);
                  if(constInfo != null)
                  {
                    Object pObj = null;
                    try
                    {
                      pObj = constInfo.Invoke(null);
                    }
                    catch (Exception e)
                    {
                      Log.TraceWarning("Cannot create class \"{0}\". Exception {1}: {2}", AssemblyType.Name, e.ToString(), e.Message);
                    }
                    if(pObj != null)
                    {
                      myMemberInfo.Invoke(pObj, new Object[] { this });
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

		protected override bool InitializeApplication( IOperationContext context )
		{
      if ( !base.InitializeApplication( context ) )
        return false;

			context.Progress( "Prepare main menu ..." );
			MainMenu.RegisterMenuGroup( CommandGroups.FileMenuGroupGuid, "File", Guid.Empty, 1 );
			MainMenu.RegisterMenuGroup( CommandGroups.EditMenuGroupGuid, "Edit", Guid.Empty, 2 );
			MainMenu.RegisterMenuGroup( CommandGroups.ViewMenuGroupGuid, "View", Guid.Empty, 3 );
			MainMenu.RegisterMenuGroup( CommandGroups.ToolsMenuGroupGuid, "Tools", Guid.Empty, 4 );
      MainMenu.RegisterMenuGroup( CommandGroups.HelpMenuGroupGuid, "Help", Guid.Empty, int.MaxValue );
      
			//FileSystem.UpdateMenu( this );
			SourceFileSystem.UpdateMenu( this );

			context.Progress( "Prepare editor panels ..." );
			if ( !Panels.Initialize( context ) )
				return false;

      InitMenuFromExtensions(PluginsFileNames);
			return true;
		}

		protected override void TerminateApplication()
		{
			operationExecutor.Stop();
			Panels.Terminate();
			EditorNative.EditorRender.Release();
			EditorNative.EditorSound.Release();
      base.TerminateApplication();
		}

		public IEditorCommonApplication Application { get { return this; } }

		public override Executor OperationExecutor { get { return operationExecutor; } }

		public PanelsManager Panels { get { return panels; } }
    public BindsManager BindsManager { get { return bindsManager; } }
		public ItemContextMenu ContextMenu { get { return contextMenu; } }
		public EditorMenu MainMenu { get { return mainMenu; } }
		public EditorToolbar Toolbar { get { return toolbar; } }

		public string StatusLabel { set { if ( SetStatusLabelEvent != null ) SetStatusLabelEvent( value ); } }
		public Control StatusPanel { set { if ( SetStatusPanelEvent != null ) SetStatusPanelEvent( value ); } }

		public delegate void SetStatusLabelEventHandler( string text );
		public event SetStatusLabelEventHandler SetStatusLabelEvent = null;

		public delegate void SetStatusPanelEventHandler( Control panel );
		public event SetStatusPanelEventHandler SetStatusPanelEvent = null;

		public abstract string ApplicationTitle { get; }
		public abstract string IconAssembly { get; }
  }
}

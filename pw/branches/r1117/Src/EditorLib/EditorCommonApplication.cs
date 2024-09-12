using System.Windows.Forms;
using EditorLib.Extensions;
using EditorLib.IO;
using EditorLib.Operations;
using EditorLib.Plugin;
using EditorLib.Settings;
using libdb.DB;
using libdb.Diagnostics;
using libdb.UndoRedo;
using EditorLib.Scripts;

namespace EditorLib
{
	public abstract class EditorCommonApplication : IEditorCommonApplication
	{
		private RootFileSystem rootFileSystem = null;
		private SourceFileSystem sourceFileSystem = null;
		private SettingsManager settings = null;
		private UndoRedoManager undoRedo = new libdb.UndoRedo.UndoRedoManager();
		private ExtensionsManager extensions = new ExtensionsManager();
    private ConsoleCommandsManager commands = new ConsoleCommandsManager();
    private ScriptMachine scripts = null;

    private static EditorCommonApplication singletonApplication = null;

    public static IEditorCommonApplication ApplicationSingleton { get { return singletonApplication; } }

		protected EditorCommonApplication()
		{
			settings = new SettingsManager( ApplicationName );
			rootFileSystem = Settings.Get<RootFileSystem>();
			sourceFileSystem = new SourceFileSystem( Settings.Get<SourceFileSystemConfig>() );
      scripts = new ScriptMachine( this );
			ObjectsRootFolder.Initialize( this );
		}

		protected abstract string[] PluginsFileNames { get; }
		protected abstract string[] TypePluginsFileNames { get; }

		protected abstract void RegisterExtensions();

		private bool InitializeCommon( IOperationContext context )
		{
      if ( singletonApplication != null )
      {
        MessageBox.Show( "Attempted to create another EditorCommonApplication" );
      }
      singletonApplication = this;

			context.Progress( "Initialize plugins ..." );
			Extensions.LoadAssemblies( PluginsFileNames );

			context.Progress( "Initialize database types ..." );
			DataBase.LoadTypes( TypePluginsFileNames );

			context.Progress( "Initialize configuration objects ..." );
			Extensions.RegisterConfigObjects( this );

			context.Progress( "Initialize extensions ..." );
			RegisterExtensions();

			context.Progress( "Load configuration ..." );
			Settings.Load();
      Settings.Get<RootFileSystem>();
      Settings.Get<SourceFileSystemConfig>();

			context.Progress( "Prepare database ..." );
			DataBase.SetFileSystem( FileSystem );
			DataBase.UndoRedoManager = UndoRedo;

			context.Progress( "Initialize native components ..." );

			return true;
		}

		protected abstract bool InitializeApplication( IOperationContext context );

		public bool Initialize( IOperationContext context )
		{
      if (context == null)
				context = new Operations.Executor.ExecutorOperationContext();

			context.Start( false, true );

			if ( !InitializeCommon( context ) )
				return false;
			if ( !InitializeApplication( context ) )
				return false;

			return true;
		}

		private void TerminateCommon()
		{
			Settings.Terminate();
		}

		protected abstract void TerminateApplication();

		public void Terminate()
		{
			TerminateApplication();
			TerminateCommon();
    }

		public RootFileSystem FileSystem { get { return rootFileSystem; } }
		public SourceFileSystem SourceFileSystem { get { return sourceFileSystem; } }
		public SettingsManager Settings { get { return settings; } }
		public abstract Executor OperationExecutor { get; }
		public UndoRedoManager UndoRedo { get { return undoRedo; } }
		public ExtensionsManager Extensions { get { return extensions; } }
    public ConsoleCommandsManager Commands { get { return commands; } }
    public ScriptMachine Scripts { get { return scripts; } }

		public abstract string ApplicationName { get; }
	}
}

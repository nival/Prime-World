using System.Windows.Forms;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.IO;
using EditorLib.Operations;
using EditorLib.Plugin;
using EditorLib.Scripts;
using EditorLib.Settings;
using libdb.DB;
using libdb.UndoRedo;
using EditorNative;

namespace EditorPlugins
{
  public abstract class EditorNativeApplication : EditorCommonApplication
	{
    private EditorDumperInit nativeDumper = null;

    protected override bool InitializeApplication( IOperationContext context )
		{
      nativeDumper = new EditorDumperInit();
      ResourceCache.Initialize();
      EditorFileSystem.Initialize( FileSystem );
      DataBase.ChangeDBResourceEvent += OnChangeDBResourceEvent;

			return true;
		}

		private void OnChangeDBResourceEvent( DBID dbid )
		{
			ResourceCache.MarkAsDirty( dbid );
			DBResource resource = DataBase.Get<DBResource>( dbid );
		}

    protected override void TerminateApplication()
    {
      DataBase.ChangeDBResourceEvent -= OnChangeDBResourceEvent;
      ResourceCache.Release();
      EditorFileSystem.Release();
      nativeDumper = null;
    }
	}
}

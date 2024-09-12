using System;
using EditorLib.IO;
using EditorLib.Operations;
using EditorLib.Settings;
using libdb.DB;
using libdb.UndoRedo;
using EditorLib.Extensions;
using EditorLib.Plugin;
using EditorLib.Panels;
using EditorLib.ContextMenus;
using EditorLib.Menu;
using System.Windows.Forms;
using EditorLib.Binds;
using EditorLib.Scripts;

namespace EditorLib
{
	public interface IEditorCommonApplication
	{
		RootFileSystem FileSystem { get; }
		SourceFileSystem SourceFileSystem { get; }
		SettingsManager Settings { get; }
		Executor OperationExecutor { get; }
		UndoRedoManager UndoRedo { get; }
		ExtensionsManager Extensions { get; }
    ConsoleCommandsManager Commands { get; }
    ScriptMachine Scripts { get; }
  }

	public interface IEditorWinApplication
	{
		IEditorCommonApplication Application { get; }

		PanelsManager Panels { get; }
		ItemContextMenu ContextMenu { get; }
		EditorMenu MainMenu { get; }
		EditorToolbar Toolbar { get; }
    BindsManager BindsManager { get; }

    string IconAssembly { get; }

    string StatusLabel { set; }
		Control StatusPanel { set; }
	}

	public interface IEditorConApplication
	{
		IEditorCommonApplication Application { get; }
	}
}

using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.PropertiesEditor;

namespace EditorPlugins.Commands
{
	public class UndoEditorCommand : EditorLib.Menu.IEditorCommand
	{
		public override void Execute( EditorLib.IEditorWinApplication application )
		{
			application.Application.UndoRedo.Undo();
			PropertiesEditorPanel propertiesEditor = application.Panels.GetSingletonPanel<PropertiesEditorPanel>();
			if(propertiesEditor != null )
				propertiesEditor.RefreshView(true);

      application.Toolbar.UpdateToolbars();
      application.MainMenu.UpdateMenu();
    }

		public override string Name
		{
			get { return "Undo"; }
		}

    public override System.Drawing.Bitmap Image
    {
      get
      {
        return EditorPluginResources.UndoIcon;
      }
    }

    public override bool Enabled
    {
      get
      {
        return EditorWinApplication.ApplicationSingleton.UndoRedo.CanUndo;
      }
    }
	}
}

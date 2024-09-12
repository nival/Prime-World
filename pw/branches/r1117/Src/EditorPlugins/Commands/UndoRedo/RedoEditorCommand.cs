using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.PropertiesEditor;

namespace EditorPlugins.Commands
{
	public class RedoEditorCommand : EditorLib.Menu.IEditorCommand
	{
		public override void Execute( EditorLib.IEditorWinApplication application )
		{
			application.Application.UndoRedo.Redo();
			PropertiesEditorPanel propertiesEditor = application.Panels.GetSingletonPanel<PropertiesEditorPanel>();
			if ( propertiesEditor != null )
				propertiesEditor.RefreshView(true);

      application.Toolbar.UpdateToolbars();
      application.MainMenu.UpdateMenu();
    }

		public override string Name
		{
			get { return "Redo"; }
		}

    public override System.Drawing.Bitmap Image
    {
      get
      {
        return EditorPluginResources.RedoIcon;
      }
    }

    public override bool Enabled
    {
      get
      {
        return EditorWinApplication.ApplicationSingleton.UndoRedo.CanRedo;
      }
    }
	}
}

using System;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Commands
{
	public class SaveEditorCommand : EditorLib.Menu.IEditorCommand
	{
		public override void Execute( EditorLib.IEditorWinApplication application )
		{
      DateTime start = DateTime.UtcNow;

      application.StatusLabel = "Saving resources...";
      DataBase.Store();
			application.Application.FileSystem.Store();
      application.StatusLabel = "Resources Saved";

      application.Toolbar.UpdateToolbars();
      application.MainMenu.UpdateMenu();

      Log.TraceMessage( "Save time: {0:0.####} s", ( DateTime.UtcNow - start ).TotalSeconds );
    }

		public override string Name
		{
			get { return "Save"; }
		}

    public override System.Drawing.Bitmap Image
    {
      get
      {
        return global::EditorPlugins.EditorPluginResources.Save;
      }
    }

    public override bool Enabled
    {
      get
      {
        return libdb.DB.DataBase.IsModified;
      }
    }
	}
}

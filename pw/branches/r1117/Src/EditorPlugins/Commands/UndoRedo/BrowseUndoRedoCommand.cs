using System;
using System.Collections.Generic;
using System.Text;

namespace EditorPlugins.Commands
{
  public class BrowseUndoRedoCommand : EditorLib.Menu.IEditorCommand
  {
    public override void Execute( EditorLib.IEditorWinApplication application )
    {
      UndoRedo.BrowseUndoRedoForm form = new UndoRedo.BrowseUndoRedoForm( application );
      form.ShowDialog();
    }

    public override string Name { get { return "..."; } }

    public override string TooltipText { get { return "View operations history"; } }

    public override System.Drawing.Bitmap Image
    {
      get
      {
        return null;
      }
    }

    public override bool Enabled
    {
      get
      {
        return true;
      }
    }
  }
}

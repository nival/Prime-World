using EditorLib.Panels;
using EditorLib;

namespace EditorPlugins.Commands
{
  public class ShowPanelCommand : EditorLib.Menu.IEditorCommand
  {
    private EditorPanel panel = null;

    public override void Execute( IEditorWinApplication application )
    {
      if( panel == null )
        return;

      application.Panels.ShowSingletonPanel( panel );
      panel.Activate();
    }

    public ShowPanelCommand( EditorPanel _panel )
    {
      panel = _panel;
    }

    public override string Name
    {
      get
      {
        return panel.TabText;
      }
    }

    public override System.Drawing.Bitmap Image
    {
      get { return panel.Icon.ToBitmap(); }
    }

    public override bool IsChecked
    {
      get { return !panel.IsHidden; }
    }
  }
}

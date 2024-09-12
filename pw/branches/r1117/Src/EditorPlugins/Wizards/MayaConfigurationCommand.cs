using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Menu;
using EditorLib;

namespace EditorPlugins.Wizards
{
  public class MayaConfigurationCommand : IEditorCommand
  {
    public override void Execute( IEditorWinApplication application )
    {
      new MayaConfigForm( application ).ShowDialog();
    }

    public override string Name { get { return "Maya.exe usage configuration"; } }

  }
}

using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Menu;
using libdb.IO;
using System.Windows.Forms;
using EditorLib.IO;
using EditorLib.Operations;
using libdb.DB;
using System.Threading;
using EditorLib;
using EditorPlugins.Importer.Texture;
using System.IO;
using libdb.Diagnostics;
using System.Drawing;
using DBTypes;
using EditorNative;

namespace EditorPlugins.Importer.AtlasCommand
{
  public sealed class CreateAtlasCommand : IEditorCommand
  {
    private IEditorCommonApplication application;

    private bool Work( IOperationContext context )
    {
      return GlobalAtlas.Process( application, context );
    }

    public override void Execute( IEditorWinApplication application )
    {
      this.application = application.Application;
      this.application.OperationExecutor.Start( Work );
    }

    public override string Name
    {
      get { return "Create Atlas"; }
    }
  }
}
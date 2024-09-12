using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using EditorPlugins.UIScene;
using DBTypes;
using EditorNative;

namespace EditorPlugins.Editors.FontViewer
{
  public partial class FontViewerControl : Editor2DSceneControl
  {
    private EditorMaterialScene scene = null;
    protected override Editor2DSceneBase Scene { get { return scene; } }

    public FontViewerControl()
    {
      scene = new EditorMaterialScene( Handle );
      InitializeComponent();
    }

    public void SetFont( UIFontStyle font )
    {
      scene.LoadText( font.DBId, "The quick brown fox jumps over a lazy dog.", 10, toolStrip1.Height + 10 );
      Invalidate();
    }
  }
}

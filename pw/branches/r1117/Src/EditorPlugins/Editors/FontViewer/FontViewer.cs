using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib.Extensions;
using DBTypes;
using EditorLib;
using libdb.DB;
using System.IO;

namespace EditorPlugins.Editors.FontViewer
{
  [EditorLib.Extensions.EditorAttribute( "Fonts", true )]
  [ApplicableForDeriver]
  public partial class FontViewer : Editor<UIFontStyle>
  {
    public FontViewer()
    {
      InitializeComponent();
    }
    protected override bool Initialize( DBPtr<UIFontStyle> style, IEditorWinApplication application )
    {
      fontViewerControl1.SetFont( style.Get() );
      TabText = "Font: " + Path.GetFileNameWithoutExtension( style.DBId.FileName );
      return true;
    }
  }
}

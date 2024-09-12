using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace EditorPlugins.Scene
{
  public class DoubleBufferedListBox : ListBox
  {
    public DoubleBufferedListBox()
    {
      SetStyle( ControlStyles.OptimizedDoubleBuffer | ControlStyles.AllPaintingInWmPaint | ControlStyles.ResizeRedraw | ControlStyles.Opaque | ControlStyles.SupportsTransparentBackColor, true );
    }
  }
}

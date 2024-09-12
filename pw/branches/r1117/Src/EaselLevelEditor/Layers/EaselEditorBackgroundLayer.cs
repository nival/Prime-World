using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace EaselLevelEditor.Layers
{
  /// <summary>
  /// load new background event
  /// arguments
  /// </summary>
  public class LoadBackgroundEventArgs : EventArgs
  {
    public EaselLevelEditor _editor;
  }

  public delegate void LoadEditorBackground(object source,LoadBackgroundEventArgs args);

  /// <summary>
  /// background layer object
  /// is responsible for background 
  /// visibility
  /// </summary>
  class EaselEditorBackgroundLayer :  EaselEditorLayer
  {
    private Rectangle clientRect;      // client rect
    private Bitmap    backgroundImage; // background

    public EaselEditorBackgroundLayer() : base()
    {
      clientRect = new Rectangle(0, 0, 1280, 1024);
      InitializeEmptyBackgound();
    }

    public void LoadBackgroundHandler(object source, LoadBackgroundEventArgs args)
    {
      OpenFileDialog fileDlg = new OpenFileDialog();
      fileDlg.InitialDirectory = "c:\\";
      fileDlg.Filter = "Image Files|*.bmp;*.jpg;*.gpeg;*tga";
      DialogResult dlgRes = fileDlg.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        // opening image
        Bitmap newImage = new Bitmap(fileDlg.FileName);

        // setting window Size
        args._editor.ClientSize = new Size(newImage.Width, newImage.Height);
               
        clientRect = new Rectangle(0, 0, newImage.Width, newImage.Height);

        // setting background
        backgroundImage = newImage;
      }
    }

    public void ClearBackgroundHandler(object source, EventArgs args)
    {
      InitializeEmptyBackgound();
    }

    protected override void vDraw(Graphics _graphics)
    {
      _graphics.DrawImage(backgroundImage, clientRect);
    }

    protected override void vResize(EaselLevelEditor _editor) 
    {
      clientRect = _editor.ClientRectangle;
    }

    // internal initialization
    private void InitializeEmptyBackgound()
    {
      // making blue background
      Bitmap background = new Bitmap(clientRect.Width, clientRect.Height);
      Graphics graphics = Graphics.FromImage(background);
      graphics.FillRectangle(Brushes.Blue, clientRect);

      backgroundImage = background;
    }
  }
}

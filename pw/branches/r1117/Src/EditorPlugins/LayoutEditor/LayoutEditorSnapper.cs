using System;
using System.Collections.Generic;
using System.Text;
using EditorNative;
using System.Drawing;
using System.Windows.Forms;
using System.Drawing.Drawing2D;


namespace EditorPlugins.LayoutEditor
{
  public class LayoutEditorSnapper
  {
    [Flags]
    public enum SnapType
    {
      Move,
      ResizeLeft,
      ResizeRight,
      ResizeTop,
      ResizeBottom,
    };

    EditorUIScene layoutController = null;

    private bool isGridSnapOn = false;
    public bool IsGridSnapOn { get { return isGridSnapOn; } set { isGridSnapOn = value; Recalculate(); } }
    private bool isGridVisible = false;
    public bool IsGridVisible { get { return isGridVisible; } set { isGridVisible = value; } }
    private bool isObjectSnapOn = false;
    public bool IsObjectSnapOn { get { return isObjectSnapOn; } set { isObjectSnapOn = value; Recalculate(); } }
    private bool isParentSnapOn = false;
    public bool IsParentSnapOn { get { return isParentSnapOn; } set { /*isParentSnapOn = value; Recalculate();*/ } }

    Pen gridPen = new Pen( Color.Black );
    public Color GridColor { get { return gridPen.Color; } set { gridPen.Color = value; } }

    private int gridSize = 20;
    private int snapSize = 10;
    public int GridSize 
    { 
      get { return gridSize; } 
      set { 
        gridSize = value; 
        snapSize = gridSize / 2;
        gridPen.DashPattern = new float[2] { 1, gridSize - 1 };
        Recalculate(); 
      } 
    }

    private int[] snapperX = new int[1280];
    private int[] snapperY = new int[1024];

    public LayoutEditorSnapper( EditorUIScene _layoutController )
    {
      layoutController = _layoutController;
      GridSize = 20;
      Recalculate();
    }

    public void OnPaint( PaintEventArgs e )
    {
      Graphics g = e.Graphics;
      if ( isGridVisible )
      {
        int minX = Math.Max( 0, e.ClipRectangle.Left ) / GridSize * GridSize;
        int maxX = ( Math.Min( 1280, e.ClipRectangle.Right ) / GridSize + 1 ) * GridSize;

        int minY = Math.Max( 0, e.ClipRectangle.Top ) / GridSize * GridSize;
        int maxY = ( Math.Min( 1024, e.ClipRectangle.Bottom ) / GridSize + 1 ) * GridSize;

        for ( int x = minX; x <= maxX; x += gridSize )
          for ( int y = minY; y <= maxY; y += gridSize )
          {
            layoutController.DrawPoint( x, y, 1, GridColor );
          }
      }
    }

    public Rectangle Snap( Rectangle desired, SnapType snapType )
    {


      return desired;
    }

    public int SnapX( int coord )
    {
      if ( coord < 0 || coord >= snapperX.Length || snapperX[coord] == -1 )
        return coord;
      else
        return snapperX[coord];
    }

    public int SnapY( int coord )
    {
      if ( coord < 0 || coord >= snapperY.Length || snapperY[coord] == -1 )
        return coord;
      else
        return snapperY[coord];
    }

    private void AdjustSnapTargets( int[] target, int from, int to, int point )
    {
      for ( int i = from ; i < to; ++i )
      {
        if ( target[i] == -1 || Math.Abs( point - i ) < Math.Abs( target[i] - i ) )
          target[i] = point;
      }
    }

    private void AddSnapPointCenter( int[] target, int point )
    {
      AdjustSnapTargets( target, Math.Max( 0, point - snapSize ), Math.Min( point + snapSize, target.Length ), point );
    }

    private void AddSnapPointPlus( int[] target, int point )
    {
      AdjustSnapTargets( target, point, Math.Min( point + snapSize, target.Length ), point );
    }

    private void AddSnapPointMinus( int[] target, int point )
    {
      AdjustSnapTargets( target, Math.Max( 0, point - snapSize ), point, point );
    }

    internal void Recalculate()
    {
      for ( int i = 0; i < 1280; ++i )
        snapperX[i] = -1;

      for ( int i = 0; i < 1024; ++i )
        snapperY[i] = -1;

      if ( isGridSnapOn )
      {
        for ( int i = 0; i < 1280; i += gridSize )
          AddSnapPointCenter( snapperX, i );

        for ( int i = 0; i < 1024; i += gridSize )
          AddSnapPointCenter( snapperY, i );
      }

      if ( isObjectSnapOn )
      {
        List<Rectangle> allBounds = layoutController.GetAllWindowBounds();

        foreach ( Rectangle item in allBounds )
        {
          AddSnapPointPlus( snapperX, item.X );
          AddSnapPointMinus( snapperX, item.X + item.Width );
          AddSnapPointPlus( snapperY, item.Y );
          AddSnapPointMinus( snapperY, item.Y + item.Height );
        }
      }
    }
  }
}

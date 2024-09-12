using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using EditorNative;

namespace EditorPlugins.UIScene
{
  public class CustomCursor
  {
    public static Cursor CreateCursorWithText( Cursor cur, String txt )
    {
      Icon icon = Icon.FromHandle( cur.Handle );
      Bitmap bitmap = icon.ToBitmap();
      Graphics g = Graphics.FromImage( bitmap );
      //g.DrawIcon(icon,0,0);
      using ( System.Drawing.Font f = new System.Drawing.Font( FontFamily.GenericSansSerif, 6, FontStyle.Regular ) )
        g.DrawString( txt, f, Brushes.Red, 0, 0 );
      System.IntPtr ptr = bitmap.GetHicon();
      Win32.ICONINFO tmp = new Win32.ICONINFO();
      Win32.User.GetIconInfo( ptr, out tmp );
      tmp.xHotspot = cur.HotSpot.X;
      tmp.yHotspot = cur.HotSpot.Y;
      tmp.fIcon = 0;
      ptr = Win32.User.CreateIconIndirect( ref tmp );
      return new Cursor( ptr );
    }
  }

  public  class Editor2DSceneControl : UserControl
  {
    protected virtual Editor2DSceneBase Scene { get { return null;  } }

    public Editor2DSceneControl()
    {
      DoubleBuffered = false;
      SetStyle( ControlStyles.UserPaint, true );
      SetStyle( ControlStyles.AllPaintingInWmPaint, true );
      SetStyle( ControlStyles.ResizeRedraw, true );
      SetStyle( ControlStyles.Opaque, true );
      SetStyle( ControlStyles.UserMouse, true );
      SetStyle( ControlStyles.Selectable, true );
      SetStyle( ControlStyles.FixedHeight, true );
      SetStyle( ControlStyles.FixedWidth, true );

      UpdateStyles();
    }

    public void DrawPoint( int x, int y, int size, Color color )
    {
      Scene.DrawPoint( x, y, size, color );
    }

    public void DrawLine( int x1, int y1, int x2, int y2, Color color )
    {
      Scene.DrawLine( x1, y1, x2, y2, color );
    }
    public void DrawLine( Point p1, Point p2, Color color )
    {
      Scene.DrawLine( p1.X, p1.Y, p2.X, p2.Y, color );
    }

    public void DrawRectangle( Rectangle rect, Color color )
    {
      DrawLine( rect.Left, rect.Top, rect.Right, rect.Top, color );
      DrawLine( rect.Right, rect.Top, rect.Right, rect.Bottom, color );
      DrawLine( rect.Right, rect.Bottom, rect.Left, rect.Bottom, color );
      DrawLine( rect.Left, rect.Bottom, rect.Left, rect.Top, color );
    }

    public void DrawSelection( Rectangle rect, Color color, bool canMove, bool canResize )
    {
      DrawRectangle( rect, color );

      if ( canMove || canResize )
      {
        DrawPoint( ( rect.Left + rect.Right ) / 2, rect.Bottom, 5, color );
        DrawPoint( rect.Right, rect.Bottom, 5, color );
        DrawPoint( rect.Left, rect.Bottom, 5, color );
        DrawPoint( rect.Right, rect.Top, 5, color );
        DrawPoint( rect.Right, ( rect.Top + rect.Bottom ) / 2, 5, color );
      }

      if ( canMove )
      {
        if ( canResize )
        {
          DrawPoint( rect.Left, rect.Top, 5, color );
          DrawPoint( ( rect.Left + rect.Right ) / 2, rect.Top, 5, color );
          DrawPoint( rect.Left, ( rect.Top + rect.Bottom ) / 2, 5, color );
        }
        else
          DrawPoint( Math.Min( rect.Left + 10, rect.Right ), rect.Top, 5, color );
      }
    }

    protected override void OnPaint( PaintEventArgs e )
    {
      if ( DesignMode )
        base.OnPaint( e );
      else if ( IsHandleCreated && !IsDisposed && Scene != null )
        Scene.Draw( Handle, ClientSize.Width, ClientSize.Height );
    }
  }
}

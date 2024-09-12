using System;
using System.Collections.Generic;
using System.Text;
using DBTypes;
using System.Drawing;
using System.Windows.Forms;
using EditorPlugins.UIScene;

namespace EditorPlugins.LayoutEditor.States
{
  class MoveSelectionState : LayoutEditorState
  {
    private List<UILayout> selectedWindows = null;
    private Point mousePosSnapped = new Point( 0, 0 );
    private Point whereMouseDown = new Point( 0, 0 );
    private List<UILayout> movedWindows = new List<UILayout>();

    public MoveSelectionState( LayoutEditorControl control, List<UILayout> _selectedWindows, Point _whereMouseDown )
      : base( control )
    {
      selectedWindows = _selectedWindows;
      whereMouseDown = _whereMouseDown;
      mousePosSnapped = whereMouseDown;

      foreach ( UILayout item in selectedWindows )
      {
        if ( !selectedWindows.Contains( Control.GetWindowParent( item ) ) )
          movedWindows.Add( item );
      }
    }

    public override void OnPaint( Editor2DSceneControl uiRender )
    {
      for ( int i = 0; i < selectedWindows.Count; ++i )
      {
        Rectangle wr = Control.GetWindowRectangle( selectedWindows[i] );
        wr.X += mousePosSnapped.X - whereMouseDown.X;
        wr.Y += mousePosSnapped.Y - whereMouseDown.Y;
        uiRender.DrawSelection( wr, SelectedState.SelectedPen.Color, true, true );
      }
      base.OnPaint( uiRender );
    }

    public override void OnMouseMove( MouseEventArgs e )
    {
      if ( movedWindows.Count == 1 )
      {
        Rectangle wr = Control.GetWindowRectangle( movedWindows[0] );
        Point snapped = wr.Location;
        snapped.X = Control.Snapper.SnapX( wr.X + e.Location.X - whereMouseDown.X );
        if ( Control.Snapper.IsObjectSnapOn && snapped.X == wr.X + e.Location.X - whereMouseDown.X )
          snapped.X = Control.Snapper.SnapX( wr.Width + e.Location.X ) - wr.Width;

        snapped.Y = Control.Snapper.SnapY( wr.Y + e.Location.Y - whereMouseDown.Y );
        if ( Control.Snapper.IsObjectSnapOn && snapped.Y == wr.Y + e.Location.Y - whereMouseDown.Y )
          snapped.Y = Control.Snapper.SnapY( wr.Height + e.Location.Y ) - wr.Height;

        mousePosSnapped.X = snapped.X + whereMouseDown.X - wr.X;
        mousePosSnapped.Y = snapped.Y + whereMouseDown.Y - wr.Y;
      }
      else
        mousePosSnapped = e.Location;

      if ( selectedWindows.Count == 1 )
      {
        EditorLib.PropertiesEditor.PropertiesEditorPanel propertiesEditor = Control.EditorApplication.Panels.GetSingletonPanel<EditorLib.PropertiesEditor.PropertiesEditorPanel>();
        if ( propertiesEditor != null )
          propertiesEditor.RefreshView( true );
      }

      Control.Refresh();
    }

    public override void OnMouseUp( MouseEventArgs e )
    {
      base.OnMouseUp( e );

      if ( e.Button != MouseButtons.Left )
        return;

      Control.EditorApplication.Application.UndoRedo.Start( "Move Windows" );

      foreach ( UILayout item in movedWindows )
      {
        item.location.x += mousePosSnapped.X - whereMouseDown.X;
        item.location.y += mousePosSnapped.Y - whereMouseDown.Y;
      }

      Control.EditorApplication.Application.UndoRedo.Commit();
      Control.Snapper.Recalculate();
      Control.Refresh();
      Control.ActiveState = new SelectedState( Control, selectedWindows );
    }


    internal static void MoveManual( LayoutEditorControl control, List<UILayout> selectedWindows, int dx, int dy )
    {
      control.EditorApplication.Application.UndoRedo.Start( "Move Windows" );

      List<UILayout> movedWindows = new List<UILayout>();
      foreach ( UILayout item in selectedWindows )
      {
        if ( !selectedWindows.Contains( control.GetWindowParent( item ) ) )
          movedWindows.Add( item );
      }

      foreach ( UILayout item in movedWindows )
      {
        item.location.x += dx;
        item.location.y += dy;
      }

      control.EditorApplication.Application.UndoRedo.Commit();
      control.Snapper.Recalculate();
      control.Refresh();
    }
  }
}

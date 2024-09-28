using System;
using System.Collections.Generic;
using System.Text;
using DBTypes;
using System.Drawing;
using System.Windows.Forms;
using EditorPlugins.UIScene;

namespace EditorPlugins.LayoutEditor.States
{
  class ResizeSelectionState : LayoutEditorState
  {
    private UILayout resizedWindow = null;
    SelectedState.Action action = SelectedState.Action.NoAction;
    private Point previousMousePos = LayoutEditorState.InvalidPoint;
    private Rectangle windowRectangle = new Rectangle();
    private Rectangle windowRectangleSnapped = new Rectangle();
    private Rectangle originalWindowRectangle = new Rectangle();

    public ResizeSelectionState( LayoutEditorControl control, UILayout actionWindow, Point _whereLeftMouseDown, SelectedState.Action _action )
      : base( control )
    {
      resizedWindow = actionWindow;
      previousMousePos = _whereLeftMouseDown;
      action = _action;
      windowRectangle = Control.GetWindowRectangle( resizedWindow );
      originalWindowRectangle = windowRectangle;
      windowRectangleSnapped = windowRectangle;
      SnapRectangle();
    }

    private void SnapRectangle()
    {
      if ( action == SelectedState.Action.DragLeft || action == SelectedState.Action.DragTopLeft || action == SelectedState.Action.DragBottomLeft )
      {
        windowRectangleSnapped.X = Control.Snapper.SnapX( windowRectangle.X );
        windowRectangleSnapped.Width = windowRectangle.Right - windowRectangleSnapped.X;
      }
      else if ( action == SelectedState.Action.DragRight || action == SelectedState.Action.DragTopRight || action == SelectedState.Action.DragBottomRight )
      {
        windowRectangleSnapped.Width = Control.Snapper.SnapX( windowRectangle.Right ) - windowRectangle.Left;
        windowRectangleSnapped.X = windowRectangle.X;
      }

      if ( action == SelectedState.Action.DragTop || action == SelectedState.Action.DragTopLeft || action == SelectedState.Action.DragTopRight )
      {
        windowRectangleSnapped.Y = Control.Snapper.SnapY( windowRectangle.Y );
        windowRectangleSnapped.Height = windowRectangle.Bottom - windowRectangleSnapped.Y;
      }
      else if ( action == SelectedState.Action.DragBottom || action == SelectedState.Action.DragBottomLeft || action == SelectedState.Action.DragBottomRight )
      {
        windowRectangleSnapped.Height = Control.Snapper.SnapX( windowRectangle.Bottom ) - windowRectangle.Top;
        windowRectangleSnapped.Y = windowRectangle.Y;
      }
    }

    public override void OnPaint( Editor2DSceneControl uiRender )
    {
      uiRender.DrawSelection( windowRectangleSnapped, SelectedState.SelectedPen.Color, true, true );
      base.OnPaint( uiRender );
    }

    public override void OnMouseMove( MouseEventArgs e )
    {
      base.OnMouseMove( e );

      int dx = e.X - previousMousePos.X;
      int dy = e.Y - previousMousePos.Y;

      if ( action == SelectedState.Action.DragLeft || action == SelectedState.Action.DragTopLeft || action == SelectedState.Action.DragBottomLeft )
      {
        windowRectangle.X += dx;
        windowRectangle.Width -= dx;
      }
      else if ( action == SelectedState.Action.DragRight || action == SelectedState.Action.DragTopRight || action == SelectedState.Action.DragBottomRight )
      {
        windowRectangle.Width += dx;
      }

      if ( action == SelectedState.Action.DragTop || action == SelectedState.Action.DragTopLeft || action == SelectedState.Action.DragTopRight )
      {
        windowRectangle.Y += dy;
        windowRectangle.Height -= dy;
      }
      else if ( action == SelectedState.Action.DragBottom || action == SelectedState.Action.DragBottomLeft || action == SelectedState.Action.DragBottomRight )
      {
        windowRectangle.Height += dy;
      }
      previousMousePos = e.Location;

      SnapRectangle();

      EditorLib.PropertiesEditor.PropertiesEditorPanel propertiesEditor = Control.EditorApplication.Panels.GetSingletonPanel<EditorLib.PropertiesEditor.PropertiesEditorPanel>();
      if ( propertiesEditor != null )
        propertiesEditor.RefreshView( true );

      Control.Refresh();
    }

    public override void OnMouseUp( MouseEventArgs e )
    {
      base.OnMouseUp( e );
      if ( e.Button != MouseButtons.Left )
        return;

      Control.EditorApplication.Application.UndoRedo.Start( "Resize Window" );
      resizedWindow.location.x += windowRectangleSnapped.X - originalWindowRectangle.X;
      resizedWindow.location.y += windowRectangleSnapped.Y - originalWindowRectangle.Y;

      foreach ( var item in resizedWindow.subLayouts )
      {
        UILayout child = item.Get();

        if ( null == child )
          continue;

        UpdateChildLocation( child );
      }

      resizedWindow.size.x = windowRectangleSnapped.Width;
      resizedWindow.size.y = windowRectangleSnapped.Height;
      Control.EditorApplication.Application.UndoRedo.Commit();
      Control.Snapper.Recalculate();
      Control.Refresh();
      List<UILayout> selectedWindows = new List<UILayout>();
      selectedWindows.Add( resizedWindow );
      Control.ActiveState = new SelectedState( Control, selectedWindows );
    }

    internal static void ResizeManual( LayoutEditorControl control, List<UILayout> selectedWindows, int dx, int dy )
    {
      control.EditorApplication.Application.UndoRedo.Start( "Move Windows" );

      foreach ( UILayout item in selectedWindows )
      {
        item.size.x += dx;
        item.size.y += dy;
      }

      control.EditorApplication.Application.UndoRedo.Commit();
      control.Snapper.Recalculate();
      control.Refresh();
    }

    private void UpdateChildLocation( UILayout child )
    {
      switch ( child.hAlign )
      {
        case EUIElementHAlign.Right:
          child.location.x += windowRectangleSnapped.Width - resizedWindow.size.x;
          break;
        case EUIElementHAlign.Center:
          child.location.x += ( windowRectangleSnapped.Width - resizedWindow.size.x ) / 2;
          break;
        case EUIElementHAlign.FixedMargins:
          child.size.x += windowRectangleSnapped.Width - resizedWindow.size.x;
          break;
        case EUIElementHAlign.Proportional:
          float posPart = (float)child.location.x / (float)resizedWindow.size.x;
          float sizePart = (float)child.size.x / (float)resizedWindow.size.x;
          child.location.x = (int)( windowRectangleSnapped.Width * posPart );
          child.size.x = (int)( windowRectangleSnapped.Width * sizePart );
          break;
      }

      switch ( child.vAlign )
      {
        case EUIElementVAlign.Bottom:
          child.location.y += windowRectangleSnapped.Height - resizedWindow.size.y;
          break;
        case EUIElementVAlign.Center:
          child.location.y += ( windowRectangleSnapped.Height - resizedWindow.size.y ) / 2;
          break;
        case EUIElementVAlign.FixedMargins:
          child.size.y += windowRectangleSnapped.Height - resizedWindow.size.y;
          break;
        case EUIElementVAlign.Proportional:
          float posPart = (float)child.location.y / (float)resizedWindow.size.y;
          float sizePart = (float)child.size.y / (float)resizedWindow.size.y;
          child.location.y = (int)( windowRectangleSnapped.Height * posPart );
          child.size.y = (int)( windowRectangleSnapped.Height * sizePart );
          break;
      }
    }

  }
}

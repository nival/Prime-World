using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using libdb.DB;
using EditorLib.Extensions;
using EditorPlugins.UIScene;
using DBTypes;
using EditorLib.PropertiesEditor.States;
using EditorLib.ToolBox;
using EditorLib.ObjectsBrowser;

namespace EditorPlugins.LayoutEditor.States
{
  internal class SelectedState : PreselectionState
  {
    private List<UILayout> selectedWindows = null;

    public override void OnEnterState( LayoutEditorState previousState )
    {
      base.OnEnterState( previousState );
      if ( selectedWindows.Count == 1 )
      {
        LayoutPropertiesEditorObject propEditorObject = new LayoutPropertiesEditorObject( selectedWindows[0], Control );
        Control.EditorApplication.Panels.GetSingletonPanel<EditorLib.PropertiesEditor.PropertiesEditorPanel>().SelectedObject = propEditorObject;
        Control.EditorApplication.Panels.GetSingletonPanel<LayoutTreeView>().SetSelectedLayout( selectedWindows[0] );
      }
      else
      {
        Control.EditorApplication.Panels.GetSingletonPanel<EditorLib.PropertiesEditor.PropertiesEditorPanel>().SelectedObject = null;
        Control.EditorApplication.Panels.GetSingletonPanel<LayoutTreeView>().SetSelectedLayout( null );
      }
    }

    public override void OnLeaveState( LayoutEditorState previousState )
    {
      base.OnLeaveState( previousState );
    }

    public SelectedState( LayoutEditorControl control, List<UILayout> _selectedWindows )
      : base( control )
    {
      this.selectedWindows = _selectedWindows;
    }

    private bool CanBeDeleted( List<UILayout> windows )
    {
      if ( windows.Count < 1 )
        return false;

      return true;
    }

    private List<UILayout> UpdateSelectedWindows( List<UILayout> windows )
    {
      List<UILayout> selectedWindowsTmp = IsControl ? new List<UILayout>( selectedWindows ) : new List<UILayout>();
      if ( IsControl )
      {
        foreach ( UILayout window in windows )
        {
          if ( selectedWindowsTmp.Contains( window ) )
          {
            selectedWindowsTmp.Remove( window );
          }
          else
          {
            selectedWindowsTmp.Add( window );
          }
        }
      }
      else
      {
        selectedWindowsTmp.AddRange( windows );
      }
      return selectedWindowsTmp;
    }

    public override void OnKeyUp( KeyEventArgs e )
    {
      base.OnKeyUp( e );
      if ( e.KeyCode == Keys.Right )
        KeyboardMoveResizeInternal( 1, 0 );
      else if ( e.KeyCode == Keys.Left )
        KeyboardMoveResizeInternal( -1, 0 );
      else if ( e.KeyCode == Keys.Up )
        KeyboardMoveResizeInternal( 0, -1 );
      else if ( e.KeyCode == Keys.Down )
        KeyboardMoveResizeInternal( 0, 1 );
      else if ( e.Control && e.KeyCode == Keys.C )
      {
        Copy( null, null );
      }
      else if ( e.Control && e.KeyCode == Keys.V )
      {
        Paste( null, null );
      }
      else if ( e.Control && e.KeyCode == Keys.X )
      {
        Delete( null, null );
      }
      else if ( e.Control && e.KeyCode == Keys.U )
      {
      }
    }

    private void KeyboardMoveResizeInternal( int dx, int dy )
    {
      int speed = IsControl ? 5 : 1;
      if ( IsShift )
        ResizeSelectionState.ResizeManual( Control, selectedWindows, dx * speed, dy * speed );
      else
        MoveSelectionState.MoveManual( Control, selectedWindows, dx * speed, dy * speed );
    }

    protected override void SelectWindow( UILayout _window )
    {
      List<UILayout> windows = new List<UILayout>();
      if ( _window != null )
      {
        windows.Add( _window );
      }
      else
      {
      }
      Control.SetSelection( UpdateSelectedWindows( windows ) );
    }

    private static List<UILayout> copiedWindows = new List<UILayout>();
    private void Copy( object sender, EventArgs e )
    {
      copiedWindows.Clear();
      foreach ( UILayout window in selectedWindows )
      {
        UILayout windowParent = Control.GetWindowParent( window );
        if ( null != windowParent && !selectedWindows.Contains( windowParent ) )
        {
          copiedWindows.Add( window );
        }
      }
    }

    private void Paste( object sender, EventArgs e )
    {
      Control.PasteWindows( copiedWindows, selectedWindows[0] );
    }

    public override void ShowContextMenu( Control ctrl, Point at )
    {
      menu.MenuItems.Clear();
      ConstructMenu( at, ( ctrl is LayoutTreeView ), false );
      menu.Show( ctrl, at );
    }

    protected override void ConstructMenu( Point location, bool showStates, bool checkCursorPos )
    {
      MenuItem itemMenu = null;
      itemMenu = new MenuItem( "Copy", Copy, Shortcut.CtrlC );
      menu.MenuItems.Add( itemMenu );
      if ( copiedWindows.Count > 0 && selectedWindows.Count == 1 )
      {
        bool canPaste = false;
        if ( checkCursorPos )
        {
          List<UILayout> windows = Control.GetWindowsUnderPoint( location );
          foreach ( UILayout window in windows )
          {
            if ( selectedWindows[0] == window )
            {
              canPaste = true;
              break;
            }
          }
        }
        else
          canPaste = true;

        foreach ( UILayout window in copiedWindows )
        {
          if ( !Control.CanAttachToParent( window, selectedWindows[0] ) )
          {
            canPaste = false;
            break;
          }
        }
        if ( canPaste )
        {
          itemMenu = new MenuItem( "Paste", Paste, Shortcut.CtrlV );
          menu.MenuItems.Add( itemMenu );
        }
      }
      if ( CanBeDeleted( selectedWindows ) )
      {
        itemMenu = new MenuItem( "Delete Selected", Delete, Shortcut.CtrlX );
        itemMenu.Tag = selectedWindows;
        itemMenu.Enabled = true;
        menu.MenuItems.Add( itemMenu );
      }
      if ( selectedWindows.Count == 1 && Control.GetWindowParent( selectedWindows[0] ) != null )
      {
        UILayout target = selectedWindows[0];
        if ( target.DBId.IsInlined && target.DBId.FileName == Control.RootLayout.DBId.FileName )
        {
          if ( target.__parent.Get() != null && target.__parent.DBId.IsInlined 
            && target.__parent.DBId.FileName == Control.RootLayout.DBId.FileName )
          {
            // This is likely a state, jump up to default state and its parent ptr
            target = target.__parent.Get();
          }

          if ( target.__parent.Get() != null && !target.__parent.DBId.IsInlined 
            && target.__parent.DBId.FileName != Control.RootLayout.DBId.FileName )
          {

            if ( menu.MenuItems.Count > 0 )
              menu.MenuItems.Add( "-" );

            itemMenu = new MenuItem( "Open '" + target.__parent.DBId + "'", OpenInNewWindow );
            itemMenu.Tag = target.__parent.DBId;
            itemMenu.Enabled = true;
            menu.MenuItems.Add( itemMenu );
          }
        }
      }
      if ( menu.MenuItems.Count > 0 )
        menu.MenuItems.Add( "-" );
      base.ConstructMenu( location, showStates, checkCursorPos );
    }

    private void Delete( object sender, EventArgs e )
    {
      Control.Delete( selectedWindows );
    }

    private void OpenInNewWindow( object sender, EventArgs e )
    {
      MenuItem item = sender as MenuItem;
      if ( item == null )
        return;

      DBID winDBId = item.Tag as DBID;
      if ( winDBId != null && winDBId != DBID.Empty )
      {
        DBResource resource = DataBase.Get<DBResource>( winDBId ).Get();
        if ( ReferenceEquals( resource, null ) )
          return;

        if ( Control.EditorApplication.Application.Extensions.GetEditorsCount( resource.GetType() ) > 0 )
        {
          Control.EditorApplication.Application.Extensions.OpenEditor( winDBId, Control.EditorApplication, null, false );
          Control.EditorApplication.Application.Settings.Get<FolderBookmarks>().RegisterOpenObject( winDBId );
        }
      }
    }

    public bool CanChangeSelection()
    {
      if ( CurrentAction != Action.NoAction &&
          CurrentAction != Action.Select )
        return false;

      return true;
    }

    private static System.Drawing.Color selectedColor = System.Drawing.Color.Green;

    private static Pen selectedPen = new Pen( selectedColor, 1.0f );
    private static Brush selectedBrush = new SolidBrush( selectedColor );
    internal static Pen SelectedPen { get { return selectedPen; } }
    internal static Brush SelectedBrush { get { return selectedBrush; } }
    internal static System.Drawing.Color SelectedColor
    {
      get
      {
        return selectedColor;
      }
      set
      {
        selectedColor = value;
        selectedPen = new Pen( selectedColor, 1.0f );
        selectedPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
        selectedBrush = new SolidBrush( selectedColor );
      }
    }

    public override void OnPaint( Editor2DSceneControl uiRender )
    {
      if ( PreSelectedWindows != null )
      {
        /*Window[] tmpWindows = UpdateSelectedWindows( PreSelectedWindows );
        for ( int i = 0; i < tmpWindows.Length; ++i )
        {
          Rectangle wr = tmpWindows[i].GetWindowRect();
          wr.Width = wr.Right - wr.Left - 1;
          wr.Height = wr.Bottom - wr.Top - 1;
          uiRender.DrawSelection( wr, SelectedState.SelectedPen.Color, tmpWindows[i].CanMove, tmpWindows[i].CanResize );
        }*/
      }
      else
      {
        UILayout commonParent = Control.GetWindowParent( selectedWindows[0] );
        bool haveSameParent = true;
        for ( int i = 0; i < selectedWindows.Count; ++i )
        {
          if ( commonParent != Control.GetWindowParent( selectedWindows[i] ) )
          {
            haveSameParent = false;
            break;
          }
        }
        if ( haveSameParent && commonParent != null )
        {
          Rectangle wr = Control.GetWindowRectangle( commonParent );
          uiRender.DrawRectangle( wr, System.Drawing.Color.Red );
        }

        for ( int i = 0; i < selectedWindows.Count; ++i )
        {
          Rectangle wr = Control.GetWindowRectangle( selectedWindows[i] );
          wr.Width = wr.Right - wr.Left - 1;
          wr.Height = wr.Bottom - wr.Top - 1;

          if ( selectedWindows[i] is UIImageLabelLayout )
          {
            UIImageLabelLayout il = selectedWindows[i] as UIImageLabelLayout;

            if ( il.textMargins.x1 != 0 || il.textMargins.x2 != 0 || il.textMargins.y1 != 0 || il.textMargins.y2 != 0 )
            {
              Rectangle textArea = wr;
              textArea.X += (int)il.textMargins.x1;
              textArea.Width -= (int)( il.textMargins.x1 + il.textMargins.x2 );
              textArea.Y += (int)il.textMargins.y1;
              textArea.Height -= (int)( il.textMargins.y1 + il.textMargins.y2 );

              uiRender.DrawSelection( textArea, System.Drawing.Color.Blue, false, false );
            }
          }

          uiRender.DrawSelection( wr, SelectedState.SelectedPen.Color, true, true );
        }
      }
      base.OnPaint( uiRender );
    }

    private UILayout currentActionWindow = null;

    public override void OnMouseMove( MouseEventArgs e )
    {
      base.OnMouseMove( e );

      if ( e.Button == MouseButtons.None && CurrentAction != Action.ChangeParent )
      {
        UILayout actionWindow = null;
        Control.SetCursor( GetActionCursor( GetActionAtPoint( e.Location, out actionWindow ) ) );
      }
      else if ( e.Button == MouseButtons.Left && CurrentAction == Action.NoAction )
      {
        if ( SelectorView.Height >= MOUSE_CLICK_DIST || SelectorView.Width >= MOUSE_CLICK_DIST )
        {
          Action action = GetActionAtPoint( WhereLeftMouseDown, out currentActionWindow );
          Control.SetCursor( GetActionCursor( action ) );
          CurrentAction = action;
          if ( action == Action.NoAction )
            CurrentAction = Action.Select;
          else if ( action == Action.Move )
            Control.ActiveState = new MoveSelectionState( Control, selectedWindows, WhereLeftMouseDown );
          else if ( action != Action.ChangeParent && action != Action.NoAction ) // resize
            Control.ActiveState = new ResizeSelectionState( Control, currentActionWindow, WhereLeftMouseDown, action );
        }
      }
    }

    public override void OnMouseDown( MouseEventArgs e )
    {
      base.OnMouseDown( e );

      if ( e.Button == MouseButtons.Left && CurrentAction != Action.ChangeParent )
      {
      }
    }

    public override void OnMouseUp( MouseEventArgs e )
    {
      base.OnMouseUp( e );
      if ( e.Button != MouseButtons.Left )
        return;

      if ( CurrentAction == Action.ChangeParent )
      {
        List<UILayout> windows = Control.GetWindowsUnderPoint( e.Location );
        if ( windows.Count > 0 )
        {
          UILayout parentWindow = windows[0];
          if ( parentWindow != null )
          {
            Control.ChangeParent( selectedWindows, -1, parentWindow );
          }
        }

      }
      else if ( CanChangeSelection() )
      {
        if ( SelectorView.Height > MOUSE_CLICK_DIST && SelectorView.Width > MOUSE_CLICK_DIST )
        {
          List<UILayout> windows = Control.GetWindowsInRect( SelectorView );
          Control.SetSelection( UpdateSelectedWindows( windows ) );
        }
        else
        {
          Action action = GetActionAtPoint( e.Location, out currentActionWindow );
          currentActionWindow = null;

          if ( IsControl || IsShift )
          {
            List<UILayout> windows = Control.GetWindowsUnderPoint( e.Location );
            windows.RemoveRange( 1, windows.Count - 1 );
            Control.SetSelection( UpdateSelectedWindows( windows ) );
          }
          else if ( action == Action.NoAction )
          {
            List<UILayout> windows = Control.GetWindowsUnderPoint( e.Location );
            UILayout selectedWindow = windows.Count > 0 ? windows[0] : null;
            SelectWindow( selectedWindow );
          }

        }
      }
      else
      {
        if ( Math.Abs( WhereLeftMouseDown.X - e.Location.X ) > MOUSE_CLICK_DIST || Math.Abs( WhereLeftMouseDown.Y - e.Location.Y ) > MOUSE_CLICK_DIST )
        {
          ApplyAction();
        }
        else
        {
          List<UILayout> windows = Control.GetWindowsUnderPoint( e.Location );
          UILayout selectedWindow = windows.Count > 0 ? windows[0] : null;
          SelectWindow( selectedWindow );
        }

      }
      CurrentAction = Action.NoAction;
      currentActionWindow = null;
    }


    #region Action

    private void ApplyAction()
    {
    }

    public enum Action
    {
      NoAction,
      Move,
      DragLeft,
      DragBottomLeft,
      DragBottom,
      DragBottomRight,
      DragRight,
      DragTopLeft,
      DragTop,
      DragTopRight,
      ChangeParent,
      Select,
    }

    private Action currentAction = Action.NoAction;

    private Action CurrentAction
    {
      get
      {
        return currentAction;
      }
      set
      {
        currentAction = value;
        Control.SetCursor( GetActionCursor( currentAction ) );
      }
    }

    private void CancelAction()
    {
      CurrentAction = Action.NoAction;
    }

    internal static readonly int DRAG_RECT_SIZE = 7;
    internal static readonly int DRAG_RECT_HALF_SIZE = ( DRAG_RECT_SIZE - DRAG_RECT_SIZE % 2 ) / 2;
    private Action GetActionAtPoint( Point mouse, Rectangle control, bool canMove, bool canResize )
    {
      int leftBound = control.Left + DRAG_RECT_HALF_SIZE - 1;
      int rightBound = control.Right - DRAG_RECT_HALF_SIZE + 1;
      int topBound = control.Top + DRAG_RECT_HALF_SIZE - 1;
      int bottomBound = control.Bottom - DRAG_RECT_HALF_SIZE + 1;

      bool inside = ( mouse.X > leftBound && mouse.X < rightBound && mouse.Y > topBound && mouse.Y < bottomBound );
      if ( inside )
      {
        if ( !canMove )
          return Action.NoAction;

        return Action.Move;
      }

      bool outsize = ( mouse.X < leftBound - DRAG_RECT_SIZE || mouse.X > rightBound + DRAG_RECT_SIZE || mouse.Y < topBound - DRAG_RECT_SIZE || mouse.Y > bottomBound + DRAG_RECT_SIZE );
      if ( outsize )
        return Action.NoAction;

      bool leftEdge = ( mouse.X <= leftBound + DRAG_RECT_HALF_SIZE ) && ( mouse.X >= leftBound - DRAG_RECT_HALF_SIZE ) && canMove && canResize;
      bool rightEdge = ( mouse.X >= rightBound - DRAG_RECT_HALF_SIZE ) && ( mouse.X <= rightBound + DRAG_RECT_HALF_SIZE ) && canResize;
      bool topEdge = ( mouse.Y <= topBound + DRAG_RECT_HALF_SIZE ) && ( mouse.Y >= topBound - DRAG_RECT_HALF_SIZE ) && canMove && canResize;
      bool bottomEdge = ( mouse.Y >= bottomBound - DRAG_RECT_HALF_SIZE ) && ( mouse.Y <= bottomBound + DRAG_RECT_HALF_SIZE ) && canResize;

      if ( topEdge )
      {
        if ( leftEdge )
          return Action.DragTopLeft;
        else if ( rightEdge )
          return Action.DragTopRight;
        else
          return Action.DragTop;
      }
      else if ( bottomEdge )
      {
        if ( leftEdge )
          return Action.DragBottomLeft;
        else if ( rightEdge )
          return Action.DragBottomRight;
        else
          return Action.DragBottom;
      }
      else if ( leftEdge )
        return Action.DragLeft;
      else if ( rightEdge )
        return Action.DragRight;
      else
        return Action.NoAction;
    }

    private Action GetActionAtPoint( Point mouse, out UILayout actionWindow )
    {
      actionWindow = null;
      if ( selectedWindows == null || IsShift || IsControl )
      {
        return Action.NoAction;
      }
      List<UILayout> windows = Control.GetWindowsUnderPoint( mouse );
      if ( windows.Count == 0 )
        return Action.NoAction;

      List<UILayout> topWindowParents = new List<UILayout>();
      UILayout parent = Control.GetWindowParent( windows[0] );
      while ( parent != null )
      {
        topWindowParents.Add( parent );
        parent = Control.GetWindowParent( parent );
      }

      for ( int i = 0; i < selectedWindows.Count; i++ )
      {
        if ( windows.Contains( selectedWindows[i] ) )
        {
          Action ma = GetActionAtPoint( mouse, Control.GetWindowRectangle( selectedWindows[i] ), true, true );
          if ( ma != Action.NoAction )
          {
            actionWindow = selectedWindows[i];
            return ma;
          }
        }
      }
      return Action.NoAction;
    }

    private static Cursor GetActionCursor( Action action )
    {
      switch ( action )
      {
        case Action.ChangeParent:
          return Cursors.IBeam;
        case Action.DragBottom:
        case Action.DragTop:
          return Cursors.SizeNS;
        case Action.DragLeft:
        case Action.DragRight:
          return Cursors.SizeWE;
        case Action.DragTopLeft:
        case Action.DragBottomRight:
          return Cursors.SizeNWSE;
        case Action.DragTopRight:
        case Action.DragBottomLeft:
          return Cursors.SizeNESW;
        case Action.Move:
          return Cursors.SizeAll;
        default:
          return Cursors.Default;
      }
    }

    #endregion
  }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Reflection;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.ToolBox;
using EditorPlugins.UIScene;
using EditorNative;
using EditorPlugins.LayoutEditor.States;
using libdb.DB;
using libdb.Diagnostics;
using Color = System.Drawing.Color;

namespace EditorPlugins.LayoutEditor
{
  public partial class LayoutEditorControl : Editor2DSceneControl
  {
    #region Private members

    private const int DRAG_RECT_SIZE = 5;

    public LayoutEditorStatusPanel editorStatusPanel = null;
    private IEditorWinApplication application = null;

    private EditorUIScene scene = null;
    protected override Editor2DSceneBase Scene { get { return scene; } }

    private LayoutEditorSnapper snapper = null;

    private int newLayoutCounter = 1;

    #endregion

    #region Basic functionality (constructor, Application, active state etc)

    public LayoutEditorControl()
    {
      scene = new EditorUIScene( Handle );
			
      SelectionColor1 = SelectionColor1;
      SelectionColor2 = SelectionColor2;
      ParentColor = ParentColor;

      InitializeComponent();

      UpdateCanvas();
    }

    public IEditorWinApplication EditorApplication { get { return application; } }

    public void SetApplication( IEditorWinApplication application )
    {
      this.application = application;
      snapper = new LayoutEditorSnapper( scene );

      activeState = new DefaultState( this );
    }

    public void OnActivate()
    {
      ActiveState = ActiveState;
    }

		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose( bool disposing )
		{
			if ( disposing && ( components != null ) )
			{
				components.Dispose();
			}

			if ( scene != null )
			{
				scene.Dispose();
				scene = null;
			}

			base.Dispose( disposing );
		}


    private LayoutEditorState activeState = null;
    internal LayoutEditorState ActiveState
    {
      set
      {
        if ( activeState != null )
          activeState.OnLeaveState( value );
        value.OnEnterState( activeState );
        activeState = value;
      }
      get
      {
        return activeState;
      }
    }

    protected override void OnPaint( PaintEventArgs e )
    {
      base.OnPaint( e );
      if ( ActiveState != null )
        ActiveState.OnPaint( this );
      if ( snapper != null )
        snapper.OnPaint( e );
    }

    #endregion

    #region Basic layout management

    private UILayout rootLayout = null;

    public UILayout RootLayout
    {
      get { return rootLayout; }
      set
      {
        if ( value != null && !value.DBId.IsEmpty && rootLayout != value )
        {
          rootLayout = value;
          scene.LoadLayout( rootLayout.DBId, rootLayout.GetStateName() );
          ActiveState = new DefaultState( this );
          UpdateCanvas();
          Width = rootLayout.size.x;
          Height = rootLayout.size.y;
          Invalidate();
        }
      }
    }

    private void UpdateCanvas()
    {
      if ( null != rootLayout )
        CanvasSize = new System.Drawing.Size( rootLayout.size.x, rootLayout.size.y );
    }

    public void SelectWindow( UILayout win )
    {
      if ( win != null )
      {
        List<UILayout> newSelection = new List<UILayout>();
        newSelection.Add( win );
        SetSelection( newSelection );
      }
      else
        SetSelection( null );
    }

    internal void SetSelection( List<UILayout> selectedWindows )
    {
      if ( selectedWindows != null && selectedWindows.Count > 0 )
        ActiveState = new SelectedState( this, selectedWindows );
      else
        ActiveState = new DefaultState( this );
      Invalidate();
    }

    public void ShowContextMenu( Control ctrl, Point at )
    {
      if ( ActiveState != null )
      {
        ActiveState.ShowContextMenu( ctrl, at );
      }
      else
      {
        Log.TraceError( "LayoutEditorControl doesn't have an active state" );
      }
      Invalidate();
    }

    internal Rectangle GetWindowRectangle( UILayout window )
    {
      return scene.GetWindowScreenPosition( window.DBId );
    }

    internal UILayout GetWindowParent( UILayout window )
    {
      DBID parentDBID = scene.GetWindowParent( window.DBId );

      if ( null == parentDBID )
        return null;

      return DataBase.Get<UILayout>( parentDBID ).Get();
    }

    internal List<UILayout> GetWindowsUnderPoint( Point point )
    {
      List<DBID> windows = scene.PickWindows( point.X, point.Y );
      List<UILayout> result = new List<UILayout>();
      foreach ( DBID windowDBID in windows )
      {
        // Remove selectability of external inlines
        if ( windowDBID.IsInlined && windowDBID.FileName != RootLayout.DBId.FileName )
          continue;

        DBPtr<UILayout> ptr = DataBase.Get<UILayout>( windowDBID );
        if ( ptr.IsValid )
          result.Add( ptr.Get( scene.GetState( windowDBID  ) ) );
      }
      return result;
    }

    internal List<UILayout> GetWindowsInRect( Rectangle rect )
    {
      List<DBID> windows = scene.PickWindows( rect );
      List<UILayout> result = new List<UILayout>();
      foreach ( DBID windowDBID in windows )
      {
        // Remove selectability of external inlines
        if ( windowDBID.IsInlined && windowDBID.FileName != RootLayout.DBId.FileName )
          continue;

        DBPtr<UILayout> ptr = DataBase.Get<UILayout>( windowDBID );
        if ( ptr.IsValid )
          result.Add( ptr.Get( scene.GetState( windowDBID ) ) );
      }
      return result;
    }

    #endregion

    #region Layout editing

    private void OnStructuralChanges()
    {
      scene.LoadLayout( rootLayout.DBId, rootLayout.GetStateName() );
    }

    public void NewWindow( object tag )
    {
      if ( null == tag && ActiveState is NewWindowState )
      {
        ActiveState = new DefaultState( this );
        return;
      }

      Type type = tag as Type;
      if ( type != null )
        ActiveState = new NewWindowState( this, type );

      DBID templateDBID = tag as DBID;
      if ( templateDBID != null && !templateDBID.IsInlined )
      {
        DBPtr<UILayout> resPtr = DataBase.Get<UILayout>( templateDBID );
        if ( resPtr.IsValid )
        {
          ActiveState = new NewWindowState( this, resPtr.Get() );
        }
      }
    }

    internal bool CanAttachToParent( UILayout window, UILayout parent )
    {
      if ( null == parent || null == window || null == GetWindowParent( window ) )
        return false;

      UILayout cur = parent;
      while ( cur != null )
      {
        if ( cur.DBId.Equals( window.DBId ) )
          return false;
        cur = GetWindowParent( cur );
      }

      foreach ( DBPtr<UILayout> child in window.subLayouts )
      {
        if ( !CanAttachToParent( child.Get(), parent ) )
          return false;
      }

      return true;
    }

    internal void ChangeParent( List<UILayout> selectedWindows, int atIndex, UILayout newParent )
    {
      bool isCanChange = true;
      for ( int i = 0; i < selectedWindows.Count && isCanChange; ++i )
      {
        if ( !CanAttachToParent( selectedWindows[i], newParent ) || selectedWindows[i] == rootLayout )
        {
          isCanChange = false;
        }
      }
      if ( !isCanChange )
        return;

      List<int> parentPath = new List<int>();
      if ( !FindChildPath( rootLayout, newParent, parentPath ) )
        return;

      application.Application.UndoRedo.Start( "Change Parent" );

      for ( int i = 0; i < selectedWindows.Count; ++i )
      {
        List<int> oldPath = new List<int>();
        if ( !FindChildPath( rootLayout, selectedWindows[i], oldPath ) )
          continue;
        if ( oldPath.Count == 0 )
          continue;

        int oldIndex = oldPath[oldPath.Count - 1];
        oldPath.RemoveAt( oldPath.Count - 1 );

        RelocateChildInAllStates( oldPath, oldIndex, parentPath, atIndex );
      }
      application.Application.UndoRedo.Commit();
      OnStructuralChanges();

      SetSelection( selectedWindows );

    }

    private void RelocateChildInAllStates( List<int> oldParentPath, int oldIndex, List<int> parentPath, int atIndex )
    {
      DBPtr<UILayout> rootPtr = DataBase.Get<UILayout>( rootLayout.DBId );
      List<string> states = rootPtr.GetStates();
      states[0] = states[states.Count - 1];
      states[states.Count - 1] = "";
      foreach ( string stateName in states )
      {
        UILayout rootInState = rootPtr.Get( stateName );

        RelocateChildByPath( rootInState, oldParentPath, oldIndex, parentPath, atIndex );
      }
    }

    private void RelocateChildByPath( UILayout rootInState, List<int> oldParentPath, int oldIndex, List<int> parentPath, int atIndex )
    {
      UILayout oldParent = GetLayoutByPath( rootInState, oldParentPath );
      if ( null == oldParent || oldIndex >= oldParent.subLayouts.Count )
        return;

      UILayout newParent = GetLayoutByPath( rootInState, parentPath );
      if ( null == newParent )
        return;

      DBPtr<UILayout> childPtr = oldParent.subLayouts[oldIndex];
      UILayout child = childPtr.Get();
      Rectangle newParentBounds = GetWindowRectangle( newParent );
      Rectangle oldParentBounds = GetWindowRectangle( oldParent );
      if ( !child.__parent.IsValid || !child.location.IsDerivedFromParent() )  // leave inherited coordinates alone
      {
        child.location.x += oldParentBounds.X - newParentBounds.X;
        child.location.y += oldParentBounds.Y - newParentBounds.Y;
      }
      oldParent.subLayouts.RemoveAt( oldIndex );
      if ( atIndex >= 0 )
      {
        bool replaceInherited = false;      // This one is for when the base state has already placed a child here (ant it has been inherited)
        if ( newParent.subLayouts.Count > atIndex )
        {
          if ( newParent.subLayouts[atIndex].Get() == child.__parent.Get() )
            replaceInherited = true;
        }
        if ( replaceInherited )
          newParent.subLayouts[atIndex] = childPtr;
        else
          newParent.subLayouts.Insert( atIndex, childPtr );
      }
      else
      {
        bool replaceInherited = false;      // This one is for when the base state has already placed a child here (ant it has been inherited)
        if ( newParent.subLayouts.Count > 0 && newParent.subLayouts.IsElementDerivedFromParent( newParent.subLayouts.Count - 1 ) )
        {
          if ( newParent.subLayouts[newParent.subLayouts.Count - 1].Get() == child.__parent.Get() )
            replaceInherited = true;
        }

        if ( replaceInherited )
          newParent.subLayouts[newParent.subLayouts.Count - 1] = childPtr;
        else
          newParent.subLayouts.Add( childPtr );
      }
    }

    internal void Delete( List<UILayout> selectedWindows )
    {
      if ( selectedWindows.Count == 1 && GetWindowParent( selectedWindows[0] ) != null )
        SetSelection( new List<UILayout> { GetWindowParent( selectedWindows[0] ) } );
      else
        SetSelection( null );

      application.Application.UndoRedo.Start( "DeleteWindows" );
      foreach ( UILayout item in selectedWindows )
      {
        DeleteChildInAllStates( item );
      }
      application.Application.UndoRedo.Commit();
      OnStructuralChanges();
    }

    private void DeleteChildInAllStates( UILayout layout )
    {
      List<int> path = new List<int>();

      if ( !FindChildPath( rootLayout, layout, path ) )
        return;

      if ( path.Count == 0 )
        return;

      int lastIndex = path[path.Count - 1];
      path.RemoveAt( path.Count - 1 );

      DBPtr<UILayout> rootPtr = DataBase.Get<UILayout>( rootLayout.DBId );
      List<string> states = rootPtr.GetStates();
      foreach ( string stateName in states )
      {
        UILayout rootInState = rootPtr.Get( stateName );

        UILayout parent = GetLayoutByPath( rootInState, path );
        if ( null == parent )
          continue;

        parent.subLayouts.RemoveAt( lastIndex );
      }
    }

    private UILayout GetLayoutByPath( UILayout fromRoot, List<int> path )
    {
      UILayout targetLayout = fromRoot;
      for ( int i = 0; i < path.Count; ++i )
      {
        if ( null == targetLayout || targetLayout.subLayouts.Count <= path[i] )
          return null;

        targetLayout = targetLayout.subLayouts[path[i]].Get();
      }
      return targetLayout;
    }

    private bool FindChildPath( UILayout parent, UILayout child, List<int> path )
    {
      if ( null == parent || null == child )
        return false;

      if ( parent == child )
        return true;

      path.Add( -1 );
      for ( int i = 0; i < parent.subLayouts.Count; ++i )
      {
        path[path.Count - 1] = i;
        if ( FindChildPath( parent.subLayouts[i].Get(), child, path ) )
          return true;
      }
      path.RemoveAt( path.Count - 1 );

      return false;
    }

    internal void PasteWindows( List<UILayout> copiedWindows, UILayout parent )
    {
      List<UILayout> newWindows = new List<UILayout>();

      List<int> path = new List<int>();
      if ( !FindChildPath( rootLayout, parent, path ) )
        return;

      application.Application.UndoRedo.Start( "Paste Windows" );
      foreach ( UILayout window in copiedWindows )
      {
        if ( DBID.IsNullOrEmpty( window.DBId ) )
          continue;

        DBPtr<UILayout> newLayout = null;
        DBID dbid = DBID.FromDBID( parent.DBId, true );
        DataBase.Copy( dbid, window.DBId );
        newLayout = DataBase.Get<DBTypes.UILayout>( dbid );

        UILayout toSelect = AddChildByPath( newLayout, path );

        newWindows.Add( toSelect );
      }
      application.Application.UndoRedo.Commit();
      OnStructuralChanges();
      SetSelection( newWindows );
    }

    internal UILayout CreateWindow( Type windowType, UILayout parent, Rectangle rect )
    {
      if ( null == windowType || null == parent )
        return null;

      ConstructorInfo constructor = windowType.GetConstructor( new Type[0] { } );
      if ( null == constructor )
        return null;

      List<int> path = new List<int>();
      if ( !FindChildPath( rootLayout, parent, path ) )
        return null;

      application.Application.UndoRedo.Start( "Create Window" );
      Rectangle normRect = NormalizeRectangle( rect );
      Rectangle parentBounds = GetWindowRectangle( parent );

      UILayout newLayout = (DBTypes.UILayout)constructor.Invoke( new object[0] { } );
      newLayout.location.x = normRect.X - parentBounds.X;
      newLayout.location.y = normRect.Y - parentBounds.Y;
      newLayout.size.x = normRect.Width;
      newLayout.size.y = normRect.Height;
      newLayout.name = "New " + newLayout.GetType().Name + newLayoutCounter;
      ++newLayoutCounter;

      UILayout toSelect = AddChildByPath( newLayout, path );

      application.Application.UndoRedo.Commit();
      OnStructuralChanges();

      SelectWindow( toSelect );

      ToolBoxPanel toolBoxPanel = EditorApplication.Panels.GetSingletonPanel<ToolBoxPanel>();
      toolBoxPanel.UpdateRecentlyUsed();

      return newLayout;
    }

    private UILayout AddChildByPath( UILayout newLayout, List<int> path )
    {
      DBPtr<UILayout> newResource = DataBase.Create<UILayout>( DBID.FromDBID( rootLayout.DBId, true ), newLayout );
      DBPtr<UILayout> rootPtr = DataBase.Get<UILayout>( rootLayout.DBId );


      UILayout targetParent = GetLayoutByPath( rootPtr.Get(), path );
      if ( null == targetParent )
        return null;
      targetParent.subLayouts.Add( newResource );

      path.Add( targetParent.subLayouts.Count - 1 );

      UILayout result = null;
      if ( rootLayout.GetStateName() == string.Empty )
        result = newLayout;

      // Add snot
      List<string> states = rootPtr.GetStates();
      foreach ( string stateName in states )
      {
        if ( stateName == string.Empty )
          continue;

        UILayout snotItem = AddSnotByPath( rootPtr.Get( stateName ), path );
        if ( stateName == rootLayout.GetStateName() )
          result = snotItem;
      }

      return result;
    }

    private UILayout AddSnotByPath( UILayout root, List<int> path )
    {
      if ( null == root || null == path || path.Count == 0 )
        return null;

      UILayout targetParent = root;
      for ( int i = 0; i < path.Count - 1; ++i )
      {
        if ( null == targetParent || targetParent.subLayouts.Count <= path[i] )
          return null;

        targetParent = targetParent.subLayouts[path[i]].Get();
      }
      DBPtr<UILayout> childPtr = targetParent.subLayouts[path[path.Count - 1]];

      Type itemType = childPtr.Get().GetType();
      UILayout newChild = TypeUtils.CreateObject( itemType ) as UILayout;

      DBPtr<UILayout> newChildPtr = DataBase.Create<UILayout>( DBID.FromDBID( rootLayout.DBId, true ), newChild );
      newChild = newChildPtr.Get();
      newChild.SetParent( childPtr.Get() );
      childPtr.Set( newChildPtr );

      return newChild;
    }

    internal void CreateWindowFromPrototype( UILayout prototype, UILayout parent, Rectangle rect )
    {
      if ( prototype == null || parent == null )
      {
        SetSelection( null );
        return;
      }

      //Check for potential cycle
      UILayout parentWalker = parent;
      while ( parentWalker != null )
      {
        if ( parentWalker == prototype )
        {
          Log.TraceWarning( "Unable to create cyclic reference by cloning a window into itself." );
          SetSelection( null );
          return;
        }

        parentWalker = GetWindowParent( parentWalker );
      }

      application.Application.UndoRedo.Start( "Create Window" );

      UILayout created = CreateWindow( prototype.GetType(), parent, rect );

      Rectangle normRect = NormalizeRectangle( rect );
      Rectangle parentBounds = GetWindowRectangle( parent );
      created.SetParent( prototype );
      created.Reset();
      created.location.x = normRect.X - parentBounds.X;
      created.location.y = normRect.Y - parentBounds.Y;
      created.size.x = normRect.Width;
      created.size.y = normRect.Height;
      created.name = "New " + created.GetType().Name + newLayoutCounter;
      ++newLayoutCounter;

      application.Application.UndoRedo.Commit();
      OnStructuralChanges();
    }

    #endregion

    #region Public properties and respective private members

    private Color backColor1 = Color.LightGray;
    private Color backColor2 = Color.White;
    private int backGridSize = 8;
    private Color selectionColor1 = Color.FromKnownColor( KnownColor.Highlight );
    private Pen selectionPen1 = null;
    internal Pen SelectionPen1 { get { return selectionPen1; } }
    private Color parentColor = Color.FromKnownColor( KnownColor.Red );
    private Pen parentPen = null;
    private Brush selectionBrush1 = null;
    private Color selectionColor2 = Color.White;
    private Pen selectionPen2 = null;
    private Brush selectionBrush2 = null;

    [Category( "Appearance" )]
    public Color BackColor1 { get { return backColor1; } set { backColor1 = value; } }
    [Category( "Appearance" )]
    public Color BackColor2 { get { return backColor2; } set { backColor2 = value; } }
    [Category( "Appearance" )]
    public int BackGridSize { get { return backGridSize; } set { backGridSize = value; } }
    [Category( "Appearance" )]
    public Color ParentColor { get { return parentColor; } set { parentColor = value; parentPen = new Pen( parentColor, 1.0f ); Invalidate(); } }
    [Category( "Appearance" )]
    public Color SelectionColor1 { get { return selectionColor1; } set { selectionColor1 = value; selectionPen1 = new Pen( SelectionColor1, 1.0f ); selectionBrush1 = new SolidBrush( SelectionColor1 ); Invalidate(); } }
    [Category( "Appearance" )]
    public Color SelectionColor2 { get { return selectionColor2; } set { selectionColor2 = value; selectionPen2 = new Pen( SelectionColor2, 1.0f ); selectionPen2.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot; selectionBrush2 = new SolidBrush( SelectionColor2 ); Invalidate(); } }

    public Size CanvasSize 
    { 
      get 
      { 
        return new Size( rootLayout.size.x, rootLayout.size.y ); 
      } 
      set 
      { 
        Width = value.Width + DRAG_RECT_SIZE + 3; 
        Height = value.Height + DRAG_RECT_SIZE + 3; 
      } 
    }

    #endregion

    #region Binds support for mouse and keyboard

    protected override void OnKeyDown( KeyEventArgs e )
    {
      base.OnKeyDown( e );
      if ( ActiveState != null )
        ActiveState.OnKeyDown( e );
      e.Handled = true;
    }

    protected override void OnKeyUp( KeyEventArgs e )
    {
      base.OnKeyUp( e );
      if ( ActiveState != null )
        ActiveState.OnKeyUp( e );
      e.Handled = true;
    }

    protected override void OnMouseDown( MouseEventArgs e )
    {
      base.OnMouseDown( e );
      if ( ActiveState != null )
        ActiveState.OnMouseDown( e );
      Focus();
    }

    protected override void OnMouseUp( MouseEventArgs e )
    {
      base.OnMouseUp( e );
      if ( ActiveState != null )
        ActiveState.OnMouseUp( e );
    }

    protected override void OnMouseMove( MouseEventArgs e )
    {
      base.OnMouseMove( e );
      if ( ActiveState != null )
        ActiveState.OnMouseMove( e );
    }

    protected override bool IsInputKey( Keys keyData )
    {
      if ( keyData == Keys.Up || keyData == Keys.Down || keyData == Keys.Right || keyData == Keys.Left || keyData == Keys.Tab ||
       keyData == Keys.Menu || keyData == Keys.ShiftKey || keyData == Keys.ControlKey )
        return true;
      else
        return base.IsInputKey( keyData );
    }

    #endregion

    internal void SetCursor( Cursor _cursor )
    {
      Cursor = _cursor;
    }

    internal LayoutEditorSnapper Snapper { get { return snapper; } }

    public static Rectangle NormalizeRectangle( Rectangle rectangle )
    {
      Rectangle rez = new Rectangle( rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height );
      if ( rez.Height < 0 )
      {
        rez.Y += rez.Height;
        rez.Height = -rez.Height;
      }
      if ( rez.Width < 0 )
      {
        rez.X += rez.Width;
        rez.Width = -rez.Width;
      }
      return rez;
    }

    internal void SetWindowVisible( UILayout win, bool visible )
    {
      scene.SetVisible( win.DBId, visible );
    }
  }
}

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Panels;
using libdb.DB;
using libdb.Diagnostics;
using Win32;


namespace EditorPlugins.LayoutEditor
{
  public partial class LayoutTreeView : EditorPanel
  {
    private struct DragInfo
    {
      public bool drawDragLine;
      public int dragLineY;
      public int dragLineLeftX;
      public int dragLineRightX;
      public TreeNode lastPickedNode;
      public System.Drawing.Color lastPickedBackColor;
      
      public DragInfo( bool drawDragLine )
      {
        this.drawDragLine = drawDragLine;
        dragLineY = -1;
        dragLineLeftX = -1;
        dragLineRightX = -1;
        lastPickedNode = null;
        lastPickedBackColor = System.Drawing.Color.White;
      }
    };

    private class ContextElement
    {
      public bool IsExpanded = true;
      public bool IsVisible = true;
      public ContextElement( bool _IsExpanded, bool _IsVisible ) { IsExpanded = _IsExpanded; IsVisible = _IsVisible; }
    }

    private class Context
    {
      public Dictionary<DBID, ContextElement> elements = new Dictionary<DBID, ContextElement>();
    }

    private DragInfo dragInfo;
    private UILayout RootElement;
    private Dictionary<UILayout, TreeNode> flatMap = new Dictionary<UILayout, TreeNode>();
    private Dictionary<UILayout, Context> contexts = new Dictionary<UILayout, Context>();
    private Context context = null;
    
    private UILayout selectedLayout = null;

    private Brush bgBrush = new SolidBrush( System.Drawing.Color.FromKnownColor( KnownColor.Highlight ) );
    private Brush fgBrush = new SolidBrush( System.Drawing.Color.FromKnownColor( KnownColor.WindowText ) );
    private Brush fgBrushSelected = new SolidBrush( System.Drawing.Color.FromKnownColor( KnownColor.HighlightText ) );

    public LayoutTreeView()
    {
      InitializeComponent();
    }

    protected override bool Initialize( IEditorWinApplication application )
    {
      DataBase.ChangeDBResourceEvent += OnDBChange;
      return true;
    }

    public override void Terminate( IEditorWinApplication application )
    {
      DataBase.ChangeDBResourceEvent -= OnDBChange;
    }

    private void OnDBChange( DBID dbid )
    {
      if ( null == RootElement )
        return;

      if ( context != null && context.elements.ContainsKey( dbid ) )
        RefreshList();
    }

    private TreeNode CreateTreeNode( UILayout layout )
    {
      TreeNode newNode = new TreeNode( layout.name + "    " );
      newNode.Tag = layout;
      newNode.Name = layout.DBId.ToString();
      newNode.ToolTipText = layout.GetType().Name;
      newNode.Checked = layout.visible;
      if ( context != null )
      {
        ContextElement desc = null;
        if ( !context.elements.TryGetValue( layout.DBId, out desc ) )
        {
          desc = new ContextElement( true, layout.visible );
          context.elements[layout.DBId] = desc;
        }
        newNode.Checked = desc.IsVisible;

        if ( SetWindowVisibleEvent != null && newNode.Checked != layout.visible )
          SetWindowVisibleEvent( layout, newNode.Checked );

        if ( desc.IsExpanded )
          newNode.Expand();
        else
          newNode.Collapse();
      }
      return newNode;
    }

    private void ProcessChildren( TreeNode parent )
    {
      UILayout layout = parent.Tag as UILayout;
      if ( null == layout )
        return;

      foreach ( DBPtr<UILayout> child in layout.subLayouts )
      {
        if ( child == null )
          continue;

        UILayout childLayout = child.Get();
        if ( childLayout == null )
          continue;

        if ( child.DBId.IsInlined && child.DBId.FileName != RootElement.DBId.FileName )
          continue;

        TreeNode newNode = CreateTreeNode( childLayout );
        parent.Nodes.Add( newNode );
        if ( !flatMap.ContainsKey( childLayout ) )
          flatMap.Add( childLayout, newNode );

        ProcessChildren( newNode );
      }
    }

    private void RefreshList()
    {
      if ( RootElement == null )
      {
        layoutTree.Nodes.Clear();
        flatMap.Clear();
        context = null;
        return;
      }

      if ( !contexts.TryGetValue( RootElement, out context ) )
      {
        context = new Context();
        contexts[RootElement] = context;
      }

      Dictionary<UILayout, TreeNode> oldMap = flatMap;
      flatMap = new Dictionary<UILayout, TreeNode>();

      TreeNode newRoot = CreateTreeNode( RootElement );
      flatMap.Add( RootElement, newRoot );
      ProcessChildren( newRoot );

      List<DBID> toRemoveElements = new List<DBID>();
      foreach ( DBID item in context.elements.Keys )
      {
        bool found = false;
        foreach ( UILayout layout in flatMap.Keys )
        {
          if ( layout.DBId == item )
          {
            found = true;
            break;
          }
        }
        if ( !found )
          toRemoveElements.Add( item );
      }
      foreach ( DBID item in toRemoveElements )
        context.elements.Remove( item );

      layoutTree.BeginUpdate();
      layoutTree.Nodes.Clear();
      layoutTree.Nodes.Add( newRoot );
      layoutTree.EndUpdate();

      if ( selectedLayout != null )
      {
        if ( layoutTree.Nodes.Find( selectedLayout.DBId.ToString(), true ).Length > 0 )
          SetSelectedLayout( selectedLayout );
        else
          SetSelectedLayout( null );
      }
    }

    #region layoutTree mouse and keyboard processors

    private void layoutTree_MouseUp( object sender, MouseEventArgs e )
    {
      if ( e.Button == MouseButtons.Right )
      {
        TreeNode dstNode = layoutTree.GetNodeAt( ( new Point( e.X, e.Y ) ) );
        UILayout dstWnd = dstNode != null ? dstNode.Tag as UILayout : null;
        if ( dstWnd != null )
        {
          if ( ChangeSelectionEvent != null )
            ChangeSelectionEvent( dstWnd );
          if ( ShowContextMenuEvent != null )
            ShowContextMenuEvent( this, new Point( e.X, e.Y ) );
        }
      }
    }

    private void layoutTree_NodeMouseDoubleClick( object sender, TreeNodeMouseClickEventArgs e )
    {
      if ( e.Button == MouseButtons.Left )
      {
        TreeNode dstNode = layoutTree.GetNodeAt( ( new Point( e.X, e.Y ) ) );
        UILayout dstWnd = dstNode != null ? dstNode.Tag as UILayout : null;
        if ( dstWnd != null )
        {
          layoutTree.LabelEdit = true;
          dstNode.BeginEdit();
        }
      }
    }

    #endregion

    #region layoutTree drag-n-drop support

    private TreeNode GetDragDropNode( Point pt )
    {
      TreeNode node = layoutTree.GetNodeAt( pt );
      if ( node != null )
        return node;

      //TODO: actualy I have no ideas how this code works, because GetEnumerator().Current should throw a exception
      TreeNode first = layoutTree.Nodes.GetEnumerator().Current as TreeNode;
      if ( first == null )
        return null;

      if ( pt.Y > first.LastNode.Bounds.Y + first.LastNode.Bounds.Size.Height )
        return first.LastNode;
      else if ( pt.Y < first.FirstNode.Bounds.Y )
        return first.FirstNode;

      return null;
    }

    private UILayout GetParentFromTree( UILayout window )
    {
      if ( null == window || !flatMap.ContainsKey( window ) )
        return null;

      if ( null == flatMap[window].Parent )
        return null;

      return flatMap[window].Parent.Tag as UILayout;
    }

    private void layoutTree_ItemDrag( object sender, ItemDragEventArgs e )
    {
      layoutTree.DoDragDrop( e.Item as TreeNode, DragDropEffects.All );
    }

    private bool CanAttachToParent( UILayout window, UILayout parent )
    {
      if ( null == parent || null == window )

      if ( null == GetParentFromTree( window ) && ( null == window.__parent || window.__parent.DBId == window.DBId ) )
        return false;

      UILayout cur = parent;
      while ( cur != null )
      {
        if ( cur.DBId.Equals( window.DBId ) )
          return false;
        cur = GetParentFromTree( cur );
      }

      foreach ( DBPtr<UILayout> child in window.subLayouts )
      {
        if ( !CanAttachToParent( child.Get(), parent ) )
          return false;
      }

      return true;
    }

    private void layoutTree_DragOver( object sender, DragEventArgs e )
    {
      if ( layoutTree.Nodes.Count == 0 )
        return;

      Point pt = PointToClient( new Point( e.X, e.Y ) );
      TreeNode dstNode = GetDragDropNode( pt );
      TreeNode srcNode = e.Data.GetData( typeof( TreeNode ) ) as TreeNode;
      UILayout dstWin = ( dstNode != null ) ? dstNode.Tag as UILayout : null;
      UILayout srcWin = ( srcNode != null ) ? srcNode.Tag as UILayout : null;
      if ( dstWin != null && srcWin != null && dstWin != srcWin )
      {
        float d = (float)( Math.Abs( dstNode.Bounds.Y - pt.Y ) ) / dstNode.Bounds.Size.Height;
        bool inNodeBottom = d <= 1.0f && d > 0.5f;
        bool controlPressed = ( ( User.GetKeyState( User.VK_CONTROL ) >> 15 ) > 0 );
        if ( ( ( inNodeBottom && !controlPressed ) || dstNode.Parent == null ) && CanAttachToParent( srcWin, dstWin ) )
        {
          if ( dstNode.BackColor != System.Drawing.Color.LightGray )
          {
            dragInfo.lastPickedBackColor = dstNode.BackColor;
            dstNode.BackColor = System.Drawing.Color.LightGray;
          }
          e.Effect = DragDropEffects.Copy;
          dragInfo.drawDragLine = false;
        }
        else if ( CanAttachToParent( srcWin, GetParentFromTree( dstWin ) ) )
        {
          dstNode.BackColor = dragInfo.lastPickedBackColor;
          e.Effect = DragDropEffects.Move;
          dragInfo.dragLineY = dstNode.Bounds.Y; // +dstNode.Bounds.Size.Height;
          dragInfo.dragLineLeftX = dstNode.Bounds.X;
          dragInfo.dragLineRightX = dstNode.Bounds.X + dstNode.Bounds.Size.Width;
          if ( dragInfo.drawDragLine == false )
            layoutTree.Invalidate();
          dragInfo.drawDragLine = true;
        }
        else
        {
          e.Effect = DragDropEffects.None;
          dragInfo.drawDragLine = false;
        }
      }
      else
      {
        e.Effect = DragDropEffects.None;
        dragInfo.drawDragLine = false;
      }
      if ( dragInfo.lastPickedNode != null && dragInfo.lastPickedNode != dstNode )
      {
        dragInfo.lastPickedNode.BackColor = dragInfo.lastPickedBackColor;
        layoutTree.Invalidate();
      }
      dragInfo.lastPickedNode = dstNode;
    }

    private void layoutTree_DragLeave( object sender, EventArgs e )
    {
      dragInfo.drawDragLine = false;
      if ( dragInfo.lastPickedNode != null )
        dragInfo.lastPickedNode.BackColor = dragInfo.lastPickedBackColor;
      layoutTree.Invalidate();
    }

    private void layoutTree_DragDrop( object sender, DragEventArgs e )
    {
      if ( layoutTree.Nodes.Count == 0 )
        return;

      dragInfo.drawDragLine = false;
      if ( dragInfo.lastPickedNode != null )
        dragInfo.lastPickedNode.BackColor = dragInfo.lastPickedBackColor;

      TreeNode dstNode = GetDragDropNode( PointToClient( new Point( e.X, e.Y ) ) );

      if ( dstNode != null )
      {
        if ( dragInfo.lastPickedNode != null )
          dstNode.BackColor = dragInfo.lastPickedBackColor;

        TreeNode srcNode = e.Data.GetData( typeof( TreeNode ) ) as TreeNode;
        if ( srcNode == null )
          return;

        UILayout dstWin = dstNode.Tag as UILayout;
        UILayout srcWin = srcNode.Tag as UILayout;

        if ( e.Effect == DragDropEffects.Copy )
          ChangeParentEvent( srcWin, -1, dstWin );
        else if ( e.Effect == DragDropEffects.Move && dstWin != srcWin )
          ChangeParentEvent( srcWin, dstNode.Index, GetParentFromTree( dstWin ) );
      }
      RefreshList();
      layoutTree.Invalidate();
    }

    #endregion

    private void layoutTree_DrawNode( object sender, DrawTreeNodeEventArgs e )
    {
      bool isSelected = e.Node.IsSelected;

      UILayout layout = e.Node.Tag as UILayout;
      bool isOutlined = false;
      if ( layout != null )
      {
        if ( !layout.DBId.IsInlined )
          isOutlined = true;
        else
        {
          UILayout parent = layout.__parent.Get();
          if ( parent != null )
          {
            if ( !parent.DBId.IsInlined )
              isOutlined = true;
            else if ( parent.DBId.FileName == layout.DBId.FileName )
            {
              UILayout parent2 = parent.__parent.Get();
              if ( parent2 != null && !parent2.DBId.IsInlined )
                isOutlined = true;
            }
          }
        }
      }
      Font font = Font;
      if ( isOutlined )
        font = new Font( Font, FontStyle.Italic );
      
      Rectangle bounds = e.Node.Bounds;
      bounds.Width = (int)e.Graphics.MeasureString( e.Node.Text.Trim(), font ).Width + 6;
      if ( bounds.Width < e.Node.Bounds.Width )
        bounds.Width = e.Node.Bounds.Width;
      if ( ( ( e.State & TreeNodeStates.Selected ) == TreeNodeStates.Selected ) && !layoutTree.Focused )
      {
        e.Graphics.FillRectangle( bgBrush, bounds );
      }

      e.Graphics.DrawString( e.Node.Text, font, isSelected ? fgBrushSelected : fgBrush, bounds );

      if ( dragInfo.drawDragLine )
        e.Graphics.DrawLine( Pens.Black, dragInfo.dragLineLeftX, dragInfo.dragLineY, dragInfo.dragLineRightX, dragInfo.dragLineY );
    }

    public delegate void ChangeSelectionEventHandler( UILayout win );
    public event ChangeSelectionEventHandler ChangeSelectionEvent = null;
    public delegate void ChangeParentEventHandler( UILayout winSrc, int atIndex, UILayout winParent );
    public event ChangeParentEventHandler ChangeParentEvent = null;
    public delegate void ShowContextMenuEventHandler( Control ctrl, Point at );
    public event ShowContextMenuEventHandler ShowContextMenuEvent = null;
    public delegate void SetWindowVisibleEventHandler( UILayout win, bool visible );
    public event SetWindowVisibleEventHandler SetWindowVisibleEvent = null;

    private void layoutTree_AfterSelect( object sender, TreeViewEventArgs e )
    {
      UILayout layout = e.Node.Tag as UILayout;
      if ( layout != null && selectedLayout != layout )
      {
        selectedLayout = layout;
        if ( ChangeSelectionEvent != null )
          ChangeSelectionEvent( layout );
      }
    }

    private void layoutTree_AfterLabelEdit( object sender, NodeLabelEditEventArgs e )
    {
      e.Node.EndEdit( false );
      layoutTree.LabelEdit = false;
      UILayout changed = e.Node.Tag as UILayout;
      if ( changed != null )
      {
        if ( !e.CancelEdit && !string.IsNullOrEmpty( e.Label ) )
          changed.name = e.Label;
      }
    }

    private void layoutTree_AfterCheck( object sender, TreeViewEventArgs e )
    {
      if ( SetWindowVisibleEvent != null )
        SetWindowVisibleEvent( e.Node.Tag as UILayout, e.Node.Checked );

      UILayout layout = e.Node.Tag as UILayout;
      if ( null != layout && null != context )
        context.elements[layout.DBId].IsVisible = e.Node.Checked;

      foreach ( TreeNode n in e.Node.Nodes )
      {
        n.Checked = e.Node.Checked;

        layout = n.Tag as UILayout;
        if ( null == layout || null == context )
          continue;
        context.elements[layout.DBId].IsVisible = e.Node.Checked;
      }
    }

    public void SetSelectedLayout( UILayout value )
    {
      TreeNode node;
      if ( value == null )
      {
        selectedLayout = null;
        layoutTree.SelectedNode = null;
      }
      else if ( flatMap.TryGetValue( value, out node ) && !node.IsSelected )
        layoutTree.SelectedNode = node;
    }

    public void SetRootElement( UILayout root )
    {
      RootElement = root;
      RefreshList();
    }

    internal void OnEditorClosed( UILayout layout )
    {
      List<UILayout> toDelete = new List<UILayout>();
      foreach ( UILayout contextRoot in contexts.Keys )
      {
        if ( layout.DBId == contextRoot.DBId )
          toDelete.Add( contextRoot );
      }
      foreach ( UILayout contextRoot in toDelete )
        contexts.Remove( contextRoot );
    }

    private void layoutTree_AfterExpand( object sender, TreeViewEventArgs e )
    {
      UILayout layout = e.Node.Tag as UILayout;
      if ( null == layout || null == context )
        return;
      context.elements[layout.DBId].IsExpanded = true;
    }

    private void layoutTree_AfterCollapse( object sender, TreeViewEventArgs e )
    {
      UILayout layout = e.Node.Tag as UILayout;
      if ( null == layout || null == context )
        return;
      context.elements[layout.DBId].IsExpanded = false;
    }
  }
}

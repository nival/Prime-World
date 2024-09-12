using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace EditorLib.ToolBox
{
  internal sealed partial class ToolBox : UserControl
  {
    private class ExtendedToolBoxItem
    {
      public bool IsUserItem { get; private set; }
      public ToolBoxItem Item { get; private set; }

      public ExtendedToolBoxItem(ToolBoxItem _item, bool _isUserItem)
      {
        Item = _item;
        IsUserItem = _isUserItem;
      }
    }

    private const int RECENTLY_LIST_SIZE = 10;
    private const string RECENTLY_KEY = "Recently used";

    internal EditorLib.Extensions.AbstractEditor activeEditor = null;

    internal ToolBox()
    {
      InitializeComponent();
      treeView.ImageList = new ImageList
      {
        ColorDepth = ColorDepth.Depth32Bit, 
        ImageSize = new Size( 16, 16 )
      };
    }

    public List<ToolBoxItem> UserItems
    {
      get
      {
        List<ToolBoxItem> result = new List<ToolBoxItem>();

        foreach( TreeNode category in treeView.Nodes )
        {
          if (category.Text == RECENTLY_KEY)
            continue;

          foreach ( TreeNode node in category.Nodes )
          {
            var item = node.Tag as ExtendedToolBoxItem;
            if ( item.IsUserItem )
              result.Add( item.Item );
          }
        }

        return result;
      }
    }

    private TreeNode FindCategory( string category, bool isUserItem )
    {
      foreach ( TreeNode node in treeView.Nodes )
      {
        if ( node.Text == category )
          return node;
      }
      
      TreeNode result = new TreeNode( category )
      {
        //ForeColor = Color.FromKnownColor( KnownColor.InactiveCaptionText ),
        //BackColor = Color.FromKnownColor( KnownColor.InactiveCaption ),
        NodeFont = new Font( treeView.Font, FontStyle.Bold ),
        Tag = new ExtendedToolBoxItem( null, isUserItem )
      };

      treeView.Nodes.Add( result );
      return result;
    }

    internal void AddItem( ToolBoxItem item, bool isUserItem )
    {
      TreeNode node = FindCategory(item.category, false).Nodes.Add(item.name, item.name);
      node.Tag = new ExtendedToolBoxItem(item, isUserItem);

      if ( item.image != null )
      {
        treeView.ImageList.Images.Add( item.category + "." + item.name, item.image );
        node.ImageKey = node.SelectedImageKey = item.category + "." + item.name;
      }
    }

    internal void Clear()
    {
      treeView.Nodes.Clear();
      treeView.Nodes.Add("[Pointer]").Tag = new ExtendedToolBoxItem(null, false);  

      if(treeView.ImageList != null)
      {
        treeView.ImageList.Images.Clear();
        treeView.ImageList.Images.Add(string.Empty, new Bitmap(16, 16));  
      }
    }

    //internal void SelectNull()
    //{
    //  treeView.SelectedNode = treeView.Nodes[0];
    //}

    internal event Operation<object> ItemSelected;
    public event Operation<object> ItemAddClicked;

    #region DragDrop

    private void OnTreeViewItemDrag( object sender, ItemDragEventArgs e )
    {
      if ( e.Button != MouseButtons.Left )
        return;

      TreeNode node = e.Item as TreeNode;
      
      if(IsRecentlyUsedNode(node))
        return;

      var tag = node.Tag as ExtendedToolBoxItem;
      if ( tag.IsUserItem && tag.Item != null)
        DoDragDrop( node, DragDropEffects.Move );
    }

    private void OnTreeViewDragOver( object sender, DragEventArgs e )
    {
      Point targetPoint = treeView.PointToClient( new Point( e.X, e.Y ) );
      treeView.SelectedNode = treeView.GetNodeAt( targetPoint );
    }

    private void OnTreeViewDragDrop( object sender, DragEventArgs e )
    {
      if ( e.Effect != DragDropEffects.Move )
        return;

      TreeNode targetNode = treeView.GetNodeAt( treeView.PointToClient( new Point( e.X, e.Y ) ) );
      if ( targetNode.Level > 0 )
        targetNode = targetNode.Parent;
      TreeNode draggedNode = e.Data.GetData( typeof( TreeNode ) ) as TreeNode;

      if ( draggedNode.Parent.Equals( targetNode ) )
        return;

      draggedNode.Remove();
      targetNode.Nodes.Add( draggedNode );
      treeView.SelectedNode = draggedNode;
    }

    private void OnTreeViewDragEnter( object sender, DragEventArgs e )
    {
      e.Effect = e.AllowedEffect;
    }

    #endregion

    private void OnTreeViewNodeMouseClick( object sender, TreeNodeMouseClickEventArgs e )
    {
      treeView.SelectedNode = e.Node;

      if ( e.Button == MouseButtons.Left )
      {
        if ( e.Node.IsExpanded )
          e.Node.Collapse();
        else
          e.Node.Expand();
      }
    }

    private void OnTreeViewAfterSelect( object sender, TreeViewEventArgs e )
    {
      TreeNode node = e.Node;
      var item = node.Tag as ExtendedToolBoxItem;

      removeToolStripMenuItem.Enabled = renameToolStripMenuItem.Enabled = item.IsUserItem && !IsRecentlyUsedNode(node);

      if(node.Level > 0 || node.Text == "[Pointer]")//игнорируем группы
        OnItemSelected(item);
     
      lastSelectedItem = node.Tag as ExtendedToolBoxItem;
    }

    private void OnTreeViewAfterLabelEdit( object sender, NodeLabelEditEventArgs e )
    {
      if ( string.IsNullOrEmpty( e.Label ) )
      {
        e.CancelEdit = true;
        return;
      }

      foreach ( TreeNode node in treeView.Nodes )
      {
        if ( e.Label == node.Name || node.Nodes.ContainsKey( e.Label ) )
        {
          e.CancelEdit = true;
          return;
        }
      }

      var tag = e.Node.Tag as ExtendedToolBoxItem;

      if ( tag.IsUserItem && tag.Item != null )
      {
        tag.Item.name = e.Label;
      }
    }

    private void OnTreeViewBeforeLabelEdit( object sender, NodeLabelEditEventArgs e )
    {
      var item = e.Node.Tag as ExtendedToolBoxItem;

      if ( !item.IsUserItem || IsRecentlyUsedNode(e.Node))
      {
        e.CancelEdit = true;
        return;
      }
    }

    private void OnItemSelected(ExtendedToolBoxItem _item)
    {
      if (ItemSelected != null)
        ItemSelected(_item.Item == null ? null : _item.Item.tag);
    }

    #region Context menu items handlers

    private void OnAddCategoryClicked( object sender, EventArgs e )
    {
      ( treeView.SelectedNode = FindCategory( string.Empty, true ) ).BeginEdit();
    }

    private void OnAddItemClicked( object sender, EventArgs e )
    {
      string category = "Custom";
      if ( treeView.SelectedNode != null )
        category = treeView.SelectedNode.Level == 1 ? treeView.SelectedNode.Parent.Text : treeView.SelectedNode.Text;
      if ( ItemAddClicked != null )
        ItemAddClicked( category );
    }

    private void OnRenameItemClicked( object sender, EventArgs e )
    {
      treeView.SelectedNode.BeginEdit();
    }

    private void OnRemoveItemClicked( object sender, EventArgs e )
    {
      string message = "Do you really want to delete this node?";
      if ( treeView.SelectedNode.Nodes != null && treeView.SelectedNode.Nodes.Count > 0 )
        message = "Do you really want to delete this node and all its subnodes?";
      if ( MessageBox.Show( message, "Delete Node", MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2 ) == DialogResult.Yes )
      {
        treeView.SelectedNode.Remove();
        treeView.SelectedNode = treeView.Nodes[0];
      }
    }

    private void contextMenuStrip_Opening( object sender, System.ComponentModel.CancelEventArgs e )
    {
      addItemFromEditorToolStripMenuItem.Enabled = true;
      ToolBoxItem candidate = null;

      if ( activeEditor != null )
        candidate = activeEditor.GetActiveItem();

      if ( null == candidate )
      {
        addItemFromEditorToolStripMenuItem.Enabled = false;
        return;
      }

      foreach ( TreeNode category in treeView.Nodes )
      {
        foreach ( TreeNode node in category.Nodes )
        {
          var tag = node.Tag as ExtendedToolBoxItem;
          if ( candidate.tag.Equals(tag.Item.tag) )
          {
            addItemFromEditorToolStripMenuItem.Enabled = false;
            return;
          }
        }
      }      
    }

    #endregion

    #region Recently Used

    private ExtendedToolBoxItem lastSelectedItem = null;

    private void AddRecentlyUsed(ExtendedToolBoxItem item)
    {
      if (item == null || item.Item == null) return;

      var categoryNodes = FindCategory(RECENTLY_KEY, false).Nodes;

      //если данный элемент уже есть в списке - удалим его
      for (int i = categoryNodes.Count - 1; i >= 0; --i)
      {
        if (categoryNodes[i].Tag == item)
        {
          categoryNodes.RemoveAt(i);
          break;
        }
      }

      //добавим элемент в начало списка
      TreeNode recentlyNode = categoryNodes.Insert(0, item.Item.name, item.Item.name);
      recentlyNode.Tag = item;

      if (item.Item.image != null)
      {
        recentlyNode.ImageKey = recentlyNode.SelectedImageKey = item.Item.category + "." + item.Item.name;
      }

      //ограничиваем число recently used items
      for (int i = categoryNodes.Count - 1; i >= RECENTLY_LIST_SIZE; --i)
      {
        categoryNodes.RemoveAt(i);
      }
    }

    public List<string> RecentlyUsed
    {
      get
      {
        var result = new List<string>();

        foreach (TreeNode item in FindCategory(RECENTLY_KEY, true).Nodes)
        {
          result.Add(item.Text);
        }

        return result;
      }
    }

    public void InitRecentlyUsed(List<string> items)
    {
      if(items.Count == 0)
      {
        items.Add("Button");
        items.Add("Image Label");
        items.Add("UILayout");
      }

      for (int i = items.Count - 1; i >= 0; --i)
      {
        TreeNode[] existingItem = treeView.Nodes.Find(items[i], true);

        if (existingItem.Length > 0 && existingItem[0] != null)
        {
          AddRecentlyUsed(existingItem[0].Tag as ExtendedToolBoxItem);
        }
      }

      ExpandCategory(RECENTLY_KEY);
    }

    private static bool IsRecentlyUsedNode(TreeNode _node)
    {
      return _node != null && _node.Parent != null && _node.Parent.Text == RECENTLY_KEY;
    }

    public void UpdateRecentlyUsed()
    {
      if(lastSelectedItem != null)
      {
        AddRecentlyUsed(lastSelectedItem);
        lastSelectedItem = null;
        //treeView.SelectedNode = treeView.Nodes[0];
      }
    }

    #endregion

    private void ExpandCategory(string _categoryName)
    {
      TreeNode category = null;

      foreach (TreeNode node in treeView.Nodes)
      {
        if (node.Text == _categoryName)
        {
          category = node;
          break;
        }
      }

      if(category != null)
      {
        treeView.CollapseAll();
        category.Expand();  
      }
    }
  }
}

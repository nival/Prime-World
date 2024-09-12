using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using libdb.Diagnostics;

namespace EditorLib
{
  public class ImprovedTreeView : TreeView
  {
    public ImprovedTreeView()  
    {  
			DrawMode = TreeViewDrawMode.OwnerDrawText;
			AdditionalTextFont = new Font(this.Font, FontStyle.Italic);
    	AdditionalTextColor = SystemColors.GrayText;

			StateContainer = new TreeStateContainer(this);
		}

		#region Public Properties

		[DefaultValue(false)]
    public bool RecursiveCheck { get; set; }

		[DefaultValue(false)]
		public bool EnableColoring { get; set; }

  	private Color[] _levelColors;
		
		[DefaultValue(null)]
  	public Color[] LevelColors
  	{
  		get { return _levelColors; }
  		set 
			{ 
				_levelColors = value ?? new Color[0];

				AssignBrushes();
			}
  	}

  	public Font AdditionalTextFont { get; set; }

		public Color AdditionalTextColor { get; set; }

  	public TreeStateContainer StateContainer { get; private set; }

		#endregion

    public List<string> GetCheckedNodes()
    {
      var result = new List<string>();

      GetCheckedInternal( Nodes, result );

      return result;
    }

    private static void GetCheckedInternal( TreeNodeCollection _nodes, ICollection<string> _checkedItems )
    {
      foreach( TreeNode node in _nodes )
      {
        if( node.Checked )
          _checkedItems.Add( node.FullPath );

        GetCheckedInternal( node.Nodes, _checkedItems );
      }
    }

		public TreeNode FindNodeByPath(string _path)
		{
			return FindNodeByPath(Nodes, _path);
		}

		private static TreeNode FindNodeByPath(TreeNodeCollection _nodes, string _path)
		{
      foreach( TreeNode node in _nodes )
			{
				if (_path == node.FullPath)
					return node;

				if (_path.Contains(node.FullPath))
				{
          TreeNode result = FindNodeByPath( node.Nodes, _path );

					if (result != null)
						return result;
				}
			}

			return null;
		}

		public TreeNode FindNodeRecursive( System.Predicate<TreeNode> _predicate )
		{
			return FindNodeRecursive( Nodes, _predicate );
		}

		public static TreeNode FindNodeRecursive( TreeNodeCollection _nodes, System.Predicate<TreeNode> _predicate )
		{
			foreach ( TreeNode node in _nodes )
			{
				if ( _predicate(node) )
					return node;

				TreeNode result = FindNodeRecursive( node.Nodes, _predicate );

				if ( result != null )
					return result;
			}

			return null;
		}

    #region Draw

  	private Brush[] levelBrushes = new Brush[0];

		private void AssignBrushes()
		{
			DisposeBrushes();

			levelBrushes = new Brush[_levelColors.Length];

			for (int i = 0; i < _levelColors.Length; i++)
			{
				levelBrushes[i] = new SolidBrush(_levelColors[i]);
			}
		}

		private void DisposeBrushes()
		{
			if (levelBrushes == null) return;

			for (int i = levelBrushes.Length - 1; i >= 0; --i)
			{
				levelBrushes[i].Dispose();
			}

			levelBrushes = null;
		}

    protected override void OnDrawNode( DrawTreeNodeEventArgs e )
    {
			base.OnDrawNode(e);

			ImprovedTreeNode node = e.Node as ImprovedTreeNode;

			if (node == null || node.Bounds.Width == 0)
			{
				e.DrawDefault = true;
				return;
			}
			
			e.DrawDefault = false;

			if (CheckBoxes && !node.Checkable)
				HideCheckBox(e.Graphics, e.Bounds);
			
			DrawBackground(e, node);
			DrawText(e, node);
    }

  	private void DrawText(DrawTreeNodeEventArgs e, ImprovedTreeNode node)
  	{
  		Color textColor = ForeColor;
  		Color additionalColor = node.AdditionalFontColor != Color.Empty ? node.AdditionalFontColor : AdditionalTextColor;

  		if ((e.State & TreeNodeStates.Selected) != 0)
  		{
  			textColor = SystemColors.HighlightText;
				additionalColor = SystemColors.HighlightText;
  		}

			using (SolidBrush textBrush = new SolidBrush(textColor), additionalTextBrush = new SolidBrush(additionalColor))
  		{
  			Font font = node.NodeFont ?? Font;
  			Font additionalFont = node.AdditionalFont ?? AdditionalTextFont;

				SizeF textSize = e.Graphics.MeasureString( node.Text, font );
				e.Graphics.DrawString( node.Text, font, textBrush, e.Bounds.Left, e.Bounds.Top );

  			if (!string.IsNullOrEmpty(node.AdditionalText))
  			{
					e.Graphics.DrawString( node.AdditionalText, additionalFont, additionalTextBrush, e.Bounds.Left + textSize.Width, e.Bounds.Top );
  			}
  		}
  	}

    private void DrawBackground( DrawTreeNodeEventArgs e, ImprovedTreeNode node )
  	{
			Font additionalFont = node.AdditionalFont ?? AdditionalTextFont;
			SizeF additionalTextSize = e.Graphics.MeasureString( node.AdditionalText, additionalFont, int.MaxValue );

      int selectionWidth = FullRowSelect ? this.Width - e.Bounds.X : (int)additionalTextSize.Width + e.Bounds.Width;
      Rectangle selectionRect = new Rectangle( e.Bounds.X, e.Bounds.Y, selectionWidth, e.Bounds.Height );

      if( ( e.State & TreeNodeStates.Selected ) != 0 )
      {
        e.Graphics.FillRectangle( SystemBrushes.Highlight, selectionRect );
        ControlPaint.DrawFocusRectangle( e.Graphics, selectionRect );
      }
			//else if( ( e.State & TreeNodeStates.Hot ) != 0 )
			//{
			//  //Rectangle rect = new Rectangle( 0, e.Bounds.Y, Width, e.Bounds.Height );

			//  e.Graphics.FillRectangle( SystemBrushes.Highlight, selectionRect );
			//}
			else if ( EnableColoring && e.Node.Level >= 0 && levelBrushes.Length > 0)
      {
				int colourCode = e.Node.Level % levelBrushes.Length;
        e.Graphics.FillRectangle( levelBrushes[colourCode], selectionRect );
      }
  	}

  	private void HideCheckBox( Graphics _graphics, Rectangle _rect )
    {
  	  int left = 0;

      if( ImageList == null )
        left = _rect.Left - 16;
      else
        left = _rect.Left - 34;

      using( SolidBrush backBrush = new SolidBrush( BackColor ) )
      {
        _graphics.FillRectangle( backBrush, left, _rect.Top, 16, _rect.Height );
      }
      
      using( Pen dottedPen = new Pen( SystemColors.ControlDark) )
      {
        dottedPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;
        _graphics.DrawLine( dottedPen, left + 1, _rect.Bottom - 8, left + 13, _rect.Bottom - 8 );
      }
    }

    #endregion

    protected override void OnBeforeCheck( TreeViewCancelEventArgs e )
    {
      if( ( e.Node is ImprovedTreeNode ) && !( (ImprovedTreeNode)e.Node ).Checkable )
      {
        e.Cancel = true;//не возникнет события AfterCheck
        return;//выходим, чтобы событие BeforeCheck не возникло
      }

      base.OnBeforeCheck( e );
    }

    protected override void OnAfterCheck( TreeViewEventArgs e )
    {
      base.OnAfterCheck( e );

			if ( RecursiveCheck )
			{
				foreach ( TreeNode nestedNode in e.Node.Nodes )
				{
					nestedNode.Checked = e.Node.Checked;
				}
			}
    }

		protected override void OnMouseUp( MouseEventArgs e )
		{
			TreeViewHitTestInfo info = HitTest(e.X, e.Y);

			if (info.Location == TreeViewHitTestLocations.RightOfLabel)
			{
				if (!FullRowSelect || ShowLines)
				{
					SelectedNode = info.Node;
				}
			}
			else if ( info.Location == TreeViewHitTestLocations.PlusMinus )//выбор ноды при нажатии на плюсик
			{
				SelectedNode = info.Node;
			}

			base.OnMouseUp(e);
		}

  	protected override void Dispose(bool disposing)
		{
			DisposeBrushes();
			base.Dispose(disposing);
		}
	}

  public class ImprovedTreeNode : TreeNode
  {
		public string AdditionalText { get; set; }
  	public Font AdditionalFont { get; set; }
		public Color AdditionalFontColor { get; set; }
		
    private bool checkable = true;
    public bool Checkable
    {
      get { return checkable; }
      set { checkable = value; }
    }
  }

	public class TreeNodeState
	{
		public string NodeText;
		public string NodePath;
		public bool Expanded;
		public bool Checked;
		public bool Selected;
	}

	/// <summary>
	/// Содержит состояние нод и полосы прокрутки для TreeView
	/// Содержит методы для сохранения и восстановления состояния TreeView
	/// </summary>
	public class TreeStateContainer
	{
		private readonly Dictionary<string, TreeNodeState> nodesState = new Dictionary<string, TreeNodeState>();
		private Point? scrollPosition;
		private readonly TreeView treeView;

		public TreeStateContainer( TreeView _treeView )
		{
			treeView = _treeView;
		}

		public void SaveState()
		{
			treeView.BeginUpdate();

			ForEachRecursive( treeView.Nodes, node => SaveNodeState( node ) );

			SaveScrollPos();

			treeView.EndUpdate();
		}

		public void RestoreState()
		{
			treeView.BeginUpdate();

			Action<TreeNode> restoreState = node =>
			{
				TreeNodeState nodeState = GetNodeState( node.FullPath );

				if ( nodeState != null )
				{
					node.Checked = nodeState.Checked;

					if ( nodeState.Selected )
						treeView.SelectedNode = node;

					if ( nodeState.Expanded )
					{
						if ( !node.IsExpanded )
							node.Expand();
					}
					else
					{
						if ( node.IsExpanded )
							node.Collapse( true );
					}
				}
			};

			ForEachRecursive( treeView.Nodes, restoreState );

			RestoreScrollPos();

			treeView.EndUpdate();
		}

		public void Clear()
		{
			nodesState.Clear();
			scrollPosition = null;
		}

		public TreeNodeState GetNodeState( string _nodePath )
		{
			TreeNodeState result = new TreeNodeState();
			nodesState.TryGetValue( _nodePath, out result );
			return result;
		}

		public void SaveNodeState( TreeNode _node )
		{
			if(_node == null)
				return;

			Log.Assert(_node.TreeView == treeView, "It's incorrect to save node state for another treeView");

			nodesState[_node.FullPath] = new TreeNodeState
			{
				NodeText = _node.Text,
				Checked = _node.Checked,
				Expanded = _node.IsExpanded,
				NodePath = _node.FullPath,
				Selected = _node.IsSelected
			};
		}

		public void SaveScrollPos( )
		{
			scrollPosition = GetScrollPos();
		}

		public void RestoreScrollPos()
		{
			if ( /*scrollPosition != null &&*/ scrollPosition.HasValue )
				SetScrollPos( scrollPosition.Value );
		}

		#region Private Methods
		
		private static void ForEachRecursive( TreeNodeCollection _nodes, Action<TreeNode> _action )
		{
			foreach ( TreeNode node in _nodes )
			{
				_action( node );
				ForEachRecursive( node.Nodes, _action );
			}
		}

		#endregion

		#region Scroll Position

		[DllImport( "user32.dll", CharSet = System.Runtime.InteropServices.CharSet.Auto )]
		private static extern int GetScrollPos( int hWnd, int nBar );

		[DllImport( "user32.dll" )]
		private static extern int SetScrollPos( IntPtr hWnd, int nBar, int nPos, bool bRedraw );

		private const int SB_HORZ = 0x0;
		private const int SB_VERT = 0x1;

		public Point GetScrollPos()
		{
			return new Point(
					GetScrollPos( (int)treeView.Handle, SB_HORZ ),
					GetScrollPos( (int)treeView.Handle, SB_VERT ) );
		}

		public void SetScrollPos(Point scrollPosition )
		{
			SetScrollPos( (IntPtr)treeView.Handle, SB_HORZ, scrollPosition.X, true );
			SetScrollPos( (IntPtr)treeView.Handle, SB_VERT, scrollPosition.Y, true );
		}

		#endregion
	}
}

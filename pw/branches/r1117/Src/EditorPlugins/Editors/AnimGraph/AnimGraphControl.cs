using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using EditorNative.SceneElements.SceneObjects;
using libdb.Diagnostics;
using libdb.UndoRedo;
using Northwoods.Go;
using Color = System.Drawing.Color;

namespace EditorPlugins.Editors.AnimGraph
{
  public class AnimGraphControl : GoView
  {
    private AnimGraphContext context;

    public AnimGraphContext Context
    {
      get { return context; }
      private set 
      {
        nodesPlayed.Clear();
        context = value; 
      }
    }

    public AnimGraphControl()
    {
      NewGoLink.Style = GoStrokeStyle.Bezier;
      NewGoLink.ToArrow = true;
      NewGoLink.HighlightWhenSelected = true;
      NewGoLink.HighlightPenColor = Color.FromKnownColor(KnownColor.Highlight);
      NewGoLink.HighlightPenWidth = 6;
      NewGoLink.PenColor = Color.Gray;

      ShowVerticalScrollBar = GoViewScrollBarVisibility.Show;
      ShowHorizontalScrollBar = GoViewScrollBarVisibility.Show;

    	AllowCopy = false;
      AllowDragOut = false;
      AllowDrop = false;
      ArrowMoveLarge = 10.0f;
      ArrowMoveSmall = 1.0f;
      DragsRealtime = true;
      PortGravity = 5.0f;
    }

  	private bool smartSelectionEnabled;
  	public bool SmartSelectionEnabled
  	{
  		get { return smartSelectionEnabled; }
  		set 
			{ 
				smartSelectionEnabled = value;
				SmartSelection(smartSelectionEnabled);
			}
  	}

  	#region Fill control with animation graph nodes and links

    private void AddNodeToGoView(Node _node)
    {
      var goNode = new GoNodeExtended
      {
        LabelSpot = GoObject.Middle,
        Shape = new GoRoundedRectangle(),
        MiddleLabelMargin = new SizeF(25, 25),
        Text = _node.Name,
        Location = new Point(_node.X, _node.Y),
        ownerFont = Font,
        UserObject = _node
      };

      goNode.Shape.FillHalfGradient(Color.Black);
      goNode.Shape.PenWidth = 2;
      goNode.Label.TextColor = Color.White;
      Document.Add(goNode);
    }

    private void AddLinkToGoView(Link _link)
    {
			var fromNode = ( (GoNodeExtended)Document.FindNode( _link.FromNode.Name ) ).Port;
			var toNode = ( (GoNodeExtended)Document.FindNode( _link.ToNode.Name ) ).Port;

      var golink = new GoLink
      {
        Style = GoStrokeStyle.Bezier,
        ToArrow = true,
        PenColor = Color.Gray,
        HighlightWhenSelected = true,
        HighlightPenColor = Color.FromKnownColor(KnownColor.Highlight),
        HighlightPenWidth = 5,
				FromPort = fromNode,
        ToPort = toNode,
        UserObject = _link
      };

      Document.Add(golink);
    }

    private void RecreateAnimGraph()
    {
    	try
    	{
				BeginUpdate();
				Document.Clear();

				if ( Context == null )
					return;

				// нарисуем ноды
				foreach ( var node in Context.ListWithoutSubnodes() )
				{
					AddNodeToGoView( node );
				}

				// нарисуем линки
				foreach ( var node in Context.ListWithoutSubnodes() )
				{
					foreach ( var link in node.Links )
					{
						AddLinkToGoView( link );
					}
				}

				RescaleToFit();

				
    	}
    	finally 
    	{
				EndUpdate();
    	}
    }

    #endregion

    #region Protected events overrides and theirs private subscribers

    protected override void OnBackgroundSingleClicked(GoInputEventArgs _args)
    {
      base.OnBackgroundSingleClicked(_args);

      if (Context != null)
      {
        PlayAnyNode();
        Refresh();
      }
    }

    protected override void OnObjectSingleClicked(GoObjectEventArgs _args)
    {
    	SmartSelection(SmartSelectionEnabled);

			base.OnObjectSingleClicked( _args );

			GoNodeExtended node = _args.GoObject.Parent as GoNodeExtended;
    	
			if(node != null)
    	{
    		if(!_args.Control || IsPlayingSubNode)
    		{
					PlayNode( node.Text, false );
    		}
    		else if(!RemoveFromPlayList(node.Text))
    		{
					PlayNode( node.Text, true );
    		}
    	}

    	UpdateSelectedObject();
    }

    protected override void OnObjectGotSelection(GoSelectionEventArgs _args)
    {
      base.OnObjectGotSelection(_args);
			
      GoNodeExtended node = _args.GoObject as GoNodeExtended;
      if (node != null)
      {
				RedrawSelectedNode( node, true );
      } 
    }

		protected override void OnObjectLostSelection( GoSelectionEventArgs _args )
		{
			base.OnObjectLostSelection( _args );

			GoNodeExtended node = _args.GoObject as GoNodeExtended;
			if ( node != null )
			{
				RedrawSelectedNode( node, false );
			}
		}

    protected override void OnSelectionMoved(EventArgs _args)
    {
      base.OnSelectionMoved(_args);

      foreach (var node in GetSelectedNodes())
      {
        Node each = Context.GetNode(node.Text);

        if (each != null)
          each.OnMoved((int)node.Location.X, (int)node.Location.Y);
      }
    }

    protected override void OnSelectionDeleting(System.ComponentModel.CancelEventArgs _args)
    {
      base.OnSelectionDeleting(_args);

      var goLinksToDelete = new List<GoLink>();

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Delete animation graph nodes" ) )
      {
        foreach( GoObject obj in Selection )
        {
          if( obj is GoNodeExtended )
          {
            var currentNode = ( obj as GoNodeExtended ).UserObject as Node;

            if( currentNode != null )
            {
              Context.RemoveNode( currentNode );
              Context.SetInvalid();
            }
          }
          else if( obj is GoLink )
          {
            var goLink = obj as GoLink;
            var currentLink = goLink.UserObject as Link;

            if( currentLink != null )
            {
              currentLink.FromNode.Links.Remove( currentLink );
            }

            goLinksToDelete.Add( goLink );
          }
        }

        foreach( var link in goLinksToDelete )
          Document.Remove( link );

        trans.Commit();
      }

      PlayAnyNode();
      UpdateSelectedObject();
    }

    protected override void OnLinkCreated(GoSelectionEventArgs evt)
    {
      base.OnLinkCreated(evt);

      GoLink link = evt.GoObject as GoLink;
      
      if (link == null) return;

			var fromNode = Context.GetNode( ( (GoNodeExtended)link.FromNode ).Text );
			var toNode = Context.GetNode( ( (GoNodeExtended)link.ToNode ).Text );

      link.UserObject = fromNode.LinkTo(toNode);
    }

    #endregion

    public void SetController(AGController _controller)
    {
      if (Context == null || _controller == null || Context.RecreateNeeded || Context.AGCDbid != _controller.DBID)
      {
        var wrapper = _controller == null ? null : new AgControllerWrapper(_controller);
        Context = AnimGraphContext.CreateContext(wrapper);

        Tag = Context;
        RecreateAnimGraph();
      }

      Refresh();

      if (Context != null)
      {
        PlayLastSelectedNodes();
      }

			Enabled = _controller != null && _controller.IsValid() && !_controller.DBID.IsEmpty;
    }

    private IEnumerable<GoNodeExtended> GetSelectedNodes()
    {
      foreach (GoObject obj in Selection)
      {
				if ( obj is GoNodeExtended )
					yield return (GoNodeExtended) obj; 
      }
		}

		private GoNodeExtended lastNode;

		private void SmartSelection(bool _enabled)
		{
			try
			{
				BeginUpdate();

				//запрещаем/разрешаем селектить линки
				foreach ( GoObject goObject in Document )
				{
					if ( goObject is GoLink )
						goObject.Selectable = !_enabled;
				}

				//деселектим старую ноду (визуально)
				if ( lastNode != null )
					RedrawSelectedNode( lastNode, false );

				if ( !_enabled )
				{
					lastNode = null;
					return;
				}				

				if ( Selection.First is GoNodeExtended )
					lastNode = (GoNodeExtended)Selection.First;

				if ( lastNode == null )
					return;

				//разрешаем селектить входящие и исходящие линки
				foreach ( IGoLink link in lastNode.Links )
				{
					link.GoObject.Selectable = true;
				}

				//отрисовываем селект ноды и линки, поселекченный линк отрисовывается автоматически контролом
				RedrawSelectedNode( lastNode, true );
			}
			finally
			{
				EndUpdate();
			}
		}

		/// <summary>
		/// Выставляем цвета поселекченной ноды
		/// </summary>
		private void RedrawSelectedNode( GoNodeExtended _node, bool _selected )
		{
			try
			{
				BeginUpdate();

				float penWidth = _selected ? 2.0f : 1.0f;
				Color sourceColor = _selected ? Color.LimeGreen : Color.Gray;
				Color destColor = _selected ? Color.FromArgb( 255, 126, 0 ) : Color.Gray;
				Color destFastColor = _selected ? Color.Red : Color.Gray;

				foreach ( GoLink goLink in _node.Port.SourceLinks )
				{
					goLink.PenColor = sourceColor;
					goLink.PenWidth = penWidth;
					( (GoNodeExtended)goLink.FromNode ).Shape.PenColor = sourceColor;
				}

				foreach ( GoLink goLink in _node.Port.DestinationLinks )
				{
					var link = goLink.UserObject as Link;

					if ( link == null )
					{
						Log.AlwaysAssert( "Link broken and can't be selected." );
						continue;
					}

					bool fastLink = ( link.MinFrom == 0.0f );
					
					goLink.PenColor = _selected ? ( fastLink ? destFastColor : destColor ) : Color.Gray;
					goLink.PenWidth = penWidth;

					GoNodeExtended toNode = (GoNodeExtended)goLink.ToNode;
					toNode.Shape.PenColor = fastLink ? destFastColor : destColor;
				}

				_node.Shape.FillHalfGradient( _selected ? Color.FromKnownColor( KnownColor.Highlight ) : Color.Black );
				_node.Label.TextColor = _selected ? Color.FromKnownColor( KnownColor.HighlightText ) : Color.White;
			}
			finally
			{
				EndUpdate();
			}
		}

		#region Context Menu

		protected override void OnBackgroundContextClicked( GoInputEventArgs _args )
		{
			base.OnBackgroundContextClicked( _args );

			GoContextMenu menu = new GoContextMenu( this );
			menu.MenuItems.Add( "Create Normal Node", OnCreateNewNode ).Tag = typeof( NormalNode );
			menu.MenuItems.Add( "Create Random Node", OnCreateNewNode ).Tag = typeof( RandomNode );
			menu.Tag = _args.MouseEventArgs.Location;
			menu.Show( this, _args.MouseEventArgs.Location );
		}

		private void OnCreateNewNode( object _sender, EventArgs _args )
		{
			MenuItem item = _sender as MenuItem;
			if ( item == null )
				return;
			Menu menu = item.Parent;
			if ( menu == null )
				return;

			if ( !( item.Tag is Type ) || !( menu.Tag is Point ) )
				return;

			Point location = (Point)( menu.Tag );
			PointF docLocation = ConvertViewToDoc( location );

			Node node = null;

			if ( item.Tag == typeof( NormalNode ) )
			{
				node = Context.CreateNormalNode( "new_node", (int)docLocation.X, (int)docLocation.Y );
			}
			else if ( item.Tag == typeof( RandomNode ) )
			{
				node = Context.CreateRandomNode( "new_node", (int)docLocation.X, (int)docLocation.Y );
			}
			else
			{
				Log.AlwaysAssert( "Invalid Node Type" );
			}

			AddNodeToGoView( node );
		}

		private void OnConvertToRandomNode( object _sender, EventArgs _args )
		{
			MenuItem item = _sender as MenuItem;
			if ( item == null )
				return;

			if ( item.Tag is NormalNode )
			{
				Context.ToRandomNode( item.Tag as NormalNode );
			}

		}

		private void OnConvertToNormalNode( object _sender, EventArgs _args )
		{
			MenuItem item = _sender as MenuItem;
			if ( item == null )
				return;

			if ( item.Tag is RandomNode )
			{
				Context.ToNormalNode( item.Tag as RandomNode );
			}

		}

		private void OnCopyNode( object _sender, EventArgs _args )
		{
			MenuItem item = _sender as MenuItem;
			if ( item == null )
				return;

			if ( item.Tag is Node )
			{
				Context.CreateNodeCopy( item.Tag as Node );
			}
		}

		private void OnPlaySubnode( object _sender, EventArgs _args )
		{
			MenuItem item = _sender as MenuItem;
			if ( item == null )
				return;

			if ( !( item.Tag is Node ) )
				return;

			Node node = item.Tag as Node;
			PlayNode( node.Name, false );

			SelectedObject = node;
		
			Refresh();
		}

		protected override void OnObjectContextClicked( GoObjectEventArgs _args )
		{
			base.OnObjectContextClicked( _args );

			GoNodeExtended goNode = _args.GoObject.Parent as GoNodeExtended;
			if ( goNode == null )
				return;

			Node node = Context.GetNode( goNode.Text );

			if ( node == null )
				return;

			GoContextMenu menu = new GoContextMenu( this );
			if ( node is NormalNode )
			{
				menu.MenuItems.Add( "Convert to Random Node", OnConvertToRandomNode ).Tag = node;
			}
			else if ( node is RandomNode )
			{
				if ( ( node as RandomNode ).SubNodes != null && ( node as RandomNode ).SubNodes.Count > 0 )
				{
					foreach ( var item in ( node as RandomNode ).SubNodes )
					{
						MenuItem menuItem = new MenuItem( item.Name, OnPlaySubnode );
						menuItem.Tag = item;
						if ( IsInPlaylist( item.Name ) )
						{
							menuItem.Checked = true;
							menuItem.RadioCheck = true;
						}
						menu.MenuItems.Add( menuItem );
					}
				}

				menu.MenuItems.Add( "-" );
				menu.MenuItems.Add( "Convert to Normal Node", OnConvertToNormalNode ).Tag = node;
			}

			menu.MenuItems.Add( string.Format( "Copy \"{0}\" node", node.Name ), OnCopyNode ).Tag = node;

			if ( menu.MenuItems.Count > 0 )
				menu.Show( this, _args.MouseEventArgs.Location );
		}

		#endregion

		#region Support single selected object

		public event EventHandler SelectedObjectChanged = null;
  	private object selectedObject;
  	
		public object SelectedObject
  	{
  		get { return selectedObject; }
  		private set 
			{ 
				selectedObject = value;
				OnSelectedObjectChanged();
			}
  	}

  	private void OnSelectedObjectChanged()
  	{
  		if (SelectedObjectChanged != null)
  			SelectedObjectChanged(this, EventArgs.Empty);
  	}

		private void UpdateSelectedObject()
		{
			if ( Selection.Count != 1 )
				return;

			if ( Selection.First is GoNode )
			{
				SelectedObject = ( (GoNode)Selection.First ).UserObject;
			}
			else if ( Selection.First is GoLink )
			{
				SelectedObject = ( (GoLink)Selection.First ).UserObject;
			}
		}

    #endregion

    #region PlayList functionality

    //плейлист
    private readonly List<string> nodesPlayed = new List<string>();
    private bool fakePlayList = false;
    public int lastPlayedIndex = -1;
		
		public bool SustainLooped { get; set; }
		public float SustainLength { get; set; }

    private void UpdatePlayListIndices()
    {
      Context.Controller.SwitchToAg();

      foreach( var node in Context.ListNodes() )
        node.PlayIndex = 0;

      if( nodesPlayed.Count > 1 )
      {
        for( int i = 0; i < nodesPlayed.Count; ++i )
        {
          Node node = Context.GetNode( nodesPlayed[i] );

          if( node != null )
            node.PlayIndex = i + 1;
        }
      }
    }

    /// <summary>
    /// Play node with specified name (or add/remove node with specified name from play sequence)
    /// </summary>
    /// <param name="name">Name of node to play</param>
    /// <param name="add">If true add specified node to play list overwise play only this node</param>
    public void PlayNode( string name, bool add )
    {
      if( !add || fakePlayList )
      {
        fakePlayList = false;
        nodesPlayed.Clear();
      }
      else if( nodesPlayed.IndexOf( name ) >= 0 )
        return;

      nodesPlayed.Insert( nodesPlayed.Count, name );
      UpdatePlayListIndices();
      PlayLastSelectedNodes();
    }

    /// <summary>
    /// Remove node with specified name from play list
    /// </summary>
    /// <param name="name">Name of node to remove from playlist</param>
    public bool RemoveFromPlayList( string name )
    {
      if( nodesPlayed.Remove( name ) )
      {
        if( nodesPlayed.Count == 0 )
          PlayAnyNode();
        else
        {
          UpdatePlayListIndices();
          PlayLastSelectedNodes();
        }

        return true;
      }

      return false;
    }

    /// <summary>
    /// Select some node to play
    /// </summary>
    public void PlayAnyNode()
    {
      Node node = Context.GetNode( Context.animGraphCreator.defaultNode );
      if( node != null )
      {
        var nodeToPlay = Context.GetNode(node.NextNode);
        if( nodeToPlay != null )
        {
          PlayNode( nodeToPlay.Name, false ); 
        }
        else
        {
          nodesPlayed.Clear();
          UpdatePlayListIndices();
        }
      }
      else
        PlayNode( Context.animGraphCreator.defaultNode, false );
      fakePlayList = true;
    }

    /// <summary>
    /// Resend played nodes sequence to Controller
    /// </summary>
    public void PlayLastSelectedNodes()
    {
      if( nodesPlayed.Count == 0 )
        return;

      var toPlay = new List<int>();
      for( int index = 0; index < nodesPlayed.Count; ++index )
      {
        Node node = Context.GetNode( nodesPlayed[index] );
        if( node == null )
          continue;

        toPlay.Add( node.AnGrNodeIndex );
      }

      if( toPlay.Count > 0 )
      {
        float loopTime = 0.0f;

        if ( SustainLooped && nodesPlayed.Count > 1 )
          loopTime = SustainLength;

        Context.Controller.PlayNodes( toPlay, loopTime );
      }
    }

    public bool IsInPlaylist( string name )
    {
      return nodesPlayed.IndexOf( name ) >= 0;
    }

    public bool IsPlayingSubNode
    {
      get
      {
        if( nodesPlayed.Count != 1 )
          return false;

        Node node = Context.GetNode( nodesPlayed[0] );

        if( node == null )
          return false;

        return node is SubNode;
      }
    }

    #endregion
  }
}

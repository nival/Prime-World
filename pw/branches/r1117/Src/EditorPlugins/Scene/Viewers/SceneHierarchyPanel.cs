using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Panels;
using EditorLib.PropertiesEditor;
using EditorLib.Utils;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Editors.AnimatedCurves;
using libdb.DB;

namespace EditorPlugins.Scene.Viewers
{
  public partial class SceneHierarchyPanel : EditorPanel
	{
		#region Nested Types

		private class ComponentsInfo
    {
      private readonly EditorSceneComponent component = null;
    	private readonly int index = 0;
			private readonly DBID dbId = DBID.Empty;

      public DBID DbId { get { return dbId; } }

			public EditorSceneComponent EditorSceneComponent
			{
				get { return component; }
			}

    	public int Index { get { return index; } }

			public Type ComponentType
			{
				get
				{
					DBResource resource = GetResource();

					if(resource != null)
						return resource.GetType();

					return null;
				}
			}

			internal ComponentsInfo( EditorSceneComponent _component, int _index )
			{
				component = _component;
				index = _index;

				if ( _component != null )
					dbId = _component.GetDBID();
			}

			public void SetVisibility(bool _visible)
			{
				component.SetHide( !_visible );
			}

      public string FormatComponentName()
      {
        DBResource resource = GetResource();
        if( resource != null )
        {
          return TypeUtils.GetFormattedListCaption( index, resource );
        }

        return string.Format( "{0}. null ( {1} )", index, component.FormatComponentName() );
      }

      public string FormatComponentNameAdditional()
      {
        return component.FormatComponentName();
      }

			public DBResource GetResource()
			{
				DBPtr<DBResource> resource = DataBase.Get<DBResource>( DbId );
				return resource.Get();
			}

			public override string ToString()
			{
				return component.GetDBID().ToString();
			}
		}

		#endregion	

		private ISceneHierarchyPanelExtension controller;

		//TODO refactor: избавиться от логики с refreshing, сделать выделение метода и просто не вызывать тот код, который не должен быть вызван при refresh
		private readonly EventSuppressor refreshing = new EventSuppressor();

    private PropertiesEditorPanel PropertiesEditor { get; set;}
		private AnimatedCurvesPanel AnimatedCurvesPanel { get; set; }

  	private EditorSceneComponent selectedComponent;
  	public EditorSceneComponent SelectedComponent
  	{
  		get { return selectedComponent; }
  		private set 
			{
				//ищем компоненту
				System.Predicate<TreeNode> predicate = _n => (_n.Tag is ComponentsInfo) && 
																										 ((ComponentsInfo) _n.Tag).EditorSceneComponent == selectedComponent;

				//сбрасываем селекшн старой ноды
				TreeNode node = treeHierarchy.FindNodeRecursive( predicate );
				if(node != null) SetNodeFont(node, FontStyle.Regular);

				selectedComponent = value;

				//выставляем селекшн новой ноды
				node = treeHierarchy.FindNodeRecursive( predicate );
				if(node != null) SetNodeFont(node, FontStyle.Bold);
			}
  	}

  	public SceneHierarchyPanel()
    {
      InitializeComponent();
    }

    protected override bool Initialize( IEditorWinApplication application )
    {
      PropertiesEditor = application.Panels.GetSingletonPanel<PropertiesEditorPanel>();
      AnimatedCurvesPanel = application.Panels.GetSingletonPanel<AnimatedCurvesPanel>();
      
      treeHierarchy.ImageList = application.Application.Extensions.GetTypesImageList();
      treeHierarchy.RecursiveCheck = true;
			treeHierarchy.PathSeparator = "~";

			noResourceLabel.Visible = true;
			treeHierarchy.Visible = false;

      return true;
    }

		internal void SetController( ISceneHierarchyPanelExtension _controller )
    {
      controller = _controller;
      Rebuild();
    }

  	#region Create & Add Nodes

    private void AddNodes( TreeNodeCollection _nodesCollection, EditorSceneComponent _editorComponent )
    {
      int index = 0;
      AddNodeInternal( _editorComponent, index, _nodesCollection );

      foreach( EditorSceneComponent component in _editorComponent.brothers )
      {
        index++;
        AddNodeInternal( component, index, _nodesCollection );
      }
    }

    private ImprovedTreeNode CreateSceneObjectNode( EditorSceneObject _sceneObject )
    {
      DBPtr<DBResource> so = DataBase.Get<DBResource>( _sceneObject.DbId );
      DBResource resource = so.Get();

      int index = 0;

      if( resource != null )
        index = GetImageIndex( resource.GetType() );

      return CreateNodeInternal( _sceneObject.DbId.ToString(), string.Empty, true, _sceneObject, index );
    }

    private ImprovedTreeNode CreateTrackNode( SceneObjectTrack _objectTrack )
    {
      int index = GetImageIndex( _objectTrack.GetType());

      return CreateNodeInternal( _objectTrack.name, "Track", false, _objectTrack, index );
    }

		private ImprovedTreeNode CreateLocatorNode( Locator _locator )
		{
			int index = GetImageIndex( _locator.GetType() );

			return CreateNodeInternal( _locator.name, "Locator", false, _locator, index );
		}

		private ImprovedTreeNode CreateAabbNode(AABB _aabb)
		{
			int index = GetImageIndex( typeof( AABB ) );
			
			return CreateNodeInternal( "AABB", string.Empty, false, _aabb, index );
		}

    private static ImprovedTreeNode CreateNodeInternal( string _text, string _additional, bool _checkable, object _value, int _imageIndex )
    {
			return new ImprovedTreeNode
			{
				Tag = _value,
				Text = _text,
				AdditionalText = _additional,
				Checked = true,
				Checkable = _checkable,
				ImageIndex = _imageIndex,
				SelectedImageIndex = _imageIndex
			};
    }

    private void AddNodeInternal( EditorSceneComponent _editorComponent, int _index, TreeNodeCollection _nodesCollection )
    {
      ComponentsInfo info = new ComponentsInfo( _editorComponent, _index );

    	ImprovedTreeNode curNode = CreateNodeInternal(info.FormatComponentName(),
    	                                              info.FormatComponentNameAdditional(), 
																										true, 
																										info, 
																										GetImageIndex( info.ComponentType ));   	

      _nodesCollection.Add( curNode );

    	AABB aabb = GetAABB(info.EditorSceneComponent);

			if(aabb != null)
			{
				ImprovedTreeNode aabbNode = CreateAabbNode(aabb);
				curNode.Nodes.Add( aabbNode );
			}
 
      if( info.EditorSceneComponent.child != null )
      {
				AddNodes( curNode.Nodes, info.EditorSceneComponent.child );
      }
    }

		private TreeNode[] AddObjectTracks( EditorSceneComponent component )
		{
			DBPtr<DBResource> so = DataBase.Get<DBResource>( component.sceneObject.DbId );
			DBResource resource = so.Get();

			List<TreeNode> result = new List<TreeNode>();

			if ( so.IsValid && resource is DBSceneObject )
			{
				DBPtr<SceneObjectTracks> dbtracks = ( (DBSceneObject)resource ).tracksList;
				if ( dbtracks != null && dbtracks.IsValid )
				{
					IList<DBPtr<SceneObjectTrack>> animatedTracks = dbtracks.Get().animatedTracks;

					foreach ( DBPtr<SceneObjectTrack> animTrack in animatedTracks )
					{
						if ( animTrack.IsValid )
						{
							result.Add( CreateTrackNode( animTrack.Get() ) );
						}
					}
				}
			}

			return result.ToArray();
		}

		private TreeNode[] AddLocators( EditorSceneComponent _component )
		{
			List<Locator> locators = RecursiveFindLocators( _component );

			List<TreeNode> result = new List<TreeNode>();

			foreach ( Locator locator in locators )
			{
				result.Add( CreateLocatorNode( locator ) );
			}

			return result.ToArray();
		}

    #endregion

    public void SelectFirstNode( EditorSceneObject obj )
    {
      if( treeHierarchy.Nodes.Count > 0 )
      {
        treeHierarchy.SelectedNode = treeHierarchy.Nodes[0];
        for( int i = 0; i < treeHierarchy.Nodes.Count; i++ )
        {
          if( treeHierarchy.Nodes[i].Text == obj.DbId.ToString() )
          {
            treeHierarchy.SelectedNode = treeHierarchy.Nodes[i];
          }
        }
      	OnComponentSelected(((EditorSceneObject) treeHierarchy.SelectedNode.Tag).GetRootEditorSceneComponent(), true);
      }
    }

    public void Rebuild()
    {
      if( !IsValid )
      {
        noResourceLabel.Visible = true;
        treeHierarchy.Visible = false;
        AnimatedCurvesPanel.SelectedObject = null;
        return;
      }

      using ( refreshing.Suppress() )
			{
				treeHierarchy.StateContainer.SaveState();

				List<TreeNode> nodes = new List<TreeNode>();

				foreach(EditorSceneComponent component in controller.Items)
				{
					if(component == null)
						continue;
					
					//Add Root Node
					ImprovedTreeNode root = CreateSceneObjectNode( component.sceneObject );

					//Add Object Tracks
					root.Nodes.AddRange(AddObjectTracks(component));

					//locators
					root.Nodes.AddRange(AddLocators(component));
					
					//other nodes
					AddNodes( root.Nodes, component );
					root.Expand();
					nodes.Add(root);
				}

				treeHierarchy.BeginUpdate();
				treeHierarchy.Nodes.Clear();
				treeHierarchy.Nodes.AddRange(nodes.ToArray());

				//expand level 1
				foreach(TreeNode node in treeHierarchy.Nodes)
				{
					node.Expand();

					//expand level 2
					foreach(TreeNode node2 in node.Nodes)
					{
						node2.Expand();
					}
				}

				treeHierarchy.StateContainer.RestoreState();
				SelectNode(treeHierarchy.SelectedNode, false);
			}

			RestoreComponentsVisibility( treeHierarchy.Nodes );

      treeHierarchy.EndUpdate();

			noResourceLabel.Visible = false;
			treeHierarchy.Visible = true;
    }

    private void SelectNode( TreeNode node, bool isManipulatorOff )
    {
      if( node == null )
        return;

			if( node.Tag is ComponentsInfo )
      {
				ComponentsInfo info = (ComponentsInfo)node.Tag;
				OnComponentSelected( info.EditorSceneComponent, isManipulatorOff );

        object peTarget = DataBase.Get<DBResource>( info.DbId ).Get();

        if( node.Parent != null && node.Parent.Tag != null )
        {
          if( node.Parent.Tag is ComponentsInfo )
          {
						ComponentsInfo parentInfo = (ComponentsInfo)node.Parent.Tag;
            DBSceneComponent parentComponent = DataBase.Get<DBSceneComponent>( parentInfo.DbId ).Get();
            if( parentComponent != null && info.Index < parentComponent.attached.Count )
              peTarget = GetAttachedComponentStruct( parentComponent.attached, peTarget );
          }
          else if( node.Parent.Tag is EditorSceneObject )
          {
						EditorSceneObject parentInfo = (EditorSceneObject)node.Parent.Tag;
            DBResource parentRes = DataBase.Get<DBResource>( parentInfo.DbId ).Get();
            if( parentRes is DBSceneObject )
            {
            	DBSceneObject sceneObject = (DBSceneObject) parentRes;
							if ( info.Index < sceneObject.attached.Count )
								peTarget = GetAttachedComponentStruct( sceneObject.attached, peTarget );
            }
            else if( parentRes is DBSceneComponent )
            {
            	DBSceneComponent sceneComponent = (DBSceneComponent) parentRes;
							if ( info.Index < sceneComponent.attached.Count )
								peTarget = GetAttachedComponentStruct( sceneComponent.attached, peTarget );
            }
          }
        }

				if(!refreshing.IsSuppressed)
				{
					PropertiesEditor.SelectedObject = peTarget;
					PropertiesEditor.ExpandOneLevel();
					AnimatedCurvesPanel.SelectedObject = peTarget;	
				}       
      }
      else if( node.Tag is EditorSceneObject )
      {
				EditorSceneObject sceneObject = (EditorSceneObject)node.Tag;
				OnComponentSelected( sceneObject.GetRootEditorSceneComponent(), isManipulatorOff );

				if(!refreshing.IsSuppressed)
          PropertiesEditor.SelectedObject = DataBase.Get<DBResource>( sceneObject.DbId ).Get();
      }
			else if( node.Tag is Locator )
			{
				using ( refreshing.Suppress() )
				{
					SelectNode( node.Parent, false );
				}

				Locator locator = (Locator)node.Tag;
				OnComponentSelected( locator, isManipulatorOff );

				if ( !refreshing.IsSuppressed )
					PropertiesEditor.SelectedObject = locator;
			}
			else
			{
				using(refreshing.Suppress())
				{
					SelectNode( node.Parent, false );
				}

				OnComponentSelected( node.Tag, false );

				if(refreshing.IsSuppressed) return;

				if ( node.Tag is AABB )
					PropertiesEditor.SelectedObject = node.Tag;

				if ( node.Tag is SceneObjectTrack )
					AnimatedCurvesPanel.SelectedObject = node.Tag;
			}
    }

		private void OnComponentSelected( object _component, bool isManipulatorOff )
		{
			if ( _component is Locator )
			{
				controller.SelectLocator( (Locator)_component );
			}
			else if ( _component is SceneObjectTrack )
			{
				controller.ApplyTrack( (SceneObjectTrack)_component );
			}
			else if ( _component is AABB )
			{
                DBSceneResource resource = DataBase.Get<DBSceneResource>(SelectedComponent.sceneObject.DbId).Get();

                if ( resource != null )
                {
                    Quat quat = null;
                    
                    foreach ( AttachedSceneComponent component in resource.attached )
                    {
                        if ( component.component.DBId == SelectedComponent.GetDBID() )
                        {
                            quat = component.placement.rot.GetValue(0);
                            break;
                        }
                    }

                    controller.SetQuat(quat);
                }

				controller.SelectAABB();
			}
			else if ( _component is EditorSceneComponent )
			{
				SelectedComponent = (EditorSceneComponent)_component;
				controller.ShowComponent( SelectedComponent, isManipulatorOff );
			}		
		}

    private static object GetAttachedComponentStruct( libdb.IChangeableList<AttachedSceneComponent> attList, object peTarget )
    {
      if( attList == null || peTarget == null )
        return peTarget;

      foreach( AttachedSceneComponent attSC in attList )
      {
        if( attSC.component.Get() == peTarget )
          return attSC;
      }
      return peTarget;
    }

		//NUM_TASK
		//protected override void OnDockStateChanged( EventArgs e )
		//{
		//  System.Diagnostics.Debug.Print( "OnDockStateChanged" );
		//  base.OnDockStateChanged( e );
		//}

    #region Event Handlers

    private void OnAfterSelectNode( object sender, TreeViewEventArgs e )
    {
      if( refreshing.IsSuppressed )
        return;
	
			SelectNode( e.Node, true );
    }

    private void OnAfterCheckNode( object sender, TreeViewEventArgs e )
    {
    	if(refreshing.IsSuppressed)
    		return;

    	SetComponentVisibility(e.Node);
    }

  	private void OnNodeMouseClick( object sender, TreeNodeMouseClickEventArgs e )
		{
			if ( refreshing.IsSuppressed )
				return;

  		TreeViewHitTestInfo info = treeHierarchy.HitTest(e.Location);

			if ( info.Location == TreeViewHitTestLocations.Label 
				|| info.Location == TreeViewHitTestLocations.RightOfLabel
				|| info.Location == TreeViewHitTestLocations.Image )
			{
				// если текущая нода не меняется, 
				// то не возникает события OnAfterSelectNode, т.ч. приходится вызывать SelectNode тут
				if(treeHierarchy.SelectedNode == e.Node)
				{
					SelectNode( e.Node, true );
				}
			}
		}

		#endregion

		#region Helpers

		private int GetImageIndex( Type _type )
		{
			return application.Application.Extensions.GetTypeIconIndex( _type, true );
		}

		private AABB GetAABB( EditorSceneComponent _component )
		{
			DBID dbId = _component.GetDBID();
			DBResource resource = DataBase.Get<DBResource>( dbId ).Get();

			if ( resource == null )
				return null;

			if ( resource is DBStaticSceneComponent )
				return ( (DBStaticSceneComponent)resource ).aabb;

			if ( resource is DBAnimatedSceneComponent )
				return ( (DBAnimatedSceneComponent)resource ).aabb;

			if ( resource is DBParticleSceneComponent )
				return ( (DBParticleSceneComponent)resource ).aabb;

			return null;
		}

		private static List<Locator> RecursiveFindLocators( EditorSceneComponent _component )
		{
			List<Locator> locators = new List<Locator>();

			Action<EditorSceneComponent> action = component =>
			{
				DBSceneComponent dbSceneComponent = DataBase.Get<DBSceneComponent>( component.GetDBID() ).Get();

				if ( dbSceneComponent == null )
					return;

				LocatorList locatorList = dbSceneComponent.locatorList.Get();

				if ( locatorList != null )
					locators.AddRange( locatorList.locators );
			};

			ReursiveIterateComponents( _component, action );

			return locators;
		}

		private static void ReursiveIterateComponents( EditorSceneComponent _root, Action<EditorSceneComponent> _action )
		{
			if ( _root == null )
				return;

			_action( _root );

			foreach ( EditorSceneComponent component in _root.brothers )
			{
				_action( component );
			}

			if ( _root.child != null )
				ReursiveIterateComponents( _root.child, _action );

		}

		private void RestoreComponentsVisibility( TreeNodeCollection _nodes )
		{
			foreach ( ImprovedTreeNode node in _nodes )
			{
				if ( node.Checkable )
				{
					SetComponentVisibility(node);
				}
				
				RestoreComponentsVisibility( node.Nodes );
			}
		}

		private void SetComponentVisibility( TreeNode _node )
		{
			if ( _node.Tag is ComponentsInfo )
				( (ComponentsInfo)_node.Tag ).SetVisibility( _node.Checked );
		}

		private void SetNodeFont( TreeNode node, FontStyle fontStyle )
		{
			node.NodeFont = new Font( treeHierarchy.Font, fontStyle );
			if ( node is ImprovedTreeNode )
				( (ImprovedTreeNode)node ).AdditionalFont = new Font( treeHierarchy.AdditionalTextFont, fontStyle );
		}

		private bool IsValid
		{
			get { return !ReferenceEquals( controller, null ) && !ReferenceEquals( controller.Items, null ); }
		}

		#endregion
	}
}
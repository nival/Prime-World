using System;
using System.Collections.Generic;
using System.Text;
using EditorNative.SceneElements.SceneObjects;
using DBTypes;

namespace EditorPlugins.Scene.Editors.Widgets
{
  public abstract class TerrainPathsWidget : TargetPathWidgetBase
  {
    private GameSceneObject gameSceneObject = null;
    private bool reverseOrder = false;
    private DBNatureMapRoad road = null;

    public TerrainPathsWidget( EditorControl _control ) : base( _control ) { }

    public override void Create( GameSceneObject target )
    {
      gameSceneObject = target;
      MainBuilding mainBldg = target.GetGameObject() as MainBuilding;
      if ( mainBldg.faction == EFaction.Burn )
        reverseOrder = true;

      DBTypes.Terrain terrain = EditorControl.TerrainController.Resource;
      if ( EditorControl != null && EditorControl.SceneControl != null && EditorControl.SceneControl.IsShowAttackSpace )
        road = terrain.natureMap.attackSpaceRoads[GetRoadIndex()];
      else
        road = terrain.natureMap.logicRoads[GetRoadIndex()];

      base.Create( target );
    }

    protected abstract int GetRoadIndex();

    private int GetIndex( int index )
    {
      if ( reverseOrder )
        return road.nodes.Count - 1 - index;
      else
        return index;
    }

    protected override Vec2 GetPosition( int index )
    {
      return road.nodes[GetIndex( index )];
    }

    protected override int GetPositionCount()
    {
      return road.nodes.Count;
    }

    protected override bool CanAddTarget()
    {
      return true;
    }

    protected override Vec2 AddTarget( int index )
    {
      if ( index < 0 )
        index = road.nodes.Count;

      int realIndex = reverseOrder ? road.nodes.Count - index : index;

      road.nodes.Insert( realIndex, new Vec2() );

      Vec2 newPoint = road.nodes[realIndex];

      if ( road.nodes.Count == 1 )
      {
        newPoint.x = gameSceneObject.Location.X + 5;
        newPoint.y = gameSceneObject.Location.Y + 5;
      }
      else if ( index == 0 )
      {
        newPoint.x = ( gameSceneObject.Location.X + road.nodes[reverseOrder ? road.nodes.Count - 2 : 1].x ) * 0.5f;
        newPoint.y = ( gameSceneObject.Location.Y + road.nodes[reverseOrder ? road.nodes.Count - 2 : 1].y ) * 0.5f;
      }
      else if ( index == road.nodes.Count - 1 )
      {
        newPoint.x = road.nodes[reverseOrder ? 1 : road.nodes.Count - 2].x + 5;
        newPoint.y = road.nodes[reverseOrder ? 1 : road.nodes.Count - 2].y;
      }
      else
      {
        newPoint.x = ( road.nodes[realIndex + 1].x + road.nodes[realIndex - 1].x ) * 0.5f;
        newPoint.y = ( road.nodes[realIndex + 1].y + road.nodes[realIndex - 1].y ) * 0.5f;
      }

      return newPoint;
    }

    protected override bool CanDeleteTarget()
    {
      return road.nodes.Count > 1;
    }

    protected override void DeleteTarget( int index )
    {
      index = GetIndex( index );

      road.nodes.RemoveAt( index );
    }

    public override bool HasThisWidget( GameSceneObject target )
    {
      return true;
    }
  }

  [EditorControlWidget( typeof( MainBuilding ) )]
  public class TerrainPathsWidgetTop : TerrainPathsWidget
  {
    public TerrainPathsWidgetTop( EditorControl _control ) : base( _control ) { }
    protected override int GetRoadIndex() { return (int)DBTypes.ERoute.Top; }
  }

  [EditorControlWidget( typeof( MainBuilding ) )]
  public class TerrainPathsWidgetCenter : TerrainPathsWidget
  {
    public TerrainPathsWidgetCenter( EditorControl _control ) : base( _control ) { }
    protected override int GetRoadIndex() { return (int)DBTypes.ERoute.Center; }
  }

  [EditorControlWidget( typeof( MainBuilding ) )]
  public class TerrainPathsWidgetBottom : TerrainPathsWidget
  {
    public TerrainPathsWidgetBottom( EditorControl _control ) : base( _control ) { }
    protected override int GetRoadIndex() { return (int)DBTypes.ERoute.Bottom; }
  }
}

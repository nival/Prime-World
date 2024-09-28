using System;
using System.Collections.Generic;
using System.Text;
using DBTypes;
using EditorNative.SceneElements.SceneObjects;
using EditorNative;

namespace EditorPlugins.Scene.Editors.Widgets
{
  [EditorControlWidget( typeof( AdvMapCreepSpawner ) )]
  public class CommonSpawnerWidget : CreepSpawnerWidget
  {
    private AdvMapCreepSpawner spawner = null;

    public CommonSpawnerWidget(EditorControl _control) : base(_control) { }

    protected override libdb.IChangeableList<Vec2> Path()
    {
      return spawner.path;
    }

    public override void Create(GameSceneObject target)
    {
      spawner = target.GetGameObject() as AdvMapCreepSpawner;
      base.Create(target);
    }
  }

  [EditorControlWidget(typeof(AdvMapNeutralCreepSpawner))]
  public class NeutralSpawnerWidget : CreepSpawnerWidget
  {
    private AdvMapNeutralCreepSpawner spawner = null;

    public NeutralSpawnerWidget(EditorControl _control) : base(_control) { }

    protected override libdb.IChangeableList<Vec2> Path()
    {
      return spawner.path;
    }

    public override void Create(GameSceneObject target)
    {
      spawner = target.GetGameObject() as AdvMapNeutralCreepSpawner;
      base.Create(target);
    }
  }
  
  [EditorControlWidget( typeof( ScriptPath ) )]
  public class ScriptAreaWidget : CreepSpawnerWidget
  {
    private ScriptPath pathObj = null;

    public ScriptAreaWidget( EditorControl _control ) : base( _control ) { }

    protected override libdb.IChangeableList<Vec2> Path()
    {
      return pathObj.path;
    }

    public override void Create( GameSceneObject target )
    {
      pathObj = target.GetGameObject() as ScriptPath;
      base.Create( target );
    }
  }

  public abstract class CreepSpawnerWidget : TargetPathWidgetBase
  {
    private GameSceneObject gameSceneObject = null;
    
    protected abstract libdb.IChangeableList<Vec2> Path();

    public CreepSpawnerWidget(EditorControl _control) : base(_control) { }

    public override bool HasThisWidget( GameSceneObject target )
    {
      return true;
    }

    public override void Create( GameSceneObject target )
    {
      gameSceneObject = target;

      base.Create( target );
    }

    protected override Vec2 GetPosition( int index )
    {
      return Path()[index];
    }

    protected override int GetPositionCount()
    {
      return Path().Count;
    }

    protected override Vec2 AddTarget( int index )
    {
      if ( index > Path().Count || index < 0 )
        index = Path().Count;

      Path().Insert( index, new Vec2() );
      Vec2 newItem = Path()[index];

      Vector3 prevPoint = null;
      if ( index == 0 )
        prevPoint = gameSceneObject.Location;
      else
      {
        prevPoint = new Vector3( Path()[index - 1].x, Path()[index - 1].y, 0 );
      }

      newItem.x = prevPoint.X;
      newItem.y = prevPoint.Y;

      if ( index == Path().Count - 1 )
      {
        newItem.x += 5;
      }
      else
      {
        Vec2 nextPoint = Path()[index + 1];
        newItem.x = ( newItem.x + nextPoint.x ) * 0.5f;
        newItem.y = ( newItem.y + nextPoint.y ) * 0.5f;
      }

      return newItem;
    }

    protected override void DeleteTarget( int index )
    {
      if ( index >= Path().Count || index < 0 )
        return;

      Path().RemoveAt( index );
    }

    protected override bool CanAddTarget()
    {
      return true;
    }

    protected override bool CanDeleteTarget()
    {
      return Path().Count > 0;
    }
  }
}

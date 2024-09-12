using DBTypes;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Editors;
using libdb.DB;
using System.Collections.Generic;
using EditorNative;

namespace PF_Editor.Map.AdvMapObjects
{
	internal sealed class AddObjectController : AddEntityController
	{
    private readonly List<AdvMapObject> advMapObjects = null;
    private readonly List<PointLightInfo> pointLights = null;
    private readonly List<ScriptArea> scriptAreas = null;
    private readonly AdvMapEditor editor = null;

    private static GameSceneObject[] CreateSceneObject(AdvMapEditor editor, GameObject gameObject)
    {
      AdvMapObject advMapObject = new AdvMapObject();
      advMapObject.gameObject = DataBase.Get<GameObject>( gameObject.DBId );

      //т.к. этот метод вызывается только при селекте объекта в ObjectBrowser, то просим нам создать ControllableVisualObject НЕ ДЛЯ ПОСТАНОВКИ НА КАРТУ (false)
      GameSceneObject obj = ControllableVisualObject.CreateVisualObject(editor.EditorControl, advMapObject, false);
      return new [] { obj };
    }

    private static GameSceneObject[] CreateSceneObject(AdvMapEditor editor, PointLightGameObject gameObject)
    {
      PointLightInfo advMapObject = new PointLightInfo();      
      GameSceneObject obj = ControllableVisualObject.CreateVisualObject(editor.EditorControl, advMapObject, false);
      return new [] { obj };
    }

    private static GameSceneObject[] CreateSceneObject( AdvMapEditor editor, ScriptAreaGameObject gameObject )
    {
      ScriptArea advMapObject = new ScriptArea();
      GameSceneObject obj = ControllableVisualObject.CreateVisualObject( editor.EditorControl, advMapObject, false );
      return new[] { obj };
    }

    private static GameSceneObject[] CreateSceneObjects(AdvMapEditor editor, List<AdvMapObject> advMapObjects, List<PointLightInfo> pointLights, List<ScriptArea> scriptAreas)
    {
      List<GameSceneObject> result = new List<GameSceneObject>();
      if (advMapObjects != null)
      {
        foreach (AdvMapObject advMapObject in advMapObjects)
        {
          GameObject gameObject = advMapObject.gameObject.Get();
          if (gameObject == null || DBID.IsNullOrEmpty(gameObject.DBId) /*|| ( DBID.IsNullOrEmpty( gameObject.visualObject.DBId ) )*/ )
            continue;

          GameSceneObject obj = ControllableVisualObject.CreateVisualObject(editor.EditorControl, advMapObject, false);

          Placement place = new Placement();
          PlacementConverter converter = new PlacementConverter();
          converter.convertPlacement( advMapObject.offset, place );

          obj.Location = new Vector3( place.location.x, place.location.y, 0.0f );
          obj.Rotation = new Quaternion(place.rotation.x, place.rotation.y, place.rotation.z, place.rotation.w);
          obj.Scale = new Vector3( place.scale.x, place.scale.y, place.scale.z );
          result.Add(obj);
        }
      }
      if (pointLights != null)
      {
        foreach (PointLightInfo pointLight in pointLights)
        {
          GameSceneObject obj = ControllableVisualObject.CreateVisualObject(editor.EditorControl, pointLight, false);
          obj.Location = new Vector3(pointLight.location.x, pointLight.location.y, 0.0f);
          result.Add(obj);
        }
      }
      if ( scriptAreas != null )
      {
        foreach ( ScriptArea scriptArea in scriptAreas )
        {
          GameSceneObject obj = ControllableVisualObject.CreateVisualObject( editor.EditorControl, scriptArea, false );
          obj.Location = new Vector3( scriptArea.position.x, scriptArea.position.y, 0.0f );
          result.Add( obj );
        }
      }
      return result.ToArray();
    }

    internal AddObjectController( AdvMapEditor editor, GameObject gameObject )
      : base( editor.EditorControl.SceneControl, CreateSceneObject( editor, gameObject ) )
    {
      this.editor = editor;

      AdvMapObject advMapObject = new AdvMapObject();
      advMapObject.gameObject = DataBase.Get<GameObject>( gameObject.DBId );

      advMapObjects = new List<AdvMapObject>();
      advMapObjects.Add( advMapObject );
    }

    internal AddObjectController( AdvMapEditor editor, PointLightGameObject gameObject )
      : base( editor.EditorControl.SceneControl, CreateSceneObject( editor, gameObject ) )
    {
      this.editor = editor;

      PointLightInfo advMapObject = new PointLightInfo();
      pointLights = new List<PointLightInfo>();
      pointLights.Add( advMapObject );
    }

    internal AddObjectController( AdvMapEditor editor, ScriptAreaGameObject gameObject )
      : base( editor.EditorControl.SceneControl, CreateSceneObject( editor, gameObject ) )
    {
      this.editor = editor;

      ScriptArea advMapObject = new ScriptArea();
      scriptAreas = new List<ScriptArea>();
      scriptAreas.Add( advMapObject );
    }

    internal AddObjectController( AdvMapEditor editor, List<AdvMapObject> advMapObjects, List<PointLightInfo> pointLights, List<ScriptArea> scriptAreas )
      : base( editor.EditorControl.SceneControl, CreateSceneObjects( editor, advMapObjects, pointLights, scriptAreas ) )
    {
      this.editor = editor;
      this.advMapObjects = advMapObjects;
      this.pointLights = pointLights;
      this.scriptAreas = scriptAreas;
    }

    protected override AddEntityController PerformAddition( float x, float y )
		{
      if (advMapObjects != null)
      {
        foreach (AdvMapObject obj in advMapObjects)
        {
          obj.offset.translateX += x;
          obj.offset.translateY += y;
        }
     
        editor.Add(advMapObjects);

        foreach (AdvMapObject obj in advMapObjects)
        {
          obj.offset.translateX -= x;
          obj.offset.translateY -= y;
        }
      }
      if (pointLights != null)
      {
        foreach (PointLightInfo obj in pointLights)
        {
          obj.location.x += x;
          obj.location.y += y;
        }
        editor.Add(pointLights);

        foreach (PointLightInfo obj in pointLights)
        {
          obj.location.x -= x;
          obj.location.y -= y;
        }
      }
      if ( scriptAreas != null )
      {
        foreach ( ScriptArea obj in scriptAreas )
        {
          obj.position.x += x;
          obj.position.y += y;
        }
        editor.Add( scriptAreas );

        foreach ( ScriptArea obj in scriptAreas )
        {
          obj.position.x -= x;
          obj.position.y -= y;
        }
      }
      return new AddObjectController( editor, advMapObjects, pointLights, scriptAreas );
    }
	}
}

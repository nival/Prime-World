using System;
using System.Collections.Generic;
using DBTypes;
using EditorNative;
using EditorPlugins.Scene.Editors;
using libdb.Diagnostics;

namespace PF_Editor.Map.AdvMapObjects
{
  internal sealed class AdvMapController
  {
    #region Private members.

    private readonly AdvMap map;
    private readonly EditorControl editorControl;

    private readonly ListObserver<AdvMapObject> mapObjects = null;
    private readonly ListObserver<PointLightInfo> pointLights = null;
    private readonly ListObserver<ScriptArea> scriptAreas = null;   

    private bool objectsSelectable = true;

    #endregion

    #region Initialization.

    internal AdvMapController( AdvMap _map, EditorControl _editor )
    {
      map = _map;
      editorControl = _editor;

      mapObjects = new ListObserver<AdvMapObject>( _map.objects );
      mapObjects.Initialize( CreateVisualObject );
      mapObjects.OnControllerRemovedEvent += OnVisualObjectRemoved;

      //Debug.Print("_time=" + _time.TotalMilliseconds + " ms");

      pointLights = new ListObserver<PointLightInfo>( _map.pointLights );
      pointLights.Initialize( CreateVisualObject );
      pointLights.OnControllerRemovedEvent += OnVisualObjectRemoved;

      scriptAreas = new ListObserver<ScriptArea>( _map.scriptAreas );
      scriptAreas.Initialize( CreateVisualObject );
      scriptAreas.OnControllerRemovedEvent += OnVisualObjectRemoved;
    }

    public void Release()
    {
      mapObjects.OnControllerRemovedEvent -= OnVisualObjectRemoved;
      pointLights.OnControllerRemovedEvent -= OnVisualObjectRemoved;
      scriptAreas.OnControllerRemovedEvent -= OnVisualObjectRemoved;
 
      mapObjects.Unsubscribe();
      pointLights.Unsubscribe();
      scriptAreas.Unsubscribe();
    }

    #endregion

    #region Overrides.

    //private TimeSpan _time;
    private ControllableVisualObject CreateVisualObject( AdvMapObject _advMapObject )
    {
      if( !_advMapObject.gameObject.IsValid )
      {
        Log.TraceWarning( "Game object is not valid." );
        return null;
      }

      GameObject gameObject = _advMapObject.gameObject.Get();

      if( gameObject == null )
      {
        Log.TraceWarning( "Game object is not valid." );
        return null;
      }

      //добавляем объект на карту
      //DateTime t = DateTime.UtcNow;
      ControllableVisualObject result = AddToScene( ControllableVisualObject.CreateVisualObject( editorControl, _advMapObject, true ) );
                         
      if ( SelectAfterAdd )
        result.IsSelected = true;
      //_time = _time + (DateTime.UtcNow - t);

      return result;
    }

    private ControllableVisualObject CreateVisualObject( PointLightInfo _pointLightInfo )
    {
      return AddToScene( ControllableVisualObject.CreateVisualObject( editorControl, _pointLightInfo, true ) );
    }

    private ControllableVisualObject CreateVisualObject( ScriptArea _scriptArea )
    {
      return AddToScene( ControllableVisualObject.CreateVisualObject( editorControl, _scriptArea, true ) );
    }

    private void OnVisualObjectRemoved( ControllableVisualObject visualObject )
    {
      Scene.Remove( visualObject );
    }

    #endregion

    #region Internal methods.

    internal void Remove( object obj )
    {
      if( obj is AdvMapObject )
      {
        map.objects.Remove( obj as AdvMapObject );
      }
      else if( obj is PointLightInfo )
      {
        map.pointLights.Remove( obj as PointLightInfo );
      }
      else if ( obj is ScriptArea )
      {
        map.scriptAreas.Remove( obj as ScriptArea );
      }
    }

    internal void BeginAdditionToScene( AdvMapEditor editor, GameObject obj )
    {
      editorControl.BeginEntityAddition( new AddObjectController( editor, obj ) );
    }

    internal void BeginAdditionToScene( AdvMapEditor editor, PointLightGameObject obj )
    {
      editorControl.BeginEntityAddition( new AddObjectController( editor, obj ) );
    }

    internal void BeginAdditionToScene( AdvMapEditor editor, ScriptAreaGameObject obj )
    {
      editorControl.BeginEntityAddition( new AddObjectController( editor, obj ) );
    }

    internal void BeginAdditionToScene( AdvMapEditor editor, List<AdvMapObject> objects, List<PointLightInfo> lights, List<ScriptArea> scriptAreas, bool select )
    {
      //SelectAfterAdd = select;
      editorControl.BeginEntityAddition( new AddObjectController( editor, objects, lights, scriptAreas ) );
    }

    #endregion

    #region Internal properties.

    internal bool SelectAfterAdd { get; set; }
       
    internal bool ObjectsSelectable
    {
      get { return objectsSelectable; }
      set
      {
        objectsSelectable = value;
        SetSelectable(mapObjects.VisualObjects, value);
        SetSelectable(pointLights.VisualObjects, value);
        SetSelectable(scriptAreas.VisualObjects, value);
      }
    }

    private void SetSelectable(IEnumerable<ControllableVisualObject> objects, bool isSelectable)
    {
      foreach ( ControllableVisualObject obj in objects )
      {
        if ( obj != null ) obj.IsSelectable = isSelectable;
      }
    }

    internal AdvMap Map
    {
      get { return map; }
    }

    #endregion

    #region Private properties.

    private EditorScene Scene
    {
      get { return editorControl.SceneControl.Scene; }
    }

    #endregion

    #region Private helper methods.

    private ControllableVisualObject AddToScene( ControllableVisualObject sceneObject )
    {
      sceneObject.IsSelectable = true;
      Scene.Add( sceneObject );
      if( sceneObject.IsMSO() && Scene.HasTerrain )
      {
        int nature = Scene.SceneTerrain.GetFraction( sceneObject.Location.X, sceneObject.Location.Y );
        sceneObject.SetSceneObject( nature );
      }
      sceneObject.OnChanged( this, EventArgs.Empty );
      return sceneObject;
    }

    #endregion
  }
}

using System;
using System.Collections.Generic;
using System.Drawing.Imaging;
using DBTypes;
using EditorLib;
using EditorLib.Operations;
using EditorNative;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;
using EditorNative.Terrain;
using EditorPlugins.Scene.Editors.Terrain;
using EditorPlugins.Utils;
using libdb.Diagnostics;
using System.Text;
using System.Drawing;
using libdb.DB;

namespace EditorPlugins.Importer.Relight
{
  public class FakeGSO : GameSceneObject
  {
    public FakeGSO( AdvMapObject advMapObject, bool placeToMap )
      : base( advMapObject.gameObject, 0, placeToMap, advMapObject.scriptGroupName )
		{
		}

    protected override List<DBID> InitSceneObjects( GameObject gameObj )
    {
      List<DBID> sceneObjects = new List<DBID>();
      if ( gameObj is SingleStateObject )
      {
        SingleStateObject sso = gameObj as SingleStateObject;

        if ( sso.sceneObject.IsValid )
          sceneObjects.Add( sso.sceneObject.DBId );

        if ( gameObj is Building )
        {
          Building building = gameObj as Building;
          if ( building.ruinSceneObject.IsValid )
            sceneObjects.Add( building.ruinSceneObject.DBId );
        }
      }
      else if ( gameObj is MultiStateObject )
      {
        MultiStateObject mso = gameObj as MultiStateObject;

        foreach ( DBPtr<DBSceneObject> so in mso.sceneObjects )
        {
          if ( so.IsValid )
            sceneObjects.Add( so.DBId );
          else
            sceneObjects.Add( DBID.Empty );
        }

        foreach (DBPtr<DBSceneObject> so in mso.nightSceneObjects)
        {
          if (so.IsValid)
            sceneObjects.Add(so.DBId);
          else
            sceneObjects.Add(DBID.Empty);
        }

        if ( gameObj is TreeObject )
        {
          TreeObject tree = gameObj as TreeObject;

          foreach ( DBPtr<DBSceneObject> so in tree.stubsSceneObjects )
          {
            if ( so.IsValid )
              sceneObjects.Add( so.DBId );
          }

          foreach (DBPtr<DBSceneObject> so in tree.nightStubsSceneObjects)
          {
            if (so.IsValid)
              sceneObjects.Add(so.DBId);
          }
        }
      }
      else if ( gameObj is AdvMapCreepSpawner )
      {
        AdvMapCreepSpawner spawner = gameObj as AdvMapCreepSpawner;
        if ( spawner.creeps.Count > 0 )
        {
          if ( spawner.creeps[0].creep.IsValid )
            if ( spawner.creeps[0].creep.Get().sceneObject.IsValid )
              sceneObjects.Add( spawner.creeps[0].creep.Get().sceneObject.DBId );
        }
        else
        {
          Log.TraceWarning( "Creep Spawner does not contain a creeps \"{0}\" with type \"{1}\"", gameObj.DBId.ToString(), gameObj.GetType().Name );
        }
      }
      else if ( gameObj is AdvMapNeutralCreepSpawner )
      {
        AdvMapNeutralCreepSpawner spawner = gameObj as AdvMapNeutralCreepSpawner;
        if ( spawner.groups.Count > 0 && spawner.groups[0].creeps.Count > 0 )
        {
          if ( spawner.groups[0].creeps[0].creep.IsValid )
            if ( spawner.groups[0].creeps[0].creep.Get().sceneObject.IsValid )
              sceneObjects.Add( spawner.groups[0].creeps[0].creep.Get().sceneObject.DBId );
        }
        else
        {
          Log.TraceWarning( "Neutral Creep Spawner does not contain a creeps \"{0}\" with type \"{1}\"", gameObj.DBId.ToString(), gameObj.GetType().Name );
        }
      }
      else if ( gameObj is AdvMapWaterZone )
      {
        sceneObjects.Add( DBID.FromString( "Tech/Default/Flag.SOBJ" ) );
      }
      else if ( gameObj is AdvMapObstacle )
      {
        sceneObjects.Add( DBID.FromString( "Tech/Default/Default.SOBJ" ) );
      }
      else if ( gameObj is ScriptAreaGameObject )
      {
        sceneObjects.Add( DBID.FromString( "Tech/Default/FlagBlue.SOBJ" ) );
      }
      else if ( gameObj is ScriptPolygonArea )
      {
        sceneObjects.Add( DBID.FromString( "Tech/Default/FlagMagenta.SOBJ" ) );
      }
      else if ( gameObj is AdvMapCameraSpline )
      {
        sceneObjects.Add( DBID.FromString( "Tech/Default/Camera.SOBJ" ) );
      }
      else
      {
        Log.TraceWarning( "Cannot create visual object for GameObject \"{0}\" with type \"{1}\"", gameObj.DBId.ToString(), gameObj.GetType().Name );
      }

      if ( sceneObjects.Count == 0 )
      {
        DBID id = DBID.FromString( "/Tech/Default/FlagBlue.SOBJ" );
        sceneObjects.Add( id );
      }

      return sceneObjects;
    }
  }

  public static class RelightMap
  {
    public static bool Process( DBID mapId )
    {
      var map = DataBase.Get<AdvMap>( mapId );
      if ( !map.IsValid )
      {
        Log.TraceError( "Map is bad" );
        return false;
      }
      if ( !map.Get().terrain.IsValid )
      {
        Log.TraceError( "Terrain is bad" );
        return false;
      }

      EditorScene scene = new EditorScene( new IntPtr( 0 ), new Size(), null, false );

      // Загрузка террейна
      var terrainController = new TerrainController( map.Get().terrain );
      scene.SceneTerrain = terrainController.Terrain;
      scene.InitLightScene();
      scene.SceneTerrain.UpdateHeightsController();

      // Загрузка объектов карты
      List<RoadWrapper> roads = new List<RoadWrapper>();
      string roadBakedLighting = "";
      foreach( var advMapObject in map.Get().objects )
      {
        if ( advMapObject.gameObject.IsValid )
        {
          if ( advMapObject.gameObject.Get() is Road )
          {
            roads.Add( new RoadWrapper( advMapObject.gameObject.Get() as Road, advMapObject.offset, scene ) );
            roadBakedLighting = (advMapObject.gameObject.Get() as Road).bakedFileName;
          }

          var sceneObject = new FakeGSO( advMapObject, true );

          Placement place = new Placement();
          PlacementConverter converter = new PlacementConverter();
          converter.convertPlacement( advMapObject.offset, place );
          Quat quat = new Quat();
          quat.x = place.rotation.x;
          quat.y = place.rotation.y;
          quat.z = place.rotation.z;
          quat.w = place.rotation.w;

          sceneObject.Location = new Vector3( place.location.x, place.location.y, place.location.z );
          sceneObject.Rotation = new Quaternion( quat.x, quat.y, quat.z, quat.w );
          sceneObject.Scale = new Vector3( place.scale.x, place.scale.y, place.scale.z );

          scene.Add( sceneObject );
          if ( sceneObject.IsMSO() && scene.HasTerrain )
          {
            int nature = scene.SceneTerrain.GetFraction( sceneObject.Location.X, sceneObject.Location.Y );
            sceneObject.SetSceneObject( nature );
          }
        }
      }

      // Загрузка источников света
      foreach ( var light in map.Get().pointLights )
      {
        var sceneObject = new GameSceneObject( DataBase.Get<GameObject>( DBID.FromString( "Tech/Default/Bulb.SMPL" ) ), 0, "" );
        sceneObject.CreateLight();
        scene.Add( sceneObject );
        if ( sceneObject.IsMSO() && scene.HasTerrain )
        {
          int nature = scene.SceneTerrain.GetFraction( sceneObject.Location.X, sceneObject.Location.Y );
          sceneObject.SetSceneObject( nature );
        }
        sceneObject.UpdateLightInfo( light );
        sceneObject.isPlaceOnTerrain = false;
      }

      // Считаем свет
      scene.InitBakedLighting( map.Get().bakedLighting );
      scene.SetDayLightEnvironment( map.Get().lightEnvironment == null ? DBID.Empty : map.Get().lightEnvironment.DBId );
      scene.SetNightLightEnvironment(map.Get().nightLightEnvironment == null ? DBID.Empty : map.Get().nightLightEnvironment.DBId);
      scene.CalculateLightingObjects();

      // Считаем высоты
      scene.Draw( new IntPtr( 0 ), 0.0f, 0.0f );
      scene.CalcObjectHeightMap();
      scene.ReplaceAllObjectsOnTerrain();
      
      // Relight
      scene.TryFullReload();
      scene.SceneTerrain.TryFullLoad();
      scene.InitBakedLighting( map.Get().bakedLighting );
      scene.SetDayLightEnvironment( map.Get().lightEnvironment == null ? DBID.Empty : map.Get().lightEnvironment.DBId );
      scene.SetNightLightEnvironment(map.Get().nightLightEnvironment == null ? DBID.Empty : map.Get().nightLightEnvironment.DBId);
      scene.CalculateLighting();
      foreach ( var road in roads )
      {
        road.Rebuild();
      }

      // Сохраняем все
      var sceneElements = scene.GetSceneElements();
      var gameObjects = new List<GameSceneObject>( sceneElements.Count );
      foreach ( var element in sceneElements )
      {
        if ( element is GameSceneObject )
          gameObjects.Add( (GameSceneObject)element );
      }

      EditorScene.BuildVertexColorDB( gameObjects, map.Get().bakedLighting.vertexColorsFileName );
      StuffUtils.StoreAdvMapWaterZone( map.Get(), 1024 );
      foreach ( var road in roads )
      {
        road.Store( roadBakedLighting );
      }

      scene.SceneTerrain.StoreBinaryData( terrainController.ElementsOrder );
      scene.CalcObjectHeightMap();
      scene.ReplaceAllObjectsOnTerrain();
      scene.SaveObjectLayer( map.Get().ObjectsLayerFileName );

      return true;
    }
  }
}

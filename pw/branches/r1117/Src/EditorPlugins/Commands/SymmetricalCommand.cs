using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.Menu;
using EditorLib.ObjectsBrowser;
using EditorLib.Operations;
using EditorNative;
using EditorNative.Terrain;
using EditorPlugins.Forms;
using EditorPlugins.ObjectLayers;
using libdb;
using libdb.DB;

namespace EditorPlugins.SymmetricalCommand
{
  public sealed class SymmetricalCommand : IEditorCommand
  {
    private BindingList<ObjectLayersPreset> presets = new BindingList<ObjectLayersPreset>();
    private readonly float SIZE_OF_PATCH = 10.0f;
    private IEditorWinApplication application = null;
    private DBPtr<AdvMap> advmap = null;
    private SymmetricalForm form = null;

    private bool Work( IOperationContext context )
    {
      System.Diagnostics.Stopwatch timeCount = new System.Diagnostics.Stopwatch();
      timeCount.Start();

      Run( advmap.Get(), form.IsTerrainChecked(), form.IsPointLightsChecked(), form.IsScriptAreasChecked(), form.GetCheckedObjectLayers(), form.IsRightToLeft(), context );

      context.Progress( "Save map...", 50 );
      application.Application.Extensions.EditorStoreMap( advmap.DBId, application );
      context.Progress( "Save map...", 90 );
      DataBase.Store();
      context.Progress( "Save map...", 95 );
      var editor = EditorsPool.GetEditorForObject( advmap.DBId );
      EditorsPool.UnregisterEditor( advmap.DBId, editor );
      context.Progress( "Save map...", 97 );
      application.Application.FileSystem.Store();
      context.Progress( "Save map...", 100 );

      timeCount.Stop();
      MessageBox.Show( "All work done! Time elapsed: " + timeCount.Elapsed.ToString(), "Symmetrical script", MessageBoxButtons.OK, MessageBoxIcon.Asterisk );

      return true;
    }

    public override void Execute( IEditorWinApplication _application )
    {
      application = _application;
      ObjectLayersConfig config = application.Application.Settings.Get<ObjectLayersConfig>();

      if ( config != null && config.Presets != null )
        presets = new BindingList<ObjectLayersPreset>( config.Presets );

      ObjectsBrowserPanel panel = application.Panels.GetSingletonPanel<ObjectsBrowserPanel>();
      if ( panel == null )
      {
        MessageBox.Show( "Please open objects browser", "Error", MessageBoxButtons.OK, MessageBoxIcon.Asterisk );
        return;
      }

      DBID obj = panel.SelectedObject();
      if ( obj == null )
      {
        MessageBox.Show( "Please select map in objects browser", "Error", MessageBoxButtons.OK, MessageBoxIcon.Asterisk );
        return;
      }

      advmap = DataBase.Get<AdvMap>( obj );
      if ( advmap == null || advmap.Get() == null )
      {
        MessageBox.Show( "Please select map in objects browser", "Error", MessageBoxButtons.OK, MessageBoxIcon.Asterisk );
        return;
      }

      var testedit = EditorsPool.GetEditorForObject( obj );
      if ( testedit != null )
      {
        MessageBox.Show( "Please close map editor", "Error", MessageBoxButtons.OK, MessageBoxIcon.Asterisk );
        return;
      }

      form = new SymmetricalForm( application, presets );

      if ( form.ShowDialog() == DialogResult.OK )
      {
        application.Application.OperationExecutor.Start( Work );
      }
    }

    float GetLength( float x, float y )
    {
      return (float)Math.Sqrt( x*x + y*y );
    }

    private TerrainElementInstance GetNearestTE( float x, float y, IChangeableList<TerrainElementInstance> listElements )
    {
      TerrainElementInstance te = listElements[0];
      float length = GetLength( x - listElements[0].position.x, y - listElements[0].position.y );

      for ( int i = 0; i < listElements.Count; i++ )
      {
        float curLen = GetLength( x - listElements[i].position.x, y - listElements[i].position.y );
        if ( curLen < length )
        {
          te = listElements[i];
          length = curLen;
        }
      }
      return te;
    }

    private void Run( AdvMap map, bool terrain, bool light, bool scripts, List<string> objects, bool right_to_left, IOperationContext context )
    {
      context.Start( true, true );
      context.Progress( "Preparing...", 1 );

      var sizeX = SIZE_OF_PATCH * map.terrain.Get().elemXCount;
      var sizeY = SIZE_OF_PATCH * map.terrain.Get().elemYCount;

      var scene = new SimpleEditorScene( new IntPtr(0), new Size() );

      DataBase.UndoRedoManager.Start( "Symmetric Script" );

      context.Progress( "Convet terrain...", 25 );
      if ( terrain && scene != null )
      {
        var ter = new EditorTerrain( map.terrain, true );
        ter.SymmetricalTerrain( sizeX, map.terrain.Get().elemXCount + 1, map.terrain.Get().elemYCount + 1, right_to_left );
        for( int i = 0; i < map.terrain.Get().geometry.terrainElements.Count; i++ )
        {
          if ( ( !right_to_left && map.terrain.Get().geometry.terrainElements[i].position.x > sizeX / 2 ) 
            || ( right_to_left && map.terrain.Get().geometry.terrainElements[i].position.x < sizeX / 2 ) )
          {
            var te = map.terrain.Get().geometry.terrainElements[i];
            var oldte = GetNearestTE( sizeX - te.position.x, sizeY - te.position.y,
                                      map.terrain.Get().geometry.terrainElements );
            te.angle = oldte.angle > 180.0f ? oldte.angle - 180.0f : oldte.angle + 180.0f;
            te.terrainObject = oldte.terrainObject;
            te.material = oldte.material;
          }
        }

        var natureMap = map.terrain.Get().natureMap;
        for( int roadIdx = 0; roadIdx < natureMap.attackSpaceRoads.Count; roadIdx++ )
        {
          var road = natureMap.attackSpaceRoads[roadIdx];
          for( int i = 0; i < road.nodes.Count; i++ )
          {
            if( ( !right_to_left && road.nodes[i].x > sizeX/2 )
              || ( right_to_left && road.nodes[i].x < sizeX / 2 ) )
            {
              road.nodes.RemoveAt( i );
              i--;
            }
          }
        }

        for ( int roadIdx = 0; roadIdx < natureMap.logicRoads.Count; roadIdx++ )
        {
          var road = natureMap.logicRoads[roadIdx];
          for ( int i = 0; i < road.nodes.Count; i++ )
          {
            if ( ( !right_to_left && road.nodes[i].x > sizeX / 2 )
              || ( right_to_left && road.nodes[i].x < sizeX / 2 ) )
            {
              road.nodes.RemoveAt( i );
              i--;
            }
          }
        }

        List<List<Vector2>> roadsMap = new List<List<Vector2>>();
        for ( int roadIdx = 0; roadIdx < natureMap.attackSpaceRoads.Count; roadIdx++ )
        {
          List<Vector2> temp = new List<Vector2>();
          var road = natureMap.attackSpaceRoads[roadIdx];
          foreach( var v in road.nodes )
          {
            temp.Add( new Vector2( v.x, v.y ) );
          }  
          roadsMap.Add( temp );
        }

        for ( int roadIdx = 0; roadIdx < natureMap.attackSpaceRoads.Count; roadIdx++ )
        {
          var road = natureMap.attackSpaceRoads[roadIdx];
          var opproad = natureMap.attackSpaceRoads[natureMap.attackSpaceRoads.Count - roadIdx - 1];
          int roadNodesCount = roadsMap[natureMap.attackSpaceRoads.Count - roadIdx - 1].Count;
          if ( !right_to_left )
          {
            for ( int i = roadNodesCount - 1; i >= 0; i-- )
            {
              Vec2 node = new Vec2( opproad.nodes[i].GetOwner(), opproad.nodes[i] );
              node.x = sizeX - roadsMap[natureMap.attackSpaceRoads.Count - roadIdx - 1][i].X;
              node.y = sizeY - roadsMap[natureMap.attackSpaceRoads.Count - roadIdx - 1][i].Y;
              if ( Math.Abs(node.x - sizeX/2) < 0.2f )
                continue;
              road.nodes.Add( node );
            }
          }
          else
          {
            for ( int i = 0; i < roadNodesCount; i++ )
            {
              Vec2 node = new Vec2( opproad.nodes[i].GetOwner(), opproad.nodes[i] );
              node.x = sizeX - roadsMap[natureMap.attackSpaceRoads.Count - roadIdx - 1][i].X;
              node.y = sizeY - roadsMap[natureMap.attackSpaceRoads.Count - roadIdx - 1][i].Y;
              if ( Math.Abs( node.x - sizeX / 2 ) < 0.2f )
                continue;
              road.nodes.Insert( 0, node );
            }
          }
        }

        roadsMap = new List<List<Vector2>>();
        for ( int roadIdx = 0; roadIdx < natureMap.logicRoads.Count; roadIdx++ )
        {
          List<Vector2> temp = new List<Vector2>();
          var road = natureMap.logicRoads[roadIdx];
          foreach ( var v in road.nodes )
          {
            temp.Add( new Vector2( v.x, v.y ) );
          }
          roadsMap.Add( temp );
        }

        for ( int roadIdx = 0; roadIdx < natureMap.logicRoads.Count; roadIdx++ )
        {
          var road = natureMap.logicRoads[roadIdx];
          var opproad = natureMap.logicRoads[natureMap.logicRoads.Count - roadIdx - 1];
          int roadNodesCount = roadsMap[natureMap.logicRoads.Count - roadIdx - 1].Count;
          if ( !right_to_left )
          {
            for ( int i = roadNodesCount - 1; i >= 0; i-- )
            {
              Vec2 node = new Vec2( opproad.nodes[i].GetOwner(), opproad.nodes[i] );
              node.x = sizeX - roadsMap[natureMap.logicRoads.Count - roadIdx - 1][i].X;
              node.y = sizeY - roadsMap[natureMap.logicRoads.Count - roadIdx - 1][i].Y;
              if ( Math.Abs( node.x - sizeX / 2 ) < 0.2f )
                continue;
              road.nodes.Add( node );
            }
          }
          else
          {
            for ( int i = 0; i < roadNodesCount; i++ )
            {
              Vec2 node = new Vec2( opproad.nodes[i].GetOwner(), opproad.nodes[i] );
              node.x = sizeX - roadsMap[natureMap.logicRoads.Count - roadIdx - 1][i].X;
              node.y = sizeY - roadsMap[natureMap.logicRoads.Count - roadIdx - 1][i].Y;
              if ( Math.Abs( node.x - sizeX / 2 ) < 0.2f )
                continue;
              road.nodes.Insert( 0, node );
            }
          }
        }
        
        if ( !right_to_left )
        {
          natureMap.baseBOffset = natureMap.baseAOffset;
          natureMap.baseB.x = sizeX - natureMap.baseA.x;
          natureMap.baseB.y = sizeY - natureMap.baseA.y;
        }
        else
        {
          natureMap.baseAOffset = natureMap.baseBOffset;
          natureMap.baseA.x = sizeX - natureMap.baseB.x;
          natureMap.baseA.y = sizeY - natureMap.baseB.y;
        }
      }

      context.Progress( "Convet light...", 27 );
      if ( light )
      {
        // убивание половины карты
        for ( int i = 0; i < map.pointLights.Count; i++ )
        {
          if ( ( !right_to_left && map.pointLights[i].location.x > sizeX / 2 ) 
            || ( right_to_left && map.pointLights[i].location.x < sizeX / 2 ) )
          {
            map.pointLights.RemoveAt( i );
            i--;
          }
        }

        // поворот оставшейся половины карты
        int pointLightsCount = map.pointLights.Count;
        for ( int i = 0; i < pointLightsCount; i++ )
        {
          PointLightInfo pLight = new PointLightInfo( map.pointLights[i].GetOwner(), map.pointLights[i] );
          pLight.location.x = sizeX - pLight.location.x;
          pLight.location.y = sizeY - pLight.location.y;
          map.pointLights.Add( pLight );
        }
      }

      context.Progress( "Convet scripts...", 30 ); 
      if ( scripts )
      {
        // убивание половины карты
        for ( int i = 0; i < map.scriptAreas.Count; i++ )
        {
          if ( ( !right_to_left && map.scriptAreas[i].position.x > sizeX / 2 ) 
            || ( right_to_left && map.scriptAreas[i].position.x < sizeX / 2 ) )
          {
            map.scriptAreas.RemoveAt( i );
            i--;
          }
        }

        // поворот оставшейся половины карты
        int scriptAreasCount = map.scriptAreas.Count;
        for ( int i = 0; i < scriptAreasCount; i++ )
        {
          ScriptArea pScript = new ScriptArea( map.scriptAreas[i].GetOwner(), map.scriptAreas[i] );
          pScript.position.x = sizeX - pScript.position.x;
          pScript.position.y = sizeY - pScript.position.y;
          map.scriptAreas.Add( pScript );
        }
      }

      context.Progress( "Gathering objects...", 33 );
      Dictionary<DBID, List<AdvMapObject>> advMapObjects = new Dictionary<DBID, List<AdvMapObject>>();

      foreach ( AdvMapObject mapObject in map.objects )
      {
        if ( !advMapObjects.ContainsKey( mapObject.gameObject.DBId ) )
        {
          advMapObjects[mapObject.gameObject.DBId] = new List<AdvMapObject>();
        }
        advMapObjects[mapObject.gameObject.DBId].Add( mapObject );
      }

      context.Progress( "Remove objects...", 40 );
      // убивание половины карты
      for( int i = 0; i < map.objects.Count; i++ )
      {
        bool needProcessObject = true;
        foreach ( ObjectLayersPreset preset in presets )
        {
          if( preset.IsObjectInPreset( advMapObjects, map.objects[i].gameObject, map.objects[i].scriptGroupName ) )
          {
            if( objects.Contains( preset.Name ) )
            {
              needProcessObject = true;
            }
            else
            {
              needProcessObject = false;
            }
          }
        }
        if ( needProcessObject )
        {
          if ( ( !right_to_left && map.objects[i].offset.translateX > sizeX / 2 ) || ( right_to_left && map.objects[i].offset.translateX < sizeX / 2 ) )
          {
            map.objects.RemoveAt( i );
            i--;
          }
        }
      }

      context.Progress( "Adding objects...", 45 );
      // поворот оставшейся половины карты
      List<AdvMapObject> newObjs = new List<AdvMapObject>( map.objects.Count );
      for ( int i = 0; i < map.objects.Count; i++ )
      {
        bool needProcessObject = false;
        foreach ( ObjectLayersPreset preset in presets )
        {
          if ( preset.IsObjectInPreset( advMapObjects, map.objects[i].gameObject, map.objects[i].scriptGroupName ) )
          {
            if ( objects.Contains( preset.Name ) )
            {
              needProcessObject = true;
            }
            else
            {
              needProcessObject = false;
            }
          }
        }
        if ( needProcessObject )
        {
          if ( ( !right_to_left && map.objects[i].offset.translateX > sizeX / 2 ) || ( right_to_left && map.objects[i].offset.translateX < sizeX / 2 ) )
          {
            continue;
          }

          AdvMapObject obj = new AdvMapObject( map.objects[i].GetOwner(), map.objects[i] );
          if ( obj.gameObject.DBId.IsInlined || obj.gameObject.Get() is Road || obj.gameObject.Get() is AdvMapCreepSpawner
            || obj.gameObject.Get() is AdvMapWaterZone || obj.gameObject.Get() is AdvMapCameraSpline )
          {
            DBID newDbid = new DBID( obj.gameObject.DBId.FileName, Guid.NewGuid() );
            DataBase.Copy( newDbid, obj.gameObject.DBId );
            DBPtr<GameObject> newObj = DataBase.Get<GameObject>( newDbid );
            obj.gameObject = newObj;
          }

          obj.offset.translateX = sizeX - obj.offset.translateX;
          obj.offset.translateY = sizeY - obj.offset.translateY;
          obj.offset.rotationZ = obj.offset.rotationZ > 180.0f
                                   ? obj.offset.rotationZ - 180.0f
                                   : obj.offset.rotationZ + 180.0f;
          if ( obj.gameObject.Get() is Road )
          {
            Road r = obj.gameObject.Get() as Road;
            for ( int k = 0; k < r.points.Count; k++ )
            {
              r.points[k].location.x = sizeX - r.points[k].location.x;
              r.points[k].location.y = sizeY - r.points[k].location.y;
            }
          }
          else if ( obj.gameObject.Get() is AdvMapCreepSpawner )
          {
            AdvMapCreepSpawner r = obj.gameObject.Get() as AdvMapCreepSpawner;
            for ( int k = 0; k < r.path.Count; k++ )
            {
              r.path[k].x = sizeX - r.path[k].x;
              r.path[k].y = sizeY - r.path[k].y;
            }
          }
          else if ( obj.gameObject.Get() is AdvMapWaterZone )
          {
            AdvMapWaterZone r = obj.gameObject.Get() as AdvMapWaterZone;
            for ( int k = 0; k < r.area.points.Count; k++ )
            {
              if ( r.area.AbsolutePosition )
              {
                r.area.points[k].location.x = sizeX - r.area.points[k].location.x;
                r.area.points[k].location.y = sizeY - r.area.points[k].location.y;

              }
              else
              {
                r.area.points[k].location.x = -r.area.points[k].location.x;
                r.area.points[k].location.y = -r.area.points[k].location.y;
              }
            }
          }
          else if ( obj.gameObject.Get() is AdvMapCameraSpline )
          {
            AdvMapCameraSpline r = obj.gameObject.Get() as AdvMapCameraSpline;
            for ( int k = 0; k < r.points.Count; k++ )
            {
              r.points[k].position.x = -r.points[k].position.x;
              r.points[k].position.y = -r.points[k].position.y;
              r.points[k].rotation.z = r.points[k].rotation.z > 180.0f
                     ? r.points[k].rotation.z - 180.0f
                     : r.points[k].rotation.z + 180.0f;

            }
          }

          newObjs.Add( obj );
        }
      }
      for ( int i = 0; i < newObjs.Count; i++ )
      {
        map.objects.Add( newObjs[i] );
      }

      context.Progress( "Save...", 49 );
      DataBase.UndoRedoManager.Commit();
      DataBase.Store();
    }

    public override string Name
    {
      get { return "Symmetrical script..."; }
    }
  }
}

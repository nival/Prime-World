using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Minimap;
using EditorLib.ObjectsBrowser;
using EditorLib.PropertiesEditor;
using EditorLib.ToolBox;
using EditorNative;
using EditorNative.SceneElements;
using EditorNative.Terrain;
using EditorPlugins.Scene.Editors;
using EditorPlugins.Utils;
using libdb.DB;
using libdb.Diagnostics;
using libdb.UndoRedo;
using PF_Editor.Map.AdvMapObjects;

namespace PF_Editor.Map
{
  [EditorAttribute( "Map Editor" )]
  public sealed class AdvMapEditor : Editor<AdvMap>, IEditorControlExtension
	{
		#region Private members.

		private PFEditorControl editorControl;
		private AdvMapController advMapController;
    
		private IEditorWinApplication application;
		private readonly List<ToolBoxItem> toolBoxItems = new List<ToolBoxItem>();

    public class MapObjectsList
    {
      public List<AdvMapObject> selectedObjects = new List<AdvMapObject>();
      public List<PointLightInfo> selectedPointLights = new List<PointLightInfo>();
      public List<ScriptArea> selectedScriptAreas = new List<ScriptArea>();

      public bool Equals(MapObjectsList other)
      {
        if (ReferenceEquals(null, other)) return false;
        if (ReferenceEquals(this, other)) return true;
        //return Equals(other.selectedObjects, selectedObjects) && Equals(other.selectedPointLights, selectedPointLights);
        return IsListsEquals(other.selectedObjects, selectedObjects)
            && IsListsEquals(other.selectedPointLights, selectedPointLights)
            && IsListsEquals(other.selectedScriptAreas, selectedScriptAreas);
      }

      public override bool Equals(object obj)
      {
        if (ReferenceEquals(null, obj)) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != typeof (MapObjectsList)) return false;
        return Equals((MapObjectsList) obj);
      }

      public override int GetHashCode()
      {
        unchecked
        {
          //return ((selectedObjects != null ? selectedObjects.GetHashCode() : 0)*397) ^ (selectedPointLights != null ? selectedPointLights.GetHashCode() : 0);
          int result = ( GetListHash( selectedObjects ) * 397 ) ^ GetListHash( selectedPointLights );
          result = ( result * 397 ) ^ GetListHash( selectedScriptAreas );
          return result;
        }
      }

      private int GetListHash<T>(List<T> _list)
      {
        int hash = 0;
        if (_list != null)
        {
          hash = _list.Count;
          foreach (var t in _list)
          {
            //hash *= 17;
            //if (!t.Equals(null)) hash = hash + t.GetHashCode();
            if (!t.Equals(null)) hash ^= t.GetHashCode();
          }
        }
        return hash;
      }

      private bool IsListsEquals<T>(List<T> _list1, List<T> _list2)
      {
        if (ReferenceEquals(_list1, _list2)) return true;
        if(_list1.Count != _list2.Count) return false;
        if(_list1.GetType() != _list2.GetType()) return false;

        Function<bool, object, object> comparer = null;

        if (typeof(T) == typeof(AdvMapObject))
          comparer = IsMapObjectsEquals;
        else if (typeof(T) == typeof(PointLightInfo))
          comparer = IsPointLightsEquals;
        else if ( typeof( T ) == typeof( ScriptArea ) )
          comparer = IsScriptAreasEquals;

        //элементы могут идти в любом порядке
        if (!CheckListItems(_list1, _list2, comparer)) return false;
        if (!CheckListItems(_list2, _list1, comparer)) return false;

        return true;
      }

      private bool CheckListItems<T>(List<T> _list1, List<T> _list2, Function<bool, object, object> comparer)
      {
        if(comparer == null) 
          return false;

        foreach (var item1 in _list1)
        {
          bool contains = false;

          foreach (var item2 in _list2)
          {
            contains = comparer(item1, item2);
            if(contains) 
              break;
          }

          if(!contains) return false;
        }
        return true;
      }

      private bool IsMapObjectsEquals(object _obj1, object _obj2)
      {
        AdvMapObject map1 = _obj1 as AdvMapObject;
        AdvMapObject map2 = _obj2 as AdvMapObject;

        return map1.gameObject.DBId.Equals(map2.gameObject.DBId) &&
               map1.offset.rotationX == map2.offset.rotationX &&
               map1.offset.rotationY == map2.offset.rotationY &&
               map1.offset.rotationZ == map2.offset.rotationZ &&
               map1.offset.scaleX == map2.offset.scaleX &&
               map1.offset.scaleY == map2.offset.scaleY &&
               map1.offset.scaleZ == map2.offset.scaleZ &&
               map1.offset.translateX == map2.offset.translateX &&
               map1.offset.translateY == map2.offset.translateY &&
               map1.offset.translateZ == map2.offset.translateZ; 
      }

      private bool IsPointLightsEquals(object _obj1, object _obj2)
      {
        PointLightInfo pi1 = _obj1 as PointLightInfo;
        PointLightInfo pi2 = _obj2 as PointLightInfo;

        return pi1.attenuation == pi2.attenuation &&
               pi1.diffuse.A == pi2.diffuse.A &&
               pi1.diffuse.B == pi2.diffuse.B &&
               pi1.diffuse.G == pi2.diffuse.G &&
               pi1.diffuse.R == pi2.diffuse.R &&
               pi1.diffuseIntensity == pi2.diffuseIntensity &&
               pi1.location.x == pi2.location.x &&
               pi1.location.y == pi2.location.y &&
               pi1.location.z == pi2.location.z &&
               pi1.range == pi2.range;
      }

      private bool IsScriptAreasEquals(object _obj1, object _obj2)
      {
        ScriptArea sa1 = _obj1 as ScriptArea;
        ScriptArea sa2 = _obj2 as ScriptArea;

        return sa1.position.x == sa2.position.y
            && sa1.position.y == sa2.position.y
            && sa1.radius == sa2.radius;
      }

      //public static bool Test()
      //{
      //  var mapObject1 = new AdvMapObject();
      //  var mapObject2 = new AdvMapObject();
      //  var pointLightInfo = new PointLightInfo();

      //  MapObjectsList first = new MapObjectsList();
      //  first.selectedObjects.Add(mapObject1);
      //  first.selectedObjects.Add(mapObject2);
      //  first.selectedPointLights.Add(pointLightInfo);

      //  MapObjectsList second = new MapObjectsList();
      //  second.selectedObjects.Add(mapObject1);
      //  second.selectedObjects.Add(mapObject2);
      //  second.selectedPointLights.Add(pointLightInfo);

      //  if (first.Equals(second) && first.GetHashCode() != second.GetHashCode())
      //  { // proven Equals, but GetHashCode() disagrees
      //    Log.TraceError("We have a problem");
      //    return false;
      //  }

      //  Dictionary<MapObjectsList, int> dict = new Dictionary<MapObjectsList, int>();

      //  dict[first] = 0;
      //  dict[second] = 1;

      //  if(dict.Count != 1)
      //  {
      //    Log.TraceError("Yup, very bad indeed");
      //    return false;
      //  }

      //  return true;
      //}
    }

    private readonly List<AdvMapObject> selectedObjects = new List<AdvMapObject>();
    private readonly List<PointLightInfo> selectedPointLights = new List<PointLightInfo>();
    private readonly List<ScriptArea> selectedScriptAreas = new List<ScriptArea>();

    private DBPtr<AdvMap> resource;

		#endregion

		#region Initialization.

		public AdvMapEditor()
		{
			TabText = "Map Editor";
		}

		protected override bool Initialize( DBPtr<AdvMap> resource, IEditorWinApplication application )
		{
      DateTime startLoading = DateTime.UtcNow;
      DateTime start = DateTime.UtcNow;
      this.resource = resource;
      
			if ( !resource.IsValid )
			{
				Log.TraceError( "Cannot edit map: resource is not valid." );
				return false;
			}

			var map = resource.Get();

			if ( !map.terrain.IsValid )
			{
				Log.TraceError( "Cannot edit map: terrain is not valid." );
				return false;
			}

			this.application = application;

      var terrain = map.terrain.Get();

		  Log.TraceMessage( "Loading map: " + terrain.DBId );
      ShowDeltaTime( "Initial assigns", start );

      // smirnov [2009/4/1]: temporary patch materials that are out of sync
      start = DateTime.UtcNow;
      {
        int warnCounter = 5;
        TerrainGeometry geo = terrain.geometry;
        foreach (TerrainElementInstance instance in geo.terrainElements)
        {
          StaticMesh mesh = instance.terrainObject.Get();
          if (mesh.materialsReferences.Count == 0 || !mesh.materialsReferences[0].IsValid)
          {
            Log.TraceError("Cannot edit map: found terrain element with no material.");
            return false;
          }
          DBPtr<Material> mat = mesh.materialsReferences[0];
          if (!instance.material.IsValid || !instance.material.Get().DBId.Equals(mat.DBId))
          {
            if (warnCounter-- > 0)
              Log.TraceWarning("Updated material reference for terrain element (was out of sync).");
            if (warnCounter == 0)
              Log.TraceWarning("Further warnings suppressed.");
            instance.material = mat;
          }
        }
      }

      ShowDeltaTime( "Strange loop", start );
      
      start = DateTime.UtcNow;
			editorControl = new PFEditorControl( application, this, terrain ) { Dock = DockStyle.Fill };
      ShowDeltaTime( "Terrain load time", start );

      start = DateTime.UtcNow;
      advMapController = new AdvMapController( map, editorControl );
      ShowDeltaTime( "Objects load time", start );

      start = DateTime.UtcNow;
      editorControl.Scene.InitBakedLighting( bakedLighting );
      ShowDeltaTime( "InitBakedLighting time", start );
      
      start = DateTime.UtcNow;
      editorControl.Scene.SetDayLightEnvironment(DayLighting == null ? DBID.Empty : DayLighting.DBId);
      editorControl.Scene.SetNightLightEnvironment(NightLighting == null ? DBID.Empty : NightLighting.DBId);
      editorControl.Scene.CalculateLightingObjects();
      ShowDeltaTime( "CalculateLighting time", start );

      // не убирайте эту строчку пожалуйста! Карта высот формируется неправильно без неё (баг NUM_TASK)
      // здесь апдейтятся SceneObjectы, которые апдейтят позиции коллизий, из которых апдейтится карта высот.
      editorControl.Scene.Draw(editorControl.SceneControl.Handle, 0.0f, 0.0f);
      
      start = DateTime.UtcNow;
      editorControl.Scene.CalcObjectHeightMap();
		  ShowDeltaTime("CalcObjectHeightMap", start);
      
      start = DateTime.UtcNow;
      editorControl.Scene.ReplaceAllObjectsOnTerrain();
      ShowDeltaTime( "ReplaceAllObjectsOnTerrain time", start );
      
      //Apply configs
      start = DateTime.UtcNow;
      AdvMapEditorConfig config = application.Application.Settings.Get<AdvMapEditorConfig>();
      ShowDeltaTime( "Config Load time", start );
      
      start = DateTime.UtcNow;
      editorControl.LockObjectMode = config.lockObjectsMode;
      ShowDeltaTime( "LockObjectMode time", start );
      
      start = DateTime.UtcNow;
      editorControl.Scene.IsMapLoaded = true;
      ShowDeltaTime( "IsMapLoaded time", start );
      
      start = DateTime.UtcNow;
      InitCamera();
      Controls.Add( editorControl );
      ShowDeltaTime( "InitCamera & Control Add time time", start );
     
		  ShowDeltaTime( "Map load time", startLoading );

      return true;
		}

    private void SubscribeToEvents()
    {
      editorControl.ResetRotation += OnResetRotation;
      editorControl.ResetRotationByTerrain += OnResetRotationByTerrain;
      editorControl.RandomRotation += OnRandomRotation;
      editorControl.RandomScale += OnRandomScale;
      editorControl.TerrainUpdated += OnTerrainUpdated;

      if ( ObjectsBrowser != null )
        ObjectsBrowser.ChangeSelectedItemEvent += OnChangeSelectedItemEvent;

      DataBase.StoreDBResourceEvent += OnStoreDBResource;
      DataBase.ChangeDBResourceEvent += OnDBResourceChanged;
    }

    private void UnsubscribeFromEvents()
    {
      editorControl.ResetRotation -= OnResetRotation;
      editorControl.ResetRotationByTerrain -= OnResetRotationByTerrain;
      editorControl.RandomRotation -= OnRandomRotation;
      editorControl.RandomScale -= OnRandomScale;
      editorControl.TerrainUpdated -= OnTerrainUpdated;

      if ( ObjectsBrowser != null )
        ObjectsBrowser.ChangeSelectedItemEvent -= OnChangeSelectedItemEvent;

      DataBase.StoreDBResourceEvent -= OnStoreDBResource;
      DataBase.ChangeDBResourceEvent -= OnDBResourceChanged;
    }

    private static void ShowDeltaTime( string message, DateTime utcStartTime )
    {
      Log.TraceMessage( "{0}: {1:0.####} s", message, ( DateTime.UtcNow - utcStartTime ).TotalSeconds );      
    }

    private void InitCamera()
		{
      AdvMap map = resource.Get();
      DBTypes.Terrain terrain = map.terrain.Get();

      float x = ( terrain.elemXCount * TerrainUtils.PatchSize ) / 2.0f;
      float y = ( terrain.elemYCount * TerrainUtils.PatchSize ) / 2.0f;
       
      float rod = x > y ? 2*x : 2*y;

      var camera = editorControl.SceneControl.Scene.SceneCamera;
			camera.Anchor = new Vector3( x, y, 0 );
			camera.Yaw = -(float)(Math.PI / 4);
			camera.Pitch = -(float)(Math.PI / 4);
			camera.Roll = 0;
			camera.Rod = rod;
		}

		#endregion

		#region Overrides.

		protected override void OnActivateEditor()
		{
  		base.OnActivateEditor();

      SubscribeToEvents();

      if ( editorControl != null && editorControl.SceneControl != null )
        editorControl.SceneControl.StartTimer();
          
      if(editorControl != null)
      {
        editorControl.Activate();

        var minimap = application.Panels.GetSingletonPanel<MinimapPanel>();
        minimap.SetCamera( editorControl.Scene.SceneCamera );
        minimap.MapSize = new SizeF
        {
          Width = editorControl.Scene.SceneTerrain.SizeX * TerrainUtils.PatchSize, 
          Height = editorControl.Scene.SceneTerrain.SizeY * TerrainUtils.PatchSize 
        };
        minimap.MapImage = Scene.CreateMinimapTexture();
      }  
 
		}

		protected override void OnDeactivateEditor()
		{
      base.OnDeactivateEditor();

      if(editorControl != null)
      {
        editorControl.Deactivate();

        var minimapPanel = application.Panels.GetSingletonPanel<MinimapPanel>();
        minimapPanel.SetCamera( null );
        minimapPanel.MapImage = null;
      }

      if ( editorControl != null && editorControl.SceneControl != null )
        editorControl.SceneControl.StopTimer();

      UnsubscribeFromEvents();
    }

		private bool TrySelectItem( DBID item )
		{
			if ( item == null || item.IsEmpty || !DataBase.IsExists( item ) )
				return false;

			DBResource resource = DataBase.Get<DBResource>( item ).Get();

			if ( resource is StaticMesh )
			{
				var selectedTerrainElements =
          CollectionUtils.FindAll( Scene.SelectedObjects, element => element is IController<TerrainElementInstance> ).
          ConvertAll( element => (IController<TerrainElementInstance>)element );

				if ( selectedTerrainElements.Count > 0 )
				{
          DBPtr<StaticMesh> mesh = DataBase.Get<StaticMesh>(item);
          DBPtr<Material> mat = mesh.Get().materialsReferences[0];
          selectedTerrainElements.ForEach(terrainElement => { terrainElement.Resource.terrainObject = mesh; terrainElement.Resource.material = mat; });
					
					if ( EditorControl.ImmediateLighting )
						EditorControl.ImmediateLightingUpdate();
				}
				else
				{
					// TODO: сделать добавление террейн элемента на сцену.
				}
			}
      else if (resource is PointLightGameObject)
      {
        advMapController.BeginAdditionToScene(this, resource as PointLightGameObject);
      }
      else if ( resource is ScriptAreaGameObject )
      {
        advMapController.BeginAdditionToScene( this, resource as ScriptAreaGameObject );
      }
      else if (resource is GameObject)
      {
        advMapController.BeginAdditionToScene(this, resource as GameObject);
      }
      else
      {
        return false;
      }

			return true;
		}

		private void OnChangeSelectedItemEvent( ObjectsBrowserPanel panel, DBID item )
		{
			TrySelectItem( item );
		}

		public override void OnSelectToolBoxItem( object tag )
		{
			base.OnSelectToolBoxItem( tag );
      if ( tag is DBID )
      {
        var dbId = tag as DBID;
        TrySelectItem( dbId );
      }
      else if ( tag is MapObjectsList )
      {
        TryPasteFromToolbox( tag as MapObjectsList );
      }
		}

		protected override sealed IEnumerable<ToolBoxItem> ToolBoxItems
		{
			get { return toolBoxItems.ToArray(); }
		}

		#endregion

		#region IEditorControlExtension Members

    public void TryRemove( SceneElement obj )
		{
			if ( obj is ControllableVisualObject )
			{
				advMapController.Remove( ((ControllableVisualObject)obj).Resource );
			}
		}

    public void TryCopy()
    {
      selectedObjects.Clear();
      selectedPointLights.Clear();
      selectedScriptAreas.Clear();
      Vector3 selectionCenter = editorControl.SceneControl.Scene.SelectedObjectsGroupCenter;
      foreach ( SceneElement obj in editorControl.SceneControl.Scene.SelectedObjects )
      {
        if ( obj is ControllableVisualObject )
        {
          if ( ( obj as ControllableVisualObject ).Resource is AdvMapObject )
          {
            AdvMapObject advMapObj = new AdvMapObject(null, (obj as ControllableVisualObject).Resource as AdvMapObject);
            advMapObj.gameObject = ((obj as ControllableVisualObject).Resource as AdvMapObject).gameObject;
            advMapObj.offset.translateX = advMapObj.offset.translateX - selectionCenter.X;
            advMapObj.offset.translateY = advMapObj.offset.translateY - selectionCenter.Y;
            selectedObjects.Add(advMapObj);
          }
          else if ( ( obj as ControllableVisualObject ).Resource is PointLightInfo )
          {
            PointLightInfo pointLightObj = new PointLightInfo(null, (obj as ControllableVisualObject).Resource as PointLightInfo);
            pointLightObj.location.x = pointLightObj.location.x - selectionCenter.X;
            pointLightObj.location.y = pointLightObj.location.y - selectionCenter.Y;
            selectedPointLights.Add( pointLightObj );
          }
          else if ( ( obj as ControllableVisualObject ).Resource is ScriptArea )
          {
            ScriptArea scriptAreaObj = new ScriptArea( null, ( obj as ControllableVisualObject ).Resource as ScriptArea );
            scriptAreaObj.position.x = scriptAreaObj.position.x - selectionCenter.X;
            scriptAreaObj.position.y = scriptAreaObj.position.y - selectionCenter.Y;
            selectedScriptAreas.Add( scriptAreaObj );
          }
        }
      }
      
      MapObjectsList objsInfo = new MapObjectsList();
      foreach ( AdvMapObject obj in selectedObjects )
      {
        objsInfo.selectedObjects.Add( obj );
      }
      foreach ( PointLightInfo obj in selectedPointLights )
      {
        objsInfo.selectedPointLights.Add( obj );
      }
      foreach ( ScriptArea obj in selectedScriptAreas )
      {
        objsInfo.selectedScriptAreas.Add( obj );
      }

      H6Clipboard.Copy( objsInfo );
    }

    public override ToolBoxItem GetActiveItem()
    {
      //MapObjectsList.Test();

      MapObjectsList objsInfo = new MapObjectsList();
      String name = String.Empty;
      Vector3 selectionCenter = editorControl.SceneControl.Scene.SelectedObjectsGroupCenter;
      foreach ( SceneElement obj in editorControl.SceneControl.Scene.SelectedObjects )
      {
        if ( obj is ControllableVisualObject )
        {
          if ( ( obj as ControllableVisualObject ).Resource is AdvMapObject )
          {
            AdvMapObject advMapObj = new AdvMapObject( null, ( obj as ControllableVisualObject ).Resource as AdvMapObject );
            advMapObj.gameObject = ( ( obj as ControllableVisualObject ).Resource as AdvMapObject ).gameObject;
            advMapObj.offset.translateX = advMapObj.offset.translateX - selectionCenter.X;
            advMapObj.offset.translateY = advMapObj.offset.translateY - selectionCenter.Y;
            objsInfo.selectedObjects.Add( advMapObj );
          }
          else if ( ( obj as ControllableVisualObject ).Resource is PointLightInfo )
          {
            PointLightInfo pointLightObj = new PointLightInfo( null, ( obj as ControllableVisualObject ).Resource as PointLightInfo );
            pointLightObj.location.x = pointLightObj.location.x - selectionCenter.X;
            pointLightObj.location.y = pointLightObj.location.y - selectionCenter.Y;
            objsInfo.selectedPointLights.Add( pointLightObj );
          }
          else if ( ( obj as ControllableVisualObject ).Resource is ScriptArea )
          {
            ScriptArea scriptAreaObj = new ScriptArea( null, ( obj as ControllableVisualObject ).Resource as ScriptArea );
            scriptAreaObj.position.x = scriptAreaObj.position.x - selectionCenter.X;
            scriptAreaObj.position.y = scriptAreaObj.position.y - selectionCenter.Y;
            objsInfo.selectedScriptAreas.Add( scriptAreaObj );
          }
        }
        name += GetMenuItemNameBy( obj ) + "; ";
      }

      ToolBoxItem item = null;

      if ( ( objsInfo.selectedObjects.Count > 0 ) || ( objsInfo.selectedPointLights.Count > 0 ) || ( objsInfo.selectedScriptAreas.Count > 0 ) )
      {
        item = new ToolBoxItem( "Map Objects", name, objsInfo );  
      }
      
      return item;
    }

    public void TryPasteFromToolbox( MapObjectsList obj )
    {
      Scene.DeselectAll();
      selectedObjects.Clear();
      selectedPointLights.Clear();
      selectedScriptAreas.Clear();
      selectedObjects.AddRange( obj.selectedObjects );
      selectedPointLights.AddRange( obj.selectedPointLights );
      selectedScriptAreas.AddRange( obj.selectedScriptAreas );
      if ( selectedObjects.Count != 0 || selectedPointLights.Count != 0 || selectedScriptAreas.Count != 0 )
        advMapController.BeginAdditionToScene( this, selectedObjects, selectedPointLights, selectedScriptAreas, true );
    }

    public void TryPaste()
    {
      Scene.DeselectAll();
      selectedObjects.Clear();
      selectedPointLights.Clear();
      selectedScriptAreas.Clear();
      for ( int i = 0; i < H6Clipboard.CopiedObjects.Length; i++ )
      {
        selectedObjects.AddRange( ( (MapObjectsList)H6Clipboard.CopiedObjects[i] ).selectedObjects );
        selectedPointLights.AddRange( ( (MapObjectsList)H6Clipboard.CopiedObjects[i] ).selectedPointLights );
        selectedScriptAreas.AddRange( ( (MapObjectsList)H6Clipboard.CopiedObjects[i] ).selectedScriptAreas );
      }
      if ( selectedObjects.Count != 0 || selectedPointLights.Count != 0 || selectedScriptAreas.Count != 0 )
      {
        advMapController.BeginAdditionToScene( this, selectedObjects, selectedPointLights, selectedScriptAreas, true );
      }
    }

    public void OnObjectSelected( SceneElement obj )
		{
			var entityController = obj as ControllableVisualObject;
      PropertiesEditorPanel propertiesEditor = application.Panels.GetSingletonPanel<PropertiesEditorPanel>();

			if ( !ReferenceEquals( entityController, null ) )
			{
				var advMapObject = entityController.Resource;

        if( advMapObject is AdvMapObject)
        {
          GameObject selectedGameObject = ( advMapObject as AdvMapObject ).gameObject.Get();
          
          if(ControllableVisualObject.IsSingleStateSoundObject(selectedGameObject as SingleStateObject))
          {
            //нет никаких проверок, т.к. все проверки были сделаны в ControllableVisualObject.IsSingleStateSoundObject
            propertiesEditor.SelectedObject = (((SingleStateObject)selectedGameObject).sceneObject.Get().attached[0].component.Get() as DBSoundSceneComponent).desc;
            return;
          }

          if(ControllableVisualObject.IsMultiStateSoundObject(selectedGameObject as MultiStateObject))
          {
            //в MultiStateSoundWrapper нет проверок, т.к. все проверки были сделаны в ControllableVisualObject.IsMultiStateSoundObject
            propertiesEditor.SelectedObject = new MultiStateSoundWrapper( selectedGameObject as MultiStateObject );
            return;
          }
        }

        propertiesEditor.SelectedObject = advMapObject;
			}
      else if ( obj != null && TypeUtils.IsSubclassOf( obj.GetType(), typeof( IController<> ) ) )
      {
        IController<TerrainElementInstance> patchInfo = obj as IController<TerrainElementInstance>;
        if ( patchInfo != null )
          propertiesEditor.SelectedObject = patchInfo.Resource;
      }
      else
      {
        propertiesEditor.SelectedObject = advMapController.Map;
      }
		}

    public string ConfigSection
		{
			get { return "MapEditor"; }
		}

    public bool ObjectsSelectable
		{
			set
			{
				if ( !ReferenceEquals( advMapController, null ) )
				{
					advMapController.ObjectsSelectable = value;
				}
			}
		}

		public string GetMenuItemNameBy( SceneElement element )
		{
			if ( element is ControllableVisualObject )
			{
				var obj = (ControllableVisualObject)element;
        if (obj.Resource is AdvMapObject)
        {
          var gameObject = (obj.Resource as AdvMapObject).gameObject;
          return gameObject.Get().GetType().Name + ": " + gameObject.DBId.Name;
        }
        else if (obj.Resource is PointLightInfo)
        {
          //TODO
          var gameObject = (obj.Resource as PointLightInfo);
          return gameObject.GetType().Name;
        }
        else if ( obj.Resource is ScriptArea )
        {
          var gameObject = ( obj.Resource as ScriptArea );
          return gameObject.GetType().Name + ": " + gameObject.name;
        }

        return null;
			}
			else
			{
				return null;
			}
		}

    public DBPtr<LightEnvironment> DayLighting { get { return advMapController.Map.lightEnvironment; } }
    public DBPtr<LightEnvironment> NightLighting { get { return advMapController.Map.nightLightEnvironment; } }
		public IEnumerable<PointLightInfo> PointLights { get { return advMapController.Map.pointLights; } }
    public BakedLighting bakedLighting { get { return advMapController.Map.bakedLighting; } }
    public DBPtr<AdvMap> Resource { get { return resource; } }

		#endregion

		#region Properties

    private EditorScene Scene
		{
			get { return editorControl.Scene; }
		}

    private ObjectsBrowserPanel ObjectsBrowser
    {
      get { return application.Panels.GetSingletonPanel<ObjectsBrowserPanel>(); }
    }

    #endregion

    private void RebuildRoads()
    {
      DateTime start = DateTime.UtcNow;

      var roads = EditorControl.Scene.GetSceneElementsByType( typeof( RoadVisualObject ) );

      foreach ( RoadVisualObject road in roads )
      {
        road.Rebuild();
      }

      ShowDeltaTime( "RebuildRoads time", start );
    }

    private void StoreRoads()
    {
      foreach ( RoadVisualObject road in Scene.GetSceneElementsByType<RoadVisualObject>() )
      {
        road.Store();
      }
    }

    public override void StoreMap()
    {
      editorControl.Relight();
      RebuildRoads();
      OnStoreDBResource(advMapController.Map.DBId);

      if( editorControl != null )
        editorControl.StoreMap();
    }

    public void Add( IEnumerable<AdvMapObject> objects )
    {
      Random rand = new Random() ;
      float rotation = (float)rand.NextDouble()*360;
      
      AdvMap map = advMapController.Map;

      advMapController.SelectAfterAdd = true;

			foreach ( AdvMapObject obj in objects )
			{
        if (editorControl.RandomZRotationEnabled)
          obj.offset.rotationZ += rotation;

        GameObject gameObj = null;

        if( obj.gameObject != null )
			    gameObj = obj.gameObject.Get();

        AdvMapObject objToAdd = GetObjectToAdd( obj, gameObj, map.DBId );
				OnRandomScaleObject(objToAdd, false);

			  map.objects.Add( objToAdd );
			}

      advMapController.SelectAfterAdd = false;

      ToolBoxPanel toolBoxPanel = application.Panels.GetSingletonPanel<ToolBoxPanel>();
      toolBoxPanel.UpdateRecentlyUsed();
    }

    private AdvMapObject GetObjectToAdd( AdvMapObject obj, GameObject gameObj, DBID mapDbId )
    {
      if ( gameObj is AdvMapWaterZone )
      {
        return CopyAdvMapObject( obj, gameObj as AdvMapWaterZone, mapDbId );
      }
      if ( gameObj is ScriptPath )
      {
        return CopyAdvMapObject( obj, gameObj as ScriptPath, mapDbId );
      }
      if ( gameObj is ScriptPolygonArea )
      {
        return CopyAdvMapObject( obj, gameObj as ScriptPolygonArea, mapDbId );
      }
      
      if (gameObj is Road)
      {
        AdvMapObject mapObjectCopy = CopyAdvMapObject( obj, gameObj as Road, mapDbId );
				Road roadCopy = (Road)mapObjectCopy.gameObject.Get();

        using( UndoRedoTransaction trans = new UndoRedoTransaction( "Correct road points" ) )
        {
          int centralPointIndex = roadCopy.points.Count/2;

          if(centralPointIndex < roadCopy.points.Count)
          {
            Vector2 pointLocation = new Vector2(
              obj.offset.translateX - roadCopy.points[centralPointIndex].location.x,
              obj.offset.translateY - roadCopy.points[centralPointIndex].location.y );
              
            foreach( RoadControlPoint point in roadCopy.points )
            {
              point.location.x += pointLocation.X;
              point.location.y += pointLocation.Y;
            }

            trans.Commit(); 
          }
        }

        return mapObjectCopy;
      }
      
      if (ControllableVisualObject.IsSingleStateSoundObject(gameObj as SingleStateObject ))
      {
        return CopyAdvMapObject( obj, gameObj as SingleStateObject, mapDbId );
      }

      if( ControllableVisualObject.IsMultiStateSoundObject( gameObj as MultiStateObject ) )
      {
        return CopyAdvMapObject( obj, gameObj as MultiStateObject, mapDbId );
      }

      if(EditorControl.InlineSpawners)
      {
        if( gameObj is AdvMapCreepSpawner )
        {
          AdvMapObject result = CopyAdvMapObject( obj, gameObj as AdvMapCreepSpawner, mapDbId );
          result.SetParent( gameObj );
          return result;
        }

        if( gameObj is AdvMapNeutralCreepSpawner )
        {
          AdvMapObject result = CopyAdvMapObject( obj, gameObj as AdvMapNeutralCreepSpawner, mapDbId );
          result.SetParent( gameObj );
          return result;
        } 
      }

      return obj;
    }

    //создает копию объекта
    private AdvMapObject CopyAdvMapObject<T>( AdvMapObject _advMapObj, T _gameObject, DBID _mapDbId )
      where T : GameObject, new()
    {
      DBPtr<T> newDbPtr = DataBase.Create( DBID.FromDBID( _mapDbId, true ), new T() );
      DBCopy.Copy( newDbPtr.Get(), _gameObject );
      
      var result = new AdvMapObject();
      result.Assign( _advMapObj );
      result.gameObject = newDbPtr.GetPtr<GameObject>();
      
      return result;
    }

    public void Add(IEnumerable<PointLightInfo> objects)
    {
      var map = advMapController.Map;
      foreach (PointLightInfo obj in objects)
        map.pointLights.Add(obj);

      ToolBoxPanel toolBoxPanel = application.Panels.GetSingletonPanel<ToolBoxPanel>();
      toolBoxPanel.UpdateRecentlyUsed();
    }

    public void Add( IEnumerable<ScriptArea> objects )
    {
      var map = advMapController.Map;
      foreach ( ScriptArea obj in objects )
        map.scriptAreas.Add( obj );

      ToolBoxPanel toolBoxPanel = application.Panels.GetSingletonPanel<ToolBoxPanel>();
      toolBoxPanel.UpdateRecentlyUsed();
    }

    public PFEditorControl EditorControl
    {
      get { return editorControl; }
    }

    private void OnStoreDBResource(DBID dbId)
    {
      if (advMapController.Map.DBId == dbId || editorControl.TerrainController.Resource.DBId == dbId)
      {
        DateTime start = DateTime.UtcNow;

        // gather vertex colors and store them into separate file
        IList<SceneElement> sceneElements = Scene.GetSceneElements();
        List<GameSceneObject> gameObjects = new List<GameSceneObject>(sceneElements.Count);

        foreach (var element in sceneElements)
        {
          if( element is GameSceneObject )
            gameObjects.Add( (GameSceneObject)element );
        }

        EditorScene.BuildVertexColorDB( gameObjects, advMapController.Map.bakedLighting.vertexColorsFileName );

        // gather water splines and build water map
        //PF_EditorNative.WaterMap.BuildAndSave(Scene, advMapController.VisualObjects, advMapController.Map.waterMapFileName);
				StuffUtils.StoreAdvMapWaterZone( resource.Get(), 1024 );
        StoreRoads();

        ShowDeltaTime("Store AdvMap time", start);
      }
    }

    private void OnDBResourceChanged( DBID dbid )
    {
      var roads = EditorControl.Scene.GetSceneElementsByType( typeof( RoadVisualObject ) );

      foreach ( RoadVisualObject road in roads )
      {
        GameObject go = road.GetGameObject();

        //NOTE don't use road.DbId it's anoter value
        if ( go != null && dbid == go.DBId )
        {
          road.Rebuild();
          break;
        }
      }
    }

    protected override void OnClosed( EventArgs e )
    {
      base.OnClosed( e );

      if ( null != advMapController )
      {
        advMapController.Release();
        advMapController = null;
      }
        
      editorControl.Dispose();
      editorControl = null;
    }

    private void OnTerrainUpdated( object sender, EventArgs e )
    {
      RebuildRoads();
    }

		private void OnResetRotation(object sender,EventArgs e)
		{
			if ( !Scene.HasSelectedObject )
				return;

			foreach ( SceneElement obj in editorControl.SceneControl.Scene.SelectedObjects )
			{
				ControllableVisualObject advMapObj = obj as ControllableVisualObject;

				if(advMapObj == null)
        {
          TcvMarker tcvObj = obj as TcvMarker;
          if (tcvObj != null)
            obj.Rotation = Quaternion.Identity;

          continue;
        }
				
				AdvMapObject aObj = advMapObj.Resource as AdvMapObject;

				if(aObj != null)
					aObj.offset.rotationX = aObj.offset.rotationY = aObj.offset.rotationZ = 0;
			}
		}

		private void OnResetRotationByTerrain(object sender,EventArgs e)
		{
			if ( !Scene.HasSelectedObject && !Scene.HasTerrain )
				return;

			foreach ( SceneElement obj in editorControl.SceneControl.Scene.SelectedObjects )
			{
				ControllableVisualObject advMapObj = obj as ControllableVisualObject;

				if(advMapObj == null)
					continue;

				AdvMapObject aObj = advMapObj.Resource as AdvMapObject;
				if ( aObj != null )
				{
					Vector3 normal = Vector3.Zero;
					bool intersection = editorControl.SceneControl.Scene.SceneTerrain.
						TryGetNormal( aObj.offset.translateX, aObj.offset.translateY, ref normal );

					if(intersection)
					{
						Vector3 worldUp = obj.Rotation.GetZAxis();
						Quaternion rotation = Quaternion.FromToRotation( worldUp, normal );
						rotation = obj.Rotation * rotation;
						obj.Rotation = Quaternion.Identity;

						aObj.offset.rotationX = rotation.EulerAngles.X;
						aObj.offset.rotationY = rotation.EulerAngles.Y;
						aObj.offset.rotationZ = rotation.EulerAngles.Z;
					}

				}
			}
		}

		private void OnRandomRotation(object sender,EventArgs e)
		{
			foreach ( SceneElement obj in editorControl.SceneControl.Scene.SelectedObjects )
			{
				ControllableVisualObject advMapObj = obj as ControllableVisualObject;

				if ( advMapObj == null )
					continue;

				AdvMapObject aObj = advMapObj.Resource as AdvMapObject;
				if ( aObj != null )
				{
					Random rand = new Random();
					float rotation = (float)rand.NextDouble()*295;

					aObj.offset.rotationZ = rotation;
				}
			}
		}

		private void OnRandomScale(object sender,EventArgs e)
		{
			foreach ( SceneElement obj in editorControl.SceneControl.Scene.SelectedObjects )
			{
				ControllableVisualObject advMapObj = obj as ControllableVisualObject;

				if ( advMapObj == null )
					continue;

				AdvMapObject aObj = advMapObj.Resource as AdvMapObject;
				if ( aObj != null )
				{
					OnRandomScaleObject(aObj, true);
				}
			}
		}

		private void OnRandomScaleObject(AdvMapObject aObj, bool activeOverride)
		{
			if ( !activeOverride )
			{
				if (!editorControl.IsRandomScaleActive)
					return;
			}

			Random rand = new Random();
			float scale = (float)rand.NextDouble();

			float size = Math.Abs(editorControl.MaxRandomScale - editorControl.MinRandomScale);
			size *= scale;
			scale = editorControl.MinRandomScale + size;

			aObj.offset.scaleX = scale;
			aObj.offset.scaleY = scale;
			aObj.offset.scaleZ = scale;
		}
	}
}

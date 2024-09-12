using System;
using System.Collections.Generic;
using DBTypes;
using EditorPlugins.Scene;
using EditorNative;
using EditorNative.Manipulators;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Editors;
using libdb.DB;
using libdb.Diagnostics;

namespace PF_Editor.Map.AdvMapObjects
{
	public class ControllableVisualObject
		: GameSceneObject,
			IMovingController,
			IObjectTransformController
	{
		#region Private members.

		private readonly EditorControl editor;
		private readonly ControllableItem item;

		#endregion

		#region Static Initializers (Factory Methods)

    public static double totalNew = 0.0;
    public static double totalOnChange = 0.0;
    public static double totalGetSceneObjects = 0.0;

    internal static ControllableVisualObject CreateVisualObject(EditorControl editor, AdvMapObject advMapObject, bool placeToMap)
    {
      var gameObject = advMapObject.gameObject.Get();

      if(gameObject is Road)
      {
        return RoadVisualObject.CreateRoadVisualObject( editor, advMapObject, placeToMap );
      }
      
      return new ControllableVisualObject( editor, advMapObject, placeToMap );
    }

    internal static ControllableVisualObject CreateVisualObject(EditorControl editor, PointLightInfo pointLight, bool isCreateLight)
    {
      return new ControllableVisualObject(editor, pointLight, isCreateLight);
    }

    internal static ControllableVisualObject CreateVisualObject( EditorControl editor, ScriptArea scriptArea, bool placeToMap )
    {
      return new ControllableVisualObject( editor, scriptArea, placeToMap );
    }

    #endregion

    #region Protected Constructors

    protected ControllableVisualObject( EditorControl editor, AdvMapObject advMapObject, bool placeToMap )
			: base( advMapObject.gameObject, 0, placeToMap, advMapObject.scriptGroupName )
		{
			this.item = new ControllableItem( advMapObject );
			this.editor = editor;
			OnResourceChanged();
			item.Changed += OnChanged;
		}

		protected ControllableVisualObject( EditorControl editor, PointLightInfo pointLight, bool isCreateLight )
			: base( DataBase.Get<GameObject>( DBID.FromString( "Tech/Default/Bulb.SMPL" ) ), 0, "" )
		{
			if ( isCreateLight )
			{
				this.CreateLight();
        this.UpdateLightInfo( pointLight );
			}
      this.isPlaceOnTerrain = false;
      this.item = new ControllableItem( pointLight );
			this.editor = editor;

			OnResourceChanged();

			item.Changed += OnChanged;
		}

    protected ControllableVisualObject( EditorControl editor, ScriptArea scriptArea, bool placeToMap )
      : base( DataBase.Get<GameObject>( DBID.FromString( "Tech/Default/ScriptArea.SCAR" ) ), 0, "" )
    {
      this.item = new ControllableItem( scriptArea );
      this.editor = editor;

      OnResourceChanged();

      item.Changed += OnChanged;
    }

		#endregion

		public void Unsubscribe()
		{
			item.Changed -= OnChanged;
		  item.Dispose();
		}

    public override void Draw()
    {
      base.Draw();

      if ( !IsSelected )
        return;

      ScriptArea scriptArea = item.GetScriptArea();
      if ( scriptArea != null )
      {
        System.Drawing.Color drawColor = System.Drawing.Color.White;

        Vector3 point1 = new Vector3( item.Location.x, item.Location.y, 0 );

        float z = 0;
        Scene.SceneTerrain.TryGetHeight( point1.X, point1.Y, ref z );
        point1.Z = z;

        EditorRender.DrawCircle3D( point1, scriptArea.radius, 32, drawColor );
      }
      
      AdvMapObject mapObject = item.Resource as AdvMapObject;
      if ( mapObject != null )
      {
        WarFogUnblock obj = mapObject.gameObject.Get() as WarFogUnblock;
        if ( obj != null )
        {
            System.Drawing.Color drawColor = System.Drawing.Color.White;

            Vector3 point1 = new Vector3(item.Location.x, item.Location.y, 0);

            float z = 0;
            Scene.SceneTerrain.TryGetHeight(point1.X, point1.Y, ref z);
            point1.Z = z;

            EditorRender.DrawCircle3D(point1, obj.radius, 32, drawColor);
        }
      }
    }

		#region Event handlers.

		public void OnChanged( object sender, EventArgs e )
		{
			PointLightInfo pointlightinfo = item.GetPointLightInfo();
			if ( pointlightinfo != null )
			{
				UpdateLightInfo( pointlightinfo );
			}
			OnResourceChanged();
		}

		protected virtual void OnResourceChanged()
		{
			Location = CalculateLocation();
			Rotation = CalculateRotation();
      if ( item.GetPointLightInfo() != null )
      {
        Vector3 scale = new Vector3(1.0f,1.0f,1.0f);
        Scale = scale;
      }
      else
      {
        Scale = CalculateScale();
      }
		}

		#endregion

		#region IMovingController Members

		public Vector2 TileCoordinates
		{
			get
			{
				return new Vector2( item.Location.x, item.Location.y );
			}
		}

		public virtual void Move( float offsetX, float offsetY, bool nonTile )
		{
			PickResult pickResult = SceneControl.Pick();
			if ( pickResult.HasTerrainIntersection )
			{
				var terrainIntersection = pickResult.TerrainIntersection;
        Vec3 newpos = new Vec3();
        newpos.z = 0;
        newpos.x = terrainIntersection.X + offsetX;
        newpos.y = terrainIntersection.Y + offsetY;

        if(item.Location.x != newpos.x || 
           item.Location.y != newpos.y || 
           item.Location.z != newpos.z)
        {
          item.Location = newpos;  
        }       
      }
		}

		#endregion

		#region IObjectTransformController Members

		Vector3 IObjectTransformController.Location
		{
			get
			{
				var location = CalculateLocation();

				float height = 0.0f;

        if ( !editor.SnapObjectsToTerrain && item.GetPointLightInfo() == null )
				  TryGetHeight( location.X, location.Y, out height );

				return CalculateLocation() + new Vector3( 0, 0, height );
			}
			set
			{
				var prevLocation = ( (IObjectTransformController)this ).Location;
        Vec3 newpos = new Vec3();
				//var location = item.Location;

        newpos.x = value.X;
        newpos.y = value.Y;

				if ( item.GetPointLightInfo() == null && ( !editor.SnapObjectsToTerrain || ( CanGetHeight( value.X, value.Y ) && CanGetHeight( prevLocation.X, prevLocation.Y ) && Math.Abs( prevLocation.Z - value.Z ) > 0.0001 ) ) )
				{
					float height = 0;
					SceneControl.Scene.SceneTerrain.TryGetHeight( value.X, value.Y, ref height );
					//location.z = value.Z - height;
          newpos.z = value.Z - height;
				}
        else
        {
          newpos.z = value.Z;
        }
        item.Location = newpos;
			}
		}

		Quaternion IObjectTransformController.Rotation
		{
			get { return new Quaternion( item.Rotation.x, item.Rotation.y, item.Rotation.z, item.Rotation.w ); }
			set
			{
        Quat newrot = new Quat();
        newrot.x = value.X;
        newrot.y = value.Y;
        newrot.z = value.Z;
        newrot.w = value.W;
        item.Rotation = newrot;
			}
		}

		Vector3 IObjectTransformController.Scale
		{
			get { return CalculateScale(); }
			set
			{
        Scale newscale = new Scale();
        newscale.x = value.X;
        newscale.y = value.Y;
        newscale.z = value.Z;
        item.Scale = newscale;
			}
		}

		TransformParameters IObjectTransformController.MovingX
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.MovingY
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.MovingZ
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.RotationPitch
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.RotationRoll
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.RotationYaw
		{
			get { return TransformParameters.FullEnabled; }
		}

		TransformParameters IObjectTransformController.ScalingX
		{
			get { return ScalingHorizontal; }
		}

		TransformParameters IObjectTransformController.ScalingY
		{
			get { return ScalingHorizontal; }
		}

		TransformParameters IObjectTransformController.ScalingZ
		{
			get { return TransformParameters.FullEnabled; }
		}

    bool IObjectTransformController.IsCommonCenter { get; set; }

		#endregion

		#region Public properties.

		public object Resource
		{
			get { return item.Resource; }
		}

		#endregion

		#region Private properties.

		private SceneControl SceneControl
		{
			get { return editor.SceneControl; }
		}

		private TransformParameters ScalingHorizontal
		{
			get
			{
				//         if (advMapObject.gameObject.IsValid)
				//         {
				return TransformParameters.FullEnabled;
				//         }
				//         else
				//         {
				//           return TransformParameters.Disabled;
				//         }
			}
		}

		private bool CanGetHeight( float x, float y )
		{
			float height;
			return TryGetHeight( x, y, out height );
		}

		private bool TryGetHeight( float x, float y, out float height )
		{
			height = 0;
			return SceneControl.Scene.SceneTerrain.TryGetHeight( x, y, ref height );
		}

		#endregion

		#region Private helper methods.

		private Vector3 CalculateLocation()
		{
			var location = item.Location;
			return new Vector3( location.x, location.y, location.z );
		}

		private Quaternion CalculateRotation()
		{
			var rotation = item.Rotation;
			return new Quaternion( rotation.x, rotation.y, rotation.z, rotation.w );
		}

		private Vector3 CalculateScale()
		{
			var scale = item.Scale;
			return new Vector3( scale.x, scale.y, scale.z );
		}

		#endregion

		protected override List<DBID> InitSceneObjects( GameObject gameObj )
		{
			List<DBID> sceneObjects = new List<DBID>();
			if ( gameObj is SingleStateObject )
			{
				SingleStateObject sso = gameObj as SingleStateObject;

        if(IsSingleStateSoundObject( sso ))
        {
          sceneObjects.Add( DBID.FromString( "Tech/Default/Flag.SOBJ" ) );
          SetSound( true );
        }
        if( sso.sceneObject.IsValid )
          sceneObjects.Add( sso.sceneObject.DBId );

        if( gameObj is Building )
        {
          Building building = gameObj as Building;
          if( building.ruinSceneObject.IsValid )
            sceneObjects.Add( building.ruinSceneObject.DBId );
        } 
			}
			else if ( gameObj is MultiStateObject )
			{
        SetFreezed( true );
        SetMSO( true );
				MultiStateObject mso = gameObj as MultiStateObject;

        if(IsMultiStateSoundObject( mso ))
        {
          sceneObjects.Add( DBID.FromString( "Tech/Default/Flag.SOBJ" ) );
          SetSound( true );
        }

        foreach( DBPtr<DBSceneObject> so in mso.sceneObjects )
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

        if( gameObj is TreeObject )
        {
          TreeObject tree = gameObj as TreeObject;

          foreach( DBPtr<DBSceneObject> so in tree.stubsSceneObjects )
          {
            if( so.IsValid )
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
          sceneObjects.Add(DBID.FromString("Tech/Default/Camera.SOBJ"));
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

    internal static bool IsMultiStateSoundObject(MultiStateObject _mso)
    {
      if(_mso == null) return false;

      foreach( DBPtr<DBSceneObject> so in _mso.sceneObjects )
      {
        if(so != null && so.IsValid && so.DBId.IsInlined && IsSoundObject( so.Get() ))
          continue;

        return false;  
      }
      return true;
    }

    internal static bool IsSingleStateSoundObject(SingleStateObject _sso)
    {
      if((_sso != null) && (_sso.sceneObject != null) && _sso.sceneObject.IsValid)
      {
        return IsSoundObject( _sso.sceneObject.Get() );  
      }
   
      return false;     
    }

	  private static bool IsSoundObject( DBSceneObject _sceneObj )
	  {
      if( _sceneObj != null && (!_sceneObj.DBId.IsEmpty) && _sceneObj.DBId.IsInlined )
      {
        if( _sceneObj.attached.Count == 1 )
        {
          var component = _sceneObj.attached[0].component;

          return component.DBId.IsInlined && (component.Get() is DBSoundSceneComponent);
        }
      }
	    
	    return false;
	  }
	}
}

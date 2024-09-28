using System;
using System.Collections.Generic;
using DBTypes;
using EditorLib.Settings;
using EditorNative;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Extensions;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Scene.Presets
{
	[ConfigObject( false, "ScenePreset" )]
	public class DefaultScenePreset : ScenePreset
	{
		public class LocatorInfo : IPresetItem
		{
			public LocatorInfo()
			{
				placement.Changed += OnPlacementChanged;
			}

			private ScenePreset owner = null;

			private bool isTerrainLike = false;
			public bool IsTerrainLike
			{
				get
				{
					return isTerrainLike;
				}
				set
				{
					isTerrainLike = value;
					if ( owner != null )
						owner.Updated();  
				}
			}

			public void SetOwner(ScenePreset preset)
			{
				owner = preset;
			}

			public List<string> GetLocators()
			{
				return owner.GetLocators();
			}

			private DBPtr<DBSceneResource> componentResource = new DBPtr<DBSceneResource>(null);
			public DBPtr<DBSceneResource> ComponentResource
			{
				get
				{
					return componentResource;
				}
				set
				{
					componentResource.Set(value);
					if ( owner != null )
						owner.Updated();  
				}
			}

			private Placement2 placement = new Placement2();
			public Placement2 Placement
			{
				get
				{
					return placement;
				}
				set
				{
					placement.Changed -= OnPlacementChanged;
					placement = value;
					placement.Changed += OnPlacementChanged;

					if (owner != null)
						owner.Updated();
				}
			}

			private void OnPlacementChanged( object sender, EventArgs e )
			{
				if( owner != null )
					owner.Updated();
			}

			private EditorSceneObject componentObject = null;
			public EditorSceneObject GetComponentObject()
			{
				return componentObject;
			}
			public void SetComponentObject(EditorSceneObject obj)
			{
				componentObject = obj;
			}

			private string locator = "None";
			[Locator]
			public string Locator
			{
				get
				{
					return locator;
				}
				set
				{
					locator = value;
					if (owner != null)
						owner.Updated();
				}
			}
		}

		public class EffectInfo : IPresetItem
		{
			private ScenePreset owner = null;

			public void SetOwner( ScenePreset preset )
			{
				owner = preset;
			}

			private DBPtr<BasicEffect> componentResource = new DBPtr<BasicEffect>( null );
			public DBPtr<BasicEffect> ComponentResource
			{
				get
				{
					return componentResource;
				}
				set
				{
					componentResource.Set( value );
					if ( owner != null )
						owner.Updated();
				}
			}

			private EditorSceneObject componentObject = null;
			public EditorSceneObject GetComponentObject()
			{
				return componentObject;
			}
			public void SetComponentObject( EditorSceneObject obj )
			{
				componentObject = obj;
			}
		}

		private DBPtr<LightEnvironment> lightResource = new DBPtr<LightEnvironment>( null );
		public DBPtr<LightEnvironment> LightResource
		{
			get
			{
				return lightResource;
			}
			set
			{
				lightResource.Set( value );
				Rebuild();
			}
		}

		private HDRColor recolor = new HDRColor();
		public HDRColor Recolor
		{
			get
			{
				return recolor;
			}
			set
			{
				recolor = value;
				Rebuild();
			}
		}

		private bool enableCameraEffects = true;
		public bool EnableCameraEffects
		{
			get
			{
				return enableCameraEffects;
			}
			set
			{
				enableCameraEffects = value;
				if ( scene != null )
				{
					scene.EnableCameraEffects( enableCameraEffects );
				}
			}
		}

		private DBID resourceDbid;
    private DBPtr<DBResource> resource;
		private EditorSceneObject sceneObject;
		private SimpleEditorScene scene;
		private AGController agc1 = null;
		private AGController agc2 = null;

		private List<EditorSceneObject> ListOfNoneObjects = new List<EditorSceneObject>();
    private List<EditorSceneObject> ListOfSpawnerObjects = new List<EditorSceneObject>();

		private PresetItemList<LocatorInfo> components;
		public PresetItemList<LocatorInfo> Components
		{
			get
			{
				return components;
			}
			set
			{
				components = new PresetItemList<LocatorInfo>( this );
				foreach (LocatorInfo obj in value)
				{

					LocatorInfo newInfo = TypeUtils.CreateInstance(obj.GetType()) as LocatorInfo;
					TypeUtils.Copy(obj, newInfo);
					components.Add(newInfo);
				}
				Updated();
			}
		}

		private PresetItemList<EffectInfo> effects;
		public PresetItemList<EffectInfo> Effects
		{
			get
			{
				return effects;
			}
			set
			{
				effects = new PresetItemList<EffectInfo>( this );
				foreach ( EffectInfo obj in value )
				{
					EffectInfo newInfo = TypeUtils.CreateInstance( obj.GetType() ) as EffectInfo;
					TypeUtils.Copy( obj, newInfo );
					effects.Add( newInfo );
				}
				Updated();
			}
		}

		private List<string> locators;

		private float oldTime = 0.0f;

		public bool spyCamera = false;

		public float Distance { get; set; }

		public float Speed = 0.0f;
		public float TimeToDeath = 0.0f;

		private float curTime = 0.0f;

		public DefaultScenePreset()
		{
			components = new PresetItemList<LocatorInfo>(this);
			effects = new PresetItemList<EffectInfo>( this );
			ReinitTime();
		}

		public override void SetControllers( AGController _agc1, AGController _agc2 )
		{
			agc1 = _agc1;
			agc2 = _agc2;
		}

		public override void Init(SimpleEditorScene _scene)
		{
			scene = _scene;
			ReinitTime();
		}

		public override void Release()
		{
			foreach ( LocatorInfo info in components )
			{
				if ( info.GetComponentObject() != null )
				{
					scene.Remove( info.GetComponentObject() );
					info.SetComponentObject( null );
				}
			}
			foreach ( EffectInfo info in effects )
			{
				if ( info.GetComponentObject() != null )
				{
					scene.Remove( info.GetComponentObject() );
					info.SetComponentObject( null );
				}
			}
			if ( sceneObject != null )
			{
				scene.Remove( sceneObject );
				sceneObject = null;
			}
		}

    public void RecreateSpawner( DBID dbid, Placement place )
    {
      EditorSceneObject so = new EditorSceneObject( dbid );
      ListOfSpawnerObjects.Add( so );
      scene.Add( so );
      so.SetCurrentPlacement( place );

      EditorSceneComponent sc = so.GetRootEditorSceneComponent();

      if ( sc != null )
      {
        so.ShowSkin( 0, true, sc.GetDBID() );
      }

      if ( so.GetRawEditorSceneObject() != (System.IntPtr)0 )
      {
        if ( Recolor.A > 0.0f )
        {
          PF_EditorNative.Utils.RecolorSceneObject( so.GetRawEditorSceneObject(), recolor.R, recolor.G, recolor.B );
        }
        else
        {
          PF_EditorNative.Utils.ResetSceneObjectRecolor( so.GetRawEditorSceneObject() );
        }
      }
    }

		public override void Rebuild()
		{
			if ( scene == null )
				return;

			PF_EditorNative.Utils.ResetCache();

			if ( scene != null && lightResource.DBId != DBID.Empty )
			{
				scene.SetLightEnvironment( lightResource.DBId );
			}
			if (sceneObject != null)
			{
				scene.Remove(sceneObject);
				scene.Add(sceneObject);
			}
			else
			{
				Log.TraceError("Preset's sceneObject is null");
				sceneObject = new EditorSceneObject(resourceDbid);
				scene.Add(sceneObject);
			}

			EditorSceneComponent component = sceneObject.GetRootEditorSceneComponent();

			if( component != null )
			{
				sceneObject.ShowSkin( 0, true, component.GetDBID() );
			}

			if ( sceneObject.GetRawEditorSceneObject() != (System.IntPtr)0 )
			{
				if ( Recolor.A > 0.0f )
				{
					PF_EditorNative.Utils.RecolorSceneObject( sceneObject.GetRawEditorSceneObject(), recolor.R, recolor.G, recolor.B );
				}
				else
				{
					PF_EditorNative.Utils.ResetSceneObjectRecolor( sceneObject.GetRawEditorSceneObject() );
				}
			}

			foreach (EditorSceneObject eso in ListOfNoneObjects)
			{
				scene.Remove(eso);
			}
			bool isContainWaterComponent = false;
			foreach (LocatorInfo info in components)
			{
				if (info.GetComponentObject() == null && info.ComponentResource != null && !info.ComponentResource.DBId.IsEmpty)
				{
					info.SetComponentObject( new EditorSceneObject(info.ComponentResource.DBId) );
					info.GetComponentObject().SetInitialPlacement( info.Placement );
					scene.Add(info.GetComponentObject());
					info.GetComponentObject().ShowSkin(0, true, DBID.Empty);
				}

				if (info.Locator != string.Empty && info.Locator.Length > 0 && info.GetComponentObject() != null)
				{
					if (locators.IndexOf(info.Locator) != -1)
					{
						info.GetComponentObject().SetInitialPlacement( info.Placement );
						sceneObject.AttachToByLocator(info.Locator, info.GetComponentObject(), info.GetComponentObject().GetInitialPlacement());
						scene.Remove(info.GetComponentObject());
						info.SetComponentObject(null);
					}
					else if (info.Locator == "None")
					{
						info.GetComponentObject().SetInitialPlacement( info.Placement );
						scene.Remove(info.GetComponentObject());
						scene.Add(info.GetComponentObject());
					}
				}

				if ( info.GetComponentObject() != null && info.IsTerrainLike )
				{
					info.GetComponentObject().SetTerrainLikeObject();
				}

				if ( info.GetComponentObject() != null && info.GetComponentObject().IsContainWaterComponent() )
				{
					isContainWaterComponent = true;
				}
			}
			foreach ( EffectInfo info in effects )
			{
				if ( info.GetComponentObject() != null )
				{
					scene.Remove( info.GetComponentObject() );
					info.SetComponentObject( null );
				}

				if ( info.ComponentResource.Get() is BasicEffectAttached )
				{
					if ( IsValidEffect( info ) )
					{
						info.SetComponentObject( new EditorSceneObject( info.ComponentResource.Get().component.DBId ) );
						scene.Add( info.GetComponentObject() );
						info.GetComponentObject().SetParentTransformUsageFlags( (uint)( ( info.ComponentResource.Get() as BasicEffectAttached ).attachFlags ) );
						info.GetComponentObject().ShowSkin( 0, true, DBID.Empty );

						string locatorName = (info.ComponentResource.Get() as BasicEffectAttached).attachType;

						if ( !string.IsNullOrEmpty(locatorName) )
						{
							sceneObject.AttachToByLocator( locatorName, info.GetComponentObject(), info.GetComponentObject().GetInitialPlacement() );
							scene.Remove( info.GetComponentObject() );
							info.SetComponentObject( null );
						}
					}
				}
				else if ( info.ComponentResource.Get() is BasicEffectStandalone )
				{
					if ( IsValidEffect( info ) )
					{
						info.SetComponentObject( new EditorSceneObject( info.ComponentResource.Get().component.DBId ) );
						scene.Add( info.GetComponentObject() );
						info.GetComponentObject().ShowSkin( 0, true, DBID.Empty );
						BasicEffectStandalone eff = info.ComponentResource.Get() as BasicEffectStandalone;
						DBTypes.Placement pl = sceneObject.GetStandAloneEffectPlacement( eff.parentType, (int)eff.parentFlags );
						if ( pl != null )
						{
							info.GetComponentObject().SetCurrentPlacement( pl );
						}
					}
				}
				else if ( info.ComponentResource.Get() is BasicEffect )
				{
					if ( IsValidEffect( info ) )
					{
						info.SetComponentObject( new EditorSceneObject( info.ComponentResource.Get().component.DBId ) );
						scene.Add( info.GetComponentObject() );
						info.GetComponentObject().ShowSkin( 0, true, DBID.Empty );
					}
				}
			}

      if ( resource.Get() is AdvMapCreepSpawner || resource.Get() is AdvMapNeutralCreepSpawner )
      {
        // Скрываем объект, тк в спавнере рисуем кастомно
        var pl = sceneObject.GetCurrentPlacement();
        pl.scale.x = 0.00001f;
        pl.scale.y = 0.00001f;
        pl.scale.z = 0.00001f;
        sceneObject.SetCurrentPlacement( pl );

        foreach ( var so in ListOfSpawnerObjects )
        {
          scene.Remove( so );
        }
        ListOfSpawnerObjects.Clear();

        if ( resource.Get() is AdvMapCreepSpawner )
        {
          AdvMapCreepSpawner advMapCreepObj = resource.Get() as AdvMapCreepSpawner;
          foreach( var creep in advMapCreepObj.creeps )
          {
            RecreateSpawner( creep.creep.Get().sceneObject.DBId, creep.place );
          }
        }

        if ( resource.Get() is AdvMapNeutralCreepSpawner )
        {
          AdvMapNeutralCreepSpawner advMapCreepObj = resource.Get() as AdvMapNeutralCreepSpawner;
          foreach ( var group in advMapCreepObj.groups )
          {
            foreach( var creep in group.creeps )
            {
              RecreateSpawner( creep.creep.Get().sceneObject.DBId, creep.offset );
            }
          }
        }
      }

			locators = sceneObject.GetLocatorsNames();
			float SpeedX = 0.0f;
			float SpeedY = 0.0f;

			GetSurfaceSpeed( ref SpeedX, ref SpeedY );

			if ( spyCamera && ( Math.Sqrt( SpeedX * SpeedX + SpeedY * SpeedY ) > 0.01f || Speed > 0.01f ) )
			{
				Placement curPlace = sceneObject.GetCurrentPlacement();
				Vector3 camPos = new Vector3( curPlace.location.x, curPlace.location.y, curPlace.location.z );
				scene.GetCamera().SetSecondAnchor( camPos );
			}

			scene.SetWaterMap( isContainWaterComponent );
			ReinitTime();
		}

		private bool IsValidEffect( EffectInfo info )
		{
			return info.GetComponentObject() == null && info.ComponentResource != null
			       && info.ComponentResource.Get().component != null
			       && !info.ComponentResource.Get().component.DBId.IsEmpty;
		}

		private void ReinitTime()
		{
			float curTimeSecond = (float)DateTime.Now.TimeOfDay.TotalMilliseconds / 1000.0f;
			oldTime = curTimeSecond;
			curTime = 0.0f;
		}

		public override void AfterRebuild()
		{
			if ( Recolor.A > 0.0f )
			{
				PF_EditorNative.Utils.RecolorSceneObject( sceneObject.GetRawEditorSceneObject(), recolor.R, recolor.G, recolor.B );
			}
			else
			{
				PF_EditorNative.Utils.ResetSceneObjectRecolor( sceneObject.GetRawEditorSceneObject() );
			}
		}

		public override bool TestForCompatible(DBID _dbid)
		{
			DBResource res = DataBase.Get<DBResource>(_dbid).Get();

			if ( res is DBSceneComponent || res is DBSceneObject
			     || res is SingleStateObject || res is MultiStateObject 
			     || res is CollisionGeometry || res is BasicEffect
			     || res is LightningEffect || res is AdvMapObstacle
           || res is AdvMapCreepSpawner || res is AdvMapNeutralCreepSpawner )
			{
				return true;
			}
			return false;
		}

		public override void SetMainObject(DBID _resource, EditorSceneObject so)
		{
			resourceDbid = _resource;
		  resource = DataBase.Get<DBResource>( _resource );
			sceneObject = so;
			locators = so.GetLocatorsNames();
		}

		public override EditorSceneObject GetMainObject()
		{
			return sceneObject;
		}

		public override List<string> GetLocators()
		{
			return locators;
		}

		public override void AddNoneObject(EditorSceneObject eso)
		{
			ListOfNoneObjects.Add(eso);
		}

		public override void OnTimerTick( float time, float delta )
		{
			if ( scene == null ) return;
			if ( !scene.IsValid() ) return;
			if ( sceneObject == null ) return;

			oldTime = curTime;
			curTime += delta;
			if ( TimeToDeath != 0.0f && curTime > TimeToDeath )
			{
				sceneObject.Die();
				curTime = 0.0f;
			}
			
			Placement curPlace = sceneObject.GetCurrentPlacement();
			Vector3 camPos = new Vector3( curPlace.location.x, curPlace.location.y, curPlace.location.z );
			if ( spyCamera )
				scene.GetCamera().SetSecondAnchor( camPos );

			if ( Distance == 0.0f )
			{
				Placement tempPlace = sceneObject.GetCurrentPlacement();
				tempPlace.location.x = 0.0f;
				tempPlace.location.y = 0.0f;
				sceneObject.SetCurrentPlacement(tempPlace);
				return;
			}

			float SpeedX = 0.0f;
			float SpeedY = 0.0f;

			GetSurfaceSpeed( ref SpeedX, ref SpeedY );

			float deltaX = SpeedX * delta * scene.TimeSpeed;
			float deltaY = SpeedY * delta * scene.TimeSpeed - Speed * delta * scene.TimeSpeed;

			if ( SpeedX == 0.0f && SpeedY == 0.0f && Speed == 0.0f )
			{
				return;
			}

			Vector3 newCamPos = new Vector3( curPlace.location.x, curPlace.location.y, curPlace.location.z );

			curPlace.location.x += deltaX;
			curPlace.location.y += deltaY;

			if ( Math.Sqrt(curPlace.location.x*curPlace.location.x+curPlace.location.y*curPlace.location.y) > Distance )
			{
				newCamPos = new Vector3(0.0f, 0.0f, 0.0f);
				curPlace.location.x = 0.0f;
				curPlace.location.y = 0.0f;
			}

			sceneObject.SetCurrentPlacement(curPlace);
			if ( spyCamera )
				scene.GetCamera().SetSecondAnchor( newCamPos );
		}

		private void GetSurfaceSpeed( ref float SpeedX, ref float SpeedY )
		{
			if ( sceneObject.GetRootEditorSceneComponent() != null && agc1 != null )
			{
				Vec2 res = agc1.GetCurNodeSurfSpeed();
				SpeedX = res.x;
				SpeedY = res.y;
			}
			else if ( sceneObject.GetRootEditorSceneComponent() != null && agc2 != null )
			{
				Vec2 res = agc2.GetCurNodeSurfSpeed();
				SpeedX = res.x;
				SpeedY = res.y;
			}
		}
	}
}
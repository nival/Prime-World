using EditorNative;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using EditorLib.Settings;
using libdb.Diagnostics;
using DBTypes;

namespace EditorPlugins.Scene.Presets
{
	[ConfigObject( false, "ScenePreset" )]
	public class StaticMeshPreset : ScenePreset
	{
		private DBID resource;
		private EditorSceneObject sceneObject;

		private SimpleEditorScene scene;

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

		public override void Init(SimpleEditorScene _scene)
		{
			scene = _scene;
		}

		public override void Release()
		{
			if (sceneObject != null)
			{
				scene.Remove(sceneObject);
				sceneObject = null;
			}
		}

		public override void Rebuild()
		{
			if ( scene == null )
				return;
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
				sceneObject = new EditorSceneObject(resource);
				scene.Add(sceneObject);
			}
		}

		public override bool TestForCompatible(DBID _dbid)
		{
			DBPtr<DBResource> res = DataBase.Get<DBResource>(_dbid);
			if (res.Get() is DBTypes.StaticMesh)
			{
				return true;
			}
			return false;
		}

		public override void SetMainObject(DBID _resource, EditorSceneObject so)
		{
			resource = _resource;
			sceneObject = so;
		}

		public override EditorSceneObject GetMainObject()
		{
			return sceneObject;
		}
	}
}
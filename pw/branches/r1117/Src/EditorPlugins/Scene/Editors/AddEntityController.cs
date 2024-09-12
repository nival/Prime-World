using System.Collections.Generic;
using System.Collections.ObjectModel;
using EditorNative;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;

namespace EditorPlugins.Scene.Editors
{
	public abstract class AddEntityController
	{
    private readonly SceneControl sceneControl;
    private readonly SceneElement[] sceneObjects;
    private readonly Vector2[] offsets;

		public IEnumerable<SceneElement> SceneObjects
		{
			get { return new ReadOnlyCollection<SceneElement>( sceneObjects ); }
		}

    protected AddEntityController( SceneControl _sceneControl, SceneElement[] _sceneObjects )
		{
      sceneControl = _sceneControl;
			sceneObjects = _sceneObjects;
      offsets = new Vector2[sceneObjects.Length];

      PickResult pickResult = sceneControl.Pick();

      //_sceneControl.Scene.DeselectAll();
      
			for ( int i = 0; i < sceneObjects.Length; ++i )
      {
        offsets[i] = new Vector2( sceneObjects[i].Location.X, this.sceneObjects[i].Location.Y );
        Vector3 position;
        if ( pickResult.HasTerrainIntersection )
          position = new Vector3( pickResult.TerrainIntersection.X + offsets[i].X, pickResult.TerrainIntersection.Y + offsets[i].Y, 0.0f );
        else
          position = new Vector3( 0.0f, 0.0f, 0.0f );

        sceneObjects[i].Location = position;
        sceneControl.Scene.Add( sceneObjects[i] );
        sceneControl.Scene.Select( sceneObjects[i] );
      }
		}

    private void RemoveVisibleObjects()
    {
      foreach ( SceneElement obj in sceneObjects )
        sceneControl.Scene.Remove( obj );
    }

		internal AddEntityController OnAdd()
		{
			RemoveVisibleObjects();
      PickResult pickResult = sceneControl.Pick();
      if ( pickResult.HasTerrainIntersection )
      {
        var intersection = pickResult.TerrainIntersection;
        return PerformAddition( intersection.X, intersection.Y );
      }
      return null;
		}

		internal void OnMove()
		{
      PickResult pickResult = sceneControl.Pick();
      if (pickResult == null) 
        return;
      if ( pickResult.HasTerrainIntersection )
      {
        for ( int i = 0; i < sceneObjects.Length; ++i )
        {
          sceneObjects[i].Location = new Vector3( pickResult.TerrainIntersection.X + offsets[i].X, pickResult.TerrainIntersection.Y + offsets[i].Y, 0.0f );
          GameSceneObject gso = sceneObjects[i] as GameSceneObject;
          if ( gso != null && gso.IsMSO() 
            && gso.Scene != null && gso.Scene.HasTerrain )
          {
            int nature = gso.Scene.SceneTerrain.GetFraction( gso.Location.X, gso.Location.Y );
            gso.SetSceneObject( nature );
          }

        }
      }
		}

		internal void OnCancel()
		{
			RemoveVisibleObjects();
		}

    protected abstract AddEntityController PerformAddition( float x, float y );
	}
}

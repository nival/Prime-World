using System.Collections.Generic;
using DBTypes;
using EditorNative.Manipulators;
using EditorNative.SceneElements;
using EditorPlugins.Scene.Editors;
using libdb.DB;
using libdb.Diagnostics;
using libdb.UndoRedo;

namespace PF_Editor.Map.AdvMapObjects
{
  internal class RoadVisualObject : ControllableVisualObject, IObjectTransformController, IPickableSceneElement
  {
    private Road road = null;
    private RoadWrapper roadWrapper = null;
    private readonly AdvMapObject mapObject = null;

    protected RoadVisualObject(EditorControl editor, AdvMapObject advMapObject, bool placeToMap)
			: base(editor, advMapObject, placeToMap)
		{
      mapObject = advMapObject;
		}

    internal static ControllableVisualObject CreateRoadVisualObject( EditorControl editor, AdvMapObject advMapObject, bool placeToMap )
    {
      return new RoadVisualObject( editor, advMapObject, placeToMap );
    }
    
    protected override List<DBID> InitSceneObjects(GameObject gameObj)
    {
      if (gameObj is Road)
      {
        List<DBID> sceneObjects = new List<DBID>();

        if(!isPlacedToMap)
          sceneObjects.Add(DBID.FromString("Tech/Default/Flag.SOBJ"));

        return sceneObjects;
      }

      Log.AlwaysAssert("Invalid gameObj. In this case gameObj must be type of Road.");
			
      return base.InitSceneObjects(gameObj);
    }

    public void Rebuild()
    {
      if(roadWrapper != null)
        roadWrapper.Rebuild();
    }

    public void Store()
    {
      roadWrapper.Store(road.bakedFileName);
    }

    #region IObjectTransformController Members

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
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.RotationPitch
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.RotationRoll
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.RotationYaw
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.ScalingX
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.ScalingY
    {
      get { return TransformParameters.Disabled; }
    }

    TransformParameters IObjectTransformController.ScalingZ
    {
      get { return TransformParameters.Disabled; }
    }

    bool IObjectTransformController.IsCommonCenter { get; set; }

    #endregion

    #region IPickableSceneElement Members

    public bool IsIntersectWith( float terrainX, float terrainY, EditorNative.Vector3 pickLocation )
    {
      if(roadWrapper != null)
      {
        return roadWrapper.IsIntersectWith( terrainX, terrainY, pickLocation );
      }

      return false;
    }

    #endregion

    protected override void OnBeforeOwnerChanged()
    {
      base.OnBeforeOwnerChanged();

      if(roadWrapper != null)
      {
        roadWrapper.Dispose();
        roadWrapper = null; 
      }
    }

    protected override void OnOwnerChanged()
    {
      base.OnOwnerChanged();

      if(Scene != null)
      {
        road = mapObject.gameObject.Get() as Road;

        //Add points to empty road
        if( road.points.Count < 2 )
        {
          using( UndoRedoTransaction trans = new UndoRedoTransaction( "Add road points" ) )
          {
            var pt = new RoadControlPoint();
            pt.location.x = mapObject.offset.translateX - 20;
            pt.location.y = mapObject.offset.translateY;
            pt.width = 10;
            road.points.Add( pt );

            pt = new RoadControlPoint();
            pt.location.x = mapObject.offset.translateX + 10;
            pt.location.y = mapObject.offset.translateY - 10;
            pt.width = 10;
            road.points.Add( pt );

            trans.Commit();
          }
        }

        roadWrapper = new RoadWrapper( road, mapObject.offset, Scene );
      }
    }
  }
}

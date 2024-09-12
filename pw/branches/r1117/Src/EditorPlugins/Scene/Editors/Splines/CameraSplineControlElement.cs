using DBTypes;
using EditorNative;
using EditorNative.SceneElements;
using libdb.UndoRedo;
using EditorNative.Manipulators;
using System;

namespace EditorPlugins.Scene.Editors.Splines
{
    internal class CameraSplineControlElement : SceneElement, IPickableSceneElement, IMovingController, IObjectTransformController
  {
    private const float markSize = 1.0f;
    private const int POINT_SEGMENTS = 20;
    private int hight;
    private readonly ISplineMainElement splineMainElement = null;
    private readonly Vec3 location = null;
    private readonly Vec3 rotation = null;
    private Quat rot = new Quat();

    public Spline3DControlPointDesc ControlPoint { get; private set; }

    public CameraSplineControlElement(ISplineMainElement _spline, Spline3DControlPointDesc _point, int _hight)
    {
      ControlPoint = _point;
      splineMainElement = _spline;

      hight = _hight;

      location = _point.position;
      rotation = _point.rotation;

      UpdateRotQuat();

      if (location.z <= 0) location.z = hight;

      IsSelectable = true;
    }

    private void UpdateRotQuat()
    {
        Placement place = new Placement();
        Placement2 place2 = new Placement2();
        PlacementConverter converter = new PlacementConverter();
        place2.rotationX = rotation.x;
        place2.rotationY = rotation.y;
        place2.rotationZ = rotation.z;
        converter.convertPlacement(place2, place);
        if ( !splineMainElement.IsAbsolutePosition )
        {
          Quaternion convertrot=new Quaternion( place.rotation.x, place.rotation.y, place.rotation.z, place.rotation.w );
          Quaternion newrot = splineMainElement.BaseRotation*convertrot;
          place.rotation.x = newrot.X;
          place.rotation.y = newrot.Y;
          place.rotation.z = newrot.Z;
          place.rotation.w = newrot.W;
        }
        rot = place.rotation;
    }

    private void ToRelativePosition(Vec3 point)
    {
        if (!splineMainElement.IsAbsolutePosition)
        {
            point.x -= splineMainElement.BaseLocation.X;
            point.y -= splineMainElement.BaseLocation.Y;
            point.z -= splineMainElement.BaseLocation.Z;
        }
    }

    public bool IsIntersectWith( float terrainX, float terrainY, Vector3 pickLocation )
    {
      float z = 0;

      Vector3 point = new Vector3(location.x, location.y, location.z);
      splineMainElement.CorrectPosition( point );
      
      // проверка пересечения с помощью луча камеры
      Vector3 locationCamera = Scene.SceneCamera.Location;
      Scene.SceneTerrain.TryGetHeight( terrainX, terrainY, ref z );
      Vector3 directionRay = new Vector3( terrainX - locationCamera.X, terrainY - locationCamera.Y, z - locationCamera.Z );
      float deltaRay = Math.Abs(Math.Abs(point.Z - locationCamera.Z) / directionRay.Normalized.Z);
      Vector3 pickPos = locationCamera + directionRay.Normalized * deltaRay;

      float dist2 = (pickPos.X - point.X) * (pickPos.X - point.X) + (pickPos.Y - point.Y) * (pickPos.Y - point.Y);
      if ( dist2 < markSize * markSize )
      {
        Scene.SceneTerrain.TryGetHeight( point.X, point.Y, ref z );
        Location.Z = z;
        pickLocation.X = Location.X;
        pickLocation.Y = Location.Y;
        pickLocation.Z = Location.Z;

        return true;
      }
      return false;
    }

    public override void Draw()
    {
      const int angleK = 2;

      System.Drawing.Color drawColor = IsSelected ? System.Drawing.Color.White : System.Drawing.Color.Red;

      Vector3 point = new Vector3( location.x, location.y, location.z );
      splineMainElement.CorrectPosition(point);

      base.Location.X = point.X;
      base.Location.Y = point.Y;
      base.Location.Z = point.Z;

      UpdateRotQuat();
      Quaternion rotating = new Quaternion(rot.x, rot.y, rot.z, rot.w);

      Vector3 transformedX = rotating.Rotate(new Vector3(1, 0, 0));
      Vector3 transformedY = rotating.Rotate(new Vector3(0, 1, 0));
      Vector3 transformedZ = rotating.Rotate(new Vector3(0, 0, 1));

      // рисование усечённой пирамиды с двумя основаниями A1B1C1D1 и A2B2C2D2
      Vector3 pointA1 = new Vector3(point.X, point.Y, point.Z);
      Vector3 pointB1 = new Vector3(point.X, point.Y, point.Z);
      Vector3 pointC1 = new Vector3(point.X, point.Y, point.Z);
      Vector3 pointD1 = new Vector3(point.X, point.Y, point.Z);

      pointA1 += transformedX.Normalized;
      pointA1 += transformedZ.Normalized;

      pointB1 -= transformedX.Normalized;
      pointB1 += transformedZ.Normalized;

      pointC1 -= transformedX.Normalized;
      pointC1 -= transformedZ.Normalized;

      pointD1 += transformedX.Normalized;
      pointD1 -= transformedZ.Normalized;

      // рисование первого основания
      EditorRender.DrawLine3D(pointA1, pointB1, drawColor, false);
      EditorRender.DrawLine3D(pointB1, pointC1, drawColor, false);
      EditorRender.DrawLine3D(pointC1, pointD1, drawColor, false);
      EditorRender.DrawLine3D(pointD1, pointA1, drawColor, false);

      Vector3 pointA2 = new Vector3(point.X, point.Y, point.Z);
      Vector3 pointB2 = new Vector3(point.X, point.Y, point.Z);
      Vector3 pointC2 = new Vector3(point.X, point.Y, point.Z);
      Vector3 pointD2 = new Vector3(point.X, point.Y, point.Z);

      pointA2 += (transformedY.Normalized * hight);
      pointB2 += (transformedY.Normalized * hight);
      pointC2 += (transformedY.Normalized * hight);
      pointD2 += (transformedY.Normalized * hight);

      pointA2 += (transformedX.Normalized * angleK);
      pointA2 += (transformedZ.Normalized * angleK);

      pointB2 -= (transformedX.Normalized * angleK);
      pointB2 += (transformedZ.Normalized * angleK);

      pointC2 -= (transformedX.Normalized * angleK);
      pointC2 -= (transformedZ.Normalized * angleK);

      pointD2 += (transformedX.Normalized * angleK);
      pointD2 -= (transformedZ.Normalized * angleK);

      // рисование второго основания
      // GreenYellow - это верхняя грань камеры, чтобы было понятно где у камеры верх
      EditorRender.DrawLine3D(pointA2, pointB2, System.Drawing.Color.GreenYellow, false);
      EditorRender.DrawLine3D(pointB2, pointC2, drawColor, false);
      EditorRender.DrawLine3D(pointC2, pointD2, drawColor, false);
      EditorRender.DrawLine3D(pointD2, pointA2, drawColor, false);

      // рисование граней
      EditorRender.DrawLine3D(pointA1, pointA2, System.Drawing.Color.GreenYellow, false);
      EditorRender.DrawLine3D(pointB1, pointB2, System.Drawing.Color.GreenYellow, false);
      EditorRender.DrawLine3D(pointC1, pointC2, drawColor, false);
      EditorRender.DrawLine3D(pointD1, pointD2, drawColor, false);

      EditorRender.DrawCircle3D(point, markSize, POINT_SEGMENTS, drawColor);

      // линия взгляда
      Vector3 viewPoint = new Vector3(0, 0, 0);
      viewPoint = point + transformedY.Normalized * hight * 2;
      EditorRender.DrawLine3D(point, viewPoint, System.Drawing.Color.GreenYellow, false);
    }

    public Vector2 TileCoordinates
    {
      get { return new Vector2( Location.X, Location.Y ); }
    }

    public void Move(float offsetX, float offsetY, bool nonTile)
    {
        PickResult pickResult = splineMainElement.SceneControl.Pick();
        if (pickResult.HasTerrainIntersection)
        {
            using (UndoRedoTransaction trans = new UndoRedoTransaction("Move point"))
            {
                //т.к. Vector3 класс, нам надо создавтать новый экземпляр, чтобы не попортить исходные данные
                Location = new Vector3(pickResult.TerrainIntersection.X,
                                        pickResult.TerrainIntersection.Y,
                                        pickResult.TerrainIntersection.Z);

                location.x = Location.X + offsetX;
                location.y = Location.Y + offsetY;
                
                ToRelativePosition(location);
                
                trans.Commit();
            }
        }

        splineMainElement.Invalidate();
    }

    public void SetPosition( Vector3 pos, Vec3 rot )
    {
      using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Update Point" ) )
      {
        location.x = pos.X;
        location.y = pos.Y;
        location.z = pos.Z;
        ToRelativePosition( location );

        rotation.x = rot.x;
        rotation.y = rot.y;
        rotation.z = rot.z;

        trans.Commit();

        splineMainElement.Invalidate();
      }
    }

    protected override void OnSelectionChanged()
    {
      base.OnSelectionChanged();
      
      splineMainElement.UpdateToolbarItems();
    }

    public void AddToScene( EditorScene scene )
    {
      scene.Add( this );
    }

    public void RemoveFromScene()
    {
      Scene.Remove( this );
    }
  
    #region IObjectTransformController Members

    Vector3 IObjectTransformController.Location
    {
        get
        {
            Vector3 vec = new Vector3(location.x, location.y, location.z);
            splineMainElement.CorrectPosition(vec);
            return (vec);
        }
        set
        {
            using (UndoRedoTransaction trans = new UndoRedoTransaction("Move point"))
            {
                Vector3 newLocation = new Vector3( value.X, value.Y, value.Z );

                location.x = newLocation.X; 
                location.y = newLocation.Y;
                location.z = newLocation.Z;

                ToRelativePosition(location);

                trans.Commit();
            }

            splineMainElement.Invalidate();
        }
    }

    Quaternion IObjectTransformController.Rotation
    {
        get { UpdateRotQuat(); return new Quaternion(rot.x, rot.y, rot.z, rot.w); }
        set
        {
            Placement place = new Placement();
            Placement2 place2 = new Placement2();
            PlacementConverter converter = new PlacementConverter();

            using ( UndoRedoTransaction trans = new UndoRedoTransaction("Rotate Point") )
            {
                rot.x = value.X;
                rot.y = value.Y;
                rot.z = value.Z;
                rot.w = value.W;
                place.rotation = rot;
                converter.convertPlacement(place, place2);
                rotation.x = place2.rotationX;
                rotation.y = place2.rotationY;
                rotation.z = place2.rotationZ;
                
                trans.Commit();
            }
        }
    }

    Vector3 IObjectTransformController.Scale { get { return (new Vector3(1, 1, 1)); } set { } }

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
        get { return TransformParameters.FullEnabled; }
    }

    TransformParameters IObjectTransformController.ScalingY
    {
        get { return TransformParameters.FullEnabled; }
    }

    TransformParameters IObjectTransformController.ScalingZ
    {
        get { return TransformParameters.FullEnabled; }
    }

    bool IObjectTransformController.IsCommonCenter { get; set; }

    #endregion
  }
}

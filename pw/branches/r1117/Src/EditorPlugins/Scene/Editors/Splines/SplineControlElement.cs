using DBTypes;
using EditorNative;
using EditorNative.SceneElements;
using libdb.UndoRedo;

namespace EditorPlugins.Scene.Editors.Splines
{
  internal class SplineControlElement : SceneElement, IPickableSceneElement, IMovingController
  {
    private const float markSize = 1.0f;
    private const int POINT_SEGMENTS = 20;
    private readonly ISplineMainElement splineMainElement = null;
    private readonly Vec2 location = null;

    private readonly SplineWidthElement widthControl = null;
    public SplineWidthElement WidthControl { get { return widthControl; } }

    public FlatSplineControlPointDesc ControlPoint { get; private set; }

    public SplineControlElement(ISplineMainElement _spline, FlatSplineControlPointDesc _point)
    {
      ControlPoint = _point;
      
      splineMainElement = _spline;
      location = _point.location;

      Location.X = location.x;
      Location.Y = location.y;
      Location.Z = 0;
      splineMainElement.CorrectPosition( Location );

      if ( splineMainElement.HasWidth )
        widthControl = new SplineWidthElement( splineMainElement, this );

      IsSelectable = true;
    }

    public bool IsIntersectWith( float terrainX, float terrainY, Vector3 pickLocation )
    {
      Vector3 point = new Vector3( location.x, location.y, 0 );
      splineMainElement.CorrectPosition( point );
      float dist2 = ( terrainX - point.X ) * ( terrainX - point.X ) + ( terrainY - point.Y ) * ( terrainY - point.Y );
      if ( dist2 < markSize * markSize )
      {
        float z = 0;
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
      System.Drawing.Color drawColor = IsSelected ? System.Drawing.Color.White : System.Drawing.Color.Red;

      float z = 0;
      Vector3 point1 = new Vector3( location.x, location.y, 0 );

      splineMainElement.CorrectPosition( point1 );
      Scene.SceneTerrain.TryGetHeight( point1.X, point1.Y, ref z );
      point1.Z = z;

      Location.X = point1.X;
      Location.Y = point1.Y;
      Location.Z = point1.Z;

      EditorRender.DrawCircle3D( point1, markSize, POINT_SEGMENTS, drawColor );
    }

    public Vector2 TileCoordinates
    {
      get { return new Vector2( Location.X, Location.Y ); }
    }

    public void Move( float offsetX, float offsetY, bool nonTile )
    {
      PickResult pickResult = splineMainElement.SceneControl.Pick();
      if ( pickResult.HasTerrainIntersection )
      {
        using(UndoRedoTransaction trans = new UndoRedoTransaction("Move point"))
        {
          //т.к. Vector3 класс, нам надо создавтать новый экземпляр, чтобы не попортить исходные данные
          Location = new Vector3( pickResult.TerrainIntersection.X,
                                  pickResult.TerrainIntersection.Y,
                                  pickResult.TerrainIntersection.Z );

          location.x = Location.X + offsetX;
          location.y = Location.Y + offsetY;

          if( !splineMainElement.IsAbsolutePosition )
          {
            location.x -= splineMainElement.BaseLocation.X;
            location.y -= splineMainElement.BaseLocation.Y;
          }

          trans.Commit();
        }
      }
      splineMainElement.Invalidate();
    }

    protected override void OnSelectionChanged()
    {
      base.OnSelectionChanged();
      
      splineMainElement.UpdateToolbarItems();
    }

    public void AddToScene( EditorScene scene )
    {
      scene.Add( this );
      if ( widthControl != null )
        scene.Add( widthControl );
    }

    public void RemoveFromScene()
    {
      if ( widthControl != null )
        Scene.Remove( widthControl );
      Scene.Remove( this );
    }
  }
}

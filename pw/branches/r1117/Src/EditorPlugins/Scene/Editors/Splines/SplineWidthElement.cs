using System;
using EditorNative;
using EditorNative.SceneElements;
using libdb.Diagnostics;
using libdb.UndoRedo;

namespace EditorPlugins.Scene.Editors.Splines
{
  internal class SplineWidthElement : SceneElement, IPickableSceneElement, IMovingController
  {
  	public static SplineWidthElement mainElement;// Элемент относительно которого расчитывается мульти перемещение

  	private static float mainElementWidth;
  	private static float mainElementWidthOffset;

    private const float markSize = 1.0f;
    private const int POINT_SEGMENTS = 20;
    private readonly ISplineMainElement splineMainElement = null;
    private WideSplineSampledPoint splinePoint = null;

    public SplineControlElement ControlElement { get; private set; }

    public SplineWidthElement(ISplineMainElement _spline, SplineControlElement _control)
    {
      splineMainElement = _spline;
      ControlElement = _control;

      IsSelectable = true;
    }

    public void SetSampledPoint(WideSplineSampledPoint _splinePoint)
    {
      Log.Assert(_splinePoint != null);

      splinePoint = _splinePoint;
    }

    public bool IsIntersectWith( float terrainX, float terrainY, Vector3 pickLocation )
    {
      if (splinePoint == null) return false;

      Vector3 point = new Vector3(splinePoint.location.X + splinePoint.normal.X * splinePoint.width,
        splinePoint.location.Y + splinePoint.normal.Y * splinePoint.width, 0);

      splineMainElement.CorrectPosition(point);
      
      float dist21 = (terrainX - point.X) * (terrainX - point.X) + (terrainY - point.Y) * (terrainY - point.Y);

      point.X -= 2 * splinePoint.normal.X * splinePoint.width;
      point.Y -= 2 * splinePoint.normal.Y * splinePoint.width;

      float dist22 = (terrainX - point.X) * (terrainX - point.X) + (terrainY - point.Y) * (terrainY - point.Y);
      
      if (dist21 < markSize * markSize || dist22 < markSize * markSize)
      {
        pickLocation.X = Location.X;
        pickLocation.Y = Location.Y;
        pickLocation.Z = Location.Z;

        return true;
      }

      return false;
    }

    public override void Draw()
    {
      if (splinePoint == null)
        return;

      System.Drawing.Color drawColor = IsSelected ? System.Drawing.Color.White : System.Drawing.Color.Magenta;
      Location = ControlElement.Location;
      float z = 0;
      
      Vector3 point1 = new Vector3( splinePoint.location.X + splinePoint.normal.X * splinePoint.width,
                                    splinePoint.location.Y + splinePoint.normal.Y * splinePoint.width, 0);

      splineMainElement.CorrectPosition(point1);
      Scene.SceneTerrain.TryGetHeight( point1.X, point1.Y, ref z );
      point1.Z = z;

      EditorRender.DrawCircle3D( point1, markSize, POINT_SEGMENTS, drawColor );



      point1 = new Vector3( splinePoint.location.X - splinePoint.normal.X * splinePoint.width,
                            splinePoint.location.Y - splinePoint.normal.Y * splinePoint.width, 0 );

      splineMainElement.CorrectPosition( point1 );
      Scene.SceneTerrain.TryGetHeight( point1.X, point1.Y, ref z );
      point1.Z = z;

      EditorRender.DrawCircle3D( point1, markSize, POINT_SEGMENTS, drawColor );
    }

    public Vector2 TileCoordinates
    {
      get{ return new Vector2(Location.X, Location.Y); }
    }

    public void Move(float offsetX, float offsetY, bool nonTile)
    {
      PickResult pickResult = splineMainElement.SceneControl.Pick();
      if (splinePoint != null && pickResult.HasTerrainIntersection)
      {
        using(UndoRedoTransaction trans = new UndoRedoTransaction("Move point"))
        {
          //т.к. Vector3 класс, нам надо создавтать новый экземпляр, чтобы не попортить исходные данные
          Vector3 pickLocation = new Vector3( pickResult.TerrainIntersection.X,
                                             pickResult.TerrainIntersection.Y,
                                             pickResult.TerrainIntersection.Z );

          if( !splineMainElement.IsAbsolutePosition )
          {
            pickLocation.X -= splineMainElement.BaseLocation.X;
            pickLocation.Y -= splineMainElement.BaseLocation.Y;
          }

          pickLocation.X -= splinePoint.location.X;
          pickLocation.Y -= splinePoint.location.Y;

					if(this == mainElement)
					{
						mainElementWidth = (float)Math.Sqrt( pickLocation.X * pickLocation.X + pickLocation.Y * pickLocation.Y );
						mainElementWidthOffset = mainElementWidth - splinePoint.width;
					}

					splinePoint.width += mainElementWidthOffset;
					splinePoint.cpoint.width += mainElementWidthOffset;

					// Равномерная ширина
					//splinePoint.width = mainElementWidth;
					//splinePoint.cpoint.width = mainElementWidth;
        }
      }
      splineMainElement.Invalidate();
    }

    protected override void OnSelectionChanged()
    {
      base.OnSelectionChanged();

      splineMainElement.UpdateToolbarItems();
    }
  }
}

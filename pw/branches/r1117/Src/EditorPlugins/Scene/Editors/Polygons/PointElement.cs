using DBTypes;
using EditorNative;
using EditorNative.SceneElements;
using libdb.UndoRedo;

namespace EditorPlugins.Scene.Editors.Polygons
{
  internal class PointElement : SceneElement, IPickableSceneElement, IMovingController
  {
    private const float markSize = 1.0f;
    private readonly  IPolygonMainElement mainElement = null;
    private readonly Vec2 location = null;
    public Vec2 Point { get { return location; } }

    public PointElement( IPolygonMainElement _mainElement, Vec2 _location )
    {
      location = _location;
      mainElement = _mainElement;

      Location.X = location.x;
      Location.Y = location.y;
      Location.Z = 0;
      IsSelectable = true;
    }

    public bool IsIntersectWith( float terrainX, float terrainY, Vector3 pickLocation )
    {
      float dist2 = ( terrainX - location.x ) * ( terrainX - location.x ) + ( terrainY - location.y ) * ( terrainY - location.y );
      if ( dist2 < markSize * markSize * 3 )
      {
        float z = 0;
        Scene.SceneTerrain.TryGetHeight( location.x, location.y, ref z );
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

      Scene.SceneTerrain.TryGetHeight( point1.X, point1.Y, ref z );
      point1.Z = z;

      Location.X = point1.X;
      Location.Y = point1.Y;
      Location.Z = point1.Z;

      EditorRender.DrawPoint3D( point1, markSize, drawColor );
    }

    public Vector2 TileCoordinates
    {
      get { return new Vector2( Location.X, Location.Y ); }
    }

    public void Move( float offsetX, float offsetY, bool nonTile )
    {
      PickResult pickResult = mainElement.SceneControl.Pick();
      if ( pickResult.HasTerrainIntersection )
      {
        using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Move point" ) )
        {
          Location = new Vector3( pickResult.TerrainIntersection.X,
                                  pickResult.TerrainIntersection.Y,
                                  pickResult.TerrainIntersection.Z );
          location.x = Location.X + offsetX;
          location.y = Location.Y + offsetY;

          trans.Commit();
        }
      }
      if ( mainElement != null )
        mainElement.Invalidate( location );
    }

    protected override void OnSelectionChanged()
    {
      if ( mainElement != null )
        mainElement.SelectionChanged( location, IsSelected );
    }

  }
}

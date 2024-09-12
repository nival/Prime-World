using DBTypes;
using EditorNative;
using EditorNative.SceneElements;
using libdb.UndoRedo;
using libdb;

namespace EditorPlugins.Scene.Editors.Polygons
{
  internal class PolylineElement 
  {
    private readonly IPolygonMainElement mainElement = null;
    private readonly ScriptPolygonAreaPolygon polygon;

    public PolylineElement( IPolygonMainElement _mainElement, ScriptPolygonAreaPolygon _polygon )
    {
      polygon = _polygon;
      mainElement = _mainElement;
    }

    public void Draw()
    {
      System.Drawing.Color drawColor = System.Drawing.Color.FromArgb( polygon.color.R, polygon.color.G, polygon.color.B );

      for ( int i = 0; i < polygon.indexes.Count; ++i )
      {
        Vector3 point1 = mainElement.GetPoint( polygon.indexes[i] );
        Vector3 point2 = mainElement.GetPoint( polygon.indexes[( i + 1 ) % polygon.indexes.Count] );
        EditorRender.DrawLine3D( point1, point2, drawColor, false );
      }
    }

  }
}

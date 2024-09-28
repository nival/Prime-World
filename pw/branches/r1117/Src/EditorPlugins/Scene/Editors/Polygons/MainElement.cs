using EditorPlugins.Scene;
using EditorNative.SceneElements;
using EditorNative;
using EditorPlugins.Mathematics;
using DBTypes;
using System.Collections.Generic;
using System.Drawing;
using libdb.DB;
using libdb;

namespace EditorPlugins.Scene.Editors.Polygons
{
  
  internal interface IPolygonMainElement
  {
    SceneControl SceneControl { get; }
    void Invalidate( Vec2 point );
    void SelectionChanged( Vec2 point, bool selected );
    Vector3 GetPoint( int index );
  }

  internal struct PermittedOperations
  {
    public bool addPoint;
    public bool deletePoint;
    public bool createPolygon;
    public bool subdivideEdge;
  }

  internal class MainElement : SceneElement, IPolygonMainElement
  {
    private readonly DBResource resource;

    private readonly IChangeableList<Vec2> points = null;
    private List<PointElement> controlPoints = new List<PointElement>();

    private readonly IChangeableList<ScriptPolygonAreaPolygon> polygons = null;
    private List<PolylineElement> controlPolygons = new List<PolylineElement>();

    public SceneControl SceneControl { get; protected set; }
    private List<int> selectedIndexes = new List<int>();
    private PermittedOperations ops = new PermittedOperations();

    public delegate void UpdateToolbarItemsHandler( PermittedOperations ops );
    public event UpdateToolbarItemsHandler UpdateToolbarItemsEvent = null;

    public MainElement( SceneControl control, DBResource _resource, IChangeableList<Vec2> _points, IChangeableList<ScriptPolygonAreaPolygon> _polygons )
    {
      points = _points;
      polygons = _polygons;
      resource = _resource;
      SceneControl = control;
    }

    public void AddToScene( EditorScene scene )
    {
      scene.Add( this );
      for ( int i = 0; i < points.Count; ++i )
      {
        PointElement newCP = new PointElement( this, points[i] );
        controlPoints.Add( newCP );
        scene.Add( newCP );
      }
      for ( int i = 0; i < polygons.Count; ++i )
      {
        PolylineElement newP = new PolylineElement( this, polygons[i] );
        controlPolygons.Add( newP );
      }
      points.ListItemAdded += OnPointAdded;
      points.ListItemChanged += OnPointChanged;
      points.ListItemBeforeRemoved += OnPointRemoving;

      polygons.ListItemAdded += OnPolygonAdded;
      polygons.ListItemChanged += OnPolygonChanged;
      polygons.ListItemBeforeRemoved += OnPolygonRemoving;

      SelectionChanged( null, false );
    }
    public void RemoveFromScene()
    {
      points.ListItemAdded -= OnPointAdded;
      points.ListItemChanged -= OnPointChanged;
      points.ListItemBeforeRemoved -= OnPointRemoving;
      polygons.ListItemAdded -= OnPolygonAdded;
      polygons.ListItemChanged -= OnPolygonChanged;
      polygons.ListItemBeforeRemoved -= OnPolygonRemoving;

      for ( int i = 0; i < controlPoints.Count; ++i )
        Scene.Remove( controlPoints[i] );
      Scene.Remove( this );
    }

    public override void Draw()
    {
      foreach ( PolylineElement p in controlPolygons )
        p.Draw();
    }

    public void Invalidate( Vec2 point )
    {
    }

    public void SelectionChanged( Vec2 point, bool selected )
    {
      int idx = points.IndexOf( point );
      if ( selected )
        selectedIndexes.Add( idx );
      else
        selectedIndexes.Remove( idx );

      ops.addPoint = selectedIndexes.Count <= 1;
      ops.deletePoint = selectedIndexes.Count >= 1;
      ops.createPolygon = selectedIndexes.Count >= 3 && !HasEqualPolygon( selectedIndexes );
      ops.subdivideEdge = selectedIndexes.Count == 2 && HasEdge( selectedIndexes );

      if ( null != UpdateToolbarItemsEvent )
        UpdateToolbarItemsEvent( ops );
    }

    private bool HasEqualPolygon(List<int> indexes)
    {
      foreach ( var p in polygons )
      {
        if ( indexes.Count < p.indexes.Count )
          continue;

        bool containsAll = true;
        foreach( int idx in p.indexes )
          if ( !indexes.Contains(idx) )
          {
            containsAll = false;
            break;
          }
        if ( containsAll )
          return true;
      }
      return false;
    }

    private bool HasEdge(List<int> indexes)
    {
      if ( indexes.Count != 2 )
        return false;

      foreach ( var p in polygons )
        if ( IndexOfSublist( indexes, p.indexes ) >= 0 )
          return true;

      return false;
    }

    private int IndexOfSublist( IList<int> sub, IList<int> list )
    {
      for( int i1 = 0; i1 < list.Count; ++i1 )
      {
        if ( list[i1] == sub[0] )
        {
          bool match = true;
          for ( int i2 = 1; i2 < sub.Count; ++i2 )
          {
            if ( list[( i1 + i2 ) % list.Count] != sub[i2] )
            {
              match = false;
              break;
            }
          }
          if ( match )
            return i1;
        }
        else if ( list[i1] == sub[sub.Count - 1] )
        {
          bool match = true;
          for ( int i2 = 1; i2 < sub.Count; ++i2 )
          {
            if ( list[( i1 + i2 ) % list.Count] != sub[sub.Count - 1 - i2] )
            {
              match = false;
              break;
            }
          }
          if ( match )
            return i1;
        }
      }
      return -1;
    }

    public Vector3 GetPoint( int index )
    {
      var res = new Vector3( points[index].x, points[index].y, 0 );

      float z = 0;
      Scene.SceneTerrain.TryGetHeight( res.X, res.Y, ref z );
      res.Z = z;
      return res;
    }

    internal new bool IsSelected { get { return selectedIndexes.Count > 0; } }


#region Operations
    internal void AddPoint( float x, float y )
    {
      if ( selectedIndexes.Count > 0 )
      {
        Vec2 cp = points[selectedIndexes[0]];
        Vector3 dir = ( new Vector3( cp.x, cp.y, 0 ) - new Vector3( x, y, 0 ) ).Normalized;
        Vector3 pos = new Vector3( cp.x, cp.y, 0 ) + dir * 5.0f;
        x = pos.X;
        y = pos.Y;
        controlPoints[selectedIndexes[0]].IsSelected = false;
      }
      else
      {
        y = y + 5.0f;
      }

      Vec2 v = new Vec2(resource);
      v.x = x;
      v.y = y;
      points.Add( v );
      controlPoints[points.Count-1].IsSelected = true;
    }

    internal void DeletePoint( PointElement element )
    {
      int idx = controlPoints.IndexOf( element );
      points.RemoveAt( idx );

      for ( int n = 0; n < polygons.Count; )
      {
        var p = polygons[n];
        for ( int i = 0; i < p.indexes.Count; )
        {
          if ( p.indexes[i] == idx )
            p.indexes.RemoveAt(i);
          else
          {
            if ( p.indexes[i] > idx )
              p.indexes[i]--;
            ++i;
          }
        }
        if ( p.indexes.Count < 3 )
          polygons.Remove( p );
        else 
          ++n;
      }
    }

    private readonly System.Drawing.Color[] polyColors = new System.Drawing.Color[]{
      System.Drawing.Color.FromArgb( 255,151,0 ),
      System.Drawing.Color.FromArgb( 0,128,0 ),
      System.Drawing.Color.FromArgb( 255,203,0 ),
      System.Drawing.Color.FromArgb( 151,203,0 ),
      System.Drawing.Color.FromArgb( 2,129,129 ),
      System.Drawing.Color.FromArgb( 255,0,128),
      System.Drawing.Color.FromArgb( 0,0,255 ),
      System.Drawing.Color.FromArgb( 0,107,197 ),
      System.Drawing.Color.FromArgb( 0,202,255 ),
      System.Drawing.Color.FromArgb( 255,0,0 ),
      System.Drawing.Color.FromArgb( 255,128,255 ),
    };

    internal void CreatePolygon()
    {
      ScriptPolygonAreaPolygon p = new ScriptPolygonAreaPolygon( resource );
      p.name = polygons.Count.ToString();
      System.Drawing.Color c = polyColors[polygons.Count % polyColors.Length];
      p.color.R = c.R;
      p.color.G = c.G;
      p.color.B = c.B;
      foreach ( int idx in selectedIndexes )
        p.indexes.Add( idx );

      polygons.Add( p );
      while ( selectedIndexes.Count > 1 )
        controlPoints[selectedIndexes[0]].IsSelected = false;
    }

    internal void SubdivideEdge()
    {
      Vec2 newCP = new Vec2( resource );
      newCP.x = (points[selectedIndexes[0]].x + points[selectedIndexes[1]].x) / 2;
      newCP.y = (points[selectedIndexes[0]].y + points[selectedIndexes[1]].y) / 2;
      points.Add( newCP );
      int newIdx = points.Count-1;
      
      foreach ( var p in polygons )
      {
        int idx = IndexOfSublist( selectedIndexes, p.indexes );
        if ( idx < 0 )
          continue;
        p.indexes.Insert( idx + 1, newIdx );
      }
      while( selectedIndexes.Count > 0 )
        controlPoints[selectedIndexes[0]].IsSelected = false;
      controlPoints[newIdx].IsSelected = true;
    }
#endregion

    #region Event handlers

    private void OnPointAdded( object sender, ListItemAddedEventArgs<Vec2> e )
    {
      PointElement newCP = new PointElement( this, points[e.Index] );
      controlPoints.Insert( e.Index, newCP );
      Scene.Add( newCP );
    }
    private void OnPointChanged( object sender, ListItemChangedEventArgs<Vec2> e )
    {
      PointElement newCP = new PointElement( this, points[e.Index] );
      Scene.Remove( controlPoints[e.Index] );
      controlPoints[e.Index] = newCP;
      Scene.Add( newCP );
    }
    private void OnPointRemoving( object sender, ListItemBeforeRemovedEventArgs<Vec2> e )
    {
      Scene.Remove( controlPoints[e.Index] );
      controlPoints.RemoveAt( e.Index );
      selectedIndexes.Remove( e.Index );
    }

    private void OnPolygonAdded( object sender, ListItemAddedEventArgs<ScriptPolygonAreaPolygon> e )
    {
      PolylineElement newP = new PolylineElement( this, polygons[e.Index] );
      controlPolygons.Insert( e.Index, newP );
    }
    private void OnPolygonChanged( object sender, ListItemChangedEventArgs<ScriptPolygonAreaPolygon> e )
    {
      PolylineElement newP = new PolylineElement( this, polygons[e.Index] );
      controlPolygons[e.Index] = newP;
    }
    private void OnPolygonRemoving( object sender, ListItemBeforeRemovedEventArgs<ScriptPolygonAreaPolygon> e )
    {
      controlPolygons.RemoveAt( e.Index );
    }
    #endregion


  }
}
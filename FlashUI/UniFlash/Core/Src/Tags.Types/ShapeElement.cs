using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using SwfDotNet.IO.Tags.Types;
using UnityEngine;

namespace Flash
{
  [System.Serializable]
  public class ShapeElement : RenderableElement, ISerializable
  {
    [System.Serializable]
    public class ShapePoints : IEnumerable<Vector3>, ISerializable
    {
      private readonly List<Vector3> _points = new List<Vector3>();

      private Vector3 _lastAddedPoint;//небольшая подпорка, используется только в IsTheSameContour
      /// <summary>
      /// Точка, которая была последней добавлена в ShapePoints, но она может не присутствовать в нем, т.к. некоторые точки игнорируются
      /// </summary>
      public Vector3 LastAddedPoint { get { return _lastAddedPoint; } }

      public ShapePoints()
      {

      }

      public ShapePoints( SerializationInfo info, StreamingContext context )
      {
        SerializeHelpers.Unpack( info, "_points", out _points );
      }

      public void GetObjectData( SerializationInfo info, StreamingContext context )
      {
        SerializeHelpers.Pack( info, "_points", _points );
      }

      public void Clear()
      {
        _points.Clear();
      }

      public void Add( Vector3 point )
      {
        //всегда добавляем нулевой элемент
        //if ( _points.Count == 0 || ( point - _points.LastOrDefault() ).magnitude >= FlashEnv.VERTEX_ADJ_BIAS )
        _points.Add( point );

        _lastAddedPoint = point;
      }

      public void AddRange( IEnumerable<Vector3> points )
      {
        foreach ( var point in points )
        {
          Add( point );
        }
      }

      public int Count { get { return _points.Count; } }

      public bool IsClosed
      {
        get { return ( _points[0] - _points[_points.Count - 1] ).magnitude < 1; }
      }

      public Vector3 this[int index]
      {
        //set { _points[index] = value; }
        get { return _points[index]; }
      }

      public IEnumerator<Vector3> GetEnumerator()
      {
        return _points.GetEnumerator();
      }

      IEnumerator IEnumerable.GetEnumerator()
      {
        return GetEnumerator();
      }
    }

    private ShapePoints _points = new ShapePoints();
    public ShapePoints Points
    {
      get { return _points; }
      set { _points = value; }
    }

    private SwfDotNet.IO.Tags.Types.Rect _bounds = new SwfDotNet.IO.Tags.Types.Rect( 0, 0, 0, 0 );
    public SwfDotNet.IO.Tags.Types.Rect LocalBounds
    {
      get { return _bounds; }
      set { _bounds = value; }
    }

    private StyleChangeRecord _styleChangeRecord;
    public StyleChangeRecord StyleChangeRecord
    {
      get { return _styleChangeRecord; }
      set { _styleChangeRecord = value; }
    }

    private bool _containsFillStyle;

    public bool ContainsFillStyle
    {
      get { return _containsFillStyle; }
    }

    private bool _containsLineStyle;
    public bool ContainsLineStyle
    {
      get { return _containsLineStyle; }
    }
    private UniFillStyle _uniFillStyle = new UniFillStyle();
    public UniFillStyle UniFillStyle
    {
      get { return _uniFillStyle; }
      set
      {
        _containsFillStyle = value != null;
        _uniFillStyle = value;
      }
    }
    private UniLineStyle _uniLineStyle = new UniLineStyle();

    public UniLineStyle UniLineStyle
    {
      get { return _uniLineStyle; }
      set
      {
        _containsLineStyle = value != null;
        _uniLineStyle = value;
      }
    }

    public bool Contains( ShapeElement other )
    {
      var t = this.LocalBounds;
      var o = other.LocalBounds;
      return t.XMin <= o.XMin && t.YMin <= o.YMin && t.XMax >= o.XMax && t.YMax >= o.YMax;
    }

    public bool IsClosed
    {
      get { return _points.IsClosed; }
    }

    public ShapeElement()
    {
      _points = new ShapePoints();
    }

    public ShapeElement( SerializationInfo info, StreamingContext context )
      : base( info, context )
    {
      _points = new ShapePoints( info, context );

      SerializeHelpers.Unpack( info, "_styleChangeRecord", out _styleChangeRecord );
      SerializeHelpers.Unpack( info, "_containsFillStyle", out _containsFillStyle );
      SerializeHelpers.Unpack( info, "_containsLineStyle", out _containsLineStyle );
      SerializeHelpers.Unpack( info, "_uniFillStyle", out _uniFillStyle );
      SerializeHelpers.Unpack( info, "_uniLineStyle", out _uniLineStyle );
    }

    public override void GetObjectData( SerializationInfo info, StreamingContext context )
    {
      base.GetObjectData( info, context );

      _points.GetObjectData( info, context );

      SerializeHelpers.Pack( info, "_styleChangeRecord", _styleChangeRecord );
      SerializeHelpers.Pack( info, "_containsFillStyle", _containsFillStyle );
      SerializeHelpers.Pack( info, "_containsLineStyle", _containsLineStyle );
      SerializeHelpers.Pack( info, "_uniFillStyle", _uniFillStyle );
      SerializeHelpers.Pack( info, "_uniLineStyle", _uniLineStyle );
    }

    public override void Release()
    {
      _points = null;
      StyleChangeRecord = null;
    }
    public override void Dispose()
    {
      base.Dispose();
      UniFlashPlayer.MaterialsReseted -= OnMaterialReset;
    }
    /// <summary>
    /// Subscribes element to lost device event.
    /// After device obtaining element must to update TextureMatrix
    /// in proposes of visual artifacts like in PF-52674
    /// </summary>
    public void RegisterTextureMatrixKeeper()
    {
      UniFlashPlayer.MaterialsReseted += OnMaterialReset;
    }

    /// <summary>
    /// Updating material's texture matrix by UniFillStyle.BitmapTransform
    /// </summary>
    private void OnMaterialReset()
    {
      if ( FillMaterial != null && FillMaterial.RenderMaterial != null )
      {
        if ( UniFillStyle != null )
          FillMaterial.RenderMaterial.SetMatrix( "_BitmapMatrix", UniFillStyle.BitmapTransform );

        FillMaterial.HasScaleGrid = false;
      }
    }
  }
}
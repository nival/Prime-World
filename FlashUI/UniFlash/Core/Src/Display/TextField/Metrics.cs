using System.Runtime.Serialization;
using UnityEngine;
using Flash;

namespace Flash
{
  [System.Serializable]
  public class Metrics : ISerializable, IFontMetrics
  {
    public Metrics()
    {}

    protected Metrics( SerializationInfo info, StreamingContext context )
    {
      SerializeHelpers.Unpack( info, "_id", out _id );
      SerializeHelpers.Unpack( info, "_char", out _char );
      SerializeHelpers.Unpack( info, "_lineHeight", out _lineHeight );
      SerializeHelpers.Unpack( info, "_floor", out _floor );
      SerializeHelpers.Unpack( info, "_rect", out _rect );
      SerializeHelpers.Unpack( info, "_uvMin", out  _uvMin );
      SerializeHelpers.Unpack( info, "_uvMax", out _uvMax );
      SerializeHelpers.Unpack( info, "_width", out _width );
      SerializeHelpers.Unpack( info, "_height", out  _height );
      SerializeHelpers.Unpack( info, "_kern", out _kern );
    }

    void ISerializable.GetObjectData( SerializationInfo info, StreamingContext context )
    {
      SerializeHelpers.Pack( info, "_id", _id );
      SerializeHelpers.Pack( info, "_char", _char );
      SerializeHelpers.Pack( info, "_lineHeight", _lineHeight );
      SerializeHelpers.Pack( info, "_floor", _floor );
      SerializeHelpers.Pack( info, "_rect", _rect );
      SerializeHelpers.Pack( info, "_uvMin", _uvMin );
      SerializeHelpers.Pack( info, "_uvMax", _uvMax );
      SerializeHelpers.Pack( info, "_width", _width );
      SerializeHelpers.Pack( info, "_height", _height );
      SerializeHelpers.Pack( info, "_kern", _kern );
    }

    private Texture2D _tex;
    public Texture2D Tex { get { return _tex; } set { _tex = value; } }

    private float _id;
    public float ID { get { return _id; } set { _id = value; } }

    private char _char;
    public char Char { get { return _char; } set { _char = value; } }

    private int _lineHeight = -1;
    public int LineHeight
    {
      get { return _lineHeight; }
      set
      {
        if ( _lineHeight < 0 )
          _lineHeight = value;
      }
    }

    private int _floor = -1;
    public int Floor
    {
      get { return _floor; }
      set
      {
        if ( _floor < 0 )
          _floor = value;
      }
    }

    private Rect _rect;
    public Rect Rect { get { return _rect; } set { _rect = value; } }

    private Vector2 _uvMin;
    public Vector2 UvMin { get { return _uvMin; } }

    private Vector2 _uvMax;
    public Vector2 UvMax { get { return _uvMax; } }

    private int _width;
    public int Width { get { return _width; } set { _width = value; } }
    public float FWidth { get { return (float)_width; } }

    private int _height;
    public int Height { get { return _height; } }

    public MetricsExt Ext { get { return default(MetricsExt); } }

    private int _kern;
    public int Kern { get { return _kern; } }

    public Metrics SetKert( int kern )
    {
      //TODO: Remove
      if ( kern != 0 )
      {
        Metrics copy = (Metrics)MemberwiseClone();
        copy._kern = kern;
        return copy;
      }
      return this;
    }

    public new string ToString()
    {
      return string.Format( "LineHeight={0}, Floor={1}, Rect={2}, Width={3}, Height={4}, uvMin={5}, uvMax={6}",
       _lineHeight, _floor, _rect, Width, Height, UvMin, UvMax );
    }

    public void Recalculate()
    {
      _uvMin = new Vector2( _rect.xMin, _rect.yMin );
      _uvMax = new Vector2( _rect.xMax, _rect.yMax );
      _width = (int)_rect.width;
      _height = (int)_rect.height;
    }
  }
}



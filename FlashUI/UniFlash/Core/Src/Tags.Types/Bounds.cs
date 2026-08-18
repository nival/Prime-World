using UnityEngine;
using System.Runtime.Serialization;

namespace Flash
{
  [System.Serializable]
  public struct Bounds : ISerializable
  {
    private Vector3 _leftTop;
    public Vector3 LeftTop
    {
      get { return _leftTop; }
      set { _leftTop = value; }
    }
    private Vector3 _rightBottom;
    public Vector3 RightBottom
    {
      get { return _rightBottom; }
      set { _rightBottom = value; }
    }
    public Vector3 Center
    {
      get
      {
        return ( RightBottom + LeftTop ) / 2;
      }
    }
    public float Width
    {
      get { return Mathf.Abs( RightBottom.x - LeftTop.x ); }
    }
    public float Height
    {
      get { return Mathf.Abs( RightBottom.y - LeftTop.y ); }
    }

    void ISerializable.GetObjectData( SerializationInfo info, StreamingContext context )
    {
      Flash.SerializeHelpers.Pack( info, "_leftTop", _leftTop );
      Flash.SerializeHelpers.Pack( info, "_rightBottom", _rightBottom );
    }

    public Bounds( SerializationInfo info, StreamingContext context )
    {
      Flash.SerializeHelpers.Unpack( info, "_leftTop", out _leftTop );
      Flash.SerializeHelpers.Unpack( info, "_rightBottom", out _rightBottom );
    }

    public Bounds(Bounds oth)
    {
      _leftTop = oth._leftTop;
      _rightBottom = oth._rightBottom;
    }

    public Bounds( Vector3 lt, Vector3 rb )
    {
      _leftTop = lt;
      _rightBottom = rb;
    }
    public static Bounds operator *( Matrix4x4 matrix, Bounds bounds )
    {
      Bounds result = new Bounds();
      result.LeftTop = matrix.MultiplyPoint3x4( bounds.LeftTop );
      result.RightBottom = matrix.MultiplyPoint3x4( bounds.RightBottom );
      return result;
    }
    public static Bounds operator +( Bounds bounds, Vector3 translation )
    {
      Bounds result = new Bounds();
      result.LeftTop = bounds.LeftTop + translation;
      result.RightBottom = bounds.RightBottom + translation;
      return result;
    }
    public static Bounds operator +( Bounds bounds, Bounds boundsRhs )
    {
      Bounds result = new Bounds();
      result.LeftTop = bounds.LeftTop + boundsRhs.LeftTop;
      result.RightBottom = bounds.RightBottom + boundsRhs.RightBottom;
      return result;
    }
    public static bool operator ==( Bounds lhs, Bounds rhs )
    {
      return lhs.Equals( rhs );
    }
    public static bool operator !=( Bounds lhs, Bounds rhs )
    {
      return !( lhs == rhs );
    }

    public override bool Equals( object obj )
    {
      if ( obj == null || !( obj is Bounds ) )
        return false;
      return Equals( (Bounds)obj );
    }

    public bool Equals( Bounds rhs )
    {
      if ( this.LeftTop != rhs.LeftTop )
        return false;
      if ( this.RightBottom != rhs.RightBottom )
        return false;

      return true;
    }

    public override int GetHashCode()
    {
      return base.GetHashCode();
    }

    public static Bounds Lerp( Bounds lhs, Bounds rhs, float t )
    {
      Bounds result = new Bounds();

      result.LeftTop = Vector2.Lerp( lhs.LeftTop, rhs.LeftTop, t );
      result.RightBottom = Vector2.Lerp( lhs.RightBottom, rhs.RightBottom, t );

      return result;
    }
    public bool Contains( Vector2 pos )
    {
      if ( pos.x >= LeftTop.x
      && pos.x <= RightBottom.x
      && pos.y >= LeftTop.y
      && pos.y <= RightBottom.y )
      {
        return true;
      }

      return false;
    }
    public bool Intersects( Bounds bounds )
    {
      return !( bounds.RightBottom.x < LeftTop.x
          || bounds.LeftTop.x > RightBottom.x
          || bounds.RightBottom.y < LeftTop.y
          || bounds.LeftTop.y > RightBottom.y );
    }
    public void ExtendToBounds( Bounds bounds )
    {
      _leftTop.x = Min( LeftTop.x, bounds.LeftTop.x, bounds.RightBottom.x );
      _leftTop.y = Min( LeftTop.y, bounds.LeftTop.y, bounds.RightBottom.y );
      _rightBottom.x = Max( RightBottom.x, bounds.LeftTop.x, bounds.RightBottom.x );
      _rightBottom.y = Max( RightBottom.y, bounds.LeftTop.y, bounds.RightBottom.y );
    }
    private static float Min( float x1, float x2, float x3 )
    {
      return Mathf.Min( x1, Mathf.Min( x2, x3 ) );
    }
    private static float Max( float x1, float x2, float x3 )
    {
      return Mathf.Max( x1, Mathf.Max( x2, x3 ) );
    }
    public void ExtendToMesh( Mesh mesh, Matrix4x4 matrix )
    {
      var bounds = mesh.bounds;
      _leftTop = matrix.MultiplyPoint3x4( bounds.max );
      _rightBottom = matrix.MultiplyPoint3x4( bounds.min );
    }
    public bool Inside( Bounds bounds )
    {
      if ( bounds.LeftTop.x > LeftTop.x
        && bounds.LeftTop.y > LeftTop.y
        && bounds.RightBottom.x < RightBottom.x
        && bounds.RightBottom.y < RightBottom.y )
        return true;

      return false;
    }
    public override string ToString()
    {
      return LeftTop.ToString( "f6" ) + " " + RightBottom.ToString( "f6" );
    }
  }
}
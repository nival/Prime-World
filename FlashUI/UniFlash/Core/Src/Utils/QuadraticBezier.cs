using UnityEngine;

namespace Flash.Utils
{
  public class QuadraticBezier
  {
    private readonly Vector3 _p0;
    public Vector3 P0
    {
      get { return _p0; }
    }
    private readonly Vector3 _p1;
    public Vector3 P1
    {
      get { return _p1; }
    }
    private readonly Vector3 _p2;
    public Vector3 P2
    {
      get { return _p2; }
    }

    private int _division = 32;
    public int Division
    {
      get { return _division; }
      set { _division = value; }
    }

    public QuadraticBezier( Vector3 po, Vector3 p1, Vector3 p2 )
    {
      _p0 = po;
      _p1 = p1;
      _p2 = p2;
    }

    public Vector3 GetPointAtTime( float t )
    {
      return ( 1 - t ) * ( 1 - t ) * _p0 + 2 * t * ( 1 - t ) * _p1 + t * t * _p2;
    }
    
    public Vector3[] GetTesselatedPoints( int division )
    {
      Vector3[] result = new Vector3[division + 1];

      float step = 1.0F / division;
      float t = step;
      result[0] = GetPointAtTime( 0 );

      for ( int i = 1; i < result.Length; ++i )
      {
        result[i] = GetPointAtTime( t );
        t += step;
      }

      return result;
    }
  }
}
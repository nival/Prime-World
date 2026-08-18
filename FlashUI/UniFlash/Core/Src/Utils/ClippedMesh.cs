using UnityEngine;
namespace Flash.Utils
{
  public class ClippedMesh
  {
    public Vector3 LeftTop { get; private set; }
    public Vector3 RightBottom { get; private set; }
    public Mesh Mesh { get; private set; }

    public ClippedMesh( Vector3 leftTop, Vector3 rightBottm, Mesh mesh )
    {
      LeftTop = leftTop;
      RightBottom = rightBottm;
      Mesh = mesh;
    }

    public override bool Equals( System.Object obj )
    {
      if ( obj == null )
      {
        return false;
      }

      ClippedMesh p = obj as ClippedMesh;
      if ( (System.Object)p == null )
      {
        return false;
      }

      // Return true if the fields match:
      return ( LeftTop == p.LeftTop && RightBottom == p.RightBottom && Mesh == p.Mesh );
    }

    public bool Equals( ClippedMesh obj )
    {
      ClippedMesh p = obj as ClippedMesh;
      if ( (System.Object)p == null )
      {
        return false;
      }

      return ( LeftTop == p.LeftTop && RightBottom == p.RightBottom && Mesh == p.Mesh );
    }

    public override int GetHashCode()
    {
      return Mesh.GetHashCode() ^ LeftTop.GetHashCode() ^ RightBottom.GetHashCode();
    }

    public static bool operator ==( ClippedMesh a, ClippedMesh b )
    {

      return ( a.LeftTop == b.LeftTop && a.RightBottom == b.RightBottom && a.Mesh == b.Mesh );
    }

    public static bool operator !=( ClippedMesh a, ClippedMesh b )
    {
      return !( a == b );
    }

  }
}
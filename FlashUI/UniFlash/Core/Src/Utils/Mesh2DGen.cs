using System.Collections.Generic;
using System.IO;
using System.Text;
using Native;
using UnityEngine;

namespace Flash.Utils
{
  // TODO refactor me!
  public class Mesh2DGen
  {	
    private static LinkedList<Vector3> list = null;
    private static List<LinkedListNode<Vector3>> convex = null;
    private static List<LinkedListNode<Vector3>> reflex = null;
    private static List<LinkedListNode<Vector3>> ears = null;
    private static Dictionary<ClippedMesh, Mesh> _clippedMeshesCache = new Dictionary<ClippedMesh, Mesh>();

    public static Mesh GetClippedMesh( Vector2 lt, Vector2 rb, RenderableElement element )
    {
      if ( element.FillMesh.vertexCount == 0 || element.LineTriangleOffset == 0 /*only line*/)
        return element.FillMesh;


      ClippedMesh clippedMesh = new ClippedMesh( lt, rb, element.FillMesh );

      if ( _clippedMeshesCache.ContainsKey( clippedMesh ) )
      {
        return _clippedMeshesCache[clippedMesh];
      }

      Mesh result = new Mesh();
      _clippedMeshesCache.Add( clippedMesh, result );

      int[] meshTriangles = element.FillMesh.triangles;
      Vector3[] meshVertexes = element.FillMesh.vertices;
      Color[] meshColors = element.FillMesh.colors;
      Vector2[] meshUvs = element.FillMesh.uv;
      List<int> resultTriangles = new List<int>();
      List<Vector3> resultVertexes = new List<Vector3>( meshVertexes.Length );
      List<Color> resultColors = new List<Color>( meshColors.Length );
      List<Vector2> resultUvs = new List<Vector2>( resultVertexes.Count );

      // Режем только shape часть, line часть уже порезана из флеша
      if ( element.LineTriangleOffset != -1 )
      {
        for ( int i = 0; i < element.LineTriangleOffset; ++i )
        {
          resultTriangles.Add( meshTriangles[i] );
        }
        for ( int i = 0; i < element.LineVertexOffset; ++i )
        {
          resultVertexes.Add( meshVertexes[i] );
          resultColors.Add( meshColors[i] );
        }
      }
      else
      {
        resultTriangles.AddRange( meshTriangles );
        resultVertexes.AddRange( meshVertexes );
        resultColors.AddRange( meshColors );
      }

      // Normalize
      Vector3 center = ( rb + lt ) / 2;
      for ( int i = 0; i < resultVertexes.Count; ++i )
        resultVertexes[i] -= center;
      lt -= new Vector2( center.x, center.y );
      rb -= new Vector2( center.x, center.y );

      // Vertex type
      float z = resultVertexes[0].z;

      Cut( resultTriangles, resultVertexes, resultColors, lt, new Vector2( rb.x, lt.y ) );
      Cut( resultTriangles, resultVertexes, resultColors, new Vector2( rb.x, lt.y ), rb );
      Cut( resultTriangles, resultVertexes, resultColors, rb, new Vector2( lt.x, rb.y ) );
      Cut( resultTriangles, resultVertexes, resultColors, new Vector2( lt.x, rb.y ), lt );

      // Add empty uv
      for ( int i = 0; i < resultVertexes.Count; i++ )
        resultUvs.Add( new Vector2( 0.0001F, 0.0001F ) );

      // UnNormalize
      for ( int i = 0; i < resultVertexes.Count; ++i )
        resultVertexes[i] += center;

      // Restore vertex type
      for ( int i = 0; i < resultVertexes.Count; ++i )
        resultVertexes[i] = new Vector3( resultVertexes[i].x, resultVertexes[i].y, z );

      // Push line part
      if ( element.LineTriangleOffset != -1 )
      {
        int trianglesCountTemp = resultTriangles.Count;
        int vertexesCountTemp = resultVertexes.Count;

        // Push line elements
        int offset = resultVertexes.Count - element.LineVertexOffset;
        for ( int i = element.LineVertexOffset; i < meshVertexes.Length; ++i )
        {
          resultVertexes.Add( meshVertexes[i] );
          resultColors.Add( meshColors[i] );
          resultUvs.Add( meshUvs[i] );
        }

        // Push line triangles);
        for ( int i = element.LineTriangleOffset; i < meshTriangles.Length; ++i )
        {
          resultTriangles.Add( meshTriangles[i] + offset );
        }

        // Override
        // TODO: Setters inside Get method. Need investigation.
        element.LineTriangleOffset = trianglesCountTemp;
        element.LineVertexOffset = vertexesCountTemp;
      }

      Vector3[] normals = new Vector3[resultVertexes.Count];
      for ( int i = 0; i < normals.Length; ++i )
        normals[i] = Vector3.zero;

      result.vertices = resultVertexes.ToArray();
      result.colors = resultColors.ToArray();
      result.uv = resultUvs.ToArray();
      result.normals = normals;
      result.triangles = resultTriangles.ToArray();

      return result;
    }

    public static bool EqualVectors(Vector3 a, Vector3 b, float tol)
    {
      var x = Mathf.Abs( a.x - b.x ) < tol;
      var y = Mathf.Abs( a.y - b.y ) < tol;
      var z = Mathf.Abs( a.z - b.z ) < tol;
      return x && y && z;
    }

    public static bool Tessellate(bool withCutouts, List<Vector3> contour, List<Vector3> polyVerts, List<int> polyInds )
    {
      // Triple length for generated vertices (avoids memalloc handling on native side)
      int numTotal = contour.Count * 3;
      var vertices = new Vector3[numTotal];
      for ( int v=0; v < contour.Count; ++v )
      {
        vertices[v] = contour[v];
      }

      int numVerts, numInds;
      var indices = new int[numTotal * 3];

      if ( NativeCode.Tessellate( withCutouts, contour.ToArray(), contour.Count, out vertices, out numVerts, out indices, out numInds ) )
      {
        for ( int v = 0; v < numVerts; ++v )
        {
          polyVerts.Add(vertices[v]);
        }

        for ( int i = 0; i < numInds; ++i )
        {
          polyInds.Add(indices[i]);
        }

        return true;
      }

      return false;
    }

    public static void TessellateLine(float lineWidth, bool closed, float edgeAA, List<Vector3> contour, Color color1, Color color2, List<Vector3> polyVerts, List<Vector2> polyNormals, List<Vector2> polyMarkers, List<Color> polyColors, List<int> polyInds )
    {
      // Preprocess points for easier algorithm (remove duplicate points, add helpers)
      var width = lineWidth;
      var modWidth = width + edgeAA;
      var eps = 0.01f;
      var verts = new List<Vector3>( contour );

      if(closed)
      {
        while ( verts.Count > 2 )
        {
          if ( EqualVectors( verts[0], verts[1], eps ) )
          {
            verts.RemoveAt( 0 );
          }
          else if ( EqualVectors( verts[verts.Count - 1], verts[verts.Count - 2], eps ) )
          {
            verts.RemoveAt( verts.Count - 1 );
          }
          else break;
        }
        if ( EqualVectors( verts[0], verts[verts.Count - 1], eps ) )
        {
          verts.RemoveAt( verts.Count - 1 );
        }
        if ( !EqualVectors( verts[0], verts[verts.Count - 1], eps ) )
        {
          verts.Insert( 0, verts[verts.Count - 1] );
          verts.Add( verts[1] );
          verts.Add( verts[2] );
        }
      }
      else
      {
        verts.Add(verts[verts.Count - 1]);
        verts.Add(verts[verts.Count - 1]);
      }

      // Create points with normals for extrusion in shader
      polyInds.AddRange(new List<int>() { 0, 1, 2, 2, 1, 3 });

      for ( int i = 0; i < verts.Count - 2; ++i )
      {
        var v1 = verts[i + 0];
        var v2 = verts[i + 1];
        var v3 = verts[i + 2];

        if ( EqualVectors( v2, v3, eps ) && i + 3 < verts.Count )
        {
          v3 = verts[i + 3];
        }

        var edge1 = v2 - v1;
        var edge2 = v3 - v2;
        var dot = Vector3.Dot( edge1, edge2 );
        var opp1 = new Vector2( -edge1.y, edge1.x );
        var opp2 = new Vector2( -edge2.y, edge2.x );

        var len1 = opp1.magnitude;
        if ( len1 > 0.0f )
        {
          opp1 /= len1;
          opp1 *= modWidth;
        }
        var len2 = opp2.magnitude;
        if ( len2 > 0.0f )
        {
          opp2 /= len2;
          opp2 *= modWidth;
        }

        var vertnormal = opp1 + opp2;
        if ( dot > 0.0f )
        {
          vertnormal *= 0.5f;
        }

        polyVerts.Add( v2 );
        polyVerts.Add( v2 );
        polyNormals.Add( new Vector2( vertnormal.x, vertnormal.y ) );
        polyNormals.Add( new Vector2( -vertnormal.x, -vertnormal.y ) );
        polyColors.Add( color1 );
        polyColors.Add( color2 );
        polyMarkers.Add( new Vector2( width, modWidth ) );
        polyMarkers.Add( new Vector2( width, -modWidth ) );

        if ( i > 1 )
        {
          var p = polyInds[polyInds.Count - 1];
          polyInds.Add( p );
          polyInds.Add( p + 1 );
          polyInds.Add( p - 1 );
          polyInds.Add( p + 1 );
          polyInds.Add( p );
          polyInds.Add( p + 2 );
        }
      }
    }

    #region TESSELATION
    private static void GetCyclicNodes( LinkedListNode<Vector3> current, ref LinkedListNode<Vector3> previous, ref LinkedListNode<Vector3> next )
    {
      previous = current.Previous;
      next = current.Next;
      if ( current == list.First )
        previous = list.Last;
      else if ( current == list.Last )
        next = list.First;
    }
    private static bool CheckConvex( LinkedListNode<Vector3> current, bool cw )
    {
      LinkedListNode<Vector3> previous = null;
      LinkedListNode<Vector3> next = null;
      GetCyclicNodes( current, ref previous, ref next );

      Vector3 a = previous.Value - current.Value;
      Vector3 b = next.Value - current.Value;
      Vector3 c = Vector3.Cross( a.normalized, b.normalized );

      // right side);
      if ( cw )
      {
        if ( c.z >= 0 )
        {
          if ( !convex.Contains( current ) )
          {
            convex.Add( current );
            if ( reflex.Contains( current ) )
              reflex.Remove( current );
          }
          return true;
        }
      }
      else// left side
      {
        if ( c.z <= 0 )
        {
          if ( !convex.Contains( current ) )
          {
            convex.Add( current );
            if ( reflex.Contains( current ) )
              reflex.Remove( current );
          }
          return true;
        }
      }


      if ( !reflex.Contains( current ) )
      {
        reflex.Add( current );

        if ( convex.Contains( current ) )
          convex.Remove( current );
        if ( ears.Contains( current ) )
          ears.Remove( current );
      }
      return false;
    }
    private static void CheckEar( LinkedListNode<Vector3> current )
    {
      LinkedListNode<Vector3> previous = null;
      LinkedListNode<Vector3> next = null;
      GetCyclicNodes( current, ref previous, ref next );

      if ( ears.Contains( current ) )
        ears.Remove( current );

      bool admitted = true;

      foreach ( LinkedListNode<Vector3> reflexed in reflex )
      {
        if ( reflexed == previous || reflexed == next )
          continue;

        if ( BarycentricTest( previous.Value, current.Value, next.Value, reflexed.Value ) )
        {
          admitted = false;
          break;
        }
      }

      if ( admitted )
        ears.Add( current );
    }
    private static bool BarycentricTest( Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p )
    {
      double A = GetMatrix3x3Determinant( p1.x, p2.x, p3.x,
                                        p1.y, p2.y, p3.y,
                                        1, 1, 1 );


      double A1 = GetMatrix3x3Determinant( p.x, p2.x, p3.x,
                                          p.y, p2.y, p3.y,
                                         1, 1, 1 );
      double u = A1 / A;
      if ( u < 0 )
        return false;

      double A2 = GetMatrix3x3Determinant( p1.x, p.x, p3.x,
                                          p1.y, p.y, p3.y,
                                          1, 1, 1 );

      double v = A2 / A;
      if ( v < 0 )
        return false;

      double w = 1 - u - v;
      if ( w < 0 )
        return false;

      return true;
    }
    private static float GetMatrix3x3Determinant( float a11, float a12, float a13,
                                                float a21, float a22, float a23,
                                                float a31, float a32, float a33 )
    {
      return a11 * a22 * a33 - a11 * a23 * a32 - a12 * a21 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a13 * a22 * a31;
    }
    private static bool CheckClockWise( List<Vector3> contour )
    {
      bool result = false;

      Vector3 dir = contour[0] - contour[contour.Count - 1];

      Vector3 ort = Vector3.zero;
      ort.x = dir.normalized.y;
      ort.y = -dir.normalized.x;

      Vector3 p = ( contour[contour.Count - 1] + dir * 0.5F ) + ort * 0.1F;

      //Vector3 p1;
      //Vector3 p2;
      //double xinters;

      //p1 = contour[0];
      //for (int i = 1; i <= contour.Count; i++)
      //{
      //  p2 = contour[i % contour.Count];
      //  if (p.y > Min(p1.y, p2.y))
      //  {
      //    if (p.y <= Max(p1.y, p2.y))
      //    {
      //      if (p.x <= Max(p1.x, p2.x))
      //      {
      //        if (p1.y != p2.y)
      //        {
      //          xinters = (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
      //          if (p1.x == p2.x || p.x <= xinters)
      //          {
      //            result = !result;
      //          }
      //        }
      //      }
      //    }
      //  }
      //  p1 = p2;
      //}

      for ( int i = 0, j = contour.Count - 1; i < contour.Count; j = i++ )
      {
        Vector3 p_j = contour[j];
        Vector3 p_i = contour[i];

        if ( ( ( ( p_i.y <= p.y ) && ( p.y < p_j.y ) ) || ( ( p_j.y <= p.y ) && ( p.y < p_i.y ) ) ) &&
          ( p.x < ( p_j.x - p_i.x ) * ( p.y - p_i.y ) / ( p_j.y - p_i.y ) + p_i.x ) )
        {
          result = !result;
        }
      }

      return result;
    }
    #endregion

    #region CLIPPING
    /// <summary>
    /// Degenerate triangles exist!
    /// </summary>
    private static void Cut( List<int> triangles, List<Vector3> vertexes, List<Color> colors, Vector2 p1, Vector2 p2 )
    {
      float A, B, C;
      GetLineEquation( p1.x, p1.y, p2.x, p2.y, out A, out B, out C );
      Vector3 lineEq = new Vector3( A, B, C );
      lineEq.Normalize();

      List<int> resultTriangles = new List<int>();
      List<Vector3> resultVertexes = new List<Vector3>();
      List<Color> resultColors = new List<Color>();

      for ( int t = 0; t < triangles.Count; t += 3 )
      {
        int tr0 = triangles[t];
        int tr1 = triangles[t + 1];
        int tr2 = triangles[t + 2];
        Vector3 v0 = vertexes[tr0];
        Vector3 v1 = vertexes[tr1];
        Vector3 v2 = vertexes[tr2];
        v0.z = 1;
        v1.z = 1;
        v2.z = 1;
        Color c0 = colors[triangles[tr0]];
        Color c1 = colors[tr1];
        Color c2 = colors[tr2];

        float relation0 = Vector3.Dot( lineEq, v0 );
        float relation1 = Vector3.Dot( lineEq, v1 );
        float relation2 = Vector3.Dot( lineEq, v2 );

        //Totaly outside or inside;
        if ( ( relation0 <= 0 && relation1 <= 0 && relation2 <= 0 ) ||
          ( relation0 >= 0 && relation1 >= 0 && relation2 >= 0 ) )
        {
          InsertTriangle( resultTriangles, resultVertexes, resultColors, v0, v1, v2, c0, c1, c2 );
        }
        else
        {
          if ( ( relation0 < 0 && relation1 >= 0 && relation2 >= 0 ) ||
            ( relation0 > 0 && relation1 <= 0 && relation2 <= 0 ) )
          {
            Vector2 v01 = Intersect( v0, v1, p1, p2 );
            Vector2 v02 = Intersect( v0, v2, p1, p2 );

            InsertTriangle( resultTriangles, resultVertexes, resultColors, v0, v01, v02, c0, c0, c0 );
            InsertTriangle( resultTriangles, resultVertexes, resultColors, v01, v1, v2, c1, c1, c1 );
            InsertTriangle( resultTriangles, resultVertexes, resultColors, v2, v02, v01, c2, c2, c2 );
          }
          else if ( ( relation2 < 0 && relation1 >= 0 && relation0 >= 0 ) ||
            ( relation2 > 0 && relation1 <= 0 && relation0 <= 0 ) )
          {
            Vector2 v21 = Intersect( v2, v1, p1, p2 );
            Vector2 v20 = Intersect( v2, v0, p1, p2 );

            InsertTriangle( resultTriangles, resultVertexes, resultColors, v2, v20, v21, c2, c2, c2 );
            InsertTriangle( resultTriangles, resultVertexes, resultColors, v20, v0, v21, c0, c0, c0 );
            InsertTriangle( resultTriangles, resultVertexes, resultColors, v21, v0, v1, c1, c1, c1 );
          }
          else if ( ( relation1 < 0 && relation2 >= 0 && relation0 >= 0 ) ||
            ( relation1 > 0 && relation2 <= 0 && relation0 <= 0 ) )
          {
            Vector2 v10 = Intersect( v1, v0, p1, p2 );
            Vector2 v12 = Intersect( v1, v2, p1, p2 );

            InsertTriangle( resultTriangles, resultVertexes, resultColors, v1, v12, v10, c1, c1, c1 );
            InsertTriangle( resultTriangles, resultVertexes, resultColors, v12, v2, v0, c2, c2, c2 );
            InsertTriangle( resultTriangles, resultVertexes, resultColors, v0, v10, v12, c0, c0, c0 );
          }
        }
      }

      triangles.Clear();
      vertexes.Clear();
      colors.Clear();

      triangles.AddRange( resultTriangles );
      vertexes.AddRange( resultVertexes );
      colors.AddRange( resultColors );
    }
    private static bool Intersect( float p1_x1, float p1_y1, float p1_x2, float p1_y2, float p2_x1, float p2_y1, float p2_x2, float p2_y2, out Vector2 result )
    {
      result = Vector2.zero;

      float A1, B1, C1;
      GetLineEquation( p1_x1, p1_y1, p1_x2, p1_y2, out A1, out B1, out C1 );
      float A2, B2, C2;
      GetLineEquation( p2_x1, p2_y1, p2_x2, p2_y2, out A2, out B2, out C2 );

      // Parallel or match
      if ( ( A1 * B2 - A2 * B1 ) == 0 )
      {
        return false;
      }

      float x = ( B1 * C2 - B2 * C1 ) / ( A1 * B2 - A2 * B1 );
      float y = ( C1 * A2 - C2 * A1 ) / ( A1 * B2 - A2 * B1 );

      result.x = x;
      result.y = y;

      return true;
    }
    private static Vector2 Intersect( Vector2 p1, Vector2 p2, Vector2 l1, Vector2 l2 )
    {
      Vector2 result = Vector2.zero;
      Intersect( p1.x, p1.y, p2.x, p2.y, l1.x, l1.y, l2.x, l2.y, out result );
      return result;
    }
    private static void GetLineEquation( float p_x1, float p_y1, float p_x2, float p_y2, out float A, out float B, out float C )
    {
      A = p_y1 - p_y2;
      B = p_x2 - p_x1;
      C = p_x1 * p_y2 - p_x2 * p_y1;
      //Debug.Log(String.Format("{0}x + {1}y + {2} = 0", A, B, C));
    }
    private static bool CheckRange( Vector2 p1, Vector2 p2, Vector2 t, bool scope )
    {
      float uX = ( t.x - p1.x ) / ( p2.x - p1.x );
      float uY = ( t.y - p1.y ) / ( p2.y - p1.y );
      if ( scope )
      {
        if ( uX < 0 || uX > 1 || uY < 0 || uY > 1 )
          return false;
      }
      else
      {
        if ( uX <= 0 || uX >= 1 || uY <= 0 || uY >= 1 )
          return false;
      }

      return true;
    }
    private static int GetLastIndex( List<Vector3> list )
    {
      return list.Count - 1;
    }
    private static void InsertTriangle( List<int> triangles, List<Vector3> vertexes, List<Color> colors
      , Vector3 v0, Vector3 v1, Vector3 v2, Color c0, Color c1, Color c2 )
    {
      int index = GetLastIndex( vertexes );
      vertexes.Add( v0 );
      vertexes.Add( v1 );
      vertexes.Add( v2 );
      colors.Add( c0 );
      colors.Add( c1 );
      colors.Add( c2 );
      triangles.Add( ++index );
      triangles.Add( ++index );
      triangles.Add( ++index );

      //_debugBuffer.Add(v0);
      //_debugBuffer.Add(v1);
      //_debugBuffer.Add(v2);
    }
    #endregion
  }
}
using SwfDotNet.IO.Tags.Types;
using UnityEngine;
using System.Runtime.Serialization;
using System.Collections.Generic;
using Rect = UnityEngine.Rect;

namespace Flash
{
  public class SerializeHelpers
  {
    // simple elements
    public static void Unpack<T>( SerializationInfo info, string fieldName, out T v )
    {
      v = (T)info.GetValue( fieldName, typeof( T ) );
    }

    public static void Pack<T>( SerializationInfo info, string fieldName, T v )
    {
      info.AddValue( fieldName, v );
    }

    // custom elements
    public static void Unpack( SerializationInfo info, string fieldName, out Vector3 v )
    {
      float[] pars = (float[])info.GetValue( fieldName, typeof( float[] ) );
      v = new Vector3( pars[0], pars[1], pars[2] );
    }

    public static void Pack( SerializationInfo info, string fieldName, Vector3 v )
    {
      info.AddValue( fieldName, new float[] { v.x, v.y, v.z } );
    }

    public static void Unpack( SerializationInfo info, string fieldName, out Vector2 v )
    {
      float[] pars = (float[])info.GetValue( fieldName, typeof( float[] ) );
      v = new Vector3( pars[0], pars[1] );
    }

    public static void Pack( SerializationInfo info, string fieldName, Vector2 v )
    {
      info.AddValue( fieldName, new float[] { v.x, v.y } );
    }

    public static void Unpack( SerializationInfo info, string fieldName, out Rect v )
    {
      float[] pars = (float[])info.GetValue( fieldName, typeof( float[] ) );
      v = new Rect( pars[0], pars[1], pars[2], pars[3] );
    }

    public static void Pack( SerializationInfo info, string fieldName, Rect v )
    {
      info.AddValue( fieldName, new float[] { v.x, v.y, v.width, v.height } );
    }

    public static void Unpack( SerializationInfo info, string fieldName, out Matrix4x4 v )
    {
      float[] pars = (float[])info.GetValue( fieldName, typeof( float[] ) );

      v = new Matrix4x4();

      for ( int i = 0; i < 16; ++i )
      {
        v[i] = pars[i];
      }
    }

    public static void Pack( SerializationInfo info, string fieldName, Matrix4x4 v )
    {
      float[] vs = new float[16];

      for ( int i = 0; i < vs.Length; ++i )
      {
        vs[i] = v[i];
      }

      info.AddValue( fieldName, vs );
    }

    public static void Unpack( SerializationInfo info, string fieldName, out Color v )
    {
      float[] pars = (float[])info.GetValue( fieldName, typeof( float[] ) );
      v = new Color( pars[0], pars[1], pars[2], pars[3] );
    }

    public static void Pack( SerializationInfo info, string fieldName, Color v )
    {
      float[] vs = new float[] { v.r, v.g, v.b, v.a };
      info.AddValue( fieldName, vs );
    }

    public static void Unpack( SerializationInfo info, string fieldName, out List<Vector3> v )
    {
      float[] pars = (float[])info.GetValue( fieldName, typeof( float[] ) );
      int count = pars.Length / 3;

      v = new List<Vector3>( count );

      for ( int i = 0; i < count; ++i )
      {
        int offset = 3 * i;
        v.Add( new Vector3( pars[offset + 0], pars[offset + 1], pars[offset + 2] ) );
      }
    }

    public static void Pack( SerializationInfo info, string fieldName, Dictionary<int, string> v )
    {
      int[] keys = new int[v.Count];
      string[] values = new string[v.Count];

      int i = 0;
      foreach ( var kv in v )
      {
        keys[i] = kv.Key;
        values[i] = kv.Value;
        i++;
      }
      info.AddValue( fieldName + "_keys", keys );
      info.AddValue( fieldName + "_values", values );
    }

    public static void Unpack( SerializationInfo info, string fieldName, out Dictionary<int, string> v )
    {
      int[] keys = (int[])info.GetValue( fieldName + "_keys", typeof( int[] ) );
      string[] values = (string[])info.GetValue( fieldName + "_values", typeof( string[] ) );
      v = new Dictionary<int, string>();
      for ( int i =0; i < keys.Length; i++ )
        v.Add( keys[i], values[i] );
    }

    public static void Pack( SerializationInfo info, string fieldName, List<Vector3> v )
    {
      float[] vs = new float[v.Count * 3];

      for ( int i = 0; i < v.Count; i++ )
      {
        Vector3 vec = v[i];
        int offset = 3 * i;
        vs[offset + 0] = vec.x;
        vs[offset + 1] = vec.y;
        vs[offset + 2] = vec.z;
      }

      info.AddValue( fieldName, vs );
    }

    public static void Unpack( SerializationInfo info, string fieldName, out Quaternion v )
    {
      float[] pars = (float[])info.GetValue( fieldName, typeof( float[] ) );
      v = new Quaternion( pars[0], pars[1], pars[2], pars[3] );
    }

    public static void Pack( SerializationInfo info, string fieldName, Quaternion v )
    {
      float[] vs = new float[] { v.x, v.y, v.z, v.w };
      info.AddValue( fieldName, vs );
    }

    public static void Unpack( SerializationInfo info, string fieldName, out StyleChangeRecord v )
    {
      v = new StyleChangeRecord();
      v.FillStyle0 = (int)info.GetValue( fieldName + ".FillStyle0", typeof( int ) );
      v.FillStyle1 = (int)info.GetValue( fieldName + ".FillStyle1", typeof( int ) );
      v.LineStyle = (int)info.GetValue( fieldName + ".LineStyle", typeof( int ) );
      v.MoveDeltaX = (int)info.GetValue( fieldName + ".MoveDeltaX", typeof( int ) );
      v.MoveDeltaY = (int)info.GetValue( fieldName + ".MoveDeltaY", typeof( int ) );
    }

    public static void Pack( SerializationInfo info, string fieldName, StyleChangeRecord v )
    {
      info.AddValue( fieldName + ".FillStyle0", v.FillStyle0 );
      info.AddValue( fieldName + ".FillStyle1", v.FillStyle1 );
      info.AddValue( fieldName + ".LineStyle", v.LineStyle );
      info.AddValue( fieldName + ".MoveDeltaX", v.MoveDeltaX );
      info.AddValue( fieldName + ".MoveDeltaY", v.MoveDeltaY );
    }
  }
}


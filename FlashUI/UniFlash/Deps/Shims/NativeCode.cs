using System.Drawing;
using System.Runtime.InteropServices;
using UnityEngine;

namespace Native
{
  public static class NativeCode
  {
    private const string NATIVE_DLL_NAME = "UnityPWLauncher";

    [DllImport( NATIVE_DLL_NAME )]
    public static extern void GetClientMousePosition( ref Point point );

    [DllImport( NATIVE_DLL_NAME )]
    public static extern void SetCastleCursor( [MarshalAs( UnmanagedType.LPStr )] string cursorName );

    [DllImport( NATIVE_DLL_NAME )]
    public static extern bool Tessellate( bool withCutouts, [MarshalAs( UnmanagedType.LPArray )] Vector3[] vertices3D, int count, [MarshalAs( UnmanagedType.LPArray )] out Vector3[] verts, out int numVerts, [MarshalAs( UnmanagedType.LPArray )] out int[] inds, out int numInds );
  }
}

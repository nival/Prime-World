using System;
using System.Runtime.InteropServices;
using UnityEngine;
using System.Collections;
using System.IO;
using System.Reflection;
using System.Text;

public class Device : MonoBehaviour {

	[DllImport( "ASimplePlugin" )]
	private static extern void CreateDevice();
	[DllImport( "ASimplePlugin" )]
	private static extern int GetTexture();
	[DllImport( "ASimplePlugin" )]
	private static extern void DrawTexture();
	[DllImport( "ASimplePlugin" )]
	private static extern void ReleaseDevice();
	[DllImport( "ASimplePlugin" )]
	private static extern void InitDevice();

	public GameObject g;
	private Texture2D tex;

	private void WriteL( string str )
	{
        FileStream FS = new FileStream( "C:\\lll.txt", FileMode.OpenOrCreate );
        StreamWriter SW = new StreamWriter( FS );
        SW.WriteLine( str );
        SW.Close();
	}
	
	// Use this for initialization
	private void Start () {
		//InitDevice();	
	
		g.renderer.material.mainTexture = CreateTexture();
	}
	
	private void OnGUI()
	{
		GUI.Label( new Rect( 200, 200, 100, 30 ), " я ёнити" );
	}

	private Texture2D CreateTexture()
	{
		CreateDevice();
		
		DrawTexture();
		
		System.IntPtr pnt = (System.IntPtr)GetTexture();
		byte[] data = new byte[1024*1024*4];
        Marshal.Copy(pnt, data, 0, 1024*1024*4);

		tex = new Texture2D( 1024, 1024, TextureFormat.ARGB32, false );
		Color[] colors = BytesToPixels(data);
		tex.SetPixels(colors);
		tex.Apply();
		ReleaseDevice();
		return tex;
	}
	private void OnDisable()
	{
		Destroy(tex);
	}
	private Color[] BytesToPixels(byte[] bytes)
	{
		int lendth =bytes.Length - bytes.Length%4;
		Color[] result = new Color[lendth / 4];
		int j = 0;
		for(int i=0; i<bytes.Length-4 ;i +=4 )
		{
			result[j].a = ( (float)bytes[i] / 255 );
			result[j].r = ( (float)bytes[i + 1] / 255 );
			result[j].g = ( (float)bytes[i + 2] / 255 );
			result[j].b = ( (float)bytes[i + 3] / 255 );
			j++;
		}

		return result;
	}

}

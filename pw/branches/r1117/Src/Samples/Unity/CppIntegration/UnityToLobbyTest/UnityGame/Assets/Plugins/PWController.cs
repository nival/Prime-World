using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using UnityEngine;
using System.Collections;



public class PWController : MonoBehaviour {

	private string _pathToPrimeWorld = "C:/Work/UnityToLobbyTest/PrimeWorld/PrimeWorld/bin/Debug/";

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

//	private void OnGUI()
//	{
//		if ( GUI.Button( new Rect( 30, 30, 200, 100 ), "Перейти в игру" ) )
//		{
//			MakeScreenShot();
//			Process.Start(new ProcessStartInfo(_pathToPrimeWorld+"PrimeWorld.exe"));
//		}
//
//		RECT rect;
//		GetWindowRect(FindWindow(null, "UnityGame"), out rect);
//		Rect myRect = new Rect();
//		myRect.x = rect.Left;
//		myRect.y = rect.Top;
//		myRect.width = rect.Right - rect.Left;
//		myRect.height = rect.Bottom - rect.Top;
//
//		GUI.Label( new Rect( 300, 300, 200, 100 ), myRect.ToString() );
//		GUI.Label( new Rect( 300, 400, 200, 100 ), rect.Left.ToString() );
//	}
	private void OnGUI()
	{
		if ( GUI.Button( new Rect( 30, 30, 200, 100 ), "Перейти в игру" ) )
		{
			Application.LoadLevel("Device");
		}
	}
	private void MakeScreenShot()
	{
		Application.CaptureScreenshot(_pathToPrimeWorld + "LobbyScreen.png");
	}

	[DllImport( "user32.dll", SetLastError = true )]
	static extern IntPtr FindWindow( string lpClassName, string lpWindowName );

	[DllImport( "user32.dll" )]
	[return: MarshalAs( UnmanagedType.Bool )]
	public static extern bool GetWindowRect( IntPtr hwnd, out RECT lpRect );

	[StructLayout( LayoutKind.Sequential )]
	public struct RECT
	{
		public int Left;        // x position of upper-left corner
		public int Top;         // y position of upper-left corner
		public int Right;       // x position of lower-right corner
		public int Bottom;      // y position of lower-right corner
	}
	private RECT GetRect( IntPtr handle )
	{
		RECT rct;
		GetWindowRect( handle, out rct );
		return rct;
	}
}

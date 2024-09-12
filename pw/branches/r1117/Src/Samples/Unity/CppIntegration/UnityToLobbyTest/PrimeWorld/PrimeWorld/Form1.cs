using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace PrimeWorld
{
	public partial class Form1 : Form
	{
		[DllImport( "user32.dll", SetLastError = true )]
		static extern IntPtr FindWindow( string lpClassName, string lpWindowName );

		[DllImport( "user32.dll" )]
		[return: MarshalAs( UnmanagedType.Bool )]
		public static extern bool GetWindowRect( IntPtr hwnd, out RECT lpRect );

	

		public Form1()
		{
			InitializeComponent();
		}
		private void Form1_Load( object sender, EventArgs e )
		{
			RECT rect;
			IntPtr handle = FindWindow(null, "UnityGame");
			GetWindowRect( handle, out rect );
			Process[] lobby = Process.GetProcessesByName("Lobby");
			if ( lobby.Length>0&&lobby[0] != null )
			 lobby[0].CloseMainWindow();
			Rectangle myRect = new Rectangle();
			myRect.X = rect.Left;
			myRect.Y = rect.Top;
			myRect.Width = rect.Right - rect.Left;
			myRect.Height = rect.Bottom - rect.Top;

			this.Location = new Point( myRect.X, myRect.Y );
			this.Size = new Size( myRect.Width, myRect.Height );
		}
	}
	[StructLayout( LayoutKind.Sequential )]
	public struct RECT
	{
		public int Left;        // x position of upper-left corner
		public int Top;         // y position of upper-left corner
		public int Right;       // x position of lower-right corner
		public int Bottom;      // y position of lower-right corner
	}
}

using System.Runtime.InteropServices;

namespace Win32
{
	[StructLayout( LayoutKind.Sequential )]
	public struct RECT
	{
		public int Left;
		public int Top;
		public int Right;
		public int Bottom;
	}

	[StructLayout( LayoutKind.Sequential )]
	public struct POINT
	{
		public int x;
		public int y;
	}

	[StructLayout( LayoutKind.Sequential )]
	public struct SIZE
	{
		public int cx;
		public int cy;
	}

	[StructLayout( LayoutKind.Sequential )]
	public struct FILETIME
	{
		public int dwLowDateTime;
		public int dwHighDateTime;
	}

	[StructLayout( LayoutKind.Sequential )]
	public struct SYSTEMTIME
	{
		public short wYear;
		public short wMonth;
		public short wDayOfWeek;
		public short wDay;
		public short wHour;
		public short wMinute;
		public short wSecond;
		public short wMilliseconds;
	}
}
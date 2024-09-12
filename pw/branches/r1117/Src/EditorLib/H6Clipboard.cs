using System;
using System.Collections.Generic;
using System.Text;

namespace EditorLib
{
	public static class H6Clipboard
	{
		private static List<object> copiedObjects = new List<object>();

		public static bool Copy( params object[] objs )
		{
			copiedObjects.Clear();
			if ( !ReferenceEquals( objs, null ) )
			{
				copiedObjects.AddRange( objs );
			}
			return true;
		}

		public static bool IsEmpty
		{
			get { return copiedObjects == null; }
		}

		public static object[] CopiedObjects
		{
			get { return copiedObjects.ToArray(); }
		}

		public static bool Paste( object obj )
		{
			return true;
		}
	}
}

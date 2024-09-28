using libdb.Diagnostics;
using System.IO;
using libdb.DB;

namespace PF_Editor
{
	public static class TypesHash
	{
		private static string hashFileName = "Types.md5";
		private static byte[] hash = new byte[] { 0x94, 0x86, 0x8D, 0x13, 0x72, 0x3D, 0x38, 0xDC, 0x5C, 0xB2, 0x2E, 0x54, 0x05, 0x09, 0xDF, 0xF5 };

		public static bool Check()
		{
			Stream file = DataBase.FileSystem.OpenFile( hashFileName );
			if ( file == null )
			{
				Log.TraceError( "Cannot open file \"{0}\" with database descriptor", hashFileName );
				return false;
			}

			if ( file.Length != hash.Length )
			{
				Log.TraceError( "Invalid size ({0}, expected {1}) of file \"{2}\" with database descriptor", file.Length, hash.Length, hashFileName );
				return false;
			}

			byte[] buffer = new byte[hash.Length];
			int readenBytes = file.Read( buffer, 0, buffer.Length );
			if ( readenBytes != buffer.Length )
			{
				Log.TraceError( "Cannot read from file \"{0}\" with database descriptor", hashFileName );
				return false;
			}

			for ( int i = 0; i < buffer.Length; ++i )
			{
				if ( buffer[i] != hash[i] )
				{
					Log.TraceError( "Database descriptor in binary file is out of date" );
					return false;
				}
			}

			return true;
		}
	}
}

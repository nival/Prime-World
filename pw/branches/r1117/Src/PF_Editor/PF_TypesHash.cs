using libdb.Diagnostics;
using System.IO;
using libdb.DB;

namespace PF_Editor
{
	public static class PF_TypesHash
	{
		private static string hashFileName = "PF_Types.md5";
		private static byte[] hash = new byte[] { 0xBD, 0xE3, 0xD7, 0xA0, 0xC8, 0xAD, 0xB2, 0x07, 0xC3, 0x1C, 0x6E, 0xB6, 0x9B, 0x13, 0x20, 0x3C };

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

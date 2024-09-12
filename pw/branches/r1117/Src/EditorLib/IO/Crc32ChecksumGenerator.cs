using System.IO;

namespace EditorLib.IO
{
	/// <summary>
	/// Генератор контрольной суммы по CRC32.
	/// Источник: http://ru.wikipedia.org/wiki/%D0%A6%D0%B8%D0%BA%D0%BB%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9_%D0%B8%D0%B7%D0%B1%D1%8B%D1%82%D0%BE%D1%87%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%B4
	/// </summary>
	public static class Crc32ChecksumGenerator
	{
		#region Private members.

		private static readonly uint[] crcTable = new uint[256];

		#endregion

		#region Initialization.

		static Crc32ChecksumGenerator()
		{
			for ( uint i = 0; i < crcTable.Length; ++i )
			{
				uint crc = i;
				for ( uint j = 0; j < 8; j++ )
				{
					if ( (crc & 1) != 0 )
					{
						crc = (crc >> 1) ^ 0xEDB88320u;
					}
					else
					{
						crc = crc >> 1;
					}
				}
				crcTable[i] = crc;
			}
		}
		#endregion

		#region Public static methods.

		public static uint GenerateChecksum( string filePath )
		{
			return GenerateChecksum( File.ReadAllBytes( filePath ) );
		}

		public static uint GenerateChecksum( Stream stream )
		{
			var buffer = new byte[stream.Length];
			stream.Read( buffer, 0, (int) stream.Length );
			return GenerateChecksum( buffer );
		}

		public static uint GenerateChecksum( byte[] data )
		{
			uint crc = 0xFFFFFFFFu;

			for ( int i = 0; i < data.Length; ++i )
			{
				crc = crcTable[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
			}

			return crc ^ 0xFFFFFFFFu;
		}

		#endregion
	}
}

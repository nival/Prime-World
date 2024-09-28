using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace EditorPlugins.Importer.Texture
{
	public static class Utility
	{
		public static void WriteUInt16( Stream stream, UInt16 word )
		{
			stream.WriteByte( (byte)(word & 0xff) );
			stream.WriteByte( (byte)(word >> 8) );
		}

		public static void WriteUInt24( Stream stream, int uint24 )
		{
			stream.WriteByte( (byte)(uint24 & 0xff) );
			stream.WriteByte( (byte)((uint24 >> 8) & 0xff) );
			stream.WriteByte( (byte)((uint24 >> 16) & 0xff) );
		}

		public static void WriteUInt32( Stream stream, UInt32 uint32 )
		{
			stream.WriteByte( (byte)(uint32 & 0xff) );
			stream.WriteByte( (byte)((uint32 >> 8) & 0xff) );
			stream.WriteByte( (byte)((uint32 >> 16) & 0xff) );
			stream.WriteByte( (byte)((uint32 >> 24) & 0xff) );
		}

		/// <summary>
		/// Reads a 24-bit unsigned integer from a Stream in little-endian format.
		/// </summary>
		/// <param name="stream"></param>
		/// <returns>-1 on failure, else the 24-bit unsigned integer that was read.</returns>
		public static int ReadUInt16( Stream stream )
		{
			int byte1 = stream.ReadByte();

			if ( byte1 == -1 )
			{
				return -1;
			}

			int byte2 = stream.ReadByte();

			if ( byte2 == -1 )
			{
				return -1;
			}

			return byte1 + (byte2 << 8);
		}

		public static int ReadUInt24( Stream stream )
		{
			int byte1 = stream.ReadByte();

			if ( byte1 == -1 )
			{
				return -1;
			}

			int byte2 = stream.ReadByte();

			if ( byte2 == -1 )
			{
				return -1;
			}

			int byte3 = stream.ReadByte();

			if ( byte3 == -1 )
			{
				return -1;
			}

			return byte1 + (byte2 << 8) + (byte3 << 16);
		}

		/// <summary>
		/// Reads a 32-bit unsigned integer from a Stream in little-endian format.
		/// </summary>
		/// <param name="stream"></param>
		/// <returns>-1 on failure, else the 32-bit unsigned integer that was read.</returns>
		public static long ReadUInt32( Stream stream )
		{
			int byte1 = stream.ReadByte();

			if ( byte1 == -1 )
			{
				return -1;
			}

			int byte2 = stream.ReadByte();

			if ( byte2 == -1 )
			{
				return -1;
			}

			int byte3 = stream.ReadByte();

			if ( byte3 == -1 )
			{
				return -1;
			}

			int byte4 = stream.ReadByte();

			if ( byte4 == -1 )
			{
				return -1;
			}

			return unchecked( (long)((uint)(byte1 + (byte2 << 8) + (byte3 << 16) + (byte4 << 24))) );
		}
	}
}

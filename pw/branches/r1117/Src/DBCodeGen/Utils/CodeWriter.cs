using System.Collections.Generic;
using System.IO;
using System.Text;

namespace DBCodeGen.Utils
{
	public class CodeWriter
	{
		private readonly string fileName = string.Empty;
		private readonly MemoryStream stream = null;
		private readonly TextWriter writer = null;

		public CodeWriter( string fileName )
		{
			this.fileName = fileName;
			stream = new MemoryStream();
			writer = new StreamWriter( stream, Encoding.Default );
		}

		private bool IsModified()
		{
			stream.Seek( 0, SeekOrigin.Begin );

			if ( !System.IO.File.Exists( fileName ) )
				return true;

			FileStream file = new FileStream( fileName, FileMode.Open, FileAccess.Read );
			if ( file.Length != stream.Length )
			{
				file.Close();
				return true;
			}

			byte[] fileBuffer = new byte[16384];
			byte[] streamBuffer = new byte[16384];
			bool endOfFile = false;
			while ( !endOfFile )
			{
				int length = file.Read( fileBuffer, 0, fileBuffer.Length );
				stream.Read( streamBuffer, 0, streamBuffer.Length );
				for ( int i = 0; i < length; ++i )
				{
					if ( streamBuffer[i] != fileBuffer[i] )
					{
						file.Close();
						return true;
					}
				}

				endOfFile = file.Position == file.Length;
			}

			file.Close();
			return false;
		}

		public void Close( bool dryRun )
		{
			stream.Flush();
			writer.Flush();

			if ( !dryRun && IsModified() )
			{
				string dirName = Path.GetDirectoryName( fileName );
				if ( !string.IsNullOrEmpty( dirName ) && !Directory.Exists( dirName ) )
					Directory.CreateDirectory( Path.GetDirectoryName( fileName ) );
				FileStream file = new FileStream( fileName, FileMode.Create, FileAccess.Write );
				stream.Seek( 0, SeekOrigin.Begin );
				stream.WriteTo( file );
				file.Close();
			}

			writer.Close();
		}

		public void WriteLine()
		{
			writer.WriteLine();
		}

		public void WriteLine( string line )
		{
			WriteLine( 0, line );
		}

		public void WriteLine( string format, params object[] args )
		{
			WriteLine( 0, format, args );
		}

		public void WriteLine( int ident, string line )
		{
			if ( ident > 0 )
				writer.Write( new string( '\t', ident ) );
			writer.WriteLine( line );
		}

		public void WriteLine( int ident, string format, params object[] args )
		{
			WriteLine( ident, string.Format( format, args ) );
		}

		public void WriteLines( int ident, IEnumerable<string> lines )
		{
			foreach ( string line in lines )
				WriteLine( ident, line );
		}

		public TextWriter Writer { get { return writer; } }
		public string FileName { get { return fileName; } }
	}
}

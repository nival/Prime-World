using libdb.Diagnostics;
using System.IO;
using System.Xml;
using libdb.IO;

namespace libdb.DB
{
	public sealed class XmlContextWriter: XmlWriter
	{
		private readonly XmlWriter writer = null;
		private readonly DBID context = DBID.Empty;

		public XmlContextWriter( XmlWriter writer, DBID context )
		{
			this.writer = writer;
			this.context = context;
		}

		internal static XmlContextWriter Create( IFileSystem fileSystem, DBID context )
		{
			if ( context.IsEmpty )
			{
				Log.TraceError( "Cannot store resource with empty file name" );
				return null;
			}

			if ( context.IsInlined )
			{
				Log.TraceError( "Cannot store inlined resource \"{0}", context.Name );
				return null;
			}

			Stream file = fileSystem.CreateFile( context.GetFullFileName() );
			if ( file == null )
			{
				Log.TraceError( "Cannot create file \"{0}\"", context.FileName );
				return null;
			}

			var settings = new XmlWriterSettings()
			{
				CloseOutput = true,
				Indent = true,
				IndentChars = "	"
			};

			return new XmlContextWriter( XmlWriter.Create( file, settings ), context );
		}

		internal static XmlContextWriter Create( MemoryStream memoryStream, DBID context )
		{
			var settings = new XmlWriterSettings()
			{
				CloseOutput = false,
				Indent = true,
				IndentChars = "	"
			};

			return new XmlContextWriter( XmlWriter.Create( memoryStream, settings ), context );
		}

		public override void Close() { writer.Close(); }
		public override void Flush() { writer.Flush(); }
		public override string LookupPrefix( string ns ) { return writer.LookupPrefix( ns ); }
		public override void WriteBase64( byte[] buffer, int index, int count ) { writer.WriteBase64( buffer, index, count ); }
		public override void WriteCData( string text ) { writer.WriteCData( text ); }
		public override void WriteCharEntity( char ch ) { writer.WriteCharEntity( ch ); }
		public override void WriteChars( char[] buffer, int index, int count ) { writer.WriteChars( buffer, index, count ); }
		public override void WriteComment( string text ) { writer.WriteComment( text ); }
		public override void WriteDocType( string name, string pubid, string sysid, string subset ) { writer.WriteDocType( name, pubid, sysid, subset ); }
		public override void WriteEndAttribute() { writer.WriteEndAttribute(); }
		public override void WriteEndDocument() { writer.WriteEndDocument(); }
		public override void WriteEndElement() { writer.WriteEndElement(); }
		public override void WriteEntityRef( string name ) { writer.WriteEntityRef( name ); }
		public override void WriteFullEndElement() { writer.WriteFullEndElement(); }
		public override void WriteProcessingInstruction( string name, string text ) { writer.WriteProcessingInstruction( name, text ); }
		public override void WriteRaw( string data ) { writer.WriteRaw( data ); }
		public override void WriteRaw( char[] buffer, int index, int count ) { writer.WriteRaw( buffer, index, count ); }
		public override void WriteStartAttribute( string prefix, string localName, string ns ) { writer.WriteStartAttribute( prefix, localName, ns ); }
		public override void WriteStartDocument( bool standalone ) { writer.WriteStartDocument( standalone ); }
		public override void WriteStartDocument() { writer.WriteStartDocument(); }
		public override void WriteStartElement( string prefix, string localName, string ns ) { writer.WriteStartElement( prefix, localName, ns ); }
		public override WriteState WriteState { get { return writer.WriteState; } }
		public override void WriteString( string text ) { writer.WriteString( text ); }
		public override void WriteSurrogateCharEntity( char lowChar, char highChar ) { writer.WriteSurrogateCharEntity( lowChar, highChar ); }
		public override void WriteWhitespace( string ws ) { writer.WriteWhitespace( ws ); }

		public DBID Context { get { return context; } }
	}
}

using System;
using System.Xml;
using libdb.Diagnostics;
using System.IO;
using libdb.IO;

namespace libdb.DB
{
	internal sealed class XmlContextReader: XmlReader
	{
		private readonly XmlReader reader = null;
		private readonly DBID context = DBID.Empty;

		private XmlContextReader( XmlReader reader, DBID context )
		{
			this.context = context;
			this.reader = reader;
		}

		public static XmlContextReader Create( IFileSystem fileSystem, DBID context )
		{
			if ( context.IsEmpty )
			{
				Log.TraceError( "Cannot create reader for resource with empty file name" );
				return null;
			}

			if ( context.IsInlined )
			{
				Log.TraceError( "Cannot create reader for inlined resource \"{0}", context.Name );
				return null;
			}

      //Log.TraceMessage("XmlContextReader: Attempt to open file \"{0}\"", context.GetFullFileName());
      Stream file = fileSystem.OpenFile(context.GetFullFileName());
			if ( file == null )
			{
        Log.TraceError("XmlContextReader: Cannot open file \"{0}\"", context.GetFullFileName());
				return null;
			}

			XmlReaderSettings settings = new XmlReaderSettings();
			settings.CloseInput = true;
			settings.ConformanceLevel = ConformanceLevel.Document;
			settings.IgnoreComments = true;
			settings.IgnoreWhitespace = true;

			return new XmlContextReader( XmlReader.Create( file, settings ), context );
		}

		public override int AttributeCount { get { return reader.AttributeCount; } }
		public override string BaseURI { get { return reader.BaseURI; } }
		public override void Close() { reader.Close(); }
		public override int Depth { get { return reader.Depth; } }
		public override bool EOF { get { return reader.EOF; } }
		public override string GetAttribute( int i ) { return reader.GetAttribute( i ); }
		public override string GetAttribute( string name, string namespaceURI ) { return reader.GetAttribute( name, namespaceURI ); }
		public override string GetAttribute( string name ) { return reader.GetAttribute( name ); }
		public override bool HasValue { get { return reader.HasValue; } }
		public override bool IsEmptyElement { get { return reader.IsEmptyElement; } }
		public override string LocalName { get { return reader.LocalName; } }
		public override string LookupNamespace( string prefix ) { return reader.LookupNamespace( prefix ); }
		public override bool MoveToAttribute( string name, string ns ) { return reader.MoveToAttribute( name, ns ); }
		public override bool MoveToAttribute( string name ) { return reader.MoveToAttribute( name ); }
		public override bool MoveToElement() { return reader.MoveToElement(); }
		public override bool MoveToFirstAttribute() { return reader.MoveToFirstAttribute(); }
		public override bool MoveToNextAttribute() { return reader.MoveToNextAttribute(); }
		public override XmlNameTable NameTable { get { return reader.NameTable; } }
		public override string NamespaceURI { get { return reader.NamespaceURI; } }
		public override XmlNodeType NodeType { get { return reader.NodeType; } }
		public override string Prefix { get { return reader.Prefix; } }
		public override bool Read() { return reader.Read(); }
		public override bool ReadAttributeValue() { return reader.ReadAttributeValue(); }
		public override ReadState ReadState { get { return reader.ReadState; } }
		public override void ResolveEntity() { reader.ResolveEntity(); }
		public override string Value { get { return reader.Value; } }

		public DBID Context { get { return context; } }
	}
}

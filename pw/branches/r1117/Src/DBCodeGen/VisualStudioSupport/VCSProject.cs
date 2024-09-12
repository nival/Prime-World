using System.Collections.Generic;
using System.IO;
using System.Xml;
using System.Diagnostics;

namespace DBCodeGen.VisualStudioSupport
{
	internal sealed class VCSProject : Project
	{
		private static string defaultNamespafeUri = "http://schemas.microsoft.com/developer/msbuild/2003";

		private List<string> references = new List<string>();

		public VCSProject( string fileName ) : base( fileName )
		{
			SetProjectName( Path.GetFileNameWithoutExtension( fileName ) );

			XmlDocument project = LoadProject();

			XmlNamespaceManager namespaceManager = new XmlNamespaceManager( new NameTable() );
			namespaceManager.AddNamespace( "def", defaultNamespafeUri );

			foreach ( XmlNode includeNode in project.SelectNodes( "/def:Project/def:ItemGroup/def:Compile/@Include", namespaceManager ) )
				RegisterFile( includeNode.Value );

			foreach ( XmlNode refNode in project.SelectNodes( "/def:Project/def:ItemGroup/def:ProjectReference/def:Name", namespaceManager ) )
				references.Add( refNode.InnerText );
		}

		protected override XmlDocument StoreProject()
		{
			XmlDocument result = LoadProject();
			XmlNamespaceManager namespaceManager = new XmlNamespaceManager( new NameTable() );
			namespaceManager.AddNamespace( "def", defaultNamespafeUri );

			XmlNode lastItemGroup = result.SelectSingleNode( "/def:Project/def:ItemGroup[last()]", namespaceManager );
			if ( lastItemGroup == null )
			{
				Trace.TraceError( "\"ItemGroup\" section not found in project \"{0}\"", ProjectName );
				return null;
			}

			XmlNode newItemGroup = result.CreateElement( "ItemGroup", result.DocumentElement.NamespaceURI );
			lastItemGroup.ParentNode.InsertAfter( newItemGroup, lastItemGroup );
			foreach ( string fileName in AddedFiles )
			{
				XmlNode fileNode = result.CreateElement( "Compile", result.DocumentElement.NamespaceURI );
				fileNode.Attributes.Append( result.CreateAttribute( "Include" ) ).Value = fileName;
				newItemGroup.AppendChild( fileNode );
			}

			return result;
		}

		public IEnumerable<string> References { get { return references; } }
	}
}

using System;
using System.Xml;
using FixSln.Utils;

namespace FixSln.SolutionStruct
{
	public sealed class CSProject : Project
	{
		public static Guid CSProjectTypeGuid = new Guid( "FAE04EC0-301F-11D3-BF4B-00C04F79EFBC" );

		public CSProject( string name, Guid guid, string filePath ) : base( name, guid, filePath ) { }

		protected override void ParseXml( XmlElement doc )
		{
			foreach ( XmlElement itemGroup in doc.GetElementsByTagName( "ItemGroup" ) )
			{
				foreach ( XmlNode item in itemGroup.ChildNodes )
				{
					if ( item.NodeType != XmlNodeType.Element )
						continue;

					if ( item.Name == "Compile" || item.Name == "EmbeddedResource" || item.Name == "BaseApplicationManifest" || item.Name == "None" || item.Name == "Content" )
					{
						string filePath = XmlUtils.GetAttribute( item as XmlElement, "Include" );
						AddFile( filePath, System.IO.Path.GetDirectoryName( filePath ) );
					}
				}
			}
		}

		public override Guid TypeGuid { get { return CSProjectTypeGuid; } }
	}
}

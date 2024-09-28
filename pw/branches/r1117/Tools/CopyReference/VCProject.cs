using System.Xml;

namespace CopyReference
{
	internal sealed class VCProject : Project
	{
		public VCProject( string fileName ) : base( fileName )
		{
			XmlDocument project = LoadProject();
			
			XmlNode projectNameNode = project.SelectSingleNode( "/VisualStudioProject/@Name" );
			if ( projectNameNode != null )
				SetProjectName( projectNameNode.Value );

			XmlNodeList filesNodes = project.SelectNodes( "/VisualStudioProject/Files//File/@RelativePath" );
			if ( filesNodes != null )
			{
				foreach ( XmlNode fileNode in filesNodes )
					RegisterFile( fileNode.Value );
			}
		}

		protected override XmlDocument StoreProject()
		{
			XmlDocument result = LoadProject();
			XmlNode filesNode = result.SelectSingleNode( "/VisualStudioProject/Files" );
			if ( filesNode == null )
			{
				return null;
			}

			foreach ( string fileName in AddedFiles )
			{
				XmlNode fileNode = result.CreateElement( "File" );
				fileNode.Attributes.Append( result.CreateAttribute( "RelativePath" ) ).Value = fileName;
				filesNode.AppendChild( fileNode );
			}

			return result;
		}
	}
}

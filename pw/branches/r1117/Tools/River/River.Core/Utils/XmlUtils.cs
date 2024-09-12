using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace River.Core.Utils
{
	public static class XmlUtils
	{
		public static bool ReadValue( XmlReader reader, ref string value )
		{
			if ( reader.IsEmptyElement )
				value = string.Empty;
			else
			{
				reader.ReadStartElement();
				value = reader.ReadContentAsString();
			}

			SkipNode( reader );
			return true;
		}

		public static bool ReadAttribute( XmlReader reader, string attribute, ref int value )
		{
			if ( !reader.MoveToAttribute( attribute ) )
			{
				return false;
			}

			string s = reader.ReadContentAsString();
			SkipNode( reader );

			int result = 0;
			if ( !int.TryParse( s, out result ) )
				return false;

			value = result;				 
			return true;
		}


		public static void SkipNode( XmlReader reader, bool isEmptyElement )
		{
			if ( isEmptyElement )
				reader.Skip();
			else
			{
				if ( reader.NodeType == XmlNodeType.Element || reader.NodeType == XmlNodeType.Attribute )
					reader.ReadStartElement();
				while ( reader.NodeType != XmlNodeType.EndElement && reader.NodeType != XmlNodeType.None )
					reader.Skip();

				if ( reader.NodeType == XmlNodeType.EndElement )
					reader.ReadEndElement();
			}
		}

		public static void SkipNode( XmlReader reader )
		{
			SkipNode( reader, reader.IsEmptyElement );
		}
	}
}

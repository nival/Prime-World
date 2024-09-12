using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace FixSln.Utils
{
	public static class XmlUtils
	{
		public static string GetAttribute( XmlElement element, string attribute )
		{
			if ( element == null )
				return string.Empty;
			XmlAttribute xmlAttribute = element.Attributes[attribute];
			if ( xmlAttribute == null )
				return string.Empty;
			return xmlAttribute.Value;
		}
	}
}

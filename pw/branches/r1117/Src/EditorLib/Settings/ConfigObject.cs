using System;
using System.Xml;
using libdb.DB;

namespace EditorLib.Settings
{
	public interface IConfigObject
	{
		/// <summary>
		/// Serialize current state of configuration object in provided XmlWriter. Do not use ANY XML ATTRIBUTES in root node they will be
		/// removed lately while composing one huge XML
		/// </summary>
		/// <param name="writer">XmlWriter where object to serialize</param>
		/// <param name="file">SimpleConfig object is using this to filter members. Could be null</param>
	 	void Serialize( XmlWriter writer, ConfigFile file );
		bool Deserialize( XmlReader reader );
	}
}

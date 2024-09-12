using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace EditorLib.IO
{
	public interface IConfigFileSystem : libdb.IO.IFileSystem
	{
		bool Configure();

		void Serialize( XmlWriter writer );
		void Deserialize( XmlReader reader );
	}
}

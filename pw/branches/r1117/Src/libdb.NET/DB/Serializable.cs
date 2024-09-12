using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.DB
{
	public interface ISerializable
	{
		void Serialize( out object nestedObject, out object attributes );

		Type GetAttributesType();
		bool DeserializeAttributes( XmlSerializer serializer, object attributes, out Type nestedObjectType );
		bool DeserializeNestedObject( XmlSerializer serializer, object attributes, object nestedObject );
	}
}

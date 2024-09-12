using System;
using System.Collections.Generic;
using libdb.DB;

namespace libdb.DB
{
	/// <summary>
	/// XmlSerializer that supports auto creation and registration of nested types. Also root type intrepriet as strcuture. Ideal for ConfigObject
	/// </summary>
	public class SimpleRegisteringXmlSerializer : XmlSerializer
	{
		private readonly Type serializedType = null;
		private Dictionary<string, Type> knownTypes = new Dictionary<string, Type>();

		public SimpleRegisteringXmlSerializer() : this( null ) { }

		public SimpleRegisteringXmlSerializer( Type type )
		{
			serializedType = type;

      RegisterNestedTypes(type);
		}

		protected override Type TryGetType( string typeName )
		{
			Type result = null;
			if ( !knownTypes.TryGetValue( typeName, out result ) )
				return base.TryGetType( typeName );

			return result;
		}

		public void RegisterNestedTypes( Type type )
		{
			if ( type == null )
				return;

      knownTypes.Add( type.Name, type );
      knownTypes.Add( type.FullName, type );
      foreach ( Type nestedType in type.GetNestedTypes( System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic ) )
      {
        knownTypes.Add( nestedType.Name, nestedType );
        knownTypes.Add( nestedType.FullName, nestedType );
      }
		}
	}
}

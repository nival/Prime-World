using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Xml;
using System.Xml.Serialization;

namespace libdb.DB
{
	public class XmlSerializer
	{
		#region Virtual methods to determinate type's type

		protected enum ObjectTypeType
		{
			None,
			Primitive,
			Struct,
			Class,
			Special,
		}

		protected virtual ObjectTypeType GetObjectTypeType( Type type )
		{
			if ( type == null )
				return ObjectTypeType.None;
			else if ( TypeUtils.IsSubclassOf( type, typeof( ISerializable ) ) || TypeUtils.IsList( type ) || TypeUtils.IsSubclassOf( type, typeof( IDictionary<,> ) ) )
				return ObjectTypeType.Special;
      else if ( type == typeof( bool ) || type == typeof( int ) || type == typeof( long ) || type == typeof( uint ) || type == typeof( float ) ||
				type == typeof( string ) || type == typeof( Guid ) || type.IsEnum || TypeUtils.IsSubclassOf( type, typeof( Type ) ) ||
        type == typeof( DBID ) )
				return ObjectTypeType.Primitive;
			else if ( type.IsValueType )
				return ObjectTypeType.Struct;
			else if ( type.IsClass )
				return ObjectTypeType.Class;

			return ObjectTypeType.None;
		}

		protected virtual DBFieldInfo[] GetFields( Type type, bool inherit )
		{
			return TypeUtils.GetFields( type, inherit );
		}

		#endregion

		#region Virtual methods to convert primitive types to their string representation

    private string GetEscapedTypeName( Type type )
    {
      return ( type.FullName + "..." + type.Assembly.GetName().Name ).Replace( "+", ".." );
    }

    private Type GetTypeFromEscapedName( string typeName )
    {
      if ( typeName == null || typeName == string.Empty )
        return null;

      string unescapedTypeName = typeName.Replace( "...", "," ).Replace( "..", "+" );
      return TryGetType( unescapedTypeName );
    }

		protected virtual void GetPrimitiveTypeValue( object obj, out string value )
		{
			Type objType = obj.GetType();
      if ( objType == typeof( bool ) || objType == typeof( int ) || objType == typeof( long ) || objType == typeof( uint ) || objType == typeof( string ) || objType.IsEnum )
        value = obj.ToString();
      else if ( objType == typeof( float ) )
        value = ( (float)obj ).ToString( NumberFormatInfo.InvariantInfo );
      else if ( objType == typeof( Guid ) )
        value = ( (Guid)obj ).ToString().ToUpper();
      else if ( TypeUtils.IsSubclassOf( objType, typeof( Type ) ) )
        value = GetEscapedTypeName( obj as Type );
      else if ( objType == typeof( DBID ) )
        value = obj.ToString();
      else
        value = string.Empty;
		}

		#endregion

		#region Serialize function and its write helpers

		private void WritePrimitive( object obj, XmlWriter writer )
		{
			string value = string.Empty;
			GetPrimitiveTypeValue( obj, out value );
			writer.WriteValue( value );
		}

		private void WriteSerializable( object obj, XmlWriter writer )
		{
			ISerializable serializable = obj as ISerializable;

			object nestedObject = null;
			object attributes = null;
			serializable.Serialize( out nestedObject, out attributes );

      List<DBFieldInfo> fields = new List<DBFieldInfo>();
      fields.AddRange( GetFields( attributes.GetType(), true ) );
      fields.Sort( ( x, y ) => { return string.Compare( x.Name, y.Name ); } );
			foreach ( DBFieldInfo field in fields )
			{
				if ( GetObjectTypeType( field.FieldType ) != ObjectTypeType.Primitive )
					continue;

				string value = string.Empty;
				GetPrimitiveTypeValue( field.GetValue( attributes ), out value );
				if ( value != string.Empty )
					writer.WriteAttributeString( field.Name, value );
			}

			if ( nestedObject != null )
				Serialize( nestedObject, writer );
		}

		private void WriteList( object obj, XmlWriter writer )
		{
			// IList<> is derived from IEnumerable so we don't expect null here
			IEnumerable list = obj as IEnumerable;
			foreach ( object item in list )
			{
				writer.WriteStartElement( "Item" );
				Serialize( item, writer );
				writer.WriteEndElement();
			}
		}

		private void WriteStruct( object obj, XmlWriter writer )
		{
      List<DBFieldInfo> fields = new List<DBFieldInfo>();
      fields.AddRange( GetFields( obj.GetType(), true ) );
      fields.Sort( ( x, y ) => { return string.Compare( x.Name, y.Name ); } );
      foreach ( DBFieldInfo field in fields )
			{
				if ( !field.CanRead || TypeUtils.HasAttribute<XmlIgnoreAttribute>( field, true ) )
					continue;

				writer.WriteStartElement( field.Name );
        object fieldValue = field.GetValue( obj );
        if ( null != fieldValue && field.GetCustomAttributes<StoreTypeWithFieldAttribute>( true ).Length > 0 )
        {
          writer.WriteAttributeString( "FullType", GetEscapedTypeName( fieldValue.GetType() ) );
        }

				Serialize( fieldValue, writer );
				writer.WriteEndElement();
			}
		}

		private void WriteClass( object obj, XmlWriter writer )
		{
			writer.WriteStartElement( GetEscapedTypeName( obj.GetType() ) );
			WriteStruct( obj, writer );
			writer.WriteEndElement();
		}

		private void WriteDictionary( object obj, XmlWriter writer )
		{
			IDictionary dict = obj as IDictionary;
			foreach ( DictionaryEntry item in dict )
			{
				writer.WriteStartElement( "Item" );
				writer.WriteStartElement( "Key" );
				Serialize( item.Key, writer );
				writer.WriteEndElement();
				Serialize( item.Value, writer );
				writer.WriteEndElement();
			}
		}

		public void Serialize( object obj, XmlWriter writer )
		{
			if ( obj == null )
				return;

			switch ( GetObjectTypeType( obj.GetType() ) )
			{
			case ObjectTypeType.Primitive:
				WritePrimitive( obj, writer );
				break;
			case ObjectTypeType.Struct:
				WriteStruct( obj, writer );
				break;
			case ObjectTypeType.Class:
				WriteClass( obj, writer );
				break;
			case ObjectTypeType.Special:
				if ( TypeUtils.IsSubclassOf( obj.GetType(), typeof( ISerializable ) ) )
					WriteSerializable( obj, writer );
				else if ( TypeUtils.IsSubclassOf( obj.GetType(), typeof( IList<> ) ) )
					WriteList( obj, writer );
				else if ( TypeUtils.IsSubclassOf( obj.GetType(), typeof( IDictionary<,> ) ) )
					WriteDictionary( obj, writer );
				break;
			}
		}

		#endregion

		#region Primitive types parser helpers

		private bool TryParseBool( string value, out object obj )
		{
			bool outObj = false;
			if ( TypeUtils.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private bool TryParseInt( string value, out object obj )
		{
			int outObj = 0;
			if ( int.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

    private bool TryParseLong( string value, out object obj )
    {
      long outObj = 0;
      if ( long.TryParse( value, out outObj ) )
        obj = outObj;
      else
        obj = null;

      return obj != null;
    }

		private bool TryParseUint( string value, out object obj )
		{
			uint outObj = 0;
			if ( uint.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private bool TryParseFloat( string value, out object obj )
		{
			float outObj = 0.0f;
			if ( float.TryParse( value, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private bool TryParseEnum( string value, Type type, out object obj )
		{
			Dictionary<string, int> enumValues = new Dictionary<string, int>();
			foreach ( string name in Enum.GetNames( type ) )
				enumValues.Add( name, (int)Enum.Parse( type, name ) );

			bool isFlag = TypeUtils.HasAttribute<FlagsAttribute>( type, true );
			string[] values = isFlag ? value.Split( ',' ) : new string[1] { value };
			int result = 0;
			foreach ( string strValue in values )
			{
				int intValue = 0;
				if ( !enumValues.TryGetValue( strValue.Trim(), out intValue ) )
				{
					obj = null;
					return false;
				}

				result |= intValue;
			}

			obj = Enum.ToObject( type, result );
			return true;
		}

		private bool TryParseGuid( string value, out object obj )
		{
			if ( string.IsNullOrEmpty( value ) )
			{
				obj = Guid.Empty;
				return true;
			}

			Guid outObj = Guid.Empty;
			if ( TypeUtils.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		#endregion

		#region Virtual methods to convert primitive types from theirs string representation

		protected virtual Type TryGetType( string typeName )
		{
			return Type.GetType( typeName, false, false );
		}

		protected virtual bool TryCreateObject( Type type, out object obj )
		{
			return TypeUtils.TryCreateObject( type, out obj );
		}

		protected virtual bool TryParsePrimitive( string value, Type objType, out object obj )
		{
			if ( objType == typeof( bool ) )
				return TryParseBool( value, out obj );
			else if ( objType == typeof( int ) )
				return TryParseInt( value, out obj );
      else if ( objType == typeof( long ) )
        return TryParseLong( value, out obj );
			else if ( objType == typeof( uint ) )
				return TryParseUint( value, out obj );
			else if ( objType == typeof( float ) )
				return TryParseFloat( value, out obj );
			else if ( objType == typeof( Guid ) )
				return TryParseGuid( value, out obj );
      else if ( objType == typeof( DBID ) )
      {
        obj = DBID.FromString( value );
        return true;
      }
      else if ( objType.IsEnum )
        return TryParseEnum( value, objType, out obj );
      else if ( objType == typeof( string ) )
      {
        obj = value;
        return true;
      }
      else if ( TypeUtils.IsSubclassOf( objType, typeof( Type ) ) )
      {
        obj = GetTypeFromEscapedName( value );
        return obj != null;
      }

			obj = null;
			return false;
		}

		#endregion

		#region Deserialize function and its helpers

		private void SkipNode( XmlReader reader, bool isEmptyElement )
		{
			if ( isEmptyElement )
				reader.Skip();
			else
			{
				if ( reader.NodeType == XmlNodeType.Element )
					reader.ReadStartElement();
				while ( reader.NodeType != XmlNodeType.EndElement )
					reader.Skip();
				reader.ReadEndElement();
			}
		}

		private void SkipNode( XmlReader reader )
		{
			SkipNode( reader, reader.IsEmptyElement );
		}

    private Type TryGetType( string typeName, string fullTypeName )
    {
      Type result = TryGetType( typeName );
      if ( result != null )
        return result;

      if ( string.IsNullOrEmpty( fullTypeName ) )
        return null;

      return TryGetType( fullTypeName );
    }

		private Dictionary<string, DBFieldInfo> GetFields( Type objType )
		{
			DBFieldInfo[] fields = GetFields( objType, true );
			Dictionary<string, DBFieldInfo> cachedFields = new Dictionary<string, DBFieldInfo>();
			foreach ( DBFieldInfo field in fields )
				cachedFields.Add( field.Name, field );
			return cachedFields;
		}

		private object ReadAttributes( XmlReader reader, Type attributesType )
		{
			object attributes = null;
			if ( !TryCreateObject( attributesType, out attributes ) )
				return null;

			Dictionary<string, DBFieldInfo> cachedFields = GetFields( attributes.GetType() );
			if ( reader.MoveToFirstAttribute() )
			{
				do
				{
					DBFieldInfo field = null;
					object fieldValue = null;
					if ( cachedFields.TryGetValue( reader.Name, out field ) && TryParsePrimitive( reader.Value, field.FieldType, out fieldValue ) )
						field.SetValue( attributes, fieldValue );
				} while ( reader.MoveToNextAttribute() );
			}

			return attributes;
		}

		private bool TryDeserializeContent( ref object obj, Type objType, XmlReader reader, bool isEmptyElement )
		{
			switch ( GetObjectTypeType( objType ) )
			{
			case ObjectTypeType.Primitive:
				return TryParsePrimitive( isEmptyElement ? string.Empty : reader.ReadContentAsString(), objType, out obj );
			case ObjectTypeType.Struct:
				return TryDeserializeStruct( obj, reader );
			case ObjectTypeType.Class:
				return TryDeserializeClass( ref obj, reader, isEmptyElement );
			case ObjectTypeType.Special:
				if ( TypeUtils.IsSubclassOf( objType, typeof( IList<> ) ) )
					return TryDeserializeList( ref obj, objType, reader, isEmptyElement );
				else if ( TypeUtils.IsSubclassOf( objType, typeof( IDictionary<,> ) ) )
					return TryDeserializeDictionary( ref obj, objType, reader, isEmptyElement );
				break;
			}

			return false;
		}

		private bool TryDeserializeField( ref object obj, Type objType, XmlReader reader )
		{
			bool isEmptyElement = reader.IsEmptyElement;
			bool result = false;

			if ( TypeUtils.IsSubclassOf( objType, typeof( ISerializable ) ) )
			{
				if ( obj == null && !TryCreateObject( objType, out obj ) )
					result = false;
				else
				{
					ISerializable serializable = obj as ISerializable;
					object attributes = ReadAttributes( reader, serializable.GetAttributesType() );
					if ( !isEmptyElement )
						reader.ReadStartElement();
					result = TryDeserializeSerializable( serializable, attributes, reader, isEmptyElement );
				}
			}
			else
			{
				if ( !isEmptyElement )
					reader.ReadStartElement();
				result = TryDeserializeContent( ref obj, objType, reader, isEmptyElement );
			}

			// skip rest of elements
			SkipNode( reader, isEmptyElement );

			return result;
		}

		private bool TryDeserializeSerializable( ISerializable obj, object attributes, XmlReader reader, bool isEmptyElement )
		{
			if ( obj == null || attributes == null )
				return false;

			Type nestedObjectType = null;
			if ( !obj.DeserializeAttributes( this, attributes, out nestedObjectType ) )
				return false;

			if ( GetObjectTypeType( nestedObjectType ) == ObjectTypeType.None )
				return true;

			object nestedObject = null;
			if ( !TryDeserializeContent( ref nestedObject, nestedObjectType, reader, isEmptyElement ) )
				return false;

			return obj.DeserializeNestedObject( this, attributes, nestedObject );
		}

		private bool TryDeserializeList( ref object list, Type listType, XmlReader reader, bool isEmptyElement )
		{
			if ( list == null )
			{
				TryCreateObject( listType, out list );
				if ( list == null )
					return false;
			}

			Type itemType = TypeUtils.GetTypeFromGeneric( listType );

			System.Reflection.PropertyInfo countProperty = TypeUtils.GetProperty( listType, "Count" );
			System.Reflection.PropertyInfo itemProperty = TypeUtils.GetProperty( listType, "Item" );
			System.Reflection.MethodInfo addMethod = TypeUtils.GetMethod( listType, "Add", new Type[1] { itemType } );
			System.Reflection.MethodInfo removeAtMethod = TypeUtils.GetMethod( listType, "RemoveAt", new Type[1] { typeof( int ) } );
			System.Reflection.MethodInfo clearMethod = TypeUtils.GetMethod( listType, "Clear", Type.EmptyTypes );

			if ( countProperty == null || itemProperty == null || addMethod == null || removeAtMethod == null || clearMethod == null )
				return false;

			int count = (int)countProperty.GetValue( list, null );

			if ( isEmptyElement )
			{
				if ( count > 0 )
					clearMethod.Invoke( list, null );

				return true;
			}

			object[] index = new object[1] { (int)0 };
			while ( reader.IsStartElement() )
			{
				if ( reader.Name != "Item" )
				{
					SkipNode( reader );
					continue;
				}

				object item = null;
				if ( (int)index[0] < count )
					item = itemProperty.GetValue( list, index );

				object itemCopy = item;
				if ( TryDeserializeField( ref item, itemType, reader ) )
				{
					if ( (int)index[0] >= count )
						addMethod.Invoke( list, new object[1] { item } );
					else
						itemProperty.SetValue( list, item, index );
				}

				index[0] = (int)index[0] + 1;
			}

			for ( int i = count - 1; i >= (int)index[0]; --i )
				removeAtMethod.Invoke( list, new object[1] { i } );

			return true;
		}

		private bool TryDeserializeDictionary( ref object dict, Type dictType, XmlReader reader, bool isEmptyElement )
		{
			if ( dict == null )
			{
				TryCreateObject( dictType, out dict );
				if ( dict == null )
					return false;
			}

			Type keyType = TypeUtils.GetTypeFromGeneric( dictType, 0 );
			Type valueType = TypeUtils.GetTypeFromGeneric( dictType, 1 );

			System.Reflection.PropertyInfo countProperty = TypeUtils.GetProperty( dictType, "Count" );
			System.Reflection.MethodInfo addMethod = TypeUtils.GetMethod( dictType, "Add", new Type[2] { keyType, valueType } );
			System.Reflection.MethodInfo containsMethod = TypeUtils.GetMethod( dictType, "Contains", new Type[1] { keyType } );
			System.Reflection.MethodInfo removeMethod = TypeUtils.GetMethod( dictType, "Remove", new Type[1] { keyType } );
			System.Reflection.MethodInfo clearMethod = TypeUtils.GetMethod( dictType, "Clear", Type.EmptyTypes );

			if ( countProperty == null || addMethod == null || containsMethod == null || removeMethod == null || clearMethod == null )
				return false;

			int count = (int)countProperty.GetValue( dict, null );

			if ( isEmptyElement )
			{
				if ( count > 0 )
					clearMethod.Invoke( dict, null );

				return true;
			}

			while ( reader.IsStartElement() )
			{
				if (reader.Name != "Item")
				{
					SkipNode(reader);
					continue;
				}

				reader.ReadStartElement("Item");
				reader.ReadStartElement("Key");

				object itemKey = null;
				TryDeserializeContent(ref itemKey, keyType, reader, reader.IsEmptyElement);
				reader.ReadEndElement();

				object itemValue = null;     
				TryDeserializeContent(ref itemValue, valueType, reader, reader.IsEmptyElement);
				reader.ReadEndElement();

				if (itemKey == null)
					continue;

				if ((bool) containsMethod.Invoke(dict, new object[1] {itemKey}))
					removeMethod.Invoke(dict, new object[1] {itemKey});

				addMethod.Invoke(dict, new object[2] {itemKey, itemValue});
			}

			return true;
		}

		private bool TryDeserializeStruct( object obj, XmlReader reader )
		{
			if ( obj == null )
				return false;

			Dictionary<string, DBFieldInfo> cachedFields = GetFields( obj.GetType() );
			while ( reader.IsStartElement() )
			{
				DBFieldInfo field = null;
				if ( !cachedFields.TryGetValue( reader.Name, out field ) || !field.CanRead || !field.CanWrite )
					SkipNode( reader );
				else
				{
					object value = field.GetValue( obj );
          Type fieldType = field.FieldType;

          if ( field.GetCustomAttributes<StoreTypeWithFieldAttribute>( true ).Length > 0 )
          {
            Type adjustedType = GetTypeFromEscapedName( reader.GetAttribute( "FullType" ) );
            if ( adjustedType != null )
              fieldType = adjustedType;
          }

					if ( TryDeserializeField( ref value, fieldType, reader ) )
						field.SetValue( obj, value );
				}
			}

			return true;
		}

		private bool TryDeserializeClass( ref object obj, XmlReader reader, bool isEmptyElement )
		{
			if ( isEmptyElement )
			{
				obj = null;
				return true;
			}

			if ( !reader.IsStartElement() )
				return false;

			if ( obj == null )
			{
				Type objType = GetTypeFromEscapedName( reader.Name );
				if ( objType == null )
				{
					SkipNode( reader );
					return false;
				}

				TypeUtils.TryCreateObject( objType, out obj );
			}

			return TryDeserializeClass( obj, reader, isEmptyElement );
		}

		private bool TryDeserializeClass( object obj, XmlReader reader, bool isEmptyElement )
		{
			if ( isEmptyElement )
			{
				obj = null;
				return true;
			}

			if ( !reader.IsStartElement() )
				return false;

			if ( obj == null )
			{
				SkipNode( reader );
				return false;
			}

      Type objType = GetTypeFromEscapedName( reader.Name );
			if ( objType != null && !TypeUtils.IsSubclassOf( obj.GetType(), objType ) )
			{
				SkipNode( reader );
				return false;
			}

			if ( reader.IsEmptyElement )
			{
				reader.Skip();
				return true;
			}

			reader.ReadStartElement();
			bool result = TryDeserializeStruct( obj, reader );
			while ( reader.ReadState != ReadState.EndOfFile && reader.NodeType != XmlNodeType.EndElement )
				reader.Skip();
      if ( reader.ReadState != ReadState.EndOfFile )
			  reader.ReadEndElement();

			return result;
		}

		public void Deserialize( object obj, XmlReader reader )
		{
			if ( obj == null )
				return;

			if ( GetObjectTypeType( obj.GetType() ) == ObjectTypeType.Class )
			{
				if ( !reader.IsEmptyElement )
					TryDeserializeClass( obj, reader, reader.IsEmptyElement );
			}
			else
				TryDeserializeContent( ref obj, obj.GetType(), reader, reader.IsEmptyElement );
		}

		public object Deserialize( XmlReader reader )
		{
			object obj = null;
			if ( !TryDeserializeClass( ref obj, reader, reader.IsEmptyElement ) )
				return null;

			return obj;
		}

		#endregion
	}
}

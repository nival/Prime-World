using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Reflection;
using System.Xml;

namespace River.Core.Utils
{
	public class XmlSerializer
	{
		#region Virtual methods for work with types

		protected enum ObjectTypeType
		{
			None,
			Primitive,
			Struct,
			Class,
		}

		protected virtual ObjectTypeType GetObjectTypeType( Type type )
		{
			if ( type == null )
				return ObjectTypeType.None;
			else if ( type.IsPrimitive || type.IsEnum || type == typeof( string ) || type == typeof( Guid ) )
				return ObjectTypeType.Primitive;
			else if ( type.IsValueType )
				return ObjectTypeType.Struct;
			else if ( type.IsClass )
				return ObjectTypeType.Class;

			return ObjectTypeType.None;
		}

		protected virtual Type TryGetType( string typeName )
		{
			return Type.GetType( typeName, false, false );
		}

		protected virtual bool TryCreateObject( Type type, out object obj )
		{
			obj = null;
			ConstructorInfo cotr = type.GetConstructor( Type.EmptyTypes );
			if ( cotr == null )
				return false;

			obj = cotr.Invoke( new Object[0] );
			return obj != null;
		}

		protected virtual IEnumerable<FieldInfo> GetFields( Type type, bool serialize )
		{
			return type.GetFields( System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance );
		}

		protected virtual IEnumerable<PropertyInfo> GetProperties( Type type, bool serialize )
		{
			return type.GetProperties( System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance );
		}

		#endregion

		#region Virtual methods to convert primitive types to their string representation

		protected virtual void GetPrimitiveTypeValue( object obj, out string value )
		{
			Type objType = obj.GetType();
			if ( objType == typeof( Single ) )
				value = ( (Single)obj ).ToString( NumberFormatInfo.InvariantInfo );
			else if ( objType == typeof( Double ) )
				value = ( (Double)obj ).ToString( NumberFormatInfo.InvariantInfo );
			else if ( objType == typeof( Guid ) )
				value = ( (Guid)obj ).ToString().ToUpper();
			else if ( objType.IsPrimitive || objType.IsEnum || objType == typeof( string ) )
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
			IEnumerable<FieldInfo> fields = GetFields( obj.GetType(), true );
			if ( fields != null )
			{
				foreach( FieldInfo field in fields )
				{
					writer.WriteStartElement( field.Name );
					Serialize( field.GetValue( obj ), writer );
					writer.WriteEndElement();
				}
			}

			IEnumerable<PropertyInfo> properties = GetProperties( obj.GetType(), true );
			if ( properties != null )
			{
				foreach ( PropertyInfo property in properties )
				{
					if ( !property.CanRead )
						return;

					writer.WriteStartElement( property.Name );
					Serialize( property.GetValue( obj, null ), writer );
					writer.WriteEndElement();
				}
			}
		}

		private void WriteClass( object obj, XmlWriter writer )
		{
			writer.WriteStartElement( obj.GetType().Name );
			WriteStruct( obj, writer );
			writer.WriteEndElement();
		}

		public void Serialize( object obj, XmlWriter writer )
		{
			if ( obj == null )
				return;

			if ( TypeUtils.IsSubclassOf( obj.GetType(), typeof( IList<> ) ) )
				WriteList( obj, writer );
			else
			{
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
				}
			}
		}

		#endregion

		#region Primitive types parser helpers

		private bool TryParseBoolean( string value, out object obj )
		{
			obj = false;
			if ( string.Compare( value, "1" ) == 0 || string.Compare( value, Boolean.TrueString, StringComparison.InvariantCultureIgnoreCase ) == 0 )
				obj = true;
			else if ( string.Compare( value, "0" ) != 0 && string.Compare( value, Boolean.FalseString, StringComparison.InvariantCultureIgnoreCase ) != 0 )
				obj = false;

			return obj != null;
		}

		private bool TryParseInt32( string value, out object obj )
		{
			Int32 outObj = 0;
			if ( Int32.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private bool TryParseUInt32( string value, out object obj )
		{
			UInt32 outObj = 0;
			if ( UInt32.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private bool TryParseSingle( string value, out object obj )
		{
			Single outObj = 0.0f;
			if ( Single.TryParse( value, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private bool TryParseDouble( string value, out object obj )
		{
			Double outObj = 0.0;
			if ( Double.TryParse( value, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out outObj ) )
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

			Object[] flagsAttributes = type.GetCustomAttributes( typeof( FlagsAttribute ), true );
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

			obj = null;
			char[] guidValue = new char[32];
			int guidIndex = 0;
			foreach ( char c in value )
			{
				if ( c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f' )
				{
					if ( guidIndex >= guidValue.Length )
						return false;
					guidValue[guidIndex++] = c;
				}
				else if ( c == '-' || c == '{' || c == '}' || c == '(' || c == ')' )
					continue;
				else
					return false;
			}

			if ( guidIndex < 32 )
				return false;

			obj = new Guid( new string( guidValue ) );
			return true;
		}

		#endregion

		#region Virtual methods to convert primitive types from theirs string representation

		protected virtual bool TryParsePrimitive( string value, Type objType, out object obj )
		{
			return TypeUtils.TryParsePrimitive( value, objType, out obj );
		}

		#endregion

		#region Deserialize function and its helpers

		private bool TryDeserializeContent( ref object obj, Type objType, XmlReader reader, bool isEmptyElement )
		{
			if ( TypeUtils.IsSubclassOf( objType, typeof( IList<> ) ) )
				return TryDeserializeList( ref obj, objType, reader, isEmptyElement );
			else
			{
				switch ( GetObjectTypeType( objType ) )
				{
				case ObjectTypeType.Primitive:
					return TryParsePrimitive( isEmptyElement ? string.Empty : reader.ReadContentAsString(), objType, out obj );
				case ObjectTypeType.Struct:
					return TryDeserializeStruct( obj, reader );
				case ObjectTypeType.Class:
					return TryDeserializeClass( ref obj, reader, isEmptyElement );
				}
			}

			return false;
		}

		private bool TryDeserializeField( ref object obj, Type objType, XmlReader reader )
		{
			bool isEmptyElement = reader.IsEmptyElement;
			bool result = false;

			if ( !isEmptyElement )
				reader.ReadStartElement();
			result = TryDeserializeContent( ref obj, objType, reader, isEmptyElement );

			// skip rest of elements
			XmlUtils.SkipNode( reader, isEmptyElement );

			return result;
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

			if ( countProperty == null || countProperty == null || addMethod == null || removeAtMethod == null || clearMethod == null )
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
					XmlUtils.SkipNode( reader );
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

		private bool TryDeserializeStruct( object obj, XmlReader reader )
		{
			if ( obj == null )
				return false;

			Dictionary<string, FieldInfo> fields = new Dictionary<string, FieldInfo>();
			foreach ( FieldInfo field in GetFields( obj.GetType(), false ) )
				fields.Add( field.Name, field );

			Dictionary<string, PropertyInfo> properties = new Dictionary<string, PropertyInfo>();
			foreach ( PropertyInfo property in GetProperties( obj.GetType(), false ) )
				properties.Add( property.Name, property );

			while ( reader.IsStartElement() )
			{
				FieldInfo field = null;
				PropertyInfo property = null;
				if ( fields.TryGetValue( reader.Name, out field ) )
				{
					object value = field.GetValue( obj );
					if ( TryDeserializeField( ref value, field.FieldType, reader ) )
						field.SetValue( obj, value );
				}
				else if ( properties.TryGetValue( reader.Name, out property ) && property.CanRead && property.CanWrite )
				{
					object value = property.GetValue( obj, null );
					if ( TryDeserializeField( ref value, property.PropertyType, reader ) )
						property.SetValue( obj, value, null );
				}
				else
					XmlUtils.SkipNode( reader );
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
				Type objType = TryGetType( reader.Name );
				if ( objType == null )
				{
					XmlUtils.SkipNode( reader );
					return false;
				}

				TryCreateObject( objType, out obj );
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
				XmlUtils.SkipNode( reader );
				return false;
			}

			Type objType = TryGetType( reader.Name );
			if ( !TypeUtils.IsSubclassOf( obj.GetType(), objType ) )
			{
				XmlUtils.SkipNode( reader );
				return false;
			}

			if ( reader.IsEmptyElement )
			{
				reader.Skip();
				return true;
			}

			reader.ReadStartElement();
			bool result = TryDeserializeStruct( obj, reader );
			XmlUtils.SkipNode( reader, false );

			return result;
		}

		public void Deserialize( object obj, XmlReader reader )
		{
			if ( obj == null )
				return;

			switch ( GetObjectTypeType( obj.GetType() ) )
			{
			case ObjectTypeType.Class:
				TryDeserializeClass( obj, reader, false );
				break;
			case ObjectTypeType.Struct:
				TryDeserializeStruct( obj, reader );
				break;
			}
		}

		public object Deserialize( XmlReader reader )
		{
			object obj = null;
			if ( !TryDeserializeClass( ref obj, reader, false ) )
				return null;

			return obj;
		}

		#endregion
	}
}

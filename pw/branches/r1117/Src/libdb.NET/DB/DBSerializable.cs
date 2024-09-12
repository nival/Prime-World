using System;
using System.Collections.Generic;
using System.Text;

namespace libdb.DB
{
	public interface IDBSerializable
	{
		void Serialize( FieldPath path, out object nestedObject, out object attributes );

		Type GetAttributesType();
		bool DeserializeAttributes( object attributes, out Type nestedObjectType );
		bool DeserializeNestedObject( object attributes, object nestedObject );
	}

	public abstract class SimpleSerializable<TAttribute> : IDBSerializable where TAttribute : class
	{
		protected abstract TAttribute Serialize( FieldPath path );
		protected abstract bool Deserialize( TAttribute attributes );

		public void Serialize( FieldPath path, out object nestedObject, out object attributes )
		{
			nestedObject = null;
			attributes = Serialize( path );
		}

		public Type GetAttributesType()
		{
			return typeof( TAttribute );
		}

		public bool DeserializeAttributes( object attributes, out Type nestedObjectType )
		{
			nestedObjectType = null;
			if ( attributes == null || attributes.GetType() != typeof( TAttribute ) )
				return false;

			return Deserialize( attributes as TAttribute );
		}

		public bool DeserializeNestedObject( object attributes, object nestedObject )
		{
			return false;
		}
	}

	public abstract class TypedSerializable<T, TAttributes> : IDBSerializable where TAttributes : class
	{
		protected abstract void SerializeTyped( FieldPath path, out T nestedObject, out TAttributes attributes );

		protected abstract bool DeserializeAttributesTyped( TAttributes attributes );
		protected abstract bool DeserializeNestedObjectTyped( TAttributes attributes, T nestedObject );

		public void Serialize( FieldPath path, out object nestedObject, out object attributes )
		{
			T typedNestedObject;
			TAttributes attributesTypes = null;
			SerializeTyped( path, out typedNestedObject, out attributesTypes );
			nestedObject = typedNestedObject;
			attributes = attributesTypes;
		}

		public Type GetAttributesType()
		{
			return typeof( TAttributes );
		}

		public bool DeserializeAttributes( object attributes, out Type nestedObjectType )
		{
			nestedObjectType = null;

			TAttributes attributesTypes = attributes as TAttributes;
			if ( attributesTypes == null )
				return false;

			if ( !DeserializeAttributesTyped( attributesTypes ) )
				return false;

			nestedObjectType = typeof( T );
			return true;
		}

		public bool DeserializeNestedObject( object attributes, object nestedObject )
		{
			TAttributes attributesTypes = attributes as TAttributes;
			if ( attributesTypes == null )
				return false;

			if ( nestedObject == null || !TypeUtils.IsSubclassOf( nestedObject.GetType(), typeof( T ) ) )
				return false;

			T nestedObjectTyped = (T)nestedObject;
			return DeserializeNestedObjectTyped( attributesTypes, nestedObjectTyped );
		}
	}
}

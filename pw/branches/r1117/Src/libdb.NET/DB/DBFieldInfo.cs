using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace libdb.DB
{
	public abstract class DBFieldInfo : ICustomAttributeProvider
	{
		public abstract Type FieldType { get; }
		public abstract Type DeclaringType { get; }
		public abstract string Name { get; }

		public abstract object GetValue( object obj );
		public abstract void SetValue( object obj, object value );

		public abstract bool IsDefined( Type attributeType, bool inherit );
		public abstract object[] GetCustomAttributes( bool inherit );
		public abstract object[] GetCustomAttributes( Type attributeType, bool inherit );
		
		public T[] GetCustomAttributes<T>( bool inherit ) where T : Attribute
		{
			object[] attributes = GetCustomAttributes( typeof( T ), inherit );
			List<T> result = new List<T>();
			foreach ( object attribute in attributes )
			{
				if ( attribute is T )
					result.Add( attribute as T );
			}

			return result.ToArray();
		}

		public abstract bool CanRead { get; }
		public abstract bool CanWrite { get; }

		public static int Compare( DBFieldInfo a, DBFieldInfo b ) {  return string.Compare( a.Name, b.Name ); }
	}

	internal sealed class DBFieldInfoField: DBFieldInfo
	{
		private readonly FieldInfo field = null;

		public DBFieldInfoField( FieldInfo field ) { this.field = field; }

		public override Type FieldType { get { return field.FieldType; } }
		public override Type DeclaringType { get { return field.DeclaringType; } }
		public override string Name { get { return field.Name; } }

		public override object GetValue( object obj ) { return field.GetValue( obj ); }
		public override void SetValue( object obj, object value ) { field.SetValue( obj, value ); }

		public override bool IsDefined( Type attributeType, bool inherit ) { return field.IsDefined( attributeType, inherit ); }
		public override object[] GetCustomAttributes(  bool inherit ) { return field.GetCustomAttributes( inherit ); }
		public override object[] GetCustomAttributes( Type attributeType, bool inherit ) { return field.GetCustomAttributes( attributeType, inherit ); }

		public override bool CanRead { get { return true; } }
		public override bool CanWrite { get { return !field.IsInitOnly; } }
	}

	internal sealed class DBFieldInfoProperty: DBFieldInfo
	{
		private readonly PropertyInfo property = null;

		public DBFieldInfoProperty( PropertyInfo property ) { this.property = property; }

		public override Type FieldType { get { return property.PropertyType; } }
		public override Type DeclaringType { get { return property.DeclaringType; } }
		public override string Name { get { return property.Name; } }

		public override object GetValue( object obj ) { return property.GetValue( obj, null ); }
		public override void SetValue( object obj, object value ) { property.SetValue( obj, value, null ); }

		public override bool IsDefined( Type attributeType, bool inherit ) { return property.IsDefined( attributeType, inherit ); }
		public override object[] GetCustomAttributes( bool inherit ) { return property.GetCustomAttributes( inherit ); }
		public override object[] GetCustomAttributes( Type attributeType, bool inherit ) { return property.GetCustomAttributes( attributeType, inherit ); }

		public override bool CanRead { get { return property.CanRead; } }
		public override bool CanWrite { get { return property.CanWrite; } }
	}
}

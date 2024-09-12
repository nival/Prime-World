using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using libdb.DB;
using System.Globalization;
using libdb.Diagnostics;
using System.Collections;

namespace EditorLib.Templates
{
	public static class TemplatePropertiesConstructor
	{
		public static PropertyDescriptorCollection GetProperties( object obj )
		{
			Type objType = obj.GetType();
			if ( objType.IsPrimitive || objType.IsEnum || objType == typeof( Guid ) || objType == typeof( string ) )
				return null;
			else if ( TypeUtils.IsSubclassOf( objType, typeof( DBPtrBase ) ) )
				return GetProperties( (obj as DBPtrBase).Get<DBResource>() );

			List<PropertyDescriptor> properties = new List<PropertyDescriptor>();

			if ( TypeUtils.IsSubclassOf( objType, typeof( IEnumerable ) ) )
			{
				int index = 0;
				foreach ( object o in (obj as IEnumerable) )
				{
					properties.Add( new TemplateStructPropertyDescriptor( index.ToString(), o ) );
					++index;
				}
			}
			else
			{
				foreach ( DBFieldInfo field in TypeUtils.GetFields( obj.GetType(), true ) )
				{
					if ( field.CanRead && field.CanWrite )
						properties.Add( new TemplateStructPropertyDescriptor( field.Name, field.GetValue( obj ) ) );
				}
			}

			return new PropertyDescriptorCollection( properties.ToArray(), true );
		}
	}

	public sealed class TemplateStructPropertyDescriptor : PropertyDescriptor
	{
		private readonly object value = null;
		
		private TypeConverter converter = null;
		private bool modifiable = false;

		public TemplateStructPropertyDescriptor( string name, object value ) : base( name, null )
		{
			this.value = value;
		}

		private TypeConverter GetConverter()
		{
			if ( converter != null )
				return converter;

			converter = new TemplateStructTypeConverter( value.ToString(), true, TemplatePropertiesConstructor.GetProperties( value ) );

			return converter;
		}

		public override bool CanResetValue( object component ) { return false; }
		public override Type ComponentType { get { return typeof( bool ); } }
		public override object GetValue( object component ) { return value.ToString() + ( modifiable ? " *" : string.Empty ); }
		public override bool IsReadOnly { get { return false; } }
		public override Type PropertyType { get { return typeof( bool ); } }
		public override void ResetValue( object component ) { }
		public override void SetValue( object component, object value ) { modifiable = value.ToString().EndsWith( "*" ); }
		public override bool ShouldSerializeValue( object component ) { return modifiable; }

		public override TypeConverter Converter { get { return GetConverter(); } }
	}

	public sealed class TemplateStructTypeConverter : TypeConverter
	{
		private readonly PropertyDescriptorCollection properties = null;
		private readonly StandardValuesCollection values = null;

		public TemplateStructTypeConverter( string value, bool canBeModifiable, PropertyDescriptorCollection properties )
		{
			if ( canBeModifiable )
				values = new StandardValuesCollection( new string[] { value, value + " *" } );
			else
				values = null;

			this.properties = properties;
		}

		public override bool CanConvertFrom( ITypeDescriptorContext context, Type sourceType )
		{
			if ( sourceType != typeof( string ) )
				return base.CanConvertFrom( context, sourceType );

			return true;
		}

		public override object ConvertFrom( ITypeDescriptorContext context, CultureInfo culture, object value )
		{
			return value;
		}

		public override bool CanConvertTo( ITypeDescriptorContext context, Type destinationType )
		{
			if ( destinationType != typeof( string ) )
				return base.CanConvertTo( context, destinationType );

			return true;
		}

		public override object ConvertTo( ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType )
		{
			if ( destinationType != typeof( string ) )
				return base.ConvertTo( context, culture, value, destinationType );

			return value.ToString();
		}

		public override PropertyDescriptorCollection GetProperties( ITypeDescriptorContext context, object value, Attribute[] attributes ) { return properties; }
		public override bool GetPropertiesSupported( ITypeDescriptorContext context ) { return properties != null; }
		public override bool GetCreateInstanceSupported( ITypeDescriptorContext context ) { return false; }
		public override bool GetStandardValuesSupported( ITypeDescriptorContext context ) { return values != null; }
		public override StandardValuesCollection GetStandardValues( ITypeDescriptorContext context ) { return values; }
		public override bool GetStandardValuesExclusive( ITypeDescriptorContext context ) {	return true; }
	}

	public sealed class TemplateStructTypeDescriptor : ICustomTypeDescriptor
	{
		private readonly object instance = null;
		private readonly PropertyDescriptorCollection properties = null;

		public TemplateStructTypeDescriptor( object instance )
		{
			this.instance = instance;
			properties = TemplatePropertiesConstructor.GetProperties( instance );
		}

		public AttributeCollection GetAttributes() { return new AttributeCollection(); }
		public string GetClassName() { return instance.GetType().ToString(); }
		public string GetComponentName() { return TypeDescriptor.GetComponentName( instance, true ); }
		public TypeConverter GetConverter() { return TypeDescriptor.GetConverter( instance.GetType() ); }
		public EventDescriptor GetDefaultEvent() { return null; }
		public PropertyDescriptor GetDefaultProperty() { return null; }
		public object GetEditor( Type editorBaseType ) { return TypeDescriptor.GetEditor( this, editorBaseType, true ); }
		public EventDescriptorCollection GetEvents( Attribute[] attributes ) { return new EventDescriptorCollection( new EventDescriptor[0], true ); }
		public EventDescriptorCollection GetEvents() { return GetEvents( null ); }
		public PropertyDescriptorCollection GetProperties( Attribute[] attributes ) { return properties; }
		public PropertyDescriptorCollection GetProperties() { return properties; }
		public object GetPropertyOwner( PropertyDescriptor pd ) { return instance; }
	}
}
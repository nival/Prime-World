using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using libdb.DB;
using System.Globalization;
using libdb.Diagnostics;
using System.Collections;
using EditorLib.IO;
using DBTypes;
using EditorLib.PropertiesEditor;
using EditorLib.Menu;

namespace EditorPlugins.Templates
{
	public static class TemplateUtils
	{
		public static string FromatValue( string value, TemplateModifiable modifiable )
		{
			switch ( modifiable )
			{
			case TemplateModifiable.None:
				return value;
			case TemplateModifiable.Modifiable:
				return "Modifiable (" + value + ")";
			case TemplateModifiable.NonNull:
				return "NonNull (" + value + ")";
			case TemplateModifiable.NonBrowse:
				return "NonBrowse (" + value + ")";
			}

			return string.Empty;
		}

		public static TemplateModifiable GetModifiable( string formattedValue, string value )
		{
			if ( formattedValue == FromatValue( value, TemplateModifiable.Modifiable ) )
				return TemplateModifiable.Modifiable;
			else if ( formattedValue == FromatValue( value, TemplateModifiable.NonNull ) )
				return TemplateModifiable.NonNull;
			else if ( formattedValue == FromatValue( value, TemplateModifiable.NonBrowse ) )
				return TemplateModifiable.NonBrowse;
			else
				return TemplateModifiable.None;
		}

		public static bool IsSimpleStruct( Type type, int depth )
		{
			if ( depth < 0 )
				return false;
			if ( type.IsPrimitive || type.IsEnum || type == typeof( Guid ) || type == typeof( string ) )
				return true;
			if ( TypeUtils.IsSubclassOf( type, typeof( DBPtrBase ) ) || TypeUtils.IsSubclassOf( type, typeof( IEnumerable ) ) )
				return false;

			foreach ( DBFieldInfo field in TypeUtils.GetFields( type, true ) )
			{
				if ( !IsSimpleStruct( field.FieldType, depth - 1 ) )
					return false;
			}

			return true;
		}

		public static PropertyDescriptorCollection GetProperties( object obj, string fieldName )
		{
			Type objType = obj.GetType();
			if ( objType.IsPrimitive || objType.IsEnum || objType == typeof( Guid ) || objType == typeof( string ) )
				return null;
			else if ( TypeUtils.IsSubclassOf( objType, typeof( DBPtrBase ) ) )
			{
				DBPtrBase ptr = obj as DBPtrBase;
				if ( ptr == null || DBID.IsNullOrEmpty( ptr.DBId ) || !ptr.DBId.IsInlined )
					return new PropertyDescriptorCollection( new PropertyDescriptor[0] );

				return GetProperties( (obj as DBPtrBase).Get<DBResource>(), fieldName );
			}

			List<PropertyDescriptor> properties = new List<PropertyDescriptor>();

			if ( TypeUtils.IsSubclassOf( objType, typeof( IEnumerable ) ) )
			{
				int index = 0;
				foreach ( object o in (obj as IEnumerable) )
				{
					properties.Add( new TemplatePropertyDescriptor( index.ToString(), o, false, fieldName + "[" + index.ToString() + "]" ) );
					++index;
				}
			}
			else
			{
				string fixedFieldName = string.IsNullOrEmpty( fieldName ) ? string.Empty : fieldName + ".";
				foreach ( DBFieldInfo field in TypeUtils.GetFields( obj.GetType(), true ) )
				{
					if ( field.CanRead && field.CanWrite )
						properties.Add( new TemplatePropertyDescriptor( field.Name, field.GetValue( obj ), TypeUtils.HasAttribute<SrcFileAttribute>( field, false ), fixedFieldName + field.Name ) );
				}
			}

			return new PropertyDescriptorCollection( properties.ToArray(), true );
		}

		public static void UpdateTemplatesMenu( EditorMenu menu )
		{
			ObjectsFolder folder = ObjectsRootFolder.Root.GetFolder( "Templates" );
			if ( folder == null || folder.Items == null )
				return;

			menu.ClearMenuGroup( NewTemplateMenuItem.NewObjectFromTemplateMenuGroupGuid );

			foreach ( DBID item in folder.Items )
			{
				DBPtr<TemplateDefinition> template = DataBase.Get<TemplateDefinition>( item );
				if ( template == null || template.Get() == null )
					continue;

				menu.RegisterMenuCommand( NewTemplateMenuItem.NewObjectFromTemplateMenuGroupGuid, 0, new NewObjectFromTemplateMenuItem( template.Get().name, template.DBId ), System.Windows.Forms.Keys.None );
			}
		}
	}

	public sealed class TemplatePropertyDescriptor : PropertyDescriptor
	{
		private readonly object value = null;
		private readonly string stringValue = null;
		private readonly string fieldName = string.Empty;
		
		private TypeConverter converter = null;
		private TemplateModifiable modifiable = TemplateModifiable.None;

		public TemplatePropertyDescriptor( string name, object value, bool srcFile, string fieldName ) : base( name, null )
		{
			this.value = value;
			this.fieldName = fieldName;

			Type valueType = value.GetType();
			if ( valueType.IsPrimitive || valueType.IsEnum || valueType == typeof( Guid ) || valueType == typeof( string ) )
				stringValue = value.ToString();
			else if ( TypeUtils.IsSubclassOf( valueType, typeof( DBPtrBase ) ) )
			{
				DBPtrBase ptr = value as DBPtrBase;
				if ( ptr == null || DBID.IsNullOrEmpty( ptr.DBId ) )
					stringValue = DBID.Empty.Name;
				else if ( ptr.DBId.IsInlined )
					stringValue = "{inlined}";
				else
					stringValue = ptr.DBId.Name;
			}
			else if ( TypeUtils.IsSubclassOf( valueType, typeof( IEnumerable ) ) )
			{
				int count = 0;
				foreach ( object o in value as IEnumerable )
					++count;
				stringValue = "{count = " + count.ToString() + "}";
			}
			else if ( srcFile )
				stringValue = "{" + valueType.Name + "}: " + value.ToString();
			else
				stringValue = "{" + valueType.Name + "}";
		}

		private TypeConverter GetConverter()
		{
			if ( converter != null )
				return converter;

			converter = new TemplateTypeConverter( stringValue, value.GetType(), TemplateUtils.GetProperties( value, fieldName ) );

			return converter;
		}

		public override bool CanResetValue( object component ) { return false; }
		public override Type ComponentType { get { return typeof( bool ); } }
		public override object GetValue( object component ) { return TemplateUtils.FromatValue( stringValue, modifiable ); }
		public override bool IsReadOnly { get { return false; } }
		public override Type PropertyType { get { return typeof( bool ); } }
		public override void ResetValue( object component ) { }
		public override void SetValue( object component, object value ) { modifiable = TemplateUtils.GetModifiable( value.ToString(), stringValue ); }
		public override bool ShouldSerializeValue( object component ) { return modifiable != TemplateModifiable.None; }

		public override TypeConverter Converter { get { return GetConverter(); } }

		public string FieldName { get { return fieldName; } }
		public TemplateModifiable Modifiable { get { return modifiable; } }
	}

	public sealed class TemplateTypeConverter : TypeConverter
	{
		private readonly PropertyDescriptorCollection properties = null;
		private readonly StandardValuesCollection values = null;

		public TemplateTypeConverter( string value, Type valueType, PropertyDescriptorCollection properties )
		{
			if ( TemplateUtils.IsSimpleStruct( valueType, 1 ) )
				values = new StandardValuesCollection( new string[] { TemplateUtils.FromatValue( value, TemplateModifiable.None ), TemplateUtils.FromatValue( value, TemplateModifiable.Modifiable ) } );
			else if ( TypeUtils.IsSubclassOf( valueType, typeof( DBPtrBase ) ) )

				values = new StandardValuesCollection( new string[] { TemplateUtils.FromatValue( value, TemplateModifiable.None ), TemplateUtils.FromatValue( value, TemplateModifiable.Modifiable ), TemplateUtils.FromatValue( value, TemplateModifiable.NonNull ), TemplateUtils.FromatValue( value, TemplateModifiable.NonBrowse ) } );
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
		public override bool GetPropertiesSupported( ITypeDescriptorContext context ) { return properties != null && properties.Count > 0; }
		public override bool GetCreateInstanceSupported( ITypeDescriptorContext context ) { return false; }
		public override bool GetStandardValuesSupported( ITypeDescriptorContext context ) { return values != null; }
		public override StandardValuesCollection GetStandardValues( ITypeDescriptorContext context ) { return values; }
		public override bool GetStandardValuesExclusive( ITypeDescriptorContext context ) {	return true; }
	}

	public sealed class TemplateTypeDescriptor : ICustomTypeDescriptor
	{
		private readonly object instance = null;
		private readonly PropertyDescriptorCollection properties = null;

		public TemplateTypeDescriptor( object instance )
		{
			this.instance = instance;
			properties = TemplateUtils.GetProperties( instance, string.Empty );
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
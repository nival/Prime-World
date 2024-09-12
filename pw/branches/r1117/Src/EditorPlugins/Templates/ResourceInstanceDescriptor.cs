using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using libdb.DB;
using EditorLib;
using EditorLib.PropertiesEditor;
using libdb.IO;
using System.Reflection;
using libdb;

namespace EditorPlugins.Templates
{
	public sealed class ModifiablePropertyDescription
	{
		public readonly object instance = null;
		public readonly DBFieldInfo field = null;

		public ModifiablePropertyDescription( object instance, DBFieldInfo field ) { this.instance = instance; this.field = field; }
	}

	public sealed class ResourceInstanceDescriptor : PropertyDescriptor
	{
		private readonly List<ModifiablePropertyDescription> properties = new List<ModifiablePropertyDescription>();
		//private readonly object instance;
		//private readonly DBFieldInfo member;
		private readonly IEditorWinApplication application;
		private readonly TypeConverter converter;
		private readonly SrcFileListDescriptionProvider provider;

		public ResourceInstanceDescriptor( string name, IEnumerable<ModifiablePropertyDescription> properties, IEditorWinApplication application )
			: base( name, new Attribute[0]{} )
		{
			//this.instance = instance;
			//this.member = member;
			this.properties.AddRange( properties ); 
			this.application = application;
			this.converter = CreateConverter();
			this.provider = CreateProvider();
		}

		~ResourceInstanceDescriptor()
		{
			if ( !ReferenceEquals( provider, null ) )
			{
				TypeDescriptor.RemoveProvider( provider, properties[0].field.GetValue( properties[0].instance ) );
			}
		}

		public override bool IsReadOnly
		{
			get { return !properties[0].field.CanWrite || properties[0].field.GetCustomAttributes( typeof( ReadOnlyAttribute ), true ).Length > 0; }
		}

		public override object GetEditor( Type editorBaseType )
		{
			DBAttribute[] attrs = properties[0].field.GetCustomAttributes<DBAttribute>( false );

			object editor = application.Application.Extensions.CreatePropertyEditor( properties[0].field.FieldType, attrs, application );
			if ( editor != null )
				return editor;
			if ( properties[0].field.FieldType.IsSubclassOf( typeof( DBPtrBase ) ) )
				return new DBPtrEditor();
			return TypeDescriptor.GetEditor( this, editorBaseType, true );
		}

		public override bool CanResetValue( object component ) { return false; }
		public override Type ComponentType { get { return properties[0].field.DeclaringType; } }

		public override object GetValue( object component )
		{
			object value = properties[0].field.GetValue( properties[0].instance );
			DBPtrBase ptrBase = value as DBPtrBase;
			if ( ptrBase != null )
				value = ptrBase.Get<DBResource>();
			return value;
		}
		public override bool IsBrowsable { get { return true; } }
    public override Type PropertyType { get { return ( properties.Count > 0 ) ? properties[0].field.FieldType : null; } }

		public override void ResetValue( object component ) { }

		private void SetValue( object value )
		{
			foreach ( ModifiablePropertyDescription property in properties )
				property.field.SetValue( property.instance, value );
		}

		public override void SetValue( object component, object value )
		{
			if ( value == null )
				return;

			Type fieldType = properties[0].field.FieldType;

			if ( value is BrowseQueryObject )
			{
				string fileName = (value as BrowseQueryObject).PerformBrowsing() as string;
				if ( !string.IsNullOrEmpty( fileName ) )
				{
					SrcFile srcFile = properties[0].field.GetValue( properties[0].instance ) as SrcFile;
					if ( srcFile == null )
						srcFile = new SrcFile();
					srcFile.SetFileName( fileName );
					SetValue( srcFile );
				}
			}
			else if ( TypeUtils.IsSubclassOf( fieldType, typeof( DBPtr<> ) ) && TypeUtils.IsSubclassOf( value.GetType(), typeof( DBPtr<> ) ) )
			{
				ConstructorInfo constructor = fieldType.GetConstructor( new Type[2] { typeof( DBID ), TypeUtils.GetTypeFromPtr( fieldType ) } );
				if ( constructor != null )
				{
					object obj = constructor.Invoke( new object[2] { (value as DBPtrBase).DBId, null } );
					SetValue( obj );
				}
			}
			else
				SetValue( value );
		}

		public override bool ShouldSerializeValue( object component )
		{
			//CRAP{
			return false;
			//CRAP} // uncomment follow text when SrcFile will be deserialized correctly

			//if ( member.FieldType != typeof( SrcFile ) )
			//  return false;

			//SrcFile srcFile = member.GetValue( component ) as SrcFile;
			//if ( srcFile == null )
			//  return false;

			//return application.Application.SourceFileSystem.IsFileModified( srcFile );
		}

		public override TypeConverter Converter
		{
			get { return converter; }
		}

		private TypeConverter CreateConverter()
		{
			if ( TypeUtils.IsSubclassOf( PropertyType, typeof( DBPtrBase ) ) )
				return new DBPtrConvertor();
			else if ( TypeUtils.IsList( PropertyType ) )
				return new ListConvertor();
			else if ( PropertyType == typeof( TextRef ) )
				return new TextRefConvertor();
			else if ( TypeUtils.IsSimpleType( PropertyType ) )
				return base.Converter;
			else if ( PropertyType == typeof( SrcFile ) && TypeUtils.HasAttribute<SrcFileAttribute>( properties[0].field, true ) )
				return new SrcFilePropertyTypeConverter( properties[0].instance, TypeUtils.GetAttribute<SrcFileAttribute>( properties[0].field, true ), application.Application.SourceFileSystem );
			else
				return new ExpandableObjectConverter();
		}

		private SrcFileListDescriptionProvider CreateProvider()
		{
			if ( TypeUtils.IsSubclassOf( PropertyType, typeof( IList<string> ) ) &&
				properties[0].field.GetCustomAttributes( typeof( SrcFileAttribute ), true ).Length > 0 )
			{
				var provider = new SrcFileListDescriptionProvider( application.Application, properties[0].instance, properties[0].field );
				TypeDescriptor.AddProvider( provider, properties[0].field.GetValue( properties[0].instance ) );
				return provider;
			}
			else
			{
				GC.SuppressFinalize( this );
				return null;
			}
		}

	}
}

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using libdb.DB;

namespace EditorLib.PropertiesEditor
{
	internal sealed class SrcFileListDescriptor : ICustomTypeDescriptor
	{
		private readonly object instance;
		private readonly DBFieldInfo member;
		private readonly IEditorCommonApplication application;
		private readonly IList<string> list;

		public SrcFileListDescriptor( IEditorCommonApplication _application, object _instance, DBFieldInfo _member )
		{
			instance = _instance;
			member = _member;
			application = _application;
			list = (IList<string>) _member.GetValue( _instance );
		}

		#region ICustomTypeDescriptor Members

		public AttributeCollection GetAttributes() { return new AttributeCollection(); }
		public string GetClassName() { return typeof( IList<string> ).ToString(); }
		public string GetComponentName() { return TypeDescriptor.GetComponentName( list, true ); }
		public TypeConverter GetConverter() { return new ExpandableObjectConverter(); }
		public EventDescriptor GetDefaultEvent() { return null; }
		public PropertyDescriptor GetDefaultProperty() { return null; }
		public object GetEditor( Type editorBaseType ) { return TypeDescriptor.GetEditor( this, editorBaseType, true ); }

		public EventDescriptorCollection GetEvents( Attribute[] attributes )
		{
			return new EventDescriptorCollection( new EventDescriptor[0], true );
		}

		public EventDescriptorCollection GetEvents()
		{
			return new EventDescriptorCollection( new EventDescriptor[0], true );
		}

		public PropertyDescriptorCollection GetProperties( Attribute[] attributes )
		{
			var items = new List<SrcFileListMemberDescriptor>();
			for ( int i = 0; i < list.Count; ++i )
			{
				items.Add( new SrcFileListMemberDescriptor(
					i,
					instance,
					(SrcFileAttribute)member.GetCustomAttributes( typeof( SrcFileAttribute ), false )[0],
					application.SourceFileSystem
					) );
			}
			return new PropertyDescriptorCollection( items.ToArray() );
		}

		public PropertyDescriptorCollection GetProperties() { return GetProperties( null ); }
		public object GetPropertyOwner( PropertyDescriptor pd ) { return list; }

		#endregion
	}
}

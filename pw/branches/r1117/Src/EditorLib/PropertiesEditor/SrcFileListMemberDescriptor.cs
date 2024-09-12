using System;
using System.Collections.Generic;
using System.ComponentModel;
using EditorLib.IO;
using libdb.DB;

namespace EditorLib.PropertiesEditor
{
	internal sealed class SrcFileListMemberDescriptor : PropertyDescriptor
	{
		private readonly int index;
		private readonly object instance;
		private readonly SrcFileAttribute attribute;
		private readonly SourceFileSystem sourceFileSystem;

		public SrcFileListMemberDescriptor(
			int _index,
			object _instance,
			SrcFileAttribute _attribute,
			SourceFileSystem _sourceFileSystem
			)
			: base( _index.ToString(), null )
		{
			index = _index;
			instance = _instance;
			attribute = _attribute;
			sourceFileSystem = _sourceFileSystem;
		}

		public override bool CanResetValue( object component ) { return false; }

		public override Type ComponentType { get { return typeof( IList<string> ); } }

		public override object GetValue( object component )
		{
			var list = component as IList<string>;
			if ( !ReferenceEquals( list, null ) && index < list.Count )
			{
				return list[index];
			}
			else
			{
				return null;
			}
		}

		public override bool IsReadOnly { get { return Attributes.Matches( ReadOnlyAttribute.Yes ); } }
		public override bool IsBrowsable { get { return false; } }
		public override Type PropertyType { get { return typeof( string ); } }
		public override void ResetValue( object component ) { }
		
		public override void SetValue( object component, object value )
		{
			var list = component as IList<string>;
			if ( !ReferenceEquals( list, null ) && index < list.Count )
			{
				if ( value is BrowseQueryObject )
				{
					var newValue = ((BrowseQueryObject)value).PerformBrowsing();
					if ( !ReferenceEquals( newValue, null ) )
					{
						list[index] = newValue.ToString();
					}
				}
				else
				{
					list[index] = value.ToString();
				}
			}
		}

		public override bool ShouldSerializeValue( object component ) { return false; }

		public override TypeConverter Converter
		{
			get
			{
				return new SrcFilePropertyTypeConverter( instance, attribute, sourceFileSystem );
			}
		}

		public int Index { get { return index; } }
	}
}

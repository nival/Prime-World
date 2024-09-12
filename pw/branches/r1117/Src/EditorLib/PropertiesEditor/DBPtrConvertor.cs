using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Globalization;
namespace EditorLib.PropertiesEditor
{
	public class DBPtrConvertor : ExpandableObjectConverter
	{
		public override bool CanConvertTo( ITypeDescriptorContext _context, Type _destinationType )
		{
			if ( _context.PropertyDescriptor.PropertyType.IsSubclassOf( typeof( libdb.DB.DBPtrBase ) ) && _destinationType == typeof( String ) )
				return true;
			return base.CanConvertTo( _context, _destinationType );
		}

		public override bool CanConvertFrom( ITypeDescriptorContext _context, Type _sourceType )
		{
			if ( _context.PropertyDescriptor.PropertyType.IsSubclassOf( typeof( libdb.DB.DBPtrBase ) ) && _sourceType == typeof( String ) )
				return true;
			bool rez = base.CanConvertFrom( _context, _sourceType );
			return rez;
		}

		public override object ConvertFrom( ITypeDescriptorContext _context, CultureInfo _culture, object _value )
		{
			object rez = null;

			if ( _context.PropertyDescriptor.PropertyType.IsSubclassOf( typeof( libdb.DB.DBPtrBase ) ) && _value.GetType() == typeof( String ) )
			{
				rez = libdb.DB.DataBase.Get<libdb.DB.DBResource>( libdb.DB.DBID.FromString( _value.ToString() ) );
				try
				{
					( rez as libdb.DB.DBPtrBase ).Get<libdb.DB.DBResource>();
				}
				catch
				{
					return null;
				}
				return rez;
			}
			rez = base.ConvertFrom( _context, _culture, _value );
			return rez;
		}

		public override bool IsValid( ITypeDescriptorContext context, object value )
		{
			return true;
		}

		public override object ConvertTo( ITypeDescriptorContext _context, CultureInfo _culture, object _value, Type _destinationType )
		{
			if ( _context.PropertyDescriptor.PropertyType.IsSubclassOf( typeof( libdb.DB.DBPtrBase ) ) && _destinationType == typeof( String ) )
				return _value != null ? ( _value as libdb.DB.DBResource ).DBId.Name.ToString() : String.Empty;
			object rez = base.ConvertTo( _context, _culture, _value, _destinationType );
			return rez;
		}
	}
}

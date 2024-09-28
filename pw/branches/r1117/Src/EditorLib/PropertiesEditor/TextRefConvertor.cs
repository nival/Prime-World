using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Globalization;
using libdb.DB;

namespace EditorLib.PropertiesEditor
{
	public class TextRefConvertor : ExpandableObjectConverter
	{
		public override bool CanConvertTo( ITypeDescriptorContext context, Type destType )
		{
			if ( context.PropertyDescriptor.PropertyType == typeof( TextRef ) && destType == typeof( String ) )
				return true;
			return base.CanConvertTo( context, destType );
		}

		public override bool CanConvertFrom( ITypeDescriptorContext context, Type srcType )
		{
			if ( context.PropertyDescriptor.PropertyType == typeof( TextRef ) && srcType == typeof( String ) )
				return true;
			return base.CanConvertFrom( context, srcType );
		}

		public override object ConvertFrom( ITypeDescriptorContext context, CultureInfo culture, object value )
		{
			if ( context.PropertyDescriptor.PropertyType == typeof( TextRef ) && value.GetType() == typeof( String ) )
			{
				TextRef res = context.PropertyDescriptor.GetValue( context.Instance ) as TextRef;
				res.FromString( value as String );
				return res;
			}
			return base.ConvertFrom( context, culture, value );
		}

		public override object ConvertTo( ITypeDescriptorContext context, CultureInfo culture, object value, Type destType )
		{
			if ( context.PropertyDescriptor.PropertyType == typeof( TextRef ) && destType == typeof( String ) )
				return ( value as TextRef ).ToString();
			return base.ConvertTo( context, culture, value, destType );
		}

		public override bool IsValid( ITypeDescriptorContext context, object value )
		{
			return true;
		}
	}
}

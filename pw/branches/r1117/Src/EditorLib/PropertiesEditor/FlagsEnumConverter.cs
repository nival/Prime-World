using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Globalization;

namespace EditorLib.PropertiesEditor
{
	public sealed class FlagsEnumConverter : TypeConverter
	{
		private readonly Type enumType = null;

		public FlagsEnumConverter( Type enumType )
		{
			this.enumType = enumType;
		}

		public override bool CanConvertFrom( ITypeDescriptorContext context, Type sourceType )
		{
			if ( sourceType == typeof( string ) )
				return true;

			return base.CanConvertFrom( context, sourceType );
		}

		public override object ConvertFrom( ITypeDescriptorContext context, CultureInfo culture, object value )
		{
			if ( value != null && value.GetType() == typeof( string ) )
				return Enum.Parse( enumType, value as string );

			return base.ConvertFrom( context, culture, value );
		}

		public override bool CanConvertTo( ITypeDescriptorContext context, Type destinationType )
		{
			if ( destinationType == typeof( string ) )
				return true;

			return base.CanConvertTo( context, destinationType );
		}

		public override object ConvertTo( ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType )
		{
			if ( destinationType == typeof( string ) )
				return Enum.Format( enumType, value, "G" );

			return base.ConvertTo( context, culture, value, destinationType );
		}
	}
}

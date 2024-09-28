using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using EditorLib.FieldProcessor;
using System.Globalization;
using libdb;
using libdb.DB;
using libdb.UndoRedo;

namespace EditorLib.FieldProcessor
{
  internal class FullTypeConverter : TypeConverter
  {
    private readonly FullTypeDescriptor descriptor = null;
    private readonly TypeConverter defaultConverter = null;

    public FullTypeConverter( FullTypeDescriptor descriptor )
    {
      this.descriptor = descriptor;
      this.defaultConverter = TypeDescriptor.GetConverter( descriptor.Type );
    }

    # region TypeConvertor overriding

    public override bool CanConvertFrom( ITypeDescriptorContext context, Type sourceType )
    {
      if ( descriptor.StringConverter != null && sourceType == typeof( string ) )
        return true;

      if ( descriptor.StandardValuesProvider != null &&
        descriptor.StandardValuesProvider.HasStandardValuesConvertor( context ) &&
        descriptor.StandardValuesProvider.GetStandardValuesType( context ) == sourceType )
      {
        return true;
      }

      return defaultConverter.CanConvertFrom( context, sourceType );
    }

    public override bool CanConvertTo( ITypeDescriptorContext context, Type destinationType )
    {
      if ( destinationType == typeof( string ) && descriptor.StringConverter != null )
        return true;
      else
        return defaultConverter.CanConvertTo( context, destinationType );
    }

    public override object ConvertFrom( ITypeDescriptorContext context, CultureInfo culture, object value )
    {
      if ( descriptor.StringConverter != null && typeof( string ) == value.GetType() )
      {
        object result;
        using( UndoRedoTransaction trans = new UndoRedoTransaction( "FullTypeConverter: " + value ) )
        {
          result = descriptor.StringConverter.ConvertFromString( context, culture, value.ToString() );
          trans.Commit();
        }
        return result;
      }

      if ( descriptor.StandardValuesProvider != null &&
        descriptor.StandardValuesProvider.HasStandardValuesConvertor( context ) &&
        descriptor.StandardValuesProvider.GetStandardValuesType( context ) == value.GetType() )
      {
        return descriptor.StandardValuesProvider.ConvertFromStandardValue( context, value );
      }

      return defaultConverter.ConvertFrom( context, culture, value );
    }

    public override object ConvertTo( ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType )
    {
      if ( typeof( string ) == destinationType && descriptor.StringConverter != null )
        return descriptor.StringConverter.ConvertToString( context, culture, value );
      else
        return defaultConverter.ConvertTo( context, culture, value, destinationType );
    }

    public override bool GetPropertiesSupported( ITypeDescriptorContext context )
    {
      return descriptor.HasProperties( context );
    }

    public override PropertyDescriptorCollection GetProperties( ITypeDescriptorContext context, object value, Attribute[] attributes )
    {
      return descriptor.GetProperties( context, value, attributes );
    }

    public override bool GetStandardValuesSupported( ITypeDescriptorContext context )
    {
      if ( TypeUtils.IsList( descriptor.Type ) )
        return false;
      if ( null != descriptor.StandardValuesProvider )
        return true;
      else
        return defaultConverter.GetStandardValuesSupported( context );
    }

    public override bool GetStandardValuesExclusive( ITypeDescriptorContext context )
    {
      if ( null != descriptor.StandardValuesProvider )
        return descriptor.StandardValuesProvider.IsStandardValuesExclusive( context );
      else
        return defaultConverter.GetStandardValuesExclusive( context );
    }

    public override StandardValuesCollection GetStandardValues( ITypeDescriptorContext context )
    {
      if ( null != descriptor.StandardValuesProvider )
        return descriptor.StandardValuesProvider.GetStandardValues( context );
      else
        return defaultConverter.GetStandardValues( context );
    }

    # endregion
  }
}

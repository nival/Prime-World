using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using libdb.DB;

namespace EditorLib.PropertiesEditor
{
  public sealed class ListConvertor : ExpandableObjectConverter
  {
    public override bool CanConvertTo( ITypeDescriptorContext _context, Type _destinationType )
    {
      if ( ConvertibleType( _context, _destinationType ) )
      {
        return true;
      }
      else
      {
        return base.CanConvertTo( _context, _destinationType );
      }
    }

    public override bool IsValid( ITypeDescriptorContext context, object value )
    {
      return true;
    }

    public override object ConvertTo( ITypeDescriptorContext _context, CultureInfo _culture, object _value, Type _destinationType )
    {
      if ( ConvertibleType( _context, _destinationType ) )
      {
        if ( _value != null )
        {
          var type = TypeUtils.GetTypeFromList( _value.GetType() );
          return ReferenceEquals( type, null ) ? string.Empty : "List of " + type.ToString();
        }
      }
      return base.ConvertTo( _context, _culture, _value, _destinationType );
    }

    private static bool ConvertibleType( ITypeDescriptorContext _context, Type _destinationType )
    {
      return
        TypeUtils.IsSubclassOf( _context.PropertyDescriptor.PropertyType, typeof( libdb.IRichList ) ) &&
        _destinationType == typeof( String );
    }
  }
}

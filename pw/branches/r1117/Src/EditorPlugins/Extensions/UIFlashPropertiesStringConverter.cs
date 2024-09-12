using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Text;
using DBTypes;
using EditorLib;
using EditorLib.FieldProcessor;
using libdb;
using libdb.Diagnostics;

namespace EditorPlugins.Extensions
{
  public sealed class UIFlashPropertiesStringConverter : TypedStringConvertor<UIFlashProperties>
  {
    public UIFlashPropertiesStringConverter( IEditorWinApplication _application )
      : base( _application )
    {
    }

    public override bool SuppressProperties
    {
      get { return true; }
    }

    protected override UIFlashProperties ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
      UIFlashProperties prop = (UIFlashProperties)context.PropertyDescriptor.GetValue( instance );
      prop.propertyValue.FromString( value );
      return prop;
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, UIFlashProperties value )
    {
      return value.propertyValue.ToString();
      //if( value == null )
      //  return "{null}";
      //Type type = value.GetType();
      //string result = type.InvokeMember( "Count", System.Reflection.BindingFlags.GetProperty, null, value, null ).ToString();
      //return string.Format( "{0} element(s)", result );
    }
  }
}

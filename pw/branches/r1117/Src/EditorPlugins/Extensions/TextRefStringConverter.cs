using System;
using System.ComponentModel;
using System.Globalization;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using libdb.DB;
using libdb.Diagnostics;
using EditorLib;

namespace EditorPlugins.Extensions
{
  [ApplicableForDeriver]
  public class TextRefStringConverter : TypedStringConvertor<TextRef>
  {
    public override bool SuppressProperties { get { return true; } }
    public TextRefStringConverter( IEditorWinApplication application ) : base( application ) { }

    protected override TextRef ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
      if ( context.PropertyDescriptor.PropertyType == typeof( TextRef ) )
      {
        TextRef res = context.PropertyDescriptor.GetValue( instance ) as TextRef;
        res.FromString( value );
        return res;
      }
      else
      {
        Log.TraceWarning( "Expected TextRef PropertyType, but got {0}", context.PropertyDescriptor.PropertyType );
        return null;
      }
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, TextRef value )
    {
      return value != null ? value.ToString() : string.Empty;
    }
  }
}

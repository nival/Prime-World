using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using EditorLib;
using System.Globalization;

namespace EditorPlugins.Extensions
{
  [ApplicableForDeriver]
  public class FloatCommaConverter : TypedStringConvertor<float>
  {
    public FloatCommaConverter( IEditorWinApplication application ) : base( application ) { }

    public override bool SuppressProperties { get { return true; } }

    protected override float ConvertFromStringInternal( System.ComponentModel.ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, string value )
    {
      string s = string.Empty;
      if ( culture.NumberFormat.NumberDecimalSeparator == "," )
        s = value.Replace( '.', ',' );
      else
        s = value.Replace( ',', '.' );

      return float.Parse( s );
    }

    protected override string ConvertToString( System.ComponentModel.ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, float value )
    {
      return value.ToString();
    }
  }
}

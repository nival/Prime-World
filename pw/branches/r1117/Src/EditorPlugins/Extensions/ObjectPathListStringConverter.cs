using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using EditorLib;
using EditorLib.FieldProcessor;
using EditorPlugins.ObjectLayers;

namespace EditorPlugins.Extensions
{
  public class ObjectPathListStringConverter : TypedStringConvertor<List<ObjectLayersPath>>
  {
    public ObjectPathListStringConverter( IEditorWinApplication application )
      : base( application )
    {
    }

    public override bool SuppressProperties
    {
      get { return false; }
    }

    protected override List<ObjectLayersPath> ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
      return context.PropertyDescriptor.GetValue( instance ) as List<ObjectLayersPath>;
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, List<ObjectLayersPath> value )
    {
      int count = value != null ? value.Count : 0;
      return string.Format( "Selected {0} paths", count );
    }
  }
}

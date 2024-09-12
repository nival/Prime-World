using System.ComponentModel;
using System.Globalization;
using EditorLib;
using EditorLib.FieldProcessor;
using EditorPlugins.ObjectLayers;

namespace EditorPlugins.Extensions
{
  public class ObjectPathStringConverter : TypedStringConvertor<ObjectLayersPath>
  {
    public ObjectPathStringConverter( IEditorWinApplication application )
      : base( application )
    {
    }

    public override bool SuppressProperties
    {
      get { return true; }
    }

    protected override ObjectLayersPath ConvertFromStringInternal(ITypeDescriptorContext context, object instance, CultureInfo culture, string value)
    {
      ObjectLayersPath pathObj = context.PropertyDescriptor.GetValue( instance ) as ObjectLayersPath;
      
      if ( pathObj != null )
        pathObj.Path = value;
      
      return pathObj;
    }

    protected override string ConvertToString(ITypeDescriptorContext context, object instance, CultureInfo culture, ObjectLayersPath value)
    {
      if ( value != null )
        return value.Path;

      return string.Empty;
    }
  }
}
//using System.Collections;
//using EditorLib;
//using EditorLib.Extensions;
//using EditorLib.FieldProcessor;

//namespace EditorPlugins.Extensions
//{
//  [ApplicableForDeriver]
//  public class ListStringConverter : TypedStringConvertor<IList>
//  {
//    public ListStringConverter( IEditorWinApplication application ) : base( application ) { }

//    public override bool SuppressProperties
//    {
//      get { return false; }
//    }

//    protected override IList ConvertFromStringInternal( System.ComponentModel.ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, string value )
//    {
//      return (IList)context.PropertyDescriptor.GetValue( instance );
//    }

//    protected override string ConvertToString( System.ComponentModel.ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, IList value )
//    {
//      if ( value == null )
//        return "{null}";

//      return string.Format( "{0} element(s)", value.Count );
//    }
//  }
//}

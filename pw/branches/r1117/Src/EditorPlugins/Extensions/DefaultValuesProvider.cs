using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.FieldProcessor;
using libdb.DB;
using System.ComponentModel;
using EditorLib;

namespace EditorPlugins.Extensions
{
  public class DefaultValuesProvider : TwoTypedStandardValuesProvider<string, DefaultValuesAttribute>
  {
    public DefaultValuesProvider( IEditorWinApplication application, Attribute attribute ) : base( application, attribute ) {}

    public override bool IsStandardValuesExclusive( ITypeDescriptorContext context )
    {
      return false;
    }

    public override TypeConverter.StandardValuesCollection GetStandardValues( ITypeDescriptorContext context )
    {
      return new TypeConverter.StandardValuesCollection( Attribute.Values );
    }

    public override bool HasStandardValuesConvertor( ITypeDescriptorContext context )
    {
      return false;
    }

    public override Type GetStandardValuesType( ITypeDescriptorContext context )
    {
      return typeof( string );
    }

    protected override string ConvertFromStandardValueInternal( ITypeDescriptorContext context, object instance, object value )
    {
      return value.ToString();
    }
  }
}

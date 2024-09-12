using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using EditorLib;
using EditorLib.FieldProcessor;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Extensions
{
  public class TypeListStringConverter : TypedStringConvertor<List<Type>>
  {
    public TypeListStringConverter(IEditorWinApplication application) : base(application)
    {
    }

    public override bool SuppressProperties
    {
      get { return true; }
    }

    protected override List<Type> ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
      if ( context.PropertyDescriptor.PropertyType == typeof( List<Type> ) )
      {
        List<Type> types = new List<Type>();
        string[] typeNames = value.Split( ',', ' ' );

        foreach ( string s in typeNames )
        {
          foreach (Type resource in DataBase.KnownResources)
          {
            if(resource.Name.Equals(s, StringComparison.InvariantCultureIgnoreCase))
            {
              types.Add( resource ); 
              break;
            }
          }
        }

        return types;
      }

      Log.TraceWarning( "Expected 'List<Type>' PropertyType, but got {0}", context.PropertyDescriptor.PropertyType );
      return context.PropertyDescriptor.GetValue( instance ) as List<Type>;
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, List<Type> value )
    {
      if ( value == null )
        return string.Empty;

      return string.Join(", ", value.ConvertAll(x => x.Name).ToArray());
    }
  }
}

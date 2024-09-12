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
  public class DBPtrStringConverter : TypedStringConvertor<DBPtrBase>
  {
    private static string Empty = "{empty}";
    public override bool SuppressProperties { get { return false; } }
    public DBPtrStringConverter( IEditorWinApplication application ) : base( application ) { }

    protected override DBPtrBase ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
      if ( null != context && context.PropertyDescriptor.PropertyType.IsSubclassOf( typeof( DBPtrBase ) ) )
      {
        try
        {
          return DataBase.Get<DBResource>( DBID.FromString( value ) );
        }
        catch
        {
          return null;
        }
      }
      else
      {
        Log.TraceWarning( "Expected DBPtrBase PropertyType, but got {0}", context.PropertyDescriptor.PropertyType );
        return null;
      }
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, DBPtrBase value )
    {
      if ( null == context )
      {
        return value != null ? value.DBId.Name : Empty;
      }
      else
      {
        if ( context.PropertyDescriptor.PropertyType.IsSubclassOf( typeof( DBPtrBase ) ) )
        {
          if ( ReferenceEquals( value, null ) )
            return Empty;
          else if ( value.DBId.IsInlined )
            return string.Format( "{0}: Inlined in \"{1}\"", value.Get<DBResource>().GetType().Name, value.DBId.FileName );
          else
            return value.DBId.Name;
        }
        else
        {
          TypeConverter converter = TypeDescriptor.GetConverter( context.PropertyDescriptor.PropertyType );
          return converter.ConvertToString( context, culture, value );
        }
      }
    }
  }
}

using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Extensions;
using libdb.DB;
using EditorLib;
using System.IO;
using System.Reflection;
using libdb.IO;
using libdb.Diagnostics;

namespace EditorPlugins.DataCheckers
{
  public class FixerFileRefCase : Checker<DBResource>
  {
    protected override bool KnownDuration { get { return false; } }

    public override bool CanFixErrors { get { return true; } }

    protected override bool Process( DBPtr<DBResource> resource, IEditorCommonApplication application )
    {
      var obj = resource.Get();

      if ( ReferenceEquals( obj, null ) )
        return true;

      foreach ( PropertyInfo memb in obj.GetType().GetProperties() )
      {
        if ( TypeUtils.GetAttribute<DstFileAttribute>( memb, false ) == null || ( !( memb.GetValue( obj, null ) is string ) ) )
          continue;

        string refName = memb.GetValue( obj, null ).ToString();
        foreach ( string f in application.FileSystem.GetFiles( Path.GetDirectoryName( refName ), "*" ) )
        {
          if ( string.Compare( FileUtils.FixFileName( f ).Trim( FileUtils.PathSeparatorChar ),
                               FileUtils.FixFileName( refName ).Trim( FileUtils.PathSeparatorChar ),
                               StringComparison.CurrentCultureIgnoreCase ) !=
               string.Compare( FileUtils.FixFileName( f ).Trim( FileUtils.PathSeparatorChar ),
                               FileUtils.FixFileName( refName ).Trim( FileUtils.PathSeparatorChar ),
                               StringComparison.CurrentCulture ) )
          {
            Log.TraceMessage( "Wrong casing found: ref='{0}' in '{2}.{3}'. real file name is '{1}'", refName, f, memb.Name, memb.DeclaringType.Name );

            if ( ShouldFixErrors )
              memb.SetValue( obj, FileUtils.FixFileName( f ), null );
            break;
          }
        }
      }

      return ShouldFixErrors;
    }
  }
}

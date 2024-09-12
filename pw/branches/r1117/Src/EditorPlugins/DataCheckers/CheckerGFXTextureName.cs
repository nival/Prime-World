using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Extensions;
using DBTypes;
using libdb.DB;
using EditorLib;
using libdb.Diagnostics;
using System.IO;

namespace EditorPlugins.DataCheckers
{
  public class CheckerGFXTextureName : Checker<Texture>
  {
    protected override bool KnownDuration { get { return false; } }

    public override bool CanFixErrors { get { return false; } }

    protected override bool Process( DBPtr<Texture> resource, IEditorCommonApplication application )
    {
      var obj = resource.Get();

      if ( ReferenceEquals( obj, null ) )
        return true;

      if ( resource.DBId.IsInlined || !resource.DBId.FileName.Contains( "GFX_Textures" ) )
        return true;

      string dbFileName = Path.GetFileNameWithoutExtension( resource.DBId.FileName );
      string srcFileName = Path.GetFileNameWithoutExtension( obj.srcFileName.FileName );

      if ( string.Compare( dbFileName, srcFileName, true ) == 0 )
        return true;

      Log.TraceMessage( "{0}: Different srcFileName ({1})", obj.DBId, srcFileName );

      Dictionary<DBID, int> backlinks = resource.GetBackLinks();
      if ( backlinks.Count > 0 )
        Log.TraceMessage( "    Linked in {0} objects:", backlinks.Count );

      foreach ( var item in backlinks )
      {
        Log.TraceMessage( "    {0}", item.Key );
      }
      return false;
    }
  }
}

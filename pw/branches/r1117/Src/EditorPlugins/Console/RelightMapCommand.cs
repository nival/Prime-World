using System;
using System.Collections.Generic;
using DBTypes;
using EditorLib;
using EditorLib.Plugin;
using EditorPlugins.Importer.Relight;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Console
{
  [CommandName( "relight", "rl", "Relight map" )]
  public sealed class CreateRelightMapCommand : IConsoleCommand
  {
    public int Execute( IEditorCommonApplication application, string[] parameters )
    {
      DateTime start = DateTime.UtcNow;

      var sessionRoot = DataBase.Get<SessionRoot>( DBID.FromString( "/Session.ROOT" ) );

      if ( !sessionRoot.IsValid )
      {
        Log.TraceError( "Session root not found" );
        return 1;
      }

      MapList mapList = sessionRoot.Get().logicRoot.Get().mapList.Get();

      List<DBID> maps = new List<DBID>();
      foreach ( var mapdesc in mapList.maps )
      {
        if ( mapdesc.IsValid )
        {
          var mapId = mapdesc.Get().map.DBId;
          if ( !maps.Contains( mapId ) )
            maps.Add( mapdesc.Get().map.DBId );
        }
      }

      //var map = DBID.FromString( "/Maps/Test/PlaneMap/_.ADMP.xdb" );
      foreach( var map in maps )
      {
        if ( !RelightMap.Process( map ) )
        {
          Log.TraceError( "Error relight {0}", map.GetFullFileName() );
        }
        else
        {
          Log.TraceMessage( "Relight {0} OK", map.GetFullFileName() );
        }
      }

      DataBase.Store();
      Log.TraceMessage( "Relight time: {0:0.####} s", ( DateTime.UtcNow - start ).TotalSeconds );
      return 0;
    }
  }
}

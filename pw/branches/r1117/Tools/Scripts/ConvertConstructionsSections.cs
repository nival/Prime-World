
/*
#about заполнение SocialRoot ссылками на данные
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
*/

using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;

public class ConvertConstructionsSections
{
	private const string ConstructionsCollectingRoot = "/Social/";
    public IEnumerable Main( IEditorCommonApplication app, string[] parameters )
    {
      bool saveDB = false;

      foreach ( string parametr in parameters )
        saveDB = saveDB || parametr == "save";

      List<DBID> dbids = new List<DBID>();
      Log.TraceMessage( "Collecting constructions..." );
      ObjectsSelector.CollectObjects( app, ConstructionsCollectingRoot, typeof( Constructon ), true, true, out dbids );
      Log.TraceMessage( "{0} founded. Processing...", dbids.Count );
      foreach ( DBID dbid in dbids )
      {
        Log.TraceMessage( "Processing {0}...", dbid.ToString() );
        Constructon c = DataBase.Get<Constructon>( dbid ).Get();

        c.SectionsLockedForBuilding.Clear();
        c.SectionsLockedForDecorations.Clear();

        if ( c.SectionsSize != 0 )
          for ( int i = 0; i < c.SectionsSize; i++ )
            for ( int j = 0; j < c.SectionsSize; j++ )
            {
              Vec2 v = new Vec2( c );
              v.x = i;
              v.y = j;
              c.SectionsLockedForBuilding.Add( v );
              if ( i != c.SectionsSize-1 )
                c.SectionsLockedForDecorations.Add( v );
            }

        Log.TraceMessage( "Sections in construction {0} converted.", dbid.ToString() );
      }

      if ( saveDB )
      {
        Log.TraceMessage( "Saving..." );
        DataBase.Store();
        Log.TraceMessage( "Successfully saved" );
      }

      yield return true;
    }
  }


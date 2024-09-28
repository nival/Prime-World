/*
#about Проверка правильности имён файлов GFX-текстур
*/
using System.Collections;
using System.Collections.Generic;
using System.IO;
using DBTypes;
using EditorLib.IO;
using libdb.DB;
using libdb.Diagnostics;


public class CheckGFXTextureSourceNames
{
  public IEnumerable Main( EditorLib.IEditorCommonApplication application )
  {
    List<DBID> items;
    ObjectsSelector.CollectObjects( application, "/GFX_Textures/", typeof( Texture ), true, true, out items );

    int counter = 0;

    foreach ( var dbId in items )
    {
      DBPtr<Texture> objPtr = DataBase.Get<Texture>( dbId );
      var obj = objPtr.Get();

      if ( ReferenceEquals( obj, null ) )
        continue;

      if ( dbId.IsInlined || !dbId.FileName.Contains( "GFX_Textures" ) )
        continue;

      string dbFileName = Path.GetFileNameWithoutExtension( dbId.FileName );
      string srcFileName = Path.GetFileNameWithoutExtension( obj.srcFileName.FileName );

      if ( string.Compare( dbFileName, srcFileName, true ) == 0 )
        continue;

      Log.TraceMessage( "{2}. {0}: Different srcFileName ({1})", obj.DBId, srcFileName, counter + 1 );

      Dictionary<DBID, int> backlinks = objPtr.GetBackLinks();
      if ( backlinks.Count > 0 )
        Log.TraceMessage( "    Linked in {0} objects:", backlinks.Count );

      foreach ( var item in backlinks )
      {
        Log.TraceMessage( "    {0}", item.Key );
      }

      ++counter;
    }

    Log.TraceMessage( "Done: {0} obejcts", counter );

    yield return true;
  }
}

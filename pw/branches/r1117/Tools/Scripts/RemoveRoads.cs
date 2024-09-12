/*
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System;
using System.Collections;
using EditorLib;
using EditorLib.Extensions;
using libdb.DB;
using libdb.Diagnostics;
using EditorNative;
using PF_Editor.Map;

public class RemoveMapRoads
{
  private void Process( EditorLib.IEditorWinApplication app )
  {

    DBPtr<DBTypes.AdvMap> mapPtr = DataBase.Get<DBTypes.AdvMap>( new DBID( "/Maps/Multiplayer/PFmap/pf.ADMP", Guid.Empty ) );
    if ( mapPtr == null )
      return;
     
    DBTypes.AdvMap map = mapPtr.Get();
    if ( map == null )
      return;

		DataBase.UndoRedoManager.Start( "Remove roads" );
    for( int i = 0; i < map.objects.Count; i++ )
    {
			if ( map.objects[i].gameObject.Get() is DBTypes.Road )
			{
				map.objects.RemoveAt( i );
				i--;
			}
    }
    DataBase.UndoRedoManager.Commit();
    DataBase.Store();
		Log.TraceMessage( "Roads are removed!" );
  }
  
  private void OpenMap( EditorLib.IEditorWinApplication app )
  {
    app.Application.Extensions.OpenEditor( new DBID( "/Maps/Multiplayer/PFmap/pf.ADMP", Guid.Empty ), app, null, true );
  }

  public IEnumerable Main( EditorLib.IEditorWinApplication app )
  {
    Process( app );
    yield return true;
    //OpenMap( app );
    //yield return true;
  }
}

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

public class RemovePFMapTrees
{
  private void Process( EditorLib.IEditorWinApplication app )
  {
    Random rnd = new Random();
    //DBID treeDbid0 = new DBID( "/Terrain/Trees/Spruces/_.TREE", Guid.Empty );
    //DBID treeDbid1 = new DBID( "/Terrain/Trees/Spruces/_.TREE", Guid.Empty );
  
    DBPtr<DBTypes.AdvMap> mapPtr = DataBase.Get<DBTypes.AdvMap>( new DBID( "/Maps/Multiplayer/PFmap/pf.ADMP", Guid.Empty ) );
    if ( mapPtr == null )
      return;
     
    DBTypes.AdvMap map = mapPtr.Get();
    if ( map == null )
      return;

		DataBase.UndoRedoManager.Start( "Remove trees" );
    for( int i = 0; i < map.objects.Count; i++ )
    {
			if ( map.objects[i].gameObject.Get() is DBTypes.TreeObject )
			{
				if ( map.objects[i].offset.translateX > 227 && map.objects[i].offset.translateX < 260 
					&& map.objects[i].offset.translateY > 175 && map.objects[i].offset.translateY < 190 )
				{
					continue;
				}
				else
				{
					map.objects.RemoveAt( i );
					i--;
				}
			}
    }
    DataBase.UndoRedoManager.Commit();
    DataBase.Store();
		Log.TraceMessage( "Trees are removed!" );
  }
  
  private void OpenMap( EditorLib.IEditorWinApplication app )
  {
    app.Application.Extensions.OpenEditor( new DBID( "/Maps/Multiplayer/PFmap/pf.ADMP", Guid.Empty ), app, null, true );
  }

  public IEnumerable Main( EditorLib.IEditorWinApplication app )
  {
    Process( app );
    yield return true;
    OpenMap( app );
    yield return true;
  }
}

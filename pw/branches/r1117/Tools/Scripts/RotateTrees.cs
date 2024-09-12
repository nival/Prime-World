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

public class RotatePFMapTrees
{
  private void Process( EditorLib.IEditorWinApplication app )
  {
    Random rnd = new Random();
    DBID treeDbid0 = new DBID( "/Terrain/Trees/Spruces/_.TREE", Guid.Empty );
    //DBID treeDbid1 = new DBID( "/Terrain/Trees/Spruces/_.TREE", Guid.Empty );
  
    DBPtr<DBTypes.AdvMap> mapPtr = DataBase.Get<DBTypes.AdvMap>( new DBID( "/Maps/Multiplayer/PFmap/pf.ADMP", Guid.Empty ) );
    if ( mapPtr == null )
      return;
     
    DBTypes.AdvMap map = mapPtr.Get();
    if ( map == null )
      return;
    
    DataBase.UndoRedoManager.Start( "Rotate trees" );
    foreach( DBTypes.AdvMapObject obj in map.objects )
    {
      if ( obj.gameObject.DBId != treeDbid0 /* && obj.gameObject.DBId != treeDbid1 */ )
        continue;
        
      //obj.offset.rotationY = (float)Math.Round( rnd.NextDouble() * 360.0 );
      obj.offset.rotationZ = (float)Math.Round( rnd.NextDouble() * 360.0 );
    }
    DataBase.UndoRedoManager.Commit();
    DataBase.Store();
    Log.TraceMessage( "Trees are rotated!" );
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

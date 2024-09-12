/*
#about Ищет объекты с collision у которых x1 > x2 или y1 > y2 и правит им маску (меняет знак)
#ref PF_Types.DBTypes.dll
*/
using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib.IO;
using libdb.Animated;
using libdb.DB;
using libdb.Diagnostics;

namespace Scripts
{
	public class FixInvertedLockMask
	{
		public IEnumerable Main( EditorLib.IEditorCommonApplication application )
		{
			Log.TraceMessage( "Start" );

			List<DBID> items;
			ObjectsSelector.CollectObjects( application, "", typeof( GameObject ), true, true, out items );

      DataBase.UndoRedoManager.Start( "Fix mask" );

			foreach ( var dbId in items )
			{
        DBPtr<GameObject> resource = DataBase.Get<GameObject>( dbId );
				if ( !ReferenceEquals( resource, null ) )
				{
					Check( application, resource );
				}
			}

      DataBase.UndoRedoManager.Commit();

			Log.TraceMessage( "Done" );

			yield return true;
		}

    public bool Check( EditorLib.IEditorCommonApplication application, DBPtr<GameObject> resource )
		{
      GameObject gobj = resource.Get();

      bool convertX = gobj.collision.x1 > gobj.collision.x2;
      bool convertY = gobj.collision.y1 > gobj.collision.y2;

      if ( convertX )
      {
        float tmp = gobj.collision.x1;
        gobj.collision.x1 = gobj.collision.x2;
        gobj.collision.x2 = tmp + 1;
      }
      if ( convertY )
      {
        float tmp = gobj.collision.y1;
        gobj.collision.y1 = gobj.collision.y2;
        gobj.collision.y2 = tmp + 1;
      }

      if ( gobj.lockMask.mask.Count > 0 && ( convertX || convertY ) )
      {
        Log.TraceMessage( gobj.DBId.GetFullFileName() );

        int minx = 0;
        int miny = 0;
        foreach ( IntPoint tile in gobj.lockMask.mask )
        {
          if ( tile.x < minx )
            minx = tile.x;
          if ( tile.y < miny )
            miny = tile.y;
        }
        foreach ( IntPoint tile in gobj.lockMask.mask )
        {
          if ( convertX )
            tile.x -= minx - 1;
          if ( convertY )
            tile.y -= miny - 1;
        }
      }

			return true;
		}
	}
}

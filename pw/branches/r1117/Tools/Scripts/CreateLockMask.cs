/*
#about Найти Items/Talents/Class/Mage/LockTiles.APLR.xdb и сделать ему LockMask в виде круга радиуса 14
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
	public class CreateLockMask
	{
		public IEnumerable Main( EditorLib.IEditorCommonApplication application )
		{
			Log.TraceMessage( "Start" );

            DBID dbId = DBID.FromFileName("Items/Talents/Class/Mage/LockTiles.APLR.xdb", false);
            DBPtr<LockTilesApplicator> resource = DataBase.Get<LockTilesApplicator>(dbId);
		    if ( !ReferenceEquals( resource, null ) )
			{
                int r = 12;
                int xc = 14;
                int yc = 14;
                int x = 0;
                int y = r;
                int p = 3 - 2 * r;
                if ( r == 0 ) yield return true;

                DataBase.UndoRedoManager.Start("Add circular lockmask");

                while (y >= x) // only formulate 1/8 of circle
                {
                    AddPoint(resource, xc - x, yc - y);//upper left left
                    if (x != y)
                        AddPoint(resource, xc - y, yc - x);//upper upper left
                    AddPoint(resource, xc + y, yc - x);//upper upper right
                    if (x != 0 && x != y)
                        AddPoint(resource, xc + x, yc - y);//upper right right
                    AddPoint(resource, xc - x, yc + y);//lower left left
                    if (x != 0 && x != y)
                        AddPoint(resource, xc - y, yc + x);//lower lower left
                    if (x != 0)
                        AddPoint(resource, xc + y, yc + x);//lower lower right
                    if (x != 0 && x != y)
                        AddPoint(resource, xc + x, yc + y);//lower right right
                    if (p < 0) p += 4 * x++ + 6;
                    else p += 4 * (x++ - y--) + 10;
                };

                DataBase.UndoRedoManager.Commit();
                DataBase.Store();
			}

			Log.TraceMessage( "Done" );

			yield return true;
		}

        public void AddPoint(DBPtr<LockTilesApplicator> resource, int x, int y)
		{
            IntPoint item = new IntPoint( resource );
            item.x = x;
            item.y = y;

            resource.Get().lockMask.mask.Add(item);
		}
	}
}

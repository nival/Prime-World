/*
#about Находит объекты, у которых есть анимированные треки с отрицательными ключами и выдает список таких объектов.
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
	public class FindBrokenAnimCurves
	{
		public IEnumerable Main( EditorLib.IEditorCommonApplication application )
		{
			Log.TraceMessage( "Start" );

			List<DBID> items;
			ObjectsSelector.CollectObjects( application, "", typeof( DBSceneResource ), true, true, out items );

			foreach ( var dbId in items )
			{
				DBPtr<DBSceneResource> resource = DataBase.Get<DBSceneResource>( dbId );
				if ( !ReferenceEquals( resource, null ) )
				{
					Check( application, resource );
				}
			}

			Log.TraceMessage( "Done" );

			yield return true;
		}

		public bool Check( EditorLib.IEditorCommonApplication application, DBPtr<DBSceneResource> resource )
		{
			foreach ( AttachedSceneComponent asc in resource.Get().attached )
			{
				bool success = CheckAnimated(asc.placement.pos) &&
											 CheckAnimated(asc.placement.rot) &&
											 CheckAnimated(asc.placement.scale);

				if ( !success )
				{
					Log.TraceMessage( resource.Get().DBId.GetFullFileName() );
					return true;
				}
			}

			return true;
		}

		private bool CheckAnimated( IAnimated animated )
		{
			for ( int i = 0; i < animated.TracksCount; i++ )
			{
				IAnimatedTrack animatedTrack = animated.GetObjectTrack( i );

				//ищем ключ с отрицательным временем
				for ( int keyIndex = 0; keyIndex < animatedTrack.KeysCount; ++keyIndex )
				{
					if ( animatedTrack.GetKey( keyIndex ) < 0 )
					{
						return false;
					}
				}
			}
			return true;
		}
	}
}

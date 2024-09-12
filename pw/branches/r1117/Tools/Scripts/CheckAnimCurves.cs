/*
#about Проверка валидности анимированных треков
*/
using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib.IO;
using libdb.Animated;
using libdb.DB;
using libdb.Diagnostics;


public class CheckAnimCurves
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
		float delta = 4.0f;

		foreach ( AttachedSceneComponent asc in resource.Get().attached )
		{
			bool success = CheckAnimated( asc.placement.pos, delta ) &&
										 CheckAnimated( asc.placement.rot, delta ) &&
										 CheckAnimated( asc.placement.scale, delta );

			if ( !success )
			{
				Log.TraceMessage( resource.Get().DBId.GetFullFileName() );
				return true;
			}
		}

		return true;
	}

	private bool CheckAnimated( IAnimated animated, float delta )
	{
		for ( int i = 0; i < animated.TracksCount; i++ )
		{
			IAnimatedTrack animatedTrack = animated.GetObjectTrack(i);

			if ( animatedTrack.Length > 0 )
			{
				if ( animatedTrack.KeysCount > 1 )
				{
					float key1 = animatedTrack.GetKey( animatedTrack.KeysCount - 2 );
					float key2 = animatedTrack.GetKey( animatedTrack.KeysCount - 1 );
					if ( key2 - key1 > delta )
					{
						if ( (float)animated.GetObjectTrackValue( key1, i ) == (float)animated.GetObjectTrackValue( key2, i ) )
						{
							return false;
						}
					}
				}
			}
		}
		return true;
	}
}

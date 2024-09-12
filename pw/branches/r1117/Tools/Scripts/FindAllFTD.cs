/*
#about Ищет и выводит список объектов, которые содержат аппликатор FlagsApplicator с flags & 128
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
	public class FindAllFTD
	{
		public IEnumerable Main( EditorLib.IEditorCommonApplication application )
		{
			Log.TraceMessage( "Start" );

			List<DBID> items;
			ObjectsSelector.CollectObjects( application, "", typeof( FlagsApplicator ), true, true, out items );

			foreach ( var dbId in items )
			{
				DBPtr<FlagsApplicator> resource = DataBase.Get<FlagsApplicator>( dbId );
				if ( !ReferenceEquals( resource, null ) )
				{
					Check( application, resource );
				}
			}

			Log.TraceMessage( "Done" );

			yield return true;
		}

		public bool Check( EditorLib.IEditorCommonApplication application, DBPtr<FlagsApplicator> resource )
		{
			if ( (resource.Get().flag & EUnitFlag.ForbidTakeDamage) != 0 )
			{
				Log.TraceMessage( resource.Get().DBId.GetFullFileName() );
				return true;
			}
			return true;
		}
	}
}

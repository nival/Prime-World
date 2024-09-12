using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using libdb.DB;

namespace EditorLib.IO
{
	public static class ObjectsSelector
	{
		public static int CollectObjects(
			IEditorCommonApplication application,
			string rootPath,
			Type typesMask,
			bool recursive,
			bool includeDeriven,
			out List<DBID> items
			)
		{
			Dictionary<Type, List<DBID>> result;
			var count = CollectObjects(
				application,
				rootPath,
				new Type[] { typesMask },
				recursive,
				includeDeriven,
				out result
				);

			items = new List<DBID>();
			foreach ( var ids in result.Values )
			{
				items.AddRange( ids );
			}

			return count;
		}

		public static int CollectObjects(
			IEditorCommonApplication application,
			string rootPath,
			Type[] typesMask,
			bool recursive,
			bool includeDeriven,
			out Dictionary<Type, List<DBID>> items
			)
		{
			if ( ReferenceEquals( ObjectsRootFolder.Root, null ) )
			{
				ObjectsRootFolder.Initialize( application );
			}

			var folder = ObjectsRootFolder.Root.GetFolder( rootPath );
			items = new Dictionary<Type, List<DBID>>();

			if ( !ReferenceEquals( folder, null ) )
			{
				var result = CollectObjects( folder, typesMask, recursive, includeDeriven, items );
				RemoveDuplicates( items );
				return result;
			}
			else
			{
				Log.TraceError( "Cannot collect types: root folder does not exist." );
				return 0;
			}
		}

		private static void RemoveDuplicates( Dictionary<Type, List<DBID>> items )
		{
			foreach ( var type in new List<Type>( items.Keys ) )
			{
				var ids = new Dictionary<DBID, DBID>();
				foreach ( var dbId in items[type] )
				{
					if ( !ids.ContainsKey( dbId ) )
					{
						ids.Add( dbId, dbId );
					}
				}
				items[type] = new List<DBID>( ids.Keys );
			}
		}

		private static int CollectObjects( ObjectsFolder folder, Type[] typesMask, bool recursive, bool includeDeriven, Dictionary<Type, List<DBID>> result )
		{
			int count = 0;
			foreach ( var dbId in folder.Items )
			{
				count += ProcessResource( dbId, typesMask, includeDeriven, result );
			}

			if ( recursive )
			{
				foreach ( var subfolder in folder.Folders )
				{
					count += CollectObjects( subfolder, typesMask, recursive, includeDeriven, result );
				}
			}

			return count;
		}

		private static int ProcessResource( DBID dbId, Type[] typesMask, bool includeDeriven, Dictionary<Type, List<DBID>> result )
		{
			DBPtr<DBResource> res = DataBase.Get<DBResource>( dbId );

			if ( res == null )
			{
				Log.TraceMessage( "Resource \"{0}\" is not exist.", dbId.Name );
				return 0;
			}

			if ( res.Get() == null )
			{
				Log.TraceMessage( "Failed to load resource \"{0}\".", dbId.Name );
				return 0;
			}

			int count = 0;

			foreach ( var inlinedObjectId in res.GetLinks().Keys )
			{
				if ( inlinedObjectId.IsInlined )
				{
					count += ProcessResource( inlinedObjectId, typesMask, includeDeriven, result );
				}
			}

			var dbObject = res.Get();

			foreach ( var type in typesMask )
			{
				if ( includeDeriven )
				{
					if ( type.IsInstanceOfType( dbObject ) )
					{
						++count;
						AddResourceToResult( result, dbObject.GetType(), dbId );
					}
				}
				else
				{
					if ( dbObject.GetType() == type )
					{
						++count;
						AddResourceToResult( result, type, dbId );
					}
				}
			}

			return count;
		}

		private static void AddResourceToResult( Dictionary<Type, List<DBID>> result, Type type, DBID dbId )
		{
			if ( result.ContainsKey( type ) )
			{
				result[type].Add( dbId );
			}
			else
			{
				result.Add( type, new List<DBID>() { dbId } );
			}
		}

    public delegate bool ProcessStructFunctor<T>( DBResource owner, T obj );

    public static bool ProcessStructs<T>( IEditorCommonApplication application, string path, bool recursive, ProcessStructFunctor<T> functor )
    {
      List<DBID> resDBIDs;

      CollectObjects( application, path, typeof( DBResource ), recursive, true, out resDBIDs );

      FieldsWalker.DepthController depth = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtr, FieldsWalker.ObjectType.All );

      bool noInterruptions = true;

      foreach ( DBID resDBID in resDBIDs )
      {
        DBResource res = DataBase.Get<DBResource>( resDBID ).Get();

        if ( null == res )
          continue;

        FieldsWalker.VisitFields<T>( res, ( ref T obj ) => { noInterruptions = noInterruptions && functor( res, obj ); return noInterruptions; }, depth.Functor );

        if ( !noInterruptions )
          break;
      }

      return noInterruptions;
    }

		public static bool ProcessStructs( IEditorCommonApplication application, string path, bool recursive, Function<bool, DBResource, object> functor )
		{
			List<DBID> resDBIDs;

			CollectObjects(application, path, typeof(DBResource), recursive, true, out resDBIDs);

			FieldsWalker.DepthController depth = new FieldsWalker.DepthController(0, FieldsWalker.ObjectType.DBPtr, FieldsWalker.ObjectType.All);

			bool noInterruptions = true;

			foreach (DBID resDBID in resDBIDs)
			{
				DBResource res = DataBase.Get<DBResource>(resDBID).Get();

				if (null == res)
					continue;

				FieldsWalker.VisitFields(res, (ref object obj) =>
				{
					noInterruptions = noInterruptions && functor(res, obj); 	
					return noInterruptions;
				}, depth.Functor);

				if (!noInterruptions)
					break;
			}

			return noInterruptions;
		}
	}
}

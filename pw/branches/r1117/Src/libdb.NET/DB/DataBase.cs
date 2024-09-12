using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using libdb.IO;
using libdb.UndoRedo;
using libdb.Diagnostics;

namespace libdb.DB
{
	public static class DataBase
	{
		#region File system relative fields, methods and properties

		private static IFileSystem fileSystem = null;

		public static IFileSystem FileSystem { get { return fileSystem; } }

		public static void SetFileSystem( IFileSystem _fileSystem ) { fileSystem = _fileSystem; }

		#endregion

		#region Types cache relative fields, methods and properties

		private static DBTypesCache typesCache = new DBTypesCache();
	
		internal static DBTypesCache TypesCache
		{
			get { return typesCache; }
		}

		public static IEnumerable<Type> KnownTypes
		{
			get
			{
				List<Type> types = new List<Type>();
				types.AddRange( TypesCache.KnownTypes );

				types.Sort( TypeUtils.Compare );
				return types;
			}
		}

		public static IEnumerable<Type> KnownResources
		{
			get
			{
				List<Type> types = new List<Type>();
				foreach ( Type type in KnownTypes )
				{
					if ( type.IsSubclassOf( typeof( DBResource ) ) )
						types.Add( type );
				}

				types.Sort( TypeUtils.Compare );
				return types;
			}
		}

		private static List<string> knownResourcesExtensions;

		public static IEnumerable<string> KnownResourcesExtensions
		{
			get
			{
				if (knownResourcesExtensions == null)
				{
					knownResourcesExtensions = new List<string>();

					foreach (Type resType in KnownResources)
					{
						UseTypeNameAttribute attribute = TypeUtils.GetAttribute<UseTypeNameAttribute>(resType, false);

						if (attribute == null)
							continue;

						if (!knownResourcesExtensions.Contains(attribute.alias))
							knownResourcesExtensions.Add(attribute.alias);
					}

					knownResourcesExtensions.Sort();				
				}

				return knownResourcesExtensions.AsReadOnly();
			}
		}

		public static void LoadTypes( IEnumerable<string> typeAssebliesFiles )
		{
			foreach ( string fileName in typeAssebliesFiles )
				typesCache.LoadTypesFromAssembly( fileName );
		}

		public static bool TryGetType( string name, out Type type )
		{
			return typesCache.TryGetType( name, out type );
		}

		#endregion

		#region UndoRedoManager relative fields, methods and properties

		public static UndoRedoManager UndoRedoManager { get; set; }

		public static void AddOperation( IUndoRedoOperation operation )
		{
			if ( UndoRedoManager != null )
				UndoRedoManager.AddOperation( operation );
		}

		#endregion

		#region Track database modification

		private static Dictionary<DBID, bool> modifiedObjects = new Dictionary<DBID, bool>();
		private static Dictionary<DBID, bool> deletedObjects = new Dictionary<DBID, bool>();

		internal static void MarkResourceAsChanged( DBID dbid )
		{
			if ( DBID.IsNullOrEmpty( dbid ) || !IsExists( dbid ) )
				return;

			DBID fullDbid = DBID.FromDBID( dbid, false );
			if ( modifiedObjects.ContainsKey( fullDbid ) || deletedObjects.ContainsKey( fullDbid ) )
				return;

			modifiedObjects.Add( fullDbid, false );
		}

		internal static void MarkResourceAsDeleted( DBID dbid )
		{
			if ( DBID.IsNullOrEmpty( dbid ) )
				return;

			if ( dbid.IsInlined )
        MarkResourceAsChanged( DBID.FromDBID( dbid, false ) );
			else
			{
				if ( deletedObjects.ContainsKey( dbid ) )
					return;

				deletedObjects.Add( dbid, false );
				if ( modifiedObjects.ContainsKey( dbid ) )
					modifiedObjects.Remove( dbid );
			}
		}

		public static bool IsModified { get { return modifiedObjects.Count > 0 || deletedObjects.Count > 0; } }

		public static void Store()
		{
			Store( false );
		}

		public static void Store( bool gameDataOnly )
		{
			foreach ( DBID dbid in modifiedObjects.Keys )
			{
				DBPtr<DBResource> resource = Get<DBResource>( dbid );
				resource.Store( gameDataOnly );
				if ( StoreDBResourceEvent != null )
					StoreDBResourceEvent( dbid );
			}

			foreach ( DBID dbid in deletedObjects.Keys )
				DataBase.FileSystem.DeleteFile( dbid.GetFullFileName() );

			deletedObjects.Clear();
			modifiedObjects.Clear();
		}

		public static void ClearModified()
		{
			deletedObjects.Clear();
			modifiedObjects.Clear();
		}

		#endregion

		#region Internal database callbacks (from UndoRedoOperations)

		internal static void CreateCallback( DBID dbid )
		{
      if ( DBID.IsNullOrEmpty( dbid ) )
      {
        Log.TraceWarning( "Try to create resource with empty dbid!" );
        return;
      }

      if ( deletedObjects.ContainsKey( dbid ) )
				deletedObjects.Remove( dbid );

			MarkResourceAsChanged( dbid );
			
			if ( CreateDBResourceEvent != null )
				CreateDBResourceEvent( dbid );
      if ( dbid.IsInlined )
        ChangeCallback( DBID.FromDBID( dbid, false ) );
    }

		public static void ChangeCallback( DBID dbid )
		{
      if ( DBID.IsNullOrEmpty( dbid ) )
        return;

      if ( UndoRedoManager != null && UndoRedoManager.IsCommandStarted )
        return;

			MarkResourceAsChanged( dbid );

			if ( ChangeDBResourceEvent != null )
				ChangeDBResourceEvent( dbid );
		}

		internal static void RenameCallback( DBID dbid, DBID oldDbid )
		{
      if ( DBID.IsNullOrEmpty( dbid ) )
      {
        Log.TraceWarning( "Try to create resource with empty dbid!" );
        return;
      }

			if ( deletedObjects.ContainsKey( dbid ) )
				deletedObjects.Remove(dbid);

			MarkResourceAsChanged( dbid );
			MarkResourceAsDeleted( oldDbid );

			if ( RenameDBResourceEvent != null )
				RenameDBResourceEvent( dbid, oldDbid );

      if ( ( UndoRedoManager != null && UndoRedoManager.IsCommandStarted ) || ChangeDBResourceEvent == null )
        return;

      if ( oldDbid.IsInlined )
        ChangeDBResourceEvent( DBID.FromDBID( oldDbid, false ) );
      if ( dbid.IsInlined )
        ChangeDBResourceEvent( DBID.FromDBID( dbid, false ) );
    }

		internal static void DeleteCallback( DBID dbid )
		{
      if ( DBID.IsNullOrEmpty( dbid ) )
      {
        Log.TraceWarning( "Try to create resource with empty dbid!" );
        return;
      }

			MarkResourceAsDeleted( dbid );

			if ( DeleteDBResourceEvent != null )
				DeleteDBResourceEvent( dbid );
      if ( dbid.IsInlined )
        ChangeCallback( DBID.FromDBID( dbid, false ) );
		}

		public static void Reset()
		{
		  modifiedObjects.Clear();
      deletedObjects.Clear();
			DBReference.Reset();
		}

		#endregion

		#region Public delegates and events.

		public delegate void CreateDBResourceEventHandler( DBID dbid );
		public static event CreateDBResourceEventHandler CreateDBResourceEvent = null;

		public delegate void ChangeDBResourceEventHandler( DBID dbid );
		public static event ChangeDBResourceEventHandler ChangeDBResourceEvent = null;

		public delegate void RenameDBResourceEventHandler( DBID dbid, DBID oldDbid );
		public static event RenameDBResourceEventHandler RenameDBResourceEvent = null;

		public delegate void DeleteDBResourceEventHandler( DBID dbid );
		public static event DeleteDBResourceEventHandler DeleteDBResourceEvent = null;

		public delegate void StoreDBResourceEventHandler( DBID dbId );
		public static event StoreDBResourceEventHandler StoreDBResourceEvent = null;

		#endregion

		#region Public database operations (wrapped with UndoRedo)

		public static DBPtr<T> Create<T>( DBID dbid, T resource ) where T : DBResource, new()
		{
			if ( resource == null )
				return Get<T>( dbid );

			AddOperation( new libdb.UndoRedo.ResourceCreateOperation( dbid, resource ) );
			return new DBPtr<T>( dbid, null );
		}

    public static DBPtr<T> Get<T>( DBID dbid ) where T : DBResource, new()
		{
			if ( dbid.IsInlined )
				return new DBPtr<T>( dbid, null, DataBase.Get<DBResource>( DBID.FromDBID( dbid, false ) ) );

			return new DBPtr<T>( dbid, null );
		}

    public static DBPtr<T> Get<T>( DBID dbid, DBResource owner ) where T : DBResource, new()
		{
			return new DBPtr<T>( dbid, null, owner );
		}

		public static void Delete( DBID dbid )
		{
			AddOperation( new libdb.UndoRedo.ResourceDeleteOperation( dbid ) );
		}

		public static void Rename( DBID newDbid, DBID oldDbid )
		{
			AddOperation( new libdb.UndoRedo.ResourceRenameOperation( newDbid, oldDbid ) );
		}

		public static void Copy( DBID newDbid, DBID oldDbid )
		{
			UndoRedoManager.Start( string.Format( "Copy \"{0}\" to \"{1}\"", oldDbid.Name, newDbid.Name ) );
			DBResource resource = Get<DBResource>( oldDbid ).Get();
			DBResource newResource = TypeUtils.CreateInstance( resource.GetType() ) as DBResource;
			Create<DBResource>( newDbid, newResource );
			DBCopy.Copy( newResource, resource );
			UndoRedoManager.Commit();
		}

		public static void Inline( DBID _dbid )
		{
			AddOperation( new ResourceInlineOperation( _dbid ) );
		}

		public static void Uninline( DBID _dbId, DBID _newDbId )
		{
			AddOperation( new ResourceUninlineOperation( _dbId, _newDbId ) );
		}

		public static void ChangeResource( DBID _dbid, DBResource _resource )
		{
			AddOperation( new ResourceChangeOperation( _dbid, _resource ) );
		}

		public static void RemoveBacklinksTo( object _root )
		{
			DBPtrBase[] links = FieldsWalker.CollectDBPtrs( _root, ( object _x, ref int _d ) =>
			{
				DBPtrBase ptr = _x as DBPtrBase;
				if ( ptr != null )
					return ptr.IsValid && ptr.DBId.IsInlined;

				return true;
			} );

			foreach ( DBPtrBase link in links )
			{
				if(link.IsValid && !link.DBId.IsInlined)
					AddOperation( new DBPtrBaseChangeOperation( link, DBID.Empty ) );
			}
		}
		#endregion

		#region Helpers ...

		public static bool IsExists( DBID dbid )
		{
			return DBReference.IsExist( dbid );
		}

		public static byte[] SerializeToMemory( DBID dbId )
		{
			var res = Get<DBResource>( dbId );
			if ( !ReferenceEquals( res, null ) && !ReferenceEquals( res.Get(), null ) )
			{
				using ( var stream = new MemoryStream() )
				{
					var writer = XmlContextWriter.Create( stream, dbId );
					DBXmlSerializer.Serialize( writer, res );
					writer.Flush();
					stream.Seek( 0, SeekOrigin.Begin );
					return stream.ToArray();
				}
			}
			else
			{
				return null;
			}
		}

		private static bool HasDependency( DBID from, DBID to, Dictionary<DBID, DBID> prevIds )
		{
			if ( prevIds.ContainsKey( to ) )
			{
				return false;
			}
			else if ( from.FileName == to.FileName )
			{
				return true;
			}
			else
			{
				prevIds.Add( to, to );

				var res = DataBase.Get<DBResource>( to );
				if ( !ReferenceEquals( res, null ) )
				{
					foreach ( var backLinkId in res.GetBackLinks().Keys )
					{
						if ( HasDependency( from, backLinkId, prevIds ) )
						{
							return true;
						}
					}
					return false;
				}
				else
				{
					return false;
				}
			}
		}

		public static bool HasDependency( DBID from, DBID to )
		{
      return !FieldsWalker.VisitFields(Get<DBResource>(from), (ref object obj, DBFieldInfo field) =>
      { return obj == null || !(obj is DBPtrBase) || (obj as DBPtrBase).DBId != to; }, 
      new libdb.DB.FieldsWalker.DepthController(-1, FieldsWalker.ObjectType.None, FieldsWalker.ObjectType.All).Functor);
		}

		#endregion

		#region Links walker

		public delegate DBPtrBase VisitLinksFunctor( DBPtrBase ptr );

		public static DBPtrBase VisitLinks( object obj, int depth, bool inlineDecreaseDepth, VisitLinksFunctor functor )
		{
			if ( depth == 0 || obj == null )
				return null;

			if ( obj.GetType().IsPrimitive || obj.GetType().IsEnum || TypeUtils.IsSimpleType( obj.GetType() ) )
				return null;

			if ( TypeUtils.GetTypeFromPtr( obj.GetType() ) != null )
			{
				DBPtrBase ptr = obj as DBPtrBase;
				if ( !ptr.DBId.IsEmpty )
				{
					int newDepth = ( inlineDecreaseDepth || !ptr.DBId.IsInlined ) ? depth - 1 : depth;
					VisitLinks( ptr.Get<DBResource>(), newDepth, inlineDecreaseDepth, functor );
					return functor( ptr );
				}
			}
			else if ( TypeUtils.IsList( obj.GetType() ) )
			{
				IEnumerable list = obj as IEnumerable;
				foreach ( object item in list )
					VisitLinks( item, depth, inlineDecreaseDepth, functor );
			}
			else
			{
				DBFieldInfo[] fields = TypeUtils.GetFields( obj.GetType(), true );
				foreach ( DBFieldInfo field in fields )
				{
					DBPtrBase ptr = VisitLinks( field.GetValue( obj ), depth, inlineDecreaseDepth, functor );
					if ( TypeUtils.GetTypeFromPtr( field.GetType() ) != null )
					{
						DBPtrBase oldPtr = field.GetValue( obj ) as DBPtrBase;
						if ( ptr != oldPtr )
							field.SetValue( obj, ptr );
					}
				}
			}

			return null;
		}

		private class LinksCollector
		{
			private List<DBPtrBase> links = new List<DBPtrBase>();

			public DBPtrBase Functor( DBPtrBase ptr )
			{
				links.Add( ptr );
				return ptr;
			}

			public DBPtrBase[] GetLinks() { return links.ToArray(); }
		}

		public static DBPtrBase[] CollectLinks( object obj, int depth, bool inlineDecreaseDepth )
		{
			LinksCollector collector = new LinksCollector();
			VisitLinks( obj, depth, inlineDecreaseDepth, collector.Functor );

			return collector.GetLinks();
		}

		#endregion
	}
}

using System;
using System.Collections.Generic;
using System.Reflection;
using libdb.Diagnostics;
using libdb.IO;
using libdb.UndoRedo;

namespace libdb.DB
{
  internal sealed class DBReference 
	{
		#region class DstFileNameFixer

		private sealed class DstFileNameFixer
		{
			private class FixedFileName
			{
				public string oldFileName = string.Empty;
				public string newFileName = string.Empty;

				public FixedFileName( string oldFileName ) { this.oldFileName = oldFileName; this.newFileName = string.Empty; }
				public void SetNewFileName( string _newFileName ) { this.newFileName = _newFileName; }
			}

			private List<FixedFileName> fileNames = new List<FixedFileName>();
			private int currentPosition = -1;

			public bool Functor( ref string fileName, DstFileAttribute dstFile, string field )
			{
				if ( currentPosition < 0 )
					fileNames.Add( new FixedFileName( fileName ) );
				else if ( currentPosition < fileNames.Count )
					fileNames[currentPosition++].SetNewFileName( fileName );
				else
					return false;

				return true;
			}

			public void StartFix() { currentPosition = 0; }

			public void DoFix( bool delete )
			{
				if ( currentPosition != fileNames.Count )
					return;

				foreach ( FixedFileName fileName in fileNames )
				{
					if ( fileName.oldFileName != fileName.newFileName )
					{
						FileUtils.CopyFile( DataBase.FileSystem, fileName.oldFileName, fileName.newFileName );
						if ( delete )
							DataBase.FileSystem.DeleteFile( fileName.oldFileName );
					}
				}
			}
		}

		#endregion

		#region class SrcFileNameFixer

		private sealed class SrcFileNameFixer
		{
			private readonly DBID newDbid = DBID.Empty;

			public SrcFileNameFixer( DBID newDbid ) { this.newDbid = newDbid; }

      public bool Functor( ref SrcFile srcFile, SrcFileAttribute srcFileAttr, string field )
			{
        string destFolder = string.Empty;

        if ( srcFileAttr == null || string.IsNullOrEmpty( srcFileAttr.SourceFolder ) )
          destFolder = FileUtils.PathSeparatorString + FileUtils.GetParentFolderPath( newDbid.FileName );
        else
          destFolder = FileUtils.PathSeparatorString + srcFileAttr.SourceFolder;

        srcFile.SetFileName( FileUtils.Combine( FileUtils.FixFolderName( destFolder ), FileUtils.GetFileName( srcFile.FileName ) ) );
        srcFile.SetChecksum( 0 );

				return true;
			}
		}

		#endregion

		#region class RemoveObsoleteLinks

		private sealed class RemoveObsoleteLinks
		{
			private readonly DBID obsoleteDbid = DBID.Empty;

			public RemoveObsoleteLinks( DBID obsoleteDbid ) { this.obsoleteDbid = obsoleteDbid; }

      public bool Functor( ref object obj, DBFieldInfo field )
      {
        DBPtrBase ptr = obj as DBPtrBase;
        if ( ptr == null )
          return true;

        if ( ptr.DBId != obsoleteDbid )
          return true;

        Type listType = TypeUtils.GetTypeFromList( field.FieldType );
        Type resourceType = TypeUtils.GetTypeFromPtr( listType == null ? field.FieldType : listType );
        ConstructorInfo cotr = field.FieldType.GetConstructor( new Type[] { typeof( DBID ), resourceType } );
        if ( cotr == null )
          return true;

        obj = cotr.Invoke( new object[] { DBID.Empty, null } );
        return false;
      }

      public bool FunctorAll( ref object obj, DBFieldInfo field )
      {
        DBPtrBase ptr = obj as DBPtrBase;
        if ( ptr == null )
          return true;

        Type listType = TypeUtils.GetTypeFromList( field.FieldType );
        Type resourceType = TypeUtils.GetTypeFromPtr( listType == null ? field.FieldType : listType );
        ConstructorInfo cotr = field.FieldType.GetConstructor( new Type[] { typeof( DBID ), resourceType } );
        if ( cotr == null )
          return true;

        obj = cotr.Invoke( new object[] { DBID.Empty, null } );
        return true;
      }


		}

		#endregion

    private Dictionary<string, DBResource> states = new Dictionary<string, DBResource>();
    private DBResource resource { get { return states[String.Empty]; } }
		private DBID dbid = DBID.Empty;
		private bool isDeletedResource = false;

		private Dictionary<DBReference, int> backLinks = new Dictionary<DBReference, int>();

    //@Ivn@TODO: review outliner
    private static object loadLocker = new object();

		private DBReference( DBID dbid )
		{
      states.Add( String.Empty, null );
			this.dbid = dbid;
		}

    private void FireChangedEvent( object sender, EventArgs e )
    {
      if ( Changed != null )
      {
        Changed( sender, e );
      }
    }

    private void Load()
    {
      lock ( loadLocker )
      {
        if ( ( resource != null || DBId.IsInlined || DBID.IsNullOrEmpty( DBId ) ) )
          return;

        using ( XmlContextReader reader = XmlContextReader.Create( DataBase.FileSystem, DBId ) )
        {
          if ( reader == null )
            return;

          Dictionary<DBID, int> tempLinks = new Dictionary<DBID, int>();
          Dictionary<string, DBResource> tempStates = new Dictionary<string, DBResource>();

          states[ String.Empty ] = DBXmlSerializer.Deserialize( reader, DataBase.TypesCache, tempLinks, tempStates );
          reader.Close();

          if ( resource != null )
          {
            resource.Rename( DBId );
            resource.Changed += FireChangedEvent;
            SetBacklinks( tempLinks );
            DBPtr<DBResource> ptr = new DBPtr<DBResource>( DBId, resource );
            ptr.LoadStates( tempStates );
          }
        }
      }
    }

    public T1 Get<T1>() where T1 : DBResource
		{
      return Get<T1>( String.Empty );
		}

    public T1 Get<T1>( string stateName ) where T1 : DBResource
    {
      if ( isDeletedResource )
        return null;

      Load();

      if ( !states.ContainsKey( stateName ) )
        return null;

      DBResource res = states[stateName];
      if ( res == null )
        return null;

      T1 result = res as T1;
      if ( result == null )
        Log.TraceError( "Cannot cast resource \"{0}\" from type \"{1}\" to type \"{2}\"", DBId.Name, resource.GetType().Name, typeof( T1 ).Name );

      return result;
    }

		internal DBResource GetDBResource()
		{
			return resource;
		}

		internal void AddBackLink( DBID reference )
		{
			this.Get<DBResource>();
			DBReference dbRef = Get( reference );
      if ( Log.Assert( !ReferenceEquals( dbRef, null ), "Try add backlink to deleted resource \"{0}\"", reference ) )
        return;

			if ( backLinks.ContainsKey( dbRef ) )
				++backLinks[dbRef];
			else
				backLinks.Add( dbRef, 1 );

			DataBase.MarkResourceAsChanged( dbid );
      DataBase.MarkResourceAsChanged( reference );
		}

		internal void RemoveBackLink( DBID reference )
		{
			this.Get<DBResource>();
			DBReference dbRef = Get( reference );
      if ( Log.Assert( !ReferenceEquals( dbRef, null ), "Try remove backlink to deleted resource \"{0}\"", reference ) )
        return;
      
      int linksCount = 0;
			if ( backLinks.TryGetValue( dbRef, out linksCount ) )
			{
				if ( linksCount == 1 )
					backLinks.Remove( dbRef );
				else
					--backLinks[dbRef];

				DataBase.MarkResourceAsChanged( dbid );
				DataBase.MarkResourceAsChanged( reference );
			}
		}

		internal void SetBacklinks( IEnumerable<KeyValuePair<DBID, int>> _backlinks )
		{
      backLinks.Clear();
      foreach ( var it in _backlinks )
      {
        if ( !IsExist( it.Key ) )
          continue;
        DBReference backLink = Get( it.Key );
        if ( Log.Assert( !ReferenceEquals( backLink, null ), "Found backlink to deleted resource \"{0}\"", it.Key ) )
          continue;
        backLinks.Add( backLink, it.Value );
      }
		}

		internal Dictionary<DBID, int> GetBackLinks()
		{
			Dictionary<DBID, int> tempLinks = new Dictionary<DBID, int>();
      foreach ( KeyValuePair<DBReference, int> it in backLinks )
      {
        if ( !tempLinks.ContainsKey( it.Key.DBId ) )
          tempLinks.Add( it.Key.DBId, it.Value );
      }

			return tempLinks;
		}

		internal DBReference Rename( DBID dbid, DBReference replacingRef )
		{
			DBID oldDbid = DBId;
			if ( oldDbid == dbid )
				return null;
			Get<DBResource>();

      DBReference overwrittenRef = null;

      if ( cache.ContainsKey( dbid ) )
        overwrittenRef = cache[dbid];

			// currently we have two dbid pointed to one reference
      cache[dbid] = this;

			FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All );

			// collect fields with DstFileAttribute attribute
			DstFileNameFixer dstFileNameFixer = new DstFileNameFixer();

      foreach ( var state in states.Values )
      {
        FieldsWalker.VisitFields<string, DstFileAttribute>( state, dstFileNameFixer.Functor, depthController.Functor );
      }

			// fix linked resources
			DBReference oldOwner = Get( DBID.FromDBID( oldDbid, false ) );
			DBReference newOwner = Get( DBID.FromDBID( dbid, false ) );
			DBPtrBase[] links = FieldsWalker.CollectDBPtrs( states.Values , depthController.Functor );
			foreach ( DBPtrBase link in links )
			{
				if ( DBID.IsNullOrEmpty( link.DBId ) )
					continue;

				if ( link.DBId.IsInlined )
				{
					// inlined resource should be renamed
					DBReference reference = null;
					if ( !cache.TryGetValue( link.DBId, out reference ) || reference == null || reference.DBId.FileName != oldDbid.FileName )
						continue;

          DBID refOldDBId = reference.DBId;
          cache.Remove( refOldDBId );
          reference.dbid = DBID.FromDBID( dbid, true );
          reference.resource.Rename( reference.DBId );
          cache.Add( reference.DBId, reference );

					DataBase.RenameCallback( reference.DBId, refOldDBId );
				}
        else
        {
					DBReference reference = Get( link.DBId );
          if ( ReferenceEquals( reference, null ) )
            continue;

          reference.Load();
          if ( oldOwner != newOwner )
          {
            int linksCount = 0;
            if ( reference.backLinks.TryGetValue( oldOwner, out linksCount ) )
            {
              if ( linksCount == 1 )
                reference.backLinks.Remove( oldOwner );
              else
                reference.backLinks[oldOwner] = linksCount - 1;
            }

            if ( reference.backLinks.TryGetValue( newOwner, out linksCount ) )
              reference.backLinks[newOwner] = linksCount + 1;
            else
              reference.backLinks.Add( newOwner, 1 );
          }

          DataBase.MarkResourceAsChanged( link.DBId );
        }
			}

			// mark backlined resources as changed
			foreach ( KeyValuePair<DBReference, int> backLink in backLinks )
			{
				backLink.Key.Load();
				DataBase.MarkResourceAsChanged( backLink.Key.DBId );
			}

			// final fix of cache
			cache[oldDbid] = replacingRef;

			// fix inner name and resource
			this.dbid = dbid;

      foreach ( var state in states.Values )
      {
        if ( state != null )
          state.Rename( dbid );
      }

      // fix fields with SrcFile and DstFile attributes (also move dst files)
      SrcFileNameFixer srcFileNameFixer = new SrcFileNameFixer( dbid );
      foreach ( var state in states.Values )
        FieldsWalker.VisitFields<SrcFile, SrcFileAttribute>( resource, srcFileNameFixer.Functor, depthController.Functor );

			dstFileNameFixer.StartFix();
      foreach ( var state in states.Values )
  			FieldsWalker.VisitFields<string, DstFileAttribute>( resource, dstFileNameFixer.Functor, depthController.Functor );
			dstFileNameFixer.DoFix( true );

			DataBase.RenameCallback( dbid, oldDbid );

      return overwrittenRef;
    }

		internal void ChangeResource( DBResource _resource )
		{
      states.Clear();
			states.Add( String.Empty, _resource );
			resource.Rename( dbid );
			DataBase.MarkResourceAsChanged( dbid );
		}

		internal void Inline( Guid _guid )
		{
			if ( backLinks.Count != 1 )
				return;

			DBID ownerDBID = null;

			using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Inline" ) )
			{
				foreach ( KeyValuePair<DBReference, int> backLink in backLinks )
				{
					if ( backLink.Value != 1 )
						return;

					ownerDBID = backLink.Key.DBId;
				}

				Guid guid = _guid == Guid.Empty ? Guid.NewGuid() : _guid;
				DBID newDbid = DBID.FromFileName( ownerDBID.FileName, guid );
				Rename( newDbid, null );

				RemoveBackLink( ownerDBID );
			
				trans.Commit();
			}

			DataBase.MarkResourceAsChanged( ownerDBID );
		}

		internal void Uninline( DBID _ownerDBID, DBID _newDBID )
		{
			if ( _newDBID == null )
				return;

			using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Uninline" ) )
			{
				// fix backlinks
				Rename( _newDBID, null );
				AddBackLink( _ownerDBID );			
				trans.Commit();
			}

			DataBase.MarkResourceAsChanged( _ownerDBID );
		}

		internal void Delete()
		{
			using(UndoRedoTransaction trans = new UndoRedoTransaction("Delete DBReference"))
			{
				FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All );
				RemoveObsoleteLinks linksRemover = new RemoveObsoleteLinks( dbid );
				List<DBReference> backLinkedResources = new List<DBReference>( backLinks.Keys );
				foreach ( DBReference backLink in backLinkedResources )
				{
					FieldsWalker.VisitFields( DataBase.Get<DBResource>( backLink.DBId ), linksRemover.Functor, depthController.Functor );
					DataBase.MarkResourceAsChanged( backLink.DBId );
				}

				if ( DBId.IsInlined )
				{
					DBID fullDbid = DBID.FromDBID( DBId, false );
					FieldsWalker.VisitFields( DataBase.Get<DBResource>( fullDbid ), linksRemover.Functor, depthController.Functor );
					DataBase.MarkResourceAsChanged( fullDbid );
				}

				RemoveStateResource( resource );
				foreach ( var state in states.Values )
					RemoveStateResource( state );

				cache[dbid] = null;
				isDeletedResource = true;
				states.Clear();
				
				trans.Commit();
			}

			DataBase.DeleteCallback( dbid );
		}

    private class PtrRepointCollector
    {
      private DBID oldDbid = null;
      private DBID newDbid = null;

      public bool Functor( ref DBPtrBase ptr )
      {
        if ( ptr.DBId != oldDbid )
          return true;

        DBPtrBase newPtr = TypeUtils.CreateInstance( ptr.GetType() ) as DBPtrBase;
        newPtr.Set( newDbid );
        ptr = newPtr;
        return true;
      }

      public PtrRepointCollector( DBID _oldDbid, DBID _newDbid ) { oldDbid = _oldDbid; newDbid = _newDbid; }
    }

    internal void RepointLinks( DBID dbid )
    {
      DBID oldDbid = DBId;
      if ( oldDbid == dbid )
        return;
      Get<DBResource>();

      List<DBResource> changeList = new List<DBResource>();
      foreach ( KeyValuePair<DBReference, int> backLink in backLinks )
      {
        backLink.Key.Load();
        foreach ( KeyValuePair<string, DBResource> item in backLink.Key.states )
          changeList.Add( item.Value );
      }

      FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All );
      PtrRepointCollector collector = new PtrRepointCollector( oldDbid, dbid );
      foreach ( DBResource link in changeList )
      {
       FieldsWalker.VisitFields<DBPtrBase>( link, collector.Functor, depthController.Functor );
      }
    }

    internal bool IsBacklinkCompatible( Type dstType )
    {
      Get<DBResource>();

      FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All );
      foreach ( KeyValuePair<DBReference, int> backLink in backLinks )
      {
        backLink.Key.Load();
        DBPtrBase[] links = FieldsWalker.CollectDBPtrs( backLink.Key.states.Values, depthController.Functor );

        foreach ( DBPtrBase link in links )
        {
          if ( link.DBId != DBId )
            continue;

          Type linkType = TypeUtils.GetTypeFromPtr( link.GetType() );
          if ( !TypeUtils.IsSubclassOf( dstType, linkType ) )
            return false;
        }
      }

      return true;
    }

    private void RemoveStateResource( DBResource resState )
    {
      FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All );
      RemoveObsoleteLinks linksRemover = new RemoveObsoleteLinks( dbid );

      FieldsWalker.VisitFields( resState, linksRemover.FunctorAll, depthController.Functor );
    }

		internal DBID DBId { get { return dbid; } }

		internal event EventHandler Changed;

    #region Data states support

    internal Dictionary<string, DBResource> States { get { return states; } }

    internal bool CanHasStates()
    {
      return resource != null && TypeUtils.HasAttribute<HasStatesAttribute>( resource.GetType(), true ); 
    }

    internal DBResource AddState( string stateName )
    {
      if ( !CanHasStates() || String.IsNullOrEmpty( stateName ) )
        return null;

      if ( states.ContainsKey( stateName ) )
        return null;

      Type objectType = resource.GetType();
      ConstructorInfo defaultConstructor = objectType.GetConstructor( Type.EmptyTypes );
      DBResource obj = (DBResource)defaultConstructor.Invoke( null );
      resource.Rename( dbid );
      resource.Changed += FireChangedEvent;
      states.Add( stateName, obj );

      return obj;
    }

    internal void RemoveState( string stateName )
    {
      if ( !CanHasStates() || String.IsNullOrEmpty( stateName ) )
        return;

      if ( !states.ContainsKey( stateName ) )
        return;

      //RemoveStateResource( states[stateName] );
      states.Remove( stateName );
    }

    internal void RestoreState( string stateName, DBResource storedState )
    {
      if ( !CanHasStates() || String.IsNullOrEmpty( stateName ) || null == storedState || states.ContainsKey( stateName ) )
        return;

      states.Add( stateName, storedState );
    }

    internal void RenameState( string oldStateName, string stateName )
    {
      if ( !CanHasStates() || String.IsNullOrEmpty( oldStateName ) || String.IsNullOrEmpty( stateName )
        || states.ContainsKey( stateName ) || !states.ContainsKey( oldStateName ) )
        return;

      DBResource state = states[oldStateName];
      states.Remove( oldStateName );
      states[stateName] = state;
      state.SetStateName( stateName );
    }

    internal void LoadStates( Dictionary<string, DBResource> states )
    {
      if ( !CanHasStates() )
        return;

      foreach ( var state in states )
      {
        this.states.Add( state.Key, state.Value );
      }

    }

    #endregion

		#region Static methods to provide DBReference cache functionality

		private static Dictionary<DBID, DBReference> cache = new Dictionary<DBID, DBReference>();
 
		public static bool IsExist( DBID dbid )
		{
			DBReference reference = null;
      if ( cache.TryGetValue( dbid, out reference ) )
        return !ReferenceEquals( reference, null );

			FileInformation info = DataBase.FileSystem.GetFileInfo( dbid.GetFullFileName() );
			return info.IsFileExists;
		}

    public static DBReference Get( DBID dbid )
    {
			if ( DBID.IsNullOrEmpty( dbid ) )
        return null;

      DBReference reference = null;
      if ( cache.TryGetValue( dbid, out reference ) )
        return reference;

			lock ( cache )
			{
			  if ( !cache.TryGetValue( dbid, out reference ) )
			  {
			    reference = new DBReference( dbid );
			    cache.Add( dbid, reference );
			  }
			}
      return reference;
    }

		public static DBReference Create( DBID dbid, DBResource resource )
		{
      if ( DBID.IsNullOrEmpty( dbid ) || resource == null )
				return null;

      DBReference reference = null;
      if ( cache.TryGetValue( dbid, out reference ) && !ReferenceEquals( reference, null ) )
      {
        if ( Log.Assert( ReferenceEquals( reference.resource, null ) || ReferenceEquals( reference.resource, resource ), "Resource \"{0}\" already cached and its differ from specified", dbid.Name ) )
          return null;
      }

      reference = new DBReference( dbid );
      lock( cache )
      {
        cache[dbid] = reference;
      }

      reference.states[ String.Empty ] = resource;
      reference.isDeletedResource = false;
			resource.Rename( dbid );
			return reference;
		}

		public static void Reset()
		{
			cache.Clear();
		}

		#endregion

  }
}

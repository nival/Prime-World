using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using libdb.UndoRedo;

namespace libdb.DB
{
  public abstract class DBPtrBase : ISerializable, IBasicDBValue
  {
    #region Private members.

    private class DBPtrAttributes
    {
      public string href = string.Empty;
      public string id = string.Empty;

      public DBPtrAttributes() { }
      public DBPtrAttributes( DBID dbid )
      {
        href = dbid.FileName;
        id = dbid.Id;
      }

      public DBID ToDBID()
      {
        Guid guidId;
        if ( id != string.Empty && TypeUtils.TryParse( id, out guidId ) )
        {
          return new DBID( href, guidId );
        }
        else
        {
          return new DBID( href, Guid.Empty );
        }
      }
    }

    private readonly DBResource owner = null;
    private DBReference __reference = null;

    private DBPtrBase parent = null;
    internal DBPtrBase Parent { get { return parent; } }
    private bool isDerivedFromParent = true;
    private DBReference reference
    {
      get
      {
        if ( parent != null && isDerivedFromParent )
        {
          return parent.reference;
        }
        return __reference;
      }
      set
      {
        __reference = value;
        isDerivedFromParent = false;
      }
    }

    string defaultState = string.Empty;
    #endregion

    #region Initialization.

    protected DBPtrBase( DBResource owner )
    {
      this.owner = owner;
    }

    protected DBPtrBase( DBID reference, DBResource resource )
    {
      if ( !reference.IsEmpty )
      {
        if ( resource != null && resource.DBId.IsEmpty )
          this.reference = DBReference.Create( reference, resource );
        else
          this.reference = DBReference.Get( reference );

        if ( this.reference != null )
          this.reference.Changed += FireChangedEvent;
      }
    }

    protected DBPtrBase( DBID reference, DBResource resource, DBResource owner )
      : this( reference, resource )
    {
      this.owner = owner;
    }

    #endregion

    #region Public methods.

    public bool CanInline()
    {
      Dictionary<DBID, int> backlinks = GetBackLinks();
      if ( DBId.IsInlined || backlinks == null || backlinks.Count != 1 || reference.States.Keys.Count != 1 )
        return false;

      int count = 0;
      foreach ( int c in backlinks.Values )
        count += c;

      return count == 1;
    }

    public void CollectLinks( out Dictionary<DBID, int> links, out Dictionary<DBID, int> backlinks )
    {
      backlinks = GetBackLinks();
      links = GetLinks();
    }

    public void CheckLinks( Dictionary<DBID, int> backlinks )
    {
      foreach ( KeyValuePair<DBID, int> bl in backlinks )
      {
        if ( bl.Value < 0 )
        {
          for ( int i = 0; i > bl.Value; i-- )
          {
            reference.AddBackLink( bl.Key );
          }
        }
        else
        {
          for ( int i = 0; i < bl.Value; i++ )
          {
            reference.RemoveBackLink( bl.Key );
          }
        }
      }
    }

    public void ClearBackLinks()
    {
      Dictionary<DBID, int> backlinks = GetBackLinks();
      foreach ( KeyValuePair<DBID, int> pair in backlinks )
      {
        for ( int i = 0; i < pair.Value; i++ )
        {
          this.reference.RemoveBackLink( pair.Key );
        }
      }
    }

    public void SetBacklinks( IEnumerable<KeyValuePair<DBID, int>> backlinks )
    {
      reference.SetBacklinks( backlinks );
      DataBase.MarkResourceAsChanged( DBId );
    }

    public void Uninline( DBID _newDBID )
    {
      if ( owner != null )
      {
        reference.Uninline( owner.DBId, _newDBID );
      }
      else
      {
        Log.TraceError( "Inlined object \"{0}\" doesn't have owner", reference.DBId );
      }
    }

    public void Set( DBID _dbid )
    {
			using ( UndoRedoTransaction trans = new UndoRedoTransaction( string.Format( "Changed DBPtr from \"{0}\" to \"{1}\"", reference!= null ? reference.DBId : DBID.Empty, _dbid ) ) )
			{
				SetInternal( _dbid );	
				trans.Commit();
			}    	
    }

  	private void SetInternal(DBID _dbid)
  	{
  		if ( !isDerivedFromParent && !ReferenceEquals( this.reference, null ) )
  		{
  			this.reference.Changed -= FireChangedEvent;
  			if ( !ReferenceEquals( owner, null ) && !owner.DBId.IsEmpty )
  			{
  				this.reference.RemoveBackLink( DBID.FromDBID( owner.DBId, false ) );
  			}

				if ( _dbid.IsEmpty && this.reference.DBId.IsInlined )
				{
					DataBase.RemoveBacklinksTo(reference.Get<DBResource>());
				}
  		}

  		this.reference = DBReference.Get( _dbid );

  		if ( !ReferenceEquals( this.reference, null ) )
  		{
  			this.reference.Changed += FireChangedEvent;
  			if ( !ReferenceEquals( owner, null ) && !owner.DBId.IsEmpty && !this.reference.DBId.IsEmpty && !this.reference.DBId.IsInlined )
  			{
  				this.reference.AddBackLink( DBID.FromDBID( owner.DBId, false ) );
  			}
  		}
  	}

    public T Get<T>() where T : DBResource
    {
      if ( reference == null )
        return null;

      return reference.Get<T>( defaultState );
    }

    public Dictionary<DBID, int> GetBackLinks()
    {
      if ( reference == null )
        return new Dictionary<DBID, int>();

      return reference.GetBackLinks();
    }

    public Dictionary<DBID, int> GetLinks()
    {
      if ( reference == null )
        return null;

      FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All );
      DBPtrBase[] ptrs = FieldsWalker.CollectDBPtrs( Get<DBResource>(), depthController.Functor );
      Dictionary<DBID, int> links = new Dictionary<DBID, int>();
      foreach ( DBPtrBase ptr in ptrs )
      {
        if ( links.ContainsKey( ptr.DBId ) )
          ++links[ptr.DBId];
        else
          links.Add( ptr.DBId, 1 );
      }

      return links;
    }

    public void RestoreBackLinks()
    {
      //reference.RestoreBackLinks();
    }

    public void Inline( Guid guid )
    {
      if ( !CanInline() )
      {
        Log.TraceError( "Object \"{0}\" cannot be inlined", DBId );
        return;
      }

      if ( reference != null )
      {
        reference.Inline( guid );
      }
      else
      {
        Log.TraceError( "Uninlided object \"{0}\" doesn't have owner or reference", reference != null ? reference.DBId : null );
      }
    }

    public void Store()
    {
      Store( false );
    }

    public void Store( bool gameDataOnly )
    {
      DBResource res = Get<DBResource>();
      if ( Log.Assert( res != null, "Attempt to store unexists resource \"{0}\"", DBId ) )
        return;

      XmlContextWriter writer = XmlContextWriter.Create( DataBase.FileSystem, DBId );
      if ( writer == null )
      {
        Log.TraceError( "Cannot serialize resource \"{0}\"", DBId.Name );
        return;
      }

      if ( gameDataOnly )
        DBXmlSerializer.Serialize( writer, this, new Type[] { typeof( NoCodeAttribute ) }, false );
      else
        DBXmlSerializer.Serialize( writer, this );

      writer.Close();
    }

    #endregion

    #region Public properties.

    public DBID DBId
    {
      get { return reference == null ? DBID.Empty : reference.DBId; }
    }

    public DBResource GetOwner() { return owner; }

    public bool IsValid
    {
      get { return !this.DBId.IsEmpty; }
    }

    #endregion

    #region Public events.

    public event EventHandler Changed;

    #endregion

    #region Internal methods.

    internal void ChangeResource( DBResource resource )
    {
      if ( !ReferenceEquals( reference, null ) )
      {
        reference.ChangeResource( resource );
      }
    }

    internal DBResource GetDBResource()
    {
      if ( reference == null )
        return null;

      return reference.GetDBResource();
    }

    internal DBReference Rename( DBID dbid, DBReference replacingRef )
    {
      if ( reference != null && reference.DBId != dbid )
        return reference.Rename( dbid, replacingRef );

      return null;
    }

    internal void Delete()
    {
      if ( reference != null )
        reference.Delete();
    }

    internal bool IsEqual( DBPtrBase source ) { return DBId == source.DBId; }

    internal void RepointLinks( DBID dbid )
    {
      if ( reference != null && reference.DBId != dbid )
        reference.RepointLinks( dbid );
    }

    internal bool IsBacklinkCompatible( Type dstType )
    {
      if ( reference != null )
        return reference.IsBacklinkCompatible( dstType );

      return false;
    }

    #endregion

    #region Overrides.

    public override bool Equals( object obj )
    {
      DBPtrBase ptr = obj as DBPtrBase;
      if ( ptr == null )
        return false;

      return this.DBId == ptr.DBId;
    }

    public override int GetHashCode()
    {
      return DBId.GetHashCode();
    }

    public override string ToString()
    {
      return this.DBId.Name;
    }

    #endregion

    #region Private helper methods.

    private void FireChangedEvent( object sender, EventArgs e )
    {
      if ( Changed != null )
      {
        Changed( sender, e );
      }
    }

    #endregion

    public void Serialize( out object nestedObject, out object attributes )
    {
      attributes = new DBPtrAttributes( DBId );
      nestedObject = DBId.IsInlined ? GetDBResource() : null;
    }

    public Type GetAttributesType()
    {
      return typeof( DBPtrAttributes );
    }

    public bool DeserializeAttributes( XmlSerializer serializer, object attributes, out Type nestedObjectType )
    {
      nestedObjectType = null;
      DBPtrAttributes dbPtrAttributes = attributes as DBPtrAttributes;
      if ( dbPtrAttributes == null )
        return false;

      //DBXmlSerializer dbSerializer = serializer as DBXmlSerializer;
      if ( serializer == null )
        return false;

      DBID dbid = dbPtrAttributes.ToDBID();
      if ( DBID.IsNullOrEmpty( dbid ) || !dbid.IsInlined )
        reference = DBReference.Get( dbid );
      else
        nestedObjectType = typeof( DBResource ); //TODO: ask derived object for nested resource type
      return true;
    }

    public bool DeserializeNestedObject( XmlSerializer serializer, object attributes, object nestedObject )
    {
      DBPtrAttributes dbPtrAttributes = attributes as DBPtrAttributes;
      if ( dbPtrAttributes == null )
        return false;

      //DBXmlSerializer dbSerializer = serializer as DBXmlSerializer;
      if ( serializer == null )
        return false;

      DBResource resource = nestedObject as DBResource;
      if ( resource == null )
        return false;

      reference = DBReference.Create( dbPtrAttributes.ToDBID(), resource );
      return true;
    }

    public void Assign( object source )
    {
      if ( source is DBPtrBase )
        Set( ( source as DBPtrBase ).DBId );
      else if ( source == null )
        reference = null;
    }

    protected abstract void OnSetParent( DBPtrBase parent );

    public void SetParent( object _parent )
    {
      DBPtrBase parent = _parent as DBPtrBase;
      OnSetParent( parent );
      this.parent = parent;
    }

    public void Reset()
    {
      if ( !isDerivedFromParent )
      {
        isDerivedFromParent = true;
        FireChangedEvent( this, EventArgs.Empty );
      }
    }

    public bool IsDerivedFromParent()
    {
      return parent == null || isDerivedFromParent;
    }

    #region Data states support

    public T Get<T>( string stateName ) where T : DBResource
    {
      if ( reference == null )
        return null;
      return reference.Get<T>( stateName );
    }

    public List<String> GetStates()
    {
      if ( reference == null )
        return null;

      return new List<String>( reference.States.Keys );
    }

    public bool HasStates { get { return reference.States.Keys.Count != 1; } }

    public void AddState( string stateName )
    {
      if ( reference == null )
        return;

      if ( DBId.IsInlined )
      {
        Log.TraceWarning( "Inlined objects can not have states" );
        return;
      }

      DataBase.AddOperation( new libdb.UndoRedo.AddStateOperation( DBId, stateName ) );
    }

    internal void AddStateInternal( string stateName )
    {
      if ( reference == null )
        return;

      DBResource newObj = reference.AddState( stateName );
      if ( newObj == null )
        return;

      ICompositeDBValue parentableObj = newObj as ICompositeDBValue;
      parentableObj.SetParent( this );
      newObj.SetStateName( stateName );
      newObj.Rename( DBId );
    }

    public void RemoveState( string stateName )
    {
      if ( reference == null )
        return;

      DataBase.AddOperation( new libdb.UndoRedo.RemoveStateOperation( DBId, stateName ) );
    }

    internal void RemoveStateInternal( string stateName )
    {
      if ( reference == null )
        return;

      if ( defaultState == stateName )
        defaultState = string.Empty;

      reference.RemoveState( stateName );
    }

    internal void RestoreStateInternal( string stateName, DBResource storedState )
    {
      if ( reference == null )
        return;

      reference.RestoreState( stateName, storedState );
    }

    public void RenameState( string oldStateName, string stateName )
    {
      if ( reference == null )
        return;

      DataBase.AddOperation( new libdb.UndoRedo.RenameStateOperation( DBId, oldStateName, stateName ) );
    }

    internal void RenameStateInternal( string oldStateName, string stateName )
    {
      if ( reference == null )
        return;

      reference.RenameState( oldStateName, stateName );
    }

    internal void LoadStates( Dictionary<string, DBResource> states )
    {
      if ( reference == null )
        return;

      foreach ( var state in states )
      {
        ICompositeDBValue parentableObj = state.Value as ICompositeDBValue;
        if ( parentableObj == null )
          continue;

        parentableObj.SetParent( this );
        state.Value.SetStateName( state.Key );
        state.Value.Rename( DBId );
      }

      reference.LoadStates( states );
    }

    public string DefaultState
    {
      get { return defaultState; }
      set
      {
        if ( reference != null && reference.States.ContainsKey( value ) )
          defaultState = value;
        else
          defaultState = string.Empty;
      }
    }

    #endregion
  }
}

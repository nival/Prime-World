using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using libdb.DB;
using libdb.Diagnostics;

namespace libdb.UndoRedo
{
  public abstract class UndoRedoListBase<T> : IChangeableList<T>, IList, IOwnerable
  {

    #region Data members.

    private readonly List<T> list = new List<T>();
    private readonly Type enumType = null;
    private readonly DBResource owner = null;
    private IChangeableList<T> parent = null;

    protected int minCount = 0;
    protected int maxCount = 0;

    protected List<T> Storage { get { return list; } }
    protected IChangeableList<T> Parent { get { return parent; } }

    #endregion

    #region Initialization.

    public UndoRedoListBase()
    {
    }

    public UndoRedoListBase( DBResource owner )
    {
      this.owner = owner;
    }

    public UndoRedoListBase( DBResource owner, int minCount, int maxCount )
    {
      this.owner = owner;
      this.minCount = minCount;
      this.maxCount = maxCount;

      InitMinCount();
    }

    public UndoRedoListBase( DBResource owner, Type enumType )
    {
      this.owner = owner;
      if ( enumType == null || !enumType.IsEnum )
      {
        Log.TraceError( enumType.ToString() + " is not Enum" );
      }
      else
      {
        this.enumType = enumType;
        minCount = Enum.GetValues( enumType ).Length;
        maxCount = minCount;

        InitMinCount();
      }
    }

    #endregion

    #region IRichList

    public Type EnumType
    {
      get { return enumType; }
    }

    public bool CanAdd
    {
      get { return ( maxCount == 0 ) || list.Count < maxCount; }
    }

    public bool CanDelete
    {
      get { return ( list.Count > minCount ); }
    }

    public bool CanInsert
    {
      get { return CanAdd; }
    }

    public bool CanMoveItems
    {
      get { return true; }
    }

    public int MinCount
    {
      get { return minCount; }
    }

    public int MaxCount
    {
      get { return maxCount; }
    }
    #endregion

    #region Own public methods and properties.

    public void SetOrAdd( int index, T value )
    {
      if ( index >= Storage.Count )
        if ( maxCount > 0 && index > maxCount )
          return;

      EnsureElementExist( index );
      this[index] = value;
    }

    #endregion

    #region Overridables

    virtual protected T CreateItem()
    {
      Type t = typeof( T );
      if ( TypeUtils.IsResourceType( t ) || TypeUtils.IsSimpleType( t ) )
      {
        if ( t == typeof( string ) )
          return (T)( string.Empty as object );
        else
          return default( T );
      }

      ConstructorInfo constructor = typeof( T ).GetConstructor( new Type[1] { typeof( DBResource ) } );
      if ( constructor == null )
        return default( T );

      return (T)constructor.Invoke( new object[1] { GetOwner() } );
    }

    protected abstract void DoAdd( T item );
    protected abstract void DoInsert( int index, T item );
    protected abstract void DoRemoveAt( int index );
    protected abstract void DoSet( int index, T item );
    protected abstract T DoGet( int index );
    protected abstract void DoAddDefaultElement();
    public abstract int IndexOf( T item );

    #endregion

    #region Methods to support UndoRedoOperations

    internal void InsertInternal( int index, T item )
    {
      if ( index == Storage.Count )
      {
        if ( !CanAdd )
        {
          Log.TraceError( string.Format( "maxCount is {0}", maxCount ) );
          return;
        }

        DoAdd( item );
      }
      else
      {
        if ( !CanInsert )
        {
          Log.TraceError( string.Format( "maxCount is {0}", maxCount ) );
          return;
        }

        DoInsert( index, item );
      }

      FireItemAddedEvent( index );
      FireChangedEvent();
    }

    internal void RemoveAtInternal( int index )
    {
      if ( !CanDelete )
      {
        Log.TraceError( string.Format( "minCount is {0}", minCount ) );
        return;
      }
      FireBeforeItemRemovedEvent( index );

      DoRemoveAt( index );

      FireChangedEvent();
    }

    internal bool RemoveInternal( T item )
    {
      int index = IndexOf( item );
      if ( index >= 0 )
      {
        RemoveAtInternal( index );
        return true;
      }

      return false;
    }

    internal void AddInternal( T item )
    {
      if ( !CanAdd )
      {
        Log.TraceError( string.Format( "maxCount is {0}", maxCount ) );
        return;
      }

      DoAdd( item );

      FireItemAddedEvent( Storage.Count - 1 );
      FireChangedEvent();
    }

    internal virtual void SetInternal( int index, T item )
    {
      FireItemBeforeChangedEvent( index );

      DoSet( index, item );

      FireItemChangedEvent( index );
      FireChangedEvent();
    }

    internal virtual void ClearInternal()
    {
      while ( Storage.Count > 0 )
      {
        FireBeforeItemRemovedEvent( Storage.Count - 1 );
        DoRemoveAt( Storage.Count - 1 );
        FireChangedEvent();
      }
      InitMinCount();
    }

    #endregion

    #region FireEvent helpers.

    protected void FireChangedEvent()
    {
      if ( Changed != null )
      {
        Changed( this, EventArgs.Empty );
      }
    }

    protected void FireItemAddedEvent()
    {
      FireItemAddedEvent( Storage.Count - 1 );
    }

    protected void FireItemAddedEvent( int index )
    {
      if ( ListItemAdded != null )
      {
        ListItemAdded( this, new ListItemAddedEventArgs<T>() { Index = index, Item = Storage[index] } );
      }
    }

    protected void FireBeforeItemRemovedEvent( int index )
    {
      if ( ListItemBeforeRemoved != null )
      {
        ListItemBeforeRemoved( this, new ListItemBeforeRemovedEventArgs<T>() { Index = index, Item = this[index] } );
      }
    }

    protected void FireItemChangedEvent( int index )
    {
      if ( ListItemChanged != null )
      {
        ListItemChanged( this, new ListItemChangedEventArgs<T>() { Index = index, NewValue = Storage[index] } );
      }
    }

    protected void FireItemBeforeChangedEvent( int index )
    {
      if ( ListItemBeforeChanged != null )
      {
        ListItemBeforeChanged( this, new ListItemBeforeChangedEventArgs<T>() { Index = index, PrevValue = Storage[index] } );
      }
    }

    #endregion

    #region Helper methods.

    private void InitMinCount()
    {
      EnsureElementExist( minCount - 1 );
    }

    protected void EnsureElementExist( int size )
    {
      if ( Storage.Count > size )
        return;
      for ( int i = Storage.Count; i <= size; ++i )
      {
        DoAddDefaultElement();
        FireItemAddedEvent();
      }
    }

    private void Subscribe()
    {
      if ( parent == null )
        return;
      parent.ListItemAdded += OnParentItemAdded;
      parent.ListItemBeforeRemoved += OnParentItemBeforeRemoved;
      parent.ListItemChanged += OnParentItemChanged;
    }

    private void Unsubscribe()
    {
      if ( parent == null )
        return;
      parent.ListItemAdded -= OnParentItemAdded;
      parent.ListItemBeforeRemoved -= OnParentItemBeforeRemoved;
      parent.ListItemChanged -= OnParentItemChanged;
    }


    #endregion

    #region IChangeableList<T> Members

    public event EventHandler<ListItemAddedEventArgs<T>> ListItemAdded;
    public event EventHandler<ListItemBeforeRemovedEventArgs<T>> ListItemBeforeRemoved;
    public event EventHandler<ListItemChangedEventArgs<T>> ListItemChanged;
    public event EventHandler<ListItemBeforeChangedEventArgs<T>> ListItemBeforeChanged;

    #endregion

    #region IChangeable Members

    public event EventHandler Changed;

    #endregion

    #region IList<T> Members

    public void Insert( int index, T item )
    {
      if ( !CanAdd )
      {
        Log.TraceError( string.Format( "maxCount is {0}", maxCount ) );
        return;
      }

      if ( owner != null && !owner.DBId.IsEmpty )
        DataBase.AddOperation( new InsertItemListOperation<T>( this, index, item ) );
      else
        InsertInternal( index, item );
    }

    public void RemoveAt( int index )
    {
      if ( !CanDelete )
      {
        Log.TraceError( string.Format( "minCount is {0}", minCount ) );
        return;
      }

      if ( owner != null && !owner.DBId.IsEmpty )
        DataBase.AddOperation( new RemoveAtItemListOperation<T>( this, index ) );
      else
        this.RemoveAtInternal( index );
    }

    #endregion

    #region ICollection<T> Members

    public void Add( T item )
    {
      Insert( Storage.Count, item );
    }

    public void Clear()
    {
      if ( owner != null && !owner.DBId.IsEmpty )
        DataBase.AddOperation( new ClearListOperation<T>( this ) );
      else
        ClearInternal();
    }

    public bool Contains( T item )
    {
      return list.Contains( item );
    }

    public void CopyTo( T[] array, int arrayIndex )
    {
      list.CopyTo( array, arrayIndex );
    }

    public int Count { get { return list.Count; } }

    public bool IsReadOnly { get { return false; } }

    public bool Remove( T item )
    {
      int index = Storage.IndexOf( item );
      if ( index < 0 )
        return false;

      RemoveAt( index );
      return true;
    }

    public virtual T this[int index]
    {
      get
      {
        return DoGet( index );
      }
      set
      {
        if ( owner != null && !owner.DBId.IsEmpty )
          DataBase.AddOperation( new ChangeItemListOperation<T>( this, index, value ) );
        else
          SetInternal( index, value );
      }
    }

    #endregion

    #region Enumerator and IEnumerable<T> Members

    public IEnumerator<T> GetEnumerator() 
    { 
        for (int i=0; i<Count; i++)
        {
            yield return this[i];
        }
    }

    System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() 
    {
      return GetEnumerator(); 
    }

    #endregion

    #region IOwnerable Members

    public DBResource GetOwner() { return owner; }

    #endregion

    #region IBasicDBValue Members

    protected abstract void OnParentItemAdded( object sender, ListItemAddedEventArgs<T> e );
    protected abstract void OnParentItemBeforeRemoved( object sender, ListItemBeforeRemovedEventArgs<T> e );
    protected abstract void OnParentItemChanged( object sender, ListItemChangedEventArgs<T> e );

    public virtual void SetParent( object _parent )
    {
      IChangeableList<T> parent = _parent as IChangeableList<T>;
      if ( parent == this.parent )
        return;

      if ( parent == null )
      {
        if ( TypeUtils.IsSubclassOf( typeof( T ), typeof( IBasicDBValue ) ) )
        {
          for ( int i = 0; i < list.Count; ++i )
            ( list[i] as IBasicDBValue ).SetParent( null );
        }
        return;
      }

      Unsubscribe();
      this.parent = parent;
      EnsureElementExist( parent.Count - 1 );
      Subscribe();

      if ( TypeUtils.IsSubclassOf( typeof( T ), typeof( IBasicDBValue ) ) )
      {
        for ( int i = 0; i < parent.Count; ++i )
          ( list[i] as IBasicDBValue ).SetParent( parent[i] );
      }
    }

    public abstract void Reset();
    public abstract void Assign( object _source );
    public abstract bool IsDerivedFromParent();
    public abstract void ResetElement( int index );
    public abstract bool IsElementDerivedFromParent( int index );

    #endregion

    #region IList Members

    int IList.Add( object value )
    {
      Add( (T)value );
      return Count - 1;
    }

    bool IList.Contains( object value )
    {
      return Contains( (T)value );
    }

    int IList.IndexOf( object value )
    {
      return IndexOf( (T)value );
    }

    void IList.Insert( int index, object value )
    {
      Insert( index, (T)value );
    }

    bool IList.IsFixedSize
    {
      get { return false; }
    }

    void IList.Remove( object value )
    {
      Remove( (T)value );
    }

    object IList.this[int index]
    {
      get
      {
        return this[index];
      }
      set
      {
        this[index] = (T)value;
      }
    }

    #endregion

    #region ICollection Members

    void ICollection.CopyTo( Array array, int index )
    {
      ((IList)list).CopyTo( array, index );
    }

    bool ICollection.IsSynchronized
    {
      get { return false; }
    }

    object ICollection.SyncRoot
    {
      get { return sync; }
    }

    private readonly object sync = new object();

    #endregion
  }
}

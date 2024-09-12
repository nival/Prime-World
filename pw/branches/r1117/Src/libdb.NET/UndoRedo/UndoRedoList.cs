using System;
using System.Collections.Generic;
using libdb.DB;
using libdb.Diagnostics;

namespace libdb.UndoRedo
{
  public sealed class UndoRedoList<T> : UndoRedoListBase<T>
	{
    private readonly List<bool> fromParent = new List<bool>();

		#region Initialization.

		public UndoRedoList() : base()
		{
      Log.TraceError( "new()" );
		}

    public UndoRedoList( DBResource owner )
      : base( owner )
		{
		}

    public UndoRedoList( DBResource owner, int minCount, int maxCount )
      : base( owner, minCount, maxCount )
		{
		}

		public UndoRedoList( DBResource owner, Type enumType )
      : base( owner, enumType )
		{
		}

		#endregion

    #region Overridables


    private T SafeGetFromParent( int index )
    {
      if ( Parent != null && index < Parent.Count )
        return Parent[index];
      else
        return CreateItem();
    }

    #endregion

    protected override void DoAdd( T item )
    {
      Storage.Add( item );
      fromParent.Add( false );
    }
    protected override void DoInsert( int index, T item )
    {
      for ( int i = index; i < Count; ++i )
      {
        if ( fromParent[i] )
        {
          Storage[i] = SafeGetFromParent( i );
          fromParent[i] = false;
        }
      }

      Storage.Insert( index, item );
      fromParent.Insert( index, false );
    }

    protected override void DoRemoveAt( int index )
    {
      Storage.RemoveAt( index );
      fromParent.RemoveAt( index );
      for ( int i = index; i < Storage.Count; ++i )
      {
        if ( fromParent[i] )
        {
          Storage[i] = SafeGetFromParent( i );
          fromParent[i] = false;
        }
      }
    }

    protected override void DoSet( int index, T item )
    {
      Storage[index] = item;
      fromParent[index] = false;

    }
    protected override T DoGet( int index )
    {
      if ( Parent != null && fromParent[index] )
      {
        return SafeGetFromParent( index );
      }
      return Storage[index];
    }
    protected override void DoAddDefaultElement()
    {
      Storage.Add( CreateItem() );
      fromParent.Add( true );
    }

    public override int IndexOf( T item )
    {
      int index = Storage.IndexOf( item );
      if ( index < 0 && Parent != null )
        index = Parent.IndexOf( item );
      return index;
    }

    #region Parent list change notification

    override protected void OnParentItemAdded( object sender, ListItemAddedEventArgs<T> e )
    {
      if ( ( Parent.Count - 1 ) >= Count )
      {
        Storage.Add( Parent[Parent.Count - 1] );
        fromParent.Add( true );
        FireItemAddedEvent( e.Index );
      }
    }

    override protected void OnParentItemBeforeRemoved( object sender, ListItemBeforeRemovedEventArgs<T> e )
    {
      if ( fromParent[fromParent.Count - 1] )
      {
        Storage.RemoveAt( Count - 1 );
        fromParent.RemoveAt( fromParent.Count - 1 );
        FireBeforeItemRemovedEvent( e.Index );
      }
    }

    override protected void OnParentItemChanged( object sender, ListItemChangedEventArgs<T> e )
    {
    }

    #endregion


    #region IBasicDBValue Members

    public override void Reset()
    {
      if ( Parent == null )
        return;

      Clear();
      EnsureElementExist( Parent.Count - 1 );
    }

    public override void Assign( object _source )
    {
      IChangeableList<T> source = _source as IChangeableList<T>;
      if ( source == null )
        return;

      if ( source == this )
        return;

      ClearInternal();

      if ( Storage.Capacity < source.Count )
        Storage.Capacity = source.Count;

      int i = 0;
      foreach ( T item in source )
      {
        SetOrAdd( i++, item );
      }
    }

    public override bool IsDerivedFromParent()
    {
      if ( Parent == null )
        return true;

      if ( Parent.Count != Count )
        return false;

      foreach ( bool par in fromParent )
        if ( !par )
          return false;
      return true;
    }

    public override void ResetElement( int index )
    {
      fromParent[index] = true;
      FireItemChangedEvent( index );
    }

    public override bool IsElementDerivedFromParent( int index )
    {
      return Parent == null || fromParent[index];
    }

    #endregion
  }
}

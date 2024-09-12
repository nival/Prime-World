using System;
using System.Reflection;
using System.Windows.Forms;
using libdb.DB;

namespace libdb.UndoRedo
{
	public sealed class UndoRedoAssignableList<T> : UndoRedoListBase<T> where T : IBasicDBValue
	{
	  private bool maybeBroken = false;

    public bool MayBeBroken()
    {
      return maybeBroken;
    }

    public void FixBroken()
    {
      maybeBroken = false;
    }

		#region Initialization.

		public UndoRedoAssignableList( DBResource owner )	: base( owner )
		{
		}

		public UndoRedoAssignableList( DBResource owner, int minCount, int maxCount ) : base( owner, minCount, maxCount )
		{
		}

		public UndoRedoAssignableList( DBResource owner, Type enumType ) : base( owner, enumType )
		{
		}

		#endregion


    private T SafeGetFromParent( int index )
    {
      if ( index < Parent.Count )
        return Parent[index];
      else
        return CreateItem();
    }

    private T CopyItemForInsert( T source )
    {
      if ( source != null && GetOwner() == source.GetOwner() )
        return source;

      if ( source == null )
        return CreateItem();

      ConstructorInfo constructor = typeof( T ).GetConstructor( new Type[] { typeof( DBResource ), typeof( T ) } );
      return (T)constructor.Invoke( new object[2] { GetOwner(), source } );
    }

    private void AssignItemToHandler( int index, T item )
    {
      if ( Storage[index] == null )
        Storage[index] = CreateItem();

      if ( item == null )
        Storage[index].Assign( CreateItem() );
      else
        Storage[index].Assign( item );
    }

    private void UpdateParents( int fromIndex, int toIndex )
    {
      if ( Parent == null )
        return;

      for ( int i = fromIndex; i < toIndex; ++i )
      {
        if ( i < Parent.Count )
          Storage[i].SetParent( Parent[i] );
        else
          Storage[i].SetParent( null );
      }
    }

    protected override void DoAdd( T item )
    {
      Storage.Add( CopyItemForInsert( item ) );
      UpdateParents( Count - 1, Count );

      if ( GetOwner() != null )
      {
        var obj = DataBase.Get<DBResource>( GetOwner().DBId );
        if( obj.GetBackLinks().Keys.Count > 0 )
        {
          maybeBroken = true;
        }
      }
    }

    protected override void DoInsert( int index, T item )
    {
      Storage.Insert( index, CopyItemForInsert( item ) );
      UpdateParents( index, Count );

      if ( GetOwner() != null )
      {
        var obj = DataBase.Get<DBResource>( GetOwner().DBId );
        if ( obj.GetBackLinks().Keys.Count > 0 )
        {
          maybeBroken = true;
        }
      }
    }

    protected override void DoRemoveAt( int index )
    {
      Storage.RemoveAt( index );
      UpdateParents( index, Count );

      if ( GetOwner() != null )
      {
        var obj = DataBase.Get<DBResource>( GetOwner().DBId );
        if ( obj.GetBackLinks().Keys.Count > 0 )
        {
          maybeBroken = true;
        }
      }
    }

    protected override void DoSet( int index, T item )
    {
      AssignItemToHandler( index, item );
      UpdateParents( index, index + 1 );
    }

    protected override T DoGet( int index )
    {
      return Storage[index];
    }

    protected override void DoAddDefaultElement()
    {
      Storage.Add( CreateItem() );
      UpdateParents( Count - 1, Count );

      if ( GetOwner() != null )
      {
        var obj = DataBase.Get<DBResource>( GetOwner().DBId );
        if ( obj.GetBackLinks().Keys.Count > 0 )
        {
          maybeBroken = true;
        }
      }
    }

    public override int IndexOf( T item )
    {
      return Storage.IndexOf( item );
    }

    #region Parent list change notification

    override protected void OnParentItemAdded( object sender, ListItemAddedEventArgs<T> e )
    {
      EnsureElementExist( Parent.Count - 1 );
      UpdateParents( e.Index, Count );
    }

    override protected void OnParentItemBeforeRemoved( object sender, ListItemBeforeRemovedEventArgs<T> e )
    {
      /*for ( int i = e.Index + 1; i < Storage.Count; ++i )
      {
        if ( Parent.Count <= i )
          break;

        Storage[i - 1].SetParent( Parent[i] );
      }*/
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

      if ( Count != Parent.Count )
        return false;

      foreach ( var item in Storage )
        if ( !item.IsDerivedFromParent() )
          return false;

      return true;
    }

    public override void ResetElement( int index )
    {
      if ( Parent == null )
        return;
          
      Storage[index].Reset();
      FireItemChangedEvent( index );
    }

    public override bool IsElementDerivedFromParent( int index )
    {
      if ( Parent == null )
        return true;
      return index < Parent.Count && Storage[index].IsDerivedFromParent();
    }

    #endregion

	}
}

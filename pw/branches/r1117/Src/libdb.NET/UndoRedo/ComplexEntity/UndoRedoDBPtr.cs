using System;
using libdb.DB;
using libdb.UndoRedo.ComplexEntity;

namespace libdb.UndoRedo
{
	public sealed class UndoRedoDBPtr<T> : IChangeable, IBasicDBValue
		where T: DBResource, new()
	{
		private DBPtr<T> value = null;

		public UndoRedoDBPtr( DBResource owner )
		{
			value = new DBPtr<T>( owner );
			value.Changed += FireChangedEvent;
		}

		public UndoRedoDBPtr( DBResource owner, DBPtr<T> source )
		{
			value = new DBPtr<T>( owner );
			value.Set( source );
      value.Reset();
			value.Changed += FireChangedEvent;
		}

    public DBResource Owner
    {
      get { return value.GetOwner(); }
    }

		public DBPtr<T> Get()
		{
			return value;
		}

    public void Set<T1>( DBPtr<T1> resource ) where T1 : DBResource, new()
		{
			if ( resource == null )
				DataBase.AddOperation( new ChangeDBPtrOperation<T>( this, DBID.Empty ) );
			else
				DataBase.AddOperation( new ChangeDBPtrOperation<T>( this, resource.DBId ) );
		}

		public event EventHandler Changed;

		internal void SetInternal( DBID dbid )
		{
			value.Set( dbid );
			FireChangedEvent( this, EventArgs.Empty );
		}

		private void FireChangedEvent( object sender, EventArgs e )
		{
			if ( Changed != null )
			{
				Changed( sender, e );
			}
		}

    #region IBasicDBValue Members

    internal void ResetInternal()
    {
      value.Reset();
    }

    public void Reset()
    {
      if ( !value.IsDerivedFromParent() )
        DataBase.AddOperation( new ResetDBPtrOperation<T>( this ) );
    }

    public bool IsDerivedFromParent()
    {
      return value.IsDerivedFromParent();
    }

    public void SetParent( object parent )
    {
      UndoRedoDBPtr<T> castParent = parent as UndoRedoDBPtr<T>;
      DBPtr<T> rawParent = ( castParent == null ) ? parent as DBPtr<T> : castParent.value;
      value.SetParent( rawParent );
    }

    public void Assign( object source )
    {
      UndoRedoDBPtr<T> castSource = source as UndoRedoDBPtr<T>;
      DBPtr<T> rawSource = ( castSource == null ) ? source as DBPtr<T> : castSource.value;
      value.Assign( rawSource );
    }

    #endregion

    #region IOwnerable Members

    public DBResource GetOwner()
    {
      return value.GetOwner();
    }

    #endregion
  }
}

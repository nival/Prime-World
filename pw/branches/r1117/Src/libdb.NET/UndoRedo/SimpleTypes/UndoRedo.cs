using System;
using libdb.DB;

namespace libdb.UndoRedo
{
	public sealed class UndoRedo<T> : IChangeable, IBasicDBValue
	{
		private DBResource owner = null;
		private T value;

    private UndoRedo<T> parent = null;
    private bool isInherited = true;

		public UndoRedo( DBResource owner, T value ) { this.owner = owner; this.value = value; }

    public T Get() { return ( parent != null && isInherited ) ? parent.Get() : value; }

		public void Set( T value )
		{
			if ( owner != null && !owner.DBId.IsEmpty )
				DataBase.AddOperation( new ChangeOperation<T>( this, value ) );
			else
				SetInternal( value );
		}

		public DBResource GetOwner() { return owner; }

		public event EventHandler Changed;

		internal void SetInternal( T value )
		{
      this.isInherited = false;
			this.value = value;
			if ( Changed != null )
				Changed( this, EventArgs.Empty );
		}

    internal void ResetInternal()
    {
      if ( parent != null && !isInherited )
      {
        this.isInherited = true;
        if ( Changed != null )
          Changed( this, EventArgs.Empty );
      }
    }

    #region IBasicDBValue Members

    public void Reset()
    {
      if ( parent != null && !isInherited )
      {
        if ( owner != null && !owner.DBId.IsEmpty )
          DataBase.AddOperation( new ResetUndoRedoOperation<T>( this ) );
        else
          SetInternal( value );
      }
    }

    public bool IsDerivedFromParent()
    {
      return ( parent == null || isInherited );
    }

    public void SetParent( object _parent )
    {
      UndoRedo<T> newParent = _parent as UndoRedo<T>;
      parent = newParent;
    }

    public void Assign( object source )
    {
      throw new NotImplementedException();
    }

    #endregion
  }
}

using System;
using System.Collections.Generic;
using System.Text;

namespace libdb.UndoRedo
{
	class ClearListOperation<T> : IUndoRedoOperation 
	{
    private readonly UndoRedoListBase<T> list;
		private readonly T[] oldItems;

    public ClearListOperation( UndoRedoListBase<T> list ) 
		{
			this.list = list;
			oldItems = new T[list.Count];
			list.CopyTo( this.oldItems, 0 );
		}

		public void Undo()
		{
			list.ClearInternal();
			foreach ( T elem in oldItems )
				list.AddInternal( elem );
		}

		public void Redo() { list.ClearInternal(); }

		public libdb.DB.DBResource GetOwner() { return list.GetOwner(); }
		public string DefaultCaption { get { return string.Format( "\"{0}\" clear list \"{1}\"", GetOwner().DBId.Name, list.ToString() ); } }
	}
}

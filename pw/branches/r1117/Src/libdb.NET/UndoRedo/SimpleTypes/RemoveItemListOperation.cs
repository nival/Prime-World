using System;
using System.Collections.Generic;
using System.Text;

namespace libdb.UndoRedo
{
	class RemoveItemListOperation<T> : IUndoRedoOperation
	{
    private readonly UndoRedoListBase<T> list;
		private int index = -1;
		private readonly T item = default(T);

    public RemoveItemListOperation( UndoRedoListBase<T> list, T value ) 
		{
			this.list = list;
			this.item = value;
			this.index = list.IndexOf( item );
		}

		public void Undo()
		{
			list.InsertInternal( index, item );
		}

		public void Redo()
		{
			list.RemoveAtInternal( index );
		}

		public libdb.DB.DBResource GetOwner()
		{
			return list.GetOwner();
		}

		public string DefaultCaption
		{
			get { return string.Format( "\"{0}\" remove \"{1}\" with index \"{2}\"", GetOwner().DBId.Name, item.ToString(), index.ToString() ); }
		}
	}
}

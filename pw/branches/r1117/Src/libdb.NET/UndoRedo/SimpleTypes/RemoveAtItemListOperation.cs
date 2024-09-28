using System;
using System.Collections.Generic;
using System.Text;

namespace libdb.UndoRedo
{
	class RemoveAtItemListOperation<T> : IUndoRedoOperation
	{
    private readonly UndoRedoListBase<T> list;
		private readonly int index;
		private T item = default(T);

    public RemoveAtItemListOperation( UndoRedoListBase<T> list, int index ) 
		{
			this.list = list;
			this.index = index;
		}

		public void Undo() { list.InsertInternal( index, item ); }
		public void Redo() { item = list[index]; list.RemoveAtInternal( index ); }

		public libdb.DB.DBResource GetOwner()  { return list.GetOwner(); }
    public string DefaultCaption { get { return string.Format( "\"{0}\" remove at \"{2}\" element \"{1}\"", ( null == GetOwner() ) ? "" : GetOwner().DBId.Name, item.ToString(), index.ToString() ); } }
	}
}

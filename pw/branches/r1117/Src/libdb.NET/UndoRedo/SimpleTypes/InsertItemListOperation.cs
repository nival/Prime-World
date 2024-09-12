using System;
using System.Collections.Generic;
using System.Text;

namespace libdb.UndoRedo
{
	class InsertItemListOperation<T> : IUndoRedoOperation
	{
		private readonly UndoRedoListBase<T> list;
		private readonly int index;
		private readonly T item;

    public InsertItemListOperation( UndoRedoListBase<T> list, int index, T item ) 
		{
			this.list = list;
			this.index = index;
			this.item = item;
		}

		public void Undo() { list.RemoveAtInternal( index ); }
		public void Redo() { list.InsertInternal( index, item ); }

		public libdb.DB.DBResource GetOwner(){ return list.GetOwner(); } 
		public string DefaultCaption { get { return string.Format( "\"{0}\" insert \"{1}\" with index \"{2}\"", GetOwner() != null ? GetOwner().DBId.Name : libdb.DB.DBID.Empty.Name, item != null ? item.ToString() : "{null}" , index.ToString() ); } }
	}
}

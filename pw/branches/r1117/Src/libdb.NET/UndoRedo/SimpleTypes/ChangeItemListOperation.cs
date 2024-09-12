using System;
using System.Collections.Generic;
using System.Text;

namespace libdb.UndoRedo
{
	class ChangeItemListOperation<T> : IUndoRedoOperation
	{
    private readonly UndoRedoListBase<T> list;
		private readonly int index;
		private readonly T item;
		private readonly T oldItem;


    public ChangeItemListOperation( UndoRedoListBase<T> list, int index, T item ) 
		{
			this.list = list;
			this.index = index;
			this.item = item;
			this.oldItem = list[index];
		}

		public void Undo() { list.SetInternal( index, oldItem ); }
		public void Redo() { list.SetInternal( index, item ); }

		public libdb.DB.DBResource GetOwner() { return list.GetOwner(); } 
		public string DefaultCaption 
		{
			get 
			{
				return string.Format( "\"{0}\" change item \"{1}\" with index \"{2}\" to \"{3}\"",
          GetOwner() != null ? GetOwner().DBId.Name : libdb.DB.DBID.Empty.Name, oldItem ==null? string.Empty:oldItem.ToString(), index, item.ToString() );
			}
		}
	}
}

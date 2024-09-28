using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.UndoRedo
{
	class ChangeOperation<T> : IUndoRedoOperation
	{
		private readonly UndoRedo<T> member;
		private readonly T value;
		private readonly T oldValue;

		public ChangeOperation( UndoRedo<T> member, T value ) 
		{
			this.member = member;
			this.value = value;
			this.oldValue = member.Get();
		}

		public void Undo() 
		{ 
			member.SetInternal( oldValue );
			DBResource owner = member.GetOwner();
		}

		public void Redo() 
		{ 
			member.SetInternal( value );
			DBResource owner = member.GetOwner();
		}

		public libdb.DB.DBResource GetOwner() { return member.GetOwner(); } 
		public string DefaultCaption { get { return string.Format( "\"{0}\" change \"{1}\" to \"{2}\"", (GetOwner()!= null && GetOwner().DBId!= null)?GetOwner().DBId.Name:String.Empty, value.ToString(), oldValue.ToString() ); } }
	}
}

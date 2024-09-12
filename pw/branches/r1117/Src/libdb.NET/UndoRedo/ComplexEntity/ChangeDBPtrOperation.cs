using System;
using libdb.DB;

namespace libdb.UndoRedo.ComplexEntity
{
	class ChangeDBPtrOperation<T> : IUndoRedoOperation where T : DBResource, new()
	{
		private readonly UndoRedoDBPtr<T> member;
		private readonly DBID value;
		private readonly DBID oldValue;

		public ChangeDBPtrOperation( UndoRedoDBPtr<T> member, DBID value )
		{
			this.member = member;
			this.value = value;
			this.oldValue = member.Get().DBId;
		}

		public void Undo() { member.SetInternal( oldValue ); }
		public void Redo() { member.SetInternal( value ); }

		public DBResource GetOwner() { return member.Owner; }
		public string DefaultCaption { get { return string.Format( "\"{0}\" change DBPtr \"{2}\" to \"{1}\"", (GetOwner() != null && GetOwner().DBId != null)?GetOwner().DBId.Name:String.Empty, value.Name, oldValue.Name ); } }
	}
}
using System;
using libdb.DB;

namespace libdb.UndoRedo.ComplexEntity
{
	class ResetDBPtrOperation<T> : IUndoRedoOperation where T : DBResource, new()
	{
		private readonly UndoRedoDBPtr<T> member;
		private readonly DBID oldValue;

		public ResetDBPtrOperation( UndoRedoDBPtr<T> member )
		{
			this.member = member;
			this.oldValue = member.Get().DBId;
		}

		public void Undo() { member.SetInternal( oldValue ); }
		public void Redo() { member.ResetInternal(); }

		public DBResource GetOwner() { return member.Owner; }
		public string DefaultCaption { get { return string.Format( "\"{0}\" Reset DBPtr \"{1}\"", ( GetOwner() != null && GetOwner().DBId != null ) ? GetOwner().DBId.Name : String.Empty, oldValue.Name ); } }
	}
}
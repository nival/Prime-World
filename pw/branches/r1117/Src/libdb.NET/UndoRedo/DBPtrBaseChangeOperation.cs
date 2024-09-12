using System;
using libdb.DB;

namespace libdb.UndoRedo
{
	public class DBPtrBaseChangeOperation : IUndoRedoOperation
	{
		private readonly DBPtrBase member;
		private readonly DBID value;
		private readonly DBID oldValue;

		public DBPtrBaseChangeOperation( DBPtrBase _member, DBID _value )
		{
			member = _member;
			value = _value;

			DBResource resource = _member.Get<DBResource>();
			oldValue = resource == null ? DBID.Empty : resource.DBId;
		}

		public void Undo() { member.Set( oldValue ); }
		public void Redo() { member.Set( value ); }

		public DBResource GetOwner() { return member.GetOwner(); }
		public string DefaultCaption { get { return string.Format( "\"{0}\" change DBPtr \"{2}\" to \"{1}\"", (GetOwner() != null && GetOwner().DBId != null)?GetOwner().DBId.Name:String.Empty, value.Name, oldValue.Name ); } }
	}
}

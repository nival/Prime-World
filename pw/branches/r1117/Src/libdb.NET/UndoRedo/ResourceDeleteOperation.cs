using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.UndoRedo
{
	class ResourceDeleteOperation : IUndoRedoOperation
	{
		private readonly DBID dbid;
		private readonly DBResource value;

		public ResourceDeleteOperation( DBID dbid )
		{
			this.dbid = dbid;
			this.value = DataBase.Get<DBResource>( dbid ).Get();
		}

		public void Undo()
		{
			if ( !DBID.IsNullOrEmpty( value.DBId ) )
				value.Rename( DBID.Empty );

			DBPtr<DBResource> ptr = new DBPtr<DBResource>( dbid, value );

			DataBase.CreateCallback( dbid );
		}

		public void Redo()
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
			ptr.Delete();
		}

		public DBResource GetOwner() { return value; } 
		public string DefaultCaption { get { return string.Format( "Delete \"{0}\"", dbid.Name ); } }
	}
}

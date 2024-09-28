using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.UndoRedo
{
	class ResourceCreateOperation : IUndoRedoOperation
	{
		private readonly DBID dbid;
		private readonly DBResource value;

		public ResourceCreateOperation( DBID dbid, DBResource value ) 
		{
			this.value = value;
			this.dbid = dbid;
		}

		public void Undo() 
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
			ptr.Delete();
		}

		public void Redo() 
		{
			if ( !DBID.IsNullOrEmpty( value.DBId ) )
				value.Rename( DBID.Empty );

			DBPtr<DBResource> ptr = new DBPtr<DBResource>( dbid, value );
		
			DataBase.CreateCallback( dbid );
		}

		public DBResource GetOwner() { return value; }
		public string DefaultCaption { get { return string.Format( "Create \"{0}\"", dbid.Name ); } }
	}
}

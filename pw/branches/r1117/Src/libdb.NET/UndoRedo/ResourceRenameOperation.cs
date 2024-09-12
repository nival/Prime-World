using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;
namespace libdb.UndoRedo
{
	internal class ResourceRenameOperation : IUndoRedoOperation
	{
		private readonly DBID dbid;
		private readonly DBID oldDbid;
    private DBReference storedSrc = null;

		public ResourceRenameOperation( DBID newdbid, DBID oldDbid )
		{
			this.dbid = newdbid;
			this.oldDbid = oldDbid;
		}

		public void Undo()
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
			ptr.Rename( oldDbid, storedSrc );
		}

		public void Redo()
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( oldDbid );
			storedSrc = ptr.Rename( dbid, null );
		}

		public DBResource GetOwner() { return null; }
		public string DefaultCaption { get { return string.Format( "Rename \"{0}\" to \"{1}\"", oldDbid.Name, dbid.Name ); } }
	}
}

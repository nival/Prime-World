using libdb.DB;

namespace libdb.UndoRedo
{
	internal sealed class ResourceChangeOperation : IUndoRedoOperation
	{
		private readonly DBID dbid;
		private readonly DBResource resource;
		private readonly DBResource oldResource = null;

		public ResourceChangeOperation( DBID dbid, DBResource resource ) 
		{
			this.dbid = dbid;
			this.resource = resource;

			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
			if ( ptr != null )
				oldResource = ptr.Get();
		}

		public void Undo()
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
			ptr.ChangeResource( oldResource );
		}

		public void Redo()
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
			ptr.ChangeResource( resource );
		}

    public DBResource GetOwner() { return resource; }
		public string DefaultCaption { get { return string.Format( "Change resource content \"{0}\"", dbid.Name ); } }
	}
}

using System;
using libdb.DB;
using libdb.Diagnostics;

namespace libdb.UndoRedo
{
	class ResourceInlineOperation : IUndoRedoOperation
	{
		private readonly DBResource oldValue;
		private DBID dbid = null;
		private readonly DBID oldDbId;

		public ResourceInlineOperation( DBID _dbId )
		{
			oldDbId = _dbId;
			oldValue = DataBase.Get<DBResource>(oldDbId).Get();
		}
		
		public void Undo()
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
			ptr.Uninline( oldDbId );
		}
		
		public void Redo()
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( oldDbId );
			ptr.Inline( Guid.Empty);
			dbid = ptr.DBId;
		}

		public DBResource GetOwner() { return oldValue; } 
		public string DefaultCaption { get { return string.Format( "Create \"{0}\"", dbid.Name ); } }
	}

	class ResourceUninlineOperation : IUndoRedoOperation
	{
		private readonly DBID oldDbId;
		private readonly DBID newDbId;
		private readonly DBResource oldValue;

		public ResourceUninlineOperation( DBID _dbId, DBID _newDbId )
		{
			oldDbId = _dbId;
			newDbId = _newDbId;
			oldValue = DataBase.Get<DBResource>(oldDbId).Get();
		}

		public void Undo()
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( newDbId );
			ptr.Inline( new Guid(oldDbId.Id) );
		}

		public void Redo()
		{
			DBPtr<DBResource> ptr = DataBase.Get<DBResource>( oldDbId );
			ptr.Uninline( newDbId );
			
			Log.Assert(oldValue == ptr.Get(), "При uninline ссылка на ресурс должна оставаться корректной");
		}

		public DBResource GetOwner() { return oldValue; }
		public string DefaultCaption { get { return string.Format( "Create \"{0}\"", newDbId.Name ); } }
	}
}

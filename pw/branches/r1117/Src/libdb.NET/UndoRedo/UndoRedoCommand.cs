using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.UndoRedo
{
	public sealed class UndoRedoCommand
	{
		private Dictionary<DBID, bool> holders = new Dictionary<DBID, bool>();
		private List<IUndoRedoOperation> operartions = new List<IUndoRedoOperation>();
		private readonly string caption;

		public string Caption { get { return caption; } }

		public UndoRedoCommand( string caption ) { this.caption = caption; }
		public void AddOperation( IUndoRedoOperation operation ) 
		{
			operartions.Add( operation );
			if ( operation.GetOwner() != null && !operation.GetOwner().DBId.IsEmpty && !holders.ContainsKey( operation.GetOwner().DBId ) )
				holders.Add( operation.GetOwner().DBId, false );
		}

		public void Undo() 
		{
			for ( int i = operartions.Count - 1; i >= 0; --i )
				operartions[i].Undo();

			Commit();
		}
		
		public void Redo() 
		{ 
			foreach ( IUndoRedoOperation operation in operartions )
				operation.Redo();

			Commit();
		}

		public void Commit()
		{
			foreach ( DBID item in holders.Keys )
				DataBase.ChangeCallback( item );
		}

    public bool IsEmpty { get { return operartions.Count == 0; } }
	}
}

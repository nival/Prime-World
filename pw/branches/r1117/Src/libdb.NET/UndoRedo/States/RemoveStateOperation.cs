using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.UndoRedo
{
  class RemoveStateOperation : IUndoRedoOperation
  {
    private readonly DBID dbid;
    private readonly string stateName;
    private readonly DBResource value;
    private readonly DBResource owner;

    public RemoveStateOperation( DBID dbid, string _stateName )
    {
      this.dbid = dbid;
      this.stateName = _stateName;
      this.value = DataBase.Get<DBResource>( dbid ).Get( stateName );
      this.owner = DataBase.Get<DBResource>( dbid ).Get();
    }

    public void Undo()
    {
      DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
      ptr.RestoreStateInternal( stateName, value );
    }

    public void Redo()
    {
      DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
      ptr.RemoveStateInternal( stateName );
    }

    public DBResource GetOwner() { return owner; }
    public string DefaultCaption { get { return string.Format( "Remove state \"{0}\" from \"{1}\"", stateName, dbid.Name ); } }
  }
}

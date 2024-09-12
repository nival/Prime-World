using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.UndoRedo
{
  class AddStateOperation : IUndoRedoOperation
  {
    private readonly DBID dbid;
    private readonly string stateName;
    private readonly DBResource owner;

    public AddStateOperation( DBID dbid, string _stateName )
    {
      this.dbid = dbid;
      stateName = _stateName;
      this.owner = DataBase.Get<DBResource>( dbid ).Get();
    }

    public void Undo()
    {
      DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
      ptr.RemoveStateInternal( stateName );
    }

    public void Redo()
    {
      DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
      ptr.AddStateInternal( stateName );
    }

    public DBResource GetOwner() { return owner; }
    public string DefaultCaption { get { return string.Format( "Add state \"{0}\" to \"{1}\"", stateName, dbid.Name ); } }
  }
}

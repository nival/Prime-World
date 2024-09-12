using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.UndoRedo
{
  class RenameStateOperation : IUndoRedoOperation
  {
    private readonly DBID dbid;
    private readonly string oldStateName;
    private readonly string stateName;
    private readonly DBResource owner;

    public RenameStateOperation( DBID dbid, string _oldStateName, string _newStateName )
    {
      this.dbid = dbid;
      this.stateName = _newStateName;
      this.oldStateName = _oldStateName;
      this.owner = DataBase.Get<DBResource>( dbid ).Get();
    }

    public void Undo()
    {
      DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
      ptr.RenameStateInternal( stateName, oldStateName );
    }

    public void Redo()
    {
      DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
      ptr.RenameStateInternal( oldStateName, stateName );
    }

    public DBResource GetOwner() { return owner; }
    public string DefaultCaption { get { return string.Format( "Rename state \"{0}\" to \"{1}\" for \"{2}\"", oldStateName, stateName, dbid.Name ); } }
  }
}

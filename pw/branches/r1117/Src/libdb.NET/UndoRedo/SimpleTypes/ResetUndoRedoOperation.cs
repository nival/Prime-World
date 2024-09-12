using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.UndoRedo
{
  class ResetUndoRedoOperation<T> : IUndoRedoOperation
  {
    private readonly UndoRedo<T> member;
    private readonly T oldValue;

    public ResetUndoRedoOperation( UndoRedo<T> member )
    {
      this.member = member;
      this.oldValue = member.Get();
    }

    public void Undo()
    {
      member.SetInternal( oldValue );
    }

    public void Redo()
    {
      member.ResetInternal();
    }

    public libdb.DB.DBResource GetOwner() { return member.GetOwner(); }
    public string DefaultCaption { get { return string.Format( "\"{0}\" reset from changed value \"{1}\"", ( GetOwner() != null && GetOwner().DBId != null ) ? GetOwner().DBId.Name : String.Empty, oldValue.ToString() ); } }
  }
}

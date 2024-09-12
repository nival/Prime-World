using System;
using libdb.DB;

namespace libdb.UndoRedo
{
  public class UndoRedoTransaction : IDisposable
  {
    private bool isStarted;

    public UndoRedoTransaction( string commandCaption )
    {
      DataBase.UndoRedoManager.Start( commandCaption );
      isStarted = true;
    }

    public void Commit()
    {
      if(isStarted)
      {
        DataBase.UndoRedoManager.Commit();
        isStarted = false;
      }
    }

    public void Cancel()
    {
      if( isStarted )
      {
        DataBase.UndoRedoManager.Cancel();
        isStarted = false;
      }
    }

    public void Dispose()
    {
      Cancel();
    }
  }
}
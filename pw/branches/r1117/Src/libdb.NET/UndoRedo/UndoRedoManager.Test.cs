using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;
using libdb.Animated;
using NUnit.Framework;

namespace libdb.UndoRedo
{
  [TestFixture]
	public class UndoRedoManagerTest
	{
    private class UndoRedoOperation : IUndoRedoOperation
    {
      private int undoCount = 0;
      private int redoCount = 0;
      private readonly DBResource owner = null;

      public UndoRedoOperation( DBResource owner )
      {
        this.owner = owner;
      }

      public void Undo()
      {
        ++undoCount;
      }

      public void Redo()
      {
        ++redoCount;
      }

      public string DefaultCaption
      {
        get { return GetType().ToString(); }
      }

      public DBResource GetOwner()
      {
        return owner;
      }
    }

    private class DataBaseChangeListener
    {
      private DBID lastDBIDChanged = DBID.Empty;

      public DataBaseChangeListener()
      {
        DataBase.ChangeDBResourceEvent += OnDataBaseChangeDBResourceEvent;
      }

      private void OnDataBaseChangeDBResourceEvent( DBID dbid )
      {
        lastDBIDChanged = dbid;
      }

      public DBID LastDBIDChanged { get { return lastDBIDChanged; } }
    }

    [Test]
    public void TestCommandStarted()
    {
      UndoRedoManager manager = new UndoRedoManager();
      Assert.IsFalse( manager.IsCommandStarted );
      manager.Start( "Test" );
      Assert.IsTrue( manager.IsCommandStarted );
      manager.Commit();
      Assert.IsFalse( manager.IsCommandStarted );
    }

    [Test]
    public void TestMultiplyCommandsStarted()
    {
      UndoRedoManager manager = new UndoRedoManager();
      Assert.IsFalse( manager.IsCommandStarted );
      manager.Start( "Test" );
      Assert.IsTrue( manager.IsCommandStarted );
      manager.Start( "Test2" );
      Assert.IsTrue( manager.IsCommandStarted );
      manager.Commit();
      Assert.IsTrue( manager.IsCommandStarted );
      manager.Commit();
      Assert.IsFalse( manager.IsCommandStarted );
    }

    [Test]
    public void TestChangedEvent()
    {
      DataBase.UndoRedoManager = new UndoRedoManager();
      DataBaseChangeListener listener = new DataBaseChangeListener();
      DBPtr<DBResource> ptr = DataBase.Create<DBResource>( DBID.FromString( "A" ), new DBResource() );
      DataBase.UndoRedoManager.AddOperation( new UndoRedoOperation( ptr.Get() ) );
      Assert.AreEqual( DBID.FromString( "A" ), listener.LastDBIDChanged );
    }

    [Test]
    public void TestChangedEventInCommand()
    {
      DataBase.UndoRedoManager = new UndoRedoManager();
      DataBaseChangeListener listener = new DataBaseChangeListener();
      DBPtr<DBResource> ptr = DataBase.Create<DBResource>( DBID.FromString( "A" ), new DBResource() );

      DataBase.UndoRedoManager.Start( "Test" );
      DataBase.UndoRedoManager.AddOperation( new UndoRedoOperation( ptr.Get() ) );
      Assert.AreEqual( DBID.Empty, listener.LastDBIDChanged );
      DataBase.UndoRedoManager.Commit();
      Assert.AreEqual( DBID.FromString( "A" ), listener.LastDBIDChanged );
    }
  }
}
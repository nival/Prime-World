using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using River.Core;
using System.IO;
using River.Bot;

namespace River.Tests.Context
{
  [TestFixture]
  public class ClientContextTests
  {
    private List<string> createdFiles = new List<string>();

    [TearDown]
    public void RemoveFiles()
    {
      if ( createdFiles.Count == 0 )
        return;

      foreach( string fileName in createdFiles )
      {
        if ( File.Exists( fileName ) )
          File.Delete( fileName );
      }

      createdFiles.Clear();
    }

    #region SyncContext interaction tests
    [Test]
    public void TestSyncContextSimpleCalls()
    {
      MockSyncContext msc = new MockSyncContext();
      IContext c = new ClientContext( msc, null );

      c.SyncInc( "var1" );
      Assert.AreEqual( 1, msc.SyncIncCalled );
      Assert.AreEqual( "var1", msc.SyncIncParam );

      c.SyncDec( "var2" );
      Assert.AreEqual( 1, msc.SyncDecCalled );
      Assert.AreEqual( "var2", msc.SyncDecParam );

      bool swr = c.SyncWait( "var3", 100, TimeSpan.MaxValue );
      Assert.IsFalse( swr );
      Assert.AreEqual( 1, msc.SyncCheckCalled );
      Assert.AreEqual( "var3", msc.SyncCheckParam1 );
      Assert.AreEqual( 100, msc.SyncCheckParam2 );
      Assert.AreEqual( TimeSpan.MaxValue, msc.SyncCheckParam3 );

      c.Progress( 10, "msg" );
      Assert.AreEqual( 1, msc.ProgressCalled );
      Assert.AreEqual( 10, msc.ProgressParam1 );
      Assert.AreEqual( "msg", msc.ProgressParam2 );

      BotDescription[] bdr = new BotDescription[3];
      msc.GetBotsResult = bdr;
      BotDescription[] gbresult = c.GetBotsWithTest( GetType().Name );
      Assert.AreEqual( 1, msc.GetBotsCalled );
      Assert.AreEqual( GetType().Name, msc.GetBotsParam );
      Assert.AreEqual( bdr, gbresult );
    }

    #endregion

    #region PutFile tests

    [Test]
    public void TestPutSingleFile()
    {
      MockSyncContext msc = new MockSyncContext();
      IContext c = new ClientContext( msc, null );

      byte[] fileData = new byte[10];
      for ( byte i = 0; i < 10; ++i )
        fileData[i] = i;

      File.WriteAllBytes( "someFile.bin", fileData );
      createdFiles.Add( "someFile.bin" );

      c.PutFile( "someFile.bin" );

      Assert.AreEqual( 1, msc.PutFileCalled );
      Assert.AreEqual( "someFile.bin", msc.PutFileParam1[0] );
      Assert.AreEqual( fileData.Length, msc.PutFileParam2[0].Length );
      for ( int i = 0; i < fileData.Length; ++i )
        Assert.AreEqual( fileData[i], msc.PutFileParam2[0][i] );
    }

    [Test]
    public void TestPutMultipleFiles()
    {
      MockSyncContext msc = new MockSyncContext();
      IContext c = new ClientContext( msc, null );

      byte[] fileData1 = new byte[10];
      for ( byte i = 0; i < 10; ++i )
        fileData1[i] = i;

      File.WriteAllBytes( "someFile1.bin", fileData1 );
      createdFiles.Add( "someFile1.bin" );

      byte[] fileData2 = new byte[10];
      for ( byte i = 0; i < 10; ++i )
        fileData2[i] = (byte)( i + 1 );

      File.WriteAllBytes( "someFile2.bin", fileData2 );
      createdFiles.Add( "someFile2.bin" );

      c.PutFile( "someFile*.bin" );

      Assert.AreEqual( 2, msc.PutFileCalled );
      Assert.AreEqual( "someFile1.bin", msc.PutFileParam1[0] );
      Assert.AreEqual( "someFile2.bin", msc.PutFileParam1[1] );
      Assert.AreEqual( fileData1.Length, msc.PutFileParam2[0].Length );
      for ( int i = 0; i < fileData1.Length; ++i )
        Assert.AreEqual( fileData1[i], msc.PutFileParam2[0][i] );

      Assert.AreEqual( fileData2.Length, msc.PutFileParam2[1].Length );
      for ( int i = 0; i < fileData2.Length; ++i )
        Assert.AreEqual( fileData2[i], msc.PutFileParam2[1][i] );
    }

    #endregion

  }
}

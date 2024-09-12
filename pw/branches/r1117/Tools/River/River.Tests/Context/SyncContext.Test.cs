using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using River.Core;
using System.ComponentModel;
using System.Threading;
using River.Master;

namespace River.Tests.Context
{
  [TestFixture]
  public class SyncContextTests
  {
    #region Sync Vars tests
    [Test]
    public void TestSyncAllExceptions()
    {
      ISyncContext context = new SyncContext( null );

      Exception e = null;
      try { context.SyncInc( null ); }
      catch ( Exception eCaught ) { e = eCaught; }
      Assert.IsNotNull( e );
      Assert.IsTrue( e is ArgumentNullException );

      e = null;
      try { context.SyncDec( null ); }
      catch ( Exception eCaught ) { e = eCaught; }
      Assert.IsNotNull( e );
      Assert.IsTrue( e is ArgumentNullException );

      e = null;
      try { context.SyncWait( null, 0, TimeSpan.Zero ); }
      catch ( Exception eCaught ) { e = eCaught; }
      Assert.IsNotNull( e );
      Assert.IsTrue( e is ArgumentNullException );

      e = null;
      try { context.SyncInc( "!!!Incorrect name///" ); }
      catch ( Exception eCaught ) { e = eCaught; }
      Assert.IsNotNull( e );
      Assert.IsTrue( e is ArgumentException );

      e = null;
      try { context.SyncDec( "!!!Incorrect name///" ); }
      catch ( Exception eCaught ) { e = eCaught; }
      Assert.IsNotNull( e );
      Assert.IsTrue( e is ArgumentException );

      e = null;
      try { context.SyncWait( "!!!Incorrect name///", 0, TimeSpan.Zero ); }
      catch ( Exception eCaught ) { e = eCaught; }
      Assert.IsNotNull( e );
      Assert.IsTrue( e is ArgumentException );
    }

    [Test]
    public void TestSyncVarBasicActions()
    {
      SyncContext context = new SyncContext( null );

      Assert.IsTrue( context.SyncWait( "unknown_var1", 0, TimeSpan.Zero ) );
      Assert.IsTrue( context.SyncWait( "unknown_var2", 0, TimeSpan.Zero ) );
      Assert.IsFalse( context.SyncWait( "unknown_var3", 1, TimeSpan.Zero ) );

      context.SyncInc( "var1" );
      Assert.IsTrue( context.SyncWait( "var1", 1, TimeSpan.Zero ) );
      Assert.IsFalse( context.SyncWait( "var2", 1, TimeSpan.Zero ) );
      Assert.IsTrue( context.SyncWait( "var2", 0, TimeSpan.Zero ) );
      context.SyncInc( "var1" );
      Assert.IsTrue( context.SyncWait( "var1", 2, TimeSpan.Zero ) );
      Assert.IsFalse( context.SyncWait( "var2", 2, TimeSpan.Zero ) );
      Assert.IsTrue( context.SyncWait( "var2", 0, TimeSpan.Zero ) );
      context.SyncDec( "var1" );
      Assert.IsTrue( context.SyncWait( "var1", 1, TimeSpan.Zero ) );
      context.SyncDec( "var1" );
      Assert.IsTrue( context.SyncWait( "var1", 0, TimeSpan.Zero ) );
      Assert.IsTrue( context.SyncWait( "var2", 0, TimeSpan.Zero ) );
    }

    [Test]
    public void TestSyncWaitDelay()
    {
    }

    [Test]
    public void TestSyncVarsConcurrency1()
    {
      SyncContext context = new SyncContext( null );
      object r1 = null;
      object r2 = null;
      object r3 = null;

      BackgroundWorker bw1 = new BackgroundWorker();
      bw1.DoWork += ( s, e ) => { if ( !( e.Argument as SyncContext ).SyncWait( "var", 1, TimeSpan.FromSeconds( 1 ) ) ) e.Result = "SyncWait 1 failed"; };
      bw1.RunWorkerCompleted += ( s, e ) => { r1 = e.Result; };
      BackgroundWorker bw2 = new BackgroundWorker();
      bw2.DoWork += ( s, e ) => { if ( !( e.Argument as SyncContext ).SyncWait( "var", 1, TimeSpan.FromSeconds( 1 ) ) ) e.Result = "SyncWait 2 failed"; };
      bw2.RunWorkerCompleted += ( s, e ) => { r2 = e.Result; };
      BackgroundWorker bw3 = new BackgroundWorker();
      bw3.DoWork += ( s, e ) => { if ( !( e.Argument as SyncContext ).SyncWait( "var", 1, TimeSpan.FromSeconds( 1 ) ) ) e.Result = "SyncWait 3 failed"; };
      bw3.RunWorkerCompleted += ( s, e ) => { r3 = e.Result; };

      bw1.RunWorkerAsync( context );
      bw2.RunWorkerAsync( context );
      bw3.RunWorkerAsync( context );

      context.SyncDec( "var" );
      context.SyncInc( "var" );
      context.SyncInc( "var" );
      Thread.Sleep( 100 );
      Assert.IsFalse( bw1.IsBusy );
      Assert.IsFalse( bw2.IsBusy );
      Assert.IsFalse( bw3.IsBusy );
      Assert.IsNull( r1 );
      Assert.IsNull( r2 );
      Assert.IsNull( r3 );
    }

    [Test]
    public void TestSyncVarsConcurrency2()
    {
      SyncContext context = new SyncContext( null );
      object r1 = null;
      object r2 = null;
      object r3 = null;

      BackgroundWorker bw1 = new BackgroundWorker();
      bw1.DoWork += ( s, e ) =>
      {
        ( e.Argument as SyncContext ).SyncInc( "var" );
        if ( !( e.Argument as SyncContext ).SyncWait( "var", 4, TimeSpan.FromSeconds( 1 ) ) ) e.Result = "SyncWait 1 failed";
      };
      bw1.RunWorkerCompleted += ( s, e ) => { r1 = e.Result; };
      BackgroundWorker bw2 = new BackgroundWorker();
      bw2.DoWork += ( s, e ) =>
      {
        ( e.Argument as SyncContext ).SyncInc( "var" );
        if ( !( e.Argument as SyncContext ).SyncWait( "var", 4, TimeSpan.FromSeconds( 1 ) ) ) e.Result = "SyncWait 2 failed";
      };
      bw2.RunWorkerCompleted += ( s, e ) => { r2 = e.Result; };
      BackgroundWorker bw3 = new BackgroundWorker();
      bw3.DoWork += ( s, e ) =>
      {
        ( e.Argument as SyncContext ).SyncInc( "var" );
        if ( !( e.Argument as SyncContext ).SyncWait( "var", 4, TimeSpan.FromSeconds( 1 ) ) ) e.Result = "SyncWait 3 failed";
      };
      bw3.RunWorkerCompleted += ( s, e ) => { r3 = e.Result; };

      bw1.RunWorkerAsync( context );
      bw2.RunWorkerAsync( context );
      bw3.RunWorkerAsync( context );

      context.SyncInc( "var" );
      Assert.IsTrue( context.SyncWait( "var", 4, TimeSpan.FromSeconds( 1 ) ) );
      ThreadUtils.WaitFor( () => { return !bw1.IsBusy && !bw2.IsBusy && !bw3.IsBusy; } );

      Assert.IsNull( r1 );
      Assert.IsNull( r2 );
      Assert.IsNull( r3 );
    }

    #endregion

    #region GetBots() tests

    [Test]
    public void TestGetBots()
    {
      SyncContext context = new SyncContext( null );

      BotDescription bd1 = new BotDescription( "bot1", -1 );
      BotDescription bd2 = new BotDescription( "bot2", -1 );
      BotDescription bd3 = new BotDescription( "bot3", -1 );
      context.RegisterBot( bd1, "SyncContext" );
      context.RegisterBot( bd2, "SyncContext" );
      context.RegisterBot( bd3, "Exception" );

      BotDescription[] type1Descs = context.GetBotsWithTest( typeof( SyncContext ).Name );
      BotDescription[] type2Descs = context.GetBotsWithTest( typeof( Exception ).Name );
      Assert.AreEqual( 2, type1Descs.Length );
      Assert.AreEqual( 1, type2Descs.Length );
      Assert.AreEqual( bd1, type1Descs[0] );
      Assert.AreEqual( bd2, type1Descs[1] );
      Assert.AreEqual( bd3, type2Descs[0] );
    }

    #endregion
  }
}

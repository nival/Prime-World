using System;
using System.CodeDom.Compiler;
using System.Diagnostics;
using System.Threading;
using NUnit.Framework;
using River.Core;
using River.Master;

namespace River.Tests.Master
{
  [TestFixture]
  public class MasterBotTests
  {
    #region Utility methods

		private MasterBot GetMasterBotInState( MasterBot.BotStatus state, out MockBot bot )
    {
      if ( state == MasterBot.BotStatus.Offline )
      {
        bot = null;
        return new MasterBot( null );
      }

      bot = new MockBot();
      MasterBot mbot = new MasterBot( bot );
      if ( state == MasterBot.BotStatus.Idle )
        return mbot;

      mbot.Load( "", "", null );
      if ( state == MasterBot.BotStatus.Loading )
        return mbot;

			bot.StopLoading();
			ThreadUtils.WaitFor( () => { return mbot.Status == MasterBot.BotStatus.Loaded; } );
      if ( state == MasterBot.BotStatus.Loaded )
        return mbot;

      mbot.BeginInstall(  );
      if ( state == MasterBot.BotStatus.Installing )
        return mbot;

      OperationResultsEventsArgs resultSuccess = new OperationResultsEventsArgs( true );
      bot.InvokeInstallFinished( resultSuccess );
			ThreadUtils.WaitFor( () => { return mbot.Status == MasterBot.BotStatus.Installed; } );

      if ( state == MasterBot.BotStatus.Installed )
        return mbot;

      mbot.BeginExecute(  );
      return mbot;    // Executing
    }

    #endregion

    #region Loading tests

    [Test, Description( "Test that Load() passes parameters correctly (and that Load is called)" )]
    public void TestLoadParameterPassing()
    {
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );
      ISyncContext context = new SyncContext( null );
      mbot.Load( "aaa", "bbb", context );
      Thread.Sleep( 10 );
      Assert.AreEqual( "aaa", ibot.LoadedSuite );
      Assert.AreEqual( "bbb", ibot.LoadedType );
      Assert.AreEqual( context, ibot.LoadedContext );
    }

    [Test, Description( "Test that Load() throws exceptions when invoked in a wrong state" )]
    public void TestLoadStatusCheck()
    {
      foreach ( MasterBot.BotStatus statusValue in Enum.GetValues( typeof( MasterBot.BotStatus ) ) )
      {
        if ( statusValue == MasterBot.BotStatus.Idle )
          continue;

        MockBot ibot = null;
				MasterBot mbot = GetMasterBotInState( statusValue, out ibot );
        Assert.AreEqual( statusValue, mbot.Status );
        Exception eCaught = null;
        try
        {
          mbot.Load( "aaa", "bbb", null );
        }
        catch ( Exception e )
        {
          eCaught = e;
        }
        Assert.IsNotNull( eCaught );
        Assert.IsTrue( eCaught is InvalidOperationException );
      }
    }

    [Test, Description( "Test that Load() reacts corrctly after code 'compiles' correctly" )]
    public void TestLoadCompileSucceeds()
    {
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );
      Exception receivedError = null;
      MasterBot.BotStatus receivedStatus = MasterBot.BotStatus.Offline;
      mbot.OnStatusChanged += ( b, s, e ) => { receivedStatus = s; receivedError = e; };

      mbot.Load( "aaa", "bbb", null );
      Assert.AreEqual( MasterBot.BotStatus.Loading, mbot.Status );

			ibot.StopLoading();
      while ( receivedStatus == MasterBot.BotStatus.Loading )
        Thread.Sleep( 10 );

      Assert.AreEqual( MasterBot.BotStatus.Loaded, mbot.Status );
      Assert.AreEqual( MasterBot.BotStatus.Loaded, receivedStatus );
      Assert.IsNull( receivedError );
    }

    [Test, Description( "Test that Load() reacts correctly after code 'not compiles', returning correct errors" )]
    public void TestLoadCompileFails()
    {
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );

      Exception receivedError = null;
      MasterBot.BotStatus receivedStatus = MasterBot.BotStatus.Offline;
      mbot.OnStatusChanged += ( b, s, e ) => { receivedStatus = s; receivedError = e; };

      mbot.Load( "aaa", "bbb", null );
      Assert.AreEqual( MasterBot.BotStatus.Loading, mbot.Status );

			CompilerErrorCollection errors = new CompilerErrorCollection( new CompilerError[]{  new CompilerError( "file", 1, 2, "E1", "ET1" ) } );
			ibot.StopLoading( errors[0] );
      while ( receivedStatus == MasterBot.BotStatus.Loading )
        Thread.Sleep( 10 );

      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot.Status );
      Assert.AreEqual( MasterBot.BotStatus.Idle, receivedStatus );
      Assert.IsNotNull( receivedError );
      Assert.IsTrue( receivedError is SuiteLoadException );
      SuiteLoadException loadEx = receivedError as SuiteLoadException;
			Assert.AreEqual( errors, loadEx.Errors );
    }

    #endregion

    #region Installing tests

    [Test, Description( "Test that Install() throws exceptions when invoked in a wrong state" )]
    public void TestInstallStatusCheck()
    {
      foreach ( MasterBot.BotStatus statusValue in Enum.GetValues( typeof( MasterBot.BotStatus ) ) )
      {
        if ( statusValue == MasterBot.BotStatus.Loaded )
          continue;

        MockBot ibot = null;
				MasterBot mbot = GetMasterBotInState( statusValue, out ibot );
        Assert.AreEqual( statusValue, mbot.Status );
        Exception eCaught = null;
        try
        {
          mbot.BeginInstall(  );
        }
        catch ( Exception e )
        {
          eCaught = e;
        }
        Assert.IsNotNull( eCaught );
        Assert.IsTrue( eCaught is InvalidOperationException );
      }
    }

    [Test, Description( "Test that Install() calls Ibot.Install" )]
    public void TestInstallCallsInstall()
    {
      MockBot ibot = null;
			MasterBot mbot = GetMasterBotInState( MasterBot.BotStatus.Loaded, out ibot );
      Assert.AreEqual( MasterBot.BotStatus.Loaded, mbot.Status );

      mbot.BeginInstall(  );
      Assert.AreEqual( 1, ibot.InstallCalled );
    }

    [Test, Description( "Test that Install() finishes correctly with proper state changes" )]
    public void TestInstallSuccess()
    {
      MockBot ibot = null;
			MasterBot mbot = GetMasterBotInState( MasterBot.BotStatus.Loaded, out ibot );
      Assert.AreEqual( MasterBot.BotStatus.Loaded, mbot.Status );

      Exception receivedError = null;
      MasterBot.BotStatus receivedStatus = MasterBot.BotStatus.Offline;
      mbot.OnStatusChanged += ( b, s, e ) => { receivedStatus = s; receivedError = e; };

      mbot.BeginInstall(  );
      Assert.AreEqual( MasterBot.BotStatus.Installing, mbot.Status );
      ibot.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );

      Thread.Sleep( 10 );
      Assert.AreEqual( MasterBot.BotStatus.Installed, receivedStatus );
      Assert.AreEqual( MasterBot.BotStatus.Installed, mbot.Status );
      Assert.IsNull( receivedError );
    }

    [Test, Description( "Test that failed Install() finishes correctly with proper state changes" )]
    public void TestInstallFailure()
    {
      MockBot ibot = null;
			MasterBot mbot = GetMasterBotInState( MasterBot.BotStatus.Loaded, out ibot );
      Assert.AreEqual( MasterBot.BotStatus.Loaded, mbot.Status );

      Exception receivedError = null;
      MasterBot.BotStatus receivedStatus = MasterBot.BotStatus.Offline;
      mbot.OnStatusChanged += ( b, s, e ) => { receivedStatus = s; receivedError = e; };

      mbot.BeginInstall(  );
      Assert.AreEqual( MasterBot.BotStatus.Installing, mbot.Status );

      Exception passedException = new Exception( "test exception" );
      ibot.InvokeInstallFinished( new OperationResultsEventsArgs( passedException ) );

      Thread.Sleep( 10 );
      Assert.AreEqual( MasterBot.BotStatus.Idle, receivedStatus );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot.Status );
      Assert.AreEqual( passedException, receivedError );
    }

    #endregion

    #region Executing tests

    [Test, Description( "Test that Execute() throws exceptions when invoked in a wrong state" )]
    public void TestExecuteStatusCheck()
    {
      foreach ( MasterBot.BotStatus statusValue in Enum.GetValues( typeof( MasterBot.BotStatus ) ) )
      {
        if ( statusValue == MasterBot.BotStatus.Installed )
          continue;

        MockBot ibot = null;
				MasterBot mbot = GetMasterBotInState( statusValue, out ibot );
        Assert.AreEqual( statusValue, mbot.Status );
        Exception eCaught = null;
        try
        {
          mbot.BeginExecute(  );
        }
        catch ( Exception e )
        {
          eCaught = e;
        }
        Assert.IsNotNull( eCaught );
        Assert.IsTrue( eCaught is InvalidOperationException );
      }
    }

    [Test, Description( "Test that Execute() calls Ibot.Execute" )]
    public void TestExecuteCallsExecute()
    {
      MockBot ibot = null;
			MasterBot mbot = GetMasterBotInState( MasterBot.BotStatus.Installed, out ibot );
      Assert.AreEqual( MasterBot.BotStatus.Installed, mbot.Status );

      mbot.BeginExecute(  );
      Assert.AreEqual( 1, ibot.ExecuteCalled );
    }

    [Test, Description( "Test that Execute() finishes correctly with proper state changes" )]
    public void TestExecuteSuccess()
    {
      MockBot ibot = null;
			MasterBot mbot = GetMasterBotInState( MasterBot.BotStatus.Installed, out ibot );
      Assert.AreEqual( MasterBot.BotStatus.Installed, mbot.Status );

      Exception receivedError = null;
      MasterBot.BotStatus receivedStatus = MasterBot.BotStatus.Offline;
      mbot.OnStatusChanged += ( b, s, e ) => { receivedStatus = s; receivedError = e; };

      mbot.BeginExecute(  );
      Assert.AreEqual( MasterBot.BotStatus.Executing, mbot.Status );
      ibot.InvokeExecuteFinished( new OperationResultsEventsArgs( true ) );

      Thread.Sleep( 10 );
      Assert.AreEqual( MasterBot.BotStatus.Idle, receivedStatus );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot.Status );
      Assert.IsNull( receivedError );
    }

    [Test, Description( "Test that failed Execute() finishes correctly with proper state changes" )]
    public void TestExecuteFailure()
    {
      MockBot ibot = null;
			MasterBot mbot = GetMasterBotInState( MasterBot.BotStatus.Installed, out ibot );
      Assert.AreEqual( MasterBot.BotStatus.Installed, mbot.Status );

      Exception receivedError = null;
      MasterBot.BotStatus receivedStatus = MasterBot.BotStatus.Offline;
      mbot.OnStatusChanged += ( b, s, e ) => { receivedStatus = s; receivedError = e; };

      mbot.BeginExecute(  );
      Assert.AreEqual( MasterBot.BotStatus.Executing, mbot.Status );
      Exception passedException = new Exception( "test exception" );
      ibot.InvokeExecuteFinished( new OperationResultsEventsArgs( passedException ) );

      Thread.Sleep( 10 );
      Assert.AreEqual( MasterBot.BotStatus.Idle, receivedStatus );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot.Status );
      Assert.AreEqual( passedException, receivedError );
    }

    #endregion

    #region Halting tests

    [Test, Description( "Test that Halt() does nothing in Idle, not even a call to IBot" )]
    public void TestHaltInIdle()
    {
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );

      mbot.Halt();
      Assert.AreEqual( 0, ibot.HaltCalled );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot.Status );
    }

    [Test, Description( "Test that Halt() does nothing in Offline" )]
    public void TestHaltInOffline()
    {
      MasterBot mbot = new MasterBot( null );

      mbot.Halt();
      Assert.AreEqual( MasterBot.BotStatus.Offline, mbot.Status );
    }

    [Test, Description( "Test that Halt() returns any state to Idle" )]
    public void TestHaltStatusCheck()
    {
      foreach ( MasterBot.BotStatus statusValue in Enum.GetValues( typeof( MasterBot.BotStatus ) ) )
      {
        if ( statusValue == MasterBot.BotStatus.Idle || statusValue == MasterBot.BotStatus.Offline )
          continue;

        Trace.TraceInformation( "Getting Bot in state {0}", statusValue );
        MockBot ibot = null;
				MasterBot mbot = GetMasterBotInState( statusValue, out ibot );
        Assert.AreEqual( statusValue, mbot.Status );
        Trace.TraceInformation( "Got Bot in state {0}", statusValue );
        Exception receivedError = null;
        MasterBot.BotStatus receivedStatus = MasterBot.BotStatus.Offline;
        mbot.OnStatusChanged += ( b, s, e ) => { receivedStatus = s; receivedError = e; };
        Trace.TraceInformation( "Halting Bot in state {0}", statusValue );
        mbot.Halt();

        if ( statusValue == MasterBot.BotStatus.Loading )
          ibot.StopLoading();
        else if ( statusValue == MasterBot.BotStatus.Installing )
          ibot.InvokeInstallFinished( new OperationResultsEventsArgs( false ) );
        else if ( statusValue == MasterBot.BotStatus.Executing )
          ibot.InvokeExecuteFinished( new OperationResultsEventsArgs( false ) );

        Thread.Sleep( 50 );

        Assert.AreEqual( MasterBot.BotStatus.Idle, receivedStatus );
        Assert.AreEqual( MasterBot.BotStatus.Idle, mbot.Status );
        Assert.IsNull( receivedError );
      }
    }

    #endregion

    #region Disconnection tests

    [Test, Description( "Test that Disconnect() does nothing in Offline" )]
    public void TestDisconnectInOffline()
    {
      MasterBot mbot = new MasterBot( null );
      Assert.AreEqual( MasterBot.BotStatus.Offline, mbot.Status );

      mbot.Disconnect();
      Assert.AreEqual( MasterBot.BotStatus.Offline, mbot.Status );
    }

    [Test, Description( "Test that Disconnect() gets every state into Offline" )]
    public void TestDisconnectStatusCheck()
    {
      foreach ( MasterBot.BotStatus statusValue in Enum.GetValues( typeof( MasterBot.BotStatus ) ) )
      {
        if ( statusValue == MasterBot.BotStatus.Offline )
          continue;

        MockBot ibot = null;
				MasterBot mbot = GetMasterBotInState( statusValue, out ibot );
        Assert.AreEqual( statusValue, mbot.Status );

        Exception receivedError = null;
        MasterBot.BotStatus receivedStatus = MasterBot.BotStatus.Offline;
        mbot.OnStatusChanged += ( b, s, e ) => { receivedStatus = s; receivedError = e; };
        mbot.Disconnect();
        Thread.Sleep( 10 );

        Assert.AreEqual( MasterBot.BotStatus.Offline, receivedStatus );
        Assert.AreEqual( MasterBot.BotStatus.Offline, mbot.Status );
        Assert.IsNull( receivedError );
      }
    }

    #endregion

    #region Misc tests

    [Test, Description( "Test that Description points to correct object" )]
    public void TestDescription()
    {
      MockBot ibot = new MockBot( new BotDescription( "SuperBot", -1 ) );
      MasterBot mbot = new MasterBot( ibot );
      Assert.AreEqual( ibot.Description, mbot.Description );
    }

    #endregion
  }
}

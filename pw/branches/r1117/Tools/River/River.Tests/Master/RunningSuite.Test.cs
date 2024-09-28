using System;
using System.CodeDom.Compiler;
using System.Threading;
using NUnit.Framework;
using River.Core;
using River.Master;

namespace River.Tests.Master
{
  [TestFixture]
  public class RunningSuiteTests
  {
    #region Utility methods

    [SetUp]
    public void Setup()
    {
      GC.Collect();
      GC.WaitForFullGCComplete();
      GC.WaitForFullGCApproach();
    }

    #endregion

    #region Creation tests

    [Test, Description( "Test that RunningSuite and bots all have correct status when RunningSuite is created" )]
    public void TestRSnBotsCorrectStartingStatus()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      Assert.AreEqual( RunningSuite.SuiteStatus.Loading, rs.Status );
      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Loading, bot.Status );
    }

    [Test, Description( "Test that RunningSuite and bots all have correct status when RunningSuite is created" )]
    public void TestCorrectSwitchToInstalling()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      ibot1.StopLoading();
      ibot2.StopLoading();
      ThreadUtils.WaitFor( () => { return rs.Status == RunningSuite.SuiteStatus.Installing; } );

      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Installing, bot.Status );
    }

    [Test, Description( "Test that failed loading halts and frees the bots" )]
    public void TestFailedLoading1()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      ibot1.StopLoading( new CompilerError() );

      Thread.Sleep( 20 );
      ibot2.StopLoading();

      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Loading && mbot2.Status != MasterBot.BotStatus.Loading; } );
      Thread.Sleep( 20 );

      Assert.AreEqual( RunningSuite.SuiteStatus.Finished, rs.Status );
      Assert.IsTrue( rs.IsFailed );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot1.Status );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot2.Status );
      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Idle, bot.Status );
    }

    [Test, Description( "Test that failed loading halts and frees the bots" )]
    public void TestFailedLoading2()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      ibot2.StopLoading();
      ThreadUtils.WaitFor( () => { return mbot2.Status != MasterBot.BotStatus.Loading; } );

      ibot1.StopLoading( new CompilerError() );

      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Loading && mbot2.Status != MasterBot.BotStatus.Loading; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );

      Assert.AreEqual( RunningSuite.SuiteStatus.Finished, rs.Status );
      Assert.IsTrue( rs.IsFailed );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot1.Status );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot2.Status );
      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Idle, bot.Status );
    }

    #endregion

    #region Installation tests

    [Test, Description( "Test that translation of an RS to Installing invokes bot's Install()" )]
    public void TestSingleBotInstallInvocation()
    {
      BotNet bn = new BotNet();
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );
      bn.RegisterBot( mbot );
      RunningSuite rs = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
      ibot.StopLoading();
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );

      Assert.AreEqual( 1, ibot.InstallCalled );
    }

    [Test, Description( "Test that RunningSuite and bots all have correct status when switching to Executing" )]
    public void TestCorrectSwitchToExecuting() 
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      ibot1.StopLoading();
      ibot2.StopLoading();
      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Loading && mbot2.Status != MasterBot.BotStatus.Loading; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );

      ibot1.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );
      ibot2.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );

      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Installing && mbot2.Status != MasterBot.BotStatus.Installing; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Installing; } );

      Assert.AreEqual( RunningSuite.SuiteStatus.Executing, rs.Status );
      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Executing, bot.Status );
    }

    [Test, Description( "Test that failed installation halts and frees the bots" )]
    public void TestFailedInstallation1()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      ibot1.StopLoading();
      ibot2.StopLoading();
      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Loading && mbot2.Status != MasterBot.BotStatus.Loading; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );

      ibot1.InvokeInstallFinished( new OperationResultsEventsArgs( new Exception() ) );
      ThreadUtils.WaitFor( () => { return ibot2.HaltCalled > 0; } );
      ibot2.InvokeInstallFinished( new OperationResultsEventsArgs( new Exception() ) );

      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Installing && mbot2.Status != MasterBot.BotStatus.Installing; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Installing; } );

      Assert.AreEqual( RunningSuite.SuiteStatus.Finished, rs.Status );
      Assert.IsTrue( rs.IsFailed );
      Assert.AreEqual( 1, ibot2.HaltCalled );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot1.Status );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot2.Status );
      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Idle, bot.Status );
    }

    [Test, Description( "Test that failed installation halts and frees the bots" )]
    public void TestFailedInstallation2()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      ibot1.StopLoading();
      ibot2.StopLoading();
      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Loading && mbot2.Status != MasterBot.BotStatus.Loading; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );
      Assert.AreEqual( RunningSuite.SuiteStatus.Installing, rs.Status );

      ibot2.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );
      ThreadUtils.WaitFor( () => { return mbot2.Status != MasterBot.BotStatus.Installing; } );

      ibot1.InvokeInstallFinished( new OperationResultsEventsArgs( new Exception() ) );
      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Installing; } );

      Assert.AreEqual( RunningSuite.SuiteStatus.Finished, rs.Status );
      Assert.IsTrue( rs.IsFailed );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot1.Status );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot2.Status );
      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Idle, bot.Status );
    }

    #endregion

    #region Execution tests

    [Test, Description( "Test that translation of an RS to Executing invokes bot's Execute()" )]
    public void TestSingleBotExecuteInvocation()
    {
      BotNet bn = new BotNet();
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );
      bn.RegisterBot( mbot );
      RunningSuite rs = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
      ibot.StopLoading();
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );

      ibot.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Installing; } );

      Assert.AreEqual( 1, ibot.ExecuteCalled );
    }

    [Test, Description( "Test that RunningSuite and bots all have correct status when finishing Executing" )]
    public void TestCorrectExecutingStatusChanges()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      ibot1.StopLoading();
      ibot2.StopLoading();
      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Loading && mbot2.Status != MasterBot.BotStatus.Loading; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );

      ibot1.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );
      ibot2.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );

      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Installing && mbot2.Status != MasterBot.BotStatus.Installing; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Installing; } );

      ibot1.InvokeExecuteFinished( new OperationResultsEventsArgs( true ) );
      ibot2.InvokeExecuteFinished( new OperationResultsEventsArgs( true ) );

      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Executing && mbot2.Status != MasterBot.BotStatus.Executing; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Executing; } );

      Assert.AreEqual( RunningSuite.SuiteStatus.Finished, rs.Status );
      Assert.IsFalse( rs.IsFailed );
      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Idle, bot.Status );
    }

    [Test, Description( "Test that failed execution halts and frees the bots" )]
    public void TestFailedExecution1()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      ibot1.StopLoading();
      ibot2.StopLoading();
      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Loading && mbot2.Status != MasterBot.BotStatus.Loading; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );

      ibot1.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );
      ibot2.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );

      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Installing && mbot2.Status != MasterBot.BotStatus.Installing; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Installing; } );

      ibot1.InvokeExecuteFinished( new OperationResultsEventsArgs( new Exception() ) );
      ThreadUtils.WaitFor( () => { return ibot2.HaltCalled > 0; } );
      ibot2.InvokeExecuteFinished( new OperationResultsEventsArgs( new Exception() ) );

      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Executing && mbot2.Status != MasterBot.BotStatus.Executing; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Executing; } );

      Assert.AreEqual( RunningSuite.SuiteStatus.Finished, rs.Status );
      Assert.IsTrue( rs.IsFailed );
      Assert.AreEqual( 1, ibot2.HaltCalled );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot1.Status );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot2.Status );
      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Idle, bot.Status );
    }

    [Test, Description( "Test that failed execution halts and frees the bots" )]
    public void TestFailedExecution2()
    {
      BotNet bn = new BotNet();
      MockBot ibot1 = new MockBot();
      MasterBot mbot1 = new MasterBot( ibot1 );
      bn.RegisterBot( mbot1 );
      MockBot ibot2 = new MockBot();
      MasterBot mbot2 = new MasterBot( ibot2 );
      bn.RegisterBot( mbot2 );

      RunningSuite rs = bn.CreateRunningSuite("TwoBotsSuite", null, Scenarios.Scenarios.TwoBotsSuite, Guid.Empty);
      ibot1.StopLoading();
      ibot2.StopLoading();
      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Loading && mbot2.Status != MasterBot.BotStatus.Loading; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );

      ibot1.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );
      ibot2.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );

      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Installing && mbot2.Status != MasterBot.BotStatus.Installing; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Installing; } );

      ibot2.InvokeExecuteFinished( new OperationResultsEventsArgs( true ) );
      ThreadUtils.WaitFor( () => { return mbot2.Status != MasterBot.BotStatus.Executing; } );

      ibot1.InvokeExecuteFinished( new OperationResultsEventsArgs( new Exception() ) );
      ThreadUtils.WaitFor( () => { return mbot1.Status != MasterBot.BotStatus.Executing; } );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Executing; } );

      Assert.AreEqual( RunningSuite.SuiteStatus.Finished, rs.Status );
      Assert.IsTrue( rs.IsFailed );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot1.Status );
      Assert.AreEqual( MasterBot.BotStatus.Idle, mbot2.Status );
      Assert.AreEqual( 2, rs.Bots.Count );
      foreach ( var bot in rs.Bots )
        Assert.AreEqual( MasterBot.BotStatus.Idle, bot.Status );
    }
    
    #endregion

    #region Bot status tests

    [Ignore]
    [Test, Description( "Test that BotDescription-s are independent from bots themselves" )]
    public void TestRSBotStatusIndependence()
    {
      BotNet bn = new BotNet();
      MockBot ibot = new MockBot();
      MasterBot mbot = new MasterBot( ibot );
      bn.RegisterBot( mbot );
      RunningSuite rs = bn.CreateRunningSuite("OneBotSuite", null, Scenarios.Scenarios.OneBotSuite, Guid.Empty);
      RunningBotStatus bdLoading = rs.Bots[0];

      ibot.StopLoading();
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Loading; } );
      Thread.Sleep( 100 );

      RunningBotStatus bdInstalling = rs.Bots[0];

      ibot.InvokeInstallFinished( new OperationResultsEventsArgs( true ) );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Installing; } );

      RunningBotStatus bdExecuting = rs.Bots[0];

      ibot.InvokeExecuteFinished( new OperationResultsEventsArgs( true ) );
      ThreadUtils.WaitFor( () => { return rs.Status != RunningSuite.SuiteStatus.Executing; } );

      RunningBotStatus bdFinished = rs.Bots[0];

      Assert.AreEqual( MasterBot.BotStatus.Loading, bdLoading.Status );
      Assert.AreEqual( MasterBot.BotStatus.Installing, bdInstalling.Status );
      Assert.AreEqual( MasterBot.BotStatus.Executing, bdExecuting.Status );
      Assert.AreEqual( MasterBot.BotStatus.Idle, bdFinished.Status );
    }

    #endregion
  }
}

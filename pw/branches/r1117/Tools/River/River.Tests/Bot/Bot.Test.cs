using System;
using System.CodeDom.Compiler;
using System.IO;
using System.Threading;
using NUnit.Framework;
using River.Bot;
using River.Core;
using River.Core.Diagnostics;
using River.Tests.Context;

namespace River.Tests.Bot
{
  [TestFixture]
  public class BotTests
  {
    #region Utility methods

    string tempFile1 = string.Empty;
    string tempFile2 = string.Empty;

    [SetUp]
    public void TempFileSetup()
    {
      tempFile1 = Path.GetTempFileName();
      tempFile2 = Path.GetTempFileName();
    }

    [TearDown]
    public void TempFileTeardown()
    {
      Thread.Sleep( 100 );
      File.Delete( tempFile1 );
      File.Delete( tempFile2 );
    }

    #endregion

    #region Load() tests

    [Test, Description( "Test that Load() compiles a correct scenario" )]
    public void TestBotLoadCompileSuccess()
    {
      string code = Scenarios.Scenarios.SimpleCorrectScenario;

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "SimpleCorrectScenario", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );
      Assert.IsFalse( e.HasWarnings );
    }

    [Test, Description( "Test that Load() compiles and returns a correct error (CS1519) at (8,6)" )]
    public void TestBotLoadCompileError()
    {
      string code = Scenarios.Scenarios.SimpleUnbuildableScenario;

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "SimpleUnbuildableScenario", null );
      Assert.IsNotNull( e );
      Assert.IsTrue( e.HasErrors );
      Assert.AreEqual( 1, e.Count );
      Assert.AreEqual( "CS1519", e[0].ErrorNumber );
      Assert.AreEqual( 8, e[0].Line );
      Assert.AreEqual( 6, e[0].Column );
    }

    [Test, Description( "Test that Load() returns correct diag when new fails" )]
    public void TestBotLoadNullScenario()
    {
      string code = Scenarios.Scenarios.SimpleNonloadableScenario;

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "SimpleNonloadableScenario", null );
      Assert.IsNotNull( e );
      Assert.IsTrue( e.HasErrors );
      Assert.AreEqual( 1, e.Count );
      Assert.AreEqual( "InvalidOperationException", e[0].ErrorNumber );
      Assert.AreEqual( 0, e[0].Line );
      Assert.AreEqual( 0, e[0].Column );
    }

    [Test, Description( "Test that Load() returns correct diag when an exception occurs" )]
    public void TestBotLoadException()
    {
      string code = Scenarios.Scenarios.SimpleExceptionScenario;

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "SimpleExceptionScenario", null );
      Assert.IsNotNull( e );
      Assert.IsTrue( e.HasErrors );
      Assert.AreEqual( 1, e.Count );
      Assert.AreEqual( "Exception", e[0].ErrorNumber );
      Assert.AreEqual( "Qwerty", e[0].ErrorText );
      Assert.AreEqual( 0, e[0].Line );
      Assert.AreEqual( 0, e[0].Column );
    }

    #endregion

    #region BeginInstall() tests

    [Test, Description( "Test that Install() gets executed on BeginInstall()" )]
    public void TestBotInstall()
    {
      string code = Scenarios.Scenarios.ScenarioInstallAndExecute.Replace( "<FILE1>", tempFile1.Replace( "\\", "\\\\" ) );

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioInstallAndExecute", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      Assert.IsNotNull( InstallOperationResults );
      Assert.IsTrue( InstallOperationResults.Success );
      Assert.AreEqual( "I", File.ReadAllText( tempFile1 ) );
    }

    [Test, Description( "Test that Install reports exceptions correctly" )]
    public void TestBotInstallException()
    {
      string code = Scenarios.Scenarios.ScenarioInstallException;
      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioInstallException", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      Assert.IsNotNull( InstallOperationResults );
      Assert.IsFalse( InstallOperationResults.Success );
      Assert.IsNotNull( InstallOperationResults.Exception );
      Assert.AreEqual( "InstallException", InstallOperationResults.Exception.Message );
    }

    #endregion

    #region BeginExecute() tests

    [Test, Description( "Test that Execute() gets run on BeginExecute()" )]
    public void TestBotExecute()
    {
      string code = Scenarios.Scenarios.ScenarioInstallAndExecute.Replace( "<FILE1>", tempFile1.Replace( "\\", "\\\\" ) );
      code = code.Replace( "<FILE2>", tempFile2.Replace( "\\", "\\\\" ) );

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioInstallAndExecute", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      Assert.IsNotNull( InstallOperationResults );

      OperationResultsEventsArgs ExecuteOperationResults = null;
      b.ExecuteFinished += ( bot, results ) => { ExecuteOperationResults = results; };
      b.BeginExecute();
      ThreadUtils.WaitFor( () => { return null != ExecuteOperationResults; } );
      Assert.IsNotNull( ExecuteOperationResults );
      Assert.IsTrue( ExecuteOperationResults.Success );
      Assert.AreEqual( "E", File.ReadAllText( tempFile2 ) );
    }

    [Test, Description( "Test that exception thrown during Execute() gets reported" )]
    public void TestBotExecuteException()
    {
      string code = Scenarios.Scenarios.ScenarioExecuteException;

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioExecuteException", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      Assert.IsNotNull( InstallOperationResults );

      OperationResultsEventsArgs ExecuteOperationResults = null;
      b.ExecuteFinished += ( bot, results ) => { ExecuteOperationResults = results; };
      b.BeginExecute();
      ThreadUtils.WaitFor( () => { return null != ExecuteOperationResults; } );
      Assert.IsNotNull( ExecuteOperationResults );
      Assert.IsFalse( ExecuteOperationResults.Success );
      Assert.IsNotNull( ExecuteOperationResults.Exception );
      Assert.AreEqual( "ExecuteException", ExecuteOperationResults.Exception.Message );
    }

    #endregion

    #region Halt() tests

    [Test, Description( "Test that Halt() halts Install() without exceptions" )]
    public void TestBotHaltInstall()
    {
      string code = Scenarios.Scenarios.ScenarioVeryLongInstall;

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioVeryLongInstall", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      b.Halt();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      Assert.IsNotNull( InstallOperationResults );
      Assert.IsFalse( InstallOperationResults.Success );
      Assert.IsNull( InstallOperationResults.Exception );
    }

    [Test, Description( "Test that Halt() halts Execute() without exceptions" )]
    public void TestBotHaltExecute()
    {
      string code = Scenarios.Scenarios.ScenarioVeryLongExecute;

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioVeryLongExecute", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      Assert.IsNotNull( InstallOperationResults );
      Assert.IsTrue( InstallOperationResults.Success );

      OperationResultsEventsArgs ExecuteOperationResults = null;
      b.ExecuteFinished += ( bot, results ) => { ExecuteOperationResults = results; };
      b.BeginExecute();
      b.Halt();
      Log.TraceDebug( "BeginWait" );
      ThreadUtils.WaitFor( () => { return null != ExecuteOperationResults; } );
      Log.TraceDebug( "EndWait" );
      Assert.IsNotNull( ExecuteOperationResults );
      Assert.IsFalse( ExecuteOperationResults.Success );
      Assert.IsNull( ExecuteOperationResults.Exception );
    }

    #endregion

    #region Environment.CurrentDirectory tests

    [Test, Description( "Test that same CurrentDirectory exists after Install() and doesn't exist after Execute()" )]
    public void TestBotInstallExecuteDirectorySame()
    {
      string code = Scenarios.Scenarios.ScenarioCurrentDirectory.Replace( "<FILE1>", tempFile1.Replace( "\\", "\\\\" ) );
      code = code.Replace( "<FILE2>", tempFile2.Replace( "\\", "\\\\" ) );

      string outerDirectory = Environment.CurrentDirectory;

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioCurrentDirectory", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      string installDirectory = File.ReadAllText( tempFile1 );
      Assert.AreNotEqual( outerDirectory, installDirectory );
      Assert.IsTrue( Directory.Exists( installDirectory ) );

      OperationResultsEventsArgs ExecuteOperationResults = null;
      b.ExecuteFinished += ( bot, results ) => { ExecuteOperationResults = results; };
      b.BeginExecute();
      ThreadUtils.WaitFor( () => { return null != ExecuteOperationResults; } );
      string executeDirectory = File.ReadAllText( tempFile2 );
      Assert.AreEqual( installDirectory, executeDirectory );
      Assert.IsFalse( Directory.Exists( installDirectory ) );
    }

    [Test, Description( "Test CurrentDirectory exists during Install() and is cleaned up on Halt()" )]
    public void TestBotInstallDirectoryExistsAndIsHalted()
    {
      string code = Scenarios.Scenarios.ScenarioCurrentDirectory.Replace( "<FILE1>", tempFile1.Replace( "\\", "\\\\" ) );
      code = code.Replace( "<FILE2>", tempFile2.Replace( "\\", "\\\\" ) );
      code = code.Replace( "waitInInstall = false", "waitInInstall = true" );

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioCurrentDirectory", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return File.Exists( tempFile1 ); } );
      Thread.Sleep( 100 );
      string installDirectory = File.ReadAllText( tempFile1 );
      Assert.IsTrue( Directory.Exists( installDirectory ) );
      b.Halt();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      Assert.IsFalse( Directory.Exists( installDirectory ) );
    }

    [Test, Description( "Test CurrentDirectory is cleaned up on exception in Install()" )]
    public void TestBotInstallDirectoryCleanedOnException()
    {
      string code = Scenarios.Scenarios.ScenarioCurrentDirectory.Replace( "<FILE1>", tempFile1.Replace( "\\", "\\\\" ) );
      code = code.Replace( "<FILE2>", tempFile2.Replace( "\\", "\\\\" ) );
      code = code.Replace( "throwInstallException = false", "throwInstallException = true" );

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioCurrentDirectory", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      string installDirectory = File.ReadAllText( tempFile1 );
      Assert.IsFalse( Directory.Exists( installDirectory ) );
    }

    [Test, Description( "Test CurrentDirectory exists during Execute() and is cleaned up on Halt()" )]
    public void TestBotExecuteDirectoryExistsAndIsHalted()
    {
      string code = Scenarios.Scenarios.ScenarioCurrentDirectory.Replace( "<FILE1>", tempFile1.Replace( "\\", "\\\\" ) );
      code = code.Replace( "<FILE2>", tempFile2.Replace( "\\", "\\\\" ) );
      code = code.Replace( "waitInExecute = false", "waitInExecute = true" );

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioCurrentDirectory", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );

      OperationResultsEventsArgs ExecuteOperationResults = null;
      b.ExecuteFinished += ( bot, results ) => { ExecuteOperationResults = results; };
      b.BeginExecute();
      ThreadUtils.WaitFor( () => { return File.Exists( tempFile2 ); } );
      Thread.Sleep( 100 );
      string executeDirectory = File.ReadAllText( tempFile2 );
      Assert.IsTrue( Directory.Exists( executeDirectory ) );
      b.Halt();
      ThreadUtils.WaitFor( () => { return null != ExecuteOperationResults; } );
      Assert.IsFalse( Directory.Exists( executeDirectory ) );
    }

    [Test, Description( "Test CurrentDirectory is cleaned up on exception in Execute()" )]
    public void TestBotExecuteDirectoryCleanedOnException()
    {
      string code = Scenarios.Scenarios.ScenarioCurrentDirectory.Replace( "<FILE1>", tempFile1.Replace( "\\", "\\\\" ) );
      code = code.Replace( "<FILE2>", tempFile2.Replace( "\\", "\\\\" ) );
      code = code.Replace( "throwExecuteException = false", "throwExecuteException = true" );

      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioCurrentDirectory", null );
      Assert.IsNotNull( e );
      Assert.IsFalse( e.HasErrors );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );

      OperationResultsEventsArgs ExecuteOperationResults = null;
      b.ExecuteFinished += ( bot, results ) => { ExecuteOperationResults = results; };
      b.BeginExecute();
      string executeDirectory = File.ReadAllText( tempFile2 );
      Assert.IsFalse( Directory.Exists( executeDirectory ) );
    }

    #endregion

    #region Miscellaneous tests

    [Test, Description( "Test that SyncContext is properly passed to the scenario" )]
    public void TestBotPassesContext()
    {
      string code = Scenarios.Scenarios.ScenarioCheckContext;

      MockSyncContext context = new MockSyncContext();
      ClientBot b = new ClientBot();
      CompilerErrorCollection e = b.Load( code, "ScenarioCheckContext", context );

      OperationResultsEventsArgs InstallOperationResults = null;
      b.InstallFinished += ( bot, results ) => { InstallOperationResults = results; };
      b.BeginInstall();
      ThreadUtils.WaitFor( () => { return null != InstallOperationResults; } );
      Assert.IsTrue( InstallOperationResults.Success );

      OperationResultsEventsArgs ExecuteOperationResults = null;
      b.ExecuteFinished += ( bot, results ) => { ExecuteOperationResults = results; };
      b.BeginExecute();
      ThreadUtils.WaitFor( () => { return null != ExecuteOperationResults; } );
      Assert.IsTrue( ExecuteOperationResults.Success );

      Assert.AreEqual( 1, context.SyncIncCalled );
      Assert.AreEqual( "var1", context.SyncIncParam );
      Assert.AreEqual( 1, context.SyncDecCalled );
      Assert.AreEqual( "var2", context.SyncDecParam );
    }

    #endregion

  }
}

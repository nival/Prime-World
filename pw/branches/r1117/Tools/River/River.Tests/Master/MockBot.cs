using System;
using System.CodeDom.Compiler;
using System.Threading;
using River.Core;

namespace River.Tests.Master
{
  public class MockBot : IBot
  {
		private CompilerErrorCollection loadedErrors = null;
		private CompilerErrorCollection loadedErrorsResults = null;

    public MockBot() : this( new BotDescription( "MockBot", -1 ) ) { }

		public MockBot( BotDescription desc )
		{
			Description = desc;
			LoadCalled = 0;
			InstallCalled = 0;
			ExecuteCalled = 0;
			HaltCalled = 0;
		}

		public BotDescription Description { get; private set; }

    public CompilerErrorCollection Load( string suite, string type, ISyncContext context )
    {
			loadedErrorsResults = null;
      ++LoadCalled;
      LoadedSuite = suite;
      LoadedType = type;
      LoadedContext = context;
      while ( loadedErrors == null )
				Thread.Sleep( 10 );

			loadedErrorsResults = loadedErrors;
			loadedErrors = null;
			return loadedErrorsResults;
    }

		public void StopLoading( params CompilerError[] errors )
		{
			loadedErrors = new CompilerErrorCollection( errors );
		}

		public int LoadCalled { get; private set; }

		public string LoadedSuite { get; private set; }
		public string LoadedType { get; private set; }
    public ISyncContext LoadedContext { get; private set; }

		public bool Loading { get { return loadedErrorsResults == null; } }

    public void BeginInstall()
    {
      ++InstallCalled;
    }

		public int InstallCalled { get; private set; }

    public event BotOperationFinishedEventHandler InstallFinished;
    public void InvokeInstallFinished( OperationResultsEventsArgs e )
    {
      if ( null != InstallFinished )
        InstallFinished( this, e );
    }

    public void BeginExecute()
    {
      ++ExecuteCalled;
    }

		public int ExecuteCalled { get; private set; }

    public event BotOperationFinishedEventHandler ExecuteFinished;
    public void InvokeExecuteFinished( OperationResultsEventsArgs e )
    {
      if ( null != ExecuteFinished )
        ExecuteFinished( this, e );
    }

    public void Ping()
    {
    }

    public void Halt()
    {
      ++HaltCalled;
    }

		public int HaltCalled { get; private set; }
  }
}

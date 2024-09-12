using System;
using System.Net;
using System.CodeDom.Compiler;

namespace River.Core
{
	[Serializable]
	public class BotDescription
	{
    private readonly string name;
    private readonly long botID;

		public BotDescription( string name, long id )
		{
      this.name = name;
      botID = id;
		}

    public string Name { get { return name; } }
    public long ID { get { return botID; } }

    public override string ToString()
    {
      return String.Format("{0}({1})", name, botID);
    }
  }

	[Serializable]
	public class OperationResultsEventsArgs : EventArgs
	{
		private readonly bool success = false;
		private readonly Exception exception = null;

		public OperationResultsEventsArgs( bool success ) { this.success = success; }
		public OperationResultsEventsArgs( Exception exception ) { this.success = false; this.exception = exception; }

		public bool Success { get { return success; } }
		public Exception Exception { get { return exception; } }
	}

	public delegate void BotOperationFinishedEventHandler( IBot bot, OperationResultsEventsArgs results );

	public interface IBot
	{
		BotDescription Description { get; }

    CompilerErrorCollection Load( string scenario, string type, ISyncContext context );

		void BeginInstall();
		event BotOperationFinishedEventHandler InstallFinished;

    void BeginExecute();
		event BotOperationFinishedEventHandler ExecuteFinished;

    void Ping();
    void Halt();
	}
}

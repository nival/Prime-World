using System;
using System.CodeDom.Compiler;
using System.ComponentModel;
using System.IO;
using System.Net;
using log4net;
using River.Core;
using River.Core.Suite;

namespace River.Bot
{
	public class ClientBot : MarshalByRefObject, IBot
	{
    private static readonly ILog logger = LogManager.GetLogger(typeof(ClientBot));

    public override object InitializeLifetimeService()
    {
      return null;
    }
    
    public enum BotStatus
		{
			Offline,
			Online,
			Busy,
		}

		public delegate void BotStatusChangedEventHandler( ClientBot bot, BotStatus status, string statusMessage );

    private BotDescription description = null;
    
		private IMaster master = null;
		private BotStatus status = BotStatus.Offline;
		private string statusMessage = string.Empty;

    private Suite activeSuite = null;
    private Scenario activeScenario = null;

    private ClientContext localContext = null;

    private string oldCurrentDirectory = string.Empty;

    public ClientBot()
    {
    }

    public void Initialize( long id )
    {
      description = new BotDescription( Dns.GetHostName(), id );
    }

		public void Connect( string masterUrl )
		{
			master = Activator.GetObject( typeof( IMaster ), masterUrl ) as IMaster;
      master.Connect( this, Initialize );
			SetBotStatus( BotStatus.Online, String.Format("({0}) {1}", Description.ID, masterUrl ));
		}

    public void MasterDisconnected()
    {
      InstallFinished = null;
      ExecuteFinished = null;
      logger.Info("Connection with master is lost. Bot will be halted.");
      Halt();
      SetBotStatus(BotStatus.Offline, string.Empty);
    }

    public void Disconnect()
    {
      logger.Info("Disconnecting from master");
      master.Disconnect(this.Description.ID);
      SetBotStatus(BotStatus.Offline, string.Empty);
    }

	  public void ExecuteSuite(string filename, string suite, Guid suiteID )
		{
      try
      {
        master.ExecuteSuite(filename, null, suite, suiteID, null, null);
      }
      catch(Exception ex)
      {
        logger.Warn("Error while executing suite.", ex);
      }
		}

		private void SetBotStatus( BotStatus status, string statusMessage )
		{
			this.status = status;
			this.statusMessage = statusMessage;
			if ( OnBotStatusChanged != null )
				OnBotStatusChanged( this, status, statusMessage );
      logger.InfoFormat("Bot {0} change status to {1}. Status message: \"{2}\"", this.description, status, statusMessage);
		}

		public event BotStatusChangedEventHandler OnBotStatusChanged = null;

		public BotDescription Description
		{
			get { return description; }
		}

    public CompilerErrorCollection Load( string scenario, string type, ISyncContext context )
		{
      logger.InfoFormat("Load CSharp scenario {0}", type);
      CompilerErrorCollection e = null;
      activeSuite = new Suite( scenario, "CSharp" );
      activeScenario = null;
      try
      {
        activeScenario = activeSuite.CreateScenario( type, out e );
        if ( e.HasErrors )
          return e;

        if ( ReferenceEquals( activeScenario, null ) )
          e.Add( new CompilerError( string.Empty, 0, 0, string.Empty, string.Empty ) );
        else
          localContext = new ClientContext( context, description );
      }
      catch ( InvalidOperationException outerException )
      {
        logger.Warn("InvalidOperationException while loading scenario", outerException);
        Exception ex = outerException;
        while ( ex.InnerException != null )
          ex = ex.InnerException;

        e.Add( new CompilerError( string.Empty, 0, 0, ex.GetType().Name, ex.Message ) );
      }
      catch ( Exception ex )
      {
        logger.Warn("Error loading scenario", ex);
        e.Add( new CompilerError( string.Empty, 0, 0, ex.GetType().Name, ex.Message ) );
      }

      return e;
    }

    #region Install

		public event BotOperationFinishedEventHandler InstallFinished;

    public void BeginInstall()
		{
      logger.Debug("BeginInstall");

      if ( null == activeScenario )
      {
        if ( InstallFinished != null )
          InstallFinished( this, new OperationResultsEventsArgs( false ) );
      }

      oldCurrentDirectory = Environment.CurrentDirectory;
      logger.DebugFormat("Creating directory", activeSuite.SuitePath);
      Directory.CreateDirectory( activeSuite.SuitePath );
      Environment.CurrentDirectory = activeSuite.SuitePath;

      BackgroundWorker bw = new BackgroundWorker();
      bw.WorkerSupportsCancellation = true;
      bw.RunWorkerCompleted += InstallFinishedEventHandler;
      bw.DoWork += InstallDoWork;
      bw.RunWorkerAsync( localContext );
		}

    private void InstallDoWork( object sender, DoWorkEventArgs e )
    {
      logger.Debug("Installing active scenario");
      activeScenario.Install( e.Argument as IContext );
    }

    private void InstallFinishedEventHandler( object sender, RunWorkerCompletedEventArgs e )
    {
      logger.Debug("Installing active scenario finished");
      Environment.CurrentDirectory = oldCurrentDirectory;
      if ( null != e.Error )
      {
        CleanUp();
        if ( InstallFinished != null )
          InstallFinished( this, new OperationResultsEventsArgs( ( e.Error is AppDomainUnloadedException ) ? null : e.Error ) );
      }
      else
      {
        if ( InstallFinished != null )
          InstallFinished( this, new OperationResultsEventsArgs( true ) );
      }
    }

    #endregion

    #region Execute

		public event BotOperationFinishedEventHandler ExecuteFinished;

    public void BeginExecute()
		{
      logger.Debug("BeginExecute");
      if ( null == activeScenario )
      {
        if ( ExecuteFinished != null )
          ExecuteFinished( this, new OperationResultsEventsArgs( false ) );
      }

      oldCurrentDirectory = Environment.CurrentDirectory;
      Environment.CurrentDirectory = activeSuite.SuitePath;

      BackgroundWorker bw = new BackgroundWorker();
      bw.WorkerSupportsCancellation = true;
      bw.RunWorkerCompleted += ExecuteFinishedEventHandler;
      bw.DoWork += ExecuteDoWork;
      bw.RunWorkerAsync( localContext );
    }

    private void ExecuteDoWork( object sender, DoWorkEventArgs e )
    {
      logger.Debug("Executing active scenario");
      activeScenario.Execute( e.Argument as IContext );
    }

    private void ExecuteFinishedEventHandler( object sender, RunWorkerCompletedEventArgs e )
    {
      Environment.CurrentDirectory = oldCurrentDirectory;
      CleanUp();
      if ( null != e.Error )
      {
        if ( ExecuteFinished != null )
          ExecuteFinished( this, new OperationResultsEventsArgs( ( e.Error is AppDomainUnloadedException ) ? null : e.Error ) );
      }
      else
      {
        if ( ExecuteFinished != null )
          ExecuteFinished( this, new OperationResultsEventsArgs( true ) );
      }
    }
    #endregion

	  public void Ping()
	  {
	  }

	  public void Halt()
    {
      logger.Info("Halting bot and cleanup active suite.");
      try
      {
        activeSuite.CleanUp();
      }
      catch(Exception ex)
      {
        logger.Warn("Exception while cleanup active suite", ex);
      }
    }

    private void CleanUp()
    {
      try
      {
        activeSuite.CleanUp();

        if (Directory.Exists(activeSuite.SuitePath))
          Directory.Delete(activeSuite.SuitePath, true);
      }
      catch(Exception ex)
      {
        logger.Warn("Exception while cleanup active suite", ex);
      }
    }

    ~ClientBot()
    {
      if ( null != activeSuite )
        CleanUp();
    }
	}
}

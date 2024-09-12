using System;
using System.Collections.Generic;
using System.Text;
using log4net;
using River.Core;
using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Threading;

namespace River.Master
{
	public class MasterBot : MarshalByRefObject
	{
    public override object InitializeLifetimeService()
    {
      return null;
    }

		public enum BotStatus
		{
			Offline,
			Idle,
			Loading,
			Loaded,
			Installing,
			Installed,
			Executing
		};

		private BotStatus currentStatus = BotStatus.Offline;
		private IBot bot = null;

    private static readonly ILog logger = LogManager.GetLogger(typeof(Master));

    // Для проверки чтобы несколько MasterBot'ов не ссылались на один IBot
    internal IBot Bot { get { return bot; } }

		private bool halting = false;

		private BackgroundWorker loadingWorker = null;

		private class LoadingParameters
		{
			public readonly IBot bot = null;
			public readonly string loadingSuite = string.Empty;
			public readonly string loadingType = string.Empty;
      public readonly ISyncContext context = null;

      public LoadingParameters( IBot bot, string suite, string type, ISyncContext context )
			{
				this.bot = bot;
				this.loadingSuite = suite;
				this.loadingType = type;
        this.context = context;
			}
		}

		public MasterBot( IBot _bot )
		{
			bot = _bot;
			if ( null == bot )
			{
				currentStatus = BotStatus.Offline;
			}
			else
			{
				currentStatus = BotStatus.Idle;
				bot.ExecuteFinished += OnBotExecuteFinished;
				bot.InstallFinished += OnBotInstallFinished;
				_botDescription = bot.Description ?? new BotDescription(String.Empty, 0);
			}
		}

    private BotDescription _botDescription;
    public BotDescription Description { get { return _botDescription; } }

		public void Load( string suite, string type, ISyncContext context )
		{
			if ( currentStatus != BotStatus.Idle )
				throw new InvalidOperationException();

			loadingWorker = new BackgroundWorker();
			loadingWorker.WorkerSupportsCancellation = true;
			loadingWorker.DoWork += OnLoading;
			loadingWorker.RunWorkerCompleted += OnLoadingComplete;
		  SetStatus( BotStatus.Loading, null );
		  loadingWorker.RunWorkerAsync( new LoadingParameters( bot, suite, type, context ) );
		}

		private void OnLoading( object sender, DoWorkEventArgs e )
		{
			LoadingParameters loadingParams = e.Argument as LoadingParameters;
			e.Result = loadingParams.bot.Load( loadingParams.loadingSuite, loadingParams.loadingType, loadingParams.context );
			if ( ( sender as BackgroundWorker ).CancellationPending )
				e.Cancel = true;
		}

		private void OnLoadingComplete( object sender, RunWorkerCompletedEventArgs e )
		{
			loadingWorker.DoWork -= OnLoading;
			loadingWorker.RunWorkerCompleted -= OnLoadingComplete;
			loadingWorker.Dispose();
			loadingWorker = null;

			if ( e.Cancelled || halting || e.Error != null )
			{
				halting = false;
				SetStatus( BotStatus.Idle, null );
        if (e.Cancelled) logger.InfoFormat("Bot {0} OnLoadingComplete : background worker cancelled", bot.Description);
        if (halting) logger.InfoFormat("Bot {0} OnLoadingComplete : halting scenario", bot.Description);
        if (e.Error != null) logger.WarnFormat("Bot {0} OnLoadingComplete : got an error \n {1}", bot.Description, e.Error);
			}
			else
			{
				CompilerErrorCollection compileResult = e.Result as CompilerErrorCollection;
				if ( null == compileResult || compileResult.HasErrors || compileResult.HasWarnings )
					SetStatus( BotStatus.Idle, new SuiteLoadException( compileResult ) );
				else
					SetStatus( BotStatus.Loaded, null );
			}
		}

		public void Halt()
		{
			if ( halting || currentStatus == BotStatus.Offline )
				return;

			switch ( currentStatus )
			{
			case BotStatus.Loading:
				halting = true;
				loadingWorker.CancelAsync();
				break;
			case BotStatus.Loaded:
				SetStatus( BotStatus.Idle, null );
				break;
			case BotStatus.Installing:
				halting = true;
				bot.Halt();
				break;
			case BotStatus.Installed:
				SetStatus( BotStatus.Idle, null );
				break;
			case BotStatus.Executing:
				halting = true;
				bot.Halt();
				break;
			}
		}

		public void BeginInstall()
		{
			if ( currentStatus != BotStatus.Loaded )
				throw new InvalidOperationException();

			bot.BeginInstall();
			SetStatus( BotStatus.Installing, null );
		}

		public void OnBotInstallFinished( IBot bot, OperationResultsEventsArgs results )
		{
			if ( results.Success )
				SetStatus( BotStatus.Installed, null );
			else
				SetStatus( BotStatus.Idle, results.Exception );
		}

    public void BeginExecute()
		{
			if ( currentStatus != BotStatus.Installed )
				throw new InvalidOperationException();

			bot.BeginExecute();
			SetStatus( BotStatus.Executing, null );
		}

		public void OnBotExecuteFinished( IBot bot, OperationResultsEventsArgs results )
		{
			SetStatus( BotStatus.Idle, results.Exception );
		}

    /// <summary>
    /// Пинг клиентского бота.
    /// </summary>
    /// <returns>Возвращается false если клиент отвалился без предупреждения</returns>
    public bool Ping()
    {
      try
      {
        bot.Ping();
        return true;
      }
      catch (System.Net.Sockets.SocketException e)
      {
        BotTerminated(e);
        return false;
      }
    }

		public void Disconnect()
		{
			if ( null != bot )
			{
				bot.ExecuteFinished -= OnBotExecuteFinished;
				bot.InstallFinished -= OnBotInstallFinished;
				bot = null;
				SetStatus( BotStatus.Offline, null );
			}
		}

		private void SetStatus( BotStatus status, Exception e )
		{
			currentStatus = status;
			if ( null != OnStatusChanged )
				OnStatusChanged( this, currentStatus, e );
		}

    private void BotTerminated(Exception e)
    {
      currentStatus = BotStatus.Offline;
      if (OnBotTerminated != null)
        OnBotTerminated(this, e);
    }

		public BotStatus Status { get { return currentStatus; } }

		public delegate void StatusChangedHandler( MasterBot bot, BotStatus newStatus, Exception error );
		public event StatusChangedHandler OnStatusChanged = null;

	  public delegate void BotTerminatedHandler(MasterBot sender, Exception error);
	  public event BotTerminatedHandler OnBotTerminated = null;
	}

	public class SuiteLoadException : Exception
	{
		public readonly CompilerErrorCollection Errors = null;

		public SuiteLoadException( CompilerErrorCollection _errors ) { Errors = _errors; }
	}
}

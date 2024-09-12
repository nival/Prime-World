using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Text;
using System.Threading;
using log4net;
using River.Core;
using River.Core.Suite;
using River.Master.Properties;

namespace River.Master
{
  public class RunningBotStatus
  {
    public readonly BotDescription Description;
    public readonly string ScenarioName;

    private MasterBot.BotStatus status;

    public bool Halted { get { return false; } }
    public MasterBot.BotStatus Status { get { return status; } }
    public Exception LastException { get { return null; } }

    public RunningBotStatus( MasterBot bot, string _scenarioName )
    {
      Description = bot.Description;
      status = bot.Status;
      ScenarioName = _scenarioName;
    }

    internal void SetStatus( MasterBot.BotStatus newStatus )
    {
      status = newStatus;
    }
  }

  public class RunningSuite
  {
    public enum SuiteStatus
    {
      Pending,
      Loading,
      Installing,
      Executing,
      Finished
    }

    private static readonly ILog logger = LogManager.GetLogger(typeof (RunningSuite));

    private SuiteStatus currentStatus = SuiteStatus.Loading;
    public SuiteStatus Status { get { return currentStatus; } }
    public string Tag { private set; get; }
    public string SuiteSource { private set; get; }
    public ScenarioDistributeInfo[] Scenarios;

    private bool aborting = false;
    private string filename;
    private List<MasterBot> bots;
    private List<RunningBotStatus> botStatuses = null;
    private ReadOnlyCollection<RunningBotStatus> readOnlyBotStatuses = null;
    private SyncContext syncContext = null;
    private Timer timer;

    public event EventHandler Started;
    public event EventHandler Finished;

    internal string OutputPath { get; private set; }

    public readonly Guid SuiteID = Guid.Empty;

    internal RunningSuite(string filename, string tag, string suite, Guid suiteID)
    {
      this.filename = filename;
      Tag = tag;
      SuiteSource = suite;
      SuiteID = suiteID;
      OutputPath = Path.Combine(Settings.Default.OutputDir, string.Format("{0:00}-{1:00}_{2}\\", DateTime.Now.Month, DateTime.Now.Day, suiteID));

      CompilerErrorCollection errors;
      Scenarios = Suite.GetScenarios(SuiteSource, "CSharp", out errors);
      if (errors.HasErrors || errors.HasWarnings)
      {
        foreach (CompilerError error in errors)
          logger.Warn(string.Format("{0}({1}): {2}", error.FileName, error.Line, error.ErrorText));
        throw new SuiteLoadException(errors);
      }
    }

    internal void Schedule(DateTime timestart, DateTime timestop, string suite)
    {
      TimeSpan dueTime = timestart > DateTime.Now ? timestart - DateTime.Now : new TimeSpan();
      TimeSpan period = timestop - timestart;
      timer = new Timer(OnScheduled, suite, dueTime, period);
      currentStatus = SuiteStatus.Pending;
    }

    private void OnScheduled(object suite)
    {
      if (Status == SuiteStatus.Pending)
      {
        currentStatus = SuiteStatus.Loading;
        Started(this, null);
      }
      else
      {
        timer.Dispose();
        Finished(this, null);
      }
    }

    internal void ExecuteRunningSuite(KeyValuePair<MasterBot, string>[] assignedBots)
    {
      logger.InfoFormat("Initializing RunningSuite: {0} bot(s)", assignedBots.Length);

      bots = new List<MasterBot>();

			currentStatus = SuiteStatus.Loading;
      botStatuses = new List<RunningBotStatus>();
      readOnlyBotStatuses = new ReadOnlyCollection<RunningBotStatus>( botStatuses );
      for (int i = 0; i < assignedBots.Length; ++i)
      {
        var bot = assignedBots[i].Key;
        botStatuses.Add(new RunningBotStatus(bot, assignedBots[i].Value));
        bot.OnStatusChanged += OnBotStatusChanged;
        bot.OnBotTerminated += OnBotTerminated;
        bots.Add(bot);
      }

      syncContext = new SyncContext( this );
      for ( int i = 0; i < bots.Count; ++i )
      {
        syncContext.RegisterBot( assignedBots[i].Key.Description, assignedBots[i].Value );
      }

      for ( int i = 0; i < bots.Count; ++i )
			{
				bots[i].Load( SuiteSource, assignedBots[i].Value, syncContext );
			}
    }

    public bool AddBotToExecution(MasterBot bot)
    {
      ScenarioDistributeInfo targetScenario = null;
      foreach (var s in Scenarios)
        if (s.Distribute.Count == 0)
        {
          targetScenario = s;
          break;
        }

      if (targetScenario == null)
        return false;

      bots.Add(bot);
      botStatuses.Add(new RunningBotStatus(bot, targetScenario.TypeName));
      bot.OnStatusChanged += OnBotStatusChanged;
      bot.OnBotTerminated += OnBotTerminated;

      syncContext.RegisterBot(bot.Description, targetScenario.TypeName);
      bot.Load(SuiteSource, targetScenario.TypeName, syncContext);
      
      return true;
    }

    public IList<RunningBotStatus> Bots
    {
      get
      {
        return readOnlyBotStatuses;
      }
    }

    public bool IsFailed
    {
      get
      {
        if ( Status != SuiteStatus.Finished )
          return false;

        foreach ( RunningBotStatus bot in botStatuses )
        {
          if ( bot.Status == MasterBot.BotStatus.Offline || bot.Status == MasterBot.BotStatus.Idle && aborting )
            return true;
          if ( bot.LastException != null )
            return true;
        }
        return false;
      }
    }

    private void Abort()
    {
      if ( !aborting )
      {
        logger.InfoFormat("Aborting suite file {0} (ID = {1})", this.filename, this.SuiteID);
        aborting = true;
        foreach ( MasterBot item in bots )
          if ( null != item )
            item.Halt();
      }
    }

    private void OnBotStatusChanged( MasterBot bot, MasterBot.BotStatus newStatus, Exception error )
    {
      lock ( botStatuses )
      {
        int index = bots.FindIndex(b => b == bot);
        if ( index == -1 )
          throw new InvalidOperationException( "RunningSuite recieve message from uncontrolled bot" );

        if (error != null)
          logger.InfoFormat("Bot {0} status change to {1} ({2})", bot.Description, newStatus, error);
        else
          logger.InfoFormat("Bot {0} status change to {1}", bot.Description, newStatus);

        botStatuses[index].SetStatus( newStatus );

        if ( error != null )
        {
          Abort();
        }

        if ( newStatus == MasterBot.BotStatus.Idle )
        {
          bots[index].OnStatusChanged -= OnBotStatusChanged;
          bots[index].OnBotTerminated -= OnBotTerminated;
          bots[index] = null;

          if ( aborting )
          {
            if (bots.Exists(b => b != null))
              return;

            SetStatus( SuiteStatus.Finished );
            return;
          }
        }

        if (botStatuses.Exists(b => !IsProperNextStatus(b.Status)))
        {
          // Код для того чтобы заново подсоединившийся бот мог "догнать" весь остальной suite
          switch (newStatus)
          {
            case MasterBot.BotStatus.Loaded:
              if (currentStatus == SuiteStatus.Installing || currentStatus == SuiteStatus.Executing)
                bot.BeginInstall();
              break;
            case MasterBot.BotStatus.Installed:
              if (currentStatus == SuiteStatus.Executing)
                bot.BeginExecute();
              break;
          }
          return;
        }

        switch ( currentStatus )
        {
          case SuiteStatus.Loading:
            foreach ( MasterBot item in bots )
              item.BeginInstall();
            SetStatus( SuiteStatus.Installing );
            break;
          case SuiteStatus.Installing:
            foreach ( MasterBot item in bots )
              item.BeginExecute();
            SetStatus( SuiteStatus.Executing );
            break;
          case SuiteStatus.Executing:
            SetStatus( SuiteStatus.Finished );
            break;
        }

        logger.InfoFormat("Running suite change to {0}", currentStatus);
      }
    }

    private void OnBotTerminated(MasterBot sender, Exception e)
    {
      lock (botStatuses)
      {
        int index = bots.FindIndex(b => b == sender);
        if (index == -1)
          throw new InvalidOperationException("RunningSuite recieve message from uncontrolled bot");

        botStatuses[index].SetStatus(MasterBot.BotStatus.Offline);
        bots[index].OnStatusChanged -= OnBotStatusChanged;
        bots[index].OnBotTerminated -= OnBotTerminated;
        bots[index] = null;
      }

      Halt();
      SetStatus(SuiteStatus.Finished);
    }

//    private bool IsProperBotStatus( MasterBot.BotStatus botStatus )
//    {
//      switch ( currentStatus )
//      {
//      case SuiteStatus.Loading:
//        return botStatus == MasterBot.BotStatus.Loading || botStatus == MasterBot.BotStatus.Loaded || botStatus == MasterBot.BotStatus.Installing;
//      case SuiteStatus.Installing:
//        return botStatus == MasterBot.BotStatus.Installing || botStatus == MasterBot.BotStatus.Installed || botStatus == MasterBot.BotStatus.Executing;
//      case SuiteStatus.Executing:
//        return botStatus == MasterBot.BotStatus.Executing || botStatus == MasterBot.BotStatus.Idle;
//      }
//      return false;
//    }

    private bool IsProperNextStatus( MasterBot.BotStatus botStatus )
    {
      switch ( currentStatus )
      {
        case SuiteStatus.Loading:
          return botStatus == MasterBot.BotStatus.Loaded;
        case SuiteStatus.Installing:
          return botStatus == MasterBot.BotStatus.Installed;
        case SuiteStatus.Executing:
          return botStatus == MasterBot.BotStatus.Idle;
      }
      return false;
    }

    public void Halt()
    {
      Abort();
    }

    private void SetStatus( SuiteStatus status )
    {
      currentStatus = status;
      if ( null != StatusChanged )
        StatusChanged( status );
    }

    public delegate void StatusChangedHandler( SuiteStatus newStatus );
    public event StatusChangedHandler StatusChanged = null;

    public override string ToString()
    {
      var builder = new StringBuilder();
      builder.AppendFormat("ID = {0}; ", SuiteID);
      builder.AppendFormat("Status = {0}; ", Status);
      builder.AppendFormat("Bots = {0}; ", Bots != null ? Bots.Count : 0);
      builder.AppendFormat("Suite file = {0}; ", filename);
      if (!String.IsNullOrEmpty(Tag))
        builder.AppendFormat("Tag = {0}; ", Tag);
      return builder.ToString();
    }
  }
}

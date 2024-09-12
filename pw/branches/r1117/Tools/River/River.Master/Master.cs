using System;
using System.Collections.Generic;
using System.Runtime.Remoting;
using log4net;
using River.Core;

namespace River.Master
{
	public class Master : MarshalByRefObject, IMaster
	{
    private readonly BotNet bots = new BotNet();
    private readonly List<RunningSuite> suites = new List<RunningSuite>();

    private long id = -1; // start enumeration bots with 0

	  private static readonly ILog logger = LogManager.GetLogger(typeof (Master));


		private Master()
		{
		}

    public override object InitializeLifetimeService()
    {
      return null;
    }

		#region IMaster Members

    public void Ping() {}

    public long Connect( IBot bot, SetBotIDCallback SetID )
		{
			lock ( bots )
			{
        if (bots.Contains(bot))
          return -1;

        ++id;
        if ( SetID != null )
          SetID( id );

			  var masterBot = new MasterBot(bot);
			  bots.RegisterBot(masterBot);
        logger.InfoFormat("Bot \"{0}\" registered with id {1}", bot.Description.Name, bot.Description.ID);

        foreach(var suite in suites)
        {
          if (suite.Status != RunningSuite.SuiteStatus.Finished && suite.AddBotToExecution(masterBot)) break;
        }
      }
      return id;
		}

    public void Disconnect( long botId )
    {
      lock (bots)
      {
        bots.UnregisterBot(botId);
      }
    }

    public void ExecuteSuite(string filename, string tag, string suite, Guid suiteID, DateTime? timestart, DateTime? timestop)
    {
      lock ( suites )
			{
        // Создается объект RunningSuite.
        var createdSuite = new RunningSuite(filename, tag, suite, suiteID);

        // Если указано расписание, инициализируется запуск по таймеру.
        if (timestart != null && timestop != null)
        {
          if (timestart.Value >= timestop.Value)
            throw new ArgumentException("timestart must be less than timestop"); //fixme: Заменить исключение на возврат bool

          createdSuite.Started += OnStarted;
          createdSuite.Finished += OnFinished;
          createdSuite.Schedule(timestart.Value, timestop.Value, suite);
        }
        // Если расписания нет, то набор сценариев стартует немедленно.
        else
        {
          bots.ExecuteRunningSuite(createdSuite);
        }

        suites.Add(createdSuite);
			}
    }

    public void HaltSuite( Guid suiteID )
    {
      foreach ( RunningSuite suite in suites )
      {
        if ( suite.SuiteID != suiteID )
          continue;

        suite.Halt();
        logger.InfoFormat("Halted suite with id {0}", suiteID.ToString());
        break;
      }
    }

    public void HaltSuite(string tag)
    {
      if (String.IsNullOrEmpty(tag))
        return;

      foreach (RunningSuite suite in suites)
      {
        if (suite.Tag == tag && suite.Status != RunningSuite.SuiteStatus.Finished)
        {
          suite.Halt();
          logger.InfoFormat("Halted suite by tag \"{0}\". Suite id {1}", tag, suite.SuiteID.ToString());
        }
      }
    }

    public void HaltAllSuites()
    {
      logger.Info("Halting all active suites.");
      suites.ForEach(s =>
                       {
                         if (s.Status != RunningSuite.SuiteStatus.Finished)
                         {
                           s.Halt();
                           logger.InfoFormat("Halted suite with id {0}", s.SuiteID.ToString());
                         }
                       });
    }

    public string[] SuitesInfo()
    {
      var info = new List<string>();
      suites.ForEach(s => info.Add(s.ToString()));
      return info.ToArray();
    }
    
		#endregion

    #region RunningSuite events processing

    private void OnStarted(object sender, EventArgs e)
    {
      lock (suites)
      {
        var runningSuite = (RunningSuite)sender;
        bots.ExecuteRunningSuite(runningSuite);
        logger.DebugFormat("Suite started. Id = {0}", runningSuite.SuiteID);
      }
    }

    private void OnFinished(object sender, EventArgs e)
    {
      lock (suites)
      {
        var runningSuite = (RunningSuite) sender;
        runningSuite.Halt();
        logger.DebugFormat("Suite finished. Id = {0}", runningSuite.SuiteID);
      }
    }

    #endregion

    #region Static helpers for create and terminate Master

    private static Master master = null;
		private static ObjRef masterRef = null;

    public static Master Create( string serviceName )
		{
      master = new Master();
			masterRef = RemotingServices.Marshal( master, serviceName );
      logger.InfoFormat("Master created as \"{0}\"", masterRef.URI);

			return master;
		}

		public static void Terminate()
		{
			RemotingServices.Disconnect( master );

			GC.Collect();
			GC.WaitForPendingFinalizers();
    }

    #endregion
  }
}

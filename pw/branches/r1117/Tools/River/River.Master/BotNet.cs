using System;
using System.Collections.Generic;
using System.Timers;
using log4net;
using River.Core;
using River.Core.Suite;
using River.Core.Utils;
using River.Master.Properties;

namespace River.Master
{
	public class BotNet
	{
    private LinkedList<MasterBot> bots = new LinkedList<MasterBot>();

    private Timer timer = new Timer();
    private readonly object _sync = new object();

    private static readonly ILog logger = LogManager.GetLogger(typeof(BotNet));

	  public BotNet()
	  {
	    timer.Interval = Settings.Default.BotsCheckInterval;
      timer.Elapsed += BotsCheck;
      timer.Start();
	  }

    void BotsCheck(object sender, ElapsedEventArgs e)
    {
      lock (_sync)
      {
        var botsToDelete = new List<MasterBot>();
        foreach (var bot in bots)
        {
          if (!bot.Ping())
            botsToDelete.Add(bot);
          //else
          //  logger.DebugFormat("Bot {0} is ok.", bot.Description); // fixme: gimme a trace
        }
        if (botsToDelete.Count > 0)
          lock (bots)
          {
            foreach (var bot in botsToDelete)
            {
              bots.Remove(bot);
              logger.InfoFormat("Bot {0} lost and disconnected", bot.Description);
            }
          }
      }
    }

    public bool Contains(IBot bot)
    {
      foreach (var b in bots)
      {
        if (b.Bot == bot)
          return true;
      }
      return false;
    }

    public void RegisterBot( MasterBot bot )
    {
      if ( bot.Status == MasterBot.BotStatus.Idle && !bots.Contains( bot ) )
      {
        bots.AddLast( bot );
        logger.InfoFormat("Bot {0} connected", bot.Description);
      }
    }

    public void UnregisterBot(long id)
    {
      lock (_sync)
      {
        foreach (var bot in bots)
        {
          if (bot.Description.ID == id)
          {
            bots.Remove(bot);
            logger.InfoFormat("Bot {0} disconnected", bot.Description);
            return;
          }
        }
      }
    }

    // кидает exception, если RunningSuite сделать не удалось 
    // (некорректный код, нет свободный ботов, нет вообще ботов и т.д.), не thread safe
    // Метод устарел, оставлен, чтобы не падали тесты.
    [Obsolete]
    public RunningSuite CreateRunningSuite(string filename, string tag, string suite, Guid suiteID )
    {
      var result = new RunningSuite(filename, tag, suite, suiteID);
      ExecuteRunningSuite(result);
      return result;
    }

    /// <summary>
    /// Подбирает ботов и запускает на них заданный набор сценариев.
    /// </summary>
    /// <exception cref="SuiteLoadException">Исключение в случае нехватки свободных ботов.</exception>
    public void ExecuteRunningSuite(RunningSuite runningSuite)
		{
			int neededBots = 0;
      Pair<ScenarioDistributeInfo, List<MasterBot>> allPossibleBots = null;
			List<Pair<ScenarioDistributeInfo, List<MasterBot>>> scenariosBots = new List<Pair<ScenarioDistributeInfo, List<MasterBot>>>();
			foreach ( ScenarioDistributeInfo scenario in runningSuite.Scenarios )
			{
        if ( scenario.Distribute.Count == 0 )
        {
          if ( allPossibleBots == null )
          {
            allPossibleBots = new Pair<ScenarioDistributeInfo, List<MasterBot>>( scenario, new List<MasterBot>() );
          }
          else
          {
            throw new InvalidOperationException(
              string.Format( "Scenario {0} can not be assigned to all free bots, that slot is already taken", scenario.TypeName ) );
          }
          continue;
        }
				scenariosBots.Add( new Pair<ScenarioDistributeInfo, List<MasterBot>>( scenario, new List<MasterBot>() ) );
				neededBots += scenario.Count;
			}

			foreach ( var bot in bots )
			{
				if ( bot.Status != MasterBot.BotStatus.Idle )
					continue;

				foreach ( var scenario in scenariosBots )
				{
					if ( scenario.Key.Count == scenario.Value.Count )
						continue;
					if ( !scenario.Key.Distribute.IsMatch( bot.Description ) )
						continue;
					scenario.Value.Add( bot );
					--neededBots;
					break;
				}

        if ( neededBots == 0 )
        {
          if ( allPossibleBots == null )
            break;

          allPossibleBots.Value.Add( bot );
        }
			}

			if ( neededBots > 0 )
				throw new InvalidOperationException( string.Format( "{0} bot(s) needed", neededBots ) );

      List<KeyValuePair<MasterBot, string>> assignedBots = new List<KeyValuePair<MasterBot, string>>();

			foreach ( var scenario in scenariosBots )
			{
				foreach ( var bot in scenario.Value )
				{
					assignedBots.Add( new KeyValuePair<MasterBot, string>( bot, scenario.Key.TypeName ) );
				}
			}

      if ( allPossibleBots != null )
        foreach ( var bot in allPossibleBots.Value )
        {
          assignedBots.Add( new KeyValuePair<MasterBot, string>( bot, allPossibleBots.Key.TypeName ) );
        }

      runningSuite.ExecuteRunningSuite(assignedBots.ToArray());
		}
	}
}

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using BusinessLogic;
using BusinessLogic.Game;
using log4net;

namespace StatisticService.LoadTests
{
  public class FullTest
  {
    private static ILog _log = LogManager.GetLogger(typeof (FullTest));

    private const string MgmtConnection = "Server=localhost;Port=5432;Database=pw_management;User ID=postgres;Password=password";
    private const string LogsConnection = "Server=localhost;Port=5432;Database=pw_logs;User ID=postgres;Password=password";

    public FullTest()
    {
      //if (!BLManager.InitDatabases(MgmtConnection, 51, LogsConnection, 32))
        throw new InvalidOperationException("Can't create test object because databases are not initialized");
    }

    public void Run()
    {
      var process_thread = new Thread(ProcessMessages);
      process_thread.Start();

      var handlers = new List<WaitHandle>();
      for (int i = 0; i < 5; i++)
      {
        var handler = new AutoResetEvent(false);
        handlers.Add(handler);
        // run the thread with sync object
        new Thread(SessionBehaviour).Start(handler);
        // wait before next step
        Thread.Sleep(3133);
      }
      WaitHandle.WaitAll(handlers.ToArray());

      stopProcessing = true;
      _log.Info("Stop signal has been sent");
      process_thread.Join();
      // waiting for worker threads
      Thread.Sleep(3000);
    }

    public void RunMM()
    {
      for (int i = 0; i < 10; i++)
      {
        var unixtime = Convert.ToUInt64((DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc)).TotalSeconds);
        ulong persistentid = (unixtime << 8) + (ulong)i;
        var mmplayers = new List<MMakingPlayerInfo>(10);
        for (int j = 0; j < 10; j++)
        {
          mmplayers.Add(new MMakingPlayerInfo { UserId = i * 100 + j, HeroId = 1617033593, Faction = 1, Rating = j * 100, Force = j * 1.1f, Sex = 4, PartyId = 2, WaitTime = 6.0f, LobbyReaction = 3 });
        }
        //BLManager.SessionWriter.MMakingSession(persistentid, 1, -1, DateTime.UtcNow, mmplayers);
        Thread.Sleep(3000);
      }
      Thread.Sleep(5000);
    }

    private volatile int sessionSequence;

    private void SessionBehaviour(object handler)
    {
      int sessionid = ++sessionSequence;

      List<SessionStartPlayerInfo> players = new List<SessionStartPlayerInfo>();
      for (int i = 1; i <= 10; i++)
        players.Add(new SessionStartPlayerInfo {UserId = sessionid*1000 + i, HeroId = 1617033593, Nickname = "test", Faction = i%2});

      lock (qlock)
      {
        tasks.Enqueue(new SessionStartTask(sessionid, players));
        _log.DebugFormat("Enqueued start session(id={0}), queue length = {1}", sessionid, tasks.Count);
      }
      Thread.Sleep(3000);

      int event_period = 5;
      for (int i = 0; i < 100; i++)
      {
        foreach (var p in players)
        {
          lock (qlock)
            tasks.Enqueue(new DebugVarTask(sessionid, p.UserId));
          Thread.Sleep(event_period);
        }
        foreach (var p in players)
        {
          lock (qlock)
            tasks.Enqueue(new KillTask(sessionid, p.UserId));
          Thread.Sleep(event_period);
        }
        foreach (var p in players)
        {
          lock (qlock)
            tasks.Enqueue(new TalentUsedTask(sessionid, p.UserId));
          Thread.Sleep(event_period);
        }
        foreach (var p in players)
        {
          lock (qlock)
            tasks.Enqueue(new ExceedingStepTimeTask(sessionid, p.UserId));
          Thread.Sleep(event_period);
        }
        foreach (var p in players)
        {
          lock (qlock)
            tasks.Enqueue(new ExceedingPingTimeTask(sessionid, p.UserId));
          Thread.Sleep(event_period);
        }
/*        foreach (var p in players)
        {
          lock (qlock)
            tasks.Enqueue(new DebugVarTask(sessionid, p.UserId));
          Thread.Sleep(event_period);
        }
        foreach (var p in players)
        {
          lock (qlock)
            tasks.Enqueue(new LevelUpTask(sessionid, p.UserId));
          Thread.Sleep(event_period);
        }
        foreach (var p in players)
        {
          lock (qlock)
            tasks.Enqueue(new DisconnectTask(sessionid, p.UserId));
          Thread.Sleep(event_period);
        }*/
      }

      var players_result = players.Select(p => new SessionResultPlayerInfo {UserId = p.UserId, Score = 666});
      lock (qlock)
        tasks.Enqueue(new SessionResultTask(sessionid, players_result));

      ((AutoResetEvent) handler).Set();
    }

    private readonly Queue<IStatisticTask> tasks = new Queue<IStatisticTask>();
    private readonly object qlock = new object();
    private bool stopProcessing;

    private void ProcessMessages()
    {
      var sw = new Stopwatch();
      int action_count = 0;
      while (true)
      {
        if (tasks.Count == 0)
        {
          if (stopProcessing)
            break;
          Thread.Sleep(1);
          continue;
        }

        IStatisticTask task;
        lock (qlock)
        {
          task = tasks.Dequeue();
          
          action_count++;
          if (action_count % 100 == 0)
            _log.Debug("Test queue length = " + tasks.Count);
        }

        sw.Reset();
        sw.Start();
        
        if (task != null) task.Execute();
        else continue;

        sw.Stop();
        if (sw.ElapsedMilliseconds > 10)
        {
          _log.WarnFormat("Action {0} too slow: {1} ms elapsed", task.ToString(), sw.ElapsedMilliseconds);
        }
      }
    }
  }

  #region Statistic tasks

  interface IStatisticTask
  {
    void Execute();
  }

  class MMakingStartTask : IStatisticTask
  {
    private readonly ulong persistentid;
    private readonly IEnumerable<MMakingPlayerInfo> mmplayers;

    public MMakingStartTask(ulong persistentid, IEnumerable<MMakingPlayerInfo> mmplayers)
    {
      this.persistentid = persistentid;
      this.mmplayers = mmplayers;
    }
    public void Execute()
    {
      //BLManager.SessionWriter.MMakingSession(persistentid, 1, -1, DateTime.UtcNow, mmplayers);
    }
    public override string ToString()
    {
      return String.Format("MMakingStartTask(persistentid={0})", persistentid);
    }
  }

  class SessionStartTask : IStatisticTask
  {
    private readonly int sessionid;
    private readonly IEnumerable<SessionStartPlayerInfo> players;
    public SessionStartTask(int sessionid, IEnumerable<SessionStartPlayerInfo> players)
    {
      this.sessionid = sessionid;
      this.players = players;
    }
    public void Execute()
    {
      var unixtime = Convert.ToUInt64((DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc)).TotalSeconds);
      ulong persistentid = (unixtime << 8) + (ulong)sessionid;
      //BLManager.SessionWriter.SessionStart(sessionid, persistentid, "", "", 4, players);
    }
    public override string ToString()
    {
      return String.Format("SessionStartTask(sessionid={0})", sessionid);
    }
  }

  class SessionResultTask : IStatisticTask
  {
    private readonly int sessionid;
    private readonly IEnumerable<SessionResultPlayerInfo> players;
    public SessionResultTask(int sessionid, IEnumerable<SessionResultPlayerInfo> players)
    {
      this.sessionid = sessionid;
      this.players = players;
    }
    public void Execute()
    {
      //BLManager.SessionWriter.SessionResult(sessionid, 0, 0, 0, players);
    }
    public override string ToString()
    {
      return String.Format("SessionResultTask(sessionid={0})", sessionid);
    }
  }

  class DebugVarTask : IStatisticTask
  {
    private readonly int sessionid;
    private readonly long userid;
    public DebugVarTask(int sessionid, long userid)
    {
      this.sessionid = sessionid;
      this.userid = userid;
    }
    public void Execute()
    {
      //BLManager.SessionEventWriter.DebugVar(sessionid, 0, 0, 0, userid, "", "");
    }
    public override string ToString()
    {
      return String.Format("DebugVarTask(sessionid={0},userid={1})", sessionid, userid);
    }
  }

  class KillTask : IStatisticTask
  {
    private readonly int sessionid;
    private readonly long userid;
    public KillTask(int sessionid, long userid)
    {
      this.sessionid = sessionid;
      this.userid = userid;
    }
    public void Execute()
    {
      //BLManager.SessionEventWriter.Kill(sessionid, 0, 0, 0, userid, userid, 0);
    }
    public override string ToString()
    {
      return String.Format("KillTask(sessionid={0},userid={1})", sessionid, userid);
    }
  }

  class TalentUsedTask : IStatisticTask
  {
    private readonly int sessionid;
    private readonly long userid;
    public TalentUsedTask(int sessionid, long userid)
    {
      this.sessionid = sessionid;
      this.userid = userid;
    }
    public void Execute()
    {
      //BLManager.SessionEventWriter.TalentUsed(sessionid, 0, 0, 0, userid, -1449993354);
    }
    public override string ToString()
    {
      return String.Format("TalentUsedTask(sessionid={0},userid={1})", sessionid, userid);
    }
  }

  class LevelUpTask : IStatisticTask
  {
    private readonly int sessionid;
    private readonly long userid;
    public LevelUpTask(int sessionid, long userid)
    {
      this.sessionid = sessionid;
      this.userid = userid;
    }
    public void Execute()
    {
      //BLManager.SessionEventWriter.LevelUp(sessionid, 0, 0, 0, userid, 0);
    }
    public override string ToString()
    {
      return String.Format("LevelUpTask(sessionid={0},userid={1})", sessionid, userid);
    }
  }
  
  class DisconnectTask : IStatisticTask
  {
    private readonly int sessionid;
    private readonly long userid;
    public DisconnectTask(int sessionid, long userid)
    {
      this.sessionid = sessionid;
      this.userid = userid;
    }
    public void Execute()
    {
      //BLManager.SessionEventWriter.Disconnect(sessionid, userid, 11, DateTime.UtcNow);
    }
    public override string ToString()
    {
      return String.Format("DisconnectTask(sessionid={0},userid={1})", sessionid, userid);
    }
  }
  


  class ExceedingStepTimeTask : IStatisticTask
  {
    private readonly int sessionid;
    private readonly long userid;
    public ExceedingStepTimeTask(int sessionid, long userid)
    {
      this.sessionid = sessionid;
      this.userid = userid;
    }
    public void Execute()
    {
      //BLManager.SessionDebugWriter.ExceedingStepTime(sessionid, userid, 1, 10, 20, DateTime.UtcNow.AddHours(-1), DateTime.UtcNow, 1, 2, 3, 4, 5, 6, 7);
    }
    public override string ToString()
    {
      return String.Format("ExceedingStepTimeTask(sessionid={0},userid={1})", sessionid, userid);
    }
  }

  class ExceedingPingTimeTask : IStatisticTask
  {
    private readonly int sessionid;
    private readonly long userid;
    public ExceedingPingTimeTask(int sessionid, long userid)
    {
      this.sessionid = sessionid;
      this.userid = userid;
    }
    public void Execute()
    {
      //BLManager.SessionDebugWriter.ExceedingPingTime(sessionid, userid, 1, DateTime.UtcNow.AddHours(-1), DateTime.UtcNow, 1, 2, 3, 4, 11, 12, 13, 14);
    }
    public override string ToString()
    {
      return String.Format("ExceedingPingTimeTask(sessionid={0},userid={1})", sessionid, userid);
    }
  }

  #endregion
}
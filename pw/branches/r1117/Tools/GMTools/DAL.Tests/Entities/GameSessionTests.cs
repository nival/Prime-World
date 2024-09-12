using System;
using System.IO;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using Npgsql;
using log4net.Config;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class GameSessionTests
  {
    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
      DatabaseHelper.Init();
    }

    [SetUp]
    public void Setup()
    {
      NHibernateHelper.SessionFactory.Evict(typeof(GameSession));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate gamesession cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static GameSession CreateNewGameSession()
    {
      return new GameSession
               {
                 PersistentId = 56784321,
                 Server = "one",
                 ServerAddress = "lolhost",
                 Cluster = "RU",
                 Map = "Test.ADMP",
                 SessionType = SessionType.Soc_Matchmaking,
                 StartTime = DateTime.Today,
                 EndTime = DateTime.Today.AddHours(1),
                 SideWon = 0,
                 SessionResult = SessionResult.SyncResults,
                 SurrenderVote = 4
               };
    }

    [Test]
    public void AddGameSessionTest()
    {
      var gs = CreateNewGameSession();
      using (var repo = new GameSessionRepository())
      {
        repo.Add(gs);
      }
      using (var repo = new GameSessionRepository())
      {
        var gs2 = repo.GetById(gs.Id);
        Assert.AreNotSame(gs, gs2);
        Assert.AreEqual(gs, gs2);
      }
    }

    [Test]
    public void WriteStartedTest()
    {
      var gs = CreateNewGameSession();
      using (var repo = new GameSessionRepository())
      {
        int id = repo.WriteStarted(gs);
        Assert.AreEqual(gs.Id, id);
      }
      using (var repo = new GameSessionRepository())
      {
        var gs2 = repo.GetById(gs.Id);
        Assert.AreNotSame(gs, gs2);
        Assert.AreEqual(gs, gs2);
      }
    }

    [Test]
    public void EqualsTest()
    {
      var gs1 = CreateNewGameSession();
      var gs2 = CreateNewGameSession();
      Assert.AreEqual(gs1, gs2);
      gs2.PersistentId = 1234;
      Assert.AreNotEqual(gs1, gs2);
    }

    [Test]
    public void UpdateGameSessionTest()
    {
      var gs = CreateNewGameSession();
      using (var repo = new GameSessionRepository())
      {
        repo.Add(gs);
      }

      GameSession gs2;
      using (var repo = new GameSessionRepository())
      {
        gs2 = repo.GetById(gs.Id);
        gs2.PersistentId = 56712312;
        gs2.Server = "two";
        gs2.Map = "Test2.ADMP";
        gs2.SessionType = SessionType.Soc_Tutorial;
        gs2.StartTime = DateTime.Today;
        gs2.EndTime = DateTime.Today.AddHours(1);
        gs2.SideWon = 1;
        gs2.SessionResult = SessionResult.AsyncResults;
        gs2.SurrenderVote = 1;
        repo.Update(gs2);
      }

      using (var repo = new GameSessionRepository())
      {
        var gs3 = repo.GetById(gs2.Id);
        Assert.AreNotSame(gs2, gs3);
        Assert.AreEqual(gs2, gs3);
      }
    }

    [Test]
    public void WriteEndedTest()
    {
      var gs = CreateNewGameSession();
      using (var repo = new GameSessionRepository())
      {
        repo.Add(gs);
      }

      using (var repo = new GameSessionRepository())
      {
        repo.WriteEnded(gs.PersistentId, (int)SessionResult.NobodyCame, DateTime.Today.AddHours(1), 1, 2);
      }

      using (var repo = new GameSessionRepository())
      {
        var gs2 = repo.GetById(gs.Id);
        Assert.AreEqual(SessionResult.NobodyCame, gs2.SessionResult);
        Assert.AreEqual(DateTime.Today.AddHours(1), gs2.EndTime);
        Assert.AreEqual(1, gs2.SideWon);
        Assert.AreEqual(2, gs2.SurrenderVote);
      }
    }

    [Test]
    public void GetByPersistentIdTest()
    {
      var gs = CreateNewGameSession();
      using (var repo = new GameSessionRepository())
      {
        repo.Add(gs);
      }
      using (var repo = new GameSessionRepository())
      {
        var gs2 = repo.GetByPersistentId(gs.PersistentId);
        Assert.AreNotSame(gs, gs2);
        Assert.AreEqual(gs, gs2);
      }
    }
  }
}

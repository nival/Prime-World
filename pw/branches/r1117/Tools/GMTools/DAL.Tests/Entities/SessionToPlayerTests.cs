using System;
using System.IO;
using DAL.Entities;
using DAL.Repositories;
using log4net.Config;
using Npgsql;
using NUnit.Framework;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class SessionToPlayerTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(Player));
      NHibernateHelper.SessionFactory.Evict(typeof(Character));
      NHibernateHelper.SessionFactory.Evict(typeof(PlayerCharacter));
      NHibernateHelper.SessionFactory.Evict(typeof(ResourceLog));
      NHibernateHelper.SessionFactory.Evict(typeof(GameSession));
      NHibernateHelper.SessionFactory.Evict(typeof(SessionToPlayer));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate character cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate gamesession cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate guild cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static SessionToPlayer CreateNewSessionToPlayer()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = "RU"};
      using (var repo = new PlayerRepository())
        repo.Add(p);
      var c = new Character {Id = 200, Name = "TestCharacter"};
      using (var repo = new CharacterRepository())
        repo.Add(c);
      var pc = new PlayerCharacter {Player = p, Character = c};
      using (var repo = new PlayerCharacterRepository())
        repo.Add(ref pc);
      var gs = new GameSession {Server = "", Map = "", PersistentId = 200600, StartTime = DateTime.Today};
      using (var repo = new GameSessionRepository())
        repo.Add(gs);
      return new SessionToPlayer {GameSession = gs, PlayerCharacter = pc, RelayAddress = "Улица Маяковского, дом 37", StartTime = gs.StartTime};
    }

    [Test]
    public void AddObjectTest()
    {
      var stp = CreateNewSessionToPlayer();
      Console.WriteLine("--- add object ---");
      using (var repo = new SessionToPlayerRepository())
        repo.Add(stp);
      Console.WriteLine("--- get object ---");
      using (var repo = new SessionToPlayerRepository())
      {
        var stp2 = repo.GetById(stp.Id);
        Assert.AreNotSame(stp, stp2);
        Assert.AreEqual(stp.Id, stp2.Id);
        Assert.AreEqual(stp.RelayAddress, stp2.RelayAddress);
        Assert.AreEqual(stp.StartTime, stp2.StartTime);
      }
    }

    [Test]
    public void CreateObjectTest()
    {
      var stp = CreateNewSessionToPlayer();
      int id;
      using (var repo = new SessionToPlayerRepository())
      {
        id = repo.Create(stp.GameSession.Id, stp.PlayerCharacter, stp.Faction);
      }
      using (var repo = new SessionToPlayerRepository())
      {
        var stp2 = repo.GetById(id);
        Assert.IsNotNull(stp2);
        Assert.AreNotSame(stp, stp2);
        Assert.AreEqual(stp.PlayerCharacter, stp2.PlayerCharacter);
        Assert.AreEqual(stp.GameSession.Id, stp2.GameSession.Id);
        Assert.AreEqual(stp.Faction, stp2.Faction);
        Assert.AreEqual(stp.StartTime, stp2.StartTime);
        Assert.IsNull(stp.Guild);
      }
    }

    [Test]
    public void CreateObjectWithGuildTest()
    {
      var guild = new Guild { Id = 8800 };
      using (var repo = new GuildRepository())
        repo.Add(guild);
      
      var stp = CreateNewSessionToPlayer();

      stp.PlayerCharacter.Player.Guild = guild;
      using (var repo1 = new PlayerCharacterRepository())
      using (var repo2 = new PlayerRepository())
      {
        repo2.Update(stp.PlayerCharacter.Player);
        repo1.Update(stp.PlayerCharacter);
      }

      int id;
      using (var repo = new SessionToPlayerRepository())
      {
        id = repo.Create(stp.GameSession.Id, stp.PlayerCharacter, stp.Faction);
      }

      using (var repo = new SessionToPlayerRepository())
      {
        var stp2 = repo.GetById(id);
        Assert.IsNotNull(stp2);
        Assert.AreNotSame(stp, stp2);
        Assert.AreEqual(stp.PlayerCharacter.Id, stp2.PlayerCharacter.Id);
        Assert.AreEqual(stp.GameSession.Id, stp2.GameSession.Id);
        Assert.AreEqual(stp.Faction, stp2.Faction);
        Assert.AreEqual(stp.StartTime, stp2.StartTime);
        Assert.AreEqual(guild.Id, stp2.Guild.Id);
      }
    }

    [Test]
    public void GetByPersistentIdTest()
    {
      var stp = CreateNewSessionToPlayer();
      using (var repo = new SessionToPlayerRepository())
        repo.Add(stp);

      using (var repo = new SessionToPlayerRepository())
      {
        var stp2 = repo.GetByPersistentId(stp.GameSession.PersistentId, stp.PlayerCharacter.Player);
        Assert.IsNotNull(stp2);
        Assert.AreEqual(stp2.Id, stp.Id);
        Assert.AreEqual(stp2.GameSession, stp.GameSession);
      }

      using (var repo = new SessionToPlayerRepository())
      {
        var stp2 = repo.GetByPersistentId(-123456, stp.PlayerCharacter.Player);
        Assert.IsNull(stp2);
      }
    }
  }
}
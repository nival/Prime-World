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
  public class MoveToBathTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(MoveToBath));
      NHibernateHelper.SessionFactory.Evict(typeof(ResourceLog));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate character cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static MoveToBath CreateNewMoveToBath()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = "RU"};
      using (var repo = new PlayerRepository())
        repo.Add(p);
      var c = new Character {Id = 123456, Name = "highlanger"};
      using (var repo = new CharacterRepository())
        repo.Add(c);
      var pc = new PlayerCharacter {Player = p, Character = c};
      using (var repo = new PlayerCharacterRepository())
        repo.Add(pc);
      var r = new ResourceLog {Player = p, Source = "test", GoldChange = -100, GoldTotal = 500, Timestamp = DateTime.Today };
      using (var repo = new ResourceLogRepository())
        repo.Add(r);
      return new MoveToBath
               {
                 Minutes = 100,
                 PlayerCharacter = pc,
                 ResourceLog = r,
                 Timestamp = DateTime.Today
               };
    }

    [Test]
    public void AddObjectTest()
    {
      var mb = CreateNewMoveToBath();
      using (var repo = new Repository<MoveToBath>())
        repo.Add(mb);
      using (var repo = new Repository<MoveToBath>())
      {
        var fc2 = repo.GetById(mb.Id);
        Assert.AreNotSame(mb, fc2);
        Assert.AreEqual(mb, fc2);
      }
    }

    [Test]
    public void GetMoveToBathWithoutResourcelog()
    {
      var mb = CreateNewMoveToBath();
      using (var repo = new Repository<MoveToBath>())
        repo.Add(mb);

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "delete from resourcelog where id = " + mb.ResourceLog.Id;
        cmd.ExecuteNonQuery();
      }

      using (var repo = new Repository<MoveToBath>())
      {
        var mb2 = repo.GetById(mb.Id);
        var rl2 = mb2.ResourceLog;
        Assert.IsNull(rl2);
      }
    }
  }
}
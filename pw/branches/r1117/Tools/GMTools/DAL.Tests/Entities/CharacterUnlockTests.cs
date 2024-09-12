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
  public class CharacterUnlockTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(ResourceLog));
      NHibernateHelper.SessionFactory.Evict(typeof(CharacterUnlock));

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

    private static CharacterUnlock CreateNewCharacterUnlock()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = "RU"};
      using (var repo = new PlayerRepository())
        repo.Add(p);
      var c = new Character { Id = 123456, Name = "highlanger" };
      using (var repo = new CharacterRepository())
        repo.Add(c);
      var pc = new PlayerCharacter {Player = p, Character = c};
      using (var repo = new PlayerCharacterRepository())
        repo.Add(ref pc);
      var r = new ResourceLog { Player = p, Source = "test", GoldChange = -100, GoldTotal = 500, Timestamp = DateTime.Today};
      using (var repo = new ResourceLogRepository())
        repo.Add(r);
      return new CharacterUnlock
      {
        PlayerCharacter = pc,
        ResourceLog = r,
        Timestamp = DateTime.Today
      };
    }

    [Test]
    public void AddObjectTest()
    {
      var cu = CreateNewCharacterUnlock();
      using (var repo = new CharacterUnlockRepository())
        repo.Add(cu);
      using (var repo = new CharacterUnlockRepository())
      {
        var cu2 = repo.GetById(cu.Id);
        Assert.AreNotSame(cu, cu2);
        Assert.AreEqual(cu, cu2);
      }
    }

    [Test]
    public void GetCharacterUnlockWithoutResourcelog()
    {
      var cu = CreateNewCharacterUnlock();
      using (var repo = new CharacterUnlockRepository())
        repo.Add(cu);

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "delete from resourcelog where id = " + cu.ResourceLog.Id;
        cmd.ExecuteNonQuery();
      }

      using (var repo = new CharacterUnlockRepository())
      {
        var cu2 = repo.GetById(cu.Id);
        var rl2 = cu2.ResourceLog;
        Assert.IsNull(rl2);
      }
    }
  }
}
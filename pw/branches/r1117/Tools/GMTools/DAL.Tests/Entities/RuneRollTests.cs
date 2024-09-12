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
  public class RuneRollTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(Rune));
      NHibernateHelper.SessionFactory.Evict(typeof(RuneRoll));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate rune cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static RuneRoll CreateNewRuneRoll()
    {
      var p = new Player { Id = 100, Nickname = "TestPlayer", Locale = "RU" };
      using (var repo = new PlayerRepository())
        repo.Add(p);
      var r = new Rune { Id = 123456, Name = "БОНУС К УБИЙСТВУ ВСЕХ ЛЮДЕЙ" };
      using (var repo = new Repository<Rune>())
        repo.Add(r);
      return new RuneRoll
      {
        Player = p,
        PersistentId = 5776506343380746254,
        Rune = r,
        Timestamp = DateTime.Today,
        Runescountold = 5,
        Runescountnew = 12
      };
    }

    [Test]
    public void AddObjectTest()
    {
      var rr = CreateNewRuneRoll();
      using (var repo = new RuneRollRepository())
        repo.Add(rr);
      using (var repo = new RuneRollRepository())
      {
        var rr2 = repo.GetById(rr.Id);
        Assert.AreNotSame(rr, rr2);
        Assert.AreEqual(rr.Player, rr2.Player);
        Assert.AreEqual(rr.Rune, rr2.Rune);
        Assert.AreEqual(rr.PersistentId, rr2.PersistentId);
      }
    }

  }
}
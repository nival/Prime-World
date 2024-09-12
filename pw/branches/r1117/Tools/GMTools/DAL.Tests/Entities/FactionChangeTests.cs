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
  public class FactionChangeTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(FactionChange));
      NHibernateHelper.SessionFactory.Evict(typeof(ResourceLog));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static FactionChange CreateNewFactionChange()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = "RU"};
      using (var repo = new PlayerRepository())
        repo.Add(p);
      var r = new ResourceLog {Player = p, Source = "test", GoldChange = -100, GoldTotal = 500, Timestamp = DateTime.Today};
      using (var repo = new ResourceLogRepository())
        repo.Add(r);
      return new FactionChange
               {
                 Player = p,
                 OldFaction = Faction.Dokt,
                 NewFaction = Faction.Adornian,
                 ResourceLog = r,
                 Timestamp = DateTime.Today
               };
    }

    [Test]
    public void AddObjectTest()
    {
      var fc = CreateNewFactionChange();
      using (var repo = new Repository<FactionChange>())
        repo.Add(fc);
      using (var repo = new Repository<FactionChange>())
      {
        var fc2 = repo.GetById(fc.Id);
        Assert.AreNotSame(fc, fc2);
        Assert.AreEqual(fc, fc2);
      }
    }

    [Test]
    public void GetFactionchangeWithoutResourcelog()
    {
      var fc = CreateNewFactionChange();
      using (var repo = new Repository<FactionChange>())
        repo.Add(fc);

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "delete from resourcelog where id = " + fc.ResourceLog.Id;
        cmd.ExecuteNonQuery();
      }

      using (var repo = new Repository<FactionChange>())
      {
        var fc2 = repo.GetById(fc.Id);
        var rl2 = fc2.ResourceLog;
        Assert.IsNull(rl2);
      }
    }
  }
}
using System;
using System.IO;
using System.Linq;
using DAL.Entities;
using DAL.Repositories;
using log4net.Config;
using Npgsql;
using NUnit.Framework;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class ResourceLogTests
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

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static ResourceLog CreateNewResourceLog()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = "RU"};
      using (var repo = new PlayerRepository())
      {
        if (repo.GetById(p.Id) == null)
          repo.Add(p);
      }
      return new ResourceLog
               {
                 Source = "testsource",
                 BuildingName = "testbuilding",
                 PersistentId = 5815088867824369677,
                 Gain = true,
                 Player = p,
                 GoldChange = 11,
                 SilverChange = 12,
                 PerlChange = 13,
                 RedPerlChange = 14,
                 PopulationChange = 15,
                 Resource1Change = 16,
                 Resource2Change = 17,
                 Resource3Change = 18,
                 ShardChange = 152,
                 GoldTotal = 101,
                 SilverTotal = 102,
                 PerlTotal = 103,
                 RedPerlTotal = 104,
                 PopulationTotal = 105,
                 Resource1Total = 106,
                 Resource2Total = 107,
                 Resource3Total = 108,
                 ShardTotal = 180,
                 Timestamp = DateTime.Today
               };
    }

    [Test]
    public void AddResourceLogTest()
    {
      var r = CreateNewResourceLog();
      using (var repo = new ResourceLogRepository())
      {
        repo.Add(r);
        Assert.AreNotEqual(0, r.Id);
      }
      Console.WriteLine("--- get object ---");
      using (var repo = new ResourceLogRepository())
      {
        var r2 = repo.GetById(r.Id);
        Assert.AreNotSame(r, r2);
        Assert.AreEqual(r, r2);
      }
    }

    [Test]
    public void DeleteResourceLogTest()
    {
      var r = CreateNewResourceLog();
      using (var repo = new ResourceLogRepository())
      {
        repo.Add(r);
      }

      ResourceLog r2;
      using (var repo = new ResourceLogRepository())
      {
        r2 = repo.GetById(r.Id);
        repo.Remove(r2);
      }

      using (var repo = new ResourceLogRepository())
      {
        var r3 = repo.GetById(r2.Id);
        Assert.IsNull(r3);
      }
    }

    [Test]
    public void GetByParametersPagedTest()
    {
      const int elements = 10;
      var rlogs = new ResourceLog[elements];
      for (int i = 0; i < elements; i++)
      {
        rlogs[i] = CreateNewResourceLog();
        rlogs[i].Timestamp = DateTime.Today.AddHours(i);
        rlogs[i].GoldTotal = 100 + i;
        if (i < 5) rlogs[i].SilverChange = 0;
      }
      using (var repo = new ResourceLogRepository())
        foreach (var rlog in rlogs)
          repo.Add(rlog);

      // base test
      using (var repo = new ResourceLogRepository())
      {
        int rows;
        var results = repo.GetByParametersPaged(100, DateTime.Today.AddHours(0), DateTime.Today.AddHours(8), null, 2, 4,
                                                true, true, true, true, true, out rows);
        Assert.IsNotNull(results);
        Assert.AreEqual(4, results.Count);
        Assert.AreEqual(9, rows);
        Assert.AreEqual(106, results[0].GoldTotal);
        Assert.AreEqual(105, results[1].GoldTotal);
        Assert.AreEqual(104, results[2].GoldTotal);
        Assert.AreEqual(103, results[3].GoldTotal);
      }

      // test resource conditions
      using (var repo = new ResourceLogRepository())
      {
        int rows;
        var results = repo.GetByParametersPaged(100, DateTime.Today.AddHours(0), DateTime.Today.AddHours(8), true, 0, 100,
                                                false, true, false, false, false, out rows);
        Assert.IsNotNull(results);
        Assert.AreEqual(4, results.Count);
        Assert.AreEqual(4, rows);
        Assert.AreEqual(108, results[0].GoldTotal);
        Assert.AreEqual(107, results[1].GoldTotal);
        Assert.AreEqual(106, results[2].GoldTotal);
        Assert.AreEqual(105, results[3].GoldTotal);
      }

    }

  }
}
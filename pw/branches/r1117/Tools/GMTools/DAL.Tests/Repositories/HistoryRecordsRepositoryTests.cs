using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using Npgsql;
using log4net.Config;

namespace DAL.Tests.Repositories
{
  [TestFixture]
  public class HistoryRecordsRepositoryTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(Talent));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate talent cascade";
        cmd.ExecuteNonQuery();
      }
    }

    [Test]
    public void GetPlayerResourcesTest()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = "RU"};
      using (var repo = new PlayerRepository())
        repo.Add(p);

      var rl = new ResourceLog
                 {
                   Player = p,
                   Source = "rl_source",
                   BuildingName = "rl_building",
                   Gain = true,
                   Timestamp = DateTime.Today.AddHours(2),
                   GoldChange = 10,
                   GoldTotal = 130
                 };
      using (var repo = new ResourceLogRepository())
        repo.Add(rl);

      var t = new Talent {Id = 884733, Name = "testtalent"};
      using (var repo = new TalentRepository())
        repo.Add(t);

      var tl = new TalentLog
                 {
                   Player = p,
                   Talent = t,
                   Operation = "tl_operaion",
                   TalentInstanceId = 366,
                   PersistentId = 981754123,
                   Timestamp = DateTime.Today.AddHours(1)
                 };
      using (var repo = new TalentLogRepository())
        repo.Add(tl);

      using (var repo = new HistoryRecordsRepository())
      {
        int rows;
        var result = repo.GetPlayerResources(100, DateTime.Today, DateTime.Today.AddDays(1), new List<Int32>(), true, true, false, false, false, false, true, "", "", 0, 10, out rows).ToArray();
        Assert.AreEqual(2, result.Length);
        Assert.AreEqual(2, rows);
        
        Assert.AreEqual("Income", result[0].Type);
        Assert.AreEqual("rl_source rl_building", result[0].Info);
        Assert.AreEqual(10, result[0].GoldChange);
        Assert.AreEqual(120, result[0].GoldBefore);
        Assert.AreEqual(rl.Timestamp, result[0].Timestamp);

        Assert.AreEqual("Talent", result[1].Type);
        Assert.AreEqual("tl_operaion 'testtalent' (id=366), session=981754123", result[1].Info);
        Assert.IsNull(result[1].GoldChange);
        Assert.IsNull(result[1].GoldBefore);
        Assert.AreEqual(tl.Timestamp, result[1].Timestamp);
      }
    }

    [Test]
    public void GetPlayerFilteredTalentsTest()
    {
      var p = new Player { Id = 100, Nickname = "TestPlayer", Locale = "RU" };
      using (var repo = new PlayerRepository())
        repo.Add(p);

      var rl = new ResourceLog
      {
        Player = p,
        Source = "rl_source",
        BuildingName = "rl_building",
        Gain = true,
        Timestamp = DateTime.Today.AddHours(2),
        GoldChange = 10,
        GoldTotal = 130
      };
      using (var repo = new ResourceLogRepository())
        repo.Add(rl);

      var t1 = new Talent { Id = 884733, Name = "testtalent" };
      using (var repo = new TalentRepository())
        repo.Add(t1);

      var t2 = new Talent { Id = 884744, Name = "testtalent" };
      using (var repo = new TalentRepository())
        repo.Add(t2);

      var t3 = new Talent { Id = 884755, Name = "testtalent" };
      using (var repo = new TalentRepository())
        repo.Add(t3);

      var t4 = new Talent { Id = 884766, Name = "testtalent" };
      using (var repo = new TalentRepository())
        repo.Add(t4);

      var tl1 = new TalentLog()
      {
        Player = p,
        Talent = t1,
        Operation = "tl_operaion",
        TalentInstanceId = 366,
        PersistentId = 981754123,
        Timestamp = DateTime.Today.AddHours(1)
      };
      var tl2 = new TalentLog()
      {
        Player = p,
        Talent = t1,
        Operation = "tl_operaion",
        TalentInstanceId = 367,
        PersistentId = 981754123,
        Timestamp = DateTime.Today.AddHours(-1)
      };
      var tl3 = new TalentLog()
      {
        Player = p,
        Talent = t2,
        Operation = "tl_operaion",
        TalentInstanceId = 368,
        PersistentId = 981754123,
        Timestamp = DateTime.Today.AddHours(1)
      };
      var tl4 = new TalentLog()
      {
        Player = p,
        Talent = t2,
        Operation = "tl_operaion",
        TalentInstanceId = 369,
        PersistentId = 981754123,
        Timestamp = DateTime.Today.AddHours(-1)
      };
      var tl5 = new TalentLog()
      {
        Player = p,
        Talent = t3,
        Operation = "tl_operaion",
        TalentInstanceId = 370,
        PersistentId = 981754123,
        Timestamp = DateTime.Today.AddHours(1)
      };
      var tl6 = new TalentLog()
      {
        Player = p,
        Talent = t4,
        Operation = "tl_operaion",
        TalentInstanceId = 371,
        PersistentId = 981754123,
        Timestamp = DateTime.Today.AddHours(-1)
      };
      using (var repo = new TalentLogRepository())
      {
        repo.Add(tl1);
        repo.Add(tl2);
        repo.Add(tl3);
        repo.Add(tl4);
        repo.Add(tl5);
        repo.Add(tl6);
      }

      using (var repo = new HistoryRecordsRepository())
      {
        int rows;
        var result = repo.GetPlayerResources(100, DateTime.Today, DateTime.Today.AddDays(1), new List<Int32>() { 884733, 884744 }, true, true, false, false, false, false, true, "", "", 0, 10, out rows).ToArray();
        Assert.AreEqual(3, result.Length);
        Assert.AreEqual(3, rows);

        for (var i = 1; i < 3; i++)
        {
          var possibleInfo = new List<String>()
          {
            "tl_operaion 'testtalent' (id=366), session=981754123",
            "tl_operaion 'testtalent' (id=368), session=981754123"
          };
          var possibleTimestamp = new List<DateTime>()
          {
            tl1.Timestamp,
            tl2.Timestamp
          };
          Assert.AreEqual("Talent", result[i].Type);
          Assert.Contains(result[1].Info, possibleInfo);
          possibleInfo.Remove(result[1].Info);
          Assert.IsNull(result[1].GoldChange);
          Assert.IsNull(result[1].GoldBefore);
          Assert.Contains(result[1].Timestamp, possibleTimestamp);
          possibleTimestamp.Remove(result[1].Timestamp);
        }
      }
    }

    [Test]
    public void GetFractionChangesByPlayerIdTest()
    {
      var p1 = new Player { Id = 102, Nickname = "BadPlayer", Locale = "RU" };
      var p2 = new Player { Id = 101, Nickname = "TestPlayer", Locale = "RU" };
      using (var repo = new PlayerRepository())
      {
        repo.Add(p1);
        repo.Add(p2);
      }

      var rl1 = new ResourceLog
      {
        Id = 301,
        Source = "factionchange",
        BuildingName = "",
        PersistentId = null,
        Gain = false,
        Player = p2,
        GoldChange = -495,
        SilverChange = 0,
        PerlChange = 0,
        RedPerlChange = 0,
        PopulationChange = 0,
        Resource1Change = 0,
        Resource2Change = 0,
        Resource3Change = 0,
        ShardChange = 0,
        GoldTotal = 1000,
        SilverTotal = 1000000,
        PerlTotal = 10000,
        RedPerlTotal = 10000,
        PopulationTotal = 0,
        Resource1Total = 10000,
        Resource2Total = 10000,
        Resource3Total = 10000,
        ShardTotal = 10000,
        Timestamp = DateTime.Now
      };
      var rl2 = new ResourceLog
      {
        Id = 302,
        Source = "factionchange",
        BuildingName = "",
        PersistentId = null,
        Gain = false,
        Player = p1,
        GoldChange = -495,
        SilverChange = 0,
        PerlChange = 0,
        RedPerlChange = 0,
        PopulationChange = 0,
        Resource1Change = 0,
        Resource2Change = 0,
        Resource3Change = 0,
        ShardChange = 0,
        GoldTotal = 1000,
        SilverTotal = 1000000,
        PerlTotal = 10000,
        RedPerlTotal = 10000,
        PopulationTotal = 0,
        Resource1Total = 10000,
        Resource2Total = 10000,
        Resource3Total = 10000,
        ShardTotal = 10000,
        Timestamp = DateTime.Now
      };

      using (var repo = new ResourceLogRepository())
      {
        repo.Add(rl1);
        repo.Add(rl2);
      }

      var fc1 = new FactionChange
      {
        Player = p2,
        OldFaction = Faction.Adornian,
        NewFaction = Faction.Dokt,
        ResourceLog = null,
        Timestamp = DateTime.Now
      };
      var fc2 = new FactionChange
      {
        Player = p2,
        OldFaction = Faction.Adornian,
        NewFaction = Faction.Dokt,
        ResourceLog = rl1,
        Timestamp = DateTime.Now
      };
      var fc3 = new FactionChange
      {
        Player = p2,
        OldFaction = Faction.Adornian,
        NewFaction = Faction.Dokt,
        ResourceLog = null,
        Timestamp = DateTime.Now
      };
      var fc4 = new FactionChange
      {
        Player = p1,
        OldFaction = Faction.Adornian,
        NewFaction = Faction.Dokt,
        ResourceLog = rl2,
        Timestamp = DateTime.Now
      };
      using (var repo = new Repository<FactionChange>())
      {
        repo.Add(fc1);
        repo.Add(fc2);
        repo.Add(fc3);
        repo.Add(fc4);
      }

      using (var repo = new HistoryRecordsRepository())
      {
        int pageQuant;
        var result = repo.GetFractionChangesByPlayerId(p2.Id, 0, out pageQuant).ToArray();
        Assert.AreEqual(3, result.Length);
      }
    }
  }
}
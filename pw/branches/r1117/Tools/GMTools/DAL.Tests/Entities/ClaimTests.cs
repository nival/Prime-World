using System;
using System.IO;
using System.Linq;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using Npgsql;
using log4net.Config;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class ClaimTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(GMUserOperation));
      NHibernateHelper.SessionFactory.Evict(typeof(Claim));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate gm_useroperation cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static Claim CreateClaim()
    {
      var p1 = new Player { Id = 101, Nickname = "TestPlayer101", Locale = Player.DefaultLocale };
      var p2 = new Player { Id = 102, Nickname = "TestPlayer102", Locale = Player.DefaultLocale };
      using (var repo = new PlayerRepository())
      {
        repo.Add(ref p1);
        repo.Add(ref p2);
      }
      return new Claim
               {
                 FromPlayer = p1,
                 ToPlayer = p2,
                 Source = 1,
                 Category = 2,
                 Locale = p1.Locale,
                 Muid = "mooid",
                 Comment = "comment",
                 ChatLog = "chatlog",
                 Timestamp = DateTime.Today.AddHours(10),
                 PersistentId = 6,
                 Kills = 7,
                 Deaths = 8,
                 Assists = 9,
                 Points = 10,
                 Prime = 11,
                 Distance = 12,
                 Afks = 13,
                 ConnStatus = PlayerConnectionStatus.DisconnectedByClient,
                 GMUserOperation = null
               };
    }

    [Test]
    public void AddClaimTest()
    {
      var c = CreateClaim();
      using (var repo = new ClaimRepository())
        repo.Add(c);

      using (var repo = new ClaimRepository())
      {
        var c2 = repo.GetById(c.Id);
        Assert.IsNotNull(c2);
        Assert.AreNotSame(c2, c);
        Assert.AreEqual(c2.FromPlayer, c.FromPlayer);
        Assert.AreEqual(c2.ToPlayer, c.ToPlayer);
        Assert.AreEqual(c2.Source, c.Source);
        Assert.AreEqual(c2.Category, c.Category);
        Assert.AreEqual(c2.Locale, c.Locale);
        Assert.AreEqual(c2.Muid, c.Muid);
        Assert.AreEqual(c2.Comment, c.Comment);
        Assert.AreEqual(c2.ChatLog, c.ChatLog);
        Assert.AreEqual(c2.Timestamp, c.Timestamp);
        Assert.AreEqual(c2.PersistentId, c.PersistentId);
        Assert.AreEqual(c2.Kills, c.Kills);
        Assert.AreEqual(c2.Deaths, c.Deaths);
        Assert.AreEqual(c2.Assists, c.Assists);
        Assert.AreEqual(c2.Points, c.Points);
        Assert.AreEqual(c2.Prime, c.Prime);
        Assert.AreEqual(c2.Distance, c.Distance);
        Assert.AreEqual(c2.Afks, c.Afks);
        Assert.AreEqual(c2.ConnStatus, c.ConnStatus);
        Assert.IsNull(c2.GMUserOperation);
      }
    }

    [Test]
    public void GetPlayerClaimCountsTest()
    {
      var c1 = CreateClaim();
      var c2 = CreateClaim();
      var c3 = CreateClaim();
      c3.ToPlayer = c3.FromPlayer;
      var c4 = CreateClaim();
      c4.Timestamp = DateTime.Today.AddDays(-1);

      using (var repo = new ClaimRepository())
      {
        repo.Add(c1);
        repo.Add(c2);
        repo.Add(c3);
        repo.Add(c4);
      }

      Console.WriteLine("--- start test ---");
      using (var repo = new ClaimRepository())
      {
        int totalRows;
        var filter = new PlayerClaimFilter()
        {
          StartDate = DateTime.Today,
          EndDate = DateTime.Today.AddDays(1),
          CurrentComplaintsType = null,
          MinComplaints = 2,
          MaxComplaints = 0,
          CurrentHistoryType = null,
          MinHistory = 0,
          MaxHistory = 0,
          Locale = null,
          Muids = null
        };
        var counts =
          repo.GetPlayerClaimCounts(filter, "ClaimsCount", false, 0, 100).ToArray();

        Assert.AreEqual(1, counts[0].TotalRows);
        Assert.IsNotNull(counts);
        Assert.AreEqual(1, counts.Length);
        Assert.AreEqual(102, counts[0].PlayerId);
        Assert.AreEqual("TestPlayer102", counts[0].PlayerNickname);
        Assert.AreEqual(2, counts[0].ClaimsCount);
        Assert.AreEqual(0, counts[0].GMUserOperationsCount);
      }
    }
  }
}

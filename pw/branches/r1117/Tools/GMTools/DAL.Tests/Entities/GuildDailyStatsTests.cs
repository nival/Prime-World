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
  public class GuildDailyStatsTests
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
      NHibernateHelper.SessionFactory.Evict(typeof (Player));
      NHibernateHelper.SessionFactory.Evict(typeof (Guild));
      NHibernateHelper.SessionFactory.Evict(typeof (GuildDailyStats));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate guild cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
      }
    }


    private GuildDailyStats CreateNewGuildDailyStats()
    {
      var player = new Player { Id = 101, Locale = "RU" };
      using (var repo = new PlayerRepository())
        repo.Add(player);

      var guild = new Guild { Id = 201, CreationDate = DateTime.Today, Creator = player };
      using (var repo = new GuildRepository())
        repo.Add(guild);


      return new GuildDailyStats
               {
                 Guild = guild,
                 Rating = 1000,
                 GuildPoints = 250,
                 GuildPointsToday = -1,
                 Rank = 10,
                 VassalsCount = 3,
                 VassalsPoints = 33,
                 Timestamp = DateTime.Today
               };
    }


    [Test]
    public void AddObjectTest()
    {
      var obj = CreateNewGuildDailyStats();
      using (var repo = new Repository<GuildDailyStats>())
        repo.Add(obj);

      using (var repo = new Repository<GuildDailyStats>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.IsNotNull(obj2);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj.Guild.Id, obj2.Guild.Id);
        Assert.AreEqual(obj.Rating, obj2.Rating);
        Assert.AreEqual(obj.GuildPointsToday, obj2.GuildPointsToday);
        Assert.AreEqual(obj.GuildPoints, obj2.GuildPoints);
        Assert.AreEqual(obj.Rank, obj2.Rank);
        Assert.AreEqual(obj.VassalsCount, obj2.VassalsCount);
        Assert.AreEqual(obj.VassalsPoints, obj2.VassalsPoints);
        Assert.AreEqual(obj.Timestamp, obj2.Timestamp);
      }
    }

  }

}
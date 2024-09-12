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
  public class GuildSiegeTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(Guild));
      NHibernateHelper.SessionFactory.Evict(typeof(GuildSiege));

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


    private GuildSiege CreateNewGuildSiege()
    {
      var player = new Player { Id = 101, Locale = "RU" };
      using (var repo = new PlayerRepository())
        repo.Add(player);

      var guild1 = new Guild { Id = 201, CreationDate = DateTime.Today, Creator = player };
      var guild2 = new Guild { Id = 202, CreationDate = DateTime.Today, Creator = player };
      var guild3 = new Guild { Id = 203, CreationDate = DateTime.Today, Creator = player };
      using (var repo = new GuildRepository())
      {
        repo.Add(guild1);
        repo.Add(guild2);
        repo.Add(guild3);
      }

      var log = new GuildPointsLog { Guild = guild1 };
      using (var repo = new Repository<GuildPointsLog>())
        repo.Add(log);

      return new GuildSiege
      {
        Id = 88602342L,

        Guild = guild1,
        TargetGuild = guild2,
        TargetSuzerainGuild= guild3,
        Winner = guild3,
        GuildPointsLog = log,

        Rating = 1201,
        TargetRating = 1202,
        TargetSuzerainRating = 1203,
        StartTime = DateTime.Today,
        EndTime = DateTime.Today.AddDays(1)
      };
    }


    [Test]
    public void AddObjectTest()
    {
      var obj = CreateNewGuildSiege();
      using (var repo = new Repository<GuildSiege>())
        repo.Add(obj);

      using (var repo = new Repository<GuildSiege>())
      {
        var obj2 = repo.GetById(88602342L);
        Assert.IsNotNull(obj2);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj.Id, obj2.Id);
        Assert.AreEqual(obj.Guild.Id, obj2.Guild.Id);
        Assert.AreEqual(obj.TargetGuild.Id, obj2.TargetGuild.Id);
        Assert.AreEqual(obj.TargetSuzerainGuild.Id, obj2.TargetSuzerainGuild.Id);
        Assert.AreEqual(obj.Winner.Id, obj2.Winner.Id);
        Assert.AreEqual(obj.Rating, obj2.Rating);
        Assert.AreEqual(obj.TargetRating, obj2.TargetRating);
        Assert.AreEqual(obj.TargetSuzerainRating, obj2.TargetSuzerainRating);
        Assert.AreEqual(obj.GuildPointsLog.Id, obj2.GuildPointsLog.Id);
        Assert.AreEqual(obj.StartTime, obj2.StartTime);
        Assert.AreEqual(obj.EndTime, obj2.EndTime);
      }
    }


  }
}
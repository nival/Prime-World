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
  public class GuildSiegeParticipantTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(GuildSiegeParticipant));

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

    private GuildSiegeParticipant CreateNewGuildSiegeParticipant()
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

      var siege = new GuildSiege
                    {
                      Guild = guild1,
                      TargetGuild = guild2,
                      TargetSuzerainGuild = guild3,
                      Winner = guild3,
                      GuildPointsLog = log,
                      StartTime = DateTime.Today,
                      EndTime = DateTime.Today.AddDays(1)
                    };
      using (var repo = new Repository<GuildSiege>())
        repo.Add(siege);

      return new GuildSiegeParticipant
               {
                 GuildSiege = siege,
                 Guild = guild3,
                 Rating = 1300,
                 SiegePoints = 123,
                 GuildPointsLog = log,
                 StartTime = DateTime.Today,
                 EndTime = DateTime.Today.AddDays(1)
               };
    }


    [Test]
    public void AddObjectTest()
    {
      var obj = CreateNewGuildSiegeParticipant();
      using (var repo = new Repository<GuildSiegeParticipant>())
        repo.Add(obj);

      using (var repo = new Repository<GuildSiegeParticipant>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.IsNotNull(obj2);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj.Guild.Id, obj2.Guild.Id);
        Assert.AreEqual(obj.GuildSiege.Id, obj2.GuildSiege.Id);
        Assert.AreEqual(obj.Rating, obj2.Rating);
        Assert.AreEqual(obj.SiegePoints, obj2.SiegePoints);
        Assert.AreEqual(obj.GuildPointsLog.Id, obj2.GuildPointsLog.Id);
        Assert.AreEqual(obj.StartTime, obj2.StartTime);
        Assert.AreEqual(obj.EndTime, obj2.EndTime);
      }
    }

  }
}
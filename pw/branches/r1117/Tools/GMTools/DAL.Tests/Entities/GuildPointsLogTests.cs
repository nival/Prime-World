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
  public class GuildPointsLogTests
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

    private GuildPointsLog CreateNewObject()
    {
      var player = new Player { Id = 101, Locale = "RU" };
      using (var repo = new PlayerRepository())
        repo.Add(player);

      var guild = new Guild { Id = 201, CreationDate = DateTime.Today, Creator = player };
      using (var repo = new GuildRepository())
        repo.Add(guild);

      return new GuildPointsLog
               {
                 Type = GuildPointsLogType.GuildSiege,
                 Guild = guild,
                 Player = player,
                 GuildPointsChange = 77,
                 PlayerPointsChange = 88,
                 GuildPointsTotal = 777,
                 PlayerPointsTotal = 888,
                 PersistentId = 1234567890,
                 Timestamp = DateTime.Today
               };
    }


    [Test]
    public void SimpleTest()
    {
      var obj = CreateNewObject();
      using (var repo = new Repository<GuildPointsLog>())
        repo.Add(obj);

      using (var repo = new Repository<GuildPointsLog>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.IsNotNull(obj2);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj.Guild.Id, obj2.Guild.Id);
        Assert.AreEqual(obj.Player.Id, obj2.Player.Id);
        Assert.AreEqual(obj.GuildPointsChange, obj2.GuildPointsChange);
        Assert.AreEqual(obj.PlayerPointsChange, obj2.PlayerPointsChange);
        Assert.AreEqual(obj.GuildPointsTotal, obj2.GuildPointsTotal);
        Assert.AreEqual(obj.PlayerPointsTotal, obj2.PlayerPointsTotal);
        Assert.AreEqual(obj.PersistentId, obj2.PersistentId);
        Assert.AreEqual(obj.Timestamp, obj2.Timestamp);
      }
    }

  }

}
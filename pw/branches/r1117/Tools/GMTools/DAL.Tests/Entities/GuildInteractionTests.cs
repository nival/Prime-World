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
  public class GuildInteractionTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(GuildInteraction));

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


    private GuildInteraction CreateNewGuildInteraction()
    {
      var player = new Player { Id = 101, Locale = "RU" };
      using (var repo = new PlayerRepository())
        repo.Add(player);

      var guild1 = new Guild { Id = 201, CreationDate = DateTime.Today, Creator = player };
      var guild2 = new Guild { Id = 202, CreationDate = DateTime.Today, Creator = player };
      using (var repo = new GuildRepository())
      {
        repo.Add(guild1);
        repo.Add(guild2);
      }

      return new GuildInteraction
               {
                 Guild = guild1,
                 TargetGuild = guild2,
                 Type = GuildInteractionType.Capture,
                 WaitingTime = 120,
                 Timestamp = DateTime.Today
               };
    }


    [Test]
    public void AddObjectTest()
    {
      var obj = CreateNewGuildInteraction();
      using (var repo = new Repository<GuildInteraction>())
        repo.Add(obj);

      using (var repo = new Repository<GuildInteraction>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.IsNotNull(obj2);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj.Guild.Id, obj2.Guild.Id);
        Assert.AreEqual(obj.TargetGuild.Id, obj2.TargetGuild.Id);
        Assert.AreEqual(obj.Type, obj2.Type);
        Assert.AreEqual(obj.WaitingTime, obj2.WaitingTime);
        Assert.AreEqual(obj.Timestamp, obj2.Timestamp);
      }
    }

  }
}
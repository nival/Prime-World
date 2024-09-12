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
  public class GuildShopBuyTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(GuildShopItem));
      NHibernateHelper.SessionFactory.Evict(typeof(GuildShopBuy));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate guild cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate guildshopitem cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private GuildShopBuy CreateNewGuildShopBuy()
    {
      var player = new Player { Id = 101, Locale = "RU" };
      using (var repo = new PlayerRepository())
        repo.Add(player);

      var guild = new Guild { Id = 201, CreationDate = DateTime.Today, Creator = player };
      using (var repo = new GuildRepository())
        repo.Add(guild);

      var item = new GuildShopItem { Id = 8001, Name = "", DBID = "", Description = "" };
      using (var repo = new Repository<GuildShopItem>())
        repo.Add(item);

      var log = new GuildPointsLog { Guild = guild };
      using (var repo = new Repository<GuildPointsLog>())
        repo.Add(log);

      return new GuildShopBuy
      {
        Guild = guild,
        Player = player,
        GuildShopItem = item,
        HasSuzerain = true,
        ShopLevel = 5,
        GuildPointsLog = log,
        Timestamp = DateTime.Today
      };
    }


    [Test]
    public void AddObjectTest()
    {
      var obj = CreateNewGuildShopBuy();
      using (var repo = new Repository<GuildShopBuy>())
        repo.Add(obj);

      using (var repo = new Repository<GuildShopBuy>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.IsNotNull(obj2);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj.Guild.Id, obj2.Guild.Id);
        Assert.AreEqual(obj.Player.Id, obj2.Player.Id);
        Assert.AreEqual(obj.GuildShopItem.Id, obj2.GuildShopItem.Id);
        Assert.AreEqual(obj.HasSuzerain, obj2.HasSuzerain);
        Assert.AreEqual(obj.ShopLevel, obj2.ShopLevel);
        Assert.AreEqual(obj.GuildPointsLog.Id, obj2.GuildPointsLog.Id);
        Assert.AreEqual(obj.Timestamp, obj2.Timestamp);
      }
    }

  }
}
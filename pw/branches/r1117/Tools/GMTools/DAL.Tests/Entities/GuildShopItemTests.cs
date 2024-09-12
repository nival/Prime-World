using System.IO;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using Npgsql;
using log4net.Config;

namespace DAL.Tests.Entities
{

  [TestFixture]
  public class GuildShopItemTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(GuildShopItem));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate guildshopitem cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private GuildShopItem CreateNewGuildShopItem()
    {
      return new GuildShopItem
               {
                 Id = 901,
                 Name = "test shop item",
                 DBID = "/items/shop/test",
                 Description = "test description of guildshopitem"
               };
    }


    [Test]
    public void AddGuildBuffTest()
    {
      var obj = CreateNewGuildShopItem();
      using (var repo = new Repository<GuildShopItem>())
      {
        repo.Add(obj);
      }

      using (var repo = new Repository<GuildShopItem>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj, obj2);
      }
    }


    [Test]
    public void UpdateGuildBuffTest()
    {
      var obj = CreateNewGuildShopItem();
      using (var repo = new Repository<GuildShopItem>())
      {
        repo.Add(obj);
      }

      GuildShopItem obj2;
      using (var repo = new Repository<GuildShopItem>())
      {
        obj2 = repo.GetById(obj.Id);
        obj2.Name = "new buff";
        obj2.DBID = "/buffs/new";
        repo.Update(obj2);
      }

      using (var repo = new Repository<GuildShopItem>())
      {
        var obj3 = repo.GetById(obj2.Id);
        Assert.AreNotSame(obj2, obj3);
        Assert.AreEqual(obj2, obj3);
      }
    }
  }

}
using System.IO;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using Npgsql;
using log4net.Config;

namespace DAL.Tests.Entities
{

  [TestFixture]
  public class GuildBuffTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(GuildBuff));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate guildbuff cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private GuildBuff CreateNewGuildBuff()
    {
      return new GuildBuff
               {
                 Id = 801,
                 Name = "test buff",
                 DBID = "/buffs/test"
               };
    }


    [Test]
    public void AddGuildBuffTest()
    {
      var obj = CreateNewGuildBuff();
      using (var repo = new Repository<GuildBuff>() )
      {
        repo.Add(obj);
      }

      using (var repo = new Repository<GuildBuff>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj, obj2);
      }
    }


    [Test]
    public void UpdateGuildBuffTest()
    {
      var obj = CreateNewGuildBuff();
      using (var repo = new Repository<GuildBuff>())
      {
        repo.Add(obj);
      }

      GuildBuff obj2;
      using (var repo = new Repository<GuildBuff>())
      {
        obj2 = repo.GetById(obj.Id);
        obj2.Name = "new buff";
        obj2.DBID = "/buffs/new";
        repo.Update(obj2);
      }

      using (var repo = new Repository<GuildBuff>())
      {
        var obj3 = repo.GetById(obj2.Id);
        Assert.AreNotSame(obj2, obj3);
        Assert.AreEqual(obj2, obj3);
      }
    }

  }

}
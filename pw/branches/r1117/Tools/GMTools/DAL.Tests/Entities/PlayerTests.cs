using System;
using System.IO;
using System.Threading;
using DAL.Entities;
using DAL.Repositories;
using log4net.Config;
using NHibernate.Hql.Ast.ANTLR.Tree;
using Npgsql;
using NUnit.Framework;
using NUnit.Framework.SyntaxHelpers;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class PlayerTests
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

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static Player CreateNewPlayer()
    {
      return new Player
               {
                 Id = 10,
                 Nickname = "TestPlayer",
                 Faction = Faction.Dokt,
                 Nival = true,
                 Sex = 1,
                 Reliability = 200,
                 Locale = "ru"
               };
    }

    [Test]
    public void AddPlayerTest()
    {
      var p = CreateNewPlayer();
      using (var repo = new PlayerRepository())
      {
        repo.Add(p);
      }
      Console.WriteLine("--- get object ---");
      using (var repo = new PlayerRepository())
      {
        var p2 = repo.GetById(p.Id);
        Assert.AreNotSame(p, p2);
        Assert.AreEqual(p, p2);
      }
    }

    [Test]
    public void ConcurrentAddPlayersTest()
    {
      var p1 = CreateNewPlayer();
      var p2 = CreateNewPlayer();

      bool success = true;
      var tstart = new ParameterizedThreadStart(
        o =>
          {
            try
            {
              var p = (Player)o;
              using (var repo = new PlayerRepository())
              {
                repo.Add(ref p);
              }
            }
            catch (Exception ex)
            {
              Console.WriteLine(ex);
              success = false;
            }
          });

      var t1 = new Thread(tstart);
      var t2 = new Thread(tstart);
      t1.Start(p1);
      t2.Start(p2);
      t1.Join();
      t2.Join();
      Assert.That(success);
    }

    [Test]
    public void UpdatePlayerTest()
    {
      var p = CreateNewPlayer();
      using (var repo = new PlayerRepository())
      {
        repo.Add(p);
      }

      Player p2;
      using (var repo = new PlayerRepository())
      {
        p2 = repo.GetById(p.Id);
        p2.Nickname = "NewTestPlayer";
        p2.Faction = 0;
        p2.Nival = false;
        p2.Sex = 2;
        p2.Reliability = 2000;
        p2.Locale = "en";
        repo.Update(p2);
      }

      using (var repo = new PlayerRepository())
      {
        var p3 = repo.GetById(p2.Id);
        Assert.AreNotSame(p2, p3);
        Assert.AreEqual(p2, p3);
      }
    }
    
    [Test]
    public void RemovePlayerTest()
    {
      var p = CreateNewPlayer();
      using (var repo = new PlayerRepository())
      {
        repo.Add(p);
      }

      using (var repo = new PlayerRepository())
      {
        var p2 = repo.GetById(p.Id);
        repo.Remove(p2);
      }

      using (var repo = new PlayerRepository())
      {
        var p3 = repo.GetById(p.Id);
        Assert.IsNull(p3);
      }
    }

    [Test]
    public void LastmodifiedTest()
    {
      var p = CreateNewPlayer();
      using (var repo = new PlayerRepository())
      {
        repo.Add(p);
      }
      var now = DateTime.Now.ToUniversalTime();
      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "select lastmodified from player where id = " + p.Id;
        object lastmodified = cmd.ExecuteScalar();
        Assert.That(lastmodified, Is.Not.InstanceOfType(typeof(DBNull)));
        Assert.That(lastmodified, Is.LessThanOrEqualTo(now));
        Assert.That((now - (DateTime)lastmodified).TotalSeconds, Is.LessThan(5));
      }
    }

    [Test]
    public void CreateOrUpdateTest()
    {
      Player p;
      using (var repo = new PlayerRepository())
        p = repo.CreateOrUpdate(10, "TestNick", 1, Faction.Dokt, true, "ru", null, null);

      // test create
      using (var repo = new PlayerRepository())
      {
        var p1 = repo.GetById(10);
        Assert.IsNotNull(p1);
        Assert.AreEqual("TestNick", p1.Nickname);
        Assert.AreEqual(1, p1.Sex);
        Assert.AreEqual(Faction.Dokt, p1.Faction);
        Assert.AreEqual(true, p1.Nival);
        Assert.AreEqual("ru", p1.Locale);
      }

      // test update
      using (var repo = new PlayerRepository())
      {
        var p2 = repo.CreateOrUpdate(10, null, null, null, null, null, null, null);
        Assert.AreEqual(p, p2);

        var p3 = repo.CreateOrUpdate(10, "NewNick", 2, Faction.Adornian, false, "tr", null, null);
        Assert.AreNotEqual(p, p3);
        Assert.AreEqual("NewNick", p3.Nickname);
        Assert.AreEqual(2, p3.Sex);
        Assert.AreEqual(Faction.Adornian, p3.Faction);
        Assert.AreEqual(false, p3.Nival);
        Assert.AreEqual("tr", p3.Locale);
      }
    }

    [Test]
    public void CreateOrUpdateNullParametersTest()
    {
      Player p;
      using (var repo = new PlayerRepository())
      {
        p = repo.CreateOrUpdate(10, null, null, null, null, null, null, null);
        Assert.IsNotNull(p);
      }

      using (var repo = new PlayerRepository())
      {
        var p2 = repo.GetById(10);
        Assert.IsNotNull(p2);
        Assert.AreEqual(null, p2.Nickname);
        Assert.AreEqual(0, p2.Sex);
        Assert.AreEqual(Faction.None, p2.Faction);
        Assert.AreEqual(false, p2.Nival);
        Assert.AreEqual(Player.DefaultLocale, p2.Locale);
      }
    }

    [Test]
    public void CreateOrUpdateChangeFactionTest()
    {
      var p = CreateNewPlayer();
      p.Faction = Faction.None;
      using (var repo = new PlayerRepository())
        repo.Add(ref p);

      using (var repo = new PlayerRepository())
      {
        var p2 = repo.CreateOrUpdate(p.Id, null, null, Faction.Dokt, null, null, null, null);
        Assert.AreEqual(Faction.Dokt, p2.Faction);
      }
      using (var repo = new PlayerRepository())
      {
        var p2 = repo.GetById(p.Id);
        Assert.IsNotNull(p2);
        Assert.AreEqual(Faction.Dokt, p2.Faction);
      }

      using (var repo = new PlayerRepository())
      {
        var p2 = repo.CreateOrUpdate(p.Id, p.Nickname, p.Sex, Faction.Adornian, p.Nival, p.Locale, null, null);
        Assert.AreEqual(Faction.Adornian, p2.Faction);
      }
      using (var repo = new PlayerRepository())
      {
        var p2 = repo.GetById(p.Id);
        Assert.IsNotNull(p2);
        Assert.AreEqual(Faction.Adornian, p2.Faction);
      }
    }
  }
}
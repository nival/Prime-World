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
  public class GuildTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(Guild));
      NHibernateHelper.SessionFactory.Evict(typeof(Player));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate guild cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static Guild CreateNewGuild()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = Player.DefaultLocale};
      using (var repo = new PlayerRepository())
        repo.Add(ref p);
      var rl = new ResourceLog {Id = 2000, Player = p, Source = "guildcreate", SilverChange = -100000, Timestamp = DateTime.Today };
      using (var repo = new ResourceLogRepository())
        repo.Add(rl);

      return new Guild
               {
                 Id = 6000,
                 ShortName = "MTG",
                 FullName = "Magic Test Guild",
                 Creator = p,
                 CreationDate = DateTime.Today,
                 DisbandingDate = DateTime.Today.AddHours(1),
                 ResourceLog = rl
               };
    }

    [Test]
    public void AddGuildTest()
    {
      var g = CreateNewGuild();
      using (var repo = new GuildRepository())
      {
        repo.Add(g);
      }
      using (var repo = new GuildRepository())
      {
        var g2 = repo.GetById(g.Id);
        Assert.IsNotNull(g2);
        Assert.AreNotSame(g2, g);
        Assert.AreEqual(g2.ShortName, g.ShortName);
        Assert.AreEqual(g2.FullName, g.FullName);
        Assert.AreEqual(g2.Creator, g.Creator);
        Assert.AreEqual(g2.CreationDate, g.CreationDate);
        Assert.AreEqual(g2.DisbandingDate, g.DisbandingDate);
        Assert.AreEqual(g2.ResourceLog, g.ResourceLog);
      }
    }

    [Test]
    public void AddGuildWithoutNamesTest()
    {
      var g = CreateNewGuild();
      g.ShortName = null;
      g.FullName = null;
      using (var repo = new GuildRepository())
      {
        repo.Add(g);
      }
      using (var repo = new GuildRepository())
      {
        var g2 = repo.GetById(g.Id);
        Assert.IsNotNull(g2);
        Assert.AreNotSame(g2, g);
        Assert.AreEqual(g2.ShortName, g.ShortName);
        Assert.AreEqual(g2.FullName, g.FullName);
        Assert.AreEqual(g2.Creator, g.Creator);
        Assert.AreEqual(g2.CreationDate, g.CreationDate);
        Assert.AreEqual(g2.DisbandingDate, g.DisbandingDate);
        Assert.AreEqual(g2.ResourceLog, g.ResourceLog);
      }
    }

    [Test]
    public void RemoveGuildTest()
    {
      var g = CreateNewGuild();
      using (var repo = new GuildRepository())
      {
        repo.Add(g);
      }
      using (var repo = new GuildRepository())
      {
        var g2 = repo.GetById(g.Id);
        repo.Remove(g2);
      }
      using (var repo = new GuildRepository())
      {
        var g3 = repo.GetById(g.Id);
        Assert.IsNull(g3);
      }
    }

    [Test]
    public void GetOrCreateByIdTest()
    {
      using (var repo = new GuildRepository())
      {
        Assert.IsNull(repo.GetById(8600L));
        var guild = repo.GetOrCreateById(8600L);
        Assert.IsNotNull(guild);
        Assert.AreEqual(8600L, guild.Id);
      }
    }

  }

}
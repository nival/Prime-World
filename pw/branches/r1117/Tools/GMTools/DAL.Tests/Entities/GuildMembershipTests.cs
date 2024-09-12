using System;
using System.Diagnostics;
using System.IO;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using Npgsql;
using log4net.Config;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class GuildMembershipTests
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
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static GuildMembership CreateNewGuildMembership()
    {
      var p = new Player { Id = 100, Nickname = "TestPlayer", Locale = Player.DefaultLocale };
      using (var repo = new PlayerRepository())
        repo.Add(ref p);
      var rl = new ResourceLog { Id = 2000, Player = p, Source = "guildcreate", SilverChange = -100000, Timestamp = DateTime.Today };
      using (var repo = new ResourceLogRepository())
        repo.Add(rl);
      var g = new Guild
                {
                  Id = 6000,
                  ShortName = "MTG",
                  FullName = "Magic Test Guild",
                  Creator = p,
                  CreationDate = DateTime.Today,
                  ResourceLog = rl
                };
      using (var repo = new GuildRepository())
        repo.Add(g);

      return new GuildMembership
               {
                 Guild = g,
                 Player = p,
                 JoinDate = DateTime.Today.AddHours(1),
                 LeaveDate = DateTime.Today.AddHours(2),
                 Kicked = false
               };
    }

    [Test]
    public void AddGuildMembershipTest()
    {
      var gm = CreateNewGuildMembership();
      using (var repo = new GuildMembershipRepository())
      {
        repo.Add(gm);
      }
      using (var repo = new GuildMembershipRepository())
      {
        var gm2 = repo.GetById(gm.Id);
        Assert.IsNotNull(gm2);
        Assert.AreNotSame(gm2, gm);
        Assert.AreEqual(gm2.Guild.Id, gm.Guild.Id);
        Assert.AreEqual(gm2.Player.Id, gm.Player.Id);
        Assert.AreEqual(gm2.JoinDate, gm.JoinDate);
        Assert.AreEqual(gm2.LeaveDate, gm.LeaveDate);
        Assert.AreEqual(gm2.Kicked, gm.Kicked);
      }
    }

    [Test]
    public void AddTwoGuildMembershipTest()
    {
      var gm1 = CreateNewGuildMembership();
      var gm2 = new GuildMembership {Guild = gm1.Guild, Player = gm1.Player};
      using (var repo = new GuildMembershipRepository())
      {
        repo.Add(gm1);
        repo.Add(gm2);
      }
      using (var repo = new GuildMembershipRepository())
      {
        var gm11 = repo.GetById(gm1.Id);
        Assert.IsNotNull(gm11);
        var gm21 = repo.GetById(gm2.Id);
        Assert.IsNotNull(gm21);
      }
    }


    [Test]
    public void GetByParamsTest()
    {
      var gm = CreateNewGuildMembership();
      using (var repo = new GuildMembershipRepository())
      {
        repo.Add(gm);
      }
      using (var repo = new GuildMembershipRepository())
      {
        var gm2 = repo.GetByParams(gm.Player, gm.Guild);
        Assert.IsNotNull(gm2);
        Assert.AreNotSame(gm2, gm);
        Assert.AreEqual(gm2.Id, gm.Id);
        Assert.AreEqual(gm2.Guild.Id, gm.Guild.Id);
        Assert.AreEqual(gm2.Player.Id, gm.Player.Id);
      }
    }

    [Test]
    public void GetByParams_MultipleMemberships_Test()
    {
      var gm1 = CreateNewGuildMembership();
      var gm2 = new GuildMembership
                  {
                    Guild = gm1.Guild,
                    Player = gm1.Player,
                    JoinDate = gm1.JoinDate.AddHours(1),
                  };

      using (var repo = new GuildMembershipRepository())
      {
        repo.Add(gm1);
        repo.Add(gm2);
      }

      using (var repo = new GuildMembershipRepository())
      {
        var gm3 = repo.GetByParams(gm1.Player, gm1.Guild);
        Assert.IsNotNull(gm3);
        Assert.AreEqual(gm3.Id, gm2.Id);
      }
    }
  }
}
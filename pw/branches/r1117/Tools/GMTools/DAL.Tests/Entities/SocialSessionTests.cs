using System;
using System.IO;
using System.Linq;
using System.Threading;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using Npgsql;
using log4net.Config;

namespace DAL.Tests.Entities
{
  public class SocialSessionTests
  {
    [TestFixtureSetUpAttribute]
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
      NHibernateHelper.SessionFactory.Evict(typeof(SocialSession));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate guild cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static SocialSession CreateNewSocialSession()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = "RU"};
      using (var repo = new PlayerRepository())
        repo.Add(p);
      var g = new Guild {Id = 2000, Creator = p};
      using (var repo = new GuildRepository())
        repo.Add(g);
      p.Guild = g;
      using (var repo = new PlayerRepository())
        repo.Update(p);

      return new SocialSession
               {
                 Player = p,
                 StartTime = DateTime.Today,
                 EndTime = DateTime.Today.AddHours(1),
                 PlayerIp = "127.0.0.1",
                 Cluster = "Lolcluster",
                 Server = "Lolserver"
               };
    }


    [Test]
    public void AddObjectTest()
    {
      var ss = CreateNewSocialSession();
      Console.WriteLine("--- add object ---");
      using (var repo = new SocialSessionRepository())
        repo.Add(ss);
      Console.WriteLine("--- get object ---");
      using (var repo = new SocialSessionRepository())
      {
        var ss2 = repo.GetById(ss.Id);
        Assert.AreNotSame(ss, ss2);
        Assert.AreEqual(ss.Id, ss2.Id);
        Assert.AreEqual(ss.StartTime, ss2.StartTime);
        Assert.AreEqual(ss.EndTime, ss2.EndTime);
        Assert.AreEqual(ss.PlayerIp, ss2.PlayerIp);
        Assert.AreEqual(ss.Cluster, ss2.Cluster);
        Assert.AreEqual(ss.Server, ss2.Server);
      }
    }

    [Test(Description = "Проверка на ошибку 'Illegally attempted to associate a proxy with two open Sessions'")]
    public void AddObjectParallelSessionsTest()
    {
      var handle1 = new ManualResetEvent(false);
      var handle2 = new ManualResetEvent(false);

      var t1 = new Thread(() =>
                            {
                              Console.WriteLine("t1: start");
                              try
                              {
                                var prepo = new PlayerRepository();
                                var grepo = new GuildRepository();
                                var p = new Player { Id = 100, Nickname = "TestPlayer", Locale = "RU" };
                                prepo.Add(p);
                                var g = new Guild { Id = 2000, Creator = p };
                                grepo.Add(g);
                                p.Guild = g;
                                prepo.Update(p);
                              }
                              finally
                              {
                                handle1.Set();
                              }
                              Console.WriteLine("t1: waiting for t2");
                              handle2.WaitOne();
                              Console.WriteLine("t1: finish");
                            });
      var t2 = new Thread(() =>
                            {
                              Console.WriteLine("t2: waiting for t1");
                              handle1.WaitOne();
                              Console.WriteLine("t2: start");
                              try
                              {
                                var prepo = new PlayerRepository();
                                var p = prepo.GetById(100);
                                //var grepo = new GuildRepository();
                                //var g = grepo.GetById(2000);
                                using (var srepo = new SocialSessionRepository())
                                {
                                  var session = new SocialSession
                                  {
                                    Player = p,
                                    StartTime = DateTime.Today,
                                    EndTime = DateTime.Today.AddHours(1),
                                    PlayerIp = "127.0.0.1",
                                    Cluster = "Lolcluster",
                                    Server = "Lolserver"
                                  };
                                  srepo.Add(session);
                                }
                                Console.WriteLine("t2: finish");
                              }
                              finally
                              {
                                handle2.Set();
                              }
                            });
      t1.Start();
      t2.Start();
      t1.Join();
      t2.Join();

      using (var repo = new SocialSessionRepository())
      {
        var ss = repo.GetAll();
        Assert.AreEqual(1, ss.Count(s => s.Player.Id == 100));
      }
    }


    [Test]
    public void WriteLogoutTest()
    {
      var ss = CreateNewSocialSession();
      ss.EndTime = DateTime.MinValue;
      Console.WriteLine("--- add object ---");
      using (var repo = new SocialSessionRepository())
        repo.Add(ss);

      var endtime = ss.StartTime.AddMinutes(1);
      using (var repo = new SocialSessionRepository())
        repo.WriteLogout(ss.Player, ss.Server, ss.Cluster, endtime);

      using (var repo = new SocialSessionRepository())
      {
        var ss2 = repo.GetById(ss.Id);
        Assert.AreEqual(endtime, ss2.EndTime);
      }
    }


    [Test(Description = "Проверка на появление варнинга 'Unable to determine if entity is transient or detached'")]
    public void WriteDetachedEntityTest()
    {
      const int REPEAT = 2;
      Console.WriteLine("--- start test ---");

      var playerRepository = new PlayerRepository();
      var socialSessionRepository = new SocialSessionRepository();
      for (int i = 0; i < REPEAT; i++)
      {
        Console.WriteLine("--- Player.CreateOrUpdate {0} ---", i);
        Player p = playerRepository.CreateOrUpdate(100 + i, "TestUser" + i, null, null, null, null, null, null);
        var session = new SocialSession
                        {
                          Player = p,
                          PlayerIp = "1",
                          Server = "2",
                          Cluster = "3",
                          StartTime = DateTime.Today,
                        };
        Thread.Sleep(100);
        Console.WriteLine("--- SocialSession.Add {0} ---", i);
        socialSessionRepository.Add(session);
      }
    }

  }
}
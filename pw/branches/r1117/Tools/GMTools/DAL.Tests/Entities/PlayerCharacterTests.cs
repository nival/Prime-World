using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading;
using DAL.Entities;
using DAL.Repositories;
using log4net.Config;
using Npgsql;
using NUnit.Framework;
using NUnit.Framework.SyntaxHelpers;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class PlayerCharacterTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(Character));
      NHibernateHelper.SessionFactory.Evict(typeof(PlayerCharacter));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate character cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static PlayerCharacter CreateNewPlayerCharacter()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = "RU"};
      var c = new Character {Id = 200, Name = "TestCharacter"};
      using (var repo = new PlayerRepository())
      {
        if (repo.GetById(p.Id) == null)
          repo.Add(p);
      }
      using (var repo = new CharacterRepository())
      {
        if (repo.GetById(c.Id) == null)
          repo.Add(c);
      }

      return new PlayerCharacter
               {
                 Id = 10,
                 Player = new Player { Id = 100, Nickname = "TestPlayer", Locale = "RU" },
                 Character = new Character {Id = 200, Name = "TestCharacter"},
                 UnlockDate = new DateTime(2012, 01, 01, 22, 00, 00),
                 Locked = false
               };
    }

    [Test]
    public void AddPlayerCharacterTest()
    {
      var pc = CreateNewPlayerCharacter();
      Console.WriteLine("--- add object ---");
      using (var repo = new PlayerCharacterRepository())
      {
        repo.Add(ref pc);
      }
      Console.WriteLine("--- get object ---");
      using (var repo = new PlayerCharacterRepository())
      {
        var pc2 = repo.GetById(pc.Id);
        Assert.AreNotSame(pc, pc2);
        Assert.AreEqual(pc, pc2);
      }
    }

    [Test]
    public void ConcurrentAddPlayerCharacterTest()
    {
      var pc1 = CreateNewPlayerCharacter();
      var pc2 = CreateNewPlayerCharacter();

      Console.WriteLine("--- start test ---");
      bool success = true;
      var tstart = new ParameterizedThreadStart(
        o =>
        {
          Console.WriteLine("{0:HH:mm:ss.fff} start thread", DateTime.UtcNow);
          try
          {
            var pc = (PlayerCharacter)o;
            using (var repo = new PlayerCharacterRepository())
            {
              repo.Add(ref pc);
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
      t1.Start(pc1);
      t2.Start(pc2);
      t1.Join();
      t2.Join();
      Assert.That(success);
    }

    class ErrState
    {
      public int success;
      public int errors;
    }

    [Test]
    public void InsaneConcurrentAddPlayerCharacterTest()
    {
      const int SIZE = 10;
      const int REPEAT = 5;

      var players = new Player[SIZE];
      var characters = new Character[SIZE];
      using (var prepo = new PlayerRepository())
      using (var crepo = new CharacterRepository())
      {
        for (int i = 0; i < SIZE; i++)
        {
          var p = new Player {Id = 100 + i, Nickname = "test", Locale = "ru"};
          var c = new Character {Id = 200 + i, Name = "test"};
          prepo.Add(p);
          crepo.Add(c);
          players[i] = p;
          characters[i] = c;
        }
      }

      var state = new ErrState();

      for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
          Console.WriteLine("test[{0},{1}]",i,j);
          var p = players[i];
          var c = characters[j];
          var sync = new ManualResetEvent(false);
          for (int k = 0; k < REPEAT; k++)
            new Thread(() => AddPlayerCharacter(p, c, state, sync)).Start();
          Thread.Sleep(10);
          sync.Set();
        }
      
      var sw = Stopwatch.StartNew();
      while (SIZE * SIZE * REPEAT != state.success + state.errors && sw.ElapsedMilliseconds < 30000)
        Thread.Sleep(100);
      sw.Stop();
      Assert.AreEqual(SIZE*SIZE*REPEAT, state.success + state.errors);
      Console.WriteLine("expected: {0}, success: {1}, errors: {2}, elapsed {3} ms",
                        SIZE*SIZE*REPEAT, state.success, state.errors, sw.ElapsedMilliseconds);
    }

    private void AddPlayerCharacter(Player p, Character c, ErrState s, WaitHandle w)
    {
      w.WaitOne();
      Console.WriteLine("p={0},c={1},s={{{2},{3}}}",p.Id,c.Id,s.success,s.errors);
      try
      {
        using (var repo = new PlayerCharacterRepository())
          repo.GetOrCreateByParams(p, c.Id);
        s.success++;
      }
      catch (Exception ex)
      {
        Console.WriteLine(ex);
        s.errors++;
      }
    }

    [Test]
    public void UpdatePlayerCharacterTest()
    {
      var pc = CreateNewPlayerCharacter();
      using (var repo = new PlayerCharacterRepository())
      {
        repo.Add(pc);
      }

      PlayerCharacter pc2;
      using (var repo = new PlayerCharacterRepository())
      {
        pc2 = repo.GetById(pc.Id);
        pc2.Locked = true;
        pc2.UnlockDate = new DateTime(2012, 01, 01, 22, 00, 00);
        repo.Update(pc2);
      }

      using (var repo = new PlayerCharacterRepository())
      {
        var pc3 = repo.GetById(pc2.Id);
        Assert.AreNotSame(pc2, pc3);
        Assert.AreEqual(pc2, pc3);
      }
    }

    [Test]
    public void LastmodifiedTest()
    {
      var pc = CreateNewPlayerCharacter();
      using (var repo = new PlayerCharacterRepository())
      {
        repo.Add(pc);
      }
      var now = DateTime.Now.ToUniversalTime();
      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "select lastmodified from playercharacter where id = " + pc.Id;
        object lastmodified = cmd.ExecuteScalar();
        Assert.That(lastmodified, Is.Not.InstanceOfType(typeof(DBNull)));
        Assert.That(lastmodified, Is.LessThanOrEqualTo(now));
        Assert.That((now - (DateTime)lastmodified).TotalSeconds, Is.LessThan(5));
      }
    }
  }
}
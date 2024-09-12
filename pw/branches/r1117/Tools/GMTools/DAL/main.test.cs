using System;
using DAL.Entities;
using DAL.Repositories;
using NHibernate;
using NUnit.Framework;

namespace DAL.Tests
{
  [TestFixture]
  public class RepositoryTest
  {
    [/*TestFixtureSetUp, */Description("Migrate entity classes to database")]
    public void DBMigrate()
    {
      NHibernateHelper.DBMigrate();
    }

    [Test, Description("Open NHibernate session test")]
    public void OpenSessionTest()
    {
      ISession actual = NHibernateHelper.OpenSession();
      Assert.IsNotNull(actual);
    }

    [Test]
    public void LongNamesTest()
    {
      var c = new Character
      {
        Id = 1101,
        Name = "Очень длинное название, г".PadRight(666, 'ы'),
        Description = "CharacterRepositoryTest"
      };

      using (var repo = new CharacterRepository())
      {
        repo.Add(c);

        Character c2 = repo.GetById(c.Id);
        Assert.AreSame(c, c2);

        c.Description = "update";
        repo.Update(c);
      }
    }


    [Test, Description("Testing CRUD operations for Character repository class")]
    public void CharacterRepositoryTest()
    {
      var c = new Character
      {
        Id = 1101,
        Name = "character0",
        Description = "CharacterRepositoryTest"
      };

      using (var repo = new CharacterRepository())
      {
        repo.Add(c);

        Character c2 = repo.GetById(c.Id);
        Assert.AreSame(c, c2);

        c.Description = "update";
        repo.Update(c);

        repo.Remove(c);
        c2 = repo.GetById(c.Id);
        Assert.IsNull(c2);
      }
    }

    [Test, Description("Testing CRUD operations for Creature repository class")]
    public void CreatureRepositoryTest()
    {
      var c = new Creature
      {
        Id = 1201,
        Name = "creature0"
      };

      using (var repo = new CreatureRepository())
      {
        repo.Add(c);

        Creature c2 = repo.GetById(c.Id);
        Assert.AreSame(c, c2);

        c.Name += "+=";
        repo.Update(c);

        repo.Remove(c);
        c2 = repo.GetById(c.Id);
        Assert.IsNull(c2);
      }
    }

    [Test, Description("Testing CRUD operations for Building repository class")]
    public void BuildingRepositoryTest()
    {
      var b = new Building
      {
        Id = 1101,
        Name = "building0",
        Description = "BuildingRepositoryTest"
      };

      using (var repo = new BuildingRepository())
      {
        repo.Add(b);

        Building b2 = repo.GetById(b.Id);
        Assert.AreSame(b, b2);

        b.Name += "+=";
        b.Description = "update";
        repo.Update(b);

        repo.Remove(b);
        b2 = repo.GetById(b.Id);
        Assert.IsNull(b2);
      }
    }

    [Test, Description("Testing CRUD operations for Player repository class")]
    public void PlayerRepositoryTest()
    {
      var p = new Player
      {
        Login = "player"
      };

      using (var repo = new PlayerRepository())
      {
        repo.Add(p);

        Player p2 = repo.GetById(p.Id);
        Assert.AreSame(p, p2);

        p.Login = "update";
        repo.Update(p);

        repo.Remove(p);
        p2 = repo.GetById(p.Id);
        Assert.IsNull(p2);
      }
    }

    [Test, Description("Testing CRUD operations for PlayerCharacter repository class")]
    public void PlayerCharacterRepositoryTest()
    {
      var c = new Character
      {
        Id = 1201,
        Name = "char2",
        Description = "desc2"
      };

      var p = new Player
      {
        Login = "player2"
      };

      using (ISession sess = NHibernateHelper.OpenSession())
      using (sess.BeginTransaction())
      {
        sess.Save(c);
        sess.Save(p);
        sess.Transaction.Commit();
      }

      var pc = new PlayerCharacter
      {
        Player = p,
        Character = c
      };

      using (var repo = new PlayerCharacterRepository())
      {
        repo.Add(pc);

        PlayerCharacter pc2 = repo.GetById(pc.Id);
        Assert.AreSame(pc, pc2);

        repo.Update(pc);

        repo.Remove(pc);
        pc2 = repo.GetById(pc.Id);
        Assert.IsNull(pc2);

        var pc3 = repo.CreateByParams("SuperPlayer", c.Id);
        var pc4 = repo.GetByParams("superplayer", c.Id);
        Assert.AreSame(pc3, pc4);
      }
    }

    [Test, Description("Testing CRUD operations for Talent repository class")]
    public void TalentRepositoryTest()
    {
      var a = new Talent
      {
        Id = 1301,
        Name = "talent",
        UsageMode = UsageMode.Passive
      };

      using (var repo = new TalentRepository())
      {
        repo.Add(a);

        Talent a2 = repo.GetById(a.Id);
        Assert.AreSame(a, a2);

        a.Name = "update";
        repo.Update(a);

        repo.Remove(a);
        a2 = repo.GetById(a.Id);
        Assert.IsNull(a2);
      }
    }

    [Test, Description("Testing CRUD operations for ImpulsiveBuff repository class")]
    public void ImpulseBuffRepositoryTest()
    {
      var ib = new ImpulsiveBuff
      {
        Id = 1401,
        Name = "impulsiveBuff"
      };

      using (var repo = new ImpulsiveBuffRepository())
      {
        repo.Add(ib);

        ImpulsiveBuff ib2 = repo.GetById(ib.Id);
        Assert.AreSame(ib, ib2);

        ib.Name = "update";
        repo.Update(ib);

        repo.Remove(ib);
        ib2 = repo.GetById(ib.Id);
        Assert.IsNull(ib2);
      }
    }

    [Test, Description("Testing CRUD operations for SessionSideResult repository class")]
    public void SessionSideResultRepositoryTest()
    {
      var ssr = new SessionSideResult
      {
        TowerSacrificed = 10
      };

      using (var repo = new SessionSideResultRepository())
      {
        repo.Add(ssr);

        SessionSideResult ssr2 = repo.GetById(ssr.Id);
        Assert.AreSame(ssr, ssr2);

        ssr.TowerSacrificed = 11;
        repo.Update(ssr);

        repo.Remove(ssr);
        ssr2 = repo.GetById(ssr.Id);
        Assert.IsNull(ssr2);
      }
    }

    [Test, Description("Testing CRUD operations for GameSession repository class")]
    public void GameSessionRepositoryTest()
    {
      var gs = new GameSession
                 {
                   Server = "nival.com",
                   Map = "test",
                   SessionStatus = SessionStatus.Started,
                   StartTime = DateTime.Now,
                   SessionType = SessionType.Quick
                 };

      using (var repo = new GameSessionRepository())
      {
        repo.Add(gs);

        GameSession gs2 = repo.GetById(gs.Id);
        Assert.AreSame(gs, gs2);

        gs.Map = "q3dm6";
        repo.Update(gs);
        
        repo.Remove(gs);
        gs2 = repo.GetById(gs.Id);
        Assert.IsNull(gs2);
      }
    }

    [Test, Description("Testing CRUD operations for SessionToPlayer repository class")]
    public void SessionToPlayerRepositoryTest()
    {
      var c = new Character {Id = 1501};
      using (var repo = new CharacterRepository())
      {
        repo.Add(c);
      }
      PlayerCharacter pc;
      using (var repo = new PlayerCharacterRepository())
      {
        pc = repo.CreateByParams("SessionToPlayerRepositoryTest", c.Id);
      }

      var gs = new GameSession
                 {
                   IdClient = 4,
                   Server = "nival.com",
                   Map = "test4",
                   SessionStatus = SessionStatus.Started,
                   StartTime = DateTime.Now.AddHours(-1)
                 };
      var gs0 = new GameSession
      {
        IdClient = 40,
        Server = "nival.com",
        Map = "test40",
        SessionStatus = SessionStatus.Started,
        StartTime = DateTime.Now.AddHours(-2)
      };

      using (var repo = new GameSessionRepository())
      {
        repo.Add(gs);
        repo.Add(gs0);
      }

      var stp = new SessionToPlayer
                 {
                   Kills = 100500,
                   GameSession = gs,
                   PlayerCharacter = pc
                 };
      var stp0 = new SessionToPlayer
                 {
                   Kills = 100500,
                   GameSession = gs0,
                   PlayerCharacter = pc
                 };

      using (var repo = new SessionToPlayerRepository())
      {
        repo.Add(stp);
        repo.Add(stp0);

        SessionToPlayer stp2 = repo.GetById(stp.Id);
        Assert.AreSame(stp, stp2);

        repo.MaxLevelReached(stp.Id);
        stp2 = repo.GetById(stp.Id);
        Assert.GreaterOrEqual(stp2.MaxLevelReached, 60);

        int id = repo.GetIdByParams(stp.GameSession.IdClient, stp.PlayerCharacter.Player.Login);
        Assert.AreEqual(id, stp.Id);

        stp.NeutralCreepsKilled = 100500;
        repo.Update(stp);

        var dtos = repo.GetSessionToPlayerCount(DateTime.Today.AddDays(-1), DateTime.Today.AddDays(1));
        Assert.AreEqual(dtos.Count, 1);

        repo.Remove(stp);
        stp2 = repo.GetById(stp.Id);
        Assert.IsNull(stp2);
      }
    }

    [Test, Description("Test for logging game session start and game session results")]
    public void LogSessionResultsTest()
    {
      var c = new Character { Id = 2001 };
      using (var repo = new CharacterRepository())
      {
        repo.Add(c);
      }

      PlayerCharacter pc1, pc2;
      using (var repo = new PlayerCharacterRepository())
      {
        pc1 = repo.CreateByParams("LogSessionResultsTest1", c.Id);
        pc2 = repo.CreateByParams("LogSessionResultsTest2", c.Id);
      }

      var gs = new GameSession
                 {
                   IdClient = 8,
                   Server = "nival.com",
                   Map = "LogSessionResultsTest",
                   SessionStatus = SessionStatus.Started,
                   StartTime = DateTime.Now.AddHours(-1)
                 };
      using (var repo = new GameSessionRepository())
      {
        repo.WriteStarted(gs);
        Assert.AreNotEqual(gs.Id, 0);
      }

      using (var repo = new SessionToPlayerRepository())
      {
        repo.Create(gs.Id, pc1, 1, 1);
        repo.Create(gs.Id, pc2, 2, 2);

        Assert.AreNotEqual(repo.GetIdByParams(8, "LogSessionResultsTest1"), 0);
        Assert.AreNotEqual(repo.GetIdByParams(8, "LogSessionResultsTest2"), 0);
      }

      using (var repo = new GameSessionRepository())
      {
        repo.WriteEnded(gs.Id, DateTime.Now, "орки");
        repo.WriteEnded(gs.Id, DateTime.Now.AddHours(1), "нежить");

        var gs2 = repo.GetById(gs.Id);
        Assert.LessOrEqual(gs2.EndTime, DateTime.Now);
        Assert.AreEqual(gs2.SessionStatus, SessionStatus.Finished);
      }

      using (var repo = new SessionToPlayerRepository())
      {
        repo.LogSessionResults(gs.Id, pc1, 101, 101, 101, 101, 101, 101, 101);
        repo.LogSessionResults(gs.Id, pc2, 102, 102, 102, 102, 102, 102, 102);
        var stp1 = repo.GetById(repo.GetIdByParams(8, "LogSessionResultsTest1"));
        var stp2 = repo.GetById(repo.GetIdByParams(8, "LogSessionResultsTest2"));

        Assert.IsNotNull(stp1);
        Assert.IsNotNull(stp2);
        Assert.AreEqual(stp1.Deaths, 101);
        Assert.AreEqual(stp1.FinalLevel, 101);
        Assert.AreEqual(stp2.Deaths, 102);
        Assert.AreEqual(stp2.FinalLevel, 102);
      }
    }

    [Test, Description("Database functions test")]
    public void FunctionsTest()
    {
      ISession actual = NHibernateHelper.OpenSession();
      int version = (int) actual.GetNamedQuery("DBVersion").UniqueResult();
      System.Diagnostics.Debug.Write(version);
    }
  }
}
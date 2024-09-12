using System;
using System.Collections.Generic;
using System.IO;
using BusinessLogic.DBManagement;
using BusinessLogic.Game;
using DAL.Entities;
using DAL.Repositories;
using log4net.Config;
using Moq;
using NUnit.Framework;

namespace BusinessLogic.Tests.Tasks
{
  [TestFixture]
  public class SessionStartTaskTests
  {
    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void SimpleTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockgamesessionrepo = new Mock<IGameSessionRepository>();
      var mocksessiontoplayerrepo = new Mock<ISessionToPlayerRepository>();

      var p = new Player {Id = 123, Nickname = "nick", Sex = 1, Faction = Faction.Adornian};
      var pc = new PlayerCharacter {Player = p, Character = new Character {Id = 2345}};
      var now = DateTime.UtcNow;

      mockgamesessionrepo
        .Setup(m => m.WriteStarted(It.Is<GameSession>(gs => gs.PersistentId == 987654321 && gs.Map == "testmap" && gs.Server == "testserver" && gs.ServerAddress == "0.0.0.0" && gs.Cluster == "RU" && gs.SessionType == (SessionType)4 && gs.StartTime == now)))
        .Returns((GameSession gs) => { gs.Id = 2000; return gs.Id; });
      mockplayerrepo.Setup(m => m.CreateOrUpdate(123, "nick", 1, (Faction)1, null, null, null, null)).Returns(p);
      mockplayercharacterrepo.Setup(m => m.GetOrCreateByParams(p, pc.Character.Id)).Returns(pc);
      mocksessiontoplayerrepo.Setup(m => m.Create(2000, pc, p.Faction)).Returns(30000);

      var startinfos = new List<SessionStartPlayerInfo> { new SessionStartPlayerInfo { UserId = p.Id, Nickname = p.Nickname, Sex = p.Sex, Faction = (int)p.Faction, HeroId = pc.Character.Id } };
      var task = new SessionStartTask(987654321, "testmap", "testserver", "0.0.0.0", "RU", 4, now, startinfos,
        mockgamesessionrepo.Object, mockplayerrepo.Object, mockplayercharacterrepo.Object, mocksessiontoplayerrepo.Object);

      Assert.That(task.Execute());

      mockgamesessionrepo.VerifyAll();
      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
      mocksessiontoplayerrepo.VerifyAll();
    }

    [Test]
    public void GameSessionAddFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockgamesessionrepo = new Mock<IGameSessionRepository>();
      var mocksessiontoplayerrepo = new Mock<ISessionToPlayerRepository>();

      mockgamesessionrepo.Setup(m => m.WriteStarted(It.IsAny<GameSession>())).Throws(new Exception("TEST"));

      var startinfos = new List<SessionStartPlayerInfo> { new SessionStartPlayerInfo () };
      var task = new SessionStartTask(987654321, "testmap", "testserver", "0.0.0.0", "RU", 4, DateTime.UtcNow, startinfos,
        mockgamesessionrepo.Object, mockplayerrepo.Object, mockplayercharacterrepo.Object, mocksessiontoplayerrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockgamesessionrepo.VerifyAll();
      mockplayerrepo.Verify(m => m.CreateOrUpdate(It.IsAny<long>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<Faction?>(), It.IsAny<bool?>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<bool?>()), Times.Never());
    }

    [Test]
    public void PlayerCreateOrUpdateFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockgamesessionrepo = new Mock<IGameSessionRepository>();
      var mocksessiontoplayerrepo = new Mock<ISessionToPlayerRepository>();

      mockgamesessionrepo.Setup(m => m.WriteStarted(It.IsAny<GameSession>())).Returns(100);
      mockplayerrepo.Setup(m => m.CreateOrUpdate(It.IsAny<long>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<Faction?>(), It.IsAny<bool?>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<bool?>())).Throws<Exception>();

      var startinfos = new List<SessionStartPlayerInfo> { new SessionStartPlayerInfo() };
      var task = new SessionStartTask(987654321, "testmap", "testserver", "0.0.0.0", "RU", 4, DateTime.UtcNow, startinfos,
        mockgamesessionrepo.Object, mockplayerrepo.Object, mockplayercharacterrepo.Object, mocksessiontoplayerrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mockgamesessionrepo.VerifyAll();
      mockplayerrepo.VerifyAll();
    }

    [Test]
    public void TaskRestartTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockgamesessionrepo = new Mock<IGameSessionRepository>();
      var mocksessiontoplayerrepo = new Mock<ISessionToPlayerRepository>();

      mockgamesessionrepo.Setup(m => m.WriteStarted(It.IsAny<GameSession>())).Returns(100).AtMostOnce();
      mockplayerrepo.Setup(m => m.CreateOrUpdate(101, It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<Faction?>(), It.IsAny<bool?>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<bool?>())).Returns(new Player()).AtMostOnce();
      mockplayerrepo.Setup(m => m.CreateOrUpdate(102, It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<Faction?>(), It.IsAny<bool?>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<bool?>())).Throws<Exception>();
      mockplayerrepo.Setup(m => m.CreateOrUpdate(103, It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<Faction?>(), It.IsAny<bool?>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<bool?>())).Returns(new Player());
      mockplayercharacterrepo.Setup(m => m.GetOrCreateByParams(It.IsAny<Player>(), It.IsAny<int>())).Returns(new PlayerCharacter());

      var startinfos = new List<SessionStartPlayerInfo>
                         {
                           new SessionStartPlayerInfo {UserId = 101},
                           new SessionStartPlayerInfo {UserId = 102},
                           new SessionStartPlayerInfo {UserId = 103}
                         };
      var task = new SessionStartTask(987654321, "testmap", "testserver", "0.0.0.0", "RU", 4, DateTime.UtcNow, startinfos,
        mockgamesessionrepo.Object, mockplayerrepo.Object, mockplayercharacterrepo.Object, mocksessiontoplayerrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mockplayerrepo.Setup(m => m.CreateOrUpdate(102, It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<Faction?>(), It.IsAny<bool?>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<bool?>())).Returns(new Player());
      Assert.That(task.Execute());

      mockgamesessionrepo.VerifyAll();
      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
    }
  }
}
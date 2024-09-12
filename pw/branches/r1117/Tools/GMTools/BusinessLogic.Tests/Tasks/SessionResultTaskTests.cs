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
  public class SessionResultTaskTests
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
      var mockgamesessionrepo = new Mock<IGameSessionRepository>();
      var mocksessiontoplayerrepo = new Mock<ISessionToPlayerRepository>();

      var p = new Player {Id = 123};
      var now = DateTime.UtcNow;
      var results = new List<SessionResultPlayerInfo> { new SessionResultPlayerInfo { UserId = 123, FinalLevel = 25, Leaver = false, Score = 150, Kills = 8, Deaths = 2, Assists = 6, EnemyCreepsKilled = 99, NeutralCreepsKilled = 11 } };
      var task = new SessionResultTask(666, 2, 1, 4, now, results, mockgamesessionrepo.Object, mockplayerrepo.Object, mocksessiontoplayerrepo.Object);

      mockgamesessionrepo.Setup(m => m.WriteEnded(666, 2, now, 1, 4)).Returns(777);
      mockplayerrepo.Setup(m => m.GetById(123)).Returns(p);
      mocksessiontoplayerrepo.Setup(m => m.LogSessionResults(777, p, 25, false, 150, 8, 2, 6, 99, 11));

      Assert.That(task.Execute());

      mockgamesessionrepo.VerifyAll();
      mockplayerrepo.VerifyAll();
      mocksessiontoplayerrepo.VerifyAll();
    }

    [Test]
    public void GameSessionWriteEndedFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockgamesessionrepo = new Mock<IGameSessionRepository>();
      var mocksessiontoplayerrepo = new Mock<ISessionToPlayerRepository>();

      var now = DateTime.UtcNow;
      var results = new List<SessionResultPlayerInfo> { new SessionResultPlayerInfo { UserId = 123, FinalLevel = 25, Leaver = false, Score = 150, Kills = 8, Deaths = 2, Assists = 6, EnemyCreepsKilled = 99, NeutralCreepsKilled = 11 } };
      var task = new SessionResultTask(666, 2, 1, 4, now, results, mockgamesessionrepo.Object, mockplayerrepo.Object, mocksessiontoplayerrepo.Object);

      mockgamesessionrepo.Setup(m => m.WriteEnded(666, 2, now, 1, 4)).Throws(new Exception("TEST"));

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockgamesessionrepo.VerifyAll();
      mockplayerrepo.Verify(m => m.GetById(123), Times.Never());
    }

    [Test]
    public void TaskRestartTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockgamesessionrepo = new Mock<IGameSessionRepository>();
      var mocksessiontoplayerrepo = new Mock<ISessionToPlayerRepository>();

      var p1 = new Player { Id = 101 };
      var p2 = new Player { Id = 102 };
      var p3 = new Player { Id = 103 };
      var now = DateTime.UtcNow;
      var results = new List<SessionResultPlayerInfo>
                      {
                        new SessionResultPlayerInfo {UserId = 101},
                        new SessionResultPlayerInfo {UserId = 102},
                        new SessionResultPlayerInfo {UserId = 103}
                      };
      var task = new SessionResultTask(666, 2, 1, 4, now, results, mockgamesessionrepo.Object, mockplayerrepo.Object, mocksessiontoplayerrepo.Object);

      mockgamesessionrepo.Setup(m => m.WriteEnded(666, 2, now, 1, 4)).Returns(777).AtMostOnce();
      mockplayerrepo.Setup(m => m.GetById(101)).Returns(p1);
      mockplayerrepo.Setup(m => m.GetById(102)).Returns(p2);
      mockplayerrepo.Setup(m => m.GetById(103)).Returns(p3);
      mocksessiontoplayerrepo.Setup(m => m.LogSessionResults(777, p1, 0, false, 0, 0, 0, 0, 0, 0)).AtMostOnce();
      mocksessiontoplayerrepo.Setup(m => m.LogSessionResults(777, p2, 0, false, 0, 0, 0, 0, 0, 0)).Throws<Exception>();
      mocksessiontoplayerrepo.Setup(m => m.LogSessionResults(777, p3, 0, false, 0, 0, 0, 0, 0, 0)).AtMostOnce();

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mocksessiontoplayerrepo.Setup(m => m.LogSessionResults(777, p2, 0, false, 0, 0, 0, 0, 0, 0));
      Assert.That(task.Execute());

      mockgamesessionrepo.VerifyAll();
      mocksessiontoplayerrepo.VerifyAll();
    }
  }
}
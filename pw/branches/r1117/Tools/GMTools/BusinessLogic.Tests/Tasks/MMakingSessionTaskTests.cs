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
  public class MMakingSessionTaskTests
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
      var mockmmakingplayerrepo = new Mock<IMMakingPlayerRepository>();
      var mockmmakingsessionrepo = new Mock<IMMakingSessionRepository>();

      var p = new Player { Id = 25 };
      var c = new Character { Id = 123456 };
      var pc = new PlayerCharacter { Player = p, Character = c };
      mockplayerrepo.Setup(m => m.CreateOrUpdate(25L, null, 0, It.IsAny<Faction>(), null, null, null, null)).Returns(p);
      mockplayercharacterrepo.Setup(m => m.GetOrCreateByParams(p, 123456)).Returns(pc);
      mockmmakingplayerrepo.Setup(m => m.Add(It.IsAny<MMakingPlayer>()));
      mockmmakingsessionrepo.Setup(m => m.Add(It.Is<MMakingSession>(ms => ms.PersistentId == 9876543 && ms.ManoeuvresFaction == -1 && ms.Status == 1 && ms.Basket == 4 && ms.Map == "testmap")));

      var now = DateTime.Now;
      var infos = new List<MMakingPlayerInfo> {new MMakingPlayerInfo {UserId = 25, HeroId = 123456}};
      var task = new MMakingSessionTask(9876543, 1, -1, 4, "testmap", now, infos, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmmakingplayerrepo.Object, mockmmakingsessionrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
      mockmmakingplayerrepo.VerifyAll();
      mockmmakingsessionrepo.VerifyAll();
    }

    [Test]
    public void MMakingSessionAddFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockmmakingplayerrepo = new Mock<IMMakingPlayerRepository>();
      var mockmmakingsessionrepo = new Mock<IMMakingSessionRepository>();

      mockmmakingsessionrepo.Setup(m => m.Add(It.IsAny<MMakingSession>())).Throws(new Exception("TEST EXCEPTION"));

      var now = DateTime.Now;
      var infos = new List<MMakingPlayerInfo> { new MMakingPlayerInfo { UserId = 25, HeroId = 123456 } };
      var task = new MMakingSessionTask(9876543, 1, -1, -1, "", now, infos, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmmakingplayerrepo.Object, mockmmakingsessionrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST EXCEPTION", task.LastErrorMessage);

      mockmmakingsessionrepo.VerifyAll();
    }

    [Test]
    public void MMakingPlayerSubtaskFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockmmakingplayerrepo = new Mock<IMMakingPlayerRepository>();
      var mockmmakingsessionrepo = new Mock<IMMakingSessionRepository>();

      var p = new Player { Id = 25 };
      var c = new Character { Id = 123456 };
      var pc = new PlayerCharacter { Player = p, Character = c };
      mockplayerrepo.Setup(m => m.CreateOrUpdate(25, null, 0, Faction.Dokt, null, null, null, null)).Returns(p).AtMostOnce();
      mockplayerrepo.Setup(m => m.CreateOrUpdate(26, null, 0, Faction.Dokt, null, null, null, null)).Throws(new Exception("TEST")).AtMost(2);
      mockplayercharacterrepo.Setup(m => m.GetOrCreateByParams(p, 123456)).Returns(pc);
      mockmmakingplayerrepo.Setup(m => m.Add(It.IsAny<MMakingPlayer>()));
      mockmmakingsessionrepo.Setup(m => m.Add(It.Is<MMakingSession>(ms => ms.PersistentId == 9876543 && ms.ManoeuvresFaction == -1 && ms.Status == 1))).AtMostOnce();

      var now = DateTime.Now;
      var infos = new List<MMakingPlayerInfo>
                    {
                      new MMakingPlayerInfo {UserId = 25, HeroId = 123456},
                      new MMakingPlayerInfo {UserId = 26, HeroId = 123456}
                    };
      var task = new MMakingSessionTask(9876543, 1, -1, -1, "", now, infos, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmmakingplayerrepo.Object, mockmmakingsessionrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mockplayerrepo.Setup(m => m.CreateOrUpdate(26, null, 0, Faction.Dokt, null, null, null, null)).Returns(p).AtMost(2);
      Assert.IsTrue(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
      mockmmakingplayerrepo.VerifyAll();
      mockmmakingsessionrepo.VerifyAll();
    }
  }
}
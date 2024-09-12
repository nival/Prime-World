using System;
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
  public class MMakingPlayerTaskTests
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

      var p = new Player {Id = 25};
      var c = new Character {Id = 123456};
      var pc = new PlayerCharacter {Player = p, Character = c};
      mockplayerrepo.Setup(m => m.CreateOrUpdate(25, null, 1, Faction.Adornian, null, null, null, null)).Returns(p);
      mockplayercharacterrepo.Setup(m => m.GetOrCreateByParams(p, 123456)).Returns(pc);
      mockmmakingplayerrepo
        .Setup(m => m.Add(It.Is<MMakingPlayer>(mp => mp.PlayerCharacter == pc && mp.Rating == 1200 && mp.PlayerRating == 2200 && mp.Force == 110.3f && mp.FameLevel == 16
                                                     && mp.LobbyReaction == 2 && mp.Party == -1 && mp.WaitInterval == 59 && mp.Basket == 4
                                                     && mp.LobbyReactionTime == 6.7f)));

      var now = DateTime.Now;
      var info = new MMakingPlayerInfo { UserId = 25, Faction = 1, Sex = 1, HeroId = 123456, Rating = 1200, PlayerRating = 2200, Force = 110.3f, FameLevel = 16, LobbyReaction = 2, LobbyReactionTime = 6.7f, PartyId = -1, WaitTime = 59, Basket = 4};
      var task = new MMakingPlayerTask(info, null, now, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmmakingplayerrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
      mockmmakingplayerrepo.VerifyAll();
    }

    [Test]
    public void CreateOrUpdateFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockmmakingplayerrepo = new Mock<IMMakingPlayerRepository>();

      mockplayerrepo
        .Setup(m => m.CreateOrUpdate(It.IsAny<long>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<Faction>(), It.IsAny<bool?>(), It.IsAny<String>(), It.IsAny<int?>(), It.IsAny<bool?>()))
        .Throws(new Exception());

      var now = DateTime.Now;
      var info = new MMakingPlayerInfo();
      var task = new MMakingPlayerTask(info, null, now, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmmakingplayerrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.Verify(m => m.GetOrCreateByParams(It.IsAny<Player>(), It.IsAny<int>()), Times.Never());
      mockmmakingplayerrepo.Verify(m => m.Add(It.IsAny<MMakingPlayer>()), Times.Never());
    }

    [Test]
    public void GetOrCreateByParamsFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockmmakingplayerrepo = new Mock<IMMakingPlayerRepository>();

      mockplayercharacterrepo
        .Setup(m => m.GetOrCreateByParams(It.IsAny<Player>(), It.IsAny<int>()))
        .Throws(new Exception());

      var now = DateTime.Now;
      var info = new MMakingPlayerInfo();
      var task = new MMakingPlayerTask(info, null, now, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmmakingplayerrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mockplayercharacterrepo.VerifyAll();
      mockmmakingplayerrepo.Verify(m => m.Add(It.IsAny<MMakingPlayer>()), Times.Never());
    }

    [Test]
    public void GetOrCreateByParamsNullTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockmmakingplayerrepo = new Mock<IMMakingPlayerRepository>();

      mockplayerrepo
        .Setup(m => m.CreateOrUpdate(It.IsAny<long>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<Faction>(), It.IsAny<bool?>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<bool?>()))
        .Returns(new Player());

      var now = DateTime.Now;
      var info = new MMakingPlayerInfo();
      var task = new MMakingPlayerTask(info, null, now, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmmakingplayerrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mockplayercharacterrepo.VerifyAll();
      mockmmakingplayerrepo.Verify(m => m.Add(It.IsAny<MMakingPlayer>()), Times.Never());
    }

    [Test]
    public void MMakingPlayerAddFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockmmakingplayerrepo = new Mock<IMMakingPlayerRepository>();

      var p = new Player { Id = 25 };
      var c = new Character { Id = 123456 };
      var pc = new PlayerCharacter { Player = p, Character = c };
      mockplayerrepo
        .Setup(m => m.CreateOrUpdate(It.IsAny<long>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<Faction>(), It.IsAny<bool?>(), It.IsAny<string>(), It.IsAny<int?>(), It.IsAny<bool?>()))
        .Returns(p);
      mockplayercharacterrepo
        .Setup(m => m.GetOrCreateByParams(It.IsAny<Player>(), It.IsAny<int>()))
        .Returns(pc);
      mockmmakingplayerrepo
        .Setup(m => m.Add(It.IsAny<MMakingPlayer>()))
        .Throws(new Exception());

      var now = DateTime.Now;
      var info = new MMakingPlayerInfo();
      var task = new MMakingPlayerTask(info, null, now, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmmakingplayerrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
      mockmmakingplayerrepo.VerifyAll();
    }

  }
}
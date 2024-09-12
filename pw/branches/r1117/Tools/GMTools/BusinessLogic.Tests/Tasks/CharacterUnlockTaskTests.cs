using System;
using System.Collections.Generic;
using System.IO;
using BusinessLogic.DBManagement;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;
using log4net.Config;
using Moq;
using NUnit.Framework;

namespace BusinessLogic.Tests.Tasks
{
  [TestFixture]
  public class CharacterUnlockTaskTests
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
      var mockcharacterunlockrepo = new Mock<ICharacterUnlockRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      var now = DateTime.UtcNow;
      var p = new Player {Id = 101};
      var pc = new PlayerCharacter {Player = p, Character = new Character {Name = "Hero"}};
      var unlocks = new List<UnlockHeroInfoBL> { new UnlockHeroInfoBL {UserId = 101, HeroId = 987654, RChange = new ResourceTableBL {Gold = 5}, RTotal = new ResourceTableBL {Gold = 10}, Timestamp = now}};

      mockplayerrepo.Setup(m => m.GetById(101)).Returns(p);
      mockplayercharacterrepo.Setup(m => m.GetOrCreateByParams(p, 987654)).Returns(pc);

      var task = new CharacterUnlockTask(unlocks, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockcharacterunlockrepo.Object, mockresourcelogrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
      mockplayercharacterrepo.Verify(m => m.Update(pc), Times.Once());
      Assert.AreEqual(now, pc.UnlockDate);
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.Source == CharacterUnlockTask.RLOG_SOURCE && r.BuildingName == "Hero" && r.Player == p && r.GoldChange == -5 && r.GoldTotal == 10 && r.Timestamp == now)), Times.Once());
      mockcharacterunlockrepo.Verify(m => m.Add(It.Is<CharacterUnlock>(cu => cu.Timestamp == now && cu.PlayerCharacter == pc)));
    }

    [Test]
    public void TaskRestartTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockcharacterunlockrepo = new Mock<ICharacterUnlockRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      var unlocks = new List<UnlockHeroInfoBL>
                      {
                        new UnlockHeroInfoBL {UserId = 101, RChange = new ResourceTableBL(), RTotal = new ResourceTableBL()},
                        new UnlockHeroInfoBL {UserId = 102, RChange = new ResourceTableBL(), RTotal = new ResourceTableBL()},
                        new UnlockHeroInfoBL {UserId = 103, RChange = new ResourceTableBL(), RTotal = new ResourceTableBL()}
                      };

      mockplayerrepo.Setup(m => m.GetById(It.IsAny<long>()))
        .Returns((long id) => new Player {Id = id});
      mockplayercharacterrepo.Setup(m => m.GetOrCreateByParams(It.IsAny<Player>(), It.IsAny<int>()))
        .Returns((Player p, int c) => new PlayerCharacter {Player = p, Character = new Character()});
      mockcharacterunlockrepo.Setup(m => m.Add(It.Is<CharacterUnlock>(cu => cu.PlayerCharacter.Player.Id == 101))).AtMostOnce();
      mockcharacterunlockrepo.Setup(m => m.Add(It.Is<CharacterUnlock>(cu => cu.PlayerCharacter.Player.Id == 102))).Throws(new Exception("TEST"));
      mockcharacterunlockrepo.Setup(m => m.Add(It.Is<CharacterUnlock>(cu => cu.PlayerCharacter.Player.Id == 103))).AtMostOnce();

      var task = new CharacterUnlockTask(unlocks, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockcharacterunlockrepo.Object, mockresourcelogrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockcharacterunlockrepo.Setup(m => m.Add(It.Is<CharacterUnlock>(cu => cu.PlayerCharacter.Player.Id == 102)));
      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
      mockcharacterunlockrepo.VerifyAll();
    }
  }
}
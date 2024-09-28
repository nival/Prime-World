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
  public class MoveToBathTaskTests
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
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();
      var mockmovetobathrepo = new Mock<IRepository<MoveToBath>>();

      var now = DateTime.UtcNow;
      var p = new Player {Id = 101};
      var pc = new PlayerCharacter {Player = p};

      mockplayerrepo.Setup(m => m.GetById(101)).Returns(p).AtMostOnce();
      mockplayercharacterrepo.Setup(m => m.GetOrCreateByParams(p, 987654)).Returns(pc).AtMostOnce();
      
      var infos = new List<MoveToBathInfoBL> { new MoveToBathInfoBL { UserId = 101, HeroId = 987654, Minutes = 180, RChange = new ResourceTableBL { Gold = 5 }, RTotal = new ResourceTableBL { Gold = 10 }, Timestamp = now } };
      var task = new MoveToBathTask(infos, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmovetobathrepo.Object, mockresourcelogrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
      mockplayercharacterrepo.Verify(m => m.Update(pc), Times.Never());
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.Source == "movetobath" && r.Gain == false && r.Player == p && r.GoldChange == -5 && r.GoldTotal == 10 && r.Timestamp == now)), Times.Once());
      mockmovetobathrepo.Verify(m => m.Add(It.Is<MoveToBath>(mt => mt.PlayerCharacter == pc && mt.Minutes == 180 && mt.Timestamp == now)));
    }

    [Test]
    public void TaskRestartTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockplayercharacterrepo = new Mock<IPlayerCharacterRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();
      var mockmovetobathrepo = new Mock<IRepository<MoveToBath>>();

      mockplayerrepo.Setup(m => m.GetById(It.IsAny<long>()))
        .Returns((long id) => new Player { Id = id });
      mockplayercharacterrepo.Setup(m => m.GetOrCreateByParams(It.IsAny<Player>(), It.IsAny<int>()))
        .Returns((Player p, int c) => new PlayerCharacter { Player = p, Character = new Character() });
      mockmovetobathrepo.Setup(m => m.Add(It.Is<MoveToBath>(cu => cu.PlayerCharacter.Player.Id == 101))).AtMostOnce();
      mockmovetobathrepo.Setup(m => m.Add(It.Is<MoveToBath>(cu => cu.PlayerCharacter.Player.Id == 102))).Throws(new Exception("TEST"));
      mockmovetobathrepo.Setup(m => m.Add(It.Is<MoveToBath>(cu => cu.PlayerCharacter.Player.Id == 103))).AtMostOnce();

      var infos = new List<MoveToBathInfoBL>
                    {
                      new MoveToBathInfoBL { UserId = 101, RChange = new ResourceTableBL(), RTotal = new ResourceTableBL()},
                      new MoveToBathInfoBL { UserId = 102, RChange = new ResourceTableBL(), RTotal = new ResourceTableBL()},
                      new MoveToBathInfoBL { UserId = 103, RChange = new ResourceTableBL(), RTotal = new ResourceTableBL()}
                    };
      var task = new MoveToBathTask(infos, mockplayerrepo.Object, mockplayercharacterrepo.Object, mockmovetobathrepo.Object, mockresourcelogrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockmovetobathrepo.Setup(m => m.Add(It.Is<MoveToBath>(cu => cu.PlayerCharacter.Player.Id == 102)));
      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayercharacterrepo.VerifyAll();
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(rl => rl.Player.Id == 101)), Times.Once());
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(rl => rl.Player.Id == 102)), Times.Once());
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(rl => rl.Player.Id == 103)), Times.Once());
      mockmovetobathrepo.VerifyAll();
    }
  }
}
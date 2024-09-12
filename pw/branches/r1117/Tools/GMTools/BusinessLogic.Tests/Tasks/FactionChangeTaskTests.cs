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
  public class FactionChangeTaskTests
  {
    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void PaidFactionChangeTest()
    {
      var p = new Player {Id = 1, Faction = Faction.Dokt};
      var mockplayerrepo = new Mock<IPlayerRepository>();
      mockplayerrepo.Setup(m => m.GetById(1)).Returns(p);
      var mockfactionchangerepo = new Mock<IRepository<FactionChange>>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      var task =
        new FactionChangeTask(
          new List<FactionSelectInfoBL>
            {
              new FactionSelectInfoBL
                {
                  UserId = p.Id,
                  OldFaction = 0,
                  NewFaction = 1,
                  RChange = new ResourceTableBL {Gold = 100},
                  RTotal = new ResourceTableBL {Gold = 500},
                  Timestamp = DateTime.UtcNow
                }
            },
          mockplayerrepo.Object, mockfactionchangerepo.Object, mockresourcelogrepo.Object);
      task.Execute();

      Assert.AreEqual(Faction.Adornian, p.Faction);
      mockplayerrepo.Verify(m => m.GetById(1), Times.Once());
      mockplayerrepo.Verify(m => m.Update(p), Times.Once());
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.Player == p && r.Source == "factionchange" && r.GoldChange == -100)), Times.Once());
      mockfactionchangerepo.Verify(m => m.Add(It.Is<FactionChange>(f => f.Player == p && f.OldFaction == Faction.Dokt && f.NewFaction == Faction.Adornian)), Times.Once());
    }

    [Test]
    public void FreeFactionChangeTest()
    {
      var p = new Player {Id = 1, Faction = Faction.Dokt};
      var mockplayerrepo = new Mock<IPlayerRepository>();
      mockplayerrepo.Setup(m => m.GetById(1)).Returns(p);
      var mockfactionchangerepo = new Mock<IRepository<FactionChange>>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      var task =
        new FactionChangeTask(
          new List<FactionSelectInfoBL>
            {
              new FactionSelectInfoBL
                {
                  UserId = p.Id,
                  OldFaction = 0,
                  NewFaction = 1,
                  RChange = new ResourceTableBL(),
                  RTotal = new ResourceTableBL(),
                  Timestamp = DateTime.UtcNow
                }
            },
          mockplayerrepo.Object, mockfactionchangerepo.Object, mockresourcelogrepo.Object);
      task.Execute();

      Assert.AreEqual(Faction.Adornian, p.Faction);
      mockplayerrepo.Verify(m => m.GetById(1), Times.Once());
      mockplayerrepo.Verify(m => m.Update(p), Times.Once());
      mockresourcelogrepo.Verify(m => m.Add(It.IsAny<ResourceLog>()), Times.Never());
      mockfactionchangerepo.Verify(m => m.Add(It.Is<FactionChange>(f => f.Player == p && f.OldFaction == Faction.Dokt && f.NewFaction == Faction.Adornian)), Times.Once());
    }

    [Test]
    public void TaskRestartTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockfactionchangerepo = new Mock<IRepository<FactionChange>>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      mockplayerrepo.Setup(m => m.GetById(101)).Returns(new Player()).AtMostOnce();
      mockplayerrepo.Setup(m => m.GetById(102)).Throws(new Exception("TEST"));
      mockplayerrepo.Setup(m => m.GetById(103)).Returns(new Player()).AtMostOnce();

      var infos = new List<FactionSelectInfoBL>
                    {
                      new FactionSelectInfoBL {UserId = 101, RChange = new ResourceTableBL(), RTotal = new ResourceTableBL()},
                      new FactionSelectInfoBL {UserId = 102, RChange = new ResourceTableBL(), RTotal = new ResourceTableBL()},
                      new FactionSelectInfoBL {UserId = 103, RChange = new ResourceTableBL(), RTotal = new ResourceTableBL()}
                    };
      var task = new FactionChangeTask(infos, mockplayerrepo.Object, mockfactionchangerepo.Object, mockresourcelogrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockplayerrepo.Setup(m => m.GetById(102)).Returns(new Player());

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
    }

    [Test]
    public void FactionChangeAddFailed()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockfactionchangerepo = new Mock<IRepository<FactionChange>>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      mockplayerrepo.Setup(m => m.GetById(101)).Returns(new Player());
      mockfactionchangerepo.Setup(m => m.Add(It.IsAny<FactionChange>())).Throws<Exception>();

      var infos = new List<FactionSelectInfoBL> { new FactionSelectInfoBL {UserId = 101, RChange = new ResourceTableBL {Gold = 5}, RTotal = new ResourceTableBL()} };
      var task = new FactionChangeTask(infos, mockplayerrepo.Object, mockfactionchangerepo.Object, mockresourcelogrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mockfactionchangerepo.Setup(m => m.Add(It.IsAny<FactionChange>()));
      Assert.That(task.Execute());

      mockfactionchangerepo.VerifyAll();
      mockresourcelogrepo.Verify(m => m.Add(It.IsAny<ResourceLog>()), Times.Once());
    }
  }
}
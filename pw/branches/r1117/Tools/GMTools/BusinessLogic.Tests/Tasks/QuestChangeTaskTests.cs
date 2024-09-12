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
  public class QuestChangeTaskTests
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
      var mockquestrepo = new Mock<IRepository<Quest>>();
      var mockquestchangerepo = new Mock<IRepository<QuestChange>>();

      var now = DateTime.UtcNow;
      var p = new Player { Id = 101 };
      var q = new Quest { Id = 600 };

      mockplayerrepo.Setup(m => m.GetById(101)).Returns(p).AtMostOnce();
      mockquestrepo.Setup(m => m.GetById(600)).Returns(q).AtMostOnce();

      var infos = new List<QuestChangeInfoBL> { new QuestChangeInfoBL { Auid = 101, QuestId = 600, Reason = 2, Timestamp = now } };
      var task = new QuestChangeTask(infos, mockplayerrepo.Object, mockquestrepo.Object, mockquestchangerepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockquestrepo.VerifyAll();
      mockquestchangerepo.Verify(m => m.Add(It.Is<QuestChange>(qc => qc.Player == p && qc.Quest == q && qc.ChangeType == QuestChangeType.Complete && qc.Timestamp == now)));
    }

    [Test]
    public void TaskRestartTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockquestrepo = new Mock<IRepository<Quest>>();
      var mockquestchangerepo = new Mock<IRepository<QuestChange>>();

      mockplayerrepo.Setup(m => m.GetById(It.IsAny<long>()))
        .Returns((long id) => new Player { Id = id });
      mockquestrepo.Setup(m => m.GetById(600)).Returns(new Quest());

      mockquestchangerepo.Setup(m => m.Add(It.Is<QuestChange>(qc => qc.Player.Id == 101))).AtMostOnce();
      mockquestchangerepo.Setup(m => m.Add(It.Is<QuestChange>(qc => qc.Player.Id == 102))).Throws(new Exception("TEST"));
      mockquestchangerepo.Setup(m => m.Add(It.Is<QuestChange>(qc => qc.Player.Id == 103))).AtMostOnce();

      var infos = new List<QuestChangeInfoBL>
                    {
                      new QuestChangeInfoBL { Auid = 101, QuestId = 600, Reason = 1 },
                      new QuestChangeInfoBL { Auid = 102, QuestId = 600, Reason = 1 },
                      new QuestChangeInfoBL { Auid = 103, QuestId = 600, Reason = 1 }
                    };
      var task = new QuestChangeTask(infos, mockplayerrepo.Object, mockquestrepo.Object, mockquestchangerepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockquestchangerepo.Setup(m => m.Add(It.Is<QuestChange>(qc => qc.Player.Id == 102)));
      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockquestrepo.VerifyAll();
      mockquestchangerepo.Verify(m => m.Add(It.Is<QuestChange>(qc => qc.Player.Id == 101)), Times.Once());
      mockquestchangerepo.Verify(m => m.Add(It.Is<QuestChange>(qc => qc.Player.Id == 102)), Times.Exactly(2));
      mockquestchangerepo.Verify(m => m.Add(It.Is<QuestChange>(qc => qc.Player.Id == 103)), Times.Once());
    }
  }
}
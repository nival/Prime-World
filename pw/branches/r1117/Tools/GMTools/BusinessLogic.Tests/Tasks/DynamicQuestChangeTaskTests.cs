using System;
using System.Collections.Generic;
using System.IO;
using BusinessLogic.DBManagement;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;
using Moq;
using NUnit.Framework;
using log4net.Config;

namespace BusinessLogic.Tests.Tasks
{

  [TestFixture]
  public class DynamicQuestChangeTaskTests
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
      var mockdynamicquestchangerepo = new Mock<IRepository<DynamicQuestChange>>();

      var now = DateTime.UtcNow;
      var p = new Player { Id = 101 };

      mockplayerrepo.Setup(m => m.GetById(101)).Returns(p).AtMostOnce();

      var infos = new List<DynamicQuestChangeInfoBL> { new DynamicQuestChangeInfoBL { Auid = 101, QuestIndex = 803, QuestName = "testdquest", Reason = 1, Timestamp = now } };
      var task = new DynamicQuestChangeTask(infos, mockdynamicquestchangerepo.Object, mockplayerrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockdynamicquestchangerepo.Verify(m => m.Add(It.Is<DynamicQuestChange>(qc => qc.Player == p && qc.QuestIndex == 803 && qc.QuestName == "testdquest" && qc.ChangeType == QuestChangeType.Accept && qc.Timestamp == now)));
    }


  }

}
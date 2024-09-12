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
  public class SocialLogoutTaskTests
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
      var mocksocialsessionrepo = new Mock<ISocialSessionRepository>();

      var p = new Player { Id = 1, Faction = (Faction)1, Nickname = "testlogin" };
      var now = DateTime.Now;
      mockplayerrepo.Setup(m => m.GetById(1)).Returns(p);
      mocksocialsessionrepo.Setup(m => m.WriteLogout(p, "testserver", "testcluster", now));

      var infos = new List<LoginInfoBL> { new LoginInfoBL { UserId = 1, Cluster = "testcluster", Server = "testserver", Timestamp = now } };
      var task = new SocialLogoutTask(infos, mockplayerrepo.Object, mocksocialsessionrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mocksocialsessionrepo.VerifyAll();
    }

    [Test]
    public void TaskRestartTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mocksocialsessionrepo = new Mock<ISocialSessionRepository>();

      mockplayerrepo.Setup(m => m.GetById(101)).Returns(new Player()).AtMostOnce();
      mockplayerrepo.Setup(m => m.GetById(102)).Throws(new Exception("TEST"));
      mockplayerrepo.Setup(m => m.GetById(103)).Returns(new Player()).AtMostOnce();
      mocksocialsessionrepo.Setup(m => m.WriteLogout(It.IsAny<Player>(), null, null, It.IsAny<DateTime>()));

      var infos = new List<LoginInfoBL>
                    {
                      new LoginInfoBL { UserId = 101 },
                      new LoginInfoBL { UserId = 102 },
                      new LoginInfoBL { UserId = 103 }
                    };
      var task = new SocialLogoutTask(infos, mockplayerrepo.Object, mocksocialsessionrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockplayerrepo.Setup(m => m.GetById(102)).Returns(new Player());

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mocksocialsessionrepo.VerifyAll();

    }
  }
}
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
  public class SocialLoginTaskTests
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
      var mockguildrepo = new Mock<IGuildRepository>();

      var p = new Player { Id = 1, Faction = (Faction)1, Nickname = "testlogin"};
      var now = DateTime.Now;
      mockplayerrepo.Setup(m => m.CreateOrUpdate(1, "testlogin", null, (Faction)1, false, null, 0, false)).Returns(p);
      mocksocialsessionrepo.Setup(m => m.Add(It.Is<SocialSession>(s => s.Player == p && s.PlayerIp == "::1" && s.Cluster == "testcluster" && s.Server == "testserver" && s.StartTime == now)));

      var infos = new List<LoginInfoBL> {new LoginInfoBL {UserId = 1, Login = "testlogin", Cluster = "testcluster", Server = "testserver", Faction = 1, Ip = "::1", Timestamp = now}};
      var task = new SocialLoginTask(infos, mockplayerrepo.Object, mocksocialsessionrepo.Object, mockguildrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mocksocialsessionrepo.VerifyAll();
    }

    [Test]
    public void TaskRestartTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mocksocialsessionrepo = new Mock<ISocialSessionRepository>();
      var mockguildrepo = new Mock<IGuildRepository>();

      mockplayerrepo.Setup(m => m.CreateOrUpdate(101, null, null, It.IsAny<Faction>(), false, null, 0, false)).Returns(new Player()).AtMostOnce();
      mockplayerrepo.Setup(m => m.CreateOrUpdate(102, null, null, It.IsAny<Faction>(), false, null, 0, false)).Throws(new Exception("TEST"));
      mockplayerrepo.Setup(m => m.CreateOrUpdate(103, null, null, It.IsAny<Faction>(), false, null, 0, false)).Returns(new Player()).AtMostOnce();
      mocksocialsessionrepo.Setup(m => m.Add(It.IsAny<SocialSession>()));

      var infos = new List<LoginInfoBL>
                    {
                      new LoginInfoBL {UserId = 101},
                      new LoginInfoBL {UserId = 102},
                      new LoginInfoBL {UserId = 103}
                    };
      var task = new SocialLoginTask(infos, mockplayerrepo.Object, mocksocialsessionrepo.Object, mockguildrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockplayerrepo.Setup(m => m.CreateOrUpdate(102, null, null, It.IsAny<Faction>(), false, null, 0, false)).Returns(new Player());

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mocksocialsessionrepo.VerifyAll();
    }
  }
}
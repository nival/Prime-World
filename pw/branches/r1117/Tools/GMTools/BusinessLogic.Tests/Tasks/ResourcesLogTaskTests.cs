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
  public class ResourcesLogTaskTests
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
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      var now = DateTime.UtcNow;
      var p = new Player {Id = 101};

      mockplayerrepo.Setup(m => m.GetById(101)).Returns(p);

      var infos = new List<ResourcesChangeInfoBL>
                    {
                      new ResourcesChangeInfoBL
                        {
                          Auid = 101,
                          Source = "testsrc",
                          BuildingName = "testbld",
                          Gain = true,
                          RChange = new ResourceTableBL {Silver = 926},
                          RTotal = new ResourceTableBL {Silver = 101426},
                          Timestamp = now
                        }
                    };
      var task = new ResourcesLogTask(infos, mockplayerrepo.Object, mockresourcelogrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.Player == p && r.Source == "testsrc" && r.BuildingName == "testbld" && r.SilverChange == 926 && r.SilverTotal == 101426 && r.Timestamp == now)));
    }

    [Test]
    public void UpdateFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      mockplayerrepo.Setup(m => m.GetById(It.IsAny<long>())).Returns((long id) => new Player {Id = id});
      mockresourcelogrepo.Setup(m => m.Add(It.Is<ResourceLog>(r => r.Player.Id == 101))).AtMostOnce();
      mockresourcelogrepo.Setup(m => m.Add(It.Is<ResourceLog>(r => r.Player.Id == 102))).Throws(new Exception("TEST"));
      mockresourcelogrepo.Setup(m => m.Add(It.Is<ResourceLog>(r => r.Player.Id == 103))).AtMostOnce();

      var infos = new List<ResourcesChangeInfoBL>
                    {
                      new ResourcesChangeInfoBL { Auid = 101, RChange = new ResourceTableBL (), RTotal = new ResourceTableBL () },
                      new ResourcesChangeInfoBL { Auid = 102, RChange = new ResourceTableBL (), RTotal = new ResourceTableBL () },
                      new ResourcesChangeInfoBL { Auid = 103, RChange = new ResourceTableBL (), RTotal = new ResourceTableBL () }
                    };
      var task = new ResourcesLogTask(infos, mockplayerrepo.Object, mockresourcelogrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockresourcelogrepo.Setup(m => m.Add(It.Is<ResourceLog>(r => r.Player.Id == 102)));
      Assert.That(task.Execute());

      mockresourcelogrepo.VerifyAll();
    }
  }
}
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
  public class GMUserOperationTaskTests
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
      var mockclaimrepo = new Mock<IRepository<Claim>>();
      var mockgmuseroprepo = new Mock<IGMUserOperationRepository>();

      var now = DateTime.UtcNow;
      var p = new Player {Id = 101};
      var c = new Claim {Id = 88};
      var infos = new List<GMUserOperationInfoBL>
                    {
                      new GMUserOperationInfoBL
                        {
                          UserId = 101,
                          GMLogin = "testlogin",
                          Type = 2,
                          Minutes = 120,
                          Reason = "test reason",
                          Timestamp = now,
                          ClaimIds = new List<int> {88}
                        }
                    };

      mockplayerrepo.Setup(m => m.GetById(101)).Returns(p);
      mockclaimrepo.Setup(m => m.GetById(88)).Returns(c);
      mockgmuseroprepo.Setup(m => m.Add(It.Is<GMUserOperation>(g => g.Player.Id == 101 && g.GMLogin == "testlogin" && g.Reason == "test reason" &&
                                                                    g.Type == GMUserOperationType.Unban && g.Timestamp == now)))
                      .Callback((GMUserOperation g) => g.Id = 1);

      var task = new GMUserOperationTask(infos, mockgmuseroprepo.Object, mockplayerrepo.Object, mockclaimrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockgmuseroprepo.VerifyAll();
      mockclaimrepo.VerifyAll();
      mockclaimrepo.Verify(m => m.Update(c));
      Assert.IsNotNull(c.GMUserOperation);
      Assert.AreEqual(1, c.GMUserOperation.Id);
    }
  }
}
using System;
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
  public class GMOperationTests
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
      var mockgmoperationrepo = new Mock<IGMOperationRepository>();

      var now = DateTime.UtcNow;
      var p = new Player {Id = 1};

      var infos = new[]
                    {
                      new GMOperationInfoBL
                        {
                          UserId = 1,
                          Type = "PlayerEdit",
                          Data = "test data",
                          GMLogin = "gm",
                          Timestamp = now
                        }
                    };
      var task = new GMOperationTask(infos, mockplayerrepo.Object, mockgmoperationrepo.Object);
    }
  }
}
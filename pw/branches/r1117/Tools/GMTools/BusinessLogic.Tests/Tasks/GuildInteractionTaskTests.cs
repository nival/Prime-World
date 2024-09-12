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
  public class GuildInteractionTaskTests
  {

    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void SimpleTest()
    {
      var mockguildrepo = new Mock<IGuildRepository>();
      var mockguildsiegerepo = new Mock<IRepository<GuildSiege>>();
      var mockguildinteractionrepo = new Mock<IRepository<GuildInteraction>>();

      var g1 = new Guild { Id = 6001 };
      var g2 = new Guild { Id = 6002 };
      var gs = new GuildSiege { Id = 7001 };
      var infos = new List<GuildInteractionInfoBL>
                    {
                      new GuildInteractionInfoBL
                        {
                          GuildId = 6001,
                          TargetGuildId = 6002,
                          SiegeId = 7001,
                          Type = "Capture",
                          WaitingTime = 1234,
                          Timestamp = DateTime.Today
                        }
                    };

      mockguildrepo.Setup(m => m.CheckAndGetById(6001L)).Returns(g1);
      mockguildrepo.Setup(m => m.CheckAndGetById(6002L)).Returns(g2);
      mockguildsiegerepo.Setup(m => m.CheckAndGetById(7001L)).Returns(gs);

      var task = new GuildInteractionTask(infos, mockguildrepo.Object, mockguildsiegerepo.Object, mockguildinteractionrepo.Object);

      Assert.That(task.Execute());

      mockguildrepo.VerifyAll();
      mockguildsiegerepo.VerifyAll();
      mockguildinteractionrepo.Verify(m => m.Add(It.Is<GuildInteraction>(g => g.Guild == g1 && g.TargetGuild == g2 && g.GuildSiege == gs && g.Type == GuildInteractionType.Capture && g.WaitingTime == 1234 && g.Timestamp == DateTime.Today)));
    }
  }
}
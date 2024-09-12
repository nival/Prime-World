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
  public class GuildSiegeTaskTests
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
      var mockguildsiegeparticipantrepo = new Mock<IRepository<GuildSiegeParticipant>>();
      var mockguildpointsrepo = new Mock<IRepository<GuildPointsLog>>();

      var g1 = new Guild { Id = 6001 };
      var g2 = new Guild { Id = 6002 };
      var g3 = new Guild { Id = 6003 };

      var infos = new List<GuildSiegeInfoBL>
                    {
                      new GuildSiegeInfoBL
                        {
                          SiegeId = 8828374698200,
                          GuildId = 6001,
                          TargetGuildId = 6002,
                          TargetSuzerainId = 6003,
                          GuildRating = 12001,
                          TargetGuildRating = 12002,
                          TargetSuzerainRating = 12003,
                          GuildPointsChange = 77,
                          GuildPointsTotal = 7777,
                          StartTimestamp = DateTime.Today,
                          EndTimestamp = DateTime.Today.AddDays(1),
                          Participants = new List<GuildSiegeParticipantInfoBL>
                                           {
                                             new GuildSiegeParticipantInfoBL
                                               {
                                                 GuildId = 6002,
                                                 GuildRating = 11999,
                                                 GuildPointsChange = 66,
                                                 GuildPointsTotal = 6666,
                                                 StartTimestamp = DateTime.Today.AddHours(1),
                                                 EndTimestamp = DateTime.Today.AddDays(1),
                                                 SiegePoints = 1488
                                               }
                                           }
                        }
                    };

      mockguildrepo.Setup(m => m.GetOrCreateById(6001L)).Returns(g1);
      mockguildrepo.Setup(m => m.GetOrCreateById(6002L)).Returns(g2);
      mockguildrepo.Setup(m => m.GetOrCreateById(6003L)).Returns(g3);

      var task = new GuildSiegeTask(infos, mockguildrepo.Object, mockguildsiegerepo.Object, mockguildsiegeparticipantrepo.Object, mockguildpointsrepo.Object);
      Assert.That(task.Execute());

      mockguildrepo.VerifyAll();
      mockguildsiegerepo.Verify(
        m => m.Add(It.Is<GuildSiege>(gs => gs.Id == 8828374698200 && gs.Guild == g1 && gs.TargetGuild == g2 && gs.TargetSuzerainGuild == g3
                                           && gs.Rating == 12001 && gs.TargetRating == 12002 && gs.TargetSuzerainRating == 12003
                                           && gs.GuildPointsLog != null && gs.StartTime == DateTime.Today && gs.EndTime == DateTime.Today.AddDays(1))));

      mockguildsiegeparticipantrepo.Verify(
        m => m.Add(It.Is<GuildSiegeParticipant>(gsp => gsp.GuildSiege.Id == 8828374698200 && gsp.Guild == g2 && gsp.GuildPointsLog != null
          && gsp.StartTime == DateTime.Today.AddHours(1) && gsp.EndTime == DateTime.Today.AddDays(1) && gsp.SiegePoints == 1488)));

      mockguildpointsrepo.Verify(m => m.Add(It.Is<GuildPointsLog>(gpl => gpl.Type == GuildPointsLogType.GuildSiege && gpl.Player == null && gpl.Guild == g1 && gpl.GuildPointsChange == 77 && gpl.GuildPointsTotal == 7777)));
      mockguildpointsrepo.Verify(m => m.Add(It.Is<GuildPointsLog>(gpl => gpl.Type == GuildPointsLogType.GuildSiege && gpl.Player == null && gpl.Guild == g2 && gpl.GuildPointsChange == 66 && gpl.GuildPointsTotal == 6666)));
    }

  }

}
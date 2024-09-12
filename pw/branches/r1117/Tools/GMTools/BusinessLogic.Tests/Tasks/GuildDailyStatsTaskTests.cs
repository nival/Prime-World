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
  public class GuildDailyStatsTaskTests
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
      var mockdailystatsrepo = new Mock<IRepository<GuildDailyStats>>();

      var g1 = new Guild { Id = 6001 };

      var infos = new List<GuildDailyStatsInfoBL>
                    {
                      new GuildDailyStatsInfoBL
                        {
                          GuildId = 6001,
                          GuildRating = 9001,
                          GuildRatingToday = 1,
                          GuildPoints = 35900,
                          GuildRank = 2,
                          Vassals = new Dictionary<long, long> { { 1, 100 }, { 2, 200 } },
                          Suggested = new Dictionary<long, long> { { 5002, 22000 }, { 5003, 23000 } },
                          Timestamp = DateTime.Today
                        }
                    };

      mockguildrepo.Setup(m => m.CheckAndGetById(6001L)).Returns(g1);

      var task = new GuildDailyStatsTask(infos, mockguildrepo.Object, mockdailystatsrepo.Object);
      Assert.That(task.Execute());

      mockguildrepo.VerifyAll();
      mockdailystatsrepo.Verify(m => m.Add(It.Is<GuildDailyStats>(g => g.Guild == g1 && g.Rating == 9001 && g.GuildPointsToday == 1 && g.GuildPoints == 35900 && g.VassalsPoints == 300 && g.VassalsCount == 2 && g.Timestamp == DateTime.Today)));
    }

  }

}
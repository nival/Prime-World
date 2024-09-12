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
  public class GuildShopBuyTaskTests
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
      var mockguildrepo = new Mock<IGuildRepository>();
      var mockguildshopitemrepo = new Mock<IRepository<GuildShopItem>>();
      var mockguildshopbuyrepo = new Mock<IRepository<GuildShopBuy>>();
      var mockguildpointsrepo = new Mock<IRepository<GuildPointsLog>>();
      var resourcelogrepo = new Mock<IRepository<ResourceLog>>();

      var p = new Player { Id = 101 };
      var g = new Guild { Id = 6001 };
      var gsi = new GuildShopItem { Id = 654321 };

      var infos = new List<GuildShopBuyInfoBL>
                    {
                      new GuildShopBuyInfoBL
                        {
                          Auid = 101,
                          GuildId = 6001,
                          ShopItemId = 654321,
                          ShopLevel = 6,
                          GuildPointsChange = 77,
                          GuildPointsTotal = 7777,
                          PlayerPointsChange = 88,
                          PlayerPointsTotal = 8888,
                          HasSuzerain = true,
                          Timestamp = DateTime.Today
                        }
                    };

      mockplayerrepo.Setup(m => m.CheckAndGetById(101L)).Returns(p);
      mockguildrepo.Setup(m => m.CheckAndGetById(6001L)).Returns(g);
      mockguildshopitemrepo.Setup(m => m.CheckAndGetById(654321)).Returns(gsi);

      var task = new GuildShopBuyTask(infos, mockplayerrepo.Object, mockguildrepo.Object, mockguildshopitemrepo.Object, mockguildshopbuyrepo.Object, mockguildpointsrepo.Object, resourcelogrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockguildrepo.VerifyAll();
      mockguildshopitemrepo.VerifyAll();
      mockguildshopbuyrepo.Verify(m => m.Add(It.Is<GuildShopBuy>(gs => gs.Player == p && gs.Guild == g && gs.GuildShopItem == gsi && gs.GuildPointsLog != null && gs.HasSuzerain && gs.ShopLevel == 6 && gs.Timestamp == DateTime.Today)));
      mockguildpointsrepo.Verify(m => m.Add(It.Is<GuildPointsLog>(gpl => gpl.Type == GuildPointsLogType.GuildShopBuy && gpl.Player == p && gpl.Guild == g && gpl.GuildPointsChange == 77 && gpl.GuildPointsTotal == 7777 && gpl.PlayerPointsChange == 88 && gpl.PlayerPointsTotal == 8888)));
    }

  }

}
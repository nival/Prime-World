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
  public class GuildCreateTaskTests
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
      var mockguildmembershiprepo = new Mock<IGuildMembershipRepository>();
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      var now = DateTime.UtcNow;
      var p = new Player {Id = 100};
      var infos = new List<GuildInfoBL>
                    {
                      new GuildInfoBL
                        {
                          Auid = 100,
                          GuildId = 6000,
                          ShortName = "MTG",
                          FullName = "Magic Test Guild",
                          RChange = new ResourceTableBL {Silver = 150000},
                          RTotal = new ResourceTableBL {Silver = 500000},
                          Timestamp = now
                        }
                    };

      mockplayerrepo.Setup(m => m.GetById(100)).Returns(p);
      mockresourcelogrepo.Setup(m => m.Add(It.IsAny<ResourceLog>())).Callback((ResourceLog r) => r.Id = 3000);

      var task = new GuildCreateTask(infos, mockguildrepo.Object, mockguildmembershiprepo.Object, mockplayerrepo.Object, mockresourcelogrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayerrepo.Verify(m => m.Update(It.Is<Player>(pl => pl.Id == 100 && pl.Guild.Id == 6000)));
      mockguildrepo.Verify(m => m.Add(It.Is<Guild>(g => g.Id == 6000 && g.Creator == p && g.CreationDate == now && g.ShortName == "MTG" &&
                                                   g.FullName == "Magic Test Guild" && g.ResourceLog.Id == 3000 && g.MembersCount == 1)));
      mockguildmembershiprepo.Verify(m => m.Add(It.Is<GuildMembership>(gm => gm.Player == p && gm.Guild.Id == 6000 && gm.JoinDate == now)));
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.Player == p && r.Gain == false && r.SilverChange == -150000 && r.SilverTotal == 500000 && r.Source == GuildCreateTask.RLOG_SOURCE)));
    }

    [Test]
    public void TaskRestartGuildAddFailingTest()
    {
      var mockguildrepo = new Mock<IGuildRepository>();
      var mockguildmembershiprepo = new Mock<IGuildMembershipRepository>();
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      mockplayerrepo.Setup(m => m.GetById(It.IsAny<long>())).Returns((long id) => new Player {Id = id});
      mockresourcelogrepo.Setup(m => m.Add(It.IsAny<ResourceLog>())).Callback((ResourceLog rl) => rl.Id = rl.GoldTotal);
      mockguildrepo.Setup(m => m.Add(It.Is<Guild>(g => g.Id == 6002))).Throws(new Exception("TEST"));

      var infos = new List<GuildInfoBL>
                    {
                      new GuildInfoBL { Auid = 101, GuildId = 6001, RChange = new ResourceTableBL {Silver = 1}, RTotal = new ResourceTableBL { Gold = 3001 } },
                      new GuildInfoBL { Auid = 102, GuildId = 6002, RChange = new ResourceTableBL {Silver = 2}, RTotal = new ResourceTableBL { Gold = 3002 } },
                      new GuildInfoBL { Auid = 103, GuildId = 6003, RChange = new ResourceTableBL {Silver = 3}, RTotal = new ResourceTableBL { Gold = 3003 } }
                    };

      var task = new GuildCreateTask(infos, mockguildrepo.Object, mockguildmembershiprepo.Object, mockplayerrepo.Object, mockresourcelogrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);
      Assert.AreEqual("TEST", task.LastErrorMessage);

      mockguildrepo.Setup(m => m.Add(It.Is<Guild>(g => g.Id == 6002)));

      Assert.That(task.Execute());

      mockplayerrepo.Verify(m => m.Update(It.Is<Player>(p => p.Id == 101 && p.Guild.Id == 6001)), Times.Once());
      mockplayerrepo.Verify(m => m.Update(It.Is<Player>(p => p.Id == 102 && p.Guild.Id == 6002)), Times.Once());
      mockplayerrepo.Verify(m => m.Update(It.Is<Player>(p => p.Id == 103 && p.Guild.Id == 6003)), Times.Once());
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.Player.Id == 101 && r.SilverChange == -1)), Times.Once());
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.Player.Id == 102 && r.SilverChange == -2)), Times.Once());
      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.Player.Id == 103 && r.SilverChange == -3)), Times.Once());
      mockguildrepo.Verify(m => m.Add(It.Is<Guild>(g => g.Id == 6001)), Times.Once());
      mockguildrepo.Verify(m => m.Add(It.Is<Guild>(g => g.Id == 6002)), Times.Exactly(2));
      mockguildrepo.Verify(m => m.Add(It.Is<Guild>(g => g.Id == 6003)), Times.Once());
      mockguildmembershiprepo.Verify(m => m.Add(It.Is<GuildMembership>(gm => gm.Guild.Id == 6001)), Times.Once());
      mockguildmembershiprepo.Verify(m => m.Add(It.Is<GuildMembership>(gm => gm.Guild.Id == 6002)), Times.Once());
      mockguildmembershiprepo.Verify(m => m.Add(It.Is<GuildMembership>(gm => gm.Guild.Id == 6003)), Times.Once());
    }
  }
}
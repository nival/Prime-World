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
  public class SessionAwardTaskTests
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
      var mocktalentlogrepo = new Mock<ITalentLogRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();
      var mockguildpointsrepo = new Mock<IRepository<GuildPointsLog>>();
      var mockleaverpointsrepo = new Mock<IRepository<LeaverPointsLog>>();

      var g = new Guild();
      var p = new Player {Id = 1, Guild = g};

      mockplayerrepo.Setup(m => m.GetById(1)).Returns(p);
      mockplayerrepo.Setup(m => m.CheckAndGetById(1L)).Returns(p);

      var info = new SessionAwardsInfoBL
                   {
                     Auid = 1,
                     HeroId = 2,
                     SessionPersistentId = 100500,
                     RChange = new ResourceTableBL { Gold = 11, Silver = 12, Perl = 13, RedPerl = 14, Population = 15, Resource1 = 16, Resource2 = 17, Resource3 = 18, Shard = 20 },
                     RTotal = new ResourceTableBL { Gold = 111, Silver = 112, Perl = 113, RedPerl = 114, Population = 115, Resource1 = 116, Resource2 = 117, Resource3 = 118, Shard = 119 },
                     Nick = "testnick",
                     Timestamp = DateTime.Today,
                     Talents = new List<SessionAwardsInfoBL.TalentInfoBL>
                                 {
                                   new SessionAwardsInfoBL.TalentInfoBL {Id = 12345, InstanceId = 1234512345},
                                   new SessionAwardsInfoBL.TalentInfoBL {Id = 23456, InstanceId = 2345623456}
                                 },
                     GuildPointsChange = 77,
                     GuildPointsTotal = 7777,
                     PlayerPointsChange = 88,
                     PlayerPointsTotal = 8888,
                     LeaverPointsChange = new LeaverPointsChangeInfoBL
                                          {
                                            Auid = 1,
                                            IsBadBehaviour = false,
                                            IsLeaver = true,
                                            IsLeaverChanged = false,
                                            LeaverPointsChange = 9090,
                                            LeaverPointsTotal = 91919,
                                            PersistentId = 100500,
                                            Timestamp = DateTime.Today,
                                            Type = "test"
                                          },
                   };
      var task = new SessionAwardsTask(new List<SessionAwardsInfoBL> {info},
                                       mockplayerrepo.Object, mocktalentlogrepo.Object, mockresourcelogrepo.Object, mockguildpointsrepo.Object, mockleaverpointsrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.Verify(m => m.Update(p), Times.Never());
      mockresourcelogrepo.Verify(m => m.Add(It.IsAny<ResourceLog>()), Times.Once());
      mocktalentlogrepo.Verify(m => m.Create(SessionAwardsTask.TLOG_SOURCE, null, 1, 12345, 1234512345, null, 100500, DateTime.Today), Times.Once());
      mockguildpointsrepo.Verify(m => m.Add(It.Is<GuildPointsLog>(gpl => gpl.Type == GuildPointsLogType.Session && gpl.PersistentId == 100500 && gpl.Player == p && gpl.Guild == g && gpl.GuildPointsChange == 77 && gpl.GuildPointsTotal == 7777 && gpl.PlayerPointsChange == 88 && gpl.PlayerPointsTotal == 8888)));
      mockleaverpointsrepo.Verify(m => m.Add(It.Is<LeaverPointsLog>(lpl => lpl.IsLeaver && !lpl.IsLeaverChanged && !lpl.IsBadBehaviour && lpl.LeaverPointsChange == 9090 && lpl.LeaverPointsTotal == 91919 && lpl.Player == p && lpl.PersistentId == 100500 && lpl.Type == "test")));
    }

    [Test]
    public void ResourceLogAddFailingTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mocktalentlogrepo = new Mock<ITalentLogRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();
      var mockguildpointsrepo = new Mock<IRepository<GuildPointsLog>>();
      var mockleaverpointsrepo = new Mock<IRepository<LeaverPointsLog>>();

      var p = new Player { Id = 1 };

      mockplayerrepo.Setup(m => m.GetById(It.IsAny<long>())).Returns(p);
      mockresourcelogrepo.Setup(m => m.Add(It.Is<ResourceLog>(r => r.GoldChange == 12))).Throws<Exception>();

      var infos = new List<SessionAwardsInfoBL>
                    {
                      new SessionAwardsInfoBL {Auid = 1, RChange = new ResourceTableBL {Gold = 11},RTotal = new ResourceTableBL {Gold = 111},Talents = null, LeaverPointsChange = new LeaverPointsChangeInfoBL()},
                      new SessionAwardsInfoBL {Auid = 1, RChange = new ResourceTableBL {Gold = 12},RTotal = new ResourceTableBL {Gold = 111},Talents = null, LeaverPointsChange = new LeaverPointsChangeInfoBL()},
                      new SessionAwardsInfoBL {Auid = 1, RChange = new ResourceTableBL {Gold = 13},RTotal = new ResourceTableBL {Gold = 111},Talents = null, LeaverPointsChange = new LeaverPointsChangeInfoBL()}
                    };
      var task = new SessionAwardsTask(infos, mockplayerrepo.Object, mocktalentlogrepo.Object, mockresourcelogrepo.Object, mockguildpointsrepo.Object, mockleaverpointsrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mockresourcelogrepo.Setup(m => m.Add(It.Is<ResourceLog>(r => r.GoldChange == 12)));
      Assert.That(task.Execute());

      mockresourcelogrepo.VerifyAll();
    }

    [Test]
    public void TalentLogCreateTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mocktalentlogrepo = new Mock<ITalentLogRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();
      var mockguildpointsrepo = new Mock<IRepository<GuildPointsLog>>();
      var mockleaverpointsrepo = new Mock<IRepository<LeaverPointsLog>>();

      var p = new Player { Id = 1 };

      mockplayerrepo.Setup(m => m.GetById(It.IsAny<long>())).Returns(p);
      mocktalentlogrepo.Setup(m => m.Create(SessionAwardsTask.TLOG_SOURCE, null, 1, 23456, 2345623456, null, 100500, DateTime.Today)).Throws<Exception>();

      var infos = new List<SessionAwardsInfoBL>
                  {
                    new SessionAwardsInfoBL
                    {
                      Auid = 1,
                      SessionPersistentId = 100500,
                      Timestamp = DateTime.Today,
                      Talents = new List<SessionAwardsInfoBL.TalentInfoBL>
                                {
                                  new SessionAwardsInfoBL.TalentInfoBL { Id = 12345, InstanceId = 1234512345 },
                                  new SessionAwardsInfoBL.TalentInfoBL { Id = 23456, InstanceId = 2345623456 },
                                  new SessionAwardsInfoBL.TalentInfoBL { Id = 34567, InstanceId = 3456734567 }
                                },
                      LeaverPointsChange = new LeaverPointsChangeInfoBL()
                    }
                  };
      var task = new SessionAwardsTask(infos, mockplayerrepo.Object, mocktalentlogrepo.Object, mockresourcelogrepo.Object, mockguildpointsrepo.Object, mockleaverpointsrepo.Object);

      Assert.IsFalse(task.Execute());
      Assert.AreEqual(1, task.ErrorCount);

      mocktalentlogrepo.Setup(m => m.Create(SessionAwardsTask.TLOG_SOURCE, null, 1, 23456, 2345623456, null, 100500, DateTime.Today));
      Assert.That(task.Execute());

      mockresourcelogrepo.VerifyAll();
      mocktalentlogrepo.Verify(m => m.Create(SessionAwardsTask.TLOG_SOURCE, null, 1, 12345, 1234512345, null, 100500, DateTime.Today), Times.Once());
      mocktalentlogrepo.Verify(m => m.Create(SessionAwardsTask.TLOG_SOURCE, null, 1, 34567, 3456734567, null, 100500, DateTime.Today), Times.Once());
      mocktalentlogrepo.Verify(m => m.Create(SessionAwardsTask.TLOG_SOURCE, null, 1, 23456, 2345623456, null, 100500, DateTime.Today), Times.Exactly(2));
    }
  }
}
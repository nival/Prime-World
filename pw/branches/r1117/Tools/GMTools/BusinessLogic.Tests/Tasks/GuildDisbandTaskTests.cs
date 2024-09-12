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
  public class GuildDisbandTaskTests
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

      var now = DateTime.UtcNow;
      var p = new Player { Id = 100 };
      var guild = new Guild { Id = 6000, ShortName = "MTG", FullName = "Magic Test Guild", DisbandingDate = null };
      var gmembership = new GuildMembership { Player = p, Guild = guild, Kicked = null };
      var infos = new List<GuildCoreInfoBL>
                    {
                      new GuildCoreInfoBL
                        {
                          Auid = 100,
                          GuildId = 6000,
                          Timestamp = now
                        }
                    };

      mockplayerrepo.Setup(m => m.GetById(100L)).Returns(p);
      mockguildrepo.Setup(m => m.GetById(6000L)).Returns(guild);
      mockguildmembershiprepo.Setup(m => m.GetByParams(p, guild)).Returns(gmembership);

      var task = new GuildDisbandTask(infos, mockguildrepo.Object, mockguildmembershiprepo.Object, mockplayerrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayerrepo.Verify(m => m.Update(It.Is<Player>(pl => pl.Id == 100 && pl.Guild == null)));
      mockguildrepo.VerifyAll();
      mockguildrepo.Verify(m => m.Update(It.Is<Guild>(gl => gl.Id == 6000L && gl.DisbandingDate == now)));
      mockguildmembershiprepo.Verify(m => m.Update(It.Is<GuildMembership>(gm => gm.Player == p && gm.Guild == guild && gm.LeaveDate == now && gm.Kicked == false)));
    }
  }
}
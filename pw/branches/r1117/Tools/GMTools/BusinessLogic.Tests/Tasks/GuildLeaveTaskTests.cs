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
  public class GuildLeaveTaskTests
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
      var guild = new Guild { Id = 6000 };
      var player = new Player { Id = 100, Guild = guild };
      var gmembership = new GuildMembership { Player = player, Guild = guild, Kicked = null };
      var infos = new List<GuildLeaveInfoBL>
                    {
                      new GuildLeaveInfoBL
                        {
                          Auid = 100,
                          Members = 21,
                          GuildId = 6000,
                          Kicked = true,
                          Timestamp = now
                        }
                    };

      mockplayerrepo.Setup(m => m.CheckAndGetById(100L)).Returns(player);
      mockguildrepo.Setup(m => m.GetById(6000L)).Returns(guild);
      mockguildmembershiprepo.Setup(m => m.GetByParams(player, guild)).Returns(gmembership);

      var task = new GuildLeaveTask(infos, mockguildrepo.Object, mockguildmembershiprepo.Object, mockplayerrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayerrepo.Verify(m => m.Update(player));
      Assert.IsNull(player.Guild);

      mockguildrepo.VerifyAll();
      mockguildmembershiprepo.Verify(m => m.Update(It.Is<GuildMembership>(gm => gm.Player == player && gm.Guild == guild && gm.LeaveDate == now && gm.Kicked == true)));
    }
    
    [Test]
    public void GuildNotExistsTest()
    {
      var mockguildrepo = new Mock<IGuildRepository>();
      var mockguildmembershiprepo = new Mock<IGuildMembershipRepository>();
      var mockplayerrepo = new Mock<IPlayerRepository>();

      var now = DateTime.UtcNow;
      var guild = new Guild { Id = 6000 };
      var p = new Player { Id = 100, Guild = guild };
      var gmembership = new GuildMembership { Player = p, Guild = guild, Kicked = null };
      var infos = new List<GuildLeaveInfoBL>
                    {
                      new GuildLeaveInfoBL
                        {
                          Auid = 100,
                          Members = 20,
                          GuildId = 6000,
                          Kicked = true,
                          Timestamp = now
                        }
                    };

      mockplayerrepo.Setup(m => m.CheckAndGetById(100L)).Returns(p);
      mockguildrepo.Setup(m => m.GetById(6000L)).Returns((Guild)null);

      var task = new GuildLeaveTask(infos, mockguildrepo.Object, mockguildmembershiprepo.Object, mockplayerrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayerrepo.Verify(m => m.Update(It.IsAny<Player>()), Times.Never());
      mockguildrepo.VerifyAll();
      mockguildrepo.Verify(m => m.Add(It.IsAny<Guild>()), Times.Never());
      mockguildmembershiprepo.Verify(m => m.Update(It.IsAny<GuildMembership>()), Times.Never());
    } 
  }
}
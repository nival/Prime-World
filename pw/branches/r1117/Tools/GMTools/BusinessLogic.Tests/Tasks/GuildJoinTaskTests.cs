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
  public class GuildJoinTaskTests
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
      var player = new Player { Id = 100 };
      var guild = new Guild { Id = 6000, MembersCount = 19, ShortName = "MTG", FullName = "Magic Test Guild" };
      var infos = new List<GuildCoreInfoBL>
                    {
                      new GuildCoreInfoBL
                        {
                          Auid = 100,
                          Members = 20,
                          GuildId = 6000,
                          Timestamp = now
                        }
                    };

      mockplayerrepo.Setup(m => m.CheckAndGetById(100L)).Returns(player);
      mockguildrepo.Setup(m => m.GetById(6000L)).Returns(guild);

      var task = new GuildJoinTask(infos, mockguildrepo.Object, mockguildmembershiprepo.Object, mockplayerrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      //mockplayerrepo.Verify(m => m.Update(It.Is<Player>(pl => pl.Id == 100 && pl.Guild == guild)));
      mockplayerrepo.Verify(m => m.Update(player));
      Assert.AreEqual(guild, player.Guild);

      mockguildrepo.VerifyAll();
      mockguildrepo.Verify(m => m.Update(guild));
      Assert.AreEqual(20, guild.MembersCount);

      mockguildmembershiprepo.Verify(m => m.Add(It.Is<GuildMembership>(gm => gm.Player == player && gm.Guild.Id == 6000 && gm.JoinDate == now)));
    }

    [Test]
    public void GuildNotExistsTest()
    {
      var mockguildrepo = new Mock<IGuildRepository>();
      var mockguildmembershiprepo = new Mock<IGuildMembershipRepository>();
      var mockplayerrepo = new Mock<IPlayerRepository>();

      var player = new Player { Id = 100 };
      var infos = new List<GuildCoreInfoBL>
                    {
                      new GuildCoreInfoBL
                        {
                          Auid = 100,
                          Members = 20,
                          GuildId = 6000,
                          Timestamp = DateTime.Today
                        }
                    };

      mockplayerrepo.Setup(m => m.CheckAndGetById(100L)).Returns(player);
      mockguildrepo.Setup(m => m.GetById(6000L)).Returns((Guild)null);

      var task = new GuildJoinTask(infos, mockguildrepo.Object, mockguildmembershiprepo.Object, mockplayerrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayerrepo.Verify(m => m.Update(player));
      Assert.IsNotNull(player.Guild);
      Assert.AreEqual(6000, player.Guild.Id);

      mockguildrepo.VerifyAll();
      mockguildrepo.Verify(m => m.Add(It.Is<Guild>(g => g.Id == 6000 && g.MembersCount == 20)));

      mockguildmembershiprepo.Verify(m => m.Add(It.Is<GuildMembership>(gm => gm.Player == player && gm.Guild.Id == 6000 && gm.JoinDate == DateTime.Today)));
    }
  }
}
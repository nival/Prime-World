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
  public class GuildRenameTaskTests
  {
    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void RenameExistingGuildTest()
    {
      var mockguildrepo = new Mock<IGuildRepository>();
      var mockguildmembershiprepo = new Mock<IGuildMembershipRepository>();
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      var now = DateTime.UtcNow;
      var player = new Player { Id = 100 };
      var guild = new Guild {Id = 6000, ShortName = "MTG", FullName = "Magic Test Guild"};
      var guildmembership = new GuildMembership { Guild = guild, Player = player };
      var infos = new List<GuildInfoBL>
                    {
                      new GuildInfoBL
                        {
                          Auid = 100,
                          GuildId = 6000,
                          ShortName = "NGG",
                          FullName = "New Generation Guild",
                          RChange = new ResourceTableBL {Gold = 499},
                          RTotal = new ResourceTableBL {Gold = 1},
                          Timestamp = now
                        }
                    };

      mockguildrepo.Setup(m => m.GetOrCreateById(6000L)).Returns(guild);
      mockguildrepo.Setup(m => m.Update(It.IsAny<Guild>()));
      mockplayerrepo.Setup(m => m.CheckAndGetById(100L)).Returns(player);
      mockguildmembershiprepo.Setup(m => m.GetByParams(player, guild)).Returns(guildmembership);
      mockresourcelogrepo.Setup(m => m.Add(It.IsAny<ResourceLog>())).Callback((ResourceLog r) => r.Id = 3000);

      var task = new GuildRenameTask(infos, mockguildrepo.Object, mockguildmembershiprepo.Object, mockplayerrepo.Object, mockresourcelogrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();

      mockguildrepo.Verify(m => m.Update(guild));
      Assert.AreEqual("NGG", guild.ShortName);
      Assert.AreEqual("New Generation Guild", guild.FullName);

      mockguildmembershiprepo.VerifyAll();

      mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.GoldChange == -499 && r.GoldTotal == 1 && r.Source == GuildRenameTask.RLOG_SOURCE)));
    }

    [Test]
    public void RenameNotExistingGuildTest()
    {
      var mockguildrepo = new Mock<IGuildRepository>();
      var mockguildmembershiprepo = new Mock<IGuildMembershipRepository>();
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mockresourcelogrepo = new Mock<IResourceLogRepository>();

      var now = DateTime.UtcNow;
      var player = new Player { Id = 100 };
      var guild = new Guild { Id = 6000 };

      var infos = new List<GuildInfoBL>
                    {
                      new GuildInfoBL
                        {
                          Auid = 100,
                          GuildId = 6000,
                          ShortName = "NGG",
                          FullName = "New Generation Guild",
                          RChange = new ResourceTableBL {Gold = 499},
                          RTotal = new ResourceTableBL {Gold = 1},
                          Timestamp = now
                        }
                    };

      mockguildrepo.Setup(m => m.GetOrCreateById(6000L)).Returns(guild);
      mockplayerrepo.Setup(m => m.CheckAndGetById(100L)).Returns(player);
      mockguildmembershiprepo.Setup(m => m.GetByParams(player, guild)).Returns((GuildMembership)null);
      mockresourcelogrepo.Setup(m => m.Add(It.IsAny<ResourceLog>())).Callback((ResourceLog r) => r.Id = 3000);

      var task = new GuildRenameTask(infos, mockguildrepo.Object, mockguildmembershiprepo.Object, mockplayerrepo.Object, mockresourcelogrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockplayerrepo.Verify(m => m.Update(player));
      Assert.AreEqual(guild, player.Guild);
      
      mockguildrepo.Verify(m => m.Update(guild));
      Assert.AreEqual("NGG", guild.ShortName);
      Assert.AreEqual("New Generation Guild", guild.FullName); mockresourcelogrepo.Verify(m => m.Add(It.Is<ResourceLog>(r => r.GoldChange == -499 && r.GoldTotal == 1 && r.Source == GuildRenameTask.RLOG_SOURCE)));

      mockguildmembershiprepo.VerifyAll();
      mockguildmembershiprepo.Verify(m => m.Add(It.Is<GuildMembership>(gm => gm.Player == player && gm.Guild == guild && gm.JoinDate == now)));
    }
  }
}
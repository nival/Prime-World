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
  public class AfterPartyTaskTests
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
      var mockafterpartyrepo = new Mock<IRepository<AfterParty>>();
      var mockafterpartymemberrepo = new Mock<IRepository<AfterPartyMember>>();

      var p1 = new Player();
      var p2 = new Player();

      var infos = new List<AfterPartyInfoBL>
                  {
                    new AfterPartyInfoBL
                    {
                      MMStarted = true,
                      Timestamp = DateTime.Today,
                      Members = new List<AfterPartyMemberInfoBL>
                                {
                                  new AfterPartyMemberInfoBL
                                  {
                                    Auid = 101,
                                    SessionPersistentId = 0,
                                    Kicked = true,
                                    Leaved = false
                                  },
                                  new AfterPartyMemberInfoBL
                                  {
                                    Auid = 102,
                                    SessionPersistentId = 100500,
                                    Kicked = false,
                                    Leaved = true
                                  }
                                }
                    }
                  };

      mockplayerrepo.Setup(m => m.CheckAndGetById(101L)).Returns(p1);
      mockplayerrepo.Setup(m => m.CheckAndGetById(102L)).Returns(p2);

      var task = new AfterPartyTask(infos, mockplayerrepo.Object, mockafterpartyrepo.Object, mockafterpartymemberrepo.Object);

      Assert.That(task.Execute());

      mockplayerrepo.VerifyAll();
      mockafterpartyrepo.Verify(m => m.Add(It.Is<AfterParty>(a => a.MMStarted && a.Timestamp == DateTime.Today && a.PersistentId == 100500)));
      mockafterpartymemberrepo.Verify(m => m.Add(It.Is<AfterPartyMember>(a => a.Player == p1 && a.AfterParty != null && a.PersistentId == null && a.Kicked && !a.Leaved && a.Timestamp == DateTime.Today)));
      mockafterpartymemberrepo.Verify(m => m.Add(It.Is<AfterPartyMember>(a => a.Player == p2 && a.AfterParty != null && a.PersistentId == 100500 && !a.Kicked && a.Leaved && a.Timestamp == DateTime.Today)));
    }

  }

}
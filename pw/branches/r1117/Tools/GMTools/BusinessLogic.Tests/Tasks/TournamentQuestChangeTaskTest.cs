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
  public class TournamentQuestChangeTaskTests
  {

    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure( new FileInfo( "log4net.config" ) );
    }


    [Test]
    public void SimpleTest()
    {
      var mockplayerrepo = new Mock<IPlayerRepository>();
      var mocktournamentquestchangerepo = new Mock<IRepository<TournamentQuestChange>>();

      var now = DateTime.UtcNow;
      var p = new Player { Id = 101 };

      mockplayerrepo.Setup( m => m.GetById( 101 ) ).Returns( p ).AtMostOnce();

      var infos = new List<TournamentQuestChangeInfoBL> { new TournamentQuestChangeInfoBL { Auid = 101, QuestIndex = 803, QuestName = "testdquest", Reason = 1, Timestamp = now } };
      var task = new TournamentQuestChangeTask( infos, mocktournamentquestchangerepo.Object, mockplayerrepo.Object );

      Assert.That( task.Execute() );

      mockplayerrepo.VerifyAll();
      mocktournamentquestchangerepo.Verify( m => m.Add( It.Is<TournamentQuestChange>( qc => qc.Player == p && qc.QuestIndex == 803 && qc.QuestName == "testdquest" && qc.CompleteType == TournamentQuestResult.Win && qc.Timestamp == now ) ) );
    }


  }

}
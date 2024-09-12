using System.IO;
using BusinessLogic.DBManagement;
using DAL.Entities;
using DAL.Repositories;
using Moq;
using NUnit.Framework;
using log4net.Config;

namespace BusinessLogic.Tests.Tasks
{
  [TestFixture]
  public class SessionRelayInfoTaskTests
  {
    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void SimpleTest()
    {
      var mockgamesessionrepo = new Mock<IGameSessionRepository>();
      var mocksessiontoplayerrepo = new Mock<ISessionToPlayerRepository>();

      var gs = new GameSession {Id = 2000, PersistentId = 123456};
      var pc = new PlayerCharacter {Id = 3000, Player = new Player {Id = 100}};
      var stp = new SessionToPlayer {Id = 3000, GameSession = gs, PlayerCharacter = pc};

      mockgamesessionrepo.Setup(m => m.GetByPersistentId(123456)).Returns(gs);
      mocksessiontoplayerrepo.Setup(m => m.SelectByGameSession(gs))
                             .Returns(new[]
                                        {
                                          new SessionToPlayer {GameSession = new GameSession(), PlayerCharacter = new PlayerCharacter {Player = new Player {Id = 101}}},
                                          stp
                                        });

      var task = new SessionRelayInfoTask(123456, 100, "127.0.0.1:8080",
                                          mockgamesessionrepo.Object, mocksessiontoplayerrepo.Object);

      Assert.That(task.Execute());

      mockgamesessionrepo.VerifyAll();
      mocksessiontoplayerrepo.VerifyAll();
      mocksessiontoplayerrepo.Verify(m => m.Update(It.Is<SessionToPlayer>(s => s.Id == 3000 && s.RelayAddress == "127.0.0.1:8080")));
    }
  }
}
using System;
using System.IO;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using log4net.Config;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class GMUserOperationTests
  {
    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
      DatabaseHelper.Init();
    }

    private static GMUserOperation CreateNewGMUserOperation()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = Player.DefaultLocale};
      using (var repo = new PlayerRepository())
        repo.Add(ref p);
      return new GMUserOperation
               {
                 Player = p,
                 GMLogin = "testlogin",
                 Type = GMUserOperationType.Unban,
                 Minutes = 120,
                 Reason = "test reason",
                 Timestamp = DateTime.Today,
               };
    }

    [Test]
    public void AddGMUserOperationTest()
    {
      var go = CreateNewGMUserOperation();
      using (var repo = new Repository<GMUserOperation>())
        repo.Add(go);

      using (var repo = new Repository<GMUserOperation>())
      {
        var go2 = repo.GetById(go.Id);
        Assert.IsNotNull(go2);
        Assert.AreNotSame(go2, go);
        Assert.AreEqual(go2.Player, go.Player);
        Assert.AreEqual(go2.GMLogin, go.GMLogin);
        Assert.AreEqual(go2.Type, go.Type);
        Assert.AreEqual(go2.Minutes, go.Minutes);
        Assert.AreEqual(go2.Reason, go.Reason);
        Assert.AreEqual(go2.Timestamp, go.Timestamp);
      }
    }
  }
}
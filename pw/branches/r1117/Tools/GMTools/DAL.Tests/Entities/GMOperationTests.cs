using System;
using System.IO;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using log4net.Config;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class GMOperationTests
  {
    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
      DatabaseHelper.Init();
    }

    private static GMOperation CreateNewGMOperation()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = Player.DefaultLocale};
      using (var repo = new PlayerRepository())
        repo.Add(ref p);
      return new GMOperation
               {
                 Player = p,
                 GMLogin = "testlogin",
                 Type = GMOperationType.PlayerEdit,
                 Data = "test data example",
                 Timestamp = DateTime.Today
               };
    }

    [Test]
    public void AddGMOperationTest()
    {
      var go = CreateNewGMOperation();
      using (var repo = new Repository<GMOperation>())
        repo.Add(go);

      using (var repo = new Repository<GMOperation>())
      {
        var go2 = repo.GetById(go.Id);
        Assert.IsNotNull(go2);
        Assert.AreNotSame(go2, go);
        Assert.AreEqual(go2.Player, go.Player);
        Assert.AreEqual(go2.GMLogin, go.GMLogin);
        Assert.AreEqual(go2.Type, go.Type);
        Assert.AreEqual(go2.Data, go.Data);
        Assert.AreEqual(go2.Timestamp, go.Timestamp);
      }
    }
  }
}
using System.Collections.Generic;
using System.IO;
using log4net.Config;
using NUnit.Framework;

namespace KontagentLib.Tests
{
  [TestFixture]
  public class KontagentTaskCreatorTests
  {
    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void CreateLauncherStartTest()
    {
      var creator = new KontagentTaskCreator();
      var task = (LauncherStartTask)creator.CreateLauncherStart(123, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "100.500.ap1.ap2");
      Assert.AreEqual(123, task.Auid);
      Assert.AreEqual("fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", task.HostId);
      Assert.AreEqual("100.500.ap1.ap2", task.Version);
    }

    [Test]
    public void CreateLauncherDStartTest()
    {
      var creator = new KontagentTaskCreator();
      var task = (LauncherDStartTask)creator.CreateLauncherDStart(123, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "PvP_XXtoXX.solidpkg", "66");
      Assert.AreEqual(123, task.Auid);
      Assert.AreEqual("fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", task.HostId);
      Assert.AreEqual("PvP_XXtoXX.solidpkg", task.Package);
      Assert.AreEqual("66", task.Version);
    }

    [Test]
    public void CreateLauncherDEndTest()
    {
      var creator = new KontagentTaskCreator();
      var task = (LauncherDEndTask)creator.CreateLauncherDEnd(123, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "PvP_XXtoXX.solidpkg", "66", 1);
      Assert.AreEqual(123, task.Auid);
      Assert.AreEqual("fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", task.HostId);
      Assert.AreEqual("PvP_XXtoXX.solidpkg", task.Package);
      Assert.AreEqual("66", task.Version);
      Assert.AreEqual(1, task.Status);
    }

    [Test]
    public void CreateLauncherEventsTest()
    {
      var creator = new KontagentTaskCreator();
      var task = (LauncherEventsTask)creator.CreateLauncherEvents(123, "mooid", 2096);
      Assert.AreEqual(123, task.Auid);
      Assert.AreEqual("mooid", task.Muid);
      Assert.AreEqual(2096, task.Events);
    }

    [Test]
    public void CreateCastleLoginTest()
    {
      var creator = new KontagentTaskCreator();
      var task = (CastleLoginTask)creator.CreateCastleLogin(123, 1);
      Assert.AreEqual(123, task.Auid);
      Assert.AreEqual(1, task.Faction);
    }

    [Test]
    public void CreateFactionSelectedTest()
    {
      var creator = new KontagentTaskCreator();
      var task = (FactionSelectedTask)creator.CreateFactionSelected(123, 1);
      Assert.AreEqual(123, task.Auid);
      Assert.AreEqual(1, task.Faction);
    }

    [Test]
    public void CreateSessionStartTest()
    {
      var creator = new KontagentTaskCreator();
      var task = (SessionStartTask)creator.CreateSessionStart(123, 1, 4, 100500);
      Assert.AreEqual(123, task.Auid);
      Assert.AreEqual(1, task.Faction);
      Assert.AreEqual(4, task.SessionType);
      Assert.AreEqual(100500, task.HeroId);
    }

    [Test]
    public void CreateResourceChangeTest()
    {
      var creator = new KontagentTaskCreator();
      var task = (ResourceChangeTask)creator.CreateResourceChange(123, "test", true, 1, 2, 3, 4, 5, 6, 7, 8, new Dictionary<string, int>());
      Assert.AreEqual(123, task.Auid);
      Assert.AreEqual("test", task.Source);
      Assert.AreEqual(true, task.Gain);
      Assert.AreEqual(1, task.GoldChange);
      Assert.AreEqual(2, task.SilverChange);
      Assert.AreEqual(3, task.PerlChange);
      Assert.AreEqual(4, task.RedPerlChange);
      Assert.AreEqual(5, task.Resource1Change);
      Assert.AreEqual(6, task.Resource2Change);
      Assert.AreEqual(7, task.Resource3Change);
      Assert.AreEqual(8, task.ShardChange);
    }

    [Test]
    public void CreateQuestChangeTest()
    {
      var creator = new KontagentTaskCreator();
      var task = (QuestChangeTask)creator.CreateQuestChange(123, 1, 2, 3);
      Assert.AreEqual(123, task.Auid);
      Assert.AreEqual(1, task.Status);
      Assert.AreEqual(2, task.Quid);
      Assert.AreEqual(3, task.Tm);
    }
  }
}
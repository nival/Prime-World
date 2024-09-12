using System;
using System.IO;
using BusinessLogic.DBManagement;
using BusinessLogic.Social;
using DAL.Repositories;
using Moq;
using NUnit.Framework;
using log4net.Config;

namespace BusinessLogic.Tests.Tasks
{
  public class TalentLogTaskTest
  {
    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void SimpleTest()
    {
      var mocktalentlogrepo = new Mock<ITalentLogRepository>();

      var info = new TalentChangeInfoBL
                   {
                     Auid = 1,
                     Operation = "testoperation",
                     Data = "testdata",
                     TalentId = 12345,
                     TalentInstanceId = 1234512345,
                     BoundHero = 54321,
                     Timestamp = DateTime.Today
                   };
      var task = new TalentLogTask(new[] { info }, mocktalentlogrepo.Object);

      Assert.That(task.Execute());

      mocktalentlogrepo.Verify(m => m.Create("testoperation", "testdata", 1, 12345, 1234512345, 54321, null, DateTime.Today));
    }
  }
}
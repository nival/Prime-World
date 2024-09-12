using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading;
using BusinessLogic.DBManagement;
using BusinessLogic.Queuing;
using log4net;
using log4net.Config;
using Moq;
using NUnit.Framework;

namespace BusinessLogic.Tests.Queuing
{
  [TestFixture]
  public class TaskExecutorTests
  {
    private static ILog _log = LogManager.GetLogger(typeof(Worker));

    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void SimpleTest()
    {
      var executor = new TaskExecutor(5);
      var mocktask = new Mock<ITask>();
      bool finished = false;
      mocktask.Setup(m => m.Execute()).Callback(() => Thread.Sleep(10))
        .Returns(true).Callback(() => finished = true);

      executor.Run();
      _log.Info("enqueue task");
      executor.EnqueueTask(mocktask.Object);
      Thread.Sleep(100);

      Assert.That(finished);
      mocktask.VerifyAll();
    }

    [Test]
    public void BrokenTaskTest()
    {
      var executor = new TaskExecutor(1) {MaxTaskAttempts = 2};
      var mocktask = new Mock<ITask>();
      mocktask.SetupAllProperties();
      mocktask.Setup(m => m.Execute()).Callback(() => mocktask.Object.ErrorCount++).Returns(false);
      mocktask.Setup(m => m.Dump()).Returns("TASK INFO");

      executor.Run();
      executor.EnqueueTask(mocktask.Object);
      Thread.Sleep(210);

      mocktask.Verify(m => m.Execute(), Times.Exactly(2));
      mocktask.Verify(m => m.Dump(), Times.Once());
    }

    [Test]
    public void UnstableTaskTest()
    {
      var executor = new TaskExecutor(5) {MaxTaskAttempts = 10};
      var mocktask = new Mock<ITask>();
      mocktask.SetupAllProperties();
      mocktask.Setup(m => m.Execute()).Callback(() => { mocktask.Object.ErrorCount++; Thread.Sleep(10); }).Returns(false);
      mocktask.Setup(m => m.Dump()).Returns("TASK INFO");

      executor.Run();
      _log.Info("enqueue task");
      executor.EnqueueTask(mocktask.Object);
      Thread.Sleep(100);
      _log.Info("fixing task");
      mocktask.Setup(m => m.Execute()).Returns(true);
      Thread.Sleep(150);
      Assert.AreEqual(0, executor.QueueLength);

      mocktask.Verify(m => m.Execute(), Times.AtMost(9));
      mocktask.Verify(m => m.Dump(), Times.Never());
    }

    [Test]
    public void TaskQueueTest()
    {
      var executor = new TaskExecutor(3);
      var mocktasks = new List<Mock<ITask>>();
      for (int i = 0; i < 10; i++)
      {
        var mock = new Mock<ITask>();
        mock.Setup(m => m.Execute()).Callback(() => Thread.Sleep(30)).Returns(true);
        mocktasks.Add(mock);
      }
      executor.Run();
      mocktasks.ForEach(m => executor.EnqueueTask(m.Object));
      Thread.Sleep(300);
      mocktasks.ForEach(m => m.VerifyAll());
    }

    [Test, Ignore("Unstable debug test")]
    public void SelfMonitoringTest()
    {
      var executor = new TaskExecutor(5);
      executor.SelfMonitoringInterval = 100;
      var mocktasks = new List<Mock<ITask>>();
      for (int i = 0; i < 100; i++)
      {
        var mock = new Mock<ITask>();
        mock.Setup(m => m.Execute()).Callback(() => Thread.Sleep(30)).Returns(true);
        mocktasks.Add(mock);
      }
      executor.Run();
      mocktasks.ForEach(m => executor.EnqueueTask(m.Object));
      Thread.Sleep(1000);
      mocktasks.ForEach(m => m.VerifyAll());
    }

    [Test]
    public void DelayBeforeRetryTest()
    {
      var executor = new TaskExecutor(1);
      var mtask = new Mock<ITask>();

      mtask.Setup(m => m.Execute()).Returns(false);
      mtask.SetupAllProperties();

      executor.Run();
      executor.EnqueueTask(mtask.Object);

      Thread.Sleep(200);
      executor.Stop();

      mtask.Verify(m => m.Execute(), Times.Exactly(2));
    }
  }
}
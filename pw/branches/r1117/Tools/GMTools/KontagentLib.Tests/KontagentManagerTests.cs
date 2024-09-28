using System;
using System.Diagnostics;
using System.IO;
using System.Threading;
using log4net.Config;
using Moq;
using NUnit.Framework;

namespace KontagentLib.Tests
{
  [TestFixture]
  public class KontagentManagerTests
  {
    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    private KontagentContext CreateKontagentContext()
    {
      return new KontagentContext
               {
                 MarketingServiceUrl = "test://url",
                 RequestTimeout = 1000,
                 TimeoutAfterError = 5000,
                 QueueLength = 20000,
                 QueueDumpingPart = 0.5f,
                 QueueRestoringPoint = 0.25f,
                 SentRateMin = 20,
                 SentRateChange = 10,
                 MaxFailPercent = 0.5f
               };
    }

    [Test]
    public void SimpleTaskRunTest()
    {
      var mockTaskDumper = new Mock<ITaskDumper>();
      var mockTaskCreator = new Mock<IKontagentTaskCreator>();
      var mockTask = new Mock<IKontagentTask>();
      mockTaskCreator.Setup(m => m.CreateLauncherStart(123, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "100.500.ap1.ap2"))
        .Returns(mockTask.Object).AtMostOnce();
      mockTask.Setup(m => m.SendRequest()).Returns(true)
        .Callback(() => new Thread(() =>
                                     {
                                       Thread.Sleep(50);
                                       mockTask.Raise(m => m.Finished += null, mockTask.Object, true);
                                     }).Start())
        .AtMostOnce();

      var kontagentManager = new KontagentManager(CreateKontagentContext(), mockTaskDumper.Object, mockTaskCreator.Object);
      kontagentManager.Run();
      kontagentManager.LauncherStart(123, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "100.500.ap1.ap2");
      Thread.Sleep(2000);

      mockTaskCreator.VerifyAll();
      mockTask.VerifyAll();
    }

    [Test]
    public void RestartFailedTaskTest()
    {
      var mockTaskDumper = new Mock<ITaskDumper>();
      var mockTaskCreator = new Mock<IKontagentTaskCreator>();
      var mockTask = new Mock<IKontagentTask>();
      mockTask.Setup(m => m.SendRequest()).Returns(true)
        .Callback(() => new Thread(() =>
                                     {
                                       Thread.Sleep(50);
                                       mockTask.Raise(m => m.Finished += null, mockTask.Object, false);
                                     }).Start());
      mockTaskCreator.Setup(m => m.CreateLauncherStart(123, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "100.500.ap1.ap2"))
        .Returns(mockTask.Object);
      var mockTask2 = new Mock<IKontagentTask>();
      mockTask2.Setup(m => m.SendRequest()).Returns(true)
        .Callback(() => new Thread(() =>
                                     {
                                       Thread.Sleep(50);
                                       mockTask2.Raise(m => m.Finished += null, mockTask2.Object, true);
                                     }).Start());
      mockTaskCreator.Setup(m => m.CreateLauncherStart(234, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "100.500.ap1.ap2"))
        .Returns(mockTask2.Object);

      var kontagentManager = new KontagentManager(CreateKontagentContext(), mockTaskDumper.Object, mockTaskCreator.Object);
      kontagentManager.Run();

      kontagentManager.LauncherStart(123, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "100.500.ap1.ap2");
      kontagentManager.LauncherStart(234, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "100.500.ap1.ap2");
      Thread.Sleep(1500);
      mockTask.Setup(m => m.SendRequest()).Returns(true)
        .Callback(() => new Thread(() =>
                                     {
                                       Thread.Sleep(50);
                                       mockTask.Raise(m => m.Finished += null, mockTask.Object, true);
                                     }).Start());
      Thread.Sleep(1500);

      mockTaskCreator.VerifyAll();
      mockTask.Verify(m => m.SendRequest(), Times.Exactly(2));
    }

    [Test, Ignore, Description("Тест отключен, потому что очень долгий")]
    public void ManyTasksTest()
    {
      var mockTaskDumper = new Mock<ITaskDumper>();
      var mockTaskCreator = new Mock<IKontagentTaskCreator>();
      mockTaskCreator.Setup(m => m.CreateLauncherStart(123, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "100.500.ap1.ap2"))
        .Returns(() =>
                   {
                     // mock объект для таска создается при каждом запросе к креатору
                     var mockTask = new Mock<IKontagentTask>();
                     mockTask.Setup(m => m.SendRequest()).Returns(true)
                       .Callback(() => new Thread(() =>
                                                    {
                                                      Thread.Sleep(50);
                                                      mockTask.Raise(m => m.Finished += null, mockTask.Object, true);
                                                    }).Start())
                       .AtMostOnce();
                     return mockTask.Object;
                   });

      var kontagentManager = new KontagentManager(CreateKontagentContext(), mockTaskDumper.Object, mockTaskCreator.Object);
      kontagentManager.Run();

      for (int i = 0; i < 3000; i++)
      {
        kontagentManager.LauncherStart(123, "fb42ed5d-0f6b-43ca-8c0b-92a90b1671d1", "100.500.ap1.ap2");
        Thread.Sleep(10);
      }
      Thread.Sleep(30000);

      mockTaskCreator.VerifyAll();
    }

    [Test, Ignore]
    public void EndlessRealTasksTest()
    {
      var mockTaskDumper = new Mock<ITaskDumper>();
      var context = CreateKontagentContext();
      context.MarketingServiceUrl = "http://localhost:8080";

      var kontagentManager = new KontagentManager(context, mockTaskDumper.Object);
      kontagentManager.Run();

      var sw = Stopwatch.StartNew();
      while (sw.Elapsed < new TimeSpan(0, 10, 0))
      {
        kontagentManager.FirstLogin(123,"mooid");
        Thread.Sleep(1000);
      }
    }

  }
}
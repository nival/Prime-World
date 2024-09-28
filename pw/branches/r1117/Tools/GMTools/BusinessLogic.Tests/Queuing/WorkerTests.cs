using System.IO;
using System.Threading;
using BusinessLogic.Queuing;
using log4net;
using log4net.Config;
using Moq;
using NUnit.Framework;

namespace BusinessLogic.Tests.Queuing
{
  [TestFixture]
  public class WorkerTests
  {
    private static ILog _log = LogManager.GetLogger(typeof(Worker));

    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void ExecuteTask()
    {
      var mocktask = new Mock<ITask>();
      mocktask.Setup(m => m.Execute())
        .Callback(() => Thread.Sleep(50))
        .Returns(true);

      var worker = new Worker();
      bool callback_fired = false;
      worker.Finished += (t, s, e) =>
                           {
                             callback_fired = true;
                             Assert.AreSame(t, mocktask.Object);
                             Assert.IsTrue(s);
                             Assert.Greater(e, 0);
                           };
      Assert.IsTrue(worker.Idle);
      worker.Execute(mocktask.Object);
      Thread.Sleep(10);
      Assert.IsFalse(worker.Idle);
      Thread.Sleep(100);
      Assert.IsTrue(worker.Idle);
      Assert.IsTrue(callback_fired);
      mocktask.Verify(m => m.Execute(), Times.Once());
    }

    [Test]
    public void ExecuteBrokenTask()
    {
      var mocktask = new Mock<ITask>();
      mocktask.Setup(m => m.Execute())
        .Callback(() => Thread.Sleep(50))
        .Returns(false);

      var worker = new Worker();
      bool callback_fired = false;
      worker.Finished += (t, s, e) =>
                           {
                             callback_fired = true;
                             Assert.AreSame(t, mocktask.Object);
                             Assert.IsFalse(s);
                             Assert.Greater(e, 0);
                           };
      Assert.IsTrue(worker.Idle);
      worker.Execute(mocktask.Object);
      Thread.Sleep(10);
      Assert.IsFalse(worker.Idle);
      Thread.Sleep(200);
      Assert.IsTrue(worker.Idle);
      Assert.IsTrue(callback_fired);
      mocktask.Verify(m => m.Execute(), Times.Once());
    }
  }
}
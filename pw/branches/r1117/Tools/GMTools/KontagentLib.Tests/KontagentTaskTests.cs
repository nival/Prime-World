using System;
using System.IO;
using System.Net;
using System.Text;
using System.Threading;
using log4net;
using log4net.Config;
using Moq;
using NUnit.Framework;

namespace KontagentLib.Tests
{
  [TestFixture]
  public class KontagentTaskTests
  {
    private static ILog _log = LogManager.GetLogger(typeof (KontagentTaskTests));

    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    class SomeTask : KontagentTask
    {
      public override string Method() { return "some_method"; }
      public int IntProp { get; set; }
      public string StrProp { get; set; }
    }

    [Test]
    public void GetParametersTest()
    {
      var t = new SomeTask {IntProp = 10, StrProp = "hello"};
      var parameters = t.GetParameters();
      Assert.AreEqual("method=some_method&intprop=10&strprop=hello", parameters);
    }

    [Test]
    public void GetParametersUnicodeTest()
    {
      var t = new SomeTask { IntProp = 10, StrProp = "лолушки" };
      var parameters = t.GetParameters();
      Assert.AreEqual("method=some_method&intprop=10&strprop=%d0%bb%d0%be%d0%bb%d1%83%d1%88%d0%ba%d0%b8", parameters);
    }

    [Test]
    public void GetParametersQuestionMarksTest()
    {
      var t = new SomeTask { IntProp = 10, StrProp = null };
      var parameters = t.GetParameters();
      Assert.AreEqual("method=some_method&intprop=10&strprop=", parameters);
    }


    [Test]
    public void ToStringTest()
    {
      var t = new SomeTask { IntProp = 10, StrProp = "hello" };
      Assert.AreEqual("SomeTask(Method=some_method,IntProp=10,StrProp=hello)", t.ToString());
    }

    [Test]
    public void SendingRequestTest()
    {
      var mockwebrequestcreate = new Mock<IWebRequestCreate>();
      var mockwebrequest = new Mock<WebRequest>();
      var mockwebresponse = new Mock<WebResponse>();
      var mockasyncresult = new Mock<IAsyncResult>();
      var waithandle = new AutoResetEvent(false);

      mockwebrequestcreate.Setup(m => m.Create(It.IsAny<Uri>())).Returns(mockwebrequest.Object);
      mockwebrequest.Setup(m => m.BeginGetResponse(It.IsAny<AsyncCallback>(), It.IsAny<object>()))
        .Callback((AsyncCallback callback, object obj) => callback(mockasyncresult.Object))
        .Returns(mockasyncresult.Object);
      mockwebrequest.Setup(m => m.EndGetResponse(mockasyncresult.Object)).Returns(mockwebresponse.Object);
      mockwebresponse.Setup(m => m.GetResponseStream())
        .Returns(new MemoryStream(Encoding.UTF8.GetBytes("{\"ec\":0, \"tm\":10, \"message\":\"testmessage\"}")));
      mockasyncresult.Setup(m => m.AsyncWaitHandle).Returns(waithandle);


      WebRequest.RegisterPrefix("test", mockwebrequestcreate.Object);
      KontagentTask.ServiceUrl = "test://url";

      var t = new SomeTask { IntProp = 10, StrProp = "hello" };
      bool finished = false;
      t.Finished += (task, success) =>
                      {
                        Thread.Sleep(1);
                        waithandle.Set();
                        Assert.AreEqual(t, task);
                        Assert.IsTrue(success);
                        finished = true;
                      };

      Assert.IsTrue(t.SendRequest());
      Thread.Sleep(3000);
      Assert.That(finished);

      mockwebrequestcreate.Verify(m => m.Create(It.Is<Uri>(u => u == new Uri("test://url?method=some_method&intprop=10&strprop=hello"))));
      mockwebrequest.VerifyAll();
    }

    [Test]
    [Ignore("Дебажный тест, хотелось проверить работу таймаута на реальном WebRequest, а не на mock")]
    public void RequestTimeoutTest()
    {
      KontagentTask.ServiceUrl = "http://localhost:8080";

      var t = new SomeTask {IntProp = 10, StrProp = "hello"};
      bool finished = false;

      t.Finished += (task, success) =>
                      {
                        _log.Info("CALLBACK! success = " + success);
                        Assert.AreEqual(t, task);
                        //Assert.IsFalse(success);
                        finished = true;
                      };

      Assert.That(t.SendRequest());
      Thread.Sleep(3000);
      Assert.That(finished, "CALLBACK wasn't called");
    }
  }
}
//
//  based on source:
//  http://svn.apache.org/repos/asf/thrift/trunk/lib/csharp/src/Transport/THttpHandler.cs
//

using System;
using System.Net;
using log4net;
using Thrift;
using Thrift.Protocol;
using Thrift.Transport;

namespace DummyMonitoringService.Thrift
{
  public class THttpHandler// : IHttpHandler
  {
    private static ILog _log = LogManager.GetLogger(typeof(THttpHandler));

    protected TProcessor processor;

    protected TProtocolFactory inputProtocolFactory;
    protected TProtocolFactory outputProtocolFactory;

    public THttpHandler(TProcessor processor)
      : this(processor, new TBinaryProtocol.Factory())
    {
    }

    public THttpHandler(TProcessor processor, TProtocolFactory protocolFactory)
      : this(processor, protocolFactory, protocolFactory)
    {
    }

    public THttpHandler(TProcessor processor, TProtocolFactory inputProtocolFactory, TProtocolFactory outputProtocolFactory)
    {
      this.processor = processor;
      this.inputProtocolFactory = inputProtocolFactory;
      this.outputProtocolFactory = outputProtocolFactory;
    }

    public void ProcessRequest(HttpListenerContext context)//(HttpContext context)
    {
      context.Response.ContentType = "application/x-thrift";
      context.Response.ContentEncoding = System.Text.Encoding.UTF8;

      TTransport transport = new TStreamTransport(context.Request.InputStream, context.Response.OutputStream);

      try
      {
        TProtocol inputProtocol = inputProtocolFactory.GetProtocol(transport);
        TProtocol outputProtocol = outputProtocolFactory.GetProtocol(transport);

        while (processor.Process(inputProtocol, outputProtocol)) { }
      }
      catch (TTransportException)
      {
        // Client died, just move on
      }
      catch (Exception x)
      {
        _log.Error("Error while processing http request", x);
      }

      transport.Close();
    }
  }
}
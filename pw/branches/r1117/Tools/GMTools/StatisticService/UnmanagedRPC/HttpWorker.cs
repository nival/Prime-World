using System;
using System.IO;
using System.Net;
using log4net;
using System.Threading;
using System.Diagnostics;

namespace StatisticService
{
  public interface IBinaryMessageHandler
  {
    void HandleBinaryMessage(uint msgid, BinaryReader reader, ICallContext callCtx);
  };

  public class HttpWorker
  {
    private static ILog log = LogManager.GetLogger(typeof(HttpWorker));

    public HttpWorker(string url, MemoryStream serializedPermittedMethods, IBinaryMessageHandler messagesHandler)
    {
      this.serializedPermittedMethods = serializedPermittedMethods;
      this.messagesHandler = messagesHandler;

      log.InfoFormat("Game Statistics starting. prefixes='{0}'", url);

      httpServer.Prefixes.Add(url);
      httpServer.Start();

      log.InfoFormat("Game Statistics listening.");

      stats_timer.Start();
    }


    public void Shutdown()
    {
      runThreadRun = false;
    }


    public void DumpStats()
    {
      long ms = stats_timer.ElapsedMilliseconds;
      if ( ms < 10000 )
        return;

      stats_timer.Reset();
      stats_timer.Start();

      if( ( stats_getRequests > 0 ) || ( stats_postRequests > 0 ) )
      {
        log.InfoFormat( "Load values, per second: gets={0:0.#}, posts={1:0.#}, get_kb={2:0.0}, post_kb={3:0.0}, msg={4:0.0}, exceptions={5:0.0}",
          0.1 * (float)stats_getRequests,
          0.1 * (float)stats_postRequests,
          0.1 * (float)stats_bytesDownloaded / 1024.0,
          0.1 * (float)stats_bytesUploaded / 1024.0,
          0.1 * (float)stats_messages,
          0.1 * (float)stats_exceptions);
      }

      stats_getRequests = 0;
      stats_postRequests = 0;
      stats_bytesUploaded = 0;
      stats_bytesDownloaded = 0;
      stats_exceptions = 0;
    }

    
    const int MsgPerChunkLimit = 65536;
    const UInt32 DATA_MARKER = 0xc001face;

    public void ParallelWork()
    {
      while (runThreadRun)
      {
        HttpListenerContext context = httpServer.GetContext();
        HttpListenerRequest request = context.Request;

        log.DebugFormat("Processing HTTP request. remote={0}, method={1}, bytes={2}, url={3}", request.RemoteEndPoint, request.HttpMethod, request.ContentLength64, request.Url);

        try
        {
          if (request.HttpMethod == "GET")
          {
            using (var response = context.Response)
            {
              response.ContentType = "application/octet-stream";
              byte[] data = serializedPermittedMethods.GetBuffer();
              response.OutputStream.Write(data, 0, (int)serializedPermittedMethods.Length);
              response.OutputStream.Close();
            }

            Interlocked.Add(ref stats_getRequests, 1);
            Interlocked.Add(ref stats_bytesDownloaded, (int) serializedPermittedMethods.Length);
          }
          else if (request.HttpMethod == "POST")
          {
            string responseString;
            try
            {
              int msgNum = ProcessPostRequest(request);
              responseString = string.Format("Data accepted. content_length={0}, messages_read={1}",
                                             request.ContentLength64, msgNum);
            }
            catch (Exception excep)
            {
              log.ErrorFormat("Exception while processing HTTP POST! remote={0}\n{1}", request.RemoteEndPoint, excep);
              responseString = "Exception catched. text=" + excep.Message;

              Interlocked.Add(ref stats_exceptions, 1);
            }
            
            using (var response = context.Response)
            {
              byte[] buffer = System.Text.Encoding.UTF8.GetBytes(responseString);
              response.ContentLength64 = buffer.Length;
              response.OutputStream.Write(buffer, 0, buffer.Length);
              response.OutputStream.Close();
            }
          }
        }
        catch (Exception ex)
        {
          log.Error("Unexpected HttpWorker exception", ex);
          Interlocked.Add(ref stats_exceptions, 1);
        }
      }

      httpServer.Close();
    }


    private int ProcessPostRequest(HttpListenerRequest request)
    {
      ICallContext callCtx = new ICallContext();

      ExtractClientTimestamp(request, callCtx);

      var reader = new BinaryReader(request.InputStream);

      int messagesNumber = 0;
      long dataLeft = request.ContentLength64;
      while (true)
      {
        if (dataLeft <= 0)
          break;
        ParseMessageFromChunk(reader, ref dataLeft, callCtx);
        ++messagesNumber;
        if (messagesNumber >= MsgPerChunkLimit)
          throw new NotSupportedException(String.Format("Too many messages in chunk! limit={0}", messagesNumber));
      }
      reader.Close();

      Interlocked.Add(ref stats_postRequests, 1);
      Interlocked.Add(ref stats_bytesUploaded, (int)request.ContentLength64);
      Interlocked.Add(ref stats_messages, messagesNumber);

      return messagesNumber;
    }


    private void ExtractClientTimestamp(HttpListenerRequest request, ICallContext callCtx)
    {
      string clientTimestampStr = request.QueryString.Get("timestamp");
      if (clientTimestampStr != null)
        callCtx.transmissionTimestamp = Convert.ToUInt32(clientTimestampStr);
    }


    private void ParseMessageFromChunk(BinaryReader reader, ref long bytesLeft, ICallContext callCtx)
    {
      UInt32 marker = reader.ReadUInt32();
      if (marker != DATA_MARKER)
        throw new Exception(String.Format("Data marker expected"));

      UInt32 msgId = reader.ReadUInt32();

      callCtx.eventTimestamp = reader.ReadUInt32();

      UInt32 msgLen = reader.ReadUInt32();
      if (msgLen < 4 || msgLen >= 32768)
        throw new Exception(String.Format("Invalid message size. size={0}", msgLen));

      messagesHandler.HandleBinaryMessage(msgId, reader, callCtx);

      bytesLeft -= 4 * sizeof(UInt32);
      bytesLeft -= msgLen;
    }


    private IBinaryMessageHandler messagesHandler;
    private MemoryStream serializedPermittedMethods;

    private HttpListener httpServer = new HttpListener();
    private volatile bool runThreadRun = true;

    private Stopwatch stats_timer = new Stopwatch();
    private int stats_getRequests;
    private int stats_postRequests;
    private int stats_bytesUploaded;
    private int stats_bytesDownloaded;
    private int stats_exceptions;
    private int stats_messages;
  }
}

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using log4net;
using StatisticService.RPC;


namespace StatisticService
{
  public class UnmanagedRPC : IUnmanagedRpcCallbacks, IBinaryMessageHandler
  {
    private static ILog log = LogManager.GetLogger(typeof(UnmanagedRPC));

    public void Start(string url, List<string> permittedMethods, List<int> permittedEventTypes)
    {
      var stream = new MemoryStream();
      SerializePermittedMethods(stream, permittedMethods, permittedEventTypes);

      httpWorker = new HttpWorker(url, stream, this);

      httpWorkerThread = new Thread(httpWorker.ParallelWork);
      httpWorkerThread.Start();
    }


    public void Shutdown()
    {
      if (httpWorker!=null)
        httpWorker.Shutdown();
    }


    public void Poll()
    {
      if (httpWorker != null)
        httpWorker.DumpStats();
    }


    private void SerializePermittedMethods(MemoryStream destStream, List<string> structures, List<int> eventTypes)
    {
      var events = new PermittedStatisticsMethods
      {
        methods = structures.Select(m => (int)NivalGenuineStringHash(m)).ToList(),
        sessionEvents = eventTypes
      };
      var writer = new BinaryWriter(destStream);
      var serializer = new ChunklessWriter(writer);

      events.Serialize(serializer);
    }


    void IUnmanagedRpcCallbacks.Register<TData>(RemoteCallHandler<TData> handler)
    {
      string name = typeof(TData).Name;
      uint hash = NivalGenuineStringHash(name);

      log.DebugFormat("Registering unmanaged data. name={0}, hash={1}", name, hash);

      var handlerInfo = new BoxedRemoteHandlerInfo<TData>(handler);

      handlers.Add(hash, handlerInfo);
    }



    private uint NivalGenuineStringHash(string s)
    { 
      uint h = 0;
      foreach(char c in s)
        h = 5 * h + (uint)c;
      return h;
    }


    public void HandleBinaryMessage(uint msgid, BinaryReader reader, ICallContext callCtx)
    {
      RemoteCallHandlerInfo handler;
      if (!handlers.TryGetValue(msgid, out handler))
      {
        log.ErrorFormat("Unknown message! id={0}", msgid);
        return;
      }

      var serializer = new ChunklessReader(reader);

      var dataObj = Activator.CreateInstance(handler.type);

      var ser = (ISerializable) dataObj;
      ser.Serialize(serializer);

      handler.BoxedCall(ser, callCtx);
    }


    private abstract class RemoteCallHandlerInfo
    {
      public Type type;

      public RemoteCallHandlerInfo(Type t)
      {
        type = t;
      }

      public abstract void BoxedCall(ISerializable boxedData, ICallContext callCtx);
    }


    private class BoxedRemoteHandlerInfo<TData> : RemoteCallHandlerInfo
    where TData : ISerializable, new()
    {
      public BoxedRemoteHandlerInfo(RemoteCallHandler<TData> h):
      base(typeof(TData))
      {
        this.handler = h;
      }

      public override void BoxedCall(ISerializable boxedData, ICallContext callCtx)
      {
        TData data = boxedData as TData;
        handler(data, callCtx);
      }

      private RemoteCallHandler<TData> handler;
    }



    private Dictionary<uint, RemoteCallHandlerInfo> handlers = new Dictionary<uint, RemoteCallHandlerInfo>();

    private HttpWorker httpWorker;
    private Thread httpWorkerThread;
  }
}

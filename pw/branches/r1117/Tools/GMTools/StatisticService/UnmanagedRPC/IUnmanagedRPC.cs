namespace StatisticService
{
  public class ICallContext
  {
    public uint transmissionTimestamp = 0;
    public uint eventTimestamp = 0;
  };

  public delegate void RemoteCallHandler<TData>(TData data, ICallContext callCtx);

  public interface IUnmanagedRpcCallbacks
  {
    void Register<TData>(RemoteCallHandler<TData> handler) where TData : ISerializable, new();
  }
}

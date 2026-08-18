using System;
using System.Collections.Generic;
using ModelData.Network;
using UnityEngine;
using UnityEngine.Networking;
using Lobby.Configs;

public class HTTPSocketComponent : MonoBehaviour, IHTTPSocket
{
  #region Requests
  private bool _stopRequests;
  private abstract class RequestItem
  {
    private readonly string _url;
    private float _executeTime;
    public float SendingTime { get; private set; }
    private readonly float _timeOut;
    private bool _executed = false;
    private UnityWebRequest _www = null;

    private readonly SocketReceiveResponseHandler _responseHandler;

    public RequestItem(string url, float time, float delay, float timeOut, SocketReceiveResponseHandler responseHandler)
    {
      _url = url;
      _executeTime = delay == 0 ? 0 : time + delay;
      _timeOut = timeOut;
      _responseHandler = responseHandler;
    }

    protected abstract void Execute();

    protected void AssignWWW(UnityWebRequest www)
    {
      _www = www;
      _www.SendWebRequest();
    }

    public bool TryExecute(float time)
    {
      if (Executed || _executeTime > time)
        return false;

      _executed = true;
      _executeTime = time + _timeOut;
      SendingTime = time;
      Execute();
      return true;
    }

    public bool IsTimeOut(float time)
    {
      return Executed && (_timeOut != 0 && _executeTime < time);
    }

    public string Url { get { return _url; } }
    public bool Executed { get { return _executed; } }

    public UnityWebRequest WWW { get { return _www; } }
    public SocketReceiveResponseHandler ResponseHandler { get { return _responseHandler; } }
  }
  private sealed class GetRequestItem : RequestItem
  {
    public GetRequestItem(string url, float time, float delay, float timeOut, SocketReceiveResponseHandler responseHandler)
      : base(url, time, delay, timeOut, responseHandler)
    {
    }

    protected override void Execute()
    {
      NivalCLI.CLI.NetLog("Send GET: {0}", RequestProcessor.SendPacketRegex.Replace(Url, "$1=***"));
      AssignWWW(UnityWebRequest.Get(Url));
    }
  }
  private sealed class PostRequestItem : RequestItem
  {
    private Dictionary<string, string> _data;
    private Dictionary<string, byte[]> _binaryData;
    public PostRequestItem(string url, float time, float delay, float timeOut,
      Dictionary<string, string> data, SocketReceiveResponseHandler responseHandler)
      : base(url, time, delay, timeOut, responseHandler)
    {
      _data = data;
    }

    public PostRequestItem(string url, float time, float delay, float timeOut,
      Dictionary<string, string> data, Dictionary<string, byte[]> binaryData,
      SocketReceiveResponseHandler responseHandler)
      : base(url, time, delay, timeOut, responseHandler)
    {
      _data = data;
      _binaryData = binaryData;
    }

    protected override void Execute()
    {
      var formString = string.Empty;
      var form = new WWWForm();
      if (_data != null)
        foreach (var v in _data)
        {
          form.AddField(v.Key, v.Value);
          formString += v.Key + "=" + v.Value + " ";
        }
      if (_binaryData != null)
        foreach (var v in _binaryData)
        {
          form.AddBinaryData(v.Key, v.Value, v.Key, "image/png");
        }
      formString = "{ " + formString + " }";
      NivalCLI.CLI.NetLog("Send POST: {0}\nForm data: {1}", RequestProcessor.SendPacketRegex.Replace(Url, "$1=***"),
        RequestProcessor.SendPacketRegex.Replace(formString, "$1=***"));
      AssignWWW(UnityWebRequest.Post(Url, form));
    }
  }
  #endregion

  #region Helpers
  public class WWWResponseArgs : HTTPResponseArgs
  {
    public UnityWebRequest WWW { get; private set; }

    public WWWResponseArgs(StatusCode code, string error, byte[] packet, UnityWebRequest www, float duration)
      : base(code, error, packet, www.url, duration)
    {
      WWW = www;
    }
  }

  private static StatusCode GetError(string error)
  {
    var errorLower = error.ToLower();
    if (errorLower.Contains("503"))
      return StatusCode.FatalConnectionLost;
    if (errorLower.Contains("410"))
      return StatusCode.ServerIsShuttingDown;
    if (errorLower.Contains("selfmade timeout"))
      return StatusCode.ManualTimeOut;
    if (errorLower.Contains("504"))
      return StatusCode.GatewayTimeOut;
    if (errorLower.Contains("500"))
      return StatusCode.InternalServerError;
    if (errorLower.Contains("could not resolve host") 
      || errorLower.Contains("couldn't resolve host")
      || errorLower.Contains("couldn't connect to host") 
      || errorLower.Contains("couldn't connect to server")
      || errorLower.Contains("host not found")
      || errorLower.Contains("502") 
      || errorLower.Contains("connection was reset") 
      || errorLower.Contains("timed out") 
      || errorLower.Contains("failed to connect"))
      return StatusCode.MinorConnectionLost;

    NivalCLI.CLI.NetLog("Get error: {0}", string.IsNullOrEmpty(error) ? "None" : error);
    return StatusCode.UnknownError;
  }
  #endregion

  private readonly List<RequestItem> _requestList = new List<RequestItem>();
  public int RequestsCount { get { return _requestList.Count; } }

  private void FixedUpdate()
  {
    var time = Time.time;
    for (int it = 0; it < _requestList.Count; ++it)
    {
      RequestItem request = _requestList[it];
      if (!request.Executed)
        request.TryExecute(time);
      else if (request.WWW.isDone || request.IsTimeOut(time))
      {
        try
        {
          if (request.ResponseHandler != null)
          {
            var duration = time - request.SendingTime;
            var error = !request.WWW.isDone ? "Selfmade timeout" : request.WWW.error;
            request.ResponseHandler(string.IsNullOrEmpty(error)
              ? new WWWResponseArgs(StatusCode.OK, error, request.WWW.downloadHandler.data, request.WWW, duration)
              : new WWWResponseArgs(GetError(error), error.TrimEnd(), new byte[0], request.WWW, duration));
          }
        }
        catch (Exception e)
        {
          NivalCLI.CLI.Error("Response process failed: {0}\n{1}", e.Message, e.StackTrace);
        }
        finally
        {
          request.WWW.Dispose();
          _requestList.RemoveAt(it--);
        }
      }
    }
  }

  #region IHTTPSocket implementation

  public void StopRequests()
  {
    _stopRequests = true;
  }
  public void SendGetRequest(string request, float executeDelay, SocketReceiveResponseHandler responseHandler)
  {
    if (_stopRequests)
      return;
    SendGetRequest(request, executeDelay, (float)Config.WwwTimeout, responseHandler);
  }

  public void SendGetRequest(string request, float executeDelay, float timeout, SocketReceiveResponseHandler responseHandler)
  {
    if (_stopRequests)
      return;

    var item = new GetRequestItem(request, Time.time, executeDelay, timeout, responseHandler);
    _requestList.Add(item);
  }

  public void SendPostRequest(string request, float executeDelay,
    Dictionary<string, string> data, Dictionary<string, byte[]> binaryData, SocketReceiveResponseHandler responseHandler)
  {
    if (_stopRequests)
      return;

    SendPostRequest(request, executeDelay, (float)Config.WwwTimeout, data, binaryData, responseHandler);
  }

  public void SendPostRequest(string request, float executeDelay, float timeout,
    Dictionary<string, string> data, Dictionary<string, byte[]> binaryData, SocketReceiveResponseHandler responseHandler)
  {
    if (_stopRequests)
      return;
    var item = new PostRequestItem(request, Time.time, executeDelay, timeout, data, binaryData, responseHandler);
    _requestList.Add(item);
  }
  #endregion
}

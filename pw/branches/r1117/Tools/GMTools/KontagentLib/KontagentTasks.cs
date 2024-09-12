using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Threading;
using System.Web;
using System.Web.Script.Serialization;
using DAL.Entities;
using DAL.Repositories;
using log4net;

namespace KontagentLib
{
  public delegate void TaskCallback(IKontagentTask task, bool success);

  public interface IKontagentTask
  {
    bool SendRequest();
    event TaskCallback Finished;
  }

  public abstract class KontagentTask : IKontagentTask
  {
    private static ILog _log = LogManager.GetLogger(typeof (KontagentTask));

    private WebRequest request;
    private Stopwatch requesttimer = new Stopwatch();

    private static int requestTimeout = 10000;
    public static int RequestTimeout
    {
      set
      {
        if (value <= 0)
          throw new ArgumentException("Invalid request timeout = " + value, "value");
        requestTimeout = value;
      }
      get { return requestTimeout; }
    }
    private static string serviceurl;
    public static string ServiceUrl
    {
      set
      {
        if (value == null || !Uri.IsWellFormedUriString(value, UriKind.Absolute))
          throw new ArgumentException("Invalid marketing service url = " + value, "value");
        serviceurl = value;
      }
      get { return serviceurl; }
    }

    public abstract string Method();

    internal string GetParameters()
    {
      var parameters = this.GetType().GetProperties()
        .Select(p => String.Format("{0}={1}", p.Name.ToLower(),
                                   p.GetValue(this, null) != null
                                     ? HttpUtility.UrlEncode(p.GetValue(this, null).ToString())
                                     : String.Empty));
      return String.Format("method={0}&{1}", Method(), String.Join("&", parameters.ToArray()));
    }

    private string RequestUrl
    {
      get
      {
        if (ServiceUrl == null)
          throw new Exception("Service url is null");
        return serviceurl + "?" + GetParameters();
      }
    }

    public override string ToString()
    {
      var parameters = this.GetType().GetProperties()
        .Select(p => String.Format("{0}={1}", p.Name, p.GetValue(this, null)));
      return String.Format("{0}(Method={1},{2})", this.GetType().Name, Method(), String.Join(",", parameters.ToArray()));
    }

    public virtual bool SendRequest()
    {
      try
      {
        _log.Debug("Sending request to marketing service " + RequestUrl);
        requesttimer = Stopwatch.StartNew();
        request = WebRequest.Create(RequestUrl);
        IAsyncResult result = request.BeginGetResponse(ResponseCallback, null);
        ThreadPool.RegisterWaitForSingleObject(result.AsyncWaitHandle, TimeoutCallback, null, RequestTimeout, true);
      }
      catch (Exception ex)
      {
        _log.Error("Failed to send request " + RequestUrl, ex);
        return false;
      }
      return true;
    }

    public event TaskCallback Finished;

    private void ResponseCallback(IAsyncResult result)
    {
      try
      {
        requesttimer.Stop();

        using (var response = request.EndGetResponse(result))
        using (var responseReader = new StreamReader(response.GetResponseStream()))
        {
          var responseBody = responseReader.ReadToEnd();

          var serializer = new JavaScriptSerializer();
          MarketingServiceResponse msresponse;
          try
          {
            msresponse = serializer.Deserialize<MarketingServiceResponse>(responseBody);
          }
          catch (Exception ex)
          {
            throw new Exception("Failed to parse server response \"" + responseBody + "\"", ex);
          }
          if (msresponse.ec == 0)
            _log.DebugFormat("OK response. remote exec time = {0}, total exec time = {1} ms, request url = {2}", msresponse.tm, requesttimer.ElapsedMilliseconds, RequestUrl);
          else
            _log.WarnFormat("Error response (code={0}, message={1}), exec time = {2}, request url = {3}, task = {4}", msresponse.ec, msresponse.em, requesttimer.ElapsedMilliseconds, RequestUrl, this);
          if (Finished != null)
            Finished(this, true);
        }
      }
      catch (Exception ex)
      {
        if (ex is WebException && ((WebException)ex).Status == WebExceptionStatus.RequestCanceled)
          _log.DebugFormat("Request cancelled in {0} ms by timeout, request url = {1}", requesttimer.ElapsedMilliseconds, RequestUrl);
        else
          _log.Error("Exception in callback from task " + this, ex);
        if (Finished != null)
          Finished(this, false);
      }
    }

    private void TimeoutCallback(object state, bool timedOut)
    {
      if (timedOut)
        this.request.Abort();
    }
  }

  internal class MarketingServiceResponse
  {
    public int ec;
    public string tm;
    public string em;
  }

  public class LauncherStartTask : KontagentTask
  {
    public override string Method() { return "launcher_start"; }
    public long Auid { get; set; }
    public string HostId { get; set; }
    public string Version { get; set; }
  }

  public class LauncherDStartTask : KontagentTask
  {
    public override string Method() { return "launcher_dstart"; }
    public long Auid { get; set; }
    public string HostId { get; set; }
    public string Package { get; set; }
    public string Version { get; set; }
  }

  public class LauncherDEndTask : KontagentTask
  {
    public override string Method() { return "launcher_dend"; }
    public long Auid { get; set; }
    public string HostId { get; set; }
    public string Package { get; set; }
    public string Version { get; set; }
    public int Status { get; set; }
  }

  public class LauncherEventsTask : KontagentTask
  {
    public override string Method() { return "launcher_events"; }
    public long Auid { get; set; }
    public string Muid { get; set; }
    public long Events { get; set; }
  }

  public class FirstLoginTask : KontagentTask
  {
    public override string Method() { return "first_login"; }
    public long Auid { get; set; }
    public string Muid { get; set; }
  }

  public class FactionSelectedTask : KontagentTask
  {
    public override string Method() { return "faction_selected"; }
    public long Auid { get; set; }
    public int Faction { get; set; }
  }

  public class CastleLoginTask : KontagentTask
  {
    public override string Method() { return "castle_login"; }
    public long Auid { get; set; }
    public int Faction { get; set; }
  }

  public class SessionStartTask : KontagentTask
  {
    private static ILog _log = LogManager.GetLogger(typeof (SessionStartTask));

    public override string Method() { return "session_start"; }
    public long Auid { get; set; }
    public int Faction { get; set; }
    public int SessionType { get; set; }
    public int HeroId { get; set; }
    public string HeroName { get; set; }

    private ICharacterRepository characterRepository;

    public SessionStartTask()
    {
    }

    public SessionStartTask(ICharacterRepository crepo)
    {
      characterRepository = crepo;
    }

    public override bool SendRequest()
    {
      switch (SessionType)
      {
        case 4: // Сессия
          SessionType = 1;
          break;
        case 5: // Тренировка
          SessionType = 0;
          break;
        case 6: // Туториал
          SessionType = 2;
          break;
        default: // Что-то еще
          SessionType = -1;
          _log.WarnFormat("Unexpected session type = {0} in SessionStartTask", SessionType);
          break;
      }
      try
      {
        if (String.IsNullOrEmpty(HeroName))
        {
          Character hero;
          if (characterRepository != null)
            hero = characterRepository.GetById(HeroId);
          else
            using (var repo = new CharacterRepository())
              hero = repo.GetById(HeroId);

          if (hero == null)
          {
            _log.Error("Incorrect hero id in task " + this);
            return true; // чтобы больше не пытаться его выполнить
          }
          HeroName = hero.Name;
        }

        return base.SendRequest();
      }
      catch (Exception ex)
      {
        _log.Error("Failed task " + this, ex);
        return false;
      }
    }
  }

  public class ResourceChangeTask : KontagentTask
  {
    public override string Method() { return "resource_change"; }
    public long Auid { get; set; }
    public string Source { get; set; }
    public bool Gain { get; set; }
    public int GoldChange { get; set; }
    public int SilverChange { get; set; }
    public int PerlChange { get; set; }
    public int RedPerlChange { get; set; }
    public int Resource1Change { get; set; }
    public int Resource2Change { get; set; }
    public int Resource3Change { get; set; }
    public int ShardChange { get; set; }
    public Dictionary<string, int> CurrencyChange{ get; set; }
  }

  public class QuestChangeTask : KontagentTask
  {
    public override string Method() { return "quest"; }
    public long Auid { get; set; }
    public int Status { get; set; }
    public int Quid { get; set; }
    public int Tm { get; set; }
  }
}
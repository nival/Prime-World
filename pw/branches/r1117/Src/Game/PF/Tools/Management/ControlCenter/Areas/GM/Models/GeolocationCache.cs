using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Script.Serialization;
using log4net;

namespace ControlCenter.Areas.GM.Models
{

  public interface IGeolocationCache
  {
    List<Country> GetCountries();
    List<Region> GetRegions(string countryCode);
  }


  /// <summary>
  /// Кэшированный справочник геолокаций
  /// </summary>
  public class GeolocationCache : IGeolocationCache
  {
    #region static code

    private static ILog _log = LogManager.GetLogger(typeof(GeolocationDictionaryRequester));

    private static GeolocationCache _instance;
    public static GeolocationCache Instance
    {
      get { return _instance; }
    }

    public static void Init(string address)
    {
      _instance = new GeolocationCache(address);
    }

    #endregion


    private IGeolocationDictionaryRequester _requester;
    private IJsonParser _parser;

    private List<Country> _countries;
    private Dictionary<string, List<Region>> _regionsmap = new Dictionary<string, List<Region>>();

    private readonly object _lockerCountries = new object();
    private readonly object _lockerRegions = new object();


    public GeolocationCache(string address)
      : this(new GeolocationDictionaryRequester(address), new JsonParser())
    {
    }

    public GeolocationCache(IGeolocationDictionaryRequester requester, IJsonParser parser)
    {
      if (requester == null) throw new ArgumentNullException("requester");
      if (parser == null) throw new ArgumentNullException("parser");

      this._requester = requester;
      this._parser = parser;
    }


    public List<Country> GetCountries()
    {
      if (_countries == null)
      {
        lock (_lockerCountries)
        {
          if (_countries == null)
          {
            var response = _requester.GetCountries();
            if (!String.IsNullOrEmpty(response))
              _countries = _parser.ParseCountries(response);
          }
        }
      }
      return _countries;
    }


    public List<Region> GetRegions(string countryCode)
    {
      var countries = GetCountries();
      if (countries == null || !countries.Exists(c => c.Id == countryCode))
        return null;

      if (!_regionsmap.ContainsKey(countryCode))
      {
        lock (_lockerRegions)
        {
          if (!_regionsmap.ContainsKey(countryCode))
          {
            var response = _requester.GetRegions(countryCode);
            if (!String.IsNullOrEmpty(response))
            {
              var regions = _parser.ParseRegions(response);
              if (regions != null && regions.Count > 0)
              {
                _regionsmap.Add(countryCode, regions);
                return regions;
              }
            }
            return null;
          }
        }
      }
      return _regionsmap[countryCode];
    }

  }



  public interface IJsonParser
  {
    List<Country> ParseCountries(string str);
    List<Region> ParseRegions(string str);
  }


  /// <summary>
  /// Парсер JSON строки в набор объектов
  /// </summary>
  public class JsonParser : IJsonParser
  {
    private static ILog _log = LogManager.GetLogger(typeof(Country));
    
    private JavaScriptSerializer _jss = new JavaScriptSerializer();


    public List<Country> ParseCountries(string str)
    {
      try
      {
        var dict = _jss.Deserialize<Dictionary<string, Country>>(str);
        foreach (var pair in dict)
          pair.Value.Id = pair.Key;
        return dict.Values.OrderBy(v => v.Name).ToList();
      }
      catch (Exception ex)
      {
        _log.ErrorFormat("Invalid JSON '{0}'\nParsing error = {1}", str, ex);
        return null;
      }
    }


    public List<Region> ParseRegions(string str)
    {
      try
      {
        var regions = _jss.Deserialize<List<Region>>(str);
        foreach (var r in regions)
          r.Cities.Sort();
        regions.Sort((a,b) => String.Compare(a.Region_name_en, b.Region_name_en, StringComparison.Ordinal));
        return regions;
      }
      catch (Exception ex)
      {
        _log.ErrorFormat("Invalid JSON '{0}'\nParsing error = {1}", str, ex);
        return null;
      }
    }

  }



  public class Country
  {
    public string Id { get; set; }
    public string Code { get; set; }
    public string Name { get; set; }
  }


  public class Region
  {
    public string Region_code { get; set; }
    public string Region_id { get; set; }
    public string Region_name_en { get; set; }
    public List<string> Cities { get; set; }
  }



  public interface IGeolocationDictionaryRequester
  {
    string GetCountries();
    string GetRegions(string countryCode);
  }


  /// <summary>
  /// Обращается к внешнему сервису и возвращает оттуда строку ответа
  /// </summary>
  public class GeolocationDictionaryRequester : IGeolocationDictionaryRequester
  {
    private static ILog _log = LogManager.GetLogger(typeof(GeolocationDictionaryRequester));
    
    private const string GET_COUNTRIES_REQUEST = "get_countries";
    private const string GET_REGIONS_REQUEST = "get_cities?country_code=";

    private const int REQUEST_TIMEOUT = 5000;

    private string address;


    public GeolocationDictionaryRequester(string address)
    {
      if (!Uri.IsWellFormedUriString(address, UriKind.Absolute))
        throw new ArgumentException("Incorrect url address", "address");
      
      this.address = address.TrimEnd('/') + '/';
    }


    public string GetCountries()
    {
      return ExecuteRequest(address + GET_COUNTRIES_REQUEST);
    }


    public string GetRegions(string countryCode)
    {
      return ExecuteRequest(address + GET_REGIONS_REQUEST + countryCode);
    }


    private string ExecuteRequest(string url)
    {
      try
      {
        _log.Debug("Sending request: " + url);

        var request = WebRequest.Create(url);
        request.Timeout = REQUEST_TIMEOUT;

        var watch = Stopwatch.StartNew();
        using (var response = (HttpWebResponse) request.GetResponse())
        using (var reader = new StreamReader(response.GetResponseStream()))
        {
          string result = reader.ReadToEnd();
          _log.DebugFormat("Response in {0} ms, length = {1}", watch.ElapsedMilliseconds, result.Length);
          return result;
        }
      }
      catch (Exception ex)
      {
        _log.Error("Error while executing request", ex);
        return null;
      }
    }

  }

}

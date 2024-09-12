#include <stdafx.h>
#include "HttpStuff.h"
#include "curl/curl.h"
#include "System/Math/MD4.h"

namespace NGameX
{
namespace Http
{

//////////////////////////////////////////////////////////////////////////

  nstl::string BuildLocation(const nstl::string& host, const nstl::string& path)
  {
    struct Local
    {
      static inline int ChopTrailingSlashes(const nstl::string& s)
      {
        for (int i = s.length(); i > 0; )
        {
          --i;

          if (s[i] == '/') continue;
          if (s[i] == '\\') continue;

          return (i + 1);
        }

        return 0;
      }
    };

    nstl::string location;

    const int hostLength = Local::ChopTrailingSlashes(host);

    if (hostLength < host.length())
      location += host.substr(0, hostLength);
    else
      location += host;

    location += "/";
    location += path;

    return location;
  }

//////////////////////////////////////////////////////////////////////////

  nstl::string HttpQuery::Build(const nstl::string& secret)
  {
    static const nstl::string& sign("sign");

    {
      RemoveParam(sign);
    }

    if (params.empty())
      return nstl::string();

    if (!secret.empty())
    {
      nstl::sort(params.begin(), params.end());

      nstl::string data;

      Params::const_iterator it = params.begin();
      Params::const_iterator it_end = params.end();
      for (; it != it_end; ++it)
      {
        Params::const_reference p = *it;

        data += p.name;
        data += p.value;
      }

      data += secret;

      const byte* const bytes = reinterpret_cast<const byte*>(data.c_str());
      const uint size = static_cast<uint>(data.size());

      AddParam(sign, math::GenerateMD5(bytes, size).ToString());
    }

    nstl::string query("?");

    const int pcount = params.size();

    for (int i = 0, last = pcount - 1; i < last; ++i)
    {
      Params::const_reference p = params[i];

      query += p.name;
      query += "=";
      NStr::UrlEncode(query, p.value, false, false);
      query += "&";
    }

    for (int i = pcount - 1, last = pcount; i < last; ++i)
    {
      Params::const_reference p = params[i];

      query += p.name;
      query += "=";
      NStr::UrlEncode(query, p.value, false, false);
    }

    return query;
  }

//////////////////////////////////////////////////////////////////////////

  void HttpRequest::SetRID(const int value)
  {
    static const nstl::string name("rid");

    if (value > 0)
      AddQueryParam(name, value);
  }

  void HttpRequest::SetUID(const nstl::string& value)
  {
    static const nstl::string name("uid");

    if (!value.empty())
      AddQueryParam(name, value);
  }

  void HttpRequest::SetKey(const nstl::string& value)
  {
    static const nstl::string name("key");

    if (!value.empty())
      AddQueryParam(name, value);
  }

//////////////////////////////////////////////////////////////////////////

  RequestSender::RequestSender(const nstl::string& uri, const nstl::string& data, const bool handleResponse)
    : uri(uri)
    , data(data)
    , handleResponse(handleResponse)
    , response()
    , ok(false)
    , finished(false)
    , curl(NULL)
    , json()
  {

  }

  RequestSender::~RequestSender()
  {
    Cleanup();
    Finish();
  }

  void RequestSender::Work(volatile bool&)
  {
    struct Local
    {
      static size_t WriteCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
      {
        const size_t bytes = size * nmemb;

        if (bytes)
          reinterpret_cast<nstl::string*>(userdata)->append(ptr, ptr + (size * nmemb));

        return bytes;
      }
    };

    if (uri.empty())
      return;

    curl = curl_easy_init();

    if (!curl)
    {
      ErrorTrace("HTTP: Failed to initialize curl");
      return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Local::WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_error);

    if (!data.empty())
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

    const CURLcode result = curl_easy_perform(curl);

    Cleanup();

    DevTrace("HTTP SEND: %s", uri.c_str());
    DevTrace("HTTP RECV: %s", response.c_str());

    if (result == CURLE_OK)
    {
      ok = ProcessResponse();
    }
    else
    {
      ok = false;

      response.clear();

      ErrorTrace("HTTP: CURL error - %d (%s)", static_cast<int>(result), curl_error);
    }

    Finish();
  }

  void RequestSender::Cleanup()
  {
    if (!curl)
      return;

    curl_easy_cleanup(curl);

    curl = NULL;
  }

  void RequestSender::Finish()
  {
    finished = true;
  }

  bool RequestSender::ProcessResponse()
  {
    if (!handleResponse)
      return true;

    if (response.empty())
    {
      ErrorTrace("HTTP: got empty response");
      return false;
    }

    const char* const jsonDocBegin = response.c_str();
    const char* const jsonDocEnd = response.c_str() + response.size();

    Json::Reader parser;

    if (!parser.parse(jsonDocBegin, jsonDocEnd, json, false))
    {
      const std::string error(parser.getFormatedErrorMessages());

      ErrorTrace("HTTP: Failed to parse JSON! %s", error.c_str());
      return false;
    }

    const Json::Value& jsonResponse = json["response"];

    if (!jsonResponse)
    {
      ErrorTrace("HTTP: Malformed response (missing response itself)");
      return false;
    }

    // TODO: ?
    json = jsonResponse;

    const Json::Value& ok = json["ok"];
    const Json::Value& ec = json["ec"];

    if (!ok || !ec)
    {
      ErrorTrace("HTTP: Malformed response (missing status)");
      return false;
    }

    if (!ok.asBool())
    {
      const Json::Value& error = json["error"];

      ErrorTrace("HTTP: Request failed - %d (%s)", ec.asInt(), (!!error ? error.asCString() : "n/a"));
      return false;
    }

    NI_VERIFY(ec.asInt() == 0, "Bad response", return false);

    DevTrace("HTTP: Request complete");

    return true;
  }

  ResponseStatus::Enum NGameX::Http::RequestSender::GetResponseStatus() const
  {
    if (!finished)
      return ResponseStatus::Pending;

    if (!ok)
      return ResponseStatus::Failed;

    return ResponseStatus::OK;
  }

  StrongMT<RequestSender> RequestSender::Create(const nstl::string& uri, const nstl::string& data, const bool handleResponse)
  {
    const StrongMT<RequestSender> job(new RequestSender(uri, data, handleResponse));

    return job;
  }

//////////////////////////////////////////////////////////////////////////

  StrongMT<RequestSender> CreateRequestSender(const HttpRequest& request, const bool handleResponse /*= false*/)
  {
    return RequestSender::Create(request.uri, nstl::string(), handleResponse);
  }

  StrongMT<RequestSender> CreateRequestSender(const HttpRequest& request, const nstl::string& data, const bool handleResponse /*= false*/)
  {
    return RequestSender::Create(request.uri, data, handleResponse);
  }

  StrongMT<RequestSender> SendRequest(const HttpRequest& request, const bool handleResponse /*= false*/)
  {
    StrongMT<RequestSender> sender;
    StrongMT<threading::JobThread> worker(SendRequestAsync(sender, request, handleResponse));

    // CURL timeout + some more
    if (!worker->Wait(30000 + 2000))
    {
      ErrorTrace("HTTP: Request sender timed out!");
    }

    return sender;
  }

  StrongMT<RequestSender> SendRequest(const HttpRequest& request, const nstl::string& data, const bool handleResponse /*= false*/)
  {
    StrongMT<RequestSender> sender;
    StrongMT<threading::JobThread> worker(SendRequestAsync(sender, request, data, handleResponse));

    // CURL timeout + some more
    if (!worker->Wait(30000 + 2000))
    {
      ErrorTrace("HTTP: Request sender timed out!");
    }

    return sender;
  }

  StrongMT<threading::JobThread> SendRequestAsync(StrongMT<RequestSender>& sender, const HttpRequest& request, const bool handleResponse /*= false*/)
  {
    sender = CreateRequestSender(request, handleResponse);

    const StrongMT<threading::JobThread> worker(new threading::JobThread(sender, "SendHttpRequestAsync", 5000));

    return worker;
  }

  StrongMT<threading::JobThread> SendRequestAsync(StrongMT<RequestSender>& sender, const HttpRequest& request, const nstl::string& data, const bool handleResponse /*= false*/)
  {
    sender = CreateRequestSender(request, data, handleResponse);

    const StrongMT<threading::JobThread> worker(new threading::JobThread(sender, "SendHttpRequestAsync", 5000));

    return worker;
  }

//////////////////////////////////////////////////////////////////////////

} // namespace Http
} // namespace NGameX

NI_DEFINE_REFCOUNT( NGameX::Http::RequestSender );


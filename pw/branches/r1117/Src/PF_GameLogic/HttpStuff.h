#pragma once

#include "System/JobThread.h"

#include <Vendor/libcurl/include/curl/curl.h>
#include <Vendor/JsonCpp/include/json/json.h>

#include <sstream>

namespace NGameX
{
  namespace Http
  {
    struct HttpQueryParam
    {
      nstl::string name;
      nstl::string value;

      HttpQueryParam()
        : name()
        , value()
      {

      }

      template <typename T>
      HttpQueryParam(const nstl::string& _name, const T& _value)
        : name(_name)
      {
        SetValue(_value);
      }

      template <typename T>
      void Set(const nstl::string& _name, const T& _value)
      {
        name = _name;

        SetValue(_value);
      }

      void SetValue(const nstl::string& _value)
      {
        value = _value;
      }

      void SetValue(const std::string& _value)
      {
        value = _value.c_str();
      }

      void SetValue(const char* const (&_value))
      {
        value = _value;
      }

      template <typename T>
      void SetValue(const T& _value)
      {
        std::ostringstream ss;

        ss << _value;

        SetValue(ss.str());
      }
    };

    inline bool operator==(const HttpQueryParam& lhs, const HttpQueryParam& rhs)
    {
      return lhs.name == rhs.name;
    }
    
    inline bool operator!=(const HttpQueryParam& lhs, const HttpQueryParam& rhs)
    {
      return lhs.name != rhs.name;
    }

    inline bool operator<(const HttpQueryParam& lhs, const HttpQueryParam& rhs)
    {
      return lhs.name < rhs.name;
    }

    struct HttpQuery
    {
      typedef nstl::vector<HttpQueryParam> Params;

      HttpQuery()
        : params()
      {

      }

      nstl::string Build(const nstl::string& secret);

      template <typename T>
      void AddParam(const nstl::string& name, const T& value)
      {
        Params::iterator it = params.begin();
        Params::iterator it_end = params.end();
        for (; it != it_end; ++it)
        {
          Params::reference p = *it;

          if (p.name == name)
          {
            p.SetValue(value);
            return;
          }
        }

        params.push_back();
        params.back().Set(name, value);
      }

      void RemoveParam(const nstl::string& name)
      {
        Params::iterator it = params.begin();
        Params::iterator it_end = params.end();
        for (; it != it_end; ++it)
        {
          if (it->name == name)
          {
            params.erase(it);
            return;
          }
        }
      }
    private:
      Params params;
    };

    struct HttpRequest
    {
      const nstl::string& location;

      nstl::string uri;

      explicit HttpRequest(const nstl::string& location)
        : location(location)
        , uri(location)
        , query()
      {

      }

      void SetRID(const int value);
      void SetUID(const nstl::string& value);
      void SetKey(const nstl::string& value);

      template <typename T>
      void AddQueryParam(const nstl::string& name, const T& value)
      {
        query.AddParam(name, value);
      }

      void RemoveQueryParam(const nstl::string& name)
      {
        query.RemoveParam(name);
      }

      void Build(const nstl::string& secret = nstl::string())
      {
        uri = location + query.Build(secret);
      }
    private:
      HttpRequest();
      HttpRequest& operator=(const HttpRequest&);

      HttpQuery query;
    };

    namespace ResponseStatus
    {
      enum Enum
      {
        Invalid,
        Failed,
        Pending,
        OK,
      };
    }

    class RequestSender : public BaseObjectMT, public threading::IThreadJob
    {
      NI_DECLARE_REFCOUNT_CLASS_2(RequestSender, BaseObjectMT, threading::IThreadJob);
    public:
      static StrongMT<RequestSender> Create(const nstl::string& uri, const nstl::string& data, const bool handleResponse);

      virtual ~RequestSender();

      ResponseStatus::Enum GetResponseStatus() const;

      const nstl::string& GetResponse() const { return response; }
      const Json::Value& GetResponseJson() const { return json; }
    protected:
      RequestSender(const nstl::string& uri, const nstl::string& data, const bool handleResponse);

      virtual void Work(volatile bool&);
    private:
      void Cleanup();
      void Finish();

      bool ProcessResponse();

      const nstl::string uri;
      const nstl::string data;

      const bool handleResponse;

      nstl::string response;

      volatile bool ok;
      volatile bool finished;

      CURL *curl;

      char curl_error[CURL_ERROR_SIZE];

      Json::Value json;
    };

    nstl::string BuildLocation(const nstl::string& host, const nstl::string& path);

    StrongMT<RequestSender> CreateRequestSender(const HttpRequest& request, const bool handleResponse = false);
    StrongMT<RequestSender> CreateRequestSender(const HttpRequest& request, const nstl::string& data, const bool handleResponse = false);

    StrongMT<RequestSender> SendRequest(const HttpRequest& request, const bool handleResponse = false);
    StrongMT<RequestSender> SendRequest(const HttpRequest& request, const nstl::string& data, const bool handleResponse = false);

    StrongMT<threading::JobThread> SendRequestAsync(StrongMT<RequestSender>& sender, const HttpRequest& request, const bool handleResponse = false);
    StrongMT<threading::JobThread> SendRequestAsync(StrongMT<RequestSender>& sender, const HttpRequest& request, const nstl::string& data, const bool handleResponse = false);
  }
}


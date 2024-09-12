#ifndef WEBJSONCLIENT_H_INCLUDED
#define WEBJSONCLIENT_H_INCLUDED

namespace Json
{
  class Value;
}


namespace webClient
{

class IJsonClient : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IJsonClient, IBaseInterfaceMT );

public:
  virtual bool PerformJsonPOST( const char * url, const Json::Value & request, Json::Value & answer ) = 0;
};

IJsonClient * NewJsonClient( bool _dumpJson, bool _prettyJson );

} //namespace webClient

#endif //WEBJSONCLIENT_H_INCLUDED

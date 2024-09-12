#include "stdafx.h"
#include "WebJsonClient.h"
#include "System/SafeTextFormatStl.h"
#include "WebClient.h"
#include <json/reader.h>
#include <json/writer.h>


namespace webClient
{

class JsonClient : public BaseObjectMT, public IJsonClient
{
  NI_DECLARE_REFCOUNT_CLASS_2( JsonClient, BaseObjectMT, IJsonClient );

public:
  JsonClient( bool _dumpJson, bool _prettyJson ) :
  dumpJson( _dumpJson ), prettyJson( _prettyJson )
  {
    httpClient = NewHttpClient();
  }

protected:
  virtual bool PerformJsonPOST( const char * url, const Json::Value & request, Json::Value & answer );

private:
  const bool dumpJson, prettyJson;
  StrongMT<IHttpClient> httpClient;
};




IJsonClient * NewJsonClient( bool _dumpJson, bool _prettyJson )
{
  return new JsonClient( _dumpJson, _prettyJson );
}



bool JsonClient::PerformJsonPOST( const char * url, const Json::Value & request, Json::Value & answer )
{
  std::string requestText;
  if ( prettyJson )
  {
    Json::StyledWriter writer;
    requestText = writer.write( request );
  }
  else
  {
    Json::FastWriter writer;
    requestText = writer.write( request );
  }

  if ( dumpJson )
    DebugTrace( "JSON text:\n%s", requestText );

  string answerHeader, answerBody;
  if ( !httpClient->PerformPOST( url, requestText.c_str(), requestText.length(), answerHeader, answerBody ) )
    return false;

  if ( dumpJson )
    DebugTrace( "JSON text:\n%s", answerBody );

  Json::Reader reader;
  if ( !reader.parse( answerBody.begin(), answerBody.end(), answer ) ) {
    ErrorTrace( "JSON parse error: %s", reader.getFormatedErrorMessages().c_str() );
    if ( !dumpJson )
      DebugTrace( "JSON text:\n%s", answerBody );
    return false;
  }

  return true;
}

} //namespace webClient

NI_DEFINE_REFCOUNT( webClient::JsonClient );

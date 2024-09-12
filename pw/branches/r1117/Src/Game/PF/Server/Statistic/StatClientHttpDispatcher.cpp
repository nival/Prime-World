#include "stdafx.h"
#include "StatClientHttpDispatcher.h"


namespace StatisticService
{


static string     s_url = "http://localhost:8080/data/";

REGISTER_VAR( "stat_client_url", s_url, STORAGE_NONE );



string & ClientHttpDispatcher::DestUrl()
{
  return s_url;
}



ClientHttpDispatcher::ClientHttpDispatcher()
{
  httpClient = webClient::NewHttpClient();
}



bool ClientHttpDispatcher::DispatchChunk( const TMessageData & _data, unsigned _msgNumber )
{
  if ( !_data.size() )
    return true;

  time_t tstamp = 0;
  time( &tstamp );

  string url = s_url;
  url += NI_STRFMT( "?timestamp=%u", (unsigned)tstamp );

  string answerBody;
  string answerHdr;
  if ( !httpClient->PerformPOST( url.c_str(), &_data[0], _data.size(), answerHdr, answerBody ) )
    return false;

  if ( httpClient->GetResponseCode() != 200 )
    return false;

  DebugTrace( "Statistics data chunk uploaded. size=%u", _data.size() );
  return true;
}



bool ClientHttpDispatcher::GetPermittedEventsChunk( TMessageData & _data )
{
  MessageTrace( "Recieving permitted event data" );

  string answerBody;
  string answerHdr;
  if ( !httpClient->PerformGET( s_url.c_str(), answerHdr, answerBody ) )
    return false;

  if ( httpClient->GetResponseCode() != 200 )
    return false;

  _data.resize( answerBody.size() );
  if ( answerBody.size() )
    memcpy( &_data[0], &answerBody[0], answerBody.size() );

  MessageTrace( "Recieved permitted event data. size=%u", _data.size() );
  return true;
}

} //namespace StatisticService
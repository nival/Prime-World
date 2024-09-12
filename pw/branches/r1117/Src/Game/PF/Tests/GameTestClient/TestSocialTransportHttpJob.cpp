#include "stdafx.h"
#include "TestSocialTransportHttpJob.h"
#include "HttpGatewayProtoVersion.h"
#include "System/SafeTextFormatStl.h"
#include <json/reader.h>
#include <json/writer.h>


namespace GtcSocial
{

TransportHttpJob::TransportHttpJob( const SSocialConfig & socConfig ) :
_socConfig( socConfig )
{
  httpClient = webClient::NewJsonClient( _socConfig.dumpJson, _socConfig.prettyJson );
}



void TransportHttpJob::AddRequest( IJsonRequestItem * item )
{
  threading::MutexLock lock( _incominMutex );
  _incominLine.push_back( item );
}



void TransportHttpJob::Apply()
{
  threading::MutexLock lock( _outgoinMutex );

  for ( TLine::iterator it = _outgoinLine.begin(); it != _outgoinLine.end(); ++it ) {
    StrongMT<IJsonRequestItem> item = *it;
    item->Apply();
  }
  _outgoinLine.clear();

  for ( TLine::iterator it = _failedLine.begin(); it != _failedLine.end(); ++it ) {
    StrongMT<IJsonRequestItem> item = *it;
    item->Failed();
  }
  _failedLine.clear();
}



void TransportHttpJob::Work( volatile bool & isRunning )
{
  while ( isRunning ) {
    if ( !ProcessRequests() )
      Sleep( 10 );
  }
}



bool TransportHttpJob::ProcessRequests()
{
  TLine head;

  {
    threading::MutexLock lock( _incominMutex );
    if ( _incominLine.empty() )
      return false;
    TLine::iterator end = _incominLine.begin();
    for ( int i = 0; end != _incominLine.end(); ++end, ++i )
      if ( _socConfig.jsonItemsPerRequest && ( i >= _socConfig.jsonItemsPerRequest ) )
        break;
    head.insert( head.begin(), _incominLine.begin(), end );
    _incominLine.erase( _incominLine.begin(), end );

    MessageTrace( "Pulled %d JSON request items from line; %d items left", head.size(), _incominLine.size() );
    if ( _incominLine.size() > 256 )
      WarningTrace( "JSON requests line overflowed!" );
  }

  Json::Value request;

  request["ver"] = NStr::StrFmt( "%d.%d.%d.gtc", Version::Major, Version::Minor, Version::Patch );

  for ( TLine::iterator it = head.begin(); it != head.end(); ++it ) {
    StrongMT<IJsonRequestItem> item = *it;
    item->DoIntoJson( request );
  }

  string url = _socConfig.gatewayUrl;
  url += "/x?action=mm";

  Json::Value answer;
  if ( httpClient->PerformJsonPOST( url.c_str(), request, answer ) )
  {
    Json::Value response = answer.get( "response", Json::Value() );
    if ( response.isObject() )
    {
      Json::Value ok = response.get( "ok", Json::Value() );
      if ( ok.isInt() && ok.asInt() == 1 )
      {
        Json::Value pvx = response.get( "pvx", Json::Value() );
        if ( pvx.isObject() )
        {
          for ( TLine::iterator it = head.begin(); it != head.end(); ++it ) {
            StrongMT<IJsonRequestItem> item = *it;
            item->ParseJsonBack( pvx ); //TODO: utilize value returned from 'ParseJsonBack'
          }

          {
            threading::MutexLock lock( _outgoinMutex );
            _outgoinLine.insert( _outgoinLine.end(), head.begin(), head.end() );
          }

          MessageTrace( "Successfully processed %d JSON request items", head.size() );
          return true;
        }
        else
          MessageTrace( "'pvx' tag not found in JSON reply" );
      }
      else
        MessageTrace( "'ok' tag not found in JSON reply" );
    }
    else
      MessageTrace( "'response' tag not found in JSON reply" );
  }

  //Failure case
  {
    threading::MutexLock lock( _outgoinMutex );
    _failedLine.insert( _failedLine.end(), head.begin(), head.end() );
    MessageTrace( "Failed to process %d JSON request items", head.size() );
  }

  return true;
}

} //namespace GtcSocial

NI_DEFINE_REFCOUNT( GtcSocial::IJsonRequestItem );
NI_DEFINE_REFCOUNT( GtcSocial::TransportHttpJob );

#include "stdafx.h"
#include "LogMonitorAgent.h"
#include "LogMonitorConfig.h"
#include "System/LogHelpers.h"
#include "System/SafeTextFormatStl.h"
#include "System/sleep.h"
#include <json/value.h>
#include <json/writer.h>


namespace logMonitor
{

Agent::Agent( Config * _cfg, const char * _serviceClass ) :
config( _cfg ),
epochScalarTime( 0 ),
processId( 0 ),
eventsSkipped( 0 ),
nextPushTime( 0 ),
currentPeriod( _cfg->defaultPushPeriod )
{
  SetupPrerequisites( _serviceClass );

  if ( !config->enabled )
    return;

  buffer = new LogBuffer;

  httpClient = webClient::NewHttpClient();

  GetSystemLog().AddNotifyCallback( buffer );

  MessageTrace( "Log monitor agent started. svc_id='%s', machine='%s', pid=%d, url='%s'", 
    serviceClass, machineName, processId, config->destUrl.c_str() );
}



Agent::~Agent()
{
  if ( buffer )
    GetSystemLog().RemoveNotifyCallback( buffer );
}



void Agent::SetupPrerequisites( const char * _serviceClass )
{
  serviceClass.reserve( 64 );
  NStr::UrlEncode( serviceClass, _serviceClass, true, false );

#if defined( NV_WIN_PLATFORM )
  processId = GetCurrentProcessId();
#elif defined( NV_LINUX_PLATFORM )
  processId = getpid();
#endif

  timer::DecodedTime epochTime;
  timer::SetupEpoch( epochTime );
  epochScalarTime = timer::DecodedTimeToScalar( epochTime );

#if defined( NV_WIN_PLATFORM )
  char compNameBuf[128];
  if ( GetEnvironmentVariable( "COMPUTERNAME", compNameBuf, 128 ) > 0 )
    NStr::UrlEncode( machineName, compNameBuf, true, false );
  else
    machineName = "unknown";
#elif defined( NV_LINUX_PLATFORM )
  machineName = "unknown";
#endif
}



void Agent::Poll()
{
  PullNewEvents();

  PushEvents();
}



void Agent::PullNewEvents()
{
  if ( !buffer )
    return;

  EventQueue newEvents;
  unsigned skipped = 0;
  buffer->PopEvents( newEvents, skipped );

  eventsSkipped += skipped;

  events.insert( events.end(), newEvents.begin(), newEvents.end() );
}



void Agent::PushEvents()
{
  if ( !httpClient )
    return;

  if ( events.empty() )
    return;

  timer::Time now = timer::Now();

  if ( now < nextPushTime )
    return;

  Json::Value request;
  int eventsNumber = 0;
  EventQueue::iterator eraseTo = PackEvents( request, eventsNumber );

  std::string requestText;
  {
    Json::FastWriter writer;
    requestText = writer.write( request );
  }

  std::string url = NI_STRFMT( "%s?host=%s&sid=%s&pid=%d&skipped=%d", config->destUrl, machineName, serviceClass, processId, eventsSkipped );

  string answerHdr, answerBody;
  if ( httpClient->PerformPOST( url.c_str(), requestText.c_str(), requestText.length(), answerHdr, answerBody ) )
  {
    long response = httpClient->GetResponseCode();
    if ( response == 200 )
    {
      DebugTrace( "Messages posted to log server. evt_num=%d", eventsNumber );

      currentPeriod = config->defaultPushPeriod;
      nextPushTime = now + currentPeriod;

      events.erase( events.begin(), eraseTo );
      eventsSkipped = 0;
      return;
    }
    else
    {
      ErrorTrace( "Log server returned HTTP error. code=%d, answer='%s', evt_num=%d", response, answerHdr, eventsNumber );
    }
  }

  currentPeriod = currentPeriod * 2.0f;
  currentPeriod = Min( currentPeriod, (timer::Time)config->maxPushPeriod );
  nextPushTime = now + currentPeriod;
}



EventQueue::iterator Agent::PackEvents( Json::Value & request, int & packednumber )
{
  request = Json::Value( Json::arrayValue );

  EventQueue::iterator it = events.begin();

  packednumber = 0;
  for ( ; ( it != events.end() ) && ( packednumber < config->sendPackSize ); ++packednumber, ++it )
  {
    StrongMT<BufferedEvent> evt = *it;

    Json::Value item;

    const NLogg::SEntryInfo & info = evt->EntryInfo();

    std::string datetime = NI_STRFMT( "%04u.%02u.%02u %02u:%02u:%02u", info.time.wYear, info.time.wMonth, info.time.wDay, info.time.wHour, info.time.wMinute, info.time.wSecond );

    timer::Time unixtime = DecodedTimeToScalar( info.time ) - epochScalarTime;
    item["tm"] = unixtime;
    item["datetime"] = datetime;
    item["type"] = NLogg::MessageLevelToStringFull( info.level );
    item["msg"] = evt->Text().c_str();
    item["channel"] = info.channel ? info.channel : "";
    item["file"] = info.filename ? info.filename : "";
    item["line"] = info.line;

    request.append( item );
  }

  return it;
}






class AgentParallelPollerJob : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( AgentParallelPollerJob, threading::IThreadJob, BaseObjectMT );

public:
  AgentParallelPollerJob( Agent * _ag ) :
  agent( _ag )
  {}

private:
  StrongMT<Agent>                 agent;

  virtual void Work( volatile bool & isRunning )
  {
    while ( isRunning )
    {
      agent->Poll();
      nival::sleep( 100 );
    }
  }
};



AgentParallelPoller::AgentParallelPoller( Agent * _ag )
{
  thread = new threading::JobThread( new AgentParallelPollerJob( _ag ), "LogMonitorAgent" );
}



AgentParallelPoller::~AgentParallelPoller()
{
  thread = 0;
}

} //namespace logMonitor

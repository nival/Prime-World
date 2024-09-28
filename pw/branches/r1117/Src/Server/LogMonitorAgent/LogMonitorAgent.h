#ifndef LOGMONITORAGENT_H_INCLUDED
#define LOGMONITORAGENT_H_INCLUDED

#include "LogMonitorBuffer.h"
#include "Server/WebClient/WebClient.h"
#include "System/JobThread.h"


namespace Json
{
  class Value;
}


namespace logMonitor
{

class Config;


class Agent : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( Agent, BaseObjectMT );

public:
  Agent( Config * _cfg, const char * _serviceClass );
  ~Agent();

  void Poll();

private:
  Strong<Config>        config;

  timer::Time           epochScalarTime;
  string                machineName;
  unsigned              processId;
  string                serviceClass;

  StrongMT<LogBuffer>   buffer;

  EventQueue            events;
  unsigned              eventsSkipped;

  timer::Time           nextPushTime;
  timer::Time           currentPeriod;

  StrongMT<webClient::IHttpClient>  httpClient;

  void SetupPrerequisites( const char * _serviceClass );
  void PullNewEvents();
  void PushEvents();
  EventQueue::iterator PackEvents( Json::Value & request, int & packednumber );
};



class AgentParallelPoller : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( AgentParallelPoller, BaseObjectMT );

public:
  AgentParallelPoller( Agent * _ag );
  ~AgentParallelPoller();

private:
  StrongMT<threading::JobThread>  thread;
};

} //namespace logMonitor

#endif //LOGMONITORAGENT_H_INCLUDED

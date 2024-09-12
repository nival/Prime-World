#pragma once

#include "TestSocialTransport.h"
#include "System/JobThread.h"
#include "Server/WebClient/WebJsonClient.h"

namespace Json
{
  class Value;
}


namespace GtcSocial
{

class IJsonRequestItem : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IJsonRequestItem, IBaseInterfaceMT );

public:
  virtual void DoIntoJson( Json::Value & requestRoot ) = 0;
  virtual bool ParseJsonBack( const Json::Value & answerRoot ) = 0;
  virtual void Apply() = 0;
  virtual void Failed() = 0;
};



class TransportHttpJob : public BaseObjectMT, public threading::IThreadJob
{
  NI_DECLARE_REFCOUNT_CLASS_2( TransportHttpJob, BaseObjectMT, threading::IThreadJob );

public:
  TransportHttpJob( const SSocialConfig & socConfig );

  void AddRequest( IJsonRequestItem * item );
  void Apply();

private:
  typedef list<StrongMT<IJsonRequestItem>> TLine;

  const SSocialConfig _socConfig;
  threading::Mutex _incominMutex, _outgoinMutex;
  TLine _incominLine, _outgoinLine, _failedLine;

  StrongMT<webClient::IJsonClient>  httpClient;

  //threading::IThreadJob
  virtual void Work( volatile bool & isRunning );

  bool ProcessRequests();
  bool PerformRequest( Json::Value & answer, const Json::Value & request );
};

} //namespace GtcSocial

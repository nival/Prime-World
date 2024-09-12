#ifndef STATCLIENTHTTPDISPATCHER_H_INCLUDED
#define STATCLIENTHTTPDISPATCHER_H_INCLUDED

#include "GameStatClient.h"
#include "Server/WebClient/WebClient.h"

namespace StatisticService
{

class ClientHttpDispatcher : public IStatDataDispatcher, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( ClientHttpDispatcher, IStatDataDispatcher, BaseObjectMT );

public:
  ClientHttpDispatcher();

protected:
  //IStatDataDispatcher
  virtual bool DispatchChunk( const TMessageData & _data, unsigned _msgNumber );
  virtual bool GetPermittedEventsChunk( TMessageData & _data );

protected:
  static string & DestUrl();

private:
  StrongMT<webClient::IHttpClient>  httpClient;
};

} //namespace StatisticService

#endif // STATCLIENTHTTPDISPATCHER_H_INCLUDED

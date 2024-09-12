#ifndef CENSORCLIENT_H_INCLUDED
#define CENSORCLIENT_H_INCLUDED

#include "ICensorClient.h"
#include "CensorSettings.h"
#include "CensorJob.h"
#include "Server/WebClient/WebClient.h"
#include <vector>
#include <list>
#include "System/JobThread.h"


namespace censorship
{

class CensorWorker;

class CensorClient : public ICensorClient, public BaseObjectMT
{
  friend class CensorWorker;

  NI_DECLARE_REFCOUNT_CLASS_2( CensorClient, ICensorClient, BaseObjectMT );

public:
  CensorClient( Settings * _sett );
  ~CensorClient();

  //ICensorClient
  virtual TRequestId Check( TAuxId _auxId, ICensorClientCallback * _callback, const wstring & _text );
  virtual void Poll();

private:
  typedef std::list<StrongMT<CheckJob> > Jobs;
  StrongMT<Settings>                sett;
  TRequestId                        nextRequestId;

  threading::Mutex                  mutex;
  std::vector<StrongMT<threading::JobThread> >  workers;
  Jobs                              todoJobs, processedJobs;

  //Multithread:
  StrongMT<CheckJob> PopJob();
  void PushProcessedJob( CheckJob * job );
};

} //namespace censorship

#endif //CENSORCLIENT_H_INCLUDED

#include "stdafx.h"
#include "CensorClient.h"


namespace censorship
{

NI_ENUM_BEGIN_STD( ECheckResult );
  NI_ENUM_ITEM( Clean );
  NI_ENUM_ITEM( Dirty );
  NI_ENUM_ITEM( SvcFailure );
NI_ENUM_END_STD;


ICensorClient * CreateClient() { return new CensorClient( CreateSettingsFromConfig() ); }



class CensorWorker : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( CensorWorker, threading::IThreadJob, BaseObjectMT );
public:
  CensorWorker( CensorClient * _master ) :
  master( _master )
  {}

  virtual void Work( volatile bool & isRunning );

private:
  WeakMT<CensorClient>  master;

  StrongMT<CheckJob> PopJob();
  void PushProcessedJob( CheckJob * job );
};



CensorClient::CensorClient( Settings * _sett ) :
sett( _sett ),
nextRequestId( 1 )
{
  for ( int i = 0; i < sett->workers; ++i )
    workers.push_back( new threading::JobThread( new CensorWorker( this ), "CensorWorker" ) );
}



CensorClient::~CensorClient()
{
  for ( size_t i = 0; i < workers.size(); ++i )
    workers[i]->AsyncStop();
  
  workers.clear();
}



TRequestId CensorClient::Check( TAuxId _auxId, ICensorClientCallback * _callback, const wstring & _text )
{
  TRequestId reqId = nextRequestId++;

  StrongMT<CheckJob> job = new CheckJob( sett, timer::Now(), reqId, _auxId, _callback, _text );

  DebugTrace( "CleanSpeak: Adding new request. req=%d, aux=%d, text='%s'", reqId, _auxId, _text );

  threading::MutexLock lock( mutex );

  //Overflow
  if ( sett->queueLimit )
    NI_VERIFY( (int)todoJobs.size() < sett->queueLimit, "", return 0 );

  todoJobs.push_back( job );
  return reqId;
}



void CensorClient::Poll()
{
  Jobs jobs;

  {
    threading::MutexLock lock( mutex );
    processedJobs.swap( jobs );
  }

  for ( Jobs::iterator it = jobs.begin(); it != jobs.end(); ++it )
  {
    StrongMT<CheckJob> job = *it;
    job->Finish();
  }

  if ( sett->queueTimelimit > 0 )
  {
    timer::Time queueTimelimit = timer::Now() - sett->queueTimelimit;

    threading::MutexLock lock( mutex );

    for ( Jobs::iterator it = todoJobs.begin(); it != todoJobs.end(); )
      if ( (*it)->CreationTime() < queueTimelimit )
      {
        StrongMT<CheckJob> job = *it;
        ErrorTrace( "CleanSpeak: Request timed out. req=%d, aux=%d", job->RequestId(), job->AuxId() );
        it = todoJobs.erase( it );

        processedJobs.push_back( job );
      }
      else
        ++it;
  }
}



StrongMT<CheckJob> CensorClient::PopJob()
{
  threading::MutexLock lock( mutex );

  if ( todoJobs.empty() )
    return 0;

  StrongMT<CheckJob> job = todoJobs.front();
  todoJobs.pop_front();
  return job;
}



void CensorClient::PushProcessedJob( CheckJob * job )
{
  threading::MutexLock lock( mutex );

  if ( sett->outQueueLimit )
    NI_VERIFY( (int)processedJobs.size() < sett->outQueueLimit, "", return );

  processedJobs.push_back( job );
}




void CensorWorker::Work( volatile bool & isRunning )
{
  StrongMT<webClient::IHttpClient> httpClient = webClient::NewHttpClient();
  webClient::TRequestProperties reqProp;
  reqProp.push_back( "Content-Type: application/x-www-form-urlencoded" );
  httpClient->SetRequestProperies( reqProp );

  while ( isRunning )
  {
    StrongMT<CheckJob> job = PopJob();

    if ( !job )
    {
      //No job to do. Let's get some sleep
      threading::Sleep( 10 );
      continue;
    }

    job->Perform( httpClient );

    PushProcessedJob( job );
  }
}


StrongMT<CheckJob> CensorWorker::PopJob()
{
  if ( StrongMT<CensorClient> locked = master.Lock() )
    return locked->PopJob();

  return 0;
}



void CensorWorker::PushProcessedJob( CheckJob * job )
{
  if ( StrongMT<CensorClient> locked = master.Lock() )
    locked->PushProcessedJob( job );
}

} //namespace censorship

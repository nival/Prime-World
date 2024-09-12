#include <System/systemStdAfx.h>
#include <Server/RPC/RPC.h>
#include "SessionConnector.h"

#include "HybridServer/PeeredImpl.h"
#include "HybridServer/RPeered.auto.h"

namespace Peered
{
  bool SchedulerInstance::Step( NHPTimer::FTime time )
  {
    StrongMT<Peered::CommandsScheduler> _server = Get();
    if (!_server)
    {
      return false;
    }

    //Constrain steps on 0.1 sec
    const NHPTimer::FTime WorldStep = 0.1;

    if ( nextStepTime < 0 )
      nextStepTime = time; //First step
    else
      if ( time < nextStepTime )
        return false;

    nextStepTime += WorldStep;

    _server->Step();

    return true;
  }

SessionConnector::SessionConnector()
{
  currentScheduler_ = createScheduler();
}

RIGameServer* SessionConnector::Connect()
{
  StrongMT<SchedulerInstance> tmp = currentScheduler_;
  printf("SessionConnector::Connect\n");
  if (currentScheduler_->Get()->GetNumberOfClients() == 9)
  {
    printf("Session is ready\n");
    currentScheduler_ = createScheduler();
  }

  return RemotePtr<Peered::RIGameServer>((Peered::IGameServer*)(tmp->Get()));
}

void SessionConnector::Step()
{
  static int count = 0;
  bool blog = false;

  NHPTimer::FTime t = NHPTimer::GetScalarTime();
  for ( SchedulersT::iterator it = schedulers_.begin(); it != schedulers_.end(); )
  {
    if ( (*it)->Get() )
    {
      if ((*it)->Step( t ))
        blog = true;

      ++it;
    }
    else
    {
      it = schedulers_.erase( it );
    }
  }

  ++count;
  if (blog && count > 100)
  {
    printf("Schedulers step(%d): %f\n", schedulers_.size(), NHPTimer::GetScalarTime() - t);
    count = 0;
  }
}

StrongMT<SchedulerInstance> SessionConnector::createScheduler()
{
  Peered::SchedulerData data;
  data.simulationStep = 100;
  data.dumpStepsMaxCount = 0; 
  data.trustGap = 0;
  data.serverId = 0;
  data.afcStepsCount = 0;
  data.disconnectionGap = 0;
  data.disconnectionWaterline = 0;
  data.connectionTimeout = 0;
  data.confirmFrequency = 1;
  data.firstConnectionTimeout = 0;

  StrongMT<SchedulerInstance> scheduler = new SchedulerInstance(new Peered::CommandsScheduler( data ));
  schedulers_.push_back(scheduler);
  return scheduler;
}


}

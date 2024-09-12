#pragma once

#include <Game/PF/HybridServer/PeeredImpl.h>

namespace Peered
{

class RIGameServer;

class SchedulerInstance : public BaseObjectMT
{
   NI_DECLARE_REFCOUNT_CLASS_1( SchedulerInstance, BaseObjectMT );
public:
  SchedulerInstance() : nextStepTime( 0 ) {}
  SchedulerInstance( Peered::CommandsScheduler * _server ) : nextStepTime( -1.0 ), server( _server ) {}

  bool Step( NHPTimer::FTime time );

  StrongMT<Peered::CommandsScheduler> Get() { return server.Lock(); }

private:
  WeakMT<Peered::CommandsScheduler>  server;
  NHPTimer::FTime  nextStepTime;
};

REMOTE struct SessionConnector : BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( SessionConnector, BaseObjectMT )
  RPC_ID();

  SessionConnector();
  REMOTE RIGameServer* Connect();
  void Step();

  typedef list<StrongMT<Peered::SchedulerInstance>>  SchedulersT;
  SchedulersT schedulers_;

private:
  StrongMT<SchedulerInstance> createScheduler();

  StrongMT<SchedulerInstance> currentScheduler_;
};

} //namespace Peered

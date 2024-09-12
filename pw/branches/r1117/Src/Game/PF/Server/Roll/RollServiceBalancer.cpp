#include "stdafx.h"
#include "RollServiceBalancer.h"
#include "RollInstance.h"
#include "RollConfig.h"
#include "RRollInstance.auto.h"


namespace roll
{

Balancer::Balancer()
{
  config = CreateConfigFromStatics();
}



void Balancer::ReloadConfig()
{
  config->ReloadConfig();
}



void Balancer::Poll()
{
  timer::Time t = timer::Now();

  StrongMT<RollConfig> cfg = config->Cfg();

  for ( Slots::iterator it = instances.begin(); it != instances.end(); )
  {
    Slots::iterator next = it;
    ++next;

    if ( it->ptr->GetStatus() != rpc::Connected )
    {
      WarningTrace( "Lost connection to roll instance: id=%s, load=%d", it->serviceId, it->load );
      instances.erase( it );
    }
    else if ( t > it->lastUpdate + cfg->instanceUpdateTimeout )
    {
      WarningTrace( "Connection to roll instance timed out: id=%s, load=%d, timeout=%.1f", it->serviceId, it->load, cfg->instanceUpdateTimeout );
      instances.erase( it );
    }

    it = next;
  }
}



void Balancer::LoadNotify( RIInstance* inst, const string & serviceId, int currentLoad )
{
  NI_VERIFY( inst, "", return );

  for ( Slots::iterator it = instances.begin(); it != instances.end(); ++it )
    if ( it->serviceId == serviceId )
    {
      it->load = currentLoad;
      it->lastUpdate = timer::Now();
      MessageTrace( "Roll instance updated: id=%s, load=%d", serviceId, currentLoad );
      return;
    }

  instances.push_back( Slot( serviceId, inst, currentLoad ) );

  MessageTrace( "Roll instance added: id=%s, load=%d", serviceId, currentLoad );
}



RIInstance * Balancer::AllocateInstance()
{
  DebugTrace( "Roll instance requested from balancer" );

  StrongMT<RollConfig> cfg = config->Cfg();

  for ( Slots::reverse_iterator it = instances.rbegin(); it != instances.rend(); ++it )
    if ( it->ptr->GetStatus() == rpc::Connected )
      if ( it->load < cfg->balancerSoftLimit )
        return it->ptr;

  StrongMT<RIInstance> result;
  int minLoad = 0;
  for ( Slots::reverse_iterator it = instances.rbegin(); it != instances.rend(); ++it )
    if ( !result || ( it->load < minLoad ) ) {
      result = it->ptr;
      minLoad = it->load;
    }

  if ( minLoad >= cfg->balancerHardLimit ) {
    ErrorTrace( "Roll instance allocation failed: overload" );
    return 0;
  }

  if ( !result )
    ErrorTrace( "Roll instance allocation failed: no valid instances" );

  return result;
}

} //namespace roll

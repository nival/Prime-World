#ifndef ROLLSERVICEBALANCER_H_INCLUDED
#define ROLLSERVICEBALANCER_H_INCLUDED

#include "RollBalancer.h"
#include "RollConfig.h"
#include <list>

namespace roll
{

class Balancer : public IBalancer, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Balancer, IBalancer, BaseObjectMT );

public:
  RPC_ID();

  Balancer();

  void ReloadConfig();
  void Poll();

  //IBalancer
  virtual void LoadNotify( RIInstance* inst, const string & serviceId, int currentLoad );
  virtual RIInstance * AllocateInstance();

private:
  struct Slot
  {
    string                serviceId;
    StrongMT<RIInstance>  ptr;
    timer::Time           lastUpdate;
    int                   load;

    Slot( const string & id, RIInstance * p, int ld ) :
    serviceId( id ), ptr( p ), lastUpdate( timer::Now() ), load( ld )
    {}
  };

  typedef std::list<Slot> Slots;

  StrongMT<IConfigProvider> config;
  Slots   instances;
};

} //namespace roll

#endif //ROLLSERVICEBALANCER_H_INCLUDED

#ifndef NEWLOGINSVCLINKINTERFACE_H_INCLUDED
#define NEWLOGINSVCLINKINTERFACE_H_INCLUDED

//#include "RdpTransport/RRdpFrontendAgentInterface.auto.h"
//#include <RPC/RPC.h>
#include "rpc/base.h"
#include "Network/Address.h"

namespace rdp_transport
{
  class IFrontendAgent;
}


namespace newLogin
{

class ISvcLink : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ISvcLink, IBaseInterfaceMT );

public:
  virtual bool Ready() const = 0;
  virtual const Transport::TServiceId & SvcId() const = 0;
  virtual const Network::NetAddress & FrontendSvcAddr() const = 0;
  virtual StrongMT<rdp_transport::IFrontendAgent> Get() = 0;
};



class ISvcLinkDict : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ISvcLinkDict, IBaseInterfaceMT );

public:
  virtual StrongMT<ISvcLink> GetSvcLink( const Transport::TServiceId & _svcId ) = 0;
};

} //namespace newLogin

#endif //NEWLOGINSVCLINKINTERFACE_H_INCLUDED

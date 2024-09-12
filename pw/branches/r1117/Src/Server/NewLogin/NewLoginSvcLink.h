#ifndef NEWLOGINSVCLINK_H_INCLUDED
#define NEWLOGINSVCLINK_H_INCLUDED

#include "NewLoginSvcLinkInterface.h"
#include "RdpTransport/RRdpFrontendAgentInterface.auto.h"
#include "rpc/IfaceRequester.h"

namespace rdp_transport
{
  class IFrontendAgent;
}


namespace newLogin
{

class SvcLink : public ISvcLink, public rpc::IfaceRequesterCallback<rdp_transport::RIFrontendAgent>, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_3( SvcLink, ISvcLink, rpc::IfaceRequesterCallback<rdp_transport::RIFrontendAgent>, BaseObjectMT );

public:
  SvcLink( rpc::GateKeeper * _gk, const Transport::TServiceId & _svcId, const Network::NetAddress & _frontSvcAddr );

  //ISvcLink
  virtual bool Ready() const;
  virtual const Transport::TServiceId & SvcId() const { return  svcId; }
  virtual const Network::NetAddress & FrontendSvcAddr() const { return frontendSvcAddr; }
  virtual StrongMT<rdp_transport::IFrontendAgent> Get();

  bool Poll();

  bool Failed() const { return failed; }

private:
  const Transport::TServiceId   svcId;
  const Network::NetAddress     frontendSvcAddr;
  StrongMT<rpc::IfaceRequester<rdp_transport::RIFrontendAgent> > remote;
  bool failed;

  virtual void onChangeState( rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<rdp_transport::RIFrontendAgent>> const & _ifacereq );
};

} //namespace newLogin

#endif //NEWLOGINSVCLINK_H_INCLUDED

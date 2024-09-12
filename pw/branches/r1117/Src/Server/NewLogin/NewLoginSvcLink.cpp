#include "stdafx.h"
#include "NewLoginSvcLink.h"
#include "NewLoginLog.h"

NI_DEFINE_REFCOUNT( newLogin::ISvcLink );
NI_DEFINE_REFCOUNT( newLogin::ISvcLinkDict );


namespace newLogin
{

SvcLink::SvcLink( rpc::GateKeeper * _gk, const Transport::TServiceId & _svcId, const Network::NetAddress & _frontSvcAddr ):
svcId( _svcId ),
frontendSvcAddr( _frontSvcAddr ),
failed( false )
{
  remote = new rpc::IfaceRequester<rdp_transport::RIFrontendAgent>;

  remote->init( _gk, svcId, rdp_transport::IFrontendAgent::InterfaceId, &GetSystemLog(), 0, this );
}



bool SvcLink::Ready() const
{
  if ( failed )
    return false;

  return remote->isopen();
}



StrongMT<rdp_transport::IFrontendAgent> SvcLink::Get()
{
  if ( failed )
    return 0;

  if ( !remote->isopen() )
    return 0;

  return remote->iface().Get();
}



bool SvcLink::Poll()
{
  remote->step();

  return !failed;
}



void SvcLink::onChangeState( rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<rdp_transport::RIFrontendAgent>> const & _ifacereq )
{
  if ( _st == rpc::IfaceRequesterState::CLOSED )
  {
    NEWLOGIN_LOG_WRN( "Lost connection to service. svc_id=%s", svcId.c_str() );

    failed = true;
  }
  else if ( _st == rpc::IfaceRequesterState::OPENED )
  {
    NEWLOGIN_LOG_MSG( "Connected to service. svc_id=%s", svcId.c_str() );
  }
}

} //namespace newLogin
